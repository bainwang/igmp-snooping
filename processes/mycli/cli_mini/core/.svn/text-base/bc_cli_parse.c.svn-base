/*******************************************************************************
 * Copyright(C) 2008, Kingtype Networks Corporation. All rights reserved.
 *
 * This is unpublished proprietary source code of Kingtype Networks Corporation.
 *
 * The copyright notice above does not evidence any actual or intended
 *  publication of such source code.
*******************************************************************************/
/*==============================================================================
 * MODULE NAME: Kingtype CLI, bc_cli
 * FILE NAME  : bc_cli_parse.c
 * VERSION    : 1.0.0
 * DESCRIPTION: 
 * NOTES      :
 *
 * HISTORY    :
 * -----------------------------------------------------------------------------
 * Version 1.0 -- 2009-Aug-03 by wangbin
 * [NEW FEATURE]
 * <DESCRIPTION> Create
 *============================================================================*/

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								头   文   件								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_modules.h"
#include "bc_cli_type.h"
#include "bc_cli_parse.h"
#include "bc_cli_misc.h"



////////////////////////////////////////////////////////////////////////////////
//																			  //
//						外 部 变 量、 函 数 引 用							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//																			  //
//						结   构   体   宏   定   义							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
#define CLI_PARSE_SYNCMD_MAX_SIZE 40000 /* max size of the syntax command */



////////////////////////////////////////////////////////////////////////////////
//																			  //
//							全 局 变 量 定 义								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
/* 
 *	外部全局变量，提供整个工程调用，在头文件中提供调用接口(外部引用声明)。
 */

/* 
 *	内部全局变量，只提供给该文件内部函数调用，不在头文件中提供调用接口。
 */

//static unsigned int 	l_mdl_id = BC_MODULE_CLI_KERNEL;

static I8_T 			s_cli2_parse_syncmd_buf[CLI_PARSE_SYNCMD_MAX_SIZE];



////////////////////////////////////////////////////////////////////////////////
//																			  //
//								函  数  声  明								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//																			  //
//								函  数  定  义								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_PARSE_Preprocess_Syncmd
 *
 * DESCRIPTION:
 *   Format a syntax command:
 *     1. delete all white spaces and / in the front of the command.
 *     2. delete all white spaces just before and after "/{}[]<>()#".
 *     3. add a space before and after "|".
 *     4. delete all white spaces between word and add a space betreen them.
 *     5. all chars between # are saved.
 *     6. delete all white spaces at the end of the command description.
 *     7. use a global variable s_cli2_parse_syncmd_buf to save the formatted variable.
 *     8. calling the function and visit the out value should be locked in a task.
 *
 * INPUT:
 *   cmd      : address of the pointer to get the cmd pointer
 *   cmd_desc : description of the syntax command
 *   para     : address of the pointer to get the parameter pointer
 *   view     : address of the pointer to get the view pointer
 *
 * OUTPUT:
 *   *view    : if (*view == *cmd), command is registered in the root view, else pointer of the view.
 *   *cmd     : if return TRUE, it get the pointer of the syntax command.
 *   *para    : if NULL, command has no parameter part, else pointer of the parameter part.
 *
 * RETURN:
 *   TRUE     : format syntax command success.
 *   FALSE    : format syntax command failure.
 *
 * NOTES:
 *   None
 *
 * HISTORY:
 *   2009-Aug-03 by wangbin -- Create
 *
