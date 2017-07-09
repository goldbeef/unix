/*************************************************************************
    > File Name: nanosleep.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年07月09日 星期日 11时32分24秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

void sigHandler(int signo)
{
    //printf("catch signal[%d:%s]\n", signo, strsignal(signo));
}

int main(int argc, char* argv[])
{
    struct timeval start, finish;
    struct timespec request, remain;
    struct sigaction sa;
    int ret;

    if (argc !=  3 || strcmp(argv[1], "--help") == 0)
    {
        CHECK_RET(-1, "Usage: %s secs nanosecs\n", argv[0]);
    }

    request.tv_sec = atoi(argv[1]);
    request.tv_nsec = atoi(argv[2]);

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = sigHandler;

    ret = sigaction(SIGINT, &sa, NULL);
    CHECK_RET(ret, "sigaction");

    ret = gettimeofday(&start, NULL);
    CHECK_RET(ret, "gettimeofday");

    while (1)
    {
        ret = nanosleep(&request, &remain);
        if (ret == -1 && errno != EINTR)
        {
            CHECK_RET(ret, "nanosleep, errno[%d:%s]", errno, strerror(errno));
        }

        if (ret == 0)
        {
            break;
        }

        ret = gettimeofday(&finish, NULL);
        CHECK_RET(ret, "gettimeofday");
        printf("Slept for: secs[%9.6f]\n", finish.tv_sec - start.tv_sec + 
                (finish.tv_usec - start.tv_usec)/1000000.0);
        
        
        printf("Remain: secs[%9.6f]\n", remain.tv_sec + remain.tv_nsec/100000000.0);
        
        request = remain;
    }

    printf("sleep complete\n");

    return 0;
}
