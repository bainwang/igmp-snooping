/****************************************************************************
 * Copyright (c) 2005-2010  Kingtype Corporation   All rights reserved.
 *
 * This is unpublished proprietary source code of Kingtype networks Corporation
 *
 * The copyright notice above does not evidence any actual or intended
 *  publication of such source code.
 ****************************************************************************
 */

/*----------------------------------------------------------------------------
 * MODULE NAME: Kingtype CLI, bc_cli
 * FILE NAME  : bc_cli_bnr_cmd.c
 * Purposes:
 *----------------------------------------------------------------------------
 */

////////////////////////////////////////////////////////////////////////////////
// 																			  //
// 							 	头   文   件								  //
// 																			  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_modules.h"

#include "bc_cli_vt100.h"
#include "bc_cli_bnr.h"
#include "bc_cli_vkey.h"
#include "bc_cli_bnr_stk.h"
#include "bc_cli_bnr_msg.h"
#include "bc_cli_paratype.h"
#include "bc_cli_acc.h"

#include "bc_cli.h"
//#include "bc_sys_ipc_client.h"



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

enum
{
    Msg_None,
    Msg_Success,
    Msg_QuitWithoutSave,
    Msg_SettingFail
};

typedef struct _banner_editor
{
    UI32_T  currLINE; /* Max is 6 or 24 */
    UI32_T  currROW; /* Max is 80 */
    UI32_T  positionLINE; /* Max is 6 */
    char    line[BANNER_MAX_LINE][BANNER_MAX_COLUMN + 1];
    UI32_T  endPosition[BANNER_MAX_LINE];
    UI32_T  EditMsg;
} BANNER_INFO_T;



////////////////////////////////////////////////////////////////////////////////
//																			  //
//							全 局 变 量 定 义								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

//static unsigned int 	l_mdl_id = BC_MODULE_CLI_KERNEL_BNR_CMD;



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
#if 0
/*------------------------------------------------------------------------
 * Function:   cli2_bnr_cmd_get_free_separator
 * Purpose:    Find a char which is exclude in msg as separator
 * Parameters:
 *    Input:   sessionID = sessionID identifier
 *    Output:  None
 * Returns:    the separator char
 *------------------------------------------------------------------------
 */
I8_T cli2_bnr_cmd_get_free_separator
    (
    I8_T *msg
    )
{
    I8_T        i;
    I32_T       j;
    const I8_T  spec_ch[]   =
    {
        '`', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '_', '=', '+', ';', ':', '\'', '\"', '|', '\\', ',',
        '<', '.', '>', '/', '[', '{', ']', '}'
    };
    /* '?' can not be took as seperator*/

    for (i = 'a'; i <= 'z'; i++)
    {
        if (!strchr(msg, i))
        {
            return i;
        }
    }

    for (i = 'A'; i <= 'Z'; i++)
    {
        if (!strchr(msg, i))
        {
            return i;
        }
    }   

    for (i = '0'; i <= '9'; i++)
    {
        if (!strchr(msg, i))
        {
            return i;
        }
    }   

    j = 0;
    while (j < sizeof(spec_ch))
    {
        if (!strchr(msg, spec_ch[j])) //can not use i here,otherwise the compiler check wil fall
        {
            return spec_ch[j];
        }
    }

    return 0;
}
#endif

#if 0// 保存配置

typedef enum etag_cli_xfile_return_status_type
{
    XFILE_OK,
    XFILE_ERROR_BUFFER_FULL
} cli_xfile_rtn_sta_e;

typedef struct stag_cli_xfile_type
{
    int                 sessionID;
    UI32_T              pos;
    UI32_T              size;
    I8_T                *buf;
    I8_T                *oldcompress;      	/* old compress format */
    I8_T                *cbuf;            	/* compress buf */
    UI32_T              csize;           	/* compress total size */
    UI32_T              cpos;            	/* new entry point */
    cli_xfile_rtn_sta_e return_status;
} cli_xfile_t;

