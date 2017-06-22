/*************************************************************************
    > File Name: sigwaitinfo.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年06月22日 星期四 19时30分50秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

int main(int argc, char* argv[])
{
    int sig;
    siginfo_t si;
    sigset_t allSig;

    if (argc > 1 && strcmp(argv[1], "--help") == 0)
    {
        printf("Usage: %s [delay-secs]\n", argv[0]);
        return 0;
    }

    sigfillset(&allSig);
    
    int ret = sigprocmask(SIG_SETMASK, &allSig, NULL);
    CHECK_RET(ret, "sigprocmask error");

    if (argc > 1)
    {
        printf("begin to delay %d seconds\n", atoi(argv[1]));
        sleep(atoi(argv[1]));
    }

    while (1)
    {
        sig = sigwaitinfo(&allSig, &si);
        CHECK_RET(sig, "sigwaitinfo error");
        
        if (sig == SIGINT || sig == SIGTERM)
        {
            return 0;
        }

        printf("catch sig[%d:%s]\n", sig, strsignal(sig));
        printf("\t\t si_signo[%d], si_code[%d], si_value[%d]\n", si.si_signo, si.si_code, si.si_value.sival_int);
    }

    return 0;
}
