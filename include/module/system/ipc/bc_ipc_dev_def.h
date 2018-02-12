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

#ifndef __BC_IPC_DEV_DEF_H__
#define __BC_IPC_DEV_DEF_H__

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								头   文   件								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_err.h"
#include "bc_ipc_def.h"

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								宏   定   义								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////


#define     DEV_IPC_SERVER_NAME                 	"/tmp/IPC_BCApp"

#define     DEV_BORAD_IPC_SERVER_NAME      	"PROCESS_EXTERNAL"

#define     BC_IPC_SNMP_SERVER_NAME         	"/tmp/IPC_BCSnmpApp"

#define     BC_IPC_CLI_SERVER_NAME			"/tmp/IPC_KTCliApp"
#define     BC_IPC_CLI_SERVER_NAME1         	"/tmp/IPC_BCCliApp1"
#define     BC_IPC_CLI_SERVER_NAME2         	"/tmp/IPC_BCCliApp2"
#define     BC_IPC_CLI_SERVER_NAME3         	"/tmp/IPC_BCCliApp3"
#define     BC_IPC_CLI_SERVER_NAME4         	"/tmp/IPC_BCCliApp4"
#define     BC_IPC_CLI_SERVER_NAME5         	"/tmp/IPC_BCCliApp5"
#define     BC_IPC_CLI_SERVER_NAME6         	"/tmp/IPC_BCCliApp6"
#define     BC_IPC_CLI_SERVER_NAME7         	"/tmp/IPC_BCCliApp7"
#define     BC_IPC_CLI_SERVER_NAME8         	"/tmp/IPC_BCCliApp8"

#define     BC_IPC_LWIP_SERVER_NAME           	"/tmp/IPC_BCLwipApp"

////////////////////////////////////////////////////////////////////////////////
//																			  //
//					结 构 体 、联 合 体、枚 举 定 义						  //
//																			  //
////////////////////////////////////////////////////////////////////////////////


#define    TEST_STR_LEN           1024

typedef struct
{
	bc_uint8       val_uint8;
	bc_int32       val_uint32;
	bc_int64       val_uint64;
	bc_boolean     val_boolean;
	bc_char        val_char;
	bc_char        val_str[TEST_STR_LEN];
}bc_ipc_dev_test_t;


////////////////////////////////////////////////////////////////////////////////
//																			  //
//						外 部 变 量、 函 数 声 明							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////



#endif /* __BC_IPC_DEV_CLIENT_H__ */

