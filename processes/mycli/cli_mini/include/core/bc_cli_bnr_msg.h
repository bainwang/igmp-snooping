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
 * FILE NAME  : bc_cli_bnr_msg.h
 * VERSION    : 1.0.0
 * DESCRIPTION: command prompt or parameters prompt for banner configure 
 * NOTES:
 *
 * HISTORY:
 * -----------------------------------------------------------------------------
 * Version 1.0
 * wangbin ,2011/06
 * Newly add
 *============================================================================*/

#ifndef  __BC_CLI_BNR_MSG_H__
#define  __BC_CLI_BNR_MSG_H__

////////////////////////////////////////////////////////////////////////////////
// 								    										  //
// 							    ͷ   ��   ��								  //
// 										    								  //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//																			  //
//						��   ��   ��   ��   ��   ��							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

/* Banner parameter help message */
#define CLI_BNR_MSG_SET_LOGIN  			"#LINE  c banner-text c, where 'c' is a delimiting character#"
#define CLI_BNR_MSG_SET_PROMPTP 			"#Prompt string#"
#define CLI_BNR_MSG_BANNER_HELP  			"#Define a login banner#"

/* Command help message */
#define CLI_BNR_MSG_SET_LOGIN_HELP  		"Set login banner"
#define CLI_BNR_MSG_SHOW_LOGIN_HELP 		"Show login banner"
#define CLI_BNR_MSG_PROMPT_HELP  			"Set system's prompt"

/* Running prompt message */
#define CLI_BNR_MSG_SET_LOGIN_PMT  		"LINE  c banner-text c, where 'c' is a delimiting character"



////////////////////////////////////////////////////////////////////////////////
//																			  //
//								��	��	��	��								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////



#endif /* __BC_CLI_BNR_MSG_H__ */

