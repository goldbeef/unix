/*************************************************************************
    > File Name: svshm_create.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月20日 星期日 10时58分45秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

int main(int argc, char *argv[])
{
	int numKeyFlags = 0;
	int flags, shmid, opt;
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
				key = atoi(optarg);
				CHECK_RET((int)key, "scanf");
				numKeyFlags++;
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
				CHECK_RET(-1, "Usage: %s [-cx] {-f pathname | -k key| -p} [otical-perm] shm-size", argv[0]);
			}
		}
	}

	if (numKeyFlags != 1)
	{
		CHECK_RET(-1, "Usage: %s [-cx] {-f pathname | -k key| -p} [otical-perm] shm-size", argv[0]);
	}
	
	int shmSize = 0;
	if (optind + 1 < argc)
	{
		perm = atoi(argv[optind]);
		shmSize = atoi(argv[optind + 1]);
	}
	else 
	{
		perm = S_IRUSR | S_IWUSR;
		shmSize = atoi(argv[optind]);
	}
	
	shmid = shmget(key, shmSize, flags | perm);
	CHECK_RET(shmid, "shmget");

	return 0;
}
