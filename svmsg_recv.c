/*************************************************************************
    > File Name: svmsg_recv.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月13日 星期日 15时10分03秒
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
	int msqid, flags, type;
	int msglen;
	int maxBytes;
	struct mbuf msg;
	int opt;

	while ((opt = getopt(argc, argv, "ent:x")) != -1)
	{
		switch (opt)
		{
			case 'e':
				flags |= MSG_NOERROR; break;
			case 'n':
				flags |= IPC_NOWAIT; break;
			case 't':
				type = atoi(optarg); break;
			#ifdef MSG_EXCEPT 
			case 'x':
				flags |= MSG_EXCEPT; break;
			#endif
			default:
				CHECK_RET(-1, "Usage: %s [-enx] [-t type] msqid [max-bytes]", argv[0]);
		}
	}

	if (argc < optind + 1 || argc > optind + 2)
	{
		CHECK_RET(-1, "Usage: %s [-enx] [-t type] msqid [max-bytes]", argv[0]);
	}

	msqid = atoi(argv[optind]);
	maxBytes = (argc > optind + 1) ? atoi(argv[optind + 1]) : MAX_MTEXT;

	msglen = msgrcv(msqid, &msg, maxBytes, type, flags);
	CHECK_RET(msglen, "msgrcv");

	printf("msgrcv: type[%d], msglen[%d], body[%s]\n", msg.mtype, msglen, 
			(msglen > 0) ? msg.mtext : "");
	return 0;
}
