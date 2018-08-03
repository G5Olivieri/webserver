#include "response.h"

struct http_response new_response_header()
{
    struct http_response hh;
    hh.header = NULL;
    hh.status.message = NULL;
    set_response_status(&hh, 200);
    return hh;
}

void destroy_response_header(struct http_response *hh)
{
    if(hh->status.message != NULL)
    {
        free(hh->status.message);
    }
    hash_free(&hh->header);
}

char *response_header_to_string(struct http_response hh)
{
	char *str, buffer[128], *aux;
	sprintf(buffer, "HTTP/1.1 %d %s\r\n", hh.status.number, hh.status.message);
    str = new_string(buffer);
    struct node *it;
	int i;
    struct list *l = hash_get_pairs(hh.header);
    if(l != NULL)
    {
        it = l->first;
        for(i = 0; i < l->size; i++)
        {
            aux = str;
            str = str_concat(str, str_concat(((struct pair *)it->data)->key, str_concat(": ", str_concat(((struct pair*)it->data)->value, "\r\n"))));
            free(aux);
            it=it->next;
        }
    }
    aux = str;
    str = str_concat(str, "\r\n");
	return str;
}

void set_response_status(struct http_response *hh, int s)
{
    if(hh->status.message != NULL)
    {
        free(hh->status.message);
    }
	switch(s)
	{
		case 200:
			hh->status.number = s;
			hh->status.message = new_string("OK");
            break;
        case 404:
            hh->status.number = s;
            hh->status.message = new_string("NOT FOUND");
		break;
	}
}


void set_response_header(struct http_response *hh, char *att, char *value)
{
    hash_put(&hh->header, att, value);
}

/*void set_response_content(struct http_response *hh, char *content)
{
    if(hh->content != NULL)
        free(hh->content);
    hh->content = new_string(content);
}*/