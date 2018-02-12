/************************************************************************
 * Copyright(c) 1995 Kingtype networks Corporation. All rights reserved.
 *
 * This is unpublished proprietary source code of Kingtype networks Corporation.
 *
 * The copyright notice above does not evidence any actual or intended
 * publication of such source code
 ************************************************************************
 */

/*========================================================================
 * Mdule Name: Vt100 header file
 *
 * Module Function: Generates VT100 Command code to form the Screen Layout
 * Author   Name: Ray Hsu
 * Create   Date: 12/05/2000
 *========================================================================
 */

#ifndef __VT_100_H__
#define __VT_100_H__

//#include    <runtime/runtime.h>
#include "bc_cli_type.h"



#define VT_RESET_CURSOR_POSITION    "\033[1;1H"
#define VT_SAVE_CURSOR_POSITION     "\0337"
#define VT_RESTORE_CURSOR_POSITION  "\0338"
#define VT_SET_CURSOR_AP_MODE       "\033[?1h"
#define VT_SET_CURSOR_NORMAL_MODE   "\033[?11"
#define VT_DELETE_ONE               "\033[1P"
#define VT_INSERT_MODE              "\033[4h"
#define VT_REPLASE_MODE             "\033[41"
#define VT_RESET                    "\033c"
#define VT_ORIGIN_RELATIVE          "\033[6h"
#define VT_ORIGIN_ABAOLUTE          "\033[61"
#define VT_BELL                     "\07"

/*
 * VT100 Character Set
 */
#define  VT_ASCII_CHAR_SET 'B'
#define  VT_DEC_GRAPHIC    '0'

#define  VT_ZERO   '0' /* char '0' symbol */
#define  VT_NULL   '\0' /* string ending indicator */
#define  VT_DIFF   ('A' - '9' - 1) /* used to convert the hex symbols 'A' ~ 'F' */

/*
 * VT100 DEC Special Graphic : box line ASCII code
 */
#define  VT_BOX_LEFTUP     0x6c  /* ?*/
#define  VT_BOX_RIGHTUP    0x6b  /* ?*/
#define  VT_BOX_LEFTDOWN   0x6d  /* ?*/
#define  VT_BOX_RIGHTDOWN  0x6a  /* ?*/
#define  VT_BOX_LEFT       0x78  /* ?*/
#define  VT_BOX_RIGHT      0x78  /* ?*/
#define  VT_BOX_UP         0x71  /* ?*/
#define  VT_BOX_DOWN       0x71  /* ?*/
#define  VT_BOX_CROSS      0x6e  /* ?*/
#define  VT_BOX_LEFT_T     0x74  /* ?*/
#define  VT_BOX_RIGHT_T    0x75  /* ?*/


/*
 * ASCII code : keystroke
 */
#define  VT_CTRL_C                  0x03
#define  VT_CTRL_D                  0x04
#define  VT_BACKSPACE               0x08
#define  VT_BACK_TAB                0x08
#define  VT_TAB                     0x09
#define  VT_LF                      0x0a
#define  VT_CTRL_J                  0x0a
#define  VT_CTRL_ENTER              0x0a
#define  VT_CTRL_K		    		0x0b
#define  VT_FUN4                    0x0c
#define  VT_CTRL_L					0x0c
#define  VT_CR                      0x0d
#define  VT_CTRL_P                  0x10
#define  VT_CTRL_N                  0x0e
#define  VT_CTRL_R                  0x12
#define  VT_CTRL_S                  0x13
#define  VT_CTRL_T                  0x14
#define  VT_CTRL_X                  0x18
#define  VT_CTRL_Z                  0x1a
#define  VT_SAVE_SETTINGS           0x17  //now is W
#define  VT_GOTO_LAST_FIELD         0x19  //now is Y
#define  VT_ESC                     0x1b
#define  VT_SPACE                   0x20
#define  VT_BRACKET                 0x5b
#define  VT_DEL                     0x7f

