#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<netinet/in.h>
#include <sys/socket.h>
#define PORT 8000
#define SIZE 1024
int main(){
    int i = 0;
    int sockfd,no,k;
    char buffer[SIZE];
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
    printf("Enter the number of frames to sent!\n");
    scanf("%d",&no);
    for(int j = 0; j < no ; j++){
        memset(buffer,0,SIZE);
        snprintf(buffer,SIZE,"Hello Server, I am Frame %d!",i);
        sendto(sockfd,buffer,SIZE,MSG_CONFIRM,(struct sockaddr*)&serverAddr,len);
        printf("Frame %d send to server!\nWaiting for acknowledgement....\n",i);
        memset(buffer,0,SIZE);
        k = recvfrom(sockfd,buffer,SIZE,MSG_WAITALL,(struct sockaddr*)&serverAddr,&len);
        buffer[k] = '\0';
        printf("Acknowledgement received for Frame %d : \n\t%s\n",i++,buffer);
    }
    printf("Frames send successfully!\nExiting..................\n");
    close(sockfd);
    return 0;
}