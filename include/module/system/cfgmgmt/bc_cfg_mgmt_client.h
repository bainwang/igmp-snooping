/************************************************************
  -------------------------------------------------------------------------
  FileName: bc_cfg_mgmt_client.h
  Author:  bain.wang@outlook.com      Version :  1.0        Date:2016-8-15
  Description: proj depend parameter define       
  Version:                        
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/
#ifndef __BC_CFG_MGMT_CLIENT_H__
#define __BC_CFG_MGMT_CLIENT_H__

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              头   文   件                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
#include "bc_err.h"
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
  Function: bc_cfg_save_client
  Description: 
  Input: 
  		
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_cfg_save_client(bc_char *file_name);



/*************************************************
  Function: bc_cfg_get_run_client
  Description: 
  Input: 
  		
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_cfg_get_run_client(bc_cfg_run_t *run_para);



/*************************************************
  Function: bc_cfg_clr_client
  Description: 
  Input: 
  		
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_cfg_clr_client(bc_char *cfg_file);



/*************************************************
  Function: bc_cfg_get_cfglist_client
  Description: 
  Input: 
  		
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_cfg_get_cfglist_client(bc_cfg_file_info_t *file_list, bc_uint32 *actual_num);



/*************************************************
  Function: bc_cfg_set_boot_load_file_client
  Description: 
  Input: 
  		
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_cfg_set_boot_load_file_client(bc_char boot_file[BC_CFG_BOOT_NAME_LEN]);



/*************************************************
  Function: bc_cfg_no_boot_load_file_client
  Description: 
  Input: 
  		
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_cfg_no_boot_load_file_client(void);



/*************************************************
  Function: bc_cfg_dbg_dump_client
  Description: 
  Input: 
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_cfg_dbg_dump_client(void);

bc_err_e bc_cfg_dbg_mdl_ins(bc_uint32 fun_id, bc_modules_e mdl_id, bc_cfg_type_e mode, bc_uint32 mdl_pri);


#endif		/* BC_CFG_MGMT_CLIENT_H */



