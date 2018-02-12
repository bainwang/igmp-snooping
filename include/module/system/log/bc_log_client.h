/************************************************************
  -------------------------------------------------------------------------
  FileName: bc_log_client.h
  Author:  bain.wang@outlook.com      Version :  1.0        Date:2016-7-2
  Description: proj depend parameter define       
  Version:                        
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/
#ifndef __BC_LOG_CLIENT_H__
#define __BC_LOG_CLIENT_H__

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              ͷ   ��   ��                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
#include "bc_err.h"
#include "bc_ipc_def.h"
#include "bc_common_defs.h"
#include "bc_ipc_dev_client.h"



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
  Function: bc_log_lvl_en_client
  Description: �Ƿ�д�ü������־
  Input: 
  		log_level		��־����λ��
  Output:
  		NULL
  Return:
  		0: FALSE(0)��ʾ��д��־���ļ�
  		~0: TRUE(1)��ʾд����־�ļ�
  Note: 
  History: 
*************************************************/
bc_err_e bc_log_lvl_en_client(bc_uint32 log_level);



/*************************************************
  Function: bc_log_lvl_open_client
  Description: ��д��־�ļ���
  Input: 
  		log_level		��־����λ��
  Output:
  		NULL
  Return:
  		0: 
  		~0: 
  Note: 
  History: 
*************************************************/
bc_err_e bc_log_lvl_open_client(bc_uint32 log_level);



/*************************************************
  Function: bc_log_lvl_close_client
  Description: �ر�д��־����(λ)
  Input: 
  		log_level		��־����λ��
  Output:
  		NULL
  Return:
  		0: 
  		~0: 
  Note: 
  History: 
*************************************************/
bc_err_e bc_log_lvl_close_client(bc_uint32 log_level);



/*************************************************
  Function: bc_log_lvl_get_client
  Description: ��ȡ��־����(λ)
  Input: 
  		log_level		��־����λ��
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_log_lvl_get_client(bc_uint32 *log_level);



#if 1
/*************************************************
  Function: bc_log_sys_wrt_upper_layer_client
  Description: дһ����־�Ŀͻ���
  Input: 
  		sys_note		ָ��һ����־��ָ��
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_log_sys_wrt_upper_layer_client(bc_log_sys_note_t *sys_note);



/*************************************************
  Function: bc_log_sys_buffer_clear_client
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
bc_err_e bc_log_sys_buffer_clear_client(void);



/*************************************************
  Function: bc_log_sys_flash_clear_client
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
bc_err_e bc_log_sys_flash_clear_client(void);



/*************************************************
  Function: bc_log_get_sys_log_client
  Description: ��ȡ����ϵͳ��־��������Ϣ��
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
bc_err_e bc_log_get_sys_log_client(void);


/*************************************************
  Function: bc_log_sys_dbg_dump_client
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
bc_err_e bc_log_sys_dbg_dump_client(void);

bc_err_e bc_log_sys_dbg_wrt_client(bc_int32 log_level, bc_int32 module_id, bc_char *fmt);

#endif



#endif /* __BC_LOG_CLIENT_H__ */
