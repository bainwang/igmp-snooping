/*******************************************************************************
  Copyright (C), 1988-2012, xxxxx Tech. Co., Ltd.
  [File name]  : \\BC\ktapi_sys_global_info.c
  [Author]     : wangbin
  [Version]    : 1.0
  [Date]       : 2012-06-11
  [Description]:

  [Others]     :

  [Function List]:  
    1. ....
    2. ....
  [History]:
	 D a t e    Modification 										  Initials
	---------- --------------                                        ----------
	2014-08-04  Created												  wangbin
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								头   文   件								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////


#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

#include "bc_err.h"
#include "bc_print.h"
//#include "bc_ipc_def.h"
//#include "bc_ipc_package.h"
#include "bc_platform_mutex.h"
#include "bc_platform_time.h"

#include "bc_platform_thread.h"
#include "bc_platform_sem.h"
#include "bc_platform_mem.h"
#include "utili_string.h"
#include "bc_filetrans_def.h"
#include "bc_vfs.h"
//#include "bc_modules_com_para.h"
#include "bc_filetrans_db.h"



////////////////////////////////////////////////////////////////////////////////
//																			  //
//						外 部 变 量、 函 数 引 用					          //
//																			  //
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//																			  //
//						结   构   体   宏   定   义							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
/*
 *		当源文件需要定义宏，而头文件又与其它模块头文件中的宏定义有重复定义嫌疑
 *	时，在此处定义。
 */

#if 1
#define CHECK_FTP_FNCT_ID(trans_fun) \
	do \
	{ \
		if((trans_fun < BC_FILETRANS_KERNEL)||(trans_fun >= BC_FILETRANS_MAX)) \
		{ \
			BC_PT_DBG_CPL(BC_MODULE_FILETRANS, "error ftp function id : [%d]\r\n", trans_fun); \
			return BC_ERR_FILETRANS_FUN_ERROR; \
		} \
	} while(0)


#define UN_USED_INDEX  (-1)
#endif

////////////////////////////////////////////////////////////////////////////////
//																			  //
//							全 局 变 量 定 义							      //
//																			  //
////////////////////////////////////////////////////////////////////////////////
/* 
 *	外部全局变量，提供整个工程调用，在头文件中提供调用接口(外部引用声明)。
 */
#if 1
static bc_filetrans_cfg_t g_filetrans_cfg[BC_FILETRANS_MAX] = 
{
		{BC_FILETRANS_TYPE_TFTP, 0,"","",BC_FILETRANS_S_FILE_NAME_KERNEL,BC_FILETRANS_D_FILE_NAME_KERNEL,
			BC_FILETRANS_KERNEL,BC_FILETRANS_ACTION_NONE,BC_FILETRANS_STATUS_IDLE,0,FALSE},
		{BC_FILETRANS_TYPE_TFTP, 0,"","",BC_FILETRANS_S_FILE_NAME_ROOT_FS,BC_FILETRANS_D_FILE_NAME_ROOT_FS,
			BC_FILETRANS_ROOT_FS,BC_FILETRANS_ACTION_NONE,BC_FILETRANS_STATUS_IDLE,0,FALSE},
		{BC_FILETRANS_TYPE_TFTP, 0,"","",BC_FILETRANS_S_FILE_NAME_USER_FS,BC_FILETRANS_D_FILE_NAME_USER_FS,
			BC_FILETRANS_USER_FS,BC_FILETRANS_ACTION_NONE,BC_FILETRANS_STATUS_IDLE,0,FALSE},
		{BC_FILETRANS_TYPE_TFTP, 0,"","",BC_FILETRANS_S_FILE_NAME_OLT,BC_FILETRANS_D_FILE_NAME_OLT,
			BC_FILETRANS_OLT,BC_FILETRANS_ACTION_NONE,BC_FILETRANS_STATUS_IDLE,0,FALSE},
		{BC_FILETRANS_TYPE_TFTP, 0,"","",BC_FILETRANS_S_FILE_NAME_DBTB,BC_FILETRANS_D_FILE_NAME_DBTB,
			BC_FILETRANS_DBTB,BC_FILETRANS_ACTION_NONE,BC_FILETRANS_STATUS_IDLE,0,FALSE},
		{BC_FILETRANS_TYPE_TFTP, 0,"","",BC_FILETRANS_S_FILE_NAME_UBOOT,BC_FILETRANS_D_FILE_NAME_UBOOT,
			BC_FILETRANS_UBOOT,BC_FILETRANS_ACTION_NONE,BC_FILETRANS_STATUS_IDLE,0,FALSE},
};
#endif


