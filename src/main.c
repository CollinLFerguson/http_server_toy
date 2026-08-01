#include <stdio.h>
#include <include/connection.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <errno.h>

#define _DEFAULT_PORT 3000

int main(void){
    printf("Hello World!\n");
    
    struct sockaddr_in peer_addr;

    struct sockaddr_in host_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(_DEFAULT_PORT),
        .sin_addr.s_addr = INADDR_ANY
    };

    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if(socketfd == -1){
        //further error handling here
        printf("Failure to acquire socket. Error: %d", errno);
        return -1;
    }
    int bind_res = bind(socketfd, (struct sockaddr *) &host_addr, sizeof(struct sockaddr));
    
    if(bind_res == -1){
        printf("Failure to bind socket. Error: %d", errno);
        return -1;
    }

    int listen_res = listen(socketfd, 128);
    
    if(listen_res == -1) {
        printf("Failure to begin listening for connection. Error: %d", errno);
        return -1;
    }
    
    printf("Started listening for oncoming connection on port: %d\n", _DEFAULT_PORT);

    socklen_t peer_addr_size = sizeof(&peer_addr);

    int connection_descriptor = accept(socketfd, (struct sockaddr *) &peer_addr, &peer_addr_size);
    if(connection_descriptor == -1) {
        printf("Failure to accept oncoming connection. Error: %d", errno);
        return -1;
    }

    printf("Client connected successfully");

    shutdown(socketfd, SHUT_RDWR);
    return 0;
}