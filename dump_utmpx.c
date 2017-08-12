/*************************************************************************
    > File Name: dump_utmpx.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月05日 星期六 13时58分25秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

int main(int argc, char* argv[])
{
    if (argc > 1 && strcmp(argv[1], "--help") == 0)
    {
        CHECK_RET(-1, "Usage: %s [utmp-path]", argv[1]);
    }
    
    int ret;
    if (argc > 1)
    {
        ret = utmpxname(argv[1]);
        CHECK_RET(ret, "utmpxname");
    }
    
    setutxent();

    printf("user\ttype\tpid\tline\tid\thost\tdate\ttime\n");
    
    struct utmpx* ut;
    while ((ut = getutxent()) != NULL)
    {
        printf("%s\t", ut->ut_user);
        printf("%s\t", 
               (ut->ut_type == EMPTY) ? "EMPTY": 
               (ut->ut_type == BOOT_TIME) ? "BOOT_TIME": 
               (ut->ut_type == NEW_TIME) ? "NEW_TIME": 
               (ut->ut_type == OLD_TIME) ? "OLD_TIME": 
               (ut->ut_type == INIT_PROCESS) ? "INIT_PROCESS": 
               (ut->ut_type == LOGIN_PROCESS) ? "LOGIN_PROCESS": 
               (ut->ut_type == USER_PROCESS) ? "USER_PROCESS": 
               (ut->ut_type == DEAD_PROCESS) ? "DEAD_PROCESS": "???"
              );
        printf("%d\t", ut->ut_pid);
        printf("%s\t", ut->ut_line);
        printf("%s\t", ut->ut_id);
        printf("%s\t", ut->ut_host);
        printf("%s\n", ctime((time_t*)&ut->ut_tv.tv_sec));
    }

    endutxent();
    return 0;
}
