/*******************************************************************
MODULE NAME:
	CLI G2 Directory Module

FILE NAME:
 	bc_cli_dir.h

VERSION:
	2.00

DESCRIPTION:
 	.h file of directory function for CLI G2 module.

NOTES:
    NA

HISTORY:
	Ver2.00:	2011.3.4 bain.wang@outlook.com new added

********************************************************************/

#ifndef __BC_CLI_DIR_H__
#define __BC_CLI_DIR_H__

////////////////////////////////////////////////////////////////////////////////
// 								    										  //
// 							    头   文   件								  //
// 										    								  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_cli_kernel_cfg.h"
#include "bc_cli_paratype.h"



////////////////////////////////////////////////////////////////////////////////
//																			  //
//						结   构   体   宏   定   义							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//																			  //
//								函	数	声	明								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

/**************************************************************************
FUNCTION NAME:
	CLI_DIR_Create

DESCRIPTION:
	Create directory of root path information .

INPUT:
	NA

OUTPUT:
	NA

RETURN:
	directory handle

NOTES:

HISTORY:

**************************************************************************/
HANDLE_T CLI_DIR_Create(void);

/**************************************************************************
FUNCTION NAME:
	CLI_DIR_Destroy

DESCRIPTION:
	Destory the path information.

INPUT:
	dir_handle		: directory handle

OUTPUT:
	NA

RETURN:
	NA

NOTES:

HISTORY:
	Creat by bain.wang@outlook.com 2011.3.2

**************************************************************************/
void CLI_DIR_Destroy(IN HANDLE_T dir_handle);

/**************************************************************************
FUNCTION NAME:
	CLI_DIR_Clean

DESCRIPTION:
	Clean the path information.

INPUT:
	dir_handle		: directory handle

OUTPUT:
	NA

RETURN:
	NA

NOTES:

HISTORY:
	Creat by bain.wang@outlook.com 2011.3.2

**************************************************************************/
void CLI_DIR_Clean(IN HANDLE_T dir_handle);

/**************************************************************************
FUNCTION NAME:
	cli_dir_set_cmdpath

DESCRIPTION:
	Set the CLI command executing path.
	1.若为根目录，则直接设置；
	2.在当前模式用户进入的模式顺序链表中查找相同模式提示符的结点；
	3.若找到，把链表中的后续结点删除；
	4.若未找到，在链表末尾追加新的模式结点；
	5.挂载进入该模式的参数

INPUT:
	dir_handle	: directory handle
	path		: full path string
					For example: "/config/config-if-port"
	path_prompt	: the prompt message after entered the configured path
					For example: "(config-if)"
	ptrPathValue: current path's information get from input CLI parameter value

OUTPUT:
	NA

RETURN:
	TRUE		: Enter and set path success.
	FALSE		: Enter or set path fail.

NOTES:
	if exist the path node has same prompt then replace it, else append it

HISTORY:
	Creat by bain.wang@outlook.com 2011.3.2

**************************************************************************/
BOOL_T cli_dir_set_cmdpath(
	IN HANDLE_T dir_handle,
	IN I8_T *path,
	IN I8_T *path_prompt,
	IN cli_value_t *node_param);

/**************************************************************************
FUNCTION NAME:
	cli_dir_get_cmdpath

DESCRIPTION:
	Get the CLI command executing path.

INPUT:
	dir_handle	: directory handle

OUTPUT:
	NA

RETURN:
	current path

NOTES:

HISTORY:
	Creat by bain.wang@outlook.com 2011.3.2

**************************************************************************/
I8_T *cli_dir_get_cmdpath(IN HANDLE_T dir_handle);

/**************************************************************************
FUNCTION NAME:
	CLI_DIR_Set_PathPrompt

DESCRIPTION:
	Set the CLI command executing path prompt. (Just change the root prompt)

INPUT:
	dir_handle	: directory handle
	prompt		: path prompt

OUTPUT:
	NA

RETURN:
	TRUE		: set success
	FALSE		: prompt length is error

NOTES:

HISTORY:
	Creat by bain.wang@outlook.com 2011.3.7

**************************************************************************/
BOOL_T CLI_DIR_Set_PathPrompt(IN HANDLE_T dir_handle, IN I8_T *path_prompt);

/**************************************************************************
FUNCTION NAME:
	CLI_DIR_Get_PathPrompt

DESCRIPTION:
	Get the CLI command executing path prompt.

INPUT:
	dir_handle	: directory handle

OUTPUT:
	NA

RETURN:
	current path prompt

NOTES:

HISTORY:
	Creat by bain.wang@outlook.com 2011.3.2

**************************************************************************/
I8_T *CLI_DIR_Get_PathPrompt(IN HANDLE_T dir_handle);

