/************************************************************
  Copyright (C), 1988-2014, xxxxx Tech. Co., Ltd.
  FileName:
  Author:  wangbin      Version :  1.0        Date:2014-2-8
  Description:      线程相关函数             
  Version:    1.0                    
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/
#include "bc_platform_thread.h"
#include "bc_platform_sem.h"
#include "bc_platform_time.h"
#include "bc_platform_mem.h"
#include "bc_platform_mutex.h"
#include "bc_print.h"
#include "utili_list.h"

#define BC_PLATFORM_THREAD_DEBUG 1

#if BC_PLATFORM_THREAD_DEBUG
static bc_uint32 bc_platform_thread_count_curr;
static bc_uint32 bc_platform_thread_count_max;
static bc_uint32 bc_platform_thread_stack_size_curr;
static bc_uint32 bc_platform_thread_stack_size_max;
#define BC_PLATFORM_THREAD_RESOURCE_USAGE_INCR(a_cnt, a_cnt_max, a_sz,      \
                                       a_sz_max, n_ssize, ilock)    \
    a_cnt++;                                                        \
    a_sz += (n_ssize);                                              \
    a_cnt_max = ((a_cnt) > (a_cnt_max)) ? (a_cnt) : (a_cnt_max);    \
    a_sz_max = ((a_sz) > (a_sz_max)) ? (a_sz) : (a_sz_max)

#define BC_PLATFORM_THREAD_RESOURCE_USAGE_DECR(a_count, a_ssize, n_ssize, ilock)\
        a_count--;                                                      \
        a_ssize -= (n_ssize)

/*
 * Function:
 *      bc_platform_thread_ResourceUsageGet
 * Purpose:
 *      Provides count of active threads and stack allocation
 * Parameters:
 *      alloc_curr - Current memory usage.
 *      alloc_max - Memory usage high water mark
 */
 
void bc_platform_thread_ResourceUsageGet(unsigned int *ktos_thread_count_curr,
                              unsigned int *ktos_stack_size_curr,
                              unsigned int *ktos_thread_count_max,
                              unsigned int *ktos_stack_size_max)
{
    if (ktos_thread_count_curr != NULL) {
        *ktos_thread_count_curr = bc_platform_thread_count_curr;
    }
    if (ktos_stack_size_curr != NULL) {
        *ktos_stack_size_curr = bc_platform_thread_stack_size_curr;
    }
    if (ktos_thread_count_max != NULL) {
        *ktos_thread_count_max = bc_platform_thread_count_max;
    }
    if (ktos_stack_size_max != NULL) {
        *ktos_stack_size_max = bc_platform_thread_stack_size_max;
    }
}

#else
/* Resource tracking disabled */
#define BC_PLATFORM_THREAD_RESOURCE_USAGE_INCR(a_cnt, a_cnt_max, a_sz,      \
                                       a_sz_max, n_ssize, ilock)
#define BC_PLATFORM_THREAD_RESOURCE_USAGE_DECR(a_count, a_ssize, n_ssize, ilock)
#endif

#define BC_PTHREAD_STACK_MIN (16*BC_THREAD_1K_STACK_SIAE) /* min stack 16k*/
#define BC_PTHREAD_STACK_MAX (5*1024*BC_THREAD_1K_STACK_SIAE) /*max stack 5M*/

/*
 * Function:
 *	thread_boot
 * Purpose:
 *	Entry point for each new thread created
 * Parameters:
 *	ti - information about thread being created
 * Notes:
 *	Signals and other parameters are configured before jumping to
 *	the actual thread's main routine.
 */

typedef struct  {
    bc_char		 name[BC_THREAD_MAX_API_NAME];
	bc_thread_t	 id;
	bc_int32     stacksize;
	bc_int32     prio;
	bc_pid_t     tid;
	void		 (*f)(void *);
    void		 *arg;
    bc_sem_t   *sem;
} bc_thread_info_t;


