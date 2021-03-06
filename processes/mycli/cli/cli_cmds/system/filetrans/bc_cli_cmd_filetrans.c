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
	2016-08-05  Created												  bain.wang@outlook.com
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								头   文   件								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "bc_modules.h"

#include "bc_cli_type.h"
#include "bc_cli_paratype.h"

#include "bc_cli.h"
#include "bc_filetrans_def.h"
#include "bc_filetrans_file.h"

#include "utili_bit.h"
//#include "bc_cli_cmd_port.h"
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
 static unsigned int 	l_mdl_id = BC_MODULE_FILETRANS;

#define DEBUG_CMD_EN	FALSE

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




#if 1
/******************************************************************************\
  Function   : __filetrans_transmission_show
  Description: 显示下载中的信息
  Return     : bool true: 成功  false:非零失败
  Others     : 
\******************************************************************************/
static bc_err_e __filetrans_show(bc_filetrans_function_e trans_fun)
{
	bc_filetrans_cfg_t trans_cfg;
	bc_err_e ret = BC_ERR_OK;

	CLI_DBG_ENTER(l_mdl_id);
	memset(&trans_cfg, 0, sizeof(bc_filetrans_cfg_t));

	ret = bc_filetrans_get_info(trans_fun, &trans_cfg);
	if(ret != BC_ERR_OK)
	{
		CLI_API_Printf(l_mdl_id, "\r\n Failed to get info = %d!\r\n", ret);
		return ret;
	}
	CLI_API_Printf(l_mdl_id, "\r\n");
	while(trans_cfg.status == BC_FILETRANS_STATUS_INPROGRESS)
	{
		sleep(1);

		CLI_API_Printf(l_mdl_id, "Downloading...%3u%% \r", trans_cfg.prog_value);
		
		fflush(stdout);
		ret = bc_filetrans_get_info(trans_fun, &trans_cfg);
		if(ret != BC_ERR_OK)
		{
			CLI_API_Printf(l_mdl_id, "\r\n Failed to get info = %d!\r\n", ret);
			return ret;
		}
	}
	if(trans_fun == BC_FILETRANS_BACKUP_CONFIG ||trans_fun == BC_FILETRANS_BACKUP_LOG)
	{
		CLI_API_Printf(l_mdl_id, "Uploading...%3u%% \r\n", trans_cfg.prog_value);
	}
	else
	{
		CLI_API_Printf(l_mdl_id, "Downloading...%3u%% \r\n", trans_cfg.prog_value);
	}
	CLI_API_Printf(l_mdl_id, "status: ");
	switch (trans_cfg.status)
	{
		case BC_FILETRANS_STATUS_IDLE:
			CLI_API_Printf(l_mdl_id, "%s\r\n", "idle");
			break;
		case BC_FILETRANS_STATUS_INPROGRESS:
			CLI_API_Printf(l_mdl_id, "%s\r\n", "in progress");
			break;
		case BC_FILETRANS_STATUS_SUCCESS:
			CLI_API_Printf(l_mdl_id, "%s\r\n", "success");
			break;
		case BC_FILETRANS_STATUS_FAILURE:
			CLI_API_Printf(l_mdl_id, "%s\r\n", "failure");
			break;
		case BC_FILETRANS_STATUS_NO_RESOURCE:
			CLI_API_Printf(l_mdl_id, "%s\r\n", "No Resource");
			break;
		case BC_FILETRANS_STATUS_STOP_SUCCESS:
			CLI_API_Printf(l_mdl_id, "%s\r\n", "stop success!");
			break;
		default:
			CLI_API_Printf(l_mdl_id, "%s\r\n", "??");
		break;
	}
	
	CLI_DBG_LEAVE(l_mdl_id);

	return ret;
}

