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
#include "bc_vfs.h"
//#include "bc_ipc_def.h"
//#include "bc_ipc_package.h"
#include "bc_platform_mutex.h"
#include "bc_platform_time.h"

#include "bc_platform_thread.h"
#include "bc_platform_sem.h"
#include "bc_platform_mem.h"
#include "utili_string.h"
#include "bc_filetrans_def.h"
//#include "bc_modules_com_para.h"
#include "bc_filetrans_db.h"
#include "bc_filetrans_core.h"



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




////////////////////////////////////////////////////////////////////////////////
//																			  //
//							全 局 变 量 定 义							      //
//																			  //
////////////////////////////////////////////////////////////////////////////////
/* 
 *	外部全局变量，提供整个工程调用，在头文件中提供调用接口(外部引用声明)。
 */



/* 
 *	内部全局变量，只提供给该文件内部函数调用，不在头文件中提供调用接口。
 */

static bc_filetrans_cfg_t	*curr_ftp_cfg;

//SEM
static bc_sem_t *__filetrans_srv_global_sem;
#define __BC_FILETRANS_SRV_GLOBAL_SEM	"filetrans srv global sem"	/*FILETRANS 全局信号量*/

//THREAD
static bc_thread_t *bc_filetrans_thread;
#define FILETRANS_SRV_THREAD 	"filetrans srv thread"
#define FILETRANS_SRV_THREAD_PRI	25

//MUTEX
static bc_pthread_mutex_t                *__filetrans_tftp_mutex;
static bc_pthread_mutex_t                *__filetrans_file_trans_mutex;
#define  __FILETRANS_TFTP_MUTEX_NAME    		 "filetrans tftp mutex" 
#define  __FILETRANS_FILE_TRANS_MUTEX_NAME    	 "filetrans file trans mutex"

#define BC_FILETRANS_TFTP_MUTEX_LOCK()  bc_platform_mutex_lock(__filetrans_tftp_mutex)
#define BC_FILETRANS_TFTP_MUTEX_UNLOCK()  bc_platform_mutex_unlock(__filetrans_tftp_mutex)

#define BC_FILETRANS_FILE_MUTEX_LOCK()  bc_platform_mutex_lock(__filetrans_file_trans_mutex)
#define BC_FILETRANS_FILE_MUTEX_UNLOCK()  bc_platform_mutex_unlock(__filetrans_file_trans_mutex)

#define BC_FILETRANS_SEM_LOCK() bc_platform_sem_wait(__filetrans_srv_global_sem, BC_SEM_WAIT_FOREVER);
#define BC_FILETRANS_SEM_UNLOCK()   bc_platform_sem_post(__filetrans_srv_global_sem);	


#define BC_FILETRANS_CHECK_STATUS()	\
	do{	\
		if(curr_ftp_cfg != NULL)	\
		{	\
			if(curr_ftp_cfg->status == BC_FILETRANS_STATUS_INPROGRESS)	\
			{	\
				return BC_ERR_FILETRANS_RUNNING;	\
			}	\
		}	\
	}while(0)

#define BC_FILETRANS_RUN_CMD(cmd)	\
	do{	\
		if(system(cmd) < 0)	\
		{	\
			update_ok = FALSE;	\
			goto RELEASEMUTEX;	\
		}	\
	}while(0)

#define BC_FILETRANS_SET_PROGVAL(val)	\
	do{	\
		trans_cfg->prog_value = val;	\
	}while(0)
	
#define BC_FILETRANS_SET_STATUS(val)	\
	do{	\
		trans_cfg->status = val;	\
	}while(0)
	
#define BC_FILETRANS_ERR_GOTO(cmd)	\
	do{	\
		update_ok = FALSE;	\
		goto RELEASEMUTEX;	\
	}while(0)

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
  Function   : bc_filetrans_get_info_core
  Description: 获取某个文 件的传输信息
  Return     : ktep_errcode_e  成功、失败
  Others     : 
