/*************************************************************************
    > File Name: mprotect.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月20日 星期日 15时57分12秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

#define SHELL_FMT "cat /proc/%d/maps | grep zero"
#define CMD_SIZE (sizeof(SHELL_FMT) + 20)

#define MAX_MAP_SIZE 1024
int main(int argc, char *argv[])
{
	char cmd[CMD_SIZE];
	char* addr;

	addr = mmap(NULL, MAX_MAP_SIZE, PROT_NONE, MAP_SHARED|MAP_ANON, -1, 0);
	CHECK_RET((int)addr, "mmap");

	printf("before mprotect\n");
	snprintf(cmd, CMD_SIZE, SHELL_FMT, getpid());
	system(cmd);

	int ret = mprotect(addr, MAX_MAP_SIZE, PROT_READ|PROT_WRITE);
	CHECK_RET(ret, "mprotect");

	printf("after mprotect\n");
	system(cmd);
	return 0;
}
