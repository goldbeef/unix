/*************************************************************************
    > File Name: anon_mmap.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月20日 星期日 15时39分52秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

int main(int argc, char *argv[])
{
	char*  addr;

#ifdef USE_MAP_ANON
	addr = mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
	CHECK_RET((int)addr, "mmap");
#else 
	int fd;
	fd = open("/dev/zero", O_RDWR);
	CHECK_RET(fd, "open");

	addr = mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	CHECK_RET((int)addr, "mmap");
	close(fd);
#endif

	*addr = 1;

	int ret = fork();
	CHECK_RET(ret, "fork");

	if (ret == 0)
	{
		//child-process 
		(*addr)++;
		ret = munmap(addr, sizeof(int));
		CHECK_RET(ret, "munmap");

		_exit(0);
	}

	//parent-process 
	ret = wait(NULL);
	CHECK_RET(ret, "wait");

	printf("parent-process, value[%d]\n", *addr);
	ret = munmap(addr, sizeof(int));
	CHECK_RET(ret, "munmap");

	return 0;
}
