#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Serverfunc.h"
#include "sock_dg_inet.h"


int Socket_creation(){
    int sock_fd;
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd == -1){
        perror("socket: creation failed");
        exit(-1);
    }
    return sock_fd;
}

void Socket_identification(int sock_fd){
    
    struct sockaddr_in local_addr;
    local_addr.sin_family = AF_INET;
    local_addr.sin_port =htons(SOCK_PORT);
    local_addr.sin_addr.s_addr = INADDR_ANY;

    int err = bind(sock_fd, (struct sockaddr *)&local_addr, sizeof(local_addr));
    if(err == -1) {
        perror("bind");
        exit(-1);
    }
}

void Send_Reply_server(int sock_fd, message_server *reply_message, struct sockaddr_in* client_addr){
    socklen_t client_addr_size = sizeof(struct sockaddr_in);
    int nbytes = sendto(sock_fd, reply_message, sizeof(message_server), 0,  (struct sockaddr *) client_addr, client_addr_size);
    if (nbytes == -1){
        perror("sendto");
        exit(-1);
    }
}
void Send_Reply_client(int sock_fd, message_client *reply_message, struct sockaddr_in* client_addr){
    socklen_t client_addr_size = sizeof(struct sockaddr_in);
    int nbytes = sendto(sock_fd, reply_message, sizeof(message_client), 0,  (struct sockaddr *) client_addr, client_addr_size);
    if (nbytes == -1){
        perror("sendto");
        exit(-1);
    }
}

void Receive_message_server(int sock_fd, message_client *ball, struct sockaddr_in* client_addr){
    socklen_t client_addr_size = sizeof(struct sockaddr_in);
    int nbytes = recvfrom(sock_fd, ball, sizeof(*ball), 0, (struct sockaddr *) client_addr, &client_addr_size);
    if (nbytes == -1){
        perror("recvfrom");
        exit(-1);
    }
}

void Receive_message_client(int sock_fd, message_server *ball, struct sockaddr_in* client_addr){
    socklen_t client_addr_size = sizeof(struct sockaddr_in);
    int nbytes = recvfrom(sock_fd, ball, sizeof(*ball), 0, (struct sockaddr *) client_addr, &client_addr_size);
    if (nbytes == -1){
        perror("recvfrom");
        exit(-1);
    }
}