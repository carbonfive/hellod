#include <ev.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>

/*
 * Thanks to:
 *
 * http://codefundas.blogspot.com/2010/09/create-tcp-echo-server-using-libev.html
 * http://github.com/coolaj86/libev-examples
 *
 */

#define BUFFER_SIZE 1024

int port = 8000;
int total_clients = 0;

void accept_cb(struct ev_loop *loop, struct ev_io *w, int revents);
void read_cb(struct ev_loop *loop, struct ev_io *w, int revents);

int
bind_server_socket()
{
  int sd;
  struct sockaddr_in addr;

  if ((sd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket error");
    return -1;
  }
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
read_cb(struct ev_loop *loop, struct ev_io *w, int revents)
{
  char buffer[BUFFER_SIZE];
  ssize_t read;

  if (EV_ERROR & revents) {
    perror("got invalid event");
    return;
  }

  read = recv(w->fd, buffer, BUFFER_SIZE, 0);
  if (read < 0) {
    // TODO: check errno == EAGAIN
    perror("read error");
    return;
  }

  if (read == 0) {
    ev_io_stop(loop, w);
    free(w);
    perror("peer might be closing");
    total_clients--;
    printf("%d client(s) connected.\n", total_clients);
    return;
  } else {
    printf("message: %s\n", buffer);
  }
  // TODO: this wants to be async
  send(w->fd, buffer, read, 0);
  bzero(buffer, read);
}

void
accept_cb(struct ev_loop *loop, struct ev_io *w, int revents)
{
  int client_sd;
  struct sockaddr_in client_addr;
  socklen_t client_len = sizeof(client_addr);
  struct ev_io *w_client = (struct ev_io*) malloc(sizeof(struct ev_io));

  if (EV_ERROR & revents) {
    perror("got invalid event");
    return;
  }

  client_sd = accept(w->fd, (struct sockaddr *)&client_addr, &client_len);
  if (client_sd < 0) {
    perror("accept error");
    return;
  }

  total_clients++;
  puts("Succcessfully connected with client.");
  printf("%d client(s) connected.\n", total_clients);

  ev_io_init(w_client, read_cb, client_sd, EV_READ);
  ev_io_start(loop, w_client);
}

void
accept_connections()
{
  int sd;
  struct ev_loop *loop;
  ev_io w_accept;

  sd = bind_server_socket();
  listen(sd, 2);

  loop = ev_default_loop(0);
  ev_io_init(&w_accept, accept_cb, sd, EV_READ);
  ev_io_start(loop, &w_accept);
  ev_loop(loop, 0);

  // We don't get here.
  close(sd);
}

int
main(void)
{
  puts("started.");
  accept_connections();
}

