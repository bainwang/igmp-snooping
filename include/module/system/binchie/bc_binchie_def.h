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
	2016-07-31  Created									bain.wang@outlook.com
*******************************************************************************/

#ifndef __BC_BINCHIE_DEF_H__
#define __BC_BINCHIE_DEF_H__

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								ͷ   ��   ��								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_err.h"
#include "bc_binchie_def.h"
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

#define BC_BINCHIE_OP_PWD		"bain.wang@outlook.com"

#define BC_BINCHIE_TEL_LEN_MAX		12
#define BC_BINCHIE_QQ_LEN_MAX		12
#define BC_BINCHIE_FAX_LEN_MAX		12
#define BC_BINCHIE_JOB_LEN_MAX		12
#define BC_BINCHIE_EMAIL_LEN_MAX	32
#define BC_BINCHIE_WECHAT_LEN_MAX	32

#define BC_BINCHIE_NAME_LEN_MAX		32
#define BC_BINCHIE_ADDR_LEN_MAX		128


#define BC_BINCHIE_DEVELOPER_USER_NUM_MAX		1
#define BC_BINCHIE_TEST_USER_NUM_MAX			5
#define BC_BINCHIE_VINDICATOR_USER_NUM_MAX		10
#define BC_BINCHIE_USER_NUM_MAX					(BC_BINCHIE_DEVELOPER_USER_NUM_MAX+BC_BINCHIE_TEST_USER_NUM_MAX+BC_BINCHIE_VINDICATOR_USER_NUM_MAX)

#define BC_BINCHIE_DEVELOPER_IDX				0

#define BC_BINCHIE_DEVELOPER_NAME_DEF			"WangBin"
#define BC_BINCHIE_DEVELOPER_SEX_DEF			BC_BINCHIE_SEX_MAN
#define BC_BINCHIE_DEVELOPER_AGE_DEF			31
#define BC_BINCHIE_DEVELOPER_ADDR_DEF			"ChengDu"
#define BC_BINCHIE_DEVELOPER_CONTACT_TEL_DEF	"138xxxx4828"
#define BC_BINCHIE_DEVELOPER_CONTACT_FAX_DEF	"empty"
#define BC_BINCHIE_DEVELOPER_CONTACT_JOB_DEF	"empty"
#define BC_BINCHIE_DEVELOPER_CONTACT_WECHAT_DEF	"138xxxx4828"
#define BC_BINCHIE_DEVELOPER_CONTACT_EMAIL_DEF	"bain.wang@outlook.com"
#define BC_BINCHIE_DEVELOPER_CONTACT_QQ_DEF		"136335455"

typedef enum{
	BC_BINCHIE_SEX_MAN = 0,		/*��*/
	BC_BINCHIE_SEX_WOMAN,		/*Ů*/
	BC_BINCHIE_SEX_VALID
}bc_binchie_sex_e;

typedef enum{
	BC_BINCHIE_DUTY_DEVELOPER = 0,		/*������*/
	BC_BINCHIE_DUTY_TEST,				/*������*/
	BC_BINCHIE_DUTY_VINDICATOR,			/*ά����*/
	BC_BINCHIE_DUTY_DEVEP_TEST,			/*�������������*/
	BC_BINCHIE_DUTY_DEVEP_VINDI,		/*��������ά����*/
	BC_BINCHIE_DUTY_TEST_VINDI,			/*��������ά����*/
	BC_BINCHIE_DUTY_DEVEP_TEST_VINDI,	/*���������������ά����*/
	BC_BINCHIE_DUTY_OTHER,				/*������Ա����ʹ����*/
	BC_BINCHIE_DUTY_INVALID
}bc_binchie_duty_e;

typedef struct{
	char tel[BC_BINCHIE_TEL_LEN_MAX];			/*�ֻ�*/
	char qq[BC_BINCHIE_QQ_LEN_MAX];				/*QQ */
	char fax[BC_BINCHIE_FAX_LEN_MAX];			/*����*/
	char email[BC_BINCHIE_EMAIL_LEN_MAX];		/*����*/
	char wechat[BC_BINCHIE_WECHAT_LEN_MAX];		/*΢��*/
	char job[BC_BINCHIE_JOB_LEN_MAX];			/*����*/
}bc_binchie_contact_t;

typedef struct{
	char name[BC_BINCHIE_NAME_LEN_MAX];	/*����*/
	bc_binchie_sex_e sex;						/*�Ա�*/
	int age;									/*����*/
	char addr[BC_BINCHIE_ADDR_LEN_MAX];			/*��ַ*/
	bc_binchie_duty_e duty;						/*ְ��*/
	bc_binchie_contact_t contact;				/*��ϵ��ʽ*/
	bc_boolean is_used;							/*������Ϣ�Ƿ���Ч*/
	bc_boolean is_continued;					/*�Ƿ���Ȼά����*/
}bc_binchie_info_t;


#endif /* __BC_BINCHIE_DEF_H__ */





