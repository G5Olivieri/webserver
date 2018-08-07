#ifndef _REQUEST_H_
#define _REQUEST_H_

#include <stdio.h>
#include <stdlib.h>

#include "../hashmap.h"
#include "../string.h"

struct http_request{
    char *method;
    char *uri;
    struct hashmap *header;
};

struct http_request *string_to_request_header(char*);
struct pair *get_pair(char*);

#endif