#if 1
/******************************************************************************\
  Function   : __filetrans_dump
  Description: 实时显示传输所有参数
  Return     : bool true: 成功  false:非零失败
  Others     : 
\******************************************************************************/
static void __filetrans_dump(UI32_T sid, bc_filetrans_cfg_t trans_cfg)
{
	int i = 0;
	struct in_addr sin_addr;

	CLI_API_Printf(sid, "\r\n--------------------FiletransInfo----------------------\r\n");

		//协议类型
		CLI_API_Printf(sid, "%-15s:", "proto_type");
		if(trans_cfg.proto_type == BC_FILETRANS_TYPE_TFTP)
		{
			CLI_API_Printf(sid, "TFTP.\r\n");
		}
		else if(trans_cfg.proto_type == BC_FILETRANS_TYPE_FTP)
		{
			CLI_API_Printf(sid, "FTP.\r\n");
		}
		else
		{
			CLI_API_Printf(sid, "USB.\r\n");
		}
		
		//文件类型
		CLI_API_Printf(sid, "%-15s:", "trans_fun");
		if(trans_cfg.trans_fun == BC_FILETRANS_KERNEL)
		{
			CLI_API_Printf(sid, "kernel.\r\n");
		}
		else if(trans_cfg.trans_fun == BC_FILETRANS_ROOT_FS)
		{
			CLI_API_Printf(sid, "root-fs.\r\n");
		}
		else if(trans_cfg.trans_fun == BC_FILETRANS_USER_FS)
		{
			CLI_API_Printf(sid, "user-fs.\r\n");
		}
		else if(trans_cfg.trans_fun == BC_FILETRANS_OLT)
		{
			CLI_API_Printf(sid, "olt-image.\r\n");
		}
		else if(trans_cfg.trans_fun == BC_FILETRANS_BACKUP_CONFIG)
		{
			CLI_API_Printf(sid, "backup-config.\r\n");
		}
		else if(trans_cfg.trans_fun == BC_FILETRANS_CONFIG)
		{
			CLI_API_Printf(sid, "config.\r\n");
		}
		else if(trans_cfg.trans_fun == BC_FILETRANS_DBTB)
		{
			CLI_API_Printf(sid, "dbtb.\r\n");
		}
		else if(trans_cfg.trans_fun == BC_FILETRANS_UBOOT)
		{
			CLI_API_Printf(sid, "uboot.\r\n");
		}
		else
		{
			CLI_API_Printf(sid, "log.\r\n");
		}
		//用户名与密码
		if(trans_cfg.proto_type == BC_FILETRANS_TYPE_FTP)
		{
			CLI_API_Printf(sid, "%-15s:.\r\n", trans_cfg.usr_name);
			CLI_API_Printf(sid, "%-15s:.\r\n", trans_cfg.psswrd);
		}
		//文件名
		if(trans_cfg.trans_fun == BC_FILETRANS_BACKUP_CONFIG || trans_cfg.trans_fun == BC_FILETRANS_BACKUP_LOG)
		{
			CLI_API_Printf(sid, "%-15s:%s.\r\n", "dst_file_name", trans_cfg.dst_file_name);
		}
		else
		{
			CLI_API_Printf(sid, "%-15s:%s.\r\n", "src_file_name", trans_cfg.src_file_name);
		}
		//IP地址
		sin_addr.s_addr = trans_cfg.ip;
		CLI_API_Printf(sid, "%-15s:%s.\r\n", "ip-address", inet_ntoa(sin_addr));

	CLI_API_Printf(sid, "\r\n-------------------------------------------------------\r\n");
}
#endif
/******************************************************************************\
  Function   : __do_filetrans_upgrade
  Description: 传输文件
  Return     : bool true: 成功  false:非零失败
  Others     : 
\******************************************************************************/
static bc_err_e __do_filetrans_upgrade
    (
    IN const UI32_T	sid,
    IN cli_value_t		*ptrCliValue,
    IN void			*ptrUserData,
    IN bc_filetrans_function_e trans_fun,
    IN bc_filetrans_proto_type_e proto_type
    )
{
	bc_err_e ret = BC_ERR_OK;
	bc_filetrans_cfg_t trans_cfg;
	cli_value_t		*para_tmp = ptrCliValue;
	bc_int32 i = 0;
	
	CLI_DBG_ENTER(l_mdl_id);
	
	memset(trans_cfg.usr_name, 0, sizeof(trans_cfg.usr_name));
	memset(trans_cfg.psswrd, 0, sizeof(trans_cfg.psswrd));
	trans_cfg.proto_type = proto_type;
	trans_cfg.trans_fun = trans_fun;

	if(proto_type == BC_FILETRANS_TYPE_FTP)	/*NONSUPPORT*/
	{
	//	printf("proto_type == BC_FILETRANS_TYPE_FTP\r\n");
		strcpy(trans_cfg.usr_name, (bc_char *)para_tmp->value);
		para_tmp = para_tmp->next;
		strcpy(trans_cfg.psswrd, (bc_char *)para_tmp->value);
		para_tmp = para_tmp->next;
		BC_PT_DBG_CPL(l_mdl_id, "Cli Para No3: usr_name=%s\r\n", trans_cfg.usr_name);
		BC_PT_DBG_CPL(l_mdl_id, "Cli Para No4: psswrd=%s\r\n", trans_cfg.psswrd);
	}

	if(trans_fun == BC_FILETRANS_BACKUP_CONFIG || trans_fun == BC_FILETRANS_BACKUP_LOG)
	{
	//	printf("trans_fun == BC_FILETRANS_BACKUP_CONFIG || trans_fun == BC_FILETRANS_BACKUP_LOG\r\n");
		strcpy(trans_cfg.dst_file_name, (bc_char *)para_tmp->value);

#if 1
		if(strlen(trans_cfg.dst_file_name) >=BC_MODULE_NAME_LENGTH)
		{
			return BC_ERR_FILETRANS_NAME_INVALID;
		}
		/*check src file name*/
		for(i=0; i<strlen(trans_cfg.dst_file_name); i++)
		{
			if(trans_cfg.dst_file_name[i] == '(' 
				|| trans_cfg.dst_file_name[i] == ')'
				|| trans_cfg.dst_file_name[i] == '/' 
				|| trans_cfg.dst_file_name[i] == '\''
				|| trans_cfg.dst_file_name[i] == '~'
				|| trans_cfg.dst_file_name[i] == '`'
				|| trans_cfg.dst_file_name[i] == '!' 
				|| trans_cfg.dst_file_name[i] == '@'
				|| trans_cfg.dst_file_name[i] == '#'
				|| trans_cfg.dst_file_name[i] == '$'
				|| trans_cfg.dst_file_name[i] == '%' 
				|| trans_cfg.dst_file_name[i] == '^'
				|| trans_cfg.dst_file_name[i] == '&'
				|| trans_cfg.dst_file_name[i] == '*'
				|| trans_cfg.dst_file_name[i] == '/' 
				|| trans_cfg.dst_file_name[i] == '\''
				|| trans_cfg.dst_file_name[i] == '~')
			{
				return BC_ERR_FILETRANS_NAME_INVALID;
			}
		}
#endif	
		if(proto_type != BC_FILETRANS_TYPE_USB)
		{
			para_tmp = para_tmp->next;
			trans_cfg.ip = *(bc_uint32 *)para_tmp->value;
		}

	//	__filetrans_dump(sid, trans_cfg);
		
		BC_PT_DBG_CPL(l_mdl_id, "Cli Para No5: dst_file_name=%s\r\n", trans_cfg.dst_file_name);
		if(proto_type != BC_FILETRANS_TYPE_USB)
		{
			BC_PT_DBG_CPL(l_mdl_id, "Cli Para No6: ip=%ld\r\n", trans_cfg.ip);
		}
		if((ret = bc_filetrans_set_upload_file(&trans_cfg)) != BC_ERR_OK)
		{
			CLI_API_Printf(sid, "\r\n Failed to filetrans set upload file, ret = 0x%x!\r\n", ret);
			return ret;
		}
	}
	else
	{
	//	printf("trans_fun != BC_FILETRANS_BACKUP_CONFIG  trans_fun != BC_FILETRANS_BACKUP_LOG\r\n");
		strcpy(trans_cfg.src_file_name, (bc_char *)para_tmp->value);
#if 1
	//	printf("src_file_name = [%s], len = %d\r\n", trans_cfg.src_file_name, strlen(trans_cfg.src_file_name));
		/*check src file name*/
		if(strlen(trans_cfg.src_file_name) >=BC_MODULE_NAME_LENGTH)
		{
			return BC_ERR_FILETRANS_NAME_INVALID;
		}
		for(i=0; i<strlen(trans_cfg.src_file_name); i++)
		{
		//	printf("p[%d]=%c\r\n", i, trans_cfg.src_file_name[i]);
			if(trans_cfg.src_file_name[i] == '(' 
				|| trans_cfg.src_file_name[i] == ')'
				|| trans_cfg.src_file_name[i] == '/' 
				|| trans_cfg.src_file_name[i] == '\''
				|| trans_cfg.src_file_name[i] == '~'
				|| trans_cfg.src_file_name[i] == '`'
				|| trans_cfg.src_file_name[i] == '!' 
				|| trans_cfg.src_file_name[i] == '@'
				|| trans_cfg.src_file_name[i] == '#'
				|| trans_cfg.src_file_name[i] == '$'
				|| trans_cfg.src_file_name[i] == '%' 
				|| trans_cfg.src_file_name[i] == '^'
				|| trans_cfg.src_file_name[i] == '&'
				|| trans_cfg.src_file_name[i] == '*'
				|| trans_cfg.src_file_name[i] == '/' 
				|| trans_cfg.src_file_name[i] == '\''
				|| trans_cfg.src_file_name[i] == '~')
			{
			//	printf("p[%d]=%c false!\r\n", i, trans_cfg.src_file_name[i]);
				return BC_ERR_FILETRANS_NAME_INVALID;
			}
		//	printf("p[%d]=%c true!\r\n\n", i, trans_cfg.src_file_name[i]);
		}
#endif	
		if(proto_type != BC_FILETRANS_TYPE_USB)
		{
			para_tmp = para_tmp->next;
			trans_cfg.ip = *(bc_uint32 *)para_tmp->value;
		}
	//	__filetrans_dump(sid, trans_cfg);
		
		BC_PT_DBG_CPL(l_mdl_id, "Cli Para No5: src_file_name=%s\r\n", trans_cfg.src_file_name);
		if(proto_type != BC_FILETRANS_TYPE_USB)
		{
			BC_PT_DBG_CPL(l_mdl_id, "Cli Para No6: ip=%ld\r\n", trans_cfg.ip);
		}
		if((ret = bc_filetrans_set_download_file(&trans_cfg)) != BC_ERR_OK)
		{			
			CLI_API_Printf(sid, "\r\n Failed to filetrans set download file, ret = 0x%x!\r\n", ret);
			return ret;
		}
	}
	
	CLI_DBG_LEAVE(l_mdl_id);
	
	return __filetrans_show(trans_cfg.trans_fun);
}

