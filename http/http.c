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
	public = NULL;
	cli = 0;
}

static char *http_read()
{
	int aux;
	char *buffer = (char*)malloc(sizeof(char)*1024);

	aux = read(cli, buffer, 1024);
	buffer[aux] = 0;
	return buffer;
}

void http_write(struct http_response hr, char *str)
{
	char *aux;
	aux = str;
	str = str_concat(response_header_to_string(hr), str);
	free(aux);
	write(cli, str, str_len(str));
	free(str);
}

static void http_close()
{
	printf("close %d\n", cli);
	error(shutdown(cli, SHUT_RDWR), shutdown); // SHUT_RD, SHUT_WR
}

static struct http_server server_config(int port)
{
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
	server_config(port);
    int aux = sizeof(server.addr);
	struct http_response response;
	struct node *it;
	struct http_request *request;
	struct sockaddr_in addr_cli;
	char *buffer, *file;
	while(true){
		cli = accept(server.sock, (struct sockaddr*)&addr_cli, &aux);
		error(cli, accept);
		printf("open %d\n", cli);
		response = new_response_header();
		request = string_to_request_header(http_read());
		it = handles->first;
		while(it != NULL)
		{
			if(!str_comp(((struct handle*)it->data)->msg, request->uri))
			{
				((struct handle*)it->data)->func_handle(&response, request);
				break;
			}
			it = it->next;
		}
		if(it == NULL)
		{
			if(public != NULL)
			{
				buffer = str_concat(public, request->uri);
				file = file_read(buffer);
				if(file != NULL)
				{
					http_write(response, file);
				}
				else
					http_handle_not_found(&response, request);
				free(buffer);
			}
			else
				http_handle_not_found(&response, request);
		}
		free(request);
		http_close();
	}
}

void http_set_handle(char *str, void (*func_handle)(struct http_response *hh, struct http_request *req))
{
	struct handle *hd = (struct handle *)malloc(sizeof(struct handle));
	struct node *it;
	hd->msg = str;
	hd->func_handle = func_handle;
	if(handles != NULL)
	{
		it = handles->first;
		while(it != NULL)
		{
			if(!str_comp(((struct handle*)it->data)->msg, str))
			{
				it->data = hd;
				return;
			}
			it = it->next;
		}
		list_append(&handles, hd);
	}
	else
		list_append(&handles, hd);
}

static void http_handle_not_found(struct http_response *response, struct http_request *request)
{
	struct utsname name;
	uname(&name);
	char *buffer = new_string("<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><title>404 NOT FOUND</title></head><body><h1>Not Found</h1><p>The requested URL %s not found on this server.</p><hr><p>Glayson/0.0.1 (%s) Server at %s Port %d</p></body></html>");
	char *str = (char*)malloc(sizeof(char)* (str_len(buffer) + str_len(request->uri) + str_len(name.sysname) + 10));
	//name.sysname: OS, name.nodename: username, name.release: 2.2.1, name.version: date, name.machine: x86_64
	sprintf(str, buffer,
	 request->uri, name.sysname, "localhost", ntohs(server.addr.sin_port));
	set_response_status(response, 404);
	http_write(*response, str);
	free(buffer);
}

void http_set_public(char *path)
{
	public = new_string(path);
}

char *file_read(char *path)
{
	FILE *file;
    file = fopen(path, "r");
    if(file == NULL)
    {
        perror("fopen failure");
        return NULL;
	}
    fseek(file, 0L, SEEK_END);
    size_t szfile = ftell(file);
    rewind(file);
    char *buffer = (char*)malloc(sizeof(char) * (szfile + 1));
    fread(buffer, szfile, 1, file);
    buffer[szfile] = '\0';
    fclose(file);
	return buffer;
}