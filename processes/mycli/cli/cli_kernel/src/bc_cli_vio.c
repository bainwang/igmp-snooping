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


#if 1

/*-----------------------------------------------------------------------
 VT100 KEY SEQUENCE

--------- EDIT KEYS ------------
ESC[1~      INSERT
ESC[2~      HOME
ESC[3~      PAGE UP
ESC[4~      DELETE
ESC[5~      END
ESC[6~      PAGE DOWN

--------- DIRECTION KEYS ----------
ESC[A       UP
ESC[B       DOWN
ESC[C       RIGHT
ESC[D       LEFT

--------- FUNCTION KEYS -------------
ESC[11~     F1
ESC[12~     F2
ESC[13~     F3
ESC[14~     F4
ESC[16~     F5
ESC[17~     F6
ESC[18~     F7
ESC[19~     F8
ESC[20~     F9
ESC[21~     F10
ESC[23~     F11
ESC[24~     F12
*-----------------------------------------------------------------------
*/
typedef struct
{
    I32_T                       mapnum;
    UI8_T                       *keys;
} CLI_KEYMAP_VT100_T;

typedef struct
{
    CLI_VIO_ERASE_T            mode;
    UI8_T                       *keys;
} CLI_KEYMAP_ERASE_T;

/*
 * 方向键映射表
 */
static CLI_KEYMAP_VT100_T  s_vt100_drct_list[] =
{
    {CLI_VKEY_UP,    (UI8_T *)"\x1B\x5B\x41"},
	{CLI_VKEY_DOWN,  (UI8_T *)"\x1B\x5B\x42"},
	{CLI_VKEY_RIGHT, (UI8_T *)"\x1B\x5B\x43"},
    {CLI_VKEY_LEFT,  (UI8_T *)"\x1B\x5B\x44"}
};

/*
 * 擦除键映射表
 */
static CLI_KEYMAP_ERASE_T  s_vt100_erase_list[]    =
{
    {CLI_SCREEN_FROM_CURSOR2END,   (UI8_T *)"\x1B\x5B\x30\x4A"},
	{CLI_SCREEN_FROM_BEGIN2CURSOR, (UI8_T *)"\x1B\x5B\x31\x4A"},
    {CLI_SCREEN_COMPLETE,          (UI8_T *)"\x1B\x5B\x32\x4A\x1B\x5B\x48"},
    {CLI_LINE_FROM_CURSOR2END,     (UI8_T *)"\x1B\x5B\x30\x4B"},
    {CLI_LINE_FROM_BEGIN2CURSOR,   (UI8_T *)"\x1B\x5B\x31\x4B"},
    {CLI_LINE_COMPLETE,            (UI8_T *)"\x1B\x5B\x32\x4B"}
};


