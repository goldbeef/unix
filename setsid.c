/*************************************************************************
    > File Name: setsid.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年07月12日 星期三 21时17分11秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

int main(int argc, char* argv[])
{
    int ret;
    ret = fork();
    if (ret != 0)
    {
        //parent process 
        _exit(0);
    }

    //child process
    ret = setsid();
    CHECK_RET(ret, "setsid");

    printf("pid[%d], pgid[%d], sid[%d]\n",  getpid(), getpgrp(), getsid(0));
    ret = open("/dev/tty", O_RDWR);
    CHECK_RET(ret, "open");
    
    return 0;
}

