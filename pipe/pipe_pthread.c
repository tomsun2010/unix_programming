/************************************
 * File name   : pipe.c
 * Author      : SJC
 * Description : 利用管道进行线程间通信
 *             ：#include <unistd.h>
                 int pipe(int fd[2]);    
				 //fd[0]--读端；fd[1]--写端
 * Date        : 2016-8-16 10:57:49
 * Modification:
 * 
 * Makefile    ：gcc -o pipe_thread pipe_thread.c -lpthread
***************************************************/

#include <stdio.h>  // printf  
#include <stdlib.h> // exit  
#include <unistd.h> // pipe  
#include <string.h> // strlen  
#include <pthread.h> // pthread_create  

void *func(void * fd)  
{  
        printf("write fd = %d\n", *(int*)fd);  
        char str[] = "hello everyone!";  
        write( *(int*)fd, str, strlen(str) );  
}  
  
int main()  
{  
        int fd[2];  
        char readbuf[1024];  
  
        if(pipe(fd) < 0)  
        {  
            printf("pipe error!\n");  
        }  
  
        // create a new thread  
        pthread_t tid = 0;  
        pthread_create(&tid, NULL, func, &fd[1]);  //写端作为参数，往写端写
        pthread_join(tid, NULL);                   //以阻塞的方式等待线程结束 
  
        //sleep(3);  
  
        // read buf from child thread  
        read( fd[0], readbuf, sizeof(readbuf) );  //从读端读取数据
        printf("read buf = %s\n", readbuf);  
  
        return 0;  
}  