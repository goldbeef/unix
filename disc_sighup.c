/*************************************************************************
    > File Name: disc_sighup.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年07月15日 星期六 10时08分33秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

void sigHandler(int signo)
{
    printf("catch signal[%d:%s]\n", signo, strsignal(signo));
}

int main(int argc, char* argv[])
{
    pid_t pid;
    int i;
    struct sigaction sa;
    int ret;

    if (argc < 2 || strcmp(argv[1], "--help") == 0)
    {
        CHECK_RET(-1, "Usage: %s param1 ...", argv[0]);
    }

    setbuf(stdout, NULL);
    printf("main-process's parent-pid[%d], foregroud process-group[%d], argc[%d]\n", 
           (int)getppid(), (int)tcgetpgrp(STDIN_FILENO), argc);

    for (i = 1; i < argc; i++)
    {
        pid = fork();
        CHECK_RET(pid, "fork");

        if (pid == 0)
        {
            //child-process
            if (argv[i][0] == 'd')
            {
                ret = setpgid(0, 0);
                CHECK_RET(ret, "getppid");

                sigemptyset(&sa.sa_mask);
                sa.sa_flags = 0;
                sa.sa_handler = sigHandler;

                ret = sigaction(SIGHUP, &sa, NULL);
                CHECK_RET(ret, "sigaction");
                break; //important
            }
        }

        //parent-process
    }
    
    //both child-process and parent-process
    alarm(10);

    printf("pid[%d], ppid[%d], pgid[%d]\n", (int)getpid(), (int)getppid(), (int)getpgrp());
    while (1)
    {
        pause();
    }

    return 0;
}
