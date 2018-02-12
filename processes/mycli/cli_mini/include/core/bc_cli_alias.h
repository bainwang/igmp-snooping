/*******************************************************************************
 * Copyright(C) 2008, Kingtype Networks Corporation. All rights reserved.
 *
 * This is unpublished proprietary source code of Kingtype Networks Corporation.
 *
 * The copyright notice above does not evidence any actual or intended
 *	publication of such source code.
*******************************************************************************/
/*==============================================================================
 * MODULE NAME: Kingtype CLI, bc_cli
 * FILE NAME  : bc_cli_alias.h
 * VERSION    : 1.0.0
 * DESCRIPTION:
 * NOTES:
 *
 * HISTORY:
 * -----------------------------------------------------------------------------
 * Version 1.0 -- 2009-Mar-12 by wangbin
 * [NEW FEATURE]
 * <DESCRIPTION> Create
 *============================================================================*/

#ifndef __BC_CLI_ALIAS_H__
#define __BC_CLI_ALIAS_H__

////////////////////////////////////////////////////////////////////////////////
// 								    										  //
// 							    头   文   件								  //
// 										    								  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_cli_type.h"
#include "bc_cli_paratype.h"
#include "bc_cli_priv.h"
#include "bc_cli_para.h"



////////////////////////////////////////////////////////////////////////////////
//																			  //
//						结   构   体   宏   定   义							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#define CLI_TYPES_MAX_NAME_LEN 	32

typedef struct
{
	const I8_T *name; // name of the word
	const I8_T *help_en; // English help
	const I8_T *help_local; // local help
	/*
	 * lparam, rparam --
	 * alias ARGUMENT       : [lparam, rparam] = range;
	 * OPTIONAL             : <lparam> = the options in the group should appeared in user command at least
	 * REQUIRED             : <lparam> = the options in the group can repeat n times at most
	 * OPTIONAL or REQUIRED : <rparam> = number of the child
	 * ENUM                 : <lparam> = enum value of the KEYWORD
	 */
	LPARAM lparam;
	RPARAM rparam;
	UI16_T type;		   // type of the word
	UI16_T name_len;	   // length of the name
	UI16_T help_en_len;    // length of the English help
	UI16_T help_local_len; // length of the local help
} CLI_PARA_WORD_T;



////////////////////////////////////////////////////////////////////////////////
//																			  //
//								函	数	声	明								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 CLI_TYPES_GET_RANGE_FUNC_T
 *
 * DESCRIPTION:
 *	 This type of the function is used to convert range of the ARGUMENT to
 *	string used in ? or <tab> help system.
 *
 * INPUT:
 *	 str	-- range string (may be rparam, lparam-rparam or none)
 *	 end	-- end of the range string
 *	 lparam -- Left param of the range
 *	 rparam -- Right param of the range
 *
 * OUTPUT:
 *	 NA
 *
 * RETURN:
 *	 TRUE -- success
 *	 FALSE -- failure
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-14 by wangbin -- Create
 *
*******************************************************************************/
typedef BOOL_T CLI_TYPES_GET_RANGE_FUNC_T(IN const I8_T *str, IN const I8_T *end, IN OUT LPARAM *lparam, IN OUT RPARAM *rparam);


/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 CLI_TYPES_PRT_RANGE_FUNC_T
 *
 * DESCRIPTION:
 *	 This type of the function is used to check the range of an ARGUMENT
 *	string in user command.
 *convert range of the ARGUMENT to
 *	string used in ? or <tab> help system.
 *
 * INPUT:
 *	 lparam -- Left param of the range
 *	 rparam -- Right param of the range
 *
 * OUTPUT:
 *	 buf -- range string like <lparam-rparam>
 *
 * RETURN:
 *	 >= 0 -- length of the result string
 *	 = -1 -- failure
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-14 by wangbin -- Create
 *
