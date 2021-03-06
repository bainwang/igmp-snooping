/*******************************************************************
MODULE NAME:
	CLI G2 Directory Module

FILE NAME:
 	cli2_dir.c

VERSION:
	2.00

DESCRIPTION:
 	The directory function for CLI G2 module.

NOTES:
    NA

HISTORY:
	Ver2.00:	2011.3.4 bain.wang@outlook.com new added

********************************************************************/

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              头   文   件                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "bc_modules.h"

#include "bc_cli_type.h"
#include "bc_cli_paratype.h"
#include "bc_cli_dir.h"
#include "bc_cli_misc.h"
#include "bc_cli_msg.h"

#include "bc_cli_para.h"



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
typedef struct tagCLI_PATH_NODE
{
	struct tagCLI_PATH_NODE 	*next;
	I8_T 						wd[CLI_DIR_WD_MAX + 1]; 			/* current directory of the node */
	I8_T 						prompt[CLI_DIR_PROMPT_MAX + 1]; 	/* prompt of the path */
	cli_value_t 				*prev_param;
} CLI_PATH_NODE_T;

typedef struct tagCLI_PATH_INFO
{
	CLI_PATH_NODE_T 	path_node;
	I8_T 				wd[CLI_DIR_WD_MAX + 1]; 			/* current directory of the session */
	I8_T 				prompt[CLI_DIR_PROMPT_MAX + 1]; 	/* prompt of the session */
	cli_value_t 		*path_param;
} CLI_PATH_INFO_T;

typedef struct tagCLI_MODE_NODE
{
	struct tagCLI_MODE_NODE 	*next;
	I8_T 						*wd; 		/* the directory of the mode, this value must different with others */
	I8_T 						*mode_name; /* mode name */
	I8_T 						*mode_desc; /* mode description */
} CLI_MODE_NODE_T;



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                          全 局 变 量 定 义                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
static CLI_MODE_NODE_T *s_cli2_mode_list = NULL;

