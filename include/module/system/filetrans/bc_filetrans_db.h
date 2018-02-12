/*******************************************************************************
  -------------------------------------------------------------------------
  [File name]  : 
  [Author]     : bain.wang@outlook.com
  [Version]    : 1.0
  [Date]       : 2017-06-11
  [Description]:

  [Others]     :

  [Function List]:  
    1. ....
    2. ....
  [History]:
	 D a t e    Modification 										  Initials
	---------- --------------                                        ----------
	2016-08-04  Created												  bain.wang@outlook.com
*******************************************************************************/

#ifndef __BC_FILETRANS_DB_H__
#define __BC_FILETRANS_DB_H__

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								ͷ   ��   ��								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_err.h"
#include "bc_filetrans_def.h"
#include "bc_modules_com_para.h"
#include "bc_proj_defs.h"

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								��   ��   ��								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
#define FLASH_ERASEALL_DEV_MTD1			"flash_eraseall /dev/mtd1"
#define FLASH_ERASEALL_DEV_MTD2			"flash_eraseall /dev/mtd2"
#define FLASH_ERASEALL_DEV_MTD3			"flash_eraseall /dev/mtd3"
#define FLASH_ERASEALL_DEV_MTD4			"flash_eraseall /dev/mtd4"
#define FLASH_ERASEALL_DEV_MTD5			"flash_eraseall /dev/mtd5"
#define FLASH_ERASEALL_DEV_MTD6			"flash_eraseall /dev/mtd6"
#define FLASH_ERASEALL_DEV_MTD7			"flash_eraseall /dev/mtd7"
#define FLASH_ERASEALL_DEV_MTD8			"flash_eraseall /dev/mtd8"

#define CMD_CP_FILE_TO_BLK1				"cp "BC_FILETRANS_D_FILE_NAME_USER_FS" /dev/mtdblock1"
#define CMD_CP_FILE_TO_BLK2				"cp "BC_FILETRANS_D_FILE_NAME_KERNEL" /dev/mtdblock2"
#define CMD_CP_FILE_TO_BLK3				"cp "BC_FILETRANS_D_FILE_NAME_ROOT_FS" /dev/mtdblock3"
#define CMD_CP_FILE_TO_BLK4				"cp "BC_FILETRANS_D_FILE_NAME_KERNEL" /dev/mtdblock4"
#define CMD_CP_FILE_TO_BLK5				"cp "BC_FILETRANS_D_FILE_NAME_ROOT_FS" /dev/mtdblock5"
#define CMD_CP_FILE_TO_BLK6				"cp "BC_FILETRANS_D_FILE_NAME_ROOT_FS" /dev/mtdblock6"
#define CMD_CP_FILE_TO_BLK7				"cp "BC_FILETRANS_D_FILE_NAME_KERNEL" /dev/mtdblock7"
#define CMD_CP_FILE_TO_BLK8				"cp "BC_FILETRANS_D_FILE_NAME_DBTB" /dev/mtdblock8"

#define CMD_MKDIR_TMP_TMPDIR				"mkdir /tmp/tmpdir"
#define CMD_RM_RF_TMP_TMPDIR				"rm -rf /tmp/tmpdir"

#define CMD_RM_TMP_KERNEL_FILE			"rm -f "BC_FILETRANS_D_FILE_NAME_KERNEL
#define CMD_RM_TMP_ROOTFS_FILE			"rm -f "BC_FILETRANS_D_FILE_NAME_ROOT_FS
#define CMD_RM_TMP_USERFS_FILE			"rm -f "BC_FILETRANS_D_FILE_NAME_USER_FS
#define CMD_RM_TMP_ONU_FILE				"rm -f "BC_FILETRANS_D_FILE_NAME_ONU
#define CMD_RM_TMP_COMBAK_PARAM_FILE	"rm -f "BC_FILETRANS_D_FILE_NAME_CONFIG
#define CMD_RM_TMP_DBTB_FILE				"rm -f "BC_FILETRANS_D_FILE_NAME_DBTB
#define CMD_RM_TMP_UBOOT_FILE				"rm -f "BC_FILETRANS_D_FILE_NAME_UBOOT

#define CMD_TAR_OLT_FILE_NEW_1			"gunzip "BC_FILETRANS_D_FILE_NAME_OLT
#define CMD_TAR_OLT_FILE_NEW_2			"tar -xf olt_img.tar"
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
//					�� �� �� ���� �� �塢ö �� �� ��						  //
//																			  //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//																			  //
//						�� �� �� ���� �� �� �� ��							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#define BC_F_MAX_SHELL_CMD_LEN        1024

/******************************************************************************\
  Function   : bc_filetrans_get_filetrans_cfg_db
  Description: �ж��Ƿ�ΪĿ¼
  Return     : bool true: �ɹ�  false:����ʧ��
  Others     : 
\******************************************************************************/
bc_filetrans_cfg_t*  bc_filetrans_get_filetrans_cfg_db(void);


/******************************************************************************\
  Function   : __bc_filetrans_get_boot_flag
  Description: ��ȡboot flag
  Return     : 0: ������  1:������
  Others     : 
\******************************************************************************/
bc_int32 bc_filetrans_get_boot_flag_db( );