/******************************************************************************\
  Function   : __filetrans_upgrade
  Description: 设置且升级
  Return     : bool true: 成功  false:非零失败
  Others     : 
\******************************************************************************/
static cli_cmd_ret_e __filetrans_upgrade
    (
    IN const UI32_T	sid,
    IN cli_value_t		*ptrCliValue,
    IN void			*ptrUserData
    )
{
	bc_err_e ret = BC_ERR_OK;

	cli_lan_t     language = CLI_LAN_MAX;
	
	bc_filetrans_function_e trans_fun;
	bc_filetrans_proto_type_e proto_type;
	cli_value_t *para_tmp = ptrCliValue;
	UI32_T op_id = *(UI32_T *)para_tmp->value;
	para_tmp = para_tmp->next;
	CLI_DBG_ENTER(l_mdl_id);
	BC_PT_DBG_CPL(l_mdl_id, "Cli Para No1: op_id=%u\r\n", op_id);

#if 1
	CLI_API_Printf(sid, "\r\n*** not supported warning ***\r\n", ret);
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
#endif

	language = bc_cli_get_lan();
	
	if(op_id == 1 ||op_id == 3)
	{
		if(op_id == 1)
		{
			proto_type = BC_FILETRANS_TYPE_TFTP;
		}
		else		/*NONSUPPORT*/
		{
			proto_type = BC_FILETRANS_TYPE_FTP;
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\tNONSUPPORT! \n\r");
			}
			else
			{
				CLI_API_Printf(sid, "\t不支持! \n\r");
			}
			return CLI_CMD_SUCCESS_PRT_NEWLINE;
		}
		op_id = *(UI32_T *)para_tmp->value;
		para_tmp = para_tmp->next;
		BC_PT_DBG_CPL(l_mdl_id, "Cli Para No2: op_id=%u\r\n", op_id);
		switch(op_id)
		{
			case 14:
				trans_fun = BC_FILETRANS_OLT;
				break;
			case 16:
				trans_fun = BC_FILETRANS_CONFIG;
				break;
			default:
				return CLI_CMD_FAIL_PRT_NEWLINE;
				break;
		}
	}
	else
	{
		if(op_id == 2)
		{
			proto_type = BC_FILETRANS_TYPE_TFTP;
		}
		else
		{
			proto_type = BC_FILETRANS_TYPE_FTP;
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\tNONSUPPORT! \n\r");
			}
			else
			{
				CLI_API_Printf(sid, "\t不支持! \n\r");
			}
			return CLI_CMD_SUCCESS_PRT_NEWLINE;
		}
		op_id = *(UI32_T *)para_tmp->value;
		para_tmp = para_tmp->next;
		BC_PT_DBG_CPL(l_mdl_id, "Cli Para No2: op_id=%u\r\n", op_id);
		switch(op_id)
		{
			case 21:
				trans_fun = BC_FILETRANS_BACKUP_CONFIG;
				break;
			case 22:
				trans_fun = BC_FILETRANS_BACKUP_LOG;
				break;
			default:
				return CLI_CMD_FAIL_PRT_NEWLINE;
				break;
		}
	}

	if(proto_type == BC_FILETRANS_TYPE_FTP)
	{
		//验证用户名与密码
	}
	
	ret = __do_filetrans_upgrade(sid, para_tmp, ptrUserData, trans_fun,proto_type);
	if(ret != BC_ERR_OK)
	{
		if(ret == BC_ERR_FILETRANS_NAME_INVALID)
		{
			if(language == CLI_LAN_EN)
			{	
				CLI_API_Printf(sid, "\r\n Operation failure: File name contains invalid characters or length error!\r\n");
			}
			else
			{
				CLI_API_Printf(sid, "\t操作错误:文件名包含无效的字符或长度不正确 \n\r");
			}
		}
		else
		{
			CLI_API_Printf(sid, "\r\n Failed to transmission set, ret = 0x%x!\r\n", ret);
		}
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}

	CLI_DBG_LEAVE(l_mdl_id);
	
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}


