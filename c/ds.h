#define DEBUG 1

// Size of the stack that is malloc'd per libtask coroutine
#define STACK_SIZE 1024

#ifdef DEBUG
#define dbgprintf(fmt, args...) ((void) fprintf(stderr, fmt, ##args))
#define twarn(fmt, args...) warn("%s:%d in %s: " fmt, \
                                 __FILE__, __LINE__, __func__, ##args)
#else
#define dbgprintf(fmt, ...) ((void) 0)
#define twarn(fmt, ...) ((void) 0)
#endif

#define LINE_BUF_SIZE 256
#define MAX_DATA_SIZE 1024

typedef struct Connection *Connection;

struct Connection {
  int fd;

  char command[LINE_BUF_SIZE];

  char *data_in;
  int data_in_len;
  int data_in_loc;
};

Connection conn_init();
void conn_close(Connection conn);
int conn_read_command(Connection conn);
