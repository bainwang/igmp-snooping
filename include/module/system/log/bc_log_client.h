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
//                              头   文   件                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
#include "bc_err.h"
#include "bc_ipc_def.h"
#include "bc_common_defs.h"
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
  Function: bc_log_lvl_en_client
  Description: 是否写该级别的日志
  Input: 
  		log_level		日志级别（位）
  Output:
  		NULL
  Return:
  		0: FALSE(0)表示不写日志该文件
  		~0: TRUE(1)表示写该日志文件
  Note: 
  History: 
*************************************************/
bc_err_e bc_log_lvl_en_client(bc_uint32 log_level);



/*************************************************
  Function: bc_log_lvl_open_client
  Description: 打开写日志的级别
  Input: 
  		log_level		日志级别（位）
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
  Description: 关闭写日志级别(位)
  Input: 
  		log_level		日志级别（位）
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
  Description: 获取日志级别(位)
  Input: 
  		log_level		日志级别（位）
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
  Description: 写一条日志的客户端
  Input: 
  		sys_note		指向一条日志的指针
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
  Description: 清空内存中的系统日志数据信息。
  Input: 
  		void
  Output:
  		NULL
  Return:
  		0: 
  		~0: 
  Note:    核心进程清空内存接口
  History: 
*************************************************/
bc_err_e bc_log_sys_buffer_clear_client(void);



/*************************************************
  Function: bc_log_sys_flash_clear_client
  Description: 清除系统日志文件。
  Input: 
  		void
  Output:
  		NULL
  Return:
  		0: 
  		~0: 
  Note:    核心进程清除文件接口
  History: 
*************************************************/
bc_err_e bc_log_sys_flash_clear_client(void);



/*************************************************
  Function: bc_log_get_sys_log_client
  Description: 获取整个系统日志的所有信息。
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
  Description: dump系统日志的所有信息。
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
bc_err_e bc_log_sys_dbg_dump_client(void);

bc_err_e bc_log_sys_dbg_wrt_client(bc_int32 log_level, bc_int32 module_id, bc_char *fmt);

#endif



#endif /* __BC_LOG_CLIENT_H__ */
