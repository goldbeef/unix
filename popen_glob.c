/*************************************************************************
    > File Name: popen_glob.c
    > Author: goldbeef
    > Mail: goldbeef@163.com 
    > Created Time: 2017年08月12日 星期六 09时48分26秒
 ************************************************************************/

#include <stdio.h>
#include "all_def.h"

#define POPEN_FMT "/bin/ls -d %s 2>/dev/null"
#define POPEN_FMT_SLEEP "/bin/sleep 1024 2>/dev/null"
#define PAT_SIZE 20
#define PCMD_BUF_SIZE (sizeof(POPEN_FMT) + PAT_SIZE)
#define PATH_MAX 1024

int main()
{
    char pat[PAT_SIZE];
    char popenCmd[PCMD_BUF_SIZE];
    FILE* fp = NULL;
    int badPattern = 0;
    int len, status, fileCnt, i;
    char pathname[PATH_MAX];
    void* ptr = NULL;

    while (1)
    {
        printf("pattern: ");
        fflush(stdout);
    
        ptr = fgets(pat, PAT_SIZE, stdin);
        CHECK_NULL(ptr, "fgets");
        len = strlen(pat);
        if (len <= 1)
        {
            continue;
        }

        if (pat[len - 1] == '\n')
        {
            pat[len - 1] = '\0';
        }

        for (i = 0, badPattern = 0; i < len && !badPattern; i++)
        {
            if ( !isalnum(pat[i]) &&  strchr("_*?[^-].", pat[i]) == NULL )
            {
                badPattern = 1;
            }
        }

        if (badPattern)
        {
            printf("Bad pattern character: %c\n", pat[i]);
            continue;
        }
        
        //build and execute command to glob 
        //snprintf(popenCmd, PCMD_BUF_SIZE, POPEN_FMT, pat);
        snprintf(popenCmd, PCMD_BUF_SIZE, POPEN_FMT_SLEEP);
        popenCmd[PCMD_BUF_SIZE - 1] = '\0';
        
        fp = popen(popenCmd, "r");
        if (fp == NULL)
        {
            printf("popen error\n");
            continue;
        }

        fileCnt = 0;
        while (fgets(pathname, PATH_MAX, fp) != NULL)
        {
            printf("%s ", pathname);
            fileCnt++;
        }

        status = pclose(fp);
        printf("match fileNum[%d], status[%d]\n", fileCnt, status);
    }

    return 0;
}

