////////////////////////////////////////////////////////////////////////////////
// 																			  //
// 							 	头   文   件								  //
// 																			  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_modules.h"
#include "bc_platform_time.h"

#include "bc_cli_type.h"

#include "bc_cli_vio.h"
#include "bc_cli_vt100.h"
#include "bc_cli_misc.h"
#include "bc_cli_hook.h"
#include "bc_cli_vkey.h"
#include "bc_cli_acc.h"
#include "bc_cli_sesn.h"



////////////////////////////////////////////////////////////////////////////////
//																			  //
//						外 部 变 量、 函 数 引 用							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//																			  //
//						结   构   体   宏   定   义							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//																			  //
//							全 局 变 量 定 义								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

static unsigned int 	l_mdl_id = BC_MODULE_CLI_KERNEL_VIO;



////////////////////////////////////////////////////////////////////////////////
//																			  //
//								函  数  声  明								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//																			  //
//								函  数  定  义								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

/**************************************************************************
FUNCTION NAME:
	CLI_VIO_Create

DESCRIPTION:
	Create vio handle for using this module

INPUT:
	hterm		: the handle for using IO modules such as Telnet RS232 SSH and so on
	vio_type	: the type of terminal protocol

OUTPUT:
	NA

RETURN:
	pointer 	: the handle for using vio module

NOTES:

HISTORY:

**************************************************************************/
HANDLE_T CLI_VIO_Create(IN CLI_TERMINAL_IO_T *hterm, IN CLI_VIOTYPE_T vio_type)
{
	CLI_VIO_T *vio;

	vio = (CLI_VIO_T *)CLI_MISC_Calloc(1, sizeof(CLI_VIO_T));

	vio->hterm = *hterm;

	switch (vio_type)
	{
	case CLI_VT100:
	default:
		vio->getchar = CLI_VT100_Getc;
		vio->putchar = CLI_VT100_Putc;
		vio->eraseString = CLI_VT100_Erase;
		break;
	}

	return (HANDLE_T) vio;
}



/**************************************************************************
FUNCTION NAME:
	CLI_VIO_Getc

DESCRIPTION:
	Get the input character from vio

INPUT:
	hvio	: the handle for using vio modules
	timeout : the timeout for geting input charcater

OUTPUT:
	NA

RETURN:
	CLI_VKEY_IO_CLOSED		: IO closed
	CLI_VKEY_IO_TIMEOUT	: timeout
	CLI_VKEY_IO_NOACTION	: noaction(the input function is null)
	CLI_VKEY_IO_EXITCMD	: exit cmd
	CLI_VKEY_IO_WRONGVALUE	: the got value is wrong
	CLI_VKEY_IO_NOTIFY		: have notify message input
	>0						: input character

NOTES:
	NA

HISTORY:

**************************************************************************/
I32_T CLI_VIO_Getc(IN HANDLE_T hvio, IN I32_T timeout)
{
	CLI_DBG_ENTER(l_mdl_id);
	
	CLI_VIO_T 					*vio;
	CLI_VIO_GET_CHAR 			inputFunction;
	I32_T 						rxCh;
	UI32_T  					lastTime, nowTime, diffTime;
	
	if (hvio)
	{
		vio = (CLI_VIO_T *)hvio;
	}
	else
	{
		CLI_DBG_LEAVE(l_mdl_id);
		return CLI_VKEY_IO_NOACTION;
	}

	/* get input function by type (VT100 VT220 ...) */
	if (vio->getchar)
	{
		inputFunction = vio->getchar;
	}
	else
	{
		CLI_DBG_LEAVE(l_mdl_id);
		return CLI_VKEY_IO_NOACTION;
	}

	bc_platform_time_sec_get(&lastTime);
	while (1)
	{
#if 0 // wangbin 20140520
		/* add for execute CLI notify message hook function */
		if (vio->hterm.putstr)
		{
			CLI_NOTIFY_MSG_CALLBACK_T	msgCallbackFunc;
			void						*callbackCookie;
			BOOL_T						msgFlag;
			I32_T						i;
			
			msgFlag = FALSE;
			for (i = BC_FIRST_MODULE; i < (BC_LAST_MODULE - BC_FIRST_MODULE) / BC_MODULE_INTERVAL; i++)
			{
				CLI_HOOK_Get_NotifyMsg(i, &msgCallbackFunc, &callbackCookie);
				if (msgCallbackFunc)
				{
					CLI_ACC_CURSOR_STATUS_T	cursor_status;
					BOOL_T						back_stopFlag;
					
					CLI_ACC_GetCursorStatus(vio->hterm.sessionID, &cursor_status);
					back_stopFlag = CLI_ACC_GetPageStopStatus(vio->hterm.sessionID);
					CLI_ACC_SetPageStopStatus(vio->hterm.sessionID, FALSE);
					if ((*msgCallbackFunc)(vio->hterm.sessionID, callbackCookie))
					{
						msgFlag = TRUE;
					}
					CLI_ACC_SetPageStopStatus(vio->hterm.sessionID, back_stopFlag);
					CLI_ACC_SetCursorStatus(vio->hterm.sessionID, &cursor_status);
				}
			}

			if (msgFlag)
			{
				CLI_DBG_LEAVE(l_mdl_id);
				return CLI_VKEY_IO_NOTIFY;
			}
		}
#endif
		rxCh = (*inputFunction) (&vio->hterm, 100);
		CLI_DBG_CPL(l_mdl_id, "[rxCh=\"%c\",%d,0x%X]\r\n", rxCh, rxCh, rxCh);

		if (rxCh == CLI_VKEY_IO_TIMEOUT)
		{
			if (timeout != 0)
			{
				bc_platform_time_sec_get(&nowTime);
				if (nowTime >=  lastTime) /* normal */
				{
					diffTime =  nowTime - lastTime;
				}
				else /* turn over */
				{
					diffTime = 0xFFFFFFFF - lastTime + nowTime + 1;
				}

				if (diffTime >= timeout)
				{
					CLI_DBG_LEAVE(l_mdl_id);
					return CLI_VKEY_IO_TIMEOUT;
				}
			}
		}
		else
		{
			CLI_DBG_LEAVE(l_mdl_id);
			return rxCh;
		}
	}
}



