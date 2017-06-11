/*************************************************************************
    > File Name: inotify.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年06月11日 星期日 19时54分55秒
 ************************************************************************/

#include <stdio.h>
#include <sys/inotify.h>

#define NAME_MAX 1024
#define BUFF_LEN  (10*(sizeof(struct inotify_event) + 1024 + 1))

void displayInotifyEvent(struct inotify_event* pNotifyEvent)
{
    printf("wd[%d]\n", pNotifyEvent->wd);
    printf("mask=\n");
    if (pNotifyEvent->mask & IN_ACCESS) printf("IN_ACCESS ");
    if (pNotifyEvent->mask & IN_ATTRIB) printf("IN_ATTRIB ");
    if (pNotifyEvent->mask & IN_CLOSE_NOWRITE) printf("IN_CLOSE_NOWRITE ");
    if (pNotifyEvent->mask & IN_CLOSE_WRITE) printf("IN_CLOSE_WRITE ");
    if (pNotifyEvent->mask & IN_CREATE) printf("IN_CREATE ");
    if (pNotifyEvent->mask & IN_DELETE) printf("IN_DELETE ");
    if (pNotifyEvent->mask & IN_DELETE_SELF) printf("IN_DELETE_SELF ");
    if (pNotifyEvent->mask & IN_IGNORED) printf("IN_IGNORED ");
    if (pNotifyEvent->mask & IN_ISDIR) printf("IN_ISDIR ");
    if (pNotifyEvent->mask & IN_MODIFY) printf("IN_MODIFY ");
    if (pNotifyEvent->mask & IN_MOVE_SELF) printf("IN_MOVE_SELF ");
    if (pNotifyEvent->mask & IN_MOVED_FROM) printf("IN_MOVED_FROM ");
    if (pNotifyEvent->mask & IN_MOVED_TO) printf("IN_MOVED_TO ");
    if (pNotifyEvent->mask & IN_OPEN) printf("IN_OPEN ");
    if (pNotifyEvent->mask & IN_Q_OVERFLOW) printf("IN_Q_OVERFLOW ");
    if (pNotifyEvent->mask & IN_UNMOUNT) printf("IN_UNMOUNT ");
    printf("\n");

    if (pNotifyEvent->len > 0)
    {
        printf("name = %s\n", pNotifyEvent->name);
    }
}

int main(int argc, char* argv[])
{
    int inotifyFd, wd, i;
    char buff[BUFF_LEN];
    ssize_t numRead;
    char *ptr;

    struct inotify_event* pInotifyEvent;
    if (argc < 2)
    {
        printf("Usage: %s pathname ...\n", argv[0]);
        return -1;
    }

    inotifyFd = inotify_init();
    if (inotifyFd < 0)
    {
        printf("inotify_init error]");
        return -1;
    }

    for (i = 1; i < argc; i++)
    {
        wd = inotify_add_watch(inotifyFd, argv[i], IN_ALL_EVENTS);
        if (wd < 0)
        {
            printf("inotify_add_watch fail, path[%s]\n", argv[i]);
            return -1;
        }
    }

    while (1)
    {
        numRead = read(inotifyFd, buff, BUFF_LEN);
        if (numRead < 0)
        {
            printf("read error\n");
            return -1;
        }

        if (numRead == 0)
        {
            printf("read empty\n");
            continue;
        }
        
        for (ptr = buff; ptr < buff + numRead;)
        {
            pInotifyEvent  = (struct inotify_event*) ptr;
            displayInotifyEvent(pInotifyEvent);
            ptr += sizeof(struct inotify_event) + pInotifyEvent->len;
        }
    
    }

    return 0;
}
