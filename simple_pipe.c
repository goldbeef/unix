/*************************************************************************
    > File Name: simple_pipe.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月06日 星期日 12时20分07秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

#define BUF_SIZE 10

int main(int argc, char* argv[])
{
    int fds[2];
    char buf[BUF_SIZE];
    int numRead;

    if (argc != 2 || strcmp(argv[1], "--help") == 0)
    {
        CHECK_RET(-1, "Usage: %s stringContent", argv[0]);
    }
    
    int ret = pipe(fds);
    CHECK_RET(ret, "pipe");
    
    ret = fork();
    CHECK_RET(ret, "fork");

    if (ret == 0)
    {
        //child-process
        close(fds[1]);

        while (1)
        {
            numRead = read(fds[0], buf, BUF_SIZE);
            CHECK_RET(numRead, "read");

            if (numRead == 0)
            {
                break;
            }

            ret = write(STDOUT_FILENO, buf, BUF_SIZE);
            CHECK_RET(ret, "write");
        }
        write(STDOUT_FILENO, "\n", 1);
        close(fds[0]);

        _exit(0);
    }

    close(fds[0]);
    ret = write(fds[1], argv[1], strlen(argv[1]));
    CHECK_RET(ret, "write");

    close(fds[1]);
    wait(NULL);
    return 0;
}
