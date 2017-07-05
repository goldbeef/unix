/*************************************************************************
    > File Name: thread_multijoin.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年07月01日 星期六 14时15分56秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

pthread_cond_t threadDied = PTHREAD_COND_INITIALIZER;
pthread_mutex_t threadMutex = PTHREAD_MUTEX_INITIALIZER;

int totalThreads = 0;
int numLive = 0;
int numUnJoined = 0;

enum tstate
{
    TS_ALIVE,
    TS_TERMINATED,
    TS_JOINED
};

struct thread{
    pthread_t tid;
    enum tstate state;
    int sleepTime;
};

struct thread* threadInfo;

void* threadFunc(void* arg)
{
    int idx = (int)arg;
    int ret;

    sleep(threadInfo[idx].sleepTime);

    ret = pthread_mutex_lock(&threadMutex);
    CHECK_THREAD_RET(ret, "pthread_mutex_lock");

    numUnJoined++;
    threadInfo[idx].state = TS_TERMINATED;

    ret = pthread_cond_signal(&threadDied);
    CHECK_THREAD_RET(ret, "pthread_cond_signal");

    ret = pthread_mutex_unlock(&threadMutex);
    CHECK_THREAD_RET(ret, "pthread_mutex_unlock");
    
    /*
    ret = pthread_cond_signal(&threadDied);
    CHECK_THREAD_RET(ret, "pthread_cond_signal");
    */

    return NULL;
}

int main(int argc, char* argv[])
{
    int ret, idx;

    if (argc < 2 || strcmp(argv[1], "--help") == 0)
    {
        CHECK_RET(-1, "Usage: %s time1 time2 ...\n", argv[0]);
    }

    threadInfo = malloc((argc - 1) * sizeof(struct thread));
    CHECK_NULL(threadInfo, "malloc");

    for (idx = 0; idx < argc - 1; idx++)
    {
        threadInfo[idx].sleepTime = atoi(argv[idx + 1]);
        threadInfo[idx].state = TS_ALIVE;
        ret = pthread_create(&threadInfo[idx].tid, NULL, threadFunc, (void*)idx);
        CHECK_THREAD_RET(ret, "pthread_create");
    }

    totalThreads = argc - 1;
    numLive = totalThreads;

    //join with terminated thread;
    while (numLive > 0)
    {
        ret = pthread_mutex_lock(&threadMutex);
        CHECK_THREAD_RET(ret, "pthread_mutex_lock");

        while (numUnJoined == 0)
        {
            ret = pthread_cond_wait(&threadDied, &threadMutex);
            CHECK_THREAD_RET(ret, "pthread_cond_wait");
        }

        for (idx = 0; idx < totalThreads; idx++)
        {
            if (threadInfo[idx].state == TS_TERMINATED)
            {
                ret = pthread_join(threadInfo[idx].tid, NULL);
                CHECK_THREAD_RET(ret, "pthread_join");

                threadInfo[idx].state = TS_JOINED;
                numLive--;
                numUnJoined--;
                printf("Reaped thread %d (numLive=%d)\n", idx, numLive);
            }
        }
        ret = pthread_mutex_unlock(&threadMutex);
        CHECK_THREAD_RET(ret, "pthread_mutex_unlock");
    }

    return 0;
}
