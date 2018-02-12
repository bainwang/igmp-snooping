/*******************************************************************
MODULE NAME:
    CLI command belong to CLI kernel

FILE NAME:
    bc_cli_sys_cmd.c

VERSION:
    2.00

DESCRIPTION:
    CLI command belong to CLI kernel

NOTES:
    NA

HISTORY:
    Ver2.00:    2011.3.7 bain.wang@outlook.com new added

********************************************************************/

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              头   文   件                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "bc_platform_time.h"

#include "bc_cli_bnr.h"
#include "bc_cli_msg.h"
#include "bc_cli_paratype.h"
#include "bc_cli_dir.h"

#if CLI_COMMAND_LOGGING_INCLUDED
#include "bc_cli_log_cmd.h"
#endif

#include "bc_cli.h"
#include "bc_msg.h"
#include "bc_cli_type.h"
#include "bc_cli_vkey.h"
#include "bc_sys_ipc_client.h"
#include "bc_usermgmt.h"



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                      外 部 变 量、 函 数 引 用                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                      结   构   体   宏   定   义                           //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#define SYS_KEY_HELP_QUIT_CN	"#退出CLI#"
#define SYS_KEY_HELP_QUIT_EN	"#Quit CLI#"

#define DBG_PASSWD     			"binchie"
#define DBG_PASSWD_LEN          32



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                          全 局 变 量 定 义                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

static unsigned int 	l_mdl_id = BC_MODULE_CLI_KERNEL_SYS_CMD;

static bc_boolean		dbg_flag = FALSE;
static UI32_T      		usr_level = 0;



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              函  数  声  明                                //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              函  数  定  义                                //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

/**************************************************************************
FUNCTION NAME:
    __cli2_cmd_exit

DESCRIPTION:
    Exit from current mode.

INPUT:
    sid   		: created session ID by CLI kernel
    cli_para 	: cli command parameters
    user_data 	: user data with register this command parameter

OUTPUT:
    NA

RETURN:
    Print information type after executed this command

NOTES:

HISTORY:

**************************************************************************/
static I32_T __cli2_cmd_exit
    (
    IN const UI32_T     sid,
    IN cli_value_t 		*cli_para,
    IN void 			*user_data
    )
{
	UNUSED(cli_para);
	UNUSED(user_data);

	if (TRUE == dbg_flag)
	{
		bc_cli_set_usr_lvl(sid, usr_level);
	}

    if (FALSE == bc_cli_exit_curpath(sid))
    {
        /* current path is root, execute logout function */
        //bc_cli_close_sesn(sid, CLI_KP_LOGOUT);
    }

    return CLI_CMD_SUCCESS_PRT_NEWLINE;
}



