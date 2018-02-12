
//#include <termio.h>
//#include <unistd.h>
#include <setjmp.h>

#include "bc_modules.h"
#include "bc_platform_thread.h"
#include "bc_platform_sem.h"

#include "bc_cli_type.h"
#include "bc_cli_vio.h"
#include "bc_cli_term.h"
#include "bc_cli_sesn.h"
#include "bc_cli_dir.h"
#include "bc_cli_vkey.h"
#include "bc_cli_hist.h"
#include "bc_cli_edit.h"
#include "bc_cli_core.h"
#include "bc_cli_hook.h"
#include "bc_cli_misc.h"
#include "bc_cli_fltr.h"
#include "bc_cli_para.h"
#include "bc_cli_alias.h"
#include "bc_cli_bnr.h"

#include "bc_cli_sys_cmd.h"
#include "bc_cli_bnr_cmd.h"

#include "bc_cli.h"
#include "bc_sys_defs.h"
#include "bc_sys_ipc_client.h"

#include "bc_log.h"
#include "bc_usermgmt_def.h"
#include "bc_usermgmt.h"
#include "bc_sys_ipc_client.h"


#define CLI_API_SCRIPT_PROMPT 					"error: "
#define xkbhit()   	 							TRUE

#define BOOTUP_LOGIN_MAXRETRYTIME       (3)
#define BOOTUP_LOGIN_INPUT_TIMEOUTSEC   (60)
#define BOOTUP_LOGIN_BUFLEN             (100)

#define PRIVMGMT_ANONYMOUS_USER			"anonymous"



typedef void        (*VT_PUTSTR)(int, UI8_T *, int);  /* string and length */
typedef int         (*VT_GETCHAR)(int, int);         /* delay */
typedef BOOL_T      (*VT_CHECK_EMPTY)(int);         /* check char pull is empty */

typedef struct stag_vt_io_ctrl_t
{
    VT_PUTSTR               putstr;         /* write one character */
    VT_GETCHAR              getchar;        /* read one character */
    VT_CHECK_EMPTY          checkEmpty;     /* read one character */
    int                     flags;          /* CON_IO */
    int                     sessionID;
    UI8_T                   ip6Flag;        /*0 is IPv4, other is IPv6*/
    UI32_T                  ipAddress;
    UI8_T                   ip6Address[16];
    /* Added by bain.wang@outlook.com, 2008.06.18
     * Add it to make application can force command exit on an specific session.
     * When call VT_GetChar, it will first check this previous buffer,
     *  if has an valid value(Not NULL), it will return this value, and clear it.
     *  so, when next time to get char, it will correctly read char from the
     *  pre-registered API.
     */
#if 1
    I32_T                   insert_input_char;
#endif
} VT_IOCTL_T;



static unsigned int 	l_mdl_id = BC_MODULE_CLI_KERNEL_MAINPROCESS;
static struct termios   l_tty;

static float    		complete = 0.0;
jmp_buf					bc_jmp_buf;




/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_API_Execute_OneUserCmd
 *
 * DESCRIPTION:
 *   Execute a user command end by '\0'
 *   1.获取当前路径
 *   2.获取当前用户级别
 *   3.解析用户输入命令，并在在当前模式和全局模式搜索下搜索该命令
 *   4.执行钩子函数
 *   5.执行命令回调函数
 *   6.执行钩子函数
 *
 * INPUT:
 *   session_id -- session id
 *   cmd_buf -- command string for execute
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   ref. cli_cmd_ret_e
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2009-Mar-25 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
I32_T CLI_API_Execute_OneUserCmd(IN I32_T session_id, IN I8_T *cmd_buf)
{
    cli_value_t    	*cli2_value;
    CLI_CMD_NODE_T 	*cmd_node;
    cli_sesn_t  	*session;
    CLI_CMD_FUNC_T 	callback;
    //I8_T 			*filter;
    I32_T           i;
    UI8_T           level;
    I8_T            view[CLI_DIR_WD_MAX + 1];
    I32_T           ret_value = CLI_CMD_SUCCESS_PRT_NONE;
    UI32_T          noEditeLen;

    session = bc_cli_session_get();
    if (NULL == session)
    {
        return CLI_CMD_FAIL_PRT_NONE;
    }

    bc_platform_sem_wait(session->lock, BC_SEM_WAIT_FOREVER);
    strcpy(view, cli_dir_get_cmdpath(session->hdir));
    level = bc_cli_session_get_lvl();
    cli2_value = NULL;
    cmd_node = CLI_CORE_Parse_Cmdstr(view, cmd_buf, level, &cli2_value, &(session->err_pos));
    bc_cli_session_set_pagestopstatus(bc_cli_session_get_pagestopstatus()); /* reset pagestop */
	
    if ((cmd_node == NULL) || (cmd_node == CLI_AMBIGUOUS_NODE))
    {
        if (cmd_node == CLI_AMBIGUOUS_NODE)
        {
            CLI_API_Printf(session_id, "Ambiguous command\r\n");
        }
        else if (session->err_pos == strlen(session->cmd))
        {
            CLI_API_Printf(session_id, "Incomplete command\r\n");
        }
        else
        {
            if (session->acc_info.script_mode)
            {
                CLI_API_Printf(session_id, "\r\n%s%s\r\n", CLI_API_SCRIPT_PROMPT, cmd_buf);
                noEditeLen = strlen(CLI_API_SCRIPT_PROMPT);
            }
            else
            {
                /*get the no edit length */
                noEditeLen = CLI_EDIT_Get_PromptLen(session->hedit);
            }

			CLI_DBG_CPL(l_mdl_id, "session->err_pos=%d,noEditeLen=%d,session->acc_info.script_mode=%d\r\n", session->err_pos, noEditeLen, session->acc_info.script_mode);
            for (i = 1; i <= (session->err_pos + noEditeLen); i++)
            {
                CLI_API_Printf(session_id, " ");
				if (!(i % 80))
				{
					CLI_API_Printf(session_id, "\r\n");
				}
            }
            CLI_API_Printf(session_id, "^\r\n");
            CLI_API_Printf(session_id, "Invalid input detected at \"^\" marker!\r\n");
        }
        callback = NULL;
    }
    else
    {
        callback = cmd_node->callback;
    }

    bc_platform_sem_post(session->lock);

    if (callback)
    {
        I8_T                        *cmd;
        CLI_CMD_EXECUTE_CALLBACK_T 	callbackFunc;
        void                        *callbackCookie;
        BOOL_T                      executeFlag;
        I32_T                       pre_state[CLI_HOOK_CMD_EXECUTE_MAXNUM];

        cmd = NULL;
        callbackFunc = NULL;
        callbackCookie = NULL;
        executeFlag = FALSE;
        memset(pre_state, 0, sizeof(pre_state));
        i = 0;
		
        while (CLI_HOOK_Get_NextCmdExecute_CallbackFunc(&callbackFunc, &callbackCookie))
        {
            if (executeFlag == FALSE)
            {
                cmd = CLI_MISC_Malloc(CLI_API_MAX_CMD_LEN + 1);
                if (cmd)
                {
                    /* Because some commands will clear edit buffer, so should get
                     * the command string before execute command.
                     * example: the command "create account",
                     * before input password, the edit buffer will be cleared.
                     */
                    strcpy(cmd, cmd_buf);
                    executeFlag = TRUE;
                }
                else
                {
                    break;
                }
            }

			pre_state[i] = (*callbackFunc) (session_id, cmd, TRUE, 0, 0, callbackCookie);
            i++;
        }

        /* execute command */
        ret_value = callback(session_id, cli2_value, cmd_node->cookie);

        if (executeFlag)
        {
            callbackFunc = NULL;
            i = 0;

            while (CLI_HOOK_Get_NextCmdExecute_CallbackFunc(&callbackFunc, &callbackCookie))
            {
                (*callbackFunc) (session_id, cmd, FALSE, ret_value, pre_state[i], callbackCookie);
                i++;
            }

            CLI_MISC_Free(cmd);
        }
    }


    CLI_PARA_Free_ValueList(cli2_value);
    if (cmd_node)
    {
        return ret_value;
    }
    else
    {
        return CLI_CMD_SUCCESS_PRT_NONE;
    }
}



