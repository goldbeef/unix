/*************************************************************************
    > File Name: catch_rtsig.h
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年06月21日 星期三 21时26分12秒
 ************************************************************************/

#include "all_def.h"

volatile int handlerSleepTime;
volatile int sigCnt = 0;
volatile int allDone = 0;

void siginfoHandler(int sig, siginfo_t* si, void* ucontext)
{
    if (sig == SIGINT || sig == SIGTERM)
    {
        allDone = 1;
        return;
    }

    sigCnt++;
    printf("catch signal[%d]\n", sig);
    printf("\t\t si_signo[%d], si_code[%d:%s],", si->si_signo, si->si_code,
             (si->si_signo == SI_USER) ? "SI_USER" :
            (si->si_signo == SI_QUEUE) ? "SI_QUEUE" : "OTHER"
          );
    printf(" si_val[%d]\n", si->si_value.sival_int);
    printf("\t\t si_pid[%d], si_uid[%d]\n", si->si_pid, si->si_uid);
    
    sleep(handlerSleepTime);
}

int main(int argc, char* argv[])
{
    int ret = 0;
    struct sigaction sa;
    int sig;
    sigset_t preMask, blockMask;

    if (argc > 1 && strcmp(argv[1], "--help") == 0)
    {
        printf("Usage: %s [block-time [handler-sleep-time]]\n", argv[0]);
        return 0;
    }

    handlerSleepTime = (argc > 2) ? atoi(argv[2]) : 1;
    
    sa.sa_sigaction = siginfoHandler;
    sa.sa_flags = SA_SIGINFO;

    for (sig = 1; sig < NSIG; sig++)
    {
        if (sig != SIGTSTP && sig != SIGQUIT)
            sigaction(sig, &sa, NULL);
    }

    if (argc > 1) 
    {
        sigfillset(&blockMask);
        sigdelset(&blockMask, SIGINT);
        sigdelset(&blockMask, SIGTERM);

        ret = sigprocmask(SIG_SETMASK, &blockMask, &preMask);
        CHECK_RET(ret, "sigprocmask error");

        printf("signal blocked, sleeping %s second\n", argv[1]);
        sleep(atoi(argv[1]));
        printf("sleep complete\n");

        ret = sigprocmask(SIG_SETMASK, &preMask, NULL);
        CHECK_RET(ret, "sigprocmask error");
    }

    while (!allDone)
        pause();
    
    return 0;
}
