#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
#define PORT 8000
#define SIZE 1024
int main(){
    char file[SIZE];
    char buffer[SIZE];
    char * msg = "Hello from Client!";
    struct sockaddr_in Addr;
    socklen_t len = sizeof(Addr);
    int sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd < 0 ){
        perror("Socket creation failed!\n");
        exit(EXIT_FAILURE);
    }else printf("Socket created successfully\n");
    memset(&Addr,0,len);
    Addr.sin_family = AF_INET;
    Addr.sin_port = htons(PORT);
    Addr.sin_addr.s_addr = INADDR_ANY;
    sendto(sockfd,msg,strlen(msg),MSG_CONFIRM,(struct sockaddr*)&Addr,len);
    printf("Hello sent to client!\n");
    int k = recvfrom(sockfd,buffer,SIZE,MSG_WAITALL,(struct sockaddr*)&Addr,&len);
    buffer[k] = '\0';
    printf("Message received from server:\n\t%s\n",buffer);
    printf("Enter the filename :");
    fgets(file,SIZE,stdin);
    file[strcspn(file, "\n")] = '\0';
    printf("filename entered is:%s\n",file);
    sendto(sockfd,file,strlen(file),MSG_CONFIRM,(struct sockaddr*)&Addr,len);   
    printf("File name sent to server\n");
    memset(&buffer,0,SIZE);
    k = recvfrom(sockfd,buffer,SIZE,MSG_WAITALL,(struct sockaddr*)&Addr,&len);
    buffer[k] = '\0';
    printf("Contents inside the file is : \n\t%s\n",buffer);
    close(sockfd);
    return 0;
}