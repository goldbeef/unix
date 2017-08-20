/*************************************************************************
    > File Name: svsem_mon.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月16日 星期三 20时26分36秒
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
	union semun arg, dummy;
	int semid, j;

	if (argc != 2 || strcmp(argv[1], "--help") == 0)
	{
		CHECK_RET(-1, "Usage: %s semdid", argv[0]);
	}

	semid = atoi(argv[1]);
	arg.buf = &ds;

	int ret = semctl(semid, 0, IPC_STAT, arg);
	CHECK_RET(ret, "semctl");
	
	printf("Semphore changed: %s\n", ctime(&ds.sem_ctime));
	printf("Last semop(): %s\n", ctime(&ds.sem_otime));

	arg.array = calloc(ds.sem_nsems, sizeof(arg.array[0]));
	CHECK_NULL(arg.array, "calloc");

	ret = semctl(semid, 0, GETALL, arg);
	CHECK_RET(ret, "semctl");
	
	printf("sem#\tvalue\tsempid\tsemncnt\tsemzcnt\n");
	for (j = 0; j < ds.sem_nsems; j++)
	{
		printf("%d\t%d\t%d\t%d\t%d\n", j, arg.array[j], 
				semctl(semid, j, GETPID, dummy),
				semctl(semid, j, GETNCNT, dummy),
				semctl(semid, j, GETZCNT, dummy)
				);
	}

	return 0;
}