#define  VT_UPPERCASE_B             0x42
#define  VT_LOWERCASE_B             0x62
#define  VT_UPPERCASE_C             0x43
#define  VT_LOWERCASE_C             0x63
#define  VT_UPPERCASE_E             0x45
#define  VT_LOWERCASE_E             0x65
#define  VT_UPPERCASE_N             0x4e
#define  VT_LOWERCASE_N             0x6e
#define  VT_UPPERCASE_P             0x50
#define  VT_LOWERCASE_P             0x70
#define  VT_LOWERCASE_Q             0x71
#define  VT_UPPERCASE_Y             0x59
#define  VT_LOWERCASE_Y             0x79

/*modify by peterson zhou at 2008-6-11,because previous funtion key(0x81~0x94) conflict with shit-jis coding in japanese*/
/* modify to 2^31 to avoid the valule overflow than signed int */

#define VT_FUNC_EDIT_KEY_BASE (0x7FFFFD00L)

/* Function Keys
ESC[11~		F1
ESC[12~		F2
ESC[13~		F3
ESC[14~		F4
ESC[16~		F5
ESC[17~		F6
ESC[18~		F7
ESC[19~		F8

ESC[20~		F9
ESC[21~		F10
ESC[23~		F11
ESC[24~		F12
*/
#define  VT_F1				( VT_FUNC_EDIT_KEY_BASE + 11L )
#define  VT_F2				( VT_FUNC_EDIT_KEY_BASE + 12L )
#define  VT_F3				( VT_FUNC_EDIT_KEY_BASE + 13L )
#define  VT_F4                      	( VT_FUNC_EDIT_KEY_BASE + 14L )

#define  VT_F5                      	( VT_FUNC_EDIT_KEY_BASE + 15L )
#define  VT_F6                      	( VT_FUNC_EDIT_KEY_BASE + 17L )
#define  VT_F7                      	( VT_FUNC_EDIT_KEY_BASE + 18L )
#define  VT_F8                      	( VT_FUNC_EDIT_KEY_BASE + 19L )

#define  VT_F9                      	( VT_FUNC_EDIT_KEY_BASE + 20L )
#define  VT_F10                      	( VT_FUNC_EDIT_KEY_BASE + 21L )
#define  VT_F11                      	( VT_FUNC_EDIT_KEY_BASE + 23L )
#define  VT_F12                      	( VT_FUNC_EDIT_KEY_BASE + 24L )

/* Edit keys */
#define  VT_INSERT                 	( VT_FUNC_EDIT_KEY_BASE + 0x01L )
#define  VT_HOME                    	( VT_FUNC_EDIT_KEY_BASE + 0x02L )
#define  VT_PAGEUP                	( VT_FUNC_EDIT_KEY_BASE + 0x03L )
#define  VT_DELETE                 	( VT_FUNC_EDIT_KEY_BASE + 0x04L )
#define  VT_END                      	( VT_FUNC_EDIT_KEY_BASE + 0x05L )
#define  VT_PAGEDOWN           	( VT_FUNC_EDIT_KEY_BASE + 0x06L )

/*
 * The definition of Cursor movement
 */
#define  VT_LEFT                    	( VT_FUNC_EDIT_KEY_BASE + 0x44L )
#define  VT_RIGHT                  	( VT_FUNC_EDIT_KEY_BASE + 0x43L )
#define  VT_UP                        	( VT_FUNC_EDIT_KEY_BASE + 0x41L )
#define  VT_DOWN                   	( VT_FUNC_EDIT_KEY_BASE + 0x42L )

/*
 * The definition for I/O event
 */
#define VT_IO_CLOSED  			-1/* This parameter also need define as following. */
/*this value should be same as UTL_COM_CONSOLE_TIMEOUT utl_com.h, define as following to avoid duplicate with JAPAN code. */
#define VT_IO_TIMEOUT  			-1282  /* 0xFFFFFAFE */
#define VT_IO_NOACTION 			-1283  /* 0xFFFFFAFD */
#define VT_IO_EXITCMD  			-1284  /* 0xFFFFFAFC */
#define VT_IO_NOTIFY			-1285 /* 0xFFFFFAFB */
#if MEM_COMPRESS_INCLUDED
#define VT_IO_EXITBATCONFIG	-10 /* this value is used for exit batch config and not close the session */
#endif

/*
 * The definition for Keystroke states
 */
