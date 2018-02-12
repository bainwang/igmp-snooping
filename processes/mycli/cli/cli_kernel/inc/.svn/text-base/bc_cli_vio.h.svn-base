
#ifndef __BC_CLI_VIO_H__
#define __BC_CLI_VIO_H__

////////////////////////////////////////////////////////////////////////////////
// 								    										  //
// 							    头   文   件								  //
// 										    								  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_cli_type.h"
#include "bc_cli_priv.h"
#include "bc_cli_term.h"



////////////////////////////////////////////////////////////////////////////////
//																			  //
//						结   构   体   宏   定   义							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
typedef enum
{
    CLI_VT100          = 1,    /* 1 */
    CLI_VT220,                 /* 2 */
    CLI_VT320,                 /* 3 */
    CLI_VT460,                 /* 4 */
    CLI_PC,
    CLI_LINUX
} CLI_VIOTYPE_T;

typedef BOOL_T(*CLI_VIO_PUT_CHAR)(CLI_TERMINAL_IO_T *, I32_T);
typedef I32_T(*CLI_VIO_GET_CHAR)(CLI_TERMINAL_IO_T *, I32_T);
typedef BOOL_T(*CLI_VIO_ERASE_FUNCTION)(CLI_TERMINAL_IO_T *, CLI_VIO_ERASE_T);

typedef struct
{
    CLI_VIO_PUT_CHAR       putchar;
    CLI_VIO_GET_CHAR       getchar;
    CLI_VIO_ERASE_FUNCTION eraseString;
    CLI_TERMINAL_IO_T      hterm;
} CLI_VIO_T;



////////////////////////////////////////////////////////////////////////////////
//																			  //
//								函	数	声	明								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

/**************************************************************************
FUNCTION NAME:
	CLI_VIO_Create

DESCRIPTION:
	create vio handle for using this module

INPUT:
	hterm		: the handle for using IO modules such as Telnet RS232 SSH and so on
	vio_type		: the type of terminal protocol

OUTPUT:
	None

RETURN:
	pointer 	: the handle for using vio module

NOTES:

HISTORY:

**************************************************************************/
HANDLE_T CLI_VIO_Create(IN CLI_TERMINAL_IO_T *hterm, IN CLI_VIOTYPE_T vio_type);

/**************************************************************************
FUNCTION NAME:
	CLI_VIO_Getc

DESCRIPTION:
	get the input character from vio

INPUT:
	hvio			: the handle for using vio modules
	timeout 	: the timeout for geting input charcater

OUTPUT:
	None

RETURN:
	CLI_VKEY_IO_CLOSED		: IO closed
	CLI_VKEY_IO_TIMEOUT		: timeout
	CLI_VKEY_IO_NOACTION		: noaction(the input function is null)
	CLI_VKEY_IO_EXITCMD		: exit cmd
	CLI_VKEY_IO_WRONGVALUE	: the got value is wrong
	CLI_VKEY_IO_NOTIFY			: have notify message input
	>0			: input character

NOTES:

HISTORY:

**************************************************************************/
I32_T CLI_VIO_Getc(IN HANDLE_T hvio, IN I32_T timeout);

/**************************************************************************
FUNCTION NAME:
	CLI_VIO_Putc

DESCRIPTION:
	output the character(some predefined control keys can be outputed by the function such as
	cursor left right and so on)

INPUT:
	hvio			: the handle for using vio modules
	rxCh		: the output character

OUTPUT:
	None

RETURN:
	true			: output success
	false			: the output function is null or output false

NOTES:

HISTORY:

**************************************************************************/
BOOL_T CLI_VIO_Putc(IN HANDLE_T hvio, IN I32_T rxCh);

/**************************************************************************
FUNCTION NAME:
	CLI_VIO_Puts

DESCRIPTION:
	output the string by length(some predefined control keys can be outputed by the function
	such as cursor left right and so on)

INPUT:
	hvio			: the handle for using vio modules
	str 		: the pointer of string
	length		: the length of string

OUTPUT:
	None

RETURN:
	true			: output success
	false			: the output function is null or the string is null or output false

NOTES:

HISTORY:

**************************************************************************/
BOOL_T CLI_VIO_Puts(IN HANDLE_T hvio, IN const I8_T * str, IN I32_T length);

/**************************************************************************
FUNCTION NAME:
	CLI_VIO_Destroy

DESCRIPTION:
	destroy the vio handle free the memory

INPUT:
	hvio			: the handle for using vio module

OUTPUT:
	None

RETURN:
	None

NOTES:

HISTORY:

**************************************************************************/
void CLI_VIO_Destroy(IN HANDLE_T hvio);

/**************************************************************************
FUNCTION NAME:
	CLI_VIO_Move_Cursor_XY

DESCRIPTION:
	move cursor by given steps

INPUT:
	hvio			: the handle for using vio modules
	columns 	: move cursor left or right by given steps (<0 move left , >0 move right)
	rows			: move cursor up or down by given steps (<0 move up , >0 move down)

OUTPUT:
	None

RETURN:
	true			: move success
	false			: the output function is null

NOTES:

HISTORY:

**************************************************************************/
BOOL_T CLI_VIO_Move_Cursor_XY(IN HANDLE_T hvio, IN I32_T columns, IN I32_T rows);

/**************************************************************************
FUNCTION NAME:
	CLI_VIO_Erase

DESCRIPTION:
	erase text on screen

INPUT:
	hvio: the handle for using vio modules
	mode: the mode of erasing text
		  CLI_SCREEN_FROM_CURSOR2END(1) earse from cursor to the end of screen
		  CLI_SCREEN_FROM_BEGIN2CURSOR(2) earse from begin of screen to cursor
		  CLI_SCREEN_COMPLETE(3) earse the whole screen
		  CLI_LINE_FROM_CURSOR2END(4) earse from cursor to the end of line
		  CLI_LINE_FROM_BEGIN2CURSOR(5) earse from begin of line to cursor
		  CLI_LINE_COMPLETE(6) earse the line which cursor stay

OUTPUT:
	None

RETURN:
	true: earse success
	false: the earse function is null or earse false

NOTES:

HISTORY:

**************************************************************************/
BOOL_T CLI_VIO_Erase(IN HANDLE_T hvio, IN CLI_VIO_ERASE_T mode);

/**************************************************************************
FUNCTION NAME:
	CLI_VIO_Get_Hterm

DESCRIPTION:
	Get the terminal IO struct

INPUT:
	hvio			: the handle for using vio modules

OUTPUT:
	None

RETURN:
	the terminal IO struct for using IO modules such as Telnet RS232 SSH and so on
	NULL		: the VIO is null

NOTES:

HISTORY:

**************************************************************************/
CLI_TERMINAL_IO_T *CLI_VIO_Get_Hterm(IN HANDLE_T hvio);

/**************************************************************************
FUNCTION NAME:
	CLI_VIO_Set_Hterm

DESCRIPTION:
	Set the terminal IO struct in vio module

INPUT:
	hvio		: the handle for using vio modules
	hterm	: the terminal IO struct for using IO modules
			  such as Telnet RS232 SSH and so on

OUTPUT:
	None

RETURN:
	TRUE	: set success
	FALSE	: the VIO is null

NOTES:

HISTORY:

**************************************************************************/
BOOL_T CLI_VIO_Set_Hterm(
	IN HANDLE_T hvio,
	IN CLI_TERMINAL_IO_T *hterm);



#endif /* __BC_CLI_VIO_H__ */