static BOOL_T __cli2_bnr_cmd_retrieve_banner_prompt_v2
    (
    cli_xfile_t *pFile
    )
{
    I8_T        *bnr_msg;
    I8_T        separator;
    const I32_T msg_len = (BANNER_MAX_LINE *BANNER_MAX_COLUMN + 1 + 2 /*The head and tail delimeters*/);

    bnr_msg = (I8_T *)malloc(msg_len);
    if (!bnr_msg)
    {
        return FALSE;
    }

	memset(bnr_msg, 0, msg_len);

    CLI_CFG_Printf(pFile, "configure terminal\n\r");

    if (CLI_BNR_Get_GreetingMsg((UI8_T *)bnr_msg + 1, msg_len, NULL))
    {
        separator = cli2_bnr_cmd_get_free_separator(bnr_msg + 1);
        if (separator == 0)
        {
            CLI_CFG_Printf(pFile, "no banner login \n\r");
        }
        else
        {
            bnr_msg[0] = separator;
            bnr_msg[strlen(bnr_msg)] = separator;
            bnr_msg[strlen(bnr_msg)] = '\0';

            CLI_CFG_Printf(pFile, "banner login <string>\n\r", bnr_msg);
        }
    }
    else
    {
        CLI_CFG_Printf(pFile, "no banner login \n\r");
    }

    if (CLI_BNR_Get_Prompt(VT_CHANNEL_LAST, bnr_msg, msg_len))
    {
        CLI_CFG_Printf(pFile, "prompt <string>\n\r", bnr_msg);
    }
    else
    {
        CLI_CFG_Printf(pFile, "no prompt\n\r", bnr_msg);
    }

    CLI_CFG_Printf(pFile, "end\n\r");  
    free(bnr_msg);

    return TRUE;
}
#endif



/*------------------------------------------------------------------------
 * Function   : cli_bnr_cmd_show_banner
 * Description: Display the login banner
 * Parameters : const int sessionID, cli_value_t *ptrCliValue, void *ptrUserData
 * Input      :
 * Output     :
 * Returns    :      
 * writer     : wangbin, 2011-06-05
 *------------------------------------------------------------------------
*/
I32_T cli_bnr_cmd_show_banner
    (
    IN const UI32_T sessionID,
    IN cli_value_t *ptrCliValue,
    IN void *ptrUserData
    )
{
    UI8_T   *msg_buf;
    I32_T   ret_val;

    UNUSED(ptrUserData);
    UNUSED(ptrCliValue);

    msg_buf = (UI8_T *) malloc(BANNER_MAX_LINE * BANNER_MAX_COLUMN + 1);

    if (!msg_buf)
    {
        return CLI_CMD_FAIL_PRT_PROMPT;
    }

    if (CLI_BNR_Get_GreetingMsg(msg_buf, (BANNER_MAX_LINE * BANNER_MAX_COLUMN + 1), NULL))
    {
        CLI_ACC_SetPageStopStatus(sessionID, FALSE);
        CLI_API_Printf(sessionID, "\r\n================================================================================\n\r");
        CLI_API_Printf(sessionID, "%s", msg_buf);
        CLI_API_Printf(sessionID, "\n\r================================================================================\n\r");
        CLI_ACC_SetPageStopStatus(sessionID, TRUE);

        ret_val = CLI_CMD_SUCCESS_PRT_NEWLINE;
    }
    else
    {
        ret_val = CLI_CMD_FAIL_PRT_PROMPT;
    }

    free(msg_buf);

	return ret_val;
}


