
#include "bc_modules.h"
#include "bc_platform_sem.h"

#include "bc_cli_type.h"
#include "bc_cli_vkey.h"
#include "bc_cli_hist.h"
#include "bc_cli_kernel_cfg.h"
#include "bc_cli_paratype.h"
#include "bc_cli_chs.h"
#include "bc_cli_priv.h"
#include "bc_cli_term.h"
#include "bc_cli_vio.h"
#include "bc_cli_misc.h"
#include "bc_cli_sesn.h"
#include "bc_platform_time.h"
#include "bc_cli_edit.h"
#include "bc_cli_dir.h"
#include "bc_cli_bnr.h"

#include "bc_cli.h"


static HANDLE_T session_mutex = NULL; 	// the mutex of session , to lock all the cli2 sessions

static cli_sesn_t  session_info;

#if 1


BOOL_T bc_cli_session_get_scriptmode(void)
{
    return session_info.acc_info.script_mode;
}


void bc_cli_session_set_scriptmode(IN BOOL_T script_mode)
{
    session_info.acc_info.script_mode = script_mode;
}


BOOL_T bc_cli_session_get_lan(void)
{
    return session_info.acc_info.help_local;
}

BOOL_T bc_cli_session_set_lan(IN BOOL_T help_local)
{
	session_info.acc_info.help_local = help_local;
	return TRUE;
}


BOOL_T bc_cli_session_get_pagestopstatus(void)
{
    return session_info.acc_info.page_stop;
}

void bc_cli_session_set_pagestopstatus(IN BOOL_T page_stop)
{
	session_info.acc_info.page_stop = page_stop;
	session_info.acc_info.cursor_status.line = 0;
	session_info.acc_info.cursor_status.column = 0;
	session_info.acc_info.cursor_status.page_action = CLI_PAGE_NOACTION;
	session_info.acc_info.cursor_status.refresh_action = 0;
}

void bc_cli_session_get_cursorstatus(OUT CLI_ACC_CURSOR_STATUS_T *cursor_status)
{
    cursor_status->line = session_info.acc_info.cursor_status.line;
    cursor_status->column = session_info.acc_info.cursor_status.column;
    cursor_status->max_line = session_info.acc_info.cursor_status.max_line;
    cursor_status->max_column = session_info.acc_info.cursor_status.max_column;
    cursor_status->page_action = session_info.acc_info.cursor_status.page_action;
    cursor_status->refresh_action = session_info.acc_info.cursor_status.refresh_action;
}

void bc_cli_session_set_cursorstatus(IN CLI_ACC_CURSOR_STATUS_T *status)
{
	session_info.acc_info.cursor_status.line = status->line;
	session_info.acc_info.cursor_status.column = status->column;
	session_info.acc_info.cursor_status.page_action = status->page_action;
	session_info.acc_info.cursor_status.refresh_action = status->refresh_action;
}


UI32_T bc_cli_session_get_lvl(void)
{
    return session_info.acc_info.level;
}

void bc_cli_session_set_lvl(IN UI8_T level)
{
    session_info.acc_info.level = level;
}


void bc_cli_session_get_logintime(OUT DEV_RTC_TIME_T *login_time)
{
    memcpy(login_time, &session_info.acc_info.login_time, sizeof(DEV_RTC_TIME_T));
}

void bc_cli_session_set_logintime(IN DEV_RTC_TIME_T *login_time, IN UI32_T login_systemTime)
{
	memcpy(&session_info.acc_info.login_time, login_time, sizeof(DEV_RTC_TIME_T));
	session_info.acc_info.login_systemTime = login_systemTime;
}


void bc_cli_session_get_loginname(OUT I8_T login_name[CLI_ACC_MAX_NAMELEN + 1])
{
    strncpy(login_name, session_info.acc_info.login_name, CLI_ACC_MAX_NAMELEN + 1);
}


void bc_cli_session_set_loginname(IN I8_T login_name[CLI_ACC_MAX_NAMELEN + 1])
{
    strncpy(session_info.acc_info.login_name, login_name, CLI_ACC_MAX_NAMELEN + 1);
}


void bc_cli_session_get_accinfo(OUT CLI_ACC_INFO_T *acc)
{
    memcpy(acc, &(session_info.acc_info), sizeof(CLI_ACC_INFO_T));
}


#endif
#if 1

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   __cli2_api_init_acc_info
 *
 * DESCRIPTION:
 *   Init acc information
 *
 * INPUT:
 *   acc_info: point to the acc information
 *   login_name -- login name
 *   level -- current level of user
 *   ip_info -- IP address information(IPv4 && IPv6)
 *
 * OUTPUT:
 *   *acc_info: acc information already initted.
 *
 * RETURN:
 *   NULL -- failure
 *   not NULL -- handle of the access data
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2009-Mar-19 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
static HANDLE_T __cli2_api_init_acc_info
	(
	IN OUT CLI_ACC_INFO_T 	*acc_info,
    IN const I8_T 			login_name[CLI_ACC_MAX_NAMELEN + 1],
    IN UI8_T 				level,
    IN CLI_IP_INFO_T 		*ip_info)
{
    // save access info of the current session
    memset(acc_info->login_name, 0, sizeof(acc_info->login_name));
    strncpy(acc_info->login_name, login_name, CLI_ACC_MAX_NAMELEN);
    acc_info->level = level;
    acc_info->ipaddr = ip_info->ipaddr;
    acc_info->is_ipv6 = ip_info->is_ipv6;
    memcpy(&acc_info->ipv6addr, &ip_info->ipv6addr, sizeof(LA3_IP6ADDR));
    acc_info->script_mode = FALSE;
    acc_info->help_local = TRUE; 
    acc_info->page_stop = FALSE;
    acc_info->cursor_status.line = 0;
    acc_info->cursor_status.column = 0;
    acc_info->cursor_status.max_line = CLI_CFG_TERMINAL_LINE;
    acc_info->cursor_status.max_column = CLI_CFG_TERMINAL_COLUMN;
    acc_info->cursor_status.page_action = CLI_PAGE_NOACTION;
    acc_info->cursor_status.refresh_action = 0;
    //DEV_RTC_Get_Time(DEV_RTC_ID_1, &acc_info->login_time);
    bc_platform_time_sec_get(&acc_info->login_systemTime);

    return acc_info;
}


