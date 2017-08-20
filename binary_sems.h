/*************************************************************************
    > File Name: binary_sems.h
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月20日 星期日 08时57分36秒
 ************************************************************************/

#ifndef __BINARY_SEMS_H
#define __BINARY_SEMS_H 

#include "all_def.h"

union semun 
{
   int		val;	/* Value for SETVAL */
   struct semid_ds *buf;	/* Buffer for IPC_STAT, IPC_SET */
   unsigned short  *array;	/* Array for GETALL, SETALL */
   struct seminfo  *__buf;	/* Buffer for IPC_INFO
			   (Linux-specific) */
};

extern int isUseSemUndo;
extern int isRetryOnErrByIntr;

int initSemAvaliable(int semid, int semnum);
int initSemInUse(int semid, int semnum);
int reserveSem(int semid, int semnum);
int releaseSem(int semid, int semnum);


#endif /* ifndef __BINARY_SEMS_H */
