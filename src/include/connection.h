#pragma once
#include <sys/socket.h>
#include <netinet/in.h>


typedef struct connection_server{
    int socketfd;
    struct sockaddr_in server_addr;
} connection_server; 

void connection_init_server(connection_server* server);

int connection_begin_listening(connection_server* server);

void connection_accept_clients(connection_server* server);