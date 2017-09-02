/*************************************************************************
    > File Name: pmsg_send.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月26日 星期六 10时33分59秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

int main(int argc, char *argv[])
{
	int flags, opt;
	mqd_t mqd;
	int prio = 0;

	flags = O_WRONLY;
	while ((opt = getopt(argc, argv, "np:")) != -1)
	{
		switch (opt)
		{
			case 'n':
				flags |= O_NONBLOCK;
				break;
			case 'p':
				prio = atoi(optarg);
				break;
			default:
				CHECK_RET(-1, "Usage: %s [-n] [-p prio] mq-name msg", argv[0]);
		}
	}

	if (optind + 1 >= argc)
	{
		CHECK_RET(-1, "Usage: %s [-n] [-p prio] mq-name msg", argv[0]);
	}

	mqd = mq_open(argv[optind], flags);
	CHECK_RET(mqd, "mq_open");

	int ret = mq_send(mqd, argv[optind + 1], strlen(argv[optind + 1]), prio);
	CHECK_RET(ret, "mq_send");

	return 0;
}
