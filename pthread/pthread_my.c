/************************************
 * File name   : pthread_my.c
 * Author      : SJC
 * Description : 线程的创建，用信号量进行IPC

 * Date        : 2016-8-17 10:07:34
 * Modification:
 *
 * Makefile    : gcc -o pthread_my pthread_my.c -lpthread
***************************************************/

#ifdef __cplusplus
    extern "C" {
#endif  /* __cplusplus */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#include <semaphore.h>
#include <assert.h>


//static pthread_mutex_t g_myMtx = PTHREAD_MUTEX_INITIALIZER; //定义并初始化互斥锁
static sem_t sem_my;   //定义信号量

static void* my_thr(void *p)
{
    pthread_detach(pthread_self());  //改变线程状态为:unjoinable
    while(1)
    {
        sem_wait(&sem_my);
		printf("hello!!!!\n");
	}
	
	pthread_exit(0);    //线程结束，资源回收
    return NULL;
}

int my_thread1_init()
{
	int ret = -1;
	pthread_t tid;
    pthread_attr_t attr;
    //struct sched_param param;
    
    pthread_attr_init(&attr);
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_attr_setstacksize(&attr, 1*1024*1024); 
	
	/*
    ret = pthread_attr_setschedpolicy(&attr, SCHED_FIFO);  
    if(0 != ret)
    {  
		printf("2222\n");
		goto EXIT0;
    }  
    param.sched_priority = 3;    
    ret = pthread_attr_setschedparam(&attr,&param);  
    if(0 != ret)
    {  
		printf("3333\n");
        goto EXIT0;
    }
	*/
	
    ret = pthread_create(&tid, &attr, (void *)my_thr, NULL);
    if(0 != ret)
    {
		printf("4444\n");
        goto EXIT0;
    }
	
	
	ret = 0;
	
EXIT0:
	//printf("7777\n");
	pthread_attr_destroy(&attr);
    return ret;
	
}

int main(void)
{
    int ret = -1;
	sem_init(&sem_my, 0, 0);
	
	ret = my_thread1_init();
	if (0 != ret)
	{
		printf("my_thread1_init fail!\n");
		goto EXIT0;
	}
	
	while(1)
	{
		sleep(3);
		sem_post(&sem_my);
	}

EXIT0:
	printf("5555\n");
	sem_destroy(&sem_my);
    return ret;
}

#ifdef __cplusplus
}
#endif  /* __cplusplus */

