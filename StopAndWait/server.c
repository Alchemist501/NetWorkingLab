#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
#define PORT 8000
#define SIZE 1024
int main(){
    int i = 0;
    char buffer[SIZE] ;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t serverlen = sizeof(serverAddr);
    socklen_t clientlen = sizeof(clientAddr);
    int sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd < 0){
        perror("Socket creation failed!\n");
        exit(EXIT_FAILURE);
    }else printf("Socket created successfully!\n");
    memset(&serverAddr,0,serverlen);
    memset(&clientAddr,0,clientlen);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    int k = bind(sockfd,(struct sockaddr*)&serverAddr,serverlen);
    if(k < 0) perror("Binding failed!!!\n");
    else printf("Client connected successfully!!!\n");
    printf("Receiver is waiting for frames\n");
    while(1){
        memset(buffer,0,SIZE);
        k = recvfrom(sockfd,(char *)buffer,SIZE,MSG_WAITALL,(struct sockaddr*)&clientAddr,&clientlen);
        buffer[k] = '\0';
        printf("Frame %d received : %s\nSending acknowledgement....\n",i,buffer);
        memset(buffer,0,SIZE);
        snprintf(buffer,SIZE,"Acknowledgment for frame %d",i);
        printf("Acknowledgment for frame %d : %s\n",i++,buffer);
        sendto(sockfd,buffer,SIZE,MSG_CONFIRM,(struct sockaddr*)&clientAddr,clientlen);
    }
    printf("Exiting.............\n");
    close(sockfd);
    return 0;
}