/*************************************************************************
    > File Name: orphaned_pgrp_sighup.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年07月16日 星期日 16时23分36秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

void sigHandler(int signo)
{
    printf("pid[%d], catch signal[%d:%s]\n", (int)getpid(), signo, strsignal(signo));
}

int main(int argc, char* argv[])
{
    int i;
    struct sigaction sa;
    
    if (argc < 2 || strcmp(argv[1], "--help") == 0)
    {
        CHECK_RET(-1, "Usage: %s {s|p} ...", argv[0]);
    }

    setbuf(stdout, NULL);

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = sigHandler;

    int ret = sigaction(SIGHUP, &sa, NULL);
    CHECK_RET(ret, "sigaction");
    
    ret = sigaction(SIGCONT, &sa, NULL);
    CHECK_RET(ret, "sigaction");

    printf("parent-process, pid[%d], ppid[%d], pgid[%d], sid[%d]\n", 
           (int)getpid(), (int)getppid(), (int)getpgrp(), (int)getsid(0));

    for (i = 1; i < argc; i++)
    {
        ret = fork();
        CHECK_RET(ret, "fork");

        if (ret == 0)
        {
            //child-process
            printf("child-process, pid[%d], ppid[%d], pgid[%d], sid[%d]\n",
                  (int)getpid(), (int)getppid(), (int)getpgrp(), (int)getsid(0));
            if (argv[i][0] == 's')
            {
                printf("pid[%d] stopping\n", (int)getpid());
                raise(SIGSTOP);
            }
            else
            {
                alarm(60);
                printf("pid[%d] pausing\n", (int)getpid());
                pause();
            }
            _exit(0);
        }
    }

    //parent-process
    sleep(3); // give child-process a chance to start 
    printf("parent-process exiting\n");
    
    exit(0); // and orphan them and their group
}
