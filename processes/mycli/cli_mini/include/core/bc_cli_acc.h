#ifndef __BC_CLI_ACC_H__
#define __BC_CLI_ACC_H__

#include "bc_cli_sesn.h"

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_ACC_GetAllInfo
 *
 * DESCRIPTION:
 *   Get all access information
 *
 * INPUT:
 *   session_id -- session ID
 *
 * OUTPUT:
 *   buf -- access information
 *
 * RETURN:
 *   NA
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2009-Mar-19 by wangbin -- Create
 *
*******************************************************************************/
void                        CLI_ACC_GetAllInfo(IN I32_T session_id, OUT CLI_ACC_INFO_T *buf);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_ACC_GetCursorStatus
 *
 * DESCRIPTION:
 *   Get cursor position in a terminal
 *
 * INPUT:
 *   session_id -- session ID
 *
 * OUTPUT:
 *   cursor_pos -- position of the cursor in session
 *
 * RETURN:
 *   NA
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2009-Mar-19 by wangbin -- Create
 *
*******************************************************************************/
void                        CLI_ACC_GetCursorStatus(IN I32_T session_id, OUT CLI_ACC_CURSOR_STATUS_T *cursor_status);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   cli_acc_get_lan
 *
 * DESCRIPTION:
 *   Get help language
 *
 * INPUT:
 *   session_id -- session ID
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   TRUE -- Use local language
 *   FALSE -- Use English
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2009-Mar-19 by wangbin -- Create
 *
*******************************************************************************/
BOOL_T                      cli_acc_get_lan(IN I32_T session_id);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_ACC_GetIPAddr
 *
 * DESCRIPTION:
 *   Get IP address
 *
 * INPUT:
 *   session_id -- session ID
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   IP adress
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2009-Mar-19 by wangbin -- Create
 *
*******************************************************************************/
UI32_T                      CLI_ACC_GetIPAddr(IN I32_T session_id);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_ACC_GetIPAddr
 *
 * DESCRIPTION:
 *   Get IPv6 address
 *
 * INPUT:
 *   session_id -- session ID
 *
 * OUTPUT:
 *   ipv6addr -- ipv6 address
 *
 * RETURN:
 *   TRUE/FALSE
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *
*******************************************************************************/
BOOL_T                      CLI_ACC_GetIPv6Addr(IN I32_T session_id, OUT LA3_IP6ADDR *ipv6addr);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   cli_acc_get_lvl
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
UI32_T                      cli_acc_get_lvl(IN I32_T session_id);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_ACC_GetLoginName
 *
 * DESCRIPTION:
 *   Get the login name
 *
 * INPUT:
 *   session_id -- session ID
 *
 * OUTPUT:
 *   login_name -- login name of the access
 *
 * RETURN:
 *   NA
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2009-Mar-19 by wangbin -- Create
 *
*******************************************************************************/
void                        CLI_ACC_GetLoginName(IN I32_T session_id, OUT I8_T login_name[CLI_ACC_MAX_NAMELEN + 1]);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_ACC_GetLoginTime
 *
 * DESCRIPTION:
 *   Get the login time
 *
 * INPUT:
 *   session_id -- session ID
 *
 * OUTPUT:
 *   login_time -- login time of the access
 *
 * RETURN:
 *   NA
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2009-Mar-19 by wangbin -- Create
 *
*******************************************************************************/
void                        CLI_ACC_GetLoginTime(IN I32_T session_id, OUT DEV_RTC_TIME_T *login_time);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_ACC_GetPageStopStatus
 *
 * DESCRIPTION:
 *   Get page stop status
 *
 * INPUT:
 *   session_id -- session ID
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   page stop status
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2009-Mar-19 by wangbin -- Create
 *
*******************************************************************************/
BOOL_T                      CLI_ACC_GetPageStopStatus(IN I32_T session_id);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_ACC_GetScriptMode
 *
 * DESCRIPTION:
 *   Get script mode status
 *
 * INPUT:
 *   session_id -- session ID
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   Script Mode status.
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2009-Mar-19 by wangbin -- Create
 *
