/*************************************************************************
    > File Name: svmsg_file_server.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月13日 星期日 16时33分21秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"
#include "svmsg_file.h"

static void sigHandler(int signo)
{
	int savedErrno;
	savedErrno = errno;
	
	while (waitpid(-1, NULL, WNOHANG) != -1)
	{
		continue;
	}
	errno = savedErrno;
}


static void serverRequest(struct RequestMsg* pReq)
{
	int fd;
	int nread;
	struct ResponseMsg res;
	int ret;
	fd = open(pReq->pathname, O_RDONLY);
	if (fd == -1)
	{
		res.mtype = RESP_MT_FAIL;
		snprintf(res.data, sizeof(res.data), "%s", "open fail");
		ret = msgsnd(pReq->clientId, &res, strlen(res.data) + 1, 0);
		return;
	}

	res.mtype = RESP_MT_DATA;
	while ((nread = read(fd, res.data, RESP_MSG_SIZE)) > 0)
	{
		ret = msgsnd(pReq->clientId, &res, nread, 0);
		CHECK_RET_VOID(ret, "msgsnd");
	}

	res.mtype = RESP_MT_END;
	ret = msgsnd(pReq->clientId, &res, 0, 0);
	CHECK_RET_VOID(ret, "msgsend");

	return;
}

int main(int argc, char *argv[])
{	
	struct RequestMsg  req;
	pid_t pid;
	int msglen;
	int serverId;
	struct sigaction sa;

	serverId = msgget(SERVER_KEY, IPC_CREAT|S_IRUSR|S_IWUSR|S_IWGRP);
	CHECK_RET(serverId, "msgget");

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = sigHandler;

	int ret = sigaction(SIGCHLD, &sa, NULL);
	CHECK_RET(ret, "sigaction");
	
	while (1)
	{
		msglen = msgrcv(serverId, &req, REQ_MSG_SIZE, 0, 0);
		if (msglen == -1)
		{
			if (errno != EINTR)
			{
				CHECK_RET(-1, "msgrcv, errno[%d]", errno);
			}
			continue;
		}

		pid = fork();
		CHECK_RET(pid, "fork");

		if (pid == 0)
		{
			//child-process 
			serverRequest(&req);
			_exit(0);
		}

		//parent-process
	}

	ret = msgctl(serverId, IPC_RMID, NULL);
	CHECK_RET(ret, "msgctl");

	return 0;
}
