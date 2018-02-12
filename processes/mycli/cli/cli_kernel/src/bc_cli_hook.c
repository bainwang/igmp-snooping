/*******************************************************************
MODULE NAME:
	BC_CLI

FILE NAME:
 	bc_cli_hook.c

VERSION:
	1.00

DESCRIPTION:
 	The hook function for BC_CLI kernel.

NOTES:
    NA

HISTORY:
	Ver1.00:	2011.6.2 bain.wang@outlook.com new added

********************************************************************/

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              头   文   件                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "bc_cli_hook.h"



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                      外 部 变 量、 函 数 引 用                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                      结   构   体   宏   定   义                           //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	CLI_NOTIFY_MSG_CALLBACK_T	cb_func;
	void 						*cb_ck; /* callback cookie, define by registered callback function */
} CLI_HOOK_NOTIFYMSG_T;

typedef struct
{
	CLI_CMD_EXECUTE_CALLBACK_T cb_func;
	void 						*cb_ck; /* callback cookie, define by registered callback function */
} CLI_HOOK_CMD_EXECUTE_T;



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                          全 局 变 量 定 义                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

static CLI_HOOK_NOTIFYMSG_T 	s_ntfmsg_cblist[(BC_LAST_MODULE - BC_FIRST_MODULE)/BC_MODULE_INTERVAL]; /* notify message callback list */
static CLI_HOOK_CMD_EXECUTE_T 	s_cmdexe_cblist[CLI_HOOK_CMD_EXECUTE_MAXNUM]; /* command execute callback list */



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              函  数  声  明                                //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              函  数  定  义                                //
//                                                                            //
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
	If there is registered callback function for input module ID, it will be replaced 
	by input callback function

HISTORY:

**************************************************************************/
void CLI_HOOK_Register_NotifyMsg
	(
	IN bc_modules_e 				moduleID, 
	IN CLI_NOTIFY_MSG_CALLBACK_T 	callbackFunc,
	IN void 						*callbackCookie
	)
{
	if ((moduleID > BC_FIRST_MODULE) && (moduleID < BC_LAST_MODULE))
	{
		s_ntfmsg_cblist[moduleID/BC_MODULE_INTERVAL].cb_func = callbackFunc;
		s_ntfmsg_cblist[moduleID/BC_MODULE_INTERVAL].cb_ck = callbackCookie;
	}
}



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
void CLI_HOOK_Deregister_NotifyMsg(IN bc_modules_e moduleID)
{
	if ((moduleID > BC_FIRST_MODULE) && (moduleID < BC_LAST_MODULE))
	{
		s_ntfmsg_cblist[moduleID/BC_MODULE_INTERVAL].cb_func = NULL;
		s_ntfmsg_cblist[moduleID/BC_MODULE_INTERVAL].cb_ck = NULL;
	}
}



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
	)
{
	if ((moduleID > BC_FIRST_MODULE) && (moduleID < BC_LAST_MODULE))
	{
		*callbackFunc = s_ntfmsg_cblist[moduleID/BC_MODULE_INTERVAL].cb_func;
		*callbackCookie = s_ntfmsg_cblist[moduleID/BC_MODULE_INTERVAL].cb_ck;
	}
	else
	{
		*callbackFunc = NULL;
		*callbackCookie = NULL;
	}
}



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
	)
{
	UI32_T position = 0;
	BOOL_T found_flag = FALSE;
	UI32_T i;

	for (i = 0; i < CLI_HOOK_CMD_EXECUTE_MAXNUM; i++)
	{
		/* 查找空闲位置 */
		if ((FALSE == found_flag) && (NULL == s_cmdexe_cblist[i].cb_func))
		{
			position = i;
			found_flag = TRUE;
		}

		/* 验证是否已经挂钩回调 */
		if (s_cmdexe_cblist[i].cb_func == callbackFunc)
		{
			s_cmdexe_cblist[i].cb_ck = callbackCookie;
			
			return TRUE;
		}
	}

	if (found_flag)
	{
		s_cmdexe_cblist[position].cb_func = callbackFunc;
		s_cmdexe_cblist[position].cb_ck = callbackCookie;
	}

	return found_flag;
}



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
BOOL_T CLI_HOOK_Deregister_CmdExecute_CallbackFunc
	(
	IN CLI_CMD_EXECUTE_CALLBACK_T callbackFunc
	)
{
	UI32_T i;

	for (i = 0; i < CLI_HOOK_CMD_EXECUTE_MAXNUM; i++)
	{
		if (s_cmdexe_cblist[i].cb_func == callbackFunc)
		{
			s_cmdexe_cblist[i].cb_func = NULL;
			s_cmdexe_cblist[i].cb_ck = NULL;

			return TRUE;
		}
	}

	return FALSE;
}



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
BOOL_T CLI_HOOK_Get_NextCmdExecute_CallbackFunc
	(
	IN OUT CLI_CMD_EXECUTE_CALLBACK_T 	*callbackFunc,
	OUT void 							**callbackCookie
	)
{
	UI32_T i, j;

	if (*callbackFunc == NULL)
	{
		for (i = 0; i < CLI_HOOK_CMD_EXECUTE_MAXNUM; i++)
		{
			if (s_cmdexe_cblist[i].cb_func != NULL)
			{
				*callbackFunc = s_cmdexe_cblist[i].cb_func;
				*callbackCookie = s_cmdexe_cblist[i].cb_ck;

				return TRUE;
			}
		}
	}
	else
	{
		for (i = 0; i < CLI_HOOK_CMD_EXECUTE_MAXNUM; i++)
		{
			if (s_cmdexe_cblist[i].cb_func == *callbackFunc)
			{
				for (j = i + 1; j < CLI_HOOK_CMD_EXECUTE_MAXNUM; j++)
				{
					if (s_cmdexe_cblist[j].cb_func != NULL)
					{
						*callbackFunc = s_cmdexe_cblist[j].cb_func;
						*callbackCookie = s_cmdexe_cblist[j].cb_ck;

						return TRUE;
					}
				}
			}
		}
	}

	return FALSE;
}