/**************************************************************************
FUNCTION NAME:
	CLI_VIO_Putc

DESCRIPTION:
	Output the character(some predefined control keys can be outputed by the
	 function such as cursor left right and so on)

INPUT:
	hvio		: the handle for using vio modules
	rxCh		: the output character

OUTPUT:
	NA

RETURN:
	true		: output success
	false		: the output function is null or output false

NOTES:

HISTORY:

**************************************************************************/
BOOL_T CLI_VIO_Putc(IN HANDLE_T hvio, IN I32_T rxCh)
{
	CLI_VIO_T *vio;
	CLI_VIO_PUT_CHAR outputFunction;

	if (hvio)
	{
		vio = (CLI_VIO_T *) hvio;
	}
	else
	{
		return FALSE;
	}

	/* get output function by type (VT100 VT220 ...) */
	if (vio->putchar)
	{
		outputFunction = vio->putchar;
	}
	else
	{
		return FALSE;
	}

	return (*outputFunction) (&vio->hterm, rxCh);
}



/**************************************************************************
FUNCTION NAME:
	CLI_VIO_Puts

DESCRIPTION:
	Output the string by length(some predefined control keys can be outputed
	 by the function such as cursor left right and so on)

INPUT:
	hvio		: the handle for using vio modules
	str 		: the pointer of string
	length		: the length of string

OUTPUT:
	NA

RETURN:
	true		: output success
	false		: the output function is null or the string is null or output false

NOTES:

HISTORY:

**************************************************************************/
BOOL_T CLI_VIO_Puts(IN HANDLE_T hvio, IN const I8_T * str, IN I32_T length)
{
	CLI_VIO_T 			*vio;
	CLI_VIO_PUT_CHAR 	outputFunction;
	BOOL_T 				outputFlag;
	I32_T 				i;

	if (hvio)
	{
		vio = (CLI_VIO_T *) hvio;
	}
	else
	{
		return FALSE;
	}

	/* get output function by type (VT100 VT220 ...) */
	if (vio->putchar)
	{
		outputFunction = vio->putchar;
	}
	else
	{
		return FALSE;
	}

	if (str == NULL || length <= 0)
	{
		return FALSE;
	}

	for (i = 0; i < length; i++, str++)
	{
		outputFlag = (*outputFunction) (&vio->hterm, (I32_T) * str);
		if (outputFlag == FALSE)
		{
			return FALSE;
		}
	}

	return TRUE;
}



/**************************************************************************
FUNCTION NAME:
	CLI_VIO_Destroy

DESCRIPTION:
	Destroy the vio handle free the memory

INPUT:
	hvio		: the handle for using vio module

OUTPUT:
	NA

RETURN:
	NA

NOTES:

HISTORY:

**************************************************************************/
void CLI_VIO_Destroy(IN HANDLE_T hvio)
{
	cli_misc_free(hvio);

	return;
}



