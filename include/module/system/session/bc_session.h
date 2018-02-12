/*************************************************
  Copyright (C), 1988-2020, xxxxx Tech. Co., Ltd.
  File name:      sys_message.h
  Author:  bain.wang@outlook.com     Version:  v1.0      Date: 2013/10/08
  Description:    Define internal interface and data structure of sys module
  Others:         none
  Function List:  none
  History:          
    1. Date: 2013/10/08
       Author: bain.wang@outlook.com       
       Modification: create
  
*************************************************/

#ifndef __BC_SESSION_H__
#define __BC_SESSION_H__

#include "bc_err.h"
#include "bc_common_defs.h"
#include "bc_ipc_def.h"
#include "bc_session_def.h"



/*获取Session客户端开启的IPC Server网络参数*/
extern bc_err_e bc_seesion_srv_para_get(bc_uint32 sessionid, bc_ipc_server_data_t  *srv_para);

extern void bc_session_dbg_dump(void);
extern void bc_session_dbg_msg_back(bc_uint32 session_id, bc_char *msg);


#endif

