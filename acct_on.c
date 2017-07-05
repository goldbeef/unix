/*************************************************************************
    > File Name: acct_on.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年06月26日 星期一 22时41分17秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

int main(int argc, char* argv[])
{
    if (argc > 2 || (argc > 2 && strcmp(argv[1], "--help") == 0))
    {
        CHECK_RET(-1, "%s [file]\n", argv[0]);
    }

    int ret = acct(argv[1]);
    CHECK_RET(ret, "acc");

    return 0;
}
