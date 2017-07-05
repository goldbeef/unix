/*************************************************************************
    > File Name: thread.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年07月01日 星期六 09时30分47秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

void* threadFunc(void* arg)
{
    char* s = (char*) arg;
    printf("threadFunc,  msg[%s]\n", s);
    return (void*) strlen(s);
}

int main()
{
    pthread_t tid;
    void* res;
    int ret;
    pthread_attr_t attr;

    ret = pthread_attr_init(&attr);
    CHECK_THREAD_RET(ret, "pthread_attr_init");
    ret = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    CHECK_THREAD_RET(ret, "pthread_attr_setdetachstate");


    ret = pthread_create(&tid, &attr, threadFunc, "hello world\n");
    CHECK_THREAD_RET(ret, "pthread_create");

    printf("Message from main()\n");
    
   // pause();

    ret = pthread_join(tid, &res);
    CHECK_THREAD_RET(ret, "pthread_join");

    printf("Thread return, ret[%d]\n", (int)res);

    return 0;
}
