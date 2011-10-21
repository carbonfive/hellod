#include <err.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libtask/task.h"
#include "ds.h"

#define BODY_TEXT   "<html><body><h1>Hello World</h1></body></html>\r\n"
#define HEADER_TEXT "HTTP/1.1 200 OK\r\nConnection: close\r\nContent-Type: text/html\r\nContent-Length: %lu\r\n\r\n"

char *address = "0.0.0.0";
int port = 8085;

void
exit_cleanly()
{
  fprintf(stderr, "Exiting.\n");
  taskexitall(0);
}

void
set_sig_handlers()
{
  int r;
  struct sigaction sa;

  sa.sa_handler = SIG_IGN;
  sa.sa_flags = 0;
  r = sigemptyset(&sa.sa_mask);
  if (r == -1) twarn("sigemptyset()"), exit(111);

  r = sigaction(SIGPIPE, &sa, 0);
  if (r == -1) twarn("sigaction(SIGPIPE)"), exit(111);

  sa.sa_handler = exit_cleanly;
  r = sigaction(SIGINT, &sa, 0);
  if (r == -1) twarn("sigaction(SIGINT)"), exit(111);

  sa.sa_handler = exit_cleanly;
  r = sigaction (SIGTERM, &sa, 0);
  if (r == -1) twarn("sigaction(SIGTERM)"), exit(111);

}

void
say_hello(int fd)
{
  char *headers = calloc(sizeof(HEADER_TEXT) + 16, sizeof(char));
  sprintf(headers, HEADER_TEXT, sizeof(BODY_TEXT) - 1);
  dbgprintf("%s\n", headers);

  fdwrite(fd, headers, strlen(headers));
  fdwrite(fd, BODY_TEXT, strlen(BODY_TEXT));
}

void
hellodtask(void *v)
{
  Connection conn;
  conn = (Connection)v;

  int r;
  for (;;) {
    r = conn_read_command(conn);
    if (r == -1) {
      dbgprintf("Could not conn_read_command()\n");
      taskexit(-1);
    }
    dbgprintf("Command: %s\n", conn->command);

    dbgprintf("Saying hello.\n");
    say_hello(conn->fd);
    dbgprintf("Said hello.\n");
    conn_close(conn);
    dbgprintf("Conn closed\n");
    taskexit(0);
  }
}

void
taskmain(int argc, char **argv)
{
  int cfd, fd;
  char remote[16];
  int rport;

  set_sig_handlers();

  fd = netannounce(TCP, address, port);
  if (fd < 0) {
    fprintf(stderr, "Could not bind to %s:%i. Exiting.\n", address, port);
    taskexitall(1);
  }

  fdnoblock(fd);

  while (1) {
    cfd = netaccept(fd, remote, &rport);
    fdnoblock(cfd);
    if (cfd < 0) {
      exit(1);
    }
    Connection conn = conn_init();
    conn->fd = cfd;

    taskcreate(hellodtask, (void*)conn, STACK_SIZE);
  }
}
