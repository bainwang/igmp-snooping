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
 * FILE NAME  : cli2_hist.h
 * VERSION    : 1.0.0
 * DESCRIPTION:
 * NOTES:
 *
 * HISTORY:
 * -----------------------------------------------------------------------------
 * Version 1.0 -  2008-Dec-17 by wangbin
 * [NEW FEATURE]
 * <DESCRIPTION> Create
 *============================================================================*/

#ifndef __BC_CLI_HIST_H__
#define __BC_CLI_HIST_H__

#include "bc_cli_type.h"



/*******************************************************************************
 *
 * Func:   CLI_HIST_Create
 * DESCRIPTION: Create a new history handle, allocate resources for the history handle
 * INPUT:  hist_size -- the max item size of the history
 * OUTPUT: NA
 * RETURN: HANDLE -- handle of the new history
 * NOTES:  NA
 * HISTORY:
 *	 2008-Dec-17 by wangbin -- Create
 *
*******************************************************************************/
HANDLE_T CLI_HIST_Create(IN UI32_T hist_size);

/*******************************************************************************
 *
 * Func:   CLI_HIST_Destroy
 * DESCRIPTION: Destroy history handle, Release history resources
 * INPUT:  h_hist -- Handle of the history, it must be returned by CLI_HIST_Create
 * OUTPUT: NA
 * RETURN: NA
 * NOTES:  use h_hist after called CLI_HIST_Destroy will cause fatal errors
 * HISTORY:
 *	 2008-Dec-17 by wangbin -- Create
 *
*******************************************************************************/
void CLI_HIST_Destroy(IN HANDLE_T h_hist);

/*******************************************************************************
 *
 * Func:   CLI_HIST_GetPrevItem
 * DESCRIPTION: Get the previous history string
 * INPUT:  h_hist -- Handle of the history, it must be returned by CLI_HIST_Create
 * OUTPUT: NA
 * RETURN: NULL -- There is no previous history item, not NULL -- the address of the
 *			 previous history string
 * NOTES:  NA
 * HISTORY:
 *	 2008-Dec-17 by wangbin -- Create
 *
*******************************************************************************/
I8_T *CLI_HIST_GetPrevItem(IN HANDLE_T h_hist);

/*******************************************************************************
 *
 * Func:   CLI_HIST_GetCurItem
 * DESCRIPTION: Get the current history string
 * INPUT:  h_hist -- Handle of the history, it must be returned by CLI_HIST_Create
 * OUTPUT: NA
 * RETURN: NULL -- There is no history item, not NULL -- the address of the
 *			 current history string
 * NOTES:  NA
 * HISTORY:
 *	 2008-Dec-17 by wangbin -- Create
 *
*******************************************************************************/
I8_T *CLI_HIST_GetCurItem(IN HANDLE_T h_hist);

/*******************************************************************************
 *
 * Func:   CLI_HIST_GetNextItem
 * DESCRIPTION: Get the next history string
 * INPUT:  h_hist -- Handle of the history, it must be returned by CLI_HIST_Create
 * OUTPUT: NA
 * RETURN: NULL -- There is no next history item, not NULL -- the address of the
 *			 next history string
 * NOTES:  NA
 * HISTORY:
 *	 2008-Dec-17 by wangbin -- Create
 *
*******************************************************************************/
I8_T *CLI_HIST_GetNextItem(IN HANDLE_T h_hist);

/*******************************************************************************
 *
 * Func:   CLI_HIST_InsertItem
 * DESCRIPTION: add a new history to the end of history buffer, if history buffer
 *		 is full, the first history item will be removed from it.
 * INPUT:  h_hist -- Handle of the history, it must be returned by CLI_HIST_Create
 *		   buf -- The new history string
 * OUTPUT: NA
 * RETURN: NULL -- insert failed, not NULL -- The address of the new history item
 * NOTES:  ###
 * HISTORY:
 *	 2008-Dec-17 by wangbin -- Create
 *
*******************************************************************************/
I8_T *CLI_HIST_InsertItem(IN HANDLE_T h_hist, IN const I8_T *buf);

/*******************************************************************************
 *
 * Func:   CLI_HIST_SetSize
 * DESCRIPTION: Set a new size to history
 * INPUT:  h_hist -- Handle of the history, it must be returned by CLI_HIST_Create
 *		   new_size -- The new size of the history
 * OUTPUT: NA
 * RETURN: if (new_size == old_size) The history buffer not changed
 *		   if (new_size < old_size) The HANDLE not changed, but all history
 *			   data was cleared
 *		   if (new_size > old_size) The HANDLE changed to new, all history data
 *			   was cleared, and old resources was released. If memory allocate
 *			   failed, this function will return (HANDLE)0 in this case.
 *
 * NOTES:  NA
 * HISTORY:
 *	 2008-Dec-17 by wangbin -- Create
 *
*******************************************************************************/
HANDLE_T CLI_HIST_SetSize(IN HANDLE_T h_hist, IN I32_T new_size);

/*******************************************************************************
 *
 * Func:   CLI_HIST_ShowAllHist
 * DESCRIPTION: Show all histories
 * INPUT:  h_hist -- Handle of the history, it must be returned by CLI_HIST_Create
 *		   start -- TRUE(return the first item in the history buffer)
 *					FALSE (return the next item in the history buffer)
 * OUTPUT: NA
 * RETURN: not NULL -- the pointer of the history buffer, NULL -- There is no more
 *				 item in the history buffer, the operation may be stopped
 * USAGE:
 *		  {
 *			 I8_T *p;
 *
 *			 p = CLI_HIST_ShowAllHist (h_hist, TRUE);
 *			 printf ("%s\n", p);
 *			 while ((p = CLI_HIST_ShowAllHist (h_hist, FALSE)) != NULL)
 *			 {
 *				 printf ("%s\n", p);
 *			 }
 *		  }
 * HISTORY:
 *	 2008-Dec-17 by wangbin -- Create
 *
*******************************************************************************/
I8_T *CLI_HIST_ShowAllHist(IN HANDLE_T h_hist, IN BOOL_T start);

/**************************************************************************
FUNCTION NAME:
	CLI_HIST_SetState

DESCRIPTION:
	Set the history module state.

INPUT:
	h_hist	: Handle of the history, it must be returned by CLI_HIST_Create
	bEnable	: TRUE -> open the history function
			  FALSE -> close the history function

OUTPUT:
	None

RETURN:
	None

NOTES:

HISTORY:

**************************************************************************/
void CLI_HIST_SetState(
	IN HANDLE_T h_hist,
	IN BOOL_T bEnable);

/**************************************************************************
FUNCTION NAME:
	CLI_HIST_GetState

DESCRIPTION:
	Get the history module state.

INPUT:
	h_hist	: Handle of the history, it must be returned by CLI_HIST_Create

OUTPUT:
	None

RETURN:
	TRUE	: the history function is open
	FALSE	: the history function is closen

NOTES:

HISTORY:

**************************************************************************/
BOOL_T CLI_HIST_GetState(IN HANDLE_T h_hist);



#endif /* __BC_CLI_HIST_H__ */

