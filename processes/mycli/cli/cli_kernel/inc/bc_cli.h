/*******************************************************************************
  -------------------------------------------------------------------------
  [File name]  : \\BC\cli\bc_cli.h
  [Author]     : bain.wang@outlook.com
  [Version]    : 1.0
  [Date]       : 2016-04-21
  [Description]:

  [Others]     :

  [Function List]:
	1. ....
	2. ....
  [History]:
	 D a t e	Modification										  Initials
	---------- --------------										 ----------
	2016-04-21	Created 											  bain.wang@outlook.com
*******************************************************************************/

#ifndef __INC_BC_CLI_H__
#define __INC_BC_CLI_H__

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								头   文   件								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_print.h"

#include "bc_cli_type.h"
#include "bc_cli_paratype.h"
#include "bc_cli_sesn.h"
#include "bc_cli_misc.h"


////////////////////////////////////////////////////////////////////////////////
//																			  //
//								宏   定   义								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

/* 监控模式 */
#define CLI_MOD_MONITOR_PATH        "/"

/* 特权模式 */
#define CLI_MOD_PRIVI_PATH  		"/ena"
#define CLI_MOD_PRIVI_PROM 			"(pri)"

/* 全局配置模式 */
#define CLI_MOD_GLBCFG_PATH  		"/cfg"
#define CLI_MOD_GLBCFG_PROM 		"(config)"

/* 端口配置模式 */
#define CLI_MOD_VLAN_INTERFACE_PATH  	"/if-vlan"
#define CLI_MOD_VLAN_INTERFACE_PROM 	"(config-if-vlan-interface-"

/* onu配置模式 */
#define CLI_MOD_ONU_PATH  	            "/onu"
#define CLI_MOD_ONU_PROM 	            "(config-if-onu)"

/* onu模板模式 */
#define CLI_MOD_PROFILE_PATH  	            "/profile"
#define CLI_MOD_PROFILE_PROM 	            "(config-if-profile)"

/* 调试模式 */
#define CLI_MOD_DEBUG_PATH  		"/dbg"
#define CLI_MOD_DEBUG_PROM 			"(dbg)"

/* 布尔康调试命令 */
#define CLI_MOD_DEBUG_BCM_PATH "/bcm"
#define CLI_MOD_DEBUG_BCM_PROM "(bcm)"

/* 全局模式，一个虚拟模式，供类似于show这种能在所有模式下运行的命令注册的模式 */
#define CLI_MOD_GLOBAL_PATH        	"/glb"



////////////////////////////////////////////////////////////////////////////////
//																			  //
//					结 构 体 、联 合 体、枚 举 定 义						  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#define L3_TN_MAX_CONNECT_NUMBER    (8)        	/* the number of users use the server current 1~8 */
#define SSH_OPT_MAX_CONNECTIONS		(8)			/* maximum connections supported in server */

/* define CLI session ID and range */
typedef enum etag_vt_channel_type
{
	VT_TNBEGIN_CHANNEL = 0,
	VT_RS232_CHANNEL=VT_TNBEGIN_CHANNEL + L3_TN_MAX_CONNECT_NUMBER,	/* 8 */
	VT_SSHBEGIN_CHANNEL,
	VT_WINSIM_CHANNEL=VT_SSHBEGIN_CHANNEL+SSH_OPT_MAX_CONNECTIONS,
	VT_PSEUDO_CHANNEL,
	VT_WEB_CHANNEL,
	VT_SNMP_CHANNEL,
	VT_DEBUG_BUF_CHANNEL,
	VT_TS_BUF_CHANNEL,
	VT_SECURITY_CHANNEL,
#if MANAGEMENT_PORT_INCLUDED
	VT_MGMT_TN_CHANNEL,
	VT_MGMT_SSH_CHANNEL,
#endif
	VT_MAX_IO_CHANNEL,
	VT_CHANNEL_LAST /* for count channel*/
} cli_chn_e;
#define VT_BROCAST_CHANNEL 255

