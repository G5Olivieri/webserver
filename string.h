#ifndef _STRING_H_
#define _STRING_H_

#include "gutils.h"
#include <stdlib.h>

uint str_len(char*);
int str_comp(char*, char*);
char* new_string(char*);
char *str_concat(char *,char *);
char *get_line(char*);

#endif