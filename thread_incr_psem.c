/*************************************************************************
    > File Name: thread_incr_psem.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月26日 星期六 16时34分36秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

static int glob = 0;
static sem_t sem;

void* threadRountine(void* arg)
{
	int loops = (int)arg;

	int i = 0;
	int ret; 
	for (i = 0; i < loops; i++)
	{
		ret = sem_wait(&sem);
		CHECK_THREAD_RET(ret, "sem_wait");
		
		glob++;

		ret = sem_post(&sem);
		CHECK_THREAD_RET(ret, "sem_post");
	}

	return NULL;
}


int main(int argc, char *argv[])
{
	int ret;
	if (argc != 2 || strcmp(argv[1], "--help") == 0)
	{
		CHECK_RET(-1, "Usage: %s loop-num", argv[0]);
	}

	ret = sem_init(&sem, 0, 1);
	CHECK_RET(ret, "sem_init");

	int loopNum = atoi(argv[1]);

	pthread_t tids[2];
	int i = 0;
	for (i = 0; i < 2; i++)
	{
		ret = pthread_create(&tids[i], NULL, threadRountine, (void*)loopNum);
		CHECK_RET(ret, "pthread_create");
	}


	for (i = 0; i < 2; i++)
	{
		ret = pthread_join(tids[i], NULL);
		CHECK_RET(ret, "pthread_join");
	}
	
	printf("mainThread, glob[%d]\n", glob);

	return 0;
}
