/**************************************************************************
 *
 *	@file		:			comm_thread.c
 * 	@brief		:		通用线程编程接口
 * 	@author		:		sjc	
 *	@date		:		2016年5月3日15:00:01	
 *	@note		:			

**************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#include "comm_thread.h"


/***********************************************************************************
*
* 	@func name	:	comm_thread_create
*	@brief		:	创建线程
*	@param		:	thread: pthread_t类型的线程ID
					pAttr: 线程属性，为空时采用默认的属性配置
					func: 线程的运行函数的起始地址
					param: 运行函数的参数，一般为NULL
*	@return		:	成功返回0，失败返回-1
*	@author		:	sjc
*	@date		:	2016年5月3日15:01:16
*	@modify		:	         
*	@note		:
*	@example	:	comm_thread_create(&thr_id, NULL, &run_thr, NULL)
*	
**********************************************************************************/
int comm_thread_create(pthread_t *thread, pthread_attr_t *pAttr, thread_func func, void *param)
{
	pthread_attr_t thread_attr;         //定义线程属性:scope属性,detach属性,堆栈地址,堆栈大小,优先级
	pthread_attr_init(&thread_attr);     //对线程属性变量进行初始化

	/*属性不为空时*/
	if(pAttr != NULL)
	{
		
		struct sched_param param;

		/*设置线程的scope属性*/
		pthread_attr_setscope(&thread_attr, PTHREAD_SCOPE_SYSTEM);   //与系统中所有线程一起竞争cpu时间

		/*设置调度策略: 为SCHED_FIFO时优先级的设置才有效*/
		pthread_attr_setschedpolicy(&thread_attr, SCHED_FIFO);

		/*设置线程的优先级*/
		param.sched_priority = 99;    //默认为0
		pthread_attr_setschedparam(&thread_attr, &param);
        //pthread_attr_setinheritsched(&thread_attr, PTHREAD_EXPLICIT_SCHED); //使优先级生效
	}

	/* 设置线程为分离模式 ,这种模式下不能用pthread_join来同步*/
	pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);   //退出时自行释放所占资源

	/* 设置线程栈大小1MB */
	pthread_attr_setstacksize(&thread_attr, 1*1024*1024);  

	/*线程创建函数:线程ID,属性, 线程函数,线程参数*/
	int ret = pthread_create(thread, &thread_attr, func, param);
	if(ret != 0)
	{
		/*销毁设置好的线程属性*/
		pthread_attr_destroy(&thread_attr);
	}

	return ret;
}

/***********************************************************************************
*
* 	@func name	:	comm_thread_create_with_largestack
*	@brief		:	创建大栈线程
*	@param		:	thread: pthread_t类型的线程ID
					pAttr: 线程属性，为空时采用默认的属性配置
					func: 线程的运行函数的起始地址
					param: 运行函数的参数，一般为NULL
*	@return		:	成功返回0，失败返回-1
*	@author		:	sjc
*	@date		:	2016年5月3日15:01:16
*	@modify		:	         
*	@note		:
*	
**********************************************************************************/
int comm_thread_create_with_largestack(pthread_t *thread, pthread_attr_t *pAttr, thread_func func, void *param)
{
    pthread_attr_t thread_attr;
    pthread_attr_init(&thread_attr);

    if(pAttr != NULL)
    {
        struct sched_param param;
        pthread_attr_setscope(&thread_attr, PTHREAD_SCOPE_SYSTEM);
        pthread_attr_setschedpolicy(&thread_attr, SCHED_FIFO);
        
        param.sched_priority = 99;
        pthread_attr_setschedparam(&thread_attr, &param);
    }

    /* 设置线程为分离模式 */
    pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);

    /* 设置线程栈大小8MB */
    pthread_attr_setstacksize(&thread_attr, 8*1024*1024);  
    
    int ret = pthread_create(thread, &thread_attr, func, param);
    if(ret != 0)
    {
        pthread_attr_destroy(&thread_attr);
    }
    
    return ret;
}



/***********************************************************************************
*
* 	@func name	:	comm_thread_cancle
*	@brief		:	线程取消
*	@param		:	handle: 要取消的线程的线程ID
*	@return		:	0--成功，-1--失败
*	@author		:	sjc
*	@date		:	2016年5月3日15:01:16
*	@modify		:	         
*	@note		:	发送终止信号给线程，发送成功并不意味着
					线程会终止(使用的少)
*	
**********************************************************************************/
int comm_thread_cancel(pthread_t handle)
{
	int ret = 0;

	ret = pthread_cancel(handle);

	return ret;
}



