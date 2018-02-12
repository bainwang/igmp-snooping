/*******************************************************************************
 * Copyright(C) 2008, Kingtype Networks Corporation. All rights reserved.
 *
 * This is unpublished proprietary source code of Kingtype Networks Corporation.
 *
 * The copyright notice above does not evidence any actual or intended
 *	publication of such source code.
*******************************************************************************/
/*==============================================================================
 * MODULE NAME: Kingtype CLI, bc_cli
 * FILE NAME  : bc_cli_misc.c
 * VERSION    : 1.0.0
 * DESCRIPTION:
 * NOTES      :
 *
 * HISTORY    :
 * -----------------------------------------------------------------------------
 * Version 1.0 -  2008-Nov-28 by wangbin
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
#include "bc_cli_os.h"



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
static unsigned int 		l_mdl_id = BC_MODULE_CLI;

static HANDLE_T 			s_mem_pool;
static unsigned int			s_mem_count;



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
 *	 2008-Nov-19 by wangbin -- Create
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
BOOL_T bc_cli_misc_init(void)
{
	CLI_DBG_ENTER(l_mdl_id);

	/* Initialization for memory allocation */
	s_mem_count = 0;
	s_mem_pool = CLI_OS_MEMPOOL_Create("CLI-MEMORY", MEM_SIZE);

	if (NULL == s_mem_pool)
	{
		CLI_DBG_CPL(l_mdl_id, "\n Create CLI memory Pool failed!\n");
		CLI_DBG_LEAVE(l_mdl_id);
		return FALSE;
	}

	CLI_DBG_LEAVE(l_mdl_id);
	return TRUE;
}



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
I32_T CLI_MISC_CheckMem (void)
{
	return s_mem_count;
}



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
BOOL_T CLI_MISC_Destroy(void)
{
	CLI_OS_MEMPOOL_Destroy(s_mem_pool);
	return TRUE;
}



/*******************************************************************************
 *
 * Func       : cli_misc_malloc
 * DESCRIPTION: It request a block of memory has size <size>.
 * INPUT      : size -- the size of the memory block
 * OUTPUT     : NA
 * RETURN     : if successful, return a pointer to the memory space; else, 'NULL'
 * NOTES      : NA
 * HISTORY    :
 *	 2008-Dec-19 by wangbin -- Create
 *
*******************************************************************************/
void *cli_misc_malloc(
	IN UI32_T 		size)
{
	void *p;

	p = CLI_OS_MEMPOOL_Alloc(s_mem_pool, size);
	if (!p)
	{
		return p;
	}

	s_mem_count++;
	return p;
}



/*******************************************************************************
 *
 * Func       : cli_misc_calloc
 * DESCRIPTION: It request a block of memory sufficient to hold an array of
 *		   		<count> elements, each of which has size <size>. The function do
 *		   		the same thing as cli_misc_malloc, except that the
 *		   		first one initialize the memory block to all zero bytes.
 * INPUT      : count    -- the elements of the array
 *		   		size     -- the size of each element
 *		   		filename -- The name of the file where this function is called
 *		   		lineno   -- The line where this fuction is called in the file <filename>
 * OUTPUT     : NA
 * RETURN     : if successful, return a pointer to the memory space; else, 'NULL'
 * NOTES      : NA
 * HISTORY    :
 *	 2008-Dec-19 by wangbin -- Create
 *
*******************************************************************************/
void *cli_misc_calloc(
	IN UI32_T 		count,
	IN UI32_T 		size)
{
	void 	*p;

	p = CLI_OS_MEMPOOL_Alloc(s_mem_pool, count * size);
	if (!p)
	{
		return p;
	}

	memset(p, 0, count * size);
	s_mem_count++;

	return p;
}




/*******************************************************************************
 *
 * Func       : cli_misc_realloc
 * DESCRIPTION: It attempts to expand the old memory block pointed by <old_ptr>
 *				to <size> bytes. The  old memory block must be obtained by calling
 *				cli_misc_malloc, cli_misc_calloc or
 *				cli_misc_realloc. It adjusts the size of the memory block
 *				to new_size, the contents will be copied to the new location if necessary.
 * INPUT      : old_ptr  -- the old memory block
 *		   		size     -- the new size of the memory block
 *		   		filename -- The name of the file where this function is called
 *		   		lineno   -- The line where this fuction is called in the file <filename>
 * OUTPUT     : NA
 * RETURN     : if successful, return a pointer to the memory space; else, 'NULL'
 * NOTES      : NA
 * HISTORY    :
 *	 2008-Dec-19 by wangbin -- Create
 *
*******************************************************************************/
void *cli_misc_realloc(
	IN void 		*old_ptr,
	IN UI32_T 		size)
{
#ifdef __LINUX_DEBUG__
	void *p;

	if (filename)
	{
	}

	if (lineno)
	{
	}

	p = OS_MEMPOOL_Realloc(s_mem_pool, old_ptr, size);
	if (old_ptr)
	{
		if (!p)
		{
			s_mem_count--;
		}

		return p;
	}
	else if (p)
	{
		s_mem_count++;
	}

	return p;
#else
	CLI_DBG_NOTSUPPORTED(l_mdl_id);
	return NULL;
#endif
}



/*******************************************************************************
 *
 * Func       : cli_misc_free
 * DESCRIPTION: Release memory block allocated by cli_misc_malloc,
 *				cli_misc_calloc, or cli_misc_realloc
 * INPUT      : ptr -- pointer of the memory block
 * OUTPUT     : NA
 * RETURN     : NA
 * NOTES      : NA
 * HISTORY    :
 *	 2008-Dec-19 by wangbin -- Create
 *
*******************************************************************************/
void cli_misc_free(IN void *ptr)
{
	if (ptr)
	{
		s_mem_count--;
		CLI_OS_MEMPOOL_Free(s_mem_pool, ptr);
	}
}