static cli_cmd_ret_e __filetrans_upgrade_dbg
    (
    IN const UI32_T	sid,
    IN cli_value_t		*ptrCliValue,
    IN void			*ptrUserData
    )
{
	bc_err_e ret = BC_ERR_OK;
	bc_filetrans_function_e trans_fun;
	bc_filetrans_proto_type_e proto_type;
	cli_value_t *para_tmp = ptrCliValue;
	UI32_T op_id = *(UI32_T *)para_tmp->value;
	para_tmp = para_tmp->next;
	CLI_DBG_ENTER(l_mdl_id);
	BC_PT_DBG_CPL(l_mdl_id, "Cli Para No1: op_id=%u\r\n", op_id);
	
	if(op_id == 1 ||op_id == 3)
	{
		if(op_id == 1)
		{
			proto_type = BC_FILETRANS_TYPE_TFTP;
		}
		else		/*NONSUPPORT*/
		{
			proto_type = BC_FILETRANS_TYPE_FTP;
			CLI_API_Printf(sid, "\r\n No support!\r\n");
			
			return CLI_CMD_SUCCESS_PRT_NEWLINE;
		}
		op_id = *(UI32_T *)para_tmp->value;
		para_tmp = para_tmp->next;
		BC_PT_DBG_CPL(l_mdl_id, "Cli Para No2: op_id=%u\r\n", op_id);
		switch(op_id)
		{
			case 11:
				trans_fun = BC_FILETRANS_KERNEL;
				break;
			case 12:
				trans_fun = BC_FILETRANS_ROOT_FS;
				break;
			case 13:
				trans_fun = BC_FILETRANS_USER_FS;
				break;
			case 14:
				trans_fun = BC_FILETRANS_OLT;
				break;
			case 16:
				trans_fun = BC_FILETRANS_CONFIG;
				break;
			case 17:
				trans_fun = BC_FILETRANS_DBTB;
				CLI_API_Printf(sid, "\r\n No support!\r\n");
				return CLI_CMD_SUCCESS_PRT_NEWLINE;
			case 18:
				trans_fun = BC_FILETRANS_UBOOT;
				CLI_API_Printf(sid, "\r\n No support!\r\n");
				return CLI_CMD_SUCCESS_PRT_NEWLINE;
			default:
				return CLI_CMD_FAIL_PRT_NEWLINE;
				break;
		}
	}
	else
	{
		if(op_id == 2)
		{
			proto_type = BC_FILETRANS_TYPE_TFTP;
		}
		else
		{
			proto_type = BC_FILETRANS_TYPE_FTP;
			CLI_API_Printf(l_mdl_id, "\tNONSUPPORT! \n\r");
			return CLI_CMD_SUCCESS_PRT_NEWLINE;
		}
		op_id = *(UI32_T *)para_tmp->value;
		para_tmp = para_tmp->next;
		BC_PT_DBG_CPL(l_mdl_id, "Cli Para No2: op_id=%u\r\n", op_id);
		switch(op_id)
		{
			case 21:
				trans_fun = BC_FILETRANS_BACKUP_CONFIG;
				break;
			case 22:
				trans_fun = BC_FILETRANS_BACKUP_LOG;
				break;
			default:
				return CLI_CMD_FAIL_PRT_NEWLINE;
				break;
		}
	}

	if(proto_type == BC_FILETRANS_TYPE_FTP)
	{
		//验证用户名与密码
	}
	
	ret = __do_filetrans_upgrade(sid, para_tmp, ptrUserData, trans_fun,proto_type);
	if(ret != BC_ERR_OK)
	{
		CLI_API_Printf(sid, "\r\n Failed to transmission set, ret = 0x%x!\r\n", ret);
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}

	CLI_DBG_LEAVE(l_mdl_id);
	
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

/******************************************************************************\
  Function   : __filetrans_upgrade
  Description: 设置且升级
  Return     : bool true: 成功  false:非零失败
  Others     : 
\******************************************************************************/
static cli_cmd_ret_e __filetrans_upgrade_usb
    (
    IN const UI32_T	sid,
    IN cli_value_t		*ptrCliValue,
    IN void			*ptrUserData
    )
{
	bc_err_e ret = BC_ERR_OK;
	bc_filetrans_function_e trans_fun;
	bc_filetrans_proto_type_e proto_type;
	cli_value_t *para_tmp = ptrCliValue;
	UI32_T op_id = *(UI32_T *)para_tmp->value;
	para_tmp = para_tmp->next;
	CLI_DBG_ENTER(l_mdl_id);
	BC_PT_DBG_CPL(l_mdl_id, "Cli Para No1: op_id=%u\r\n", op_id);

#if 1
	CLI_API_Printf(sid, "\r\n*** not supported warning ***\r\n", ret);
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
#endif

	if(op_id == 5)
	{
		op_id = *(UI32_T *)para_tmp->value;
		para_tmp = para_tmp->next;
		BC_PT_DBG_CPL(l_mdl_id, "Cli Para No2: op_id=%u\r\n", op_id);
		switch(op_id)
		{
			case 14:
				trans_fun = BC_FILETRANS_OLT;
				break;
			case 16:
				trans_fun = BC_FILETRANS_CONFIG;
				break;
			default:
				return CLI_CMD_FAIL_PRT_NEWLINE;
				break;
		}
	}
	else
	{
		op_id = *(UI32_T *)para_tmp->value;
		para_tmp = para_tmp->next;
		BC_PT_DBG_CPL(l_mdl_id, "Cli Para No2: op_id=%u\r\n", op_id);
		switch(op_id)
		{
			case 21:
				trans_fun = BC_FILETRANS_BACKUP_CONFIG;
				break;
			case 22:
				trans_fun = BC_FILETRANS_BACKUP_LOG;
				break;
			default:
				return CLI_CMD_FAIL_PRT_NEWLINE;
				break;
		}
	}

	proto_type = BC_FILETRANS_TYPE_USB;
	
	ret = __do_filetrans_upgrade(sid, para_tmp, ptrUserData, trans_fun,proto_type);
	if(ret != BC_ERR_OK)
	{
		CLI_API_Printf(sid, "\r\n Failed to transmission set, ret = 0x%x!\r\n", ret);
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}

	CLI_DBG_LEAVE(l_mdl_id);
	
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

static cli_cmd_ret_e __filetrans_upgrade_usb_dbg
    (
    IN const UI32_T	sid,
    IN cli_value_t		*ptrCliValue,
    IN void			*ptrUserData
    )
{
	bc_err_e ret = BC_ERR_OK;
	bc_filetrans_function_e trans_fun;
	bc_filetrans_proto_type_e proto_type;
	cli_value_t *para_tmp = ptrCliValue;
	UI32_T op_id = *(UI32_T *)para_tmp->value;
	para_tmp = para_tmp->next;
	CLI_DBG_ENTER(l_mdl_id);
	BC_PT_DBG_CPL(l_mdl_id, "Cli Para No1: op_id=%u\r\n", op_id);
	
	if(op_id == 5)
	{
		op_id = *(UI32_T *)para_tmp->value;
		para_tmp = para_tmp->next;
		BC_PT_DBG_CPL(l_mdl_id, "Cli Para No2: op_id=%u\r\n", op_id);
		switch(op_id)
		{
			case 11:
				trans_fun = BC_FILETRANS_KERNEL;
				break;
			case 12:
				trans_fun = BC_FILETRANS_ROOT_FS;
				break;
			case 13:
				trans_fun = BC_FILETRANS_USER_FS;
				break;
			case 14:
				trans_fun = BC_FILETRANS_OLT;
				break;
			case 16:
				trans_fun = BC_FILETRANS_CONFIG;
				break;
			case 17:
				trans_fun = BC_FILETRANS_DBTB;
				CLI_API_Printf(sid, "\r\n No support!\r\n");
				return CLI_CMD_SUCCESS_PRT_NEWLINE;
			case 18:
				trans_fun = BC_FILETRANS_UBOOT;
				CLI_API_Printf(sid, "\r\n No support!\r\n");
				return CLI_CMD_SUCCESS_PRT_NEWLINE;
				break;
			default:
				return CLI_CMD_FAIL_PRT_NEWLINE;
				break;
		}
	}
	else
	{
		op_id = *(UI32_T *)para_tmp->value;
		para_tmp = para_tmp->next;
		BC_PT_DBG_CPL(l_mdl_id, "Cli Para No2: op_id=%u\r\n", op_id);
		switch(op_id)
		{
			case 21:
				trans_fun = BC_FILETRANS_BACKUP_CONFIG;
				break;
			case 22:
				trans_fun = BC_FILETRANS_BACKUP_LOG;
				break;
			default:
				return CLI_CMD_FAIL_PRT_NEWLINE;
				break;
		}
	}

	proto_type = BC_FILETRANS_TYPE_USB;
	
	ret = __do_filetrans_upgrade(sid, para_tmp, ptrUserData, trans_fun,proto_type);
	if(ret != BC_ERR_OK)
	{
		CLI_API_Printf(sid, "\r\n Failed to transmission set, ret = 0x%x!\r\n", ret);
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}

	CLI_DBG_LEAVE(l_mdl_id);
	
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}
#endif

static cli_cmd_ret_e __filetrans_switch_over
    (
    IN const UI32_T	sid,
    IN cli_value_t		*ptrCliValue,
    IN void			*ptrUserData
    )
{
	bc_err_e ret = BC_ERR_OK;
	cli_value_t *para_tmp = ptrCliValue;
	UI32_T op_id = *(UI32_T *)para_tmp->value;

#if 0
	switch(op_id)
	{
		case 1://kernel
			ret = bc_filetrans_switch_over_kernel();
			if(ret != BC_ERR_OK)
			{
				CLI_API_Printf(sid, "\r\n Failed to bc_filetrans_switch_over_kernel, ret = 0x%x!\r\n", ret);
				return CLI_CMD_FAIL_PRT_NEWLINE;
			}
			break;
		case 2://file-system
			ret = bc_filetrans_switch_over_file_system();
			if(ret != BC_ERR_OK)
			{
				CLI_API_Printf(sid, "\r\n Failed to bc_filetrans_switch_over_file_system, ret = 0x%x!\r\n", ret);
				return CLI_CMD_FAIL_PRT_NEWLINE;
			}
			break;
		default:
			break;
	}
#else
	CLI_API_Printf(sid, "\r\n*** not supported warning ***\r\n", ret);
#endif
	return CLI_CMD_SUCCESS_PRT_NEWLINE;	
}


void bc_cli_cmd_filetrans_reg(void)
{
	CLI_DBG_ENTER(l_mdl_id);
	BOOL_T ret_reg;

/*
	download or upload
*/
#if 1	
	ret_reg = bc_cli_reg_cmd(
		CLI_MOD_PRIVI_PATH
		"/usb "		 	"#Usb transfer information #""#USB升级#"
		"{ "
			"download(5) "	"#Download files #""#下载文件#"
			"{ "
				"dev-image(14) "		"#Image file of DEV.#""#dev镜像文件#"
				"| "
				"config-file(16) "		"#User configuration file.#""#配置用户配置文件相关参数#"
			"} "
			"| "
			"upload(6) "		"#Upload files.#""#上传文件#"
			"{ "
				"config-file(21) "		"#User configuration file.#""#配置用户配置文件相关参数。#"
				"| "
				"log-file(22) "			"#System log file.#""#系统日志#"
			"} "
		"} "
		"<file-name> "	"#Source name#""#源文件名#",
		__filetrans_upgrade_usb,
		CLI_ACC_LVL_BASIC,
		"usb.",
		"USB对文件升级。",
		NULL);
	CLI_DBG_CPL(l_mdl_id, "ret=%d\r\n", ret_reg);

	ret_reg = bc_cli_reg_cmd(
		CLI_MOD_PRIVI_PATH
		"/tftp "		 	"#Tftp transfer information #""#TFTP传输协议升级#"
		"{ "
			"download(1) "	"#Download files #""#下载文件#"
			"{ "
				"dev-image(14) "		"#Image file of DEV.#""#dev镜像文件#"
				"| "
				"config-file(16) "		"#User configuration file.#""#配置用户配置文件相关参数#"
			"} "
			"| "
			"upload(2) "		"#Upload files.#""#上传文件#"
			"{ "
				"config-file(21) "		"#User configuration file.#""#配置用户配置文件相关参数。#"
				"| "
				"log-file(22) "			"#System log file.#""#系统日志#"
			"} "
		"} "
		"<file-name> "	"#Source name#""#源文件名#"
		"<ip-address>"		"#FORMAT:DDD.DDD.DDD.DDD (DDD<255) #""#FORMAT:DDD.DDD.DDD.DDD (DDD<255) #", 
		__filetrans_upgrade,
		CLI_ACC_LVL_BASIC,
		"tftp.",
		"TFTP传输协议对文件升级。",
		NULL);
	CLI_DBG_CPL(l_mdl_id, "ret=%d\r\n", ret_reg);

	ret_reg = bc_cli_reg_cmd(
		CLI_MOD_PRIVI_PATH
		"/ftp "		 	"#Ftp transfer information #""#Ftp传输协议升级#"
		"{ "
			"download(3) "	"#Download files #""#下载文件#"
			"{ "
				"dev-image(14) "		"#Image file of DEV #""#dev镜像文件#"
				"| "
				"config-file(16) "		"#User configuration file #""#配置用户配置文件相关参数#"
			"} "
			"| "
			"upload(4) "		"#Upload files #""#上传文件#"
			"{ "
				"config-file(21) "		"#User configuration file #""#配置用户配置文件相关参数。#"
				"| "
				"log-file(22) "			"#System log file #""#系统日志#"
			"} "
		"} "
		"<username>"		"#ftp user name #""#用户名#"
		"<password>"		"#ftp password #""#密码#"
		"<file-name> "	"#Source name#""#源文件名#"
		"<ip-address>"		"#FORMAT:DDD.DDD.DDD.DDD (DDD<255) #""#FORMAT:DDD.DDD.DDD.DDD (DDD<255) #", 
		__filetrans_upgrade,
		CLI_ACC_LVL_BASIC,
		"ftp.",
		"FTP传输协议对文件升级。",
		NULL);
	CLI_DBG_CPL(l_mdl_id, "ret=%d\r\n", ret_reg);
#endif


/*
	DEBUG
	download or upload
*/
#if 1
	ret_reg = bc_cli_reg_cmd(
		CLI_MOD_DEBUG_PATH
		"/usb "		 	"#Usb transfer information #""#USB升级#"
		"{ "
			"download(5) "	"#Download files #""#下载文件#"
			"{ "
				"kernel(11) " 			"#System kernel #""#系统内核#"
				"| "
				"root-file-system(12) "		"#Root file system.#""#根文件系统 #"
				"| "
				"user-file-system(13) "		"#User file system.#""#用户文件系统#"
				"| "
				"dev-image(14) "		"#Image file of DEV.#""#dev镜像文件#"
				"| "
				"config-file(16) "		"#User configuration file.#""#配置用户配置文件相关参数#"
				"| "
				"dbtb(17) "			"#dbtb.#""#dbtb #"
				"| "
				"uboot(18) "			"#uboot.#""#uboot #"
			"} "
			"| "
			"upload(6) "		"#Upload files.#""#上传文件#"
			"{ "
				"config-file(21) "		"#User configuration file.#""#配置用户配置文件相关参数。#"
				"| "
				"log-file(22) "			"#System log file.#""#系统日志#"
			"} "
		"} "
		"<file-name> "	"#Source name#""#源文件名#",
		__filetrans_upgrade_usb_dbg,
		CLI_ACC_LVL_BASIC,
		"usb.",
		"USB对文件升级。",
		NULL);
	CLI_DBG_CPL(l_mdl_id, "ret=%d\r\n", ret_reg);

	ret_reg = bc_cli_reg_cmd(
		CLI_MOD_DEBUG_PATH
		"/tftp "		 	"#Tftp transfer information #""#TFTP传输协议升级#"
		"{ "
			"download(1) "	"#Download files #""#下载文件#"
			"{ "
				"kernel(11) " 			"#System kernel #""#系统内核#"
				"| "
				"root-file-system(12) "		"#Root file system.#""#根文件系统 #"
				"| "
				"user-file-system(13) "		"#User file system.#""#用户文件系统#"
				"| "
				"dev-image(14) "		"#Image file of DEV.#""#dev镜像文件#"
				"| "
				"config-file(16) "		"#User configuration file.#""#配置用户配置文件相关参数#"
				"| "
				"dbtb(17) "			"#dbtb.#""#dbtb #"
				"| "
				"uboot(18) "			"#uboot.#""#uboot #"
			"} "
			"| "
			"upload(2) "		"#Upload files.#""#上传文件#"
			"{ "
				"config-file(21) "		"#User configuration file.#""#配置用户配置文件相关参数。#"
				"| "
				"log-file(22) "			"#System log file.#""#系统日志#"
			"} "
		"} "
		"<file-name> "	"#Source name#""#源文件名#"
		"<ip-address>"		"#FORMAT:DDD.DDD.DDD.DDD (DDD<255) #""#FORMAT:DDD.DDD.DDD.DDD (DDD<255) #", 
		__filetrans_upgrade_dbg,
		CLI_ACC_LVL_BASIC,
		"tftp.",
		"TFTP传输协议对文件升级。",
		NULL);
	CLI_DBG_CPL(l_mdl_id, "ret=%d\r\n", ret_reg);

	ret_reg = bc_cli_reg_cmd(
		CLI_MOD_DEBUG_PATH
		"/ftp "		 	"#Ftp transfer information #""#Ftp传输协议升级#"
		"{ "
			"download(3) "	"#Download files #""#下载文件#"
			"{ "
				"kernel(11) " 			"#System kernel #""#系统内核#"
				"| "
				"root-file-system(12) "		"#Root file system #""#根文件系统 #"
				"| "
				"user-file-system(13) "		"#User file system #""#用户文件系统#"
				"| "
				"dev-image(14) "		"#Image file of DEV #""#dev镜像文件#"
				"| "
				"config-file(16) "		"#User configuration file #""#配置用户配置文件相关参数#"
				"| "
				"dbtb(17) "			"#dbtb #""#dbtb #"
				"| "
				"uboot(18) "			"#uboot #""#uboot #"
			"} "
			"| "
			"upload(4) "		"#Upload files #""#上传文件#"
			"{ "
				"config-file(21) "		"#User configuration file #""#配置用户配置文件相关参数。#"
				"| "
				"log-file(22) "			"#System log file #""#系统日志#"
			"} "
		"} "
		"<username>"		"#ftp user name #""#用户名#"
		"<password>"		"#ftp password #""#密码#"
		"<file-name> "	"#Source name#""#源文件名#"
		"<ip-address>"		"#FORMAT:DDD.DDD.DDD.DDD (DDD<255) #""#FORMAT:DDD.DDD.DDD.DDD (DDD<255) #", 
		__filetrans_upgrade_dbg,
		CLI_ACC_LVL_BASIC,
		"ftp.",
		"FTP传输协议对文件升级。",
		NULL);
	CLI_DBG_CPL(l_mdl_id, "ret=%d\r\n", ret_reg);

	ret_reg = bc_cli_reg_cmd(
		CLI_MOD_DEBUG_PATH
		"/switch-over "		 "#Switch over system or partition.#""#切换主/备系统、分区、设备等。#"
		"{"
			"kernel(1)"		"#System kernel#""#内核#"
			"|"
			"file-system(2)"	"#File system#""#文件系统#"
		"}",
		__filetrans_switch_over,
		CLI_ACC_LVL_BASIC,
		"switch-over.",
		"切换。",
		NULL);

	CLI_DBG_CPL(l_mdl_id, "ret=%d\r\n", ret_reg);
#endif

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
