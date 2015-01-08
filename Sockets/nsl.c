/********************************************************************************
 * nsl.c
 *
 * Computer Science 3357a
 * Assignment 3
 *
 * Author: Jennifer Knull, jknull@uwo.ca
 *         Valmir Verbani, vverbani@uwo.ca
 *
 * Description: this program emulates a DNS client which requests a DNS server
 *  over the real network
********************************************************************************/

#include <arpa/inet.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <netdb.h>
#include <ctype.h>
#include "nsl.h"

struct addrinfo* get_udp_sockaddr(const char* node, int flags)
{
    struct addrinfo hints;
    struct addrinfo* results;
    int retval;

    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_family = AF_INET; // Return socket addresses for our local IPv4 addresses
    hints.ai_socktype = SOCK_DGRAM; // Return UDP socket addresses
    hints.ai_flags = flags; // Socket addresses should be listening sockets
    retval = getaddrinfo(node, "53", &hints, &results);

    if (retval != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(retval));
        exit(EXIT_FAILURE);
    }

    return results;
}

message_t* create_message()
{
    return (message_t*)malloc(sizeof(message_t));
}

message_t* receive_message(int sockfd, host_t* source)
{
    message_t* msg = create_message();

    // Length of the remote IP structure
    source->addr_len = sizeof(source->addr);

    // Read message, storing its contents in msg->buffer, and
    // the source address in source->addr
    msg->length = recvfrom(sockfd, msg->buffer, sizeof(msg->buffer), 0, (struct sockaddr*)&source->addr, &source->addr_len);

    // If a message was read
    if (msg->length > 0)
    {
        // Convert the source address to a human-readable form,
        // storing it in source->friendly_ip
        inet_ntop(source->addr.sin_family, &source->addr.sin_addr,
        source->friendly_ip, sizeof(source->friendly_ip));

        // Return the message received
        return msg;
    }
    else
    {
        // Otherwise, free the allocated memory and return NULL
        free(msg);
        return NULL;
    }
}

int send_message(int sockfd, message_t* msg, host_t* dest)
{
    return sendto(sockfd, msg->buffer, msg->length, 0, (struct sockaddr*)&dest->addr, dest->addr_len);
}

int create_client_socket(char* hostname, host_t* server)
{
    int sockfd;
    struct addrinfo* addr;
    struct addrinfo* results = get_udp_sockaddr(hostname, 0);

    // Iterate thr  ough each addrinfo in the list;
    // stop when we successfully create a socket
    for (addr = results; addr != NULL; addr = addr->ai_next)
    {
        // Open a socket
        sockfd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);

        // Try the next address if we couldn't open a socket
        if (sockfd == -1)
            continue;

        // Copy server address and length to the out parameter 'server'
        memcpy(&server->addr, addr->ai_addr, addr->ai_addrlen);
        memcpy(&server->addr_len, &addr->ai_addrlen, sizeof(addr->ai_addrlen));

        // We've successfully created a socket; stop iterating
        break;
    }

    // Free the memory allocated to the addrinfo list
    freeaddrinfo(results);

    // If we tried every addrinfo and failed to create a socket
    if (addr == NULL)
    {
        perror("Unable to create socket");
        exit(EXIT_FAILURE);
    }
    else
    {
        // Otherwise, return the socket descriptor
        return sockfd;
    }
}
/*
* As the function name states; it returns the type of dns defined
* Using strcmp to check if the paratmer value is equal to one of our
* dns types, if it is then it assigns an equivalent value to that type
*/
int get_dns_type(char* type)
{
    int final;

    if(strcmp(type, "A") == 0)
    {
      final = 1;
    }
    if(strcmp(type, "CNAME") == 0)
    {
      final = 5;
    }
    if(strcmp(type, "NS") == 0)
    {
      final = 2;
    }
    if(strcmp(type, "MX") == 0)
    {
      final = 15;
    }
    if(strcmp(type, "TXT") == 0)
    {
      final = 16;
    }

    return final;
}

