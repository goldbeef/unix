/*************************************************************************
    > File Name: ptmr_sigev_signal.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年07月09日 星期日 16时21分20秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

#define TIMER_SIG SIGRTMAX

void sigHandler(int signo, siginfo_t* si, void* uc)
{
    timer_t* pTimer;
    pTimer = si->si_value.sival_ptr;

    printf("Got signal[%d:%s]\n", signo, strsignal(signo));
    printf("\t\ttimerID[%d]\n", (int)*pTimer);
    printf("\t\ttimer_getoverrun[%d]\n", timer_getoverrun(*pTimer));
    printf("\t\ttsi_overrun[%d]\n", si->si_overrun);
}


int main(int argc, char* argv[])
{
    struct itimerspec ts;
    struct sigaction sa;
    struct sigevent sev;
    
    timer_t timerID;
    
    if (argc < 5 || strcmp(argv[1], "--help")== 0)
    {
        CHECK_RET(-1, "Usage: %s secs nsecs int-secs int-usecs", argv[0]);
    }

    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = sigHandler;
    sigemptyset(&sa.sa_mask);
    int ret = sigaction(TIMER_SIG, &sa, NULL);
    CHECK_RET(ret, "sigaction");

    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = TIMER_SIG;
    sev.sigev_value.sival_ptr = &timerID;

    ts.it_value.tv_sec = atoi(argv[1]);
    ts.it_value.tv_nsec = atoi(argv[2]);
    ts.it_interval.tv_sec = atoi(argv[3]);
    ts.it_interval.tv_nsec = atoi(argv[4]);

    ret = timer_create(CLOCK_REALTIME, &sev, &timerID);
    CHECK_RET(ret, "timer_create");
    printf("timerID[%d]\n", (int)timerID);

    ret = timer_settime(timerID, 0, &ts, NULL);
    CHECK_RET(ret, "timer_settime");

    while (1)
    {
        pause();
    }
    return 0;
}