/**************************************************************************
FUNCTION NAME:
    __cli2_api_get_usrcmd

DESCRIPTION:
    Get input command.

INPUT:
    session     	: session struct created by CLI kernel
    pseudo_enable	: pseudo task enable

OUTPUT:
    session     : session struct created by CLI kernel

RETURN:
    command length

NOTES:

HISTORY:

**************************************************************************/
static I32_T __cli2_api_get_usrcmd(IN OUT cli_sesn_t *session, IN BOOL_T pseudo_enable)
{
	CLI_DBG_ENTER(l_mdl_id);
	
    //  MIB_CST_CONSOLE_TIMEOUT_VALUE timeout_value;
    I32_T   ret_value;
    UI32_T  noEditeLen;
    I32_T   map_sessionID;
    I8_T    promptMsg[CLI_DIR_PROMPT_MAX + 20];

    map_sessionID = session->map_sessionID;

#if 0
    /* timeout_value -- when terminal idle for timeout seconds, terminal will
     * be closed automatically. if timeoutSec = 0; terminal will never be closed.
    */
#if SSH_SERVER_INCLUDED
    if (session->session_type == CLI_SESN_TYPE_SSH)
    {
        session->timeout = ST_SSH_Get_ConfigConnectionTimeout();
    }
    else
#endif
    {
        timeout_value = ST_SYS_Get_ConsoleTimeout ();
        switch (timeout_value)
        {
            case CONSOLE_TIMEOUT_NEVER:
                if (session->session_type == CLI_SESN_TYPE_CONSOLE)
                {
                    session->timeout = 0;
                }
                else
                {
                    session->timeout = 15*60;
                }
                break;
            case CONSOLE_TIMEOUT_2:
                session->timeout = 2*60;
                break;
            case CONSOLE_TIMEOUT_5:
                session->timeout = 5*60;
                break;
            case CONSOLE_TIMEOUT_10:
                session->timeout = 10*60;
                break;
            case CONSOLE_TIMEOUT_15:
                session->timeout = 15*60;
                break;
            default:
                session->timeout = 10*60;
                break;
        }
    }
#endif

REFRESH_CASE:
    if (session->previous_ch == 0)
    {
       if (TRUE == pseudo_enable)
       {
#if 0
       		/* pseudo */
       		bc_cli_get_prompt(map_sessionID, promptMsg);
	        noEditeLen = strlen(promptMsg);
	        CLI_API_SetNoEditingLen(map_sessionID, noEditeLen);
	        //CLI_API_Printf(map_sessionID, "%s", promptMsg);
#endif
	   }
	   else
	   {
	   		/* command */
       		bc_cli_get_prompt(map_sessionID, promptMsg);
	   		noEditeLen = strlen(promptMsg);
	        CLI_API_SetNoEditingLen(map_sessionID, noEditeLen);
	        CLI_API_Printf(map_sessionID, "%s", promptMsg);
	        CLI_API_Printf(map_sessionID, "%s", session->cmd);
	   }
    }
    else
    {
        session->previous_ch = 0;
    }

    ret_value = CLI_EDIT_Get_Line(session->hedit, session->hhist, session->cmd, CLI_API_MAX_CMD_LEN, session->timeout, session->previous_ch);
    session->previous_ch = 0;
    if (ret_value == CLI_VKEY_IO_NOTIFY)
    {	
        /* have notify message display, so print a new line and refresh */
        CLI_API_Printf(map_sessionID, "\n\r");
        goto REFRESH_CASE;
    }
	
	CLI_DBG_LEAVE(l_mdl_id);
    return ret_value;
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_API_SetNoEditingLen
 *
 * DESCRIPTION:
 *   Set chars that can not be edited form the start of the line.
 *
 * INPUT:
 *   len -- chars that cannot be deleted.
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
 *   2009-Mar-31 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
void CLI_API_SetNoEditingLen(IN I32_T session_id, IN UI32_T len)
{
    cli_sesn_t  *session;

    session = bc_cli_session_get();
    if (session)
    {
        CLI_EDIT_Set_PromptLen(session->hedit, len);
    }
}



/**************************************************************************
FUNCTION NAME:
    __cli2_api_display_Info_next

DESCRIPTION:
    Display next possible input help information when input '?' key.

INPUT:
    session_id  : created session ID by CLI kernel
    tempList        : the help list need to display

OUTPUT:
    NA

RETURN:
    NA

NOTES:

HISTORY:
    Creat by bain.wang@outlook.com 2011.5.26

**************************************************************************/
static void __cli2_api_display_Info_next(IN I32_T sessionID, IN CLI_PRIV_HELPLIST_T *tempList)
{
    I32_T   i, j, k;
    I32_T   wordLen, helpInfoLen, editLen, printLen;
    I8_T    editBuf[CLI_EDIT_LINE_LEN + 10];

    /* display next possible word and according help information */
    for (i = 0; i < tempList->count; i++)
    {
        /* the same information don't need to display again */
        for (j = 0; j < i; j++)
        {
            if ((strcmp(tempList->name[i], tempList->name[j]) == 0)
             && (strcmp(tempList->help[i], tempList->help[j]) == 0))
            {
                continue;
            }
        }

        if (tempList->help[i])
        {
            wordLen = strlen(tempList->name[i]);
            helpInfoLen = strlen(tempList->help[i]);
            if (wordLen < 20)
            {
                wordLen = 20;
            }
            editLen = CLI_EDIT_LINE_LEN - wordLen - 1;

            if (editLen >= helpInfoLen)
            {
                CLI_API_Printf(sessionID, "%-20s %s\r\n", tempList->name[i], tempList->help[i]);
            }
            else
            {
                /* print for aligning */
                CLI_API_Printf(sessionID, "%-20s ", tempList->name[i]);
                printLen = 0;
                while (printLen < helpInfoLen)
                {
                    if (*(tempList->help[i] + printLen) == ' ')
                    {
                        /* skip the first space */
                        printLen++;
                    }

                    if (helpInfoLen - printLen > editLen)
                    {
                        k = editLen;
                        if (*(tempList->help[i] + printLen + k) != ' ' && *(tempList->help[i] + printLen + k - 1) != ' ')
                        {
                            while (k)
                            {
                                if (*(tempList->help[i] + printLen + k - 1) == ' ')
                                {
                                    break;
                                }
                                k--;
                            }
                            if (k == 0)
                            {
                                k = editLen;
                            }
                        }
                        memcpy(editBuf, tempList->help[i] + printLen, k);
                        printLen += k;

                        memcpy(editBuf + k, "\r\n", 2);
                        memset(editBuf + k + 2, ' ', wordLen + 1);
                        editBuf[k + 2 + wordLen + 1] = '\0';
                    }
                    else
                    {
                        strcpy(editBuf, tempList->help[i] + printLen);
                        printLen = helpInfoLen;
                    }
                    CLI_API_Printf(sessionID, "%s", editBuf);
                }
                CLI_API_Printf(sessionID, "\n\r");
            }
        }
        else
        {
            CLI_API_Printf(sessionID, "%s\r\n", tempList->name[i]);
        }
    }
}



/**************************************************************************
FUNCTION NAME:
    __cli2_api_display_Info_current

DESCRIPTION:
    Display current possible input when input '?' key.

INPUT:
    session_id  : created session ID by CLI kernel
    tempList    : the help list need to display

OUTPUT:
    NA

RETURN:
    NA

NOTES:

HISTORY:
    Creat by bain.wang@outlook.com 2011.5.26

**************************************************************************/
static void __cli2_api_display_Info_current(IN I32_T sessionID, IN CLI_PRIV_HELPLIST_T *tempList)
{
    I32_T   i, j, k;
    I32_T   tempLen, spaceNum;

    k = 0;
    for (i = 0; i < tempList->count; i++)
    {
        /* the same information don't need to display again */
        for (j = 0; j < i; j++)
        {
            if (strcmp(tempList->name[i], tempList->name[j]) == 0)
            {
                continue;
            }
        }

        /* for current possible word, need check the more match word */
        if (tempList->count > 1)
        {
            /* the string parameter type have the lowest level,
                        so if have other type, the string type will not be displayed */
            if ((strcmp(tempList->name[i], "WORD") == 0)
             || (strcmp(tempList->name[i], "MULTI-WORD") == 0)
             || (strcmp(tempList->name[i], "LINE") == 0))
            {
                continue;
            }
        }

        tempLen = strlen(tempList->name[i]);
        if (tempLen / 20)
        {
            k += (tempLen / 20 + 1);
            if (k > 4)
            {
                CLI_API_Printf(sessionID, "\n\r");
                k = tempLen / 20 + 1;
            }
            CLI_API_Printf(sessionID, "%s", tempList->name[i]);
            spaceNum = (tempLen / 20 + 1) * 20 - tempLen;
            for (j = 0; j < spaceNum; j++)
            {
                CLI_API_Printf(sessionID, " ");
            }
        }
        else
        {
            CLI_API_Printf(sessionID, "%-20s", tempList->name[i]);
            k++;
        }

        if (k == 4)
        {
            /* one line display 4 word */
            CLI_API_Printf(sessionID, "\n\r");
            k = 0;
        }
    }

    if (k > 0)
    {
        /* last line add \n\r */
        CLI_API_Printf(sessionID, "\n\r");
    }
}



/**************************************************************************
FUNCTION NAME:
    __cli2_api_translate_helpList

DESCRIPTION:
    Translate the help list.
    Change the parameter string in help list to parameter format string.

INPUT:
    helpList    : help list

OUTPUT:
    helpList    : help list

RETURN:
    NA

NOTES:

HISTORY:
    Creat by bain.wang@outlook.com 2011.4.1

**************************************************************************/
static void __cli2_api_translate_helpList(IN OUT CLI_PRIV_HELPLIST_T *helpList)
{
    I32_T   i;
    I8_T    *dst_ptr, *src_ptr;

    for (i = 0; i < helpList->count; i++)
    {
        src_ptr = helpList->name[i];
        dst_ptr = helpList->name_buf + helpList->name_buf_used;
        /* if is parameter string and translate success, then change the help information */
        if (CLI_ALIAS_GetParaFormat_ByParaString(src_ptr, dst_ptr))
        {
            if (helpList->help[i] == NULL)
            {
                helpList->help[i] = helpList->name[i];
            }
            helpList->name[i] = dst_ptr;
            helpList->name_buf_used += strlen(dst_ptr) + 1;
        }
    }

    /* check the help information buffer used */
    CLI_MISC_Assert(helpList->name_buf_used < sizeof(helpList->name_buf));
}



/**************************************************************************
FUNCTION NAME:
    __cli2_api_display_Info_help

DESCRIPTION:
    Display help information when input '?' key.

INPUT:
    session_id  : created session ID by CLI kernel
    helpList    : the help list need to display

OUTPUT:
    NA

RETURN:
    NA

NOTES:

HISTORY:
    Creat by bain.wang@outlook.com 2011.4.2

**************************************************************************/
static void __cli2_api_display_Info_help(IN I32_T sessionID, IN CLI_PRIV_HELPLIST_T *helpList)
{
    I32_T               	i;
    CLI_PRIV_HELPLIST_T	*tempList;

    tempList = CLI_MISC_Malloc(sizeof(CLI_PRIV_HELPLIST_T));
    CLI_MISC_Assert(tempList);

    /*
     * Not just copy.
     * Because after copy the tempList->name will point to helpList->name_buf,
     * so the tempList->name need change to point to tempList->name_buf.
     */
    memcpy(tempList, helpList, sizeof(CLI_PRIV_HELPLIST_T));
    for (i = 0; i < helpList->count; i++)
    {
        /* base address add the offset */
        tempList->name[i] = tempList->name_buf + (helpList->name[i] - helpList->name_buf);
    }

    /* translate parameter string to parameter format string and attch the help information */
    __cli2_api_translate_helpList(tempList);

    /* when display help information, will enable paging function */
    bc_cli_session_set_pagestopstatus(TRUE);

    if (helpList->nexthelp) /* display next possible word and according help information */
    {
        __cli2_api_display_Info_next(sessionID, tempList);
    }
    else /* display current possible input word  */
    {
        __cli2_api_display_Info_current(sessionID, tempList);
    }

    /* display the paging function */
    bc_cli_session_set_pagestopstatus(FALSE);
    CLI_API_Printf(sessionID, "\r\n");

    CLI_MISC_Free(tempList);
}


extern UI32_T total_byte;
/**************************************************************************
FUNCTION NAME:
    __cli2_api_cfg_file_progress_rate

DESCRIPTION:
    print configure file command execute progress rate

INPUT:
    cmd_buf		command string for execute

OUTPUT:
    NA

RETURN:


NOTES:

HISTORY:

**************************************************************************/
static void __cli2_api_cfg_file_progress_rate(IN I8_T *cmd_buf)
{
	float	 step = 0.0;	 
	I32_T	 cmd_len = 0;	 
	UI32_T	 percent = 0;

	if (NULL == cmd_buf)
	{
		return;
	}

	cmd_len = strlen(cmd_buf);

	step = 100 * (1.0 * cmd_len / total_byte);
	complete += step;
	
	percent = (UI32_T)complete;

#ifdef BC_PT_D12G
	CLI_MSG_INI(l_mdl_id, "\rOLT Configuration...................................%2u%%", percent);
#else
	CLI_MSG_INI(l_mdl_id, "\rOLT Configuration.............................%2u%%", percent);
#endif

	return;	
}


/**************************************************************************
FUNCTION NAME:
    cli_main_process

DESCRIPTION:
    Run the main process of CLI kernel for the input session.

INPUT:
    map_sessionID   : mapped session ID for other modules used
    pseudo_enable	: pseudo task enable

OUTPUT:
    NA

RETURN:
    quit reason
    the value is in bc_cli_vkey.h
    CLI_VKEY_IO_CLOSED
    CLI_VKEY_IO_TIMEOUT
    ...

NOTES:

HISTORY:

**************************************************************************/
I32_T cli_main_process(IN I32_T map_sessionID, IN BOOL_T pseudo_enable)
{
    cli_sesn_t  	*session;
    BOOL_T          next_help_flag;
    I32_T           i;
    I32_T           ret_value, cmd_ret;
    I32_T           cmdlen;
    I8_T            view[CLI_DIR_WD_MAX + 1];
    I32_T           noEditeLen;
    UI8_T           level;
	I8_T			user_name[32 + 1] = {0};

    /* check if the session is already created */
    session = bc_cli_session_get();
    if (NULL == session)
    {
        return CLI_VKEY_IO_WRONGVALUE;
    }

    /* begin the main process */
#if 1
	if (TRUE == pseudo_enable)
	{
		bc_cli_session_set_scriptmode(TRUE);
		bc_cli_set_cmdpath(map_sessionID, CLI_MOD_GLBCFG_PATH, CLI_MOD_GLBCFG_PROM, NULL);
	}
	else
	{
		bc_cli_session_set_scriptmode(FALSE);
	}
#endif

    cmdlen = 0; /* clear command buffer */
	session->previous_ch = 0;

    while (1)
    {	
        /* get user command */
        bc_cli_session_sem_wait();
        if (session->quit_flag == TRUE)
        {	
			bc_cli_session_sem_post();
            break;
        }

        strcpy(view, cli_dir_get_cmdpath(session->hdir));
        level = session->acc_info.level;
        bc_cli_session_sem_post();

		/* timeout init, if no input ,cut connect */
		bc_cli_timeout_init();
		
        /* get input command */
        session->cmd[cmdlen] = '\0';
        ret_value = __cli2_api_get_usrcmd(session, pseudo_enable);

		if (TRUE == pseudo_enable)
		{
			/* print execute command progress rate */
			__cli2_api_cfg_file_progress_rate(session->cmd);	
		}
		if ((0 == strcasecmp("&", session->cmd)) && (TRUE == pseudo_enable))
		{
			break;
		}

        switch (ret_value)
        {
        case CLI_VKEY_IO_TIMEOUT:
            /* fall through */
            CLI_VIO_Erase(session->hvio, CLI_SCREEN_CLEAR);
            session->quit_flag = TRUE;
            session->quit_reason = CLI_VKEY_IO_TIMEOUT;
            continue;

        case CLI_VKEY_IO_CLOSED:
            /* fall through */
            session->quit_flag = TRUE;
            session->quit_reason = CLI_VKEY_IO_CLOSED;
            continue;

        default:
            break;
        }

        next_help_flag = FALSE;
        /* skip white spaces at the front of the line */
        for (i = 0; (session->cmd[i] == ' ') || (session->cmd[i] == '\t'); i++)
		{
            ;
		}

        if ((session->cmd[i] == '#') || (session->cmd[i] == '!'))
        {
            /* skip blank line or comments */
            if (ret_value == '\t')
            {
                CLI_API_Printf(map_sessionID, "\r\n");
            }

            continue;
        }

        if (session->cmd[i] == '\0')
        {
            if ((ret_value == '?') || (ret_value == '-'))
            {
                /* get next help word for input no valid word */
                ret_value = '-';
                session->cmd[0] = '\0';
            }
            else if (ret_value == '\n')
            {
                continue;
            }
        }
        else if (ret_value == '\n')
        {
            CLI_HIST_InsertItem(session->hhist, session->cmd + i);
        }
        else if ((ret_value == '?') || (ret_value == '-'))
        {
            CLI_HIST_InsertItem(session->hhist, session->cmd + i);
        }

        switch (ret_value)
        {
        case CLI_VKEY_CTRL_Z: /* empty command line */
            /* exit configure mode and return to user mode */
            cmdlen = 0;
            continue;

        case '\t': /* tab complete */
            session->previous_ch = 0;
            if (CLI_EDIT_Match_Tab(session->hedit, view, level, &session->helplist))
            {
                session->previous_ch = '\t';
            }
            cmdlen = strlen(session->cmd);
            continue;

        case '\n': /* execute command */
			/* write cli user command log */

			if ((memcmp(view, "/bcm", 4) == 0) && (memcmp(session->cmd, "exit", 4) != 0))
			{
				bc_platform_sem_wait(session->lock, BC_SEM_WAIT_FOREVER);
			//	bc_sys_bcm_string(session->cmd);	// bain.wang@outlook.com for cli
				memset(session->cmd, 0x00, CLI_API_MAX_CMD_LEN);
				bc_platform_sem_post(session->lock);
			}
			else
			{
				if (FALSE == pseudo_enable)
				{
					if (bc_cli_get_usr_name(map_sessionID, user_name) != TRUE)
						return CLI_VKEY_IO_WRONGVALUE;

				//	bc_log_wrt_user_log(user_name, session->cmd);	// bain.wang@outlook.com for cli
				}

				bc_cli_session_set_pagestopstatus(TRUE);
				cmd_ret = CLI_API_Execute_OneUserCmd(map_sessionID, session->cmd);
				bc_cli_session_set_pagestopstatus(FALSE);
				switch (cmd_ret)
				{
				case CLI_CMD_QUIT_SESSION:
					session->quit_flag   = TRUE;
					session->quit_reason = CLI_VKEY_IO_CLOSED;
					continue;

				case CLI_CMD_FAIL_PRT_PROMPT:
					CLI_API_Printf(map_sessionID, "Failure\r\n");
					break;

				case CLI_CMD_SUCCESS_PRT_PROMPT:
					if (TRUE == pseudo_enable)
						break;
					CLI_API_Printf(map_sessionID, "Success\r\n");
					break;

				case CLI_CMD_FAIL_PRT_NONE:
				case CLI_CMD_SUCCESS_PRT_NONE:
					break;

				case CLI_CMD_FAIL_PRT_PROMPT_NEWLINE:
					CLI_API_Printf(map_sessionID, "\r\nFailure\r\n\r\n");
					break;

				case CLI_CMD_SUCCESS_PRT_PROMPT_NEWLINE:
					if (TRUE == pseudo_enable)
						break;
					CLI_API_Printf(map_sessionID, "\r\nSuccess\r\n\r\n");
					break;

				case CLI_CMD_FAIL_PRT_NEWLINE:
				case CLI_CMD_SUCCESS_PRT_NEWLINE:
					if (TRUE == pseudo_enable)
						break;
					CLI_API_Printf(map_sessionID, "\r\n");
					break;

				default:
					break;
				}

				cmdlen = 0;
			}

			break;

        case '-':
            /* fall through */
            /* get the help of the word just after the command line */
            next_help_flag = TRUE;

        case '?':
			if ((memcmp(view, "/bcm", 4) == 0) && (memcmp(session->cmd, "exit", 4) != 0))
			{
				bc_platform_sem_wait(session->lock, BC_SEM_WAIT_FOREVER);
			//	bc_sys_bcm_string(session->cmd);	// bain.wang@outlook.com for cli
				memset(session->cmd, 0x00, CLI_API_MAX_CMD_LEN);
				bc_platform_sem_post(session->lock);
			}
			else
			{
	            /* get the help of the last word in the command line */
	            cmdlen = strlen(session->cmd);
	            session->cmd[cmdlen] = '\0';
	            bc_platform_sem_wait(session->lock, BC_SEM_WAIT_FOREVER);

	            session->helplist.nexthelp = next_help_flag;
	            session->helplist.local_help = bc_cli_session_get_lan();
	            if (CLI_CORE_Get_Help(&session->helplist, view, session->cmd, level) < 0)
	            {
	                /* get no editing length */
	                noEditeLen = CLI_EDIT_Get_PromptLen(session->hedit);
	                for (i = 1; i <= (session->helplist.error_pos + noEditeLen); i++)
	                {
	                    CLI_API_Printf(map_sessionID, " ");
						if (!(i % 80))
						{
							CLI_API_Printf(map_sessionID, "\r\n");
						}
	                }
					CLI_API_Printf(map_sessionID, "^\r\n");
					CLI_API_Printf(map_sessionID, "Invalid input detected at \"^\" marker!\r\n");
	            }
	            else
	            {
	                __cli2_api_display_Info_help(map_sessionID, &session->helplist);
	            }

	            bc_platform_sem_post(session->lock);
			}

            break;

        default:
            session->previous_ch = ret_value;
            break;
        }
	}
	
    return session->quit_reason;
}



void __key_set(void)
{
    struct termios  new_tty;  

    tcgetattr(0, &l_tty);  
    new_tty = l_tty;  
    new_tty.c_lflag &= ~(ICANON | ECHO | ISIG);  
    new_tty.c_cc[VTIME] = 0;  
    new_tty.c_cc[VMIN] = 1;  
    tcsetattr(0, TCSANOW, &new_tty);  

    return;
}  



void __key_reset(void)
{
    tcsetattr(0, TCSANOW, &l_tty);  
    return;
}



char __key_getch(void)
{
    int     i;  
    char    ch;  

    i = read(0, &ch, 1);

    switch (i)
    {
    case 1: /* 读取成功 */
		break;
    case -1: /* 读取错误 */
		CLI_DBG_CPL(l_mdl_id, "命令读取：错误\r\n");
        ch = 0;
		break;
    case 0: /* 文件尾，读完 */
		CLI_DBG_CPL(l_mdl_id, "命令读取：标准输入文件以读取完毕\r\n");
        ch = 0;
		break;
	default:
		CLI_DBG_CPL(l_mdl_id, "命令读取：默认错误，返回%d\r\n", i);
        ch = 0;
		break;
    }  

	return (ch);
}  



/*------------------------------------------------------------------------
 * Function   : __cli_io_put_str_to_rs232
 * Purpose    : Put string to standard output
 * Parameters :
 *    Input   : sessionId = session identifier
 *              string = output string
 *              length = string length
 *    Output  : NA
 * Returns    : NA
 *------------------------------------------------------------------------
 */
static void __cli_io_put_str_to_rs232
    (
    int     sessionID,
    UI8_T 	*str,
    int     len
    )
{
    int i;

    if (sessionID) {}
    if (str == NULL || len <= 0)
        return ;

    for (i = 0; i < len; i++)
    {
        putchar(str[i]);
    }

	fflush(stdout);
}



/*------------------------------------------------------------------------
 * Function   : __cli_io_get_str_from_rs232
 * Purpose    : Get char from standard input
 * Parameters :
 *    Input   : sessionID = session identifier
 *              timeout = not use (blocking)
 *    Output  : NA
 * Returns    : The charater
 *------------------------------------------------------------------------
 */
static int __cli_io_get_str_from_rs232
    (
    int sessionID,
    int timeout
    )
{
	I32_T   rx_int = 0;
	char 	rx_ch;  

	UNUSED(sessionID);

  	__key_set();  
	rx_ch = __key_getch();  
    CLI_DBG_CPL(l_mdl_id, "[rx_ch=\"%c\",%d,0x%X]\r\n", rx_ch, rx_ch, rx_ch);  
  	rx_int = (int)rx_ch;
  	__key_reset();  
	
    return rx_int;
}



/*------------------------------------------------------------------------
 * Function   : _CLI_IO_Check_WinBufferEmpty
 * Purpose    : Check standard input buffer is empty
 * Parameters :
 *    Input   : sessionID = session identifier
 *    Output  : NA
 * Returns    : 0
 *------------------------------------------------------------------------
 */
static BOOL_T __cli_io_check_rs232_buf_empty
    (
    int sessionID
    )
{
    if (sessionID) {}

    if (xkbhit())
    {
        return TRUE;
    }

    bc_platform_time_usleep(50 * 1000);
    return (xkbhit()) ? TRUE : FALSE;
}


#if 1
/**************************************************************************
FUNCTION NAME:
    __cli2_io_check_loginbyloginlocal

DESCRIPTION:
    Login process by login local method.

INPUT:
    session_id  : created session ID by CLI kernel

OUTPUT:
    user_item   : auth information

RETURN:
    TRUE        : auth success
    FALSE       : auth fail

NOTES:

HISTORY:
    Creat by bain.wang@outlook.com 2011.6.29

**************************************************************************/
static BOOL_T __cli2_io_check_loginbyloginlocal(IN const UI32_T sessionID, OUT bc_usermgmt_info_t *user_item)
{
    I32_T   trigger[]   =
    {
        CLI_VKEY_CTRL_ENTER, CLI_VKEY_CR, 0
    };
    I32_T   rxCh;
    I8_T    *temp_ptr;
    I8_T    username_buf[BOOTUP_LOGIN_BUFLEN];
    I8_T    password_buf[BOOTUP_LOGIN_BUFLEN];
    //I8_T    login_name[32];
    I32_T   retry_times;
	bc_usermgmt_level_e level;
	bc_err_e  ret = BC_ERR_OK;

    CLI_API_Printf(sessionID, "\n\rUser Access Verification\n\r");

    /* if the login methold is login local, get the username
        and password the auth */
    retry_times = 0;
    while (retry_times < BOOTUP_LOGIN_MAXRETRYTIME)
    {
        temp_ptr = username_buf;
        memset(username_buf, 0, sizeof(username_buf));
        CLI_API_Printf(sessionID, "\n\rUsername:");
        rxCh = bc_cli_get_line(sessionID, sizeof("Username:"), CLI_OUTPUT_NORMAL, username_buf, sizeof(username_buf), BOOTUP_LOGIN_INPUT_TIMEOUTSEC, trigger);
		switch (rxCh)
        {
        case CLI_VKEY_IO_CLOSED:
        case CLI_VKEY_IO_EXITCMD:
        case CLI_VKEY_IO_WRONGVALUE:
            return FALSE;

        case CLI_VKEY_IO_TIMEOUT:
            CLI_API_Printf(sessionID, "\n\r%% Username:  timeout expired!");
            retry_times++;
            continue;

        case CLI_VKEY_IO_NOTIFY:
            continue;

        default:
            while (*temp_ptr == ' ' || *temp_ptr == '\t')
            {
                temp_ptr++;
            }
            if (*temp_ptr == '\0')
            {
                continue;
            }
            break;
        }

        memset(password_buf, 0, sizeof(password_buf));
        CLI_API_Printf(sessionID, "\n\rPassword:");
        rxCh = bc_cli_get_line(sessionID, sizeof("Password:"), CLI_OUTPUT_PASSWORD, password_buf, sizeof(password_buf), BOOTUP_LOGIN_INPUT_TIMEOUTSEC, trigger);
        switch (rxCh)
        {
        case CLI_VKEY_IO_CLOSED:
        case CLI_VKEY_IO_EXITCMD:
        case CLI_VKEY_IO_WRONGVALUE:
            return FALSE;

        case CLI_VKEY_IO_TIMEOUT:
            CLI_API_Printf(sessionID, "\n\r%% Password:  timeout expired!");
            retry_times++;
            continue;

        case CLI_VKEY_IO_NOTIFY:
            continue;

        default:
            break;
        }

        if (strlen(username_buf) < 32)
        {
            strncpy(user_item->name, username_buf, 32);
			//printf("\n====username: %s, len: %d, password: %s, len: %d\n", username_buf, strlen(username_buf), password_buf, strlen(password_buf));
			if (BC_ERR_OK == (ret = bc_usermgmt_login(username_buf, password_buf, &level)))
			{
				user_item->level = level;
				return TRUE;
			}
#if 0			
            if (PRIVMGMT_MGT_Find_UserItem(user_item))
            {
                if (PRIVMGMT_MGT_IS_PasswordSame(password_buf, user_item->password))
                {
                    CLI_API_Printf(sessionID, "\n\r\n\r");
                    return TRUE;
                }
            }
#endif
		}
        else
        {
            memcpy(user_item->name, username_buf, 32);
            user_item->name[31] = '\0';
        }
		
        CLI_API_Printf(sessionID, "\n\r%% Login invalid\n\r");

        /*need add log, change the session login name to want set login name */
        //bc_cli_session_get_loginname(login_name);
        bc_cli_session_set_loginname(user_item->name);
        //CLI_PORT_Log(sessionID, CLI_LOG_FAIL);
        //bc_cli_session_set_loginname(login_name);

        retry_times++;
    }

    return FALSE;
}
#endif


#if 0
/**************************************************************************
FUNCTION NAME:
    __cli2_io_check_loginbylinelogin

DESCRIPTION:
    Login process by line login method.

INPUT:
    session_id  : created session ID by CLI kernel
    line        : the line number of the session

OUTPUT:
    NA

RETURN:
    TRUE        : auth success
    FALSE       : auth fail

NOTES:

HISTORY:
    Creat by bain.wang@outlook.com 2011.6.29

**************************************************************************/
static BOOL_T __cli2_io_check_loginbylinelogin(IN const UI32_T sessionID, IN UI32_T line)
{
    I32_T   trigger[]   =
    {
        CLI_VKEY_CTRL_ENTER, CLI_VKEY_CR, 0
    };
    I32_T   rxCh;
    I8_T    password_buf[BOOTUP_LOGIN_BUFLEN];
    I8_T    login_name[PRIVMGMT_USER_NAME_MAX_BUF_LEN];
    I32_T   retry_times;

    CLI_API_Printf(sessionID, "\n\rUser Access Verification\n\r");

    retry_times = 0;
    while (retry_times < BOOTUP_LOGIN_MAXRETRYTIME)
    {
        memset(password_buf, 0, sizeof(password_buf));
        CLI_API_Printf(sessionID, "\n\rPassword:");
        rxCh = bc_cli_get_line(sessionID, sizeof("Password:"), CLI_OUTPUT_PASSWORD, password_buf, sizeof(password_buf), BOOTUP_LOGIN_INPUT_TIMEOUTSEC, trigger);
        switch (rxCh)
        {
        case CLI_VKEY_IO_CLOSED:
        case CLI_VKEY_IO_EXITCMD:
        case CLI_VKEY_IO_WRONGVALUE:
            return FALSE;

        case CLI_VKEY_IO_TIMEOUT:
            CLI_API_Printf(sessionID, "\n\r%% Password:  timeout expired!");
            retry_times++;
            continue;

        case CLI_VKEY_IO_NOTIFY:
            continue;

        default:
            break;
        }

        if (PRIVMGMT_MGT_Is_LinePassword_Correct(line, password_buf))
        {
            CLI_API_Printf(sessionID, "\n\r\n\r");
            return TRUE;
        }

        retry_times++;
    }

    CLI_API_Printf(sessionID, "\n\r%%  Bad password");
    /*need add log, change the session login name to want set login name */
    bc_cli_session_get_loginname(login_name);
    bc_cli_session_set_loginname(PRIVMGMT_ANONYMOUS_USER);
    CLI_PORT_Log(sessionID, CLI_LOG_FAIL);
    bc_cli_session_set_loginname(login_name);

    return FALSE;
}
#endif


/**************************************************************************
FUNCTION NAME:
    __cli2_io_login_process

DESCRIPTION:
    Execute the login process

INPUT:
    session_id  : created session ID by CLI kernel

OUTPUT:
    NA

RETURN:
    TRUE/FALSE

NOTES:

HISTORY:
    Creat by bain.wang@outlook.com 2011.6.29

**************************************************************************/
static BOOL_T __cli2_io_login_process
    (
    IN I32_T sessionID
    )
{
#if 0
    return TRUE;
#else
    //I8_T                    *greeingMsgBuf;
    //I32_T                   greetingMsgLen;
    //UI32_T                  line;
    //PRIVMGMT_LOGIN_MODE_T   state;
    bc_usermgmt_info_t      user_item;
    //AAA_LINE_LOGIN_INFO_T   ui_login_info;
    BOOL_T                  ret;

#if 0
    /* console checking */
    if (sessionID == VT_RS232_CHANNEL)
    {
        I32_T   rxChr;

        bc_cli_clear_screen(sessionID);
        CLI_API_Printf(sessionID, "\n\rSwitch con0 is now available");
        CLI_API_Printf(sessionID, "\n\r\n\r\n\r\n\r\n\r");
        CLI_API_Printf(sessionID, "\n\rPress RETURN to get started.\n\r\n\r");

        /* clear all input characters in rx buffer */
        DEV_UART_Clear_RxBuffer(PROJ_OS_DEFAULT_UART);
        for (; ;)
        {
            rxChr = bc_cli_api_vt_getc(sessionID, 100);
            if ((rxChr == VT_CTRL_ENTER) || (rxChr == CLI_VKEY_CR))
            {
                break;
            }
        }

        /* clear all input characters in rx buffer */
        DEV_UART_Clear_RxBuffer(PROJ_OS_DEFAULT_UART);
    }

    /* first print greeting message */
    greeingMsgBuf = CLI_MISC_Malloc(BANNER_MAX_LINE * (BANNER_MAX_COLUMN + 10));
    bc_cli_clear_screen(sessionID);
    if (greeingMsgBuf)
    {
        CLI_BNR_Get_GreetingMsg(greeingMsgBuf, (BANNER_MAX_LINE * (BANNER_MAX_COLUMN + 10)), &greetingMsgLen);
        CLI_API_Printf(sessionID, "%s", greeingMsgBuf);
        CLI_MISC_Free(greeingMsgBuf);
        CLI_API_Printf(sessionID, "\n\r");
    }
#endif

    /* user login process */
    ret = FALSE;
    memset(&user_item, 0x0, sizeof(bc_usermgmt_info_t));
    //strncpy(user_item.username, PRIVMGMT_ANONYMOUS_USER, 32);
    //user_item.privilege_level = CLI_ACC_LVL_BASIC;

#if 0
    if (LINE_API_Get_LineNumBySessionID(sessionID, &line) == FALSE)
    {
        return FALSE;
    }


    /* get the session login methold check if it is login auth */
    PRIVMGMT_MGT_Get_LineLoginMethod(line, &state);
    switch (state)
    {
    case NO_LOGIN:
        ret = TRUE;
        break;

    case LOGIN_LOCAL:
        ret = __cli2_io_check_loginbyloginlocal(sessionID, &user_item);
        break;

    case LOGIN_AUTH:
        memset(&ui_login_info, 0, sizeof(AAA_LINE_LOGIN_INFO_T));
        ui_login_info.line_num = line;
        ret = AAA_API_Login_FromLine(&ui_login_info);
        if (ret)
        {
            strncpy(user_item.username, ui_login_info.username, PRIVMGMT_USER_NAME_MAX_BUF_LEN);
            user_item.privilege_level = ui_login_info.access_level;
        }
        break;

    case LOGIN:
        ret = __cli2_io_check_loginbylinelogin(sessionID, line);
        break;

    default:
        return FALSE;;
    }
#endif

	ret = __cli2_io_check_loginbyloginlocal(sessionID, &user_item);
    if (ret)
    {
        DEV_RTC_TIME_T  login_time;
        bc_loc_date_t   date;
        bc_uint64       us;
        UI32_T          ms;

        /* set the login information on session */
        bc_platform_time_date_get(&date);
        login_time.year = date.loc_year;
        login_time.month = date.loc_mon;
        login_time.monthday = date.loc_mday;
        login_time.weekday = date.loc_wday;
        login_time.hour = date.loc_hour;
        login_time.minute = date.loc_min;
        login_time.second = date.loc_sec;

        bc_platform_time_us_get(&us);
        ms = us / 1000;

        bc_cli_session_set_logintime(&login_time, ms);
        bc_cli_session_set_loginname(user_item.name);
        bc_cli_session_set_lvl((UI8_T) user_item.level);

        //CLI_PORT_Log(sessionID, CLI_LOG_SUCCESS);
        //ACCT_API_Login_FromLine(line);
    }
    return ret;
#endif
}



/**************************************************************************
FUNCTION NAME:
    __cli2_io_logout_process

DESCRIPTION:
    Execute the logout process

INPUT:
    session_id  : created session ID by CLI kernel
    logout_flag : session logout flag

OUTPUT:
    NA

RETURN:
    TRUE/FALSE

NOTES:

HISTORY:
    Creat by bain.wang@outlook.com 2011.6.29

**************************************************************************/
static BOOL_T __cli2_io_logout_process
    (
    IN I32_T sessionID,
    IN I32_T logout_flag
    )
{
#if 0
    UI32_T  line;

    if (LINE_API_Get_LineNumBySessionID(sessionID, &line) == FALSE)
    {
        return FALSE;
    }

    switch (logout_flag)
    {
    case CLI_VKEY_IO_TIMEOUT:
        ACCT_API_Timeout_FromLine(line);
        CLI_PORT_Log(sessionID, CLI_LOG_TIMEOUT);
        break;

    case CLI_VKEY_IO_CLOSED:
    case CLI_VKEY_IO_EXITCMD:
        ACCT_API_Logout_FromLine(line);
        CLI_PORT_Log(sessionID, CLI_LOG_LOGOUT);
        break;

    default:
        ACCT_API_Logout_FromLine(line);
        break;
    }
#endif
    return TRUE;
}



#if 1
/******************************************************************************\
  Function   : __cli_get_language
  Description: 
  Return     : 
  Others     : 
\******************************************************************************/
static cli_lan_t __cli_get_language(void)
{
	cli_lan_t 			language = CLI_LAN_MAX;
	bc_sys_baseinfo_t	sys_info;

	CLI_DBG_ENTER(l_mdl_id);

	/* 通过OLT核心进程获取到 */
	memset(&sys_info, 0x00, sizeof(sys_info));
	bc_sys_ipc_baseinfo(&sys_info);
	language = (cli_lan_t)sys_info.def_lan;
	if (CLI_LAN_CN == language)
	{
		CLI_DBG_LEAVE(l_mdl_id);
		return CLI_LAN_CN;
	}

	CLI_DBG_LEAVE(l_mdl_id);
	return CLI_LAN_EN;
}



/******************************************************************************\
  Function   : __cli_set_language
  Description: 
  Return     : 
  Others     : 
\******************************************************************************/
static void __cli_set_language(IN cli_lan_t lan, IN I32_T session_id)
{

	CLI_DBG_ENTER(l_mdl_id);
	
	CLI_DBG_CPL(l_mdl_id, "language = %d, session_id = %d\r\n", lan, session_id);
	switch (lan)
	{
	case CLI_LAN_CN:
		bc_cli_set_lan(session_id, TRUE);
		break;

	case CLI_LAN_EN:
		if (FALSE == bc_cli_set_lan(session_id, FALSE))
			CLI_API_Printf(session_id, "cli set language error!\r\n");
		break;

	default:
		break;
	}

	CLI_DBG_LEAVE(l_mdl_id);

	return;
}



#endif




/*------------------------------------------------------------------------
 * Function   : __io_start_menu
 * Purpose    : Main Menu Process
 * Parameters :
 *    Input   : ptrIcb = io control block for CLI
 *              level = user initial level
 *    Output  : NA
 * Returns    : NA
 *------------------------------------------------------------------------
 */
void __io_start_menu
    (
    VT_IOCTL_T *ptrIcb,
    const int   level
    )
{
    CLI_DBG_ENTER(l_mdl_id);

    CLI_TERMINAL_IO_T  terminal_io;
    CLI_IP_INFO_T      ip_info;
    I32_T               sessionID;
    I32_T               ret_flag;

    terminal_io.putstr = ptrIcb->putstr;
    terminal_io.getchar = ptrIcb->getchar;
    terminal_io.checkEmpty = ptrIcb->checkEmpty;
    terminal_io.sessionID = ptrIcb->sessionID;

    /* get ip address information */
    ip_info.ipaddr = ptrIcb->ipAddress;
    memcpy(&ip_info.ipv6addr, ptrIcb->ip6Address, sizeof(LA3_IP6ADDR));
    if (ptrIcb->ip6Flag)
    {
        ip_info.is_ipv6 = TRUE;
    }
    else
    {
        ip_info.is_ipv6 = FALSE;
    }

	if (1 == setjmp(bc_jmp_buf))
	{
		CLI_DBG_CPL(l_mdl_id, "success jump this! OK OK OK!\n");
	}

    sessionID = bc_cli_session_create(ptrIcb->sessionID, ptrIcb->flags, &terminal_io, CLI_VT100, &ip_info, NULL);
    if (sessionID < 0)
    {
        return;
    }

#if 1
	/* set language */
	__cli_set_language(__cli_get_language(), sessionID);

#endif

    bc_cli_session_set_lvl(level);
    bc_cli_session_set_pagestopstatus(FALSE);

#if 0
    /* wait the boot-up configuration execute completed, then execute login process */
    while (ST_STACK_Get_CliCfgKickoff() == FALSE)
    {
        OS_TASK_Sleep_Msec(100);
    }
#endif

    /* Login process */
    if (__cli2_io_login_process(sessionID))
    {
    	/* display the login banner */
		cli_bnr_cmd_show_banner(0, NULL, NULL);
		CLI_API_Printf(-1, "\r\n");

        ret_flag = cli_main_process(sessionID, FALSE);

        /* logout process */
        __cli2_io_logout_process(sessionID, ret_flag);
    }

    bc_cli_session_destroy(sessionID);

    CLI_DBG_LEAVE(l_mdl_id);
    return;
}



/*------------------------------------------------------------------------
 * Function   : cli_io_task
 * Purpose    : the main task
 * Parameters :
 *    Input   : argc = no use
 *              (argv) = no use
 *    Output  : NA
 * Returns    : NA
 *------------------------------------------------------------------------
 */
void cli_io_task
    (
    void *argv
    )
{
    CLI_DBG_ENTER(l_mdl_id);

    VT_IOCTL_T  icb;

    UNUSED(argv);

    memset(&icb, 0x0, sizeof(VT_IOCTL_T));

    icb.putstr = __cli_io_put_str_to_rs232;
    icb.getchar = __cli_io_get_str_from_rs232;
    icb.checkEmpty = __cli_io_check_rs232_buf_empty;
    icb.flags = CLI_SESN_TYPE_CONSOLE;
    icb.sessionID = VT_RS232_CHANNEL;
    icb.ipAddress = 0;

    /* set debug input/output for show-tech and debug in CLI(telnet), the input/output will use CLI session print */
    //OS_DEBUG_Register_IOFunc(DEBUG_IO_CLI, __cli_io_os_debug_getc_cli, __cli_io_os_debug_vprintf);

    // After removing console task, baud-rate init must be called in cli task.
    // If cli task does not call baud-rate init, baud-rate will not restore its value without console after rebooting.
    /* init baudrate */
    //__console_UART_Init();

    //__io_start_menu(&icb, CLI_ACC_LVL_BASIC);
    __io_start_menu(&icb, CLI_ACC_LVL_DEBUG);

    CLI_DBG_LEAVE(l_mdl_id);
    return;
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *   cli_ker_cmd_reg
 *
 * DESCRIPTION:
 *   Init cli2 environment when switch startup, this function must called
 *   before other cli2 functions been called.
 *
 * INPUT:
 *   NA
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   0  -- init success
 *   -1 -- init failure
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2009-Mar-25 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
I32_T cli_ker_cmd_reg(void)
{
	CLI_DBG_ENTER(l_mdl_id);

#if CLI_COMMAND_LOGGING_INCLUDED
    bc_cli_log_cmd_reg();
#endif

    bc_cli_sys_cmd_reg();
    bc_cli_bnr_cmd_reg() ;

	CLI_DBG_LEAVE(l_mdl_id);
    return 0;
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *   cli_ker_init
 *
 * DESCRIPTION:
 *   Initialize CLI's OS resource and fixed database
 *
 * INPUT:
 *   NA
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
 *   2010-Mar-05 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
void cli_ker_init(void)
{
	CLI_DBG_ENTER(l_mdl_id);

    bc_cli_session_create_sem();
    bc_cli_core_init();
    bc_cli_para_init();
    bc_cli_bnr_init();
#if CLI_COMMAND_LOGGING_INCLUDED
    bc_cli_log_init();
#endif

    /* Add version control */
    //MODULE_API_Set_ModuleRevision(MOD_CLI, CLI_REVISION);

	CLI_DBG_LEAVE(l_mdl_id);
	return;
}