/* return value list of CLI command callback */
typedef enum etag_cli_command_return_value_type
{
    CLI_CMD_FAIL_PRT_NONE              = -100,    /* execute failure, print nothing */
    CLI_CMD_SUCCESS_PRT_NONE           = -99,     /* execute success, print nothing */

    CLI_CMD_FAIL_PRT_NEWLINE           = -1,      /* execute failure, print "\r\n" */
    CLI_CMD_SUCCESS_PRT_NEWLINE        = 0,       /* execute success, print "\r\n" */

    CLI_CMD_SUCCESS_PRT_PROMPT,                   /* execute success, print "success" */
    CLI_CMD_FAIL_PRT_PROMPT,                      /* execute failure, print "failure" */

    CLI_CMD_SUCCESS_PRT_PROMPT_NEWLINE = 5,       /* execute success, print "success and \r\n" */
    CLI_CMD_FAIL_PRT_PROMPT_NEWLINE    = 6,       /* execute failure, print "failure and \r\n" */

    CLI_CMD_QUIT_SESSION,
} cli_cmd_ret_e;

typedef enum etag_cli_account_level_type
{
    CLI_ACC_LVL_BASIC = 1,
    CLI_ACC_LVL_PRIVI,
    CLI_ACC_LVL_USER,
    CLI_ACC_LVL_PUSER,
    CLI_ACC_LVL_ADMIN,
    CLI_ACC_LVL_FACTORY,
    CLI_ACC_LVL_DEBUG = 128
} cli_acc_lvl_e;

typedef enum etag_cli_kp_close_event_type
{
    CLI_KP_TIMEOUT  = 1,
    CLI_KP_LOGOUT,
    CLI_KP_FORCE
} CLI_KP_ClOSE_EVENT_T;

#define CLI_API_RET_IO_CLOSED 			(-1)
#define CLI_API_RET_TIMEOUT 			(-1282)
#define CLI_API_RET_NOACTION 			(-1283)
#define CLI_API_RET_EXIT_CMD 			(-1284)
#define CLI_API_RET_WRONGVALUE 			(-5)
#define CLI_API_RET_QUIT_SESSION 		(-100)
#define CLI_API_RET_SUCCESS 			(1)

#if 0
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

typedef struct stag_cli_user_information_type
{
    I32_T           sessionID;
    UI32_T          loginTime;
    UI8_T           ip6Flag;                /*0 is IPv4, other is IPv6*/
    UI32_T          ipAddress;
    UI8_T           ip6Address[16];
    UI32_T          level;
    I8_T            name[BNR_CPU_NAME_MAX_LEN + 1];
} cli_usr_info_t;

typedef enum etag_cli_come_from_type
{
    CLI_COME_FROM_UNKNOWN       = 1,
    CLI_COME_FROM_CONSOLE,
    CLI_COME_FROM_LOGON,
    CLI_COME_FROM_TELNET,
    CLI_COME_FROM_SSH
} cli_come_from_e;

#define CLI_IO_WEB        8
#define CLI_IO_WINTEST    5
#define CLI_IO_DEBUG      4
#define CLI_IO_SSH        CON_IO_SSH
#define CLI_IO_CLI        VT_IO_CLI
#define CLI_IO_TELNET     CON_IO_TELNET
#define CLI_IO_LOCAL      CON_IO_LOCAL
#define CLI_IO_QUIT       VT_IO_QUIT

#define CLI_BAT_Check_Playback(session_id)		FALSE



