/************************************************************
  Copyright (C), 1988-2014, xxxxx Tech. Co., Ltd.
  FileName:
  Author:  wangbin      Version :  1.0        Date:2014-2-8
  Description:         互斥锁相关函数
  Version:                1.0     
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/

#ifndef _BC_PLATFORM_MUTEX_H
#define _BC_PLATFORM_MUTEX_H

#include <pthread.h>
#include "bc_platform_types.h"

#define BC_PLATFORM_MUTEX_DEBUG 

#define BC_MUTEX_MAX_API_NAME  30

typedef pthread_mutex_t bc_pthread_mutex_t;

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
extern void bc_platform_mutex_init(void);
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
extern bc_pthread_mutex_t *bc_platform_mutex_create(bc_char *name);

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
extern bc_err_e bc_platform_mutex_destroy(bc_pthread_mutex_t *m);

/*************************************************
  Function: bc_platform_mutex_lock_ex
  Description:互斥锁上锁
  Input: 
  		m:互斥锁id
  		fun:记录上锁的函数名
  		line:记录上锁的位置
  		
  Output:
  Return:
		bc_err_e
  Note: 外部调用请直接使用bc_platform_mutex_lock
  这个宏定义
  History: 
*************************************************/
extern bc_err_e bc_platform_mutex_lock_ex(bc_pthread_mutex_t *m,bc_char *func,bc_uint32 line);


/*************************************************
  Function: bc_platform_mutex_lock
  Description:互斥锁上锁
  Input: 
  		m:互斥锁id	
  Output:
  Return:
		成功:返回BC_ERR_OK   失败:other
  Note: 外部调用请直接使用bc_platform_mutex_lock
  这个宏定义
  History: 
*************************************************/
#define bc_platform_mutex_lock(m) \
	bc_platform_mutex_lock_ex(m,(bc_char *)__FUNCTION__,__LINE__)
	
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
extern bc_err_e bc_platform_mutex_unlock(bc_pthread_mutex_t *m);

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
extern bc_err_e bc_platform_mutex_statue_get(bc_pthread_mutex_t *m, bc_uint8 *statue);

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
extern bc_err_e bc_platform_mutex_name_statue_get(
	 bc_pthread_mutex_t *m, 
	 bc_int8 *name, 
	 bc_int32 mutex_name_size, 
	 bc_int32 *statue);

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
extern void bc_platform_mutex_show(void);

#ifdef BC_PLATFORM_MUTEX_DEBUG
extern void bc_platform_mutex_ResourceUsageGet(unsigned int *mutex_curr, unsigned int *mutex_max);
#endif


#endif	//_BC_PLATFORM_MUTEX_H 

