/*******************************************************************

COPYRIGHT:
	Copyright (c) 2005-2011  Kingtype Corporation   All rights reserved.
   	This is unpublished proprietary source code of Kingtype Corporation.
	The copyright notice above does not evidence any actual or intended
	publication of such source code.

MODULE NAME:
	CLI

FILE NAME:
 	cli2_cmdlog.c

VERSION:
	1.00

DESCRIPTION:
 	Add the command logging function.

NOTES:
   	NA

HISTORY:
	Ver1.00:	2010.6.22 wangbin

********************************************************************/

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              头   文   件                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "bc_modules.h"
#include "bc_platform_sem.h"

#include "bc_cli_type.h"
#include "bc_cli_misc.h"
#include "bc_cli_hook.h"
#include "bc_cli_acc.h"

#if CLI_COMMAND_LOGGING_INCLUDED
#include "bc_cli_log_cmd.h"
#endif

//#include "bc_cli.h"



#if 0 //CLI_COMMAND_LOGGING_INCLUDED

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



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                          全 局 变 量 定 义                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

static unsigned int 			l_mdl_id = BC_MODULE_CLI_KERNEL;

static CLI_CMDLOG_STATE_T 		s_cmdlog_state;

static HANDLE_T 				s_cmdlog_semaphore = NULL; /* semaphore for command logging */

#define CLI_CMDLOG_DB_Lock()	bc_platform_sem_wait(s_cmdlog_semaphore, BC_SEM_WAIT_FOREVER)
#define CLI_CMDLOG_DB_Unlock()	bc_platform_sem_post(s_cmdlog_semaphore)



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
	CLI_CMDLOG_Get_State

DESCRIPTION:
	Get the state of command logging function.

INPUT:
	NA

OUTPUT:
	cmdLogState	: the command logging state

RETURN:
	NA

NOTES:

HISTORY:
	Creat by wangbin 2011.6.22

**************************************************************************/
void CLI_CMDLOG_Get_State(OUT CLI_CMDLOG_STATE_T *cmdLogState)
{
	CLI_CMDLOG_DB_Lock();
	cmdLogState->cmdlog_enable = s_cmdlog_state.cmdlog_enable;
	cmdLogState->cmdlog_level  = s_cmdlog_state.cmdlog_level;
	CLI_CMDLOG_DB_Unlock();

	return;
}



/**************************************************************************
FUNCTION NAME:
	CLI_CMDLOG_Set_State

DESCRIPTION:
	Set the state of command logging function.

INPUT:
	cmdLogState	: the command logging state

OUTPUT:
	NA

RETURN:
	NA

NOTES:

HISTORY:
	Creat by wangbin 2011.6.22

**************************************************************************/
void CLI_CMDLOG_Set_State(IN CLI_CMDLOG_STATE_T *cmdLogState)
{
	CLI_CMDLOG_DB_Lock();
	s_cmdlog_state.cmdlog_enable = cmdLogState->cmdlog_enable;
	s_cmdlog_state.cmdlog_level  = cmdLogState->cmdlog_level;
	CLI_CMDLOG_DB_Unlock();

	return;
}



/**************************************************************************
FUNCTION NAME:
	__cli2_cmdlog_get_firstWord

DESCRIPTION:
	Get first word from input string

INPUT:
	cmd_string	: the pointer of input command string

OUTPUT:
	word_buf	: first word buffer

RETURN:
	the parsed position

NOTES:

HISTORY:
	Creat by wangbin 2011.6.22

**************************************************************************/
static I8_T *__cli2_cmdlog_get_firstWord(IN I8_T *cmd_string, OUT I8_T *word_buf)
{
	while (*cmd_string == ' ' || *cmd_string == '\t')
	{
		cmd_string++;
	}

	while (*cmd_string && *cmd_string != ' ' && *cmd_string != '\t')
	{
		*word_buf++ = *cmd_string++;
	}

	*word_buf = '\0';

	return cmd_string;
}



/**************************************************************************
FUNCTION NAME:
	__cli2_cmdlog_check_cmd

DESCRIPTION:
	This funtion is used to check input command that need record log or not.

INPUT:
	cmd_string	: the pointer of input command string

OUTPUT:
	cmd_string	: command which need to record

RETURN:
	TRUE	: need to record
	FALSE	: don't record

NOTES:

HISTORY:
	Creat by wangbin 2011.6.22

**************************************************************************/
static BOOL_T __cli2_cmdlog_check_cmd(IN OUT I8_T *cmd_string)
{
	I8_T 	*cmd_str_left = NULL;
	I8_T 	first_word[100];

	cmd_str_left = __cli2_cmdlog_get_firstWord(cmd_string, first_word);

	if (first_word[0] == 0)
	{
		return FALSE;
	}

	if (!memcmp("show", first_word, strlen(first_word)))
	{
		return FALSE;
	}

	if (!memcmp("ping", first_word, strlen(first_word)))
	{
		return FALSE;
	}

	return TRUE;
}



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
						  TRUE  -> before execute command
						  FALSE -> after execute command
	ret_execute_cmd		: if after execute command, the value record the executed result
	pre_state			: previous state of execute the callback function
	cookie				: cookie (define by callback function)

