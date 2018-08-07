#ifndef _HTTP_H_
#define _HTTP_H_

#include <sys/socket.h>
#include <sys/utsname.h>
#include <netinet/in.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

#include "../string.h"
#include "../gutils.h"
#include "../list.h"

#include "response.h"
#include "request.h"

struct http_server
{
	int sock;
	struct sockaddr_in addr;
};

struct handle {
	char *msg;
	void (*func_handle)(struct http_response*, struct http_request*);
};	

struct http_server server;
struct list *handles;
char *public;
int cli;

void http_init();
static char * http_read();
void http_write(struct http_response, char*);
static void http_close();
static struct http_server server_config();
void http_run(int);
void http_set_handle(char *str, void (*)(struct http_response*, struct http_request*));
static void http_handle_not_found(struct http_response*, struct http_request*);
char *file_read(char *);
void http_set_public(char*);

#endif