/**************************************************************************
FUNCTION NAME:
	CLI_DIR_Get_PathParameter

DESCRIPTION:
	Get the path's information.

INPUT:
	dir_handle	: directory handle

OUTPUT:
	NA

RETURN:
	cli_value_t	: the path's information for example
	path        : /path1/path2/path3
		enter path1 use command: [root] enter path1 <parameter1>
		enter path2 use command: [path1] enter path2
		enter path3 use command: [path2] enter path3 <parameter3>
		-> after enter path3, the cli_value_t path's information is: <parameter1>-><parameter3>
NOTES:

HISTORY:
	Creat by bain.wang@outlook.com 2011.3.2

**************************************************************************/
cli_value_t *CLI_DIR_Get_PathParameter(IN HANDLE_T dir_handle);

/**************************************************************************
FUNCTION NAME:
	CLI_DIR_Free_LastPathNode

DESCRIPTION:
	Free the last path node, if have root node only, return FALSE.

INPUT:
	dir_handle	: directory handle

OUTPUT:
	NA

RETURN:
	TRUE		: free success
	FALSE		: just have root node only

NOTES:

HISTORY:
	Creat by bain.wang@outlook.com 2011.3.7

**************************************************************************/
BOOL_T CLI_DIR_Free_LastPathNode(IN HANDLE_T dir_handle);

/**************************************************************************
FUNCTION NAME:
	cli_dir_reg_mode

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
BOOL_T cli_dir_reg_mode(
	IN I8_T *wd,
	IN I8_T *mode_name,
	IN I8_T *mode_desc);

/**************************************************************************
FUNCTION NAME:
	CLI_DIR_Get_NextModeInfo

DESCRIPTION:
	Get the next mode node information for input node.

INPUT:
	pre_node	: previous node, if it's null that means get first node.

OUTPUT:
	wd			: the directory of the mode, this value must different with others
				  such as: /config
	mode_name	: the mode name which indicates the directory
	mode_desc	: the mode description

RETURN:
	current mode node, if the value is null that means the next node of input node is null.

NOTES:

HISTORY:
	Creat by bain.wang@outlook.com 2011.6.23

**************************************************************************/
HANDLE_T CLI_DIR_Get_NextModeInfo(
	IN HANDLE_T pre_node,
	OUT I8_T *wd,
	OUT I8_T *mode_name,
	OUT I8_T *mode_desc);

/**************************************************************************
FUNCTION NAME:
	CLI_DIR_Get_CurrentModeInfo

DESCRIPTION:
	Get the current mode node information for input node.

INPUT:
	current_node	: current node, if it's null will return FALSE.

OUTPUT:
	wd				: the directory of the mode, this value must different with others
					  such as: /config
	mode_name		: the mode name which indicates the directory
	mode_desc		: the mode description

RETURN:
	TRUE			: get success
	FALSE			: current node is null

NOTES:

HISTORY:
	Creat by bain.wang@outlook.com 2011.6.23

**************************************************************************/
BOOL_T CLI_DIR_Get_CurrentModeInfo(
	IN HANDLE_T current_node,
	OUT I8_T *wd,
	OUT I8_T *mode_name,
	OUT I8_T *mode_desc);

/**************************************************************************
FUNCTION NAME:
	CLI_DIR_Get_ModeName_ByModeDirectory

DESCRIPTION:
	Get corresponding mode name by input mode name.

INPUT:
	wd			: the directory of the mode, this value must different with others
				  such as: /config

OUTPUT:
	mode_name	: the mode name which indicates the directory

RETURN:
	current mode node with the input directory,
	if the value is null that means don't exit the node with the input directory.

NOTES:

HISTORY:
	Creat by bain.wang@outlook.com 2011.6.24

**************************************************************************/
HANDLE_T CLI_DIR_Get_ModeName_ByModeDirectory(
	IN I8_T *wd,
	OUT I8_T *mode_name);

/**************************************************************************
FUNCTION NAME:
	CLI_DIR_Get_NextModeDirectory_ByModeName

DESCRIPTION:
	Get the next mode directory by input mode node and mode name.

INPUT:
	pre_node	: previous node, if it's null that means get first node with the input name
	mode_name	: the mode name which indicates the directory

OUTPUT:
	wd			: the directory of the mode, this value must different with others
				  such as: /config

RETURN:
	current mode node, if the value is null that means
	the next node with input mode name of input node is null.

NOTES:

HISTORY:
	Creat by bain.wang@outlook.com 2011.6.24

**************************************************************************/
HANDLE_T CLI_DIR_Get_NextModeDirectory_ByModeName(
	IN HANDLE_T pre_node,
	IN I8_T *mode_name,
	OUT I8_T *wd);



#endif /* __BC_CLI_DIR_H__ */

