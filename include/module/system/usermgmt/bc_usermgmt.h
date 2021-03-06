/*******************************************************************************
  -------------------------------------------------------------------------
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
	2016-07-31  Created												  bain.wang@outlook.com
*******************************************************************************/

#ifndef __BC_SYS_USERMGMT_H__
#define __BC_SYS_USERMGMT_H__

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								头   文   件								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_err.h"
#include "bc_usermgmt_def.h"
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



bc_err_e bc_usermgmt_register
(
	bc_usermgmt_info_t *usermgmt_info
);

bc_err_e bc_usermgmt_unregister
(
	bc_char name[BC_USERMGMT_NAME_LEN]
);

bc_err_e bc_usermgmt_login
(
	bc_char name[BC_USERMGMT_NAME_LEN], 
	bc_char pwd[BC_USERMGMT_NAME_LEN], 
	bc_usermgmt_level_e *level
);

bc_err_e bc_usermgmt_logout();

bc_err_e bc_usermgmt_set_password
(
	bc_char name[BC_USERMGMT_NAME_LEN], 
	bc_char pwd[BC_USERMGMT_NAME_LEN]
);


bc_err_e bc_usermgmt_set_level
(
	bc_char name[BC_USERMGMT_NAME_LEN], 
	bc_usermgmt_level_e level
);

bc_err_e bc_usermgmt_get_user_count
(
	bc_int32 *num
);

bc_err_e bc_usermgmt_get_info
(
	bc_char name[BC_USERMGMT_NAME_LEN],
	bc_usermgmt_info_t *usermgmt_info
);

bc_err_e bc_usermgmt_get_list
(
	bc_usermgmt_info_t usermgmt_info[BC_USERMGMT_USER_NUM],
	bc_int32 *num
);

bc_err_e bc_usermgmt_get_list_dump
(
	bc_usermgmt_info_t usermgmt_info[BC_USERMGMT_USER_NUM],
	bc_int32 *num
);

bc_err_e bc_usermgmt_get_line_info 
(
	bc_usermgmt_info_t *usermgmt_info
);


#endif /* __BC_SYS_USERMGMT_H__ */





