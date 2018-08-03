#ifndef _HTTP_H_
#define _HTTP_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

#include "../string.h"
#include "../gutils.h"
#include "response.h"
#include "../list.h"

struct http_server
{
	int sock;
	struct sockaddr_in addr;
};

struct handle {
	char *msg;
	void (*func_handle)(struct http_response *hh);
};	

struct list *handles;
int cli;

void http_init();
static void http_read();
void http_write(struct http_response, char*);
static void http_close();
static struct http_server server_config();
void http_run(int);
void http_set_handle(char *str, void (*)(struct http_response*));

#endif