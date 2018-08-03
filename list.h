#ifndef _LIST_H_
#define _LIST_H_

#include <stdlib.h>
#include "gutils.h"

struct node {
	void *data;
	struct node *next, *previus;
};

struct list {
	struct node *first, *last;
	uint size;
};

static struct node* new_node(struct node*, void*, struct node*);
void list_append(struct list **, void *);
void list_free(struct list **);

#endif