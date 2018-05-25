#ifndef _HEADER_H
#define _HEADER_H
#include <stdio.h>
#include <string.h>
#include "map.h"

map header = NULL;

string header_toString()
{
    if(map_isEmpty(header))
    {
        return "header vazio";
    }
    no temp = header->f->n;
    char buffer[1024];
    char pair[1024];
    strcpy(pair, temp->key);
    strcat(pair, " ");
    strcat(pair, temp->value);
    strcat(pair, "\r\n");
    strcpy(buffer, pair);
    while(temp->n != NULL)
    {
        temp = temp->n;
        strcpy(pair, temp->key);
        strcat(pair, ": ");
        strcat(pair, temp->value);
        strcat(pair, "\r\n");
        strcat(buffer, pair);
    }
    strcat(buffer, "\r\n");
    printf("%d\n", strlen(buffer));
    return buffer;
}

void setHeader(string key, string value)
{
    map_put(&header, key, value);
}

void setStatus(int status)
{
    switch(status)
    {
        case 200:
            map_put(&header, "HTTP/1.1", "200 OK");
            break;
        case 404:
            map_put(&header, "HTTP/1.1", "404 NOT FOUND");
            break;
    }
}

#endif // _HEADER_H