#if 1
#define BC_FILETRANS_USB_AREA_MAX		4
#define BC_FILETRANS_USBFILE_NAME_LEN		32

static bc_char usb_area[BC_FILETRANS_USB_AREA_MAX][BC_FILETRANS_USBFILE_NAME_LEN] = {
		"/media/sda1/",
		"/media/sda2/",
		"/media/sda3/",
		"/media/sda4/"};
#endif


/* 
 *	内部全局变量，只提供给该文件内部函数调用，不在头文件中提供调用接口。
 */
#if 1
#define STARTUP_FILE        "/usr/local/etc/startup_file"         //系统启动配置
#define UPDATE_FLAG_FILE    "/usr/local/etc/update_flag"          //升级标识文件 存在即首次升级文成，将*.so文件复制到/usr/lib目录下
#endif
////////////////////////////////////////////////////////////////////////////////
//																			  //
//								函  数  声  明							      //
//																			  //
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//																			  //
//								函  数  定  义							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////


/******************************************************************************\
  Function   : bc_filetrans_get_filetrans_cfg_db
  Description: bc_filetrans_get_filetrans_cfg_db
  Return     : bool true: 成功  false:非零失败
  Others     : 
\******************************************************************************/
bc_filetrans_cfg_t*  bc_filetrans_get_filetrans_cfg_db(void)
{
	return (bc_filetrans_cfg_t*)g_filetrans_cfg;
}

#if 1

/******************************************************************************\
  Function   : __bc_filetrans_get_boot_flag
  Description: 获取boot flag
  Return     : 0: 主分区  1:备份区
  Others     : 
\******************************************************************************/
bc_int32 bc_filetrans_get_boot_flag_db( )
{
	char buf[1024];
	FILE *lp = NULL;

	memset(buf, 0, sizeof(buf));
	if((lp = popen("fw_printenv bootflag", "r")) == NULL)
	{
		printf("popen() error!\n");
		return BC_ERR_FILETRANS_ACCESS_ERROR;
	}
	fgets(buf, sizeof(buf), lp);
	pclose(lp);

	BC_PT_DBG_CPL(BC_MODULE_FILETRANS, "get boot flag, buf = %s!\n\r", buf);

	if(memcmp(buf, "bootflag=0", sizeof("bootflag=0")) == 0)
	{
		BC_PT_DBG_CPL(BC_MODULE_FILETRANS, "bootflag=0 !\n\r");
		return 0;
	}
	else
	{
		BC_PT_DBG_CPL(BC_MODULE_FILETRANS, "bootflag=1 !\n\r");
		return 1; 
	}
}


/******************************************************************************\
  Function   : __bc_filetrans_set_startup_flag
  Description: 设置 startup flag 
  Return     : 0: 主分区  1:备份区
  Others     : 
\******************************************************************************/
bc_int32 bc_filetrans_set_startup_flag_db(bc_int32 flag)
{
	FILE *fp;

	if((fp=fopen(STARTUP_FILE, "w"))!=NULL)
	{         
		fprintf(fp,"startupflag=%d", flag);
		fclose(fp);

		return 0;
	}    
	else
	{
		return -1;
	} 
}

/******************************************************************************\
  Function   : __bc_filetrans_get_startup_flag
  Description: 设置 startup flag 
  Return     : 0: 主分区  1:备份区
  Others     : 
\******************************************************************************/
bc_int32 bc_filetrans_get_startup_flag_db()
{
	bc_char link[128];
	bc_char path[128];   

	memset(link, 0, sizeof(link));
	memset(path, 0, sizeof(path));
	
	sprintf(link, "/proc/%d/exe", getpid());   
	readlink(link, path, sizeof(path));     

	if(strstr(path, "fwbak") == 0)
	{
		return BC_FILETRANS_STARTUP_AREA_MAIN;
	}
	else
	{
		return BC_FILETRANS_STARTUP_AREA_SLAVE; 
	}
}

