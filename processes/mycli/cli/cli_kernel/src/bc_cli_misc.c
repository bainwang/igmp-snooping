/*==============================================================================
 * FILE NAME  : bc_cli_misc.c
 * VERSION    : 1.0.0
 * DESCRIPTION:
 * NOTES      :
 *
 * HISTORY    :
 * -----------------------------------------------------------------------------
 * Version 1.0 -  2008-Nov-28 by bain.wang@outlook.com
 * [NEW FEATURE]
 * <DESCRIPTION> Create
 *============================================================================*/
	 
 ////////////////////////////////////////////////////////////////////////////////
 // 																		   //
 // 							 头   文   件								   //
 // 																		   //
 ////////////////////////////////////////////////////////////////////////////////

#include "bc_cli_type.h"
#include "bc_cli_misc.h"

#include "bc_modules.h"
#include "utili_block_ext.h"

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

#define MEM_SIZE 			(5*1024*1024)



////////////////////////////////////////////////////////////////////////////////
//																			  //
//							全 局 变 量 定 义								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////


#if 1

BOOL_T CLI_MISC_Is_Keyword_Char (IN const I8_T ch)
{
	if (((ch >= 'a') && (ch <= 'z')) // lowercase
		|| ((ch >= 'A') && (ch <= 'Z')) // uppercase
		|| ((ch >= '0') && (ch <= '9')) // digital
		|| (ch == '-') || (ch == '_') || (ch == '.') || (ch == ':')
		|| (ch == '+') || (ch == '@') || (ch == '$') || (ch == '*')) // other chars
	{
		return TRUE;
	}

	return FALSE;
}



BOOL_T CLI_MISC_Is_Alias_Char (IN const I8_T ch)
{
	if (((ch >= 'a') && (ch <= 'z')) // lowercase
		|| ((ch >= 'A') && (ch <= 'Z')) // uppercase
		|| ((ch >= '0') && (ch <= '9')) // digital
		|| (ch == '-') || (ch == '_') || (ch == '.') || (ch == ':')) // other chars
	{
		return TRUE;
	}

	return FALSE;
}



BOOL_T CLI_MISC_Is_Alias_Char_OutAngleBrackets(IN const I8_T ch)
{
	if (((ch >= 'A') && (ch <= 'Z')) // uppercase
		|| ((ch >= '0') && (ch <= '9')) // digital
		|| (ch == '-') || (ch == '_') || (ch == '.') || (ch == ':')) // other chars
	{
		return TRUE;
	}

	return FALSE;
}



/*******************************************************************************
 *
 * Func       : CLI_MISC_Skip_WhiteSpace
 * DESCRIPTION: Skip spaces and tabs in the front of the string.
 * INPUT      : str -- string for process
 * OUTPUT     : NA
 * RETURN     : new pointer point to str, which skipped spaces and tabs in the front of the string
 * NOTES      : NA
 * HISTORY    :
 *	 2008-Nov-19 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
I8_T *CLI_MISC_Skip_WhiteSpace(IN const I8_T * str)
{
	if (!str)
	{
		return NULL;
	}

	/* skip the white space ' ' or '\t' */
	while ((*str == ' ') || *str == '\t')
	{
		str++;
	}

	/* return the begin position non-space */
	return (I8_T *) str;
}

#endif
#if 1

static utili_block_ext_t cli_prt_block;

bc_char * bc_cli_misc_alloc(void)
{
	return utili_block_ext_alloc(&cli_prt_block);
}

void bc_cli_misc_free(bc_char *ptr)
{
	utili_block_ext_free(&cli_prt_block, ptr);
}

bc_err_e bc_cli_misc_init(void)
{
	return utili_block_ext_init(&cli_prt_block, BC_MODULE_CLI, "print", 10240, 1024);
}

#endif