#if 0
/*------------------------------------------------------------------------
 * Function:    __cmd_cfg_greeting_msg
 * Description: Set the greeting messge
 * Parameters:  const int sessionID, cli_value_t *ptrCliValue, void *ptrUserData
 * Input:
 * Output:
 * Returns:      
 * writer:      wangbin, 2011-06-07
 *------------------------------------------------------------------------
*/
static I32_T __cmd_cfg_greeting_msg
    (
    IN const UI32_T sessionID,
    IN cli_value_t *ptrCliValue,
    IN void *ptrUserData
    )
{
    BANNER_PRMPT_BANNER_T   *bnr_msg;
    I8_T                    separator;
    I8_T                    *msg_head   = NULL;
    I8_T                    *msg_end    = NULL;    
    I32_T                   ret_val;
    I32_T                   line_len;
    I32_T                   msg_used    = 0;
    const I32_T             msg_size    = (BANNER_MAX_LINE *BANNER_MAX_COLUMN);
    I32_T                   timeout;
    I32_T                   get_line_code;
    I8_T                    *pgreeting_msg;
    I32_T                   trigger[]   =
    {
        CLI_VKEY_CTRL_ENTER, CLI_VKEY_CR, CLI_VKEY_CTRL_C, 0
    };

    UNUSED(ptrUserData);

    bnr_msg = (BANNER_PRMPT_BANNER_T *)malloc(sizeof(BANNER_PRMPT_BANNER_T));

    if (!bnr_msg)
    {
        return CLI_CMD_FAIL_PRT_PROMPT;
    }

	if (!CLI_BNR_Get_PromptBannerInfo(bnr_msg))
    {
        ret_val = CLI_CMD_FAIL_PRT_PROMPT;
        goto FAIL_RETURN;
    }

    pgreeting_msg = &bnr_msg->greeting_msg[0];
    memset(pgreeting_msg, 0, msg_size);    
    bnr_msg->bUseGreetMsg = USR_BANN_STATE_ENABLED;

    separator = *(I8_T *) ptrCliValue->value;
    if (*((I8_T *) ptrCliValue->value + 1) != '\0')
    {
        msg_head = (I8_T *) ptrCliValue->value + 1;
        msg_end = strchr(msg_head, separator);
    }   

    if (msg_head && msg_end)
    {
        line_len = MIN((I32_T) (msg_end - msg_head + 1), msg_size);
        strncpy(pgreeting_msg, msg_head, line_len);
        pgreeting_msg[line_len] = '\0';
    }
    else
    {
        if (msg_head)
        {
            line_len = MIN(strlen(msg_head), msg_size);
            strncpy(pgreeting_msg, msg_head, line_len);
            msg_used = line_len;

            if (line_len < msg_size)
            {
                pgreeting_msg[line_len] = '\n';
                msg_used++;
            }
        }
        else
        {
            CLI_API_Printf(sessionID, CLI_BNR_MSG_SET_LOGIN_PMT"\n\r");
        }

        timeout = bc_cli_get_sesntimeout(sessionID); 
        while (msg_used <= msg_size)
        {
            msg_end = NULL;
            get_line_code = bc_cli_get_line(sessionID, 0, CLI_OUTPUT_NORMAL, pgreeting_msg + msg_used, (msg_size - msg_used), timeout, trigger);

            switch (get_line_code)
            {
            case CLI_VKEY_CR:
            case CLI_VKEY_CTRL_ENTER :
                msg_end = strchr(pgreeting_msg + msg_used, separator);

                if (msg_end) //if separator is found, cut the string and save
                {
                    *msg_end = '\0';
                    msg_used = msg_size + 1;
                    break;
                }

                line_len = strlen(pgreeting_msg + msg_used);
                msg_used += line_len;
                if (msg_used == msg_size)
                {
                    pgreeting_msg[msg_size] = '\0';
                    msg_used = msg_size + 1;
                    break;
                }

                pgreeting_msg[msg_used] = '\n';
                msg_used++;        
                break;         

            default :
                bc_cli_close_sesn(sessionID, CLI_KP_TIMEOUT);
                ret_val = CLI_CMD_FAIL_PRT_PROMPT_NEWLINE;
                goto FAIL_RETURN;
            }

			CLI_API_Printf(sessionID, "\n\r");
        }
    }

    if (!CLI_BNR_Update_PromptBannerInfo(bnr_msg))
    {
        ret_val = CLI_CMD_FAIL_PRT_PROMPT_NEWLINE;
        goto FAIL_RETURN;
    }

#ifdef USER_PROMPT_INCLUDED
    CLI_BNR_STK_Send_UpdatePromptBannerMSG(bnr_msg);
#endif
    ret_val = CLI_CMD_SUCCESS_PRT_NONE;

FAIL_RETURN:
	free(bnr_msg);
    return ret_val;
}



