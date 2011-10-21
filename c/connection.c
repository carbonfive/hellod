#include <assert.h>
#include <err.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <task.h>
#include "ds.h"
#include <unistd.h>

Connection conn_init()
{
  Connection conn;
  conn = malloc(sizeof(struct Connection));

  conn->data_in = calloc(MAX_DATA_SIZE, sizeof(char));
  conn->data_in_len = 0;
  conn->data_in_loc = 0;

  return conn;
}

void
conn_close(Connection conn)
{
  close(conn->fd);
  free(conn->data_in);
  free(conn);
}

/* Scan the given string for the sequence "\r\n" and return the line length.
 * Always returns at least 2 if a match is found. Returns 0 if no match. */
static int
scan_line_end(const char *s, int size)
{
  char *match;

  match = memchr(s, '\r', size - 1);
  if (!match) return 0;

    /* this is safe because we only scan size - 1 chars above */
  if (match[1] == '\n') return match - s + 2;

  return 0;
}

// This is not remotely threadsafe.
int
conn_read_command(Connection conn)
{
  int r;
  int line_read = 0;
  int line_end = 0;
  do {
    r = fdread(conn->fd, conn->command, LINE_BUF_SIZE - line_read);
    if (r == 0) {
      dbgprintf("read_command(): client hung up.\n");
      return -1;
    }
    if (r == -1) {
      twarn("read_command(): fdread");
      return -1;
    }
    line_read += r;
    line_end = scan_line_end(conn->command, line_read);
  } while((line_read < LINE_BUF_SIZE) && (line_end == 0));

  if (line_end == 0) {
    dbgprintf("read_command(): could not find EOL\n");
    return -1;
  }

  // NULL terminate the command string
  conn->command[line_end - 2] = '\0';

  // Something strange (and malicious) is afoot at the Circle K.
  assert(strlen(conn->command) == (line_end - 2));

  // copy any trailing bytes into the data buffer
  memcpy(conn->data_in, &(conn->command[line_end]), line_read - line_end);
  conn->data_in_loc = line_read - line_end;
  conn->data_in_len = line_read - line_end;

  return 1;
}
