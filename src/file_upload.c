#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/wait.h>
#include"file_upload.h"

#define FILE_NAME_SIZE 1024

int file_upload(int Argc, char* Argv[], void** Buf)
{
	pid_t pid;
    int pfd[2];
    char *buf = (char*)malloc(FILE_NAME_SIZE);

    char *argv[] = {"./../etc/file/fdfs_upload_file", "./../etc/conf/client.conf", Argv[1], (char*)0};
    char *envp[] = {"./../etc/lib", (char*)0};

    if(Argc < 2)
    {
        printf("File_upload Error!\n");
        return -1;
    }

    if(pipe(pfd) < 0)
    {
        printf("Pipe Error!\n");
        return -1;
    }

	pid = fork();
    if(pid < 0)
    {
        printf("Fork Error!\n");
        return -1;
    }
    else if(pid == 0)
    {
        close(pfd[0]);

        if(dup2(pfd[1], STDOUT_FILENO) < 0)
        {
            printf("Dup2 Error!\n");
            return -1;
        }

        if(execve("./../etc/file/fdfs_upload_file", argv, envp) < 0)
        {
            printf("Exec Error!\n");
            return -1;
        }
    }
    else
    {
        wait(NULL);

        close(pfd[1]);

        read(pfd[0], buf, FILE_NAME_SIZE);

	    *Buf = buf;
    }

    return 0;
}
