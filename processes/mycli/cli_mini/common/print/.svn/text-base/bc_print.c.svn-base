/************************************************************
  Copyright (C), 1988-2014, xxxxx Tech. Co., Ltd.
  FileName: \\OLT\common\print\bc_print.c
  Author:  wangbin      Version :  1.0        Date:2014-4-25
  Description:                   
  Version:                        
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              头   文   件                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>

#include "bc_print.h"
#include "bc_modules.h"



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

static bc_uint8				bc_print_init_flag = 0;

static bc_uint32			bc_print_prt_lvl   = 0;

static bc_pt_prj_flg_t		bc_print_prt_flg;



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              函  数  声  明                                //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
#define BC_PT_CHECK_INIT()		\
	do\
	{\
		if (0 == bc_print_init_flag)\
		{\
			return BC_ERR_PRINT_NOT_INIT;\
		}\
	} while(0)



#define BC_PT_CHECK_MODULE_ID(module_id)	\
	do\
	{\
		if (0 == module_id || (~0) == module_id)\
		{\
			return BC_ERR_PRINT_MDL_ID_EXCEED;\
		}\
	} while(0)



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              函  数  定  义                                //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
#if 1
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
void bc_pt_init_prt(void)
{
	bc_print_prt_lvl = 0;
	bc_print_prt_lvl |= (BC_LVL_BIT_INIT | BC_LVL_BIT_COMMAND | BC_LVL_BIT_EVENT | BC_LVL_BIT_WARNING | BC_LVL_BIT_ERROR);
	memset(&bc_print_prt_flg, 0x00, sizeof(bc_print_prt_flg));

	return;
}



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
void bc_pt_init(void)
{
	if (bc_print_init_flag != 0)
	{
		return;
	}

	bc_pt_init_prt();
	
	bc_print_init_flag = 1;
	return;
}
#endif

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
void bc_pt_prt_open_all(void)
{
	bc_print_prt_flg.flag = BC_PT_FLAG_ALL;
	memset(&bc_print_prt_flg.mdls, 0x00, sizeof(bc_pt_mdl_flg_t)*BC_PT_PRJ_MDL_NUM_MAX);

	return;
}



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
void bc_pt_prt_close_all(void)
{
	bc_print_prt_lvl = BC_LVL_BIT_NONE;
	memset(&bc_print_prt_flg, 0x00, sizeof(bc_print_prt_flg));

	bc_print_prt_flg.flag = BC_PT_FLAG_NONE;
	return;
}



/*************************************************
  Function: bc_pt_prt_this_mdl_en
  Description: 是否打印该模块
  Input: 
  		module_id		模块id
  Output:
  		NULL
  Return:
  		0:  返回FALSE表示不打印该模块
  		~0: 返回值为TRUE，表示打印该模块
  Note: 
  History: 
*************************************************/
bc_boolean bc_pt_prt_this_mdl_en(bc_uint32 module_id)
{
	bc_uint32		loop_mdl;

	if (0 == bc_print_init_flag)
	{
		return FALSE;
	}

	switch(bc_print_prt_flg.flag)
	{
	case BC_PT_FLAG_ALL:
		return TRUE;

	case BC_PT_FLAG_NONE:
		return FALSE;

	case BC_PT_FLAG_DETAIL:
	default:
		for (loop_mdl = 0; loop_mdl < BC_PT_MDL_FILE_NUM_MAX; loop_mdl++)
		{
			if (module_id == bc_print_prt_flg.mdls[loop_mdl].id)	
			{
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		}

		return FALSE;
	}
	
}



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
bc_boolean bc_pt_prt_this_file_en(bc_uint32 module_id, bc_uint8 *file_name)
{
	bc_uint32			loop_file;
	bc_pt_file_flg_t	*p_file;

	if (0 == bc_print_init_flag)
	{
		return FALSE;
	}

	if (BC_PT_FLAG_ALL == bc_print_prt_flg.mdls[module_id].flag)
	{
		return TRUE;
	}

	if (BC_PT_FLAG_NONE == bc_print_prt_flg.mdls[module_id].flag)
	{
		return FALSE;
	}

	p_file = bc_print_prt_flg.mdls[module_id].files;
	for (loop_file = 0; loop_file < BC_PT_MDL_FILE_NUM_MAX; loop_file++)
	{
		if (0 == strcmp((char *)file_name, (char *)((p_file + loop_file)->file_name)))
		{
			return TRUE;
		}
	}

	return FALSE;
}
#endif

#if 1
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
bc_int32 bc_pt_prt_lvl_en(bc_uint32 prt_level)
{
	return (bc_print_prt_lvl & (prt_level));
}



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
  		0: 返回FALSE则不打印该行语句
  		~0: 返回TRUE表示打印该行语句
  Note: 
  History: 
*************************************************/
bc_boolean bc_pt_prt_line_en(bc_uint32 module_id, bc_char *file_name, bc_uint32 line_num)
{
	bc_uint32			loop_mdl;
	bc_uint32			loop_file;
	bc_pt_file_flg_t	*p_file;

	if (0 == bc_print_init_flag)
	{
		return FALSE;
	}

	if (NULL == file_name)
	{
		return FALSE;
	}

	/* print or not print module */
	switch (bc_print_prt_flg.flag)
	{
	case BC_PT_FLAG_ALL:	/* print all modules in the project */
		return TRUE;
		
	case BC_PT_FLAG_NONE:	/* print nothing in the project */
		return FALSE;

	case BC_PT_FLAG_DETAIL:	/* l_prt_flg.flag = others */
	default:
		break;
	}

	/* search for module */
	for (loop_mdl = 0; loop_mdl < BC_PT_PRJ_MDL_NUM_MAX; loop_mdl++)
	{
		if (0 == bc_print_prt_flg.mdls[loop_mdl].id)
		{
			return FALSE;
		}

		if (module_id < bc_print_prt_flg.mdls[loop_mdl].id)
		{
			return FALSE;
		}

		if (module_id == bc_print_prt_flg.mdls[loop_mdl].id)
		{
			break;
		}
	}

	/* print or not print all files in the module */
	switch(bc_print_prt_flg.mdls[loop_mdl].flag)
	{
	case BC_PT_FLAG_ALL:		/* print all files in the module */
		return TRUE;

	case BC_PT_FLAG_NONE:		/* print nothing in the module */
		return FALSE;

	case BC_PT_FLAG_DETAIL:		/* l_prt_flg.mdls[loop_mdl].flag = others */
	default:
		break;
	}

	/* search for file, when l_prt_flg.mdls[mdl_id].flag = others */
	p_file = bc_print_prt_flg.mdls[loop_mdl].files;
	for (loop_file = 0; loop_file < BC_PT_MDL_FILE_NUM_MAX; loop_file++, p_file++)
	{
		if (0 == p_file->file_name[0])
		{
			continue;
		}

		if (0 != strncasecmp(file_name, (bc_char *)p_file->file_name, BC_PT_FILE_NAME_LEN_MAX))
		{
			continue;
		}

		if ((line_num >= p_file->line_start) && (line_num <= p_file->line_end))
		{
			return TRUE;
		}

		return FALSE;	/* not print this line */
	}

	return FALSE;		/* no this file */
}
#endif

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
bc_err_e bc_pt_prt_lvl_open(bc_int32 prt_level)
{
	BC_PT_CHECK_INIT();

	bc_print_prt_lvl |= (prt_level);

	return BC_ERR_OK;
}



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
bc_err_e bc_pt_prt_lvl_close(bc_int32 prt_level)
{
	BC_PT_CHECK_INIT();

	bc_print_prt_lvl &= (~prt_level);

	return BC_ERR_OK;
}



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
bc_err_e bc_pt_open_prj_all(void)
{
	BC_PT_CHECK_INIT();

	bc_print_prt_flg.flag = BC_PT_FLAG_ALL;
	memset(bc_print_prt_flg.mdls, 0x00, sizeof(bc_pt_mdl_flg_t) * BC_PT_PRJ_MDL_NUM_MAX);

	return BC_ERR_OK;
}



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
bc_err_e bc_pt_open_prj_mdl(bc_uint32 module_id)
{
	bc_uint32		loop_mdl  = 0;
	bc_uint32		mov_start = 0;
	bc_uint32		mov_end   = 0;

	BC_PT_CHECK_INIT();
	BC_PT_CHECK_MODULE_ID(module_id);

	/* search for module */
	for (loop_mdl = 0; loop_mdl < BC_PT_PRJ_MDL_NUM_MAX; loop_mdl++)
	{
		if (0 == bc_print_prt_flg.mdls[loop_mdl].id)	/* search for the end of valid buf, not found this module */
		{
			bc_print_prt_flg.flag = BC_PT_FLAG_DETAIL;
			bc_print_prt_flg.mdls[loop_mdl].id = module_id;
			bc_print_prt_flg.mdls[loop_mdl].flag = BC_PT_FLAG_ALL;
			memset(bc_print_prt_flg.mdls[loop_mdl].files, 0x00, sizeof(bc_pt_file_flg_t) * BC_PT_MDL_FILE_NUM_MAX);

			return BC_ERR_OK;
		}

		/* can match module */
		if (module_id == bc_print_prt_flg.mdls[loop_mdl].id)
		{
			bc_print_prt_flg.flag = BC_PT_FLAG_DETAIL;
			bc_print_prt_flg.mdls[loop_mdl].flag = BC_PT_FLAG_ALL;
			memset(bc_print_prt_flg.mdls[loop_mdl].files, 0x00, sizeof(bc_pt_file_flg_t) * BC_PT_MDL_FILE_NUM_MAX);

			return BC_ERR_OK;
		}

		/* no this module, insert this module if it has idle buffer */
		if (module_id < bc_print_prt_flg.mdls[loop_mdl].id)
		{
			break;
		}
	}

	/* no enough buffer and no this module */
	if (loop_mdl >= BC_PT_PRJ_MDL_NUM_MAX)
	{
		return BC_ERR_PRINT_MDL_ID_EXCEED;
	}

	/* no this module, insert this module if it has enough module buffer */
	mov_start = loop_mdl;
	for (loop_mdl++; loop_mdl < BC_PT_PRJ_MDL_NUM_MAX; loop_mdl++)
	{
		if (0 == bc_print_prt_flg.mdls[loop_mdl].id)	/* it has an idle module buffer */
		{
			mov_end = loop_mdl;
			break;
		}
	}

	if (loop_mdl >= BC_PT_PRJ_MDL_NUM_MAX)
	{
		return BC_ERR_PRINT_MDL_ID_EXCEED;
	}

	/* it has an idle module buf, move back old module bufs one by one */
	memmove(&bc_print_prt_flg.mdls[mov_start+1], &bc_print_prt_flg.mdls[mov_start], sizeof(bc_pt_mdl_flg_t) * (mov_end-mov_start));

	/* insert new module */
	bc_print_prt_flg.flag = BC_PT_FLAG_DETAIL;
	bc_print_prt_flg.mdls[mov_start].id = module_id;
	bc_print_prt_flg.mdls[mov_start].flag = BC_PT_FLAG_ALL;
	memset(bc_print_prt_flg.mdls[mov_start].files, 0x00, sizeof(bc_pt_file_flg_t) * BC_PT_MDL_FILE_NUM_MAX);

	return BC_ERR_OK;
}



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
bc_err_e bc_pt_open_prj_mdl_file(bc_uint32 module_id, bc_pt_file_flg_t *file)
{	
	bc_int32				loop_file 	= 0;
	bc_int32				name_cmpare	= 0;
	bc_uint32				loop_mdl	= 0;
	bc_uint32				mov_start 	= 0;
	bc_uint32				mov_end		= 0;
	bc_pt_file_flg_t		*p_file_buf = NULL;

	BC_PT_CHECK_INIT();
	BC_PT_CHECK_MODULE_ID(module_id);

	if (NULL == file)
	{
		return BC_ERR_PARA;
	}

	if ((0 == file->file_name[0]) || (file->line_end < file->line_start))
	{
		return BC_ERR_PARA;
	}

	/* search for module */
	for (loop_mdl = 0; loop_mdl < BC_PT_PRJ_MDL_NUM_MAX; loop_mdl++)
	{
		if (0 == bc_print_prt_flg.mdls[loop_mdl].id)	/* search for the end of the valid buf, no this module */
		{
			bc_print_prt_flg.flag = BC_PT_FLAG_DETAIL;
			bc_print_prt_flg.mdls[loop_mdl].id = module_id;
			bc_print_prt_flg.mdls[loop_mdl].flag = BC_PT_FLAG_DETAIL;
			memset(bc_print_prt_flg.mdls[loop_mdl].files, 0x00, sizeof(bc_pt_file_flg_t) * BC_PT_MDL_FILE_NUM_MAX);

			return BC_ERR_OK;
		}

		/* can match module */
		if (module_id == bc_print_prt_flg.mdls[loop_mdl].id)
		{
			p_file_buf = bc_print_prt_flg.mdls[loop_mdl].files;
			for (loop_file = 0; loop_file < BC_PT_MDL_FILE_NUM_MAX; loop_file++, p_file_buf++)
			{
				if (0 == p_file_buf->file_name[0])	/* found the idle buffer */
				{
					printf("p_file_buf->file_name[0][%s] == 0\n", (bc_char *)p_file_buf->file_name);
					bc_print_prt_flg.mdls[loop_mdl].flag = BC_PT_FLAG_DETAIL;
					memcpy(&bc_print_prt_flg.mdls[loop_mdl].files[loop_file], file, sizeof(bc_pt_file_flg_t));

					return BC_ERR_OK;
				}

				name_cmpare = strncasecmp((bc_char *)p_file_buf->file_name, (bc_char *)file->file_name, BC_PT_FILE_NAME_LEN_MAX);
				/* file name match */
				if (0 == name_cmpare)
				{
					printf("file->file_name[%s] == p_file_buf->file_name[%s]\n", (bc_char *)file->file_name, (bc_char *)p_file_buf->file_name);
					p_file_buf->line_start = file->line_start;
					p_file_buf->line_end   = file->line_end;

					return BC_ERR_OK;
				}

				/* insert */
				if (0 < name_cmpare)
				{
					printf("file->file_name[%s] < p_file_buf->file_name[%s]\n", (bc_char *)file->file_name, (bc_char *)p_file_buf->file_name);
					break;
				}
			}

			/* no idle buffer */
			if (loop_file >= BC_PT_MDL_FILE_NUM_MAX)
			{
				return BC_ERR_PRINT_FILE_NUM_EXCEED;
			}

			/* no this file, insert this file if it has enough file buffer */
			mov_start = loop_file;
			for (p_file_buf++, loop_file++; loop_file < BC_PT_MDL_FILE_NUM_MAX; p_file_buf++, loop_file++)
			{
				if (0 == p_file_buf->file_name[0])	/* it has an idle module buffer */
				{
					mov_end = loop_file;
					break;
				}
			}

			if (loop_file >= BC_PT_MDL_FILE_NUM_MAX)
			{
				return BC_ERR_PRINT_FILE_NUM_EXCEED;
			}

			memmove(&bc_print_prt_flg.mdls[loop_mdl].files[mov_start+1], &bc_print_prt_flg.mdls[loop_mdl].files[mov_start], 
					sizeof(bc_pt_file_flg_t) * (mov_end-mov_start));


			/* insert new module */
			memset(&bc_print_prt_flg.mdls[loop_mdl].files[mov_start], 0x00, sizeof(bc_pt_file_flg_t));
			memcpy(&bc_print_prt_flg.mdls[loop_mdl].files[mov_start], file, sizeof(bc_pt_file_flg_t));

			return BC_ERR_OK;
		}

		/* no this module, insert this module if it has an idle module buffer */
		if (module_id < bc_print_prt_flg.mdls[loop_mdl].id)
		{
			break;
		}
	}

	/* no enough buffer and no this module */
	if (loop_mdl >= BC_PT_PRJ_MDL_NUM_MAX)
	{
		return BC_ERR_PRINT_MDL_ID_EXCEED;
	}

	/* no this module, insert this module if it has enough module buffer */
	mov_start = loop_mdl;
	for (loop_mdl++; loop_mdl < BC_PT_PRJ_MDL_NUM_MAX; loop_mdl++)
	{
		if (0 == bc_print_prt_flg.mdls[loop_mdl].id)	/* it has an idle module buffer */
		{
			mov_end = loop_mdl;
			break;
		}
	}

	if (loop_mdl >= BC_PT_PRJ_MDL_NUM_MAX)
	{
		return BC_ERR_PRINT_MDL_ID_EXCEED;
	}

	/* It has an idle module buffer, move back old module buffers one by one */
	memmove(&bc_print_prt_flg.mdls[mov_start+1], &bc_print_prt_flg.mdls[mov_start], 
			sizeof(bc_pt_mdl_flg_t) * (mov_end-mov_start));

	/* insert new module */
	bc_print_prt_flg.flag = BC_PT_FLAG_DETAIL;
	bc_print_prt_flg.mdls[mov_start].id = module_id;
	bc_print_prt_flg.mdls[mov_start].flag = BC_PT_FLAG_DETAIL;
	memset(bc_print_prt_flg.mdls[mov_start].files, 0x00, sizeof(bc_pt_file_flg_t) * BC_PT_MDL_FILE_NUM_MAX);
	memcpy(bc_print_prt_flg.mdls[mov_start].files, file, sizeof(bc_pt_file_flg_t));

	return BC_ERR_OK;
}



/*************************************************
  Function: bc_pt_close_prj_all
  Description: 关闭整个工程(所有模块的所有文件)的打印
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
bc_err_e bc_pt_close_prj_all(void)
{
	BC_PT_CHECK_INIT();

	bc_print_prt_flg.flag = BC_PT_FLAG_NONE;
	memset(bc_print_prt_flg.mdls, 0x00, sizeof(bc_pt_mdl_flg_t) * BC_PT_PRJ_MDL_NUM_MAX);

	return BC_ERR_OK;
}



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
bc_err_e bc_pt_close_prj_mdl(bc_uint32 module_id)
{
	bc_int32		loop_mdl = 0;

	BC_PT_CHECK_INIT();
	BC_PT_CHECK_MODULE_ID(module_id);

	if (BC_PT_FLAG_NONE == bc_print_prt_flg.flag)
	{
		return BC_ERR_OK;
	}

	if (BC_PT_FLAG_ALL == bc_print_prt_flg.flag)
	{
		return BC_ERR_PRINT_MDL_ID_EXCEED;
	}

	for (loop_mdl = 0; loop_mdl < BC_PT_PRJ_MDL_NUM_MAX; loop_mdl++)
	{
		if (0 == bc_print_prt_flg.mdls[loop_mdl].id)
		{
			return BC_ERR_OK;
		}

		if (module_id == bc_print_prt_flg.mdls[loop_mdl].id)
		{
			memmove(&bc_print_prt_flg.mdls[loop_mdl], &bc_print_prt_flg.mdls[loop_mdl+1], 
					sizeof(bc_pt_mdl_flg_t) * (BC_PT_PRJ_MDL_NUM_MAX - 1 - loop_mdl));
			memset(&bc_print_prt_flg.mdls[BC_PT_PRJ_MDL_NUM_MAX-1], 0x00, sizeof(bc_pt_mdl_flg_t));

			return BC_ERR_OK;
		}

		if (module_id < bc_print_prt_flg.mdls[loop_mdl].id)
		{
			return BC_ERR_OK;
		}
	}

	return BC_ERR_OK;
}



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
bc_err_e bc_pt_close_prj_mdl_file(bc_uint32 module_id, bc_char file_name[BC_PT_FILE_NAME_LEN_MAX])
{
	bc_int32				loop_file    = 0;
	bc_int32				name_compare = 0;
	bc_int32				loop_mdl	 = 0;
	bc_pt_file_flg_t		*p_file_buf  = NULL;

	BC_PT_CHECK_INIT();
	BC_PT_CHECK_MODULE_ID(module_id);

	if (0 == file_name[0])
	{
		return BC_ERR_PARA;
	}

	if (BC_PT_FLAG_NONE == bc_print_prt_flg.flag)
	{
		return BC_ERR_OK;
	}

	if (BC_PT_FLAG_ALL == bc_print_prt_flg.flag)
	{
		return BC_ERR_PRINT_MDL_ID_EXCEED;
	}

	for (loop_mdl = 0; loop_mdl < BC_PT_PRJ_MDL_NUM_MAX; loop_mdl++)
	{
		if (0 == bc_print_prt_flg.mdls[loop_mdl].id)
		{
			return BC_ERR_OK;
		}

		if (module_id == bc_print_prt_flg.mdls[loop_mdl].id)
		{
			p_file_buf = bc_print_prt_flg.mdls[loop_mdl].files;
			for (loop_file = 0; loop_file < BC_PT_MDL_FILE_NUM_MAX; loop_file++, p_file_buf++)
			{
				if (0 == p_file_buf->file_name[0])	/* no file */
				{
					return BC_ERR_OK;
				}

				name_compare = strncasecmp((bc_char *)file_name, (bc_char *)p_file_buf->file_name, BC_PT_FILE_NAME_LEN_MAX);

				if (0 == name_compare)	/* file name match */
				{
					if(0 != (BC_PT_MDL_FILE_NUM_MAX - 1 - loop_file))
					{
						memmove(p_file_buf, p_file_buf + 1, sizeof(bc_pt_file_flg_t) * (BC_PT_MDL_FILE_NUM_MAX - 1 - loop_file));
					}

					memset(&bc_print_prt_flg.mdls[loop_mdl].files[BC_PT_FILE_NAME_LEN_MAX - 1], 0x00, sizeof(bc_pt_mdl_flg_t));

					return BC_ERR_OK;
				}

				if (0 > name_compare)
				{
					return BC_ERR_OK;
				}

			}

			return BC_ERR_OK;
		}

		if (module_id < bc_print_prt_flg.mdls[loop_mdl].id)
		{
			return BC_ERR_OK;
		}
	}

	return BC_ERR_OK;
}



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
bc_err_e bc_pt_get_prt_lvl(bc_uint32 *prt_level)
{
	BC_PT_CHECK_INIT();

	if (NULL == prt_level)
	{
		return BC_ERR_PRINT_NOT_INIT;
	}

	*prt_level = bc_print_prt_lvl;

	return BC_ERR_OK;
}



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
bc_err_e bc_pt_get_prj_all(bc_pt_prj_flg_t *all_prj)
{
	BC_PT_CHECK_INIT();

	if (NULL == all_prj)
	{
		return BC_ERR_PRINT_NOT_INIT;
	}

	memcpy(all_prj, &bc_print_prt_flg, sizeof(bc_pt_prj_flg_t));

	return BC_ERR_OK;
}
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
  		0: 返回值为0表示成功
  		~0: 非0表示失败
  Note: 
  History: 
