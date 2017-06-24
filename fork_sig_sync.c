/*************************************************************************
    > File Name: fork_sig_sync.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年06月24日 星期六 16时42分19秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"


void sigHandler(int sig)
{
    printf("sigHandler\n");
}


int main()
{
    pid_t childPid;
    sigset_t blockMask, origMask, emptyMask;

    struct sigaction sa;

    setbuf(stdout, NULL);

    sigemptyset(&blockMask);
    sigaddset(&blockMask, SIGUSR1);
    int ret = sigprocmask(SIG_BLOCK, &blockMask, &origMask);
    CHECK_RET(ret, "sigprocmask");

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = sigHandler;
    ret = sigaction(SIGUSR1, &sa, NULL);
    CHECK_RET(ret, "sigaction");

    childPid = fork();
    CHECK_RET(childPid, "fork");

    if (childPid == 0)
    {
        //child process
        printf("child processs start\n");
        //do sth

        ret = kill(getppid(), SIGUSR1);
        CHECK_RET(ret, "kill");

        _exit(0);
    }

    //parent process 
    printf("parent procese wait for child process\n");
    sigemptyset(&emptyMask);
    sigsuspend(&emptyMask);

    printf("parent process catch signal, continue\n");
    ret = sigprocmask(SIG_SETMASK, &origMask, NULL);
    CHECK_RET(ret, "sigprocmask");

    return 0;
}
