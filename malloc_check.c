/*************************************************************************
    > File Name: malloc_check.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年05月20日 星期六 19时35分05秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <mcheck.h>
#include <unistd.h>

// a.out block-num block-size step min max
int main(int argc, char* argv[])
{
    mtrace();
 
    if (argc < 6)
    {
        printf("%s block-num block-size step min max\n", argv[0]);
        return -1;
    }

    int blockNum = atoi(argv[1]);
    int blockSize = atoi(argv[2]);
    int step = atoi(argv[3]);
    int min = atoi(argv[4]);
    int max = atoi(argv[5]);

    if (blockNum < 0 || blockSize < 0
        || step < 0 || min < 0 || max < 0
       )
    {
        printf("invlaid paramp\n");
        return -1;
    }

    char** ptrArray = (char**) malloc(blockNum*sizeof(char*));
    if (ptrArray == NULL)
    {
        printf("malloc fail, ptrArray\n");
        return -1;
    }

    int i;
    for (i = 0; i < blockNum; i++)
    {
        ptrArray[i] = (char*) malloc(blockSize);
        if (ptrArray[i] == NULL)
        {
            printf("malloc fail, ptrArray[%d]\n", i);
            return -1;
        }
    }
    printf("all malloc finished, program break[%p]\n", sbrk(0));

    for (i = min; i <= max && i < blockNum; i += step)
    {
        free(ptrArray[i]);
    }

    printf("after free, program break[%p]\n", sbrk(0));

    return 0;
}

