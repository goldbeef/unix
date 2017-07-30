/*************************************************************************
    > File Name: dynload.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年07月29日 星期六 15时12分04秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

int main(int argc, char* argv[])
{
    void* libHandle;
    typedef void (*FuncPtr) (void);
    const char* err;

    if (argc != 3 || strcmp(argv[1], "--help") == 0)
    {
        CHECK_RET(-1, "Usage: %s lib-path func-name", argv[0]);
    }

    libHandle = dlopen(argv[1], RTLD_LAZY);
    CHECK_NULL(libHandle, "dlopen");

    dlerror(); //clear dlerror 
    FuncPtr funcPtr = (FuncPtr) dlsym(libHandle, argv[2]);
    if (dlerror())
    {
        CHECK_RET(-1, "dlerror");
    }

    if (funcPtr == NULL)
    {
        printf("ptr[%s] is null\n", argv[2]);
    }
    else
    {
        (*funcPtr)();
    }
    
    Dl_info stDlInfo;
    int ret = dladdr(funcPtr, &stDlInfo);

    dlclose(libHandle);
    return 0;
}
