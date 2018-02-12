/************************************************************
  FileName: bc_log.h
  Author:  bain.wang@outlook.com      Version :  1.0        Date:2017-04-04
  Description:                   
  Version:                        
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/
#ifndef __BC_LOG_H__
#define __BC_LOG_H__



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              头   文   件                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "bc_err.h"
#include "bc_vfs.h"
#include "bc_print.h"
#include "bc_modules.h"

#include "bc_platform_time.h"
#include "bc_platform_mutex.h"
#include "bc_platform_procps.h"



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

#define BC_LOG_MAX_NOTE_NUM         	2000

#define BC_LOG_SYS_TIME_BUF_LEN			20
#define BC_LOG_ROW_POS_INFO_LEN			32
#define BC_LOG_TMP_DATA_INFO_LEN		64
#define BC_LOG_MAX_LINE_LEN				1024


/* user log */
#define BC_LOG_MAX_USER_NAME_LEN		32
#define BC_LOG_USR_BUF_LEN				384
#define BC_LOG_USER_CMD_LEN				200



/* system log */
#define BC_LOG_SYS_LEVEL_NAME_LEN		16
#define BC_LOG_SYS_BUF_LEN				384
#define BC_LOG_SYS_MAX_CONTENT_LEN		150

#define BC_LOG_SYS_FILE					"system.log"
#define BC_LOG_SYS_FILE_BACKUP			"backup_syslog"
#define BC_LOG_SYS_RUNNING_FILE 		"sys_running.log"
#define BC_LOG_SYS_TMP_FILE 			"tmp_sys.log"

#define	BC_LOG_SYS_WRT_THREAD			"sys_log_wrt_thread"	




////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                  结 构 体 、联 合 体、枚 举 定 义                          //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
typedef enum bc_log_etag_level_bit
{
	BC_LOG_LVL_INIT,
	BC_LOG_LVL_EVT,
	BC_LOG_LVL_WARN,
	BC_LOG_LVL_ERR,
	BC_LOG_LVL_COMMAND,
	BC_LOG_LVL_MAX
} bc_log_lvl_e;

/* 日志级别位 */
#define BC_LOG_BIT_ALL					0xFFFFFFFF
#define BC_LOG_BIT_NONE					0x00000000

#define BC_LOG_BIT_INIT					(BC_LOG_BIT_ALL & (0x01 << BC_LOG_LVL_INIT))
#define BC_LOG_BIT_EVENT				(BC_LOG_BIT_ALL & (0x01 << BC_LOG_LVL_EVT))
#define BC_LOG_BIT_WARNING				(BC_LOG_BIT_ALL & (0x01 << BC_LOG_LVL_WARN))
#define BC_LOG_BIT_ERROR				(BC_LOG_BIT_ALL & (0x01 << BC_LOG_LVL_ERR))
#define BC_LOG_BIT_COMMAND				(BC_LOG_BIT_ALL & (0x01 << BC_LOG_LVL_COMMAND))

typedef struct bc_log_sys_note_flag
{
	bc_int16			item_no;
	bc_log_lvl_e  		log_lvl;
	bc_char				sys_level[BC_LOG_SYS_LEVEL_NAME_LEN];
	bc_char				sys_time[BC_LOG_SYS_TIME_BUF_LEN];
	bc_char				log_content[BC_LOG_SYS_MAX_CONTENT_LEN];
} bc_log_sys_note_t;



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
#if 1
/*************************************************
  Function: bc_log_lvl_en
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
bc_boolean bc_log_lvl_en(bc_uint32 log_level);



/*************************************************
  Function: bc_log_lvl_open
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
bc_boolean bc_log_lvl_open(bc_uint32 log_level);



/*************************************************
  Function: bc_log_lvl_close
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
bc_boolean bc_log_lvl_close(bc_uint32 log_level);



/*************************************************
  Function: bc_log_lvl_get
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
bc_err_e bc_log_lvl_get(bc_uint32 *log_level);


#endif


#if 1
/*************************************************
  Function: bc_log_sys_init
  Description: 初始化系统日志(日志级别、系统日志)
  Input: 
  		void
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: core process init
  History: 
*************************************************/
bc_err_e bc_log_sys_init(void);



/*************************************************
  Function: bc_log_wrt_sys_log
  Description: 写系统日志(一条系统日志，包括:记录号、
  			时间、级别名、日志内容)到系统日志文件。
  Input: 
  		log_level		日志的级别
	  	module _id		模块id
	  	filename		文件名
	  	fun_name		函数名
	  	line_no			行号
	  	fmt				格式化信息
	  	…				参数列表信息
  Output:
  		NULL
  Return:
  		0: 
  		~0: 
  Note: 
  History: 
*************************************************/
bc_err_e bc_log_wrt_sys_log
	(
		bc_int32 			log_level, 
		bc_int32 			module_id, 
		const bc_char 		*filename, 
		const bc_char 		*fun_name, 
		bc_int32 			line_no, 
		const char 			*fmt, 
		...
	);



/*************************************************
  Function: bc_log_sys_buffer_clear
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
bc_err_e bc_log_sys_buffer_clear(void);


/*************************************************
  Function: bc_log_sys_flash_clear
  Description: 清除临时日志文件。
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
bc_err_e bc_log_sys_tmp_flash_clear(void);


/*************************************************
  Function: bc_log_sys_flash_clear
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
bc_err_e bc_log_sys_flash_clear(void);



/*************************************************
  Function: bc_log_get_sys_log
  Description: 获取整个系统日志的所有信息。
  Input: 
 		void
  Output:
  		NULL
  Return:
  		0: 
  		~0: 
  Note: 
  History: 
*************************************************/
bc_err_e bc_log_get_sys_log(void);



/*************************************************
  Function: bc_log_sys_wrt_opper_layer
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
bc_err_e bc_log_sys_wrt_upper_layer(bc_log_sys_note_t *sys_note);



/*************************************************
  Function: bc_log_sys_dbg_dump
  Description: 打印系统中所有的系统日志数据信息
  Input: 
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_log_sys_dbg_dump(void);

#endif


#endif



