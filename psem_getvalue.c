/*************************************************************************
    > File Name: psem_getvalue.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月26日 星期六 16时19分05秒
 ************************************************************************/

#include <stdio.h>

#include "all_def.h"

int main(int argc, char *argv[])
{
	sem_t* sem;
	if (argc != 2 || strcmp(argv[1], "--help") == 0)
	{
		CHECK_RET(-1, "Usage: %s sem-name", argv[0]);
	}

	sem = sem_open(argv[1], 0);
	CHECK_NULL(sem, "sem_open");

	int val = 0;
	int ret = sem_getvalue(sem, &val);
	CHECK_RET(ret, "sem_getvalue");

	printf("sem[%s], value[%d]\n", argv[1], val);

	return 0;
}
