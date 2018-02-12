/*==============================================================================
 * FILE NAME  : bc_cli_parse.h
 * VERSION    : 1.0.0
 * DESCRIPTION: 
 * NOTES: 
 * 
 * HISTORY:
 * -----------------------------------------------------------------------------
 * Version 1.0 -- 2009-Aug-03 by bain.wang@outlook.com
 * [NEW FEATURE]
 * <DESCRIPTION> Create
 *============================================================================*/

#ifndef __BC_CLI_PARSE_H__
#define __BC_CLI_PARSE_H__

#include "bc_cli_type.h"



////////////////////////////////////////////////////////////////////////////////
//																			  //
//								头   文   件								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////



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
 *   2009-Aug-03 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
BOOL_T CLI_PARSE_Preprocess_Syncmd (
	IN const I8_T *cmd_desc,
	IN OUT I8_T **view,
	IN OUT I8_T **cmd,
	IN OUT I8_T **para);



#endif /* __BC_CLI_PARSE_H__ */

/* End of file */
