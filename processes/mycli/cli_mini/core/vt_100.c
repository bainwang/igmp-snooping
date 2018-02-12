/*******************************************************************

COPYRIGHT:
	Copyright (c) 2005-2010  Kingtype Corporation   All rights reserved.
    	This is unpublished proprietary source code of Kingtype Corporation.
	The copyright notice above does not evidence any actual or intended
	publication of such source code.

MODULE NAME:
	VIO

FILE NAME:
 	vt_100.c

VERSION:
	1.00

DESCRIPTION:
 	Add the IO control of VT100.

NOTES:
    	None

HISTORY:
	Ver1.00:	2009.11.18 wangbin

********************************************************************/

//#include <string.h>
//#include <utl/vt_100.h>
//#include <utl/vt_utl.h>
//#include <utl/translat.h>
//#include <utl/utl_debug.h>

#include "bc_modules.h"

#include "bc_cli_type.h"
#include "vt_100.h"

extern void VT_Put_String(IN I32_T sessionID, IN const I8_T *string, IN I32_T length);


static unsigned int 	l_mdl_id = BC_MODULE_CLI_KERNEL;




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
void VT_100_Move_CursorLeft(IN I32_T sessionID, IN I32_T columns)
{
	I8_T  escape_str[8], *temp_ptr ;

	/* Reserve 8 bytes space for Escape sequence */

	temp_ptr = escape_str ;
	*temp_ptr++ = VT_ESC ;
	*temp_ptr++ = '[' ;

	temp_ptr += TRAN_I32toA( temp_ptr, columns, 10 );

	*temp_ptr++ = 'D' ;
	*temp_ptr = VT_NULL ;

	VT_Put_String(sessionID, escape_str, strlen(escape_str));
} 



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
void VT_100_Move_CursorRight(IN I32_T sessionID, IN I32_T columns)
{
	I8_T  escape_str[8], *temp_ptr ;

	/* Reserve 8 bytes space for Escape sequence */

	temp_ptr = escape_str ;
	*temp_ptr++ = VT_ESC ;
	*temp_ptr++ = '[' ;

	temp_ptr += TRAN_I32toA( temp_ptr, columns, 10 );

	*temp_ptr++ = 'C' ;
	*temp_ptr = VT_NULL ;

	VT_Put_String(sessionID, escape_str, strlen(escape_str));
}
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
void VT_100_Move_CursorUp(IN I32_T sessionID, IN I32_T columns)
{
	I8_T  escape_str[8], *temp_ptr ;

	/* Reserve 8 bytes space for Escape sequence */

	temp_ptr = escape_str ;
	*temp_ptr++ = VT_ESC ;
	*temp_ptr++ = '[' ;

	temp_ptr += sprintf(temp_ptr, "%d", columns);

	*temp_ptr++ = 'A' ;
	*temp_ptr = VT_NULL ;

	VT_Put_String(sessionID, escape_str, strlen(escape_str));
}

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
void VT_100_Move_CursorDown(IN I32_T sessionID, IN I32_T columns)
{
	I8_T  escape_str[8], *temp_ptr ;

	/* Reserve 8 bytes space for Escape sequence */

	temp_ptr = escape_str ;
	*temp_ptr++ = VT_ESC ;
	*temp_ptr++ = '[' ;

	temp_ptr += sprintf(temp_ptr, "%d", columns);

	*temp_ptr++ = 'B' ;
	*temp_ptr = VT_NULL ;

	VT_Put_String(sessionID, escape_str, strlen(escape_str));
}
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
void VT_100_Erase_Screen(IN I32_T sessionID, IN VT_ERASE_MODE_T erase_mode)
{
	I8_T  escape_str[5], *temp_ptr ;

	temp_ptr = escape_str ;
	*temp_ptr++ = VT_ESC ;
	*temp_ptr++ = '[' ;
	temp_ptr += TRAN_I32toA( temp_ptr, erase_mode, 10 );
	*temp_ptr++ = 'J' ;
	*temp_ptr = VT_NULL ;

	VT_Put_String(sessionID, escape_str, strlen(escape_str));
} 

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
void VT_100_Erase_Line(IN I32_T sessionID, IN VT_ERASE_MODE_T erase_mode)
{
	I8_T  escape_str[5], *temp_ptr ;

	temp_ptr = escape_str ;
	*temp_ptr++ = VT_ESC ;
	*temp_ptr++ = '[' ;
	temp_ptr += TRAN_I32toA( temp_ptr, erase_mode, 10 );
	*temp_ptr++ = 'K' ;
	*temp_ptr = VT_NULL ;

	VT_Put_String(sessionID, escape_str, strlen(escape_str));
}

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
void VT_100_Set_Text_Attributes(IN I32_T sessionID, IN VT_TEXT_MODE_T attribute)
{
	I8_T  escape_str[6], *temp_ptr;

	temp_ptr = escape_str;
	*temp_ptr++ = VT_ESC;
	*temp_ptr++ = '[';

	temp_ptr += TRAN_I32toA( temp_ptr, attribute, 10 );

	*temp_ptr++ = 'm';
	*temp_ptr = VT_NULL;

	VT_Put_String(sessionID, escape_str, strlen(escape_str));
}


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
void VT_100_Set_Char(IN I32_T sessionID, IN I8_T set)
{
	I8_T  escape_str[4], *temp_ptr ;

	temp_ptr = escape_str ;
	*temp_ptr++ = VT_ESC ;
	*temp_ptr++ = '(' ;
	*temp_ptr++ = (I8_T)set ;

	*temp_ptr = VT_NULL ;
	VT_Put_String(sessionID, escape_str, strlen(escape_str));
}

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
void VT_100_Set_Xmargin (IN I32_T sessionID,  IN UI8_T line1, IN UI8_T line2)
{
	I8_T  escape_str[12], *temp_ptr ;

	temp_ptr = escape_str ;
	*temp_ptr++ = VT_ESC ;
	*temp_ptr++ = '[' ;

	temp_ptr += TRAN_I32toA( temp_ptr, line1, 10 );

	*temp_ptr++ = ';' ;

	temp_ptr += TRAN_I32toA( temp_ptr, line2, 10 );

	*temp_ptr++ = 's' ;
	*temp_ptr = VT_NULL ;

	 VT_Put_String(sessionID, escape_str, strlen(escape_str));
} 

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
void VT_100_Set_Ymargin (IN I32_T sessionID, IN UI8_T line1, IN UI8_T line2)
{
	I8_T  escape_str[12], *temp_ptr ;

	temp_ptr = escape_str ;
	*temp_ptr++ = VT_ESC ;
	*temp_ptr++ = '[' ;

	temp_ptr += TRAN_I32toA( temp_ptr, line1, 10 );

	*temp_ptr++ = ';' ;

	temp_ptr += TRAN_I32toA( temp_ptr, line2, 10 );

	*temp_ptr++ = 'r' ;
	*temp_ptr = VT_NULL ;

	VT_Put_String(sessionID, escape_str, strlen(escape_str));
}

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
void VT_100_Set_Cursor_to_XY(IN I32_T sessionID, IN I32_T row, IN I32_T column)
{
	I8_T  escape_str[12], *temp_ptr ;

	/* Reserve 12 bytes space for Escape sequence */
	
	temp_ptr = escape_str ;
	*temp_ptr++ = VT_ESC ;
	*temp_ptr++ = '[' ;

	temp_ptr += TRAN_I32toA( temp_ptr, row, 10 );

	*temp_ptr++ = ';' ;

	temp_ptr += TRAN_I32toA( temp_ptr, column, 10 );

	*temp_ptr++ = 'H' ;
	*temp_ptr = VT_NULL ;

	VT_Put_String(sessionID, escape_str, strlen(escape_str));
}
#endif



