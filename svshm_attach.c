/*************************************************************************
    > File Name: svshm_attach.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月20日 星期日 11时32分01秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

int main(int argc, char *argv[])
{
	if (argc < 2 || strcmp(argv[1], "--help") == 0)
	{
		CHECK_RET(-1, "Usage: %s shmid1 [shmid2 ...]", argv[0]);
	}
	
	int i;
	void* ptr;
	for (i = 0; i < argc - 1; i++)
	{
		ptr = shmat(atoi(argv[i + 1]), 0, 0);
		CHECK_RET((int)ptr, "shmat");
	}

	while (1)
	{
		sleep(1);
	}

	return 0;
}
