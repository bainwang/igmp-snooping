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
//								ͷ   ��   ��								  //
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
//								��   ��   ��								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////






////////////////////////////////////////////////////////////////////////////////
//																			  //
//					�� �� �� ���� �� �塢ö �� �� ��						  //
//																			  //
////////////////////////////////////////////////////////////////////////////////


#define BC_USERMGMT_DEVELOPER_NUM  1	/*�з��˺�*/
#define BC_USERMGMT_FACTORY_NUM 2	/*�����˺�*/
#define BC_USERMGMT_OBLIGATE_NUM 2	/*Ԥ���˺�*/
#define BC_USERMGMT_NORMAL_NUM 10	/*�û��˺�*/

#define BC_USERMGMT_NAME_LEN	32

#define BC_USERMGMT_NORMAL_NUM_OFFSET	5	/*�û��˻���λ��*/


#define BC_USERMGMT_USER_NUM	(BC_USERMGMT_DEVELOPER_NUM+BC_USERMGMT_FACTORY_NUM+BC_USERMGMT_OBLIGATE_NUM+BC_USERMGMT_NORMAL_NUM)		/*����˺���*/
#define BC_USERMGMT_INFO_SIZE	(sizeof(bc_usermgmt_info_t))		/*ÿ���˺ŵĿռ��С*/
#define BC_USERMGMT_LIST_SIZE (BC_USERMGMT_INFO_SIZE*BC_USERMGMT_USER_NUM)	/*�˺�SIZE*/
#define BC_USERMGMT_LINKS_MAX 8		/*�˻����������*/
#define BC_USERMGMT_SID_UNUSED (-1)	/*SID δʹ��*/

/*
    CLI_ACC_LVL_BASIC = 1,
    CLI_ACC_LVL_PRIVI,
    CLI_ACC_LVL_USER,
    CLI_ACC_LVL_PUSER,
    CLI_ACC_LVL_ADMIN,
    CLI_ACC_LVL_FACTORY,
    CLI_ACC_LVL_DEBUG = 128
*/

//�û�Ȩ��
typedef enum{
	BC_USERMGMT_LVL_BASIC = 1,	/*����*/
	BC_USERMGMT_LVL_PRIVI,		/*��Ȩ*/
	BC_USERMGMT_LVL_USER,			/*�û�*/
	BC_USERMGMT_LVL_PUSER,		/*PUSER*/
	BC_USERMGMT_LVL_ADMIN,		/*����Ա*/
	BC_USERMGMT_LVL_FACTORY,		/*����*/
	BC_USERMGMT_LVL_DEBUG = 128,	/*����/��ʽ*/
	BC_USERMGMT_LVL_MAX
}bc_usermgmt_level_e;

//�˺�״̬
typedef enum{
	BC_USERMGMT_STATE_LOGIN = 1,		/*��½*/
	BC_USERMGMT_STATE_LOGOUT,		/*�ǳ�*/
	BC_USERMGMT_STATE_UNUSED		/*δע��*/
}bc_usermgmt_state_e;


//�û���½��Ϣ
typedef struct
{
	int sid;								/* session id*/
	bc_usermgmt_state_e state;			/*��½״̬*/
}bc_username_line_info;


//�û���Ϣ
typedef struct 
{
	bc_char 				name[BC_USERMGMT_NAME_LEN];			/*�û���*/
	bc_char 				pwd[BC_USERMGMT_NAME_LEN];			/*��������*/
	bc_char 				encrypt_pwd[BC_USERMGMT_NAME_LEN];	/*��������*/
	bc_usermgmt_level_e	level;									/*�û�Ȩ��*/
	bc_int32 				links;									/*������*/
	bc_usermgmt_state_e 	state;									/*�û�״̬*/
	time_t 				login_time;								/*��½ʱ��*/
	time_t 				logout_time; 							/*�ǳ�ʱ��*/
	bc_boolean 			encrypt_enable;							/*����ʹ��*/
	bc_username_line_info 	line_info[BC_USERMGMT_LINKS_MAX];		/*������Ϣ*/
}bc_usermgmt_info_t;




////////////////////////////////////////////////////////////////////////////////
//																			  //
//						�� �� �� ���� �� �� �� ��							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////



#endif /* __BC_SYS_USERMGMT_DEF_H__ */