\******************************************************************************/
bc_err_e bc_filetrans_get_info_core(bc_filetrans_function_e trans_fun, bc_filetrans_cfg_t *para)
{	
	return bc_filetrans_get_info_db(trans_fun, para);
}


/******************************************************************************\
  Function   : bc_filetrans_set_info_core
  Description: 设置传输信息
  Return     : ktep_errcode_e  成功、失败
  Others     : 
\******************************************************************************/
bc_err_e bc_filetrans_set_info_core(bc_filetrans_function_e trans_fun, bc_filetrans_cfg_t para)
{	
	return bc_filetrans_set_info_db(trans_fun, para);
}



/******************************************************************************\
  Function   : __bc_filetrans_reboot_system
  Description: 
  Return     : 
  Others     : 
\******************************************************************************/
static void __bc_filetrans_reboot_system(void)
{
	bc_int32   ret = 0;

	sleep(1);
	BC_PT_COMMAND(-1, "reboot \r\n");
	ret = system("reboot");
	if (0 != ret)
	{
		BC_PT_COMMAND(-1, "reboot system error!\r\n");
		return ;
	}

	return;
}



/******************************************************************************\
  Function   : __bc_filetrans_update_kernel_file
  Description: 升级管理板内核
  Return     : ktep_errcode_e  成功、失败
  Others     : 
\******************************************************************************/
static void __bc_filetrans_update_kernel_file_core(void *para)
{	
	/*
	ftpget -u user -p password 192.168.1.10 vmlinux.bin.gz.uboot vmlinux.bin.gz.uboot
	flash_eraseall /dev/mtd2
	cp vmlinux.bin.gz.uboot /dev/mtdblock2
	*/
	bc_filetrans_cfg_t *trans_cfg = NULL;
	bc_boolean __attribute__ ((unused)) update_ok = TRUE;

	trans_cfg = (bc_filetrans_cfg_t*)para;
	
	BC_PT_DBG_CPL(BC_MODULE_FILETRANS, "ktep_update_kernel_file begin !\n\r");
	BC_FILETRANS_FILE_MUTEX_LOCK();

	/*修改下载状态*/
	BC_FILETRANS_SET_STATUS(BC_FILETRANS_STATUS_INPROGRESS);	

	/*下载文件到OLT*/
	if(bc_filetrans_db_update(FILE_DIR_TMP, trans_cfg) != TRUE)
	{
		BC_FILETRANS_ERR_GOTO();
	}
	BC_FILETRANS_SET_PROGVAL(50);

	/*升级内核*/
	if(bc_filetrans_get_boot_flag_db() == 1)
	{
		BC_FILETRANS_RUN_CMD(FLASH_ERASEALL_DEV_MTD2);
		printf("2. %s\n\r", FLASH_ERASEALL_DEV_MTD2);
		BC_FILETRANS_SET_PROGVAL(75);
		BC_FILETRANS_RUN_CMD(CMD_CP_FILE_TO_BLK2);	
		printf("3. %s\n\r", CMD_CP_FILE_TO_BLK2);
		BC_FILETRANS_SET_PROGVAL(100);
	}
	else
	{
		BC_FILETRANS_RUN_CMD(FLASH_ERASEALL_DEV_MTD4);	
		printf("2. %s\n\r", FLASH_ERASEALL_DEV_MTD4);
		BC_FILETRANS_SET_PROGVAL(75);
		BC_FILETRANS_RUN_CMD(CMD_CP_FILE_TO_BLK4);
		printf("3. %s\n\r", CMD_CP_FILE_TO_BLK4);
		BC_FILETRANS_SET_PROGVAL(100);
	}	

	BC_FILETRANS_RUN_CMD("sync");
	
RELEASEMUTEX:

	if(update_ok == FALSE)
	{
		BC_FILETRANS_SET_STATUS(BC_FILETRANS_STATUS_FAILURE);
		printf("__bc_filetrans_update_kernel_file_core() failure !\n\r");
	}
	else
	{
		BC_FILETRANS_SET_PROGVAL(100);
		BC_FILETRANS_SET_STATUS(BC_FILETRANS_STATUS_SUCCESS);
		BC_PT_DBG_CPL(BC_MODULE_USERMGMT, "__bc_filetrans_update_kernel_file_core() success !\n\r");
	}
	
	BC_FILETRANS_FILE_MUTEX_UNLOCK();
}

