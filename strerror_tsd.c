/*************************************************************************
    > File Name: strerror_tsd.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年07月02日 星期日 21时10分14秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

#define MSG_LEN 256

pthread_once_t once = PTHREAD_ONCE_INIT;
pthread_key_t strerrorKey;


void destructor(void* buff)
{
    free(buff);
}

void createKey(void)
{
    int ret;
    ret = pthread_key_create(&strerrorKey, destructor);
    CHECK_THREAD_RET(ret, "pthread_key_create");
}

char* strerrorTsd(int err)
{
    int ret;
    char*  buff;
    
    ret = pthread_once(&once, createKey);
    CHECK_THREAD_RET(ret, "pthread_once");

    buff = pthread_getspecific(strerrorKey);
    if (buff == NULL)
    {
        buff = malloc(MSG_LEN);
        if (buff == NULL)
        {
            return NULL;
        }

        ret = pthread_setspecific(strerrorKey, buff);
        CHECK_THREAD_RET(ret, "pthread_setspecific");
    }

    snprintf(buff, MSG_LEN, "error[%d]", err);
    return buff;
}

void* threadFunc(void* arg)
{
    char* str;
    printf("Other thread about to call strerrorTsd\n");
    str = strerrorTsd(EPERM);
    printf("Other thread: str(%p:%s)\n", str, str);
    return NULL;
}

int main()
{
    pthread_t tid;
    int ret;
    char* str;

    str = strerrorTsd(EINVAL);
    printf("Main thread has called strerrorTsd\n");

    ret = pthread_create(&tid, NULL, threadFunc, NULL);
    CHECK_THREAD_RET(ret, "pthread_create");

    ret = pthread_join(tid, NULL);
    CHECK_THREAD_RET(ret, "pthread_join");

    printf("Main thread: str(%p:%s)\n", str, str);

    return 0;
}