////////////////////////////////////////////////////////////////////////////////
//																			  //
//						外 部 变 量、 函 数 声 明							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_API_SetNoEditingLen
 *
 * DESCRIPTION:
 *   Set chars that can not be edited from the start of the line.
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
void                CLI_API_SetNoEditingLen(IN I32_T session_id, IN UI32_T len);


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
    );

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
	IN I8_T *mode_desc);

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
BOOL_T 				bc_cli_reg_cmd
	(
	I8_T 			*cmd_desc, 		/* the pointer of command string pointer */
    CLI_CMD_FUNC_T callbackFunc, 	/* the command's callback function */
    I32_T 			flag, 			/* the access level and flag of command (low 8bits is the level) */
    I8_T 			*help_en, 		/* englist help message */
    I8_T 			*help_local, 	/* chinese help message */
    void 			*user_data  	/* user data as a cookie */
    );

/*****************************************************************************
FUNCTION NAME:
    bc_cli_dereg_cmd

DESCRIPTION:
    deregister a command:
        1. find the command and its path
        2. free the parameter and information
        3. destory the command and its path (update the path's level also)

INPUT:
    cmd_desc    : the pointer of command string pointer

OUTPUT:

RETURN:
    TRUE        : success
    FALSE       : command not exist

NOTES:

HISTORY:

*******************************************************************************/
BOOL_T              bc_cli_dereg_cmd(IN I8_T *cmd_desc);

/**************************************************************************
FUNCTION NAME:
    CLI_API_Display_FirstNode_UnderInputPath

DESCRIPTION:
    Display first word of commands under this directory.

INPUT:
    session_id  : created session ID by CLI kernel
    path_string : path string(such as: /config)
    level           : current user level

OUTPUT:
    None

RETURN:
    None

NOTES:

HISTORY:
    Creat by bain.wang@outlook.com 2011.3.2

**************************************************************************/
void                        CLI_API_Display_FirstNode_UnderInputPath(IN I32_T session_id, IN I8_T *path_string,
                                                                      IN UI8_T level);

/**************************************************************************
FUNCTION NAME:
    CLI_API_Display_Cmd_UnderInputPath

DESCRIPTION:
    Display commands under input directory.

INPUT:
    session_id  : created session ID by CLI kernel
    path_string : path string(such as: /config)
    level           : current user level

OUTPUT:
    None

RETURN:
    None

NOTES:

HISTORY:
    Creat by bain.wang@outlook.com 2011.3.2

**************************************************************************/
void                        CLI_API_Display_Cmd_UnderInputPath(IN I32_T session_id, IN I8_T *path_string,
                                                                IN UI8_T level);

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
    ptrPathValue: current path's information get from input CLI parameter value

OUTPUT:
    None

RETURN:
    TRUE        : Enter and set path success.
    FALSE       : Enter or set path fail.

NOTES:

HISTORY:
    Creat by bain.wang@outlook.com 2011.3.2

**************************************************************************/
BOOL_T bc_cli_set_cmdpath(IN I32_T sessionID, IN I8_T *path, IN I8_T *path_prompt,
                                                     IN cli_value_t *path_param);

/**************************************************************************
FUNCTION NAME:
    bc_cli_get_cmdpath

DESCRIPTION:
    Get the CLI command executing path.

INPUT:
    sessionID   : created session ID by CLI kernel

OUTPUT:
    None

RETURN:
    current path

NOTES:

HISTORY:
    Creat by bain.wang@outlook.com 2011.3.2

**************************************************************************/
I8_T                        *bc_cli_get_cmdpath(IN I32_T sessionID);

/**************************************************************************
FUNCTION NAME:
    bc_cli_get_path_parameter

DESCRIPTION:
    Get the path's information.

INPUT:
    sessionID   : created session ID by CLI kernel

OUTPUT:
    None

RETURN:
    cli_value_t : the path's information for example
    path: /path1/path2/path3
        enter path1 use command: [root] enter path1 <parameter1>
        enter path2 use command: [path1] enter path2
        enter path3 use command: [path2] enter path3 <parameter3>
        -> after enter path3, the cli_value_t path's information is: <parameter1>-><parameter3>
NOTES:

HISTORY:
    Creat by bain.wang@outlook.com 2011.3.2

**************************************************************************/
cli_value_t                *bc_cli_get_path_parameter(IN I32_T sessionID);

