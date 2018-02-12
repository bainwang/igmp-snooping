/************************************************************
  Copyright (C), 1988-2014, xxxxx Tech. Co., Ltd.
  FileName: \\OLT\include\common\print\bc_print.h
  Author:  wangbin      Version :  1.0        Date:2014-4-25
  Description:                   
  Version:                        
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/
#ifndef	__BC_PRINT_H__
#define	__BC_PRINT_H__



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              头   文   件                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "bc_common_defs.h"
#include "bc_err.h"



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              宏   定   义                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
#define BC_COMPANY             		"KT"

#define BC_PT_PRJ_MDL_NUM_MAX		4
#define BC_PT_MDL_NAME_LEN_MAX		32

#define BC_PT_MDL_FILE_NUM_MAX		32
#define BC_PT_FILE_NAME_LEN_MAX 	32

#define BC_PT_FLAG_ALL				0xFF
#define BC_PT_FLAG_DETAIL			0x01
#define BC_PT_FLAG_NONE				0x00



#define BC_PT_MAXLINE				1024
#define BC_PT_WRT_FUN_MAX			8
#define BC_PT_WRT_FUN_NAME_MAX		32

#define BC_PT_DEL_CMD_BUF_SIZE		32

/* temp */
#define BC_PT_DBG_FILE				"print_dbg"



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                  结 构 体 、联 合 体、枚 举 定 义                          //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
/* print level bit */
typedef enum bc_print_etag_level_bit
{
	BC_LVL_DBGFUN,
	BC_LVL_DBGSMP,
	BC_LVL_DBGCPL,

	BC_LVL_INIT,
	BC_LVL_EVT,
	BC_LVL_WARN,
	BC_LVL_ERR,
	BC_LVL_CMD,
	BC_LVL_MORE,
	BC_LVL_MAX
} bc_pt_lvl_e;



typedef struct bc_print_stag_file_flag
{
	bc_char 			file_name[BC_PT_FILE_NAME_LEN_MAX];
	bc_uint32 			line_start;
	bc_uint32 			line_end;
} bc_pt_file_flg_t;

typedef struct bc_print_stag_mdl_flag
{
	bc_uint8			flag; 	/* flag = 0xff, print all files in this module; 
								   flag = others, print following files in this module; 
								   flag = 0, don't print all files in this module 
								*/ 
	bc_uint32 			id; 	/* id = 0, idle; id = (~0), reserved; */ 
	bc_pt_file_flg_t	files[BC_PT_MDL_FILE_NUM_MAX];
} bc_pt_mdl_flg_t;

typedef struct bc_print_stag_prj_flag
{
	bc_uint8 			flag; 	/* flag = 0xff, print all modules; 
								   flag = others, print following modules; 
								   flag = 0, not print all modules; 
								*/ 
	bc_pt_mdl_flg_t		mdls[BC_PT_PRJ_MDL_NUM_MAX];
} bc_pt_prj_flg_t;



/* 打印级别位 */
#define	BC_LVL_BIT_ALL				0xFFFFFFFF
#define	BC_LVL_BIT_NONE				0x00000000

#define	BC_LVL_BIT_DBG_FUNC			(BC_LVL_BIT_ALL & (0x01 << BC_LVL_DBGFUN))
#define	BC_LVL_BIT_DBG_SMPL			(BC_LVL_BIT_ALL & (0x01 << BC_LVL_DBGSMP))
#define	BC_LVL_BIT_DBG_CPLX			(BC_LVL_BIT_ALL & (0x01 << BC_LVL_DBGCPL))

#define	BC_LVL_BIT_INIT				(BC_LVL_BIT_ALL & (0x01 << BC_LVL_INIT))
#define	BC_LVL_BIT_EVENT			(BC_LVL_BIT_ALL & (0x01 << BC_LVL_EVT))
#define	BC_LVL_BIT_WARNING			(BC_LVL_BIT_ALL & (0x01 << BC_LVL_WARN))
#define	BC_LVL_BIT_ERROR			(BC_LVL_BIT_ALL & (0x01 << BC_LVL_ERR))
#define	BC_LVL_BIT_COMMAND			(BC_LVL_BIT_ALL & (0x01 << BC_LVL_CMD))



