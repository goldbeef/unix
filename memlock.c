/*************************************************************************
    > File Name: memlock.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月20日 星期日 16时07分12秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

void displayMincore(char* addr, int len)
{
	char* vec;
	int pagesize, numPages, j;

	pagesize = sysconf(_SC_PAGESIZE);
	CHECK_RET_VOID(pagesize, "sysconf");


	numPages = (len + pagesize - 1) / pagesize;
	vec = malloc(numPages);
	CHECK_NULL_VOID(vec, "malloc");

	int ret;
	ret = mincore(addr, len, vec);
	CHECK_RET_VOID(ret, "mincore");

	for (j = 0; j < numPages; j++)
	{
		printf("%c", vec[j]&1 ? '*':'.');
	}

	printf("\n");
}

int main(int argc, char *argv[])
{
	char*  addr;
	int len, locklen;
	int pagesize, stepsize, i;

	if (argc != 4 || strcmp(argv[1], "--help") == 0)
	{
		CHECK_RET(-1, "Usage: %s num-pages lock-page-step lock-page-len\n", argv[0]);
	}

	pagesize = sysconf(_SC_PAGESIZE);
	CHECK_RET(pagesize, "sysconf");

	len = pagesize * atoi(argv[1]);
	stepsize = pagesize * atoi(argv[2]);
	locklen = pagesize * atoi(argv[3]);

	addr = mmap(NULL, len, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
	CHECK_RET((int)addr, "mmap");
	
	printf("before lock\n");
	displayMincore(addr, len);

	int ret= 0;
	for (i = 0; i + locklen < len; i += stepsize)
	{
		ret = mlock(addr + i, locklen);
		CHECK_RET(ret, "mlock");
	}

	printf("after lock\n");
	displayMincore(addr, len);

	//sdfsdf
	//sdfsdf 
	//sdfs 
	//sdfsd 
	//sdf
	return 0;
}