/******************************************************************************\
  Function   : bc_filetrans_update_root_fs_core
  Description: 升级管理板根文件系统
  Return     : ktep_errcode_e  成功、失败
  Others     : 
\******************************************************************************/
static void __bc_filetrans_update_root_fs_core(void *para)
{
	/*
	ftpget -u user -p password 192.168.1.10 rootfs.ext2.gz.uboot rootfs.ext2.gz.uboot
	flash_eraseall /dev/mtd3
	cp rootfs.ext2.gz.uboot /dev/mtdblock3
	*/
	bc_filetrans_cfg_t *trans_cfg = NULL;
	bc_boolean __attribute__ ((unused)) update_ok = TRUE;

	trans_cfg = (bc_filetrans_cfg_t*)para;
	    
	BC_PT_DBG_CPL(BC_MODULE_FILETRANS, "ktep_update_root_fs begin !\n\r");	
	BC_FILETRANS_FILE_MUTEX_LOCK();
	
	BC_FILETRANS_SET_STATUS(BC_FILETRANS_STATUS_INPROGRESS);
	
	if(bc_filetrans_db_update(FILE_DIR_TMP, trans_cfg) != TRUE)
	{
		BC_FILETRANS_ERR_GOTO();
	}
	BC_FILETRANS_SET_PROGVAL(50);
	
	if(bc_filetrans_get_boot_flag_db() == 1)
	{
		BC_FILETRANS_RUN_CMD(FLASH_ERASEALL_DEV_MTD3);	
		printf("2. %s\n\r", FLASH_ERASEALL_DEV_MTD3);
		BC_FILETRANS_SET_PROGVAL(75);
		BC_FILETRANS_RUN_CMD(CMD_CP_FILE_TO_BLK3);	
		printf("3. %s\n\r", CMD_CP_FILE_TO_BLK3);
		BC_FILETRANS_SET_PROGVAL(100);
	}	
	else
	{
		BC_FILETRANS_RUN_CMD(FLASH_ERASEALL_DEV_MTD5);	
		printf("2. %s\n\r", FLASH_ERASEALL_DEV_MTD5);
		BC_FILETRANS_SET_PROGVAL(75);
		BC_FILETRANS_RUN_CMD(CMD_CP_FILE_TO_BLK5);	
		printf("3. %s\n\r", CMD_CP_FILE_TO_BLK5);
		BC_FILETRANS_SET_PROGVAL(100);
	}

	BC_FILETRANS_RUN_CMD("sync");
	
RELEASEMUTEX:
	
	if(update_ok == FALSE)
	{
		BC_FILETRANS_SET_STATUS(BC_FILETRANS_STATUS_FAILURE);
		printf("__bc_filetrans_update_root_fs_core() failure !\n\r");
	}
	else
	{
		BC_FILETRANS_SET_PROGVAL(100);
		BC_FILETRANS_SET_STATUS(BC_FILETRANS_STATUS_SUCCESS);
		BC_PT_DBG_CPL(BC_MODULE_USERMGMT, "__bc_filetrans_update_root_fs_core() success !\n\r");
	}
	
	BC_FILETRANS_FILE_MUTEX_UNLOCK();
}

