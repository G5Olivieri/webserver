#ifndef _GUTILS_H
#define _GUTILS_H

#define min(a,b) a < b ? a : b
#define max(a,b) a > b ? a : b

#include <stdlib.h>
#include <stdio.h>

#define error(a, b) \
if(a < 0) {\
printf("ERROR function: %s line %d\n", #b, __LINE__);\
exit(EXIT_FAILURE); \
}

typedef unsigned uint;
typedef enum _bool {false, true} bool;

#endif