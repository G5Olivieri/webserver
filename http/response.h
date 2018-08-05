#ifndef _RESPONSE_H_
#define _RESPONSE_H_

#include "../hashmap.h"
#include "../string.h"

struct http_response {
	struct {
		char *message;
		int number;
	} status;
	struct hashmap *header;
};

struct http_response new_response_header();
char *response_header_to_string(struct http_response);
void set_response_status(struct http_response*, int);
void set_response_header(struct http_response*, char*, char*);
//void set_response_content(struct http_response*, char*);
#endif