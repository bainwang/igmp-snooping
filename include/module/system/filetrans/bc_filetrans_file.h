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
	2016-06-03  Created												  bain.wang@outlook.com
*******************************************************************************/

#ifndef __BC_FILETRANS_FILE_H__
#define __BC_FILETRANS_FILE_H__

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								头   文   件								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_err.h"
#include "bc_filetrans_def.h"

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




////////////////////////////////////////////////////////////////////////////////
//																			  //
//						外 部 变 量、 函 数 声 明							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////


/*获取文件传输列表*/
bc_err_e bc_filetrans_get_list(bc_filetrans_cfg_t paras[BC_FILETRANS_MAX], bc_int32 *num);

/*获取文件传输参数*/
bc_err_e bc_filetrans_get_info(bc_filetrans_function_e trans_fun, bc_filetrans_cfg_t *para);

/*设置文件传输参数*/
bc_err_e bc_filetrans_set_info(bc_filetrans_function_e trans_fun, bc_filetrans_cfg_t* para);

/*上传文件*/
bc_err_e bc_filetrans_upload_file(bc_filetrans_function_e trans_fun);

/*下载文件*/
bc_err_e bc_filetrans_download_file(bc_filetrans_function_e trans_fun);

/*上传设置*/
bc_err_e bc_filetrans_set_upload_file(bc_filetrans_cfg_t *para);

/*下载设置*/
bc_err_e bc_filetrans_set_download_file(bc_filetrans_cfg_t *para);

bc_err_e bc_filetrans_switch_over_kernel();
bc_err_e bc_filetrans_switch_over_file_system();
#endif /* __BC_FILETRANS_FILE_H__ */




