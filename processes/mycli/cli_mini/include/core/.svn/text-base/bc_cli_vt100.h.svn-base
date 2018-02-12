
#ifndef __BC_CLI_VT100_H__
#define __BC_CLI_VT100_H__

////////////////////////////////////////////////////////////////////////////////
// 								    										  //
// 							    头   文   件								  //
// 										    								  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_cli_type.h"
#include "bc_cli_term.h"



////////////////////////////////////////////////////////////////////////////////
//																			  //
//						结   构   体   宏   定   义							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#define VT_RESET_CURSOR_POSITION	"\033[1;1H"
#define VT_SAVE_CURSOR_POSITION 	"\0337"
#define VT_RESTORE_CURSOR_POSITION	"\0338"
#define VT_SET_CURSOR_AP_MODE		"\033[?1h"
#define VT_SET_CURSOR_NORMAL_MODE	"\033[?11"
#define VT_DELETE_ONE				"\033[1P"
#define VT_INSERT_MODE				"\033[4h"
#define VT_REPLASE_MODE 			"\033[41"
#define VT_RESET					"\033c"
#define VT_ORIGIN_RELATIVE			"\033[6h"
#define VT_ORIGIN_ABAOLUTE			"\033[61"
#define VT_BELL 					"\07"

#define VT_NULL   					'\0'			/* string ending indicator */

/*
 * The definition for Keystroke states
 */
#define  CLI_VT100_WAIT_FOR_KEYSTROKE		0x01
#define  CLI_VT100_WAIT_FOR_2ND_ESC_SEQ	0x02
#define  CLI_VT100_WAIT_FOR_AFTER_BRACKET	0x03
#define  CLI_VT100_WAIT_FOR_AFTER_O		0x04

#define  CLI_VT100_WAIT_FOR_AFTER_1   		0x05
#define  CLI_VT100_WAIT_FOR_AFTER_2	 	0x06
#define  CLI_VT100_WAIT_FOR_AFTER_3   		0x07
#define  CLI_VT100_WAIT_FOR_AFTER_4   		0x08
#define  CLI_VT100_WAIT_FOR_AFTER_5	  	0x09
#define  CLI_VT100_WAIT_FOR_AFTER_6  		0x0A

#define  CLI_VT100_WAIT_FOR_FUNC_KEY2		0x0F



////////////////////////////////////////////////////////////////////////////////
//																			  //
//								函	数	声	明								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

/**************************************************************************
FUNCTION NAME:
	CLI_VT100_Getc

DESCRIPTION:
	Get a input character and map the control sequence to predefined key

INPUT:
	hterm		: the handle for using terminal IO
	timeout 	: the timeout for geting input charcater

OUTPUT:
	NA

RETURN:
	-1			: IO closed
	-2			: timeout
	-3			: noaction(the input function is null)
	-4			: exit cmd
	-5			: the got value is wrong
	>0			: input character

NOTES:

HISTORY:

**************************************************************************/
I32_T CLI_VT100_Getc(IN CLI_TERMINAL_IO_T *hterm, IN I32_T timeout);

/**************************************************************************
FUNCTION NAME:
	CLI_VT100_Putc

DESCRIPTION:
	Output the character(some predefined control keys can be outputed by
	 the function such ascursor left right and so on)

INPUT:
	hterm		: the handle for using terminal IO
	rxCh		: the output character

OUTPUT:
	NA

RETURN:
	true		: output success
	false		: the output function is null or output false

NOTES:

HISTORY:

**************************************************************************/
BOOL_T CLI_VT100_Putc(IN CLI_TERMINAL_IO_T *hterm, IN I32_T rxCh);

/**************************************************************************
FUNCTION NAME:
	CLI_VT100_Erase

DESCRIPTION:
	Erase text on screen

INPUT:
	hterm		: the handle for using terminal IO
	mode		: the mode of erasing text
				CLI_SCREEN_FROM_CURSOR2END(1) earse from cursor to the end of screen
				CLI_SCREEN_FROM_BEGIN2CURSOR(2) earse from begin of screen to cursor
				CLI_SCREEN_COMPLETE(3) earse the whole screen
				CLI_LINE_FROM_CURSOR2END(4) earse from cursor to the end of line
				CLI_LINE_FROM_BEGIN2CURSOR(5) earse from begin of line to cursor
				CLI_LINE_COMPLETE(6) earse the line which cursor stay

OUTPUT:
	NA

RETURN:
	true		: earse success
	false		: the earse function is null or earse false

NOTES:

HISTORY:

**************************************************************************/
BOOL_T CLI_VT100_Erase(IN CLI_TERMINAL_IO_T *hterm, IN CLI_VIO_ERASE_T mode);



#endif /* __BC_CLI_VT100_H__ */

