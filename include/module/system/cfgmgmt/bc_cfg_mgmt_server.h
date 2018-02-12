/************************************************************
  FileName: bc_cfg_mgmt_server.h
  Author:  bain.wang@outlook.com      Version :  1.0        Date:2016-8-15
  Description: proj depend parameter define       
  Version:                        
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/
#ifndef __BC_CFG_MGMT_SERVER_H__
#define __BC_CFG_MGMT_SERVER_H__

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              ͷ   ��   ��                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
#include "bc_err.h"
#include "bc_ipc_def.h"
#include "bc_cfg_mgmt.h"




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
  Function: bc_cfg_save_no_name_srv
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
bc_err_e bc_cfg_save_no_name_srv(bc_ipc_package_t *data);



/*************************************************
  Function: bc_cfg_save_name_srv
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
bc_err_e bc_cfg_save_name_srv(bc_ipc_package_t *data);


/*************************************************
  Function: bc_cfg_get_run_srv
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
bc_err_e bc_cfg_get_run_srv(bc_ipc_package_t *data);



/*************************************************
  Function: bc_cfg_clr_srv
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
bc_err_e bc_cfg_clr_srv(bc_ipc_package_t *data);



/*************************************************
  Function: bc_cfg_get_cfglist_srv
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
bc_err_e bc_cfg_get_cfglist_srv(bc_ipc_package_t *data);



/*************************************************
  Function: bc_cfg_set_boot_load_file_srv
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
bc_err_e bc_cfg_set_boot_load_file_srv(bc_ipc_package_t *data);



/*************************************************
  Function: bc_cfg_no_boot_load_file_srv
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
bc_err_e bc_cfg_no_boot_load_file_srv(bc_ipc_package_t *data);



/*************************************************
  Function: bc_cfg_dbg_dump_srv
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
bc_err_e bc_cfg_dbg_dump_srv(bc_ipc_package_t *data);


bc_err_e bc_cfg_dbg_mdl_ins_srv(bc_ipc_package_t *data);



#endif		/* BC_CFG_MGMT_SERVER_H */


