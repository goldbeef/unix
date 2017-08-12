/*************************************************************************
    > File Name: all_def.h
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年06月21日 星期三 21时18分44秒
 ************************************************************************/

#ifndef __ALL_DEF__
#define __ALL_DEF__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/signalfd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <libgen.h>
#include <sched.h>
#include <sys/syscall.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>
#include <sys/timerfd.h>
#include <sys/resource.h>
#include <sched.h>
#include <dlfcn.h>
#include <paths.h>
#include <utmpx.h>
#include <ctype.h>
#include <sys/stat.h>

#include "check.h"
#include "signal_function.c"
#include "print_wait_status.c"

#endif
