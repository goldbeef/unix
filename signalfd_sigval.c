/*************************************************************************
    > File Name: signalfd_sigval.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年06月22日 星期四 20时06分30秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

int main(int argc, char* argv[])
{
    sigset_t mask;
    int sfd, j;
    struct signalfd_siginfo fdSi;
    ssize_t s;

    if (argc < 2 || strcmp(argv[1], "--help") == 0)
    {
        CHECK_RET(-1, "Usage: %s sig1 ...\n", argv[0]);
    }

    sigemptyset(&mask);
    for (j = 0; j < argc; j++)
    {
        sigaddset(&mask, atoi(argv[j]));
    }

    int ret = sigprocmask(SIG_SETMASK, &mask, NULL);
    CHECK_RET(ret, "sigprocmask error");

    sfd = signalfd(-1, &mask, 0);
    CHECK_RET(sfd, "signalfd error");
    
    while (1)
    {
        s = read(sfd, &fdSi, sizeof(struct signalfd_siginfo));
        if (s != sizeof(struct signalfd_siginfo))
        {
            CHECK_RET(-1, "read size error");
        }

        printf("catch signal[%d:%s]\n", fdSi.ssi_signo, strsignal(fdSi.ssi_signo));
    }

    return 0;
}
