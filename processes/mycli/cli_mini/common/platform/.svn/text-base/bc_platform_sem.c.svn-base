/************************************************************
  Copyright (C), 1988-2014, xxxxx Tech. Co., Ltd.
  FileName:
  Author:  wangbin      Version :  1.0        Date:2014-2-8
  Description:     信号量相关函数              
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
#include "bc_print.h"
#include "utili_list.h"


typedef struct bc_sem_info_s {
    bc_char		name[BC_SEM_MAX_API_NAME];
	bc_sem_t	    id;
	bc_char        *func;
	bc_uint32       line;
	bc_uint32		recurse_wait_count;
	bc_uint32		recurse_post_count;
} bc_sem_info_t;

typedef struct 
{
	utili_node 	     utili_node;
	bc_sem_info_t	 data;        
} bc_sem_node_t;

static utili_list bc_platform_sem_head;
static bc_pthread_mutex_t *bc_platform_sem_mut;  

#ifdef BC_PLATFORM_SEM_DEBUG
static bc_uint32 bc_platform_sem_count_curr;
static bc_uint32 bc_platform_sem_count_max;
#define BC_PLATFORM_SEM_RESOURCE_USAGE_INCR(a_curr, a_max, ilock)               \
        a_curr++;                                                       \
        a_max = ((a_curr) > (a_max)) ? (a_curr) : (a_max)
    
#define BC_PLATFORM_SEM_RESOURCE_USAGE_DECR(a_curr, ilock)                      \
        a_curr--

/*
 * Function:
 *      bc_platform_sem_ResourceUsageGet
 * Purpose:
 *      Provides count of active sem and maximum sem allocation
 * Parameters:
 *      sem_curr - Current semaphore allocation.
 *      sem_max - Maximum semaphore allocation.
 */

void bc_platform_sem_ResourceUsageGet(bc_uint32 *sem_curr, bc_uint32 *sem_max)
{
    if (sem_curr != NULL) {
        *sem_curr = bc_platform_sem_count_curr;
    }
    if (sem_max != NULL) {
        *sem_max = bc_platform_sem_count_max;
    }
}
#endif//BC_PLATFORM_SEM_DEBUG


static bc_int32 __bc_platform_sem_compare(void * node, bc_uint32 key)
{

	bc_sem_info_t *ti = &((bc_sem_node_t *)node)->data;
	bc_int32 ret = 0;
	
	if((bc_uint32)&ti->id == key)
	{
		ret = 0;
	}
	else //if(&ti->id != key)
	{
		ret = -1;
	}
	
	//bc_platform_trace("<%s-%d>:ti->id:%p,key:%p,name:%s,ret=%d\n",__FUNCTION__,__LINE__,&ti->id,(bc_sem_t *)key,ti->name,ret);
	
	return ret;
}

/*************************************************
  Function: bc_platform_sem_init
  Description:初始化信号量结构
  Input: 
  		
  Output:
  Return:
  		void
  Note: 用bc_platform_init替代bc_platform_sem_init
  进行平台结构的初始化
  History: 
*************************************************/
void bc_platform_sem_init(void)
{
	if((bc_platform_sem_mut = bc_platform_mutex_create("SemMutex1")) == NULL)
	{
		BC_PT_ERROR(BC_MODULE_PLATFORM, "<%s>:create mutex 1 fail!\n",__FUNCTION__);
		return ;
	}
	
	utili_lst_init(&bc_platform_sem_head,__bc_platform_sem_compare);
	
}

/*************************************************
  Function: bc_platform_sem_create
  Description:创建一个信号量
  Input: 
 		 name:信号量名称
 		 initial_count:信号量初始值
  		
  Output:
  Return:
  		成功:返回信号量id
  		失败:返回NULL
  Note:
  History: 
*************************************************/
bc_sem_t *bc_platform_sem_create(bc_char *name, bc_int32 initial_count)
{
    bc_sem_info_t *ti;
	bc_sem_node_t *sem_node;

    /* Ignore binary for now */

	if((name == NULL)||(strlen(name) >= BC_SEM_MAX_API_NAME))
	{
		BC_PT_ERROR(BC_MODULE_PLATFORM,"\r\n create sem err!!..");
		return NULL;
	}
	
    if ((sem_node = bc_platform_mem_malloc(BC_MODULE_PLATFORM,sizeof (bc_sem_node_t))) == NULL)
	{
		return NULL;
    }
	memset(sem_node,0,sizeof(bc_sem_node_t));
	
	ti = &sem_node->data;
	strcpy(ti->name,name);
	ti->func = "------";
	ti->line = 0;

	if(sem_init(&ti->id, 0, initial_count))
	{
		bc_platform_mem_free(BC_MODULE_PLATFORM,sem_node);
		return NULL;
	}
	
	bc_platform_mutex_lock(bc_platform_sem_mut);
	utili_lst_add(&bc_platform_sem_head,(utili_node *)sem_node);
#ifdef BC_PLATFORM_SEM_DEBUG
        BC_PLATFORM_SEM_RESOURCE_USAGE_INCR(
            bc_platform_sem_count_curr,
            bc_platform_sem_count_max,
            ilock);
#endif

	bc_platform_mutex_unlock(bc_platform_sem_mut);

    return (bc_sem_t *)(&ti->id);
}


