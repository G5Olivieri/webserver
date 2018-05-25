#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#include "header.h"

#define PORT 8080

typedef char* string;

string concat(string one, string two) 
{
    char str[strlen(one)+strlen(two)+1];
    strcpy(str, one);
    strcat(str, two);
    return str;
}

void check(int condition, string function)
{
    if(condition < 0)
    {
        perror(concat(function, " failure"));
        exit(EXIT_FAILURE);
    }
}

int server_fd;
struct sockaddr_in address;
socklen_t addrlen = sizeof(address);

void start()
{
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
}

int new_client()
{
    int newsocket;
    newsocket = accept(server_fd, (struct sockaddr*)&address, &addrlen);
    check(newsocket, "accept");
    return newsocket;
}

void close_client(int client)
{
    check(shutdown(client, 0), "shutdown");
}
int http_send(int client, const char *str)
{
    setStatus(200);
    setHeader("content-type", "application/json; charset=utf-8");
    char buffer[1024 + strlen(str)];
    strcpy(buffer, header_toString());
    strcat(buffer, str);
    return write(client, buffer, strlen(buffer));
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

        puts(buffer);
        
        http_send(newsocket, "{\"nome\":\"glayson\"}");

        close_client(newsocket);
    } 
    

    return 0;
}