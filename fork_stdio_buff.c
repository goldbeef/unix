/*************************************************************************
    > File Name: fork_stdio_buff.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年06月24日 星期六 20时15分52秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

#define STRINGS "write system-call\n"

int main()
{
    printf("hello world\n");

    write(STDOUT_FILENO, STRINGS, strlen(STRINGS));

    int ret = fork();
    CHECK_RET(ret, "fork");

    //both parent-process and child-process come here
    exit(0);
}
