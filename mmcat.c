/*************************************************************************
    > File Name: mmcat.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月20日 星期日 14时39分12秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

int main(int argc, char *argv[])
{
	char* addr = NULL;
	int fd;
	struct stat fileStat;

	if (argc != 2 || strcmp(argv[0], "--help") == 0)
	{
		CHECK_RET(-1, "Usage: %s file-path", argv[0]);
	}

	fd = open(argv[1], O_RDONLY);
	CHECK_RET(fd, "open");

	int ret = fstat(fd, &fileStat);
	CHECK_RET(ret, "fstat");

	addr = mmap(NULL, fileStat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	CHECK_RET((int)addr, "mmap");

	ret = write(STDOUT_FILENO, addr, fileStat.st_size);
	CHECK_RET(ret, "write");

	while (1)
	{
		sleep(1);
	}
	return 0;
}
