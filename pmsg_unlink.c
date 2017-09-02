/*************************************************************************
    > File Name: pmsg_unlink.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月26日 星期六 09时49分21秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

int main(int argc, char *argv[])
{
	if (argc != 2 || strcmp(argv[1], "--help") == 0)
	{
		CHECK_RET(-1, "Usage: %s mq-name", argv[0]);
	}

	int ret = mq_unlink(argv[1]);
	CHECK_RET(ret, "mq_unlink");

	return 0;
}
