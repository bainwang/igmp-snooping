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
	2016-09-05  Created									bain.wang@outlook.com
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								头   文   件								  //
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
#include "bc_usermgmt_def.h"
#include "bc_usermgmt.h"

#include "utili_bit.h"
static unsigned int 	l_mdl_id = BC_MODULE_USERMGMT;

////////////////////////////////////////////////////////////////////////////////
//																			  //
//						外 部 变 量、 函 数 引 用					          //
//																			  //
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//																			  //
//						结   构   体   宏   定   义							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
/*
 *		当源文件需要定义宏，而头文件又与其它模块头文件中的宏定义有重复定义嫌疑
 *	时，在此处定义。
 */

#define ECHOFLAGS (ECHO | ECHOE | ECHOK | ECHONL)  
////////////////////////////////////////////////////////////////////////////////
//																			  //
//							全 局 变 量 定 义							      //
//																			  //
////////////////////////////////////////////////////////////////////////////////
/* 
 *	外部全局变量，提供整个工程调用，在头文件中提供调用接口(外部引用声明)。
 */

/* 
 *	内部全局变量，只提供给该文件内部函数调用，不在头文件中提供调用接口。
 */


////////////////////////////////////////////////////////////////////////////////
//																			  //
//								函  数  声  明							      //
//																			  //
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//																			  //
//								函  数  定  义							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

/******************************************************************************\
  Function   : 
  Description:
  Return     : bool true: 成功  false:非零失败
  Others     : 
\******************************************************************************/
int __usermgmt_set_disp_mode
(
	int fd,
	int enable
)  
{  
	int retval;  
	struct termios term;  
	
	if(tcgetattr(fd,&term) == -1)
	{  
		perror("Cannot get the attribution of the terminal");  
		return FALSE;  
	}  
	
	if(enable == TRUE)  
		term.c_lflag |= ECHOFLAGS;  
	else  
		term.c_lflag &= ~ECHOFLAGS;  
	
	retval=tcsetattr(fd,TCSAFLUSH,&term); 
	if(retval == -1 && retval == EINTR)
	{  
		perror("Cannot set the attribution of the terminal");  
		return FALSE;  
	}  
   	return TRUE;  
}  

/******************************************************************************\
  Function   : 
  Description:
  Return     : bool true: 成功  false:非零失败
  Others     : 
\******************************************************************************/
int __usermgmt_get_pwd(char *passwd, int size)  
{  
	int c;
	int n = 0;

	if(!passwd)
		return FALSE;
	
	do{  
		c=getchar();  
		if ((c != '\n') | (c != '\r'))
		{  
			passwd[n++] = c;  
		}  
	}while(c != '\n' && c !='\r' && n < (size));  
	passwd[n] = '\0';  
	
	return TRUE;  
} 


#if 0
//test
void __usermgmt_pt_test(const UI32_T sid, bc_usermgmt_info_t usermgmt_info)
{
	int i = 0;
	
	CLI_API_Printf(sid, "\r\n name: %s", usermgmt_info.name);
	CLI_API_Printf(sid, "\r\n pwd: %s", usermgmt_info.pwd);
	CLI_API_Printf(sid, "\r\n encrypt_enable: %d", usermgmt_info.encrypt_enable);
	CLI_API_Printf(sid, "\r\n encrypt_pwd: %s", usermgmt_info.encrypt_pwd);
	CLI_API_Printf(sid, "\r\n level: %d", usermgmt_info.level);
	CLI_API_Printf(sid, "\r\n links: %d", usermgmt_info.links);
	CLI_API_Printf(sid, "\r\n state: %d", usermgmt_info.state);
	CLI_API_Printf(sid, "\r\n login_tm: %s", "null");
	CLI_API_Printf(sid, "\r\n logout_tm: %s", "null");
	CLI_API_Printf(sid, "\r\n --------------------------------------------------------");
	
	for(i=0; i<usermgmt_info.links; i++)
	{
		CLI_API_Printf(sid, "\r\n sid: %d", usermgmt_info.line_info[i].sid);
		CLI_API_Printf(sid, "\r\n state: %d", usermgmt_info.line_info[i].state);
	}
	CLI_API_Printf(sid, "\r\n");
}
#endif


