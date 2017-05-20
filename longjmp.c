/*************************************************************************
    > File Name: longjmp.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年05月20日 星期六 11时37分41秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

static jmp_buf env;

static void doJump(int var1, int var2, int var3)
{
    printf("doJump, var1[%d], var2[%d], var3[%d]\n", var1, var2, var3);
    longjmp(env,1);
}

int main()
{
    int var1;
    register int var2;
    volatile int var3;

    var1 = 111;
    var2 = 222;
    var3 = 333;

    if (setjmp(env) == 0)
    {
        var1 = 444;
        var2 = 555;
        var3 = 666;
        doJump(var1, var2, var3);
    }
    else
    {
        printf("After Jump, var1[%d], var2[%d], var3[%d]\n", var1, var2, var3);
    }

    return 0;

}

