/*************************************************************************
    > File Name: sig_sender.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年06月19日 星期一 22时29分26秒
 ************************************************************************/

#include <stdio.h>
#include <signal.h>

int main(int argc, char* argv[])
{
    int numSigs, sig, j, pid;
    if (argc < 4)
    {
        printf("Usage: %s pid num-sigs sig-num [sig-num-2]\n", argv[0]);
        return -1;
    }

    pid = atoi(argv[1]);
    numSigs = atoi(argv[2]);
    sig = atoi(argv[3]);

    for (j = 0; j < numSigs; j++)
    {
        if (kill(pid, sig) < 0)
        {
            printf("kill error\n");
            return -1;
        }
    }

    if (argc > 4)
    {
        if (kill(pid, atoi(argv[4])) < 0)
        {
            printf("kill error\n");
            return -1;
        }
    }

    return 0;
}
