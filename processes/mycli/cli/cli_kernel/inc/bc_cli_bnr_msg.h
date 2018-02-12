
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
 * bain.wang@outlook.com ,2011/06
 * Newly add
 *============================================================================*/

#ifndef  __BC_CLI_BNR_MSG_H__
#define  __BC_CLI_BNR_MSG_H__

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
//								函	数	声	明								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////



#endif /* __BC_CLI_BNR_MSG_H__ */

