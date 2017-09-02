/*************************************************************************
    > File Name: psem_create.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月26日 星期六 15时58分29秒
 ************************************************************************/
#include <stdio.h>
#include "all_def.h"

int main(int argc, char *argv[])
{
	int flags, opt;
	mode_t perms = 0666;
	sem_t* sem;
	int val;
	while ((opt = getopt(argc, argv, "cx")) != -1)
	{
		switch (opt)
		{
			case 'c':
				flags |= O_CREAT;
				break;
			case 'x':
				flags |= O_EXCL;
				break;
			default:
				CHECK_RET(-1, "Usage: %s [-cx] sem-name sem-value", argv[0]);
		}
	}
	
	if (optind + 1 >= argc)
	{
		CHECK_RET(-1, "Usage: %s [-cx] sem-name sem-value", argv[0]);
	}

	val = atoi(argv[optind + 1]);
	sem  = sem_open(argv[optind], flags, perms, val); 
	CHECK_NULL(sem, "sem_open");

	return 0;
}

