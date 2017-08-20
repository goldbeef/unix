/*************************************************************************
    > File Name: svmsg_create.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月13日 星期日 10时40分06秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

int main(int argc, char *argv[])
{
	int numKeyFlags = 0;
	int flags, msqid, opt;
	int perm;
	key_t key;
	int ret;

	while ((opt = getopt(argc, argv, "cf:k:px")) != -1)
	{
		switch (opt) 
		{
			case 'c':
			{
				flags |= IPC_CREAT;
			}
			break;
			
			case 'f':
			{
				key = ftok(optarg, 1);
				CHECK_RET(key, "ftok");
				numKeyFlags++;
			}
			break;
			
			case 'k':
			{
				ret = scanf(optarg, "%d", &key);
				CHECK_RET(ret, "scanf");
			}
			break;

			case 'p':
			{
				key = IPC_PRIVATE;
				numKeyFlags++;
			}
			break;

			case 'x':
			{
				flags |= IPC_EXCL;
			}
			break;

			default:
			{
				CHECK_RET(-1, "Usage: %s [-cx] {-f pathname | -k key| -p} [otical-perm]", argv[0]);
			}
		}
	}

	if (numKeyFlags != 1)
	{
		CHECK_RET(-1, "Usage: %s [-cx] {-f pathname | -k key| -p} [otical-perm]", argv[0]);
	}
	
	perm = (optind == argc) ? (S_IRUSR | S_IWUSR) : atoi(argv[optind]);
	
	msqid = msgget(key, flags | perm);
	CHECK_RET(msqid, "msgget");

	return 0;
}