/*-----------------------------------------------------------------------
 VT100 KEY SEQUENCE

--------- EDIT KEYS ------------
ESC[1~		INSERT
ESC[2~		HOME
ESC[3~		PAGE UP
ESC[4~		DELETE
ESC[5~		END
ESC[6~		PAGE DOWN

--------- DIRECTION KEYS ----------
ESC[A		UP
ESC[B		DOWN
ESC[C		RIGHT
ESC[D		LEFT

--------- FUNCTION KEYS -------------
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
*-----------------------------------------------------------------------
*/
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
I32_T VT_100_Analysis_Keystroke(IN UI8_T *ptrKeystrokeState, IN I32_T rxChr)
{
	I32_T rtn_value ;
	static I32_T func_key1 = 0, func_key2 = 0;

	/* set default return value */
	rtn_value = VT_NULL ;

	switch (*ptrKeystrokeState)
	{
		case VT_WAIT_FOR_KEYSTROKE:
			switch (rxChr)
			{
				case VT_LF :
				case VT_CR :
					rtn_value = VT_CR ;
					break;
					
				case VT_ESC:
					*ptrKeystrokeState = VT_WAIT_FOR_2ND_ESC_SEQ;
					break;
					
				default:
					rtn_value= rxChr;
					break;
			}
	    		break;
				
		case VT_WAIT_FOR_2ND_ESC_SEQ:
			switch (rxChr)
			{
				case VT_BRACKET :
					*ptrKeystrokeState = VT_WAIT_FOR_AFTER_BRACKET ;
					break;
					
				case 'O' :
					*ptrKeystrokeState = VT_WAIT_FOR_AFTER_O ;
					break;
					
				default:
					rtn_value= rxChr;
					break;
			}
			break;
			
		case VT_WAIT_FOR_AFTER_BRACKET:
			switch (rxChr)
			{
				case 'A':
					rtn_value= VT_UP;
					break;
					
				case 'B' :
					rtn_value= VT_DOWN;
					break;
					
				case 'C':
					rtn_value= VT_RIGHT;
					break;
					
				case 'D' :
					rtn_value= VT_LEFT;
					break;

				case '1':
					*ptrKeystrokeState = VT_WAIT_FOR_7e_AFTER_INSERT;
					func_key1 = '1';
					break;
					
				case '2' :
					*ptrKeystrokeState = VT_WAIT_FOR_7e_AFTER_HOME;
					func_key1 = '2';
					break;
					
				case '3':
					*ptrKeystrokeState = VT_WAIT_FOR_7e_AFTER_PAGEUP;
					break;
					
				case '4' :
					*ptrKeystrokeState = VT_WAIT_FOR_7e_AFTER_DELETE;
					break;
					
				case '5':
					*ptrKeystrokeState = VT_WAIT_FOR_7e_AFTER_END;
					break;
					
				case '6' :
					*ptrKeystrokeState = VT_WAIT_FOR_7e_AFTER_PAGEDOWN;
					break;

				default:
					rtn_value= rxChr;
					break;
			}
			break;

		case VT_WAIT_FOR_7e_AFTER_INSERT:
		case VT_WAIT_FOR_7e_AFTER_HOME:
		case VT_WAIT_FOR_7e_AFTER_PAGEUP:
		case VT_WAIT_FOR_7e_AFTER_DELETE:
		case VT_WAIT_FOR_7e_AFTER_END:
		case VT_WAIT_FOR_7e_AFTER_PAGEDOWN:
	 		/* restore the value that has been added by VT_WAIT_FOR_7e_AFTER_INSERT */
			if (rxChr=='~')
			{
				/* map to the predefined key */
				rtn_value = (*ptrKeystrokeState - VT_WAIT_FOR_7e_AFTER_INSERT + 1) + VT_FUNC_EDIT_KEY_BASE;
			}
			/* check if the 1 sequence for function key, F1 - F12 */
			else if ((rxChr >= '0' && rxChr <= '9') && (func_key1 == '1' || func_key1 == '2'))
			{
				*ptrKeystrokeState = VT_WAIT_FOR_7E_FOR_FUNC_KEY2;
				func_key2 = rxChr;
				CLI_DBG_CPL(l_mdl_id, "\nCLI_Wait_7e: FuncK: func1 = %d, func2 = %d", func_key1, func_key2);
			}
	 		/* abort the escape sequence analysis */
	 		else
			{
				rtn_value=rxChr;
				CLI_DBG_CPL(l_mdl_id, "\nCLI_Wait_7e: FuncK abort: func1 = %d, rxChr = %d", func_key1, rxChr);
			}
	    		break;

		case VT_WAIT_FOR_7E_FOR_FUNC_KEY2:
			if (rxChr=='~')
			{
				I32_T fx;
				
				fx = ((func_key1 - '0') * 10 + (func_key2 - '0'));
				CLI_DBG_CPL(l_mdl_id, "\nCLI analysis fx = %d", fx);
				if (fx > 10 && fx < 25)
				{
					rtn_value= fx + VT_FUNC_EDIT_KEY_BASE;
				}
				else
				{	
					/* invalid function key, return ~ */
					rtn_value = rxChr;
				}
			}
			/* abort the escape sequence analysis */
			else
			{
				rtn_value=rxChr;
			}
			break;

		case VT_WAIT_FOR_AFTER_O:
			switch (rxChr)
			{
				case 'A':
					rtn_value= VT_UP;
					break;
					
				case 'B' :
					rtn_value= VT_DOWN;
					break;

				case 'C':
					rtn_value= VT_LEFT;
					break;

				case 'D' :
					rtn_value= VT_RIGHT;
					break;

				default:
					rtn_value= rxChr;
					break;
			}
			break;

		default:
			break;
	}

	if (rtn_value!=VT_NULL)
	{
		*ptrKeystrokeState = VT_WAIT_FOR_KEYSTROKE;
		func_key1 = func_key2 = 0;
		if (rtn_value >= VT_FUNC_EDIT_KEY_BASE)
		{
			CLI_DBG_CPL(l_mdl_id, "\nCLI analysis key: %d", (rtn_value - (I32_T)VT_FUNC_EDIT_KEY_BASE));
		}
	}

	return rtn_value;
}

