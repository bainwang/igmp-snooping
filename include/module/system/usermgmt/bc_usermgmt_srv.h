/*******************************************************************************
  Copyright (C), 1988-2018, xxxxx Tech. Co., Ltd.
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

#ifndef __BC_SYS_PRIVMGMT_SRV_H__
#define __BC_SYS_PRIVMGMT_SRV_H__

#include "bc_usermgmt_def.h"
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




/******************************************************************************\
  Function   : bc_usermgmt_register
  Description: ע��
  Return     : bc_err_e  �ɹ���ʧ��
  Others     : 
\******************************************************************************/
bc_err_e bc_usermgmt_register_srv(bc_ipc_package_t *data);


/******************************************************************************\
  Function   : bc_usermgmt_unregister_srv
  Description: ע��
  Return     : bc_err_e  �ɹ���ʧ��
  Others     : 
\******************************************************************************/
bc_err_e bc_usermgmt_unregister_srv(bc_ipc_package_t *data);


/******************************************************************************\
  Function   : bc_usermgmt_login
  Description: ��½
  Return     : bc_err_e  �ɹ���ʧ��
  Others     : 
\******************************************************************************/
bc_err_e bc_usermgmt_login_srv(bc_ipc_package_t *data);


/******************************************************************************\
  Function   : bc_usermgmt_logout
  Description: �ǳ�
  Return     : bc_err_e  �ɹ���ʧ��
  Others     : 
\******************************************************************************/
bc_err_e bc_usermgmt_logout_srv(bc_ipc_package_t *data);


/******************************************************************************\
  Function   : bc_usermgmt_set_password
  Description: �޸��û�����
  Return     : bc_err_e  �ɹ���ʧ��
  Others     : 
\******************************************************************************/
bc_err_e bc_usermgmt_set_password_srv(bc_ipc_package_t *data);


/******************************************************************************\
  Function   : bc_usermgmt_set_level
  Description: �޸��û�Ȩ��
  Return     : bc_err_e  �ɹ���ʧ��
  Others     : 
\******************************************************************************/
bc_err_e bc_usermgmt_set_level_srv(bc_ipc_package_t *data);


/******************************************************************************\
  Function   : bc_usermgmt_get_info_srv
  Description: ��ȡָ���û���Ϣ
  Return     : bc_err_e  �ɹ���ʧ��
  Others     : 
\******************************************************************************/
bc_err_e bc_usermgmt_get_info_srv(bc_ipc_package_t *data);


/******************************************************************************\
  Function   : bc_usermgmt_get_list_srv
  Description: ��ȡ�����û���Ϣ
  Return     : bc_err_e  �ɹ���ʧ��
  Others     : 
\******************************************************************************/
bc_err_e bc_usermgmt_get_list_srv(bc_ipc_package_t *data);

bc_err_e bc_usermgmt_get_list_dump_srv(bc_ipc_package_t *data);

bc_err_e bc_usermgmt_get_user_count_srv(bc_ipc_package_t *data);


bc_err_e bc_usermgmt_get_line_info_srv(bc_ipc_package_t *data);


#endif	/*__BC_SYS_PRIVMGMT_SRV_H__*/

