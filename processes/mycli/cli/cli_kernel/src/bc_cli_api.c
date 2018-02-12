	
////////////////////////////////////////////////////////////////////////////////
//																			  //
//								头	 文   件								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_modules.h"
#include "bc_platform_time.h"
#include "bc_platform_thread.h"

#include "bc_cli_type.h"
#include "bc_cli_sesn.h"
#include "bc_cli_vkey.h"
#include "bc_cli_edit.h"
#include "bc_cli_core.h"
#include "bc_cli_db.h"
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

static unsigned int 	l_mdl_id = BC_MODULE_CLI_KERNEL;

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


static BOOL_T           l_page_state = TRUE;  // global cli paging state, TRUE: enable, FALSE: disable


static cli_lan_t 		l_language = DEF_LANGUAGE;

static UI32_T 		 	l_timeout = DEF_TIMEOUT;

extern jmp_buf   		bc_jmp_buf;


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

#if 1


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
    session = bc_cli_session_get();
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
	Creat by bain.wang@outlook.com 2011.6.23

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
 *   2009-Mar-25 by bain.wang@outlook.com -- Create
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
    Creat by bain.wang@outlook.com 2011.3.2

**************************************************************************/
BOOL_T bc_cli_set_cmdpath(IN I32_T sessionID, IN I8_T *path, IN I8_T *path_prompt, IN cli_value_t *path_value)
{
    cli_sesn_t  *session;

    /* get session data */
    session = bc_cli_session_get();
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
    Creat by bain.wang@outlook.com 2011.3.2

**************************************************************************/
I8_T * bc_cli_get_cmdpath(IN I32_T sessionID)
{
    cli_sesn_t  *session;

    /* get session data */
    session = bc_cli_session_get();
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
    Creat by bain.wang@outlook.com 2011.3.2

**************************************************************************/
cli_value_t * bc_cli_get_path_parameter(IN I32_T sessionID)
{
    cli_sesn_t  *session;

    /* get session data */
    session = bc_cli_session_get();
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
    Creat by bain.wang@outlook.com 2011.3.7

**************************************************************************/
BOOL_T bc_cli_exit_curpath(IN I32_T sessionID)
{
    cli_sesn_t  *session;

    /* get session data */
    session = bc_cli_session_get();
    if (NULL == session)
    {
        return FALSE;
    }

    return CLI_DIR_Free_LastPathNode(session->hdir);
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
	bc_cli_session_set_quit_flag(TRUE, CLI_API_RET_QUIT_SESSION);

	/* check if it had login */
	if (bc_cli_session_get_lvl() <= CLI_ACC_LVL_BASIC)
	{
		return;
	}

	bc_cli_session_set_lvl(CLI_ACC_LVL_BASIC);

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
 *   2009-Mar-19 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
BOOL_T bc_cli_set_usr_lvl(const int session_id, const UI32_T level)
{
	bc_cli_session_set_lvl((UI8_T)level);
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
 *   2009-Mar-19 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
UI32_T bc_cli_get_usr_lvl(const int session_id)
{
	return bc_cli_session_get_lvl();
}


BOOL_T bc_cli_get_usr_info(cli_usr_info_t *pEntry)
{
	CLI_ACC_INFO_T ptrAccInfo;

	if (pEntry == NULL)
	{
		return FALSE;
	}

	bc_cli_session_get_accinfo(&ptrAccInfo);

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

	bc_cli_session_get_accinfo(&ptrAccInfo);

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

    session = bc_cli_session_get();
    if (NULL == session)
    {
        return FALSE;
    }

    return CLI_VIO_Erase(session->hvio, CLI_SCREEN_CLEAR);
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
    session = bc_cli_session_get();
    if (NULL == session)
    {
        return FALSE;
    }

    session->hhist = CLI_HIST_SetSize(session->hhist, size);

    return TRUE;
}

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
 *   2009-May-05 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
I8_T * bc_cli_show_all_hist(IN I32_T session_id, IN BOOL_T start)
{
    HANDLE_T        h_hist;
    cli_sesn_t  *session;

    session = bc_cli_session_get();
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
 *   2016-05-26 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
cli_lan_t bc_cli_get_lan(void)
{
	return l_language;
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *   bc_cli_set_lan
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
 *   2009-Mar-19 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
BOOL_T bc_cli_set_lan(IN I32_T session_id, IN BOOL_T help_local)
{
	l_language = (help_local == TRUE) ? CLI_LAN_CN : CLI_LAN_EN;
    return bc_cli_session_set_lan(help_local);
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
    session = bc_cli_session_get();
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
            strcat(msg_buf, ":GOD#");
        }
        break;

    default:
        strcat(msg_buf, "#");
        break;
    }

	strcat(msg_buf, " ");
    return TRUE;
}

#endif
#if 1

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
    Creat by bain.wang@outlook.com 2011.3.2

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

					if (bc_cli_session_get_lan() && entry->help_local)
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
    Creat by bain.wang@outlook.com 2011.3.2

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
    Creat by bain.wang@outlook.com 2011.3.2

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

				if (bc_cli_session_get_lan() && entry->help_local)
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

#endif
#if 1


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
static CLI_TERMINAL_IO_T * __bc_cli_api_get_hterm(void)
{
    cli_sesn_t  *session;

    /* get session data */
    session = bc_cli_session_get();
    if (NULL == session)
    {
        return NULL;
    }

    return CLI_VIO_Get_Hterm(session->hvio);
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *   __bc_cli_api_getc
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
 *   2009-May-27 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
static I32_T __bc_cli_api_getc(IN I32_T session_id, IN I32_T timeout_msec)
{
    cli_sesn_t  *session;

    session = bc_cli_session_get();
    if (NULL == session)
    {
        return CLI_VKEY_IO_WRONGVALUE;
    }

    return CLI_VIO_Getc(session->hvio, timeout_msec);
}


/**************************************************************************
FUNCTION NAME:
	bc_cli_api_vt_getc

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
I32_T bc_cli_api_vt_getc(IN I32_T sessionID, IN I32_T timeout)
{
	return __bc_cli_api_getc(sessionID, timeout);
}



/**************************************************************************
FUNCTION NAME:
	__bc_cli_api_vt_put_string

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
static void __bc_cli_api_vt_put_string(IN I32_T sessionID, IN const I8_T *string, IN I32_T length)
{
	CLI_TERMINAL_IO_T *terminal;

	terminal = __bc_cli_api_get_hterm();
	if (terminal && terminal->putstr)
	{
		(*terminal->putstr)(sessionID, (UI8_T *)string, length);
	}
	
}



/**************************************************************************
FUNCTION NAME:
	__bc_vt_move_cursor_up

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
static void __bc_vt_move_cursor_up(IN I32_T sessionID, IN I32_T columns)
{
	I8_T  escape_str[8], *temp_ptr ;

	/* Reserve 8 bytes space for Escape sequence */

	temp_ptr = escape_str ;
	*temp_ptr++ = VT_ESC ;
	*temp_ptr++ = '[' ;

	temp_ptr += sprintf(temp_ptr, "%d", columns);

	*temp_ptr++ = 'A' ;
	*temp_ptr = VT_NULL ;

	__bc_cli_api_vt_put_string(sessionID, escape_str, strlen(escape_str));
} 



/**************************************************************************
FUNCTION NAME:
	__bc_vt_move_cursor_down

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
static void __bc_vt_move_cursor_down(IN I32_T sessionID, IN I32_T columns)
{
	I8_T  escape_str[8], *temp_ptr ;

	/* Reserve 8 bytes space for Escape sequence */

	temp_ptr = escape_str ;
	*temp_ptr++ = VT_ESC ;
	*temp_ptr++ = '[' ;

	temp_ptr += sprintf(temp_ptr, "%d", columns);

	*temp_ptr++ = 'B' ;
	*temp_ptr = VT_NULL ;

	__bc_cli_api_vt_put_string(sessionID, escape_str, strlen(escape_str));
} 


/*-----------------------------------------------------------------------
 VT100 KEY SEQUENCE

--------- EDIT KEYS ------------
ESC[1~		INSERT
ESC[2~		HOME
ESC[3~		PAGE UP
ESC[4~		DELETE
ESC[5~		END
ESC[6~		PAGE DOWN

--------- DIRECTION KEYS ----------
ESC[A		UP
ESC[B		DOWN
ESC[C		RIGHT
ESC[D		LEFT

--------- FUNCTION KEYS -------------
ESC[11~		F1
ESC[12~		F2
ESC[13~		F3
ESC[14~		F4
ESC[16~		F5
ESC[17~		F6
ESC[18~		F7
ESC[19~		F8
ESC[20~		F9
ESC[21~		F10
ESC[23~		F11
ESC[24~		F12
*-----------------------------------------------------------------------
*/

/**************************************************************************
FUNCTION NAME:
	__bc_vt_analysis_keystroke

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
static I32_T __bc_vt_analysis_keystroke(
	IN I32_T sessionID,
	IN UI8_T *ptrKeystrokeState,
	IN I32_T rxChr)
{
	I32_T rtn_value ;
	static I32_T func_key1 = 0, func_key2 = 0;

	/* set default return value */
	rtn_value = VT_NULL ;

	switch (*ptrKeystrokeState)
	{
		case VT_WAIT_FOR_KEYSTROKE:
			switch (rxChr)
			{
				case VT_LF :
				case VT_CR :
					rtn_value = VT_CR ;
					break;
					
				case VT_ESC:
					*ptrKeystrokeState = VT_WAIT_FOR_2ND_ESC_SEQ;
					break;
					
				default:
					rtn_value= rxChr;
					break;
			}
	    		break;
				
		case VT_WAIT_FOR_2ND_ESC_SEQ:
			switch (rxChr)
			{
				case VT_BRACKET :
					*ptrKeystrokeState = VT_WAIT_FOR_AFTER_BRACKET ;
					break;
					
				case 'O' :
					*ptrKeystrokeState = VT_WAIT_FOR_AFTER_O ;
					break;
					
				default:
					rtn_value= rxChr;
					break;
			}
			break;
			
		case VT_WAIT_FOR_AFTER_BRACKET:
			switch (rxChr)
			{
				case 'A':
					rtn_value= VT_UP;
					break;
					
				case 'B' :
					rtn_value= VT_DOWN;
					break;
					
				case 'C':
					rtn_value= VT_RIGHT;
					break;
					
				case 'D' :
					rtn_value= VT_LEFT;
					break;

				case '1':
					*ptrKeystrokeState = VT_WAIT_FOR_7e_AFTER_INSERT;
					func_key1 = '1';
					break;
					
				case '2' :
					*ptrKeystrokeState = VT_WAIT_FOR_7e_AFTER_HOME;
					func_key1 = '2';
					break;
					
				case '3':
					*ptrKeystrokeState = VT_WAIT_FOR_7e_AFTER_PAGEUP;
					break;
					
				case '4' :
					*ptrKeystrokeState = VT_WAIT_FOR_7e_AFTER_DELETE;
					break;
					
				case '5':
					*ptrKeystrokeState = VT_WAIT_FOR_7e_AFTER_END;
					break;
					
				case '6' :
					*ptrKeystrokeState = VT_WAIT_FOR_7e_AFTER_PAGEDOWN;
					break;

				default:
					rtn_value= rxChr;
					break;
			}
			break;

		case VT_WAIT_FOR_7e_AFTER_INSERT:
		case VT_WAIT_FOR_7e_AFTER_HOME:
		case VT_WAIT_FOR_7e_AFTER_PAGEUP:
		case VT_WAIT_FOR_7e_AFTER_DELETE:
		case VT_WAIT_FOR_7e_AFTER_END:
		case VT_WAIT_FOR_7e_AFTER_PAGEDOWN:
	 		/* restore the value that has been added by VT_WAIT_FOR_7e_AFTER_INSERT */
			if (rxChr=='~')
			{
				/* map to the predefined key */
				rtn_value = (*ptrKeystrokeState - VT_WAIT_FOR_7e_AFTER_INSERT + 1) + VT_FUNC_EDIT_KEY_BASE;
			}
			/* check if the 1 sequence for function key, F1 - F12 */
			else if ((rxChr >= '0' && rxChr <= '9') && (func_key1 == '1' || func_key1 == '2'))
			{
				*ptrKeystrokeState = VT_WAIT_FOR_7E_FOR_FUNC_KEY2;
				func_key2 = rxChr;
				CLI_DBG_CPL(l_mdl_id, "\nCLI_Wait_7e: FuncK: func1 = %d, func2 = %d", func_key1, func_key2);
			}
	 		/* abort the escape sequence analysis */
	 		else
			{
				rtn_value=rxChr;
				CLI_DBG_CPL(l_mdl_id, "\nCLI_Wait_7e: FuncK abort: func1 = %d, rxChr = %d", func_key1, rxChr);
			}
	    		break;

		case VT_WAIT_FOR_7E_FOR_FUNC_KEY2:
			if (rxChr=='~')
			{
				I32_T fx;
				
				fx = ((func_key1 - '0') * 10 + (func_key2 - '0'));
				CLI_DBG_CPL(l_mdl_id, "\nCLI analysis fx = %d", fx);
				if (fx > 10 && fx < 25)
				{
					rtn_value= fx + VT_FUNC_EDIT_KEY_BASE;
				}
				else
				{	
					/* invalid function key, return ~ */
					rtn_value = rxChr;
				}
			}
			/* abort the escape sequence analysis */
			else
			{
				rtn_value=rxChr;
			}
			break;

		case VT_WAIT_FOR_AFTER_O:
			switch (rxChr)
			{
				case 'A':
					rtn_value= VT_UP;
					break;
					
				case 'B' :
					rtn_value= VT_DOWN;
					break;

				case 'C':
					rtn_value= VT_LEFT;
					break;

				case 'D' :
					rtn_value= VT_RIGHT;
					break;

				default:
					rtn_value= rxChr;
					break;
			}
			break;

		default:
			break;
	}

	if (rtn_value!=VT_NULL)
	{
		*ptrKeystrokeState = VT_WAIT_FOR_KEYSTROKE;
		func_key1 = func_key2 = 0;
		if (rtn_value >= VT_FUNC_EDIT_KEY_BASE)
		{
			CLI_DBG_CPL(l_mdl_id, "\nCLI analysis key: %d", (rtn_value - (I32_T)VT_FUNC_EDIT_KEY_BASE));
		}
	}

	return rtn_value;
}


/**************************************************************************
FUNCTION NAME:
	__bc_vt_erase_line

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
static void __bc_vt_erase_line(IN I32_T sessionID, IN VT_ERASE_MODE_T erase_mode)
{
	I8_T  escape_str[5], *temp_ptr ;

	temp_ptr = escape_str ;
	*temp_ptr++ = CLI_VKEY_ESC ;
	*temp_ptr++ = '[' ;
	//temp_ptr += TRAN_I32toA( temp_ptr, erase_mode, 10 );
	temp_ptr += sprintf(temp_ptr, "%d", erase_mode);
	*temp_ptr++ = 'K' ;
	*temp_ptr = VT_NULL ;

	__bc_cli_api_vt_put_string(sessionID, escape_str, strlen(escape_str));
}


/**************************************************************************
FUNCTION NAME:
	__bc_vt_check_inputbuffer_empty

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
static I32_T __bc_vt_check_inputbuffer_empty(IN I32_T sessionID)
{
	CLI_TERMINAL_IO_T *terminal;

	terminal = __bc_cli_api_get_hterm();
	if (terminal && terminal->checkEmpty)
	{
		return (*terminal->checkEmpty)(sessionID);
	}

	return 1;
}


/*------------------------------------------------------------------------
 * Function   : __bc_cli_edit_get_input_event
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
static BOOL_T __bc_cli_edit_get_input_event(
	IN const I32_T sessionID,
	IN UI32_T timeoutSec,
	IN BOOL_T bReGetTimeOut,
	OUT I32_T *pRxCh)
{
	BOOL_T bQuit;
	I32_T quitFlag;
	
	UI32_T lastTime, nowTime, diffTime;
	I32_T rxChr;

	bc_platform_time_sec_get(&lastTime);

	for (;;)
	{
		bc_cli_session_get_quit_flag(&bQuit, &quitFlag);
		if (bQuit)
		{
			rxChr = CLI_VKEY_IO_CLOSED;
			break;
		}

		rxChr = bc_cli_api_vt_getc(sessionID, 500);
		if (rxChr == CLI_VKEY_IO_TIMEOUT)
		{
			if (bReGetTimeOut == TRUE )
			{
				timeoutSec = bc_cli_session_get_timeout();
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
		if (__bc_vt_check_inputbuffer_empty(sessionID) == 0)
		{
			/* re-define the 'ESC' key to 'F4' */
			rxChr = CLI_VKEY_F4;
		}
	}

	*pRxCh = rxChr;
	return TRUE;
}



