/*************************************************************************
    > File Name: psem_unlink.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月26日 星期六 16时09分23秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

int main(int argc, char *argv[])
{
	if (argc != 2 || strcmp(argv[1], "--help") == 0)
	{
		CHECK_RET(-1, "Usage: %s sem-name", argv[0]);
	}

	int ret = sem_unlink(argv[1]);
	CHECK_RET(ret, "sem_unlink");

	return 0;
}