static unsigned int 	l_mdl_id = BC_MODULE_CLI_KERNEL;



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
HANDLE_T CLI_DIR_Create(void)
{
	CLI_PATH_INFO_T *path_info;

	/* create root path node */
	path_info = CLI_MISC_Malloc(sizeof(CLI_PATH_INFO_T));
	if (path_info == NULL)
	{
		CLI_MSG_ERR(l_mdl_id, UTL_MISC_ERR_MEMORY_OVERFLOW);
		return NULL;
	}

	memset(path_info, 0, sizeof(CLI_PATH_INFO_T));

	return (HANDLE_T)path_info;
}



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
void CLI_DIR_Destroy(IN HANDLE_T dir_handle)
{
	CLI_PATH_INFO_T *path_info;
	CLI_PATH_NODE_T *next_pathNode, *temp_pathNode;

	path_info = (CLI_PATH_INFO_T *)dir_handle;

	/* get the next path node from root */
	next_pathNode = path_info->path_node.next;
	/* Free the path node */
	while (next_pathNode)
	{
		temp_pathNode = next_pathNode;
		next_pathNode = temp_pathNode->next;
		CLI_MISC_Free(temp_pathNode);
	}

	/* Free the path parameter */
	CLI_PARA_Free_ValueList(path_info->path_param);

	/* free the root node */
	CLI_MISC_Free(path_info);
}



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
void CLI_DIR_Clean(IN HANDLE_T dir_handle)
{
	CLI_PATH_INFO_T *path_info;
	CLI_PATH_NODE_T *next_pathNode, *temp_pathNode;

	path_info = (CLI_PATH_INFO_T *)dir_handle;

	/* get the next path node from root */
	next_pathNode = path_info->path_node.next;
	/* Free the path node */
	while (next_pathNode)
	{
		temp_pathNode = next_pathNode;
		next_pathNode = temp_pathNode->next;
		CLI_MISC_Free(temp_pathNode);
	}

	/* Free the path parameter */
	CLI_PARA_Free_ValueList(path_info->path_param);

	/* reset all */
	memset(path_info, 0, sizeof(CLI_PATH_INFO_T));
}



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
	IN cli_value_t *node_param)
{
	CLI_PATH_INFO_T 	*path_info;
	CLI_PATH_NODE_T 	*next_pathNode, *temp_pathNode;
	cli_value_t 		*ptr_param, *temp_param;
	UI32_T 				prompt_size;

	path_info = (CLI_PATH_INFO_T *)dir_handle;

	prompt_size = strlen(path_prompt);
	if (prompt_size > CLI_DIR_PROMPT_MAX)
	{
		return FALSE;
	}

	if (strlen(path) > CLI_DIR_WD_MAX)
	{
		return FALSE;
	}

	if (memcmp("/", path, strlen(path)) == 0)
	{
		/* reset root path */
		CLI_DIR_Clean(dir_handle);
		strcpy(path_info->wd, "/");
		strcpy(path_info->path_node.wd, "/");
		strcpy(path_info->prompt, path_prompt);
		strcpy(path_info->path_node.prompt, path_prompt);
	}
	else
	{
		/* set other path information */
		/* generate parameter list */
		ptr_param = CLI_PARA_Generate_ValueList(node_param);

		/* search if have path node has same prompt */
		/* search from root->next */
		temp_pathNode = path_info->path_node.next;
		while (temp_pathNode)
		{
			if (memcmp(temp_pathNode->prompt, path_prompt, strlen(path_prompt)) == 0)
			{
				break;
			}

			temp_pathNode = temp_pathNode->next;
		}

		if (temp_pathNode) /* find the same prompt node, so replace it */
		{
			if (temp_pathNode->prev_param) /* exist path parameter before current path node */
			{
				CLI_PARA_Free_ValueList(temp_pathNode->prev_param->next);
				temp_pathNode->prev_param->next = ptr_param;
			}
			else /* current path node parameter is first parameter in path */
			{
				CLI_PARA_Free_ValueList(path_info->path_param);
				path_info->path_param = ptr_param;
			}

			strcpy(temp_pathNode->wd, path);

			/* free the path node after current node */
			next_pathNode = temp_pathNode->next;
			temp_pathNode->next = NULL;
			while (next_pathNode)
			{
				temp_pathNode = next_pathNode;
				next_pathNode = next_pathNode->next;
				CLI_MISC_Free(temp_pathNode);
			}
		}
		else /* not find, it is new, so append it */
		{
			/* find the last node */
			temp_pathNode = &path_info->path_node;
			while (temp_pathNode->next)
			{
				temp_pathNode = temp_pathNode->next;
			}

			temp_pathNode->next = CLI_MISC_Malloc(sizeof(CLI_PATH_NODE_T));
			memset(temp_pathNode->next, 0, sizeof(CLI_PATH_NODE_T));
			strcpy(temp_pathNode->next->prompt, path_prompt);

			strcpy(temp_pathNode->next->wd, path);

			if (temp_pathNode->prev_param)
			{
				/* exist path parameter before append path node */
				temp_param = temp_pathNode->prev_param;
			}
			else
			{
				/* the node before append node prev parameter is null */
				temp_param = path_info->path_param;
			}

			if (temp_param)
			{
				/* the node before append node has path parameter */
				while (temp_param->next)
				{
					temp_param = temp_param->next;
				}
				temp_param->next = ptr_param;

				/* set the append node prev parameter pointer */
				temp_pathNode->next->prev_param = temp_param;
			}
			else
			{
				/* before append node the path parameter is null */
				path_info->path_param = ptr_param;
			}
		}

		strcpy(path_info->wd, path);
		memset(path_info->prompt, 0, sizeof(path_info->prompt));
		if (strlen(path_info->path_node.prompt) > (CLI_DIR_PROMPT_MAX - prompt_size))
		{
			strncpy(path_info->prompt, path_info->path_node.prompt, (CLI_DIR_PROMPT_MAX - prompt_size));
		}
		else
		{
			strcpy(path_info->prompt, path_info->path_node.prompt);
		}
		strcat(path_info->prompt, path_prompt);
	}

	return TRUE;
}



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
I8_T *cli_dir_get_cmdpath(IN HANDLE_T dir_handle)
{
	CLI_PATH_INFO_T 	*path_info;

	path_info = (CLI_PATH_INFO_T *)dir_handle;

	return path_info->wd;
}



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
BOOL_T CLI_DIR_Set_PathPrompt(IN HANDLE_T dir_handle, IN I8_T *path_prompt)
{
	UI32_T length;
	CLI_PATH_INFO_T *path_info;
	CLI_PATH_NODE_T *next_pathNode, *temp_pathNode;

	path_info = (CLI_PATH_INFO_T *)dir_handle;
	if (strlen(path_prompt) > CLI_DIR_PROMPT_MAX)
	{
		return FALSE;
	}

	temp_pathNode = NULL;
	next_pathNode = path_info->path_node.next;
	while (next_pathNode)
	{
		temp_pathNode = next_pathNode;
		next_pathNode = next_pathNode->next;
	}

	strcpy(path_info->path_node.prompt, path_prompt);

	if (temp_pathNode)
	{
		memset(path_info->prompt, 0, sizeof(path_info->prompt));
		length = strlen(temp_pathNode->prompt);

		if (strlen(path_info->path_node.prompt) > (CLI_DIR_PROMPT_MAX - length))
		{
			strncpy(path_info->prompt, path_info->path_node.prompt,
				(CLI_DIR_PROMPT_MAX - length));
		}
		else
		{
			strcpy(path_info->prompt, path_info->path_node.prompt);
		}
		strcat(path_info->prompt, temp_pathNode->prompt);
	}
	else
	{
		strcpy(path_info->prompt, path_info->path_node.prompt);
	}

	return TRUE;
}



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
I8_T *CLI_DIR_Get_PathPrompt(IN HANDLE_T dir_handle)
{
	CLI_PATH_INFO_T *path_info;

	path_info = (CLI_PATH_INFO_T *)dir_handle;

	return path_info->prompt;
}



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
	path: /path1/path2/path3
		enter path1 use command: [root] enter path1 <parameter1>
		enter path2 use command: [path1] enter path2
		enter path3 use command: [path2] enter path3 <parameter3>
		-> after enter path3, the cli_value_t path's information is: <parameter1>-><parameter3>
