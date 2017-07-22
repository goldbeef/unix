/*************************************************************************
    > File Name: job_mon.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年07月15日 星期六 11时37分59秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

int cmdNum;

void sigHandler(int signo)
{
    if (getpid() == getpgrp())
    {
        //process-group leader
        fprintf(stderr, "Terminal FG process-group[%d]\n", tcgetpgrp(STDERR_FILENO));
    }

    fprintf(stderr, "Process[%d](%d) receive signal[%d:%s]\n", 
            (int)getpid(), cmdNum, signo, strsignal(signo));
    
    //if catch SIGSTP, then raise SITSTOP to stop process 
    if (signo == SIGTSTP)
    {
        raise(SIGSTOP);
    }
}

int main(int argc, char* argv)
{
    struct sigaction sa;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = sigHandler;

    int ret;
    ret = sigaction(SIGINT, &sa, NULL);
    CHECK_RET(ret, "sigaction");
    ret = sigaction(SIGTSTP, &sa, NULL);
    CHECK_RET(ret, "sigaction");
    ret = sigaction(SIGCONT, &sa, NULL);
    CHECK_RET(ret, "sigaction");

    if (isatty(STDIN_FILENO))
    {
        //first process 
        fprintf(stderr, "Terminal FG process-group[%d]\n", tcgetpgrp(STDERR_FILENO));
        fprintf(stderr, "Command\tpid\tppid\tpgrp\tsid\n");
    }
    else
    {
        ret = read(STDIN_FILENO, &cmdNum, sizeof(cmdNum));
        CHECK_RET(ret, "read");
    }
    cmdNum++;

    fprintf(stderr, "%d\t%d\t%d\t%d\t%d\n", 
           cmdNum, (int)getpid(), (int)getppid(), (int)getpgrp(), (int)getsid(0));
    if (!isatty(STDOUT_FILENO))
    {
        //if not, then pipe
        ret = write(STDOUT_FILENO, &cmdNum, sizeof(cmdNum));
    }

    while (1)
    {
        pause();
    }

    return 0;
}