*******************************************************************************/
BOOL_T CLI_PARSE_Preprocess_Syncmd
	(
	IN const I8_T 	*cmd_desc,
	IN OUT I8_T 	**view,
	IN OUT I8_T 	**cmd,
	IN OUT I8_T 	**para
	)
{
	I8_T 			*buf = s_cli2_parse_syncmd_buf;
	const I8_T 		*ptr;

	CLI_MISC_Assert(cmd_desc && view && cmd && para);

	/* skip white spaces and "/" at the front of the command description */
	while (CLI_MISC_IS_WHITESPACE(*cmd_desc) || CLI_MISC_IS_VIEW_SEPERATOR(*cmd_desc))
	{
		cmd_desc++;
	}

	CLI_MISC_Assert(*cmd_desc); // command name not found
	CLI_MISC_Assert(strlen(cmd_desc) < CLI_PARSE_SYNCMD_MAX_SIZE); // command name not found

	if (!isalpha(*cmd_desc) && !CLI_MISC_IS_PARA_START(*cmd_desc))
	{
		/* invalid command name or view name */
		/* invalid command parameter (added for the command: "/<int> xxx", just one for a path) */
		return FALSE;
	}

	*view = buf;
	*cmd = buf;
	*para = NULL;

	/* format view and command name */
	while (*cmd_desc)
	{
		if (CLI_MISC_IS_WHITESPACE(*cmd_desc))
		{
			while (CLI_MISC_IS_WHITESPACE(*cmd_desc))
			{
				cmd_desc++;
			}

			if (!CLI_MISC_IS_HELP_START(*cmd_desc) && !CLI_MISC_IS_VIEW_SEPERATOR(*cmd_desc))
			{
				*buf++ = ' ';
			}
		}
		else if (CLI_MISC_IS_VIEW_SEPERATOR(*cmd_desc))
		{
			*buf++ = *cmd_desc++;

			while (CLI_MISC_IS_WHITESPACE(*cmd_desc) || CLI_MISC_IS_VIEW_SEPERATOR(*cmd_desc))
			{/* skip extra view seperator and white spaces*/
				cmd_desc++;
			}

			if (!isalpha(*cmd_desc) && !CLI_MISC_IS_PARA_START(*cmd_desc))
			{
				/* invalid command name or view name */
				/* invalid command parameter (added for the command: "/view/<int> xxx", just one for a path) */
				return FALSE;
			}

			*cmd = buf;
		}
		else if (CLI_MISC_IS_PARA_START(*cmd_desc))
		{
			/* check if it is a parameter */
			ptr = cmd_desc;
			if (isupper(*ptr))
			{
				while (CLI_MISC_Is_Alias_Char_OutAngleBrackets(*ptr))
				{
					ptr++;
				}

				if (CLI_MISC_Is_Keyword_Char(*ptr)) /* the word is keyword */
				{
					/* get command keyword */
					while (CLI_MISC_Is_Keyword_Char(*cmd_desc))
					{
						*buf++ = *cmd_desc++;
					}
				}
				else /* the word is parameter */
				{
					break;
				}
			}
			else
			{
				/* parameter start */
				break;
			}
		}
		else if (CLI_MISC_IS_HELP_START(*cmd_desc)) /* process help string */
		{
			*buf++ = *cmd_desc++;
			while (*cmd_desc && (CLI_MISC_IS_HELP_START(*cmd_desc) == FALSE))
			{
				*buf++ = *cmd_desc++;
			}

			if (!CLI_MISC_IS_HELP_START(*cmd_desc))
			{/* help message not finished */
				return FALSE;
			}

			*buf++ = *cmd_desc++;
		}
		else /* get command keywords */
		{
			*buf++ = *cmd_desc++;
			while (CLI_MISC_Is_Keyword_Char(*cmd_desc))
			{
				*buf++ = *cmd_desc++;
			}
		}
	}

	if (*view == *cmd)
	{
		*view = NULL;
	}
	else
	{
		*(*cmd - 1) = '\0';
	}

	if ((buf != s_cli2_parse_syncmd_buf) && (*(buf - 1) == ' '))
	{
		*(buf - 1) = '\0';
	}
	else
	{
		*buf++ = '\0';
	}

	*para = buf;
	/* format parameter */
	while (*cmd_desc)
	{
		if (CLI_MISC_IS_WHITESPACE(*cmd_desc))
		{
			while (CLI_MISC_IS_WHITESPACE(*cmd_desc))
			{
				cmd_desc++;
			}

			if (!CLI_MISC_IS_HELP_START(*cmd_desc)
				&& (*cmd_desc != '|') && (*cmd_desc != '{') && (*cmd_desc != '}')
				&& (*cmd_desc != '[') && (*cmd_desc != ']')	&& (*cmd_desc != '<')
				&& (*cmd_desc != '>') && (*cmd_desc != '(') && (*cmd_desc != ')'))
			{
				*buf++ = ' ';
			}
		}
		else if (*cmd_desc == '|')
		{
			*buf++ = ' ';
			*buf++ = *cmd_desc++;
			*buf++ = ' ';
			while (CLI_MISC_IS_WHITESPACE(*cmd_desc))
			{
				cmd_desc++;
			}
		}
		else if (*cmd_desc == '(')
		{
			*buf++ = *cmd_desc++;
			while (CLI_MISC_IS_WHITESPACE(*cmd_desc))
			{
				cmd_desc++;
			}
		}
		else if ((*cmd_desc == '{') || (*cmd_desc == '[') || (*cmd_desc == '<'))
		{
			*buf++ = ' ';
			*buf++ = *cmd_desc++;
			while (CLI_MISC_IS_WHITESPACE(*cmd_desc))
			{
				cmd_desc++;
			}
		}
		else if ((*cmd_desc == '}') || (*cmd_desc == ']') || (*cmd_desc == '>')	|| (*cmd_desc == ')'))
		{
			*buf++ = *cmd_desc++;
			*buf++ = ' ';
			while (CLI_MISC_IS_WHITESPACE(*cmd_desc))
			{
				cmd_desc++;
			}
		}
		else
		{
			*buf++ = *cmd_desc++;
		}
	}

	*buf = '\0';

	/* check if the command don't have word part, just start with parameter. such as: "/<int> xxx" */
	if (**cmd == '\0')
	{
		/* check the command is start with parameter */
		*cmd = NULL;
		/* if the command word is null and the parameter is null, the command is error */
		if (**para == '\0')
		{
			return FALSE;
		}
	}

	return TRUE;
}



/* End of file */
