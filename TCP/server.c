#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

struct sockaddr_in server_address;
struct sockaddr_in client_address;

int main()
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    int clientlen = sizeof(client_address);

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8090);
    server_address.sin_addr.s_addr = INADDR_ANY;

    bind(socket_fd, (struct sockaddr *)&server_address, sizeof(server_address));
    listen(socket_fd, 5);

    int client_socket = accept(socket_fd, (struct sockaddr *)&client_address, (socklen_t *)&clientlen);

    char buffer[1024] = {0};
    int byte_rec = recv(client_socket, buffer, sizeof(buffer), 0);

    send(client_socket, buffer, byte_rec, 0);

    close(socket_fd);
    close(client_socket);
    return 0;
}
