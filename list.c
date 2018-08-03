#include "list.h"

static struct node* new_node(struct node* previus, void* data, struct node* next)
{
	struct node* nw = (struct node*)malloc(sizeof(struct node));
	nw->next = next;
	nw->previus = previus;
	nw->data = data;
	return nw;
}

void list_append(struct list **l, void *data)
{
	if(*l == NULL)
	{
		*l = (struct list *)malloc(sizeof(struct list));
		(*l)->first = new_node(NULL, data, NULL);
		(*l)->last = new_node(NULL, data, NULL);
		(*l)->size = 1;
	}
	else
	{
		if((*l)->size == 1)
		{
			(*l)->last = new_node((*l)->first, data, NULL);
			(*l)->first->next = (*l)->last;
			
		}
		else
		{
			(*l)->last->next = new_node((*l)->last, data, NULL);
			(*l)->last = (*l)->last->next;
		}
		(*l)->size++;
	}
}

void list_free(struct list **l)
{
	struct node *it = (*l)->first;
	(*l)->first = (*l)->first->next;
	while((*l)->first != NULL)
	{
		free(it);
		it = (*l)->first;
		(*l)->first = (*l)->first->next;
	}
	free(it);
	free((*l));
}