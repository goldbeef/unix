/*************************************************************************
    > File Name: file_io.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年05月17日 星期三 21时25分23秒
 ************************************************************************/

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
              
int main()
{
    /*
    char buff[1024];
    int ret = read(STDIN_FILENO, buff, sizeof(buff) - 1);
    if (ret > 0)
    { 
        buff[ret] = '\0';
        printf("byte[%d], buff[%s]\n", ret, buff);
    }*/

    int fd = open("./file_with_hole", O_WRONLY);
    if (fd < 0)
    {
        printf("open file error \n");
        return -1;
    }

    int offset = lseek(fd, 100000000, SEEK_END);
    if (offset == -1)
    {
        printf("lseek error\n");
        return -1;
    }

    char buff[1024] = "hello world";
    int ret = write(fd, buff, strlen(buff));
    if (ret < 0)
    {
        printf("write error\n");
        return -1;
    }

    return 0;
}
