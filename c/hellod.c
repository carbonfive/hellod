#include <ev.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

/*
 * Thanks to:
 *
 * http://codefundas.blogspot.com/2010/09/create-tcp-echo-server-using-libev.html
 * http://github.com/coolaj86/libev-examples
 *
 * and especially
 *
 * http://comments.gmane.org/gmane.comp.lib.ev/1424
 * where Brandon Black says:
 *
 * The most generic answer is
 * this: create both reader and writer watchers for the socket
 * separately, but only activate the read watcher when you need to
 * receive traffic, and only active the write watcher when you have
 * buffered data ready to write to the socket.  You can enable and
 * disable them independently with ev_io_start() and ev_io_stop().  e.g.
 * for a simple HTTP server, you might start with only the read watcher
 * enabled.  Once you've processed a request and have a response ready to
 * send, you turn on the write watcher to drain the buffered data, then
 * turn it off again when the write buffer is empty.
 *
 */

// Our global event loop.
struct ev_loop *global_loop;

#define IO_COLLECT_INTERVAL 0.01

#define HEADER_TEXT "HTTP/1.1 200 OK\r\nConnection: close\r\nContent-Type: text/html\r\nContent-Length: %lu\r\n\r\n"
#define BODY_TEXT   "<html><body><h1>Hello World</h1></body></html>\r\n"

#define BUFFER_SIZE 1024

int port = 8085;
int total_clients = 0;

char *body;

void accept_cb(struct ev_loop *loop, struct ev_io *watcher, int revents);

typedef struct Connection *Connection;
typedef struct Buffer *Buffer;

struct Connection {
  int fd;
  struct ev_io *read_watcher;
  struct ev_io *write_watcher;
  Buffer in;
  Buffer out;
};

struct Buffer {
  char *data;
  int capacity;
  int len;
  int loc;
};

Connection conn_init();
void conn_close(Connection conn);
void conn_write(Connection conn, char *to_write, int to_write_len);
void conn_read_callback(struct ev_loop *loop, struct ev_io *watcher, int revents);
void conn_write_callback(struct ev_loop *loop, struct ev_io *watcher, int revents);

Buffer buffer_init();
void buffer_destroy(Buffer buffer);

Connection
conn_init(int fd)
{
  Connection conn;

  total_clients++;
  //puts("Succcessfully connected with client.");
  //printf("%d client(s) connected.\n", total_clients);

  conn = malloc(sizeof(struct Connection));
  conn->fd = fd;
  conn->read_watcher = (struct ev_io*) malloc(sizeof(struct ev_io));
  conn->read_watcher->data = (void*)conn;
  conn->write_watcher = (struct ev_io*) malloc(sizeof(struct ev_io));
  conn->write_watcher->data = (void*)conn;
  ev_io_init(conn->read_watcher, conn_read_callback, fd, EV_READ);
  ev_io_init(conn->write_watcher, conn_write_callback, fd, EV_WRITE);
  conn->in = buffer_init(BUFFER_SIZE);
  conn->out = buffer_init(BUFFER_SIZE);
  return conn;
}

void
conn_close(Connection conn)
{
  total_clients--;
  //printf("%d client(s) connected.\n", total_clients);

  ev_io_stop(global_loop, conn->read_watcher);
  ev_io_stop(global_loop, conn->write_watcher);
  shutdown(conn->fd, SHUT_RDWR);
  close(conn->fd);

  buffer_destroy(conn->in);
  buffer_destroy(conn->out);
  free(conn);
}

void
conn_write(Connection conn, char *to_write, int to_write_len)
{
  char *buffer_address = conn->out->data + conn->out->len;
  if (to_write_len > (conn->out->capacity - conn->out->len)) {
    perror("conn_write(): would overflow");
    return;
  }
  memmove(buffer_address, to_write, to_write_len);
  conn->out->len += to_write_len;
}

Buffer
buffer_init(int size)
{
  Buffer buffer;
  buffer = malloc(sizeof(struct Buffer));
  buffer->data = calloc(size, sizeof(char));
  buffer->capacity = size;
  buffer->len = 0;
  buffer->loc = 0;
  return buffer;
}

void
buffer_reset(Buffer buffer)
{
  bzero(buffer->data, buffer->capacity);
  buffer->len = 0;
  buffer->loc = 0;
}

void
buffer_destroy(Buffer buffer)
{
  free(buffer->data);
  free(buffer);
}

void
setnonblock(int fd)
{
  fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK);
}

