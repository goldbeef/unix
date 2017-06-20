/*************************************************************************
    > File Name: sig_longjmp.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年06月20日 星期二 19时59分24秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include <signal.h>

#include "signal_function.c"

volatile sig_atomic_t canJump = 0;

#ifdef USE_SIGSETJMP
sigjmp_buf senv;
#else
jmp_buf env;
#endif 

void handler(int sig)
{
    printf("receive signal[%d:%s]\n", sig, strsignal(sig));
    printSigMask(stdout, NULL);

    if (!canJump)
    {
        printf("env buff not yet set, just return");
        return;
    }

#ifdef USE_SIGSETJMP
    siglongjmp(senv, 1);
#else 
    longjmp(env, 1);
#endif

}


int main()
{
    struct sigaction sa;
    
    printSigMask(stdout, "printSigMask at start up\n");

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = handler;
    if (sigaction(SIGINT, &sa, NULL) < 0)
    {
        printf("sigaction error\n");
        return -1;
    }

#ifdef USE_SIGSETJMP
    printf("calling sigsetjmp\n");
    if (sigsetjmp(senv, 1) == 0)
#else
    printf("call setjmp\n");
    if (setjmp(env) == 0)
#endif 
        canJump = 1;
    else
    {
        printSigMask(stdout, "After jump from handler, sigmask is \n");
    }

    while (1)
    {
        pause();
    }
    
    return 0;
}
