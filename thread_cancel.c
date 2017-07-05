/*************************************************************************
    > File Name: thread_cancel.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年07月03日 星期一 22时05分02秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

void* threadFunc(void* arg)
{
    int i;
    printf("new thread start\n");

    for (i = 0; ; i++)
    {
        printf("loop, i[%d]\n", i);
        sleep(1);
    }

    return NULL;
}

int main()
{
    pthread_t tid;
    int  ret;
    void* res;

    ret = pthread_create(&tid, NULL, threadFunc, NULL);
    CHECK_THREAD_RET(ret, "pthread_create");

    sleep(3);
    
    ret = pthread_cancel(tid);
    CHECK_THREAD_RET(ret, "pthread_cancel");

    ret = pthread_join(tid, &res);
    CHECK_THREAD_RET(ret, "pthread_join");

    if (res == PTHREAD_CANCELED)
    {
        printf("thread was canceled\n");
    }
    else
    {
        printf("thread was not canceled( should not happed)\n");       
    }
    return 0;
}
