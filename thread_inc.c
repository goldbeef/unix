/*************************************************************************
    > File Name: thread_inc.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年07月01日 星期六 09时55分50秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

#define MAX_THREAD 10

int global = 0;
pthread_t tids[MAX_THREAD];

void* threadFunc(void* arg)
{
    int i;
    int loop = *((int*)arg);
    for (i = 0; i < loop; i++)
    {
        global++;
    }

    return NULL;
}

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        CHECK_RET(-1, "Usage: %s thread-num loop\n", argv[0]);
    }
    
    int threadNum = atoi(argv[1]);
    if (threadNum > MAX_THREAD)
    {
        threadNum = MAX_THREAD;
    }
    
    int loop = atoi(argv[2]);

    printf("threadNum[%d], loop[%d], global[%d]\n", threadNum, loop, global);

    int i, ret;
    for (i = 0; i < threadNum; i++)
    {
        ret = pthread_create(&tids[i], NULL, threadFunc, &loop);
        CHECK_THREAD_RET(ret, "pthread_create");
    }

    for (i = 0; i < threadNum; i++)
    {
        ret = pthread_join(tids[i], NULL);
    }

    printf("threadNum[%d], loop[%d], global[%d]\n", threadNum, loop, global);
    return 0;
}