/******************************************************************************\
  Function   : bc_filetrans_update_user_fs_core
  Description: 升级管理板用户文件系统
  Return     : ktep_errcode_e  成功、失败
  Others     : 
\******************************************************************************/
static void __bc_filetrans_update_user_fs_core(void *para)
{
	/*
	ftpget -u user -p password 192.168.1.10 flashfs.jffs2 flashfs.jffs2
	flash_eraseall /dev/mtd6
	cp userfs.jffs2 /dev/mtdblock6
	*/
	bc_filetrans_cfg_t *trans_cfg = NULL;
	bc_boolean __attribute__ ((unused)) update_ok = TRUE;

	trans_cfg = (bc_filetrans_cfg_t*)para;
	
	BC_PT_DBG_CPL(BC_MODULE_FILETRANS, "__bc_filetrans_update_user_fs_core() begin !\n\r");	
	BC_FILETRANS_FILE_MUTEX_LOCK();
	
	BC_FILETRANS_SET_STATUS(BC_FILETRANS_STATUS_INPROGRESS);
	
	if(bc_filetrans_db_update(FILE_DIR_TMP, trans_cfg) != TRUE)
	{
		BC_FILETRANS_ERR_GOTO();
	}
	BC_FILETRANS_SET_PROGVAL(50);
	
	BC_FILETRANS_RUN_CMD(FLASH_ERASEALL_DEV_MTD6);	
	printf("2. %s\n\r", FLASH_ERASEALL_DEV_MTD6);
	BC_FILETRANS_SET_PROGVAL(75);
	BC_FILETRANS_RUN_CMD(CMD_CP_FILE_TO_BLK6);	
	printf("2. %s\n\r", CMD_CP_FILE_TO_BLK6);

	BC_FILETRANS_RUN_CMD("sync");
	BC_FILETRANS_SET_PROGVAL(100);

RELEASEMUTEX:
	
	if(update_ok == FALSE)
	{
		BC_FILETRANS_SET_STATUS(BC_FILETRANS_STATUS_FAILURE);
		printf("__bc_filetrans_update_user_fs_core() failure !\n\r");
	}
	else
	{
		BC_FILETRANS_SET_PROGVAL(100);
		BC_FILETRANS_SET_STATUS(BC_FILETRANS_STATUS_SUCCESS);
		BC_PT_DBG_CPL(BC_MODULE_USERMGMT, "__bc_filetrans_update_user_fs_core() success !\n\r");
	}
	BC_FILETRANS_FILE_MUTEX_UNLOCK();
}

