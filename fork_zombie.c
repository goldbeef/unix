/*************************************************************************
    > File Name: fork.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年06月25日 星期日 10时37分33秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

int main(void)
{
    int ret = fork();
    CHECK_RET(ret, "fork");

    if (ret == 0)
    {
        _exit(0);
    }

    //parent-process
    while (1)
    {
        pause();
    }
    
    return 0;
}
