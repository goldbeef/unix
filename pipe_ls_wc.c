/*************************************************************************
    > File Name: pipe_ls_wc.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月12日 星期六 08时59分44秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

int main(int argc, char* argv[])
{
    int pfd[2];

    int ret = pipe(pfd);
    CHECK_RET(ret, "pipe");

    ret = fork();
    CHECK_RET(ret, "fork");
    if (ret == 0)
    {
        //first child-process to run "ls"
        close(pfd[0]);
        if (pfd[1] != STDOUT_FILENO)
        {
            ret = dup2(pfd[1], STDOUT_FILENO);
            CHECK_RET(ret, "dup2");
            close(pfd[1]);
        }

        execlp("ls", "ls", NULL);
        _exit(0);
    }
    
    //parent-process
    ret = fork();
    if (ret == 0)
    {
        //second child-process to run "wc -l"
        close(pfd[1]);
        if (pfd[0] != STDIN_FILENO)
        {
            ret = dup2(pfd[0], STDIN_FILENO);
            CHECK_RET(ret, "dup2");
        }

        execlp("wc", "wc", "-l", NULL);
        _exit(0);
    }

    close(pfd[0]);
    close(pfd[1]);

    wait(NULL);
    wait(NULL);
    return 0;
}
