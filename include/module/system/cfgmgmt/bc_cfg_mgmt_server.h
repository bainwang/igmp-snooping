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
//                              头   文   件                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
#include "bc_err.h"
#include "bc_ipc_def.h"
#include "bc_cfg_mgmt.h"




////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                      外 部 变 量、 函 数 引 用                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              宏   定   义                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                  结 构 体 、联 合 体、枚 举 定 义                          //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                          全 局 变 量 定 义                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
/* 
 *  外部全局变量，提供整个工程调用，在头文件中提供调用接口(外部引用声明)。
 */

/* 
 *  内部全局变量，只提供给该文件内部函数调用，不在头文件中提供调用接口。
 */



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              函  数  声  明                                //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

/*************************************************
  Function: bc_cfg_save_no_name_srv
  Description: 
  Input: 
  		data	IPC数据
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
  		data	IPC数据
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
  		data	IPC数据
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
  		data	IPC数据
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
  		data	IPC数据
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
  		data	IPC数据
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
  		data	IPC数据
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
  		data	IPC数据
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


