#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "header.h"

#define PORT 8080

typedef char* string;

void check(int condition, string function)
{
    if(condition < 0)
    {
        perror(str_concat(function, " failure"));
        exit(EXIT_FAILURE);
    }
}

int server_fd;
struct sockaddr_in address;
socklen_t addrlen = sizeof(address);

void start()
{
    header_init();
    int newsocket;
    int opt = 1;
    
    server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    check(server_fd, "socket");
    check(setsockopt(server_fd, SOL_SOCKET, 
            SO_REUSEADDR | SO_REUSEPORT, &opt, 
            sizeof(opt)), "setsockopt");

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = INADDR_ANY;

    check(bind(server_fd, (struct sockaddr*)&address, addrlen), "bind");
    check(listen(server_fd, 1), "listen");
    setStatus(200);
    response_setHeader("server", "glayson/0.0.1");
}

int new_client()
{
    int newsocket;
    newsocket = accept(server_fd, (struct sockaddr*)&address, &addrlen);
    check(newsocket, "accept");
    return newsocket;
}

int http_send(int client, const char *str)
{
    char *buffer;
    buffer = str_concat(response_header_toString(), str);
    return write(client, buffer, str_len(buffer));
}

int http_send_file(int client, const char *path)
{
    FILE *file;
    file = fopen(path, "r");
    if(file == NULL)
    {
        perror("fopen failure");
        return -1;
    }
    fseek(file, 0L, SEEK_END);
    size_t szfile = ftell(file);
    rewind(file);
    char buffer[ szfile + 1];
    fread(buffer, szfile, 1, file);
    buffer[szfile] = 0;
    fclose(file);
    response_setHeader("content-type", "text/html");
    return http_send(client, buffer);
}

int main(int argc, char *argv[])
{
    start();
    int newsocket;
    char buffer[1024];
    int valread;

    while(1)
    {
        newsocket = new_client();
        valread = read(newsocket, buffer, 1024);

        buffer[valread] = 0;

        request_getHeader(buffer);

        http_send_file(newsocket, "index.html");
        shutdown(newsocket, SHUT_RDWR);
    }
    return 0;
}