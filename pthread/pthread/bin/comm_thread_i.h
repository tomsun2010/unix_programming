/**************************************************************************
 *
 *	@file		:			comm_thread_i.h
 * 	@brief		:			线程操作接口
 * 	@author		:			sun_jichuan
 *	@date		:			2014-12-02
 *	@note		:			

**************************************************************************/
#ifndef __COMM_THREAD_I_H
#define __COMM_THREAD_I_H

#ifdef __cplusplus
extern "C" {
#endif


typedef void* (*thread_func)(void *param);
typedef void (*thread_cleanup)(void*);


/*******************************************************************************************
*
* 	@func name	:	comm_thread_create
*	@brief		:	
*	@param		:	
*	@return		:	
*	@author		:	sjc
*	@date		:	2016年5月3日15:03:03
*	@modify		:	         
*	@note		:		
*	
******************************************************************************************/
int comm_thread_create(pthread_t *thread, pthread_attr_t *pAttr, thread_func func, void *param);




/*******************************************************************************************
*
* 	@func name	:	comm_thread_create_with_largestack
*	@brief		:	
*	@param		:	
*	@return		:	
*	@author		:	sjc
*	@date		:	2016年5月3日15:03:13
*	@modify		:	         
*	@note		:		
*	
******************************************************************************************/
int comm_thread_create_with_largestack(pthread_t *thread, pthread_attr_t *pAttr, thread_func func, void *param);
int comm_thread_cancel(pthread_t handle);
int comm_thread_exit();
int comm_thread_mutex_init(pthread_mutex_t *mutex, void *attr);
int comm_thread_mutex_destroy(pthread_mutex_t *mutex);
int comm_thread_mutex_trylock(pthread_mutex_t *m, const char *functionName);
int comm_thread_mutex_lock(pthread_mutex_t *m);
int comm_thread_mutex_unlock(pthread_mutex_t *m);
int comm_thread_cond_init(pthread_cond_t *c, void *attr);
int comm_thread_cond_destroy(pthread_cond_t *c);
int comm_thread_cond_signal(pthread_cond_t *c);
int comm_thread_cond_outtime_wait(pthread_cond_t *c, pthread_mutex_t *m, long nsecond, char *functionName);
int comm_thread_cond_wait(pthread_cond_t *c, pthread_mutex_t *m);


#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif 


