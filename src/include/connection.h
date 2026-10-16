#ifndef CONNECTIONS_FILE
#define CONNECTIONS_FILE


#include <sys/socket.h>
#include <netinet/in.h>


typedef struct connection_server{
    int socketfd;
    struct sockaddr_in server_addr;
} connection_server; 

void connection_init_server(connection_server* server);

int connection_begin_listening(connection_server* server);

void connection_accept_clients(connection_server* server);

void read_client_test(int connection_descriptor); //test function

void write_client(int connection_descriptor); //test function

#endif