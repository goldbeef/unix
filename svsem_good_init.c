/*************************************************************************
    > File Name: svsem_good_init.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月20日 星期日 07时25分52秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

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
	if (argc < 3 || strcmp(argv[1], "--help") == 0)
	{
		CHECK_RET(-1, "Usage: %s sem-key sem-val1 [sem-val2 ...]", argv[0]);
	}

	int semid, semkey, semnum;
	semkey = atoi(argv[1]);
	semnum = argc - 2;

	int ret = 0;
	int i;
	semid = semget(semkey, argc - 2, IPC_CREAT | IPC_EXCL | 0666);
	if (semid == 0)
	{
		//new-create 
		union semun arg;
		struct sembuf sop;
		
		//init sem-val 
		arg.val = 0;
		ret = semctl(semid, 0, SETALL, arg);
		CHECK_RET(ret, "semctl");

		//nop-op, change the sem_otime
		//very important
		sop.sem_num = 0;
		sop.sem_op = 0;
		sop.sem_flg = 0;
		ret = semop(semid, &sop, 1);
		CHECK_RET(ret, "semop");

		//init finish 
	}
	else 
	{
		//already-created sem 
		union semun arg;
		struct semid_ds ds;
		
		if (errno != EEXIST)
		{
			CHECK_RET(-1, "sem-create error[%d:%s]", errno, strerror(errno));
		}

		semid = semget(semkey, 0, 0666);
		CHECK_RET(semid, "semget");

		arg.buf = &ds;
		for (i = 0; i < 3; i++)
		{
			ret = semctl(semid, 0, IPC_STAT, arg);
			CHECK_RET(ret, "semctl");
			
			//very important
			if (ds.sem_otime != 0)
			{
				break;
			}
			sleep(1);
		}

		if (ds.sem_otime == 0)
		{
			CHECK_RET(-1, "exist sem not init");
		}
	}


	printf("sem-init success\n");

	//do other things
	return 0;
}
