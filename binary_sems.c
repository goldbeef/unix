/*************************************************************************
    > File Name: binary_sems.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月20日 星期日 09时02分15秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"
#include "binary_sems.h"

int isUseSemUndo = 0;
int isRetryOnErrByIntr = 1;

int initSemAvaliable(int semid, int semnum)
{
	union semun arg;
	arg.val = 1;
	return semctl(semid, semnum, SETVAL, arg);
}

int initSemInUse(int semid, int semnum)
{
	union semun arg;
	arg.val = 0;
	return semctl(semid, semnum, SETVAL, arg);

}

int reserveSem(int semid, int semnum)
{
	struct sembuf ops;
	ops.sem_num = semnum;
	ops.sem_op= -1;
	ops.sem_flg = isUseSemUndo ? SEM_UNDO : 0;

	while (semop(semid, &ops, 1) == -1)
	{
		if (errno != EINTR || !isRetryOnErrByIntr)
		{
			return -1;
		}
	}

	return 0;
}


int releaseSem(int semid, int semnum)
{
	struct sembuf ops;
	ops.sem_num = semnum;
	ops.sem_op= 1;
	ops.sem_flg = isUseSemUndo ? SEM_UNDO : 0;
	
	return semop(semid, &ops, 1);
}
	

