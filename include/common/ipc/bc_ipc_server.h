/*******************************************************************************
  Copyright (C), 2010-2030, xxxxx Tech. Co., Ltd.
  [File name]  : \\BC\Include\Common\Ipc\bc_ipc_package.h
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

#ifndef __BC_IPC_SERVER_H__
#define __BC_IPC_SERVER_H__
       
////////////////////////////////////////////////////////////////////////////////
//																			  //
//								头   文   件								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_err.h"
#include "bc_ipc_def.h"
#include "bc_ipc_package.h"

#define  BC_IPC_DEF_TCP_PORT            15898

typedef enum
{
	IPC_SERVER_TYPE_IPC_SOCKET  =  1,     /*基于IPC SOCKET 进程间通信*/
	IPC_SERVER_TYPE_TCP  = 2,             /*基于TCP 进程间通信*/ 
	IPC_SERVER_TYPE_UDP  = 3,             /*基于UDP 进程间通信*/
	IPC_SERVER_TYPE_PIPE = 4,             /*基于PIPE 进程间通信*/ 
	IPC_SERVER_TYPE_SHARE_MEM = 5,        /*基于共享内存 进程间通信*/ 
	IPC_SERVER_TYPE_MESSAGE = 6,          /*基于消息 进程间通信*/
	IPC_SERVER_TYPE_MAX                   
} bc_ipc_server_type_e;

typedef struct { 
	bc_ipc_server_type_e 	srv_type;                           /*IPC Server 服务类型*/ 
	bc_char 	          				srv_name[MAX_IPC_NAME_LEN];             /*IPC 名称*/

	union {
		struct {
			bc_char name[MAX_IPC_NAME_LEN];
		} ipc;

		struct {
			bc_ip ip;
			bc_uint32 port;
		} sock_tcp;
	} data;
 } bc_ipc_server_data_t;


/*IPC Server Call back*/
typedef bc_err_e (*bc_ipc_server_proc_handler)(bc_ipc_package_t *data);

/*IPC Server结构*/
typedef struct
{ 
	bc_ipc_server_data_t           		srv_para;                           /*IPC Server 通信参数*/
	
    bc_uint32                      			proc_thread_count;                  /*并发处理线程数*/
    bc_ipc_server_proc_handler     srv_proc;                           /*服务端口处理回调*/ 
} bc_ipc_server_t; 


/*IPC Server User Hander*/
typedef bc_err_e (*bc_ipc_user_hander)(bc_ipc_package_t *data);


/*IPC Server 用户注册hander*/
typedef struct
{
	bc_uint32                     	functionid;                         /*函数ID*/
    bc_uint32                    	sync_ctrl;                            /*是否板卡同步*/
    bc_uint32                  	standby_ctrl;                     /*是否standby状态操作*/ 
    bc_ipc_user_hander      	user_hander;                        /*用户hander*/
    bc_char                       	hander_name[MAX_HANDER_NAME];       /*hander_name 提供调试信息*/

	bc_uint32 						in_cnt;
	bc_uint32							out_cnt;
	bc_uint32 						err_cnt;
} bc_ipc_reg_user_handler_t;


/*IPC Server创建*/
bc_err_e  bc_ipc_server_create(bc_ipc_server_t  *ipc_srv);

/*IPC Server dump*/
bc_err_e bc_ipc_server_dump(void);



#endif /* __BC_IPC_SERVER_H__ */

