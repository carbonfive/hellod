CC=gcc
CFLAGS=
LIBS=-lev
SRCS=hellod.c
TARG=hellod

.PHONY: all
all: $(TARG)

$(TARG):
	$(CC) $(CFLAGS) $(LIBS) $(SRCS) -o $(TARG)

clean:
	rm -f *.o $(TARG)
