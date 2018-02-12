/*******************************************************************************
  Copyright (C), 2010-2030, xxxxx Tech. Co., Ltd.
  [Author]     : bain.wang@outlook.com
  [Version]    : 1.0
  [Date]       : 2016-07-31
  [Description]:
 
  [Others]     :

  [Function List]:
	1. ....
	2. ....
  [History]:
	 D a t e	Modification										  Initials
	---------- --------------										 ----------
	2016-07-31	Created 											  bain.wang@outlook.com
*******************************************************************************/

#ifndef __BC_SYS_USERMGMT_DEF_H__
#define __BC_SYS_USERMGMT_DEF_H__
       
////////////////////////////////////////////////////////////////////////////////
//																			  //
//								头   文   件								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#include <memory.h>
#include <stdio.h>
#include <time.h>
#include "bc_err.h"
#include "bc_print.h"
#include "bc_func.h"
#include "bc_common_defs.h"

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


#define BC_USERMGMT_DEVELOPER_NUM  1	/*研发账号*/
#define BC_USERMGMT_FACTORY_NUM 2	/*出厂账号*/
#define BC_USERMGMT_OBLIGATE_NUM 2	/*预留账号*/
#define BC_USERMGMT_NORMAL_NUM 10	/*用户账号*/

#define BC_USERMGMT_NAME_LEN	32

#define BC_USERMGMT_NORMAL_NUM_OFFSET	5	/*用户账户号位置*/


#define BC_USERMGMT_USER_NUM	(BC_USERMGMT_DEVELOPER_NUM+BC_USERMGMT_FACTORY_NUM+BC_USERMGMT_OBLIGATE_NUM+BC_USERMGMT_NORMAL_NUM)		/*最大账号数*/
#define BC_USERMGMT_INFO_SIZE	(sizeof(bc_usermgmt_info_t))		/*每个账号的空间大小*/
#define BC_USERMGMT_LIST_SIZE (BC_USERMGMT_INFO_SIZE*BC_USERMGMT_USER_NUM)	/*账号SIZE*/
#define BC_USERMGMT_LINKS_MAX 8		/*账户最大连接数*/
#define BC_USERMGMT_SID_UNUSED (-1)	/*SID 未使用*/

/*
    CLI_ACC_LVL_BASIC = 1,
    CLI_ACC_LVL_PRIVI,
    CLI_ACC_LVL_USER,
    CLI_ACC_LVL_PUSER,
    CLI_ACC_LVL_ADMIN,
    CLI_ACC_LVL_FACTORY,
    CLI_ACC_LVL_DEBUG = 128
*/

//用户权限
typedef enum{
	BC_USERMGMT_LVL_BASIC = 1,	/*基本*/
	BC_USERMGMT_LVL_PRIVI,		/*特权*/
	BC_USERMGMT_LVL_USER,			/*用户*/
	BC_USERMGMT_LVL_PUSER,		/*PUSER*/
	BC_USERMGMT_LVL_ADMIN,		/*管理员*/
	BC_USERMGMT_LVL_FACTORY,		/*出厂*/
	BC_USERMGMT_LVL_DEBUG = 128,	/*开发/调式*/
	BC_USERMGMT_LVL_MAX
}bc_usermgmt_level_e;

//账号状态
typedef enum{
	BC_USERMGMT_STATE_LOGIN = 1,		/*登陆*/
	BC_USERMGMT_STATE_LOGOUT,		/*登出*/
	BC_USERMGMT_STATE_UNUSED		/*未注册*/
}bc_usermgmt_state_e;


//用户登陆信息
typedef struct
{
	int sid;								/* session id*/
	bc_usermgmt_state_e state;			/*登陆状态*/
}bc_username_line_info;


//用户信息
typedef struct 
{
	bc_char 				name[BC_USERMGMT_NAME_LEN];			/*用户名*/
	bc_char 				pwd[BC_USERMGMT_NAME_LEN];			/*明文密码*/
	bc_char 				encrypt_pwd[BC_USERMGMT_NAME_LEN];	/*加密密码*/
	bc_usermgmt_level_e	level;									/*用户权限*/
	bc_int32 				links;									/*连接数*/
	bc_usermgmt_state_e 	state;									/*用户状态*/
	time_t 				login_time;								/*登陆时间*/
	time_t 				logout_time; 							/*登出时间*/
	bc_boolean 			encrypt_enable;							/*加密使能*/
	bc_username_line_info 	line_info[BC_USERMGMT_LINKS_MAX];		/*在线信息*/
}bc_usermgmt_info_t;




////////////////////////////////////////////////////////////////////////////////
//																			  //
//						外 部 变 量、 函 数 声 明							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////



#endif /* __BC_SYS_USERMGMT_DEF_H__ */