*******************************************************************************/
typedef I32_T CLI_TYPES_PRT_RANGE_FUNC_T(OUT I8_T *buf,	IN LPARAM lparam, IN RPARAM rparam);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 CLI_TYPES_GET_VALUE_FUNC_T
 *
 * DESCRIPTION:
 *	 This type of the function is used to check the correction of an ARGUMENT
 *	string in user command and convert it to value in cli_value_t.
 *
 * INPUT:
 *	 str    -- ARGUMENT string in user command.
 *	 lparam -- Left param of the range
 *	 rparam -- Right param of the range
 *
 * OUTPUT:
 *	 *value -- value in cli_value_t
 *
 * RETURN:
 *	 TRUE   -- success
 *	 FALSE  -- failure
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-14 by wangbin -- Create
 *
*******************************************************************************/
typedef BOOL_T CLI_TYPES_GET_VALUE_FUNC_T(IN const I8_T *str, IN LPARAM lparam,	IN RPARAM rparam, OUT void *value);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 CLI_TYPES_GET_HELP_FUNC_T
 *
 * DESCRIPTION:
 *	 This type of the function is used to check the correction of an ARGUMENT
 *	string in user command and convert it to value in cli_value_t.
 *
 * INPUT:
 *	 str     -- ARGUMENT string in user command.
 *	 lparam  -- Left param of the range
 *	 rparam  -- Right param of the range
 *
 * OUTPUT:
 *	 *p_help -- value in cli_value_t
 *
 * RETURN:
 *	 TRUE    -- success
 *	 FALSE   -- failure
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-14 by wangbin -- Create
 *
*******************************************************************************/
typedef BOOL_T CLI_TYPES_GET_HELP_FUNC_T(IN const I8_T *str, IN LPARAM lparam, IN RPARAM rparam);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 CLI_TYPES_PRT_VALUE_FUNC_T
 *
 * DESCRIPTION:
 *	 This type of the function is used to convert ARGUMENT value in cli_value_t
 *	to string in user command.
 *
 * INPUT:
 *	 value -- value in cli_value_t
 *
 * OUTPUT:
 *	 buf   -- result string
 *
 * RETURN:
 *	 >= 0  -- length of the result string
 *	 = -1  -- failure
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-14 by wangbin -- Create
 *
*******************************************************************************/
typedef I32_T CLI_TYPES_PRT_VALUE_FUNC_T (OUT I8_T *buf, IN void *value);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 CLI_TYPES_PRT_VALUE_FUNC_T
 *
 * DESCRIPTION:
 *	 This type of the function is used to compare ARGUMENT value in cli_value_t
 *
 * INPUT:
 *	 dst -- first value
 *	 src -- second value
 *
 * OUTPUT:
 *	 NA
 *
 * RETURN:
 *	 -1 -- dst < src
 *	  0 -- dst = src
 *	  1 -- dst > src
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-14 by wangbin -- Create
 *
*******************************************************************************/
typedef I32_T CLI_TYPES_CMP_VALUE_FUNC_T(IN void *dst, IN void *src);

typedef struct  // collect all functions for process a specified argument type.
{
	CLI_PRIMITIVE_SYNTAX_T 	type; 		// primitive type of the argument in CLI
	UI32_T 						flags; 		// reserved
	CLI_TYPES_GET_RANGE_FUNC_T *get_range;
	CLI_TYPES_PRT_RANGE_FUNC_T *prt_range;
	CLI_TYPES_GET_VALUE_FUNC_T *get_value;
	CLI_TYPES_GET_HELP_FUNC_T  *get_help;
	CLI_TYPES_PRT_VALUE_FUNC_T *prt_value;
	CLI_TYPES_CMP_VALUE_FUNC_T *cmp_value;
} CLI_TYPES_ARGUFUNC_T;



////////////////////////////////////////////////////////////////////////////////
//																			  //
//								函	数	声	明								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 CLI_ALIAS_Init
 *
 * DESCRIPTION:
 *	 Init global variables in alias module
 *
 * INPUT:
 *	 NA
 *
 * OUTPUT:
 *	 NA
 *
 * RETURN:
 *	 NA
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-19 by wangbin -- Create
 *
