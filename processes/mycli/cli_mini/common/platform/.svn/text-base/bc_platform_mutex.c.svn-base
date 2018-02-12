/************************************************************
  Copyright (C), 1988-2014, xxxxx Tech. Co., Ltd.
  FileName:
  Author:  wangbin      Version :  1.0        Date:2014-2-8
  Description:    互斥锁相关函数               
  Version:        1.0                
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/


#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

#include "bc_platform_thread.h"
#include "bc_platform_sem.h"
#include "bc_platform_time.h"
#include "bc_platform_mutex.h"
#include "utili_list.h"
#include "bc_print.h"


#ifdef BC_PLATFORM_MUTEX_DEBUG
static bc_uint32 bc_platform_mutex_count_curr;
static bc_uint32 bc_platform_mutex_count_max;
#define BC_PLATFORM_MUTEX_RESOURCE_USAGE_INCR(a_curr, a_max, ilock)               \
        a_curr++;                                                       \
        a_max = ((a_curr) > (a_max)) ? (a_curr) : (a_max)
    
#define BC_PLATFORM_MUTEX_RESOURCE_USAGE_DECR(a_curr, ilock)                      \
        a_curr--

/*
 * Function:
 *      bc_platform_mutex_ResourceUsageGet
 * Purpose:
 *      Provides count of active mutex and maximum mutex allocation
 * Parameters:
 *      mutex_curr - Current mutex allocation.
 *      mutex_max - Maximum mutex allocation.
 */

void bc_platform_mutex_ResourceUsageGet(bc_uint32 *mutex_curr, bc_uint32 *mutex_max)
{
    if (mutex_curr != NULL) {
        *mutex_curr = bc_platform_mutex_count_curr;
    }
    if (mutex_max != NULL) {
        *mutex_max = bc_platform_mutex_count_max;
    }
}
#endif //BC_PLATFORM_MUTEX_DEBUG


/*
 * bc_mutex_info_t
 *
 *   This is an abstract type built on the POSIX mutex that allows a
 *   mutex to be taken recursively by the same thread without deadlock.
 *
 *   The Linux version of pthreads supports recursive mutexes
 *   (a non-portable extension to posix).  this case, we 
 *   use the Linux support instead of our own. 
 */

typedef struct bc_mutex_info_s {
	bc_char	name[BC_MUTEX_MAX_API_NAME];
    bc_pthread_mutex_t	mutex;
	bc_char        *func;
	bc_uint32       line;
    bc_uint32		recurse_lock_count;
	bc_uint32		recurse_unlock_count;
} bc_mutex_info_t;


typedef struct 
{
	utili_node 	     utili_node;
	bc_mutex_info_t	 data;        
} bc_mutex_node_t;

static utili_list bc_platform_mutex_head;
static bc_pthread_mutex_t bc_platform_mutex_mut;

static bc_int32 __bc_platform_mutex_compare(void * node, bc_uint32 key)
{

	bc_mutex_info_t *ti = &((bc_mutex_node_t *)node)->data;
	bc_int32 ret = 0;
	
	if((bc_uint32)&ti->mutex == key)
	{
		ret = 0;
	}
	else //if(&ti->id != key)
	{
		ret = -1;
	}
	return ret;
}

 
/*************************************************
  Function: bc_platform_mutex_init
  Description:初始化互斥锁结构
  Input: 
  		
  Output:
  Return:
  		void
  Note: 用bc_platform_init替代bc_platform_mutex_init
  进行平台结构的初始化
  History: 
*************************************************/
void bc_platform_mutex_init(void)
{
	if(pthread_mutex_init(&bc_platform_mutex_mut,NULL))
    {
    	return ;
    }

	utili_lst_init(&bc_platform_mutex_head,__bc_platform_mutex_compare);	
}