/**************************************************************************
FUNCTION NAME:
    __cli2_vt100_analysis_keystroke

DESCRIPTION:
    Analysis keystroke

INPUT:
    ptrKeystrokeState   : the state of input character (used to analysis control sequence)
    rxChr           	: the input character

OUTPUT:
    ptrKeystrokeState   : the state of control sequence

RETURN:
    -5              	: the control sequence is wrong
    > 0             	: the character or predefined control character

NOTES:

HISTORY:

**************************************************************************/
static I32_T __cli2_vt100_analysis_keystroke
    (
    IN OUT UI8_T *ptrKeystrokeState,
    IN I32_T rxChr
    )
{
    I32_T           rtn_value;
    static I32_T    func_key1 = 0, func_key2 = 0;

    /* set default return value */
    rtn_value = VT_NULL;

    switch (*ptrKeystrokeState)
    {
    case CLI_VT100_WAIT_FOR_KEYSTROKE:
        rtn_value = rxChr;
        break;

        /* is control sequence */
    case CLI_VT100_WAIT_FOR_2ND_ESC_SEQ:
        switch (rxChr)
        {
        case CLI_VKEY_BRACKET:
            *ptrKeystrokeState = CLI_VT100_WAIT_FOR_AFTER_BRACKET;
            break;
        case 'O':
            *ptrKeystrokeState = CLI_VT100_WAIT_FOR_AFTER_O;
            break;
        default:
            rtn_value = CLI_VKEY_IO_WRONGVALUE;
            break;
        }
        break;

        /* map to the predefined key */
    case CLI_VT100_WAIT_FOR_AFTER_BRACKET:
        switch (rxChr)
        {
        case 'A':
            rtn_value = CLI_VKEY_UP;
            break;
        case 'B':
            rtn_value = CLI_VKEY_DOWN;
            break;
        case 'C':
            rtn_value = CLI_VKEY_RIGHT;
            break;
        case 'D':
            rtn_value = CLI_VKEY_LEFT;
            break;

        case '1':
            *ptrKeystrokeState = CLI_VT100_WAIT_FOR_AFTER_1;
            func_key1 = '1';
            break;
        case '2':
            *ptrKeystrokeState = CLI_VT100_WAIT_FOR_AFTER_2;
            func_key1 = '2';
            break;
        case '3':
            *ptrKeystrokeState = CLI_VT100_WAIT_FOR_AFTER_3;
            break;
        case '4':
            *ptrKeystrokeState = CLI_VT100_WAIT_FOR_AFTER_4;
            break;
        case '5':
            *ptrKeystrokeState = CLI_VT100_WAIT_FOR_AFTER_5;
            break;
        case '6':
            *ptrKeystrokeState = CLI_VT100_WAIT_FOR_AFTER_6;
            break;

        default:
            rtn_value = CLI_VKEY_IO_WRONGVALUE;
            break;
        }
        break;

        /* map to the predefined key */
    case CLI_VT100_WAIT_FOR_AFTER_O:
        switch (rxChr)
        {
        case 'P':
            rtn_value = CLI_VKEY_OP;
            break;
        case 'Q':
            rtn_value = CLI_VKEY_OQ;
            break;
        case 'R':
            rtn_value = CLI_VKEY_OR;
            break;
        case 'S':
            rtn_value = CLI_VKEY_OS;
            break;
		
		case 'H':
			rtn_value = CLI_VKEY_HOME;
			break;
		
		case 'F':
			rtn_value = CLI_VKEY_END;
			break;

        default:
            rtn_value = CLI_VKEY_IO_WRONGVALUE;
            break;
        }
        break;

    case CLI_VT100_WAIT_FOR_AFTER_1:
    case CLI_VT100_WAIT_FOR_AFTER_2:
    case CLI_VT100_WAIT_FOR_AFTER_3:
    case CLI_VT100_WAIT_FOR_AFTER_4:
    case CLI_VT100_WAIT_FOR_AFTER_5:
    case CLI_VT100_WAIT_FOR_AFTER_6:
        if (rxChr == '~')
        {
            /* map to the predefined key */
            rtn_value = (*ptrKeystrokeState - CLI_VT100_WAIT_FOR_AFTER_1 + 1) + CLI_VKEY_EDIT_KEY_BASE;
        }
        /* the control sequence is F1~F12 */
        else if ((rxChr >= '0' && rxChr <= '9') && (func_key1 == '1' || func_key1 == '2'))
        {
            *ptrKeystrokeState = CLI_VT100_WAIT_FOR_FUNC_KEY2;
            func_key2 = rxChr;
        }
        else
        {
            rtn_value = CLI_VKEY_IO_WRONGVALUE;
        }
        break;

    case CLI_VT100_WAIT_FOR_FUNC_KEY2:
        /* map to the predefined key */
        if (rxChr == '~')
        {
            I32_T   fx;
            fx = ((func_key1 - '0') * 10 + (func_key2 - '0'));
            if (fx > 10 && fx < 25)
            {
                rtn_value = fx + CLI_VKEY_EDIT_KEY_BASE;
            }
            else
            {
                rtn_value = CLI_VKEY_IO_WRONGVALUE;
            }
        }
        else
        {
            /* invalid function key, return CLI_VKEY_IO_WRONGVALUE */
            rtn_value = CLI_VKEY_IO_WRONGVALUE;
        }
        break;
    }

    /* confirm a character reset the analysis state */
    if (rtn_value != VT_NULL)
    {
        *ptrKeystrokeState = CLI_VT100_WAIT_FOR_KEYSTROKE;
        func_key1 = func_key2 = 0;
    }

    return rtn_value;
}


static I32_T __bc_cli_vt100_getc(IN CLI_TERMINAL_IO_T *hterm, IN I32_T timeout)
{
    CLI_TERMINAL_GETCHAR       	inputFunction;
    CLI_TERMINAL_CHECK_EMPTY   	checkFunction;
    I32_T                       rxChr;
    BOOL_T                      timeoutFlag     = TRUE;
    UI8_T                       keystrokeState  = CLI_VT100_WAIT_FOR_KEYSTROKE;

    if (hterm == NULL)
    {
        return CLI_VKEY_IO_NOACTION;
    }

    /* get the terminal IO */
    inputFunction = hterm->getchar;
    checkFunction = hterm->checkEmpty;
    if (inputFunction == NULL)
    {
        return CLI_VKEY_IO_NOACTION;
    }

    if (timeout == 0)
    {
        timeoutFlag = FALSE;
        timeout = 1000;
    }

    for (; ;)
    {
        /* get a char from terminal */
        rxChr = (*inputFunction) (hterm->sessionID, timeout);
        if (rxChr == CLI_VKEY_ESC)
        {
            if (checkFunction && (*checkFunction) (hterm->sessionID) != 0)
            {
                /* It's a control sequence */
                keystrokeState = CLI_VT100_WAIT_FOR_2ND_ESC_SEQ;
                continue;
            }
        }

        /* analysis keystroke if it's a control sequence map it to predefined key */
        rxChr = __cli2_vt100_analysis_keystroke(&keystrokeState, rxChr);
        if (rxChr != VT_NULL)
        {
            if ((FALSE == timeoutFlag) && (rxChr == CLI_VKEY_IO_TIMEOUT))
            {
                continue;
            }

            break;
        }
    }

    return rxChr;
}


