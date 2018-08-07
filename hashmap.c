#include "hashmap.h"

static struct pair* new_pair(char *key, char *value)
{
	struct pair *nw = (struct pair*)malloc(sizeof(struct pair));
	nw->key = new_string(key);
	nw->value = new_string(value);
	return nw;
}

static struct hashmap* new_hashmap(uint capacity)
{
	struct hashmap* nw = (struct hashmap*)malloc(sizeof(struct hashmap));
	nw->table = (struct list**)malloc(capacity * sizeof(struct list *));
	int i;
	for(i=0;i<capacity;i++)
	{
		nw->table[i] = NULL;
	}
	nw->capacity = capacity;
	nw->size = 0;
	return nw;
}

static uint hash_index(struct hashmap *hm, char *str)
{
	uint prime=31, result=1;
	while(*str!='\0')
	{
		result=result*prime + (int)(*str);
		str++;
	}
	return result % hm->capacity;
}


static void hash_resize(struct hashmap **hm, uint capacity)
{
	struct hashmap *nw = new_hashmap(capacity);
	struct node *it ;
	int i;
	for(i=0;i<(*hm)->capacity;i++)
	{
		if((*hm)->table[i] != NULL)
		{
			it = (*hm)->table[i]->first;
			while(it != NULL)
			{
				hash_put(&nw, ((struct pair*)it->data)->key, ((struct pair*)it->data)->value);
				it = it->next;
			}
		}
	}
	hash_free(hm);
	*hm = nw;
}

void hash_put(struct hashmap **hm, char *key, char *value)
{
	if(*hm == NULL)
	{
		*hm = new_hashmap(16);
	}
	int i = hash_index(*hm, key);
	struct node *it;
	if((*hm)->table[i] != NULL)
	{
		it = (*hm)->table[i]->first;
		while(it != NULL)
		{
			if(!str_comp(((struct pair*)it->data)->key, key))
			{
				free(((struct pair*)it->data)->value);
				((struct pair*)it->data)->value = new_string(value);
				return;
			}
			it = it->next;
		}
		list_append(&(*hm)->table[i], new_pair(key, value));
		return;
	}
	list_append(&(*hm)->table[i], new_pair(key, value));
	(*hm)->size++;
	if((*hm)->size >= (int)((*hm)->capacity * 0.75))
	{
		hash_resize(hm, (*hm)->capacity*2);
	}
}

void hash_free(struct hashmap **hm)
{
	if(*hm == NULL)
	{
		return;
	}
	int i;
	for(i=0;i<(*hm)->capacity;i++)
	{
		if((*hm)->table[i] != NULL)
		{
			list_free(&(*hm)->table[i]);
		}
	}
	free((*hm));
}

void hash_print(struct hashmap *hm)
{
	if(hm == NULL)
	{
		return;
	}
	struct node *it ;
	int i;
	for(i=0;i<hm->capacity;i++)
	{
		if(hm->table[i] != NULL)
		{
			it = hm->table[i]->first;
			while(it != NULL)
			{
				printf("%s=>%s\n", ((struct pair*)it->data)->key, ((struct pair*)it->data)->value);
				it = it->next;
			}
		}
	}
}

struct list *hash_get_pairs(struct hashmap *hm)
{
	if(hm == NULL)
	{
		return NULL;
	}
	struct list *l = NULL;
	struct node *it ;
	int i;
	for(i=0;i<hm->capacity;i++)
	{
		if(hm->table[i] != NULL)
		{
			it = hm->table[i]->first;
			while(it != NULL)
			{
				list_append(&l, new_pair(((struct pair*)it->data)->key, ((struct pair*)it->data)->value));
				it = it->next;
			}
		}
	}
	return l;
}