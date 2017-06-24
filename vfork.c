/*************************************************************************
    > File Name: vfork.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年06月24日 星期六 16时29分50秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

int main()
{
    int istatck = 222;
    int ret = vfork();
    CHECK_RET(ret, "vfork");

    if (ret == 0)
    {
        sleep(3);
        printf("child-process running\n");
        istatck *= 3;
        _exit(0);
        //return 0;//cause strange problemmm
    }

    printf("parent-process running\n");
    printf("istatck = %d\n", istatck);
    return 0;
}
