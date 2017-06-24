/*************************************************************************
    > File Name: exit_handler.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年06月24日 星期六 20时09分48秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"


void atexitFunc1(void)
{
    printf("atexitFunc1\n");
}

void atexitFunc2(void)
{
    printf("atexitFunc2\n");
}

void onatexitFunc1(int status, void* arg)
{
    printf("onatexitFunc1, status[%d], arg[%p]\n", status, arg);
}

int main()
{
    int ret;
    ret = on_exit(onatexitFunc1, (void*) 10);
    CHECK_RET(ret, "on_exit");

    atexit(atexitFunc1);
    CHECK_RET(ret, "atexitFunc1");

    atexit(atexitFunc2);
    CHECK_RET(ret, "atexitFunc2");

    ret = on_exit(onatexitFunc1, (void*) 20);
    CHECK_RET(ret, "on_exit");
    exit(0);
}
