/*******************************************************************************
  Copyright (C), 1988-2018, xxxxx Tech. Co., Ltd.
  [File name]  : \\BC\api_system\ktapi_file_trans.h
  [Author]     : bain.wang@outlook.com
  [Version]    : 1.0
  [Date]       : 2017-06-11
  [Description]:

  [Others]     :

  [Function List]:
	1. ....
	2. ....
  [History]:
	 D a t e	Modification										  Initials
	---------- --------------										 ----------
	2016-06-05	Created 										      bain.wang@outlook.com
*******************************************************************************/

#ifndef __BC_FILETRANS_FILE_SRV_H__
#define __BC_FILETRANS_FILE_SRV_H__

#include "bc_filetrans_def.h"
#include "bc_err.h"
#include "bc_ipc_def.h"
////////////////////////////////////////////////////////////////////////////////
//																			  //
//								ͷ   ��   ��								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//																			  //
//								��   ��   ��								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//																			  //
//					�� �� �� ���� �� �塢ö �� �� ��				          //
//																			  //
////////////////////////////////////////////////////////////////////////////////
/*��ȡ������ļ�����������Ϣ*/

/*��ȡ�ļ������б�*/
bc_err_e bc_filetrans_get_list_srv(bc_ipc_package_t *data);

/*��ȡ�ļ��������*/
bc_err_e bc_filetrans_get_info_srv(bc_ipc_package_t *data);

/*�����ļ��������*/
bc_err_e bc_filetrans_set_info_srv(bc_ipc_package_t *data);

/*�ϴ��ļ�*/
bc_err_e bc_filetrans_upload_file_srv(bc_ipc_package_t *data);

/*�����ļ�*/
bc_err_e bc_filetrans_download_file_srv(bc_ipc_package_t *data);

/*�ϴ�����*/
bc_err_e bc_filetrans_set_upload_file_srv(bc_ipc_package_t *data);

/*��������*/
bc_err_e bc_filetrans_set_download_file_srv(bc_ipc_package_t *data);

bc_err_e bc_filetrans_switch_over_kernel_srv(bc_ipc_package_t *data);

bc_err_e bc_filetrans_switch_over_file_system_srv(bc_ipc_package_t *data);

#endif	/*__BC_FILETRANS_FILE_SRV_H__*/

