/*************************************************************************
    > File Name: svsem_setall.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月16日 星期三 20时55分57秒
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
	struct semid_ds ds;
	union semun arg;
	int i, semid;

	if (argc < 3 || strcmp(argv[1], "--help") == 0)
	{
		CHECK_RET(-1, "Usage: %s semid val ...", argv[0]);
	}

	semid = atoi(argv[1]);
	arg.buf = &ds;

	int ret = semctl(semid, 0, IPC_STAT, arg);
	CHECK_RET(ret, "semctl");

	if (ds.sem_nsems != argc - 2)
	{
		CHECK_RET(-1, "ds.sem_nsems != argc -2");
	}

	arg.array = calloc(ds.sem_nsems, sizeof(arg.array[0]));
	CHECK_NULL(arg.array, "calloc");

	for (i = 2; i < argc; i++)
	{
		arg.array[i - 2] = atoi(argv[i]);
	}

	ret = semctl(semid, 0, SETALL, arg);
	CHECK_RET(ret, "semctl");

	printf("Semphore values changed, pid[%d]\n", getpid());
	return 0;
}
