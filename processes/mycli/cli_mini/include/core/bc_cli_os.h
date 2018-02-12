/*******************************************************************************
  Copyright (C), 1988-2012, xxxxx Tech. Co., Ltd.
  [File name]  : \\BC\include\cli\bc_cli_os.h
  [Author]     : wangbin
  [Version]    : 1.0
  [Date]       : 2014-04-21
  [Description]:

  [Others]     :

  [Function List]:
	1. ....
	2. ....
  [History]:
	 D a t e	Modification										  Initials
	---------- --------------										 ----------
	2014-04-21	Created 											  wangbin
*******************************************************************************/

#ifndef __INC_BC_CLI_OS_H__
#define __INC_BC_CLI_OS_H__

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								头   文   件								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_platform_mem.h"



////////////////////////////////////////////////////////////////////////////////
//																			  //
//								宏   定   义								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#define CLI_OS_MEMPOOL_Create(name, size) 	(HANDLE_T)BC_MODULE_CLI_KERNEL//bc_platform_mem_malloc(BC_MODULE_CLI_KERNEL, size)
#define CLI_OS_MEMPOOL_Destroy(pool) 		UNUSED(pool)//bc_platform_mem_free(pool)

#define CLI_OS_MEMPOOL_Alloc(pool, size) 	bc_platform_mem_malloc(BC_MODULE_CLI_KERNEL, size)
#define CLI_OS_MEMPOOL_Free(pool, ptr) 		bc_platform_mem_free(BC_MODULE_CLI_KERNEL, ptr)



////////////////////////////////////////////////////////////////////////////////
//																			  //
//					结 构 体 、联 合 体、枚 举 定 义						  //
//																			  //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//																			  //
//						外 部 变 量、 函 数 声 明							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////




#endif /* __INC_BC_CLI_OS_H__ */

