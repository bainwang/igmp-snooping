/*******************************************************************************
 * Copyright(C) 2011, Kingtype Networks Corporation. All rights reserved.
 *
 * This is unpublished proprietary source code of Kingtype Networks Corporation.
 *
 * The copyright notice above does not evidence any actual or intended
 *	publication of such source code.
*******************************************************************************/
/*==============================================================================
 * MODULE NAME: Banner
 * FILE NAME  : bc_cli_bnr_stk.h
 * VERSION    : 1.0.0
 * DESCRIPTION: Stacking message deal
 * NOTES:
 *
 * HISTORY:
 * -----------------------------------------------------------------------------
 * Version 1.0
 * [NEW FEATURE]
 * <DESCRIPTION>
 *============================================================================*/

#ifndef __BC_CLI_BNR_STK_H__
#define __BC_CLI_BNR_STK_H__

////////////////////////////////////////////////////////////////////////////////
// 								    										  //
// 							    头   文   件								  //
// 										    								  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_cli_bnr.h"



#if USER_PROMPT_INCLUDED

////////////////////////////////////////////////////////////////////////////////
//																			  //
//						结   构   体   宏   定   义							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#define	CLI_BNR_STK_MSG_UPDATE_PROMPT_BANNER  		101



////////////////////////////////////////////////////////////////////////////////
//																			  //
//								函	数	声	明								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

/*-----------------------------------------------------------------------------
 * Function   : void CLI_BNR_STK_Send_UpdatePromptBannerMSG(BANNER_PRMPT_BANNER_T *info)
 * Purpose    : Send update prompt or banner system message
 * Parameters :
 *    Input   : msg info
 *    Output  : None
 * Returns    : None
 * Note       :
 * Programmer :
 *-----------------------------------------------------------------------------
 */
void CLI_BNR_STK_Send_UpdatePromptBannerMSG(BANNER_PRMPT_BANNER_T *info);

/*-----------------------------------------------------------------------------
 * Function   : void CLI_BNR_STK_ResetDefault(void)
 * Purpose    : Command reset config or reset system using
 * Parameters :
 *    Input   : None
 *    Output  : None
 * Returns    : None
 * Note       :
 * Programmer :
 *-----------------------------------------------------------------------------
 */
void CLI_BNR_STK_ResetDefault(void);

/*------------------------------------------------------------------------
 * Function   : void CLI_BNR_STK_Init_Stack()
 * Purpose    :
 * Parameters :
 *    Input   :
 *    Output  :
 * Returns    :
 *------------------------------------------------------------------------
 */
void CLI_BNR_STK_Init_Stack(void);



#endif

#endif /* __BC_CLI_BNR_STK_H__ */

