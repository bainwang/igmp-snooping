/*******************************************************************************
 * Copyright(C) 2008, Kingtype Networks Corporation. All rights reserved.
 *
 * This is unpublished proprietary source code of Kingtype Networks Corporation.
 *
 * The copyright notice above does not evidence any actual or intended 
 *  publication of such source code.
*******************************************************************************/
/*==============================================================================
 * MODULE NAME: Kingtype CLI, bc_cli
 * FILE NAME  : bc_cli_chs.h
 * VERSION    : 1.0.0
 * DESCRIPTION: 
 * NOTES: 
 * 
 * HISTORY:
 * -----------------------------------------------------------------------------
 * Version 1.0 -- 2010-May-08 by wangbin
 * [NEW FEATURE]
 * <DESCRIPTION> Create
 *============================================================================*/

#ifndef __BC_CLI_CHS_H__
#define __BC_CLI_CHS_H__

////////////////////////////////////////////////////////////////////////////////
// 								    										  //
// 							    头   文   件								  //
// 										    								  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_cli_type.h"



////////////////////////////////////////////////////////////////////////////////
//																			  //
//						结   构   体   宏   定   义							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

typedef enum 
{
	CLI_CHARSET_ASCII 	= 1,
	CLI_CHARSET_GB2312,
	CLI_CHARSET_GBK
} CLI_CHARSET_T;

#define CLI_DEFAULT_CHARSET 	CLI_CHARSET_GBK



////////////////////////////////////////////////////////////////////////////////
//																			  //
//								函	数	声	明								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

BOOL_T 	CLI_CHARSET_Is_AsciiChar (UI8_T ch);
BOOL_T 	CLI_CHARSET_Is_Gb2312FirstChar (UI8_T ch);
BOOL_T 	CLI_CHARSET_Is_Gb2312SecondChar (UI8_T ch);
BOOL_T 	CLI_CHARSET_Is_Gb2312Char (UI8_T ch1, UI8_T ch2);
BOOL_T 	CLI_CHARSET_Is_GbkFirstChar (UI8_T ch);
BOOL_T 	CLI_CHARSET_Is_GbkSecondChar (UI8_T ch);
BOOL_T 	CLI_CHARSET_Is_GbkChar (UI8_T ch1, UI8_T ch2);
I32_T 	CLI_CHARSET_Get_PrevCharSize(I32_T charset, UI8_T *buf, I32_T idx);
BOOL_T 	CLI_CHARSET_Is_CursorInsideChar(I32_T charset, UI8_T *buf, I32_T idx);
I32_T 	CLI_CHARSET_Get_NextCharSize(I32_T charset, UI8_T *buf, I32_T idx);



#endif /* __BC_CLI_CHS_H__ */

/* End of file */
