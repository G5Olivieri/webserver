#include "string.h"

uint str_len(char* str)
{
	int cont=0;
	while(*str!='\0')
	{
		cont++;
		str++;
	}
	return cont;
}

int str_comp(char *str, char *str1)
{
	if(str == NULL)
	{
		if(str1 == NULL)
		{
			return 0;
		}
		else
		{
			return -1;
		}
	}
	if(str1 == NULL)
		return 1;
	int len = str_len(str), len1 = str_len(str1);
	int m = min(len, len1);
	int i;
	for(i=0;i<m;i++)
	{
		if(*str < *str1)
			return -1;
		else if(*str > *str1)
		 {
		 	return 1;
		 }
		str++;str1++;
	}
	if(len == len1)
		return 0;
	else if(len > len1)
		return 1;
	else
		return -1;
	return 0;
}

char *new_string(char *str)
{
	char *nw = (char*)malloc(str_len(str)+1);
	char *it=nw;
	while(*str!='\0')
	{
		*it=*str;
		it++;
		str++;
	}
	*it='\0';
	return nw;
}


char *str_concat(char *str, char *str1)
{
	int i;
	int len = str_len(str), len1 = str_len(str1);
	char *cat = (char*)malloc((len+len1+1)*sizeof(char));
	for(i=0;i<len;i++)
	{
		cat[i] = str[i];
	}
	for(i=0;i<len1;i++)
	{
		cat[i+len] = str1[i];
	}
	cat[len+len1] = '\0';
	return cat;
}

char *get_line(char *str)
{
    char *it, *buffer;
    int len_line = 0, i;
    it = str;
    while(*it != '\0' && *it != '\n')
    {
        len_line++;
        it++;
    }
    buffer = (char*)malloc(sizeof(char)*len_line + 1);
    it = str;
    for(i = 0; i < len_line; i++)
    {
        buffer[i] = *it;
        it++;
    }
    buffer[i] = '\0';
    return buffer;
}