/**************************************************************************
FUNCTION NAME:
    bc_cli_session_create

DESCRIPTION:
    Create a session struct of CLI kernel.

INPUT:
    map_sessionID   : mapped session ID for other modules used
    session_type    : session type (CONSOLE, SSH, TELNET)
    hterm           : the terminal IO struct
    vio_type        : type of the terminal, such as VT100, LINUX, etc.
                      Now we only support for VT100
    ip_info         : IP address information (include IPv4 && IPv6)
    session_data    : only used as the return value of CLI_API_GetSessionData

OUTPUT:
    NA

RETURN:
    -1                  : fail to create session
    mapped session ID   : create session struct of CLI kernel success

NOTES:

HISTORY:

**************************************************************************/
I32_T bc_cli_session_create
	(
	IN I32_T 				map_sessionID,
	IN cli_sesn_type_t 		session_type,
	IN CLI_TERMINAL_IO_T 	*hterm,
    IN CLI_VIOTYPE_T 		vio_type,
    IN CLI_IP_INFO_T 		*ip_info,
    IN void 				*session_data
    )
{
    I8_T promptMsg[BNR_MAX_LEN] = {0};

    memset(&session_info, 0, sizeof(cli_sesn_t));

    /* set map session ID */
    session_info.map_sessionID = map_sessionID;

    /* init cli2 vio */
    session_info.session_type = session_type;
    session_info.session_data = session_data;

    session_info.hvio = CLI_VIO_Create(hterm, vio_type);
    if (NULL == session_info.hvio)
    {
        return -1;
    }

    /* init cli2 edit */
    session_info.hedit = CLI_EDIT_Create(session_info.hvio);
    if (NULL == session_info.hedit)
    {
        CLI_VIO_Destroy(session_info.hvio);
        return -1;
    }

    session_info.lock = bc_platform_sem_create("cli2-session", 1);
    session_info.quit_flag   = FALSE;
    session_info.quit_reason = CLI_VKEY_IO_NOACTION;
    session_info.hhist       = CLI_HIST_Create(20);
    session_info.charset     = CLI_DEFAULT_CHARSET;

    /* add access infomation */
    __cli2_api_init_acc_info(&(session_info.acc_info), "anonymous", CLI_ACC_LVL_BASIC, ip_info);

    /* init path information */
    session_info.hdir = CLI_DIR_Create();

    CLI_BNR_Get_Prompt(map_sessionID, promptMsg, BNR_MAX_LEN);
	cli_dir_set_cmdpath(session_info.hdir, CLI_MOD_MONITOR_PATH, promptMsg, NULL);

    session_info.hfilter = NULL;
		
    return map_sessionID;
}



/**************************************************************************
FUNCTION NAME:
    bc_cli_session_destroy

DESCRIPTION:
    Destroy the session struct of CLI kernel (release the resource).

INPUT:
    map_sessionID   : mapped session ID for other modules used

OUTPUT:
    NA

RETURN:

NOTES:

HISTORY:

**************************************************************************/
void bc_cli_session_destroy(IN I32_T map_sessionID)
{
    CLI_HIST_Destroy(session_info.hhist);
    CLI_EDIT_Destroy(session_info.hedit);
    bc_platform_sem_destroy(session_info.lock);
    CLI_VIO_Destroy(session_info.hvio);
    CLI_DIR_Destroy(session_info.hdir);
}

cli_sesn_type_t bc_cli_session_get_type(void)
{
    cli_sesn_t  *session;

    session = bc_cli_session_get();
    if (NULL == session)
    {
        return CLI_SESN_TYPE_NONE;
    }

    return session->session_type;
}

I32_T bc_cli_session_get_timeout(void)
{
	return session_info.timeout;
}

cli_sesn_t * bc_cli_session_get(void)
{
    return &session_info;
}

HANDLE_T bc_cli_session_get_hvio(void)
{
    return session_info.hvio;
}

BOOL_T bc_cli_session_get_quit_flag(OUT BOOL_T *quit_flag, OUT I32_T *quit_reason)
{
    *quit_flag   = session_info.quit_flag;
    *quit_reason = session_info.quit_reason;

	return TRUE;
}

void bc_cli_session_set_quit_flag(IN BOOL_T quit_flag, IN I32_T quit_reason)
{
    session_info.quit_flag   = quit_flag;
    session_info.quit_reason = quit_reason;
}


#endif
#if 1

BOOL_T bc_cli_session_create_sem(void)
{
	if (NULL != session_mutex)
		return TRUE;

	session_mutex = bc_platform_sem_create("cli-session-glb", 1);
	return (NULL != session_mutex ? TRUE : FALSE);
}

void bc_cli_session_sem_wait(void)
{
	if (NULL == session_mutex)
	{
		return;
	}
	
	bc_platform_sem_wait(session_mutex, BC_SEM_WAIT_FOREVER);
	return;
}

void bc_cli_session_sem_post(void)
{
	if (NULL == session_mutex)
	{
		return;
	}

	bc_platform_sem_post(session_mutex);
	return;
}

#endif

