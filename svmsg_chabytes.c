/*************************************************************************
    > File Name: svmsg_chabytes.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月13日 星期日 15时45分04秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

int main(int argc, char *argv[])
{
	struct msqid_ds ds;
	int msqid;

	if (argc != 3 || strcmp(argv[1], "--help") == 0)
	{
		CHECK_RET(-1, "Usage: %s msqid max-bytes", argv[0]);
	}

	msqid = atoi(argv[1]);
	int ret = msgctl(msqid, IPC_STAT, &ds);
	CHECK_RET(ret, "msgctl");

	ds.msg_qbytes = atoi(argv[2]);

	ret = msgctl(msqid, IPC_SET, &ds);
	CHECK_RET(ret, "msgctl");

	return 0;
}
