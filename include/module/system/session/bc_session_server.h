/*******************************************************************************
  Copyright (C), 2010-2030, xxxxx Tech. Co., Ltd.
  [File name]  : \\BCCommon\Ipc\bc_session_ipc_srv.h
  [Author]     : bain.wang@outlook.com
  [Version]    : 1.0
  [Date]       : 2015-08-4
  [Description]:

  [Others]     :

  [Function List]:  
    1. ....
    2. ....
  [History]:
	 D a t e    Modification 										  Initials
	---------- --------------                                        ----------
	2015-08-4  Created												  bain.wang@outlook.com
*******************************************************************************/

#ifndef __BC_SESSION_SERVER_H__
#define __BC_SESSION_SERVER_H__

#include "bc_err.h"
#include "bc_ipc_def.h"

extern bc_err_e bc_session_create_srv(bc_ipc_package_t *data);
extern bc_err_e bc_session_release_srv(bc_ipc_package_t *data);
extern bc_err_e bc_session_time_tick_srv(bc_ipc_package_t *data);

extern bc_err_e bc_session_ipc_dump_srv(bc_ipc_package_t *data);
extern bc_err_e bc_session_ipc_msg_back_srv(bc_ipc_package_t *data);

#endif