*******************************************************************************/
void CLI_ALIAS_Init (void);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 CLI_ALIAS_Parse
 *
 * DESCRIPTION:
 *	 Parse an alias in syntax command to check the correction of it and get the
 *		range and other message of it.
 *
 * INPUT:
 *	 alias -- alias string in syntax command. it may be in <> or in uppercase.
 *	 end -- end pointer of the string.
 *
 * OUTPUT:
 *	 node -- alias messages(name, type, range and help information)
 *
 * RETURN:
 *	 TRUE -- success
 *	 FALSE -- failure
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-19 by wangbin -- Create
 *
*******************************************************************************/
BOOL_T CLI_ALIAS_Parse (
	IN const I8_T *alias,
	IN const I8_T *end,
	OUT CLI_PARA_WORD_T * node);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_ALIAS_Set_AliasRange
 *
 * DESCRIPTION:
 *   Change the range of the alias.
 *
 * INPUT:
 *   alias_name -- name of the alias
 *   alias_range -- range of the alias
 *
 * OUTPUT:
 *   None
 *
 * RETURN:
 *   TRUE -- set alias range to new value success
 *   FALSE -- set alias range to new value failure
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2009-May-26 by wangbin -- Create
 *
*******************************************************************************/
BOOL_T CLI_ALIAS_Set_AliasRange (
	IN const I8_T *alias_name,
	IN const I8_T *alias_range);

/**************************************************************************
FUNCTION NAME:
	CLI_ALIAS_Clac_ParaValueSize

DESCRIPTION:
	Calculate the parameter value size.

INPUT:
	type		: parameter base type
	ptr			: input string or parameter value

OUTPUT:

RETURN:
	The size of parameter value

NOTES:

HISTORY:

**************************************************************************/
UI32_T CLI_ALIAS_Clac_ParaValueSize(
	IN CLI_PRIMITIVE_SYNTAX_T type,
	IN const I8_T *ptr);

/**************************************************************************
FUNCTION NAME:
	CLI_ALIAS_GetParaType_ByName

DESCRIPTION:
	Get parameter type by input name string.

INPUT:
	name		: parameter name string
	len			: length of name string

OUTPUT:

RETURN:
	parameter type
	-1			: don't have this parameter with input name

NOTES:

HISTORY:

**************************************************************************/
CLI_PRIMITIVE_SYNTAX_T CLI_ALIAS_GetParaType_ByName(
	IN const I8_T *name,
	IN I32_T len);

/**************************************************************************
FUNCTION NAME:
	CLI_ALIAS_GetParaFormat_ByParaString

DESCRIPTION:
	Get the parameter format string by input parameter string.

INPUT:
	para_str		: parameter string (Ex: <int 1-100>)

OUTPUT:
	format_str	: used to store the translated parameter format string

RETURN:
	TRUE		: Get success
	FALSE		: the parameter string is error

NOTES:

HISTORY:

**************************************************************************/
BOOL_T CLI_ALIAS_GetParaFormat_ByParaString(
	IN I8_T *para_str,
	OUT I8_T *format_str);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 CLI_TYPES_GetCmpValueFunc
 *
 * DESCRIPTION:
 *	 Get cmp_value functions of the specified argument type
 *
 * INPUT:
 *	 type -- type of the argument
 *
 * OUTPUT:
 *	 NA
 *
 * RETURN:
 *	 pointer of the cmp_value function
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-15 by foo -- Create
 *
*******************************************************************************/
CLI_TYPES_CMP_VALUE_FUNC_T *CLI_TYPES_GetCmpValueFunc (IN I32_T type);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 CLI_TYPES_GetGetRangeFunc
 *
 * DESCRIPTION:
 *	 Get get_range function of the specified argument type
 *
 * INPUT:
 *	 type -- type of the argument
 *
 * OUTPUT:
 *	 NA
 *
 * RETURN:
 *	 pointer of the get_range function
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-15 by foo -- Create
 *
*******************************************************************************/
CLI_TYPES_GET_RANGE_FUNC_T *CLI_TYPES_GetGetRangeFunc (IN I32_T type);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 CLI_TYPES_GetGetValueFunc
 *
 * DESCRIPTION:
 *	 Get get_value functions of the specified argument type
 *
 * INPUT:
 *	 type -- type of the argument
 *
 * OUTPUT:
 *	 NA
 *
 * RETURN:
 *	 pointer of the get_value function
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-15 by foo -- Create
 *
