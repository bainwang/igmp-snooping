
#ifndef __BC_CLI_SESN__
#define __BC_CLI_SESN__

#include "bc_cli_paratype.h"
#include "bc_cli_chs.h"
#include "bc_cli_priv.h"
#include "bc_cli_term.h"
#include "bc_cli_vio.h"



#define CLI_ACC_MAX_NAMELEN 32

#define CLI_ACC_TIME_LENGTH 20 /* yyyy-mm-dd hh:mm:ss */


#if 1
/* page actions when print */
typedef enum etag_cli_page_action
{
    CLI_PAGE_EXIT     = -3,    /* quit display */
    CLI_PAGE_TIMEOUT  = -2,    /* timeout */
    CLI_PAGE_DISABLE  = -1,    /* disable page stop function */
    CLI_PAGE_NOACTION = 0,     /* print all buffer without any action */
    CLI_PAGE_UP,               /* scroll output data scroll to previous one page  */
    CLI_PAGE_DOWN,             /* scroll output data scroll to next one page */
    CLI_PAGE_REFRESH,          /* refresh this pages data */
    CLI_PAGE_NEXTLINE,         /* scroll output data scroll to next one page line */
    CLI_PAGE_ALL,              /* display all data without stop */
    CLI_PAGE_NOTIFY
} cli_page_act_e;        
#endif

#if 0
typedef enum
{
    CLI_ACC_BASIC_LEVEL            = 1, /* 基础 */
    CLI_ACC_PRIVILEGED_LEVEL       = 2, /* 特权 */
    CLI_ACC_USER_LEVEL             = 3, /* 用户 */
    CLI_ACC_PUSER_LEVEL            = 8,
    CLI_ACC_OPERATOR_LEVEL         = 12,
    CLI_ACC_ADVANCED_LEVEL         = CLI_ACC_OPERATOR_LEVEL,
    CLI_ACC_ADMIN_LEVEL            = 15,
    CLI_ACC_FACTORY_LEVEL          = 20,   /* used for manufactory */
    CLI_ACC_RD_LEVEL               = 128 	/* used for RD */
} CLI_ACC_LEVEL_T;
#endif

/* struct used for position a cursor in terminal */
typedef struct
{
    UI16_T              line; 		/* current line. numbered from 0 - (terminal_line - 1) */
    UI16_T              column; 	/* current column in a line. numbered from 0 - (terminal_column - 1) */
    UI16_T              max_line; 	/* max line in a page */
    UI16_T              max_column; /* max column in a page */
    cli_page_act_e    	page_action;
    UI32_T              refresh_action;
} CLI_ACC_CURSOR_STATUS_T;

typedef struct stag_cli_accounts_information_t
{
    BOOL_T                      script_mode;        /* TRUE -- user commad is from script, FALSE -- user command is from shell */
    BOOL_T                      help_local;         /* TRUE -- use local help message, FALSE -- use English help */
    UI32_T                      ipaddr;             /* ipaddr of the access terminal */
    LA3_IP6ADDR                 ipv6addr;
    BOOL_T                      is_ipv6;
    UI8_T                       level;              /* level of the current access user */
    BOOL_T                      page_stop;          /* TRUE - CLI_API_Printf will wait for command after a page printed. */
    CLI_ACC_CURSOR_STATUS_T    cursor_status;      /* the cursor status of the session */
    DEV_RTC_TIME_T              login_time;         /* login time of the session, (实时时钟, Real-Time Clock, RTC) */
    UI32_T                      login_systemTime;   /* login system time, (the number of milliseconds that have elapsed since system was started) */
    I8_T                        login_name[CLI_ACC_MAX_NAMELEN + 1]; /* login name of the session */
    I32_T                       usermethod;         /* now just for RADIUS ACCOUNT used */
} CLI_ACC_INFO_T;

#define  VT_IO_SSH         3
#define  VT_IO_CLI	       2
#define  VT_IO_TELNET      1
#define  VT_IO_LOCAL       0
#define  VT_IO_QUIT       -1

