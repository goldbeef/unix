/*************************************************************************
    > File Name: fifo_seqnum_server.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月12日 星期六 12时58分38秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"
#include "fifo_seqnum.h"

int main()
{
    int serverFd, dummyFd, clientFd;
    char clientFifo[CLIENT_FIFO_NAME_LEN];
    struct Request req;
    struct Response res;
    int seqNum = 0;

    umask(0);
    int ret = mkfifo(SERVER_FIFO, 0666);
    CHECK_RET(ret, "mkfifo");

    serverFd = open(SERVER_FIFO, O_RDONLY);
    CHECK_RET(serverFd, "open");

    dummyFd = open(SERVER_FIFO, O_WRONLY);
    CHECK_RET(dummyFd, "open");

    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
    {
        CHECK_RET(-1, "signal");
    }

    while (1)
    {
        ret = read(serverFd, &req, sizeof(req));
        CHECK_RET(ret, "read");

        if (ret != sizeof(req))
        {
            continue;
        }

        //open client-fifo 
        snprintf(clientFifo, CLIENT_FIFO_NAME_LEN,  CLIENT_FIFO_TEMPLATE, req.pid);
        clientFd = open(clientFifo, O_WRONLY);
        if (clientFd == -1)
        {
            continue;
        }

        //send resp 
        res.seqNum = seqNum;
        ret = write(clientFd, &res, sizeof(res));
        if (ret != sizeof(res))
        {
            continue;
        }

        close(clientFd);
        seqNum+= req.seqLen; 
    }

    return 0;
}
