/*******************************************************************************
 * Copyright(C) 2008, Kingtype Networks Corporation. All rights reserved.
 *
 * This is unpublished proprietary source code of Kingtype Networks Corporation.
 *
 * The copyright notice above does not evidence any actual or intended
 *  publication of such source code.
*******************************************************************************/
/*==============================================================================
 * MODULE NAME: Kingtype CLI, bc_cli
 * FILE NAME  : bc_cli_misc.h
 * VERSION    : 1.0.0
 * DESCRIPTION:
 * NOTES      :
 *
 * HISTORY    :
 * -----------------------------------------------------------------------------
 * Version 1.0 -- 2009-Jul-30 by wangbin
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

#define CLI_MISC_Malloc(size) 								cli_misc_malloc(size)
#define CLI_MISC_Calloc(count_of_array, size_per_count) 	cli_misc_calloc(count_of_array, size_per_count)
#define CLI_MISC_Realloc(old_ptr,size) 					cli_misc_realloc(old_ptr, size)


#define CLI_MISC_Assert(a) \
	do \
	{ \
		if (0 == (a)) \
		{ \
			CLI_MSG_ERR(l_mdl_id, "File(%s)Line(%d): Assert failed!\n", __FILE__, __LINE__); \
		} \
	} while (0)



////////////////////////////////////////////////////////////////////////////////
//																			  //
//								函	数	声	明								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
 *
 * Func       : bc_cli_misc_init
 * DESCRIPTION: Initialize CLI MISC
 * INPUT      : NA
 * OUTPUT     : NA
 * RETURN     : TRUE  -- Initial succeeded
 *		        FALSE -- Initial failed
 * NOTES      : NA
 * HISTORY    :
 *	 2008-Dec-19 by wangbin -- Create
 *
*******************************************************************************/
BOOL_T bc_cli_misc_init(void);

/*******************************************************************************
 *
 * Func       : CLI_MISC_Destroy
 * DESCRIPTION: Release resources allocated by bc_cli_misc_init
 * INPUT      : NA
 * OUTPUT     : NA
 * RETURN     : TRUE  -- Release resources successed
 *		        FALSE -- Release resources failed (Reserved)
 * NOTES      : ###
 * HISTORY    :
 *	 2008-Dec-19 by wangbin -- Create
 *
*******************************************************************************/
BOOL_T CLI_MISC_Destroy(void);

/*******************************************************************************
 *
 * Func:   cli_misc_malloc
 * DESCRIPTION: It request a block of memory has size <size>.
 * INPUT:  size -- the size of the memory block
 * OUTPUT: NA
 * RETURN: if successful, return a pointer to the memory space; else, 'NULL'
 * NOTES:  NA
 * HISTORY:
 *	 2008-Dec-19 by wangbin -- Create
 *
*******************************************************************************/
void *cli_misc_malloc(IN UI32_T size);

/*******************************************************************************
 *
 * Func:   cli_misc_calloc
 * DESCRIPTION: It request a block of memory sufficient to hold an array of
 *		   <count> elements, each of which has size <size>. The function do
 *		   the same thing as cli_misc_malloc, except that the
 *		   first one initialize the memory block to all zero bytes.
 * INPUT:  count -- the elements of the array
 *		   size  -- the size of each element
 *		   filename -- The name of the file where this function is called
 *		   lineno -- The line where this fuction is called in the file <filename>
 * OUTPUT: NA
 * RETURN: if successful, return a pointer to the memory space; else, 'NULL'
 * NOTES:  NA
 * HISTORY:
 *	 2008-Dec-19 by wangbin -- Create
 *
*******************************************************************************/
void *cli_misc_calloc(
	IN UI32_T count,
	IN UI32_T size);


/*******************************************************************************
 *
 * Func:   cli_misc_realloc
 * DESCRIPTION: It attempts to expand the old memory block pointed by <old_ptr>
 *		to <size> bytes. The  old memory block must be obtained by calling
 *		cli_misc_malloc, cli_misc_calloc or
 *		cli_misc_realloc. It adjusts the size of the memory block
 *		to new_size, the contents will be copied to the new location if necessary.
 * INPUT:  old_ptr -- the old memory block
 *		   size -- the new size of the memory block
 *		   filename -- The name of the file where this function is called
 *		   lineno -- The line where this fuction is called in the file <filename>
 * OUTPUT: NA
 * RETURN: if successful, return a pointer to the memory space; else, 'NULL'
 * NOTES:  NA
 * HISTORY:
 *	 2008-Dec-19 by wangbin -- Create
 *
*******************************************************************************/
void *cli_misc_realloc(
	IN void *old_ptr,
	IN UI32_T size);

/*******************************************************************************
 *
 * Func:   cli_misc_free
 * DESCRIPTION: Release memory block allocated by cli_misc_malloc,
 *		cli_misc_calloc, or cli_misc_realloc
 * INPUT:  ptr -- pointer of the memory block
 * OUTPUT: NA
 * RETURN: NA
 * NOTES:  NA
 * HISTORY:
 *	 2008-Dec-19 by wangbin -- Create
 *
*******************************************************************************/
void cli_misc_free(IN void *ptr);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 CLI_MISC_CheckMem
 *
 * DESCRIPTION:
 *	 Show memory malloced by CLI kernel
 *
 * INPUT:
 *	 NA
 *
 * OUTPUT:
 *	 NA
 *
 * RETURN:
 *	 NA
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-24 by wangbin -- Create
 *
*******************************************************************************/
I32_T CLI_MISC_CheckMem (void);
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
 *	 2008-Nov-19 by wangbin -- Create
 *
*******************************************************************************/
I8_T *CLI_MISC_Skip_WhiteSpace(IN const I8_T * str);



#endif /* __BC_CLI_MISC_H__ */

/* End of file */
