/*************************************************************************
    > File Name: svshm_xfr_reader.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月20日 星期日 10时23分18秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"
#include "svshm_xfr.h"

int main(int argc, char *argv[])
{
	int semid, shmid, bytes, xfrs;
	struct shmseg* pShmseg;
	int ret;
	semid = semget(SEM_KEY, 0, 0);
	CHECK_RET(semid, "semget");

	shmid = shmget(SHM_KEY, 0, 0);
	CHECK_RET(shmid, "shmget");

	pShmseg = shmat(shmid, NULL, SHM_RDONLY);
	CHECK_RET((int)pShmseg, "shmat");

	for (xfrs = 0, bytes = 0; ; xfrs++)
	{
		ret = reserveSem(semid, READ_SEM);
		CHECK_RET(ret, "reserveSem");

		if (pShmseg->cnt == 0)
		{
			//eof 
			break;
		}
		bytes += pShmseg->cnt;

		ret  = write(STDOUT_FILENO, pShmseg->buf, pShmseg->cnt);
		CHECK_RET(ret, "write");

		ret = releaseSem(semid, WRITE_SEM);
		CHECK_RET(ret, "releaseSem");
	}

	ret = shmdt(pShmseg);
	CHECK_RET(ret, "shmdt");

	//give writer one more ture, so it can clean up 
	//important 
	ret = releaseSem(semid, WRITE_SEM);
	CHECK_RET(ret, "releaseSem");
	
	printf("read %d bytes in %d times\n", bytes, xfrs);
	return 0;
}

