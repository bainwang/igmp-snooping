/*******************************************************************

COPYRIGHT:
	Copyright (c) 2005-2011  Kingtype Corporation   All rights reserved.
    This is unpublished proprietary source code of Kingtype Corporation.
	The copyright notice above does not evidence any actual or intended
	publication of such source code.

MODULE NAME:
	CLI command belong to CLI kernel

FILE NAME:
 	bc_cli_sys_cmd.h

VERSION:
	2.00

DESCRIPTION:
 	CLI command belong to CLI kernel

NOTES:
   	NA

HISTORY:
	Ver2.00:	2011.3.7 wangbin new added

********************************************************************/

#ifndef __BC_CLI_SYS_CMD_H__
#define __BC_CLI_SYS_CMD_H__

////////////////////////////////////////////////////////////////////////////////
// 								    										  //
// 							    头   文   件								  //
// 										    								  //
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

/*------------------------------------------------------------------------
 * Function   : cli_bnr_cmd_show_banner
 * Description: Display the login banner
 * Parameters : const int sessionID, cli_value_t *ptrCliValue, void *ptrUserData
 * Input      :
 * Output     :
 * Returns    :      
 * writer     : wangbin, 2011-06-05
 *------------------------------------------------------------------------
*/
I32_T cli_bnr_cmd_show_banner
    (
    IN const UI32_T sessionID,
    IN cli_value_t *ptrCliValue,
    IN void *ptrUserData
    );

/**************************************************************************
FUNCTION NAME:
	bc_cli_sys_cmd_reg

DESCRIPTION:
	Register CLI kernel basic commands.

INPUT:
	NA

OUTPUT:
	NA

RETURN:
	NA

NOTES:

HISTORY:

**************************************************************************/
void bc_cli_sys_cmd_reg(void);



#endif /* __BC_CLI_SYS_CMD_H__ */

