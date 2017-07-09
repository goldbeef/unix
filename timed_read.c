/*************************************************************************
    > File Name: timed_read.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年07月09日 星期日 10时54分38秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

#define BUFF_SIZE 100

void sigHandler(int signo)
{
    printf("catch signal[%d:%s]\n", signo, strsignal(signo));
}

int main(int argc, char* argv[])
{
    struct sigaction sa;
    char buff[BUFF_SIZE];
    ssize_t numRead;
    int savedErrno;

    if (argc > 1 && strcmp(argv[1], "--help") == 0)
    {
        CHECK_RET(-1, "Usage: %s [ num-secs [restart-flag]]", argv[0]);
    }

    sa.sa_flags = (argc > 2) ? SA_RESTART : 0;
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = sigHandler;

    int ret = sigaction(SIGALRM, &sa, NULL);
    CHECK_RET(ret, "sigaction");

    int timeSecs = (argc > 1) ? atoi(argv[1]) : 5;
    alarm(timeSecs);

    numRead = read(STDIN_FILENO, buff, BUFF_SIZE - 1);
    savedErrno = errno; //in case alarm change it
    alarm(0); // ensure timer is turned off
    errno = savedErrno;

    if (numRead == -1)
    {
        if (errno == EINTR)
        {
            printf("Read time out\n");
        }
        else
        {
            printf("Other error[%d:%s]\n", errno, strerror(errno));
        }
        exit(0);
    }

    printf("Successful read byte(%d), msg[%s]\n", numRead, buff);
    exit(0);
}
