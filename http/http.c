#include "http.h"

static void handler_interuption(int a)
{
	printf("Shutdown server...\n");
	list_free(&handles);
	exit(EXIT_SUCCESS);
}

void http_init()
{
	handles = NULL;
	cli = 0;
}

static char *http_read()
{
	int aux;
	char *buffer = (char*)malloc(sizeof(char)*1024), *it, *uri = (char*)malloc(sizeof(char)*4);

	aux = read(cli, buffer, 1024);
	buffer[aux] = 0;
	printf(buffer);
	it = buffer;
	while(*it != '\0' && *it != ' ')
	{ 
		it++;
	}
	it++;
	aux = 0;
	while(*it != ' ' && *it != '\0')
	{
		uri[aux] = *it;
		it++; aux++;
	}
	uri[aux] = '\0';
	free(buffer);
	return uri;
}

void http_write(struct http_response hr, char *str)
{
	char *aux;
	aux = str;
	str = str_concat(response_header_to_string(hr), str);
	free(aux);
	write(cli, str, str_len(str));
}

static void http_close()
{
	error(shutdown(cli, SHUT_RDWR), shutdown); // SHUT_RD, SHUT_WR
}

static struct http_server server_config(int port)
{
	struct http_server server;
	
	server.sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	error(server.sock, socket);
	
	server.addr.sin_family = AF_INET;
	server.addr.sin_port = htons(port);
	server.addr.sin_addr.s_addr = INADDR_ANY;
	
	error(bind(server.sock, (struct sockaddr*)&server.addr, sizeof(server.addr)), bind);
	
	error(listen(server.sock, 3), listen);

	return server;
}

void http_run(int port)
{
	signal(SIGINT, handler_interuption);
	struct http_server server = server_config(port);
    int aux = sizeof(server.addr);
	struct http_response response = new_response_header();
	struct node *it;
	char *uri;
	while(true){
		cli = accept(server.sock, (struct sockaddr*)&server.addr, &aux);
		error(cli, accept);
		uri = http_read();
		it = handles->first;
		while(it != NULL)
		{
			if(!str_comp(((struct handle*)it->data)->msg, uri))
			{
				((struct handle*)it->data)->func_handle(&response);
			}
			it = it->next;
		}
		free(uri);
		http_close();
	}
}

void http_set_handle(char *str, void (*func_handle)(struct http_response *hh))
{
	struct handle *hd = (struct handle *)malloc(sizeof(struct handle));
	hd->msg = str;
	hd->func_handle = func_handle;
	list_append(&handles, hd);
}