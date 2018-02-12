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

#ifndef __BC_FILETRANS_DB_H__
#define __BC_FILETRANS_DB_H__

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								头   文   件								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_err.h"
#include "bc_filetrans_def.h"
//#include "bc_modules_com_para.h"
//#include "bc_port_def.h"
//#include "bc_proj_defs.h"

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								宏   定   义								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
#define FLASH_ERASEALL_DEV_MTD1			"flash_eraseall /dev/mtd1"
#define FLASH_ERASEALL_DEV_MTD2			"flash_eraseall /dev/mtd2"
#define FLASH_ERASEALL_DEV_MTD3			"flash_eraseall /dev/mtd3"
#define FLASH_ERASEALL_DEV_MTD4			"flash_eraseall /dev/mtd4"
#define FLASH_ERASEALL_DEV_MTD5			"flash_eraseall /dev/mtd5"
#define FLASH_ERASEALL_DEV_MTD6			"flash_eraseall /dev/mtd6"
#define FLASH_ERASEALL_DEV_MTD8			"flash_eraseall /dev/mtd8"

#define CMD_CP_FILE_TO_BLK1				"cp "BC_FILETRANS_D_FILE_NAME_UBOOT" /dev/mtdblock1"
#define CMD_CP_FILE_TO_BLK2				"cp "BC_FILETRANS_D_FILE_NAME_KERNEL" /dev/mtdblock2"
#define CMD_CP_FILE_TO_BLK3				"cp "BC_FILETRANS_D_FILE_NAME_ROOT_FS" /dev/mtdblock3"
#define CMD_CP_FILE_TO_BLK4				"cp "BC_FILETRANS_D_FILE_NAME_KERNEL" /dev/mtdblock4"
#define CMD_CP_FILE_TO_BLK5				"cp "BC_FILETRANS_D_FILE_NAME_ROOT_FS" /dev/mtdblock5"
#define CMD_CP_FILE_TO_BLK6				"cp "BC_FILETRANS_D_FILE_NAME_USER_FS" /dev/mtdblock6"
#define CMD_CP_FILE_TO_BLK8				"cp "BC_FILETRANS_D_FILE_NAME_DBTB" /dev/mtdblock8"

#define CMD_MKDIR_TMP_TMPDIR				"mkdir /tmp/tmpdir"
#define CMD_RM_RF_TMP_TMPDIR				"rm -rf /tmp/tmpdir"

#define CMD_RM_TMP_KERNEL_FILE			"rm -f "BC_FILETRANS_D_FILE_NAME_KERNEL
#define CMD_RM_TMP_ROOTFS_FILE			"rm -f "BC_FILETRANS_D_FILE_NAME_ROOT_FS
#define CMD_RM_TMP_USERFS_FILE			"rm -f "BC_FILETRANS_D_FILE_NAME_USER_FS
#define CMD_RM_TMP_DBTB_FILE				"rm -f "BC_FILETRANS_D_FILE_NAME_DBTB
#define CMD_RM_TMP_UBOOT_FILE				"rm -f "BC_FILETRANS_D_FILE_NAME_UBOOT

#define CMD_TAR_OLT_FILE					"tar -zxf "BC_FILETRANS_D_FILE_NAME_OLT

#define CMD_CP_LIB_TO_USR_LIB				"cp -f /tmp/tmpdir/image/*.so /usr/lib/"
#define CMD_CP_IMAGE_TO_USER_FW			"cp -f /tmp/tmpdir/image/* /usr/fw/"
#define CMD_CP_IMAGE_TO_USER_FWBAK		"cp -f /tmp/tmpdir/image/* /usr/fwbak/"

#define FILE_DIR_TMP							"/tmp/"
#define FILE_DIR_TMP_TMPDIR					"/tmp/tmpdir"
#define FILE_DIR_USER_FW					"/usr/fw/"
#define FILE_DIR_USER_FWBAK				"/usr/fwbak/"


