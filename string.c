#include <stdio.h>
#include <stdlib.h>

void print(char*);
int str_len(const char*);
char *str_concat(char*, const char*);
char *str_sub(char *, int, int);
int str_contains(const char*, const char*);
int str_comp(const char*, const char*);

int main()
{
    char *g = "Murollo";
    g = str_concat("Meu pay ", "Glayson");
    print(g);
    printf("%d\n", str_contains(g, "o"));
    return 0;
}

int str_comp(const char *str, const char *str1)
{
    
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

char *str_sub(char *str, int in, int la1)
{
    int la = la1 + 1;
    if(in < 0 || in > str_len(str) || la <= in || la <= 0 || la > str_len(str))
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

void print(char *g)
{
    if(g == NULL) return;
    puts(g);
    printf("%d\n", str_len(g));
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
