/*************************************************************************
    > File Name: svmsg_ls.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月13日 星期日 15时57分11秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

int main(int argc, char *argv[])
{
	int maxind, ind, msqid;
	struct msqid_ds ds;
	struct msginfo msginfo;

	maxind = msgctl(0, MSG_INFO, (struct msqid_ds*)&msginfo);
	CHECK_RET(maxind, "msgctl");

	printf("maxind[%d]\n", maxind);
	printf("index\tmsqid\tkey\tmsg\n");
	for (ind = 0; ind <= maxind; ind++)
	{
		msqid = msgctl(ind, MSG_STAT, &ds);
		if (msqid < 0)
		{
			continue;
		}

		printf("%d\t%d\t%x\t%d\n", ind, msqid, (int)ds.msg_perm.__key, (int)ds.msg_qnum);
	}
	return 0;
}
