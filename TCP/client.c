#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

struct sockaddr_in server_address;

int main()
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8090);
    inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);

    connect(socket_fd, (struct sockaddr *)&server_address, sizeof(server_address));

    const char *hello = "Hello server";
    send(socket_fd, hello, strlen(hello), 0);

    char buffer[1024] = {0};
    recv(socket_fd, buffer, sizeof(buffer), 0);
    printf("Reversed string: %s", buffer);

    close(socket_fd);
    return 0;
}
