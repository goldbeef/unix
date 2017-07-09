/*************************************************************************
    > File Name: alarm.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年07月09日 星期日 10时31分42秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

void sigHandler(int signo)
{
    printf("catch signal[%d:%s]\n", signo, strsignal(signo));
}

int main(int argc, char* argv[])
{
    if (argc < 2 || strcmp(argv[1], "--help") == 0)
    {
        CHECK_RET(-1, "Usage: %s time-sec", argv[0]);
    }

    signal(SIGALRM, sigHandler);

    int timeouts = atoi(argv[1]);
    alarm(timeouts);
    
    pause();
    return 0;
}
