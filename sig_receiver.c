/*************************************************************************
    > File Name: sig_receiver.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年06月19日 星期一 22时45分05秒
 ************************************************************************/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#include "signal_function.c"

static int sigCnt[NSIG];
static volatile sig_atomic_t gotSigint = 0;

void sigHandler(int sig)
{
    if (sig == SIGINT)
    {
        gotSigint = 1;
    }
    else
    {
        sigCnt[sig]++;
    }
}


int main(int argc, char* argv[])
{
    int n, numSecs;
    sigset_t pendingSet, blockSet, emptySet;
    
    for (n = 0; n < NSIG; n++)
    {
        signal(n, sigHandler);
    }

    if (argc > 0)
    {
        numSecs = atoi(argv[1]);

        sigfillset(&blockSet);
        if (sigprocmask(SIG_SETMASK, &blockSet, NULL) < 0)
        {
            printf("sigprocmask error\n");
            return -1;
        }

        sleep(numSecs);

        if (sigpending(&pendingSet) < 0)
        {
            printf("sigpending error\n");
            return -1;
        }

        printf("pending signals\n");
        printSigset(stdout, "\t\t", &pendingSet);

        sigemptyset(&emptySet);
        if (sigprocmask(SIG_SETMASK, &emptySet, NULL) < 0)
        {
            printf("sigprocmask error\n");
            return -1;
        }

    }


    while (!gotSigint)
    {
        continue;
    }


    for (n = 0; n < NSIG; n++)
    {
        if (sigCnt[n] != 0)
        {
            printf("signal[%d] caught time[%d]\n", n, sigCnt[n]);
        }
    }

    return 0;

}
