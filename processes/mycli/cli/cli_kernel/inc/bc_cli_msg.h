/*==============================================================================
 * FILE NAME  : bc_cli_msg.h
 * VERSION    : 1.0.0
 * DESCRIPTION:
 * NOTES:
 *
 * HISTORY:
 * -----------------------------------------------------------------------------
 * Version 1.0 -  2009-Feb-13 by bain.wang@outlook.com
 * [NEW FEATURE]
 * <DESCRIPTION> Create
 *============================================================================*/

#ifndef __BC_CLI_MSG_H__
#define __BC_CLI_MSG_H__

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								头   文   件								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_cli_type.h"



////////////////////////////////////////////////////////////////////////////////
//																			  //
//						结   构   体   宏   定   义							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#define UTL_MISC_ERR_MEMORY_OVERFLOW 				"Memory overflow!\n"
#define UTL_MISC_ERR_POINTER_NULL 					"Pointer is NULL!\n"
#define UTL_MISC_ERR_PARA 							"Parameter error\n"
#define UTL_MISC_ERR_PARA_REGISTER_CONFLICT 		"Parameter register conflict\n"
#define UTL_MISC_ERR_PARA_TYPES_NOTDEFINED 			"Basic types not defined\n"
#define UTL_MISC_ERR_TYPES_PRIMITIVE_REPETITION 	"Primitive type repetition\n"
#define UTL_MISC_ERR_SYS_CFG_FILE_NUM_IS_SMALL 		"CLI_CFG_FILE_MAX_NUM is too small\n"
#define UTL_MISC_ERR_TOO_MANY_ENUMLIST 				"Too many enumlist!\n"
#define UTL_MISC_ERR_REDEFINE_ENUMLIST 				"Enumlist already registered\n"
#define CLI_PUPROSE_HELP							"Use to display the hele information. "



/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 CLI_MSG_PrtErrMsg
 *
 * DESCRIPTION:
 *	 Print error message and position in CLI Kernel
 *
 * INPUT:
 *	 fmt -- One of the macro defined in this file should be used to specify the
 *		error messages.
 *
 * OUTPUT:
 *	 NA
 *
 * RETURN:
 *	 NA
 *
 * NOTES:
 *	 A message will be outputed to RS232 terminal (if any, otherwise nothing)
 *	will happened.
 *
 * HISTORY:
 *	 2009-Mar-09 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
#define CLI_MSG_PrtErrMsg(msg...) CLI_MSG_ERR(l_mdl_id, msg)



////////////////////////////////////////////////////////////////////////////////
//																			  //
//								函	数	声	明								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////



#endif /* __BC_CLI_MSG_H__ */

