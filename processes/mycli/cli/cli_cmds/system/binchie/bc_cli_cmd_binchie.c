/*******************************************************************************
  -------------------------------------------------------------------------
  [File name]  : \\BC\bc_sys_global_info.c
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
	2016-09-05  Created									bain.wang@outlook.com
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								ͷ   ��   ��								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>  
#include <unistd.h>  
#include <errno.h>  
#include <string.h>


#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "bc_modules.h"

#include "bc_cli_type.h"
#include "bc_cli_paratype.h"

#include "bc_cli.h"
#include "bc_binchie_def.h"
#include "bc_binchie_client.h"

#include "utili_bit.h"
#include "bc_cli_vkey.h"

static unsigned int 	l_mdl_id = BC_MODULE_BINCHIE;

////////////////////////////////////////////////////////////////////////////////
//																			  //
//						�� �� �� ���� �� �� �� ��					          //
//																			  //
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//																			  //
//						��   ��   ��   ��   ��   ��							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
/*
 *		��Դ�ļ���Ҫ����꣬��ͷ�ļ���������ģ��ͷ�ļ��еĺ궨�����ظ���������
 *	ʱ���ڴ˴����塣
 */
 #define PRT_CLI_PARA(l_mdl_id, cli_para) \
	do\
	{\
		cli_value_t *cli_para_tmp = cli_para;\
		UI32_T para_num = 1;\
		for (; NULL != cli_para_tmp; cli_para_tmp = cli_para_tmp->next, para_num++)\
		{\
			BC_PT_DBG_CPL\
			(\
				l_mdl_id,\
				"Cli Para No.%03u: Address=0x%08X type=%d, name=%s, priority=%d, next=0x%08X\r\n",\
				para_num, (int)cli_para_tmp,\
				cli_para_tmp->type, cli_para_tmp->name, cli_para_tmp->priority, (int)cli_para_tmp->next\
			);\
		}\
	} while (0)

#define CHECK_BCAPI_RET(ret_api)\
	do\
	{\
		if (ret_api != BC_ERR_OK)\
		{\
			bc_msg_err_get(ret_api, (bc_cli_get_lan() == CLI_LAN_CN ? BC_LAN_CHINESE_E : BC_LAN_ENGLISH_E));\
			return;\
		}\
	} while (0)
	

#define ECHOFLAGS (ECHO | ECHOE | ECHOK | ECHONL)  
////////////////////////////////////////////////////////////////////////////////
//																			  //
//							ȫ �� �� �� �� ��							      //
//																			  //
////////////////////////////////////////////////////////////////////////////////
/* 
 *	�ⲿȫ�ֱ������ṩ�������̵��ã���ͷ�ļ����ṩ���ýӿ�(�ⲿ��������)��
 */

/* 
 *	�ڲ�ȫ�ֱ�����ֻ�ṩ�����ļ��ڲ��������ã�����ͷ�ļ����ṩ���ýӿڡ�
 */


////////////////////////////////////////////////////////////////////////////////
//																			  //
//								��  ��  ��  ��							      //
//																			  //
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//																			  //
//								��  ��  ��  ��							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

