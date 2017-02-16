/************************************
 * File name   : pipe.c
 * Author      : SJC
 * Description : ���ùܵ������̼߳�ͨ��
 *             ��#include <unistd.h>
                 int pipe(int fd[2]);    
				 //fd[0]--���ˣ�fd[1]--д��
 * Date        : 2016-8-16 10:57:49
 * Modification:
 * 
 * Makefile    ��gcc -o pipe_thread pipe_thread.c -lpthread
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
        pthread_create(&tid, NULL, func, &fd[1]);  //д����Ϊ��������д��д
        pthread_join(tid, NULL);                   //�������ķ�ʽ�ȴ��߳̽��� 
  
        //sleep(3);  
  
        // read buf from child thread  
        read( fd[0], readbuf, sizeof(readbuf) );  //�Ӷ��˶�ȡ����
        printf("read buf = %s\n", readbuf);  
  
        return 0;  
}  