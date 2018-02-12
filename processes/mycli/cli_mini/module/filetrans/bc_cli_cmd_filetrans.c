/*******************************************************************************
  Copyright (C), 1988-2012, xxxxx Tech. Co., Ltd.
  [File name]  : bc_cli_cmd_filetrans.c
  [Author]     : wangbin
  [Version]    : 1.0
  [Date]       : 2015-01-20
  [Description]:

  [Others]     :

  [Function List]:  
    1. ....
    2. ....
  [History]:
	 D a t e    Modification 										  Initials
	---------- --------------                                        ----------
	2015-01-20  Created												  wangbin
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								头   文   件								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "bc_cli_type.h"
#include "bc_cli_paratype.h"
#include "bc_cli.h"

#include "bc_modules.h"
#include "bc_filetrans_def.h"
#include "utili_bit.h"

#include "bc_filetrans_file.h"



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
	if (ret != BC_ERR_OK)
	{
		CLI_API_Printf(l_mdl_id, "\r\n Failed to get info = %d!\r\n", ret);
		return ret;
	}
	
	CLI_API_Printf(l_mdl_id, "\r\n");
	while (BC_FILETRANS_STATUS_INPROGRESS == trans_cfg.status)
	{
		sleep(1);
		ret = bc_filetrans_get_info(trans_fun, &trans_cfg);
		if(ret != BC_ERR_OK)
		{
			CLI_API_Printf(l_mdl_id, "\r\n Failed to get info = %d!\r\n", ret);
			return ret;
		}
		
		CLI_API_Printf(l_mdl_id, "Downloading...%3u%% \r", trans_cfg.prog_value);
		fflush(stdout);
	}

	CLI_API_Printf(l_mdl_id, "Downloading...%3u%% \r\n", trans_cfg.prog_value);
	CLI_API_Printf(l_mdl_id, "\r\n");
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
	
	CLI_DBG_ENTER(l_mdl_id);

	memset(trans_cfg.usr_name, 0, sizeof(trans_cfg.usr_name));
	memset(trans_cfg.psswrd, 0, sizeof(trans_cfg.psswrd));
	trans_cfg.proto_type = proto_type;
	trans_cfg.trans_fun = trans_fun;
	
	strcpy(trans_cfg.src_file_name, (bc_char *)para_tmp->value);
	
	if(proto_type != BC_FILETRANS_TYPE_USB)
	{
		para_tmp = para_tmp->next;
		trans_cfg.ip = *(bc_uint32 *)para_tmp->value;
	}
	
	if((ret = bc_filetrans_set_download_file(trans_cfg)) != BC_ERR_OK)
	{			
		CLI_API_Printf(sid, "\r\n Failed to filetrans set download file, ret = 0x%x!\r\n", ret);
		return ret;
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
    IN const UI32_T	    sid,
    IN cli_value_t		*ptrCliValue,
    IN void			    *ptrUserData
    )
{
	UI32_T                    op_id = -1;
	bc_err_e                  ret = BC_ERR_OK;
	cli_value_t               *para_tmp = NULL;
	bc_filetrans_function_e   trans_fun;
	bc_filetrans_proto_type_e proto_type;
	
//	CLI_DBG_ENTER(l_mdl_id);
#if 1
	CLI_API_Printf(sid, "\r\n*** not supported warning ***\r\n", ret);
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
#endif

	para_tmp = ptrCliValue;
	op_id = *(UI32_T *)para_tmp->value;
	para_tmp = para_tmp->next;
	switch (op_id)
	{
	case 11:
		trans_fun = BC_FILETRANS_KERNEL;
		break;

	case 22:
		trans_fun = BC_FILETRANS_ROOT_FS;
		break;

	case 33:
		trans_fun  = BC_FILETRANS_USER_FS;
		break;

	case 44:
		trans_fun = BC_FILETRANS_OLT;
		break;

	case 55:
		trans_fun = BC_FILETRANS_DBTB;
		break;

	case 66:
		trans_fun = BC_FILETRANS_UBOOT;
		break;

	default:
		return CLI_CMD_FAIL_PRT_NEWLINE;
		break;
	}

	proto_type = BC_FILETRANS_TYPE_TFTP;
	ret = __do_filetrans_upgrade(sid, para_tmp, ptrUserData, trans_fun, proto_type);
	if(ret != BC_ERR_OK)
	{
		CLI_API_Printf(sid, "\r\n Failed to transmission set, ret = 0x%x!\r\n", ret);
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}

	CLI_DBG_LEAVE(l_mdl_id);
	
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}
#endif

static cli_cmd_ret_e __filetrans_upgrade_usb
    (
    IN const UI32_T	    sid,
    IN cli_value_t		*ptrCliValue,
    IN void			    *ptrUserData
    )
{
	UI32_T                    op_id = -1;
	bc_err_e                  ret = BC_ERR_OK;
	cli_value_t               *para_tmp = NULL;
	bc_filetrans_function_e   trans_fun;
	bc_filetrans_proto_type_e proto_type;
	
//	CLI_DBG_ENTER(l_mdl_id);

#if 1
	CLI_API_Printf(sid, "\r\n*** not supported warning ***\r\n", ret);
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
#endif

	para_tmp = ptrCliValue;
	op_id = *(UI32_T *)para_tmp->value;
	para_tmp = para_tmp->next;
	switch (op_id)
	{
	case 11:
		trans_fun = BC_FILETRANS_KERNEL;
		break;

	case 22:
		trans_fun = BC_FILETRANS_ROOT_FS;
		break;

	case 33:
		trans_fun  = BC_FILETRANS_USER_FS;
		break;

	case 44:
		trans_fun = BC_FILETRANS_OLT;
		break;

	case 55:
		trans_fun = BC_FILETRANS_DBTB;
		break;

	case 66:
		trans_fun = BC_FILETRANS_UBOOT;
		break;

	default:
		return CLI_CMD_FAIL_PRT_NEWLINE;
		break;
	}

	proto_type = BC_FILETRANS_TYPE_USB;
	ret = __do_filetrans_upgrade(sid, para_tmp, ptrUserData, trans_fun, proto_type);
	if(ret != BC_ERR_OK)
	{
		CLI_API_Printf(sid, "\r\n Failed to transmission set, ret = 0x%x!\r\n", ret);
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}

	CLI_DBG_LEAVE(l_mdl_id);
	
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

void bc_cli_cmd_filetrans_reg(void)
{
	BOOL_T ret_reg = 0;
	
	/*tftp*/
	ret_reg = bc_cli_reg_cmd(
		CLI_MOD_PRIVI_PATH
		"/tftp "		 				"#Tftp transfer information #""#TFTP传输协议升级#"
		"download "						"#Download files #""#下载文件#"
		"{ "
			"kernel(11) " 				"#System kernel #""#系统内核#"
			" | "
			"root-file-system(22) "		"#Root file system.#""#根文件系统 #"
			" | "
			"user-file-system(33) "		"#User file system.#""#用户文件系统#"
			" | "
			"olt-image(44) "				"#Image file of OLT.#""#olt镜像文件#"
			" | "
			"dbtb(55) "					"#dbtb.#""#dbtb #"
			" | "
			"uboot(66) "					"#uboot.#""#uboot #"
		"} "
		"<file-name> "					"#Object name (at the end of the string with a space character) #""#Object name (at the end of the string with a space character) #"
		"<ip-address> "					"#FORMAT:DDD.DDD.DDD.DDD (DDD<255) #""#FORMAT:DDD.DDD.DDD.DDD (DDD<255) #", 
		__filetrans_upgrade,
		CLI_ACC_LVL_BASIC,
		"tftp.",
		"TFTP传输协议对文件升级。",
		NULL);
	CLI_DBG_CPL(l_mdl_id, "ret=%d\r\n", ret_reg);

	/*usb*/
	ret_reg = bc_cli_reg_cmd(
		CLI_MOD_PRIVI_PATH
		"/usb "		 				"#Usb transfer information #""#USB升级#"
		"download "						"#Download files #""#下载文件#"
		"{ "
			"kernel(11) " 				"#System kernel #""#系统内核#"
			" | "
			"root-file-system(22) "		"#Root file system.#""#根文件系统 #"
			" | "
			"user-file-system(33) "		"#User file system.#""#用户文件系统#"
			" | "
			"olt-image(44) "				"#Image file of DEV.#""#dev镜像文件#"
			" | "
			"dbtb(55) "					"#dbtb.#""#dbtb #"
			" | "
			"uboot(66) "					"#uboot.#""#uboot #"
		"} "
		"<file-name> "					"#Object name (at the end of the string with a space character) #""#Object name (at the end of the string with a space character) #",
		__filetrans_upgrade_usb,
		CLI_ACC_LVL_BASIC,
		"usb.",
		"USB对文件升级。",
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
