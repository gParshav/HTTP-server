#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(){
    int client_fd = socket(AF_INET, SOCK_STREAM, 0); //create the client socket
    if(client_fd == -1){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    printf("created the client socket\n");
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET; //this mentions IPv4
    server_addr.sin_port = htons(8080);
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        perror("inet_pton");
        exit(EXIT_FAILURE);
    }

    if(connect(client_fd, (struct sockaddr*) &server_addr, sizeof(server_addr))==-1){
        perror("connect");
        exit(EXIT_FAILURE);
    }
    
    printf("Client is connected to the server\n");

    char msg[] = "Hello Server\n";
    write(client_fd, msg, strlen(msg));
    printf("Client sent message to server\n");


    

    return 0;
}