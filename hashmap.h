#ifndef _HASHMAP_H_
#define _HASHMAP_H_

#include <stdio.h>
#include <stdlib.h>
#include "gutils.h"
#include "string.h"
#include "list.h"

struct pair {
	char *key;
	char *value;
};

struct hashmap {
	struct list **table;
	uint size;
	uint capacity;
};

static struct pair* new_pair(char*, char*);
static struct hashmap* new_hashmap(uint);

static uint hash_index(struct hashmap*, char*);
static void hash_resize(struct hashmap**, uint);

void hash_put(struct hashmap**, char*, char*);
void hash_free(struct hashmap**);
void hash_print(struct hashmap*);
struct list *hash_get_pairs(struct hashmap*);

#endif