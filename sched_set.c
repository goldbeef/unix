/*************************************************************************
    > File Name: sched_set.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年07月22日 星期六 13时51分05秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

int main(int argc, char* argv[])
{
    int pol;
    struct sched_param sp;

    if (argc < 3 || strchr("rfo", argv[1][0]) == NULL)
    {
        CHECK_RET(-1, "Usage: %s policy priority pid\n"
                 " policy is: r(RR); f(FIFO);  o(other)\n", argv[0]);
    }
    
    if (argv[1][0] == 'r')
    {
        pol = SCHED_RR;
    }
    else if (argv[1][0] == 'f')
    {
        pol = SCHED_FIFO;
    }
    else
    {
        pol = SCHED_OTHER;
    }
    
    sp.sched_priority = atoi(argv[2]);
    
    int pid = atoi(argv[3]);
    int ret = sched_setscheduler(pid, pol, &sp);
    CHECK_RET(ret, "sched_setscheduler, errno[%d:%s]", errno, strerror(errno));
    
    return 0;
}
