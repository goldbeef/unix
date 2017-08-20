/*************************************************************************
    > File Name: check.h
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年06月21日 星期三 20时01分10秒
 ************************************************************************/
#ifndef __CHECK__
#define __CHECK__

#include <stdio.h>
#include <pthread.h>

#define CHECK_RET(ret, format, args...)                                             \
    do                                                                              \
    {                                                                               \
        if (ret == -1)                                                               \
        {                                                                           \
            printf("(%s:%d) ret[%d] "format"\n", __FILE__, __LINE__, ret, ##args);  \
            return ret;                                                             \
        }                                                                           \
    }                                                                               \
    while(0);


#define CHECK_RET_VOID(ret, format, args...)                                             \
    do                                                                              \
    {                                                                               \
        if (ret == -1)                                                               \
        {                                                                           \
            printf("(%s:%d) ret[%d] "format"\n", __FILE__, __LINE__, ret, ##args);  \
            return;                                                             \
        }                                                                           \
    }                                                                               \
    while(0);


#define CHECK_THREAD_RET(ret, format, args...)                                             \
    do                                                                              \
    {                                                                               \
        if (ret != 0)                                                               \
        {                                                                           \
            printf("(%s:%d) ret[%d] "format"\n", __FILE__, __LINE__, ret, ##args);  \
            pthread_exit((void*) ret);                                                             \
        }                                                                           \
    }                                                                               \
    while(0);

#define CHECK_NULL(ptr, format, args...)                                                    \
    do                                                                                      \
    {                                                                                       \
        if (ptr == NULL)                                                                    \
        {                                                                                   \
            printf("(%s:%d) ptr[%s] NULL, "format"\n", __FILE__, __LINE__, #ptr, ##args);   \
            return -1;                                                                      \
        }                                                                                   \
    }                                                                                       \
    while(0);

#define CHECK_NULL_VOID(ptr, format, args...)                                                    \
    do                                                                                      \
    {                                                                                       \
        if (ptr == NULL)                                                                    \
        {                                                                                   \
            printf("(%s:%d) ptr[%s] NULL, "format"\n", __FILE__, __LINE__, #ptr, ##args);   \
            return ;                                                                      \
        }                                                                                   \
    }                                                                                       \
    while(0);

#endif