int
bind_server_socket()
{
  int sd;
  struct sockaddr_in addr;

  if ((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket error");
    return -1;
  }
  int flags = 1;
  setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (void *)&flags, sizeof(flags));
  bzero(&addr, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = INADDR_ANY;
  if (bind(sd, (struct sockaddr*) &addr, sizeof(addr)) != 0) {
    perror("bind");
  }
  return sd;
}

void
check_error(Connection conn)
{
  if (errno == EAGAIN) return;
  if (errno == EINTR) return;
  if (errno == EWOULDBLOCK) return;

  perror("io error");
  conn_close(conn);
  return;
}

void
conn_read_callback(struct ev_loop *loop, struct ev_io *watcher, int revents)
{
  Connection conn;
  ssize_t bytes_read;

  if (EV_ERROR & revents) {
    perror("got invalid event");
  }

  conn = (Connection)watcher->data;
  bytes_read = recv(watcher->fd, conn->in->data, BUFFER_SIZE, 0);
  // error
  if (bytes_read < 0) {
    check_error(conn);
    return;
  }
  // connection closing
  if (bytes_read == 0) {
    conn_close(conn);
    return;
  }
  // read some stuff - right now we cheat and just assume it is a request :)
  ev_io_stop(loop, conn->read_watcher);

  /* char *headers = calloc(strlen(HEADER_TEXT) + 16, sizeof(char));*/
  /* sprintf(headers, HEADER_TEXT, strlen(HEADER_TEXT));*/
  /* conn_write(conn, headers, strlen(headers));*/
  /* conn_write(conn, BODY_TEXT, strlen(BODY_TEXT));*/
  conn_write(conn, body, strlen(body));

  ev_io_start(loop, conn->write_watcher);
}

void
conn_write_callback(struct ev_loop *loop, struct ev_io *watcher, int revents)
{
  Connection conn;
  ssize_t bytes_written;
  char *buffer_location;
  int buffer_length;
  int new_loc;

  conn = (Connection)watcher->data;
  buffer_location = conn->out->data + conn->out->loc;
  buffer_length = conn->out->len - conn->out->loc;

  bytes_written = send(conn->fd, buffer_location, buffer_length, 0);
  if (bytes_written < 0) {
    check_error(conn);
    return;
  }
  new_loc = conn->out->loc + bytes_written;
  if (new_loc > buffer_length) {
    perror("conn_write_callback(): wrote > buffer_length?!");
    return;
  }
  // if we haven't drained the buffer just move its loc so the next pass through the event loop can
  conn->out->loc = new_loc;
  // if we've drained our buffer, GTFO
  if (conn->out->loc >= conn->out->len) {
    /* buffer_reset(conn->out);*/
    /* ev_io_stop(loop, conn->write_watcher);*/
    /* ev_io_start(loop, conn->read_watcher);*/
    //printf("Done writing. Closing connection %i.\n", total_clients);
    conn_close(conn);
  }
}

void
accept_cb(struct ev_loop *loop, struct ev_io *w, int revents)
{
  int client_sd;
  struct sockaddr_in client_addr;
  socklen_t client_len = sizeof(client_addr);
  Connection conn;

  if (EV_ERROR & revents) {
    perror("got invalid event");
    return;
  }

  while ((client_sd = accept(w->fd, (struct sockaddr *)&client_addr, &client_len)) > 0) {
    setnonblock(client_sd);
    conn = conn_init(client_sd);
    ev_io_start(loop, conn->read_watcher);
  }

  if (errno != EAGAIN && errno != EINTR && errno != EWOULDBLOCK) {
    perror("accept error");
    return;
  }
}

void
exit_cleanly_callback(struct ev_loop *loop, struct ev_signal *watcher, int revents)
{
  puts("stopping.");
  ev_unloop(loop, EVUNLOOP_ALL);
  exit(0);
}

void
set_sig_handlers()
{
  ev_signal sigint_watcher;
  ev_signal sighup_watcher;
  ev_signal sigterm_watcher;

  ev_signal_init(&sigint_watcher, exit_cleanly_callback, SIGINT);
  ev_signal_init(&sighup_watcher, exit_cleanly_callback, SIGHUP);
  ev_signal_init(&sigterm_watcher, exit_cleanly_callback, SIGTERM);

  ev_signal_start(global_loop, &sigint_watcher);
  ev_signal_start(global_loop, &sighup_watcher);
  ev_signal_start(global_loop, &sigterm_watcher);
}

void
accept_connections()
{
  int sd;
  ev_io accept_watcher;

  sd = bind_server_socket();
  setnonblock(sd);
  listen(sd, 256);

  ev_io_init(&accept_watcher, accept_cb, sd, EV_READ);
  ev_io_start(global_loop, &accept_watcher);
  ev_loop(global_loop, 0);

  // We don't get here.
  close(sd);
}

void
setup_event_loop()
{
  global_loop = ev_default_loop(0);
  /* ev_set_io_collect_interval(global_loop, IO_COLLECT_INTERVAL);*/
}

void
prep_content_buffers()
{
  char *headers = calloc(strlen(HEADER_TEXT) + 16, sizeof(char));
  sprintf(headers, HEADER_TEXT, strlen(BODY_TEXT));
  body = calloc(strlen(HEADER_TEXT) + 16 + strlen(BODY_TEXT), sizeof(char));
  memmove(body, headers, strlen(headers));
  memmove(body+strlen(headers), BODY_TEXT, strlen(BODY_TEXT));
}

int
main(void)
{
  puts("started.");

  prep_content_buffers();
  setup_event_loop();
  /* set_sig_handlers();*/
  accept_connections();
  exit(0);
}