*******************************************************************************/
BOOL_T                      CLI_ACC_GetScriptMode(IN I32_T session_id);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_ACC_SetCursorStatus
 *
 * DESCRIPTION:
 *   Set cursor status in a page
 *
 * INPUT:
 *   session_id -- session ID
 *   status -- the status of the cursor
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
 *   2009-Mar-19 by wangbin -- Create
 *
*******************************************************************************/
void                        CLI_ACC_SetCursorStatus(IN I32_T session_id, IN CLI_ACC_CURSOR_STATUS_T *status);


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
 *   help_local --  // TRUE -- use local help message, FALSE -- use English help
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   BOOL_T
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2009-Mar-19 by wangbin -- Create
 *
*******************************************************************************/
BOOL_T cli_acc_set_lan(IN I32_T session_id, IN BOOL_T help_local);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_ACC_SetIPAddr
 *
 * DESCRIPTION:
 *   Set IP address
 *
 * INPUT:
 *   session_id -- session ID
 *   ipaddr -- new IP address in unsigned int
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
 *   2009-Mar-19 by wangbin -- Create
 *
*******************************************************************************/
void                        CLI_ACC_SetIPAddr(IN I32_T session_id, IN UI32_T ipaddr);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_ACC_SetIPv6Addr
 *
 * DESCRIPTION:
 *   Set IPv6 address
 *
 * INPUT:
 *   session_id -- session ID
 *   ipv6addr -- IPv6 address
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
 *
*******************************************************************************/
void                        CLI_ACC_SetIPv6Addr(IN I32_T session_id, IN LA3_IP6ADDR *ipv6addr);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   cli_acc_set_lvl
 *
 * DESCRIPTION:
 *   Set level of the current access user
 *
 * INPUT:
 *   session_id -- session ID
 *   level -- new level
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
 *   2009-Mar-19 by wangbin -- Create
 *
*******************************************************************************/
void                        cli_acc_set_lvl(IN I32_T session_id, IN UI8_T level);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_ACC_SetLoginName
 *
 * DESCRIPTION:
 *   Set the login name
 *
 * INPUT:
 *   session_id -- session ID
 *   login_name -- login name
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
 *   2009-Mar-19 by wangbin -- Create
 *
*******************************************************************************/
void                        CLI_ACC_SetLoginName(IN I32_T session_id, IN I8_T login_name[CLI_ACC_MAX_NAMELEN + 1]);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_ACC_SetLoginTime
 *
 * DESCRIPTION:
 *   Set the login time
 *
 * INPUT:
 *   session_id -- session ID
 *   login_time -- login time
 *     login_systemTime -- login system time (millisecond)
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
 *   2009-Mar-19 by wangbin -- Create
 *
*******************************************************************************/
void                        CLI_ACC_SetLoginTime(IN I32_T session_id, IN DEV_RTC_TIME_T *login_time,
                                                  IN UI32_T login_systemTime);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_ACC_SetPageStopStatus
 *
 * DESCRIPTION:
 *   Set page stop status
 *
 * INPUT:
 *   session_id -- session ID
 *   page_stop -- TRUE -- stop output after one page
 *                FALSE -- not stop output after one page
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
 *   2009-Mar-19 by wangbin -- Create
 *
*******************************************************************************/
void                        CLI_ACC_SetPageStopStatus(IN I32_T session_id, IN BOOL_T page_stop);


/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_ACC_SetScriptMode
 *
 * DESCRIPTION:
 *   Set script mode status
 *
 * INPUT:
 *   session_id -- session ID
 *   script_mode -- TRUE: command is from script file
 *                  FALSE: command is from shell
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
 *   2009-Mar-19 by wangbin -- Create
 *
*******************************************************************************/
void                        CLI_ACC_SetScriptMode(IN I32_T session_id, IN BOOL_T script_mode);

/**************************************************************************
FUNCTION NAME:
    CLI_ACC_SetUserMethod

DESCRIPTION:
    Set account user method

INPUT:
    sessionID       : the mapped session ID
    usermethod      : now just for RADIUS ACCOUNT used

OUTPUT:
    None

RETURN:
    None

NOTES:

HISTORY:

**************************************************************************/
void                        CLI_ACC_SetUserMethod(IN I32_T sessionID, IN I32_T usermethod);



#endif /* __BC_CLI_ACC_H__ */

