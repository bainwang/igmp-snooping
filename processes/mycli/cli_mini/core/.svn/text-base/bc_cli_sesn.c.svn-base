
#include "bc_modules.h"
#include "bc_platform_sem.h"

#include "bc_cli_type.h"
#include "bc_cli_vkey.h"
#include "bc_cli_hist.h"
#include "bc_cli_kernel_cfg.h"
//#include "bc_cli_acc.h"
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



static unsigned int 	l_mdl_id = BC_MODULE_CLI_KERNEL;

static cli_sesn_t   	*s_sesn_list = NULL;	// the pointer of session list, no head node, only a pointer

HANDLE_T         		bc_sesn_mtx = NULL; 	// the mutex of session , to lock all the cli2 sessions



/*******************************************************************************
 *
 * FUNCTION NAME:
 *   __cli2_api_insert_session
 *
 * DESCRIPTION:
 *   insert a session to session list
 *
 * INPUT:
 *   session -- session to be inserted
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
 *   2009-May-31 by wangbin -- Create
 *
*******************************************************************************/
static void __cli2_api_insert_session(IN cli_sesn_t *session)
{
    bc_platform_sem_wait(bc_sesn_mtx, BC_SEM_WAIT_FOREVER);

    session->next = s_sesn_list;
    session->prev = NULL;

    if (s_sesn_list)
    {
        s_sesn_list->prev = session;
    }

    s_sesn_list = session;

    bc_platform_sem_post(bc_sesn_mtx);
	return;
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *   __cli2_api_remove_session
 *
 * DESCRIPTION:
 *   remove a session from session list
 *
 * INPUT:
 *   session  -- session to be removed
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   not NULL -- session has been removed from session list.
 *   NULL     -- session not found.
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2009-May-31 by wangbin -- Create
 *
*******************************************************************************/
static cli_sesn_t * __cli2_api_remove_session(IN cli_sesn_t *session)
{
    cli_sesn_t  *p;
    cli_sesn_t  *prev   = NULL;
    cli_sesn_t  *next   = NULL;

    if (NULL == session)
    {
        return NULL;
    }

    bc_platform_sem_wait(bc_sesn_mtx, BC_SEM_WAIT_FOREVER);
    p = s_sesn_list;
    while (p && (p != session))
    {
        p = p->next;
    }

    if (p)
    {
        prev = p->prev;
        next = p->next;
    }

    if (prev && next)
    {
        prev->next = next;
        next->prev = prev;
    }
    else if (prev)
    {
        prev->next = NULL;
    }
    else if (next)
    {
        s_sesn_list = next;
        next->prev = NULL;
    }
    else
    {
        s_sesn_list = NULL;
    }
    bc_platform_sem_post(bc_sesn_mtx);

    return p;
}



/**************************************************************************
FUNCTION NAME:
    cli_sesn_get_by_sid

DESCRIPTION:
    Get session struct information from session list by maped sessionID.

INPUT:
    map_sessionID   : map to old sessionID in CLIG1 for other module use

OUTPUT:
    NA

RETURN:
    pointer of session struct
    NULL            : the session with input map_sessionID is not exist

NOTES:

HISTORY:

**************************************************************************/
cli_sesn_t * cli_sesn_get_by_sid(IN I32_T       map_sessionID)
{
    cli_sesn_t  *temp_session;

    bc_platform_sem_wait(bc_sesn_mtx, BC_SEM_WAIT_FOREVER);
    temp_session = s_sesn_list;
    while (temp_session)
    {
        if (temp_session->map_sessionID == map_sessionID) // 找到
        {
            break;
        }

        // 该结点不是对应session，后移，继续找
        temp_session = temp_session->next;
    }
    bc_platform_sem_post(bc_sesn_mtx);

    // 返回时，可能是链表尾部空结点，即 the session with input map_sessionID is not exist，返回 NULL
    return temp_session;
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *   cli_api_get_hacc_from_session
 *
 * DESCRIPTION:
 *   Get handle for access data from session
 *
 * INPUT:
 *   session_id -- session ID
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   pointer for the access info
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2009-Mar-25 by wangbin -- Create
 *
*******************************************************************************/
CLI_ACC_INFO_T * cli_api_get_hacc_from_session(IN I32_T session_id)
{
    cli_sesn_t  *session;

    session = cli_sesn_get_by_sid(session_id);
    if (NULL == session)
    {
        return NULL;
    }

    return &(session->acc_info);
}



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
 *   2009-Mar-19 by wangbin -- Create
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
    acc_info->help_local = FALSE; // wangbin, 2014-05-22, cli_acc_set_lan
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



BOOL_T CLI_API_CreateSessionSem(void)
{
	CLI_DBG_ENTER(l_mdl_id);

	if (NULL != bc_sesn_mtx)
	{
		CLI_DBG_LEAVE(l_mdl_id);
		return TRUE;
	}

	CLI_DBG_TAG(l_mdl_id);
	bc_sesn_mtx = bc_platform_sem_create("cli2-module", 1);
	CLI_DBG_LEAVE(l_mdl_id);
	return (NULL != bc_sesn_mtx ? TRUE : FALSE);
}



void CLI_API_DestroySessionSem(void)
{
	bc_platform_sem_destroy(bc_sesn_mtx);
	return;
}



/**************************************************************************
FUNCTION NAME:
    CLI_API_Check_Session

DESCRIPTION:
    Check whether the input session ID is valid.

INPUT:
    sessionID   : created session ID by CLI kernel

OUTPUT:
    NA

RETURN:
    TRUE        : the session ID is valid can be used
    FALSE       : the session ID is invalid

NOTES:

HISTORY:

**************************************************************************/
BOOL_T CLI_API_Check_Session(IN I32_T sessionID)
{
    if (cli_sesn_get_by_sid(sessionID))
    {
        return TRUE;
    }

    return FALSE;
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_API_GetHvioFromSession
 *
 * DESCRIPTION:
 *   Get handle for vio from session
 *
 * INPUT:
 *   session_id -- session ID
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   handle for vio
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2009-Mar-25 by wangbin -- Create
 *
*******************************************************************************/
HANDLE_T CLI_API_GetHvioFromSession(IN I32_T session_id)
{
    cli_sesn_t  *session;

    session = cli_sesn_get_by_sid(session_id);
    if (NULL == session)
    {
        return NULL;
    }

    return session->hvio;
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_API_GetSessionData
 *
 * DESCRIPTION:
 *   Get the session data
 *
 * INPUT:
 *   session_id -- session ID
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   address of the session data
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2009-Mar-25 by wangbin -- Create
 *
*******************************************************************************/
void * CLI_API_GetSessionData(IN I32_T session_id)
{
    cli_sesn_t  *session;

    session = cli_sesn_get_by_sid(session_id);
    if (NULL == session)
    {
        return NULL;
    }

    return session->session_data;
}



/**************************************************************************
FUNCTION NAME:
    CLI_API_CreateSession

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
I32_T CLI_API_CreateSession
	(
	IN I32_T 				map_sessionID,
	IN cli_sesn_type_t 		session_type,
	IN CLI_TERMINAL_IO_T 	*hterm,
    IN CLI_VIOTYPE_T 		vio_type,
    IN CLI_IP_INFO_T 		*ip_info,
    IN void 				*session_data
    )
{
    cli_sesn_t  			*session;
    I8_T    				promptMsg[BNR_CPU_NAME_MAX_LEN + 1];

    if (cli_sesn_get_by_sid(map_sessionID))
    {
        /* the session is already exist */
        return -1;
    }

    /* allocate memory for session */
    session = CLI_MISC_Malloc(sizeof(cli_sesn_t));
    if (!session)
    {
        return -1;
    }
    memset(session, 0, sizeof(cli_sesn_t));

    /* set map session ID */
    session->map_sessionID = map_sessionID;

    /* init cli2 vio */
    session->session_type = session_type;
    session->session_data = session_data;

    session->hvio = CLI_VIO_Create(hterm, vio_type);
    if (NULL == session->hvio)
    {
        cli_misc_free(session);
        return -1;
    }

    /* init cli2 edit */
    session->hedit = CLI_EDIT_Create(session->hvio);
    if (NULL == session->hedit)
    {
        CLI_VIO_Destroy(session->hvio);
        cli_misc_free(session);
        return -1;
    }

    session->lock        = bc_platform_sem_create("cli2-session", 1);
    session->quit_flag   = FALSE;
    session->quit_reason = CLI_VKEY_IO_NOACTION;
    session->hhist       = CLI_HIST_Create(20);
    session->charset     = CLI_DEFAULT_CHARSET;

    /* add access infomation */
    __cli2_api_init_acc_info(&session->acc_info, "anonymous", CLI_ACC_LVL_BASIC, ip_info);

    /* init path information */
    session->hdir = CLI_DIR_Create();

    CLI_BNR_Get_Prompt(map_sessionID, promptMsg, BNR_CPU_NAME_MAX_LEN + 1);
	cli_dir_set_cmdpath(session->hdir, CLI_MOD_MONITOR_PATH, promptMsg, NULL);

    session->hfilter = NULL;

    __cli2_api_insert_session(session);

    return map_sessionID;
}



/**************************************************************************
FUNCTION NAME:
    CLI_API_DestroySession

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
void CLI_API_DestroySession(IN I32_T map_sessionID)
{
    cli_sesn_t  *session;

    session = cli_sesn_get_by_sid(map_sessionID);
    if (NULL == session)
    {
        return;
    }

    CLI_HIST_Destroy(session->hhist);
    CLI_EDIT_Destroy(session->hedit);
    bc_platform_sem_destroy(session->lock);
    CLI_VIO_Destroy(session->hvio);
    CLI_DIR_Destroy(session->hdir);
    __cli2_api_remove_session(session);
    cli_misc_free(session);
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_ACC_GetFirstInfo
 *
 * DESCRIPTION:
 *   Get first access information
 *
 * INPUT:
 *   NA
 *
 * OUTPUT:
 *   buf -- access information
 *
 * RETURN:
 *   -1 -- no session exist
 *   Maped session ID for other module used
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2009-Mar-19 by wangbin -- Create
 *
*******************************************************************************/
I32_T CLI_ACC_GetFirstInfo(OUT CLI_ACC_INFO_T *buf)
{
    cli_sesn_t  *ret_session;

    bc_platform_sem_wait(bc_sesn_mtx, BC_SEM_WAIT_FOREVER);
    ret_session = s_sesn_list;
    while (ret_session && ret_session->session_type == CLI_SESN_TYPE_PSEUDO)
    {
        ret_session = ret_session->next;
    }

    if (ret_session)
    {
        memcpy(buf, &(ret_session->acc_info), sizeof(CLI_ACC_INFO_T));
    }
    bc_platform_sem_post(bc_sesn_mtx);

    if (ret_session)
    {
        return ret_session->map_sessionID;
    }
    else
    {
        return -1;
    }
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_ACC_GetNextInfo
 *
 * DESCRIPTION:
 *   Get next access information
 *
 * INPUT:
 *   NA
 *
 * OUTPUT:
 *   buf -- access information
 *
 * RETURN:
 *   -1 -- no session exist
 *   Maped session ID for other module used
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2009-Mar-19 by wangbin -- Create
 *
*******************************************************************************/
I32_T CLI_ACC_GetNextInfo(IN I32_T hcur_session, OUT CLI_ACC_INFO_T *buf)
{
    cli_sesn_t  *session;
    cli_sesn_t  *ret_session;

    session = cli_sesn_get_by_sid(hcur_session);
    if (NULL == session)
    {
        return -1;
    }

    bc_platform_sem_wait(bc_sesn_mtx, BC_SEM_WAIT_FOREVER);
    ret_session = session->next;
    while (ret_session && ret_session->session_type == CLI_SESN_TYPE_PSEUDO)
    {
        ret_session = ret_session->next;
    }

    if (ret_session)
    {
        memcpy(buf, &(ret_session->acc_info), sizeof(CLI_ACC_INFO_T));
    }
    bc_platform_sem_post(bc_sesn_mtx);

    if (ret_session)
    {
        return ret_session->map_sessionID;
    }
    else
    {
        return -1;
    }
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *   cli_sesn_get_type
 *
 * DESCRIPTION:
 *   Get the session type from the specified session_id
 *
 * INPUT:
 *   session_id: session ID
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   session type
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2009-Jun-09 by wangbin -- Create
 *
*******************************************************************************/
cli_sesn_type_t cli_sesn_get_type(IN I32_T session_id)
{
    cli_sesn_t  *session;

    session = cli_sesn_get_by_sid(session_id);
    if (NULL == session)
    {
        return CLI_SESN_TYPE_NONE;
    }

    return session->session_type;
}



void cli_sesn_wait(void)
{
	if (NULL == bc_sesn_mtx)
	{
		return;
	}
	
	bc_platform_sem_wait(bc_sesn_mtx, BC_SEM_WAIT_FOREVER);
	return;
}



void cli_sesn_post(void)
{
	if (NULL == bc_sesn_mtx)
	{
		return;
	}

	bc_platform_sem_post(bc_sesn_mtx);
	return;
}



