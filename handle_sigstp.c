/*************************************************************************
    > File Name: handle_sigstp.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年07月15日 星期六 14时47分18秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

void sigTstpHandler(int signo)
{
    sigset_t tstpMask, preMask;
    int saveErrno;
    struct sigaction  sa;

    saveErrno = errno;
    printf("catch signal[%d:%s]\n", signo, strsignal(signo));

    //set handler to def
    if (signal(SIGTSTP, SIG_DFL) == SIG_ERR)
    {
        CHECK_RET_VOID(-1, "signal");
    }

    //generate a signal 
    raise(SIGTSTP);

    //unblock SIGTSTP; the pending SIGTSTP suspend the process
    sigemptyset(&tstpMask);
    sigaddset(&tstpMask, SIGTSTP);
    int ret = sigprocmask(SIG_UNBLOCK, &tstpMask, &preMask);
    CHECK_RET_VOID(ret, "sigprocmask");

    //execution resumes here after SIGCONT, block SIGTSTP again
    ret = sigprocmask(SIG_SETMASK, &preMask, NULL);
    CHECK_RET_VOID(ret, "sigprocmask");

    //reestablish handler 
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = sigTstpHandler;
    ret = sigaction(SIGTSTP, &sa, NULL);
    CHECK_RET_VOID(ret, "sigaction");

    printf("Exit sigTstpHandler\n");
    errno = saveErrno;
}

int main(int argc, char* argv[])
{
    struct sigaction sa;
    int ret;

    ret = sigaction(SIGTSTP, NULL, &sa);
    CHECK_RET(ret, "sigaction");

    if (sa.sa_handler != SIG_IGN)
    {
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = SA_RESTART;
        sa.sa_handler = sigTstpHandler;

        ret = sigaction(SIGTSTP, &sa, NULL);
        CHECK_RET(ret, "sigaction");
    }
    
    while (1)
    {
        pause();
        printf("Main\n");
    }

    return 0;
}

