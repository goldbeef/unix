/*************************************************************************
    > File Name: print_wait_status.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年06月25日 星期日 08时48分12秒
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void printWaitStatus(const char* msg, int status)
{
    if (msg != NULL)
    {
        printf("%s, ", msg);
    }

    if (WIFEXITED(status))
    {
        printf("child exited, status[%d]\n", WEXITSTATUS(status));
    }
    else if (WIFSIGNALED(status))
    {
        printf("child killed by signal[%d:%s] ", WTERMSIG(status), strsignal(WTERMSIG(status)));
        if (WCOREDUMP(status))
        {
            printf("(core dumped)");
        }
        printf("\n");
    }
    else if (WIFSTOPPED(status))
    {
        printf("child stopped by signal[%d:%s]\n", WSTOPSIG(status), strsignal(WSTOPSIG(status)));
    }
    else if (WIFCONTINUED(status))
    {
        printf("child continue\n");
    }
    else
    {
        printf("impossible !!!!\n");
    }
}
