/*==============================================================================
 * FILE NAME  : bc_cli_misc.h
 * VERSION    : 1.0.0
 * DESCRIPTION:
 * NOTES      :
 *
 * HISTORY    :
 * -----------------------------------------------------------------------------
 * Version 1.0 -- 2009-Jul-30 by bain.wang@outlook.com
 * [NEW FEATURE]
 * <DESCRIPTION> Create
 *============================================================================*/

#ifndef __BC_CLI_MISC_H__
#define __BC_CLI_MISC_H__

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								头   文   件								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#ifdef __LINUX_DEBUG__
#include <platform/os/os_mempool.h>
#include <runtime/os_switch.h>
#else
#ifndef INSTALL_ON_BIG_ENDIAN
#define INSTALL_ON_BIG_ENDIAN 1
#endif
#endif

#include "bc_platform_mem.h"


////////////////////////////////////////////////////////////////////////////////
//																			  //
//						结   构   体   宏   定   义							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#if INSTALL_ON_BIG_ENDIAN
#define UTL_MISC_SWAP16(x)		(x)
#define UTL_MISC_SWAP32(x)		(x)
#else
#define UTL_MISC_SWAP16(x) 		(((x&0x00ff)<<8)|((x&0xff00)>>8))
#define UTL_MISC_SWAP32(x) 		(((x&0x000000ff)<<24)|((x&0x0000ff00)<<8)|((x&0x00ff0000)>>8)|((x&0xff000000)>>24))
#endif

#define CLI_MISC_IS_CONNECTCHAR(ch) 	((ch == '-') || (ch == '_'))
#define CLI_MISC_IS_WHITESPACE(ch) 	((ch == ' ') || (ch == '\t'))
#define CLI_MISC_IS_VIEW_SEPERATOR(ch) (ch == '/')

#define CLI_MISC_IS_PARA_START(ch) 	(isupper (ch) || (ch == '{') || (ch == '[') || (ch == '<'))
#define CLI_MISC_IS_HELP_START(ch) 	(ch == '#')

#define CLI_MISC_Malloc(size) bc_platform_mem_malloc(BC_MODULE_CLI, size)
#define CLI_MISC_Free(ptr) bc_platform_mem_free(BC_MODULE_CLI, ptr)


#define CLI_MISC_Assert(a) \
	do \
	{ \
		if (0 == (a)) \
		{ \
			CLI_MSG_ERR(l_mdl_id, "File(%s)Line(%d): Assert failed!\n", __FILE__, __LINE__); \
		} \
	} while (0)



#if 1

BOOL_T CLI_MISC_Is_Keyword_Char (IN const I8_T ch);
BOOL_T CLI_MISC_Is_Alias_Char (IN const I8_T ch);
BOOL_T CLI_MISC_Is_Alias_Char_OutAngleBrackets(IN const I8_T ch);

/*******************************************************************************
 *
 * Func:   CLI_MISC_Skip_WhiteSpace
 * DESCRIPTION: Skip whitespaces (spaces and tabs) in the front of the string.
 * INPUT:  str -- string for process
 * OUTPUT: NA
 * RETURN: new pointer point to str, which skipped spaces and tabs in the front of the string
 * NOTES:  NA
 * HISTORY:
 *	 2008-Nov-19 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
I8_T *CLI_MISC_Skip_WhiteSpace(IN const I8_T * str);

#endif
#if 1

extern bc_char * bc_cli_misc_alloc(void);
extern void bc_cli_misc_free(bc_char *ptr);
extern bc_err_e bc_cli_misc_init(void);

#endif
#endif /* __BC_CLI_MISC_H__ */

/* End of file */
