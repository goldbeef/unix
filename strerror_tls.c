/*************************************************************************
    > File Name: strerror_tsd.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年07月02日 星期日 21时10分14秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

#define MSG_LEN 256


__thread char buff[MSG_LEN];

char* strerrorTls(int err)
{
    int ret;
    snprintf(buff, MSG_LEN, "error[%d]", err);
    return buff;
}

void* threadFunc(void* arg)
{
    char* str;
    printf("Other thread about to call strerrorTls\n");
    str = strerrorTls(EPERM);
    printf("Other thread: str(%p:%s)\n", str, str);
    return NULL;
}

int main()
{
    pthread_t tid;
    int ret;
    char* str;

    str = strerrorTls(EINVAL);
    printf("Main thread has called strerrorTls\n");

    ret = pthread_create(&tid, NULL, threadFunc, NULL);
    CHECK_THREAD_RET(ret, "pthread_create");

    ret = pthread_join(tid, NULL);
    CHECK_THREAD_RET(ret, "pthread_join");

    printf("Main thread: str(%p:%s)\n", str, str);

    return 0;
}