typedef enum
{
    CLI_SESN_TYPE_CONSOLE       = VT_IO_LOCAL,
    CLI_SESN_TYPE_TELNET        = VT_IO_TELNET,
    CLI_SESN_TYPE_SSH           = VT_IO_SSH,
    CLI_SESN_TYPE_PSEUDO        = 100,
    CLI_SESN_TYPE_NONE          = -100,
} cli_sesn_type_t;

typedef struct stag_cli_session_t
{
    struct stag_cli_session_t  	*prev;
    struct stag_cli_session_t  	*next;

    I32_T                   map_sessionID;      //map to old sessionID in CLIG1 for other module use
    I8_T                    cmd[CLI_API_MAX_CMD_LEN + 1];  // command string
    CLI_CHARSET_T          	charset;
    I32_T                   previous_ch;		// previous input character
    I32_T                   err_pos;            // error position for command executed
    I32_T                   timeout;            // timeout second
    BOOL_T                  quit_flag;			// Indicate whether to exit the command line
    I32_T                   quit_reason;        // indicate the quit reason, value which in bc_cli_vkey.h
    cli_sesn_type_t     	session_type;
    HANDLE_T                hvio;               // handle for virtual IO
    HANDLE_T                hedit;              // handle for edit in the session
    HANDLE_T                hhist;              // handle of the history
    HANDLE_T                hfilter;            // filter of the CLI_API_Printf
    HANDLE_T                lock;               // lock of CLI session
    HANDLE_T                hdir;               // handle for directory in the session
    void                    *session_data;      // public data between CLI user commands
    CLI_PRIV_HELPLIST_T    helplist;
    CLI_ACC_INFO_T         acc_info;
} cli_sesn_t;



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
 *   None
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
cli_sesn_type_t cli_sesn_get_type(IN I32_T session_id);

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
cli_sesn_t * cli_sesn_get_by_sid(IN I32_T map_sessionID);

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
CLI_ACC_INFO_T * cli_api_get_hacc_from_session(IN I32_T session_id);

BOOL_T CLI_API_CreateSessionSem(void);
void CLI_API_DestroySessionSem(void);
	
/**************************************************************************
FUNCTION NAME:
	CLI_API_Check_Session

DESCRIPTION:
	Check if the input session ID is valid.

INPUT:
	sessionID	: created session ID by CLI kernel

OUTPUT:
	None

RETURN:
	TRUE		: the session ID is valid can be used
	FALSE		: the session ID is invalid

NOTES:

HISTORY:

**************************************************************************/
BOOL_T				CLI_API_Check_Session(IN I32_T sessionID);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_API_GetHaccFromSession
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
HANDLE_T            CLI_API_GetHvioFromSession(IN I32_T session_id);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_API_GetSessionData
 *
 * DESCRIPTION:
 *   get the session data
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
void                *CLI_API_GetSessionData(IN I32_T session_id);

/**************************************************************************
FUNCTION NAME:
    CLI_API_CreateSession

DESCRIPTION:
    Create a session struct of CLI kernel.

INPUT:
    map_sessionID   : mapped session ID for other modules used
    session_type        : session type (CONSOLE, SSH, TELNET)
    hterm           : the terminal IO struct
    vio_type            : type of the terminal, such as VT100, LINUX, etc.
                      Now we only support for VT100
    ip_info         : IP address information (include IPv4 && IPv6)
    session_data        : only used as the return value of CLI_API_GetSessionData

OUTPUT:
    None

RETURN:
    -1              : fail to create session
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
    );

/**************************************************************************
FUNCTION NAME:
    CLI_API_DestroySession

DESCRIPTION:
    Destroy the session struct of CLI kernel (release the resource).

INPUT:
    map_sessionID   : mapped session ID for other modules used

OUTPUT:
    None

RETURN:

NOTES:

HISTORY:

**************************************************************************/
void                CLI_API_DestroySession(IN I32_T map_sessionID);


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
I32_T                       CLI_ACC_GetFirstInfo(OUT CLI_ACC_INFO_T *buf);

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
I32_T                       CLI_ACC_GetNextInfo(IN I32_T hcur_session, OUT CLI_ACC_INFO_T *buf);

void cli_sesn_wait(void);
void cli_sesn_post(void);



#endif /* __BC_CLI_SESN__ */

