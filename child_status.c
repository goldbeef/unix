/*************************************************************************
    > File Name: child_status.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年06月25日 星期日 09时00分21秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

int main(int argc, char* argv[])
{
    int status;
    pid_t childPid;

    if (argc > 1 && strcmp(argv[1], "--help") == 0)
    {
        CHECK_RET(-1, "Usage: %s [exit-status]\n", argv[0]);
    }

    int ret = fork();
    CHECK_RET(ret, "fork");

    if (ret == 0)
    {
        //child-process
        printf("child started with pid[%d]\n", getpid());

        if (argc > 1)
        {
            exit(atoi(argv[1]));
        }

        while (1)
        {
            pause();
        }

        exit(0);
    }

    //parent-process
    
    while (1)
    {
        childPid = waitpid(-1, &status, WUNTRACED|WCONTINUED);

        if (childPid == -1)
        {
            exit(0);
        }

        printf("catch child-process, pid[%d]\n", getpid());
        printWaitStatus("hello", status);
    }

    return 0;
}
