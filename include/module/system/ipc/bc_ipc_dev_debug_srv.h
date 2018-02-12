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

#ifndef __BC_IPC_DEV_DEBUG_SRV_H__
#define __BC_IPC_DEV_DEBUG_SRV_H__

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								ͷ   ��   ��								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_err.h"
#include "bc_ipc_def.h"

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


/*OLT���Ľ��� Server ��dump*/
bc_err_e bc_ipc_dev_server_package_dump_srv(bc_ipc_package_t *data);

/*OLT���Ľ��� Server ��Ϣdump*/
extern bc_err_e bc_ipc_dev_bcdevapp_server_dump_srv(bc_ipc_package_t *data);

extern bc_err_e bc_ipc_dev_bcdevapp_trans_dump_srv(bc_ipc_package_t *data);

extern bc_err_e bc_ipc_dev_bcdevapp_proc_dump_srv(bc_ipc_package_t *data);

extern bc_err_e bc_ipc_dev_bcdevapp_proc_ofs_dump_srv(bc_ipc_package_t *data);

#endif
#if 1

/*���� */
bc_err_e bc_test_ipc_create_srv(bc_ipc_package_t *data);

/*���� */
bc_err_e bc_ipc_dev_client_request_test_srv(bc_ipc_package_t *data);

/*����*/
bc_err_e bc_ipc_dev_client_struct_test_srv(bc_ipc_package_t *data);

/*����*/
bc_err_e bc_ipc_dev_broad_client_struct_test_srv(bc_ipc_package_t *data);

#endif

#endif /* __BC_IPC_DEV_DEBUG_SRV_H__ */

