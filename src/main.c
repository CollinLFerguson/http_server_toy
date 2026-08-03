#include <stdio.h>
#include <include/connection.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <errno.h>

int main(void){
    printf("Hello World!\n");
        
    connection_server server;
    
    connection_init_server(&server);
    int con_res = connection_begin_listening(&server);
    
    if(con_res == -1){
        printf("Failure to begin listening. Error: %d\n", errno);
        return -1;
    }

    connection_accept_clients(&server);

    shutdown(server.socketfd, SHUT_RDWR);
    return 0;
}