NOTES:

HISTORY:
	Creat by bain.wang@outlook.com 2011.3.2

**************************************************************************/
cli_value_t *CLI_DIR_Get_PathParameter(IN HANDLE_T dir_handle)
{
	CLI_PATH_INFO_T *path_info;

	path_info = (CLI_PATH_INFO_T *)dir_handle;

	return path_info->path_param;
}



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
BOOL_T CLI_DIR_Free_LastPathNode(IN HANDLE_T dir_handle)
{
	CLI_PATH_INFO_T 	*path_info;
	CLI_PATH_NODE_T 	*prev_pathNode, *next_pathNode, *temp_pathNode;
	UI32_T				length;

	path_info = (CLI_PATH_INFO_T *)dir_handle;

	prev_pathNode = &path_info->path_node;
	temp_pathNode = NULL;
	next_pathNode = path_info->path_node.next;
	while (next_pathNode)
	{
		temp_pathNode = next_pathNode;
		if (next_pathNode->next)
		{
			prev_pathNode = temp_pathNode;
		}
		next_pathNode = next_pathNode->next;
	}

	if (temp_pathNode)
	{
		/* Free last path node parameter */
		if (temp_pathNode->prev_param)
		{
			CLI_PARA_Free_ValueList(temp_pathNode->prev_param->next);
			temp_pathNode->prev_param->next = NULL;
		}
		else
		{
			/* maybe the last path node has parameter but before it the parameter is NULL */
			CLI_PARA_Free_ValueList(path_info->path_param);
			path_info->path_param = NULL;
		}

		/* free the last node and modify node */
		prev_pathNode->next = NULL;
		CLI_MISC_Free(temp_pathNode);

		/* set the current path */
		strcpy(path_info->wd, prev_pathNode->wd);

		/* modify the path prompt */
		memset(path_info->prompt, 0, sizeof(path_info->prompt));
		if (&path_info->path_node == prev_pathNode)
		{
			strcpy(path_info->prompt, path_info->path_node.prompt);
		}
		else
		{
			length = strlen(prev_pathNode->prompt);

			if (strlen(path_info->path_node.prompt) > (CLI_DIR_PROMPT_MAX - length))
			{
				strncpy(path_info->prompt, path_info->path_node.prompt,
					(CLI_DIR_PROMPT_MAX - length));
			}
			else
			{
				strcpy(path_info->prompt, path_info->path_node.prompt);
			}
			strcat(path_info->prompt, prev_pathNode->prompt);
		}
	}
	else
	{
		/* only have one root node, not free */
		return FALSE;
	}

	return TRUE;
}



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
	IN I8_T *mode_desc)
{
	UI32_T 				buf_size, wd_size, mode_name_size, mode_desc_size;
	CLI_MODE_NODE_T 	*new_mode_node;
	CLI_MODE_NODE_T 	*last_mode_node, *temp_mode_node;

	if (wd == NULL || mode_name == NULL)
	{
		return FALSE;
	}

	last_mode_node = s_cli2_mode_list;
	temp_mode_node = s_cli2_mode_list;

	/* search mode list */
	while (temp_mode_node)
	{
		if (strcmp(temp_mode_node->wd, wd) == 0) /* found it, failed to create the mode */
		{
			return FALSE;
		}

		last_mode_node = temp_mode_node;
		temp_mode_node = temp_mode_node->next;
	}

	/* calculate the node buffer to store the mode information */
	wd_size = strlen(wd);
	mode_name_size = strlen(mode_name);
	if (mode_desc)
	{
		mode_desc_size = strlen(mode_desc);
	}
	else
	{
		mode_desc_size = 0;
	}

	/* create the new mode node */
	buf_size = sizeof(CLI_MODE_NODE_T) + wd_size + 1 + mode_name_size + 1 + mode_desc_size + 1;
	new_mode_node = (CLI_MODE_NODE_T *)CLI_MISC_Malloc(buf_size);
	if (new_mode_node == NULL)
	{
		return FALSE;
	}

	/* assignment */
	new_mode_node->next = NULL;
	new_mode_node->wd = (I8_T *)(new_mode_node + 1); /* 1.CLI_MODE_NODE_T指针加1，2.转换为I8_T指针 */
	strcpy(new_mode_node->wd, wd);
	new_mode_node->mode_name = new_mode_node->wd + wd_size + 1;
	strcpy(new_mode_node->mode_name, mode_name);
	new_mode_node->mode_desc = new_mode_node->mode_name + mode_name_size + 1;
	if (mode_desc)
	{
		strcpy(new_mode_node->mode_desc, mode_desc);
	}
	else
	{
		new_mode_node->mode_desc[0] = '\0';
	}

	/* insert the new mode node into the mode list */
	if (s_cli2_mode_list == NULL)
	{
		s_cli2_mode_list = new_mode_node;
	}
	else
	{
		last_mode_node->next = new_mode_node;
	}

	return TRUE;
}



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
	OUT I8_T *mode_desc)
{
	CLI_MODE_NODE_T *temp_mode_node;

	temp_mode_node = s_cli2_mode_list;
	if (temp_mode_node == NULL)
	{
		return NULL;
	}

	if (pre_node == NULL)
	{
		strcpy(wd, temp_mode_node->wd);
		strcpy(mode_name, temp_mode_node->mode_name);
		strcpy(mode_desc, temp_mode_node->mode_desc);

		return temp_mode_node;
	}
	else
	{
		while (temp_mode_node)
		{
			if (temp_mode_node == (CLI_MODE_NODE_T *)pre_node)
			{
				temp_mode_node = temp_mode_node->next;
				break;
			}

			temp_mode_node = temp_mode_node->next;
		}

		if (temp_mode_node)
		{
			strcpy(wd, temp_mode_node->wd);
			strcpy(mode_name, temp_mode_node->mode_name);
			strcpy(mode_desc, temp_mode_node->mode_desc);
		}

		return temp_mode_node;
	}
}



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
	OUT I8_T 	*wd,
	OUT I8_T 	*mode_name,
	OUT I8_T 	*mode_desc)
{
	CLI_MODE_NODE_T *temp_mode_node;

	if (NULL == current_node)
	{
		return FALSE;
	}

	temp_mode_node = (CLI_MODE_NODE_T *)current_node;
	strcpy(wd, temp_mode_node->wd);
	strcpy(mode_name, temp_mode_node->mode_name);
	strcpy(mode_desc, temp_mode_node->mode_desc);

	return TRUE;
}



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
	OUT I8_T *mode_name)
{
	CLI_MODE_NODE_T *temp_mode_node;

	temp_mode_node = s_cli2_mode_list;
	while (temp_mode_node)
	{
		if (strcmp(temp_mode_node->wd, wd) == 0)
		{
			strcpy(mode_name, temp_mode_node->mode_name);
			return temp_mode_node;
		}

		temp_mode_node = temp_mode_node->next;
	}

	return NULL;
}



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
	OUT I8_T *wd)
{
	CLI_MODE_NODE_T 	*temp_mode_node;
	BOOL_T 				pre_flag;

	temp_mode_node = s_cli2_mode_list;
	if (pre_node == NULL)
	{
		pre_flag = TRUE;
	}
	else
	{
		pre_flag = FALSE;
	}

	while (temp_mode_node)
	{
		if (strcmp(temp_mode_node->mode_name, mode_name) == 0)
		{
			if (pre_flag)
			{
				strcpy(wd, temp_mode_node->wd);
				return temp_mode_node;
			}

			if (temp_mode_node == (CLI_MODE_NODE_T *)pre_node)
			{
				pre_flag = TRUE;
			}
		}

		temp_mode_node = temp_mode_node->next;
	}

	return NULL;
}