/*------------------------------------------------------------------------
 * Function   : __bc_cli_edit_get_pageaction
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
static BOOL_T __bc_cli_edit_get_pageaction(
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
		__bc_cli_edit_get_input_event(sessionID, timeoutSec, bReGetSetting, &rxChr);

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
				rxChr = __bc_vt_analysis_keystroke(sessionID, &keystrokeState, rxChr);

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

	bc_cli_session_get_cursorstatus(&prtState);

	switch (prtState.refresh_action)
	{
	case 0: /* frist time print */
		headerCnt[sessionID] = prtState.line;
		freshTime[sessionID] = 0;
		prtState.refresh_action = 1;
		prtState.column = 0;
		prtState.line = 0;
		prtState.page_action = CLI_PAGE_REFRESH;
		bc_cli_session_set_cursorstatus(&prtState);
		return CLI_PAGE_REFRESH;

	case 1: /* second time print */
		prtState.refresh_action = 2;

		for (i = prtState.line; i < (I32_T)(CLI_UTL_PRINT_MAX_PAGE_LINES - 1 - headerCnt[sessionID]); i++ )
		{
			__bc_cli_api_vt_put_string(sessionID, "\n\r", 2);
		}

		/* add bottom */
		__bc_cli_api_vt_put_string(sessionID, l_page_prompt, strlen(l_page_prompt));
		/* add the line number of bottom */
		i++;
		break;

	case 2: /* other */
	default:
		for (i = prtState.line; i < (I32_T)(CLI_UTL_PRINT_MAX_PAGE_LINES - 1 - headerCnt[sessionID]); i++ )
		{
			__bc_cli_api_vt_put_string(sessionID,"\n\r", 2);
			__bc_vt_erase_line(sessionID, VT_COMPLETE_ERASE);
		}
		break;
	}

	for (;;)
	{
		__bc_cli_edit_get_pageaction(sessionID,timoutSec,&action);

		switch (action)
		{
			case CLI_PAGE_UP:
			case CLI_PAGE_DOWN:
			case CLI_PAGE_REFRESH:
			case CLI_PAGE_TIMEOUT:
				if (i > 0)
				{
					__bc_vt_move_cursor_up(sessionID, i);
					/* clear the old print message */
					clearCnt = ((CLI_UTL_PRINT_MAX_PAGE_LINES - 1 - headerCnt[sessionID]) > i)?
								i : (CLI_UTL_PRINT_MAX_PAGE_LINES - 1 - headerCnt[sessionID]);
					for (j = 0; j < clearCnt; j++)
					{
						__bc_cli_api_vt_put_string(sessionID,"\n\r", 2);
						__bc_vt_erase_line(sessionID, VT_COMPLETE_ERASE);
					}
					__bc_vt_move_cursor_up(sessionID, clearCnt);
				}
				prtState.line = 0;
				prtState.column = 0;

				if (action == CLI_PAGE_TIMEOUT)
				{
					freshTime[sessionID] += timoutSec;
					freshTimeoutSec = bc_cli_session_get_timeout();
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
					__bc_vt_move_cursor_down(sessionID, i);
				}
				if (i < 0)
				{
					__bc_vt_move_cursor_up(sessionID, 1);
				}
				__bc_cli_api_vt_put_string(sessionID,"\r", 1);
				__bc_vt_erase_line(sessionID, VT_COMPLETE_ERASE);
				__bc_vt_move_cursor_up( sessionID, 1);
				freshTime[sessionID] = 0;
				prtState.page_action = CLI_PAGE_NOACTION;
				break;

			case CLI_PAGE_NOTIFY:
				__bc_cli_api_vt_put_string(sessionID,"\n\r", 2);
				freshTime[sessionID] = 0;
				prtState.page_action = CLI_PAGE_NOACTION;
				action = CLI_PAGE_EXIT;
				break;

			default:
				freshTime[sessionID] = 0;
				continue;
		}

		bc_cli_session_set_cursorstatus(&prtState);
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
	Added by bain.wang@outlook.com 2009.11.6

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


#endif
#if 1

#define CLI2_MAX_PRINT_LINE_NUMBER_FOR_SLEEP 100

BOOL_T bc_cli_global_paging = TRUE;
static const I8_T scrollPrompt[] =
""
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
"ENTER"
"\033[0m"
" Next Entry "
"\033[7m"
"a"
"\033[0m"
" All                     ";

static cli_page_act_e __bc_cli_prt_get_page_action(void)
{
	HANDLE_T hvio;
	I32_T timeOut;

	bc_uint64 waitMsec = 0;
	BOOL_T bwait_timeOut = FALSE;

	bc_uint64 lastTime = 0, nowTime = 0, diffTime;

	hvio = bc_cli_session_get_hvio();
	timeOut = bc_cli_session_get_timeout();

	if (timeOut <= 0)
	{
#ifdef BC_PTC88C
		waitMsec = 0xFFFFFFFF;
#else
		waitMsec = 0xFFFFFFFFFFFFFFFF;
#endif
		bwait_timeOut = FALSE;
	}
	else
	{
		waitMsec = timeOut * 1000000;
		bwait_timeOut = TRUE;
		bc_platform_time_us_get(&lastTime);
	}

	for( ; ; )
	{
		switch (CLI_VIO_Getc(hvio, 1000))
		{
			case VT_CTRL_C:
			case VT_ESC:
			case VT_LOWERCASE_Q:
			case CLI_VKEY_IO_NOTIFY:
				return CLI_PAGE_EXIT;

			case VT_SPACE:
			case VT_LOWERCASE_N:
				return CLI_PAGE_DOWN;

			case VT_CR:
			case VT_CTRL_ENTER:
				return CLI_PAGE_NEXTLINE;

			case 'a':
				return  CLI_PAGE_ALL;

			case VT_IO_CLOSED:
			case VT_IO_EXITCMD:
				return CLI_PAGE_EXIT;

			case VT_IO_TIMEOUT:
				if (bwait_timeOut)
				{
					bc_platform_time_us_get(&nowTime);

					if (nowTime >=  lastTime) /* normal */
					{
						diffTime =  nowTime - lastTime;
					}
					else /* turn over */
					{
					#ifdef BC_PTC88C
						diffTime = 0xFFFFFFFFUL - lastTime + nowTime + 1;
					#else
						diffTime = 0xFFFFFFFFFFFFFFFFUL - lastTime + nowTime + 1;
					#endif
					}

					if (diffTime > waitMsec)
					{
						return CLI_PAGE_TIMEOUT;
					}
				}
				break;

			default:
				if (bwait_timeOut)
				{
					bc_platform_time_us_get(&lastTime);
				}
				break;
		}
	}

}

static void __bc_cli_prt_putc(bc_char ch)
{
	HANDLE_T hvio;
	
	BOOL_T page_stop;
	CLI_ACC_CURSOR_STATUS_T cursor_status;
	
	hvio = bc_cli_session_get_hvio();

	if (bc_cli_global_paging == FALSE)
	{
		CLI_VIO_Putc(hvio, ch);
		return ;
	}

	page_stop = bc_cli_session_get_pagestopstatus();
	if (page_stop == FALSE)
	{
		CLI_VIO_Putc(hvio, ch);
		return ;
	}

	bc_cli_session_get_cursorstatus (&cursor_status);
	if (cursor_status.page_action != CLI_PAGE_EXIT && ch)
	{
		/* calculate the cursor position */
		switch (ch)
		{
			case '\n':
				cursor_status.line++;
				cursor_status.column = 0;
				break;

			case '\r':
				cursor_status.column = 0;
				break;

			default:
				cursor_status.column++;
				break;
		}

		if (cursor_status.column > cursor_status.max_column)
		{
			cursor_status.column = cursor_status.column - cursor_status.max_column;
			cursor_status.line++;
		}

		if (cursor_status.line > cursor_status.max_line && cursor_status.page_action != CLI_PAGE_ALL)
		{
			cli_page_act_e pageAction;

			/*
			    sleep a while to avoid
			    tie the system when user press space very quickly
			*/
			bc_platform_time_usleep(50);

			/* print scroll prompt */
			CLI_VIO_Puts(hvio, "\r\n", 2);
			CLI_VIO_Puts(hvio, scrollPrompt, strlen(scrollPrompt));

			pageAction = __bc_cli_prt_get_page_action();
			switch(pageAction)
			{
				case CLI_PAGE_TIMEOUT:
					pageAction = CLI_PAGE_EXIT;
					break;

				case CLI_PAGE_DOWN:
					cursor_status.line = cursor_status.line - cursor_status.max_line;
					break;

				case CLI_PAGE_NEXTLINE:
					cursor_status.line = cursor_status.line - 1;
					break;

				default:
					break;
			}
			cursor_status.page_action = pageAction;

			CLI_VIO_Erase(hvio, CLI_LINE_COMPLETE);
			/* move to the begining of line */
			CLI_VIO_Puts(hvio, "\r", 1);

			if (ch == '\n')
			{
				ch = '\r';
			}
		}
	

		if (cursor_status.page_action != CLI_PAGE_EXIT)
		{
			if ((cursor_status.page_action == CLI_PAGE_ALL) && 
					(cursor_status.line >= CLI2_MAX_PRINT_LINE_NUMBER_FOR_SLEEP))
			{
				bc_platform_time_usleep(500);
				cursor_status.line = cursor_status.line - CLI2_MAX_PRINT_LINE_NUMBER_FOR_SLEEP;
			}

			if (ch == '\n')
			{
				CLI_VIO_Puts(hvio, "\n\r", 2);
			}
			else
			{
				CLI_VIO_Putc(hvio, ch);
			}
		}

		bc_cli_session_set_cursorstatus(&cursor_status);
	}
}

void bc_cli_prt_puts(bc_char *buf, bc_uint32 len)
{
	bc_uint32 i;

	for (i = 0; i < len; i++)
		__bc_cli_prt_putc(buf[i]);
}


/* timeout */

#endif 
#if 1
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
    __bc_cli_timeout_action_init

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
static void __bc_cli_timeout_action_init(void)
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
    __bc_cli_timeout_time_init

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
static void __bc_cli_timeout_time_init(void)
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
	__bc_cli_timeout_time_init();

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

	__bc_cli_timeout_action_init();
	__bc_cli_timeout_time_init();
	
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


	bc_cli_session_destroy(sid);

	CLI_DBG_CPL(l_mdl_id, "logout OK! longjmp OK!\n");
	longjmp(bc_jmp_buf, 1);

}

#endif



