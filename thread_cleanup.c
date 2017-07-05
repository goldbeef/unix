/*************************************************************************
    > File Name: thread_cleanup.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年07月03日 星期一 22时13分17秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
int glob = 0;

void cleanupHandler(void* arg)
{
    int ret;
    printf("cleanup: freeing block at %p\n", arg);
    free(arg);

    printf("cleanup: unlocking mutex\n");

    ret = pthread_mutex_unlock(&mtx);
    CHECK_THREAD_RET(ret, "pthread_mutex_unlock");
}


void* threadFunc(void* arg)
{
    int ret;
    void* buff = NULL;

    buff = malloc(1000);
    printf("thead: allocated memory at %p\n", buff);
    

    ret = pthread_mutex_lock(&mtx);
    CHECK_THREAD_RET(ret, "pthread_mutex_lock");

    pthread_cleanup_push(cleanupHandler, buff);

    while (glob == 0)
    {
        ret = pthread_cond_wait(&cond, &mtx);
        CHECK_THREAD_RET(ret, "pthread_cond_wait");
    }

    printf("thread, condition_wait loop completed\n");
    pthread_cleanup_pop(1);

    return NULL;
}

int main(int argc, char* argv[])
{
    pthread_t tid;
    void* res;
    int ret;

    ret = pthread_create(&tid, NULL, threadFunc, NULL);
    CHECK_THREAD_RET(ret, "pthread_create");

    sleep(2);

    if (argc > 1)
    {
        printf("main: about to signal thread\n");
        glob = 1;
        ret = pthread_cond_signal(&cond);
        CHECK_THREAD_RET(ret, "pthread_cond_signal");
    }
    else
    {
        printf("main: about to cancel thread\n");
        ret = pthread_cancel(tid);
        CHECK_THREAD_RET(ret, "pthread_cancel");
    }

    ret = pthread_join(tid, &res);
    CHECK_THREAD_RET(ret, "pthread_join");

    if (res == PTHREAD_CANCELED)
    {
        printf("main: thead was canceled\n");
    }
    else
    {
        printf("main: thread terminated normally\n");
    }

    return 0;


}
