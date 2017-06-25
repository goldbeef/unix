/*************************************************************************
    > File Name: closeonexec.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年06月25日 星期日 15时52分47秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

int main(int argc, char* argv[])
{
    int flags;

    if (argc > 1)
    {
        flags = fcntl(STDOUT_FILENO, F_GETFD);
        CHECK_RET(flags, "fcntl");

        flags |= FD_CLOEXEC;
        int ret = fcntl(STDOUT_FILENO, F_SETFD, flags);
        CHECK_RET(flags, "fcntl");
    }

    execlp("ls", "ls", "-l", argv[0], NULL);
    return 0;
}