/**************************************************************************
FUNCTION NAME:
    bc_cli_exit_curpath

DESCRIPTION:
    Exit currnt path and return to prev-path.
    If current path is EXEC(root path), return FALSE.

INPUT:
    sessionID   : created session ID by CLI kernel

OUTPUT:
    None

RETURN:
    TRUE        : exit success
    FALSE       : current path is EXEC(root path)

NOTES:

HISTORY:
    Creat by bain.wang@outlook.com 2011.3.7

**************************************************************************/
BOOL_T                      bc_cli_exit_curpath(IN I32_T sessionID);


/*------------------------------------------------------------------------
 * Function:    bc_cli_close_sesn
 * Purpose:     close session
 * Parameters:
 *    Input:    sessionID = session identifier
 *    Output:   NA
 * Returns:     NA
 *------------------------------------------------------------------------
 */
void            bc_cli_close_sesn
    (
    const int  sessionID,
    CLI_KP_ClOSE_EVENT_T event
    );

/*------------------------------------------------------------------------
 * Function:    bc_cli_set_usr_lvl
 * Purpose:     set user level
 * Parameters:
 *    Input:    session_id = session identifier
 *              level      = user level
 *    Output:   NA
 * Returns:     TRUE       = is access
 *------------------------------------------------------------------------
 */
BOOL_T          bc_cli_set_usr_lvl
    (
    const int    session_id,
    const UI32_T level
    );

/*------------------------------------------------------------------------
 * Function:    bc_cli_get_usr_lvl
 * Purpose:     check the node is access
 * Parameters:
 *    Input:    session_id = session identifier
 *    Output:   NA
 * Returns:     user level
 *
 *------------------------------------------------------------------------
 */
UI32_T          bc_cli_get_usr_lvl
    (
    const int     session_id
    );

/*------------------------------------------------------------------------
 * Function:    bc_cli_get_usr_info
 * Purpose:     get usr info in CLI DB
 * Parameters:
 *    Input:    pEntry = point to output struct
 *    Output:   *pEntry = the user infomation
 * Returns:     TRUE : is access, FALSE : failure
 *------------------------------------------------------------------------
 */
BOOL_T          bc_cli_get_usr_info
    (
    cli_usr_info_t *pEntry
    );


/*------------------------------------------------------------------------
 * Function:    bc_cli_get_usr_name
 * Purpose:     get user name
 * Parameters:
 *    Input:    sessionID = session identifier
 *    Output:   name = user name
 * Returns:     TRUE = success
 *              FALSE = failure
 *------------------------------------------------------------------------
 */
BOOL_T          bc_cli_get_usr_name
    (
    const int   sessionID,
    I8_T *name
    );


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
BOOL_T              bc_cli_clear_screen(IN I32_T session_id);


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
        const int sessionID,
        UI32_T    timoutSec) ;

/**************************************************************************
FUNCTION NAME:
    CLI_BNR_Trans_AccLevel_To_String

DESCRIPTION:
    Translate user account access level to string.

INPUT:
    acclevel        : the value of user account access level

OUTPUT:
    level_string    : the pointer of buffer used to store string

RETURN:
    the size of translated string

NOTES:
    Added for displaying access level in string.

HISTORY:
    Added by bain.wang@outlook.com 2009.11.6

**************************************************************************/
UI32_T          CLI_BNR_Trans_AccLevel_To_String
    (
    OUT I8_T *level_string,
    IN I32_T acclevel
    );



