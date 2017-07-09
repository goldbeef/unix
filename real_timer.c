/*************************************************************************
    > File Name: real_timer.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年07月05日 星期三 21时37分57秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

volatile sig_atomic_t gotAlarm = 0;

void displayTime(const char* msg, int includeTimer)
{
    struct itimerval itv;
    struct timeval curr;

    static struct timeval start;
    static int calNum = 0;

    int ret;
    if (calNum == 0)
    {
        ret = gettimeofday(&start, NULL);
        CHECK_RET_VOID(ret, "gettimeofday");
    }

    if (calNum % 20 == 0)
    {
        printf("\tElasped value interval\n");
    }

    ret = gettimeofday(&curr, NULL);
    CHECK_RET_VOID(ret, "gettimeofday");
    printf("%-7s\t%6.2f", msg, curr.tv_sec - start.tv_sec + (curr.tv_usec - start.tv_usec)/1000000.0);
    
    if (includeTimer)
    {
        ret = getitimer(ITIMER_REAL, &itv);
        CHECK_RET_VOID(ret, "getitimer");
        printf("\t%6.2f\t%6.2f\n", itv.it_value.tv_sec + itv.it_value.tv_usec/1000000.0,
               itv.it_interval.tv_sec + itv.it_interval.tv_usec/1000000.0);
    }
    printf("\n");
    
    calNum++;
}

void sigAlarmHandler(int signo)
{
    gotAlarm = 1;
}

int main(int argc, char* argv[])
{
    struct itimerval itv;
    clock_t prevClock;
    int maxSigs;
    int sigCnt;
    struct sigaction sa;

    if (argc > 1 && strcmp(argv[1], "--help") == 0)
    {
        CHECK_RET(-1, "Usage: %s [sec usec int-sec int-usec]", argv[0]);
    }

    sigCnt = 0;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = sigAlarmHandler;

    int ret = sigaction(SIGALRM, &sa, NULL);
    CHECK_RET(ret, "sigaction");

    //set timer
    itv.it_value.tv_sec = (argc > 1) ? atoi(argv[1]) : 2;
    itv.it_value.tv_usec = (argc > 2) ? atoi(argv[2]) : 0;
    itv.it_interval.tv_sec = (argc >3) ? atoi(argv[3]) : 0;
    itv.it_interval.tv_usec = (argc > 4) ? atoi(argv[4]) : 0;

    maxSigs = (itv.it_interval.tv_sec == 0 && itv.it_interval.tv_usec == 0) ? 1 : 3;

    ret = setitimer(ITIMER_REAL, &itv, 0);
	CHECK_RET(ret, "setitimer");
    prevClock = clock();
    sigCnt = 0;

    displayTime("Main:", 1);
    while (1)
    {
        while (((clock() - prevClock) * 10 / CLOCKS_PER_SEC) < 5)
        {
            if (gotAlarm)
            {
                gotAlarm = 0;
                displayTime("ALARM:", 1);
                
                sigCnt++;
                if (sigCnt >= maxSigs)
                {
                    printf("That's all folks\n");
                    exit(0);
                }
            }
        }
        prevClock = clock();
        displayTime("Main:", 1);
    }
    
    return 0;
}


