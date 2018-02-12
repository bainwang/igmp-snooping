/************************************************************
  -------------------------------------------------------------------------
  FileName: bc_log_server.h
  Author:  bain.wang@outlook.com      Version :  1.0        Date:2016-7-2
  Description: proj depend parameter define       
  Version:                        
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/
#ifndef __BC_LOG_SERVER_H__
#define __BC_LOG_SERVER_H__

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              ͷ   ��   ��                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
#include "bc_err.h"
#include "bc_ipc_def.h"




////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                      �� �� �� ���� �� �� �� ��                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              ��   ��   ��                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                  �� �� �� ���� �� �塢ö �� �� ��                          //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                          ȫ �� �� �� �� ��                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
/* 
 *  �ⲿȫ�ֱ������ṩ�������̵��ã���ͷ�ļ����ṩ���ýӿ�(�ⲿ��������)��
 */

/* 
 *  �ڲ�ȫ�ֱ�����ֻ�ṩ�����ļ��ڲ��������ã�����ͷ�ļ����ṩ���ýӿڡ�
 */



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              ��  ��  ��  ��                                //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

/*************************************************
  Function: bc_log_lvl_en_srv
  Description: 
  Input: 
  		data	IPC����
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_log_lvl_en_srv(bc_ipc_package_t *data);




/*************************************************
  Function: bc_log_lvl_open_srv
  Description: 
  Input: 
  		data	IPC����
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_log_lvl_open_srv(bc_ipc_package_t *data);




/*************************************************
  Function: 
  Description: 
  Input: 
  		data	IPC����
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_log_lvl_close_srv(bc_ipc_package_t *data);



/*************************************************
  Function: 
  Description: 
  Input: 
  		data	IPC����
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_log_lvl_get_srv(bc_ipc_package_t *data);


#if 1
/*************************************************
  Function: bc_log_sys_wrt_upper_layer_srv
  Description: 
  Input: 
  		void
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_log_sys_wrt_upper_layer_srv(bc_ipc_package_t *data);



/*************************************************
  Function: bc_log_sys_buffer_clear_srv
  Description: ����ڴ��е�ϵͳ��־������Ϣ��
  Input: 
  		void
  Output:
  		NULL
  Return:
  		0: 
  		~0: 
  Note:    ���Ľ�������ڴ�ӿ�
  History: 
*************************************************/
bc_err_e bc_log_sys_buffer_clear_srv(bc_ipc_package_t *data);



/*************************************************
  Function: bc_log_sys_flash_clear_srv
  Description: ���ϵͳ��־�ļ���
  Input: 
  		void
  Output:
  		NULL
  Return:
  		0: 
  		~0: 
  Note:    ���Ľ�������ļ��ӿ�
  History: 
*************************************************/
bc_err_e bc_log_sys_flash_clear_srv(bc_ipc_package_t *data);



/*************************************************
  Function: bc_log_get_sys_log_srv
  Description: ��ȡ����ϵͳ��־��������Ϣ��
  Input: 
		data	IPC����
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_log_get_sys_log_srv(bc_ipc_package_t *data);


/*************************************************
  Function: bc_log_sys_dbg_dump_srv
  Description: dumpϵͳ��־��������Ϣ��
  Input: 
		data	IPC����
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_log_sys_dbg_dump_srv(bc_ipc_package_t *data);

bc_err_e bc_log_sys_dbg_wrt_srv(bc_ipc_package_t *data);

#endif


#if 1
/*************************************************
  Function: bc_log_usr_wrt_upper_layer_srv
  Description: 
  Input: 
  		data	IPC����
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_log_usr_wrt_upper_layer_srv(bc_ipc_package_t *data);


/*************************************************
  Function: bc_log_usr_buffer_clear_srv
  Description: ����ڴ��е��û���־������Ϣ��
  Input: 
  		data	IPC����
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note:    ���Ľ�������ڴ�ӿ�
  History: 
*************************************************/
bc_err_e bc_log_usr_buffer_clear_srv(bc_ipc_package_t *data);



/*************************************************
  Function: bc_log_usr_flash_clear_srv
  Description: ����û���־�ļ���
  Input: 
  		data	IPC����
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id 
  Note:    ���Ľ�������ļ��ӿ�
  History: 
*************************************************/
bc_err_e bc_log_usr_flash_clear_srv(bc_ipc_package_t *data);



/*************************************************
  Function: bc_log_get_user_log_srv
  Description: ��ȡ�����û����˴����û������CLI
  				�����������־��������Ϣ��
  Input: 
 		data	IPC����
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_log_get_user_log_srv(bc_ipc_package_t *data);

bc_err_e bc_log_usr_dbg_wrt_srv(bc_ipc_package_t *data);

#endif

#endif /* __BC_LOG_SERVER_H__ */

