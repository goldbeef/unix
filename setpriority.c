/*************************************************************************
    > File Name: setpriority.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年07月22日 星期六 11时40分59秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

int main(int argc, char* argv[])
{
    int which, prio;
    id_t who;

    if (argc != 4 || strchr("pgu", argv[1][0]) == NULL)
    {
        CHECK_RET(-1, "Usage: [%s] p|g|u  who priority\n"
                 " set priority of: p=process; g=process-group; u=process-user\n", argv[0]);
    }

    which = (argv[1][0] == 'p') ? PRIO_PROCESS:
        (argv[1][0] == 'g') ? PRIO_PGRP : PRIO_USER;
    who = atoi(argv[2]);
    prio = atoi(argv[3]);

    int ret = setpriority(which, who, prio);
    CHECK_RET(ret, "setpriority");

    errno = 0;
    prio = getpriority(which, who);
    if (prio == -1 && errno != 0)
    {
        CHECK_RET(-1, "getpriority, errno[%d:%s]", errno, strerror(errno));
    }

    printf("Nice[%d]\n", prio);
    return 0;
}