/******************************************************************************\
  Function   : __usermgmt_register
  Description: 注册
  Return     : bool true: 成功  false:非零失败
  Others     : 
\******************************************************************************/
#include "bc_cli_vkey.h"
static cli_cmd_ret_e __usermgmt_register
(
	IN const UI32_T	sid,
	IN cli_value_t		*ptrCliValue,
	IN void			*ptrUserData
)
{
	bc_err_e ret = BC_ERR_OK;
	bc_usermgmt_info_t usermgmt_info;	
	char ptr[BC_USERMGMT_NAME_LEN];
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
	
	memset(&usermgmt_info, 0, sizeof(usermgmt_info));

#if 0
	/*name*/
	if(language == CLI_LAN_EN)
	{	
		CLI_API_Printf(sid, "\r\n New Username(<=15 chars):");
	}
	else
	{
		CLI_API_Printf(sid, "\r\n 新用户名(<=15 chars):");
	}*/
	
	setbuf(stdin, NULL);
	fgets(ptr, BC_USERMGMT_NAME_LEN-2, stdin);
	if(strlen(ptr) > 16) //15 + '\n'
	{
		CLI_API_Printf(sid, "\r\n Operation failure: the username is too long!\r\n");
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	p = ptr;
	while(*p != '\n')
	{
		if((*p>=48&&*p<=57) || (*p>=65&&*p<=90) || (*p>=97&&*p<=122))
		{
		}
		else
		{
			CLI_API_Printf(sid, "\r\n Operation failure: the username must be mixed by lowercase and uppercase and number.\r\n");
			return CLI_CMD_FAIL_PRT_NEWLINE;
		}
		p++;
	}
	strcpy(usermgmt_info.name, ptr);
	usermgmt_info.name[strlen(usermgmt_info.name)-1] = '\0';
	
	/*passwd*/
	memset(ptr, 0, sizeof(ptr));
	
	if(language == CLI_LAN_EN)
	{	
		CLI_API_Printf(sid, " New Password(<=15 chars):");
	}
	else
	{
		CLI_API_Printf(sid, " 新密码(<=15 chars):");
	}

	__usermgmt_set_disp_mode(STDIN_FILENO, FALSE);
	if(__usermgmt_get_pwd(ptr, BC_USERMGMT_NAME_LEN-2) != TRUE)
	{
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	if(strlen(ptr) > 16) //15 + '\n'
	{
		__usermgmt_set_disp_mode(STDIN_FILENO, TRUE);
		CLI_API_Printf(sid, "\r\n\n Operation failure: the password is too long!\r\n");
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	p = ptr;
	if(*p == '\n')
	{
		CLI_API_Printf(sid, "\r\n\n Operation failure: the password is too short!\r\n");
	}
	while(*p != '\n')
	{
		/*The first char must be lowercase or uppercase.*/
		if(!cnt)
		{
			if((*p>=65&&*p<=90) || (*p>=97&&*p<=122))
			{
			}
			else
			{
				__usermgmt_set_disp_mode(STDIN_FILENO, TRUE);
				CLI_API_Printf(sid, "\r\n\n Operation failure: the first char must be lowercase or uppercase.\r\n");
				return CLI_CMD_FAIL_PRT_NEWLINE;
			}
		}
		/*With the exception of the first char, the string was mixed by lowercase and uppercase and number.*/
		else	
		{
			if((*p>=48&&*p<=57) || (*p>=65&&*p<=90) || (*p>=97&&*p<=122))
			{
			}
			else
			{
				__usermgmt_set_disp_mode(STDIN_FILENO, TRUE);
				CLI_API_Printf(sid, "\r\n Operation failure: with the exception of the first char, the string was mixed by lowercase and uppercase and number.");
				return CLI_CMD_FAIL_PRT_NEWLINE;
			}	
		}
		cnt++;
		p++;
	}
	*p = '\0';
	__usermgmt_set_disp_mode(STDIN_FILENO, TRUE);
	strcpy(usermgmt_info.pwd, ptr);

#else
	/*username*/
	if(language == CLI_LAN_EN)
	{	
		snprintf(buf, sizeof(buf), "%s", "New Username(<=15 chars):");
	}
	else
	{
		snprintf(buf, sizeof(buf), "%s", "新用户名(<=15 chars):");
	}
	
	memset(ptr, 0, sizeof(ptr));
        CLI_API_Printf(sid, "\r\n %s", buf);
      	bc_cli_get_line(sid, sizeof(buf), CLI_OUTPUT_NORMAL, ptr, sizeof(ptr), 60, trigger);
	ptr[strlen(ptr)] = '\0';
	
	if(strlen(ptr) > 15)
	{
		if(language == CLI_LAN_EN)
		{	
			CLI_API_Printf(sid, "\r\n\n Operation failure: the username is too long!\r\n");
		}
		else
		{
			CLI_API_Printf(sid, "\r\n\n 操作失败:用户名太长!\r\n");
		}
		
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	if(!strlen(ptr))
	{
		if(language == CLI_LAN_EN)
		{	
			CLI_API_Printf(sid, "\r\n\n Operation failure: the username is too short!\r\n");
		}
		else
		{
			CLI_API_Printf(sid, "\r\n\n 操作失败: 用户名太短!\r\n");
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
				CLI_API_Printf(sid, "\r\n Operation failure: user name can only be letters or numbers.\r\n");
			}
			else
			{
				CLI_API_Printf(sid, "\r\n\n 操作失败: 用户名只能为字母或数字!\r\n");
			}
			return CLI_CMD_FAIL_PRT_NEWLINE;
		}
		p++;
	}
	strcpy(usermgmt_info.name, ptr);
	
	/*password*/
	memset(buf, 0, sizeof(buf));
	if(language == CLI_LAN_EN)
	{	
		snprintf(buf, sizeof(buf), "%s", "New Password(<=15 chars):");
	}
	else
	{
		snprintf(buf, sizeof(buf), "%s", "新密码(<=15 chars):");
	}
	
	memset(ptr, 0, sizeof(ptr));
        CLI_API_Printf(sid, "\r\n %s", buf);
        bc_cli_get_line(sid, sizeof(buf), CLI_OUTPUT_PASSWORD, ptr, sizeof(ptr), 60, trigger);
	ptr[strlen(ptr)] = '\0';
	
	if(strlen(ptr) > 15)
	{
		if(language == CLI_LAN_EN)
		{	
			CLI_API_Printf(sid, "\r\n\n Operation failure: the password is too long!\r\n");
		}
		else
		{
			CLI_API_Printf(sid, "\r\n\n 操作失败: 密码太长!\r\n");
		}
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	if(!strlen(ptr))
	{
		if(language == CLI_LAN_EN)
		{	
			CLI_API_Printf(sid, "\r\n\n Operation failure: the password is too short!\r\n");
		}
		else
		{
			CLI_API_Printf(sid, "\r\n\n 操作失败:密码太短!\r\n");
		}
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	p = ptr;
	while(*p != '\0')
	{
		/*The first char must be lowercase or uppercase.*/
		if(!cnt)
		{
			if((*p>=65&&*p<=90) || (*p>=97&&*p<=122))
			{
			//	printf("1-%c\n", *p);
			}
			else
			{
			//	printf("2-%c\n", *p);
				if(language == CLI_LAN_EN)
				{	
					CLI_API_Printf(sid, "\r\n\n Operation failure: the first character can only be a letter.\r\n");
				}
				else
				{
					CLI_API_Printf(sid, "\r\n\n 操作失败: 首字符只能为字母!\r\n");
				}
				return CLI_CMD_FAIL_PRT_NEWLINE;
			}
		}
		/*With the exception of the first char, the string was mixed by lowercase and uppercase and number.*/
		else	
		{
			if((*p>=48&&*p<=57) || (*p>=65&&*p<=90) || (*p>=97&&*p<=122))
			{
				
			}
			else
			{
				if(language == CLI_LAN_EN)
				{	
					CLI_API_Printf(sid, "\r\n Operation failure: with the exception of the first character, the user name can only be letters or numbers.");
				}
				else
				{
					CLI_API_Printf(sid, "\r\n 操作失败:密码只能为字母或数字!");
				}
				return CLI_CMD_FAIL_PRT_NEWLINE;
			}
		}
		cnt++;
		p++;
	}
	*p = '\0';
	strcpy(usermgmt_info.pwd, ptr);
	
#endif

	/*level*/
	if(language == CLI_LAN_EN)
	{	
		CLI_API_Printf(sid, "\r\n 1.Basic   2.Privi   3.User   4.Puser   5.Admin   6.Factory   7.Debug");
		CLI_API_Printf(sid, "\r\n User's Level: ");
	}
	else
	{
		CLI_API_Printf(sid, "\r\n 1.Basic   2.Privi   3.User   4.Puser   5.Admin   6.Factory   7.Debug");
		CLI_API_Printf(sid, "\r\n 用户权限:");
	}

	setbuf(stdin, NULL);
	fgets(ptr, 256, stdin);
	if(strlen(ptr) != 2)
	{
		if(language == CLI_LAN_EN)
		{	
			CLI_API_Printf(sid, "\r\n Operation failure: level error!\r\n");
		}
		else
		{
			CLI_API_Printf(sid, "\r\n 操作失败: 权限输入错误!\r\n");
		}
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	ptr[strlen(ptr)-1] = '\0';
	tmp_lvl = ptr[0] - '0';
		
	switch(tmp_lvl)
	{
		case 1:
			usermgmt_info.level = BC_USERMGMT_LVL_BASIC;
			break;
		case 2:
			usermgmt_info.level = BC_USERMGMT_LVL_PRIVI;
			break;
		case 3:
			usermgmt_info.level = BC_USERMGMT_LVL_USER;
			break;
		case 4:
			usermgmt_info.level = BC_USERMGMT_LVL_PUSER;
			break;
		case 5:
			usermgmt_info.level = BC_USERMGMT_LVL_ADMIN;
			break;
		case 6:
			usermgmt_info.level = BC_USERMGMT_LVL_FACTORY;
			break;
		case 7:
			usermgmt_info.level = BC_USERMGMT_LVL_DEBUG;
			break;
		default:
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n Operation failure: level error!\r\n");
			}
			else
			{
			CLI_API_Printf(sid, "\r\n 操作失败: 权限输入错误!\r\n");
			}
			return CLI_CMD_FAIL_PRT_NEWLINE;
	}	
//	__usermgmt_pt_test(sid, usermgmt_info);	//test pt
	
	ret = bc_usermgmt_register(&usermgmt_info);
	if(ret != BC_ERR_OK)
	{
		if(ret == BC_ERR_USERMGMT_REPEAT_REG)
		{
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n Operation failure: this user already exists!\r\n");
			}
			else
			{
				CLI_API_Printf(sid, "\r\n 操作失败: 用户已经存在!\r\n");
			}
		}
		else if(ret == BC_ERR_USERMGMT_LVL_ERR)
		{
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n Operation failure: current user's level is too low!\r\n");
			}
			else
			{
				CLI_API_Printf(sid, "\r\n 操作失败: 当前用户的权限太低!\r\n");
			}
		}
		else if(ret == BC_ERR_USERMGMT_USER_NUM_MAX)
		{
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n Operation failure: user number is full!\r\n");
			}
			else
			{
				CLI_API_Printf(sid, "\r\n 操作失败: 用户数已达最大值!\r\n");
			}
		}
		else
		{
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n Operation failure: this user registers failure!\r\n");
			}
			else
			{
				CLI_API_Printf(sid, "\r\n 操作失败: 用户注册失败!\r\n");
			}
		}
		
	//	CLI_API_Printf(sid, "\r\n Failed to usermgmt register, ret = 0x%x!\r\n", ret);
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	
	if(language == CLI_LAN_EN)
	{	
		CLI_API_Printf(sid, "\r\n This user has been register success!\r\n");
	}
	else
	{
		CLI_API_Printf(sid, "\r\n 用户注册成功!\r\n");
	}
	
	CLI_DBG_LEAVE(l_mdl_id);
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

/******************************************************************************\
  Function   : __usermgmt_unregister
  Description: 注销
  Return     : bool true: 成功  false:非零失败
  Others     : 
\******************************************************************************/
static cli_cmd_ret_e __usermgmt_unregister 
(
	IN const UI32_T	sid,
	IN cli_value_t		*ptrCliValue,
	IN void			*ptrUserData
)
{
	bc_err_e ret = BC_ERR_OK;
	char			pUsrPrompt[256];
	cli_value_t *para_tmp = ptrCliValue;
	bc_char name[BC_USERMGMT_NAME_LEN];
	cli_lan_t     language = CLI_LAN_MAX;

	language = bc_cli_get_lan();
	strcpy(name, (bc_char *)para_tmp->value);

	if(language == CLI_LAN_EN)
	{	
		CLI_API_Printf(sid, "\r\n Are you sure to delete the user?(y/n)\r\n");
	}
	else
	{
		CLI_API_Printf(sid, "\r\n 确认注销这个用户?(y/n)\r\n");
	}
	
	setbuf(stdin, NULL);
	fgets(pUsrPrompt, 256, stdin);
	
//	CLI_API_Printf(sid, "%c\r\n", pUsrPrompt[0]);
	if ((pUsrPrompt[0] != 'y') && (pUsrPrompt[0] != 'Y'))
	{
		setbuf(stdin, NULL);
		return CLI_CMD_SUCCESS_PRT_NEWLINE;
	}
	
	ret = bc_usermgmt_unregister(name);
	if(ret != BC_ERR_OK)
	{
		if(ret == BC_ERR_USERMGMT_NO_EXIST)
		{
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n Operation failure: this user does not exist!\r\n");
			}
			else
			{
				CLI_API_Printf(sid, "\r\n 操作失败: 此用户不存在!\r\n");
			}
		}
		else if(ret == BC_ERR_USERMGMT_UNREG_ERR)
		{
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n Operation failure: this user is online!\r\n");
			}
			else
			{
				CLI_API_Printf(sid, "\r\n 操作失败:不能注销在线用户!\r\n");
			}
		}
		else if(ret == BC_ERR_USERMGMT_LVL_ERR)
		{
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n Operation failure: current user's level is too low!\r\n");
			}
			else
			{
				CLI_API_Printf(sid, "\r\n 操作失败: 当前用户的权限太低!\r\n");
			}
		}
		else
		{
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n Operation failure: This user has been deleted failure!\r\n");
			}
			else
			{
				CLI_API_Printf(sid, "\r\n 操作失败: 用户注销失败!\r\n");
			}
		}
	//	CLI_API_Printf(sid, "\r\n Failed to usermgmt unregister, ret = 0x%x!\r\n", ret);
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	if(language == CLI_LAN_EN)
	{	
	
		CLI_API_Printf(sid, "\r\n This user has been deleted success!\r\n");
	}
	else
	{
		CLI_API_Printf(sid, "\r\n 用户注销成功!\r\n");
	}
	
	CLI_DBG_LEAVE(l_mdl_id);
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

/******************************************************************************\
  Function   : __usermgmt_set_pwd
  Description: 设置密码
  Return     : bool true: 成功  false:非零失败
  Others     : 
\******************************************************************************/
static cli_cmd_ret_e __usermgmt_set_pwd
(
	IN const UI32_T	sid,
	IN cli_value_t		*ptrCliValue,
	IN void			*ptrUserData
)
{
	bc_err_e ret = BC_ERR_OK;
	char ptr1[BC_USERMGMT_NAME_LEN];
	char ptr2[BC_USERMGMT_NAME_LEN];
	char *p = NULL, *p1 = NULL;
	cli_value_t *para_tmp = ptrCliValue;
	bc_char name[BC_USERMGMT_NAME_LEN];
	bc_char pwd[BC_USERMGMT_NAME_LEN];
	bc_usermgmt_info_t usermgmt_info;
	bc_int32 cnt = 0;
	cli_lan_t     language = CLI_LAN_MAX;
	char buf[255];
	I32_T   trigger[]   =
	{
		CLI_VKEY_CTRL_ENTER, CLI_VKEY_CR, 0
	};
	
	CLI_DBG_ENTER(l_mdl_id);
	language = bc_cli_get_lan();
	
	if(para_tmp == NULL)
	{
		bc_usermgmt_get_line_info(&usermgmt_info);
		strcpy(name, usermgmt_info.name);
	}
	else
	{
		strcpy(name, (bc_char *)para_tmp->value);
	}

#if 1
	/*password*/
	memset(buf, 0, sizeof(buf));
	if(language == CLI_LAN_EN)
	{	
		snprintf(buf, sizeof(buf), "%s", "New Password(<=15 chars):");
	}
	else
	{
		snprintf(buf, sizeof(buf), "%s", "新密码(<=15 chars):");
	}
	
	memset(ptr1, 0, sizeof(ptr1));
        CLI_API_Printf(sid, "\r\n %s", buf);
        bc_cli_get_line(sid, sizeof(buf), CLI_OUTPUT_PASSWORD, ptr1, sizeof(ptr1), 60, trigger);
	ptr1[strlen(ptr1)] = '\0';
	
	if(strlen(ptr1) > 15)
	{
		if(language == CLI_LAN_EN)
		{	
			CLI_API_Printf(sid, "\r\n\n Operation failure: the password is too long!\r\n");
		}
		else
		{
			CLI_API_Printf(sid, "\r\n\n 操作失败: 密码太长!\r\n");
		}
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	if(!strlen(ptr1))
	{
		if(language == CLI_LAN_EN)
		{	
			CLI_API_Printf(sid, "\r\n\n Operation failure: the password is too short!\r\n");
		}
		else
		{
			CLI_API_Printf(sid, "\r\n\n 操作失败:密码太短!\r\n");
		}
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	p = ptr1;
	while(*p != '\0')
	{
		/*The first char must be lowercase or uppercase.*/
		if(!cnt)
		{
			if((*p>=65&&*p<=90) || (*p>=97&&*p<=122))
			{
			//	printf("1-%c\n", *p);
			}
			else
			{
			//	printf("2-%c\n", *p);
				if(language == CLI_LAN_EN)
				{	
					CLI_API_Printf(sid, "\r\n\n Operation failure: the first character can only be a letter.\r\n");
				}
				else
				{
					CLI_API_Printf(sid, "\r\n\n 操作失败: 首字符只能为字母!\r\n");
				}
				return CLI_CMD_FAIL_PRT_NEWLINE;
			}
		}
		/*With the exception of the first char, the string was mixed by lowercase and uppercase and number.*/
		else	
		{
			if((*p>=48&&*p<=57) || (*p>=65&&*p<=90) || (*p>=97&&*p<=122))
			{
				
			}
			else
			{
				if(language == CLI_LAN_EN)
				{	
					CLI_API_Printf(sid, "\r\n Operation failure: with the exception of the first character, the user name can only be letters or numbers.");
				}
				else
				{
					CLI_API_Printf(sid, "\r\n 操作失败:密码只能为字母或数字!");
				}
				return CLI_CMD_FAIL_PRT_NEWLINE;
			}
		}
		cnt++;
		p++;
	}
	*p = '\0';

	//repeat password
	memset(buf, 0, sizeof(buf));
	if(language == CLI_LAN_EN)
	{	
		snprintf(buf, sizeof(buf), "%s", "Confirm password(<=15 chars):");
	}
	else
	{
		snprintf(buf, sizeof(buf), "%s", "确认新密码(<=15 chars):");
	}
	
	memset(ptr2, 0, sizeof(ptr2));
        CLI_API_Printf(sid, "\r\n %s", buf);
        bc_cli_get_line(sid, sizeof(buf), CLI_OUTPUT_PASSWORD, ptr2, sizeof(ptr2), 60, trigger);
	ptr2[strlen(ptr2)] = '\0';
	
	if(strlen(ptr2) > 15)
	{
		if(language == CLI_LAN_EN)
		{	
			CLI_API_Printf(sid, "\r\n\n Operation failure: the password is too long!\r\n");
		}
		else
		{
			CLI_API_Printf(sid, "\r\n\n 操作失败: 密码太长!\r\n");
		}
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	if(!strlen(ptr2))
	{
		if(language == CLI_LAN_EN)
		{	
			CLI_API_Printf(sid, "\r\n\n Operation failure: the password is too short!\r\n");
		}
		else
		{
			CLI_API_Printf(sid, "\r\n\n 操作失败:密码太短!\r\n");
		}
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	p1 = ptr2;
	while(*p1 != '\0')
	{
		/*The first char must be lowercase or uppercase.*/
		if(!cnt)
		{
			if((*p1>=65&&*p1<=90) || (*p1>=97&&*p1<=122))
			{
			//	printf("1-%c\n", *p);
			}
			else
			{
			//	printf("2-%c\n", *p);
				if(language == CLI_LAN_EN)
				{	
					CLI_API_Printf(sid, "\r\n\n Operation failure: the first character can only be a letter.\r\n");
				}
				else
				{
					CLI_API_Printf(sid, "\r\n\n 操作失败: 首字符只能为字母!\r\n");
				}
				return CLI_CMD_FAIL_PRT_NEWLINE;
			}
		}
		/*With the exception of the first char, the string was mixed by lowercase and uppercase and number.*/
		else	
		{
			if((*p1>=48&&*p1<=57) || (*p1>=65&&*p1<=90) || (*p1>=97&&*p1<=122))
			{
				
			}
			else
			{
				if(language == CLI_LAN_EN)
				{	
					CLI_API_Printf(sid, "\r\n Operation failure: with the exception of the first character, the user name can only be letters or numbers.");
				}
				else
				{
					CLI_API_Printf(sid, "\r\n 操作失败:密码只能为字母或数字!");
				}
				return CLI_CMD_FAIL_PRT_NEWLINE;
			}
		}
		cnt++;
		p1++;
	}
	*p1 = '\0';
#endif	
	if(strcmp(ptr1, ptr2) != 0)
	{
		if(language == CLI_LAN_EN)
		{	
			CLI_API_Printf(sid, "\r\n Operation failure: passowrd error!\r\n");
		}
		else
		{
			CLI_API_Printf(sid, "\r\n 操作失败: 两次输入的密码不一致!\r\n");
		}
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	
	strcpy(pwd, ptr1);

	ret = bc_usermgmt_set_password(name, pwd);
	if(ret != BC_ERR_OK)
	{
		if(language == CLI_LAN_EN)
		{	
			if(ret == BC_ERR_USERMGMT_NO_EXIST)
			{
				CLI_API_Printf(sid, "\r\n Operation failure: [%s] is not exist!\r\n", name);
			}
			else if(ret == BC_ERR_USERMGMT_LVL_ERR)
			{
				CLI_API_Printf(sid, "\r\n Operation failure: current user's level is too low!\r\n");
			}
			else if(ret == BC_ERR_USERMGMT_DEFAULT_USER)
			{
				CLI_API_Printf(sid, "\r\n Operation failure: [%s] is system user!\r\n", name);
			}
			else
			{
				CLI_API_Printf(sid, "\r\n This user's password has been set failure!\r\n");
			}
		}
		else
		{
			if(ret == BC_ERR_USERMGMT_NO_EXIST)
			{
				CLI_API_Printf(sid, "\r\n 操作失败: [%s] 不存在t!\r\n", name);
			}
			else if(ret == BC_ERR_USERMGMT_LVL_ERR)
			{
				CLI_API_Printf(sid, "\r\n 操作失败: 当前用户的权限太低!\r\n");
			}
			else if(ret == BC_ERR_USERMGMT_DEFAULT_USER)
			{
				CLI_API_Printf(sid, "\r\n 操作失败: [%s] 是系统保留用户!\r\n", name);
			}
			else
			{
				CLI_API_Printf(sid, "\r\n 操作失败: 用户密码修改失败!\r\n");
			}
		}
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	if(language == CLI_LAN_EN)
	{	
		CLI_API_Printf(sid, "\r\n This user's password has been set successfully!\r\n");
	}
	else
	{
		CLI_API_Printf(sid, "\r\n  密码修改成功!\r\n");
	}
	
	CLI_DBG_LEAVE(l_mdl_id);
	
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

/******************************************************************************\
  Function   : __usermgmt_set_lvl
  Description:设置权限
  Return     : bool true: 成功  false:非零失败
  Others     : 
\******************************************************************************/
static cli_cmd_ret_e __usermgmt_set_lvl
(
	IN const UI32_T	sid,
	IN cli_value_t		*ptrCliValue,
	IN void			*ptrUserData
)
{
	bc_err_e ret = BC_ERR_OK;
	char			pUsrPrompt[256];
	cli_value_t *para_tmp = ptrCliValue;
	bc_char name[BC_USERMGMT_NAME_LEN];
	bc_usermgmt_level_e level;
	bc_usermgmt_info_t usermgmt_info;
	int tmp_lvl = 0;
	cli_lan_t     language = CLI_LAN_MAX;
	bc_boolean cur_user = FALSE;
	
	CLI_DBG_ENTER(l_mdl_id);
	language = bc_cli_get_lan();
	
	if(para_tmp == NULL)
	{
		bc_usermgmt_get_line_info(&usermgmt_info);
		strcpy(name, usermgmt_info.name);
		cur_user = TRUE;
	}
	else
	{
		strcpy(name, (bc_char *)para_tmp->value);
		cur_user = FALSE;
	}
	/*
	BC_USERMGMT_LVL_BASIC = 1,
	BC_USERMGMT_LVL_PRIVI,
	BC_USERMGMT_LVL_USER,
	BC_USERMGMT_LVL_PUSER,
	BC_USERMGMT_LVL_ADMIN,
	BC_USERMGMT_LVL_FACTORY,
	BC_USERMGMT_LVL_DEBUG = 128,
	*/
	if(language == CLI_LAN_EN)
	{	
		CLI_API_Printf(sid, "\r\n 1.	Basic   2.Privi   3.User   4.Puser   5.Admin   6.Factory   7.Debug");
		CLI_API_Printf(sid, "\r\n User's Level: ");
	}
	else
	{
		CLI_API_Printf(sid, "\r\n 1.	Basic   2.Privi   3.User   4.Puser   5.Admin   6.Factory   7.Debug");
		CLI_API_Printf(sid, "\r\n 用户权限: ");
	}

	setbuf(stdin, NULL);
	fgets(pUsrPrompt, 256, stdin);	pUsrPrompt[strlen(pUsrPrompt)-1] = '\0';
	tmp_lvl = pUsrPrompt[0] - '0';
		
	switch(tmp_lvl)
	{
		case 1:
			level = BC_USERMGMT_LVL_BASIC;
			break;
		case 2:
			level = BC_USERMGMT_LVL_PRIVI;
			break;
		case 3:
			level = BC_USERMGMT_LVL_USER;
			break;
		case 4:
			level = BC_USERMGMT_LVL_PUSER;
			break;
		case 5:
			level = BC_USERMGMT_LVL_ADMIN;
			break;
		case 6:
			level = BC_USERMGMT_LVL_FACTORY;
			break;
		case 7:
			level = BC_USERMGMT_LVL_DEBUG;
			break;
		default:
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n Operation failure: wrong choice!\r\n");
			}
			else
			{
				CLI_API_Printf(sid, "\r\n 操作失败: 权限输入错误!\r\n");
			}
			return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	
	ret = bc_usermgmt_set_level(name, level);
	if(ret != BC_ERR_OK)
	{
		if(language == CLI_LAN_EN)
		{	
			if(ret == BC_ERR_USERMGMT_NO_EXIST)
			{
				CLI_API_Printf(sid, "\r\n Operation failure: [%s] is not exist!\r\n", name);
			}
			else if(ret == BC_ERR_USERMGMT_LVL_ERR)
			{
				CLI_API_Printf(sid, "\r\n Operation failure: current user's level is too low!\r\n");
			}
			else if(ret == BC_ERR_USERMGMT_DEFAULT_USER)
			{
				CLI_API_Printf(sid, "\r\n Operation failure: [%s] is system user!\r\n", name);
			}
			else
			{
				CLI_API_Printf(sid, "\r\n This user's level has been set failure!\r\n");
			}
		}
		else
		{
			if(ret == BC_ERR_USERMGMT_NO_EXIST)
			{
				CLI_API_Printf(sid, "\r\n 操作失败: [%s] 不存在t!\r\n", name);
			}
			else if(ret == BC_ERR_USERMGMT_LVL_ERR)
			{
				CLI_API_Printf(sid, "\r\n 操作失败: 当前用户的权限太低!\r\n");
			}
			else if(ret == BC_ERR_USERMGMT_DEFAULT_USER)
			{
				CLI_API_Printf(sid, "\r\n 操作失败: [%s] 是系统保留用户!\r\n", name);
			}
			else
			{
				CLI_API_Printf(sid, "\r\n 操作失败: 用户权限修改失败!\r\n");
			}
		}
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	if(language == CLI_LAN_EN)
	{	
		CLI_API_Printf(sid, "\r\n This user's level has been set successfully!\r\n");
	}
	else
	{
		CLI_API_Printf(sid, "\r\n 权限修改成功!\r\n");
	}

	if(cur_user == TRUE)
	{
		bc_cli_set_usr_lvl(sid, level);
	}
	
	CLI_DBG_LEAVE(l_mdl_id);
	
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

/******************************************************************************\
  Function   : __usermgmt_show_user
  Description:显示账号信息
  Return     : bool true: 成功  false:非零失败
  Others     : 
\******************************************************************************/
static cli_cmd_ret_e __usermgmt_show_user
(
	IN const UI32_T	sid,
	IN cli_value_t		*ptrCliValue,
	IN void			*ptrUserData
)
{
	bc_err_e ret = BC_ERR_OK;
	bc_char name[BC_USERMGMT_NAME_LEN];
	bc_int32 __attribute__ ((unused)) num = 0,i = 0,j=0;
	bc_usermgmt_info_t usermgmt_info[BC_USERMGMT_USER_NUM];
	cli_lan_t     language = CLI_LAN_MAX;
	
	cli_value_t *para_tmp = ptrCliValue;
	UI32_T op_id = *(UI32_T *)para_tmp->value;
	para_tmp = para_tmp->next;

	language = bc_cli_get_lan();
	
	if(op_id == 1)
	{
		ret = bc_usermgmt_get_list(usermgmt_info, &num);
		if(ret != BC_ERR_OK)
		{
			if(language == CLI_LAN_EN)
			{
				if(ret == BC_ERR_USERMGMT_NO_EXIST)
				{
					CLI_API_Printf(sid, "\r\n Operation failure: [%s] is not exist!\r\n", name);
				}
				else if(ret == BC_ERR_USERMGMT_LVL_ERR)
				{
					CLI_API_Printf(sid, "\r\n Operation failure: current user's level is too low!\r\n");
				}
				else
				{
					CLI_API_Printf(sid, "\r\n This user has been get user information failure!\r\n");
				}
			}
			else
			{
				if(ret == BC_ERR_USERMGMT_NO_EXIST)
				{
					CLI_API_Printf(sid, "\r\n 操作失败: [%s] 不存在t!\r\n", name);
				}
				else if(ret == BC_ERR_USERMGMT_LVL_ERR)
				{
					CLI_API_Printf(sid, "\r\n 操作失败: 当前用户的权限太低!\r\n");
				}
				else
				{
					CLI_API_Printf(sid, "\r\n 获取用户信息失败!\r\n");
				}
			}
			return CLI_CMD_FAIL_PRT_NEWLINE;
		}
	}
	else if(op_id == 2)
	{
		strcpy(name, (bc_char *)para_tmp->value);
		ret = bc_usermgmt_get_info(name, &usermgmt_info[0]);
		if(ret != BC_ERR_OK)
		{
			if(language == CLI_LAN_EN)
			{
				if(ret == BC_ERR_USERMGMT_NO_EXIST)
				{
					CLI_API_Printf(sid, "\r\n Operation failure: [%s] is not exist!\r\n", name);
				}
				else if(ret == BC_ERR_USERMGMT_LVL_ERR)
				{
					CLI_API_Printf(sid, "\r\n Operation failure: current user's level is too low!\r\n");
				}
				else
				{
					CLI_API_Printf(sid, "\r\n This user has been get user information failure!\r\n");
				}
			}
			else
			{
				if(ret == BC_ERR_USERMGMT_NO_EXIST)
				{
					CLI_API_Printf(sid, "\r\n 操作失败: [%s] 不存在t!\r\n", name);
				}
				else if(ret == BC_ERR_USERMGMT_LVL_ERR)
				{
					CLI_API_Printf(sid, "\r\n 操作失败: 当前用户的权限太低!\r\n");
				}
				else
				{
					CLI_API_Printf(sid, "\r\n 获取用户信息失败!\r\n");
				}
			}
			return CLI_CMD_FAIL_PRT_NEWLINE;
		}
		num = 1;
	}
	else
	{
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}

	if(language == CLI_LAN_EN)
	{	
		CLI_API_Printf(sid, "\r\n username items:[%d]", num);
		CLI_API_Printf(sid, "\r\n --------------------------------------------------------------------");
		CLI_API_Printf(sid, "\r\n     %-8s\t%-8s\t%-8s\t%-8s", "Name", "Level", "State", "Links");
		CLI_API_Printf(sid, "\r\n --------------------------------------------------------------------");
		for(i=0; i<num; i++)
		{
			CLI_API_Printf(sid, "\r\n     %-8s\t", usermgmt_info[i].name);
			switch(usermgmt_info[i].level)
			{
				case BC_USERMGMT_LVL_BASIC:
					CLI_API_Printf(sid, "%-8s\t", "basic");
					break;
				case BC_USERMGMT_LVL_PRIVI:
					CLI_API_Printf(sid, "%-8s\t", "privi");
					break;
				case BC_USERMGMT_LVL_USER:
					CLI_API_Printf(sid, "%-8s\t", "user");
					break;
				case BC_USERMGMT_LVL_PUSER:
					CLI_API_Printf(sid, "%-8s\t", "puser");
					break;
				case BC_USERMGMT_LVL_ADMIN:
					CLI_API_Printf(sid, "%-8s\t", "admin");
					break;
				case BC_USERMGMT_LVL_FACTORY:
					CLI_API_Printf(sid, "%-8s\t", "factory");
					break;
				case BC_USERMGMT_LVL_DEBUG:
					CLI_API_Printf(sid, "%-8s\t", "debug");
					break;
				default:
					CLI_API_Printf(sid, "%-8s\t", "unknow");
					break;
			}
			if(usermgmt_info[i].state == BC_USERMGMT_STATE_LOGIN)
			{
				CLI_API_Printf(sid, "%-8s\t", "online");
			}
			else
			{
				CLI_API_Printf(sid, "%-8s\t", "------");
			}
			CLI_API_Printf(sid, "%d", usermgmt_info[i].links);
		}
		CLI_API_Printf(sid, "\r\n --------------------------------------------------------------------");
	}
	else
	{
		CLI_API_Printf(sid, "\r\n 用户数目:[%d]", num);
		CLI_API_Printf(sid, "\r\n --------------------------------------------------------------------");
		CLI_API_Printf(sid, "\r\n     %-8s\t%-8s\t%-8s\t%-8s", "用户名", "权限", "状态", "连接数");
		CLI_API_Printf(sid, "\r\n --------------------------------------------------------------------");
		for(i=0; i<num; i++)
		{
			CLI_API_Printf(sid, "\r\n     %-8s\t", usermgmt_info[i].name);
			switch(usermgmt_info[i].level)
			{
				case BC_USERMGMT_LVL_BASIC:
					CLI_API_Printf(sid, "%-8s\t", "basic");
					break;
				case BC_USERMGMT_LVL_PRIVI:
					CLI_API_Printf(sid, "%-8s\t", "privi");
					break;
				case BC_USERMGMT_LVL_USER:
					CLI_API_Printf(sid, "%-8s\t", "user");
					break;
				case BC_USERMGMT_LVL_PUSER:
					CLI_API_Printf(sid, "%-8s\t", "puser");
					break;
				case BC_USERMGMT_LVL_ADMIN:
					CLI_API_Printf(sid, "%-8s\t", "admin");
					break;
				case BC_USERMGMT_LVL_FACTORY:
					CLI_API_Printf(sid, "%-8s\t", "factory");
					break;
				case BC_USERMGMT_LVL_DEBUG:
					CLI_API_Printf(sid, "%-8s\t", "debug");
					break;
				default:
					CLI_API_Printf(sid, "%-8s\t", "unknow");
					break;
			}
			if(usermgmt_info[i].state == BC_USERMGMT_STATE_LOGIN)
			{
				CLI_API_Printf(sid, "%-8s\t", "上线");
			}
			else
			{
				CLI_API_Printf(sid, "%-8s\t", "------");
			}
			CLI_API_Printf(sid, "%d", usermgmt_info[i].links);
		}
		CLI_API_Printf(sid, "\r\n --------------------------------------------------------------------");
	}
#if 0
	CLI_API_Printf(sid, "\r\n username items:[%d]", num);
	CLI_API_Printf(sid, "\r\n --------------------------------------------------------------------");
//	CLI_API_Printf(sid, "\r\n %-8s\t%-8s\t%-8s\t%-8s\t%-8s\t%-8s", "Name", "Level", "State", "Links", "LoginTime", "LogoutTime");
	CLI_API_Printf(sid, "\r\n     %-8s\t%-8s\t%-8s\t%-8s", "Name", "Level", "State", "Links");
	CLI_API_Printf(sid, "\r\n --------------------------------------------------------------------");
	for(i=0; i<num; i++)
	{
		CLI_API_Printf(sid, "\r\n     %-8s\t", usermgmt_info[i].name);
		switch(usermgmt_info[i].level)
		{
			case BC_USERMGMT_LVL_BASIC:
				CLI_API_Printf(sid, "%-8s\t", "basic");
				break;
			case BC_USERMGMT_LVL_PRIVI:
				CLI_API_Printf(sid, "%-8s\t", "privi");
				break;
			case BC_USERMGMT_LVL_USER:
				CLI_API_Printf(sid, "%-8s\t", "user");
				break;
			case BC_USERMGMT_LVL_PUSER:
				CLI_API_Printf(sid, "%-8s\t", "puser");
				break;
			case BC_USERMGMT_LVL_ADMIN:
				CLI_API_Printf(sid, "%-8s\t", "admin");
				break;
			case BC_USERMGMT_LVL_FACTORY:
				CLI_API_Printf(sid, "%-8s\t", "factory");
				break;
			case BC_USERMGMT_LVL_DEBUG:
				CLI_API_Printf(sid, "%-8s\t", "debug");
				break;
			default:
				CLI_API_Printf(sid, "%-8s\t", "unknow");
				break;
		}
		if(usermgmt_info[i].state == BC_USERMGMT_STATE_LOGIN)
		{
			CLI_API_Printf(sid, "%-8s\t", "online");
		}
		else
		{
			CLI_API_Printf(sid, "%-8s\t", "------");
		}
		/*
		CLI_API_Printf(sid, "%d[", usermgmt_info[i].links);
		for(j=0; j<usermgmt_info[i].links; j++)
		{
			if(usermgmt_info[i].line_info[j].sid != BC_USERMGMT_SID_UNUSED
				&&usermgmt_info[i].line_info[j].state == BC_USERMGMT_STATE_LOGIN)
			{
				CLI_API_Printf(sid, "%d,", usermgmt_info[i].line_info[j].sid);
			}
		}
		CLI_API_Printf(sid, "]\t");
		*/
		CLI_API_Printf(sid, "%d", usermgmt_info[i].links);
	//	CLI_API_Printf(sid, " %-8s\t", "null");
	//	CLI_API_Printf(sid, " %s", "null");
	}
	CLI_API_Printf(sid, "\r\n --------------------------------------------------------------------");
#endif
	CLI_DBG_ENTER(l_mdl_id);
	
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

/******************************************************************************\
  Function   : __usermgmt_show_user_dbg
  Description:显示账号信息
  Return     : bool true: 成功  false:非零失败
  Others     : 
\******************************************************************************/
static cli_cmd_ret_e __usermgmt_show_user_dbg
(
	IN const UI32_T	sid,
	IN cli_value_t		*ptrCliValue,
	IN void			*ptrUserData
)
{
	bc_err_e ret = BC_ERR_OK;
//	bc_char name[BC_USERMGMT_NAME_LEN];
	bc_int32 __attribute__ ((unused)) num = 0,i = 0,j=0;
	bc_usermgmt_info_t usermgmt_info[BC_USERMGMT_USER_NUM];
	
	cli_value_t *para_tmp = ptrCliValue;
	UI32_T op_id = *(UI32_T *)para_tmp->value;
	para_tmp = para_tmp->next;
/*	
	if(op_id == 1)
	{
		ret = bc_usermgmt_get_list(usermgmt_info, &num);
		if(ret != BC_ERR_OK)
		{
			CLI_API_Printf(sid, "\r\n Failed to usermgmt get list, ret = 0x%x!\r\n", ret);
			return CLI_CMD_FAIL_PRT_NEWLINE;
		}
	}
	else if(op_id == 2)
	{
		strcpy(name, (bc_char *)para_tmp->value);
		ret = bc_usermgmt_get_info(name, &usermgmt_info[0]);
		if(ret != BC_ERR_OK)
		{
			CLI_API_Printf(sid, "\r\n Failed to usermgmt get info, ret = 0x%x!\r\n", ret);
			return CLI_CMD_FAIL_PRT_NEWLINE;
		}
		num = 1;
	}*/
	if(op_id == 3)
	{
		ret = bc_usermgmt_get_list_dump(usermgmt_info, &num);
		if(ret != BC_ERR_OK)
		{
			CLI_API_Printf(sid, "\r\n Failed to usermgmt get list test, ret = 0x%x!\r\n", ret);
			return CLI_CMD_FAIL_PRT_NEWLINE;
		}
	}
	else
	{
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	
	CLI_API_Printf(sid, "\r\n username items:[%d]", num);
	CLI_API_Printf(sid, "\r\n --------------------------------------------------------------------");
//	CLI_API_Printf(sid, "\r\n %-8s\t%-8s\t%-8s\t%-8s\t%-8s\t%-8s", "Name", "Level", "State", "Links", "LoginTime", "LogoutTime");
	CLI_API_Printf(sid, "\r\n     %-8s\t%-8s\t%-8s\t%-8s", "Name", "Level", "State", "Links");
	CLI_API_Printf(sid, "\r\n --------------------------------------------------------------------");
	for(i=0; i<num; i++)
	{
		CLI_API_Printf(sid, "\r\n     %-8s\t", usermgmt_info[i].name);
		switch(usermgmt_info[i].level)
		{
			case BC_USERMGMT_LVL_BASIC:
				CLI_API_Printf(sid, "%-8s\t", "basic");
				break;
			case BC_USERMGMT_LVL_PRIVI:
				CLI_API_Printf(sid, "%-8s\t", "privi");
				break;
			case BC_USERMGMT_LVL_USER:
				CLI_API_Printf(sid, "%-8s\t", "user");
				break;
			case BC_USERMGMT_LVL_PUSER:
				CLI_API_Printf(sid, "%-8s\t", "puser");
				break;
			case BC_USERMGMT_LVL_ADMIN:
				CLI_API_Printf(sid, "%-8s\t", "admin");
				break;
			case BC_USERMGMT_LVL_FACTORY:
				CLI_API_Printf(sid, "%-8s\t", "factory");
				break;
			case BC_USERMGMT_LVL_DEBUG:
				CLI_API_Printf(sid, "%-8s\t", "debug");
				break;
			default:
				CLI_API_Printf(sid, "%-8s\t", "unknow");
				break;
		}
		if(usermgmt_info[i].state == BC_USERMGMT_STATE_LOGIN)
		{
			CLI_API_Printf(sid, "%-8s\t", "online");
		}
		else
		{
			CLI_API_Printf(sid, "%-8s\t", "------");
		}
		/*
		CLI_API_Printf(sid, "%d[", usermgmt_info[i].links);
		for(j=0; j<usermgmt_info[i].links; j++)
		{
			if(usermgmt_info[i].line_info[j].sid != BC_USERMGMT_SID_UNUSED
				&&usermgmt_info[i].line_info[j].state == BC_USERMGMT_STATE_LOGIN)
			{
				CLI_API_Printf(sid, "%d,", usermgmt_info[i].line_info[j].sid);
			}
		}
		CLI_API_Printf(sid, "]\t");
		*/
		CLI_API_Printf(sid, "%d", usermgmt_info[i].links);
	//	CLI_API_Printf(sid, " %-8s\t", "null");
	//	CLI_API_Printf(sid, " %s", "null");
	}
	CLI_API_Printf(sid, "\r\n --------------------------------------------------------------------");
	CLI_DBG_ENTER(l_mdl_id);
	
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

/******************************************************************************\
  Function   : __usermgmt_login
  Description: 注册
  Return     : bool true: 成功  false:非零失败
  Others     : 
\******************************************************************************/
static cli_cmd_ret_e __usermgmt_login
(
	IN const UI32_T	sid,
	IN cli_value_t		*ptrCliValue,
	IN void			*ptrUserData
)
{
//	int cnt = 0;
	bc_err_e ret = BC_ERR_OK;
	char			pUsrPrompt_1[BC_USERMGMT_NAME_LEN];
	char			pUsrPrompt_2[BC_USERMGMT_NAME_LEN];
	char *p = NULL;
	bc_char name[BC_USERMGMT_NAME_LEN];
	bc_char pwd[BC_USERMGMT_NAME_LEN];
	bc_usermgmt_level_e level = BC_USERMGMT_LVL_MAX;
	cli_lan_t     language = CLI_LAN_MAX;
	
	language = bc_cli_get_lan();

	if(language == CLI_LAN_EN)
	{	
		CLI_API_Printf(sid, "\r\n Username(<=15 chars):");
	}
	else
	{
		CLI_API_Printf(sid, "\r\n 用户名(<=15 chars):");
	}
	
	setbuf(stdin, NULL);
	fgets(pUsrPrompt_1, BC_USERMGMT_NAME_LEN, stdin);

	if(strlen(pUsrPrompt_1) > 15)
	{
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	strcpy(name, pUsrPrompt_1);
	name[strlen(name)-1] = '\0';
/*
	printf("strlen(%s) = %d\r\n", name, strlen(name));
	if(strlen(pUsrPrompt_1) > 17)
	{
		CLI_API_Printf(sid, "\r\n\n The username was too long!\r\n");
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
*/
	/*passwd*/
	memset(pUsrPrompt_2, 0, sizeof(pUsrPrompt_2));

	if(language == CLI_LAN_EN)
	{	
		CLI_API_Printf(sid, " Password(<=15 chars):");
	}
	else
	{
		CLI_API_Printf(sid, " 密码(<=15 chars):");
	}
	
	__usermgmt_set_disp_mode(STDIN_FILENO, FALSE);
	if(__usermgmt_get_pwd(pUsrPrompt_2, BC_USERMGMT_NAME_LEN) != TRUE)
	{
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	if(strlen(pUsrPrompt_2) > 15)
	{
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	p = pUsrPrompt_2;
	while(*p != '\n')
	{
	#if 0
		/*The first char must be lowercase or uppercase.*/
		if(!cnt)
		{
			if((*p>=65&&*p<=90) || (*p>=97&&*p<=122))
			{
			}
			else
			{
				return CLI_CMD_FAIL_PRT_NEWLINE;
			}
		}
		/*With the exception of the first char, the string was mixed by lowercase and uppercase and number.*/
		else	
		{
			if((*p>=48&&*p<=57) || (*p>=65&&*p<=90) || (*p>=97&&*p<=122))
			{
			}
			else
			{
				return CLI_CMD_FAIL_PRT_NEWLINE;
			}	
		}
	#endif
		p++;
	//	cnt++;
	}
	*p = '\0';
	
	__usermgmt_set_disp_mode(STDIN_FILENO, TRUE);
	strcpy(pwd, pUsrPrompt_2);
//	printf("strlen(%s) = %d\r\n", pUsrPrompt_2, strlen(pUsrPrompt_2));
	ret = bc_usermgmt_login(name,pwd, &level);
	if(ret != BC_ERR_OK)
	{
		level = BC_USERMGMT_LVL_MAX;
		CLI_API_Printf(sid, "\r\n\n Failed to usermgmt login, ret = 0x%x!\r\n", ret);
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}

	if(language == CLI_LAN_EN)
	{	
		CLI_API_Printf(sid, "\r\n\n This user has been login success!\r\n");
	}
	else
	{
		CLI_API_Printf(sid, "\r\n  用户登陆成功!\r\n");
	}
	
	CLI_DBG_LEAVE(l_mdl_id);
	  
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

/******************************************************************************\
  Function   : __usermgmt_logout
  Description: 注册
  Return     : bool true: 成功  false:非零失败
  Others     : 
\******************************************************************************/
static cli_cmd_ret_e __usermgmt_logout
(
	IN const UI32_T	sid,
	IN cli_value_t		*ptrCliValue,
	IN void			*ptrUserData
)
{
	bc_err_e ret = BC_ERR_OK;
	char			pUsrPrompt[BC_USERMGMT_NAME_LEN];

	cli_lan_t     language = CLI_LAN_MAX;
	language = bc_cli_get_lan();
	
	CLI_DBG_ENTER(l_mdl_id);

	if(language == CLI_LAN_EN)
	{	
		CLI_API_Printf(sid, "\r\n  Are you sure to kick the user off?(y/n)\r\n");
	}
	else
	{
		CLI_API_Printf(sid, "\r\n  确认登出此用户?(y/n)\r\n");
	}
		
	
	setbuf(stdin, NULL);
	fgets(pUsrPrompt, BC_USERMGMT_NAME_LEN, stdin);
	if(strlen(pUsrPrompt) != 2)
	{
		if(language == CLI_LAN_EN)
		{	
			CLI_API_Printf(sid, "\r\n Operation failure: Failed to input!\r\n");
		}
		else
		{
			CLI_API_Printf(sid, "\r\n 操作失败: 输入错误!\r\n");
		}
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	pUsrPrompt[strlen(pUsrPrompt) -1] = '\0';
	CLI_API_Printf(sid, "%c\r\n", pUsrPrompt[0]);
	if ((pUsrPrompt[0] != 'y') && (pUsrPrompt[0] != 'Y'))
	{
	//	printf("[%s, %d], pUsrPrompt[0] = %c, error!!!\r\n", __FUNCTION__, __LINE__, pUsrPrompt[0]);
		setbuf(stdin, NULL);
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	
	ret = bc_usermgmt_logout();
	if(ret != BC_ERR_OK)
	{
		CLI_API_Printf(sid, "\r\n Failed to usermgmt logout, ret = 0x%x!\r\n", ret);
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	if(language == CLI_LAN_EN)
	{	
		CLI_API_Printf(sid, "\r\n This user has been logout success!\r\n");
	}
	else
	{
		CLI_API_Printf(sid, "\r\n 用户登出成功!\r\n");
	}

	bc_cli_logout(sid);
	
	CLI_DBG_LEAVE(l_mdl_id);
	
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}


#if 1
void bc_cli_cmd_usermgmt_reg(void)
{
	CLI_DBG_ENTER(l_mdl_id);
	BOOL_T ret_reg;
#if 0
	/*reg*/
	ret_reg = bc_cli_reg_cmd(
		CLI_MOD_PRIVI_PATH
		"/username "		 	"#register a new user #""#注册一个新用户#"
		"<username>"	"#user name #""#用户名#"
		"password "		"#create password #""#创建登陆密码#"
		"<password>"	"#user password #""#密码#"
		"privilege "		"#create level #""#创建操作权限#"
		"<privilege>"	"#user level (1)basic, (2)privi, (3)user, (4)puser, (5)admin, (6)factory, (7)debug #""#权限(1)basic, (2)privi, (3)user, (4)puser, (5)admin, (6)factory, (7)debug #",
		__usermgmt_register,
		CLI_ACC_LVL_BASIC,
		"username.",
		"注册一个新用户。",
		NULL);
	CLI_DBG_CPL(l_mdl_id, "ret=%d\r\n", ret_reg);
#endif
	/*reg*/
	ret_reg = bc_cli_reg_cmd(
		CLI_MOD_PRIVI_PATH
		"/username "		 	"#register a new user #""#注册一个新用户#",
		__usermgmt_register,
		CLI_ACC_LVL_BASIC,
		"username.",
		"注册新用户。",
		NULL);
	CLI_DBG_CPL(l_mdl_id, "ret=%d\r\n", ret_reg);
	
	/*unreg*/
	ret_reg = bc_cli_reg_cmd(
		CLI_MOD_PRIVI_PATH
		"/no "		 	"##""##"
		"username "          "#unregister user #""#注销一个用户#"
		"<username>"		"#user name #""#用户名#",
		__usermgmt_unregister,
		CLI_ACC_LVL_BASIC,
		"username.",
		"注销一个用户。",
		NULL);
	CLI_DBG_CPL(l_mdl_id, "ret=%d\r\n", ret_reg);

	/*login*/
	ret_reg = bc_cli_reg_cmd(
		CLI_MOD_PRIVI_PATH
		"/login "		 	"#login user #""#用户登陆#",
		__usermgmt_login,
		CLI_ACC_LVL_BASIC,
		"login.",
		"用户登陆。",
		NULL);
	CLI_DBG_CPL(l_mdl_id, "ret=%d\r\n", ret_reg);

	/*logout*/
	ret_reg = bc_cli_reg_cmd(
		CLI_MOD_PRIVI_PATH
		"/logout "		 	"#logout user #""#用户登出#",
		__usermgmt_logout,
		CLI_ACC_LVL_BASIC,
		"logout.",
		"用户登出。",
		NULL);
	CLI_DBG_CPL(l_mdl_id, "ret=%d\r\n", ret_reg);

	/*set pwd*/
	ret_reg = bc_cli_reg_cmd(
		CLI_MOD_PRIVI_PATH
		"/password "		 	"#set user password #""#设置用户密码#"
		"["
			"<username>"	"#user name #""#用户名#"
		"]",
		__usermgmt_set_pwd,
		CLI_ACC_LVL_BASIC,
		"password.",
		"修改用户密码。",
		NULL);
	CLI_DBG_CPL(l_mdl_id, "ret=%d\r\n", ret_reg);

	/*set lvl*/
	ret_reg = bc_cli_reg_cmd(
		CLI_MOD_PRIVI_PATH
		"/level "		 	"#set user level #""#设置用户权限#"
		"["
			"<username>"	"#user name #""#用户名#"
		"]",
		__usermgmt_set_lvl,
		CLI_ACC_LVL_BASIC,
		"level.",
		"修改用户权限。",
		NULL);
	CLI_DBG_CPL(l_mdl_id, "ret=%d\r\n", ret_reg);

	/*show*/
	ret_reg = bc_cli_reg_cmd(
		CLI_MOD_PRIVI_PATH
		"/show "		 	"##""##"
		"user "		"#create password #""#创建登陆密码#"
		"{"
			"all(1) " 			"#user list#""#所有用户#"
			"|"
			"username(2) "		"#user name #""#用户名#"
				"<username>"		"#user name #""#用户名#"
		"}",
		__usermgmt_show_user,
		CLI_ACC_LVL_BASIC,
		"show.",
		"显示用户信息。",
		NULL);
	CLI_DBG_CPL(l_mdl_id, "ret=%d\r\n", ret_reg);

	/*debug show*/
	ret_reg = bc_cli_reg_cmd(
		CLI_MOD_DEBUG_PATH
		"/show "		 	"##""##"
		"user "		"#create password #""#创建登陆密码#"
		"{"
			"dump(3)"		"#show all #""#show all #"
		"}",
		__usermgmt_show_user_dbg,
		CLI_ACC_LVL_BASIC,
		"show.",
		"显示用户信息。",
		NULL);
	CLI_DBG_CPL(l_mdl_id, "ret=%d\r\n", ret_reg);
}




/* 
 *	预留一个注释在文件最后
 */
/******************************************************************************\
  Function   : 
  Description: 
  Return     : 
  Others     : 
\******************************************************************************/

#endif



