#ifndef UDPSERVER_FILE
#define UDPSERVER_FILE

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#include "udp_sockets.h"

int bind_socket(struct addrinfo* addr_list);
int create_server_socket(char* port);

#endif
