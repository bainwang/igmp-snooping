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

#ifndef _BC_PLATFORM_SEM_H
#define _BC_PLATFORM_SEM_H

#include <semaphore.h>
#include "bc_platform_types.h"

#define BC_PLATFORM_SEM_DEBUG

#define BC_SEM_MAX_API_NAME  30

#define BC_SEM_WAIT_FOREVER	(-1)
#define BC_SEM_NO_WAIT          0

typedef sem_t bc_sem_t;

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
extern void bc_platform_sem_init(void);

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
extern bc_sem_t *bc_platform_sem_create(bc_char *name, bc_int32 initial_count);

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
extern bc_err_e bc_platform_sem_destroy(bc_sem_t *sem);

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
extern bc_err_e bc_platform_sem_wait_ex(bc_sem_t *sem, bc_int32 timeout,bc_char *func,bc_uint32 line);

/*************************************************
  Function: bc_platform_sem_wait
  Description:信号量wait操作
  Input: 
 		 sem:信号量id
 		 timeout:BC_SEM_WAIT_FOREVER,BC_SEM_NO_WAIT
 		 
  Output:
  Return:
  		成功:返回BC_ERR_OK   失败:other
  Note: 
  History: 
*************************************************/
#define bc_platform_sem_wait(sem,timeout) \
	                         bc_platform_sem_wait_ex(sem,timeout,(bc_char *)__FUNCTION__,__LINE__)


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
extern bc_err_e bc_platform_sem_post(bc_sem_t *sem);

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
extern bc_err_e bc_platform_sem_val_get(bc_sem_t *sem,  bc_int32 *sval);

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
extern bc_err_e bc_platform_sem_name_val_get(
	 bc_sem_t *sem, 
	 bc_int8 *name, 
	 bc_int32 sem_name_size, 
	 bc_int32 *sval);

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
extern void bc_platform_sem_show(void);

#ifdef BC_PLATFORM_SEM_DEBUG
extern void bc_platform_sem_ResourceUsageGet(bc_uint32 *sem_curr, bc_uint32 *sem_max);
#endif

#endif	//_BC_PLATFORM_SEM_H 
