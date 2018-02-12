	
////////////////////////////////////////////////////////////////////////////////
//																			  //
//								头	 文   件								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_modules.h"
#include "bc_platform_time.h"


#include "bc_cli_type.h"
#include "bc_cli_sesn.h"
#include "bc_cli_vkey.h"
#include "bc_cli_edit.h"
#include "bc_cli_core.h"
#include "bc_cli_db.h"
#include "bc_cli_acc.h"
#include "bc_cli_dir.h"
#include "bc_cli_edit.h"
#include "bc_cli_vkey.h"
#include "bc_cli_vt100.h"

#include "bc_cli_kernel_cfg.h"
#include "vt_100.h"
#include "bc_cli_hist.h"

#include "bc_cli_sys_cmd.h"
#include "bc_cli_bnr_cmd.h"
#include "bc_cli_misc.h"
#include "bc_cli_para.h"
#include "bc_cli_bnr.h"

#include "bc_cli.h"
#include "sys/time.h"
#include <signal.h>
#include <setjmp.h>



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

#define CLI_ACC_ANONYMOUS_NAME      	"Guest"



////////////////////////////////////////////////////////////////////////////////
//																			  //
//							全 局 变 量 定 义								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

//static unsigned int 	l_mdl_id = BC_MODULE_CLI_KERNEL;

static const I8_T 		l_page_prompt[] =
"\n\r"
"\033[7m"
"CTRL+C"
"\033[0m"
" "
"\033[7m"
"ESC"
"\033[0m"
" "
"\033[7m"
"q"
"\033[0m"
" Quit "
"\033[7m"
"SPACE"
"\033[0m"
" "
"\033[7m"
"n"
"\033[0m"
" Next Page "
"\033[7m"
"p"
"\033[0m"
" Previous Page "
"\033[7m"
"r"
"\033[0m"
" Refresh                  ";

static BOOL_T 			l_run_env_cfg_rs232 = FALSE;
static BOOL_T 			l_show_logout_info = FALSE;
//static BOOL_T           l_page_state = TRUE;  // global cli paging state, TRUE: enable, FALSE: disable


static cli_lan_t 		l_language = DEF_LANGUAGE;

//static UI32_T 		 	l_timeout = DEF_TIMEOUT;

extern jmp_buf   buf;
extern void CLI_API_DestroySession(IN I32_T map_sessionID);



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
    bc_cli_get_sesntimeout

DESCRIPTION:
    Get time out value of input session.

INPUT:
    session_id  : session ID

OUTPUT:
    NA

RETURN:
    time out value
    -1 -- the session is not exist

NOTES:
	NA

HISTORY:

**************************************************************************/
I32_T bc_cli_get_sesntimeout(IN I32_T session_id)
{
    cli_sesn_t  *session;

    session = cli_sesn_get_by_sid(session_id);
    if (session)
    {
        return session->timeout;
    }

    return -1;
}



/**************************************************************************
FUNCTION NAME:
    bc_cli_set_sesntimeout

DESCRIPTION:
    Set the timeout second of the input session

INPUT:
    sessionID       : mapped session ID for other modules used
    timeoutSec      : timeout second, if the value set to 0 that means never timeout

OUTPUT:
    NA

RETURN:
    TRUE            : set success
    FALSE           : the session is not exist

NOTES:
    If set timeout to 0, that means the session never timeout.

HISTORY:

**************************************************************************/
BOOL_T bc_cli_set_sesntimeout(IN I32_T sessionID, IN I32_T timeoutSec)
{
    cli_sesn_t  *session;

    /* get session data */
    session = cli_sesn_get_by_sid(sessionID);
    if (NULL == session)
    {
        return FALSE;
    }

    session->timeout = timeoutSec;

    return TRUE;
}



/**************************************************************************
FUNCTION NAME:
    bc_cli_get_line

DESCRIPTION:
    Get input line from terminal

INPUT:
    session_id  : the mapped session ID
    prompt_len  : the prompt length of edit begin line
    mode        : output mode
    pbuf        : pointer of the buffer to get input string
    buflen      : size of the buffer
    timeout_sec : how many seconds the session will be closed by itself
    trigger     : trigger char which will casue the function return

OUTPUT:
    pbuf        : input string(zero terminated)

RETURN:
    trigger char which cause the function return
    CLI_VKEY_IO_CLOSED
    CLI_VKEY_IO_TIMEOUT
    CLI_VKEY_IO_EXITCMD
    CLI_VKEY_IO_NOTIFY
    CLI_VKEY_IO_WRONGVALUE
    defined in cli2_vkey.h

NOTES:

HISTORY:

**************************************************************************/
I32_T bc_cli_get_line
	(
	IN I32_T 				session_id,
	IN I32_T 				prompt_len,
	IN cli_output_mode_e 	mode,
	IN OUT I8_T 			*pbuf,
    IN UI32_T 				bufLen,
    IN I32_T 				timeout_sec,
    IN I32_T 				*trigger
    )
{
    cli_sesn_t      		*session;
    I32_T               	old_len;
    cli_output_mode_e  		old_mode;
    I32_T               	ret;

    /* get session data */
    session = cli_sesn_get_by_sid(session_id);
    if (NULL == session)
    {
        return CLI_VKEY_IO_WRONGVALUE;
    }

    /* get current output mode and prompt length */
    old_mode = CLI_EDIT_Get_OutputMode(session->hedit);
    old_len = CLI_EDIT_Get_PromptLen(session->hedit);

    /* set output mode */
    CLI_EDIT_Set_OutputMode(session->hedit, mode);
    CLI_EDIT_Set_PromptLen(session->hedit, (prompt_len % CLI_EDIT_LINE_LEN));
    CLI_EDIT_Set_HistoryStatus(session->hedit, FALSE);

    /* get command line */
    ret = CLI_EDIT_Get_Line_WithBreak(session->hedit, pbuf, bufLen, timeout_sec, trigger);

    CLI_EDIT_Set_HistoryStatus(session->hedit, TRUE);
    /* resume output mode and prompt length */
    CLI_EDIT_Set_PromptLen(session->hedit, old_len);
    CLI_EDIT_Set_OutputMode(session->hedit, old_mode);

    return ret;
}