/**************************************************************************
FUNCTION NAME:
    bc_cli_set_hist_size

DESCRIPTION:
    Set the history command size of CLI module

INPUT:
    sessionID   : the mapped session ID
    size            : history command size

OUTPUT:
    None

RETURN:
    TRUE    : set success
    FALSE   : the terminal IO in the session is null

NOTES:

HISTORY:

**************************************************************************/
BOOL_T                      bc_cli_set_hist_size(IN I32_T sessionID, IN UI32_T size);

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
 *  start -- TRUE(return the first item in the history buffer)
 *           FALSE (return the next item in the history buffer) *
 *
 * OUTPUT:
 *   None
 *
 * RETURN:
 *   not NULL -- the pointer of the history buffer, NULL -- There is no more
 *               item in the history buffer, the operation may be stopped
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
I8_T                *bc_cli_show_all_hist(IN I32_T session_id, IN BOOL_T start);

/**************************************************************************
FUNCTION NAME:
    bc_cli_set_paging

DESCRIPTION:
    Set global cli paging state.

INPUT:
    paging_state    : global paging state(TRUE: enable, FALSE: disable)

OUTPUT:
    None

RETURN:
    None

NOTES:

HISTORY:

**************************************************************************/
void                        bc_cli_set_paging(IN BOOL_T paging_state);

/**************************************************************************
FUNCTION NAME:
    bc_cli_get_paging

DESCRIPTION:
    Get global cli paging state.

INPUT:
    None

OUTPUT:
    None

RETURN:
    global cli paging state

NOTES:

HISTORY:

**************************************************************************/
BOOL_T                      bc_cli_get_paging(void);

extern void bc_cli_prt_puts(bc_char *buf, bc_uint32 len);

#define bc_cli_print(module_id, fmt, ...) \
	do \
	{ \
		bc_char *__0812_cli_private_buf = NULL; \
		__0812_cli_private_buf = bc_cli_misc_alloc(); \
		if (module_id){} \
		memset(__0812_cli_private_buf, 0x00, 10240); \
		snprintf(__0812_cli_private_buf, 10240, fmt, ##__VA_ARGS__); \
		bc_cli_prt_puts(__0812_cli_private_buf, strlen(__0812_cli_private_buf)); \
		bc_cli_misc_free(__0812_cli_private_buf); \
	} while (0)


#define BC_PT_COMMAND(module_id, fmt, ...)	\
	do \
	{ \
		bc_char *__0812_cli_private_buf = NULL; \
		__0812_cli_private_buf = bc_cli_misc_alloc(); \
		if (module_id){} \
		memset(__0812_cli_private_buf, 0x00, 10240); \
		snprintf(__0812_cli_private_buf, 10240, fmt, ##__VA_ARGS__); \
		bc_cli_prt_puts(__0812_cli_private_buf, strlen(__0812_cli_private_buf)); \
		BC_WRITE_LOG_FUN(BC_LOG_BIT_COMMAND, module_id, __FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__); \
		bc_cli_misc_free(__0812_cli_private_buf); \
	} while (0)


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
 *   cli_lan_t
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2016-05-26 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
cli_lan_t bc_cli_get_lan(void);

#define bc_cli_msg_get(msg_id) bc_msg_get((msg_id), bc_cli_get_lan())
#define bc_cli_err_msg_get(err_id) bc_msg_err_get((err_id), bc_cli_get_lan())

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
BOOL_T bc_cli_set_lan(IN I32_T session_id, IN BOOL_T help_local);

/**************************************************************************
FUNCTION NAME:
    bc_cli_get_prompt

DESCRIPTION:
    Get the command prompt message

INPUT:
    session_id  : the mapped session ID

OUTPUT:
    msg_buf      : prompt message

RETURN:
    TRUE        : get success
    FALSE       : the terminal IO in the session is null

NOTES:

HISTORY:

**************************************************************************/
BOOL_T bc_cli_get_prompt(IN I32_T session_id, OUT I8_T *msg_buf);



#if 1
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
void bc_cli_timeout_init(void);



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
void bc_cli_set_timeout(UI32_T time);



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
UI32_T bc_cli_get_timeout(void);



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
void bc_cli_logout(I32_T sid);

#endif


#endif /* __INC_BC_CLI_H__ */