static cli_cmd_ret_e __binchie_authen(UI32_T sid)
{
	char ptr[BC_BINCHIE_NAME_LEN_MAX];
	char buf[255];
	cli_lan_t     language = CLI_LAN_MAX;
	I32_T   trigger[]   =
	{
		CLI_VKEY_CTRL_ENTER, CLI_VKEY_CR, 0
	};

	CLI_DBG_ENTER(l_mdl_id);
	language = bc_cli_get_lan();
	
	if(language == CLI_LAN_EN)
	{	
		snprintf(buf, sizeof(buf), "%s", "Input password(<=15 chars):");
	}
	else
	{
		snprintf(buf, sizeof(buf), "%s", "������������֤(<=15 chars):");
	}
	
	memset(ptr, 0, sizeof(ptr));
        CLI_API_Printf(sid, "\r\n %s", buf);
      	bc_cli_get_line(sid, sizeof(buf), CLI_OUTPUT_NORMAL, ptr, sizeof(ptr), 60, trigger);
	ptr[strlen(ptr)] = '\0';
	
	if(strlen(ptr) > 15
		|| !strlen(ptr)
		||strcmp(BC_BINCHIE_OP_PWD, ptr))
	{
		if(language == CLI_LAN_EN)
		{	
			CLI_API_Printf(sid, "\r\n\n Authentication failure\r\n");
		}
		else
		{
			CLI_API_Printf(sid, "\r\n\n \t��֤ʧ��\r\n");
		} 
		
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	else
	{
		if(language == CLI_LAN_EN)
		{	
			CLI_API_Printf(sid, "\r\n\n Authentication success\r\n");
		}
		else
		{
			CLI_API_Printf(sid, "\r\n\n \t��֤�ɹ�\r\n");
		} 
	}

	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

/******************************************************************************\
  Function   : __usermgmt_register
  Description: ע��
  Return     : bool true: �ɹ�  false:����ʧ��
  Others     : 
\******************************************************************************/
static cli_cmd_ret_e __binchie_add
(
	IN const UI32_T	sid,
	IN cli_value_t		*ptrCliValue,
	IN void			*ptrUserData
)
{
	bc_err_e ret = BC_ERR_OK;
	bc_binchie_info_t info;	
	char ptr[BC_BINCHIE_NAME_LEN_MAX];
	int tmp_lvl = 0;
	char *p = NULL;
	bc_int32 cnt = 0;
	cli_lan_t     language = CLI_LAN_MAX;
	char buf[255];
	I32_T   trigger[]   =
	{
		CLI_VKEY_CTRL_ENTER, CLI_VKEY_CR, 0
	};
//	I32_T rxCh;
	
	CLI_DBG_ENTER(l_mdl_id);

	language = bc_cli_get_lan();
	
	memset(&info, 0, sizeof(info));

	if(__binchie_authen(sid) != CLI_CMD_SUCCESS_PRT_NEWLINE)
	{
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}

	/*name*/
	if(language == CLI_LAN_EN)
	{	
		snprintf(buf, sizeof(buf), "%s", "New Username(<=15 chars):");
	}
	else
	{
		snprintf(buf, sizeof(buf), "%s", "����Ա����(<=15 chars):");
	}
	
	memset(ptr, 0, sizeof(ptr));

      	bc_cli_get_line(sid, sizeof(buf), CLI_OUTPUT_NORMAL, ptr, sizeof(ptr), 60, trigger);
	ptr[strlen(ptr)] = '\0';
	
	if(strlen(ptr) > 15)
	{
		if(language == CLI_LAN_EN)
		{	
			CLI_API_Printf(sid, "\r\n\n Operation failure: the name is too long!\r\n");
		}
		else
		{
			CLI_API_Printf(sid, "\r\n\n ����ʧ��:����̫��!\r\n");
		}
		
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	if(!strlen(ptr))
	{
		if(language == CLI_LAN_EN)
		{	
			CLI_API_Printf(sid, "\r\n\n Operation failure: the name is too short!\r\n");
		}
		else
		{
			CLI_API_Printf(sid, "\r\n\n ����ʧ��: ����̫��!\r\n");
		}
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	
	p = ptr;
	while(*p != '\0')
	{
		if((*p>=48&&*p<=57) || (*p>=65&&*p<=90) || (*p>=97&&*p<=122))
		{
		//	printf("1-%c\n", *p);
		}
		else
		{
		//	printf("2-%c\n", *p);
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n Operation failure: name can only be letters or numbers.\r\n");
			}
			else
			{
				CLI_API_Printf(sid, "\r\n\n ����ʧ��: ������ֻ��Ϊ��ĸ������!\r\n");
			}
			return CLI_CMD_FAIL_PRT_NEWLINE;
		}
		p++;
	}
	strcpy(info.name, ptr);

	/*sex*/
	if(language == CLI_LAN_EN)
	{	
		CLI_API_Printf(sid, "\r\n 1.Man   2.Woman");
		CLI_API_Printf(sid, "\r\n User's Sex: ");
	}
	else
	{
		CLI_API_Printf(sid, "\r\n 1.Man   2.Woman");
		CLI_API_Printf(sid, "\r\n ��Ա�Ա�:");
	}

	setbuf(stdin, NULL);
	fgets(ptr, 256, stdin);
	if(strlen(ptr) != 2)
	{
		if(language == CLI_LAN_EN)
		{	
			CLI_API_Printf(sid, "\r\n Operation failure: sex input error!\r\n");
		}
		else
		{
			CLI_API_Printf(sid, "\r\n ����ʧ��: �Ա��������!\r\n");
		}
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	ptr[strlen(ptr)-1] = '\0';
	tmp_lvl = ptr[0] - '0';
		
	switch(tmp_lvl)
	{
		case 1:
			info.sex = BC_BINCHIE_SEX_MAN;
			break;
		case 2:
			info.sex = BC_BINCHIE_SEX_WOMAN;
			break;
		default:
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n Operation failure: sex error!\r\n");
			}
			else
			{
			CLI_API_Printf(sid, "\r\n ����ʧ��: �Ա��������!\r\n");
			}
			return CLI_CMD_FAIL_PRT_NEWLINE;
	}	

	/*age*/
	if(language == CLI_LAN_EN)
	{	
		CLI_API_Printf(sid, "\r\n User's age(50<= x >=15): ");
	}
	else
	{
		CLI_API_Printf(sid, "\r\n ��Ա����(50<= x >=15): ");
	}

	setbuf(stdin, NULL);
	fgets(ptr, 256, stdin);
	if(strlen(ptr) != 3)
	{
		if(language == CLI_LAN_EN)
		{	
			CLI_API_Printf(sid, "\r\n Operation failure: age input error!\r\n");
		}
		else
		{
			CLI_API_Printf(sid, "\r\n ����ʧ��: �����������!\r\n");
		}
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	ptr[strlen(ptr)-2] = '\0';
	tmp_lvl = ((ptr[0] - '0')*10)+(ptr[1] - '0');

	if(tmp_lvl<15 || tmp_lvl> 50)
	{
		if(language == CLI_LAN_EN)
		{	
			CLI_API_Printf(sid, "\r\n Operation failure: age input error!\r\n");
		}
		else
		{
			CLI_API_Printf(sid, "\r\n ����ʧ��: �����������!\r\n");
		}
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	info.age = tmp_lvl;

	/*addr*/
	if(language == CLI_LAN_EN)
	{	
		snprintf(buf, sizeof(buf), "%s", "Adress(<=32 chars):");
	}
	else
	{
		snprintf(buf, sizeof(buf), "%s", "����Ա��ַ(<=32 chars):");
	}
	
	memset(ptr, 0, sizeof(ptr));
        CLI_API_Printf(sid, "\r\n %s", buf);
      	bc_cli_get_line(sid, sizeof(buf), CLI_OUTPUT_NORMAL, ptr, sizeof(ptr), 60, trigger);
	ptr[strlen(ptr)] = '\0';
	
	if(strlen(ptr) > 32)
	{
		if(language == CLI_LAN_EN)
		{	
			CLI_API_Printf(sid, "\r\n\n Operation failure: the addr is too long!\r\n");
		}
		else
		{
			CLI_API_Printf(sid, "\r\n\n ����ʧ��:��ַ̫��!\r\n");
		}
		
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	if(!strlen(ptr))
	{
		if(language == CLI_LAN_EN)
		{	
			CLI_API_Printf(sid, "\r\n\n Operation failure: the addr is too short!\r\n");
		}
		else
		{
			CLI_API_Printf(sid, "\r\n\n ����ʧ��:��ַ̫��!\r\n");
		}
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	
	p = ptr;
	while(*p != '\0')
	{
		if((*p>=48&&*p<=57) || (*p>=65&&*p<=90) || (*p>=97&&*p<=122))
		{
		//	printf("1-%c\n", *p);
		}
		else
		{
		//	printf("2-%c\n", *p);
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n Operation failure: addr can only be letters or numbers.\r\n");
			}
			else
			{
				CLI_API_Printf(sid, "\r\n\n ����ʧ��: ��ַֻ��Ϊ��ĸ������!\r\n");
			}
			return CLI_CMD_FAIL_PRT_NEWLINE;
		}
		p++;
	}
	strcpy(info.addr, ptr);
#if 1
	/*duty*/
	if(language == CLI_LAN_EN)
	{	
		CLI_API_Printf(sid, "\r\n 1.Developer   2.Test   3.Vindicator   4.D&T   5.D&V   6.T&V   7.D&T&V   8.other");
		CLI_API_Printf(sid, "\r\n User's Duty: ");
	}
	else
	{
		CLI_API_Printf(sid, "\r\n 1.�з�   2.����   3.ά��   4.�з������   5.�з���ά��   6.������ά��   7.�з��������ά����   8.����");
		CLI_API_Printf(sid, "\r\n ��Աְ��:");
	}

	setbuf(stdin, NULL);
	fgets(ptr, 256, stdin);
	if(strlen(ptr) != 2)
	{
		if(language == CLI_LAN_EN)
		{	
			CLI_API_Printf(sid, "\r\n Operation failure: duty input error!\r\n");
		}
		else
		{
			CLI_API_Printf(sid, "\r\n ����ʧ��: ְ���������!\r\n");
		}
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	ptr[strlen(ptr)-1] = '\0';
	tmp_lvl = ptr[0] - '0';
		
	switch(tmp_lvl)
	{
		case 1:
			info.duty = BC_BINCHIE_DUTY_DEVELOPER;
			break;
		case 2:
			info.duty = BC_BINCHIE_DUTY_TEST;
			break;
		case 3:
			info.duty = BC_BINCHIE_DUTY_VINDICATOR;
			break;
		case 4:
			info.duty = BC_BINCHIE_DUTY_DEVEP_TEST;
			break;
		case 5:
			info.duty = BC_BINCHIE_DUTY_DEVEP_VINDI;
			break;
		case 6:
			info.duty = BC_BINCHIE_DUTY_TEST_VINDI;
			break;
		case 7:
			info.duty = BC_BINCHIE_DUTY_DEVEP_TEST_VINDI;
			break;
		case 8:
			info.duty = BC_BINCHIE_DUTY_OTHER;
			break;
		default:
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n Operation failure: duty input error!\r\n");
			}
			else
			{
			CLI_API_Printf(sid, "\r\n ����ʧ��: ְ���������!\r\n");
			}
			return CLI_CMD_FAIL_PRT_NEWLINE;
	}
#endif
	/*contact*/
	if(language == CLI_LAN_EN)
	{	
		snprintf(buf, sizeof(buf), "%s", "Contact-Tel(<=11 chars):");
	}
	else
	{
		snprintf(buf, sizeof(buf), "%s", "��ϵ�绰(<=32 chars):");
	}
	
	memset(ptr, 0, sizeof(ptr));
        CLI_API_Printf(sid, "\r\n %s", buf);
      	bc_cli_get_line(sid, sizeof(buf), CLI_OUTPUT_NORMAL, ptr, sizeof(ptr), 60, trigger);
	ptr[strlen(ptr)] = '\0';
	
	if(strlen(ptr) > 11)
	{
		if(language == CLI_LAN_EN)
		{	
			CLI_API_Printf(sid, "\r\n\n Operation failure: the tel number is too long!\r\n");
		}
		else
		{
			CLI_API_Printf(sid, "\r\n\n ����ʧ��:�绰����̫��!\r\n");
		}
		
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	if(!strlen(ptr))
	{
		if(language == CLI_LAN_EN)
		{	
			CLI_API_Printf(sid, "\r\n\n Operation failure: the tel number is too short!\r\n");
		}
		else
		{
			CLI_API_Printf(sid, "\r\n\n ����ʧ��:�绰����̫��!\r\n");
		}
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	
	p = ptr;
	while(*p != '\0')
	{
		if(*p>=48&&*p<=57)
		{
		//	printf("1-%c\n", *p);
		}
		else
		{
		//	printf("2-%c\n", *p);
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n Operation failure: tel number can only be numbers.\r\n");
			}
			else
			{
				CLI_API_Printf(sid, "\r\n\n ����ʧ��: �绰����ֻ��Ϊ����!\r\n");
			}
			return CLI_CMD_FAIL_PRT_NEWLINE;
		}
		p++;
	}
	strcpy(info.contact.tel, ptr);

	/*qq*/
	if(language == CLI_LAN_EN)
	{	
		snprintf(buf, sizeof(buf), "%s", "QQ(<=32 chars):");
	}
	else
	{
		snprintf(buf, sizeof(buf), "%s", "QQ����(<=32 chars):");
	}
	
	memset(ptr, 0, sizeof(ptr));
        CLI_API_Printf(sid, "\r\n %s", buf);
      	bc_cli_get_line(sid, sizeof(buf), CLI_OUTPUT_NORMAL, ptr, sizeof(ptr), 60, trigger);
	ptr[strlen(ptr)] = '\0';
	
	if(strlen(ptr) > 11)
	{
		if(language == CLI_LAN_EN)
		{	
			CLI_API_Printf(sid, "\r\n\n Operation failure: the qq is too long!\r\n");
		}
		else
		{
			CLI_API_Printf(sid, "\r\n\n ����ʧ��:QQ̫��!\r\n");
		}
		
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	if(!strlen(ptr))
	{
		if(language == CLI_LAN_EN)
		{	
			CLI_API_Printf(sid, "\r\n\n Operation failure: the qq is too short!\r\n");
		}
		else
		{
			CLI_API_Printf(sid, "\r\n\n ����ʧ��:QQ̫��!\r\n");
		}
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	
	p = ptr;
		
	strcpy(info.contact.qq, ptr);

	/*wechat*/
	if(language == CLI_LAN_EN)
	{	
		snprintf(buf, sizeof(buf), "%s", "Wechat(<=32 chars):");
	}
	else
	{
		snprintf(buf, sizeof(buf), "%s", "΢�ź�(<=32 chars):");
	}
	
	memset(ptr, 0, sizeof(ptr));
        CLI_API_Printf(sid, "\r\n %s", buf);
      	bc_cli_get_line(sid, sizeof(buf), CLI_OUTPUT_NORMAL, ptr, sizeof(ptr), 60, trigger);
	ptr[strlen(ptr)] = '\0';
	
	if(strlen(ptr) > 32)
	{
		if(language == CLI_LAN_EN)
		{	
			CLI_API_Printf(sid, "\r\n\n Operation failure: the wechat is too long!\r\n");
		}
		else
		{
			CLI_API_Printf(sid, "\r\n\n ����ʧ��:΢�ź�̫��!\r\n");
		}
		
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	if(!strlen(ptr))
	{
		if(language == CLI_LAN_EN)
		{	
			CLI_API_Printf(sid, "\r\n\n Operation failure: the wechat is too short!\r\n");
		}
		else
		{
			CLI_API_Printf(sid, "\r\n\n ����ʧ��:΢�ź�̫��!\r\n");
		}
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	
	p = ptr;	
	strcpy(info.contact.wechat, ptr);

	/*email*/
	if(language == CLI_LAN_EN)
	{	
		snprintf(buf, sizeof(buf), "%s", "E-mail(<=32 chars):");
	}
	else
	{
		snprintf(buf, sizeof(buf), "%s", "��������(<=32 chars):");
	}
	
	memset(ptr, 0, sizeof(ptr));
        CLI_API_Printf(sid, "\r\n %s", buf);
      	bc_cli_get_line(sid, sizeof(buf), CLI_OUTPUT_NORMAL, ptr, sizeof(ptr), 60, trigger);
	ptr[strlen(ptr)] = '\0';
	
	if(strlen(ptr) > 32)
	{
		if(language == CLI_LAN_EN)
		{	
			CLI_API_Printf(sid, "\r\n\n Operation failure: the email is too long!\r\n");
		}
		else
		{
			CLI_API_Printf(sid, "\r\n\n ����ʧ��:����̫��!\r\n");
		}
		
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	if(!strlen(ptr))
	{
		if(language == CLI_LAN_EN)
		{	
			CLI_API_Printf(sid, "\r\n\n Operation failure: the email is too short!\r\n");
		}
		else
		{
			CLI_API_Printf(sid, "\r\n\n ����ʧ��:����̫��!\r\n");
		}
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	
	p = ptr;
	strcpy(info.contact.email, ptr);

	/*is on duty*/
	if(language == CLI_LAN_EN)
	{	
		CLI_API_Printf(sid, "\r\n 1.Yes   2.No");
		CLI_API_Printf(sid, "\r\n Is on duty?: ");
	}
	else
	{
		CLI_API_Printf(sid, "\r\n 1.��   2.��");
		CLI_API_Printf(sid, "\r\n ��Ա�Ƿ��������ְ��?:");
	}

	setbuf(stdin, NULL);
	fgets(ptr, 256, stdin);
	if(strlen(ptr) != 2)
	{
		if(language == CLI_LAN_EN)
		{	
			CLI_API_Printf(sid, "\r\n Operation failure: duty continued input error!\r\n");
		}
		else
		{
			CLI_API_Printf(sid, "\r\n ����ʧ��: ְ�������������!\r\n");
		}
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	ptr[strlen(ptr)-1] = '\0';
	tmp_lvl = ptr[0] - '0';
		
	switch(tmp_lvl)
	{
		case 1:
			info.is_continued = TRUE;
			break;
		case 2:
			info.is_continued = FALSE;
			break;
		default:
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n Operation failure: duty continued input error!\r\n");
			}
			else
			{
				CLI_API_Printf(sid, "\r\n ����ʧ��: ְ�������������!\r\n");
			}
			return CLI_CMD_FAIL_PRT_NEWLINE;
	}

	info.is_used = TRUE;

	ret = bc_binchie_add_info(info);
	if(ret != BC_ERR_OK)
	{
		if(ret == BC_ERR_BINCHIE_USER_FULL)
		{
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n Operation failure: binchie user full!\r\n");
			}
			else
			{
				CLI_API_Printf(sid, "\r\n ����ʧ��: �û�����!\r\n");
			}
		}
		else if(ret == BC_ERR_BINCHIE_USER_EMPTY)
		{
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n Operation failure: binchie user empty!\r\n");
			}
			else
			{
				CLI_API_Printf(sid, "\r\n ����ʧ��: �û��ѿ�!\r\n");
			}
		}
		else if(ret == BC_ERR_BINCHIE_USER_ALREADY_EXIST)
		{
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n Operation failure: binchie user already exist!\r\n");
			}
			else
			{
				CLI_API_Printf(sid, "\r\n ����ʧ��: �û��Ѵ���!\r\n");
			}
		}
		else if(ret == BC_ERR_BINCHIE_USER_INEXIST)
		{
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n Operation failure: binchie user no exist!\r\n");
			}
			else
			{
				CLI_API_Printf(sid, "\r\n ����ʧ��: �û�������!\r\n");
			}
		}
		else if(ret == BC_ERR_BINCHIE_USER_UNLAWFUL)
		{
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n Operation failure: binchie user unlawful!\r\n");
			}
			else
			{
				CLI_API_Printf(sid, "\r\n ����ʧ��: �Ƿ������з���Ա��Ϣ!\r\n");
			}
		}
		else if(ret == BC_ERR_BINCHIE_USER_DUTY_INVALID)
		{
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n Operation failure: binchie user duty invalid!\r\n");
			}
			else
			{
				CLI_API_Printf(sid, "\r\n ����ʧ��: ��Աְ����Ϊ�з�!\r\n");
			}
		}
		else
		{
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n Operation failure: this binchie user add failure!\r\n");
			}
			else
			{
				CLI_API_Printf(sid, "\r\n ����ʧ��: binchie��Ա���ʧ��!\r\n");
			}
		}
		
	//	CLI_API_Printf(sid, "\r\n Failed to usermgmt register, ret = 0x%x!\r\n", ret);
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	
	if(language == CLI_LAN_EN)
	{	
		CLI_API_Printf(sid, "\r\n This binchie user has been add success!\r\n");
	}
	else
	{
		CLI_API_Printf(sid, "\r\n binchie��Ա��ӳɹ�!\r\n");
	}
}

/******************************************************************************\
  Function   : __usermgmt_unregister
  Description: ע��
  Return     : bool true: �ɹ�  false:����ʧ��
  Others     : 
\******************************************************************************/
static cli_cmd_ret_e __binchie_del
(
	IN const UI32_T	sid,
	IN cli_value_t		*ptrCliValue,
	IN void			*ptrUserData
)
{
	bc_err_e ret = BC_ERR_OK;
	char			pUsrPrompt[256];
	cli_value_t *para_tmp = ptrCliValue;
	bc_char name[BC_BINCHIE_USER_NUM_MAX];
	cli_lan_t     language = CLI_LAN_MAX;

	language = bc_cli_get_lan();
	strcpy(name, (bc_char *)para_tmp->value);

	if(__binchie_authen(sid) != CLI_CMD_SUCCESS_PRT_NEWLINE)
	{
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	
	if(language == CLI_LAN_EN)
	{	
		CLI_API_Printf(sid, "\r\n Are you sure to delete the user?(y/n)\r\n");
	}
	else
	{
		CLI_API_Printf(sid, "\r\n ȷ��ɾ�������Ա?(y/n)\r\n");
	}
	
	setbuf(stdin, NULL);
	fgets(pUsrPrompt, 256, stdin);
	
//	CLI_API_Printf(sid, "%c\r\n", pUsrPrompt[0]);
	if ((pUsrPrompt[0] != 'y') && (pUsrPrompt[0] != 'Y'))
	{
		setbuf(stdin, NULL);
		return CLI_CMD_SUCCESS_PRT_NEWLINE;
	}
	
	ret = bc_binchie_del_info(name);
	if(ret != BC_ERR_OK)
	{
		if(ret == BC_ERR_BINCHIE_USER_FULL)
		{
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n Operation failure: binchie user full!\r\n");
			}
			else
			{
				CLI_API_Printf(sid, "\r\n ����ʧ��: �û�����!\r\n");
			}
		}
		else if(ret == BC_ERR_BINCHIE_USER_EMPTY)
		{
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n Operation failure: binchie user empty!\r\n");
			}
			else
			{
				CLI_API_Printf(sid, "\r\n ����ʧ��: �û��ѿ�!\r\n");
			}
		}
		else if(ret == BC_ERR_BINCHIE_USER_ALREADY_EXIST)
		{
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n Operation failure: binchie user already exist!\r\n");
			}
			else
			{
				CLI_API_Printf(sid, "\r\n ����ʧ��: �û��Ѵ���!\r\n");
			}
		}
		else if(ret == BC_ERR_BINCHIE_USER_INEXIST)
		{
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n Operation failure: binchie user no exist!\r\n");
			}
			else
			{
				CLI_API_Printf(sid, "\r\n ����ʧ��: �û�������!\r\n");
			}
		}
		else if(ret == BC_ERR_BINCHIE_USER_UNLAWFUL)
		{
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n Operation failure: binchie user unlawful!\r\n");
			}
			else
			{
				CLI_API_Printf(sid, "\r\n ����ʧ��: �Ƿ������з���Ա��Ϣ!\r\n");
			}
		}
		else if(ret == BC_ERR_BINCHIE_USER_DUTY_INVALID)
		{
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n Operation failure: binchie user duty invalid!\r\n");
			}
			else
			{
				CLI_API_Printf(sid, "\r\n ����ʧ��: ��Աְ����Ϊ�з�!\r\n");
			}
		}
		else
		{
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n Operation failure: this binchie user add failure!\r\n");
			}
			else
			{
				CLI_API_Printf(sid, "\r\n ����ʧ��: binchie��Ա���ʧ��!\r\n");
			}
		}
		
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	if(language == CLI_LAN_EN)
	{	
	
		CLI_API_Printf(sid, "\r\n This user has been deleted success!\r\n");
	}
	else
	{
		CLI_API_Printf(sid, "\r\n ��Աɾ���ɹ�!\r\n");
	}
	
	CLI_DBG_LEAVE(l_mdl_id);
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

/******************************************************************************\
  Function   : __usermgmt_set_pwd
  Description: ��������
  Return     : bool true: �ɹ�  false:����ʧ��
  Others     : 
\******************************************************************************/
static cli_cmd_ret_e __binchie_set
(
	IN const UI32_T	sid,
	IN cli_value_t		*ptrCliValue,
	IN void			*ptrUserData
)
{
	bc_err_e ret = BC_ERR_OK;
	cli_value_t *para_tmp = ptrCliValue;
	UI32_T op_id = *(UI32_T *)para_tmp->value;
	
	bc_binchie_info_t info;	
	char ptr[BC_BINCHIE_NAME_LEN_MAX];
	char name[BC_BINCHIE_NAME_LEN_MAX];
	int tmp_lvl = 0;
	char *p = NULL;
	bc_int32 cnt = 0;
	cli_lan_t     language = CLI_LAN_MAX;
	char buf[255];
	I32_T   trigger[]   =
	{
		CLI_VKEY_CTRL_ENTER, CLI_VKEY_CR, 0
	};
//	I32_T rxCh;
	
	CLI_DBG_ENTER(l_mdl_id);

	language = bc_cli_get_lan();
	memset(&info, 0, sizeof(info));

	CLI_API_Printf(sid, "\r\n*** not supported warning ***\r\n");
#if 0
	if(__binchie_authen(sid) != CLI_CMD_SUCCESS_PRT_NEWLINE)
	{
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	
	para_tmp = para_tmp->next;
	strcpy(name, (bc_char *)para_tmp->value);

	if(bc_binchie_get_info(name, &info) != BC_ERR_OK)
	{
		if(language == CLI_LAN_EN)
		{	
		
			CLI_API_Printf(sid, "\r\n Operation failure: this binchie user set failure!\r\n");
		}
		else
		{
			CLI_API_Printf(sid, "\r\n ����ʧ��: binchie��Ա�޸�ʧ��!\r\n");
		}
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	
	switch(op_id)
	{
		case 21:	/*name*/
			if(language == CLI_LAN_EN)
			{	
				snprintf(buf, sizeof(buf), "%s", "New Username(<=15 chars):");
			}
			else
			{
				snprintf(buf, sizeof(buf), "%s", "����Ա����(<=15 chars):");
			}
			
			memset(ptr, 0, sizeof(ptr));
		        CLI_API_Printf(sid, "\r\n %s", buf);
		      	bc_cli_get_line(sid, sizeof(buf), CLI_OUTPUT_NORMAL, ptr, sizeof(ptr), 60, trigger);
			ptr[strlen(ptr)] = '\0';
	
			if(strlen(ptr) > 15)
			{
				if(language == CLI_LAN_EN)
				{	
					CLI_API_Printf(sid, "\r\n\n Operation failure: the name is too long!\r\n");
				}
				else
				{
					CLI_API_Printf(sid, "\r\n\n ����ʧ��:����̫��!\r\n");
				}
				
				return CLI_CMD_FAIL_PRT_NEWLINE;
			}
			if(!strlen(ptr))
			{
				if(language == CLI_LAN_EN)
				{	
					CLI_API_Printf(sid, "\r\n\n Operation failure: the name is too short!\r\n");
				}
				else
				{
					CLI_API_Printf(sid, "\r\n\n ����ʧ��: ����̫��!\r\n");
				}
				return CLI_CMD_FAIL_PRT_NEWLINE;
			}
	
			p = ptr;
			while(*p != '\0')
			{
				if((*p>=48&&*p<=57) || (*p>=65&&*p<=90) || (*p>=97&&*p<=122))
				{
				//	printf("1-%c\n", *p);
				}
				else
				{
				//	printf("2-%c\n", *p);
					if(language == CLI_LAN_EN)
					{	
						CLI_API_Printf(sid, "\r\n Operation failure: name can only be letters or numbers.\r\n");
					}
					else
					{
						CLI_API_Printf(sid, "\r\n\n ����ʧ��: ������ֻ��Ϊ��ĸ������!\r\n");
					}
					return CLI_CMD_FAIL_PRT_NEWLINE;
				}
				p++;
			}
			strcpy(info.name, ptr);	
			break;
		case 22:	/*sex*/
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n 1.Man   2.Woman");
				CLI_API_Printf(sid, "\r\n User's Sex: ");
			}
			else
			{
				CLI_API_Printf(sid, "\r\n 1.Man   2.Woman");
				CLI_API_Printf(sid, "\r\n ��Ա�Ա�:");
			}

			setbuf(stdin, NULL);
			fgets(ptr, 256, stdin);
			if(strlen(ptr) != 2)
			{
				if(language == CLI_LAN_EN)
				{	
					CLI_API_Printf(sid, "\r\n Operation failure: sex input error!\r\n");
				}
				else
				{
					CLI_API_Printf(sid, "\r\n ����ʧ��: �Ա��������!\r\n");
				}
				return CLI_CMD_FAIL_PRT_NEWLINE;
			}
			ptr[strlen(ptr)-1] = '\0';
			tmp_lvl = ptr[0] - '0';
				
			switch(tmp_lvl)
			{
				case 1:
					info.sex = BC_BINCHIE_SEX_MAN;
					break;
				case 2:
					info.sex = BC_BINCHIE_SEX_WOMAN;
					break;
				default:
					if(language == CLI_LAN_EN)
					{	
						CLI_API_Printf(sid, "\r\n Operation failure: sex error!\r\n");
					}
					else
					{
						CLI_API_Printf(sid, "\r\n ����ʧ��: �Ա��������!\r\n");
					}
					return CLI_CMD_FAIL_PRT_NEWLINE;
			}
			break;
		case 23:	/*age*/
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n User's age(50<= x >=15): ");
			}
			else
			{
				CLI_API_Printf(sid, "\r\n ��Ա����(50<= x >=15): ");
			}

			setbuf(stdin, NULL);
			fgets(ptr, 256, stdin);
			if(strlen(ptr) != 3)
			{
				if(language == CLI_LAN_EN)
				{	
					CLI_API_Printf(sid, "\r\n Operation failure: age input error!\r\n");
				}
				else
				{
					CLI_API_Printf(sid, "\r\n ����ʧ��: �����������!\r\n");
				}
				return CLI_CMD_FAIL_PRT_NEWLINE;
			}
			ptr[strlen(ptr)-1] = '\0';
			tmp_lvl = ptr[0] - '0';

			if(tmp_lvl<15 > 50)
			{
				if(language == CLI_LAN_EN)
				{	
					CLI_API_Printf(sid, "\r\n Operation failure: age input error!\r\n");
				}
				else
				{
					CLI_API_Printf(sid, "\r\n ����ʧ��: �����������!\r\n");
				}
				return CLI_CMD_FAIL_PRT_NEWLINE;
			}
			info.age = tmp_lvl;
			break;
		case 24:	/*addr*/
			/*addr*/
			if(language == CLI_LAN_EN)
			{	
				snprintf(buf, sizeof(buf), "%s", "Adress(<=32 chars):");
			}
			else
			{
				snprintf(buf, sizeof(buf), "%s", "����Ա��ַ(<=32 chars):");
			}
			
			memset(ptr, 0, sizeof(ptr));
		        CLI_API_Printf(sid, "\r\n %s", buf);
		      	bc_cli_get_line(sid, sizeof(buf), CLI_OUTPUT_NORMAL, ptr, sizeof(ptr), 60, trigger);
			ptr[strlen(ptr)] = '\0';
			
			if(strlen(ptr) > 32)
			{
				if(language == CLI_LAN_EN)
				{	
					CLI_API_Printf(sid, "\r\n\n Operation failure: the addr is too long!\r\n");
				}
				else
				{
					CLI_API_Printf(sid, "\r\n\n ����ʧ��:��ַ̫��!\r\n");
				}
				
				return CLI_CMD_FAIL_PRT_NEWLINE;
			}
			if(!strlen(ptr))
			{
				if(language == CLI_LAN_EN)
				{	
					CLI_API_Printf(sid, "\r\n\n Operation failure: the addr is too short!\r\n");
				}
				else
				{
					CLI_API_Printf(sid, "\r\n\n ����ʧ��:��ַ̫��!\r\n");
				}
				return CLI_CMD_FAIL_PRT_NEWLINE;
			}
	
			p = ptr;
			while(*p != '\0')
			{
				if((*p>=48&&*p<=57) || (*p>=65&&*p<=90) || (*p>=97&&*p<=122))
				{
				//	printf("1-%c\n", *p);
				}
				else
				{
				//	printf("2-%c\n", *p);
					if(language == CLI_LAN_EN)
					{	
						CLI_API_Printf(sid, "\r\n Operation failure: addr can only be letters or numbers.\r\n");
					}
					else
					{
						CLI_API_Printf(sid, "\r\n\n ����ʧ��: ��ַֻ��Ϊ��ĸ������!\r\n");
					}
					return CLI_CMD_FAIL_PRT_NEWLINE;
				}
				p++;
			}
			strcpy(info.addr, ptr);
			break;
		case 25:
		{
			para_tmp = para_tmp->next;
			op_id = *(UI32_T *)para_tmp->value;
			switch(op_id)
			{
				case 251:	/*tel*/
					if(language == CLI_LAN_EN)
					{	
						snprintf(buf, sizeof(buf), "%s", "Contact-Tel(<=11 chars):");
					}
					else
					{
						snprintf(buf, sizeof(buf), "%s", "��ϵ�绰(<=32 chars):");
					}
					
					memset(ptr, 0, sizeof(ptr));
				        CLI_API_Printf(sid, "\r\n %s", buf);
				      	bc_cli_get_line(sid, sizeof(buf), CLI_OUTPUT_NORMAL, ptr, sizeof(ptr), 60, trigger);
					ptr[strlen(ptr)] = '\0';
					
					if(strlen(ptr) > 11)
					{
						if(language == CLI_LAN_EN)
						{	
							CLI_API_Printf(sid, "\r\n\n Operation failure: the tel number is too long!\r\n");
						}
						else
						{
							CLI_API_Printf(sid, "\r\n\n ����ʧ��:�绰����̫��!\r\n");
						}
						
						return CLI_CMD_FAIL_PRT_NEWLINE;
					}
					if(!strlen(ptr))
					{
						if(language == CLI_LAN_EN)
						{	
							CLI_API_Printf(sid, "\r\n\n Operation failure: the tel number is too short!\r\n");
						}
						else
						{
							CLI_API_Printf(sid, "\r\n\n ����ʧ��:�绰����̫��!\r\n");
						}
						return CLI_CMD_FAIL_PRT_NEWLINE;
					}
			
					p = ptr;
					while(*p != '\0')
					{
						if(*p>=48&&*p<=57)
						{
						//	printf("1-%c\n", *p);
						}
						else
						{
						//	printf("2-%c\n", *p);
							if(language == CLI_LAN_EN)
							{	
								CLI_API_Printf(sid, "\r\n Operation failure: tel number can only be numbers.\r\n");
							}
							else
							{
								CLI_API_Printf(sid, "\r\n\n ����ʧ��: �绰����ֻ��Ϊ����!\r\n");
							}
							return CLI_CMD_FAIL_PRT_NEWLINE;
						}
						p++;
					}
					strcpy(info.contact.tel, ptr);
					break;
				case 252:	/*wechat*/
					if(language == CLI_LAN_EN)
					{	
						snprintf(buf, sizeof(buf), "%s", "Wechat(<=32 chars):");
					}
					else
					{
						snprintf(buf, sizeof(buf), "%s", "΢�ź�(<=32 chars):");
					}
			
					memset(ptr, 0, sizeof(ptr));
				        CLI_API_Printf(sid, "\r\n %s", buf);
				      	bc_cli_get_line(sid, sizeof(buf), CLI_OUTPUT_NORMAL, ptr, sizeof(ptr), 60, trigger);
					ptr[strlen(ptr)] = '\0';
			
					if(strlen(ptr) > 32)
					{
						if(language == CLI_LAN_EN)
						{	
							CLI_API_Printf(sid, "\r\n\n Operation failure: the wechat is too long!\r\n");
						}
						else
						{
							CLI_API_Printf(sid, "\r\n\n ����ʧ��:΢�ź�̫��!\r\n");
						}
						
						return CLI_CMD_FAIL_PRT_NEWLINE;
					}
					if(!strlen(ptr))
					{
						if(language == CLI_LAN_EN)
						{	
							CLI_API_Printf(sid, "\r\n\n Operation failure: the wechat is too short!\r\n");
						}
						else
						{
							CLI_API_Printf(sid, "\r\n\n ����ʧ��:΢�ź�̫��!\r\n");
						}
						return CLI_CMD_FAIL_PRT_NEWLINE;
					}
					break;
				case 253:	/*email*/
					if(language == CLI_LAN_EN)
					{	
						snprintf(buf, sizeof(buf), "%s", "E-mail(<=32 chars):");
					}
					else
					{
						snprintf(buf, sizeof(buf), "%s", "��������(<=32 chars):");
					}
			
					memset(ptr, 0, sizeof(ptr));
				        CLI_API_Printf(sid, "\r\n %s", buf);
				      	bc_cli_get_line(sid, sizeof(buf), CLI_OUTPUT_NORMAL, ptr, sizeof(ptr), 60, trigger);
					ptr[strlen(ptr)] = '\0';
					
					if(strlen(ptr) > 32)
					{
						if(language == CLI_LAN_EN)
						{	
							CLI_API_Printf(sid, "\r\n\n Operation failure: the email is too long!\r\n");
						}
						else
						{
							CLI_API_Printf(sid, "\r\n\n ����ʧ��:����̫��!\r\n");
						}
						
						return CLI_CMD_FAIL_PRT_NEWLINE;
					}
					if(!strlen(ptr))
					{
						if(language == CLI_LAN_EN)
						{	
							CLI_API_Printf(sid, "\r\n\n Operation failure: the email is too short!\r\n");
						}
						else
						{
							CLI_API_Printf(sid, "\r\n\n ����ʧ��:����̫��!\r\n");
						}
						return CLI_CMD_FAIL_PRT_NEWLINE;
					}
					strcpy(info.contact.email, ptr);

					break;
				case 254:	/*qq*/
					if(language == CLI_LAN_EN)
					{	
						snprintf(buf, sizeof(buf), "%s", "QQ(<=32 chars):");
					}
					else
					{
						snprintf(buf, sizeof(buf), "%s", "QQ����(<=32 chars):");
					}
					
					memset(ptr, 0, sizeof(ptr));
				        CLI_API_Printf(sid, "\r\n %s", buf);
				      	bc_cli_get_line(sid, sizeof(buf), CLI_OUTPUT_NORMAL, ptr, sizeof(ptr), 60, trigger);
					ptr[strlen(ptr)] = '\0';
			
					if(strlen(ptr) > 11)
					{
						if(language == CLI_LAN_EN)
						{	
							CLI_API_Printf(sid, "\r\n\n Operation failure: the qq is too long!\r\n");
						}
						else
						{
							CLI_API_Printf(sid, "\r\n\n ����ʧ��:QQ̫��!\r\n");
						}
						
						return CLI_CMD_FAIL_PRT_NEWLINE;
					}
					if(!strlen(ptr))
					{
						if(language == CLI_LAN_EN)
						{	
							CLI_API_Printf(sid, "\r\n\n Operation failure: the qq is too short!\r\n");
						}
						else
						{
							CLI_API_Printf(sid, "\r\n\n ����ʧ��:QQ̫��!\r\n");
						}
						return CLI_CMD_FAIL_PRT_NEWLINE;
					}
					strcpy(info.contact.qq, ptr);
					break;
				case 255:	/*job*/
					CLI_API_Printf(sid, "\r\n\n*** not supported warning ***\r\n");
					break;
				case 256:	/*fax*/
					CLI_API_Printf(sid, "\r\n\n*** not supported warning ***\r\n");
					break;
				default:
					if(language == CLI_LAN_EN)
					{	
						CLI_API_Printf(sid, "\r\n\n Operation failure: the command no found!\r\n");
					}
					else
					{
						CLI_API_Printf(sid, "\r\n\n ����ʧ��:����δ�ҵ�!\r\n");
					}
					return CLI_CMD_FAIL_PRT_NEWLINE;
			}
		}
		case 26:		/*duty*/
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n 1.Developer   2.Test   3.Vindicator   4.D&T   5.D&V   6.T&V   7.D&T&V   8.other");
				CLI_API_Printf(sid, "\r\n User's Duty: ");
			}
			else
			{
				CLI_API_Printf(sid, "\r\n 1.�з�   2.����   3.ά��   4.�з������   5.�з���ά��   6.������ά��   7.�з��������ά����   8.����");
				CLI_API_Printf(sid, "\r\n ��Աְ��:");
			}

			setbuf(stdin, NULL);
			fgets(ptr, 256, stdin);
			if(strlen(ptr) != 2)
			{
				if(language == CLI_LAN_EN)
				{	
					CLI_API_Printf(sid, "\r\n Operation failure: duty input error!\r\n");
				}
				else
				{
					CLI_API_Printf(sid, "\r\n ����ʧ��: ְ���������!\r\n");
				}
				return CLI_CMD_FAIL_PRT_NEWLINE;
			}
			ptr[strlen(ptr)-1] = '\0';
			tmp_lvl = ptr[0] - '0';
				
			switch(tmp_lvl)
			{
				case 1:
					info.duty = BC_BINCHIE_DUTY_DEVELOPER;
					break;
				case 2:
					info.duty = BC_BINCHIE_DUTY_TEST;
					break;
				case 3:
					info.duty = BC_BINCHIE_DUTY_VINDICATOR;
					break;
				case 4:
					info.duty = BC_BINCHIE_DUTY_DEVEP_TEST;
					break;
				case 5:
					info.duty = BC_BINCHIE_DUTY_DEVEP_VINDI;
					break;
				case 6:
					info.duty = BC_BINCHIE_DUTY_TEST_VINDI;
					break;
				case 7:
					info.duty = BC_BINCHIE_DUTY_DEVEP_TEST_VINDI;
					break;
				case 8:
					info.duty = BC_BINCHIE_DUTY_OTHER;
					break;
				default:
					if(language == CLI_LAN_EN)
					{	
						CLI_API_Printf(sid, "\r\n Operation failure: duty input error!\r\n");
					}
					else
					{
					CLI_API_Printf(sid, "\r\n ����ʧ��: ְ���������!\r\n");
					}
					return CLI_CMD_FAIL_PRT_NEWLINE;
			}
			break;
		case 27:		/*continue*/
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n 1.Yes   2.No");
				CLI_API_Printf(sid, "\r\n Is on duty?: ");
			}
			else
			{
				CLI_API_Printf(sid, "\r\n 1.��   2.��");
				CLI_API_Printf(sid, "\r\n ��Ա�Ƿ��������ְ��?:");
			}

			setbuf(stdin, NULL);
			fgets(ptr, 256, stdin);
			if(strlen(ptr) != 2)
			{
				if(language == CLI_LAN_EN)
				{	
					CLI_API_Printf(sid, "\r\n Operation failure: duty continued input error!\r\n");
				}
				else
				{
					CLI_API_Printf(sid, "\r\n ����ʧ��: ְ�������������!\r\n");
				}
				return CLI_CMD_FAIL_PRT_NEWLINE;
			}
			ptr[strlen(ptr)-1] = '\0';
			tmp_lvl = ptr[0] - '0';
				
			switch(tmp_lvl)
			{
				case 1:
					info.is_continued = TRUE;
					break;
				case 2:
					info.is_continued = FALSE;
					break;
				default:
					if(language == CLI_LAN_EN)
					{	
						CLI_API_Printf(sid, "\r\n Operation failure: duty continued input error!\r\n");
					}
					else
					{
						CLI_API_Printf(sid, "\r\n ����ʧ��: ְ�������������!\r\n");
					}
					return CLI_CMD_FAIL_PRT_NEWLINE;
			}
			break;
		default:
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n Operation failure: command no found!\r\n");
			}
			else
			{
				CLI_API_Printf(sid, "\r\n ����ʧ��: ����δ�ҵ�!\r\n");
			}
			return CLI_CMD_FAIL_PRT_NEWLINE;
	}

	ret = bc_binchie_set_info(name, info);
	if(ret != BC_ERR_OK)
	{
		if(ret == BC_ERR_BINCHIE_USER_FULL)
		{
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n Operation failure: binchie user full!\r\n");
			}
			else
			{
				CLI_API_Printf(sid, "\r\n ����ʧ��: �û�����!\r\n");
			}
		}
		else if(ret == BC_ERR_BINCHIE_USER_EMPTY)
		{
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n Operation failure: binchie user empty!\r\n");
			}
			else
			{
				CLI_API_Printf(sid, "\r\n ����ʧ��: �û��ѿ�!\r\n");
			}
		}
		else if(ret == BC_ERR_BINCHIE_USER_ALREADY_EXIST)
		{
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n Operation failure: binchie user already exist!\r\n");
			}
			else
			{
				CLI_API_Printf(sid, "\r\n ����ʧ��: �û��Ѵ���!\r\n");
			}
		}
		else if(ret == BC_ERR_BINCHIE_USER_INEXIST)
		{
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n Operation failure: binchie user no exist!\r\n");
			}
			else
			{
				CLI_API_Printf(sid, "\r\n ����ʧ��: �û�������!\r\n");
			}
		}
		else if(ret == BC_ERR_BINCHIE_USER_UNLAWFUL)
		{
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n Operation failure: binchie user unlawful!\r\n");
			}
			else
			{
				CLI_API_Printf(sid, "\r\n ����ʧ��: �Ƿ������з���Ա��Ϣ!\r\n");
			}
		}
		else if(ret == BC_ERR_BINCHIE_USER_DUTY_INVALID)
		{
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n Operation failure: binchie user duty invalid!\r\n");
			}
			else
			{
				CLI_API_Printf(sid, "\r\n ����ʧ��: ��Աְ����Ϊ�з�!\r\n");
			}
		}
		else
		{
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n Operation failure: this binchie user add failure!\r\n");
			}
			else
			{
				CLI_API_Printf(sid, "\r\n ����ʧ��: binchie��Ա���ʧ��!\r\n");
			}
		}
		
	//	CLI_API_Printf(sid, "\r\n Failed to usermgmt register, ret = 0x%x!\r\n", ret);
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	
	if(language == CLI_LAN_EN)
	{	
		CLI_API_Printf(sid, "\r\n This binchie user has been modify success!\r\n");
	}
	else
	{
		CLI_API_Printf(sid, "\r\n binchie��Ա��Ϣ�޸ĳɹ�!\r\n");
	}