////////////////////////////////////////////////////////////////////////////////
//																			  //
//					结 构 体 、联 合 体、枚 举 定 义						  //
//																			  //
////////////////////////////////////////////////////////////////////////////////


typedef enum
{
	BC_FILETRANS_STARTUP_AREA_MAIN = 0,
	BC_FILETRANS_STARTUP_AREA_SLAVE,
	BC_FILETRANS_STARTUP_AREA_INVALID
}bc_filetrans_bc_startup_area_e;



////////////////////////////////////////////////////////////////////////////////
//																			  //
//						外 部 变 量、 函 数 声 明							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#define BC_F_MAX_SHELL_CMD_LEN        1024

/******************************************************************************\
  Function   : bc_filetrans_get_filetrans_cfg_db
  Description: 判断是否为目录
  Return     : bool true: 成功  false:非零失败
  Others     : 
\******************************************************************************/
bc_filetrans_cfg_t*  bc_filetrans_get_filetrans_cfg_db(void);


/******************************************************************************\
  Function   : __bc_filetrans_get_boot_flag
  Description: 获取boot flag
  Return     : 0: 主分区  1:备份区
  Others     : 
\******************************************************************************/
bc_int32 bc_filetrans_get_boot_flag_db( );

/******************************************************************************\
  Function   : __bc_filetrans_set_startup_flag
  Description: 设置 startup flag 
  Return     : 0: 主分区  1:备份区
  Others     : 
\******************************************************************************/
bc_int32 bc_filetrans_set_startup_flag_db(bc_int32 flag);

/******************************************************************************\
  Function   : __bc_filetrans_get_startup_flag
  Description: 设置 startup flag 
  Return     : 0: 主分区  1:备份区
  Others     : 
\******************************************************************************/
bc_int32 bc_filetrans_get_startup_flag_db();

/******************************************************************************\
  Function   : __bc_filetrans_set_update_flag
  Description: 设置 update flag 
  Return     : 0: 主分区升级完成  1:备份分区升级完成
  Others     : 
\******************************************************************************/
bc_int32 bc_filetrans_set_update_flag_db(bc_int32 flag);

/******************************************************************************\
  Function   : bc_filetrans_exec_shell_command
  Description: 执行shell 命令
  Return     : 0: 成功  1:非零失败
  Others     : 
\******************************************************************************/
bc_int32 bc_filetrans_exec_shell_command_db(char* cmd, char retvalue[BC_F_MAX_SHELL_CMD_LEN]);

/******************************************************************************\
  Function   : bc_filetrans_file_is_exist_db
  Description: 判断文件是否存在
  Return     : ktep_errcode_e  成功、失败
  Others     : 
\******************************************************************************/
bc_boolean bc_filetrans_file_is_exist_db(bc_char *filename);

/******************************************************************************\
  Function   : bc_filetrans_set_info_db
  Description: 设置传输信息
  Return     : ktep_errcode_e  成功、失败
  Others     : 
\******************************************************************************/
bc_err_e bc_filetrans_set_info_db(bc_filetrans_function_e trans_fun, bc_filetrans_cfg_t para);

/******************************************************************************\
  Function   : bc_filetrans_get_info_db
  Description: 获取某个文 件的传输信息
  Return     : ktep_errcode_e  成功、失败
  Others     : 
\******************************************************************************/
bc_err_e bc_filetrans_get_info_db(bc_filetrans_function_e trans_fun, bc_filetrans_cfg_t *para);

/******************************************************************************\
  Function   : bc_filetrans_ipv4_to_str_db
  Description: Ip转换
  Return     : ktep_errcode_e  成功、失败
  Others     : 
\******************************************************************************/
bc_err_e bc_filetrans_ipv4_to_str_db(bc_int32 str, bc_char* ip_str);

bc_boolean bc_filetrans_db_update(char into_dir[255], bc_filetrans_cfg_t *trans_cfg);

#endif /* __BC_FILETRANS_DB_H__ */




