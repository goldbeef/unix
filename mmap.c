/*************************************************************************
    > File Name: mmap.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月20日 星期日 15时07分53秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

#define MAX_MAP_SIZE 10

int main(int argc, char *argv[])
{
	char* addr = NULL;
	int fd;
	int ret;

	if (argc < 2 || strcmp(argv[1], "--help") == 0)
	{
		CHECK_RET(-1, "Usage: %s file-path [new-value]", argv[0]);
	}

	fd = open(argv[1], O_RDWR);
	CHECK_RET(fd, "open");

	addr = mmap(NULL, MAX_MAP_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	CHECK_RET((int)addr, "mmap");

	close(fd);

	if (argc > 2)
	{
		if (strlen(argv[2]) >= MAX_MAP_SIZE)
		{
			CHECK_RET(-1, "new-value too large");
		}
		memset(addr, 0, MAX_MAP_SIZE);
		strncpy(addr, argv[2], MAX_MAP_SIZE - 1);

		ret = msync(addr, MAX_MAP_SIZE, MS_SYNC);
		CHECK_RET(ret, "msync");
	}

	addr[1024] = 10; //ok 
	addr[8000] = 10; //sigsegv

	return 0;
}
