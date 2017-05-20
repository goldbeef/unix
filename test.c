/*************************************************************************
    > File Name: test.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年05月20日 星期六 10时13分21秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main()
{
#ifdef _GNU_SOURCE
    printf("fullPath[%d], shortPath[%s]\n", name, short_name);
#endif
    while (1)
    {
        sleep(5);
    }
    return 0;
}