/*------------------------------------------------------------------------
 * Function:    __cmd_cfg_greeting_msg_no
 * Description: Set the greeting messge no
 * Parameters:  const int sessionID, cli_value_t *ptrCliValue, void *ptrUserData
 * Input:
 * Output:
 * Returns:      
 * writer:      wangbin, 2011-06-07
 *------------------------------------------------------------------------
*/
static I32_T __cmd_cfg_greeting_msg_no
    (
    IN const UI32_T sessionID,
    IN cli_value_t *ptrCliValue,
    IN void *ptrUserData
    )
{
    BANNER_PRMPT_BANNER_T   *bnr_msg;
    I32_T                   ret_val;

    NO_WARNING(sessionID);
    NO_WARNING(ptrCliValue);
    NO_WARNING(ptrUserData);

    bnr_msg = (BANNER_PRMPT_BANNER_T *) malloc(sizeof(BANNER_PRMPT_BANNER_T));
    if (!bnr_msg)
    {
        return CLI_CMD_FAIL_PRT_PROMPT;
    }

    if (CLI_BNR_Get_PromptBannerInfo(bnr_msg))
    {
        memset(bnr_msg->greeting_msg, 0, (BANNER_MAX_COLUMN * BANNER_MAX_LINE + 1));
        if (CLI_BNR_Update_PromptBannerInfo(bnr_msg))
        {
            ret_val = CLI_CMD_SUCCESS_PRT_PROMPT;
        }
        else
        {
            ret_val = CLI_CMD_FAIL_PRT_PROMPT;
        }
    }
    else
    {
        ret_val = CLI_CMD_FAIL_PRT_PROMPT;
    }

    free(bnr_msg);
    return ret_val;
}
#endif

#if 0
/*------------------------------------------------------------------------
 * Function:    __cmd_cfg_prompt
 * Description: Set the command prompt
 * Parameters:  const int sessionID, cli_value_t *ptrCliValue, void *ptrUserData
 * Input:
 * Output:
 * Returns:      
 * writer:      wangbin, 2011-06-07
 *------------------------------------------------------------------------
*/
static I32_T __cmd_cfg_prompt
    (
    IN const UI32_T sessionID,
    IN cli_value_t *ptrCliValue,
    IN void *ptrUserData
    )
{
    BANNER_PRMPT_BANNER_T   *bnr_msg;
    I8_T                    prompt[BNR_CPU_NAME_MAX_LEN + 1] = {0};
    I32_T                   ret_val;

	UNUSED(ptrUserData);

    bnr_msg = (BANNER_PRMPT_BANNER_T *) malloc(sizeof(BANNER_PRMPT_BANNER_T));
    if (!bnr_msg)
    {
        return CLI_CMD_FAIL_PRT_PROMPT;
    }

    if (!CLI_BNR_Get_PromptBannerInfo(bnr_msg))
    {
        ret_val = CLI_CMD_FAIL_PRT_PROMPT;
        goto FAIL_RETURN;
    }

    bnr_msg->bUseCmdPrompt = USR_BANN_STATE_ENABLED;
    bnr_msg->cmd_prompt.bUserName = FALSE;
    strncpy(bnr_msg->cmd_prompt.string, (I8_T *) ptrCliValue->value, BNR_CPU_NAME_MAX_LEN);

    if (!CLI_BNR_Update_PromptBannerInfo(bnr_msg))
    {
        ret_val = CLI_CMD_FAIL_PRT_PROMPT;
        goto FAIL_RETURN;
    }

#ifdef USER_PROMPT_INCLUDED
    CLI_BNR_STK_Send_UpdatePromptBannerMSG(bnr_msg);
#endif

    CLI_BNR_Get_Prompt(sessionID, prompt, sizeof(prompt));
    bc_cli_set_cmdpath(sessionID, CLI_MOD_MONITOR_PATH, prompt, NULL);
    ret_val = CLI_CMD_SUCCESS_PRT_NONE;

FAIL_RETURN:
    free(bnr_msg);
    return ret_val;
}



/*------------------------------------------------------------------------
 * Function:    __cmd_cfg_prompt_no
 * Description: Set the command prompt no
 * Parameters:  const int sessionID, cli_value_t *ptrCliValue, void *ptrUserData
 * Input:
 * Output:
 * Returns:     TRUE/FALSE
 * writer:      wangbin, 2011-06-07
 *------------------------------------------------------------------------
*/
static I32_T __cmd_cfg_prompt_no
    (
    IN const UI32_T sessionID,
    IN cli_value_t *ptrCliValue,
    IN void *ptrUserData
    )
{
    BANNER_PRMPT_BANNER_T   *tmp_prompt;
    I8_T                    prompt[BNR_CPU_NAME_MAX_LEN + 1] = {0};
    I32_T                   ret_val;

    UNUSED(ptrCliValue);
    UNUSED(ptrUserData);

    tmp_prompt = (BANNER_PRMPT_BANNER_T *) malloc(sizeof(BANNER_PRMPT_BANNER_T));
    if (!tmp_prompt)
    {
        return CLI_CMD_FAIL_PRT_PROMPT;
    }

    if (!CLI_BNR_Get_PromptBannerInfo(tmp_prompt))
    {
        ret_val = CLI_CMD_FAIL_PRT_PROMPT;
        goto FAIL_RETURN;
    }

    tmp_prompt->cmd_prompt.bUserName = FALSE;
    memset(tmp_prompt->cmd_prompt.string, 0, (BNR_CPU_NAME_MAX_LEN + 1));
    if (!CLI_BNR_Update_PromptBannerInfo(tmp_prompt))
    {
        ret_val = CLI_CMD_FAIL_PRT_PROMPT_NEWLINE;
        goto FAIL_RETURN;
    }

#ifdef USER_PROMPT_INCLUDED
    CLI_BNR_STK_Send_UpdatePromptBannerMSG(tmp_prompt);
#endif

    CLI_BNR_Get_Prompt(sessionID, prompt, sizeof(prompt));
    bc_cli_set_cmdpath(sessionID, CLI_MOD_MONITOR_PATH, prompt, NULL);
    ret_val = CLI_CMD_SUCCESS_PRT_PROMPT_NEWLINE;

FAIL_RETURN:
    free(tmp_prompt);
    return ret_val;
}
#endif



