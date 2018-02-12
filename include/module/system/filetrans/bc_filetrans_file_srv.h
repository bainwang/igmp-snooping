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
//								头   文   件								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//																			  //
//								宏   定   义								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//																			  //
//					结 构 体 、联 合 体、枚 举 定 义				          //
//																			  //
////////////////////////////////////////////////////////////////////////////////
/*获取保存的文件传输配置信息*/

/*获取文件传输列表*/
bc_err_e bc_filetrans_get_list_srv(bc_ipc_package_t *data);

/*获取文件传输参数*/
bc_err_e bc_filetrans_get_info_srv(bc_ipc_package_t *data);

/*设置文件传输参数*/
bc_err_e bc_filetrans_set_info_srv(bc_ipc_package_t *data);

/*上传文件*/
bc_err_e bc_filetrans_upload_file_srv(bc_ipc_package_t *data);

/*下载文件*/
bc_err_e bc_filetrans_download_file_srv(bc_ipc_package_t *data);

/*上传设置*/
bc_err_e bc_filetrans_set_upload_file_srv(bc_ipc_package_t *data);

/*下载设置*/
bc_err_e bc_filetrans_set_download_file_srv(bc_ipc_package_t *data);

bc_err_e bc_filetrans_switch_over_kernel_srv(bc_ipc_package_t *data);

bc_err_e bc_filetrans_switch_over_file_system_srv(bc_ipc_package_t *data);

#endif	/*__BC_FILETRANS_FILE_SRV_H__*/

