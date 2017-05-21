/*************************************************************************
    > File Name: alloca.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年05月21日 星期日 10时52分49秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>

void* fun(void* ptr)
{
    return ptr;
}

int main()
{
    /*
    char tmp;
    tmp = 1;
    char* buff = alloca(100);
    */
    
    /*
    char* buff = (char*) malloc(200);
    buff[0] = 0;
    */

    char* ptr = fun(alloca(1000));
    int i;
    for (i = 0; i < 1000; i++)
    {
        ptr[i] = 0xff;
    }
    return 0;
}
