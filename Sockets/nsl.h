#ifndef NSL_H
#define NSL_H

#define QR_QUERY 0
#define QR_RESPONSE 1
#define OPCODE_QUERY 0 
#define AA_NONAUTHORITY 0
#define AA_AUTHORITY 1
#define SIZE 512
#define PORT 53

typedef struct
{
	// call htons on bigger than a byte, uint16 / 32
	uint16_t id; 
	unsigned int qr:1;
	unsigned int opcode:4;
	unsigned int aa:1;
	unsigned int tc:1;
	unsigned int rd:1;
	unsigned int ra:1;
	unsigned int z:3;
	unsigned int rcode:4;
	uint16_t qd_count;
	uint16_t an_count;
	uint16_t ns_count;
	uint16_t ar_count;

} header_t;

typedef struct
{
	uint16_t qtype;
	uint16_t qclass;
} query_t;

typedef struct
{
        uint16_t rtype;
	uint16_t rclass;
	uint32_t ttl;
	uint16_t rd_length;
} answer_t;


typedef struct
{
	int length;
	uint8_t buffer[SIZE];
} message_t;

typedef struct
{
    struct sockaddr_in addr;
    socklen_t addr_len;
    char friendly_ip[INET_ADDRSTRLEN];
} host_t;

struct addrinfo* get_udp_sockaddr(const char* node, int flags);

message_t* create_message();

message_t* receive_message(int sockfd, host_t* source);

int send_message(int sockfd, message_t* msg, host_t* dest);

int create_client_socket(char* hostname, host_t* server);

int get_dns_type(char* type);

#endif

