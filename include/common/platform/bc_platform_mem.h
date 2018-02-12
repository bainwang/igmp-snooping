/************************************************************
  FileName:
  Author:  bain.wang@outlook.com      Version :  1.0        Date:2017-04-04
  Description:         内存分配函数
  Version:     1.0                
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/

#ifndef _BC_PLATFORM_MEM_H_
#define _BC_PLATFORM_MEM_H_

#include "bc_common_defs.h"
#include "bc_modules.h"


#ifdef _MEM_POOL_







#else
extern void bc_platform_mem_init_ex(void);

extern void *bc_platform_mem_malloc_ex(
	bc_modules_e module,
	bc_char *func,
	bc_uint32 line,
	bc_uint32  size
);

extern void bc_platform_mem_free_ex(
	bc_modules_e module,
	bc_char  *func,
	bc_uint32 line,
	void *p
);


/*************************************************
  Function: bc_platform_mem_init_ex
  Description:初始化内存分配相关结构
  Input: 
  		
  Output:
  Return:
  		void
  Note: 用bc_platform_init替代bc_platform_mem_init
  进行平台结构的初始化
  History: 
*************************************************/
#define bc_platform_mem_init()  bc_platform_mem_init_ex()

/*************************************************
  Function: bc_platform_mem_set_maxsize
  Description:设置每个进程内存分配的最大值
  Input: 
  		maxsize:每个进程内存分配的最大值，
  		单位字节
  		
  Output:
  Return:
  		void
  Note: 默认值:5*1024*1024
  History: 
*************************************************/
extern void bc_platform_mem_set_maxsize(bc_uint64 maxsize);

/*************************************************
  Function: bc_platform_mem_malloc
  Description:分配函数
  Input: 
  		module:模块id
  		func:记录调用分配函数的函数名
  		line:记录分配位置
  		size:分配的空间大小
  		
  Output:
  Return:
  		成功:返回 指向所分配的内存单元的指针
  		失败:返回NULL
  Note: 外部调用请使用宏bc_platform_mem_malloc
  History: 
*************************************************/
#define  bc_platform_mem_malloc(module_id,size) \
	bc_platform_mem_malloc_ex(module_id,(bc_char *)__FUNCTION__,(bc_uint32)__LINE__,size)

/*************************************************
  Function: bc_platform_mem_free
  Description:释放内存函数
  Input: 
  		module:模块id
  		func:记录调用分配函数的函数名
  		line:记录分配位置
  		p:释放的地址指针
  		
  Output:
  Return:
  		void
  Note: 外部调用请使用宏bc_platform_mem_free
  History: 
*************************************************/	
#define  bc_platform_mem_free(module_id,ptr) \
	bc_platform_mem_free_ex(module_id,(bc_char *)__FUNCTION__,(bc_uint32)__LINE__,ptr)
	
/*************************************************
  Function: bc_platform_mem_show
  Description:dump 所有内存分配的情况
  Input: 
	
  Output:
  Return:
  		void
  Note: 
  History: 
*************************************************/
extern void bc_platform_mem_show(void);

#endif




#endif //_BC_PLATFORM_MEM_H_

