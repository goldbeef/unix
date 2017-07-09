/*************************************************************************
    > File Name: ptmr_sigev_signal.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年07月09日 星期日 16时21分20秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

#define TIMER_SIG SIGRTMAX

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int expireCnt = 0;

void threadFunc(union sigval sv)
{
    timer_t* pTimerID;
    pTimerID = sv.sival_ptr;

    printf("Thread notify\n");
    printf("\t\ttimeID[%d]\n", (int)*pTimerID);
    printf("\t\ttime_getoverrun[%d]\n", timer_getoverrun(*pTimerID));

    int ret = pthread_mutex_lock(&mtx);
    CHECK_THREAD_RET(ret, "pthread_mutex_t");

    expireCnt += 1 + timer_getoverrun(*pTimerID);

    ret = pthread_mutex_unlock(&mtx);
    CHECK_THREAD_RET(ret, "pthread_mutex_unlock");

    ret = pthread_cond_signal(&cond);
    CHECK_THREAD_RET(ret, "pthread_cond_signal");
}


int main(int argc, char* argv[])
{
    struct itimerspec ts;
    struct sigevent sev;
    timer_t timerID;
    
    if (argc < 5 || strcmp(argv[1], "--help")== 0)
    {
        CHECK_RET(-1, "Usage: %s secs nsecs int-secs int-usecs", argv[0]);
    }


    sev.sigev_notify = SIGEV_THREAD;
    sev.sigev_notify_function = threadFunc;
    sev.sigev_notify_attributes = NULL; //pthread_attr_t
    sev.sigev_value.sival_ptr = &timerID;

    ts.it_value.tv_sec = atoi(argv[1]);
    ts.it_value.tv_nsec = atoi(argv[2]);
    ts.it_interval.tv_sec = atoi(argv[3]);
    ts.it_interval.tv_nsec = atoi(argv[4]);

    int ret = timer_create(CLOCK_REALTIME, &sev, &timerID);
    CHECK_RET(ret, "timer_create");
    printf("timerID[%d]\n", (int)timerID);

    ret = timer_settime(timerID, 0, &ts, NULL);
    CHECK_RET(ret, "timer_settime");

    ret = pthread_mutex_lock(&mtx);
    CHECK_THREAD_RET(ret,"pthread_mutex_lock");

    while (1)
    {
        ret = pthread_cond_wait(&cond, &mtx);
        CHECK_THREAD_RET(ret, "pthread_cond_wait");

        printf("Main(): expireCnt[%d]\n", expireCnt);
    }
    
    ret = pthread_mutex_unlock(&mtx);
    CHECK_THREAD_RET(ret, "pthread_mutex_unlock");
    return 0;
}