/******************************************************************************\
  Function   : __bc_filetrans_set_startup_flag
  Description: ���� startup flag 
  Return     : 0: ������  1:������
  Others     : 
\******************************************************************************/
bc_int32 bc_filetrans_set_startup_flag_db(bc_int32 flag);

/******************************************************************************\
  Function   : __bc_filetrans_get_startup_flag
  Description: ���� startup flag 
  Return     : 0: ������  1:������
  Others     : 
\******************************************************************************/
bc_int32 bc_filetrans_get_startup_flag_db();

/******************************************************************************\
  Function   : __bc_filetrans_set_update_flag
  Description: ���� update flag 
  Return     : 0: �������������  1:���ݷ����������
  Others     : 
\******************************************************************************/
bc_int32 bc_filetrans_set_update_flag_db(bc_int32 flag);

/******************************************************************************\
  Function   : bc_filetrans_exec_shell_command
  Description: ִ��shell ����
  Return     : 0: �ɹ�  1:����ʧ��
  Others     : 
\******************************************************************************/
bc_int32 bc_filetrans_exec_shell_command_db(char* cmd, char retvalue[BC_F_MAX_SHELL_CMD_LEN]);

bc_boolean bc_filetrans_file_is_exist_db(bc_char *filename);


/******************************************************************************\
  Function   : bc_filetrans_get_config_src_path_db
  Description: ����
  Return     : bc_err_e  �ɹ���ʧ��
  Others     : 
\******************************************************************************/
bc_boolean bc_filetrans_get_config_src_path_db(bc_char src_file_name[BC_MODULE_NAME_LENGTH], bc_char src_file_path[BC_MODULE_NAME_LENGTH]);

/******************************************************************************\
  Function   : bc_filetrans_get_config_dst_path_db
  Description: ����
  Return     : bc_err_e  �ɹ���ʧ��
  Others     : 
\******************************************************************************/
bc_boolean bc_filetrans_get_config_dst_path_db(bc_char dst_file_name[BC_MODULE_NAME_LENGTH], bc_char dst_file_path[BC_MODULE_NAME_LENGTH]);


/******************************************************************************\
  Function   : bc_filetrans_set_info_db
  Description: ���ô�����Ϣ
  Return     : bc_err_e  �ɹ���ʧ��
  Others     : 
\******************************************************************************/
bc_err_e bc_filetrans_set_info_db(bc_filetrans_function_e trans_fun, bc_filetrans_cfg_t para);

/******************************************************************************\
  Function   : bc_filetrans_get_info_db
  Description: ��ȡĳ���� ���Ĵ�����Ϣ
  Return     : bc_err_e  �ɹ���ʧ��
  Others     : 
\******************************************************************************/
bc_err_e bc_filetrans_get_info_db(bc_filetrans_function_e trans_fun, bc_filetrans_cfg_t *para);

/******************************************************************************\
  Function   : bc_filetrans_get_list_db
  Description: ��ȡĳ���� ���Ĵ�����Ϣ
  Return     : bc_err_e  �ɹ���ʧ��
  Others     : 
\******************************************************************************/
bc_err_e bc_filetrans_get_list_db(bc_filetrans_cfg_t paras[BC_FILETRANS_MAX], bc_int32 *num);

/******************************************************************************\
  Function   : bc_filetrans_ipv4_to_str_db
  Description: Ipת��
  Return     : bc_err_e  �ɹ���ʧ��
  Others     : 
\******************************************************************************/
bc_err_e bc_filetrans_ipv4_to_str_db(bc_int32 str, bc_char* ip_str);


/******************************************************************************\
  Function   : bc_filetrans_show_info_db
  Description: ʵʱ��ʾ�������в���
  Return     : bool true: �ɹ�  false:����ʧ��
  Others     : 
\******************************************************************************/
void bc_filetrans_show_info_db(bc_int32 sid, bc_filetrans_cfg_t *_trans_cfg);

bc_boolean bc_filetrans_db_update(char into_dir[255], bc_filetrans_cfg_t *trans_cfg);
bc_boolean bc_filetrans_db_backup(bc_char into_dir[255], bc_filetrans_cfg_t *trans_cfg);

/******************************************************************************\
  Function   : bc_filetrans_db_cfg_to_dev
  Description: д�������ļ���OLT��
  Return     : bool true: �ɹ�  false:����ʧ��
  Others     : 
\******************************************************************************/
bc_boolean bc_filetrans_db_cfg_to_dev(bc_char file_name[BC_MODULE_NAME_LENGTH], bc_char file_path[BC_MODULE_NAME_LENGTH]);

/******************************************************************************\
  Function   : bc_filetrans_db_cfg_check
  Description: 
  Return     : bool true: �ɹ�  false:����ʧ��
  Others     : 
\******************************************************************************/
bc_boolean bc_filetrans_db_cfg_check(bc_char file_name[BC_MODULE_NAME_LENGTH]);

/******************************************************************************\
  Function   : bc_filetrans_db_log_check
  Description: 
  Return     : bool true: �ɹ�  false:����ʧ��
  Others     : 
\******************************************************************************/
bc_boolean bc_filetrans_db_log_check(bc_char file_name[BC_MODULE_NAME_LENGTH]);

bc_boolean bc_filetrans_db_is_timeout(time_t last_update_time, bc_int32 tmout_val);

void bc_filetrans_db_get_cur_time(time_t *cur_time);


#endif /* __BC_FILETRANS_DB_H__ */




