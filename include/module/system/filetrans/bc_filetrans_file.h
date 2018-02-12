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


/*��ȡ�ļ������б�*/
bc_err_e bc_filetrans_get_list(bc_filetrans_cfg_t paras[BC_FILETRANS_MAX], bc_int32 *num);

/*��ȡ�ļ��������*/
bc_err_e bc_filetrans_get_info(bc_filetrans_function_e trans_fun, bc_filetrans_cfg_t *para);

/*�����ļ��������*/
bc_err_e bc_filetrans_set_info(bc_filetrans_function_e trans_fun, bc_filetrans_cfg_t* para);

/*�ϴ��ļ�*/
bc_err_e bc_filetrans_upload_file(bc_filetrans_function_e trans_fun);

/*�����ļ�*/
bc_err_e bc_filetrans_download_file(bc_filetrans_function_e trans_fun);

/*�ϴ�����*/
bc_err_e bc_filetrans_set_upload_file(bc_filetrans_cfg_t *para);

/*��������*/
bc_err_e bc_filetrans_set_download_file(bc_filetrans_cfg_t *para);

bc_err_e bc_filetrans_switch_over_kernel();
bc_err_e bc_filetrans_switch_over_file_system();
#endif /* __BC_FILETRANS_FILE_H__ */




