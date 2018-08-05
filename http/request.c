#include <stdio.h>
#include <stdlib.h>

#include "../hashmap.h"
#include "../string.h"

struct http_request{
    char *method;
    char *uri;
    struct hashmap *header;
};

struct pair *get_pair(char *line)
{
    struct pair *p = (struct pair*)malloc(sizeof(struct pair));
    char *it, *str;
    it = line;
    int len = 0, i;
    while(*it != '\0' && *it != ':')
    {
        len++;
        it++;
    }
    it = line;
    str = (char*)malloc(sizeof(char) * len + 1);
    for(i = 0; i < len; i++)
    {
        str[i] = *it;
        it++;
    }
    
    str[i] = '\0';
    p->key = new_string(str);
    free(str);
    
    len = 0;
    it++;
    while(*it == ' ')
        it++;
    str = it;
    while(*it != '\0' && *it != ':')
    {
        len++;
        it++;
    }
    it = str;
    str = (char*)malloc(sizeof(char) * len + 1);
    for(i = 0; i < len; i++)
    {
        str[i] = *it;
        it++;
    }

    str[i] = '\0';
    p->value = new_string(str);
    free(str);

    return p;
}

struct http_request *string_to_request_header(char *request)
{
    struct http_request *request_header = (struct http_request*)malloc(sizeof(struct http_request));
    struct pair *p;
    char *it, *str = get_line(request);
    int len = 0, i;

	it = str;
	while(*it != '\0' && *it != ' ')
	{
        len++;
		it++;
	}

    request_header->method = (char*)malloc(sizeof(char)*len+1);
    it = str;
    for(i = 0; i < len; i++)
    {
        request_header->method[i] = *it;
        it++;
    }
    request_header->method[i] = '\0';
    
    len = 0;
	it++;
    request_header->uri = it;
    while(*it != '\0' && *it != ' ')
    {
        len++;
        it++;
    }

    it = request_header->uri;
    request_header->uri = (char*)malloc(sizeof(char)*len+1);
    for(i = 0; i < len; i++)
    {
        request_header->uri[i] = *it;
        it++;
    }
    request_header->uri[i] = '\0';

    request += str_len(str) + 1;
    str = get_line(request);

    request_header->header = NULL;
    while(*str != '\r')
    {
        p = get_pair(str);
        free(str);
        str = get_line(request);
        hash_put(&request_header->header, p->key, p->value);
        request += str_len(str) + 1;
        free(p);
    }
    return request_header;
}