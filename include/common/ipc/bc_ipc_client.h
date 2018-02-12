/*******************************************************************************
  Copyright (C), 2010-2030, xxxxx Tech. Co., Ltd.
  [File name]  : \\BC\Include\Common\Ipc\bc_ipc_client.h
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

#ifndef __BC_IPC_CLIENT_H__
#define __BC_IPC_CLIENT_H__

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								头   文   件								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_err.h"
#include "bc_ipc_def.h"
#include "bc_ipc_server.h"

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




/*IPC Client 类型*/
typedef enum
{
	IPC_CLIENT_TYPE_CLI  =  1,    /*CLI 进程*/                   
	IPC_CLIENT_TYPE_WEB  = 2,     /*WEB服务器进程*/
	IPC_CLIENT_TYPE_SNMP = 3,     /*SNMP进程*/
	IPC_CLIENT_TYPE_TEST = 4,      /*TEST进程*/
	IPC_CLIENT_TYPE_X5 = 5,    /*板卡间DEV核心进程*/
	IPC_CLIENT_TYPE_X6 = 6,
	IPC_CLIENT_TYPE_MAX = 7
} bc_ipc_client_type_e;


/*IPC Client Request*/
extern bc_err_e bc_ipc_comm_client_request(
	bc_ipc_server_data_t *srv_info,
	bc_uint32 		 functionid, 
	bc_ipc_package_t	 *data, 
	bc_boolean		 need_response
);

extern bc_err_e bc_ipc_comm_client_dump(void);


#endif /* __BC_IPC_CLIENT_H__ */

