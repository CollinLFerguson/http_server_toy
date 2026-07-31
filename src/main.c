#include <stdio.h>
#include <include/connection.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <errno.h>

#define _DEFAULT_PORT 3000

int main(void){
    printf("Hello World!\n");
    
    struct sockaddr_in socketaddr = 
    {
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
    int bind_res = bind(socketfd, (struct socketaddr *) &socketaddr, sizeof(socketaddr));
    
    if(bind_res == -1){
        printf("Failure to bind socket. Error: %d", errno);
        return -1;
    }

    //listen(socket)
    
    shutdown(socketfd, SHUT_RDWR);
    return 0;
}