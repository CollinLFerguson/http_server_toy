#include <include/connection.h>

#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>


#define _DEFAULT_PORT 3099
#define _MAX_CONNECTION_QUEUE 128 //No reason besides this being the max allowed on older linux systems. 

int connection_begin_listening(connection_server* server){

    server->socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if(server->socketfd == -1){
        printf("Failure to acquire socket. Error: %d", errno);
        return -1;
    }
    int bind_res = bind(server->socketfd, (struct sockaddr *) &(server->server_addr), sizeof(struct sockaddr));
    
    if(bind_res == -1){
        printf("Failure to bind socket. Error: %d\n", errno);
        return -1;
    }

    int listen_res = listen(server->socketfd, _MAX_CONNECTION_QUEUE);
    
    if(listen_res == -1) {
        printf("Failure to begin listening for connection. Error: %d\n", errno);
        return -1;
    }
    
    printf("Started listening for oncoming connection on port: %d\n", _DEFAULT_PORT);
    
    return 0;
}

void connection_accept_clients(connection_server * server){
    while(1) {
        struct sockaddr_in peer_addr;
        socklen_t peer_addr_size = sizeof(&peer_addr);

        int connection_descriptor = accept(server->socketfd, (struct sockaddr *) &peer_addr, &peer_addr_size);
        if(connection_descriptor == -1) {
            printf("Failure to accept oncoming connection. Error: %d\n", errno);
        }

        printf("Client connected successfully\n");   

        /*
        * spin off thread here. Use pthread? 
        * is pthread os specific? Look this up.
        */
    }
}

void connection_init_server(connection_server* server){
    server->server_addr.sin_family = AF_INET;
    server->server_addr.sin_port = htons(_DEFAULT_PORT);
    server->server_addr.sin_addr.s_addr = INADDR_ANY;
}