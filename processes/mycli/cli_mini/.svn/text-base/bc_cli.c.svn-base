
/*******************************************************************************
  Copyright (C), 1988-2015, xxxxx Tech. Co., Ltd.
  [File name]  : \\BC\cli_mini\bc_cli.c
  [Author]     : wangbin
  [Version]    : 1.0
  [Date]       : 2015-01-20
  [Description]: 
  
  [Others]     :

  [Function List]:
    1. ....
    2. ....
  [History]:
     D a t e    Modification                                          Initials
    ---------- --------------                                        ----------
    2015-01-20  Created                                               
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              头   文   件                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/un.h>
#include <getopt.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

#include "bc_common_defs.h"
#include "bc_modules.h"
#include "bc_platform_init.h"
#include "bc_print.h"
#include "bc_vfs.h"

#include "bc_cli.h"
#include "bc_cli_type.h"
#include "bc_cli_mainprocess.h"
#include "bc_cli_cmds.h"

#include "bc_filetrans_file.h"



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                      外 部 变 量、 函 数 引 用                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//extern void cmd_file_config_file_load(char *filename, char flg);



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                      结   构   体   宏   定   义                           //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
/*
 *      当源文件需要定义宏，而头文件又与其它模块头文件中的宏定义有重复定义嫌疑
 *  时，在此处定义。
 */


typedef enum enum_start_up_mode
{
	UP_WAIT_CMD = 0,	/* 命令行输入模式：初始化运行环境，并运行shell */
	UP_LOAD_USR_CFG,	/* 加载用户配置模式：加载出厂默认配置及用户配置 */
	UP_ARG_CMD,
	UP_READ_FILE,
	UP_MAX_MODE
} start_mode_e;

typedef struct tag_start_up_arg
{
	cli_link_t		link_type;
	start_mode_e	mode;
	char            *pgm_name;
	char        	*arg;
} start_arg_t;




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

static unsigned int 	l_mdl_id = BC_MODULE_CLI;
static start_arg_t 		l_run_arg = {0};


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              函  数  声  明                                //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              函  数  定  义                                //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
/******************************************************************************\
  Function   : main
  Description: 
  Return     : 
  Others     : 
\******************************************************************************/
int
main
(
    int argc,
    char **argv,
    char **env
)
{
	/* 初始化基本模块 */
	bc_pt_init();
	bc_platform_init();
	bc_file_init();
	bc_filetrans_init();

	/* 初始化cli kernel以及注册命令 */
	cli_ker_init();
	cli_ker_cmd_reg();
	bc_cli_app_cmd_reg();

	/* ------------------------------------------------------------------- */
	
	/* ------------------------------------------------------------------- */
	switch (l_run_arg.mode)
	{
	case UP_WAIT_CMD:/* 命令行输入模式：初始化运行环境，并运行shell */
		CLI_DBG_CPL(l_mdl_id, "UP_WAIT_CMD\n");
		cli_io_task(NULL);
		break;

	default:
		CLI_DBG_CPL(l_mdl_id, "Unknown program mode!\r\n");
		break;
	}

    return 0;
}




/* 
 *	预留一个注释在文件最后
 */
/******************************************************************************\
  Function   : 
  Description: 
  Return     : 
  Others     : 
\******************************************************************************/

