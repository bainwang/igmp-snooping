/*******************************************************************************
  Copyright (C), 2010-2030, xxxxx Tech. Co., Ltd.
  [File name]  : \\BC\Include\Common\Ipc\bc_ipc_def.h
  [Author]     : bain.wang@outlook.com
  [Version]    : 1.0
  [Date]       : 2016-02-14
  [Description]:
 
  [Others]     :

  [Function List]:
	1. ....
	2. ....
  [History]:
	 D a t e	Modification										  Initials
	---------- --------------										 ----------
	2016-02-14	Created 											 bain.wang@outlook.com
*******************************************************************************/

#ifndef __BC_IPC_CMM_H__
#define __BC_IPC_CMM_H__

#include "bc_ipc_server.h"

typedef struct {
	bc_uint32 ipc_proc_dbg_err_module_cnt;
	bc_uint32 ipc_proc_dbg_err_arr_cnt;
	bc_uint32 ipc_proc_dbg_err_func_id_cnt;
	bc_uint32 ipc_proc_dbg_err_sync_only_cnt;
	bc_uint32 ipc_proc_dbg_err_slave_cannot_use_cnt;
	bc_uint32 ipc_proc_dbg_err_handler_null_cnt;

	bc_uint32 ipc_proc_handler_start_cnt;
	bc_uint32 ipc_proc_handler_err_cnt;
	bc_uint32 ipc_proc_handler_end_cnt;
	bc_uint32 ipc_proc_dbg_sync_cnt;
} bc_ipc_cmm_srv_proc_cnt_t;


typedef struct {
	bc_ipc_reg_user_handler_t *func_arr;
	bc_uint32 func_num;

	bc_ipc_cmm_srv_proc_cnt_t ipc_cnt;
} bc_ipc_cmm_server_t;

extern bc_err_e bc_ipc_cmm_server_ipc_proc_check(bc_ipc_cmm_server_t *srv, bc_uint32 module_offset, bc_uint32 msg_offset, bc_uint32 func_id);
extern bc_err_e bc_ipc_cmm_server_ipc_proc(bc_ipc_cmm_server_t *srv, bc_ipc_package_t *data);

extern void bc_ipc_cmm_server_dump(bc_ipc_cmm_server_t *srv);
extern void bc_ipc_cmm_server_cnt_dump(bc_ipc_cmm_server_t *srv, bc_uint32 ofs);

#endif
