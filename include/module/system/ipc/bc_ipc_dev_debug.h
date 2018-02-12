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
//								ͷ   ��   ��								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_err.h"
#include "bc_ipc_def.h"
#include "bc_ipc_dev_def.h"

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								��   ��   ��								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//																			  //
//					�� �� �� ���� �� �塢ö �� �� ��						  //
//																			  //
////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////
//																			  //
//						�� �� �� ���� �� �� �� ��							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#if 1


/*DEV���Ľ��� Server ��dump*/
bc_err_e bc_ipc_dev_server_package_dump(void);

extern bc_err_e bc_ipc_dev_bcdevapp_trans_dump(void);

/*DEV���Ľ��� Server ��Ϣdump*/
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