typedef struct 
{
	utili_node 	         utili_node;
	bc_thread_info_t	 data;        
} bc_thread_node_t;


static utili_list bc_platform_thread_head;
static bc_pthread_mutex_t  *bc_platform_thread_mut;

static void *__bc_platform_thread_boot( void *ti_void)
{

    bc_thread_info_t	*ti = ti_void;
    void		(*f)(void *);
    void		*arg;
	
    /* Ensure that we give up all resources upon exit */
    pthread_detach(pthread_self());

#ifndef netbsd
    /* not supported */
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
#endif /* netbsd */

    f = ti->f;
    arg = ti->arg;

    ti->id = pthread_self();
	
	ti->tid = syscall(SYS_gettid);

    /* Notify parent to continue */
    bc_platform_sem_post(ti->sem);

    /* Call thread function */
    (*f)(arg);

    /* Thread function did not call bc_platform_thread_exit() */
    bc_platform_thread_exit(0);

    /* Will never get here */
    return NULL;
}


static bc_int32 __bc_platform_thread_compare(void * node, bc_uint32 key)
{

	bc_thread_info_t *ti = &((bc_thread_node_t *)node)->data;
	if(node == NULL)
	{
		return -1;
	}

	if(ti->id == (bc_thread_t)key)
	{
		return 0;
	}
	else if(ti->id > (bc_thread_t)key)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

 
/*************************************************
  Function: bc_platform_thread_init
  Description:线程结构初始化
  Input: 
  
  Output:
  Return:
  		void
  Note: 用bc_platform_init替代bc_platform_thread_init进行
  初始化
  History: 
*************************************************/
void bc_platform_thread_init(void)
{
	if((bc_platform_thread_mut = bc_platform_mutex_create("ThreadMutex1")) == NULL)
	{
		BC_PT_ERROR(BC_MODULE_PLATFORM,"<%s>:create mutex 1 fail!\n",__FUNCTION__);
		return ;
	}
	
	utili_lst_init(&bc_platform_thread_head,__bc_platform_thread_compare);
}

/*************************************************
  Function: bc_platform_thread_create
  Description:创建一个线程
  Input: 
	  	name : name of task
  		stacksize : stack size requested
  		prio : scheduling prio (1 = lowest,99 =  highest)
  		f:address of function to call
  		arg:argument passed to func
  Output:
  Return:
  		成功:THREAD ID
  		失败:NULL
  Note: 
  History: 
*************************************************/
bc_thread_t *bc_platform_thread_create(
	 bc_char *name,
	 bc_int32 stacksize, 
	 bc_int32 prio, 
	 void (*f)(void *), 
	 void *arg
)
{
    pthread_attr_t	attribs;
	struct sched_param priority_holder;
    bc_thread_info_t	*ti;
	bc_thread_node_t    *thread_node;
    bc_sem_t           *sem;

	if((name == NULL)||(prio<1)||(prio>99)||(f == NULL))
	{
		return NULL;
	}

	if(strlen(name) >= BC_THREAD_MAX_API_NAME)
	{
		BC_PT_ERROR(BC_MODULE_PLATFORM,"thread name is too long\n");
		return NULL;
	}
	
    if (pthread_attr_init(&attribs))
	{
        return NULL;
    }

    if (stacksize < BC_PTHREAD_STACK_MIN)
	{
		stacksize = BC_PTHREAD_STACK_MIN;
	}
	
	if (stacksize > BC_PTHREAD_STACK_MAX)
	{
		stacksize = BC_PTHREAD_STACK_MAX;
	}
	
    pthread_attr_setstacksize(&attribs, stacksize);

    priority_holder.sched_priority = prio;
	pthread_attr_setschedparam(&attribs,&priority_holder);

    if ((thread_node = bc_platform_mem_malloc(BC_MODULE_PLATFORM,sizeof (*thread_node))) == NULL) 
	{
		return NULL;
    }

    if ((sem = bc_platform_sem_create("threadBoot", 0)) == NULL) 
	{
		bc_platform_mem_free(BC_MODULE_PLATFORM,thread_node);
		return NULL;
    }
	
	ti = &thread_node->data;
	strcpy(ti->name,name);
	ti->id = (bc_thread_t)0;
	ti->stacksize = stacksize;
	ti->prio = prio;
    ti->f = f;
    ti->arg = arg;
	ti->tid = (bc_pid_t)0; 
	ti->sem = sem;
	
    if (pthread_create(&(ti->id), &attribs, __bc_platform_thread_boot, (void *)ti))
	{
		bc_platform_mem_free(BC_MODULE_PLATFORM,thread_node);
	    bc_platform_sem_destroy(sem);
		return NULL;
    }
	
	bc_platform_mutex_lock(bc_platform_thread_mut);
	utili_lst_add(&bc_platform_thread_head,(utili_node *)thread_node);

    BC_PLATFORM_THREAD_RESOURCE_USAGE_INCR(
        bc_platform_thread_count_curr,
        bc_platform_thread_count_max,
        bc_platform_thread_stack_size_curr,
        bc_platform_thread_stack_size_max,
        stacksize,
        ilock);
	bc_platform_mutex_unlock(bc_platform_thread_mut);

    /*
     * Note that at this point ti can no longer be safely
     * dereferenced, as the thread we just created may have
     * exited already. Instead we wait for the new thread
     * to update bc_thread_info_t and tell us to continue.
     */
    bc_platform_sem_wait(sem, BC_SEM_WAIT_FOREVER);
    bc_platform_sem_destroy(sem);

    return (bc_thread_t *)(&ti->id);;
}

/*************************************************
  Function: bc_platform_thread_destroy
  Description:destroy a task
  Input: 
	  	thread : thread id
  Output:
  Return:
		成功:BC_ERR_OK 失败:other
  Notes:
 	This routine is not generally used by Broadcom drivers because
 	it's unsafe.  If a task is destroyed while holding a mutex or
 	other resource, system operation becomes unpredictable.  Also,
 	some RTOS's do not include kill routines.
 
 	Instead, Broadcom tasks are written so they can be notified via
 	semaphore when it is time to exit, at which time they call
 	bc_platform_thread_exit().
  History: 
*************************************************/

bc_err_e bc_platform_thread_destroy(bc_thread_t *thread)
{

    bc_thread_info_t	*ti;
    utili_node *node;
	
	bc_platform_mutex_lock(bc_platform_thread_mut);
    if (pthread_cancel(*thread)) 
	{
		bc_platform_mutex_unlock(bc_platform_thread_mut);
		return BC_ERR_PARA;
    }

	node = utili_lst_remove(&bc_platform_thread_head,*thread);
	if(node != NULL)
	{
		ti = &((bc_thread_node_t *)node)->data;
		
        BC_PLATFORM_THREAD_RESOURCE_USAGE_DECR(
	        bc_platform_thread_count_curr,
	        bc_platform_thread_stack_size_curr,
	        ti->stacksize,
	        ilock);
		bc_platform_mem_free(BC_MODULE_PLATFORM,node);
		bc_platform_mutex_unlock(bc_platform_thread_mut);
		return BC_ERR_OK;
	}

	bc_platform_mutex_unlock(bc_platform_thread_mut);
    return BC_ERR_PARA;
}


/*************************************************
  Function: bc_platform_thread_exit
  Description:Exit the calling thread
  Input: 
	  	rc - return code from thread.
  Output:
  Return:
		void
  Notes:
  History: 
*************************************************/
void bc_platform_thread_exit(bc_int32 rc)
{
    bc_thread_info_t	*ti;
	utili_node     *node;
    bc_thread_t		thread = pthread_self();
	
	bc_platform_mutex_lock(bc_platform_thread_mut);
	node = utili_lst_remove(&bc_platform_thread_head,thread);
	if (node != NULL)
	{
		ti = &((bc_thread_node_t *)node)->data;
		
        BC_PLATFORM_THREAD_RESOURCE_USAGE_DECR(
	        bc_platform_thread_count_curr,
	        bc_platform_thread_stack_size_curr,
	        ti->stacksize,
	        ilock);
		bc_platform_mem_free(BC_MODULE_PLATFORM,node);
		bc_platform_mutex_unlock(bc_platform_thread_mut);
		return ;
	}
	bc_platform_mutex_unlock(bc_platform_thread_mut);
	
	pthread_exit(BC_INT_TO_PTR(rc));
	
}


/*************************************************
  Function: bc_platform_thread_id_get
  Description:Return thread ID of caller
  Input: 
  
  Output:
  Return:
		void
  Notes:
  History: 
*************************************************/
bc_thread_t bc_platform_thread_id_get(void)
{
    return (bc_thread_t) pthread_self();
}

/*************************************************
  Function: bc_platform_thread_name_get
  Description:Return name given to thread when it was created
  Input: 
   	thread : thread ID
 	thread_name : buffer to return thread name;
 			gets empty string if not available
 	thread_name_size : maximum size of buffer
  
  Output:
  Return:
		成功:BC_ERR_OK  失败:other
  Notes:
  History: 
*************************************************/
bc_err_e bc_platform_thread_name_get(
	 bc_thread_t *thread,
	 bc_int8 *thread_name,
	 bc_int32  thread_name_size
)
{
    bc_thread_info_t	*ti;
	utili_node     *node;

	if (thread_name_size < BC_THREAD_MAX_API_NAME)
	{
		return BC_ERR_PARA;
	}

	memset(thread_name, 0, thread_name_size);
	
	node = utili_lst_find(&bc_platform_thread_head,*thread);
	if (node != NULL)
	{
		ti = &((bc_thread_node_t *)node)->data;
		memcpy(thread_name, ti->name, BC_THREAD_MAX_API_NAME);
		return BC_ERR_OK;
	}
	
    return BC_ERR_PLATFROM_THREAD_NOT_EXIST;
}

/*************************************************
  Function: bc_platform_thread_stack_get
  Description:Return stack given to thread when it was created
  Input: 
   	thread : thread ID
 	stacksize : stack size
  
  Output:
  Return:
		成功:BC_ERR_OK  失败:other
  Notes:
  History: 
*************************************************/
bc_err_e bc_platform_thread_stack_get(bc_thread_t *thread, bc_int32 *stacksize)
{
    bc_thread_info_t	*ti;
	utili_node     *node;
	
	node = utili_lst_find(&bc_platform_thread_head,*thread);
	if (node != NULL)
	{
		ti = &((bc_thread_node_t *)node)->data;
		*stacksize = ti->stacksize;
		return BC_ERR_OK;
	}
	
    return BC_ERR_PLATFROM_THREAD_NOT_EXIST;
}

/*************************************************
  Function: bc_platform_thread_piro_get
  Description:Return prio given to thread when it was created
  Input: 
   	thread : thread ID
 	pro : pro 
  
  Output:
  Return:
		成功:BC_ERR_OK  失败:other
  Notes:
  History: 
*************************************************/
bc_err_e bc_platform_thread_piro_get(bc_thread_t *thread, bc_int32 *pro)
{
	bc_thread_info_t	*ti;
	utili_node     *node;
	
	node = utili_lst_find(&bc_platform_thread_head,*thread);
	if (node != NULL)
	{
		ti = &((bc_thread_node_t *)node)->data;
		*pro = ti->prio;
		return BC_ERR_OK;
	}

    return BC_ERR_PLATFROM_THREAD_NOT_EXIST;
}

/*************************************************
  Function: bc_platform_thread_tid_get
  Description:Return tid given to thread when it was created
  Input: 
   	thread : thread ID
 	tid :  
  
  Output:
  Return:
		成功:BC_ERR_OK  失败:other
  Notes:
  History: 
*************************************************/
bc_err_e bc_platform_thread_tid_get(bc_thread_t *thread, bc_int32 *tid)
{
	bc_thread_info_t	*ti;
	utili_node     *node;
	
	node = utili_lst_find(&bc_platform_thread_head,*thread);
	if (node != NULL)
	{
		ti = &((bc_thread_node_t *)node)->data;
		*tid = ti->tid;
		return BC_ERR_OK;
	}

    return BC_ERR_PLATFROM_THREAD_NOT_EXIST;
}

/*************************************************
  Function: bc_platform_thread_show
  Description:dump所有 线程信息
  Input: 

  Output:
  Return:
		void
  Notes:
  History: 
*************************************************/
void bc_platform_thread_show(void)
{
 	bc_uint32 i = 1;
	utili_node *predecessor,*next;
	bc_thread_info_t *ti;
    BC_PT_COMMAND(BC_MODULE_PLATFORM,"\r\n=================================================================");
    BC_PT_COMMAND(BC_MODULE_PLATFORM,"\r\n%-4s %-30s %-11s %-12s %-8s","Id", "Name", "Thread ID", "StackSize", "Pri");
    BC_PT_COMMAND(BC_MODULE_PLATFORM,"\r\n-----------------------------------------------------------------");
	
	predecessor = utili_lst_first(&bc_platform_thread_head);
	while(predecessor != NULL)
	{
		ti = &((bc_thread_node_t *)predecessor)->data;
		BC_PT_COMMAND(BC_MODULE_PLATFORM,"\r\n%-4d %-30s %-9d 0x%-10x %-6d",i,ti->name,ti->tid,ti->stacksize,ti->prio);
		next = utili_lst_next((utili_node *)predecessor);
		predecessor = next;
		i++;
	}
	
	#if BC_PLATFORM_THREAD_DEBUG
	BC_PT_COMMAND(BC_MODULE_PLATFORM,"\r\nthread info total[COUNT:%d,MAX:%d,USED STACK:%0.1lfMB,MAX STACK:%0.1lfMB]\n",bc_platform_thread_count_curr,bc_platform_thread_count_max,((float)bc_platform_thread_stack_size_curr)/1024/1024,((float)bc_platform_thread_stack_size_max)/1024/1024);
	#endif
}

/*************************************************
  Function: bc_platform_time_sleep
  Description:Suspend calling thread for a specified number of seconds
  Input: 
  		sec:number of seconds to suspend

  Output:
  Return:
		void
  Notes:Other tasks are free to run while the caller is suspended.
  History: 
*************************************************/

void bc_platform_time_sleep(bc_uint32 sec)
{
    struct timeval tv;
    tv.tv_sec = (time_t) sec;
    tv.tv_usec = 0;
    select(0, (fd_set *) 0, (fd_set *) 0, (fd_set *) 0, &tv);
}

/*************************************************
  Function: bc_platform_time_usleep
  Description:Suspend calling thread for a specified number of microseconds.
  Input: 
  		usec:number of microseconds to suspend

  Output:
  Return:
		void
  Notes:	The actual delay period depends on the resolution of the
 	Unix select routine, whose precision is limited to the
 	the period of the scheduler tick, generally 1/60 or 1/100 sec.
 	Other tasks are free to run while the caller is suspended.
  History: 
*************************************************/
void bc_platform_time_usleep(bc_uint32 usec)
{
    struct timeval tv;

    tv.tv_sec = (time_t) (usec / SECOND_USEC);
    tv.tv_usec = (long) (usec % SECOND_USEC);
    select(0, (fd_set *) 0, (fd_set *) 0, (fd_set *) 0, &tv);
}

