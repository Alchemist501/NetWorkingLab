#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
#define PORT 8000
#define SIZE 1024
int main(){
    int sockfd,k;
    char fname[SIZE];
    char buffer[SIZE];
    char * hello = "Hello from server!";
    struct sockaddr_in serverAddr,clientAddr;
    socklen_t serverlen = sizeof(serverAddr);
    socklen_t clientlen = sizeof(clientAddr);
    if((sockfd = socket(AF_INET,SOCK_DGRAM,0)) < 0){
        perror("Socket creation failed!\n");
        exit(EXIT_FAILURE);
    }else printf("Socket created successfully!\n");
    memset(&serverAddr,0,serverlen);
    memset(&clientAddr,0,clientlen);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    if((k = bind(sockfd,(struct sockaddr*)&serverAddr,serverlen)) < 0 )
        perror("Binding failed!\n");
    k = recvfrom(sockfd,buffer,SIZE,MSG_WAITALL,(struct sockaddr*)&clientAddr,&clientlen);
    buffer[k] = '\0';
    printf("Message received : %s\n",buffer);
    sendto(sockfd,hello,strlen(hello),MSG_CONFIRM,(struct sockaddr*)&clientAddr,clientlen);
    printf("Hello sent to client!\n");
    k = recvfrom(sockfd,fname,SIZE,MSG_WAITALL,(struct sockaddr*)&clientAddr,&clientlen);
    fname[k] = '\0';
    printf("File name received is %s.\n",fname);
    memset(&buffer,0,SIZE);
    FILE* fp = fopen(fname,"r");
    if (fp == NULL) {  
        perror("File is not found!\n");
    }
    fseek(fp,0,SEEK_END);
    long file_size = ftell(fp);
    fseek(fp,0,SEEK_SET);
    fread(buffer,1,file_size,fp);
    printf("The content inside file is \n%s\n",buffer);
    sendto(sockfd,buffer,SIZE,MSG_CONFIRM,(struct sockaddr*)&clientAddr,clientlen);
    printf("Content sent to client!\n");
    fclose(fp);
    return 0;
}