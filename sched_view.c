/*************************************************************************
    > File Name: shed_view.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年07月22日 星期六 14时40分07秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        CHECK_RET(-1, "Usage: %s pid", argv[0]);
    }

    int pol;
    struct sched_param sp;

    pol = sched_getscheduler(atoi(argv[1]));
    CHECK_RET(pol, "shed_getscheduler");
    
    int ret;
    ret = sched_getparam(atoi(argv[1]), &sp);
    CHECK_RET(ret, "sched_param");

    printf("pol: ");
    if (pol == SCHED_OTHER)
    {
        printf("other\n");
    }
    else if (pol == SCHED_RR)
    {
        printf("rr\n");
    }
    else if (pol == SCHED_FIFO)
    {
        printf("fifo\n");
    }

    printf("\t priority: %d\n", sp.sched_priority);

    return 0;
}
