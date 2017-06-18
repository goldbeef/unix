/*************************************************************************
    > File Name: sigaltstack.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年06月17日 星期六 10时39分45秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

void sigsegHandler(int sig)
{
    int x;
    printf("caught signal %d(%s)\n", sig, strsignal(sig));
    printf("top of handler statck near, %p\n", &x);
    fflush(NULL);
    _exit(-1);
}


void overflowStack(int callNum)
{
    char  buff[102400];
    printf("call %d --- top of statck near %p\n", callNum, &buff[0]);
    overflowStack(callNum + 1);
}

int main()
{
    stack_t sigstack;
    struct sigaction sa;
    int j;

    printf("top of standard stack is near %p\n", &j);
    printf("SIGSTKSZ[%d]\n", SIGSTKSZ);

    sigstack.ss_sp = malloc(SIGSTKSZ);
    sigstack.ss_flags = 0;
    sigstack.ss_size = SIGSTKSZ;

    if (sigaltstack(&sigstack, NULL) < 0)
    {
        printf("sigaltstack error\n");
        return -1;
    }
    printf("alternate statck si at %p - %p\n", sigstack.ss_sp, sbrk(0));

    sa.sa_handler = sigsegHandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_ONSTACK;
    //sa.sa_flags = 0;

    if (sigaction(SIGSEGV, &sa, NULL) < 0)
    {
        printf("sigaction error\n");
        return -1;
    }

    overflowStack(1);

    return 0;
}
