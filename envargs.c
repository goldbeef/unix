/*************************************************************************
    > File Name: envargs.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年06月25日 星期日 15时38分42秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

extern char** environ;

int main(int argc, char* argv[])
{
    int j;
    char** ep;

    for (j = 0; j < argc; j++)
    {
        printf("argv[%d] = %s\n", j, argv[j]);
    }

    int count = 0;
    for (ep = environ; *ep != NULL; ep++)
    {
        printf("environ[%d] = %s\n", count, *ep);
        count++;
    }

    return 0;
}