static BOOL_T __bc_cli_vt100_putc(IN CLI_TERMINAL_IO_T *hterm, IN I32_T rxCh)
{
    CLI_TERMINAL_PUTSTR    outputFunction;
    I32_T                   i;
    UI8_T                   ch;

    if ((NULL == hterm) || (NULL == hterm->putstr))
    {
        return FALSE;
    }

    outputFunction = hterm->putstr;

    /* map the predefined control keys to VT100 control sequence */
    if (rxCh > CLI_VKEY_EDIT_KEY_BASE/* || rxCh < 0*/)
    {
        switch (rxCh)
        {
        case CLI_VKEY_UP:
        case CLI_VKEY_DOWN:
        case CLI_VKEY_RIGHT:
        case CLI_VKEY_LEFT:
            /* move cursor */
            for (i = 0; i < (sizeof(s_vt100_drct_list) / sizeof(CLI_KEYMAP_VT100_T)); i++)
            {
                if (rxCh == s_vt100_drct_list[i].mapnum)
                {
                    (*outputFunction) (hterm->sessionID, s_vt100_drct_list[i].keys, strlen((I8_T *)s_vt100_drct_list[i].keys));
                    return TRUE;
                }
            }
            break;

        default:
            break;
        }

        return FALSE;
    }

    /* It's not a control sequence output normally */
    ch = (UI8_T) rxCh;
    (*outputFunction) (hterm->sessionID, & ch, sizeof(ch));

    return TRUE;
}

static BOOL_T __bc_cli_vt100_erase(IN CLI_TERMINAL_IO_T *hterm, IN CLI_VIO_ERASE_T mode)
{
    CLI_TERMINAL_PUTSTR    outputFunction;
    I32_T                   i;

    if (hterm == NULL)
    {
        return FALSE;
    }

    if (hterm->putstr)
    {
        outputFunction = hterm->putstr;
    }
    else
    {
        return FALSE;
    }

    /* output control sequence for earse text by input mode */
    for (i = 0; i < (sizeof(s_vt100_erase_list) / sizeof(CLI_KEYMAP_ERASE_T)); i++)
    {
        if (mode == s_vt100_erase_list[i].mode)
        {
            (*outputFunction) (hterm->sessionID, s_vt100_erase_list[i].keys, strlen((I8_T *)s_vt100_erase_list[i].keys));

            return TRUE;
        }
    }

    if (mode == CLI_SCREEN_CLEAR)
    {
        (*outputFunction) (hterm->sessionID, (UI8_T *)"\033[1;1H", strlen("\033[1;1H"));
        (*outputFunction) (hterm->sessionID, (UI8_T *)"\x1B\x5B\x32\x4A\x1B\x5B\x48", strlen("\x1B\x5B\x32\x4A\x1B\x5B\x48"));

        return TRUE;
    }

    return FALSE;
}

#endif
#if 1

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

	vio = (CLI_VIO_T *)CLI_MISC_Malloc(sizeof(CLI_VIO_T));

	vio->hterm = *hterm;

	switch (vio_type)
	{
	case CLI_VT100:
	default:
		vio->getchar = __bc_cli_vt100_getc;
		vio->putchar = __bc_cli_vt100_putc;
		vio->eraseString = __bc_cli_vt100_erase;
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
#if 0 // jash law 20140520
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
					
					bc_cli_session_get_cursorstatus(&cursor_status);
					back_stopFlag = bc_cli_session_get_pagestopstatus();
					bc_cli_session_set_pagestopstatus(FALSE);
					if ((*msgCallbackFunc)(vio->hterm.sessionID, callbackCookie))
					{
						msgFlag = TRUE;
					}
					bc_cli_session_set_pagestopstatus(back_stopFlag);
					bc_cli_session_set_cursorstatus(&cursor_status);
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
	CLI_MISC_Free(hvio);

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

#endif

