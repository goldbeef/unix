/*************************************************************************
    > File Name: sigsuspend.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年06月22日 星期四 08时15分29秒
 ************************************************************************/

#include "all_def.h"

volatile sig_atomic_t gotSigquit = 0;

void sigHandler(int sig)
{
    printf("catch signal[%d:%s]\n", sig, strsignal(sig));
    if (sig == SIGQUIT)
    {
        gotSigquit = 1;
    }
}


int main(int argc, char* argv[])
{
    int loopNum;
    time_t startTime;
    sigset_t origMask, blockMask;
    struct sigaction sa;

    printSigMask(stdout, "origMask is :\n");

    sigemptyset(&blockMask);
    sigaddset(&blockMask, SIGINT);
    sigaddset(&blockMask, SIGQUIT);

    int ret = 0;
    ret = sigprocmask(SIG_BLOCK, &blockMask, &origMask);
    CHECK_RET(ret, "sigprocmask error");

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = sigHandler;

    ret = sigaction(SIGINT, &sa, NULL);
    CHECK_RET(ret, "sigaction");
    ret = sigaction(SIGQUIT, &sa, NULL);
    CHECK_RET(ret, "sigaction");

    for (loopNum = 1; !gotSigquit; loopNum++)
    {
        printf("====LOOP %d\n", loopNum);
        printSigMask(stdout, "start critical section, signal mask is:\n");
        
        for (startTime = time(NULL); time(NULL) < startTime + 4;)
            continue;

        printPendingSig(stdout, "Before sigsuspend --- pending signal:\n");

        sigsuspend(&origMask);
    }

    ret = sigprocmask(SIG_SETMASK, &origMask, NULL);
    CHECK_RET(ret, "sigprocmask error");

    return 0;
}
