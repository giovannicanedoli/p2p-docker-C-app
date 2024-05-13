#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "main.h"

int main(int argc, char const *argv[]){
    int ret;
    // I should set portnumber directly from docker compose!
    int portnumber;
    printf("ENTER PORT NUMBER: ");
    fflush(stdout);
    scanf("%d", &portnumber);
    while(getchar() != '\n');

    int server_fd, new_socket, valread;
    struct sockaddr_in address;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        handle_error("socket creation failed");
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(portnumber);

    printf("IP address is: %s\n", inet_ntoa(address.sin_addr));
    printf("port is: %d\n", (int)ntohs(address.sin_port));
    

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) != 0){
        handle_error("bind failed");
    }

    if (listen(server_fd, 5) != 0){
        handle_error("listen failed");
    }

    pthread_t thread;
    if(pthread_create(&thread, NULL, &receive_fun, &server_fd) != 0){
        handle_error("couldn't spawn the recv thread");
    }

    printf("Enter message to send, QUIT to quit\n");
    char* message = malloc(MESSAGESIZE);
    
    fgets(message, MESSAGESIZE, stdin);
    // printf("%s\n", message);
    
    while(strcmp(message, "QUIT") != 0){

        //send_data_to_server(message);   this has to be changed!
        int port_other_peer;
        printf("Enter others peer port: \n");
        scanf(" %d", &port_other_peer);
        while(getchar() != '\n');

        send_data_to_peer(port_other_peer, message, "client_2");

        printf("Message sent successfully!\n");

        memset(message, 0, MESSAGESIZE);

        printf("Enter new message to send: \n");
        fgets(message, MESSAGESIZE, stdin);

    }

    return 0;
}

void handle_error(const char* message){
    perror(message);
    exit(EXIT_FAILURE);
}

void* receive_fun(void* serverfdaddress){
    int socket = *((int*)serverfdaddress);
    while(1){
        sleep(2);
        recvdata(socket);
    }
}

void recvdata(int socket){
    struct sockaddr_in address;
    int valread;
    char buffer[2000] = {0};    //change this
    int addrlen = sizeof(address);

    fd_set current_sockets, ready_sockets;

    //Initialize my current set
    FD_ZERO(&current_sockets);
    FD_SET(socket, &current_sockets);
    int k = 0;
    
    while (k < FD_SETSIZE){
        k++;
        ready_sockets = current_sockets;

        if (select(FD_SETSIZE, &ready_sockets, NULL, NULL, NULL) < 0){
            perror("Error");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < FD_SETSIZE; i++){
            if (FD_ISSET(i, &ready_sockets)){
                if (i == socket){
                    int client_socket;

                    if ((client_socket = accept(socket, (struct sockaddr *)&address,
                                                (socklen_t *)&addrlen)) < 0){
                        perror("accept");
                        exit(EXIT_FAILURE);
                    }
                    FD_SET(client_socket, &current_sockets);
                }
                else{
                    valread = recv(i, buffer, sizeof(buffer), 0);
                    printf("%s", buffer);
                    FD_CLR(i, &current_sockets);
                }
            }
        }

    }
}

void send_data_to_peer(const int peerport, const char* msg, const char* peer){

    int sockfd;
    int valread;
    struct sockaddr_in otherpeeraddr;

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        handle_error("Cannot create other socket");
    }

    //change this voices!
    otherpeeraddr.sin_family = AF_INET;
    otherpeeraddr.sin_addr.s_addr = INADDR_ANY; //INADDR_ANY always gives an IP of 0.0.0.0
    otherpeeraddr.sin_port = htons(peerport);

    if (connect(sockfd, (struct sockaddr *)&otherpeeraddr, sizeof(otherpeeraddr)) < 0){
        handle_error("Connection failed!");
    }

    //check for errors in send!
    send(sockfd, msg, sizeof(msg), 0);
    int ret = close(sockfd);
    if(ret == -1){
        handle_error("Couldn't close file descriptor!");
    }
    return;
}

void send_data_to_server(const char* msg){
    /*da modificare con la porta del server!
    ora ci metto un numero a caso
    */
    send_data_to_peer(20009, msg, "SERVER");
}