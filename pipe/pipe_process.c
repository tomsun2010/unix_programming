/************************************
 * File name   : pipe_process.c
 * Author      : SJC
 * Description : 利用管道进行进程间通信：父进程关闭写端，子进程关闭读端
 *             ：#include <unistd.h>
                 int pipe(int fd[2]);    
				 //fd[0]--读端；fd[1]--写端
 * Date        : 2016-8-16 10:46:09
 * Modification:
 *
 * Makefile    : gcc -o pipe_process pipe_process.c  
***************************************************/

#include <stdio.h>  // printf  
#include <stdlib.h> // exit  
#include <unistd.h> // pipe  
#include <string.h> // strlen  
  
int main(void)  
{  
        int fd[2];  
        int pid = 0;  
        char str[] = "hello";  
        char readbuf[1024];  
  
        if(pipe(fd) < 0)  
        {  
                printf("pipe error!\n");  
        }  
  
        if((pid = fork()) < 0)  
        {  
                printf("fork error!\n");  
        }  
        else if(pid == 0)  
        {  
                printf("child process!\n");  
  
                // close read channel  
                close(fd[0]);  
                write(fd[1], str, strlen(str));  
        }  
        else  
        {  
                printf("father process!\n");  
  
                // close write channel  
                close(fd[1]);  
                read(fd[0], readbuf, sizeof(readbuf));  
                printf("readbuf = %s\n", readbuf);  
        }  
  
        return 0;  
}  