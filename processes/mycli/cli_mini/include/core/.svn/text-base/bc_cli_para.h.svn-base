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
 * FILE NAME  : bc_cli_para.h
 * VERSION    : 1.0.0
 * DESCRIPTION:
 * NOTES:
 *
 * HISTORY:
 * -----------------------------------------------------------------------------
 * Version 1.0 -  2008-Nov-28 by wangbin
 * [NEW FEATURE]
 * <DESCRIPTION> Create
 *============================================================================*/

#ifndef __BC_CLI_PARA_H__
#define __BC_CLI_PARA_H__

////////////////////////////////////////////////////////////////////////////////
// 								    										  //
// 							    头   文   件								  //
// 										    								  //
////////////////////////////////////////////////////////////////////////////////

#include <bc_cli_priv.h>
#include <bc_cli_misc.h>



////////////////////////////////////////////////////////////////////////////////
//																			  //
//						结   构   体   宏   定   义							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#define CLI_PARA_CMD_TAB_LIST 			200
#define CLI_PARA_CMD_MAX_POSIBLE_NODE 	50

typedef struct
{
	CLI_PRIV_PARA_SYN_NODE_T *list[CLI_PARA_CMD_TAB_LIST];
	//CLI_PRIV_PARA_SYN_NODE_T *cur_posible_node[CLI_PARA_CMD_MAX_POSIBLE_NODE];
	cli_value_t head;
	cli_value_t *lastword;
	cli_value_t *tail; 		// if tail == NULL then not get value, else get it
	I32_T count;				// count of the node list
	I32_T save_count;
	I32_T cur_posible_node_count;
	BOOL_T most_match;
	BOOL_T finish; /* TRUE: command may be finished; FALSE: command may not be finished */
	I32_T error_pos;			// error pos of the cmd para
} CLI_PARA_CMD_TAB_LIST_T;

typedef struct
{
	I8_T *name; 				// for types which have a name, it points to the name address.
	I32_T len;					// length of the name
	UI32_T num_of_child;		// how many child of this node
	I32_T lparam;				// first parameter for this type
	I32_T rparam;				// second parameter for this type
	CLI_PRIMITIVE_SYNTAX_T type; // type of the word
	I32_T idx_of_sibling;		// index of the sibling (start from 1)
} CLI_PARA_LEX_NODE_T;


#define CLI_PARA_GET_CUR_WORDLIST 	0
#define CLI_PARA_GET_NEXT_WORDLIST 1
#define CLI_PARA_GET_VALUE 		2



////////////////////////////////////////////////////////////////////////////////
//																			  //
//								函	数	声	明								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 CLI_Para_Check_FirstUnitIsStringLike
 *
 * DESCRIPTION:
 *	 Check the first word of parameter is StringLike or not.
 *
 * INPUT:
 *	 root -- start node of the parameter tree.
 *
 * OUTPUT:
 *	 *count -- Count of the string like nodes in the first word.
 *
 * RETURN:
 *	 NA
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-20 by wangbin -- Create
 *
*******************************************************************************/
void CLI_Para_Check_FirstUnitIsStringLike(
	IN const CLI_PRIV_PARA_SYN_NODE_T * root,
	OUT I32_T *count);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 CLI_PARA_Destroy
 *
 * DESCRIPTION:
 *	 Release resources allocated by CLI para
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
 *	 2009-Mar-20 by wangbin -- Create
 *
*******************************************************************************/
void CLI_PARA_Destroy(void);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 CLI_PARA_Free_ValueList
 *
 * DESCRIPTION:
 *	 Free memory allocated in cli_value_t list
 *
 * INPUT:
 *	 value -- pointer of the value list
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
 *	 2009-Mar-23 by wangbin -- Create
 *
*******************************************************************************/
void CLI_PARA_Free_ValueList(cli_value_t * value);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 CLI_PARA_Get_Value
 *
 * DESCRIPTION:
 *	 Check parameter in a user command and get it's value
 *
 * INPUT:
 *	 pwords -- word list in the user command.
 *	 root -- parameter tree
 *	 result -- point to the result buffer
 *	 flags -- CLI_PARA_GET_VALUE
 *
 * OUTPUT:
 *	 result -- list of the cli_value_t
 *
 * RETURN:
 *	 < 0 -- failure
 *	 = 0 -- success
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-23 by wangbin -- Create
 *
*******************************************************************************/
I32_T CLI_PARA_Get_Value(
	IN CLI_PRIV_USRCMD_WORDLIST_T *pwords,
	IN CLI_PRIV_PARA_SYN_NODE_T *root,
	IN OUT cli_value_t **value,
	OUT I32_T *error_position);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 bc_cli_para_init
 *
 * DESCRIPTION:
 *	 Init resources for CLI para
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
 *	 2009-Mar-20 by wangbin -- Create
 *
*******************************************************************************/
I32_T bc_cli_para_init(void);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 CLI_PARA_Get_Help
 *
 * DESCRIPTION:
 *	 Get word list match the last word in user command or all the probably
 *		word after the user command for the help system
 *
 * INPUT:
 *	 pwords -- word list in the user command.
 *	 root -- parameter tree
 *	 result -- point to the result buffer
 *	 flags -- CLI_PARA_GET_CUR_WORDLIST, CLI_PARA_GET_NEXT_WORDLIST
 *
 * OUTPUT:
 *	 result -- word list
 *
 * RETURN:
 *	 < 0 -- failure
 *	 = 0 -- success
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-23 by wangbin -- Create
 *
*******************************************************************************/
I32_T CLI_PARA_Get_Help(
	IN CLI_PRIV_USRCMD_WORDLIST_T *pwords,
	IN CLI_PRIV_PARA_SYN_NODE_T * root,
	IN OUT CLI_PRIV_HELPLIST_T *helplist,
	IN I32_T flags);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 CLI_PARA_Parse_SyncmdPara
 *
 * DESCRIPTION:
 *	 Check the parameter string in syntax command is correct or not, if it is
 *		 correct, register it.
 *
 * INPUT:
 *	 str -- parameter string in syntax command
 *	 pp_syn -- address of the pointer to get the result parameter tree
 *
 * OUTPUT:
 *	 *pp_syn -- pointer of the parameter tree.
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
BOOL_T CLI_PARA_Parse_SyncmdPara (
	IN const I8_T *str,
	IN OUT CLI_PRIV_PARA_SYN_NODE_T **pp_syn);

/**************************************************************************
FUNCTION NAME:
	CLI_PARA_Generate_ValueList

DESCRIPTION:
	Generate value list by input value list(alloc memory and generate).

INPUT:
	node_param	: input value list

OUTPUT:
	None

RETURN:
	generated value list

NOTES:

HISTORY:
	Creat by wangbin 2011.3.2

**************************************************************************/
cli_value_t *CLI_PARA_Generate_ValueList(IN cli_value_t *node_param);



#endif /* __BC_CLI_PARA_H__ */