/**************************************************************************
FUNCTION NAME:
    __cli2_cmd_end

DESCRIPTION:
    Exit to EXEC mode.

INPUT:
    sid   		: created session ID by CLI kernel
    cli_para 	: cli command parameters
    user_data 	: user data with register this command parameter

OUTPUT:
    NA

RETURN:
    Print information type after executed this command

NOTES:

HISTORY:

**************************************************************************/
static I32_T __cli2_cmd_end
    (
    IN const UI32_T     sid,
    IN cli_value_t 		*cli_para,
    IN void 			*user_data
    )
{
#if 0
    I8_T    			promptMsg[BNR_CPU_NAME_MAX_LEN + 1];
#else
	I8_T				*cur_path;
#endif

	UNUSED(cli_para);
	UNUSED(user_data);

	cur_path = bc_cli_get_cmdpath(sid);
	if ((0 == strcmp(CLI_MOD_MONITOR_PATH, cur_path)) || (0 == strcmp(CLI_MOD_PRIVI_PATH, cur_path)))
	{
		//CLI_API_Printf(sid, "Current mode ");
        return CLI_CMD_FAIL_PRT_NEWLINE;
	}

#if 0
    CLI_BNR_Get_Prompt(sid, promptMsg, BNR_CPU_NAME_MAX_LEN + 1);
    if (bc_cli_set_cmdpath(sid, CLI_MOD_MONITOR_PATH, promptMsg, NULL))
#else
	if (bc_cli_set_cmdpath(sid, CLI_MOD_PRIVI_PATH, CLI_MOD_PRIVI_PROM, NULL))
#endif
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
    __cli2_cmd_quit

DESCRIPTION:
    Exit from current mode.

INPUT:
    sid   		: created session ID by CLI kernel
    cli_para 	: cli command parameters
    user_data 	: user data with register this command parameter

OUTPUT:
    NA

RETURN:
    Print information type after executed this command

NOTES:

HISTORY:

**************************************************************************/
static I32_T __cli2_cmd_quit
    (
    IN const UI32_T     sid,
    IN cli_value_t 		*cli_para,
    IN void 			*user_data
    )
{
	UNUSED(cli_para);
	UNUSED(user_data);

    /* current path is root, execute logout function */
    bc_cli_close_sesn(sid, CLI_KP_LOGOUT);
	bc_usermgmt_logout();

	return CLI_CMD_SUCCESS_PRT_NONE;
}



/**************************************************************************
FUNCTION NAME:
    __cli2_cmd_clear_screen

DESCRIPTION:
    Clear screen.

INPUT:
    sid   		: created session ID by CLI kernel
    cli_para 	: cli command parameters
    user_data 	: user data with register this command parameter

OUTPUT:
    NA

RETURN:
    Print information type after executed this command

NOTES:

HISTORY:

**************************************************************************/
static I32_T __cli2_cmd_clear_screen
    (
    IN const UI32_T     sid,
    IN cli_value_t 		*cli_para,
    IN void 			*user_data
    )
{
    UNUSED(cli_para);
    UNUSED(user_data);

    bc_cli_clear_screen(sid);

    return CLI_CMD_SUCCESS_PRT_NONE;
}


/**************************************************************************
FUNCTION NAME:
    __cli2_cmd_config_hist

DESCRIPTION:
    Configure command history number.

INPUT:
    sid   		: created session ID by CLI kernel
    cli_para 	: cli command parameters
    user_data 	: user data with register this command parameter

OUTPUT:
    NA

RETURN:
    Print information type after executed this command

NOTES:

HISTORY:

**************************************************************************/
static I32_T __cli2_cmd_config_hist
    (
    IN const UI32_T sid,
    IN cli_value_t 	*cli_para,
    IN void 	 	*user_data
    )
{
    UI32_T  		hist_num;

    UNUSED(user_data);

    hist_num = *(UI32_T *) cli_para->value;

    if (bc_cli_set_hist_size(sid, hist_num))
    {
        return CLI_CMD_SUCCESS_PRT_PROMPT_NEWLINE;
    }
    else
    {
        return CLI_CMD_FAIL_PRT_PROMPT_NEWLINE;
    }
}



/**************************************************************************
FUNCTION NAME:
    __cli2_cmd_show_hist

DESCRIPTION:
    Used to display command history.

INPUT:
    sid   		: created session ID by CLI kernel
    cli_para 	: cli command parameters
    user_data 	: user data with register this command parameter

OUTPUT:
    NA

RETURN:
    Print information type after executed this command

NOTES:

HISTORY:

**************************************************************************/
static I32_T __cli2_cmd_show_hist
    (
    IN const UI32_T sid,
    IN cli_value_t 	*cli_para,
    IN void 		*user_data
    )
{
    I8_T			*histCmd_ptr;

    UNUSED(cli_para);
    UNUSED(user_data);

    histCmd_ptr = bc_cli_show_all_hist(sid, TRUE);

    while (histCmd_ptr)
    {
        CLI_API_Printf(sid, "\n\r%s", histCmd_ptr);
        histCmd_ptr = bc_cli_show_all_hist(sid, FALSE);
    }

    return CLI_CMD_SUCCESS_PRT_NEWLINE;
}



/**************************************************************************
FUNCTION NAME:
    __cli2_cmd_enable_paging

DESCRIPTION:
    Enable all cli paging function.

INPUT:
    sid   		: created session ID by CLI kernel
    cli_para 	: cli command parameters
    user_data 	: user data with register this command parameter

OUTPUT:
    NA

RETURN:
    Print information type after executed this command

NOTES:

HISTORY:

**************************************************************************/
static I32_T __cli2_cmd_enable_paging
    (
    IN const UI32_T sid,
    IN cli_value_t 	*cli_para,
    IN void 		*user_data
    )
{
    UNUSED(cli_para);
    UNUSED(user_data);

    bc_cli_set_paging(TRUE);

    return CLI_CMD_SUCCESS_PRT_PROMPT_NEWLINE;
}



/**************************************************************************
FUNCTION NAME:
    __cli2_cmd_disable_paging

DESCRIPTION:
    Disable all cli paging function.

INPUT:
    sid   		: created session ID by CLI kernel
    cli_para 	: cli command parameters
    user_data 	: user data with register this command parameter

OUTPUT:
    NA

RETURN:
    Print information type after executed this command

NOTES:

HISTORY:

**************************************************************************/
static I32_T __cli2_cmd_disable_paging
    (
    IN const UI32_T sid,
    IN cli_value_t 	*cli_para,
    IN void 		*user_data
    )
{
    UNUSED(cli_para);
    UNUSED(user_data);

    bc_cli_set_paging(FALSE);

    return CLI_CMD_SUCCESS_PRT_PROMPT_NEWLINE;
}



#if CLI_COMMAND_LOGGING_INCLUDED

/**************************************************************************
FUNCTION NAME:
    __cli2_cmd_enable_cmdLogState

DESCRIPTION:
    Enable command logging function.

INPUT:
    sid   		: created session ID by CLI kernel
    cli_para 	: cli command parameters
    user_data 	: user data with register this command parameter

OUTPUT:
    NA

RETURN:
    Print information type after executed this command

NOTES:

HISTORY:

**************************************************************************/
static I32_T __cli2_cmd_enable_cmdLogState
    (
    IN const UI32_T     sid,
    IN cli_value_t 		*cli_para,
    IN void 			*user_data
    )
{
    CLI_CMDLOG_STATE_T	cmdlog_state;

    NO_WARNING(sid);
    NO_WARNING(cli_para);
    NO_WARNING(user_data);

    CLI_CMDLOG_Get_State(&cmdlog_state);
    cmdlog_state.cmdlog_enable = TRUE;

    /* think about stacking */
    //ST_SYS_Set_CMDLogState(&cmdlog_state);

    return CLI_CMD_SUCCESS_PRT_PROMPT_NEWLINE;
}



/**************************************************************************
FUNCTION NAME:
    __cli2_cmd_disable_cmdLogState

DESCRIPTION:
    Disable command logging function.

INPUT:
    sid   		: created session ID by CLI kernel
    cli_para 	: cli command parameters
    user_data 	: user data with register this command parameter

OUTPUT:
    NA

RETURN:
    Print information type after executed this command

NOTES:

HISTORY:

**************************************************************************/
static I32_T __cli2_cmd_disable_cmdLogState
    (
    IN const UI32_T sid,
    IN cli_value_t 	*cli_para,
    IN void 		*user_data
    )
{
    CLI_CMDLOG_STATE_T   cmdlog_state;

    NO_WARNING(sid);
    NO_WARNING(cli_para);
    NO_WARNING(user_data);

    CLI_CMDLOG_Get_State(&cmdlog_state);
    cmdlog_state.cmdlog_enable = FALSE;

    /* think about stacking */
    //ST_SYS_Set_CMDLogState(&cmdlog_state);

    return CLI_CMD_SUCCESS_PRT_PROMPT_NEWLINE;
}



/**************************************************************************
FUNCTION NAME:
    __cli2_cmd_show_cmdLogState

DESCRIPTION:
    Show command logging state.

INPUT:
    sid   		: created session ID by CLI kernel
    cli_para 	: cli command parameters
    user_data 	: user data with register this command parameter

OUTPUT:
    NA

RETURN:
    Print information type after executed this command

NOTES:

HISTORY:

**************************************************************************/
static I32_T __cli2_cmd_show_cmdLogState
    (
    IN const UI32_T 	sid,
    IN cli_value_t 		*cli_para,
    IN void 			*user_data
    )
{
    CLI_CMDLOG_STATE_T 	cmdlog_state;

    NO_WARNING(cli_para);
    NO_WARNING(user_data);

    CLI_CMDLOG_Get_State(&cmdlog_state);

    if (cmdlog_state.cmdlog_enable)
    {
        CLI_API_Printf(sid, "\n\r Command Logging State:	Enabled");
    }
    else
    {
        CLI_API_Printf(sid, "\n\r Command Logging State:	Disabled");
    }

    return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

#endif



#if 0 // 保存配置

/**************************************************************************
FUNCTION NAME:
    __cli2_cmd_retrieve

DESCRIPTION:
    Generate cli configuration file.

INPUT:
    NA

OUTPUT:
    pFile   : the pointer of output file

RETURN:
    TRUE    : successful to generate configuration file
    FALSE   : generate failure

NOTES:

HISTORY:
    Added by bain.wang@outlook.com 2011.6.23

**************************************************************************/
static BOOL_T __cli2_cmd_retrieve
    (
    OUT cli_xfile_t *pFile
    )
{
#if CLI_COMMAND_LOGGING_INCLUDED
    CLI_CMDLOG_STATE_T cmdlog_state;
#endif

    /* the default state of clipaging is enable */
    if (bc_cli_get_paging())
    {
        CLI_CFG_Printf(pFile, "\n\renable clipaging");
    }
    else
    {
        CLI_CFG_Printf(pFile, "\n\rdisable clipaging");
    }

#if CLI_COMMAND_LOGGING_INCLUDED
    /* the default state of recording command logging is disable */
    CLI_CMDLOG_Get_State(&cmdlog_state);
    if (cmdlog_state.cmdlog_enable)
    {
        CLI_CFG_Printf(pFile, "\n\renable command logging");
    }
    else
    {
        CLI_CFG_Printf(pFile, "\n\rdisable command logging");
    }
#endif

    return TRUE;
}



/**************************************************************************
FUNCTION NAME:
    __cli2_cmd_enhance_retrieve

DESCRIPTION:
    Generate cli configuration file by input type.

INPUT:
    cfg_type: the type of current configuration file

OUTPUT:
    pFile   : the pointer of output file

RETURN:
    TRUE    : successful to generate configuration file
    FALSE   : generate failure

NOTES:
    Added for enhancing show config command(add {[effective | modified]} parameters).

HISTORY:
    Added by bain.wang@outlook.com 2011.6.23

**************************************************************************/
static BOOL_T __cli2_cmd_enhance_retrieve
    (
    OUT cli_xfile_t 	*pFile,
    IN CLI_CFG_TYPE_T   cfg_type
    )
{
#if CLI_COMMAND_LOGGING_INCLUDED
    CLI_CMDLOG_STATE_T cmdlog_state;
#endif

    /* the default state of clipaging is enable */
    if (bc_cli_get_paging())
    {
        if (cfg_type != CLI_CFG_TYPE_MODIFIED)
        {
            CLI_CFG_Printf(pFile, "\n\renable clipaging");
        }
    }
    else
    {
        CLI_CFG_Printf(pFile, "\n\rdisable clipaging");
    }

#if CLI_COMMAND_LOGGING_INCLUDED
    /* the default state of recording command logging is disable */
    CLI_CMDLOG_Get_State(&cmdlog_state);
    if (cmdlog_state.cmdlog_enable)
    {
        CLI_CFG_Printf(pFile, "\n\renable command logging");
    }
    else
    {
        if (cfg_type != CLI_CFG_TYPE_MODIFIED)
        {
            CLI_CFG_Printf(pFile, "\n\rdisable command logging");
        }
    }
#endif

    return TRUE;
}

#endif



/**************************************************************************
FUNCTION NAME:
	__sys_enter_privi_mode

DESCRIPTION:
	Enter privilege mode.

INPUT:
	sid			: created session ID by CLI kernel
	cli_para	: cli command parameters
	user_data	: user data with register this command parameter

OUTPUT:
	None

RETURN:
	Print information type after executed this command

NOTES:

HISTORY:

**************************************************************************/
static I32_T __sys_enter_privi_mode(
	IN const UI32_T sid,
	IN cli_value_t 	*cli_para,
	IN void 		*user_data)
{
	UNUSED(cli_para);
	UNUSED(user_data);

	if (bc_cli_set_cmdpath(sid, CLI_MOD_PRIVI_PATH, CLI_MOD_PRIVI_PROM, NULL))
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
	__sys_enter_cfg_mode

DESCRIPTION:
	Enter terminal configuration mode.

INPUT:
	sid			: created session ID by CLI kernel
	cli_para	: cli command parameters
	user_data	: user data with register this command parameter

OUTPUT:
	None

RETURN:
	Print information type after executed this command

NOTES:

HISTORY:

**************************************************************************/
static I32_T __sys_enter_cfg_mode(
	IN const UI32_T sid,
	IN cli_value_t 	*cli_para,
	IN void 		*user_data)
{
	UNUSED(cli_para);
	UNUSED(user_data);

	if (bc_cli_set_cmdpath(sid, CLI_MOD_GLBCFG_PATH, CLI_MOD_GLBCFG_PROM, NULL))
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
	__sys_enter_debug_mode

DESCRIPTION:
	Enter debug mode.

INPUT:
	sid			: created session ID by CLI kernel
	cli_para	: cli command parameters
	user_data	: user data with register this command parameter

OUTPUT:
	None

RETURN:
	Print information type after executed this command

NOTES:

HISTORY:

**************************************************************************/
static I32_T __sys_enter_debug_mode(
	IN const UI32_T sid,
	IN cli_value_t 	*cli_para,
	IN void 		*user_data)
{
	I8_T        pwd[DBG_PASSWD_LEN] = {0};
	I32_T   	trigger[] ={CLI_VKEY_CTRL_ENTER, CLI_VKEY_CR, 0};

	UNUSED(cli_para);
	UNUSED(user_data);

	CLI_API_Printf(sid, "Password: ");
	bc_cli_get_line(sid, sizeof("Password: "), CLI_OUTPUT_NORMAL, pwd, sizeof(pwd), 60, trigger);

	pwd[DBG_PASSWD_LEN - 1] = '\0';
	//CLI_API_Printf(sid, "\n%s, strlen(pwd) = %d\r\n", pwd, strlen(pwd));
	if (strcasecmp(pwd, DBG_PASSWD) != 0)
	{
		CLI_API_Printf(sid, "\nInput password error!\r\n");
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}

	CLI_API_Printf(sid, "\r\n");
	usr_level = bc_cli_get_usr_lvl(sid);
	if (bc_cli_set_cmdpath(sid, CLI_MOD_DEBUG_PATH, CLI_MOD_DEBUG_PROM, NULL))
	{
		bc_cli_set_usr_lvl(sid, CLI_ACC_LVL_DEBUG);
		dbg_flag = TRUE;
		
		return CLI_CMD_SUCCESS_PRT_NEWLINE;
	}
	else
	{
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
}



#if 1
/**************************************************************************
FUNCTION NAME:
	__show_language

DESCRIPTION:
	display current language

INPUT:
	sid			: created session ID by CLI kernel
	cli_para	: cli command parameters
	user_data	: user data with register this command parameter

OUTPUT:
	None

RETURN:
	

NOTES:

HISTORY:

**************************************************************************/
static I32_T __show_language(
	IN const UI32_T sid,
    IN cli_value_t 	*cli_para,
    IN void 	 	*user_data
)
{
	cli_lan_t     language = CLI_LAN_MAX;

	CLI_DBG_ENTER(l_mdl_id);

	language = bc_cli_get_lan();
	CLI_DBG_CPL(l_mdl_id, "language value = %d\r\n", language);
	switch (language)
	{
	case CLI_LAN_EN:
		CLI_API_Printf(-1, "English. \r\n");
		break;

	case CLI_LAN_CN:
		CLI_API_Printf(-1, "汉语(简体中文)。 \r\n");
		break;

	default:
		CLI_API_Printf(-1, "Unknown language! \r\n");
		break;
	}

	CLI_DBG_LEAVE(l_mdl_id);
	
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}



/**************************************************************************
FUNCTION NAME:
	__set_language

DESCRIPTION:
	set current language

INPUT:
	sid			: created session ID by CLI kernel
	cli_para	: cli command parameters
	user_data	: user data with register this command parameter

OUTPUT:
	None

RETURN:
	

NOTES:

HISTORY:

**************************************************************************/
static I32_T __set_language(
	IN const UI32_T sid,
    IN cli_value_t 	*cli_para,
    IN void 	 	*user_data
)
{
	I32_T		op_code = 0;

	CLI_DBG_ENTER(l_mdl_id);
	
	op_code = *(I32_T *)cli_para->value;
	CLI_DBG_CPL(l_mdl_id, "op_code = %d, sid = %d\r\n", op_code, sid);
	switch (op_code)
	{
	case 1://chinese
		if (FALSE == bc_cli_set_lan(sid, TRUE))
		{
			CLI_API_Printf(sid, "set language failed!\r\n");
			return CLI_CMD_FAIL_PRT_NEWLINE;
		}
		
		/* OLT process set language */
		if (BC_ERR_OK != bc_sys_set_sys_language_client((bc_lan_e)CLI_LAN_CN))
		{
			CLI_DBG_CPL(l_mdl_id, "set system language client error!\r\n");
			return CLI_CMD_FAIL_PRT_NEWLINE;
		}
		
		break;

	case 2://english
		if (FALSE == bc_cli_set_lan(sid, FALSE))
		{
			CLI_API_Printf(sid, "set language failed!\r\n");
			return CLI_CMD_FAIL_PRT_NEWLINE;
		}

		/* OLT process set language */
		if (BC_ERR_OK != bc_sys_set_sys_language_client((bc_lan_e)CLI_LAN_EN))
		{
			CLI_DBG_CPL(l_mdl_id, "set system language client error!\r\n");
			return CLI_CMD_FAIL_PRT_NEWLINE;
		}
		
		break;

	default:
		CLI_API_Printf(sid, "Unknown language!\r\n");
		return CLI_CMD_FAIL_PRT_NEWLINE;
		break;
	}

	CLI_DBG_LEAVE(l_mdl_id);

	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}
#endif


#if 1
/**************************************************************************
FUNCTION NAME:
	__set_timeout_0

DESCRIPTION:
	set never timeout

INPUT:
	sid			: created session ID by CLI kernel
	cli_para	: cli command parameters
	user_data	: user data with register this command parameter

OUTPUT:
	None

RETURN:
	

NOTES:

HISTORY:

**************************************************************************/
static I32_T __set_timeout_0(
	IN const UI32_T sid,
    IN cli_value_t 	*cli_para,
    IN void 	 	*user_data
)
{

	CLI_DBG_ENTER(l_mdl_id);

	bc_cli_set_timeout(0);

	CLI_DBG_LEAVE(l_mdl_id);

	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}



/**************************************************************************
FUNCTION NAME:
	__set_timeout_no

DESCRIPTION:
	recover default timeout

INPUT:
	sid			: created session ID by CLI kernel
	cli_para	: cli command parameters
	user_data	: user data with register this command parameter

OUTPUT:
	None

RETURN:
	

NOTES:

HISTORY:

**************************************************************************/
static I32_T __set_timeout_no(
	IN const UI32_T sid,
    IN cli_value_t 	*cli_para,
    IN void 	 	*user_data
)
{
	CLI_DBG_ENTER(l_mdl_id);

	/* default timeout time is 5 minutes */
	bc_cli_set_timeout(DEF_TIMEOUT);

	CLI_DBG_LEAVE(l_mdl_id);

	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}



/**************************************************************************
FUNCTION NAME:
	__set_timeout_time

DESCRIPTION:
	set timeout time value

INPUT:
	sid			: created session ID by CLI kernel
	cli_para	: cli command parameters
	user_data	: user data with register this command parameter

OUTPUT:
	None

RETURN:
	

NOTES:

HISTORY:

**************************************************************************/
static I32_T __set_timeout_time(
	IN const UI32_T sid,
    IN cli_value_t 	*cli_para,
    IN void 	 	*user_data
)
{
	cli_value_t		*tmp_para  = NULL;
	UI32_T			time_value = DEF_TIMEOUT;

	CLI_DBG_ENTER(l_mdl_id);

	tmp_para = cli_para;
	if (NULL == tmp_para)
	{
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	
	time_value = *(UI32_T *)tmp_para->value;
	CLI_DBG_CPL(l_mdl_id, "time_value = %d\r\n", time_value);
	
	bc_cli_set_timeout(time_value * 60);

	CLI_DBG_LEAVE(l_mdl_id);

	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

#endif

extern void bc_cli_db_dump(bc_uint32 mode, bc_char str[256]);
static I32_T __dump_cmd(
	IN const UI32_T sid,
    IN cli_value_t 	*cli_para,
    IN void 	 	*user_data
)
{
	bc_uint32 mode = 0; /* include:0, exclude:1, all:2 */
	bc_char str[256] = {0};

	if (*((bc_uint32*)cli_para->value) == 0)
	{
		mode = 0;
		cli_para = cli_para->next;
		strncpy(str, (bc_char*)cli_para->value, 256);
	}
	else if (*((bc_uint32*)cli_para->value) == 1)
	{
		mode = 1;
		cli_para = cli_para->next;
		strncpy(str, (bc_char*)cli_para->value, 256);
	}
	else
	{
		mode = 2; 
	}

	bc_cli_db_dump(mode, str);
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

static I32_T __paging(
	IN const UI32_T sid,
    IN cli_value_t 	*cli_para,
    IN void 	 	*user_data
)
{
	int i;

	for (i = 0; i < 1000; i++)
	{
		bc_cli_print(BC_MODULE_CLI, "12345678901234567890123456789012345678901234567890\n\r");
	}

	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}


/**************************************************************************
FUNCTION NAME:
    bc_cli_sys_cmd_reg

DESCRIPTION:
    Register CLI kernel basic commands.

INPUT:
    NA

OUTPUT:
    NA

RETURN:
    NA

NOTES:

HISTORY:

**************************************************************************/
void bc_cli_sys_cmd_reg(void)
{
	CLI_DBG_ENTER(l_mdl_id);

	bc_cli_reg_cmd(
		CLI_MOD_GLOBAL_PATH
		"/exit " 			"#Exit from current mode#""#退出当前模式#"
		,
		__cli2_cmd_exit,
		CLI_ACC_LVL_BASIC,
		"Exit from current mode.",
		"退出当前模式。",
		NULL);

	bc_cli_reg_cmd(
		CLI_MOD_GLOBAL_PATH
		"/end "				"#Exit to EXEC mode#""#退出执行模式#"
		,
		__cli2_cmd_end,
		CLI_ACC_LVL_BASIC,
		"Exit to EXEC mode.",
		"退出执行模式。",
		NULL);

	bc_cli_reg_cmd(
		CLI_MOD_MONITOR_PATH
		"/quit "				SYS_KEY_HELP_QUIT_EN SYS_KEY_HELP_QUIT_CN 
		,
		__cli2_cmd_quit,
		CLI_ACC_LVL_BASIC,
		SYS_KEY_HELP_QUIT_EN,
		SYS_KEY_HELP_QUIT_CN,
		NULL);

	bc_cli_reg_cmd(
		CLI_MOD_PRIVI_PATH
		"/quit "				SYS_KEY_HELP_QUIT_EN SYS_KEY_HELP_QUIT_CN 
		,
		__cli2_cmd_quit,
		CLI_ACC_LVL_BASIC,
		SYS_KEY_HELP_QUIT_EN,
		SYS_KEY_HELP_QUIT_CN,
		NULL);

	bc_cli_reg_cmd(
		CLI_MOD_GLBCFG_PATH
		"/quit "				SYS_KEY_HELP_QUIT_EN SYS_KEY_HELP_QUIT_CN 
		,
		__cli2_cmd_quit,
		CLI_ACC_LVL_BASIC,
		SYS_KEY_HELP_QUIT_EN,
		SYS_KEY_HELP_QUIT_CN,
		NULL);

	bc_cli_reg_cmd(
		CLI_MOD_MONITOR_PATH
		"/enable "				"#Enter privilege mode#""#进入特权模式#"
		,
		__sys_enter_privi_mode,
		CLI_ACC_LVL_PRIVI,
		"Enter privilege mode.",
		"进入特权模式。",
		NULL);
	cli_dir_reg_mode(CLI_MOD_PRIVI_PATH, "privilege", "privilege mode");

	bc_cli_reg_cmd(
		CLI_MOD_PRIVI_PATH
		"/configure "			"#Enter global configuration mode#""#进入全局配置模式#"
		"terminal"				"#Configure from the terminal#""#进行终端配置#"
		,
		__sys_enter_cfg_mode,
		CLI_ACC_LVL_USER,
		"Enter terminal configuration mode.",
		"进入全局配置模式。",
		NULL);
	cli_dir_reg_mode(CLI_MOD_GLBCFG_PATH, "configure", "Global configuration mode");

	bc_cli_reg_cmd(
		CLI_MOD_PRIVI_PATH
		"/debug "				"#Enter debug mode#""#进入调试模式#"
		,
		__sys_enter_debug_mode,
		CLI_ACC_LVL_ADMIN,
		"Enter debug mode.",
		"进入调试模式。",
		NULL);
	cli_dir_reg_mode(CLI_MOD_DEBUG_PATH, "debug", "Debug mode");

	bc_cli_reg_cmd(
		CLI_MOD_GLOBAL_PATH
		"/clear "				"#Clear screen#""#清屏#"
		,
		__cli2_cmd_clear_screen,
		CLI_ACC_LVL_PRIVI,
		"Clear screen.",
		"清屏。",
		NULL);
#if 0
	bc_cli_reg_cmd(
		CLI_MOD_GLOBAL_PATH
		"/show "
		"session "				"#Display session information#""#显示用户信息#"
		,
		__cli2_cmd_show_session,
		CLI_ACC_LVL_PUSER,
		"Used to display a list of currently logged-in users.",
		"显示用户信息。",
		NULL);
#endif
	bc_cli_reg_cmd(
		CLI_MOD_GLOBAL_PATH
		"/command-history "		"#set command history#""#设置历史命令#"
		"max"					"#maximal value#""#最大值#"
		"<value 1-40> "
		,
		__cli2_cmd_config_hist,
		CLI_ACC_LVL_PUSER,
		"Used to configure the maximal value of command history.",
		"设置命令行保存的最大历史命令数。",
		NULL);

	bc_cli_reg_cmd(
		CLI_MOD_GLOBAL_PATH
		"/show "
		"command-history "		"#Display history command#""#显示历史命令#"
		,
		__cli2_cmd_show_hist,
		CLI_ACC_LVL_PRIVI,
		"Used to display command history.",
		"显示历史命令。",
		NULL);

	bc_cli_reg_cmd(
		CLI_MOD_GLOBAL_PATH
		"/paging "				"#Configure cli paging#""#配置CLI分页#"
		"enable "				"#Enable cli paging#""#打开CLI分页功能#"
		,
		__cli2_cmd_enable_paging,
		CLI_ACC_LVL_PUSER,
		"Used to pause the scrolling of the console screen when the show command displays more than one page.",
		"打开CLI分页功能。",
		NULL);

	bc_cli_reg_cmd(
		CLI_MOD_GLOBAL_PATH
		"/paging "
		"disable "				"#Disable cli paging#""#关闭CLI分页功能#"
		,
		__cli2_cmd_disable_paging,
		CLI_ACC_LVL_PUSER,
		"Used to disable the pausing of the console screen scrolling at the end of each page "
		"when the show command would display more than one screen of information.",
		"关闭CLI分页功能。",
		NULL);

#if CLI_COMMAND_LOGGING_INCLUDED
	bc_cli_reg_cmd(
		"/command logging enable"
		,
		__cli2_cmd_enable_cmdLogState,
		CLI_ACC_LVL_ADMIN,
		"Use to enable the command logging.",
		NULL,
		NULL);

	bc_cli_reg_cmd(
		"/command logging disable"
		,
		__cli2_cmd_disable_cmdLogState,
		CLI_ACC_LVL_ADMIN,
		"Use to disable the command logging.",
		NULL,
		NULL);

	bc_cli_reg_cmd(
		CLI_MOD_GLOBAL_PATH
		"/show command logging"
		,
		__cli2_cmd_show_cmdLogState,
		CLI_ACC_LVL_PUSER,
		"Use this command to show the command logging configuration status.",
		NULL,
		NULL);
#endif

	//CLI_CFG_Reg_RetrieveFunc(__cli2_cmd_retrieve, NULL,"/300/CLI");
	//CLI_CFG_Reg_Enhanced_RetrieveFunc(__cli2_cmd_enhance_retrieve, "/CLI");


#if 1
	bc_cli_reg_cmd(
		CLI_MOD_GLOBAL_PATH
		"/show "
		"language "				"#Show cli language#""#显示CLI语言#"
		,
		__show_language,
		CLI_ACC_LVL_USER,
		"Show cli language.",
		"显示CLI语言.",
		NULL
		);
	
	bc_cli_reg_cmd(
		CLI_MOD_GLOBAL_PATH
		"/language "			"#Set cli language#""#设置CLI语言#"
		"{ "
			"chinese(1) "		"#chinese#""#中文#"
			"| "
			"english(2) "		"#english#""#英文#"
		"} "
		,
		__set_language,
		CLI_ACC_LVL_USER,
		"Set cli language.",
		"设置CLI语言",
		NULL
		);

#endif

#if 1
	bc_cli_reg_cmd(
		CLI_MOD_MONITOR_PATH
		"/timeout "				"#Set telnet timeout#""#设置登陆用户的超时时间#"
		"0 "					"#set never timeout#""#超时时间为永不超时#"
		,
		__set_timeout_0,
		CLI_ACC_LVL_USER,
		"Set telnet never timeout",
		"设置登陆用户为永不超时",
		NULL
		);

	bc_cli_reg_cmd(
		CLI_MOD_PRIVI_PATH
		"/timeout "				"#Set telnet timeout#""#设置登陆用户的超时时间#"
		"0 "					"#set never timeout#""#超时时间为永不超时#"
		,
		__set_timeout_0,
		CLI_ACC_LVL_USER,
		"Set telnet never timeout",
		"设置登陆用户为永不超时",
		NULL
		);

	bc_cli_reg_cmd(
		CLI_MOD_MONITOR_PATH
		"/no "					"#Set default value#""#恢复默认配置或删除配置#"
		"timeout "				"#Set telnet timeout#""#设置登陆用户的超时时间#"
		,
		__set_timeout_no,
		CLI_ACC_LVL_USER,
		"Recover default timeout",
		"恢复默认超时时间",
		NULL
		);

	bc_cli_reg_cmd(
		CLI_MOD_PRIVI_PATH
		"/no "					"#Set default value#""#恢复默认配置或删除配置#"
		"timeout "				"#Set telnet timeout#""#设置登陆用户的超时时间#"
		,
		__set_timeout_no,
		CLI_ACC_LVL_USER,
		"Recover default timeout",
		"恢复默认超时时间",
		NULL
		);

	bc_cli_reg_cmd(
		CLI_MOD_MONITOR_PATH
		"/timeout "				"#Set telnet timeout#""#设置登陆用户的超时时间#"
		"<timeout> "			"#Time value(minute)#""#时间值(分钟)#"
		,
		__set_timeout_time,
		CLI_ACC_LVL_USER,
		"Set timeout value",
		"设置超时时间值",
		NULL
		);

	bc_cli_reg_cmd(
		CLI_MOD_PRIVI_PATH
		"/timeout "				"#Set telnet timeout#""#设置登陆用户的超时时间#"
		"<timeout> "			"#Time value(minute)#""#时间值(分钟)#"
		,
		__set_timeout_time,
		CLI_ACC_LVL_USER,
		"Set timeout value",
		"设置超时时间值",
		NULL
		);


#endif

	bc_cli_reg_cmd(
		CLI_MOD_DEBUG_PATH
		"/cli command { include(0) <string> | exclude(1) <string> | all(2) }"
		,
		__dump_cmd,
		CLI_ACC_LVL_USER,
		"Set timeout value",
		"设置超时时间值",
		NULL
		);

	bc_cli_reg_cmd(
		CLI_MOD_DEBUG_PATH
		"/cli paging test"
		,
		__paging,
		CLI_ACC_LVL_USER,
		"",
		"",
		NULL
		);


    return;
}