#endif
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

static cli_cmd_ret_e __binchie_api_ret_err_pt(IN const UI32_T sid, bc_err_e ret)
{
	cli_lan_t     language = CLI_LAN_MAX;
	
	language = bc_cli_get_lan();
	
	if(ret == BC_ERR_BINCHIE_USER_FULL)
	{
		if(language == CLI_LAN_EN)
		{	
			CLI_API_Printf(sid, "\r\n Operation failure: binchie user full!\r\n");
		}
		else
		{
			CLI_API_Printf(sid, "\r\n ����ʧ��: �û�����!\r\n");
		}
	}
	else if(ret == BC_ERR_BINCHIE_USER_EMPTY)
	{
		if(language == CLI_LAN_EN)
		{	
			CLI_API_Printf(sid, "\r\n Operation failure: binchie user empty!\r\n");
		}
		else
		{
			CLI_API_Printf(sid, "\r\n ����ʧ��: �û��ѿ�!\r\n");
		}
	}
	else if(ret == BC_ERR_BINCHIE_USER_ALREADY_EXIST)
	{
		if(language == CLI_LAN_EN)
		{	
			CLI_API_Printf(sid, "\r\n Operation failure: binchie user already exist!\r\n");
		}
		else
		{
			CLI_API_Printf(sid, "\r\n ����ʧ��: �û��Ѵ���!\r\n");
		}
	}
	else if(ret == BC_ERR_BINCHIE_USER_INEXIST)
	{
		if(language == CLI_LAN_EN)
		{	
			CLI_API_Printf(sid, "\r\n Operation failure: binchie user no exist!\r\n");
		}
		else
		{
			CLI_API_Printf(sid, "\r\n ����ʧ��: �û�������!\r\n");
		}
	}
	else if(ret == BC_ERR_BINCHIE_USER_UNLAWFUL)
	{
		if(language == CLI_LAN_EN)
		{	
			CLI_API_Printf(sid, "\r\n Operation failure: binchie user unlawful!\r\n");
		}
		else
		{
			CLI_API_Printf(sid, "\r\n ����ʧ��: �Ƿ������з���Ա��Ϣ!\r\n");
		}
	}
	else if(ret == BC_ERR_BINCHIE_USER_DUTY_INVALID)
	{
		if(language == CLI_LAN_EN)
		{	
			CLI_API_Printf(sid, "\r\n Operation failure: binchie user duty invalid!\r\n");
		}
		else
		{
			CLI_API_Printf(sid, "\r\n ����ʧ��: ��Աְ����Ϊ�з�!\r\n");
		}
	}
	else
	{
		if(language == CLI_LAN_EN)
		{	
		CLI_API_Printf(sid, "\r\n Operation failure: this binchie user add failure!\r\n");
		}
		else
		{
		CLI_API_Printf(sid, "\r\n ����ʧ��: binchie��Ա���ʧ��!\r\n");
		}
	}
		
	//CLI_API_Printf(sid, "\r\n Failed to usermgmt register, ret = 0x%x!\r\n", ret);
	return CLI_CMD_FAIL_PRT_NEWLINE;
}

