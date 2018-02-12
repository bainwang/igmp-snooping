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

#ifndef __BC_IPC_DEV_CLIENT_H__
#define __BC_IPC_DEV_CLIENT_H__

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								头   文   件								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_err.h"
#include "bc_ipc_def.h"
#include "bc_ipc_package.h"
#include "bc_ipc_client.h"

/*OLT核心进程 client 请求*/
bc_err_e bc_ipc_dev_client_request(bc_uint32 functionid, 
	           bc_ipc_package_t *data);

extern void bc_ipc_dev_client_dump(void);

extern bc_uint32 bc_ipc_dev_client_session_get(void);

/*创建 IPC client*/
bc_err_e bc_ipc_dev_client_create(bc_ipc_client_type_e client_type);

/*IPC client 释放*/
bc_err_e bc_ipc_dev_client_release(void);

#if 1
#define bc_ipc_create(client_type)		\
	bc_ipc_dev_client_create(client_type)

#define bc_ipc_client_request(functionid, data)		\
	bc_ipc_dev_client_request(functionid, data)

#define bc_ipc_client_dump()		\
	bc_ipc_dev_client_dump()

#define bc_ipc_client_session_get()		\
	bc_ipc_dev_client_session_get()

#define bc_ipc_client_release()		\
	bc_ipc_dev_client_release()

#endif

#endif /* __BC_IPC_OLT_CLIENT_H__ */

