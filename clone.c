/*************************************************************************
    > File Name: clone.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年06月30日 星期五 22时28分46秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h" 

#define CHILD_SIG SIGUSR1

int childFunc(void *arg)
{
    int ret;
    ret = close(*((int*)arg));
    CHECK_RET(ret, "close");
    
    return ret;
}

int main(int argc, char* argv[])
{
    int ret;
    const int STACK_SIZE = 1024*1024;
    char* stack;
    char* stackTop;
    int s, fd, flags;

    //flags = (argc > 1) ? CLONE_FILES : 0;
    flags = (argc > 1) ?  0x00000400 : 0;

    stack = malloc(STACK_SIZE);
    CHECK_NULL(stack, "malloc");

    stackTop = stack + STACK_SIZE;

    fd = open("/dev/null", O_RDWR);
    CHECK_RET(fd, "open");

    ret = clone(childFunc, stackTop, flags, (void*)&fd);
    CHECK_RET(ret, "clone");

    ret = waitpid(-1, NULL, __WCLONE);
    CHECK_RET(ret, "waitpid");

    s = write(fd, "x", 1);
    CHECK_RET(s, "write");

    return 0;

}
