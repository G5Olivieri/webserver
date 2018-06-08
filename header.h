#ifndef _HEADER_H
#define _HEADER_H

#include "string.h"
#include <stdio.h>
#include <string.h>
#include "map.h"

struct _response {
    string status;
    map header;
} response;

struct _request {
    string method;
    string uri;
    map header;
} request;

void request_getHeader(string buffer);
void setStatus(int status);
void response_setHeader(string key, string value);
string response_header_toString();
void request_get_method_and_uri(string request);
void request_setHeader(string key, string value);
void header_init();

void header_init()
{
    response.header = NULL;
    request.header = NULL;
}

string response_header_toString()
{
    if(map_isEmpty(response.header))
    {
        return "header vazio";
    }
    no temp = response.header->f->n;
    char *buffer;
    buffer = response.status;
    
    while(temp->n != NULL)
    {
        buffer = str_concat(buffer, 
                    str_concat(temp->key, 
                    str_concat(": ", 
                    str_concat(temp->value, "\r\n"))));
        temp = temp->n;
    }
    buffer = str_concat(buffer, "\r\n");
    return buffer;
}

void response_setHeader(string key, string value)
{
    map_put(&response.header, key, value);
}

void setStatus(int status)
{
    switch(status)
    {
        case 200:
            response.status = "HTTP/1.1 200 OK\r\n";
            break;
        case 404:
            response.status = "HTTP/1.1 404 NOT FOUND\r\n";
            break;
    }
}


void request_getHeader(string buffer)
{
    char *line = getLine(buffer);
    request_get_method_and_uri(line);
    buffer = str_sub(buffer, str_len(line)+2, str_len(buffer));
    line = getLine(buffer);
    while(line != NULL)
    {
        request_setHeader(str_sub(line, 0, str_contains(line, ":")), 
                        str_sub(line, str_contains(line, ":")+1, str_len(line)));
        buffer = str_sub(buffer, str_len(line)+2, str_len(buffer));
        line = getLine(buffer);
    }
}

void request_get_method_and_uri(string r)
{
    char *buffer;
    request.method = str_toUpperCase(str_sub(r, 0, str_contains(r, " ")));
    r = str_sub(r, str_len(request.method)+1, str_len(r));
    request.uri = str_sub(r, 0, str_contains(r, " "));
}

void request_setHeader(string key, string value)
{
    map_put(&request.header, trim(key), trim(value));
}

#endif // _HEADER_H