*************************************************/
bc_err_e bc_pt_dbg_init(void)
{
	bc_file		*fp_dbg 	= NULL;

	if (BC_ERR_OK == bc_file_access(BC_PT_DBG_FILE, BC_VFS_ROOT_C, BC_VFS_F_OK))
	{
		fp_dbg = bc_file_open(BC_PT_DBG_FILE, BC_VFS_READ_BRW, BC_VFS_ROOT_C, BC_MODULE_PRINT);
		if (NULL == fp_dbg)
		{
			BC_PT_DBG_CPL(BC_MODULE_PRINT, "open debug configuration file failed!\r\n");
			return BC_ERR_VFS_OPEN_FAIL;
		}
	}
	else
	{
		fp_dbg = bc_file_open(BC_PT_DBG_FILE, BC_VFS_WRITE_BRW, BC_VFS_ROOT_C, BC_MODULE_PRINT);
		if (NULL == fp_dbg)
		{
			BC_PT_DBG_CPL(BC_MODULE_PRINT, "create debug configuration file failed!\r\n");
			return BC_ERR_VFS_OPEN_FAIL;
		}
	}

	bc_file_read(&bc_print_prt_lvl, sizeof(bc_uint32), 1, fp_dbg);
	bc_file_read(&bc_print_prt_flg, sizeof(bc_pt_prj_flg_t), 1, fp_dbg);
	
	bc_file_close(fp_dbg, BC_MODULE_PRINT, BC_PT_DBG_FILE);
	return BC_ERR_OK;
}



