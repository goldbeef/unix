/*************************************************************************
    > File Name: pmsg_create.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月26日 星期六 09时54分26秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

int main(int argc, char *argv[])
{
	int flags, opt;
	mode_t perms = 0666;
	mqd_t mqd;
	struct mq_attr attr, *attrp;

	attrp = NULL;
	attr.mq_maxmsg = 10;
	attr.mq_msgsize = 4096;

	while ((opt = getopt(argc, argv, "cxm:s:")) != -1)
	{
		switch (opt)
		{
			case 'c':
				flags |= O_CREAT;
				break;
			case 'x':
				flags |= O_EXCL;
				break;
			case 'm':
				attr.mq_maxmsg = atof(optarg);
				attrp = &attr;
				break;
			case 's':
				attr.mq_msgsize = atoi(optarg);
				attrp = &attr;
				break;
			default:
				CHECK_RET(-1, "Usage: %s [-cx] [-m maxmsg] [-s msgsize] mq-name", argv[0]);
		}
	}
	
	if (optind >= argc)
	{
		CHECK_RET(-1, "Usage: %s [-cx] [-m maxmsg] [-s msgsize] mq-name", argv[0]);
	}

	mqd = mq_open(argv[optind], flags, perms, attrp);
	CHECK_RET(mqd, "mq_open");

	return 0;
}

