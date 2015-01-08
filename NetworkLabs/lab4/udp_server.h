#ifndef UDPSERVER_FILE
#define UDPSERVER_FILE

#include <netdb.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include "udp_sockets.h"

int bind_socket(struct addrinfo* addr_list);
int create_server(char* port);

#endif