/******************************************************************************\
  Function   : __bc_filetrans_set_update_flag
  Description: 设置 update flag 
  Return     : 0: 主分区升级完成  1:备份分区升级完成
  Others     : 
\******************************************************************************/
bc_int32 bc_filetrans_set_update_flag_db(bc_int32 flag)
{
	FILE *fp;

	if((fp=fopen(UPDATE_FLAG_FILE, "w"))!=NULL)
	{         
		fprintf(fp,"updateflag=%d", flag);
		fclose(fp);
		return 0;
	}    
	else
	{
		return -1;
	} 
}
#endif

#if 1

/******************************************************************************\
  Function   : bc_filetrans_file_db_get_usb_area
  Description: 判断USB文件所在区
  Return     : ktep_errcode_e  成功、失败
  Others     : 
\******************************************************************************/
bc_boolean __bc_filetrans_file_db_get_usb_area_2(bc_char *filename, bc_int32 *area)
{
	int i = 0;
	bc_char cmd[255];
	for(i=0; i<BC_FILETRANS_USB_AREA_MAX; i++)
	{
		memset(cmd, 0, sizeof(cmd));
		snprintf(cmd, sizeof(cmd), "%s%s", usb_area[i], filename);
		
		if(bc_filetrans_file_is_exist_db(cmd))
		{
			*area = i+1;
		//	printf("usb file area is %d.\r\n", i+1);
			return TRUE;
		}
	}
	
	return FALSE;
}

/******************************************************************************\
  Function   : bc_filetrans_ipv4_to_str_db
  Description: Ip转换
  Return     : ktep_errcode_e  成功、失败
  Others     : 
\******************************************************************************/
bc_err_e bc_filetrans_ipv4_to_str_db(bc_int32 str, bc_char* ip_str)
{
	memset(ip_str, 0, sizeof(ip_str));
	return utili_ipv4_to_str(str, ip_str);
}

