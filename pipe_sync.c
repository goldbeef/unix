/*************************************************************************
    > File Name: pipc_sync.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月12日 星期六 08时36分05秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

int main(int argc, char* argv[])
{
    int pfd[2];
    int i, dummy;
    
    if (argc < 2 || strcmp(argv[1], "--help") == 0)
    {
        CHECK_RET(-1, "Usage: %s sleep-time1 ...", argv[0]);
    }

    setbuf(stdout, NULL);
    printf("parent started\n");

    int ret = pipe(pfd);
    CHECK_RET(ret, "pipe");

    for (i = 1; i < argc; i++)
    {
        ret = fork();
        CHECK_RET(ret, "fork");

        if (ret == 0)
        {
            //child-process
            close(pfd[0]);
            sleep(atoi(argv[i]));
            printf("child-process[%d] close pipe\n", getpid());
            _exit(0);
        }

        //parent-process
    }

    close(pfd[1]); //very important
    ret = read(pfd[0], &dummy, sizeof(dummy));
    CHECK_RET(ret, "read");
    if (ret == 0)
    {
        printf("parent-process read eof\n");
    }

    return 0;
}
