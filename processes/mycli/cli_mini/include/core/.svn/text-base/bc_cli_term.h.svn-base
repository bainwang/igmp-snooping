
#ifndef __BC_CLI_TERM_H__
#define __BC_CLI_TERM_H__

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

typedef void (*CLI_TERMINAL_PUTSTR)(I32_T, UI8_T *, I32_T); /* string and length */
typedef I32_T (*CLI_TERMINAL_GETCHAR)(I32_T, I32_T); /* delay */
typedef BOOL_T(*CLI_TERMINAL_CHECK_EMPTY)(I32_T); /* check char pull is empty */

typedef struct
{
    CLI_TERMINAL_PUTSTR        putstr;     /* write one character */
    CLI_TERMINAL_GETCHAR       getchar;    /* read one character */
    CLI_TERMINAL_CHECK_EMPTY   checkEmpty; /* read one character */
    I32_T                       sessionID;  /* now just be the mapped session for other modules used */
} CLI_TERMINAL_IO_T;

typedef enum
{
    CLI_SCREEN_FROM_CURSOR2END    = 1, /* 1 */
    CLI_SCREEN_FROM_BEGIN2CURSOR,      /* 2 */
    CLI_SCREEN_COMPLETE,               /* 3 */
    CLI_LINE_FROM_CURSOR2END,          /* 4 */
    CLI_LINE_FROM_BEGIN2CURSOR,        /* 5 */
    CLI_LINE_COMPLETE,                 /* 6 */
    CLI_SCREEN_CLEAR                   /* 7 */
} CLI_VIO_ERASE_T;



////////////////////////////////////////////////////////////////////////////////
//																			  //
//								函	数	声	明								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////




#endif /* __BC_CLI_TERM_H__ */