OUTPUT:
	NA

RETURN:
	NA

NOTES:

HISTORY:

**************************************************************************/
static I32_T __cli2_cmdlog_execute_callbackFunc
	(
	IN UI32_T 	sessionID, 
	IN I8_T 	*cmd_ptr,
	IN BOOL_T 	before_execute_cmd,
	IN I32_T 	ret_execute_cmd,
	IN I32_T 	pre_state,
	IN void 	*cookie
	)
{
	cli_sesn_type_t sessionType;
	CLI_CMDLOG_T 		cmdLog;
		
	UNUSED(cookie);

	if (before_execute_cmd) // TRUE = before_execute_cmd, before execute command
	{
		/* check if need record this command */
		sessionType = cli_sesn_get_type(sessionID);
		if ((CLI_SESN_TYPE_PSEUDO == sessionType) || (CLI_SESN_TYPE_NONE == sessionType)) // for pseudo not recored the log
		{
			return 0;
		}

		if (CLI_BAT_Check_Playback(sessionID)) // for bat configuration not recored the log
		{
			return 0;
		}

		if (s_cmdlog_state.cmdlog_enable) // state enable, need record the log
		{
			return 1;
		}
	}
	else // FALSE = before_execute_cmd, after execute command
	{
		if (pre_state)
		{
			if ((CLI_CMD_SUCCESS_PRT_NONE == ret_execute_cmd)
				|| (CLI_CMD_SUCCESS_PRT_NEWLINE == ret_execute_cmd)
				|| (CLI_CMD_SUCCESS_PRT_PROMPT == ret_execute_cmd)
				|| (CLI_CMD_SUCCESS_PRT_PROMPT_NEWLINE == ret_execute_cmd))
			{
				cmdLog.sessionID = sessionID;
				cmdLog.ptrcmd    = cmd_ptr;

				if (CLI_CMDLOG_Record_LogForCMD(&cmdLog))
				{
					return 1;
				}
			}
		}
		/* else: pre_state = 0, don't need record the log */
	}

	return 0;
}



/**************************************************************************
FUNCTION NAME:
	CLI_CMDLOG_Record_LogForCMD

DESCRIPTION:
	This funtion used record a log for command.

INPUT:
	cmdlog	: command logging information

OUTPUT:
	NA

RETURN:
	TRUE	: record success
	FALSE	: record false

NOTES:

HISTORY:
	Creat by wangbin 2011.6.22

**************************************************************************/
BOOL_T CLI_CMDLOG_Record_LogForCMD(IN CLI_CMDLOG_T *cmdlog)
{
	I8_T 	username[BNR_CPU_NAME_MAX_LEN + 1];
	I8_T 	*cmd_buf;

	if (bc_cli_get_usr_name(cmdlog->sessionID, username) == FALSE)
	{
		return FALSE;
	}

	if (cmdlog->ptrcmd == NULL)
	{
		return FALSE;
	}

	cmd_buf = cli_misc_malloc(CLI_API_MAX_CMD_LEN + 1);
	if (cmd_buf == NULL)
	{
		return FALSE;
	}

	strcpy(cmd_buf, cmdlog->ptrcmd);
	if (__cli2_cmdlog_check_cmd(cmd_buf) == FALSE)
	{
		cli_misc_free(cmd_buf);
		return FALSE;
	}

#if 0 
	// write log
	SLOG_CMDLOG_LOG_CMD(username, cmd_buf);
#endif

	cli_misc_free(cmd_buf);

	return TRUE;
}



/**************************************************************************
FUNCTION NAME:
	bc_cli_log_init

DESCRIPTION:
	Initialize the record command logging function DB.

INPUT:
	NA

OUTPUT:
	NA

RETURN:
	NA

NOTES:

HISTORY:
	Creat by wangbin 2011.6.22

**************************************************************************/
void bc_cli_log_init(void)
{
	if (NULL == (s_cmdlog_semaphore = bc_platform_sem_create("CLI-LOG", 1)))
	{
		CLI_MSG_ERR(l_mdl_id, "Failed to create cmdlog sem.\n");
		return;
	}

	s_cmdlog_state.cmdlog_enable = FALSE;
	s_cmdlog_state.cmdlog_level = CLI_ACC_LVL_ADMIN;

	return;
}



/**************************************************************************
FUNCTION NAME:
	bc_cli_log_cmd_reg

DESCRIPTION:
	Initialize the record command logging function.

INPUT:
	NA

OUTPUT:
	NA

RETURN:
	NA

NOTES:

HISTORY:
	Creat by wangbin 2011.6.22

**************************************************************************/
void bc_cli_log_cmd_reg(void)
{
	CLI_HOOK_Register_CmdExecute_CallbackFunc(__cli2_cmdlog_execute_callbackFunc, NULL);
}



#endif

