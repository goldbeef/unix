/*************************************************************************
    > File Name: multi_sigchild.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年06月25日 星期日 10时54分50秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

volatile int numLiveChildProcess = 0;

void sigcildHandler(int sig)
{
    int status, savedErrno;
    pid_t childPid;

    savedErrno = errno;
    int ret;
    printf("catch signal[%d:%s]\n", sig, strsignal(sig));

    while ((childPid = waitpid(-1, &status, WNOHANG)) > 0)
    {
        printf("catch child-process, pid[%d]\n", childPid);
        printWaitStatus("\t\t", status);
        numLiveChildProcess--;
    }

    sleep(5);
    printf("sigcildHandler return\n");

    errno = savedErrno;
}

int main(int argc, char* argv[])
{
    int j, sigCnt;
    sigset_t blockMask, emptyMask;
    struct sigaction sa;

    if (argc < 2 || strcmp(argv[1], "--help") == 0)
    {
        CHECK_RET(-1, "Usage: %s time1 ...", argv[0]);
    }

    setbuf(stdout,  NULL);
    sigCnt = 0;
    numLiveChildProcess = argc - 1;

    //set signal-handler
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = sigcildHandler;
    int ret = sigaction(SIGCHLD, &sa, NULL);
    CHECK_RET(ret, "sigaction");

    //block signal 
    sigemptyset(&blockMask);
    sigaddset(&blockMask, SIGCHLD);
    ret = sigprocmask(SIG_SETMASK, &blockMask, NULL);
    CHECK_RET(ret, "sigprocmask");

    for (j = 0; j < argc; j++)
    {
        ret = fork();
        CHECK_RET(ret, "fork");

        if (ret == 0)
        {
            //child 
            sleep(atoi(argv[j]));
            _exit(0);
        }
    }

    //parent 
    sigemptyset(&emptyMask);
    while (numLiveChildProcess > 0)
    {
        sigsuspend(&emptyMask);
        sigCnt++;
    }

    printf("all child-process exit, sigNum[%d], SIGCHILD catch times[%d]", argc - 1, sigCnt);
    return 0;
}



