/*******************************************************************

COPYRIGHT:
	Copyright (c) 2005-2011  Kingtype Corporation   All rights reserved.
    This is unpublished proprietary source code of Kingtype Corporation.
	The copyright notice above does not evidence any actual or intended
	publication of such source code.

MODULE NAME:
	BC_CLI

FILE NAME:
 	bc_cli_hook.h

VERSION:
	1.00

DESCRIPTION:
 	The hook function for BC_CLI kernel.

NOTES:
    NA

HISTORY:
	Ver1.00:	2011.6.2 wangbin new added

********************************************************************/

#ifndef __BC_CLI_HOOK_H__
#define __BC_CLI_HOOK_H__

////////////////////////////////////////////////////////////////////////////////
// 								    										  //
// 							    头   文   件								  //
// 										    								  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_cli_type.h"
#include "bc_modules.h"


////////////////////////////////////////////////////////////////////////////////
//																			  //
//						结   构   体   宏   定   义							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#define CLI_HOOK_CMD_EXECUTE_MAXNUM	8

/**************************************************************************
FUNCTION NAME:
	CLI_NOTIFY_MSG_CALLBACK_T

DESCRIPTION:
	Type of the callback function for show message when CLI kernel executing.

INPUT:
	session		: session ID for other module used
	cookie		: cookie (define by callback function)

OUTPUT:
	NA

RETURN:
	TRUE		: have some message print, CLI will refresh input command.
	FALSE		: no message print, CLI will not refresh input command.

NOTES:

HISTORY:

**************************************************************************/
typedef BOOL_T (*CLI_NOTIFY_MSG_CALLBACK_T)(IN UI32_T session, IN void *cookie);

/**************************************************************************
FUNCTION NAME:
	CLI_CMD_EXECUTE_CALLBACK_T

DESCRIPTION:
	Type of the callback function.
	Will be called before execute command and after execute command.

INPUT:
	session				: session ID for other module used
	cmd_ptr				: input command string pointer
	before_execute_cmd	: the period for execute the callback function
						  TRUE->before execute command
						  FALSE->after execute command
	ret_execute_cmd		: if after execute command, the value record the executed result
	pre_state			: previous state of execute the callback function
	cookie				: cookie (define by callback function)

OUTPUT:
	NA

RETURN:
	I32_T -> current execute state

NOTES:

HISTORY:

**************************************************************************/
typedef I32_T (*CLI_CMD_EXECUTE_CALLBACK_T)
	(
	IN UI32_T 	session, 
	IN I8_T 	*cmd_ptr,
	IN BOOL_T 	before_execute_cmd,
	IN I32_T 	ret_execute_cmd,
	IN I32_T 	pre_state,
	IN void 	*cookie
	);



////////////////////////////////////////////////////////////////////////////////
//																			  //
//								函	数	声	明								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

/**************************************************************************
FUNCTION NAME:
	CLI_HOOK_Register_NotifyMsg

DESCRIPTION:
	Register callback function for show notify message by input module ID.

INPUT:
	moduleID		: module ID
	callbackFunc	: callback function for show notify message
	callbackCookie	: the cookie defined by callback function

OUTPUT:
	NA

RETURN:
	NA

NOTES:
	If there is registered callback function for input module ID, it will
	 be replaced by input callback function

HISTORY:

**************************************************************************/
void CLI_HOOK_Register_NotifyMsg(
	IN bc_modules_e moduleID, 
	IN CLI_NOTIFY_MSG_CALLBACK_T callbackFunc,
	IN void *callbackCookie);

/**************************************************************************
FUNCTION NAME:
	CLI_HOOK_Deregister_NotifyMsg

DESCRIPTION:
	Deregister callback function for show notify message by input module ID.

INPUT:
	moduleID		: module ID

OUTPUT:
	NA

RETURN:
	NA

NOTES:

HISTORY:

**************************************************************************/
void CLI_HOOK_Deregister_NotifyMsg(IN bc_modules_e moduleID);

/**************************************************************************
FUNCTION NAME:
	CLI_HOOK_Get_NotifyMsg

DESCRIPTION:
	Get callback function for show notify message by input module ID.

INPUT:
	moduleID		: module ID

OUTPUT:
	callbackFunc	: callback function for show notify message
	callbackCookie	: the cookie defined by callback function

RETURN:
	NA

NOTES:

HISTORY:

**************************************************************************/
void CLI_HOOK_Get_NotifyMsg
	(
	IN bc_modules_e 					moduleID,
	OUT CLI_NOTIFY_MSG_CALLBACK_T 	*callbackFunc,
	OUT void 						**callbackCookie
	);

/**************************************************************************
FUNCTION NAME:
	CLI_HOOK_Register_CmdExecute_CallbackFunc

DESCRIPTION:
	Register callback function.
	It will be called before execute command and after execute command.

INPUT:
	callbackFunc	: callback function
	callbackCookie	: the cookie defined by callback function

OUTPUT:
	TRUE			: register success
	FALSE			: the registered number is max

RETURN:
	NA

NOTES:
	If there is registered callback function, it will be replaced 
	by input callback function

HISTORY:

**************************************************************************/
BOOL_T CLI_HOOK_Register_CmdExecute_CallbackFunc
	(
	IN CLI_CMD_EXECUTE_CALLBACK_T 	callbackFunc,
	IN void 						*callbackCookie
	);

/**************************************************************************
FUNCTION NAME:
	CLI_HOOK_Deregister_CmdExecute_CallbackFunc

DESCRIPTION:
	Deregister callback function which will be called before execute command 
	and after execute command.

INPUT:
	callbackFunc	: callback function

OUTPUT:
	NA

RETURN:
	TRUE			: deregister success
	FALSE			: the callback function is not exist

NOTES:

HISTORY:

**************************************************************************/
BOOL_T CLI_HOOK_Deregister_CmdExecute_CallbackFunc(
	IN CLI_CMD_EXECUTE_CALLBACK_T callbackFunc);

/**************************************************************************
FUNCTION NAME:
	CLI_HOOK_Get_NextCmdExecute_CallbackFunc

DESCRIPTION:
	Get next callback function for input callback function.

INPUT:
	callbackFunc	: current callback function

OUTPUT:
	callbackFunc	: next callback function
	callbackCookie	: the cookie defined by callback function

RETURN:
	TRUE			: get success
	FALSE			: at the end or input callback function not find

NOTES:
	If input callback function is null, will get the first callback function.

HISTORY:

**************************************************************************/
BOOL_T CLI_HOOK_Get_NextCmdExecute_CallbackFunc(
	IN OUT CLI_CMD_EXECUTE_CALLBACK_T *callbackFunc,
	OUT void **callbackCookie);



#endif /* __BC_CLI_HOOK_H__ */

