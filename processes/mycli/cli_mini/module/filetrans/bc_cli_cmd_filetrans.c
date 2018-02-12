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
//								ͷ   ��   ��								  //
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
 static unsigned int 	l_mdl_id = BC_MODULE_FILETRANS;



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




#if 1
/******************************************************************************\
  Function   : __filetrans_transmission_show
  Description: ��ʾ�����е���Ϣ
  Return     : bool true: �ɹ�  false:����ʧ��
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
  Description: �����ļ�
  Return     : bool true: �ɹ�  false:����ʧ��
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
  Description: ����������
  Return     : bool true: �ɹ�  false:����ʧ��
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
		"/tftp "		 				"#Tftp transfer information #""#TFTP����Э������#"
		"download "						"#Download files #""#�����ļ�#"
		"{ "
			"kernel(11) " 				"#System kernel #""#ϵͳ�ں�#"
			" | "
			"root-file-system(22) "		"#Root file system.#""#���ļ�ϵͳ #"
			" | "
			"user-file-system(33) "		"#User file system.#""#�û��ļ�ϵͳ#"
			" | "
			"olt-image(44) "				"#Image file of OLT.#""#olt�����ļ�#"
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
		"TFTP����Э����ļ�������",
		NULL);
	CLI_DBG_CPL(l_mdl_id, "ret=%d\r\n", ret_reg);

	/*usb*/
	ret_reg = bc_cli_reg_cmd(
		CLI_MOD_PRIVI_PATH
		"/usb "		 				"#Usb transfer information #""#USB����#"
		"download "						"#Download files #""#�����ļ�#"
		"{ "
			"kernel(11) " 				"#System kernel #""#ϵͳ�ں�#"
			" | "
			"root-file-system(22) "		"#Root file system.#""#���ļ�ϵͳ #"
			" | "
			"user-file-system(33) "		"#User file system.#""#�û��ļ�ϵͳ#"
			" | "
			"olt-image(44) "				"#Image file of DEV.#""#dev�����ļ�#"
			" | "
			"dbtb(55) "					"#dbtb.#""#dbtb #"
			" | "
			"uboot(66) "					"#uboot.#""#uboot #"
		"} "
		"<file-name> "					"#Object name (at the end of the string with a space character) #""#Object name (at the end of the string with a space character) #",
		__filetrans_upgrade_usb,
		CLI_ACC_LVL_BASIC,
		"usb.",
		"USB���ļ�������",
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
