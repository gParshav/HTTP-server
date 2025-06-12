#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>


int main(){
    int server_fd = socket(AF_INET, SOCK_STREAM, 0); //socket is created
    if(server_fd == -1){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    printf("Socket created with an fd: %d\n", server_fd);
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET; //this mentions IPv4
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);
    //binding is only done if you want to assign a specific IP and a port number to the socket
    if(bind(server_fd, (struct sockaddr*)& address, sizeof(address)) == -1){ //socket is given an IP address and a port number
        perror("binding failed");
        exit(EXIT_FAILURE);
    }

    printf("Successfully binded the socket\n");

    if(listen(server_fd, 10) == -1){ // we are now waiting for the incoming syn requests from the client
        printf("The socket is not able to listen\n");
        exit(EXIT_FAILURE);
    }

    printf("The socket is now listening\n");
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
    if(client_fd == -1){
        perror("can't connect to the client");
        exit(EXIT_FAILURE);
    }
    printf("Connection between the client and the server has been established\n");
    char buffer[1024];
    int bytes_read = read(client_fd, buffer, sizeof(buffer)-1);
    if(bytes_read > 0){
        buffer[bytes_read] = '\0';
        printf("Server receieved - %s\n", buffer);
    }

    else{
        printf("Didn't recieve any message\n");
    }

    return 0;
}