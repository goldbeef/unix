/*************************************************************************
    > File Name: pmsg_getattr.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月26日 星期六 10时25分21秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

int main(int argc, char *argv[])
{
	if (argc != 2 || strcmp(argv[1], "--help") == 0)
	{
		CHECK_RET(-1, "Usage: %s mq-name", argv[0]);
	}

	mqd_t mqd;
	struct mq_attr attr;

	mqd = mq_open(argv[1], O_RDONLY);
	CHECK_RET(mqd, "mq_open");

	int ret = mq_getattr(mqd, &attr);
	CHECK_RET(ret, "mq_getattr");

	printf("maxmsg[%d], msgsize[%d], curmsgs[%d]\n",
			(int)attr.mq_maxmsg, (int)attr.mq_msgsize, (int)attr.mq_curmsgs);
	return 0;
}
