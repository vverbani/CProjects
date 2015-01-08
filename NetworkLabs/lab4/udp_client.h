#ifndef UDPCLIENT_FILE
#define UDPCLIENT_FILE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "udp_sockets.h"

int create_client_socket(char* hostname, char* port, host_t* server);

#endif