#define	BC_PT_LEVEL_ENABLE(prt_level)								bc_pt_prt_lvl_en(prt_level)
#define	BC_PT_LOCATION_ENABLE(module_id, file_name, line_num)		bc_pt_prt_line_en(module_id, file_name, line_num)



#define	BC_PT_FUN(msg...)		printf(msg)
#define BC_PT_FLUSH()			fflush(stdout)



#define BC_PT_DBG_FUN(module_id, fmt, ...)		\
	do\
	{\
		if (BC_PT_LEVEL_ENABLE(BC_LVL_BIT_DBG_FUNC) && BC_PT_LOCATION_ENABLE(module_id, __FILE__, __LINE__))\
		{\
			BC_PT_FUN("[%s-F]%s(%06d)(%s): ", BC_COMPANY, __FILE__, __LINE__, __FUNCTION__);\
			BC_PT_FUN(fmt, ##__VA_ARGS__);\
			BC_PT_FLUSH();\
		}\
	} while(0)



#define	BC_PT_DBG_SMP(module_id, fmt, ...)		\
	do\
	{\
		if (BC_PT_LEVEL_ENABLE(BC_LVL_BIT_DBG_SMPL) && BC_PT_LOCATION_ENABLE(module_id, __FILE__, __LINE__))\
		{\
			BC_PT_FUN(fmt, ##__VA_ARGS__);\
			BC_PT_FLUSH();\
		}\
	} while (0)



#define	BC_PT_DBG_CPL(module_id, fmt, ...)	\
	do\
	{\
		if (BC_PT_LEVEL_ENABLE(BC_LVL_BIT_DBG_CPLX) && BC_PT_LOCATION_ENABLE(module_id, __FILE__, __LINE__))\
		{\
			BC_PT_FUN("[%s-D]%s(%06d): ", BC_COMPANY, __FILE__, __LINE__);\
			BC_PT_FUN(fmt, ##__VA_ARGS__);\
			BC_PT_FLUSH();\
		}\
	} while (0)



#define	BC_PT_INIT(module_id, fmt, ...)		\
	do\
	{\
		if (1)\
		{\
			BC_PT_FUN(fmt, ##__VA_ARGS__);\
			BC_PT_FLUSH();\
		}\
	} while (0)



#define	BC_PT_EVENT(module_id, fmt, ...)	\
	do\
	{\
		if (BC_PT_LEVEL_ENABLE(BC_LVL_BIT_EVENT))\
		{\
			BC_PT_FUN("[%s-V]: ", BC_COMPANY);\
			BC_PT_FUN(fmt, ##__VA_ARGS__);\
			BC_PT_FLUSH();\
		}\
	} while (0)



#define	BC_PT_WARNING(module_id, fmt, ...)		\
	do\
	{\
		if(BC_PT_LEVEL_ENABLE(BC_LVL_BIT_WARNING))\
		{\
			BC_PT_FUN("[%s-W]: ", BC_COMPANY);\
			BC_PT_FUN(fmt, ##__VA_ARGS__);\
			BC_PT_FLUSH();\
		}\
	} while (0)



#define	BC_PT_ERROR(module_id, fmt, ...)		\
	do\
	{\
		if (BC_PT_LEVEL_ENABLE(BC_LVL_BIT_ERROR))\
		{\
			BC_PT_FUN("[%s-R]: ", BC_COMPANY);\
			BC_PT_FUN(fmt, ##__VA_ARGS__);\
			BC_PT_FLUSH();\
		}\
	} while (0)



#define	BC_PT_COMMAND(module_id, fmt, ...)	\
	do\
	{\
		if (1)\
		{\
			BC_PT_FUN(fmt, ##__VA_ARGS__);\
			BC_PT_FLUSH();\
		}\
	} while (0)



#define BC_PT_FUN_ENTER(module_id)				BC_PT_DBG_FUN(module_id, "function enter...\r\n")
#define BC_PT_FUN_LEAVE(module_id)				BC_PT_DBG_FUN(module_id, "function leave...\r\n")
#define BC_PT_FUN_TAG(module_id)				BC_PT_DBG_FUN(module_id, "function tag...\r\n")

#define BC_PT_FUN_NOTSUPPORTED(module_id)		BC_PT_WARNING(module_id, "*** not supported warning ***\r\n")



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                      外 部 变 量、 函 数 声 明                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

/*************************************************
  Function: bc_pt_init
  Description: 初始化PT模块功能
  Input: 
  		void
  Output:
  		NULL
  Return:
  		0: 
  		~0: 
  Note: 该函数是整个PT模块的初始化接口，可供CLI、
  		 核心进程等初始化调用
  History: 
*************************************************/
void bc_pt_init(void);



/*************************************************
  Function: bc_pt_init_prt
  Description: 初始化需要打印的级别(位)和整个工程
  Input: 
  		void
  Output:
  		NULL
  Return:
  		0: 
  		~0: 
  Note: 提供给bc_pt_init(整个PT模块的初始化)函数调用,
  		以及OLT和CLI进程清除调试配置后恢复原始状态调用
  History: 
*************************************************/
void bc_pt_init_prt(void);


#if 0
/*************************************************
  Function: bc_pt_prt_open_all
  Description: 打开所有打印配置(包括打开所有打印
  				 级别和打开所有模块)
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
void bc_pt_prt_open_all(void);



/*************************************************
  Function: bc_pt_prt_close_all
  Description: 清除打印配置，全关闭(关闭所有的打
  				 印级别和模块)
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
void bc_pt_prt_close_all(void);



/*************************************************
  Function: bc_pt_prt_this_mdl_en
  Description: 是否打印该模块
  Input: 
  		module_id		模块id
  Output:
  		NULL
  Return:
  		0:  返回FALSE表示不打印该模块
  		~0: 返回TRUE，表示打印该模块
  Note: 
  History: 
*************************************************/
bc_boolean bc_pt_prt_this_mdl_en(bc_uint32 module_id);



/*************************************************
  Function: bc_pt_prt_this_file_en
  Description: 是否打印该文件
  Input: 
  		module_id		模块id
  		file_name		文件名
  Output:
  		NULL
  Return:
  		0: 返回FALSE表示不打印
  		~0: 返回值为TRUE表示打印该文件
  Note: 
  History: 
*************************************************/
bc_boolean bc_pt_prt_this_file_en(bc_uint32 module_id, bc_uint8 *file_name);
#endif


/*************************************************
  Function: bc_pt_prt_lvl_en
  Description: 是否打印该级别的语句
  Input: 
  		prt_level		打印级别(位)		
  Output:
  		NULL
  Return:
  		0: 返回值为0表示不打印该级别语句
  		~0: 返回非0表示打印该级别的语句
  Note: 
  History: 
*************************************************/
bc_int32 bc_pt_prt_lvl_en(bc_uint32 prt_level);



/*************************************************
  Function: bc_pt_prt_line_en
  Description: 是否打印该行的语句
  Input: 
  		module_id		模块id
  		file_name		文件名
  		line_num		行号
  Output:
  		NULL
  Return:
  		0: 返回FLASE则不打印该行语句
  		~0: 返回TRUE表示打印该行语句
  Note: 
  History: 
*************************************************/
bc_boolean bc_pt_prt_line_en(bc_uint32 module_id, bc_char *file_name, bc_uint32 line_num);


#if 0
/*************************************************
  Function: bc_pt_prt_lvl_open
  Description: 打开打印的该级别(位)
  Input: 
  		prt_level		打印级别
  Output:
  		NULL
  Return:
  		0: 返回值为0表示成功
  		~0: 非0表示失败
  Note: 
  History: 
*************************************************/
bc_err_e bc_pt_prt_lvl_open(bc_int32 prt_level);



/*************************************************
  Function: bc_pt_prt_lvl_close
  Description: 关闭打印的该级别(位)
  Input: 
  		prt_level		打印级别
  Output:
  		NULL
  Return:
  		0: 返回值为0表示成功
  		~0: 非0表示失败
  Note: 
  History: 
*************************************************/
bc_err_e bc_pt_prt_lvl_close(bc_int32 prt_level);



/*************************************************
  Function: bc_pt_open_prj_all
  Description: 打开打印整个工程(开启打印所有的模块)
  Input: 
  		void
  Output:
  		NULL
  Return:
  		0: 返回值为0表示成功
  		~0: 非0表示失败
  Note: 
  History: 
*************************************************/
bc_err_e bc_pt_open_prj_all(void);



/*************************************************
  Function: bc_pt_open_prj_mdl
  Description: 打开某个模块所有文件
  Input: 
  		module_id		模块id
  Output:
  		NULL
  Return:
  		0: 返回值为0表示成功
  		~0: 非0表示失败
  Note: 
  History: 
*************************************************/
bc_err_e bc_pt_open_prj_mdl(bc_uint32 module_id);



/*************************************************
  Function: bc_pt_open_prj_mdl_file
  Description: 打开某个模块的某个文件
  Input: 
  		module_id		模块id
  		file			某个文件的文件结构指针
  Output:
  		NULL
  Return:
  		0: 返回值为0表示成功
  		~0: 非0表示失败
  Note: 
  History: 
*************************************************/
bc_err_e bc_pt_open_prj_mdl_file(bc_uint32 module_id, bc_pt_file_flg_t *file);



/*************************************************
  Function: bc_pt_close_prj_all
  Description: 关闭整个工程(所有模块的所有文件)的
  				 打印
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
bc_err_e bc_pt_close_prj_all(void);



/*************************************************
  Function: bc_pt_close_prj_mdl
  Description: 关闭某个模块的所有文件的打印
  Input: 
  		module_id		模块id
  Output:
  		NULL
  Return:
  		0: 
  		~0: 
  Note: 
  History: 
*************************************************/
bc_err_e bc_pt_close_prj_mdl(bc_uint32 module_id);



/*************************************************
  Function: bc_pt_close_prj_mdl_file
  Description: 关闭某个模块的某个文件的打印
  Input: 
  		module_id								模块id
  		file_name[BC_PT_FILE_NAME_LEN_MAX]	文件名
  Output:
  		NULL
  Return:
  		0: 返回值为0表示成功
  		~0: 非0表示失败
  Note: 
  History: 
*************************************************/
bc_err_e bc_pt_close_prj_mdl_file(bc_uint32 module_id, bc_char file_name[BC_PT_FILE_NAME_LEN_MAX]);



/*************************************************
  Function: bc_pt_get_prt_lvl
  Description: 获取打印的打印级别
  Input: 
  		prt_level		打印级别
  Output:
  		NULL
  Return:
  		0: 返回值为0表示成功
  		~0: 非0表示失败
  Note: 
  History: 
*************************************************/
bc_err_e bc_pt_get_prt_lvl(bc_uint32 *prt_level);



/*************************************************
  Function: bc_pt_get_prj_all
  Description: 获取整个工程(所有模块)数据信息
  Input: 
  		void
  Output:
  		NULL
  Return:
  		0: 返回值为0表示成功
  		~0: 非0表示失败
  Note: 整个工程的信息包括所有模块ID、所有的文件名
  		 等信息
  History: 
*************************************************/
bc_err_e bc_pt_get_prj_all(bc_pt_prj_flg_t *all_prj);
#endif

#if 0
/*************************************************
  Function: bc_pt_dbg_init
  Description: 初始化调试配置
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
bc_err_e bc_pt_dbg_init(void);



/*************************************************
  Function: bc_pt_dbg_save_cfg
  Description: 保存调试配置数据到文件
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
bc_err_e bc_pt_dbg_save_cfg(void);



/*************************************************
  Function: bc_pt_dbg_save_clear
  Description: 清除调试配置文件和内存调试数据
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
bc_err_e bc_pt_dbg_save_clear(void);
#endif



#endif

