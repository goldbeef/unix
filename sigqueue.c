/*************************************************************************
    > File Name: sigqueue.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年06月21日 星期三 21时08分33秒
 ************************************************************************/

#include <stdio.h>
#include <signal.h>

#include "check.h"

// sigqueue pid sig-num data [num-sig]
//

int main(int argc, char* argv[])
{
    int sig, numSig, j, sigData;
    union sigval sv;
    
    int ret = 0;

    if (argc < 4)
    {
        CHECK_RET(-1, "Usage: %s pid sig-num data [num-sig]\n", argv[0]);
    }
    
    sig = atoi(argv[2]);
    sigData = atoi(argv[3]);
    numSig =  (argc > 4) ? (atoi(argv[4])) : 1;

    for (j = 0; j < numSig; j++)
    {
        sv.sival_int = sigData + j;
        
        ret = sigqueue(atoi(argv[1]), sig, sv);
        CHECK_RET(ret, "sigqueue error");
    }

    return 0;
}