#define  VT_WAIT_FOR_KEYSTROKE      0x01
#define  VT_WAIT_FOR_2ND_ESC_SEQ    0x02
#define  VT_WAIT_FOR_AFTER_BRACKET  0x03
#define  VT_WAIT_FOR_AFTER_O        0x04

#define  VT_WAIT_FOR_7e_AFTER_INSERT   0x05
#define  VT_WAIT_FOR_7e_AFTER_HOME     0x06
#define  VT_WAIT_FOR_7e_AFTER_PAGEUP   0x07
#define  VT_WAIT_FOR_7e_AFTER_DELETE   0x08
#define  VT_WAIT_FOR_7e_AFTER_END      0x09
#define  VT_WAIT_FOR_7e_AFTER_PAGEDOWN 0x0A

#define  VT_WAIT_FOR_7E_FOR_FUNC_KEY2 0x0F

/* define erase mode */
typedef enum
{
	VT_FROM_CURSOR2END_ERASE = 0,
	VT_FROM_BEGIN2CURSOR_ERASE = 1,
	VT_COMPLETE_ERASE = 2
} VT_ERASE_MODE_T;

/* define text attributes */
typedef enum
{
	VT_TEXT_NORMAL = 0,
	VT_TEXT_HIGH_INTENSITY = 1,
	VT_TEXT_BLINK = 5,
	VT_TEXT_INVERSE = 7,
	VT_TEXT_CONCEALED = 8
} VT_TEXT_MODE_T;
#if 0
/**************************************************************************
FUNCTION NAME:
	VT_100_Move_CursorLeft

DESCRIPTION:
	Move Cursor backward by the specified number of columns without changing lines. 
	If the cursor is alredy in the leftmost column. VT100 ignores this sequence.

INPUT:
	sessionID	: cli session ID
	columns		: move coursor n columns left.

OUTPUT:
	None

RETURN:
	None

NOTES:

HISTORY:
	Creat by wangbin 2009.11.18

**************************************************************************/
void VT_100_Move_CursorLeft(IN I32_T sessionID, IN I32_T columns);

/**************************************************************************
FUNCTION NAME:
	VT_100_Move_CursorRight

DESCRIPTION:
	Move Cursor forward by the specified number of columns without changing lines. 
	If the cursor is alredy in the rightmost column. VT100 ignores this sequence.

INPUT:
	sessionID	: cli session ID
	columns		: move coursor n columns right.

OUTPUT:
	None

RETURN:
	None

NOTES:

HISTORY:
	Creat by wangbin 2009.11.18

**************************************************************************/
void VT_100_Move_CursorRight(IN I32_T sessionID, IN I32_T columns);
#endif
/**************************************************************************
FUNCTION NAME:
	VT_100_Move_CursorUp

DESCRIPTION:
	Move Cursor up by the specified number of columns.

INPUT:
	sessionID	: cli session ID
	columns		: move coursor n columns up.

OUTPUT:
	None

RETURN:
	None

NOTES:

HISTORY:
	Creat by wangbin 2009.11.18

**************************************************************************/
void VT_100_Move_CursorUp(IN I32_T sessionID, IN I32_T columns);

/**************************************************************************
FUNCTION NAME:
	VT_100_Move_CursorDown

DESCRIPTION:
	Move Cursor down by the specified number of columns.

INPUT:
	sessionID	: cli session ID
	columns		: move coursor n columns down.

OUTPUT:
	None

RETURN:
	None

NOTES:

HISTORY:
	Creat by wangbin 2009.11.18

**************************************************************************/
void VT_100_Move_CursorDown(IN I32_T sessionID, IN I32_T columns);
#if 0
/**************************************************************************
FUNCTION NAME:
	VT_100_Erase_Screen

DESCRIPTION:
	Erase Text on the VT100 Screen.

INPUT:
	sessionID	: cli session ID
	erase_mode	: 0 = Erase from the cursor to the end of the screen.
				  1 = Erase from the beginning of the screen to the cursor.
				  2 = Clears the screen but do not moves the cursor position.

OUTPUT:
	None

RETURN:
	None

NOTES:

HISTORY:
	Creat by wangbin 2009.11.19

**************************************************************************/
void VT_100_Erase_Screen(IN I32_T sessionID, IN VT_ERASE_MODE_T erase_mode);

