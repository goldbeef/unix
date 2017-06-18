/*************************************************************************
    > File Name: ouch.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年06月11日 星期日 23时06分30秒
 ************************************************************************/

#include <stdio.h>
#include <signal.h>

void signalHandler(int signo)
{
    static int count = 0;
    printf("ouch, count[%d]\n", count);
    count++;
}

int main()
{
    if (signal(SIGINT, signalHandler) == SIG_ERR)
    {
        printf("signal error\n");
        return -1;
    }

    while (1)
    {
        sleep(3);
    }
    return 0;
}
