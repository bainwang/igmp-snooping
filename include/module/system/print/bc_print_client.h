/************************************************************
  -------------------------------------------------------------------------
  FileName: bc_print_client.h
  Author:  bain.wang@outlook.com      Version :  1.0        Date:2016-6-23
  Description: proj depend parameter define       
  Version:                        
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/
#ifndef __BC_PRINT_CLIENT_H__
#define __BC_PRINT_CLIENT_H__

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              头   文   件                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
#include "bc_print.h"
#include "bc_err.h"
#include "bc_common_defs.h"
#include "bc_modules.h"

#include "bc_ipc_def.h"
#include "bc_ipc_client.h"
#include "bc_ipc_dev_client.h"




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
  Function: bc_pt_prt_open_all_client
  Description: 打开所有打印配置(包括打开所有打印
  				 级别和打开所有模块),客户端
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
bc_err_e bc_pt_prt_open_all_client(void);



/*************************************************
  Function: bc_pt_prt_close_all_client
  Description: 清除打印配置，全关闭(关闭所有的打
  				 印级别和模块)
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
bc_err_e bc_pt_prt_close_all_client(void);



/*************************************************
  Function: bc_pt_prt_lvl_open_client
  Description: 打开打印的该级别(位)
  Input: 
  		prt_level		打印级别
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_pt_prt_lvl_open_client(bc_int32 prt_level);



/*************************************************
  Function: bc_pt_prt_lvl_close_client
  Description: 打开打印的该级别(位)
  Input: 
  		prt_level		打印级别
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_pt_prt_lvl_close_client(bc_int32 prt_level);



/*************************************************
  Function: bc_pt_open_prj_all_client
  Description: 打开打印整个工程(开启打印所有的模块)
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
bc_err_e bc_pt_open_prj_all_client(void);



/*************************************************
  Function: bc_pt_open_prj_mdl_client
  Description: 打开某个模块所有文件
  Input: 
  		module_id		模块id
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_pt_open_prj_mdl_client(bc_uint32 module_id);



/*************************************************
  Function: bc_pt_open_prj_mdl_file_client
  Description: 打开某个模块的某个文件
  Input: 
  		module_id		模块id
  		file			某个文件的文件结构指针
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_pt_open_prj_mdl_file_client(bc_uint32 module_id, bc_pt_file_flg_t *file);



/*************************************************
  Function: bc_pt_close_prj_all_client
  Description: 关闭整个工程(所有模块的所有文件)的
  				 打印
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
bc_err_e bc_pt_close_prj_all_client(void);



/*************************************************
  Function: bc_pt_close_prj_mdl_client
  Description: 关闭某个模块的所有文件的打印
  Input: 
  		module_id		模块id
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_pt_close_prj_mdl_client(bc_uint32 module_id);




/*************************************************
  Function: bc_pt_close_prj_mdl_file_client
  Description: 关闭某个模块的某个文件的打印
  Input: 
  		module_id								模块id
  		file_name[BC_PT_FILE_NAME_LEN_MAX]	文件名
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_pt_close_prj_mdl_file_client(bc_uint32 module_id, bc_char file_name[BC_PT_FILE_NAME_LEN_MAX]);



/*************************************************
  Function: bc_pt_get_prt_lvl_client
  Description: 获取打印的打印级别
  Input: 
  		prt_level		打印级别
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_pt_get_prt_lvl_client(bc_uint32 *prt_level);



/*************************************************
  Function: bc_pt_get_prj_all_client
  Description: 获取整个工程(所有模块)数据信息
  Input: 
  		all_prj			指向整个工程的指针
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  History: 
*************************************************/
bc_err_e bc_pt_get_prj_all_client(bc_pt_prj_flg_t *all_prj);




/*************************************************
  Function: bc_pt_dbg_save_cfg_client
  Description: 保存调试配置数据到文件
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
bc_err_e bc_pt_dbg_save_cfg_client(void);



/*************************************************
  Function: bc_pt_dbg_save_clear_client
  Description: 清除调试配置文件和内存调试数据
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
bc_err_e bc_pt_dbg_save_clear_client(void);


/*************************************************
  Function: bc_pt_dump_client
  Description: dump所有内存数据
  Input: 
   		pt_lvl     指向打印级别的指针
   		pt_prj     指向PT模块工程的指针
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_pt_dump_client(bc_uint32 *pt_lvl, bc_pt_prj_flg_t *pt_prj);



#endif /* __BC_PRINT_CLIENT_H__ */


