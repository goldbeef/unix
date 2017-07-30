/*************************************************************************
    > File Name: sv_v1.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年07月29日 星期六 16时32分43秒
 ************************************************************************/

#include <stdio.h>

__asm__(".symver xyz_old, xyz@VER_1");
__asm__(".symver xyz_new, xyz@@VER_2");

void xyz_old()
{
    printf("v1 xyz\n");
}

void xyz_new()
{
    printf("v2 xyz\n");
}

void pqr(void)
{
    printf("v2 pqr\n");
}
