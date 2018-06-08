#ifndef _STRING_H
#define _STRING_H

#include <stdio.h>
#include <stdlib.h>

int str_len(const char*);
char *str_concat(char*, const char*);
char *str_sub(char *, int, int);
int str_contains(const char*, const char*);
int str_comp(const char*, const char*);
char *getLine(const char*);
int sizeLine(const char*);
char *str_toLowerCase(char *);
char *str_toUpperCase(char *);
char *str_copy(char*);
char *trim(char *);

char *str_copy(char *str)
{
    if(str == NULL) return NULL;
    char *buffer = (char*)malloc(str_len(str));
    buffer = str;
    return buffer;
}

char *trim(char *str)
{
    char *it;
    it = str + str_len(str)-1;
    int i = 0;
    while(*it == ' ')
    {
        it--; i++;
    }
    str = str_sub(str, 0, str_len(str)-i);
    while(*str == ' ') str++;
    return str_copy(str);
}

char *getLine(const char *str)
{
    if(str == NULL) return NULL;
    int sz = sizeLine(str);
    if(sz <= 0) return NULL;
    char *buffer = (char*)malloc(sz + 1);
    int i;
    char *it, *itr;
    it = str;
    itr = buffer;
    for(i = 0; i < sz; i++)
    {
        *itr = *it;
        it++;itr++;
    }
    *itr = '\0';
    return buffer;
}

int sizeLine(const char *str)
{
    if(str == NULL) return -1;
    if(*str == '\0') return -1;
    char *it;
    it = str;
    int i = 0;
    while(*it != '\0' && *it != '\n' && *it != '\r')
    {
        it++;i++;
    }
    return i;
}

int str_comp(const char *str, const char *str1)
{
    while(*str != '\0' && *str1 != '\0')
    {
        if(*str < *str1)
        {
            return -1;
        }
        else if(*str > *str1)
        {
            return 1;
        }
        str++;str1++;
    }
    return 0;
}

int str_contains(const char *str, const char *str1)
{
    if(str == NULL || str1 == NULL) return -1;
    char *it;
    it = str;
    char *it1;
    it1 = str1;
    int i;
    size_t sz = str_len(str)-(str_len(str1)-1);
    for(i = 0; i < sz; i++)
    {
        if(*it == *it1) {
            while(*it1 != '\0')
            {
                if(*it != *it1)
                {
                    it1 = str1;
                    break;
                }
                it++;it1++;i++;
            }
            if(*it1 == '\0')
            {
                return i-str_len(str1);
            }
        }
        it++;
    }
    return -1;
}

char *str_sub(char *str, int in, int la)
{
    if(in < 0 || in > str_len(str) || la < in || la < 0 || la > str_len(str))
    {
        return NULL;
    }
    char *it;
    char *buffer = (char *)malloc(la - in + 1);
    char *itr;
    itr = buffer;
    it = (str+in);
    int i;
    for(i = in; i < la; i++)
    {
        *itr = *it;
        itr++; it++;
    }
    *itr = '\0';
    return buffer;
}

char *str_concat(char *str, const char *str1)
{
    if(str == NULL || str1 == NULL) return NULL;
    char *buffer = (char*)malloc(str_len(str) + str_len(str1)+1);
    char *it;
    it = buffer;
    int i;
    size_t sz = str_len(str);
    for(i = 0; i < sz; i++)
    {
        *it = *str;
        it++;str++;
    }
    sz = str_len(str1);
    for(i = 0; i < sz; i++)
    {
        *it = *str1;
        it++;str1++;
    }
    *it = '\0';
    return buffer;
}

int str_len(const char *str)
{
    if(str == NULL)
    {
        return -1;
    }
    int i = 0;
    char *it;
    it = str;
    while(*it != '\0')
    {
        it++;i++;
    }
    return i;
}

char *str_toUpperCase(char *str)
{
    char *buffer = (char*)malloc(str_len(str)+1);
    char *it, *itr;
    it = str; itr = buffer;
    while(*it != '\0')
    {
        if(*it >= 'a' && *it <= 'z')
        {
            *itr = (*it-'a') + 'A';
        }
        else
        {
            *itr = *it;
        }
        it++;itr++;
    }
    return buffer;
}

char *str_toLowerCase(char *str)
{
    char *buffer = (char*)malloc(str_len(str)+1);
    char *it, *itr;
    it = str; itr = buffer;
    while(*it != '\0')
    {
        if(*it >= 'A' && *it <= 'Z')
        {
            *itr = (*it-'A') + 'a';
        }
        else
        {
            *itr = *it;
        }
        it++;itr++;
    }
    return buffer;
}

#endif // _STRING_H