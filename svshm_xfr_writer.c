/*************************************************************************
    > File Name: svshm_xfr_writer.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月20日 星期日 09时51分12秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"
#include "svshm_xfr.h"

int main(int argc, char *argv[])
{
	int semid, shmid, bytes, xfrs;
	struct shmseg* pShmseg;
	union semun dummy;
	int ret;

	semid = semget(SEM_KEY, 2, IPC_CREAT|OBJ_PERM);
	CHECK_RET(semid, "semget");
	ret = initSemAvaliable(semid, WRITE_SEM);
	CHECK_RET(ret, "initSemAvaliable");
	ret = initSemInUse(semid, READ_SEM);
	CHECK_RET(ret, "initSemInUse");

	shmid = shmget(SHM_KEY, sizeof(struct shmseg), IPC_CREAT|OBJ_PERM);
	CHECK_RET(shmid, "shmget");

	pShmseg = shmat(shmid, NULL, 0);
	CHECK_RET((int)pShmseg, "shmat");

	for (xfrs = 0, bytes = 0; ; xfrs++, bytes += pShmseg->cnt)
	{
		ret = reserveSem(semid, WRITE_SEM);
		CHECK_RET(ret, "reserveSem");

		pShmseg->cnt = read(STDIN_FILENO, pShmseg->buf, MAX_BUFF_SIZE);
		CHECK_RET(pShmseg->cnt, "read");

		ret = releaseSem(semid, READ_SEM);
		CHECK_RET(ret, "releaseSem");

		if (pShmseg->cnt == 0)
		{
			//eof 
			break;
		}
	}

	ret = reserveSem(semid, WRITE_SEM);
	CHECK_RET(ret, "reserveSem");
	ret = semctl(semid, 0, IPC_RMID, dummy);
	CHECK_RET(ret, "semctl");

	ret = shmdt(pShmseg);
	CHECK_RET(ret, "shmdt");
	ret = shmctl(shmid, IPC_RMID, 0);
	CHECK_RET(ret, "shmdt");

	printf("send %d bytes by %d times\n", bytes, xfrs);
	return 0;
}

