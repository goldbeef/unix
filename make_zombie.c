/*************************************************************************
    > File Name: make_zombie.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年06月25日 星期日 09时46分46秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

int main(int argc, char* argv[])
{
    pid_t childPid;
    
    setbuf(stdout, NULL);
    
    int ret = fork();
    CHECK_RET(ret, "fork");

    if (ret == 0)
    {
        //child-process
        printf("child-process exit, pid[%d]\n", getpid());
        _exit(0);
    }

    //parent-process
    sleep(3);
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "ps axj|grep %s|grep -v grep", basename(argv[0]));

    system(cmd);

    //send sigkill to the zombie 
    childPid = ret;
    ret = kill(childPid, SIGKILL);
    CHECK_RET(ret, "kill");

    sleep(3);
    printf("after sneding SIGKILL to zombie");

    system(cmd);

    return 0;
}
