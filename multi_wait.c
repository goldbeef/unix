/*************************************************************************
    > File Name: multi_wait.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年06月24日 星期六 20时48分50秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

int main(int argc, char* argv[])
{
    int numDead, ret;
    pid_t childPid;
    int j;

    if (argc  < 2 || strcmp(argv[1], "--help") == 0)
    {
        CHECK_RET(-1, "Usage: %s sleep-time1 ...", argv[0]);
    }

    setbuf(stdout, NULL);
    for (j = 1; j < argc; j++)
    {
        ret = fork();
        CHECK_RET(ret, "fork");

        if (ret == 0)
        {
            //child-process
            printf("child-process, pid[%d], sleep-time[%d]\n", getpid(), atoi(argv[j]));
            sleep(atoi(argv[1]));
            _exit(0);
        }
    }

    numDead = 0;
    while (1)
    {
        childPid = wait(NULL);
        if (childPid == -1)
        {
            if (errno = ECHILD)
            {
                printf("no-more childPid\n");
                exit(0);
            }
            else
            {
                exit(-1);
            }
        }

        numDead++;
        printf("wait return, pid[%d], numDead[%d]\n", childPid, numDead);
    }

    return 0;
}

