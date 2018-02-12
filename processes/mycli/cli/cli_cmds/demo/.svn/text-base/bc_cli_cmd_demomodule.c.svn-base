////////////////////////////////////////////////////////////////////////////////
// 																			  //
// 							 	头   文   件								  //
// 																			  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_modules.h"
#include "bc_cli_kernel_cfg.h"

#include "bc_cli_type.h"
#include "bc_cli_paratype.h"

#include "bc_cli.h"



////////////////////////////////////////////////////////////////////////////////
//																			  //
//						外 部 变 量、 函 数 引 用							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//																			  //
//						结   构   体   宏   定   义							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
#define CLI_MOD_DEMOPORT_NAME		"demointerface"
#define CLI_MOD_DEMOPORT_DESC		"demo interface mode"
#define CLI_MOD_DEMOPORT_PATH  		"/demoif"
#define CLI_MOD_DEMOPORT_PROM 		"(democfg-if-%c%u/%u)"

#define CLI_MOD_DEMOONU_NAME		"demoonu"
#define CLI_MOD_DEMOONU_DESC		"demo onu mode"
#define CLI_MOD_DEMOONU_PATH  		"/demoonu"
#define CLI_MOD_DEMOONU_PROM 		"(democfg-onu-%u/%u:%u)"

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



////////////////////////////////////////////////////////////////////////////////
//																			  //
//							全 局 变 量 定 义								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
static unsigned int 	l_mdl_id = BC_MODULE_CLI_CMD_DEMOMODULE;



////////////////////////////////////////////////////////////////////////////////
//																			  //
//								函  数  声  明								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//																			  //
//								函  数  定  义								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
/**************************************************************************
FUNCTION NAME:
	__dm_show_demo

DESCRIPTION:
	__dm_show_demo

INPUT:
	sid			: created session ID by CLI kernel
	cli_para	: cli command parameters
	user_data	: user data with register this command parameter

OUTPUT:
	NA

RETURN:
	Print information type after executed this command

NOTES:
	NA

HISTORY:
	NA

**************************************************************************/
static I32_T __dm_show_demo
    (
    IN const UI32_T 	sid,
    IN cli_value_t 		*cli_para,
    IN void 			*user_data
    )
{
	CLI_DBG_ENTER(l_mdl_id);

	CLI_API_Printf(sid, "\r\n test - Demo Module\r\n");

	CLI_DBG_LEAVE(l_mdl_id);
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}



/**************************************************************************
FUNCTION NAME:
	__dm_check_paratype_ip_address

DESCRIPTION:
	__dm_check_paratype_ip_address

INPUT:
	sid			: created session ID by CLI kernel
	cli_para	: cli command parameters
	user_data	: user data with register this command parameter

OUTPUT:
	NA

RETURN:
	Print information type after executed this command

NOTES:
	NA

HISTORY:
	NA

**************************************************************************/
static I32_T __dm_check_paratype_ip_address
    (
    IN const UI32_T 	sid,
    IN cli_value_t 		*cli_para,
    IN void 			*user_data
    )
{
	CLI_DBG_ENTER(l_mdl_id);
	PRT_CLI_PARA(l_mdl_id, cli_para);

	if (NULL == cli_para)
	{
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}

	CLI_API_Printf(sid, "Function: %s\r\n", __FUNCTION__);
	CLI_API_Printf(sid, "Session : id=%d, User Data=%d\r\n", sid, (int)user_data);
	CLI_API_Printf(sid, "Para Val: type=%d, name=%s, IP=0x%08X, priority=%d, next=0x%08X\r\n",
						cli_para->type, cli_para->name, *(UI32_T *)cli_para->value, cli_para->priority, (int)cli_para->next);

	CLI_DBG_LEAVE(l_mdl_id);
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}



/**************************************************************************
FUNCTION NAME:
	__dm_check_paratype_module_id

DESCRIPTION:
	__dm_check_paratype_module_id

INPUT:
	sid			: created session ID by CLI kernel
	cli_para	: cli command parameters
	user_data	: user data with register this command parameter

OUTPUT:
	NA

RETURN:
	Print information type after executed this command

NOTES:
	NA

HISTORY:
	NA

**************************************************************************/
static I32_T __dm_check_paratype_module_id
    (
    IN const UI32_T 	sid,
    IN cli_value_t 		*cli_para,
    IN void 			*user_data
    )
{
	CLI_DBG_ENTER(l_mdl_id);
	PRT_CLI_PARA(l_mdl_id, cli_para);

	if (NULL == cli_para)
	{
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}

	CLI_API_Printf(sid, "Function: %s\r\n", __FUNCTION__);
	CLI_API_Printf(sid, "Session : id=%d, User Data=%d\r\n", sid, (int)user_data);
	CLI_API_Printf(sid, "Para Val: type=%d, name=%s, module-id=0x%08X, priority=%d, next=0x%08X\r\n",
						cli_para->type, cli_para->name, *(UI32_T *)cli_para->value, cli_para->priority, (int)cli_para->next);

	CLI_DBG_LEAVE(l_mdl_id);
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}