/*************************************************
  Function: bc_platform_mutex_create
  Description:创建互斥锁
  Input: 
  		name:互斥锁名称
  		
  Output:
  Return:
  		成功:返回互斥锁id
  		失败:返回NULL
  Note: 
  History: 
*************************************************/
bc_pthread_mutex_t *bc_platform_mutex_create(bc_char *name)
{
    bc_mutex_info_t	*ti;
	bc_mutex_node_t *mutex_node;
	if((name == NULL)||(strlen(name) > BC_MUTEX_MAX_API_NAME))
	{
		BC_PT_ERROR(BC_MODULE_PLATFORM,"\r\n create mutex err!!..");
		return NULL;
	}
	
    if ((mutex_node = malloc(sizeof(bc_mutex_node_t))) == NULL)
	{
		return NULL;
    }
	memset(mutex_node,0,sizeof(mutex_node));
	ti = &mutex_node->data;
	strcpy(ti->name,name);
	ti->func = "------";
	ti->line = 0;
	ti->recurse_lock_count = 0;
	ti->recurse_unlock_count = 0;
	
    if(pthread_mutex_init(&ti->mutex,NULL))
    {
    	free(mutex_node);
    	return NULL;
    }
	
	pthread_mutex_lock(&bc_platform_mutex_mut);
	utili_lst_add(&bc_platform_mutex_head,(utili_node *)mutex_node);
	
#ifdef BC_PLATFORM_MUTEX_DEBUG
        BC_PLATFORM_MUTEX_RESOURCE_USAGE_INCR(
            bc_platform_mutex_count_curr,
            bc_platform_mutex_count_max,
            ilock);
#endif
	pthread_mutex_unlock(&bc_platform_mutex_mut);

    return (bc_pthread_mutex_t *)(&ti->mutex);
}

/*************************************************
  Function: bc_platform_mutex_destroy
  Description:删除互斥锁
  Input: 
  		m:互斥锁id
  		
  Output:
  Return:
		成功:返回BC_ERR_OK   失败:other
  Note: 
  History: 
*************************************************/
bc_err_e bc_platform_mutex_destroy(bc_pthread_mutex_t *m)
{
    utili_node *node;

	pthread_mutex_lock(&bc_platform_mutex_mut);
	
    if(pthread_mutex_destroy(m))
    {
    	pthread_mutex_unlock(&bc_platform_mutex_mut);
    	return BC_ERR_PARA;
    }
	node = utili_lst_find(&bc_platform_mutex_head,(unsigned int)m);
	if(node == NULL)
	{
		pthread_mutex_unlock(&bc_platform_mutex_mut);
		return BC_ERR_PLATFROM_MUTEX_NOT_EXIST;
	}
	
	utili_lst_delete(&bc_platform_mutex_head,node);
	free(node);
	
#ifdef BC_PLATFORM_MUTEX_DEBUG
	BC_PLATFORM_MUTEX_RESOURCE_USAGE_DECR(
		bc_platform_mutex_count_curr,
		ilock);
#endif

	pthread_mutex_unlock(&bc_platform_mutex_mut);
	
	return BC_ERR_OK;
		
}

/*************************************************
  Function: bc_platform_mutex_lock_ex
  Description:互斥锁上锁
  Input: 
  		m:互斥锁id
  		fun:记录上锁的函数名
  		line:记录上锁的位置
  		
  Output:
  Return:
		成功:返回BC_ERR_OK   失败:other
  Note: 外部调用请直接使用bc_platform_mutex_lock
  这个宏定义
  History: 
*************************************************/
bc_err_e bc_platform_mutex_lock_ex(bc_pthread_mutex_t *m,bc_char *func,bc_uint32 line)
{
    bc_int32			err;
	bc_mutex_info_t	*ti;
    utili_node *node;
	
	if((err = pthread_mutex_lock(m)) != 0)
	{
		return BC_ERR_PARA;
	}
	
	pthread_mutex_lock(&bc_platform_mutex_mut);
	node = utili_lst_find(&bc_platform_mutex_head,(unsigned int)m);
	if(node == NULL)
	{
		pthread_mutex_unlock(&bc_platform_mutex_mut);
		return BC_ERR_PLATFROM_MUTEX_NOT_EXIST;
	}

	ti = &((bc_mutex_node_t *)node)->data;
	ti->func = func;
	ti->line = line;
	ti->recurse_lock_count++;
	
	pthread_mutex_unlock(&bc_platform_mutex_mut);
	
    return BC_ERR_OK;
}

/*************************************************
  Function: bc_platform_mutex_unlock
  Description:互斥锁解锁
  Input: 
  		m:互斥锁id
  		
  Output:
  Return:
		成功:返回BC_ERR_OK   失败:other
  Note: 
  History: 
*************************************************/
bc_err_e bc_platform_mutex_unlock(bc_pthread_mutex_t *m)
{
    bc_int32   err;
	bc_mutex_info_t	*ti;
    utili_node *node;
	
    if((err = pthread_mutex_unlock(m)) != 0)
    {
    	return BC_ERR_PARA;
    }
	
	pthread_mutex_lock(&bc_platform_mutex_mut);
	node = utili_lst_find(&bc_platform_mutex_head,(unsigned int)m);
	if(node == NULL)
	{
		pthread_mutex_unlock(&bc_platform_mutex_mut);
		return BC_ERR_PLATFROM_MUTEX_NOT_EXIST;
	}
	ti = &((bc_mutex_node_t *)node)->data;
	ti->func = "------";
	ti->line = 0;
	ti->recurse_unlock_count++;
	
	pthread_mutex_unlock(&bc_platform_mutex_mut);
	
    return BC_ERR_OK;
}

