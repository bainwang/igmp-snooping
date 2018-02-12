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

#ifndef __BC_FILETRANS_CORE_H__
#define __BC_FILETRANS_CORE_H__

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								ͷ   ��   ��								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_err.h"
#include "bc_filetrans_def.h"
#include "bc_modules_com_para.h"

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								��   ��   ��								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////


/*
#define FLASH_ERASEALL_DEV_MTD2	"flash_eraseall /dev/mtd2"
#define FLASH_ERASEALL_DEV_MTD2	"flash_eraseall /dev/mtd2"
#define FLASH_ERASEALL_DEV_MTD2	"flash_eraseall /dev/mtd2"
#define FLASH_ERASEALL_DEV_MTD2	"flash_eraseall /dev/mtd2"
#define FLASH_ERASEALL_DEV_MTD2	"flash_eraseall /dev/mtd2"
#define FLASH_ERASEALL_DEV_MTD2	"flash_eraseall /dev/mtd2"
#define FLASH_ERASEALL_DEV_MTD2	"flash_eraseall /dev/mtd2"
#define FLASH_ERASEALL_DEV_MTD2	"flash_eraseall /dev/mtd2"
#define FLASH_ERASEALL_DEV_MTD2	"flash_eraseall /dev/mtd2"
#define FLASH_ERASEALL_DEV_MTD2	"flash_eraseall /dev/mtd2"
#define FLASH_ERASEALL_DEV_MTD2	"flash_eraseall /dev/mtd2"
#define FLASH_ERASEALL_DEV_MTD2	"flash_eraseall /dev/mtd2"
#define FLASH_ERASEALL_DEV_MTD2	"flash_eraseall /dev/mtd2"
*/


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

/******************************************************************************\
  Function   : bc_filetrans_get_list_core
  Description: ��ȡ�� ���Ĵ�����Ϣ
  Return     : bc_err_e  �ɹ���ʧ��
  Others     : 
\******************************************************************************/
bc_err_e bc_filetrans_get_list_core(bc_filetrans_cfg_t paras[BC_FILETRANS_MAX], bc_int32 *num);

/******************************************************************************\
  Function   : bc_filetrans_get_info_core
  Description: ��ȡĳ���� ���Ĵ�����Ϣ
  Return     : bc_err_e  �ɹ���ʧ��
  Others     : 
\******************************************************************************/
bc_err_e bc_filetrans_get_info_core(bc_filetrans_function_e trans_fun, bc_filetrans_cfg_t *para);

/******************************************************************************\
  Function   : bc_filetrans_set_info_core
  Description: ���ô�����Ϣ
  Return     : bc_err_e  �ɹ���ʧ��
  Others     : 
\******************************************************************************/
bc_err_e bc_filetrans_set_info_core(bc_filetrans_function_e trans_fun, bc_filetrans_cfg_t para);

//�ϴ��� ��
bc_err_e bc_filetrans_upload_file_core(bc_filetrans_function_e trans_fun);

//������ ��
bc_err_e bc_filetrans_download_file_core(bc_filetrans_function_e trans_fun);

//��ʼ��
bc_err_e bc_filetrans_init_core(void);

//��ʼ��
bc_err_e bc_filetrans_init(void);


bc_err_e bc_filetrans_core_switch_over_kernel();
bc_err_e bc_filetrans_core_switch_over_file_system();

#endif /* __BC_FILETRANS_CORE_H__ */



