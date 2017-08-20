/*************************************************************************
    > File Name: svshm_xfr.h
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月20日 星期日 09时47分54秒
 ************************************************************************/

#ifndef  __SVSHM_XFR_H
#define __SVSHM_XFR_H 
#include "all_def.h"
#include "binary_sems.h"

#define SHM_KEY 0x1234
#define SEM_KEY 0x5678


#define OBJ_PERM 0666

#define WRITE_SEM 0
#define READ_SEM 1

#define MAX_BUFF_SIZE 4096

struct shmseg
{
	int cnt;
	char buf[MAX_BUFF_SIZE];
};

#endif /* ifndef  __SVSHM_XFR_H */