/******************************************************************************\
  Function   : __binchie_command
  Description: ע��
  Return     : bool true: �ɹ�  false:����ʧ��
  Others     : 
\******************************************************************************/
static cli_cmd_ret_e __binchie_command
(
	IN const UI32_T	sid,
	IN cli_value_t		*cli_para,
	IN void			*user_data
)
{
	PRT_CLI_PARA(l_mdl_id, cli_para);
	cli_value_t *para_tmp = cli_para;
	
	UI32_T op_id = 0;
	UI32_T val = 0;
	char str[31];
	char *p = NULL;

	bc_err_e ret = BC_ERR_OK;
	bc_binchie_info_t info;	
		
       memset(&info, 0x00, sizeof(bc_binchie_info_t));
	   
       op_id = *(UI32_T *)para_tmp->value;
	BC_PT_DBG_CPL(l_mdl_id, "Cli Para No1: option=%u\r\n", op_id);
	para_tmp = para_tmp->next;

	if(op_id == 1)
	{
		//name
		strcpy(info.name, (bc_char *)para_tmp->value);
		para_tmp = para_tmp->next;

		//sex
		val = *(UI32_T *)para_tmp->value;
		if(val == 0)
			info.sex = BC_BINCHIE_SEX_MAN;
		else if(val == 1)
			info.sex = BC_BINCHIE_SEX_WOMAN;
		else
		{
			CLI_API_Printf(sid, "\r\n\n Operation failure: the sex must be is 0 or 1\r\n");
			return CLI_CMD_FAIL_PRT_NEWLINE;
		}
		para_tmp = para_tmp->next;

		//age
		val = *(UI32_T *)para_tmp->value;
		if(val <15 || val >50)
		{
			CLI_API_Printf(sid, "\r\n\n Operation failure: the age must be is >=15 and <=50\r\n");
			return CLI_CMD_FAIL_PRT_NEWLINE;
		}
		info.age = val;
		para_tmp = para_tmp->next;
		
		//duty
		val = *(UI32_T *)para_tmp->value;
		if(val <0 || val >7)
		{
			CLI_API_Printf(sid, "\r\n\n Operation failure: the duty must be is >=0 and <=7\r\n");
			return CLI_CMD_FAIL_PRT_NEWLINE;
		}
		info.duty = val;
		para_tmp = para_tmp->next;

		//addr
		memset(str, 0x00, sizeof(str));
		strcpy(str, (bc_char *)para_tmp->value);
		p = str;
		while(*p != '\0')
		{
			if((*p>=48&&*p<=57) || (*p>=65&&*p<=90) || (*p>=97&&*p<=122))
			{
			}
			else
			{
				CLI_API_Printf(sid, "\r\n\n Operation failure: the addr invalid\r\n");
				return CLI_CMD_FAIL_PRT_NEWLINE;
			}
			p++;
		}
		strcpy(info.addr, str);
		para_tmp = para_tmp->next;

		//tel
		memset(str, 0x00, sizeof(str));
		strcpy(str, (bc_char *)para_tmp->value);
		if(strlen(str) > 11)
		{
			CLI_API_Printf(sid, "\r\n\n Operation failure: the tel number is too long\r\n");
			return CLI_CMD_FAIL_PRT_NEWLINE;
		}
		p = str;
		while(*p != '\0')
		{
			if(*p>=48&&*p<=57)
			{
			}
			else
			{
				CLI_API_Printf(sid, "\r\n Operation failure: tel number can only be numbers\r\n");
				return CLI_CMD_FAIL_PRT_NEWLINE;
			}
			p++;
		}
		strcpy(info.contact.tel, str);
		para_tmp = para_tmp->next;

		//wechat
		memset(str, 0x00, sizeof(str));
		strcpy(str, (bc_char *)para_tmp->value);
		if(strlen(str) > 32)
		{
			CLI_API_Printf(sid, "\r\n\n Operation failure: the wechat is too long\r\n");
			return CLI_CMD_FAIL_PRT_NEWLINE;
		}
		strcpy(info.contact.wechat, str);
		para_tmp = para_tmp->next;
		
		//qq
		memset(str, 0x00, sizeof(str));
		strcpy(str, (bc_char *)para_tmp->value);
		if(strlen(str) > 10)
		{
			CLI_API_Printf(sid, "\r\n\n Operation failure: the qq number is too long\r\n");
			return CLI_CMD_FAIL_PRT_NEWLINE;
		}
		p = str;
		while(*p != '\0')
		{
			if(*p>=48&&*p<=57)
			{
			}
			else
			{
				CLI_API_Printf(sid, "\r\n Operation failure: qq number can only be numbers\r\n");
				return CLI_CMD_FAIL_PRT_NEWLINE;
			}
			p++;
		}
		strcpy(info.contact.qq, str);
		para_tmp = para_tmp->next;
		
		//email
		memset(str, 0x00, sizeof(str));
		strcpy(str, (bc_char *)para_tmp->value);
		if(strlen(str) > 32)
		{
			CLI_API_Printf(sid, "\r\n\n Operation failure: the email is too long\r\n");
			return CLI_CMD_FAIL_PRT_NEWLINE;
		}
		strcpy(info.contact.wechat, str);
		para_tmp = para_tmp->next;
		
		//on duty status
		val = *(UI32_T *)para_tmp->value;
		if(val == 0)
			info.is_continued = FALSE;
		else if(val == 1)
			info.is_continued = TRUE;
		else
		{
			CLI_API_Printf(sid, "\r\n\n Operation failure: the on-duty-status must be is 0 or 1\r\n");
			return CLI_CMD_FAIL_PRT_NEWLINE;
		}
		para_tmp = para_tmp->next;

		info.is_used = TRUE;
		ret = bc_binchie_add_info(info);
		if(ret != BC_ERR_OK)
		{
			if(ret == BC_ERR_BINCHIE_USER_FULL)
				CLI_API_Printf(sid, "\r\n Operation failure: binchie user full!\r\n");
			else if(ret == BC_ERR_BINCHIE_USER_EMPTY)
				CLI_API_Printf(sid, "\r\n Operation failure: binchie user empty!\r\n");
			else if(ret == BC_ERR_BINCHIE_USER_ALREADY_EXIST)
				CLI_API_Printf(sid, "\r\n Operation failure: binchie user already exist!\r\n");
			else if(ret == BC_ERR_BINCHIE_USER_INEXIST)
				CLI_API_Printf(sid, "\r\n Operation failure: binchie user no exist!\r\n");
			else if(ret == BC_ERR_BINCHIE_USER_UNLAWFUL)
				CLI_API_Printf(sid, "\r\n Operation failure: binchie user unlawful!\r\n");
			else if(ret == BC_ERR_BINCHIE_USER_DUTY_INVALID)
				CLI_API_Printf(sid, "\r\n Operation failure: binchie user duty invalid!\r\n");
			else
				CLI_API_Printf(sid, "\r\n Operation failure: this binchie user add failure!\r\n");
			return CLI_CMD_FAIL_PRT_NEWLINE;
		}
	//	return __binchie_add(sid, ptrCliValue, ptrUserData);
	}
	else if(op_id == 2)
	{
	//	para_tmp = para_tmp->next;	/* to next */
	//	return __binchie_set(sid, para_tmp, user_data);
		CLI_API_Printf(sid, "\r\n*** not supported ***\r\n");
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	else
	{
		CLI_API_Printf(sid, "\r\n command unkown!\r\n");
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}

	CLI_API_Printf(sid, "\r\n Operation failure: this binchie user add successful!\r\n");
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}


/******************************************************************************\
  Function   : __binchie_show_user
  Description:��ʾ�˺���Ϣ
  Return     : bool true: �ɹ�  false:����ʧ��
  Others     : 
\******************************************************************************/
static cli_cmd_ret_e __binchie_show_user
(
	IN const UI32_T	sid,
	IN cli_value_t		*ptrCliValue,
	IN void			*ptrUserData
)
{
	bc_err_e ret = BC_ERR_OK;
	bc_char name[BC_BINCHIE_NAME_LEN_MAX];
	bc_int32 __attribute__ ((unused)) num = 0,i = 0,j=0;
	bc_binchie_info_t info[BC_BINCHIE_USER_NUM_MAX];
	cli_lan_t     language = CLI_LAN_MAX;
	
	cli_value_t *para_tmp = ptrCliValue;
	UI32_T op_id = *(UI32_T *)para_tmp->value;
	para_tmp = para_tmp->next;

	language = bc_cli_get_lan();
	
	if(op_id == 1)
	{
		ret = bc_binchie_get_list(info, &num);
		if(ret != BC_ERR_OK)
		{
			return __binchie_api_ret_err_pt(sid, ret);
		}
	}
	else if(op_id == 2)
	{
		strcpy(name, (bc_char *)para_tmp->value);
		ret = bc_binchie_get_info(name, &info[0]);
		if(ret != BC_ERR_OK)
		{
			return __binchie_api_ret_err_pt(sid, ret);
		}
		num = 1;
	}
	else
	{
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}

	CLI_API_Printf(sid, "\r\n binchie items:[%d]", num);
	CLI_API_Printf(sid, "\r\n --------------------------------------------------------------------");
	for(i=0; i<num; i++)
	{
		if(i != 0)
			CLI_API_Printf(sid, "\r\n -------------");
		
		CLI_API_Printf(sid, "\r\n  %-8s\t%-8d", "Index:", i+1);
		CLI_API_Printf(sid, "\r\n  %-8s\t%-8s", "Name:", info[i].name);
		CLI_API_Printf(sid, "\r\n  %-8s\t%-8s", "Sex:", info[i].sex==BC_BINCHIE_SEX_MAN?"man":"woman");
		CLI_API_Printf(sid, "\r\n  %-8s\t%-8d", "Age:", info[i].age);
		CLI_API_Printf(sid, "\r\n  %-8s\t%-8s", "Addr:", info[i].addr);
		switch(info[i].duty)
		{
				case BC_BINCHIE_DUTY_DEVELOPER:
					CLI_API_Printf(sid, "\r\n  %-8s\t%-15s", "Duty:", "developer");
					break;
				case BC_BINCHIE_DUTY_TEST:
					CLI_API_Printf(sid, "\r\n  %-8s\t%-8s", "Duty:", "test");
					break;
				case BC_BINCHIE_DUTY_VINDICATOR:
					CLI_API_Printf(sid, "\r\n  %-8s\t%-15s", "Duty:", "vindicator");
					break;
				case BC_BINCHIE_DUTY_DEVEP_TEST:
					CLI_API_Printf(sid, "\r\n  %-8s\t%-30s", "Duty:", "developer | test");
					break;
				case BC_BINCHIE_DUTY_DEVEP_VINDI:
					CLI_API_Printf(sid, "\r\n  %-8s\t%-30s", "Duty:", "developer|vindicator");
					break;
				case BC_BINCHIE_DUTY_TEST_VINDI:
					CLI_API_Printf(sid, "\r\n  %-8s\t%-30s", "Duty:", "test|vindicator");
					break;
				case BC_BINCHIE_DUTY_DEVEP_TEST_VINDI:
					CLI_API_Printf(sid, "\r\n  %-8s\t%-30s", "Duty:", "developer|test|vindicator");
					break;
				case BC_BINCHIE_DUTY_OTHER:
					CLI_API_Printf(sid, "\r\n  %-8s\t%-8s", "Duty:", "other");
					break;
				default:
					break;
		}
		CLI_API_Printf(sid, "\r\n  %-8s\t%-15s", "Tel:", info[i].contact.tel);
		CLI_API_Printf(sid, "\r\n  %-8s\t%-15s", "Wechat:", info[i].contact.wechat);
		CLI_API_Printf(sid, "\r\n  %-8s\t%-15s", "QQ:", info[i].contact.qq);
		CLI_API_Printf(sid, "\r\n  %-8s\t%-15s", "Email:", info[i].contact.email);
		CLI_API_Printf(sid, "\r\n  %-8s\t%-15s", "Job:", "------");
		CLI_API_Printf(sid, "\r\n  %-8s\t%-15s", "Fax:", "------");
		CLI_API_Printf(sid, "\r\n  %-8s\t%-8s", "Status:", info[i].is_continued==TRUE?"true":"false");
	}
	CLI_API_Printf(sid, "\r\n --------------------------------------------------------------------\n");
	CLI_DBG_LEAVE(l_mdl_id);
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

#if 1
void bc_cli_cmd_binchie_reg(void)
{
	CLI_DBG_ENTER(l_mdl_id);
	BOOL_T ret_reg;
#if 0	
	/*add*/
	ret_reg = bc_cli_reg_cmd(
		CLI_MOD_PRIVI_PATH
		"/binchie "		 	"#binchie user management#""#binchie��Ա����#"
		"{"
			"add(1) "				"#add a new binchie user #""#���һ������Ա#"
			"|"
			"set(2) "				"#modify a binchie user #""#�޸���Ա��Ϣ#"
			"<username>"		"#binchie user name #""#�û���#"
			"{"
				"name(21) "			"#modify user name #""#�޸���Ա����#"
				"|"
				"age(22) "			"#modify user age #""#�޸���Ա����#"
				"|"
				"sex(23) "			"#modify user sex #""#�޸���Ա�Ա�#"
				"|"
				"addr(24) "			"#modify user addr #""#�޸���Ա��ַ#"
				"|"
				"contact(25) "			"#modify user contact #""#�޸���Ա��ϵ��ʽ#"
				"{"
					"tel(251) "			"#modify user tel #""#�޸���Ա�绰����#"
					"|"
					"wechat(252) "		"#modify user wechat #""#�޸���Ա΢�ź�#"
					"|"
					"email(253) "		"#modify user email #""#�޸���Ա��������#"
					"|"
					"qq(254) "			"#modify user qq #""#�޸���ԱQQ��#"
					"|"
					"job(255) "		"#modify user job #""#�޸���Ա����#"
					"|"
					"fax(256) "		"#modify user fax #""#�޸���Ա����#"
				"}"
				"|"
				"duty(26) "			"#modify user duty #""#�޸���Աְ��#"
				"|"
				"continued(27) "		"#modify user continued #""#�޸���Աְ���Ծ#"
			"}"
		"}",
		__binchie_command,
		CLI_ACC_LVL_BASIC,
		"add binchie user.",
		"���һ��binchie��Ա��",
		NULL);
	CLI_DBG_CPL(l_mdl_id, "ret=%d\r\n", ret_reg);
#else
	/*add*/
	ret_reg = bc_cli_reg_cmd(
		CLI_MOD_PRIVI_PATH
		"/binchie "		 	"#binchie user management#""#binchie��Ա����#"
		"{"
			"add(1) "				"#add a new binchie user #""#���һ������Ա#"
			"{"
				"<username>"		"#user-name #""#�û���#"
				"<value>"			"#user-sex <0:man 1:woman> #""#�Ա�<0:�� 1:Ů>#"
				"<value>"			"#user-age <15-50> #""#����<15-50>#"
				"<value>"			"#user-duty <0:developer 1:test 2:vindicator 3:dev-test 4:dev-vind 5:test-vind 6:dev-test-vind 7:other> #""#ְ��<0:���� 1:���� 2:ά�� 3:���������� 4:������ά�� 5:���Լ�ά�� 6:ȫȨ 7:����>#"
				"<string>"		"#user-address #""#��ַ#"
				"<string>"		"#user-phone-number #""#�ƶ��绰����#"
				"<string>"		"#user-wechat #""#΢�ź�#"
				"<string>"		"#user-QICQ #""#qq��#"
				"<string>"		"#user-E-mail #""#��������#"
				"<value>"		"#user-on-duty <1:continue 0:end> #""#ְ������״̬<1:���� 0:��ֹ> #"
			"}"
			"|"
			"set(2) "				"#modify a binchie user #""#�޸���Ա��Ϣ#"
			"{"
				"<username>"		"#binchie user name #""#�û���#"
				"{"
					"name(21) "			"#modify user name #""#�޸���Ա����#"
					"|"
					"age(22) "			"#modify user age #""#�޸���Ա����#"
					"|"
					"sex(23) "			"#modify user sex #""#�޸���Ա�Ա�#"
					"|"
					"addr(24) "			"#modify user addr #""#�޸���Ա��ַ#"
					"|"
					"contact(25) "			"#modify user contact #""#�޸���Ա��ϵ��ʽ#"
					"{"
						"tel(251) "			"#modify user tel #""#�޸���Ա�绰����#"
						"|"
						"wechat(252) "		"#modify user wechat #""#�޸���Ա΢�ź�#"
						"|"
						"email(253) "		"#modify user email #""#�޸���Ա��������#"
						"|"
						"qq(254) "			"#modify user qq #""#�޸���ԱQQ��#"
						"|"
						"job(255) "		"#modify user job #""#�޸���Ա����#"
						"|"
						"fax(256) "		"#modify user fax #""#�޸���Ա����#"
					"}"
					"|"
					"duty(26) "			"#modify user duty #""#�޸���Աְ��#"
					"|"
					"on-duty-status(27) "		"#modify user continued #""#�޸���Աְ���Ծ#"
				"}"
			"}"
		"}",
		__binchie_command,
		CLI_ACC_LVL_BASIC,
		"add or modity binchie user.",
		"���/ �޸�һ��binchie��Ա��",
		NULL);
	CLI_DBG_CPL(l_mdl_id, "ret=%d\r\n", ret_reg);
#endif
	
	/*delete*/
	ret_reg = bc_cli_reg_cmd(
		CLI_MOD_PRIVI_PATH
		"/no "		 	"##""##"
		"binchie "          "#del a exist binchie user #""#ɾ��һ���Ѵ��ڵ���Ա#"
		"<username>"		"#binchie user name #""#�û���#",
		__binchie_del,
		CLI_ACC_LVL_BASIC,
		"del binchie user.",
		"ɾ��һ��binchie ��Ա��",
		NULL);
	CLI_DBG_CPL(l_mdl_id, "ret=%d\r\n", ret_reg);

	/*show*/
	ret_reg = bc_cli_reg_cmd(
		CLI_MOD_PRIVI_PATH
		"/show "		 	"##""##"
		"binchie "		"#binchie information #""#binchie��Ա��Ϣ#"
		"{"
			"all(1) " 			"#user list#""#�����û�#"
			"|"
			"username(2) "		"#user name #""#�û���#"
				"<username>"		"#user name #""#�û���#"
		"}",
		__binchie_show_user,
		CLI_ACC_LVL_BASIC,
		"show.",
		"��ʾbinchie��Ϣ��",
		NULL);
	CLI_DBG_CPL(l_mdl_id, "ret=%d\r\n", ret_reg);
}



/* 
 *	Ԥ��һ��ע�����ļ����
 */
/******************************************************************************\
  Function   : 
  Description: 
  Return     : 
  Others     : 
\******************************************************************************/

#endif