/***********************************************************************************
*
* 	@func name	:	comm_thread_exit
*	@brief		:	线程退出
*	@param		:	无
*	@return		:	
*	@author		:	sjc
*	@date		:	2016年5月3日15:01:16
*	@modify		:	         
*	@note		:	用pthread_exit()来调用线程的返回值，用来退出
					线程，但是退出线程所占的资源不会得到释放
*	
**********************************************************************************/
int comm_thread_exit()
{
	pthread_exit(0);

	return 0;
}


/***********************************************************************************
*
* 	@func name	:	comm_thread_mutex_init
*	@brief		:	创建互斥锁
*	@param		:	mutex: pthread_t类型的锁
					attr: 锁的属性，为空时采用默认的属性配置
*	@return		:	成功返回0，失败返回-1
*	@author		:	sjc
*	@date		:	2016年5月3日15:01:16
*	@modify		:	         
*	@note		:
*	
**********************************************************************************/
int comm_thread_mutex_init(pthread_mutex_t *mutex, void *attr)
{
	return pthread_mutex_init(mutex, attr);
}

/**
 * @fn          comm_thread_mutex_destroy
 * @brief       init thread mutex
 * @param[in]   none
 * @param[out]  none
 * @return      
 */
int comm_thread_mutex_destroy(pthread_mutex_t *mutex)
{
    return pthread_mutex_destroy(mutex);
}

/**
 * @fn          comm_thread_mutex_trylock
 * @brief       trylock thread mutex ------ used to test
 * @param[in]   none
 * @param[out]  none
 * @return      
 */
int comm_thread_mutex_trylock(pthread_mutex_t *m, const char *functionName)
{
    int nCnt = 0;
    int ret = 0;

    if(m)
    {
        while(pthread_mutex_trylock(m))
        {
            usleep(1000000/30);
            nCnt++;
            if(nCnt >= 10*30)
            {
                printf("[%s: %d] " "%s thread_mutex_lock\n", __FILE__, __LINE__, functionName);
                nCnt = 0;

                ret = -1;
                break;
            }        
        }
    }

    return ret;
}

/**
 * @fn          comm_thread_mutex_lock
 * @brief       init thread mutex
 * @param[in]   none
 * @param[out]  none
 * @return      
 */
int comm_thread_mutex_lock(pthread_mutex_t *m)
{
    int ret = 0;

    if(m)
    {
        ret = pthread_mutex_lock(m);
    }

    return ret;
}

/**
 * @fn          comm_thread_mutex_unlock
 * @brief       init thread mutex
 * @param[in]   none
 * @param[out]  none
 * @return      
 */
int comm_thread_mutex_unlock(pthread_mutex_t *m)
{
    int ret = 0;

    if(m)
    {
        ret = pthread_mutex_unlock(m);
    }

    return ret;
}

/**
 * @fn          comm_thread_cond_init
 * @brief      
 * @param[in]   none
 * @param[out]  none
 * @return      
 */
int comm_thread_cond_init(pthread_cond_t *c, void *attr)
{
    return pthread_cond_init(c, attr);
}

/**
 * @fn          comm_thread_cond_destroy
 * @brief       
 * @param[in]   none
 * @param[out]  none
 * @return      
 */
int comm_thread_cond_destroy(pthread_cond_t *c)
{
    int ret = 0;

    if(c)
    {
        ret = pthread_cond_destroy(c);
    }

    return ret;
}

/**
 * @fn          comm_thread_cond_signal
 * @brief       
 * @param[in]   none
 * @param[out]  none
 * @return      
 */
int comm_thread_cond_signal(pthread_cond_t *c)
{
    int ret = 0;

    if(c)
    {
        ret = pthread_cond_signal(c);
    }
    return ret;
}

/**
 * @fn          comm_thread_cond_outtime_wait
 * @brief       
 * @param[in]   none
 * @param[out]  none
 * @return      
 */
int comm_thread_cond_outtime_wait(pthread_cond_t *c, pthread_mutex_t *m, long nsecond, char *functionName)
{
    int ret = -1;
    struct timespec ts;

    ts.tv_sec = time(NULL) + nsecond;
    ts.tv_nsec = 0;

    if(c)
    {
        ret = pthread_cond_timedwait(c, m, &ts);
        if(ret)
        {
            printf("[%s: %d] " "%s thread_cond_outtime_wait\n", __FILE__, __LINE__, functionName);
        }
    }

    return ret;
}

/**
 * @fn          comm_thread_cond_wait
 * @brief       
 * @param[in]   none
 * @param[out]  none
 * @return      
 */
int comm_thread_cond_wait(pthread_cond_t *c, pthread_mutex_t *m)
{
    int ret = 0;

    if(c)
    {
        ret = pthread_cond_wait(c, m);
    }

    return ret;
}


#ifdef __cplusplus
}
#endif  /* __cplusplus */

