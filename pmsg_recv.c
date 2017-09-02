/*************************************************************************
    > File Name: pmsg_recv.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月26日 星期六 10时52分03秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

int main(int argc, char *argv[])
{
	int flags, opt;
	mqd_t mqd;
	int prio;
	char* buff;
	struct mq_attr attr;
	int numRead;

	flags = O_RDONLY;
	while ((opt = getopt(argc, argv, "n")) != -1)
	{
		switch (opt)
		{
			case 'n':
				flags |= O_NONBLOCK;
				break;
			default:
				CHECK_RET(-1, "Usage: %s [-n] mq-name", argv[0]);
		}
	}

	if (optind >= argc)
	{
		CHECK_RET(-1, "Usage: %s [-n] mq-name", argv[0]);
	}

	mqd = mq_open(argv[1], flags);
	CHECK_RET(mqd, "mq_open");

	int ret = mq_getattr(mqd, &attr);
	CHECK_RET(ret, "mq_getattr");
	
	buff = malloc(attr.mq_msgsize);
	CHECK_NULL(buff, "malloc");

	numRead = mq_receive(mqd, buff, attr.mq_msgsize, &prio);
	CHECK_RET(numRead, "mq_receive");

	printf("msg[%s], prio[%d]\n", buff, prio);

	return 0;
}
