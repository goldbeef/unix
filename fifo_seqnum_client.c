/*************************************************************************
    > File Name: fifo_seqnum_client.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月12日 星期六 13时20分14秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"
#include "fifo_seqnum.h"

static char clientFifo[CLIENT_FIFO_NAME_LEN];

static void removeFifo(void)
{
    unlink(clientFifo);
}

int main(int argc, char*  argv[])
{
    if (argc != 2 || strcmp(argv[1], "--help") == 0)
    {
        CHECK_RET(-1, "Usage: %s seq-len", argv[0]);
    }

    umask(0);
    snprintf(clientFifo, CLIENT_FIFO_NAME_LEN,  CLIENT_FIFO_TEMPLATE, getpid());
    int ret = mkfifo(clientFifo, 0666);
    CHECK_RET(ret, "mkfifo");
    atexit(removeFifo);

    int serverFd, clientFd;
    struct Request req;
    struct Response res;

    req.pid  = getpid();
    req.seqLen = atoi(argv[1]);

    serverFd = open(SERVER_FIFO, O_WRONLY);
    CHECK_RET(serverFd, "open");

    ret = write(serverFd, &req, sizeof(req));
    if (ret != sizeof(req))
    {
        CHECK_RET(-1, "wirte");
    }

    clientFd = open(clientFifo, O_RDONLY);
    CHECK_RET(clientFd, "open");

    ret = read(clientFd, &res, sizeof(res));
    if (ret != sizeof(res))
    {
        CHECK_RET(-1, "read");
    }

    printf("%d\n", res.seqNum);

    return 0;
}
