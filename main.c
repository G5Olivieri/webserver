#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "string.h"
#include "http/http.h"

#define PORT 2666

void vindex(struct http_response *hh)
{
	set_response_header(hh, "Content-Type", "text/html");
	char *str = new_string("<html><head><title>Glayson</title></head><body><h1>Glayson</h1></body></html>");
	http_write(*hh, str);
}

void gindex(struct http_response *hh)
{
	set_response_header(hh, "Content-Type", "text/html");
	char *str = new_string("<html><head><title>Glayson</title></head><body><h1>Teste</h1></body></html>");
	http_write(*hh, str);
}


int main()
{
	http_init();
	http_set_handle("/", vindex);
	http_set_handle("/oi", gindex);
	http_run(PORT);
	return 0;
}