/*************************************************
  Function: bc_pt_dbg_save_cfg
  Description: 保存调试配置数据到文件
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
bc_err_e bc_pt_dbg_save_cfg(void)
{
	FILE		*fp_dbg 	= NULL;
	bc_uint8	wrt_count	= 0;

	fp_dbg = bc_file_open(BC_PT_DBG_FILE, BC_VFS_WRITE_BRW, BC_VFS_ROOT_C, BC_MODULE_PRINT);
	if (NULL == fp_dbg)
	{
		BC_PT_DBG_CPL(BC_MODULE_PRINT, "open debug configuration file failed!\r\n");
		return BC_ERR_VFS_OPEN_FAIL;
	}

	wrt_count = bc_file_write(&bc_print_prt_lvl, sizeof(bc_uint32), 1, fp_dbg);
	if (0 == wrt_count)
	{
		BC_PT_DBG_CPL(BC_MODULE_PRINT, "write debug configuration file failed!\r\n");
		bc_file_close(fp_dbg, BC_MODULE_PRINT, BC_PT_DBG_FILE);
		return BC_ERR_PRINT_FILE_WRITE_ERROR;
	}

	wrt_count = bc_file_write(&bc_print_prt_flg, sizeof(bc_pt_prj_flg_t), 1, fp_dbg);
	if (0 == wrt_count)
	{
		BC_PT_DBG_CPL(BC_MODULE_PRINT, "write debug configuration file failed!\r\n");
		bc_file_close(fp_dbg, BC_MODULE_PRINT, BC_PT_DBG_FILE);
		return BC_ERR_PRINT_FILE_WRITE_ERROR;
	}

	bc_file_close(fp_dbg, BC_MODULE_PRINT, BC_PT_DBG_FILE);
	return BC_ERR_OK;
}



/*************************************************
  Function: bc_pt_dbg_save_clear
  Description: 清除调试配置文件和内存调试数据
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
bc_err_e bc_pt_dbg_save_clear(void)
{
	bc_err_e   		ret = BC_ERR_OK;

	/* 恢复原始初始化状态 */
	bc_pt_init_prt();
	
	ret = bc_file_delete(BC_PT_DBG_FILE, BC_VFS_ROOT_C);
	if (BC_ERR_OK != ret)
	{
		BC_PT_DBG_CPL(BC_MODULE_PRINT, "delete print debug file failed!\r\n");
		return ret;
	}
	
	BC_PT_DBG_CPL(BC_MODULE_PRINT, "PT DBG clear file OK!\r\n");
	return BC_ERR_OK;
}
#endif