/******************************************************************************\
  Function   : bc_filetrans_update_bc_firm_core
  Description: 升级OLT固件
  Return     : ktep_errcode_e  成功、失败
  Others     : 
\******************************************************************************/
static void __bc_filetrans_update_dev_firm_core(void *para)
{
	bc_char cmd_retval[BC_F_MAX_SHELL_CMD_LEN];
	bc_filetrans_cfg_t *trans_cfg = NULL;
	bc_boolean __attribute__ ((unused)) update_ok = TRUE;

	memset(cmd_retval, 0, sizeof(cmd_retval));
	trans_cfg = (bc_filetrans_cfg_t*)para;

	/* lock */
	BC_FILETRANS_FILE_MUTEX_LOCK();
	BC_FILETRANS_SET_STATUS(BC_FILETRANS_STATUS_INPROGRESS);

	if (bc_filetrans_db_update(FILE_DIR_TMP_TMPDIR, trans_cfg) != TRUE)
	{
		BC_FILETRANS_ERR_GOTO();
	}
	BC_FILETRANS_SET_PROGVAL(25);

	BC_FILETRANS_RUN_CMD(CMD_TAR_OLT_FILE);	
	BC_FILETRANS_SET_PROGVAL(50);

	//fw
#if defined(BC_PTC88C)	
	if(bc_vfs_file_by_dir_delete(FILE_DIR_USER_FW) != 0)
	{
		BC_FILETRANS_ERR_GOTO();
	}
#else
	BC_FILETRANS_RUN_CMD("rm -rf /usr/fw/*");
#endif
	BC_FILETRANS_RUN_CMD("cp -f /tmp/tmpdir/image/* /usr/fw");
	BC_FILETRANS_SET_PROGVAL(70);

	//fwbak
#if defined(BC_PTC88C)	
	if(bc_vfs_file_by_dir_delete(FILE_DIR_USER_FWBAK) != 0)
	{
		BC_FILETRANS_ERR_GOTO();
	}
#else	
	BC_FILETRANS_RUN_CMD("rm -rf /usr/fwbak/*");
#endif
	BC_FILETRANS_RUN_CMD("cp -f /tmp/tmpdir/image/* /usr/fwbak");
	BC_FILETRANS_SET_PROGVAL(90);
	
	BC_FILETRANS_RUN_CMD(CMD_RM_RF_TMP_TMPDIR);
	bc_filetrans_set_update_flag_db(1);
	bc_filetrans_set_startup_flag_db(1);
	BC_FILETRANS_RUN_CMD("sync");
	BC_FILETRANS_SET_PROGVAL(100);
	
RELEASEMUTEX:
	if (update_ok == FALSE)
	{
		BC_FILETRANS_SET_STATUS(BC_FILETRANS_STATUS_FAILURE);
		BC_PT_DBG_CPL(BC_MODULE_USERMGMT, "__bc_filetrans_update_dev_firm_core() failure !\n\r");
	}
	else
	{
		BC_FILETRANS_SET_PROGVAL(100);
		BC_FILETRANS_SET_STATUS(BC_FILETRANS_STATUS_SUCCESS);
		BC_PT_DBG_CPL(BC_MODULE_USERMGMT, "__bc_filetrans_update_dev_firm_core() success !\n\r");
	}

	/* unlock */
	BC_FILETRANS_FILE_MUTEX_UNLOCK();

	/* reboot system */
	if (BC_FILETRANS_STATUS_SUCCESS == trans_cfg->status)
	{
		__bc_filetrans_reboot_system();
	}

	return;
}



/******************************************************************************\
  Function   : __bc_filetrans_update_manb_dbtb
  Description: 升级管理板DB
  Return     : ktep_errcode_e  成功、失败
  Others     : 
  
\******************************************************************************/
static void __bc_filetrans_update_manb_dbtb_core(void *para)
{
	/*
	ftpget -u user -p password 192.168.1.10 vmlinux.bin.gz.uboot vmlinux.bin.gz.uboot
	flash_eraseall /dev/mtd2
	cp vmlinux.bin.gz.uboot /dev/mtdblock2
     */
	bc_filetrans_cfg_t *trans_cfg = NULL;
	bc_boolean __attribute__ ((unused)) update_ok = TRUE;

	trans_cfg = (bc_filetrans_cfg_t*)para;
	
	BC_PT_DBG_CPL(BC_MODULE_FILETRANS, "update_manb_dbtb begin !\n\r");
	BC_FILETRANS_FILE_MUTEX_LOCK();

	BC_FILETRANS_SET_STATUS(BC_FILETRANS_STATUS_INPROGRESS);

	if(bc_filetrans_db_update(FILE_DIR_TMP, trans_cfg) != TRUE)
	{
		BC_FILETRANS_ERR_GOTO();
	}
	BC_FILETRANS_SET_PROGVAL(50);
	
	BC_FILETRANS_RUN_CMD(FLASH_ERASEALL_DEV_MTD8);	
	printf("2. %s\n\r", FLASH_ERASEALL_DEV_MTD8);
	BC_FILETRANS_SET_PROGVAL(75);
   	BC_FILETRANS_RUN_CMD(CMD_CP_FILE_TO_BLK8);	
	printf("3. %s\n\r", CMD_CP_FILE_TO_BLK8);
	
	BC_FILETRANS_RUN_CMD("sync");
	BC_FILETRANS_SET_PROGVAL(100);

RELEASEMUTEX:
	
	if(update_ok == FALSE)
	{
		BC_FILETRANS_SET_STATUS(BC_FILETRANS_STATUS_FAILURE);
		printf("__bc_filetrans_update_manb_dbtb_core() failure !\n\r");
	}
	else
	{
		BC_FILETRANS_SET_PROGVAL(100);
		BC_FILETRANS_SET_STATUS(BC_FILETRANS_STATUS_SUCCESS);
		BC_PT_DBG_CPL(BC_MODULE_USERMGMT, "__bc_filetrans_update_manb_dbtb_core() success !\n\r");
	}
	
	BC_FILETRANS_FILE_MUTEX_UNLOCK();
}