/**************************************************************************
FUNCTION NAME:
	CLI_VIO_Move_Cursor_XY

DESCRIPTION:
	Move cursor by given steps

INPUT:
	hvio		: the handle for using vio modules
	columns 	: move cursor left or right by given steps (<0 move left , >0 move right)
	rows		: move cursor up or down by given steps (<0 move up , >0 move down)

OUTPUT:
	NA

RETURN:
	true		: move success
	false		: the output function is null

NOTES:
	columns    	: <0 move left , >0 move right
	rows		: <0 move up ,   >0 move down
	
HISTORY:

**************************************************************************/
BOOL_T CLI_VIO_Move_Cursor_XY(IN HANDLE_T hvio, IN I32_T columns, IN I32_T rows)
{
	CLI_VIO_T 			*vio;
	CLI_VIO_PUT_CHAR 	outputFunction;
	I32_T 				i, j, num[2], rxCh[2];

	if (hvio == NULL)
	{
		return FALSE;
	}
	else
	{
		vio = (CLI_VIO_T *) hvio;
	}

	/* get output function by type (VT100 VT220 ...) */
	if (vio->putchar)
	{
		outputFunction = vio->putchar;
	}
	else
	{
		return FALSE;
	}

	if (columns < 0)
	{
		num[0] = 0 - columns;
		rxCh[0] = CLI_VKEY_LEFT;
	}
	else
	{
		num[0] = columns;
		rxCh[0] = CLI_VKEY_RIGHT;
	}

	if (rows < 0)
	{
		num[1] = 0 - rows;
		rxCh[1] = CLI_VKEY_UP;
	}
	else
	{
		num[1] = rows;
		rxCh[1] = CLI_VKEY_DOWN;
	}

	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < num[i]; j++)
		{
			(*outputFunction) (&vio->hterm, rxCh[i]);
		}
	}

	return TRUE;
}



/**************************************************************************
FUNCTION NAME:
	CLI_VIO_Erase

DESCRIPTION:
	Erase text on screen

INPUT:
	hvio			: the handle for using vio modules
	mode			: the mode of erasing text

				CLI_SCREEN_FROM_CURSOR2END(1) earse from cursor to the end of screen
				CLI_SCREEN_FROM_BEGIN2CURSOR(2) earse from begin of screen to cursor
				CLI_SCREEN_COMPLETE(3) earse the whole screen
				CLI_LINE_FROM_CURSOR2END(4) earse from cursor to the end of line
				CLI_LINE_FROM_BEGIN2CURSOR(5) earse from begin of line to cursor
				CLI_LINE_COMPLETE(6) earse the line which cursor stay
				CLI_SCREEN_CLEAR(7) clear the whole screen

OUTPUT:
	NA

RETURN:
	true			: earse success
	false			: the earse function is null or earse false

NOTES:

HISTORY:

**************************************************************************/
BOOL_T CLI_VIO_Erase(IN HANDLE_T hvio, IN CLI_VIO_ERASE_T mode)
{
	CLI_VIO_T 					*vio;
	CLI_VIO_ERASE_FUNCTION 	eraseFunction;

	if (hvio)
	{
		vio = (CLI_VIO_T *) hvio;
	}
	else
	{
		return FALSE;
	}

	/* get earse function by type (VT100 VT220 ...) */
	if (vio->eraseString)
	{
		eraseFunction = vio->eraseString;
	}
	else
	{
		return FALSE;
	}

	return (*eraseFunction) (&vio->hterm, mode);
}



/**************************************************************************
FUNCTION NAME:
	CLI_VIO_Get_Hterm

DESCRIPTION:
	Get the terminal IO struct

INPUT:
	hvio		: the handle for using vio modules

OUTPUT:
	NA

RETURN:
	the terminal IO struct for using IO modules such as Telnet RS232 SSH and so on
	NULL		: the VIO is null

NOTES:

HISTORY:

**************************************************************************/
CLI_TERMINAL_IO_T *CLI_VIO_Get_Hterm(IN HANDLE_T hvio)
{
	CLI_VIO_T *vio;

	if (NULL == hvio)
	{
		return NULL;
	}

	vio = (CLI_VIO_T *)hvio;
	return &vio->hterm;
}



/**************************************************************************
FUNCTION NAME:
	CLI_VIO_Set_Hterm

DESCRIPTION:
	Set the terminal IO struct in vio module

INPUT:
	hvio	: the handle for using vio modules
	hterm	: the terminal IO struct for using IO modules such as Telnet RS232 SSH and so on

OUTPUT:
	NA

RETURN:
	TRUE	: set success
	FALSE	: the VIO is null

NOTES:

HISTORY:

**************************************************************************/
BOOL_T CLI_VIO_Set_Hterm(
	IN HANDLE_T 			hvio,
	IN CLI_TERMINAL_IO_T 	*hterm)
{
	CLI_VIO_T *vio;

	if (hvio == NULL)
	{
		return FALSE;
	}

	vio = (CLI_VIO_T *)hvio;
	vio->hterm = *hterm;

	return TRUE;
}



/*-------------------------------------- end of program ------------------------------------------*/

