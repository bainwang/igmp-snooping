
#ifndef __BC_CLI_CORE_H__
#define __BC_CLI_CORE_H__

#include "bc_cli_type.h"
#include "bc_cli_priv.h"



/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 CLI_CORE_Get_Help
 *
 * DESCRIPTION:
 *	 Get all possible word of the user cmd in current view of default view.
 *
 * INPUT:
 *	 helplist -- pointer of the result wordlist
 *	 dir -- dir to be checked
 *	 usrcmd -- user command to be checked
 *	 level -- the level of the user who input <cmd_str>
 *
 * OUTPUT:
 *	 helplist -- result word list
 *
 * RETURN:
 *	 < 0 -- failure
 *	 = 0 -- success
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-27 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
I32_T CLI_CORE_Get_Help(
	IN OUT CLI_PRIV_HELPLIST_T *helplist,
	IN I8_T *dir,
	IN const I8_T *usrcmd,
	IN UI8_T level);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_CORE_GetView
 *
 * DESCRIPTION:
 *   Get data of view
 *
 * INPUT:
 *   dir: pointer of the directory
 *   level: access level of the current user
 *
 * OUTPUT:
 *   None
 *
 * RETURN:
 *   pointer of the dir data
 *
 * NOTES:
 *   None
 *
 * HISTORY:
 *   2009-Aug-05 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
CLI_CMD_NODE_T *CLI_CORE_GetView (IN I8_T *dir, IN UI8_T level);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   bc_cli_core_init
 *
 * DESCRIPTION:
 *   Init cli2 core
 *
 * INPUT:
 *   None
 *
 * OUTPUT:
 *   None
 *
 * RETURN:
 *   >= 0:
 *
 * NOTES:
 *   TRUE: Init cli2 core success.
 *   FALSE: Init cli2 core failure.
 *
 * HISTORY:
 *   2009-Aug-07 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
BOOL_T bc_cli_core_init (void);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_CORE_Parse_Cmdstr
 *
 * DESCRIPTION:
 *   parse the command and parameter -- 
 *   1. Parse a user command to wordlist
 *   2. Parse command in current view
 *   3. Parse command in global view
 *   4. Return found command node
 *
 * INPUT:
 *   view      : current view the command executed.
 *   usrcmd    : the command line
 *   level     : user's access level
 *   flag      : the access level and flag of command (low 8bits is the level)
 *   helpMsg   : english help message
 *   auxhelpMsg: second language help message
 *   user_data : user data as a cookie
 *
 * OUTPUT:
 *   para_list     : the parameter list
 *   error_position: error position of command line
 *
 * RETURN:
 *   pointer: found command node
 *   NULL   : match command fail or parse parameter fail
 *
 * NOTES:
 *   None
 *
 * HISTORY:
 *
*******************************************************************************/
CLI_CMD_NODE_T *CLI_CORE_Parse_Cmdstr(
	IN I8_T *view,
	IN I8_T *cmd_str,
	IN UI8_T level,
	OUT cli_value_t **para_list,
	OUT I32_T *error_position);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   cli_core_reg_cmd
 *
 * DESCRIPTION:
 *   register a command:
 *     1. create the command node and get the begin position of parameter part
 *     2. register the command's parameter part
 *
 * INPUT:
 *   vision: the version v1 or v2
 *   cmd_desc: the command string
 *   callbackFunc: the command's callback function
 *   flag: the access level and flag of command (low 8bits is the level)
 *   helpMsg: english help message
 *   auxhelpMsg: second language help message
 *   user_data: user data as a cookie
 *
 * OUTPUT:
 *   None
 *
 * RETURN:
 *   TRUE: success
 *   FALSE: error when create command:
 *     empty-string or invalid-word or memory-alloc-fail or command-existed
 *     error when register parameter:
 *
 * NOTES:
 *   None
 *
 * HISTORY:
 *
*******************************************************************************/
BOOL_T cli_core_reg_cmd(
	I8_T *cmd_desc,
	CLI_CMD_FUNC_T callbackFunc,
	I32_T flag,
	I8_T *helpMsg,
	I8_T *auxhelpMsg,
	void *user_data);

/*************************************************
FUNCTION NAME:
	cli_core_dereg_cmd

DESCRIPTION:
	deregister a command:
		1. find the command and its path
		2. free the parameter and information
		3. destory the command and its path (update the path's level also)

INPUT:
	cmd_desc	: the pointer of command string pointer

OUTPUT:

RETURN:
	TRUE		: success
	FALSE		: command not exist

NOTES:

HISTORY:

*************************************************/
BOOL_T cli_core_dereg_cmd(I8_T * cmd_desc);

/**************************************************************************
FUNCTION NAME:
	CLI_CORE_Change_CmdNode_Level

DESCRIPTION:
	Change the command node level.

INPUT:
	cmd_desc	: the pointer of command string
	new_level	: new command node level which will be configured
	all_children	: if all children nodes under the found node will be changed
				  TRUE->the children nodes under the found node will be changed
				  FALSE->just the found command node will be changed
				               (notes: in this case the found node must be a command node,
				               which has callback function.)
OUTPUT:
	None

RETURN:
	TRUE			: change success
	FALSE			: input command string is wrong

NOTES:
	If all_children == FALSE, the input command string must be a complete CLI command,
	(found node has callback function), if not will return FALSE.
	Because just change the path node level is meaningless.

HISTORY:
	Creat by bain.wang@outlook.com 2011.6.28

**************************************************************************/
BOOL_T CLI_CORE_Change_CmdNode_Level(
	IN I8_T * cmd_desc,
	IN I32_T new_level,
	IN BOOL_T all_children);

/**************************************************************************
FUNCTION NAME:
	CLI_CORE_Restore_CmdNode_Level

DESCRIPTION:
	Restore the command node level to the original registered level.

INPUT:
	cmd_desc	: the pointer of command string
	all_children	: if all children nodes under the found node will be changed
				  TRUE->the children nodes under the found node will be changed
				  FALSE->just the found command node will be changed
				               (notes: in this case the found node must be a command node,
				               which has callback function.)
OUTPUT:
	None

RETURN:
	TRUE			: change success
	FALSE			: input command string is wrong

NOTES:
	If all_children == FALSE, the input command string must be a complete CLI command,
	(found node has callback function), if not will return FALSE.
	Because just change the path node level is meaningless.

HISTORY:
	Creat by bain.wang@outlook.com 2011.6.28

**************************************************************************/
BOOL_T CLI_CORE_Restore_CmdNode_Level(
	IN I8_T * cmd_desc,
	IN BOOL_T all_children);



#endif /* __BC_CLI_CORE_H__ */