/**************************************************************************
FUNCTION NAME:
	bc_cli_reg_mode

DESCRIPTION:
	Register new mode of CLI manual. (display for user)
	1. search mode list, if found it, failed to create the mode & return
	2. calculate the node buffer to store the mode information
	3. alloc memory to create new mode node 
	4. insert the new mode node into the mode list

INPUT:
	wd			: the directory of the mode, this value must different with others
				  such as: /config
	mode_name	: the mode name which indicates the directory
	mode_desc	: the mode description

OUTPUT:
	NA

RETURN:
	TRUE		: register success
	FALSE		: have same wd or allocate memory fail

NOTES:

HISTORY:
	Creat by wangbin 2011.6.23

**************************************************************************/
BOOL_T bc_cli_reg_mode(
	IN I8_T *wd,
	IN I8_T *mode_name,
	IN I8_T *mode_desc)
{
	return cli_dir_reg_mode(wd, mode_name, mode_desc);
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *   bc_cli_reg_cmd
 *
 * DESCRIPTION:
 *   Register a command:
 *       1. create the command node and get the begin position of parameter part
 *       2. register the command's parameter part
 *
 * INPUT:
 *   vision      : the version v1 or v2(old cli), g2 for new version
 *   cmd_desc    : the pointer of command string pointer
 *   cbfunc  	 : the command's callback function
 *   flag        : the access level and flag of command (low 8bits is the level)
 *   help_en     : english help message
 *   help_local  : chinese help message
 *   user_data   : user data as a cookie
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   TRUE : success
 *   FALSE: error when create command:
 *          empty-string or invalid-word or memory-alloc-fail or command-existed
 *          error when register parameter:
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2009-Mar-25 by wangbin -- Create
 *
*******************************************************************************/
BOOL_T bc_cli_reg_cmd
	(
	IN I8_T 			*cmd_desc,		/* the pointer of command string pointer */
	IN CLI_CMD_FUNC_T	cbfunc,			/* the command's callback function */
    IN I32_T            flag,			/* the access level and flag of command (low 8bits is the level) */
    IN I8_T 			*help_en,		/* englist help message */
    IN I8_T 			*help_local,	/* chinese help message */
    IN void 			*user_data		/* user data as a cookie */
    )
{
    return cli_core_reg_cmd(cmd_desc, cbfunc, flag, help_en, help_local, user_data);
}



/*****************************************************************************
 * FUNCTION NAME:
 *     bc_cli_dereg_cmd
 * 
 * DESCRIPTION:
 *     Deregister a command:
 *         1. find the command and its path
 *         2. free the parameter and information
 *         3. destory the command and its path (update the path's level also)
 * 
 * INPUT:
 *     cmd_desc    : the pointer of command string pointer
 * 
 * OUTPUT:
 * 	   NA
 * 	
 * RETURN:
 *     TRUE        : success
 *     FALSE       : command not exist
 * 
 * NOTES:
 * 
 * HISTORY:
 * 
*******************************************************************************/
BOOL_T bc_cli_dereg_cmd(IN I8_T *cmd_desc)
{
    return cli_core_dereg_cmd(cmd_desc);
}



/**************************************************************************
FUNCTION NAME:
    __cli2_api_display_cmd_under_dir

DESCRIPTION:
    Display all commands under this directory.

INPUT:
    session_id      : created session ID by CLI kernel
    path            : path node(NULL for root tree)
    level           : current user level
    cmd_node_name   : used to pointing command node name
    num             : number of node stored in cmd_node_name array

OUTPUT:
    cmd_node_name   : used to pointing command node name

RETURN:
    CLI_PAGE_EXIT  : user want to quit the help message.
    0               : display help message success.

NOTES:

HISTORY:
    Creat by wangbin 2011.3.2

**************************************************************************/
static I32_T __cli2_api_display_cmd_under_dir
	(
	IN I32_T 			session_id,
	IN CLI_CMD_NODE_T 	*path,
	IN UI8_T 			level,
    IN OUT I8_T 		**cmd_node_name,
    IN UI32_T 			num
    )
{
    CLI_CMD_NODE_T 	*entry;
    I32_T           	ret;
    I32_T           	i, j;

    entry = CLI_DB_Get_FirstEntry(path);
    while (entry)
    {
        j = 0;

        if ((entry->type & CLI_TYPE_CMD) && (entry->level <= level))
        {
            /* if exist callback function, this is last word node of one command */
            if (entry->callback && level >= entry->cmd_level)
            {
                for (i = 0; i < num; i++)
                {
#ifdef PRT_RET
                    if (CLI_API_Printf(session_id, "%s ", cmd_node_name[i]) == CLI_PAGE_EXIT)
                    {
                        return CLI_PAGE_EXIT;
                    }
#else
					CLI_API_Printf(session_id, "%s", entry->name);
#endif

                    j += strlen(cmd_node_name[i]) + 1;
                }

#ifdef PRT_RET
				if (CLI_API_Printf(session_id, "%s", entry->name) == CLI_PAGE_EXIT)
                {
                    return CLI_PAGE_EXIT;
                }
#else
				CLI_API_Printf(session_id, "%s", entry->name);
#endif

                j += strlen(entry->name);

                if (entry->help_en && *entry->help_en)
                {
                    while (j < 20)
                    {
#ifdef PRT_RET
                        if (CLI_API_Printf(session_id, " ") == CLI_PAGE_EXIT)
                        {
                            return CLI_PAGE_EXIT;
                        }
#else
						CLI_API_Printf(session_id, "%s", entry->name);
#endif

                        j++;
                    }

					if (cli_acc_get_lan(session_id) && entry->help_local)
                    {
#ifdef PRT_RET
                        if (CLI_API_Printf(session_id, " -- %s\r\n", entry->help_local) == CLI_PAGE_EXIT)
                        {
                            return CLI_PAGE_EXIT;
                        }
#else
						CLI_API_Printf(session_id, "%s", entry->name);
#endif
                    }
                    else
                    {
#ifdef PRT_RET
                        if (CLI_API_Printf(session_id, " -- %s\r\n", entry->help_en) == CLI_PAGE_EXIT)
                        {
                            return CLI_PAGE_EXIT;
                        }
#else
						CLI_API_Printf(session_id, "%s", entry->name);
#endif
                    }
                }
                else
                {
#ifdef PRT_RET
                    if (CLI_API_Printf(session_id, "\r\n") == CLI_PAGE_EXIT)
                    {
                        return CLI_PAGE_EXIT;
                    }
#else
					CLI_API_Printf(session_id, "%s", entry->name);
#endif
                }
            }

            cmd_node_name[num] = entry->name;
            ret = __cli2_api_display_cmd_under_dir(session_id, entry, level, cmd_node_name, num + 1);
            if (ret == CLI_PAGE_EXIT)
            {
                return ret;
            }
        }

        entry = CLI_DB_Get_NextEntry(path, entry);
    }

    return 0;
}



/**************************************************************************
FUNCTION NAME:
    CLI_API_Display_FirstNode_UnderInputPath

DESCRIPTION:
    Display first word of commands under this directory.

INPUT:
    session_id  : created session ID by CLI kernel
    path_string : path string(such as: /config)
    level       : current user level

OUTPUT:
    NA

RETURN:
    NA

NOTES:
	NA

HISTORY:
    Creat by wangbin 2011.3.2

**************************************************************************/
void CLI_API_Display_FirstNode_UnderInputPath(IN I32_T session_id, IN I8_T *path_string, IN UI8_T level)
{
    CLI_CMD_NODE_T *path_node, *entry;
    I32_T           i;

    path_node = CLI_CORE_GetView(path_string, level);

    if (path_node == (CLI_CMD_NODE_T *) CLI_NULL_PATH)
    {
        return;
    }

    entry = CLI_DB_Get_FirstEntry(path_node);
    while (entry)
    {
        i = 0;

        if ((entry->type & CLI_TYPE_CMD) && (entry->level <= level))
        {
#ifdef PRT_RET
            if (CLI_API_Printf(session_id, "%s", entry->name) == CLI_PAGE_EXIT)
            {
                return;
            }
#else
			CLI_API_Printf(session_id, "%s", entry->name);
#endif
			i += strlen(entry->name);

            if (entry->help_en && *entry->help_en)
            {
                while (i < 20)
                {
#ifdef PRT_RET
                    if (CLI_API_Printf(session_id, " ") == CLI_PAGE_EXIT)
                    {
                        return;
                    }
#else
					CLI_API_Printf(session_id, "%s", entry->name);
#endif

					i++;
                }

				if (cli_acc_get_lan(session_id) && entry->help_local)
                {
#ifdef PRT_RET
                    if (CLI_API_Printf(session_id, " -- %s\r\n", entry->help_local) == CLI_PAGE_EXIT)
                    {
                        return;
                    }
#else
					CLI_API_Printf(session_id, "%s", entry->name);
#endif
                }
                else
                {
#ifdef PRT_RET
                    if (CLI_API_Printf(session_id, " -- %s\r\n", entry->help_en) == CLI_PAGE_EXIT)
                    {
                        return;
                    }
#else
					CLI_API_Printf(session_id, "%s", entry->name);
#endif
                }
            }
            else
            {
#ifdef PRT_RET
                if (CLI_API_Printf(session_id, "\r\n") == CLI_PAGE_EXIT)
                {
                    return;
                }
#else
				CLI_API_Printf(session_id, "%s", entry->name);
#endif
            }
        }

        entry = CLI_DB_Get_NextEntry(path_node, entry);
    }
}



/**************************************************************************
FUNCTION NAME:
    CLI_API_Display_Cmd_UnderInputPath

DESCRIPTION:
    Display commands under input directory.

INPUT:
    session_id  : created session ID by CLI kernel
    path_string : path string(such as: /config)
    level       : current user level

OUTPUT:
    NA

RETURN:
    NA

NOTES:
	NA

HISTORY:
    Creat by wangbin 2011.3.2

**************************************************************************/
void CLI_API_Display_Cmd_UnderInputPath(IN I32_T session_id, IN I8_T *path_string, IN UI8_T level)
{
    CLI_CMD_NODE_T *path_node;
    I8_T            *path_node_name[CLI_MAX_CMD_WORD];

    path_node = CLI_CORE_GetView(path_string, level);

    if (path_node == (CLI_CMD_NODE_T *) CLI_NULL_PATH)
    {
        return;
    }

    __cli2_api_display_cmd_under_dir(session_id, path_node, level, path_node_name, 0);
}



/**************************************************************************
FUNCTION NAME:
    bc_cli_set_cmdpath

DESCRIPTION:
    Set the CLI command executing path.

INPUT:
    sessionID   : created session ID by CLI kernel
    path        : full path string
                    For example: "/config/config-if-port"
    path_prompt : the prompt message after entered the configured path
                    For example: "(config-if)"
    path_value  : current path's information get from input CLI parameter value

OUTPUT:
    NA

RETURN:
    TRUE        : Enter and set path success.
    FALSE       : Enter or set path fail.

NOTES:
	NA

HISTORY:
    Creat by wangbin 2011.3.2

**************************************************************************/
BOOL_T bc_cli_set_cmdpath(IN I32_T sessionID, IN I8_T *path, IN I8_T *path_prompt, IN cli_value_t *path_value)
{
    cli_sesn_t  *session;

    /* get session data */
    session = cli_sesn_get_by_sid(sessionID);
    if (NULL == session)
    {
        return FALSE;
    }

    return cli_dir_set_cmdpath(session->hdir, path, path_prompt, path_value);
}



/**************************************************************************
FUNCTION NAME:
    bc_cli_get_cmdpath

DESCRIPTION:
    Get the CLI command executing path.

INPUT:
    sessionID   : created session ID by CLI kernel

OUTPUT:
    NA

RETURN:
    current path

NOTES:
	NA

HISTORY:
    Creat by wangbin 2011.3.2

**************************************************************************/
I8_T * bc_cli_get_cmdpath(IN I32_T sessionID)
{
    cli_sesn_t  *session;

    /* get session data */
    session = cli_sesn_get_by_sid(sessionID);
    if (NULL == session)
    {
        return NULL;
    }

    return cli_dir_get_cmdpath(session->hdir);
}



/**************************************************************************
FUNCTION NAME:
    bc_cli_get_path_parameter

DESCRIPTION:
    Get the path's information.

INPUT:
    sessionID   : created session ID by CLI kernel

OUTPUT:
    NA

RETURN:
    cli_value_t : the path's information. For example
    path: /path1/path2/path3
        enter path1 use command: [root] enter path1 <parameter1>
        enter path2 use command: [path1] enter path2
        enter path3 use command: [path2] enter path3 <parameter3>
        -> after enter path3, the cli_value_t path's information is: <parameter1>-><parameter3>

NOTES:
	NA

HISTORY:
    Creat by wangbin 2011.3.2

**************************************************************************/
cli_value_t * bc_cli_get_path_parameter(IN I32_T sessionID)
{
    cli_sesn_t  *session;

    /* get session data */
    session = cli_sesn_get_by_sid(sessionID);
    if (NULL == session)
    {
        return NULL;
    }

    return CLI_DIR_Get_PathParameter(session->hdir);
}


/**************************************************************************
FUNCTION NAME:
    bc_cli_exit_curpath

DESCRIPTION:
    Exit currnt path and return to prev-path.
    If current path is EXEC(root path), return FALSE.

INPUT:
    sessionID   : created session ID by CLI kernel

OUTPUT:
    NA

RETURN:
    TRUE        : exit success
    FALSE       : current path is EXEC(root path)

NOTES:
	NA

HISTORY:
    Creat by wangbin 2011.3.7

**************************************************************************/
BOOL_T bc_cli_exit_curpath(IN I32_T sessionID)
{
    cli_sesn_t  *session;

    /* get session data */
    session = cli_sesn_get_by_sid(sessionID);
    if (NULL == session)
    {
        return FALSE;
    }

    return CLI_DIR_Free_LastPathNode(session->hdir);
}



/**************************************************************************
FUNCTION NAME:
    CLI_API_Set_SessionQuitFlag

DESCRIPTION:
    Set the session of CLI kernel quit flag.

INPUT:
    sessionID       : mapped session ID for other modules used
    quit_flag       : if quit the session
    quit_reason     : quit reason
                      the value is in bc_cli_vkey.h ->
                      CLI_VKEY_IO_CLOSED
                      CLI_VKEY_IO_TIMEOUT
                      ...

OUTPUT:
    NA

RETURN:
    TRUE            : set success
    FALSE           : the session is not exist

NOTES:

HISTORY:

**************************************************************************/
BOOL_T CLI_API_Set_SessionQuitFlag(IN I32_T sessionID, IN BOOL_T quit_flag, IN I32_T quit_reason)
{
    cli_sesn_t  *session;

    /* get session data */
    session = cli_sesn_get_by_sid(sessionID);
    if (NULL == session)
    {
        return FALSE;
    }

    session->quit_flag   = quit_flag;
    session->quit_reason = quit_reason;

    return TRUE;
}



/**************************************************************************
FUNCTION NAME:
    CLI_API_Get_SessionQuitFlag

DESCRIPTION:
    Get the session of CLI kernel quit flag.

INPUT:
    sessionID       : mapped session ID for other modules used

OUTPUT:
    quit_flag       : if quit the session
    quit_reason     : quit reason
                      the value is in bc_cli_vkey.h ->
                      CLI_VKEY_IO_CLOSED
                      CLI_VKEY_IO_TIMEOUT
                      ...

RETURN:
    TRUE            : get success
    FALSE           : the session is not exist

NOTES:

HISTORY:

**************************************************************************/
BOOL_T CLI_API_Get_SessionQuitFlag(IN I32_T sessionID, OUT BOOL_T *quit_flag, OUT I32_T *quit_reason)
{
    cli_sesn_t  *session;

    /* get session data */
    session = cli_sesn_get_by_sid(sessionID);
    if (NULL == session)
    {
        return FALSE;
    }

    *quit_flag   = session->quit_flag;
    *quit_reason = session->quit_reason;

    return TRUE;
}



BOOL_T CLI_KP_Check_Closing(IN const I32_T sessionID)
{
	BOOL_T bQuit;
	I32_T quitFlag;

	if (CLI_API_Get_SessionQuitFlag(sessionID, &bQuit, &quitFlag))
	{
		return bQuit;
	}

	return TRUE;
}



BOOL_T CLI_KP_Set_bRunEnvCfg(BOOL_T bRun)
{
	l_run_env_cfg_rs232 = bRun;
	return TRUE;
}



BOOL_T CLI_KP_Get_bRunEnvCfg(void)
{
	return l_run_env_cfg_rs232;
}



/*------------------------------------------------------------------------
 * Function   : CLI_KP_IS_Show_LogoutInfo
 * Purpose    : Get whether show CLI logout print information
 * Parameters :
 *     Input  : NA
 *     Output : NA
 * Returns    : if is true, show logout info, else not show logout info
 *------------------------------------------------------------------------
 */
BOOL_T CLI_KP_IS_Show_LogoutInfo(void)
{
	return l_show_logout_info;
}



/*------------------------------------------------------------------------
 * Function   : CLI_KP_Set_Show_LogoutInfo_FLAG
 * Purpose    : Set whether show CLI logout print information
 * Parameters :
 * Input   : Flag :if is true, show logout info, else not show logout info
 * Output:  NA
 * Returns:  NA
 *------------------------------------------------------------------------
 */
void CLI_KP_Set_Show_LogoutInfo_FLAG(IN BOOL_T flag)
{
	l_show_logout_info = flag;
}



/*------------------------------------------------------------------------
 * Function   : CLI_KP_Get_AP_comingFrom
 * Purpose    : Set PromptType
 * Parameters :
 *    Input   : sessionID = session identifier
 *
 *    Output  : NA
 * Returns    : cli_come_from_e {
 *              CLI_COME_FROM_UNKNOWN = 1,
 *              CLI_COME_FROM_CONSOLE,
 *              CLI_COME_FROM_LOGON,
 *              CLI_COME_FROM_TELNET,
 *              CLI_COME_FROM_SSH }
 *------------------------------------------------------------------------
 */
cli_come_from_e CLI_KP_Get_AP_comingFrom(IN const I32_T sessionID)
{
	switch (cli_sesn_get_type(sessionID))
	{
	case CLI_SESN_TYPE_CONSOLE:
		return CLI_COME_FROM_CONSOLE;

	case CLI_SESN_TYPE_TELNET:
		return CLI_COME_FROM_TELNET;

	case CLI_SESN_TYPE_SSH:
		return CLI_COME_FROM_SSH;

#if 0 // no warning
	case CLI_IO_DEBUG:
	case CLI_IO_WINTEST:
		return CLI_COME_FROM_CONSOLE;
#endif

	default:
		return CLI_COME_FROM_UNKNOWN;
	}
}



void CLI_KP_Logout(void)
{
	/* just for console */
	if (CLI_API_Check_Session(VT_RS232_CHANNEL) == FALSE)
	{
		return;
	}

	CLI_API_Set_SessionQuitFlag(VT_RS232_CHANNEL, TRUE, CLI_API_RET_QUIT_SESSION);
	cli_acc_set_lvl(VT_RS232_CHANNEL, CLI_ACC_LVL_BASIC);
}



/*------------------------------------------------------------------------
 * Function   : bc_cli_close_sesn
 * Purpose    : Close session
 * Parameters :
 *    Input   : sessionID = session identifier
 *    Output  : NA
 * Returns    : NA
 *------------------------------------------------------------------------
 */
void bc_cli_close_sesn(const int  session_id, CLI_KP_ClOSE_EVENT_T event)
{
	if (CLI_API_Check_Session(session_id) == FALSE)
	{
		return;
	}

	CLI_API_Set_SessionQuitFlag(session_id, TRUE, CLI_API_RET_QUIT_SESSION);

	/* check if it had login */
	if (cli_acc_get_lvl(session_id) <= CLI_ACC_LVL_BASIC)
	{
		return;
	}

	cli_acc_set_lvl(session_id, CLI_ACC_LVL_BASIC);

	return;
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *   bc_cli_set_usr_lvl
 *
 * DESCRIPTION:
 *   Set level of the current access user
 *
 * INPUT:
 *   session_id -- session ID
 *   level      -- new level
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   TRUE
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2009-Mar-19 by wangbin -- Create
 *
*******************************************************************************/
BOOL_T bc_cli_set_usr_lvl(const int session_id, const UI32_T level)
{
	cli_acc_set_lvl(session_id, (UI8_T)level);
	return TRUE;
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *   bc_cli_get_usr_lvl
 *
 * DESCRIPTION:
 *   Get current level
 *
 * INPUT:
 *   session_id -- session ID
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   current level
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2009-Mar-19 by wangbin -- Create
 *
*******************************************************************************/
UI32_T bc_cli_get_usr_lvl(const int session_id)
{
	return cli_acc_get_lvl(session_id);
}



BOOL_T bc_cli_get_usr_info(cli_usr_info_t *pEntry)
{
	CLI_ACC_INFO_T ptrAccInfo;

	if (pEntry == NULL)
	{
		return FALSE;
	}

	CLI_ACC_GetAllInfo(pEntry->sessionID, &ptrAccInfo);

	pEntry->ipAddress = ptrAccInfo.ipaddr;
	if (ptrAccInfo.is_ipv6)
	{
		pEntry->ip6Flag = 1;
		memcpy(pEntry->ip6Address, (UI8_T *)&ptrAccInfo.ipv6addr, sizeof(pEntry->ip6Address));
	}
	else
	{
		pEntry->ip6Flag = 0;
		memset(pEntry->ip6Address, 0, sizeof(pEntry->ip6Address));
	}
	pEntry->level = ptrAccInfo.level;
	pEntry->loginTime = ptrAccInfo.login_systemTime;
	memcpy(pEntry->name, ptrAccInfo.login_name, BNR_CPU_NAME_MAX_LEN);
#if RADIUS_ACCOUNTING_INCLUDED
	pEntry->usermethod = ptrAccInfo.usermethod;
#endif

	return TRUE;
}



BOOL_T bc_cli_get_usr_first_info(cli_usr_info_t *pEntry)
{
	CLI_ACC_INFO_T ptrAccInfo;

	if (pEntry == NULL)
	{
		return FALSE;
	}

	pEntry->sessionID = CLI_ACC_GetFirstInfo(&ptrAccInfo);
	if (pEntry->sessionID < 0)
	{
		return FALSE;
	}

	pEntry->ipAddress = ptrAccInfo.ipaddr;
	if (ptrAccInfo.is_ipv6)
	{
		pEntry->ip6Flag = 1;
		memcpy(pEntry->ip6Address, (UI8_T *)&ptrAccInfo.ipv6addr, sizeof(pEntry->ip6Address));
	}
	else
	{
		pEntry->ip6Flag = 0;
		memset(pEntry->ip6Address, 0, sizeof(pEntry->ip6Address));
	}

	pEntry->level = ptrAccInfo.level;
	pEntry->loginTime = ptrAccInfo.login_systemTime;
	memcpy(pEntry->name, ptrAccInfo.login_name, BNR_CPU_NAME_MAX_LEN);
#if RADIUS_ACCOUNTING_INCLUDED
	pEntry->usermethod = ptrAccInfo.usermethod;
#endif

	return TRUE;
}



BOOL_T bc_cli_get_usr_next_info(cli_usr_info_t *pEntry)
{
	CLI_ACC_INFO_T ptrAccInfo;

	if (pEntry == NULL)
	{
		return FALSE;
	}

	pEntry->sessionID = CLI_ACC_GetNextInfo(pEntry->sessionID, &ptrAccInfo);
	if (pEntry->sessionID < 0)
	{
		return FALSE;
	}

	pEntry->ipAddress = ptrAccInfo.ipaddr;
	if (ptrAccInfo.is_ipv6)
	{
		pEntry->ip6Flag = 1;
		memcpy(pEntry->ip6Address, (UI8_T *)&ptrAccInfo.ipv6addr, sizeof(pEntry->ip6Address));
	}
	else
	{
		pEntry->ip6Flag = 0;
		memset(pEntry->ip6Address, 0, sizeof(pEntry->ip6Address));
	}
	pEntry->level = ptrAccInfo.level;
	pEntry->loginTime = ptrAccInfo.login_systemTime;
	memcpy(pEntry->name, ptrAccInfo.login_name, BNR_CPU_NAME_MAX_LEN);
#if RADIUS_ACCOUNTING_INCLUDED
	pEntry->usermethod = ptrAccInfo.usermethod;
#endif

	return TRUE;
}



BOOL_T bc_cli_get_usr_name(
        const int   session_id,
        I8_T        *name)
{
	CLI_ACC_INFO_T ptrAccInfo;

	CLI_ACC_GetAllInfo(session_id, &ptrAccInfo);

	if (ptrAccInfo.login_name[0])
	{
		memcpy(name, ptrAccInfo.login_name, sizeof(ptrAccInfo.login_name));
	}
	else
	{
		strcpy(name, CLI_ACC_ANONYMOUS_NAME);
	}

	return TRUE;
}



void bc_cli_close_all_sesn(void)
{
	CLI_ACC_INFO_T ptrAccInfo;
	I32_T sessionID;

	sessionID = CLI_ACC_GetFirstInfo(&ptrAccInfo);

	/*get all connected session*/
	while (sessionID >= 0)
	{
		bc_cli_close_sesn(sessionID, CLI_KP_LOGOUT);
		sessionID = CLI_ACC_GetNextInfo(sessionID, &ptrAccInfo);
	}
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *   bc_cli_clear_screen
 *
 * DESCRIPTION:
 *   Clear the whole screen and move the cursor top left corner
 *
 * INPUT:
 *   session_id -- session ID
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   TRUE       : clear success
 *   FALSE      : don't have clear callback function
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *
*******************************************************************************/
BOOL_T bc_cli_clear_screen(IN I32_T session_id)
{
    cli_sesn_t  *session;

    session = cli_sesn_get_by_sid(session_id);
    if (NULL == session)
    {
        return FALSE;
    }

    return CLI_VIO_Erase(session->hvio, CLI_SCREEN_CLEAR);
}



/**************************************************************************
FUNCTION NAME:
    CLI_API_Get_Hterm

DESCRIPTION:
    Get the terminal IO struct

INPUT:
    sessionID   : the mapped session ID

OUTPUT:
    NA

RETURN:
    the terminal IO struct for using IO modules such as Telnet RS232 SSH and so on
    NULL        : the terminal IO in the session is null

NOTES:
	NA

HISTORY:

**************************************************************************/
CLI_TERMINAL_IO_T * CLI_API_Get_Hterm(IN I32_T sessionID)
{
    cli_sesn_t  *session;

    /* get session data */
    session = cli_sesn_get_by_sid(sessionID);
    if (NULL == session)
    {
        return NULL;
    }

    return CLI_VIO_Get_Hterm(session->hvio);
}



/**************************************************************************
FUNCTION NAME:
    CLI_API_Set_Hterm

DESCRIPTION:
    Set the terminal IO struct in the session

INPUT:
    sessionID   : the mapped session ID
    hterm       : the terminal IO struct for using IO modules
                  such as Telnet RS232 SSH and so on

OUTPUT:
    NA

RETURN:
    TRUE    : set success
    FALSE   : the terminal IO in the session is null

NOTES:
	NA

HISTORY:

**************************************************************************/
BOOL_T CLI_API_Set_Hterm(IN I32_T sessionID, IN CLI_TERMINAL_IO_T *hterm)
{
    cli_sesn_t  *session;

    /* get session data */
    session = cli_sesn_get_by_sid(sessionID);
    if (NULL == session)
    {
        return FALSE;
    }

    return CLI_VIO_Set_Hterm(session->hvio, hterm);
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_API_Getc
 *
 * DESCRIPTION:
 *   Get the input character from session
 *
 * INPUT:
 *   session_id -- session ID created by cli2 kernel
 *   timeout    -- timeout millisecond seconds for geting input charcater
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   CLI_VKEY_IO_CLOSED   : IO closed
 *   CLI_VKEY_IO_TIMEOUT  : timeout
 *   CLI_VKEY_IO_NOACTION : no action (the input function is null)
 *   CLI_VKEY_IO_EXITCMD  : exit cmd
 *   >0                    : input character
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2009-May-27 by wangbin -- Create
 *
*******************************************************************************/
I32_T CLI_API_Getc(IN I32_T session_id, IN I32_T timeout_msec)
{
    cli_sesn_t  *session;

    session = cli_sesn_get_by_sid(session_id);
    if (NULL == session)
    {
        return CLI_VKEY_IO_WRONGVALUE;
    }

    return CLI_VIO_Getc(session->hvio, timeout_msec);
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_API_Puts
 *
 * DESCRIPTION:
 *   Print a string in <str> to terminal associated by session_id
 *
 * INPUT:
 *   session_id -- identifier for session
 *   str        -- string for output
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   NA
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2009-Mar-25 by wangbin -- Create
 *
*******************************************************************************/
void CLI_API_Puts(IN I32_T session_id, IN const I8_T *str)
{
    cli_sesn_t  *session;

    session = cli_sesn_get_by_sid(session_id);
    if (session)
    {
        CLI_VIO_Puts(session->hvio, str, strlen(str));
    }

	return;
}

/**************************************************************************
FUNCTION NAME:
	VT_Get_Char

DESCRIPTION:
	Get virtual terminal input charl.

INPUT:
	sessionID	: session ID created by CLIG2 kernel
	timeout		: timeout for get char

OUTPUT:

RETURN:
	virtual terminal input char

NOTES:

HISTORY:

**************************************************************************/
I32_T VT_Get_Char(IN I32_T sessionID, IN I32_T timeout)
{
	return CLI_API_Getc(sessionID, timeout);
}



/**************************************************************************
FUNCTION NAME:
	VT_Put_String

DESCRIPTION:
	Put input string to virtual terminal.

INPUT:
	sessionID	: session ID created by CLIG2 kernel
	string		: string need to print
	length		: string length

OUTPUT:

RETURN:
	None

NOTES:

HISTORY:

**************************************************************************/
void VT_Put_String(IN I32_T sessionID, IN const I8_T *string, IN I32_T length)
{
	CLI_TERMINAL_IO_T *terminal;
	I32_T i;

	//if (UTL_COM_CheckComPortLoopback() == TRUE)
	//{
	//	return;
	//}

	if (sessionID == VT_BROCAST_CHANNEL)
	{
		for (i = 0; i < VT_MAX_IO_CHANNEL; i ++)
		{
			if (CLI_API_Check_Session(i) == FALSE)
			{
				continue;
			}

			terminal = CLI_API_Get_Hterm(i);
			if (terminal && terminal->putstr)
			{
				(*terminal->putstr)(i, (UI8_T *)string, length);
			}
		}
	}
	else
	{
		if (CLI_API_Check_Session(sessionID) == FALSE)
		{
			return;
		}

		terminal = CLI_API_Get_Hterm(sessionID);
		if (terminal && terminal->putstr)
		{
			(*terminal->putstr)(sessionID, (UI8_T *)string, length);
		}
	}
}



/**************************************************************************
FUNCTION NAME:
	VT_Move_CursorUp

DESCRIPTION:
	Move Cursor up by the specified number of columns.

INPUT:
	sessionID	: cli session ID
	columns		: move coursor n columns up.

OUTPUT:
	None

RETURN:
	None

NOTES:

HISTORY:

**************************************************************************/
void VT_Move_CursorUp(IN I32_T sessionID, IN I32_T columns)
{
	VT_100_Move_CursorUp(sessionID, columns);
} /* end of VT_Move_CursorUp */



/**************************************************************************
FUNCTION NAME:
	VT_Move_CursorDown

DESCRIPTION:
	Move Cursor down by the specified number of columns.

INPUT:
	sessionID	: cli session ID
	columns		: move coursor n columns down.

OUTPUT:
	None

RETURN:
	None

NOTES:

HISTORY:

**************************************************************************/
void VT_Move_CursorDown(IN I32_T sessionID, IN I32_T columns)
{
	VT_100_Move_CursorDown(sessionID, columns);
} /* end of VT_Move_CursorDown */



/**************************************************************************
FUNCTION NAME:
	VT_Analysis_Keystroke

DESCRIPTION:
	Analysis keystroke.

INPUT:
	sessionID		: CLI session
	ptrKeystrokeState	: the state of keystroke
	rxChr			: input char

OUTPUT:
	None

RETURN:
	analysed keystroke

NOTES:

HISTORY:

**************************************************************************/
I32_T VT_Analysis_Keystroke(
	IN I32_T sessionID,
	IN UI8_T *ptrKeystrokeState,
	IN I32_T rxChr)
{
	if (sessionID){}

	return VT_100_Analysis_Keystroke(ptrKeystrokeState, rxChr);
}



/**************************************************************************
FUNCTION NAME:
	VT_100_Erase_Line

DESCRIPTION:
	Erase Text on the VT100 Screen.

INPUT:
	sessionID	: cli session ID
	erase_mode	: 0 = Erase from the cursor to the end of the line.
				  1 = Erase from the beginning of the line to the cursor.
				  2 = Clears the line but do not moves the cursor position.

OUTPUT:
	None

RETURN:
	None

NOTES:

HISTORY:
	Creat by wangbin 2009.11.19

**************************************************************************/
void VT_100_Erase_Line(IN I32_T sessionID, IN VT_ERASE_MODE_T erase_mode)
{
	I8_T  escape_str[5], *temp_ptr ;

	temp_ptr = escape_str ;
	*temp_ptr++ = CLI_VKEY_ESC ;
	*temp_ptr++ = '[' ;
	//temp_ptr += TRAN_I32toA( temp_ptr, erase_mode, 10 );
	temp_ptr += sprintf(temp_ptr, "%d", erase_mode);
	*temp_ptr++ = 'K' ;
	*temp_ptr = VT_NULL ;

	VT_Put_String(sessionID, escape_str, strlen(escape_str));
}



/**************************************************************************
FUNCTION NAME:
	VT_Erase_Line

DESCRIPTION:
	Erase Text on the screen.

INPUT:
	sessionID	: cli session ID
	erase_mode	: 0 = Erase from the cursor to the end of the line.
				  1 = Erase from the beginning of the line to the cursor.
				  2 = Clears the line but do not moves the cursor position.

OUTPUT:
	None

RETURN:
	None

NOTES:

HISTORY:

**************************************************************************/
void VT_Erase_Line(IN I32_T sessionID, IN VT_ERASE_MODE_T erase_mode)
{
	VT_100_Erase_Line(sessionID, erase_mode);
}


/**************************************************************************
FUNCTION NAME:
	VT_Check_InputBufferEmpty

DESCRIPTION:
	Check if the input buffer is empty.

INPUT:
	sessionID	: session ID created by CLIG2 kernel

OUTPUT:
	None

RETURN:
	I32_T

NOTES:

HISTORY:

**************************************************************************/
I32_T VT_Check_InputBufferEmpty(IN I32_T sessionID)
{
	CLI_TERMINAL_IO_T *terminal;

	if (CLI_API_Check_Session(sessionID) == FALSE)
	{
		return 1;
	}

	terminal = CLI_API_Get_Hterm(sessionID);
	if (terminal && terminal->checkEmpty)
	{
		return (*terminal->checkEmpty)(sessionID);
	}

	return 1;
}



/*------------------------------------------------------------------------
 * Function   : cli_edit_get_input_event
 * Purpose    : get input character and polling other event
 * Parameters :
 *    Input   : sessionID = session identifier
 *              timeoutSec = timeout second
 *              bReGetTimeOut = is get newest timeout
 *    Output  : *pRxCh = output charater
 *
 * Returns    : not define
 *------------------------------------------DLKS------------------------------
 */
static BOOL_T cli_edit_get_input_event(
	IN const I32_T sessionID,
	IN UI32_T timeoutSec,
	IN BOOL_T bReGetTimeOut,
	OUT I32_T *pRxCh)
{
	UI32_T lastTime, nowTime, diffTime;
	I32_T rxChr;

	bc_platform_time_sec_get(&lastTime);

	for (;;)
	{
		if (CLI_KP_Check_Closing(sessionID))
		{
			rxChr = CLI_VKEY_IO_CLOSED;
			break;
		}

		rxChr = VT_Get_Char(sessionID, 500);
		if (rxChr == CLI_VKEY_IO_TIMEOUT)
		{
			if (bReGetTimeOut == TRUE )
			{
				timeoutSec = bc_cli_get_sesntimeout(sessionID);
			}

			/* never timeout */
			if (timeoutSec == 0)
			{
				continue;
			}

			bc_platform_time_sec_get(&nowTime);
			if (nowTime >=  lastTime) /* normal */
			{
				diffTime =  nowTime - lastTime;
			}
			else /* turn over */
			{
				diffTime = 0xFFFFFFFF - lastTime + nowTime + 1;
			}

			if (diffTime > timeoutSec)
			{
				break;
			}
		}
		else
		{
			break;
		}
	}

	if (rxChr == CLI_VKEY_ESC)
	{
		/* Identify the ESC key */
		if (VT_Check_InputBufferEmpty(sessionID) == 0)
		{
			/* re-define the 'ESC' key to 'F4' */
			rxChr = CLI_VKEY_F4;
		}
	}

	*pRxCh = rxChr;
	return TRUE;
}



/*------------------------------------------------------------------------
 * Function   : CLI_EDIT_Get_PageAction
 * Purpose    : get user key in character
 * Parameters :
 *    Input   : sessionID = session identifier
 *              timoutSec = 0 : use session time out
 *                          other :the time out second
 *    Output    pAction = return action
 * Returns :    TRUE = return action
 *              FALSE = other return reason (timeout)
 *------------------------------------------------------------------------
 */
BOOL_T CLI_EDIT_Get_PageAction(
	IN I32_T sessionID,
	IN UI32_T timeoutSec,
	OUT cli_page_act_e *pAction)
{
	UI8_T  	keystrokeState = CLI_VT100_WAIT_FOR_KEYSTROKE;
	BOOL_T 	bReGetSetting;
	I32_T 	rxChr = 0;

	if (timeoutSec == 0)
	{
		bReGetSetting = TRUE;
	}
	else
	{
		bReGetSetting = FALSE;
	}

	for (;;)
	{
		cli_edit_get_input_event(sessionID, timeoutSec, bReGetSetting, &rxChr);

		switch (rxChr)
		{
		case CLI_VKEY_IO_TIMEOUT : /*-2 */
			if (bReGetSetting == TRUE)
			{
				bc_cli_close_sesn(sessionID, CLI_KP_TIMEOUT);
			}
			*pAction = CLI_PAGE_TIMEOUT;
			break;

		case CLI_VKEY_IO_CLOSED :  /*-1 telnet quit*/
			if (bReGetSetting == TRUE)
			{
				bc_cli_close_sesn(sessionID, CLI_KP_TIMEOUT);
			}
			*pAction = CLI_PAGE_EXIT;
			break;

		case CLI_VKEY_IO_EXITCMD:
			*pAction = CLI_PAGE_EXIT;
			break;

		case CLI_VKEY_IO_NOTIFY:
			*pAction = CLI_PAGE_NOTIFY;
			break;

		case CLI_VKEY_IO_NOACTION: /* nothing to do */
			break;

		default:
			if (rxChr > 0)
			{
				rxChr = VT_Analysis_Keystroke(sessionID, &keystrokeState, rxChr);

				if (rxChr != VT_NULL)
				{
					switch (rxChr)
					{
						case 'q':
						case 'Q':
						case CLI_VKEY_FUN4:
						case CLI_VKEY_CTRL_C:
							*pAction = CLI_PAGE_EXIT;
							break;

						case CLI_VKEY_IO_TIMEOUT:
							*pAction = CLI_PAGE_TIMEOUT;
							break;

						case 'p':
						case 'P':
							*pAction = CLI_PAGE_UP;
							break;

						case 'n':
						case 'N':
						case CLI_VKEY_SPACE:
							*pAction = CLI_PAGE_DOWN;
							break;

						case 'r':
						case 'R':
							*pAction = CLI_PAGE_REFRESH;
							break;

						case 'a':
						case 'A':
							*pAction = CLI_PAGE_ALL;
							break;

						case CLI_VKEY_CR:
							*pAction = CLI_PAGE_NEXTLINE;
							break;

						default:
							continue;
					}

					return TRUE;
				}
			}
		}

		if ((rxChr == CLI_VKEY_IO_TIMEOUT) || (rxChr == CLI_VKEY_IO_CLOSED) || (rxChr == CLI_VKEY_IO_EXITCMD) || (rxChr == CLI_VKEY_IO_NOTIFY))
		{
			break;
		}
	}

	return FALSE;
}




/*------------------------------------------------------------------------
 * Function:    CLI_PRT_Start_Paging
 * Purpose:     start paging function
 * Parameters:
 *    Input:    sessionID = session identifier
 *              timoutSec = timeout second
 *    Output:   None
 * Returns:     TRUE
 *------------------------------------------------------------------------
 */
cli_page_act_e CLI_PRT_Start_Paging(
	IN const I32_T sessionID,
	IN UI32_T timoutSec)
{
	CLI_ACC_CURSOR_STATUS_T 	prtState;
	I32_T  						i, j, clearCnt;
	cli_page_act_e 				action;
	UI32_T 						freshTimeoutSec;
	static UI32_T 				headerCnt[VT_CHANNEL_LAST];
	static UI32_T 				freshTime[VT_CHANNEL_LAST];

	if (sessionID >= VT_CHANNEL_LAST)
	{
		return CLI_PAGE_EXIT;
	}

	CLI_ACC_GetCursorStatus(sessionID, &prtState);

	switch (prtState.refresh_action)
	{
	case 0: /* frist time print */
		headerCnt[sessionID] = prtState.line;
		freshTime[sessionID] = 0;
		prtState.refresh_action = 1;
		prtState.column = 0;
		prtState.line = 0;
		prtState.page_action = CLI_PAGE_REFRESH;
		CLI_ACC_SetCursorStatus(sessionID, &prtState);
		return CLI_PAGE_REFRESH;

	case 1: /* second time print */
		prtState.refresh_action = 2;

		for (i = prtState.line; i < (I32_T)(CLI_UTL_PRINT_MAX_PAGE_LINES - 1 - headerCnt[sessionID]); i++ )
		{
			VT_Put_String(sessionID, "\n\r", 2);
		}

		/* add bottom */
		VT_Put_String(sessionID, l_page_prompt, strlen(l_page_prompt));
		/* add the line number of bottom */
		i++;
		break;

	case 2: /* other */
	default:
		for (i = prtState.line; i < (I32_T)(CLI_UTL_PRINT_MAX_PAGE_LINES - 1 - headerCnt[sessionID]); i++ )
		{
			VT_Put_String(sessionID,"\n\r", 2);
			VT_Erase_Line(sessionID, VT_COMPLETE_ERASE);
		}
		break;
	}

	for (;;)
	{
		CLI_EDIT_Get_PageAction(sessionID,timoutSec,&action);

		switch (action)
		{
			case CLI_PAGE_UP:
			case CLI_PAGE_DOWN:
			case CLI_PAGE_REFRESH:
			case CLI_PAGE_TIMEOUT:
				if (i > 0)
				{
					VT_Move_CursorUp(sessionID, i);
					/* clear the old print message */
					clearCnt = ((CLI_UTL_PRINT_MAX_PAGE_LINES - 1 - headerCnt[sessionID]) > i)?
								i : (CLI_UTL_PRINT_MAX_PAGE_LINES - 1 - headerCnt[sessionID]);
					for (j = 0; j < clearCnt; j++)
					{
						VT_Put_String(sessionID,"\n\r", 2);
						VT_Erase_Line(sessionID, VT_COMPLETE_ERASE);
					}
					VT_Move_CursorUp(sessionID, clearCnt);
				}
				prtState.line = 0;
				prtState.column = 0;

				if (action == CLI_PAGE_TIMEOUT)
				{
					freshTime[sessionID] += timoutSec;
					freshTimeoutSec = bc_cli_get_sesntimeout(sessionID);
					if ((freshTime[sessionID] > freshTimeoutSec) && (freshTimeoutSec !=0))
					{
						bc_cli_close_sesn(sessionID, CLI_KP_TIMEOUT);
					}
				}
				else
				{
					freshTime[sessionID] = 0;
				}
				break;

			case CLI_PAGE_EXIT:
				/*  clear the prompt message on telnet when input "Q", "ESC" etc */
				i = CLI_UTL_PRINT_MAX_PAGE_LINES - (i + headerCnt[sessionID]);

				if (i > 0)
				{
					VT_Move_CursorDown(sessionID, i);
				}
				if (i < 0)
				{
					VT_Move_CursorUp(sessionID, 1);
				}
				VT_Put_String(sessionID,"\r", 1);
				VT_Erase_Line(sessionID, VT_COMPLETE_ERASE);
				VT_Move_CursorUp( sessionID, 1);
				freshTime[sessionID] = 0;
				prtState.page_action = CLI_PAGE_NOACTION;
				break;

			case CLI_PAGE_NOTIFY:
				VT_Put_String(sessionID,"\n\r", 2);
				freshTime[sessionID] = 0;
				prtState.page_action = CLI_PAGE_NOACTION;
				action = CLI_PAGE_EXIT;
				break;

			default:
				freshTime[sessionID] = 0;
				continue;
		}

		CLI_ACC_SetCursorStatus(sessionID, &prtState);
		return action;
	}
}



/**************************************************************************
FUNCTION NAME:
	CLI_BNR_Trans_AccLevel_To_String

DESCRIPTION:
	Translate user account access level to string.

INPUT:
	acclevel		: the value of user account access level

OUTPUT:
	level_string	: the pointer of buffer used to store string

RETURN:
	the size of translated string

NOTES:
	Added for displaying access level in string.

HISTORY:
	Added by wangbin 2009.11.6

**************************************************************************/
UI32_T CLI_BNR_Trans_AccLevel_To_String(OUT I8_T *level_string, IN I32_T acclevel)
{
	/*just translate for customer level other level will display number*/
	switch (acclevel)
	{
	case CLI_ACC_LVL_USER:
		strcpy(level_string, "user");
		break;

	case CLI_ACC_LVL_PUSER:
		strcpy(level_string, "puser");
		break;

	case CLI_ACC_LVL_ADMIN:
		strcpy(level_string, "admin");
		break;

	default:
		if (acclevel < CLI_ACC_LVL_USER)
		{
			strcpy(level_string, "login");
		}
		else
		{
			sprintf(level_string, "%d", acclevel);
		}
		break;
	}

	return strlen(level_string);
}



/**************************************************************************
FUNCTION NAME:
    bc_cli_set_hist_state

DESCRIPTION:
    Set the history state of CLI module

INPUT:
    sessionID   : the mapped session ID
    bEnable     : TRUE  -> open the history function of CLI module
                  FALSE -> close the history function of CLI module

OUTPUT:
    NA

RETURN:
    TRUE    : set success
    FALSE   : the terminal IO in the session is null

NOTES:
	NA

HISTORY:

**************************************************************************/
BOOL_T bc_cli_set_hist_state(IN I32_T sessionID, IN BOOL_T bEnable)
{
    cli_sesn_t  *session;

    /* get session data */
    session = cli_sesn_get_by_sid(sessionID);
    if (NULL == session)
    {
        return FALSE;
    }

    CLI_HIST_SetState(session->hhist, bEnable);

    return TRUE;
}



/**************************************************************************
FUNCTION NAME:
    bc_cli_get_hist_state

DESCRIPTION:
    Get the history state of CLI module

INPUT:
    sessionID   : the mapped session ID

OUTPUT:
    bEnable     : TRUE  -> open the history function of CLI module
                  FALSE -> close the history function of CLI module

RETURN:
    TRUE    : get success
    FALSE   : the terminal IO in the session is null

NOTES:
	NA

HISTORY:

**************************************************************************/
BOOL_T bc_cli_get_hist_state(IN I32_T sessionID, OUT BOOL_T *bEnable)
{
    cli_sesn_t  *session;

    /* get session data */
    session = cli_sesn_get_by_sid(sessionID);
    if (NULL == session)
    {
        return FALSE;
    }

    *bEnable = CLI_HIST_GetState(session->hhist);

    return TRUE;
}



/**************************************************************************
FUNCTION NAME:
    bc_cli_set_hist_size

DESCRIPTION:
    Set the history command size of CLI module

INPUT:
    sessionID   : the mapped session ID
    size        : history command size

OUTPUT:
    NA

RETURN:
    TRUE    : set success
    FALSE   : the terminal IO in the session is null

NOTES:
	NA

HISTORY:

**************************************************************************/
BOOL_T bc_cli_set_hist_size(IN I32_T sessionID, IN UI32_T size)
{
    cli_sesn_t  *session;

    /* get session data */
    session = cli_sesn_get_by_sid(sessionID);
    if (NULL == session)
    {
        return FALSE;
    }

    session->hhist = CLI_HIST_SetSize(session->hhist, size);

    return TRUE;
}


#if 0
/*******************************************************************************
 *
 * FUNCTION NAME:
 *   bc_cli_show_all_hist
 *
 * DESCRIPTION:
 *   Show all histories
 *
 * INPUT:
 *  session_id -- session ID
 *  start      -- TRUE(return the first item in the history buffer)
 *                FALSE (return the next item in the history buffer) *
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   not NULL -- the pointer of the history buffer,
 *   NULL     -- There is no more item in the history buffer, the operation may be stopped
 *
 * NOTES:
 *   Usage:
 *        {
 *           I8_T *p;
 *
 *           p = bc_cli_show_all_hist (session_id, TRUE);
 *           printf ("%s\n", p);
 *           while ((p = bc_cli_show_all_hist (h_hist, FALSE)) != NULL)
 *           {
 *               CLI_API_Printf (session_id, "%s\n", p);
 *           }
 *        }
 *
 * HISTORY:
 *   2009-May-05 by wangbin -- Create
 *
*******************************************************************************/
I8_T * bc_cli_show_all_hist(IN I32_T session_id, IN BOOL_T start)
{
    HANDLE_T        h_hist;
    cli_sesn_t  *session;

    session = cli_sesn_get_by_sid(session_id);
    if (NULL == session)
    {
        return NULL;
    }

    h_hist = session->hhist;
    return CLI_HIST_ShowAllHist(h_hist, start);
}



/**************************************************************************
FUNCTION NAME:
    bc_cli_set_paging

DESCRIPTION:
    Set global cli paging state.

INPUT:
    paging_state    : global paging state(TRUE: enable, FALSE: disable)

OUTPUT:
    NA

RETURN:
    NA

NOTES:
	NA

HISTORY:

**************************************************************************/
void bc_cli_set_paging(IN BOOL_T paging_state)
{
    l_page_state = paging_state;
}



/**************************************************************************
FUNCTION NAME:
    bc_cli_get_paging

DESCRIPTION:
    Get global cli paging state.

INPUT:
    NA

OUTPUT:
    NA

RETURN:
    global cli paging state

NOTES:
	NA

HISTORY:

**************************************************************************/
BOOL_T bc_cli_get_paging(void)
{
    return l_page_state;
}
#endif


/*******************************************************************************
 *
 * FUNCTION NAME:
 *   bc_cli_get_lan
 *
 * DESCRIPTION:
 *   Get cli language
 *
 * INPUT:
 *   NA
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   TRUE  -- Use local language
 *   FALSE -- Use English
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2014-05-26 by wangbin -- Create
 *
*******************************************************************************/
cli_lan_t bc_cli_get_lan(void)
{
	return l_language;
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *   cli_acc_set_lan
 *
 * DESCRIPTION:
 *   Set help language
 *
 * INPUT:
 *   session_id -- session ID
 *   help_local -- TRUE  -- use local help message
 *                 FALSE -- use English help
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   TRUE  -- Use local language
 *   FALSE -- Use English
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2009-Mar-19 by wangbin -- Create
 *
*******************************************************************************/
BOOL_T bc_cli_set_lan(IN I32_T session_id, IN BOOL_T help_local)
{
	l_language = (help_local == TRUE) ? CLI_LAN_CN : CLI_LAN_EN;
    return cli_acc_set_lan(session_id, help_local);
}



/**************************************************************************
FUNCTION NAME:
    bc_cli_get_prompt

DESCRIPTION:
    Get the command prompt message

INPUT:
    session_id  : the mapped session ID

OUTPUT:
    msgBuf      : prompt message

RETURN:
    TRUE        : get success
    FALSE       : the terminal IO in the session is null

NOTES:
	NA

HISTORY:

**************************************************************************/
BOOL_T bc_cli_get_prompt(IN I32_T session_id, OUT I8_T *msg_buf)
{
    cli_sesn_t  *session;

    /* get session data */
    session = cli_sesn_get_by_sid(session_id);
    if ((NULL == session) || (NULL == msg_buf))
    {
        return FALSE;
    }

    *msg_buf = '\0';
    strcat(msg_buf, CLI_DIR_Get_PathPrompt(session->hdir));

    switch (session->acc_info.level)
    {
    case CLI_ACC_LVL_BASIC:
    case CLI_ACC_LVL_FACTORY:
        strcat(msg_buf, ">");
        break;

    case CLI_ACC_LVL_USER:
        strcat(msg_buf, ":user#");
        break;

    case CLI_ACC_LVL_PUSER:
        strcat(msg_buf, ":puser#");
        break;

    case CLI_ACC_LVL_ADMIN:
        strcat(msg_buf, ":admin#");
        break;

    case CLI_ACC_LVL_DEBUG:
        if ((VT_RS232_CHANNEL == session_id) && (TRUE == CLI_BAT_Check_Playback(session_id)))
        {
            strcat(msg_buf, ":LOAD#");
        }
        else
        {
            strcat(msg_buf, ":mini#");
        }
        break;

    default:
        strcat(msg_buf, "#");
        break;
    }

	strcat(msg_buf, " ");
    return TRUE;
}



/* timeout */

#if 0
/**************************************************************************
FUNCTION NAME:
    __timeout_handler_fun

DESCRIPTION:
    time timeout handler callback fun 

INPUT:
    signo  : signal id

OUTPUT:
    NA

RETURN:
    NA

NOTES:
	NA

HISTORY:

**************************************************************************/
static void __timeout_handler_fun(int signo)
{
	pid_t		pid = 0;
	I8_T		sh_cmd[32] = {0};

	CLI_DBG_ENTER(l_mdl_id);

	pid = getpid();
	CLI_DBG_CPL(l_mdl_id, "pid = %d\n", pid);
	
	snprintf(sh_cmd, 32, "kill -9 %d", pid);
	system(sh_cmd);
	
	CLI_DBG_LEAVE(l_mdl_id);
	exit(0);
}



/**************************************************************************
FUNCTION NAME:
    bc_cli_timeout_action_init

DESCRIPTION:
    set signal action

INPUT:
    NA

OUTPUT:
    NA

RETURN:
    NA

NOTES:
	NA

HISTORY:

**************************************************************************/
void bc_cli_timeout_action_init(void)
{
	struct sigaction	action;

	CLI_DBG_ENTER(l_mdl_id);

	action.sa_handler = __timeout_handler_fun;
	action.sa_flags = 0;
	sigemptyset(&action.sa_mask);
	sigaction(SIGALRM, &action, NULL);

	CLI_DBG_LEAVE(l_mdl_id);
	return;
}



/**************************************************************************
FUNCTION NAME:
    bc_cli_timeout_time_init

DESCRIPTION:
    timeout time init

INPUT:
    NA

OUTPUT:
    NA

RETURN:
    NA

NOTES:
	NA

HISTORY:

**************************************************************************/
void bc_cli_timeout_time_init(void)
{
	struct itimerval time;

	CLI_DBG_ENTER(l_mdl_id);

	time.it_value.tv_sec = l_timeout;
	time.it_value.tv_usec = 0;
	time.it_interval.tv_sec = l_timeout;
	time.it_interval.tv_usec = 0;

	setitimer(ITIMER_REAL, &time, NULL);

	CLI_DBG_LEAVE(l_mdl_id);
	return;
}



/**************************************************************************
FUNCTION NAME:
    bc_cli_set_timeout

DESCRIPTION:
    set timeout time

INPUT:
    NA

OUTPUT:
    NA

RETURN:
    NA

NOTES:
	NA

HISTORY:

**************************************************************************/
void bc_cli_set_timeout(UI32_T time)
{

	CLI_DBG_ENTER(l_mdl_id);

	l_timeout = time;
	CLI_DBG_CPL(l_mdl_id, "l_timeout = %d\r\n", l_timeout);

	/* set init timeout */
	bc_cli_timeout_time_init();

	CLI_DBG_LEAVE(l_mdl_id);
	return;
}



/**************************************************************************
FUNCTION NAME:
    bc_cli_get_timeout

DESCRIPTION:
    get timeout time

INPUT:
    NA

OUTPUT:
    NA

RETURN:
    UI32_T

NOTES:
	NA

HISTORY:

**************************************************************************/
UI32_T bc_cli_get_timeout(void)
{
	CLI_DBG_ENTER(l_mdl_id);

	CLI_DBG_LEAVE(l_mdl_id);
	return l_timeout;
}



/**************************************************************************
FUNCTION NAME:
    bc_cli_timeout_init

DESCRIPTION:
    timeout init

INPUT:
    NA

OUTPUT:
    NA

RETURN:
    NA

NOTES:
	NA

HISTORY:

**************************************************************************/
void bc_cli_timeout_init(void)
{
	CLI_DBG_ENTER(l_mdl_id);

	bc_cli_timeout_action_init();
	bc_cli_timeout_time_init();
	
	CLI_DBG_LEAVE(l_mdl_id);
	return;
}



/**************************************************************************
FUNCTION NAME:
    bc_cli_logout

DESCRIPTION:
    user cli process logout

INPUT:
    NA

OUTPUT:
    NA

RETURN:
    NA

NOTES:
	NA

HISTORY:

**************************************************************************/
void bc_cli_logout(I32_T sid)
{
#if 0
	pid_t 		pid = 0;
	I8_T		sh_cmd[32] = {0};

	CLI_DBG_ENTER(l_mdl_id);

	pid = getpid();
	CLI_DBG_CPL(l_mdl_id, "pid = %d\n", pid);
	
	snprintf(sh_cmd, 32, "kill -9 %d", pid);
	system(sh_cmd);

	CLI_DBG_LEAVE(l_mdl_id);
	exit(0);
#endif

	CLI_API_DestroySession(sid);

	CLI_DBG_CPL(l_mdl_id, "logout OK! longjmp OK!\n");
	longjmp(buf, 1);

}

#endif



