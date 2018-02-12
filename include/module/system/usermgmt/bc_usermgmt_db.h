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
	2016-06-03  Created												  bain.wang@outlook.com
*******************************************************************************/

#ifndef __BC_USERMGMT_DB_H__
#define __BC_USERMGMT_DB_H__

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								头   文   件								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_err.h"
#include "bc_modules_com_para.h"

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								宏   定   义								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////


typedef enum
{
	BC_USERFILE_EXIST_FLAG = 0,
	BC_USERFILE_NO_EXIST_FLAG	
}bc_usermgmt_file_exist_flag_e;

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




void bc_usermgmt_db_init(bc_usermgmt_file_exist_flag_e flag);

void bc_usermgmt_db_get_user_count(bc_int32 *count);


bc_boolean bc_usermgmt_db_file_create(void);


bc_boolean bc_usermgmt_db_file_read(void);


bc_boolean bc_usermgmt_db_file_write(void);


bc_boolean bc_usermgmt_db_set_state
(
	IN bc_int32 sid,
	IN bc_char name[BC_USERMGMT_NAME_LEN], 
	IN bc_usermgmt_state_e state
);


bc_boolean bc_usermgmt_db_sid_is_line(IN bc_int32 sid);


bc_boolean bc_usermgmt_db_get_userinfo_by_name(IN bc_char name[BC_USERMGMT_NAME_LEN], OUT bc_usermgmt_info_t *usermgmt_info);


bc_boolean bc_usermgmt_db_get_all_userinfo(OUT bc_usermgmt_info_t usermgmt_info[BC_USERMGMT_USER_NUM], OUT bc_int32 *num);

bc_boolean bc_usermgmt_db_is_full(void);


bc_boolean bc_usermgmt_db_is_same_name(IN bc_char name[BC_USERMGMT_NAME_LEN]);


bc_boolean bc_usermgmt_db_check_login_info(IN bc_char name[BC_USERMGMT_NAME_LEN], IN bc_char pwd[BC_USERMGMT_NAME_LEN]);


bc_boolean bc_usermgmt_db_get_user_index(IN bc_char name[BC_USERMGMT_NAME_LEN], IN bc_int32 *offset);


bc_boolean bc_usermgmt_db_get_line_userinfo_by_sid(IN bc_int32 sid, OUT bc_usermgmt_info_t *usermgmt_info);


bc_boolean bc_usermgmt_db_encrypt_pwd(IN bc_char pwd[BC_USERMGMT_NAME_LEN], OUT bc_char encrypt_pwd[BC_USERMGMT_NAME_LEN]);


bc_boolean bc_usermgmt_db_no_encrypt_pwd(IN bc_char name[BC_USERMGMT_NAME_LEN]);


bc_boolean bc_usermgmt_db_add_user(IN bc_usermgmt_info_t *usermgmt_info);


bc_boolean bc_usermgmt_db_del_user(IN bc_char name[BC_USERMGMT_NAME_LEN]);


bc_boolean bc_usermgmt_db_set_pwd(IN bc_char name[BC_USERMGMT_NAME_LEN], IN bc_char user_pwd[BC_USERMGMT_NAME_LEN]);


bc_boolean bc_usermgmt_db_set_level(IN bc_char name[BC_USERMGMT_NAME_LEN], IN bc_usermgmt_level_e user_level);


bc_boolean bc_usermgmt_db_get_link_num(IN bc_char name[BC_USERMGMT_NAME_LEN], OUT bc_int32 *link_num);


bc_boolean bc_usermgmt_db_put_single(IN bc_char name[BC_USERMGMT_NAME_LEN]);


bc_boolean bc_usermgmt_db_put_all(void);



bc_boolean bc_usermgmt_db_login_user
(
	IN bc_int32 sid,
	IN bc_char name[BC_USERMGMT_NAME_LEN],
	IN bc_boolean first_login_flag
);

bc_boolean bc_usermgmt_db_logout_user
(
	IN bc_int32 sid,
	IN bc_char name[BC_USERMGMT_NAME_LEN],
	IN bc_boolean last_logout_flag
);

//bc_boolean bc_usermgmt_db_set_pwd_level(IN bc_char name[BC_USERMGMT_NAME_LEN], IN bc_char user_pwd[BC_USERMGMT_NAME_LEN],IN bc_usermgmt_level_e user_level);
#endif /* __BC_USERMGMT_DB_H__ */




