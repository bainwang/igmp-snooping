/*******************************************************************************
  Copyright (C), 2010-2030, xxxxx Tech. Co., Ltd.
  [File name]  : \\BC\Include\Common\Ipc\bc_ipc_def.h
  [Author]     : bain.wang@outlook.com
  [Version]    : 1.0
  [Date]       : 2016-06-03
  [Description]:
 
  [Others]     :

  [Function List]:
	1. ....
	2. ....
  [History]:
	 D a t e	Modification										  Initials
	---------- --------------										 ----------
	2016-06-03	Created 											  bain.wang@outlook.com
*******************************************************************************/

#ifndef __BC_SYS_FILE_TRANS_DEF_H__
#define __BC_SYS_FILE_TRANS_DEF_H__
       
////////////////////////////////////////////////////////////////////////////////
//																			  //
//								头   文   件								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#include <memory.h>
#include <stdio.h>
#include "bc_err.h"
#include "bc_print.h"
#include "bc_func.h"
#include "bc_common_defs.h"

#include "bc_modules_com_para.h"
////////////////////////////////////////////////////////////////////////////////
//																			  //
//								宏   定   义								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////






////////////////////////////////////////////////////////////////////////////////
//																			  //
//					结 构 体 、联 合 体、枚 举 定 义						  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

//文件传输协议
typedef enum
{
	BC_FILETRANS_TYPE_FTP = 0,
	BC_FILETRANS_TYPE_TFTP = 1,	
	BC_FILETRANS_TYPE_USB = 2
}bc_filetrans_proto_type_e;


//传输状态
typedef enum
{
	BC_FILETRANS_STATUS_IDLE = 1,
	BC_FILETRANS_STATUS_INPROGRESS,
	BC_FILETRANS_STATUS_SUCCESS,
	BC_FILETRANS_STATUS_FAILURE,
	BC_FILETRANS_STATUS_NO_RESOURCE,
	BC_FILETRANS_STATUS_STOP_SUCCESS,
} bc_filetrans_status_e;

//传送对象动作
typedef enum
{
    	BC_FILETRANS_ACTION_NONE =0,
	BC_FILETRANS_ACTION_PUT,
	BC_FILETRANS_ACTION_GET,
	BC_FILETRANS_ACTION_HALT
}bc_filetrans_action_e;

//文件传送功能
typedef enum
{
	BC_FILETRANS_KERNEL = 0,
	BC_FILETRANS_ROOT_FS,
	BC_FILETRANS_USER_FS,
	BC_FILETRANS_OLT,
	BC_FILETRANS_BACKUP_CONFIG,
	BC_FILETRANS_CONFIG,
	BC_FILETRANS_DBTB,
	BC_FILETRANS_UBOOT,
	BC_FILETRANS_BACKUP_LOG,
	BC_FILETRANS_MAX
}bc_filetrans_function_e;

typedef enum
{
	BC_FILETRANS_STARTUP_AREA_MAIN = 0,
	BC_FILETRANS_STARTUP_AREA_SLAVE,
	BC_FILETRANS_STARTUP_AREA_INVALID
}bc_filetrans_startup_area_e;


//文件传输结构
typedef struct
{
	bc_filetrans_proto_type_e proto_type;
	bc_ipv4				    ip;
	bc_char				    usr_name[BC_MODULE_NAME_LENGTH];
	bc_char				    psswrd[BC_MODULE_NAME_LENGTH];
	bc_char				    src_file_name[BC_MODULE_NAME_LENGTH];
	bc_char				    dst_file_name[BC_MODULE_NAME_LENGTH];   //只读
	bc_filetrans_function_e   trans_fun;
	bc_filetrans_action_e     trans_action;
	bc_filetrans_status_e	    status;
	bc_int32                prog_value;     //执行进度 
	bc_boolean              force_stop;     //强制终止
	bc_int32 sid;	//cli session id
} bc_filetrans_cfg_t;




#define BC_FILETRANS_S_FILE_NAME_KERNEL	"vmlinux.bin.gz.uboot"
#define BC_FILETRANS_D_FILE_NAME_KERNEL	"vmlinux.bin.gz.uboot"

#define BC_FILETRANS_S_FILE_NAME_ROOT_FS	"rootfs.ext2.gz.uboot"
#define BC_FILETRANS_D_FILE_NAME_ROOT_FS	"rootfs.ext2.gz.uboot"

#define BC_FILETRANS_S_FILE_NAME_USER_FS	"userfs.jffs2"
#define BC_FILETRANS_D_FILE_NAME_USER_FS	"userfs.jffs2"

#define BC_FILETRANS_S_FILE_NAME_OLT	"olt_img.tar.gz"
#define BC_FILETRANS_D_FILE_NAME_OLT	"olt_img.tar.gz"



#define BC_FILETRANS_S_FILE_NAME_BACKUP_CONFIG	"bc_boot_def.cfg"
#define BC_FILETRANS_D_FILE_NAME_BACKUP_CONFIG	"bc_boot_def.cfg"

#define BC_FILETRANS_S_FILE_NAME_CONFIG	"bc_boot_def.cfg"
#define BC_FILETRANS_D_FILE_NAME_CONFIG	"/tmp/bc_boot_def.cfg"

#define BC_FILETRANS_S_FILE_NAME_DBTB	"mpc8308erdb.dtb"
#define BC_FILETRANS_D_FILE_NAME_DBTB	"mpc8308erdb.dtb"

#define BC_FILETRANS_S_FILE_NAME_UBOOT	"u-boot.bin"
#define BC_FILETRANS_D_FILE_NAME_UBOOT	"u-boot.bin"

#define BC_FILETRANS_S_FILE_NAME_BACKUP_LOG	"system.log"
#define BC_FILETRANS_D_FILE_NAME_BACKUP_LOG	"system.log"


////////////////////////////////////////////////////////////////////////////////
//																			  //
//						外 部 变 量、 函 数 声 明							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////



#endif /* __BC_SYS_FILE_TRANS_DEF_H__ */

