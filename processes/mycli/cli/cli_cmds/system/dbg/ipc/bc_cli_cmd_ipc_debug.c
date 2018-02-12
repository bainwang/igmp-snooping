
#include "bc_modules.h"

#include "bc_cli_type.h"
#include "bc_cli_paratype.h"

#include "bc_cli.h"
#include "bc_session_ipc_client.h"
#include "bc_ipc_dev_debug.h"
#include "bc_ipc_client.h"
#include "bc_ipc_trans.h"
#include "bc_ipc_package.h"
#include "bc_ipc_dev_client.h"
#include "bc_cli_ipc_server.h"

static unsigned int 	l_mdl_id = BC_MODULE_CLI_CMD_IPCDEBUG;

#if 1

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   __session_dump
 *
 * DESCRIPTION:
 *   DUMP session list��
 *
 * INPUT:
 *   NA
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   0  -- �ɹ�
 *   -1 -- ʧ��
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2016-05-28 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
static I32_T __ipc_session_dump
    (
    IN const UI32_T 	sid,
    IN cli_value_t 	*ptrCliValue,
    IN void 			*ptrUserData
    )
{
	bc_err_e   ret  = BC_ERR_OK;
	
	CLI_DBG_ENTER(l_mdl_id);

	ret = bc_session_ipc_dump();
	if(ret != BC_ERR_OK)
	{
		CLI_API_Printf(sid, "\r\n Failed to dump session ret = %d!\r\n", ret);
	}

	CLI_DBG_LEAVE(l_mdl_id);
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

static I32_T __ipc_session_msg_back
    (
    IN const UI32_T 	sid,
    IN cli_value_t 	*ptrCliValue,
    IN void 			*ptrUserData
    )
{
	bc_uint32 session_id;
	
	session_id = *(bc_uint32 *)ptrCliValue->value;
	bc_session_ipc_msg_back(session_id);
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

static I32_T __ipc_session_release
    (
    IN const UI32_T 	sid,
    IN cli_value_t 	*ptrCliValue,
    IN void 			*ptrUserData
    )
{
	bc_uint32 session_id = bc_ipc_dev_client_session_get();
	
	bc_session_ipc_release(session_id);
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   __ipc_server_info_dump
 *
 * DESCRIPTION:
 *   DUMP ipc server info��
 *
 * INPUT:
 *   NA
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   0  -- �ɹ�
 *   -1 -- ʧ��
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2016-06-03 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
static I32_T __ipc_bcdevapp_server_dump
    (
    IN const UI32_T 	sid,
    IN cli_value_t 	*ptrCliValue,
    IN void 			*ptrUserData
    )
{
	bc_err_e   ret  = BC_ERR_OK;
	
	CLI_DBG_ENTER(l_mdl_id);

	ret = bc_ipc_dev_bcdevapp_server_dump();
	if(ret != BC_ERR_OK)
	{
		CLI_API_Printf(sid, "\r\n Failed to dump ipc server info ret = %d!\r\n", ret);
	}

	CLI_DBG_LEAVE(l_mdl_id);
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}


static I32_T __ipc_bcdevapp_trans_dump
    (
    IN const UI32_T 	sid,
    IN cli_value_t 	*ptrCliValue,
    IN void 			*ptrUserData
    )
{
	bc_err_e   ret  = BC_ERR_OK;
	
	CLI_DBG_ENTER(l_mdl_id);

	ret = bc_ipc_dev_bcdevapp_trans_dump();
	if(ret != BC_ERR_OK)
	{
		CLI_API_Printf(sid, "\r\n Failed to dump ipc server info ret = %d!\r\n", ret);
	}

	CLI_DBG_LEAVE(l_mdl_id);
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}


/*******************************************************************************
 *
 * FUNCTION NAME:
 *   __ipc_package_dump
 *
 * DESCRIPTION:
 *   DUMP package��
 *
 * INPUT:
 *   NA
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   0  -- ��ʼ���ɹ�
 *   -1 -- ��ʼ��ʧ��
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2016-06-03 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
static I32_T __ipc_bcdevapp_package_dump
    (
    IN const UI32_T 	sid,
    IN cli_value_t 	*ptrCliValue,
    IN void 			*ptrUserData
    )
{
	bc_err_e   ret  = BC_ERR_OK;
	
	CLI_DBG_ENTER(l_mdl_id);

	ret = bc_ipc_dev_server_package_dump();
	if(ret != BC_ERR_OK)
	{
		CLI_API_Printf(sid, "\r\n Failed to dump ipc server package ret = %d!\r\n", ret);
	}

	CLI_DBG_LEAVE(l_mdl_id);
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

static I32_T __ipc_bcdevapp_proc_dump
    (
    IN const UI32_T 	sid,
    IN cli_value_t 	*ptrCliValue,
    IN void 			*ptrUserData
    )
{
	bc_err_e   ret  = BC_ERR_OK;
	
	CLI_DBG_ENTER(l_mdl_id);

	ret = bc_ipc_dev_bcdevapp_proc_dump();
	if(ret != BC_ERR_OK)
	{
		CLI_API_Printf(sid, "\r\n Failed to dump ipc server package ret = %d!\r\n", ret);
	}

	CLI_DBG_LEAVE(l_mdl_id);
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

static I32_T __ipc_bcdevapp_proc_ofs_dump
    (
    IN const UI32_T 	sid,
    IN cli_value_t 	*ptrCliValue,
    IN void 			*ptrUserData
    )
{
	bc_uint32 ofs;
	ofs = *(bc_uint32 *)ptrCliValue->value;
	bc_ipc_dev_bcdevapp_proc_ofs_dump(ofs);
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

#endif
#if 1

static I32_T __ipc_bccliapp_client_dump
    (
    IN const UI32_T 	sid,
    IN cli_value_t 	*ptrCliValue,
    IN void 			*ptrUserData
    )
{
	bc_ipc_client_dump();
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

static I32_T __ipc_bccliapp_trans_dump
    (
    IN const UI32_T 	sid,
    IN cli_value_t 	*ptrCliValue,
    IN void 			*ptrUserData
    )
{
	bc_ipc_trans_dump();
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

static I32_T __ipc_bccliapp_package_dump
    (
    IN const UI32_T 	sid,
    IN cli_value_t 	*ptrCliValue,
    IN void 			*ptrUserData
    )
{
	bc_ipc_pacakge_dump();
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

static I32_T __ipc_bccliapp_bc_client_dump
    (
    IN const UI32_T 	sid,
    IN cli_value_t 	*ptrCliValue,
    IN void 			*ptrUserData
    )
{
	bc_ipc_dev_client_dump();
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

static I32_T __ipc_bccliapp_server_dump
    (
    IN const UI32_T 	sid,
    IN cli_value_t 	*ptrCliValue,
    IN void 			*ptrUserData
    )
{
	bc_uint32 que_id = 0xffff;

	if (ptrCliValue)
	{
		que_id = *(bc_uint32*)ptrCliValue->value;
		bc_ipc_cli_server_cnt_dump(que_id);
	}
	else
	{
		bc_ipc_cli_server_dump();
	}

	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

#endif

static void __bc_cli_ipc_cmd_session_reg(void)
{
	bc_cli_reg_cmd(
		CLI_MOD_DEBUG_PATH
		"/session "	             "#IPC debug info#""#IPC debug��Ϣ#"
		"dump "		 "#IPC session dump#""#��ʾIPC session�б���Ϣ#",
		__ipc_session_dump,
		CLI_ACC_LVL_DEBUG,
		"Display ipc session list information.",
		"��ʾIPC�Ự�б���Ϣ��",
		NULL);

	bc_cli_reg_cmd(
		CLI_MOD_DEBUG_PATH
		"/session "	             "#IPC debug info#""#IPC debug��Ϣ#"
		"msg <value> "		 "#IPC session dump#""#��ʾIPC session�б���Ϣ#",
		__ipc_session_msg_back,
		CLI_ACC_LVL_DEBUG,
		"Display ipc session list information.",
		"��ʾIPC�Ự�б���Ϣ��",
		NULL);

	bc_cli_reg_cmd(
		CLI_MOD_DEBUG_PATH
		"/session "	             "#IPC debug info#""#IPC debug��Ϣ#"
		"release "		 "#IPC session release#""#Release current session#",
		__ipc_session_release,
		CLI_ACC_LVL_DEBUG,
		"Release ipc session.",
		"�ͷ�IPC session��",
		NULL);
	
}

static void __bc_cli_ipc_cmd_bcdevapp_reg(void)
{
	bc_cli_reg_cmd(
		CLI_MOD_DEBUG_PATH
		"/ipc "	                 "#IPC debug info#""#IPC debug��Ϣ#"
		"ktoltapp server "		 "#IPC server info dump#""#��ʾIPC server�б���Ϣ#",
		__ipc_bcdevapp_server_dump,
		CLI_ACC_LVL_DEBUG,
		"Display ipc server list information.",
		"��ʾIPC Server�б���Ϣ��",
		NULL);

	bc_cli_reg_cmd(
		CLI_MOD_DEBUG_PATH
		"/ipc "	                 "#IPC debug info#""#IPC debug��Ϣ#"
		"ktoltapp trans "		 "#IPC server info dump#""#��ʾIPC server�б���Ϣ#",
		__ipc_bcdevapp_trans_dump,
		CLI_ACC_LVL_DEBUG,
		"Display ipc server list information.",
		"��ʾIPC Server�б���Ϣ��",
		NULL);

	bc_cli_reg_cmd(
		CLI_MOD_DEBUG_PATH
		"/ipc "	             "#IPC Debug info#""#IPC debug��Ϣ#"
		"ktoltapp package "		 "#IPC package dump#""#��ʾIPC package�б���Ϣ#",
		__ipc_bcdevapp_package_dump,
		CLI_ACC_LVL_DEBUG,
		"Display ipc package list information.",
		"��ʾIPC Package��Ϣ��",
		NULL);

	bc_cli_reg_cmd(
		CLI_MOD_DEBUG_PATH
		"/ipc "	             "#IPC Debug info#""#IPC debug��Ϣ#"
		"ktoltapp proc "		 "#IPC package dump#""#��ʾIPC package�б���Ϣ#",
		__ipc_bcdevapp_proc_dump,
		CLI_ACC_LVL_DEBUG,
		"Display ipc package list information.",
		"��ʾIPC Package��Ϣ��",
		NULL);

	bc_cli_reg_cmd(
		CLI_MOD_DEBUG_PATH
		"/ipc "	             "#IPC Debug info#""#IPC debug��Ϣ#"
		"ktoltapp proc_ofs <value> "		 "#IPC package dump#""#��ʾIPC package�б���Ϣ#",
		__ipc_bcdevapp_proc_ofs_dump,
		CLI_ACC_LVL_DEBUG,
		"Display ipc package list information.",
		"��ʾIPC Package��Ϣ��",
		NULL);
}

static void __bc_cli_ipc_cmd_bccliapp_reg(void)
{
	bc_cli_reg_cmd(
		CLI_MOD_DEBUG_PATH
		"/ipc "	             "#IPC Debug info#""#IPC debug��Ϣ#"
		"ktcliapp client "		 "#IPC package dump#""#��ʾIPC package�б���Ϣ#",
		__ipc_bccliapp_client_dump,
		CLI_ACC_LVL_DEBUG,
		"Display ipc package list information.",
		"��ʾIPC Package��Ϣ��",
		NULL);

	bc_cli_reg_cmd(
		CLI_MOD_DEBUG_PATH
		"/ipc "	             "#IPC Debug info#""#IPC debug��Ϣ#"
		"ktcliapp trans "		 "#IPC package dump#""#��ʾIPC package�б���Ϣ#",
		__ipc_bccliapp_trans_dump,
		CLI_ACC_LVL_DEBUG,
		"Display ipc package list information.",
		"��ʾIPC Package��Ϣ��",
		NULL);

	bc_cli_reg_cmd(
		CLI_MOD_DEBUG_PATH
		"/ipc "	             "#IPC Debug info#""#IPC debug��Ϣ#"
		"ktcliapp package "		 "#IPC package dump#""#��ʾIPC package�б���Ϣ#",
		__ipc_bccliapp_package_dump,
		CLI_ACC_LVL_DEBUG,
		"Display ipc package list information.",
		"��ʾIPC Package��Ϣ��",
		NULL);

	bc_cli_reg_cmd(
		CLI_MOD_DEBUG_PATH
		"/ipc "	             "#IPC Debug info#""#IPC debug��Ϣ#"
		"ktcliapp olt client "		 "#IPC package dump#""#��ʾIPC package�б���Ϣ#",
		__ipc_bccliapp_bc_client_dump,
		CLI_ACC_LVL_DEBUG,
		"Display ipc package list information.",
		"��ʾIPC Package��Ϣ��",
		NULL);


	bc_cli_reg_cmd(
		CLI_MOD_DEBUG_PATH
		"/ipc "	            
		"ktcliapp server [<uint>]",
		__ipc_bccliapp_server_dump,
		CLI_ACC_LVL_DEBUG,
		"",
		"",
		NULL);
	}

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   bc_cli_cmd_session_dump_reg
 *
 * DESCRIPTION:
 *   DUMP session list��
 *
 * INPUT:
 *   NA
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   0  -- ��ʼ���ɹ�
 *   -1 -- ��ʼ��ʧ��
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2016-05-28 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
void bc_cli_cmd_ipc_reg(void)
{
	__bc_cli_ipc_cmd_session_reg();

	__bc_cli_ipc_cmd_bcdevapp_reg();

	__bc_cli_ipc_cmd_bccliapp_reg();
}