/*************************************************
  Function: bc_platform_sem_destroy
  Description:删除一个已创建的信号量
  Input: 
 		 sem:信号量id
  Output:
  Return:
  		成功:返回BC_ERR_OK   失败:other
  Note:
  History: 
*************************************************/
bc_err_e bc_platform_sem_destroy(bc_sem_t *sem)
{

    utili_node *node;
	
	bc_platform_mutex_lock(bc_platform_sem_mut);
	
    if(sem_destroy(sem))
	{
		bc_platform_mutex_unlock(bc_platform_sem_mut);
		return BC_ERR_PLATFROM_SEM_OP_FAIL;
    }
	node = utili_lst_find(&bc_platform_sem_head,(unsigned int)sem);
	if(node == NULL)
	{
		bc_platform_mutex_unlock(bc_platform_sem_mut);
		return BC_ERR_PLATFROM_SEM_NOT_EXIST;
	}

	utili_lst_delete(&bc_platform_sem_head,node);
	
	bc_platform_mem_free(BC_MODULE_PLATFORM,node);

#ifdef BC_PLATFORM_SEM_DEBUG
	BC_PLATFORM_SEM_RESOURCE_USAGE_DECR(
	    bc_platform_sem_count_curr,
	    ilock);
#endif
	bc_platform_mutex_unlock(bc_platform_sem_mut);

	return BC_ERR_OK;
}

/*************************************************
  Function: bc_platform_sem_wait_ex
  Description:信号量wait操作
  Input: 
 		 sem:信号量id
 		 timeout:BC_SEM_WAIT_FOREVER、BC_SEM_NO_WAIT
 		 func:记录调用者函数名称
 		 line:记录调用的位置
  Output:
  Return:
  		成功:返回BC_ERR_OK   失败:other
  Note:不要直接调用此函数，请用bc_platform_sem_wait
  History: 
*************************************************/
bc_err_e bc_platform_sem_wait_ex(bc_sem_t *sem, bc_int32 timeout,bc_char *func,bc_uint32 line)
{
    bc_int32			err;
	bc_sem_info_t	*ti;
    utili_node *node;

	bc_platform_mutex_lock(bc_platform_sem_mut);
	node = utili_lst_find(&bc_platform_sem_head,(unsigned int)sem);
	if(node == NULL)
	{
		bc_platform_mutex_unlock(bc_platform_sem_mut);
		return BC_ERR_PLATFROM_SEM_NOT_EXIST;
	}
	
	ti = &((bc_sem_node_t *)node)->data;
	ti->func = func;
	ti->line = line;
	ti->recurse_wait_count++;
	
	bc_platform_mutex_unlock(bc_platform_sem_mut);

	if(timeout == BC_SEM_NO_WAIT)
	{
		err = sem_trywait(sem);
	}
	else if(timeout == BC_SEM_WAIT_FOREVER)
	{
		err = sem_wait(sem);
	}
	
    return err ? BC_ERR_PARA : BC_ERR_OK;
}