/**************************************************************************
FUNCTION NAME:
	__dm_check_paratype_para

DESCRIPTION:
	__dm_check_paratype_para

INPUT:
	sid			: created session ID by CLI kernel
	cli_para	: cli command parameters
	user_data	: user data with register this command parameter

OUTPUT:
	NA

RETURN:
	Print information type after executed this command

NOTES:
	NA

HISTORY:
	NA

**************************************************************************/
static I32_T __dm_check_paratype_para
    (
    IN const UI32_T 	sid,
    IN cli_value_t 		*cli_para,
    IN void 			*user_data
    )
{
	CLI_DBG_ENTER(l_mdl_id);
	PRT_CLI_PARA(l_mdl_id, cli_para);

	CLI_API_Printf(sid, "Function: %s\r\n", __FUNCTION__);
	CLI_API_Printf(sid, "Session : id=%d, User Data=%d\r\n", sid, (int)user_data);
	CLI_API_Printf(sid, "Para Val: type=%d, name=%s, value=0x%08X, priority=%d, next=0x%08X\r\n",
						cli_para->type, cli_para->name, *(UI32_T *)cli_para->value, cli_para->priority, (int)cli_para->next);

	switch (cli_para->type)
	{
	case CLI_TYPES_IPADDR:
		__dm_check_paratype_ip_address(sid, cli_para, user_data);
		break;

	case CLI_TYPES_HEX:
		__dm_check_paratype_module_id(sid, cli_para, user_data);
		break;

	default:
		CLI_API_Printf(sid, "Unknown para type.\r\n");
		return CLI_CMD_FAIL_PRT_NEWLINE;
		break;
	}

	CLI_DBG_LEAVE(l_mdl_id);
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}



