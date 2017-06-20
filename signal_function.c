/*************************************************************************
    > File Name: signal_function.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年06月18日 星期日 21时14分05秒
 ************************************************************************/

#include <stdio.h>
#include <signal.h>
#include <string.h>

void printSigset(FILE* of, const char* prefix, const sigset_t* sigset)
{
    int sig, cnt;

    cnt = 0;
    for (sig = 1; sig < NSIG; sig++)
    {
        if (sigismember(sigset, sig))
        {
            cnt++;
            fprintf(of, "%s%d(%s)\n", prefix, sig, strsignal(sig));
        }
    }
    
    if (cnt == 0)
    {
        fprintf(of, "%s<empty signal set>\n", prefix);
    }
}

int printSigMask(FILE* of, const char* msg)
{
    sigset_t curMask;
    if (msg != NULL)
    {
        fprintf(of, "%s", msg);
    }

    if (sigprocmask(SIG_BLOCK, NULL, &curMask) < 0)
    {
        printf("sigprocmask error\n");
        return -1;
    }
    
    printSigset(of, "\t\t", &curMask);
}

int printPendingSig(FILE* of, const char* msg)
{
    sigset_t pendingSig;
    if (msg != NULL)
    {
        fprintf(of, "%s", msg);
    }

    if (sigpending(&pendingSig)  < 0)
    {
        printf("sigprocmask error");
        return -1;
    }

    printSigset(of, "\t\t", &pendingSig);
    return 0;
}

/*
int main()
{
    printSigMask(stdout, "sigBlk");
    printPendingSig(stdout, "sigPending");
    return 0;
}*/
