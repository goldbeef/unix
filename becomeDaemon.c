/*************************************************************************
    > File Name: daemon.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年07月23日 星期日 10时11分27秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

#define BD_NO_CHDIR 01
#define BD_NO_CLOSE_FILES 02
#define BD_NO_DUP_STD_FDS 04
#define BD_NO_UNMASK 010

#define BD_MAX_CLOSE 1024 


int becomeDaemon(int flags)
{
    int maxFd, fd;
    int ret;

    ret = fork();  //be background processs
    CHECK_RET(ret, "fork");
    if (ret > 0)
    {
        _exit(0);
    }

    ret = setsid(); // be leader of session
    CHECK_RET(ret, "setsid");

    ret = fork(); // ensure no a session leader 
    CHECK_RET(ret, "fork");
    if (ret > 0)
    {
        _exit(0);
    }

    if (!(flags & BD_NO_UNMASK))
    {
        //clear file creation mask
        umask(0);
    }

    if (!(flags & BD_NO_CHDIR))
    {
        //cd 
        chdir("/");
    }

    if (!(flags & BD_NO_CLOSE_FILES))
    {
        //close filefd
        maxFd = sysconf(_SC_OPEN_MAX);
        if (maxFd == -1)
        {
            maxFd = BD_MAX_CLOSE;
        }

        for (fd = 0; fd < maxFd; fd++)
        {
            close(fd);
        }
    }

    if (!(flags & BD_NO_DUP_STD_FDS))
    {
        //dup stdfileno to /dev/null 
        close(STDIN_FILENO);

        fd = open("/dev/null", O_RDWR);
        CHECK_RET(ret, "open");

        if (dup2(STDIN_FILENO, STDOUT_FILENO) != STDOUT_FILENO)
        {
            CHECK_RET(-1, "dup2");
        }

        if (dup2(STDIN_FILENO, STDERR_FILENO) != STDERR_FILENO)
        {
            CHECK_RET(-1, "dup2");
        }
    }

    return 0;
}

volatile sig_atomic_t hupReceived = 0;

void sighupHandler(int signo)
{
    hupReceived = 1;
}

int main(int argc, char* argv[])
{
    int ret;

    ret = becomeDaemon(0);
    CHECK_RET(ret, "daemon");

    struct sigaction sa;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = sighupHandler;

    ret = sigaction(SIGHUP, &sa, NULL);
    CHECK_RET(ret, "sigaction");

    while (1)
    {
        sleep(2);
        if (hupReceived)
        {
            printf("logOpen\n");
            printf("readConfig\n");

            hupReceived = 0;
        }
    }

    return 0;
}
