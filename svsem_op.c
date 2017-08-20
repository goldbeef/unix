/*************************************************************************
    > File Name: svsem_op.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月20日 星期日 08时00分59秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

#define MAX_SEM_PAIR 10

union semun 
{
   int		val;	/* Value for SETVAL */
   struct semid_ds *buf;	/* Buffer for IPC_STAT, IPC_SET */
   unsigned short  *array;	/* Array for GETALL, SETALL */
   struct seminfo  *__buf;	/* Buffer for IPC_INFO
			   (Linux-specific) */
};

int main(int argc, char *argv[])
{
	int ret = 0;
	int opFlag = 0;
	int opt = 0;

	struct sembuf opts[MAX_SEM_PAIR];

	while ((opt = getopt(argc, argv, "un")) != -1)
	{
		switch (opt) 
		{
			case 'u':
			{
				opFlag |= SEM_UNDO;
			}
			break;
			
			case 'n':
			{
				opFlag |= IPC_NOWAIT;
			}
			break;

			default:
			{
				CHECK_RET(-1, "Usage: %s [-un] semid semnum-opval [semnum-opval]", argv[0]);
			}
		}
	}
	
	if (argc - optind < 2 )
	{
		CHECK_RET(-1, "Usage: %s [-un] semid semnum-opval [semnum-opval]", argv[0]);
	}
	
	int semid = atoi(argv[optind]);
	int semPair = argc - optind - 1;
	int i;
	int count = 0;
	// 0-2 0+2
	for (i = 0; i < semPair && i < MAX_SEM_PAIR; i++)
	{
		const char* addOp = strchr(argv[optind + 1 + i], '+'); 
		const char* delOp = strchr(argv[optind + 1 + i], '-'); 

		if (addOp == NULL && delOp == NULL)
		{
			continue;
		}
		opts[count].sem_num = atoi(argv[optind + 1 + i]);
		opts[count].sem_op = (addOp != NULL) ? atoi(addOp) : atoi(delOp);
		opts[count].sem_flg = opFlag;
		count++;
	}

	ret = semop(semid, &opts[0], count);
	CHECK_RET(ret, "sem_op fail, errno[%d:%s]", errno, strerror(errno));

	return 0;
}