/**************************************************************************
FUNCTION NAME:
	VT_100_Erase_Line

DESCRIPTION:
	Erase Text on the VT100 Screen.

INPUT:
	sessionID	: cli session ID
	erase_mode	: 0 = Erase from the cursor to the end of the line.
				  1 = Erase from the beginning of the line to the cursor.
				  2 = Clears the line but do not moves the cursor position.

OUTPUT:
	None

RETURN:
	None

NOTES:

HISTORY:
	Creat by wangbin 2009.11.19

**************************************************************************/
void VT_100_Erase_Line(IN I32_T sessionID, IN VT_ERASE_MODE_T erase_mode);

/**************************************************************************
FUNCTION NAME:
	VT_100_Set_Text_Attributes

DESCRIPTION:
	Set Text attributes.

INPUT:
	sessionID	: cli session ID
	attribute		: 0 = NORNAL
				  1 = HIGHT INTENSITY
				  5 = BLINK
				  7 = INVERSE
				  8 = CONCEALED
				  12 = GRAPHICS

OUTPUT:
	None

RETURN:
	None

NOTES:

HISTORY:
	Creat by wangbin 2009.11.19

**************************************************************************/
void VT_100_Set_Text_Attributes(IN I32_T sessionID, IN VT_TEXT_MODE_T attribute);

/**************************************************************************
FUNCTION NAME:
	VT_100_Set_Char

DESCRIPTION:
	Set VT100 character set.

INPUT:
	sessionID	: cli session ID
	set			: 'B'- ASCII character set.
				  '0'- DEC special graphic.

OUTPUT:
	None

RETURN:
	None

NOTES:

HISTORY:
	Creat by wangbin 2009.11.19

**************************************************************************/
void VT_100_Set_Char(IN I32_T sessionID, IN I8_T set);

/**************************************************************************
FUNCTION NAME:
	VT_100_Set_Xmargin

DESCRIPTION:
	Set X margin in x1 to x2.

INPUT:
	sessionID	: cli session ID
	line1			: x1 margin
	line2			: x2 margin

OUTPUT:
	None

RETURN:
	None

NOTES:

HISTORY:
	Creat by wangbin 2009.11.19

**************************************************************************/
void VT_100_Set_Xmargin (IN I32_T sessionID,  IN UI8_T line1, IN UI8_T line2);

/**************************************************************************
FUNCTION NAME:
	VT_100_Set_Ymargin

DESCRIPTION:
	set Y margin in line1 to line 2.

INPUT:
	sessionID	: cli session ID
	line1			: top margin
	line2			: bottom margin

OUTPUT:
	None

RETURN:
	None

NOTES:

HISTORY:
	Creat by wangbin 2009.11.19

**************************************************************************/
void VT_100_Set_Ymargin (IN I32_T sessionID, IN UI8_T line1, IN UI8_T line2);

/**************************************************************************
FUNCTION NAME:
	VT_100_Set_Cursor_to_XY

DESCRIPTION:
	Moves the cursor to the specified position. If you do not specify a position, the cursor 
	moves to the home position-the upper-left corner of the screen ( line 0, column 0 ).

INPUT:
	sessionID	: cli session ID
	column		: X
	row			: Y

OUTPUT:
	None

RETURN:
	None

NOTES:

HISTORY:
	Creat by wangbin 2009.11.19

**************************************************************************/
void VT_100_Set_Cursor_to_XY(IN I32_T sessionID, IN I32_T row, IN I32_T column);
#endif
/**************************************************************************
FUNCTION NAME:
	VT_100_Analysis_Keystroke

DESCRIPTION:
	Analysis keystroke.

INPUT:
	ptrKeystrokeState	: the state of keystroke
	rxChr			: input char

OUTPUT:
	None

RETURN:
	analysed keystroke

NOTES:

HISTORY:
	Creat by wangbin 2009.11.19

**************************************************************************/
I32_T VT_100_Analysis_Keystroke(IN UI8_T *ptrKeystrokeState, IN I32_T rxChr);

#endif /*__VT_100_H__*/