message_t* generate_query(char* query, char* type)
{
    message_t* packet = create_message();
    header_t* query_header = (header_t*)packet->buffer;

    query_header->id = htons(2048);
    query_header->qr = 0; //This is a query
    query_header->opcode = 0; //This is a standard query
    query_header->aa = 0; //Not Authoritative
    query_header->tc = 0; //This message is not truncated
    query_header->rd = 0; //Recursion Desired
    query_header->ra = 0; //Recursion not available!
    query_header->z = 0;
    query_header->rcode = 0;
    query_header->qd_count = htons(1); //we have only 1 question
    query_header->an_count = htons(0);
    query_header->ns_count = htons(0);
    query_header->ar_count = htons(0);

    uint8_t* qname = (uint8_t*)&packet->buffer[sizeof(header_t)];

    int count = 0;

    strcat(query, ".");
    int i;
    for(i = 0; i < (int)strlen(query); i++)
    {
        if(query[i] == '.')
        {
                qname[count] = (i-count);
                while(count < i)
            {
                qname[count+1] = query[count];
                count++;
            }
            count++;
        }
    }
    qname[i] = '\0';

    query_t* question = (query_t*)&packet->buffer[sizeof(header_t) + i + 1];

    question->qtype = htons(get_dns_type(type));
    question->qclass = htons(1); // internet

    packet->length = sizeof(header_t) + (i+1) + sizeof(query_t);

    return packet;
}

void parse_response(message_t* rr, char* query)
{
    query_t* rquestion = (query_t*)&rr->buffer[sizeof(header_t) + strlen(query) + 1];

    answer_t* response = (answer_t*)&rr->buffer[sizeof(header_t) + sizeof(query_t) + strlen(query) + 1 + 2];

    uint8_t* ip = (uint8_t*)&rr->buffer[sizeof(header_t) + strlen(query) + 1 + sizeof(query_t) + sizeof(answer_t)];

	
    char* name = malloc(strlen(query)-1);
    strncpy(name, query, (strlen(query))-1);
   
	 
    char octet[200];
    if(ntohs(rquestion->qtype) == 1 || ntohs(rquestion->qtype) == 16)
    {
        printf("Name: %s\n", name);
        printf("Address: %d.%d.%d.%d\n", ip[0], ip[1], ip[2], ip[3]);
    }
    else if(ntohs(rquestion->qtype) == 5 || ntohs(rquestion->qtype) == 2)
    {
        printf("Name: %s\n", name);
	    printf("Address: ");
	    int i = 0;
	    while(i < ntohs(response->rd_length))
	    {
	    
	        if(ip[i] > 126)
            {
		        if(query[i] == 119)
		        {
		            char *to = (char*)malloc(strlen(query) - 1);
		            strncpy(to, query+3, strlen(query)-4);
		            printf("%s", to); 
                }
		        else printf(".%s", query);

		        break;
            }

            sprintf(octet, "%c", ip[i]);
	        if(ip[i] < 48 && i != 0 && i + 1 != ntohs(response->rd_length))
		    {
		        printf(".");
		    }
	        else
            {
		        printf("%s", octet);
		    }
            i++;  
	    }
	    printf("\n");
    }
    else if(ntohs(rquestion->qtype) == 15)
    {
	    printf("Name: %s\n", name);
        printf("Address: ");
        int i = 2;
        while(i < ntohs(response->rd_length) + 2)
        {
	        if(ip[i] > 126)
            {
                if(query[i] == 119)
                {
                    char *to = (char*)malloc(strlen(query) - 1);
                    strncpy(to, query+3, strlen(query)-4);
                    printf("%s", to);
                }
                else printf(".%s", query);

                break;
            }

            sprintf(octet, "%c", ip[i]);
            if(ip[i] < 48 && i != 0 && i + 1 != ntohs(response->rd_length))
            {
                printf(".");
            }
            else
            {
                printf("%s", octet);
            }
            i++;
        }
        printf("\n");

    }
}

int main(int argc, char** argv)
{

    int c;
    char* type = "A";
    char* dns_server = NULL;
    char* query = NULL;



    // read in options from the command line
    while (1)
    {
        static struct option long_options[] =
        {
            {"type", required_argument, 0, 't'},
            {0, 0, 0, 0}
        };

        int option_index = 0;
        c = getopt_long(argc, argv, "t:", long_options, &option_index);

        // If we've reached the end of the options, stop iterating
        if (c == -1)
            break;

        switch (c)
        {
            case 't':
                type = optarg;
                break;

            case '?':
                // Error message already printed by getopt_long -- we'll just exit
                exit(EXIT_FAILURE);
                break;
        }
    }

    // if either server or query was not specified, print error message and exit
    if(optind != argc - 2)
    {
        printf("Both server and query not specified\n");
        exit(EXIT_FAILURE);
    }

    // extract server and filename non-options from the command line
    dns_server = argv[optind];
    query = argv[optind+1];

    host_t server;
    message_t* packet = generate_query(query,  type); // query sent to server
    message_t* rr = create_message(); // resource record received from server

    // Create a socket to listen on specified port
    int sockfd = create_client_socket(dns_server, &server);
    
    send_message(sockfd, packet, &server);

    rr = receive_message(sockfd, &server);

    parse_response(rr, query);

    free(packet);
    free(rr);
    close(sockfd);

    exit(EXIT_SUCCESS);

}