/**************************************************************************
FUNCTION NAME:
	__dm_enter_if_mode

DESCRIPTION:
	Enter demo interface mode.

INPUT:
	sid			: created session ID by CLI kernel
	cli_para	: cli command parameters
	user_data	: user data with register this command parameter

OUTPUT:
	NA

RETURN:
	Print information type after executed this command

NOTES:
	NA

HISTORY:
	NA

**************************************************************************/
static I32_T __dm_enter_if_mode(
	IN const UI32_T 	sid,
	IN cli_value_t 		*cli_para,
	IN void 			*user_data)
{
	BC_PT_FUN_ENTER(l_mdl_id);

	cli_value_t 		*para_tmp = cli_para;
	char 				prompt[CLI_DIR_PROMPT_MAX + 1];
	cli_pid_t 			port_if;

	UNUSED(user_data);

	memcpy(&port_if, (char *)para_tmp->value, sizeof(port_if));
	BC_PT_DBG_CPL(l_mdl_id, "Cli Para: type=%u slot=%u, port=%u\r\n", port_if.port_type, port_if.slot_id, port_if.port_id);

	memset(prompt, 0, CLI_DIR_PROMPT_MAX + 1);
	sprintf(prompt, CLI_MOD_DEMOPORT_PROM, (port_if.port_type == CLI_PORT_TYPE_SNI) ? 's' : 'p', port_if.slot_id, port_if.port_id);

	if (bc_cli_set_cmdpath(sid, CLI_MOD_DEMOPORT_PATH, prompt, cli_para))
	{
		return CLI_CMD_SUCCESS_PRT_NEWLINE;
	}
	else
	{
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
}



/**************************************************************************
FUNCTION NAME:
	__dm_enter_onu_mode

DESCRIPTION:
	Enter demo onu mode.

INPUT:
	sid			: created session ID by CLI kernel
	cli_para	: cli command parameters
	user_data	: user data with register this command parameter

OUTPUT:
	NA

RETURN:
	Print information type after executed this command

NOTES:
	NA

HISTORY:
	NA

**************************************************************************/
static I32_T __dm_enter_onu_mode(
	IN const UI32_T 	sid,
	IN cli_value_t 		*cli_para,
	IN void 			*user_data)
{
	BC_PT_FUN_ENTER(l_mdl_id);

	cli_value_t 		*para_tmp = cli_para;
	char 				prompt[CLI_DIR_PROMPT_MAX + 1];
	cli_onuid_t 		onu_id;

	UNUSED(user_data);

	memcpy(&onu_id, (char *)para_tmp->value, sizeof(onu_id));
	BC_PT_DBG_CPL(l_mdl_id, "Cli Para: slot=%u, port=%u, llid=%u\r\n", onu_id.slot_id, onu_id.port_id, onu_id.llid);

	memset(prompt, 0, CLI_DIR_PROMPT_MAX + 1);
	sprintf(prompt, CLI_MOD_DEMOONU_PROM, onu_id.slot_id, onu_id.port_id, onu_id.llid);

	if (bc_cli_set_cmdpath(sid, CLI_MOD_DEMOONU_PATH, prompt, cli_para))
	{
		return CLI_CMD_SUCCESS_PRT_NEWLINE;
	}
	else
	{
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
}



/**************************************************************************
FUNCTION NAME:
	__dm_get_mode_para

DESCRIPTION:
	Get the para of the current mode.

INPUT:
	sid			: created session ID by CLI kernel
	cli_para	: cli command parameters
	user_data	: user data with register this command parameter

OUTPUT:
	NA

RETURN:
	Print information type after executed this command

NOTES:
	NA

HISTORY:
	NA

**************************************************************************/
static I32_T __dm_get_mode_para(
	IN const UI32_T 	sid,
	IN cli_value_t 		*cli_para,
	IN void 			*user_data)
{
	BC_PT_FUN_ENTER(l_mdl_id);

	char				*path = NULL;
	cli_value_t 		*para_tmp = NULL;
	cli_pid_t 			port_if;

	UNUSED(cli_para);
	UNUSED(user_data);

	path = bc_cli_get_cmdpath(sid);
	CLI_API_Printf(l_mdl_id, "Command path: %s\r\n", path);

	if (0 != STRCMP(path, CLI_MOD_DEMOPORT_PATH))
	{
		CLI_API_Printf(l_mdl_id, "The mode is not \"demo interface mode\"!!!\r\n");
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}

	CLI_API_Printf(l_mdl_id, "Current mode is %s - %s.\r\n", CLI_MOD_DEMOPORT_NAME, CLI_MOD_DEMOPORT_DESC);

	para_tmp = bc_cli_get_path_parameter(sid);
	if (NULL == para_tmp)
	{
		CLI_API_Printf(l_mdl_id, "Failed to get parameter!!!\r\n");
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}

	memcpy(&port_if, (char *)para_tmp->value, sizeof(port_if));
	CLI_API_Printf(l_mdl_id, "Current mode parameter: type=%u slot=%u, port=%u\r\n", port_if.port_type, port_if.slot_id, port_if.port_id);

	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}



/**************************************************************************
FUNCTION NAME:
	bc_cli_dm_cmd_reg

DESCRIPTION:
	bc_cli_dm_cmd_reg

INPUT:
	NA

OUTPUT:
	NA

RETURN:
	NA

NOTES:
	NA

HISTORY:
	NA

**************************************************************************/
void bc_cli_dm_cmd_reg(void)
{
	CLI_DBG_ENTER(l_mdl_id);

	bc_cli_reg_cmd(
		CLI_MOD_GLOBAL_PATH
		"/show "				"#Display info#""#显示信息#"
		"demo "					"#Demo module#""#显示示例模块的信息#"
		,
		__dm_show_demo,
		CLI_ACC_LVL_DEBUG,
		"Display demo module information.",
		"显示示例模块信息。",
		NULL);

	bc_cli_reg_cmd(
		CLI_MOD_DEBUG_PATH
		"/demo "				"#Demo module#""#示例模块相关命令#"
		"para-type-convert "	"#Convert parameter type#""#转换参数类型#"
		"{ "
			"<ip-address> "
			"| "
			"<module-id> "
		"} "
		,
		__dm_check_paratype_para,
		CLI_ACC_LVL_DEBUG,
		"Check & Convert the parameter type.",
		"检验并转换参数类型。",
		NULL);

	bc_cli_reg_cmd(
		CLI_MOD_DEBUG_PATH
		"/demo "
		"mode-create "
		"interface "
		"<port-frame> "
		,
		__dm_enter_if_mode,
		CLI_ACC_LVL_DEBUG,
		"Enter demo interface mode.",
		"进入demo接口配置模式。",
		NULL);
	bc_cli_reg_mode(CLI_MOD_DEMOPORT_PATH, CLI_MOD_DEMOPORT_NAME, CLI_MOD_DEMOPORT_DESC);

	bc_cli_reg_cmd(
		CLI_MOD_DEMOPORT_PATH
		"/demo "
		"mode-create "
		"onu "
		"<onu-id> "
		,
		__dm_enter_onu_mode,
		CLI_ACC_LVL_DEBUG,
		"Enter demo onu mode.",
		"进入demo onu配置模式。",
		NULL);
	bc_cli_reg_mode(CLI_MOD_DEMOONU_PATH, CLI_MOD_DEMOONU_NAME, CLI_MOD_DEMOONU_DESC);

	bc_cli_reg_cmd(
		CLI_MOD_GLOBAL_PATH
		"/demo "
		"mode-para-get "
		,
		__dm_get_mode_para,
		CLI_ACC_LVL_DEBUG,
		"Get the para of the current mode.",
		"获取模式参数。",
		NULL);

	CLI_DBG_LEAVE(l_mdl_id);
	return;
}



/**************************************************************************
FUNCTION NAME:
	最后一个备份函数

DESCRIPTION:
	最后一个备份函数

INPUT:
	NA

OUTPUT:
	NA

RETURN:
	NA

NOTES:
	NA

HISTORY:
	NA

**************************************************************************/

