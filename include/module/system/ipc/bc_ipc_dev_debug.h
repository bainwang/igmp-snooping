/*******************************************************************************
  Copyright (C), 2010-2030, xxxxx Tech. Co., Ltd.
  [File name]  : \\BC\Include\Common\Ipc\bc_ipc_bc_client.h
  [Author]     : bain.wang@outlook.com
  [Version]    : 1.0
  [Date]       : 2016-04-10
  [Description]:

  [Others]     :

  [Function List]:
	1. ....
	2. ....
  [History]:
	 D a t e	Modification										  Initials
	---------- --------------										 ----------
	2016-04-10	Created 											  bain.wang@outlook.com
*******************************************************************************/

#ifndef __BC_IPC_DEV_DEBUG_H__
#define __BC_IPC_DEV_DEBUG_H__

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								头   文   件								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_err.h"
#include "bc_ipc_def.h"
#include "bc_ipc_dev_def.h"

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								宏   定   义								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////



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

#if 1


/*DEV核心进程 Server 包dump*/
bc_err_e bc_ipc_dev_server_package_dump(void);

extern bc_err_e bc_ipc_dev_bcdevapp_trans_dump(void);

/*DEV核心进程 Server 信息dump*/
extern bc_err_e bc_ipc_dev_bcdevapp_server_dump(void);

extern bc_err_e bc_ipc_dev_bcdevapp_proc_dump(void);

extern bc_err_e bc_ipc_dev_bcdevapp_proc_ofs_dump(bc_uint32 ofs);

#endif
#if 1

/*DEV Client Test*/
bc_err_e bc_ipc_dev_client_request_test(void);

/*DEV Client Test*/
bc_err_e bc_ipc_bc_client_struct_test(bc_ipc_dev_test_t *olt_test);

/*DEV Client Test*/
bc_err_e bc_ipc_bc_broad_client_struct_test(bc_ipc_dev_test_t *olt_test);

#endif
#endif /* __BC_IPC_DEV_DEBUG_H__ */

