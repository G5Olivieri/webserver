#ifndef _MAP_H
#define _MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* string;

typedef enum _bool {false, true} bool;

typedef struct no {
    string key;
    string value;
    struct no *p, *n;
}*no, no_t;

typedef struct _map {
    size_t len;
    struct no *f, *l;
}*map, map_t;

bool map_isEmpty(map m)
{
    return (m == NULL);
}

no map_getPair(map *m, string key)
{
    no *temp = &(*m)->f->n;
    while((*temp) != NULL)
    {
        if(strcmp((*temp)->key, key) == 0)
        {
            return (*temp);
        }
        temp = &(*temp)->n;
    }
    return NULL;
}


void map_put(map *m, string k, string v)
{
    no newno = (no)malloc(sizeof(no_t));
    newno->key = k;
    newno->value = v;
    newno->n = NULL;
    newno->p = NULL;

    if(map_isEmpty(*m))
    {
        (*m) = (map)malloc(sizeof(map_t));
        (*m)->f = (no)malloc(sizeof(no_t));
        (*m)->l = (no)malloc(sizeof(no_t));

        (*m)->f->p = NULL;
        (*m)->l->n = NULL;

        (*m)->f->n = newno;
        (*m)->l->p = newno;
        (*m)->len = 1;
    } else {
        no temp = map_getPair(m, k);
        if(temp == NULL)
        {
            (*m)->l->p->n = newno;
            newno->p = (*m)->l->p;

            free((*m)->l);
            (*m)->l = (no)malloc(sizeof(no_t));
            (*m)->l->p = newno;
            (*m)->len++;
        } else {
            temp->value = v;
        }
    }
}

#endif // _MAP_H