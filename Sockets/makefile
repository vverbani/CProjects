CC=gcc
CFLAGS=-Wall -g -c
LFLAGS=-Wall -g

all: nsl

nsl: nsl.o 
	$(CC) $(LFLAGS) -o $@ $^

nsl.o: nsl.c nsl.h 
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f *.o nsl 