#if 0
/*------------------------------------------------------------------------
 * Function:    __set_hostname
 * Description: 
 * Parameters:  const int sessionID, cli_value_t *ptrCliValue, void *ptrUserData
 * Input:
 * Output:
 * Returns:      
 * writer:      wangbin, 2014-09-14
 *------------------------------------------------------------------------
*/
static I32_T __set_hostname
	(
	IN const UI32_T sessionID,
	IN cli_value_t 	*ptrCliValue,
	IN void 		*ptrUserData
	)
{
	BANNER_PRMPT_BANNER_T	tmp_bnr;
	I8_T					hostname[32] = {0};

	CLI_DBG_ENTER(l_mdl_id);

	memset(&tmp_bnr, 0x00, sizeof(BANNER_PRMPT_BANNER_T));
	
	strncpy(hostname, (I8_T *)ptrCliValue->value, 32);
	CLI_DBG_CPL(l_mdl_id, "hostname: %s, strlen(hostname) = %d\r\n", hostname, strlen(hostname));

	/* set hostname(olt name) */
	if (BC_ERR_OK != bc_sys_set_sys_name_client(hostname))
	{
		CLI_DBG_CPL(l_mdl_id, "set system name client error!\r\n");
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	
	if (FALSE == CLI_BNR_Update_To_Default_Bnr(&tmp_bnr))
	{
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}

	tmp_bnr.bUseCmdPrompt = USR_BANN_STATE_ENABLED;
	tmp_bnr.cmd_prompt.bUserName = FALSE;
	memset(tmp_bnr.cmd_prompt.string, 0x00, sizeof(tmp_bnr.cmd_prompt.string));
	strncpy(tmp_bnr.cmd_prompt.string, hostname, 32);

	if (FALSE == CLI_BNR_Update_PromptBannerInfo(&tmp_bnr))
	{
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}

	memset(hostname, 0x00, sizeof(hostname));
	CLI_BNR_Get_Prompt(sessionID, hostname, sizeof(hostname));
	CLI_DBG_CPL(l_mdl_id, "hostname: %s\r\n", hostname);
    bc_cli_set_cmdpath(sessionID, CLI_MOD_MONITOR_PATH, hostname, NULL);
	
	CLI_DBG_LEAVE(l_mdl_id);
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}



/*------------------------------------------------------------------------
 * Function:    __set_hostname_no
 * Description: 
 * Parameters:  const int sessionID, cli_value_t *ptrCliValue, void *ptrUserData
 * Input:
 * Output:
 * Returns:      
 * writer:      wangbin, 2014-09-14
 *------------------------------------------------------------------------
*/
static I32_T __set_hostname_no
	(
	IN const UI32_T sessionID,
	IN cli_value_t 	*ptrCliValue,
	IN void 		*ptrUserData
	)
{
	BANNER_PRMPT_BANNER_T	tmp_bnr;
	I8_T 					hostname[32] = {0};

	CLI_DBG_ENTER(l_mdl_id);

	memset(&tmp_bnr, 0x00, sizeof(BANNER_PRMPT_BANNER_T));
	
	if (FALSE == CLI_BNR_Get_PromptBannerInfo(&tmp_bnr))
	{
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}

	tmp_bnr.cmd_prompt.bUserName = FALSE;
	memset(tmp_bnr.cmd_prompt.string, 0x00, sizeof(tmp_bnr.cmd_prompt.string));

	/* set default olt name */
	if (BC_ERR_OK != bc_sys_set_sys_name_client(DEV_NAME))
	{
		CLI_DBG_CPL(l_mdl_id, "set system name client error!\r\n");
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	
	CLI_BNR_Update_To_Default_Bnr(&tmp_bnr);

	if (FALSE == CLI_BNR_Update_PromptBannerInfo(&tmp_bnr))
	{
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}

	CLI_BNR_Get_Prompt(sessionID, hostname, sizeof(hostname));
	CLI_DBG_CPL(l_mdl_id, "hostname: %s\r\n", hostname);
    bc_cli_set_cmdpath(sessionID, CLI_MOD_MONITOR_PATH, hostname, NULL);

	CLI_DBG_LEAVE(l_mdl_id);
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}


#endif



/*------------------------------------------------------------------------
 * Function:   BOOL_T bc_cli_bnr_cmd_reg (void)
 * Parameters: None
 *    Input:   None
 *    Output:  None
 * Returns:    None
 *------------------------------------------------------------------------
 */
BOOL_T bc_cli_bnr_cmd_reg(void)
{
#if 0
	bc_cli_reg_cmd(
		CLI_MOD_GLBCFG_PATH
		"/greeting_message "CLI_BNR_MSG_BANNER_HELP"#设置提示语#"
		"login "			CLI_BNR_MSG_SET_LOGIN"#设置登录提示语#"
		"<string>  ",
		__cmd_cfg_greeting_msg,
		CLI_ACC_LVL_USER,
		CLI_BNR_MSG_SET_LOGIN_HELP,
		"设置登录提示语。",
		NULL);	

	bc_cli_reg_cmd(
		CLI_MOD_GLBCFG_PATH
		"/no "
		"greeting_message "	CLI_BNR_MSG_BANNER_HELP"#设置提示语#"
		"login "			CLI_BNR_MSG_SET_LOGIN"#设置登录提示语#",
		__cmd_cfg_greeting_msg_no,
		CLI_ACC_LVL_USER,
		CLI_BNR_MSG_SET_LOGIN_HELP,
		NULL,
		NULL);

	bc_cli_reg_cmd(
		CLI_MOD_GLBCFG_PATH
		"/prompt "			CLI_BNR_MSG_SET_PROMPTP"#设置命令行提示语#"
		"<string> ",
		__cmd_cfg_prompt,
		CLI_ACC_LVL_USER,
		CLI_BNR_MSG_PROMPT_HELP,
		NULL,
		NULL);

	bc_cli_reg_cmd(
		CLI_MOD_GLBCFG_PATH
		"/no "
		"prompt "			CLI_BNR_MSG_SET_PROMPTP"#设置命令行提示语#",
		__cmd_cfg_prompt_no,
		CLI_ACC_LVL_USER,
		CLI_BNR_MSG_PROMPT_HELP,
		NULL,
		NULL);

	bc_cli_reg_cmd(
		CLI_MOD_GLOBAL_PATH
		"/show "
		"greeting_message"	CLI_BNR_MSG_BANNER_HELP"#显示提示语#",
		cli_bnr_cmd_show_banner,
		CLI_ACC_LVL_DEBUG,
		CLI_BNR_MSG_SHOW_LOGIN_HELP,
		NULL,
		NULL);
#endif

#if 0//挂载保存配置回调
	CLI_CFG_Reg_RetrieveFunc(__cli2_bnr_cmd_retrieve_banner_prompt_v2, NULL, "/2560/BANNER_PROMP");
#endif

	
#if 0
	bc_cli_reg_cmd(
		CLI_MOD_GLBCFG_PATH
		"/hostname "			"#set hostname#""#设置主机名#"
		"<string> "
		,
		__set_hostname,
		CLI_ACC_LVL_USER,
		"set system hostname",
		"设置系统主机名",
		NULL);

	bc_cli_reg_cmd(
		CLI_MOD_GLBCFG_PATH
		"/no "
		"hostname "			"#set hostname#""#设置主机名#"
		,
		__set_hostname_no,
		CLI_ACC_LVL_USER,
		"no system hostname",
		"恢复默认主机名",
		NULL);
#endif

    return TRUE;
}




