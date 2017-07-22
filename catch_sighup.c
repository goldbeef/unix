/*************************************************************************
    > File Name: catch_sighup.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年07月15日 星期六 09时32分47秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

void sigHandle(int signo)
{

}

int main(int argc, char* argv[])
{
    pid_t childPid;
    struct sigaction sa;

    setbuf(stdout, NULL);
    
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = sigHandle;
    
    int ret = sigaction(SIGHUP, &sa, NULL);
    CHECK_RET(ret, "sigaction");

    childPid = fork();
    CHECK_RET(childPid, "fork");

    if (childPid == 0 && argc  > 1)
    {
        //child-process
        ret = setpgid(0, 0);
        CHECK_RET(ret, "child-process, setpgid");
    }

    //both child-process and parent-process
    printf("pid[%d], ppid[%d], pgid[%d], sid[%d]\n", 
           (int)getpid(), (int)getppid(), (int)getpgrp(), (int)getsid(0));
    
    while (1)
    {
        pause();
        printf("%d: catch SIGHUP\n", (int)getpid());
    }

    return 0;
}
