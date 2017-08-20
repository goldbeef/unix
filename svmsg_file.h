/*************************************************************************
    > File Name: svmsg_file.h
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月13日 星期日 16时15分28秒
 ************************************************************************/

#ifndef _SVMSG_FILE_H     
#define _SVMSG_FILE_H     

#include "all_def.h"
#define SERVER_KEY 0xacacac
#define PATH_MAX 1024

struct RequestMsg
{
	int mtype;
	int clientId;
	char pathname[PATH_MAX];
};

#define OFFSET(TYPE, MEMBER) \
	((int)&(((TYPE*)0)->MEMBER))

#define REQ_MSG_SIZE (OFFSET(struct RequestMsg, pathname) - \
			OFFSET(struct RequestMsg, clientId) + PATH_MAX) 

#define RESP_MSG_SIZE 4096

struct ResponseMsg 
{
	int mtype;
	char data[RESP_MSG_SIZE];
};

#define RESP_MT_FAIL	1
#define RESP_MT_DATA	2
#define RESP_MT_END		3
		
#endif
 
