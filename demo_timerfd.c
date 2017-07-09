/*************************************************************************
    > File Name: ptmr_sigev_signal.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年07月09日 星期日 16时21分20秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

#define TIMER_SIG SIGRTMAX

int main(int argc, char* argv[])
{
    struct itimerspec ts;
    struct timespec start, now;
    int maxExp, fd, secs, nanosecs;
    uint64_t numExp, totalExp;

    
    if (argc < 6 || strcmp(argv[1], "--help")== 0)
    {
        CHECK_RET(-1, "Usage: %s secs nsecs int-secs int-usecs max-exp", argv[0]);
    }

    ts.it_value.tv_sec = atoi(argv[1]);
    ts.it_value.tv_nsec = atoi(argv[2]);
    ts.it_interval.tv_sec = atoi(argv[3]);
    ts.it_interval.tv_nsec = atoi(argv[4]);

    maxExp = atoi(argv[5]);

    fd = timerfd_create(CLOCK_REALTIME, 0);
    CHECK_RET(fd, "timerfd_create");

    int ret = timerfd_settime(fd, 0, &ts, NULL);
    CHECK_RET(ret, "timerfd_settime");

    ret = clock_gettime(CLOCK_MONOTONIC, &start);
    CHECK_RET(ret, "clock_gettime");

    for (totalExp = 0; totalExp < maxExp;)
    {
        ret = read(fd, &numExp, sizeof(numExp));
        if (ret != sizeof(numExp))
        {
            CHECK_RET(-1, "read");
        }

        totalExp += numExp;

        ret = clock_gettime(CLOCK_MONOTONIC, &now);
        CHECK_RET(ret, "clock_gettime");

        secs = now.tv_sec - start.tv_sec;
        nanosecs = now.tv_nsec - start.tv_nsec;
        if (nanosecs < 0)
        {
            secs--;
            nanosecs += 1000000000;
        }

        printf("expirationTime[%.6f], readExp[%d], totalExp[%d]\n", secs + nanosecs/1000000000.0, 
                (int)numExp, (int)totalExp);
    }

    return 0;
}
