/*************************************************************************
    > File Name: fork_file_sharing.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年06月24日 星期六 15时54分20秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

int main()
{
    int fd, flags;
    char template[] = "/tmp/testXXXXXX";
    setbuf(stdout, NULL);

    fd = mkstemp(template);
    CHECK_RET(fd, "mkstemp");

    flags = fcntl(fd, F_GETFL);
    CHECK_RET(flags, "fcntl");
    printf("O_APPEND flag before fork is: %s\n", (flags & O_APPEND) ? "on" : "off");

    int ret = fork();
    CHECK_RET(ret, "fork");
    
    if (ret == 0)
    {
        //child process
        ret = lseek(fd, 1000, SEEK_SET);
        CHECK_RET(ret, "child: lseek");

        flags = fcntl(fd, F_GETFL);
        CHECK_RET(ret, "fcntl");

        flags |= O_APPEND;
        ret = fcntl(fd, F_SETFL, flags);
        CHECK_RET(ret, "fcntl");

        _exit(0);
    }
    
    //parent
    ret = wait(NULL);
    CHECK_RET(ret, "wait");

    printf("file offset is %lld\n", (long long) lseek(fd, 0, SEEK_CUR));

    flags = fcntl(fd, F_GETFL);
    CHECK_RET(flags, "fcntl");
    printf("O_APPEND flag in parent is: %s\n", (flags & O_APPEND) ? "on" : "off");
    
    return 0;
}
