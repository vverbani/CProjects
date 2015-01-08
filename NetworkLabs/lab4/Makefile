CC=gcc
CFLAGS=-Wall -g -c
LFLAGS=-Wall -g

all:  server client

server: server.o udp_sockets.o udp_server.o
	$(CC) $(LFLAGS) -o $@ $^

client: client.o udp_sockets.o udp_client.o
	$(CC) $(LFLAGS) -o $@ $^

client.o: client.c udp_client.h udp_sockets.h
	$(CC) $(CFLAGS) -o $@ $<

udp_sockets.o: udp_sockets.c udp_sockets.h
	$(CC) $(CFLAGS) -o $@ $<

udp_server.o: udp_server.c udp_server.h udp_sockets.h
	$(CC) $(CFLAGS) -o $@ $<

udp_client.o: udp_client.c udp_client.h udp_sockets.h
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f *.o  server client

