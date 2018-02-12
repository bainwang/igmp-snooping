
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



#endif /* __BC_CLI_VT100_H__ */

