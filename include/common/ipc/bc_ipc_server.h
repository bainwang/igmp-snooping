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
//								ͷ   ��   ��								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_err.h"
#include "bc_ipc_def.h"
#include "bc_ipc_package.h"

#define  BC_IPC_DEF_TCP_PORT            15898

typedef enum
{
	IPC_SERVER_TYPE_IPC_SOCKET  =  1,     /*����IPC SOCKET ���̼�ͨ��*/
	IPC_SERVER_TYPE_TCP  = 2,             /*����TCP ���̼�ͨ��*/ 
	IPC_SERVER_TYPE_UDP  = 3,             /*����UDP ���̼�ͨ��*/
	IPC_SERVER_TYPE_PIPE = 4,             /*����PIPE ���̼�ͨ��*/ 
	IPC_SERVER_TYPE_SHARE_MEM = 5,        /*���ڹ����ڴ� ���̼�ͨ��*/ 
	IPC_SERVER_TYPE_MESSAGE = 6,          /*������Ϣ ���̼�ͨ��*/
	IPC_SERVER_TYPE_MAX                   
} bc_ipc_server_type_e;

typedef struct { 
	bc_ipc_server_type_e 	srv_type;                           /*IPC Server ��������*/ 
	bc_char 	          				srv_name[MAX_IPC_NAME_LEN];             /*IPC ����*/

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

/*IPC Server�ṹ*/
typedef struct
{ 
	bc_ipc_server_data_t           		srv_para;                           /*IPC Server ͨ�Ų���*/
	
    bc_uint32                      			proc_thread_count;                  /*���������߳���*/
    bc_ipc_server_proc_handler     srv_proc;                           /*����˿ڴ���ص�*/ 
} bc_ipc_server_t; 


/*IPC Server User Hander*/
typedef bc_err_e (*bc_ipc_user_hander)(bc_ipc_package_t *data);


/*IPC Server �û�ע��hander*/
typedef struct
{
	bc_uint32                     	functionid;                         /*����ID*/
    bc_uint32                    	sync_ctrl;                            /*�Ƿ�忨ͬ��*/
    bc_uint32                  	standby_ctrl;                     /*�Ƿ�standby״̬����*/ 
    bc_ipc_user_hander      	user_hander;                        /*�û�hander*/
    bc_char                       	hander_name[MAX_HANDER_NAME];       /*hander_name �ṩ������Ϣ*/

	bc_uint32 						in_cnt;
	bc_uint32							out_cnt;
	bc_uint32 						err_cnt;
} bc_ipc_reg_user_handler_t;


/*IPC Server����*/
bc_err_e  bc_ipc_server_create(bc_ipc_server_t  *ipc_srv);

/*IPC Server dump*/
bc_err_e bc_ipc_server_dump(void);



#endif /* __BC_IPC_SERVER_H__ */