/******************************************************************************\
  Function   : __bc_filetrans_update_manb_uboot_core
  Description: 升级管理板UBOOT
  Return     : ktep_errcode_e  成功、失败
  Others     : 
\******************************************************************************/
static void __bc_filetrans_update_manb_uboot_core(void *para)
{
	/*
	ftpget -u user -p password 192.168.1.10 vmlinux.bin.gz.uboot vmlinux.bin.gz.uboot
	flash_eraseall /dev/mtd2
	cp vmlinux.bin.gz.uboot /dev/mtdblock2
	*/
	bc_filetrans_cfg_t *trans_cfg = NULL;
	bc_boolean __attribute__ ((unused)) update_ok = TRUE;

	trans_cfg = (bc_filetrans_cfg_t*)para;

	BC_PT_DBG_CPL(BC_MODULE_FILETRANS, "update_manb_uboot begin !\n\r");
	BC_FILETRANS_FILE_MUTEX_LOCK();
	
	BC_FILETRANS_SET_STATUS(BC_FILETRANS_STATUS_INPROGRESS);
	
	if(bc_filetrans_db_update(FILE_DIR_TMP, trans_cfg) != TRUE)
	{
		BC_FILETRANS_ERR_GOTO();
	}
	BC_FILETRANS_SET_PROGVAL(50);
	
   	BC_FILETRANS_RUN_CMD(FLASH_ERASEALL_DEV_MTD1);	
	printf("2. %s\n\r", FLASH_ERASEALL_DEV_MTD1);
	BC_FILETRANS_SET_PROGVAL(75);
      	BC_FILETRANS_RUN_CMD(CMD_CP_FILE_TO_BLK1);	
	printf("3. %s\n\r", CMD_CP_FILE_TO_BLK1);
	
	BC_FILETRANS_RUN_CMD("sync");
	BC_FILETRANS_SET_PROGVAL(100);

RELEASEMUTEX:
	
	if(update_ok == FALSE)
	{
		BC_FILETRANS_SET_STATUS(BC_FILETRANS_STATUS_FAILURE);
		printf("__bc_filetrans_upate_manb_uboot_core() failure !\n\r");
	}
	else
	{
		BC_FILETRANS_SET_PROGVAL(100);
		BC_FILETRANS_SET_STATUS(BC_FILETRANS_STATUS_SUCCESS);
		BC_PT_DBG_CPL(BC_MODULE_USERMGMT, "__bc_filetrans_upate_manb_uboot_core() success !\n\r");
	}
	
	BC_FILETRANS_FILE_MUTEX_UNLOCK();
}



/******************************************************************************\
  Function   : __bc_filetrans_proc_thread_core
  Description: ftp 处理线程
  Return     : ktep_errcode_e  成功、失败
  Others     : 
\******************************************************************************/
static void __bc_filetrans_proc_thread_core(void)
{	
	while(TRUE)
	{
		BC_FILETRANS_SEM_LOCK();
		
		curr_ftp_cfg->force_stop = FALSE;
		switch(curr_ftp_cfg->trans_fun)
		{
			case BC_FILETRANS_KERNEL:
				__bc_filetrans_update_kernel_file_core(curr_ftp_cfg);
				break;
				
			case BC_FILETRANS_ROOT_FS:
				__bc_filetrans_update_root_fs_core(curr_ftp_cfg);
				break;
				
			case BC_FILETRANS_USER_FS:
				__bc_filetrans_update_user_fs_core(curr_ftp_cfg);
				break;
				
			case BC_FILETRANS_OLT:
				__bc_filetrans_update_dev_firm_core(curr_ftp_cfg);
				break;
				
			case BC_FILETRANS_DBTB:
				__bc_filetrans_update_manb_dbtb_core(curr_ftp_cfg);
				break;
				
			case BC_FILETRANS_UBOOT:
				__bc_filetrans_update_manb_uboot_core(curr_ftp_cfg);
				break;
			
			default:
				break;
		}
	}

	return;
}



