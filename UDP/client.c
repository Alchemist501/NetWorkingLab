#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<netinet/in.h>
#include <sys/socket.h>
#define PORT 8000
#define SIZE 1024
int main(){
    int sockfd;
    char buffer[SIZE];
    char * msg = "Hello server!";
    struct sockaddr_in serverAddr;
    socklen_t len = sizeof(serverAddr);
    if((sockfd = socket(AF_INET,SOCK_DGRAM,0)) < 0){
        perror("Socket creation failed!\n");
        exit(EXIT_FAILURE);
    }else printf("Socket created successfully\n");
    memset(&serverAddr,0,len);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    sendto(sockfd,msg,strlen(msg),MSG_CONFIRM,(struct sockaddr*)&serverAddr,len);
    printf("Hello send to server!\n");
    int k = recvfrom(sockfd,buffer,SIZE,MSG_WAITALL,(struct sockaddr*)&serverAddr,&len);
    buffer[k] = '\0';
    printf("Message received : %s\nExiting..................\n",buffer);
    close(sockfd);
    return 0;
}