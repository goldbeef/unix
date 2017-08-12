/*************************************************************************
    > File Name: utmpx_login.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月05日 星期六 15时42分15秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

int main(int argc, char* argv[])
{
    struct utmpx ut, *ptrUt;
    char* devName;

    if (argc < 2 || strcmp(argv[1], "--help") == 0)
    {
        CHECK_RET(-1, "usage: %s username [sleep-time]", argv[0]);
    }

    memset(&ut, 0, sizeof(ut));
    ut.ut_type = USER_PROCESS;
    strncpy(ut.ut_user, argv[1], sizeof(ut.ut_user));
    time((time_t*)&ut.ut_tv.tv_sec);
    ut.ut_pid = getpid();
    
    devName = ttyname(STDIN_FILENO);
    CHECK_NULL(devName, "ut_type");
    strncpy(ut.ut_line, devName + 5, sizeof(ut.ut_line));
    strncpy(ut.ut_id, devName + 8, sizeof(ut.ut_id));
    
    printf("create login entries\n");
    setutxent();

    ptrUt = pututxline(&ut);
    CHECK_NULL(ptrUt, "pututxline");

    updwtmpx(_PATH_WTMP, &ut);

    sleep(10);
    ut.ut_type = DEAD_PROCESS;
    time((time_t*)&ut.ut_tv.tv_sec);
    memset(&ut.ut_user, 0, sizeof(ut.ut_user));
    printf("create logout entries\n");

    setutxent();
    ptrUt = pututxline(&ut);
    CHECK_NULL(ptrUt, "pututxline");
    updwtmpx(_PATH_WTMP, &ut);
    endutxent();

    return 0;
}