*******************************************************************************/
CLI_TYPES_GET_VALUE_FUNC_T *CLI_TYPES_GetGetValueFunc (IN I32_T type);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 CLI_TYPES_GetGetHelpFunc.
 *
 * DESCRIPTION:
 *	 Get get_help functions of the specified argument type.
 *
 * INPUT:
 *	 type -- type of the argument.
 *
 * OUTPUT:
 *	 None.
 *
 * RETURN:
 *	 pointer of the get_value function.
 *
 * NOTES:
 *	 None.
 *
 * HISTORY:
 *   2010-Nov-05 by wangbin -- Create
 *
*******************************************************************************/
CLI_TYPES_GET_HELP_FUNC_T *CLI_TYPES_GetGetHelpFunc (IN I32_T type);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 CLI_TYPES_GetPrtRangeFunc
 *
 * DESCRIPTION:
 *	 Get prt_range function of the specified argument type
 *
 * INPUT:
 *	 type -- type of the argument
 *
 * OUTPUT:
 *	 NA
 *
 * RETURN:
 *	 pointer of the prt_range function
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-15 by foo -- Create
 *
*******************************************************************************/
CLI_TYPES_PRT_RANGE_FUNC_T *CLI_TYPES_GetPrtRangeFunc (IN I32_T type);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 CLI_TYPES_GetPrtValueFunc
 *
 * DESCRIPTION:
 *	 Get prt_value functions of the specified argument type
 *
 * INPUT:
 *	 type -- type of the argument
 *
 * OUTPUT:
 *	 NA
 *
 * RETURN:
 *	 pointer of the prt_value function
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-15 by foo -- Create
 *
*******************************************************************************/
CLI_TYPES_PRT_VALUE_FUNC_T *CLI_TYPES_GetPrtValueFunc (IN I32_T type);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 CLI_TYPES_GetValue
 *
 * DESCRIPTION:
 *	 Check and convert word in parameter of the user command to cli_value_t
 *
 * INPUT:
 *	 current -- current node in parameter tree
 *	 cmd -- word in user command
 *	 result -- word result already checked
 *
 * OUTPUT:
 *	 result -- if word in user command match word in parameter tree, the new
 *		word information will be added. else nothing changed
 *
 * RETURN:
 *	 TRUE -- success
 *	 FALSE -- failure
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-18 by wangbin -- Create
 *
*******************************************************************************/
BOOL_T CLI_TYPES_GetValue (
	IN CLI_PRIV_PARA_SYN_NODE_T * current,
	IN const I8_T * cmd,
	IN OUT CLI_PARA_CMD_TAB_LIST_T * result);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_TYPES_Get_CurrentHelp
 *
 * DESCRIPTION:
 *   Get specified word's help.
 *
 * INPUT:
 *	 current -- current node in parameter tree
 *	 cmd -- word in user command
 *	 result -- word result already checked
 *
 * OUTPUT:
 *	 result -- if word in user command match word in parameter tree, the new
 *		word information will be added. else nothing changed
 *
 * RETURN:
 *	 TRUE -- success
 *	 FALSE -- failure
 *
 * NOTES:
 *   None
 *
 * HISTORY:
 *   2010-Nov-08 by wangbin -- Create
 *
*******************************************************************************/
BOOL_T CLI_TYPES_Get_CurrentHelp (
	IN CLI_PRIV_PARA_SYN_NODE_T *current,
	IN const I8_T *cmd,
	IN OUT CLI_PARA_CMD_TAB_LIST_T *result);

/*******************************************************************************
 *
 * Func:   CLI_TYPES_Init
 * DESCRIPTION: Init resources for CLI Types
 * INPUT:  NA
 * OUTPUT: NA
 * RETURN: NA
 * NOTES:  NA
 * HISTORY:
 *	 2009-Feb-13 by wangbin -- Create
 *
*******************************************************************************/
void CLI_TYPES_Init(void);



#endif /* __BC_CLI_ALIAS_H__ */

/* End of file */
