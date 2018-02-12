/*==============================================================================
 * FILE NAME  : bc_cli_pseudo.h
 * VERSION    : 1.0.0
 * DESCRIPTION: 
 * NOTES: 
 * 
 * HISTORY:
 * -----------------------------------------------------------------------------
 * Version 1.0 -- 2009-Jun-01 by bain.wang@outlook.com
 * [NEW FEATURE]
 * <DESCRIPTION> Create
 *============================================================================*/

#ifndef __BC_CLI_PSEUDO_H__
#define __BC_CLI_PSEUDO_H__

////////////////////////////////////////////////////////////////////////////////
// 																			  //
// 							 	ͷ   ��   ��								  //
// 																			  //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//																			  //
//						��   ��   ��   ��   ��   ��							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//																			  //
//								��	��	��	��								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_PSEUDO_Execute_MiltiUserCmdWithoutOutput
 *
 * DESCRIPTION:
 *   Execute multiple user command. each command must end with a "\r\n".
 *   Commands in buffer are seperated by "\r\n"
 *
 * INPUT:
 *   str -- commands string
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
 *   2009-Jun-01 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
void CLI_PSEUDO_Execute_MiltiUserCmdWithoutOutput(IN void *str);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   cli_pseudo_task
 *
 * DESCRIPTION:
 *   Main function for the cli2 pseudo terminal task
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
 *   2009-Jun-01 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
bc_boolean cli_pseudo_task (void *arg);



#endif /* __BC_CLI_PSEUDO_H__ */

/* End of file */
