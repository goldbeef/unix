/*************************************************************************
    > File Name: svsem_create.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月16日 星期三 19时59分25秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

int main(int argc, char *argv[])
{
	int numKeyFlags = 0;
	int flags, semid, opt, semNum;
	int perm;
	key_t key;
	int ret;
	semNum = 0;

	while ((opt = getopt(argc, argv, "cf:k:px:s:")) != -1)
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
			
			case 's':
			{
				semNum = atoi(optarg);
			}
			break;

			default:
			{
				CHECK_RET(-1, "Usage: %s [-cx] {-f pathname | -k key| -p} [otical-perm] -s sem-num", argv[0]);
			}
		}
	}

	if (numKeyFlags != 1)
	{
		CHECK_RET(-1, "Usage: %s [-cx] {-f pathname | -k key| -p} [otical-perm] -s sem-num", argv[0]);
	}
	
	if (semNum <= 0)
	{
		CHECK_RET(-1, "Usage: %s [-cx] {-f pathname | -k key| -p} [otical-perm] -s sem-num", argv[0]);
	}

	perm = (optind != argc - 1) ? (S_IRUSR | S_IWUSR) : atoi(argv[optind]);

	semid = semget(key, semNum, flags | perm);
	CHECK_RET(semid, "semget");
	
	return 0;
}
