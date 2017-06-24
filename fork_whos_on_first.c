/*************************************************************************
    > File Name: fork_whos_on_first.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年06月24日 星期六 16时38分23秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

int main()
{
    int ret = fork();
    CHECK_RET(ret, "fork");

    setbuf(stdout, NULL);
    if (ret == 0)
    {
        printf("child-process\n");
        _exit(0);
    }

    printf("parent-process\n");
    return 0;
}