/*************************************************
  Function: bc_platform_mutex_statue_get
  Description:获取互斥锁的状态
  Input: 
  		m:互斥锁id
  		statue:o-lock,1-unlock
  		
  Output:
  Return:
		成功:返回BC_ERR_OK   失败:other
  Note: 
  History: 
*************************************************/
bc_err_e bc_platform_mutex_statue_get( bc_pthread_mutex_t *m, bc_uint8 *statue)
{
	bc_mutex_info_t	*ti;
    utili_node *node;
	node = utili_lst_find(&bc_platform_mutex_head,(unsigned int)m);
	if(node == NULL)
	{
		return BC_ERR_PLATFROM_MUTEX_NOT_EXIST;
	}

	ti = &((bc_mutex_node_t *)node)->data;

	if (ti->recurse_lock_count > ti->recurse_unlock_count)
	{
		*statue = 0;
	}
	else
	{
		*statue = 1;
	}
	
	return BC_ERR_OK;

}

/*************************************************
  Function: bc_platform_mutex_name_statue_get
  Description:获取互斥锁的状态和名称
  Input: 
  		m:互斥锁id
  		name:互斥锁名称
  		mutex_name_size:互斥锁名称name 所占大小
  		statue:o-lock,1-unlock
  		
  Output:
  Return:
		成功:返回BC_ERR_OK   失败:other
  Note: 
  History: 
*************************************************/
bc_err_e bc_platform_mutex_name_statue_get(
	bc_pthread_mutex_t *m,  
	bc_int8 *name, 
	bc_int32 mutex_name_size,
	bc_int32 *statue
)
{
	bc_mutex_info_t	*ti;
    utili_node *node;
	if(mutex_name_size < BC_MUTEX_MAX_API_NAME)
	{
		return BC_ERR_PARA;
	}
	memset(name,0,mutex_name_size);
	
	node = utili_lst_find(&bc_platform_mutex_head,(unsigned int)m);
	if(node == NULL)
	{
		return BC_ERR_PLATFROM_MUTEX_NOT_EXIST;
	}
	ti = &((bc_mutex_node_t *)node)->data;

	memcpy(name, ti->name, BC_MUTEX_MAX_API_NAME);
	
	if (ti->recurse_lock_count > ti->recurse_unlock_count)
	{
		*statue = 0;
	}
	else
	{
		*statue = 1;
	}
	
	return BC_ERR_OK;
}

/*************************************************
  Function: bc_platform_mutex_show
  Description:dump 所有互斥锁的状态名称等信息
  Input: 
  
  Output:
  Return:
		void
  Note: 
  History: 
*************************************************/
void bc_platform_mutex_show(void)
{
	bc_uint32 i = 1;
	utili_node *predecessor,*next;
	bc_mutex_info_t *ti;
	bc_char *status;
	
    BC_PT_COMMAND(BC_MODULE_PLATFORM,"\r\n================================================================================");
    BC_PT_COMMAND(BC_MODULE_PLATFORM,"\r\n%-4s %-30s %-10s %-10s %-7s %-7s %-15s ","Id","Name","LOCK","UNLOCK","STATUS","LINE","FUNC");
    BC_PT_COMMAND(BC_MODULE_PLATFORM,"\r\n--------------------------------------------------------------------------------");

	predecessor = utili_lst_first(&bc_platform_mutex_head);
	while(predecessor != NULL)
	{
		ti = &((bc_mutex_node_t *)predecessor)->data;
		status = (ti->recurse_lock_count>ti->recurse_unlock_count?"LOCK":"UNLOCK");
		BC_PT_COMMAND(BC_MODULE_PLATFORM,"\n\r%-4d %-30s %-10d %-10d %-7s %-7d %-15s",i,ti->name,ti->recurse_lock_count,ti->recurse_unlock_count,status,ti->line,ti->func);
		next = utili_lst_next((utili_node *)predecessor);
		predecessor = next;
		i++;
	}
	#ifdef BC_PLATFORM_MUTEX_DEBUG
	BC_PT_COMMAND(BC_MODULE_PLATFORM,"\r\nmutex info total[COUNT:%d,MAX:%d]",bc_platform_mutex_count_curr,bc_platform_mutex_count_max);
	#endif
	BC_PT_COMMAND(BC_MODULE_PLATFORM,"\n");
}

