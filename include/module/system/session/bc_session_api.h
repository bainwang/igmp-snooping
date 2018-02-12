/*******************************************************************************
  Copyright (C), 2010-2030, xxxxx Tech. Co., Ltd.
  [File name]  : \\BCCommon\Ipc\bc_session_ipc_client.h
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

#ifndef __BC_SESSION_API_H__
#define __BC_SESSION_API_H__

#include "bc_err.h"
#include "bc_common_defs.h"
#include "bc_ipc_def.h"
#include "bc_session_def.h"


/*session 初始化*/
extern bc_err_e bc_session_init(void);

/*Session创建*/
extern bc_err_e bc_session_create(bc_ipc_client_type_e client_type, bc_uint32 agging, bc_uint32 *sessionid);

/*session 释放*/
extern bc_err_e bc_session_release(bc_uint32 sessionid);

/*更新Session时间计数 */
extern bc_err_e bc_session_time_tick_reset(bc_uint32 sessionid);

/*设置Session客户端开启的IPC Server网络参数*/
extern bc_err_e bc_seesion_srv_para_set(bc_uint32 sessionid, bc_ipc_server_data_t *srv_para);



#endif

