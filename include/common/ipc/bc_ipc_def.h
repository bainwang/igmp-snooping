/*******************************************************************************
  Copyright (C), 2010-2030, xxxxx Tech. Co., Ltd.
  [File name]  : \\BC\Include\Common\Ipc\bc_ipc_def.h
  [Author]     : bain.wang@outlook.com
  [Version]    : 1.0
  [Date]       : 2016-04-15
  [Description]:
 
  [Others]     :

  [Function List]:
	1. ....
	2. ....
  [History]:
	 D a t e	Modification										  Initials
	---------- --------------										 ----------
	2016-04-15	Created 											  bain.wang@outlook.com
*******************************************************************************/

#ifndef __BC_IPC_DEF_H__
#define __BC_IPC_DEF_H__
       
////////////////////////////////////////////////////////////////////////////////
//																			  //
//								头   文   件								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#include <memory.h>
#include <stdio.h>
#include "bc_err.h"
#include "bc_print.h"
#include "bc_common_defs.h"
#include "bc_platform_thread.h"
#include "bc_ipc_package.h"

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								宏   定   义								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////


#define  MAX_IPC_NAME_LEN               64                                   /*最大的IPC NAME长度*/ 
#define  MAX_HANDER_NAME                64                                   /*用户Hander函数名最长为64字节*/  

#define  IP_ADDRESS_LEN                 20                                   /*IP地址长度*/  


/*  
	BC_F_DONT_SYNC: 不会同步，仅作进程间通信

	BC_F_SYNC: 数据会被同步发送到(主备切换)的备份板中，备份板的*_srv
接口同样能够收到这个数据，一般来讲只有set动作需要同步，而get
动作不需要同步。

   BC_F_SYNC_ONLY: 该接口只用来做主备数据同步，如果被用作进程间通信会
 返回系统不支持的错误号
*/
#define BC_F_DONT_SYNC 	0
#define BC_F_SYNC 					1
#define BC_F_SYNC_ONLY		2


/*
    BC_F_SLAVE_USE: 当本板卡作为(主备切换)备份板时，仍然可以使用该接口，
一般来说，在备份板中只允许get动作。

    BC_F_SLAVE_CANNOT_USE: 不允许在备份板中使用
*/
#define BC_F_SLAVE_USE 1
#define BC_F_SLAVE_CANNOT_USE 0


#endif /* __BC_IPC_DEF_H__ */

