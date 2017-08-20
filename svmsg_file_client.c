/*************************************************************************
    > File Name: svmsg_file_client.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月13日 星期日 17时06分12秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"
#include "svmsg_file.h"

static int clientId = 0;

void removeQueue(void)
{
	int ret;
	ret = msgctl(clientId, IPC_RMID, NULL);
	CHECK_RET_VOID(ret, "msgctl");
}

int main(int argc, char *argv[])
{
	struct RequestMsg req;
	struct ResponseMsg res;

	int serverId, numMsgs;
	int msglen, totalBytes;

	if (argc != 2 || strcmp(argv[1], "--help") == 0)
	{
		CHECK_RET(-1, "Usage: %s pathname", argv[0]);
	}

	serverId = msgget(SERVER_KEY, S_IWUSR);
	CHECK_RET(serverId, "msgget");

	clientId = msgget(IPC_PRIVATE, S_IWUSR|S_IRUSR|S_IWGRP);
	CHECK_RET(clientId, "msgget");

	atexit(removeQueue);

	req.mtype = 1;
	req.clientId = clientId;
	strncpy(req.pathname, argv[1], sizeof(req.pathname));

	int ret = msgsnd(serverId, &req, REQ_MSG_SIZE, 0);

	ret = msgrcv(clientId, &res, RESP_MSG_SIZE, 0, 0);
	CHECK_RET(ret, "msgrcv");

	if (res.mtype == RESP_MT_FAIL)
	{
		printf("%s\n", res.data);
		return -1;
	}

	totalBytes = 0;
	totalBytes += ret;

	while (res.mtype == RESP_MT_DATA)
	{
		msglen = msgrcv(clientId, &res, RESP_MSG_SIZE, 0, 0);
		CHECK_RET(msglen, "msgrcv");

		totalBytes += msglen;
	}

	printf("Receive totalBytes[%d]\n", totalBytes);
	return 0;
}

