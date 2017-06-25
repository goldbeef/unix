/*************************************************************************
    > File Name: execv.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年06月25日 星期日 15时30分04秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

int main(int arg, char* argv[])
{
    char* argVec[10] = {"arg1", "arg2", NULL};
    char* envVec[ ] = {"key1=value1", "key2=val2", NULL};
    
    execve(argv[1], argVec, envVec);
    CHECK_RET(-1, "execv");

    return 0;
}

