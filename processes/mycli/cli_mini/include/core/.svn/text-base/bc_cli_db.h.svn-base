
#ifndef __BC_CLI_DB_H__
#define __BC_CLI_DB_H__

////////////////////////////////////////////////////////////////////////////////
// 								    										  //
// 							    头   文   件								  //
// 										    								  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_cli_type.h"
#include "bc_cli_priv.h"



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

/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 CLI_DB_Destory_Entry
 *
 * DESCRIPTION:
 *	 Destory the node: delete from tree and free the entry memory
 *
 * INPUT:
 *	path  : which tree (NULL for root tree)
 *	entry : destory which
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
 *
*******************************************************************************/
void CLI_DB_Destory_Entry(IN CLI_CMD_NODE_T *path, IN CLI_CMD_NODE_T *entry);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_DB_Find_Entry
 *
 * DESCRIPTION:
 *   Find/create the entry:
 *     Find the entry with given name,
 *     if !found && auto-create: allocate node memory and insert to tree, set new=TRUE
 *
 * INPUT:
 *   path        : find/insert on which tree (NULL for root tree)
 *   type        : the node type (only used for create)
 *   name        : entry name
 *   len         : length of name
 *   auto_create : TRUE  : if entry not exist, allocate memory and create it, 
 *                 FALSE : if entry not exist, don't create
 *   (use this speed up the insert: merge the find and create on tree)
 *
 * OUTPUT:
 *   is_new	 : TRUE  : not-exist and auto-create and create success
 *             FALSE : old entry
 *
 * RETURN:
 *   pointer : the entry pointer
 *   NULL	 : not found or create fail when auto=TRUE
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *
*******************************************************************************/
CLI_CMD_NODE_T *CLI_DB_Find_Entry(
	IN OUT CLI_CMD_NODE_T *path,
	IN CLI_NODE_TYPE_T type,
	IN const I8_T *name,
	IN UI32_T len,
	IN BOOL_T auto_create,
	OUT BOOL_T *is_new);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_DB_Get_FirstEntry
 *
 * DESCRIPTION:
 *   Get the first entry node from tree
 *
 * INPUT:
 *   path: get from which tree (NULL for root tree)
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   pointer : the node entry pointer
 *   NULL    : no entry found
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *
*******************************************************************************/
CLI_CMD_NODE_T *CLI_DB_Get_FirstEntry(IN CLI_CMD_NODE_T *path);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_DB_Get_NearEntryByName
 *
 * DESCRIPTION:
 *   Search the near node entry with given name (>=given name)
 *
 * INPUT:
 *   path : search which tree (NULL for root tree)
 *   name : search name
 *   len  : the length of name
 *   type : the type
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   pointer : the node entry pointer
 *   NULL    : no near node entry found (or the prefix not same with given name+len)
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *
*******************************************************************************/
CLI_CMD_NODE_T *CLI_DB_Get_NearEntryByName(
	IN CLI_CMD_NODE_T *path,
	IN const I8_T *name,
	IN UI32_T len,
	IN CLI_NODE_TYPE_T type);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_DB_Get_NextEntry
 *
 * DESCRIPTION:
 *   Get the next entry node with given entry node (direct get from tree, no compare)
 *
 * INPUT:
 *   current : current entry
 *   path    : get from which tree (NULL for root tree)
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   pointer : the node entry pointer
 *   NULL    : no next entry found
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *
*******************************************************************************/
CLI_CMD_NODE_T *CLI_DB_Get_NextEntry(
	IN CLI_CMD_NODE_T *path,
	IN CLI_CMD_NODE_T *current);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_DB_Init
 *
 * DESCRIPTION:
 *   Initialize the database
 *
 * INPUT:
 *   NA
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
void CLI_DB_Init(void);



#endif /* __BC_CLI_DB_H__ */