/*************************************************
  Function: bc_platform_sem_post
  Description:信号量post操作
  Input: 
 		 sem:信号量id
 		 
  Output:
  Return:
  		成功:返回BC_ERR_OK   失败:other
  Note: 
  History: 
*************************************************/
bc_err_e bc_platform_sem_post( bc_sem_t *sem)
{
	bc_sem_info_t	*ti;
    utili_node *node;
	
    if (sem_post(sem) != 0)
    {
    	return BC_ERR_PARA;
    }
	
	bc_platform_mutex_lock(bc_platform_sem_mut);
	node = utili_lst_find(&bc_platform_sem_head,(unsigned int)sem);
	if(node == NULL)
	{
		bc_platform_mutex_unlock(bc_platform_sem_mut);
		return BC_ERR_PLATFROM_SEM_NOT_EXIST;
	}
	
	ti = &((bc_sem_node_t *)node)->data;
	ti->func = "------";
	ti->line = 0;
	ti->recurse_post_count++;
	
	bc_platform_mutex_unlock(bc_platform_sem_mut);

    return BC_ERR_OK;
}


/*************************************************
  Function: bc_platform_sem_val_get
  Description:获取信号量的状态
  Input: 
 		 sem:信号量id
 		 sval:信号量的值
 		 
  Output:
  Return:
  		成功:返回BC_ERR_OK   失败:other
  Note: 
  History: 
*************************************************/
bc_err_e bc_platform_sem_val_get( bc_sem_t *sem,  bc_int32 *sval)
{
    bc_int32			err;
	
	err = sem_getvalue(sem,sval);

	return err ? BC_ERR_PARA : BC_ERR_OK;
}

/*************************************************
  Function: bc_platform_sem_name_val_get
  Description:获取信号量的状态和名称
  Input: 
 		 sem:信号量id
 		 name:保存信号的名称
 		 sem_name_size:name的size
 		 sval:信号量的值
 		 
  Output:
  Return:
  		成功:返回BC_ERR_OK   失败:other
  Note: 
  History: 
*************************************************/
bc_err_e bc_platform_sem_name_val_get(
	 bc_sem_t *sem,  
	 bc_int8 *name, 
	 bc_int32 sem_name_size,
	 bc_int32 *sval
)
{

	bc_sem_info_t	*ti;
    utili_node *node;
	if(sem_name_size < BC_SEM_MAX_API_NAME)
	{
		return BC_ERR_PARA;
	}
	memset(name,0,sem_name_size);
	
	node = utili_lst_find(&bc_platform_sem_head,(unsigned int)sem);
	if(node == NULL)
	{
		return BC_ERR_PLATFROM_SEM_NOT_EXIST;
	}
	
	ti = &((bc_sem_node_t *)node)->data;
    memcpy(name, ti->name, BC_SEM_MAX_API_NAME);
	if(sem_getvalue(sem,sval))
	{
    	return BC_ERR_PLATFROM_SEM_OP_FAIL;
	}

	return BC_ERR_OK;
}


/*************************************************
  Function: bc_platform_sem_show
  Description:dump所有信号量的状态名称数量等信息
  Input:  
 		 
  Output:
  Return:
  		void
  Note: 
  History: 
*************************************************/
void bc_platform_sem_show(void)
{
	bc_uint32 i = 1;
	bc_int32 sval;
	utili_node *predecessor,*next;
	bc_sem_info_t *ti;
	
    BC_PT_COMMAND(BC_MODULE_PLATFORM, "\r\n===================================================================================================");
    BC_PT_COMMAND(BC_MODULE_PLATFORM, "\r\n%-4s %-30s %-8s %-8s %-8s %-7s %-6s %-10s ","Id","Name","WAIT","POST","VALUE","STATUS","LINE","FUNC");
    BC_PT_COMMAND(BC_MODULE_PLATFORM, "\r\n---------------------------------------------------------------------------------------------------");
	predecessor = utili_lst_first(&bc_platform_sem_head);
	while(predecessor != NULL)
	{
		ti = &((bc_sem_node_t *)predecessor)->data;
		sem_getvalue(&ti->id,&sval);
        BC_PT_COMMAND(BC_MODULE_PLATFORM,"\n\r%-4d %-30s %-8d %-8d %-8d %-7s %-6d %-10s",
			                        i,ti->name,ti->recurse_wait_count,ti->recurse_post_count,sval,(sval == 0 ? "WAIT":"RUN"),ti->line,ti->func);
		next = utili_lst_next((utili_node *)predecessor);
		predecessor = next;
		i++;
	}
	#ifdef BC_PLATFORM_SEM_DEBUG
	BC_PT_COMMAND(BC_MODULE_PLATFORM, "\r\nsem info total[COUNT:%d,MAX:%d]",bc_platform_sem_count_curr,bc_platform_sem_count_max);
	#endif
	BC_PT_COMMAND(BC_MODULE_PLATFORM,"\n");
}

