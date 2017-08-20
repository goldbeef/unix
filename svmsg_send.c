/*************************************************************************
    > File Name: svmsg_send.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月13日 星期日 11时22分43秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

#define MAX_MTEXT 1024

struct mbuf
{
	int mtype;
	char mtext[MAX_MTEXT];
};


int main(int argc, char *argv[])
{
	int msqid, flags, msglen;
	struct mbuf msg;
	int opt;

	flags = 0;
	while ((opt = getopt(argc, argv, "n")) != -1)
	{
		if (opt == 'n')
		{
			flags |= IPC_NOWAIT;
		}
		else 
		{
			CHECK_RET(-1, "Usage: %s [-n] msqid msg-type [msg-text]", argv[0]);
		}
	}

	if (argc < optind + 2 || argc > optind + 3)
	{
		CHECK_RET(-1, "Usage: %s [-n] msqid msg-type [msg-text]", argv[0]);
	}

	msqid = atoi(argv[optind]);
	msg.mtype = atoi(argv[optind + 1]);
	if (argc > optind + 2)
	{
		msglen = strlen(argv[optind + 2]) + 1;
		if (msglen > MAX_MTEXT)
		{
			CHECK_RET(-1, "msg too long");
		}

		memcpy(msg.mtext, argv[optind + 2], msglen);
	}
	else 
	{
		msglen = 0;
	}

	int ret = msgsnd(msqid, &msg, msglen, flags);
	CHECK_RET(ret, "msgsend, errno[%d:%s]", errno, strerror(errno));

	return 0;
}
