/**************************************************************************
 *
 *	@file		:			comm_thread.c
 * 	@brief		:		ͨ���̱߳�̽ӿ�
 * 	@author		:		sjc	
 *	@date		:		2016��5��3��15:00:01	
 *	@note		:			

**************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#include "comm_thread.h"


/***********************************************************************************
*
* 	@func name	:	comm_thread_create
*	@brief		:	�����߳�
*	@param		:	thread: pthread_t���͵��߳�ID
					pAttr: �߳����ԣ�Ϊ��ʱ����Ĭ�ϵ���������
					func: �̵߳����к�������ʼ��ַ
					param: ���к����Ĳ�����һ��ΪNULL
*	@return		:	�ɹ�����0��ʧ�ܷ���-1
*	@author		:	sjc
*	@date		:	2016��5��3��15:01:16
*	@modify		:	         
*	@note		:
*	@example	:	comm_thread_create(&thr_id, NULL, &run_thr, NULL)
*	
**********************************************************************************/
int comm_thread_create(pthread_t *thread, pthread_attr_t *pAttr, thread_func func, void *param)
{
	pthread_attr_t thread_attr;         //�����߳�����:scope����,detach����,��ջ��ַ,��ջ��С,���ȼ�
	pthread_attr_init(&thread_attr);     //���߳����Ա������г�ʼ��

	/*���Բ�Ϊ��ʱ*/
	if(pAttr != NULL)
	{
		
		struct sched_param param;

		/*�����̵߳�scope����*/
		pthread_attr_setscope(&thread_attr, PTHREAD_SCOPE_SYSTEM);   //��ϵͳ�������߳�һ����cpuʱ��

		/*���õ��Ȳ���: ΪSCHED_FIFOʱ���ȼ������ò���Ч*/
		pthread_attr_setschedpolicy(&thread_attr, SCHED_FIFO);

		/*�����̵߳����ȼ�*/
		param.sched_priority = 99;    //Ĭ��Ϊ0
		pthread_attr_setschedparam(&thread_attr, &param);
        //pthread_attr_setinheritsched(&thread_attr, PTHREAD_EXPLICIT_SCHED); //ʹ���ȼ���Ч
	}

	/* �����߳�Ϊ����ģʽ ,����ģʽ�²�����pthread_join��ͬ��*/
	pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);   //�˳�ʱ�����ͷ���ռ��Դ

	/* �����߳�ջ��С1MB */
	pthread_attr_setstacksize(&thread_attr, 1*1024*1024);  

	/*�̴߳�������:�߳�ID,����, �̺߳���,�̲߳���*/
	int ret = pthread_create(thread, &thread_attr, func, param);
	if(ret != 0)
	{
		/*�������úõ��߳�����*/
		pthread_attr_destroy(&thread_attr);
	}

	return ret;
}

/***********************************************************************************
*
* 	@func name	:	comm_thread_create_with_largestack
*	@brief		:	������ջ�߳�
*	@param		:	thread: pthread_t���͵��߳�ID
					pAttr: �߳����ԣ�Ϊ��ʱ����Ĭ�ϵ���������
					func: �̵߳����к�������ʼ��ַ
					param: ���к����Ĳ�����һ��ΪNULL
*	@return		:	�ɹ�����0��ʧ�ܷ���-1
*	@author		:	sjc
*	@date		:	2016��5��3��15:01:16
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

    /* �����߳�Ϊ����ģʽ */
    pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);

    /* �����߳�ջ��С8MB */
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
*	@brief		:	�߳�ȡ��
*	@param		:	handle: Ҫȡ�����̵߳��߳�ID
*	@return		:	0--�ɹ���-1--ʧ��
*	@author		:	sjc
*	@date		:	2016��5��3��15:01:16
*	@modify		:	         
*	@note		:	������ֹ�źŸ��̣߳����ͳɹ�������ζ��
					�̻߳���ֹ(ʹ�õ���)
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
*	@brief		:	�߳��˳�
*	@param		:	��
*	@return		:	
*	@author		:	sjc
*	@date		:	2016��5��3��15:01:16
*	@modify		:	         
*	@note		:	��pthread_exit()�������̵߳ķ���ֵ�������˳�
					�̣߳������˳��߳���ռ����Դ����õ��ͷ�
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
*	@brief		:	����������
*	@param		:	mutex: pthread_t���͵���
					attr: �������ԣ�Ϊ��ʱ����Ĭ�ϵ���������
*	@return		:	�ɹ�����0��ʧ�ܷ���-1
*	@author		:	sjc
*	@date		:	2016��5��3��15:01:16
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

