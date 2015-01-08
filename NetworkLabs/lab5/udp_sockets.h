

#ifndef UDPSOCKETS_FILE
#define UDPSOCKETS_FILE

#include <netdb.h>
#define UDP_MSS 65535

typedef struct
{
int length;
uint8_t buffer[UDP_MSS];
}message_t;

typedef struct
{
struct sockaddr_in addr;
socklen_t addr_len;
char friendly_ip[INET_ADDRSTRLEN];
}host_t;

struct addrinfo* get_udp_sockaddr(const char* node, const char* port, int flags);
message_t* createmessage();
message_t* receive_message(int sockfd, host_t* source);
int send_message(int sockfd,message_t* msg, host_t* dest);
message_t* receive_message_with_timeout(int sockfd,int timeout, host_t* source);

#endif




