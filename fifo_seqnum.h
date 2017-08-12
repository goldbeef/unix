/*************************************************************************
    > File Name: fifo_seqnum.h
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月12日 星期六 12时54分05秒
 ************************************************************************/

#ifndef __FIFO_SEQNUM_H
#define __FIFO_SEQNUM_H

#include "all_def.h"

#define SERVER_FIFO "/tmp/seqnum_sv"
#define CLIENT_FIFO_TEMPLATE "/tmp/seqnum_cl.%d"
#define CLIENT_FIFO_NAME_LEN (sizeof(CLIENT_FIFO_TEMPLATE) + 20)

struct Request
{
    pid_t pid;
    int seqLen;
};

struct Response
{
    int seqNum;
};

#endif 
