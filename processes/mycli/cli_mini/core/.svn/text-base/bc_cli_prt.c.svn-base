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
 * FILE NAME  : bc_cli_prt.c
 * VERSION    : 1.0.0
 * DESCRIPTION:
 * NOTES:
 *
 * HISTORY:
 * -----------------------------------------------------------------------------
 * Version 1.0 -- 2009-Mar-25 by wangbin
 * [NEW FEATURE]
 * <DESCRIPTION> Create
 *============================================================================*/

////////////////////////////////////////////////////////////////////////////////
// 																			  //
// 							 	头   文   件								  //
// 																			  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_cli_type.h"

#include "bc_cli_vkey.h"
#include "bc_cli_prt.h"
#include "bc_cli_vio.h"
#include "bc_cli_sesn.h"
#include "bc_cli_acc.h"



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



////////////////////////////////////////////////////////////////////////////////
//																			  //
//							全 局 变 量 定 义								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////



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

/**************************************************************************
FUNCTION NAME:
    CLI_PRT_GetPrtState

DESCRIPTION:
    Get the state of print.

INPUT:
    sessionID   : the mapped session ID

OUTPUT:
    NA

RETURN:
    TURE        : page stop, need exit print
    FALSE       : continue print

NOTES:

HISTORY:

**************************************************************************/
BOOL_T CLI_PRT_GetPrtState(IN const I32_T sessionID)
{
	/* note: if execute bat configuration check print */
	HANDLE_T 					hvio;
	CLI_ACC_CURSOR_STATUS_T 	cursor_status;
	BOOL_T 						page_stop;

	hvio = CLI_API_GetHvioFromSession(sessionID);

	page_stop = CLI_ACC_GetPageStopStatus(sessionID);
	CLI_ACC_GetCursorStatus (sessionID, &cursor_status);

	if (cursor_status.page_action == CLI_PAGE_EXIT)
	{
		return TRUE;
	}

	if (page_stop == FALSE || cursor_status.page_action == CLI_PAGE_ALL)
	{
		switch (CLI_VIO_Getc(hvio, 20))
		{
		case CLI_VKEY_ESC:
		case CLI_VKEY_CTRL_C:
		case CLI_VKEY_LOWERCASE_Q:
		case CLI_VKEY_IO_NOTIFY:
			return TRUE;

		default:
			return FALSE;
		}
	}

	return FALSE;
}



/* End of file */