/******************************************************************************\
  Function   : bc_filetrans_file_is_exist_db
  Description: 判断文件是否存在
  Return     : ktep_errcode_e  成功、失败
  Others     : 
\******************************************************************************/
bc_boolean bc_filetrans_file_is_exist_db(bc_char *filename)
{
	if(access(filename, 0) == 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/******************************************************************************\
  Function   : bc_filetrans_exec_shell_command
  Description: 执行shell 命令
  Return     : 0: 成功  1:非零失败
  Others     : 
\******************************************************************************/
bc_int32 bc_filetrans_exec_shell_command_db(char* cmd, char retvalue[BC_F_MAX_SHELL_CMD_LEN])
{
	char tbuf[BC_F_MAX_SHELL_CMD_LEN];
	FILE *fp = NULL;

	memset(tbuf, 0, sizeof(tbuf));
	if((fp = popen(cmd, "r")) == NULL)
	{
		return -1;
	}
	
	while (fgets(tbuf, BC_F_MAX_SHELL_CMD_LEN, fp) != NULL) 
	{
		if((strlen(tbuf) + strlen(retvalue)) < BC_F_MAX_SHELL_CMD_LEN)
		{
			sprintf(retvalue, "%s%s", retvalue, tbuf);
		}

		memset(tbuf, 0, sizeof(tbuf));
	}

	pclose(fp);

	return 0;
}
#endif



/******************************************************************************\
  Function   : bc_filetrans_set_info_db
  Description: 设置传输信息
  Return     : ktep_errcode_e  成功、失败
  Others     : 下载时只能修改源文件，上传时只能修改目 的文件
\******************************************************************************/
bc_err_e bc_filetrans_set_info_db(bc_filetrans_function_e trans_fun, bc_filetrans_cfg_t para)
{	
	bc_int32 __area = 0;
	if(g_filetrans_cfg[trans_fun].status == BC_FILETRANS_STATUS_INPROGRESS)
	{
	   	return BC_ERR_FILETRANS_SET_ERROR;
	}

	g_filetrans_cfg[trans_fun].proto_type = para.proto_type;
	g_filetrans_cfg[trans_fun].ip = para.ip;
	strcpy(g_filetrans_cfg[trans_fun].usr_name, para.usr_name);
	strcpy(g_filetrans_cfg[trans_fun].psswrd, para.psswrd);

	memset(g_filetrans_cfg[trans_fun].src_file_name, 0, sizeof(g_filetrans_cfg[trans_fun].src_file_name));
	if(para.proto_type == BC_FILETRANS_TYPE_USB)
	{
		if(!__bc_filetrans_file_db_get_usb_area_2(para.src_file_name, &__area))
		{
			return BC_ERR_FILETRANS_USB_AREA_NONEXIST;
		}
		snprintf(g_filetrans_cfg[trans_fun].src_file_name, sizeof(g_filetrans_cfg[trans_fun].src_file_name), "%s%s", usb_area[__area-1], para.src_file_name);
	}
	else
	{
		strcpy(g_filetrans_cfg[trans_fun].src_file_name, para.src_file_name);
	}
	
//	strcpy(g_filetrans_cfg[trans_fun].src_file_name, para.src_file_name);

	g_filetrans_cfg[trans_fun].status = BC_FILETRANS_STATUS_IDLE;
	g_filetrans_cfg[trans_fun].prog_value = 0;  

	return BC_ERR_OK;
}

/******************************************************************************\
  Function   : bc_filetrans_get_info_db
  Description: 获取某个文 件的传输信息
  Return     : ktep_errcode_e  成功、失败
  Others     : 
\******************************************************************************/
bc_err_e bc_filetrans_get_info_db(bc_filetrans_function_e trans_fun, bc_filetrans_cfg_t *para)
{
	memcpy(para, &g_filetrans_cfg[trans_fun], sizeof(bc_filetrans_cfg_t));
	
	return BC_ERR_OK;
}


#if 1
/******************************************************************************\
  Function   : bc_filetrans_db_update
  Description: 传输文件到OLT
  Return     : bool true: 成功  false:非零失败
  Others     : 
\******************************************************************************/
bc_boolean bc_filetrans_db_update(char into_dir[255], bc_filetrans_cfg_t *trans_cfg)
{
	char cmd[255];
	bc_char str_ip[16];
	bc_char _tmp_file_name[BC_MODULE_NAME_LENGTH];

	memcpy(_tmp_file_name, trans_cfg->dst_file_name, sizeof(trans_cfg->dst_file_name));

	/*进入TMP，清除文件*/
	if (trans_cfg->trans_fun == BC_FILETRANS_OLT)
	{
		if (system(CMD_RM_RF_TMP_TMPDIR) < 0)
		{
			return FALSE;
		}
		if (system(CMD_MKDIR_TMP_TMPDIR) < 0)
		{
			return FALSE;
		}
		
		chdir(into_dir);
	}
	else
	{
		chdir(into_dir);
		bc_file_delete(_tmp_file_name, into_dir);
	}
	trans_cfg->prog_value = 15;

	/*将文件从HOST中拷贝到TMP目录*/
	memset(cmd, 0, sizeof(cmd));

	if(trans_cfg->proto_type == BC_FILETRANS_TYPE_USB)
	{
		snprintf(cmd, sizeof(cmd), "cp %s %s", trans_cfg->src_file_name, into_dir);
		if(system(cmd) < 0)
		{
			return FALSE;
		}
		snprintf(cmd, sizeof(cmd), "mv %s %s", trans_cfg->src_file_name, _tmp_file_name);
	}
	else
	{
		bc_filetrans_ipv4_to_str_db(trans_cfg->ip, str_ip);
		if (trans_cfg->proto_type == BC_FILETRANS_TYPE_FTP)	
		{
			snprintf(cmd, sizeof(cmd), "ftpget -u %s -p %s %s %s %s", trans_cfg->usr_name, trans_cfg->psswrd, str_ip, _tmp_file_name, trans_cfg->src_file_name);	
		}
		else	
		{
			snprintf(cmd, sizeof(cmd), "tftp -g -l %s -r %s %s", _tmp_file_name, trans_cfg->src_file_name, str_ip);
		}
	}
	
	if (system(cmd) < 0)
	{
		return FALSE;
	}

	if( bc_filetrans_file_is_exist_db(_tmp_file_name) != TRUE)	
	{	
		return FALSE;
	}
	
	trans_cfg->prog_value = 25;
	return TRUE;
}

#endif



