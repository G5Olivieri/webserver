#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>

#include "string.h"
#include "http/http.h"

#define PORT 2666

void vindex(struct http_response *hh, struct http_request *req)
{
	set_response_header(hh, "Content-Type", "text/html");
	char *str = new_string("<html><head><title>Glayson</title></head><body><h1>Glayson</h1></body></html>");
	http_write(*hh, str);
}

void gindex(struct http_response *hh, struct http_request *req)
{
	set_response_header(hh, "Content-Type", "text/html");
	char *str = new_string("<html><head><title>Glayson</title></head><body><h1>Teste</h1></body></html>");
	http_write(*hh, str);
}

void hindex(struct http_response *hh, struct http_request *req)
{
	set_response_status(hh, 404);
	char *str = new_string("");
	http_write(*hh, str);
}

void eindex(struct http_response *hh, struct http_request *req)
{
	http_write(*hh, new_string(file_read("index.html")));
}

int main()
{
	http_init();
	http_set_public("./public");
	http_set_handle("/", vindex);
	http_set_handle("/oi", gindex);
	http_set_handle("/merda", hindex);
	http_set_handle("/glayson", eindex);
	http_run(PORT);
	
	return 0;
}