/******************************************************************************\
  Function   : __bc_filetrans_download_file_db
  Description: 下载文件
  Return     : ktep_errcode_e  成功、失败
  Others     : 
\******************************************************************************/
bc_err_e bc_filetrans_download_file_core(bc_filetrans_function_e trans_fun)
{		
	bc_filetrans_cfg_t *filetrans_cfg = bc_filetrans_get_filetrans_cfg_db();
	
	BC_FILETRANS_CHECK_STATUS();

	BC_FILETRANS_TFTP_MUTEX_LOCK();
	
	if(trans_fun == BC_FILETRANS_KERNEL
		||trans_fun == BC_FILETRANS_ROOT_FS
		||trans_fun == BC_FILETRANS_USER_FS
		||trans_fun == BC_FILETRANS_OLT
		||trans_fun == BC_FILETRANS_DBTB
		||trans_fun == BC_FILETRANS_UBOOT)
	{
		curr_ftp_cfg = &filetrans_cfg[trans_fun];
		curr_ftp_cfg->status = BC_FILETRANS_STATUS_INPROGRESS;
		BC_FILETRANS_SEM_UNLOCK();
	}
	else
	{
		return BC_ERR_FILETRANS_WRITE_PARA_ERROR;
	}

	BC_FILETRANS_TFTP_MUTEX_UNLOCK();
	
	return BC_ERR_OK;
}


/******************************************************************************\
Function   : bc_filetrans_init
Description: 初始化
Return     : ktep_errcode_e  成功、失败
Others     : 
\******************************************************************************/
bc_err_e bc_filetrans_init_core(void)
{
//	printf("\r\n\n\n[%s, %d] ----------------bc_filetrans_init_core, NO.2---------------\r\n\n\n\n\n", __FILE__, __LINE__);
	__filetrans_tftp_mutex = bc_platform_mutex_create((bc_char*)__FILETRANS_TFTP_MUTEX_NAME);
	if(NULL == __filetrans_tftp_mutex)
	{
		BC_PT_ERROR(BC_MODULE_FILETRANS, "Failed to create mutex!\n");
		return BC_ERR_RESOURCE;
	}

	__filetrans_srv_global_sem = bc_platform_sem_create((bc_char*)__BC_FILETRANS_SRV_GLOBAL_SEM, 0); 
	if(NULL == __filetrans_srv_global_sem)
	{
		BC_PT_ERROR(BC_MODULE_FILETRANS, "Failed to create sem!\n");
		return BC_ERR_RESOURCE;
	}
	
	__filetrans_file_trans_mutex = bc_platform_mutex_create((bc_char*)__FILETRANS_FILE_TRANS_MUTEX_NAME);
	if(NULL == __filetrans_file_trans_mutex)
	{
		BC_PT_ERROR(BC_MODULE_FILETRANS, "Failed to create mutex!\n");
		return BC_ERR_RESOURCE;
	}
	
	bc_filetrans_thread = bc_platform_thread_create(
													(bc_char*)FILETRANS_SRV_THREAD,
													BC_THREAD_DEF_STACK_SIZE, 
													FILETRANS_SRV_THREAD_PRI,
													(const void *)__bc_filetrans_proc_thread_core, 
													NULL);
	if(NULL == bc_filetrans_thread)
	{
		return BC_ERR_RESOURCE;
	}

	BC_PT_DBG_CPL(BC_MODULE_USERMGMT, "bc_filetrans_init_core() success !\n\r");
	
	return BC_ERR_OK;
}



