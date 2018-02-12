
////////////////////////////////////////////////////////////////////////////////
// 																			  //
// 							 	头   文   件								  //
// 																			  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_modules.h"

#include "bc_cli_type.h"

#include "bc_cli_vkey.h"
#include "bc_cli_term.h"
#include "bc_cli_vt100.h"



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



////////////////////////////////////////////////////////////////////////////////
//																			  //
//							全 局 变 量 定 义								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

static unsigned int 	l_mdl_id = BC_MODULE_CLI_KERNEL_VT100;

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



/**************************************************************************
FUNCTION NAME:
    CLI_VT100_Getc

DESCRIPTION:
    Get a input character and map the control sequence to predefined key

INPUT:
    hterm       : the handle for using terminal IO
    timeout     : the timeout for geting input charcater

OUTPUT:
    NA

RETURN:
    -1          : IO closed
    -2          : timeout
    -3          : noaction(the input function is null)
    -4          : exit cmd
    -5          : the got value is wrong
    >0          : input character

NOTES:

HISTORY:

**************************************************************************/
I32_T CLI_VT100_Getc
    (
    IN CLI_TERMINAL_IO_T *hterm,
    IN I32_T timeout
    )
{
	CLI_DBG_ENTER(l_mdl_id);

    CLI_TERMINAL_GETCHAR       	inputFunction;
    CLI_TERMINAL_CHECK_EMPTY   	checkFunction;
    I32_T                       rxChr;
    BOOL_T                      timeoutFlag     = TRUE;
    UI8_T                       keystrokeState  = CLI_VT100_WAIT_FOR_KEYSTROKE;

    if (hterm == NULL)
    {
		CLI_DBG_LEAVE(l_mdl_id);
        return CLI_VKEY_IO_NOACTION;
    }

    /* get the terminal IO */
    inputFunction = hterm->getchar;
    checkFunction = hterm->checkEmpty;
    if (inputFunction == NULL)
    {
		CLI_DBG_LEAVE(l_mdl_id);
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
		CLI_DBG_TAG(l_mdl_id);
        rxChr = (*inputFunction) (hterm->sessionID, timeout);
		CLI_DBG_TAG(l_mdl_id);
		CLI_DBG_CPL(l_mdl_id, "[rxCh=\"%c\",%d,0x%X]\r\n", rxChr, rxChr, rxChr);

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
		CLI_DBG_TAG(l_mdl_id);
        rxChr = __cli2_vt100_analysis_keystroke(&keystrokeState, rxChr);
		CLI_DBG_TAG(l_mdl_id);
		CLI_DBG_CPL(l_mdl_id, "[rxCh=\"%c\",%d,0x%X]\r\n", rxChr, rxChr, rxChr);

        if (rxChr != VT_NULL)
        {
            if ((FALSE == timeoutFlag) && (rxChr == CLI_VKEY_IO_TIMEOUT))
            {
                continue;
            }

            break;
        }
    }

	CLI_DBG_LEAVE(l_mdl_id);
    return rxChr;
}



/**************************************************************************
FUNCTION NAME:
    CLI_VT100_Putc

DESCRIPTION:
    Output the character(some predefined control keys can be outputed by
     the function such ascursor left right and so on)

INPUT:
    hterm       : the handle for using terminal IO
    rxCh        : the output character

OUTPUT:
    NA

RETURN:
    true        : output success
    false       : the output function is null or output false

NOTES:

HISTORY:

**************************************************************************/
BOOL_T CLI_VT100_Putc
    (
    IN CLI_TERMINAL_IO_T *hterm,
    IN I32_T rxCh
    )
{
    CLI_TERMINAL_PUTSTR    outputFunction;
    I32_T                   i;
    UI8_T                   ch;

    if (NULL == hterm)
    {
        return FALSE;
    }

    /* get the terminal IO */
    if (NULL == hterm->putstr)
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



/**************************************************************************
FUNCTION NAME:
    CLI_VT100_Erase

DESCRIPTION:
    Erase text on screen

INPUT:
    hterm       : the handle for using terminal IO
    mode        : the mode of erasing text
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
    true        : earse success
    false       : the earse function is null or earse false

NOTES:

HISTORY:

**************************************************************************/
BOOL_T CLI_VT100_Erase
    (
    IN CLI_TERMINAL_IO_T *hterm,
    IN CLI_VIO_ERASE_T mode
    )
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



/*-------------------------------------- end of program ------------------------------------------*/
