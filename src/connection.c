#include <include/connection.h>

#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> //unix specific - used for read()


#define DEFAULT_PORT 3099
#define PORT_RANGE 10
#define MAX_CONNECTION_QUEUE 128 //No reason besides this being the max allowed on older linux systems. 

int connection_begin_listening(connection_server* server){
    server->socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if(server->socketfd == -1){
        printf("Failure to acquire socket. Error: %d", errno);
        return -1;
    }


    int bind_res = bind(server->socketfd, (struct sockaddr *) &(server->server_addr), sizeof(struct sockaddr));
    for(int retry_num = 1; retry_num < PORT_RANGE-1; retry_num++){        
        printf("%d\n", bind_res);
        if(bind_res != -1){
            printf("Break Here\n");
            break;
        }
         
        printf("Failure to bind socket. Error: %d\n", errno);
        server->server_addr.sin_port = htons(DEFAULT_PORT + retry_num);
        bind_res = bind(server->socketfd, (struct sockaddr *) &(server->server_addr), sizeof(struct sockaddr));
        printf("--HERE");
    }

    if(bind_res == -1){
            printf("Failure to bind socket. Error: %d\n", errno);
            return -1;
    }

    int listen_res = listen(server->socketfd, MAX_CONNECTION_QUEUE);
    
    if(listen_res == -1) {
        printf("Failure to begin listening for connection. Error: %d\n", errno);
        return -1;
    }
    
    printf("Started listening for oncoming connection on port: %d\n", ntohs(server->server_addr.sin_port));
    
    return 0;
}

void connection_accept_clients(connection_server * server){
    while(1) {
        struct sockaddr_in peer_addr;
        socklen_t peer_addr_size = sizeof(peer_addr);

        int connection_descriptor = accept(server->socketfd, (struct sockaddr *) &peer_addr, &peer_addr_size);
        if(connection_descriptor == -1) {
            printf("Failure to accept oncoming connection. Error: %d\n", errno);
        }

        printf("Client connected successfully\n");   

        read_client_test(connection_descriptor);
        write_client(connection_descriptor);

        /*
        * spin off thread here. Use pthread? 
        * is pthread os specific? Look this up.
        */
    }
}

void read_client_test(int connection_descriptor){
    char* rd_val = malloc(sizeof(char) * 1600);

    read(connection_descriptor, rd_val, 1600);
    printf("Reading Full Packet\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("%s", rd_val);
    printf("~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("End read packet\n");

    free(rd_val);
}

void write_client(int connection_descriptor){
    printf("Start write to client\n");
    char content_body[] = "<html><body><h1>Hello World!</h1></body></html>";
    size_t content_length = strlen(content_body);
    char response_header[] = ""
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html; charset=UTF-8\r\n"
            "Connection: Close\r\n"
            "Cache-Control: no-cache\r\n";
    int response_size = snprintf(NULL, 0, "%sContent-Length: %zu\r\n\r\n%s", response_header, content_length, content_body);

    char* response = malloc((size_t) (response_size + 1));

    snprintf(response, (size_t) (response_size + 1), "%sContent-Length: %zu\r\n\r\n%s", response_header, content_length, content_body);
    printf("--response\n\n%s\n----\n", response);
    int res = send(connection_descriptor, response, response_size, 0);

    if(res == -1){
        printf("Failure to accept send message. Error: %d\n", errno);
    } else {
        printf("success in writing to client.\n");
    }

    free(response);

}

void connection_init_server(connection_server* server){
    server->server_addr.sin_family = AF_INET;
    server->server_addr.sin_port = htons(DEFAULT_PORT);
    server->server_addr.sin_addr.s_addr = INADDR_ANY;
}