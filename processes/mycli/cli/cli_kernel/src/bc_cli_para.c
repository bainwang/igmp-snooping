/*==============================================================================
 * FILE NAME  : bc_cli_para.c
 * VERSION    : 1.0.0
 * DESCRIPTION:
 * NOTES:
 *
 * HISTORY:
 * -----------------------------------------------------------------------------
 * Version 1.0 -- 2009-Mar-19 by bain.wang@outlook.com
 * [NEW FEATURE]
 * <DESCRIPTION> Create
 *============================================================================*/

////////////////////////////////////////////////////////////////////////////////
// 																			  //
// 							 	头   文   件								  //
// 																			  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_modules.h"
#include "bc_cli_priv.h"
#include "bc_cli_para.h"
#include "bc_cli_alias.h"
#include "bc_cli_msg.h"
#include "bc_cli_misc.h"



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

typedef struct
{
	const I8_T 					*para; /* parameter string of the syntax command */
	CLI_PARA_WORD_T 			*wordlist; /* wordlist[max_word] is a dynamic array */
	I16_T 						max_word;
	I16_T 						used_word; /* word index from [0, used_word) is valid */
	I16_T 						total_char; /* total chars in command after formatted (extra white spaces are deleted) */
	I8_T 						*start; /* address of the current parsing word */
	I8_T 						*end; /* address of the char just after current parsing word */
	I16_T 						nouse; /* count of nodes not need to malloc spaces */

	// next are used when generate parameter tree
	CLI_PRIV_PARA_SYN_NODE_T 	*para_node; /* point to the first empty para node to get an argument in para. */
	I8_T 						*name_buf; /* point to the empty buffer to get a word */
	I32_T 						cur; /* current word in wordlist[max_word] need to be parsed */
} CLI_SYNCMD_PARA_T;



////////////////////////////////////////////////////////////////////////////////
//																			  //
//							全 局 变 量 定 义								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

static unsigned int 		l_mdl_id = BC_MODULE_CLI_KERNEL_PARA;

/* used to save words when parsing parameter part of a syntax command */
static CLI_SYNCMD_PARA_T 	s_para_syn_cmd;



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

/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 cli2_para_clear_syncmd_array
 *
 * DESCRIPTION:
 *	 Clear all words saved in s_para_syn_cmd
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
 *	 2009-Mar-19 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
static void cli2_para_clear_syncmd_array(void)
{
	s_para_syn_cmd.para       = NULL;
	s_para_syn_cmd.used_word  = 0;
	s_para_syn_cmd.total_char = 0;
	s_para_syn_cmd.start      = NULL;
	s_para_syn_cmd.end        = NULL;
	s_para_syn_cmd.nouse      = 0;
	s_para_syn_cmd.name_buf   = NULL;
	s_para_syn_cmd.cur        = 0;
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 cli2_para_init_syncmd_array
 *
 * DESCRIPTION:
 *	 Allocate spaces and clear it for syntax command parsing when CLI init.
 *
 * INPUT:
 *	 NA
 *
 * OUTPUT:
 *	 NA
 *
 * RETURN:
 *	 TRUE  -- success
 *	 FALSE -- failure
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-19 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
static BOOL_T cli2_para_init_syncmd_array(void)
{
	I16_T count;

	count = 200; // start count of the nodes to be malloced
	s_para_syn_cmd.wordlist = CLI_MISC_Malloc(count * sizeof(CLI_PARA_WORD_T));
	if (!s_para_syn_cmd.wordlist)
	{
		CLI_MSG_PrtErrMsg(UTL_MISC_ERR_MEMORY_OVERFLOW);
		return FALSE;
	}

	s_para_syn_cmd.max_word = count;
	cli2_para_clear_syncmd_array();

	return TRUE;
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 cli2_para_destroy_syncmd_array
 *
 * DESCRIPTION:
 *	 Release resourses when CLI quit
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
 *	 2009-Mar-19 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
static void cli2_para_destroy_syncmd_array(void)
{
	CLI_MISC_Free(s_para_syn_cmd.wordlist);
	s_para_syn_cmd.max_word = 0;
	s_para_syn_cmd.wordlist = NULL;
}

/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 cli2_para_malloc_syncmd_node
 *
 * DESCRIPTION:
 *	 Allocate a node to save a CLI syntax word.
 *
 * INPUT:
 *	 NA
 *
 * OUTPUT:
 *	 NA
 *
 * RETURN:
 *	 -1 -- allocate spaces failed.
 *	 >= 0 -- index of the nodes.
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-19 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
static I32_T cli2_para_malloc_syncmd_node(void)
{
	CLI_PARA_WORD_T *p;
	I32_T total;

	if (s_para_syn_cmd.used_word >= s_para_syn_cmd.max_word)
	{
		total = s_para_syn_cmd.max_word + 50; /* increase 50 nodes. */
		p = CLI_MISC_Malloc(total * sizeof(CLI_PARA_WORD_T));
		if (!p)
		{
			CLI_MSG_PrtErrMsg(UTL_MISC_ERR_MEMORY_OVERFLOW);
			return -1;
		}

		memcpy (p, s_para_syn_cmd.wordlist,
			s_para_syn_cmd.max_word * sizeof(CLI_PARA_WORD_T));
		s_para_syn_cmd.max_word = total;
		CLI_MISC_Free(s_para_syn_cmd.wordlist);
		s_para_syn_cmd.wordlist = p;
	}

	return s_para_syn_cmd.used_word++;
}

/**************************************************************************
FUNCTION NAME:
	cli2_para_parse_help_msg

DESCRIPTION:
	Parse help message.

INPUT:
	array		: parameter word string array
	nodeidx		: which word

OUTPUT:
	array		: parameter word string array

RETURN:
	TRUE		: help message format is right
	FALSE		: help message format is wrong

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_para_parse_help_msg(
	IN OUT CLI_SYNCMD_PARA_T *array,
	IN I32_T nodeidx)
{
	array->start = CLI_MISC_Skip_WhiteSpace(array->start);
	array->end = array->start;
	if (*array->start == '#')
	{
		array->wordlist[nodeidx].help_en = NULL;
		array->wordlist[nodeidx].help_en_len = 0;

		array->wordlist[nodeidx].help_local = NULL;
		array->wordlist[nodeidx].help_local_len = 0;

		array->start++;
		array->end = array->start;
		array->wordlist[nodeidx].help_en = array->start;
		array->wordlist[nodeidx].help_local = array->wordlist[nodeidx].help_en;
		while (*array->end)
		{
			if (*array->end == '#')
			{
				if (array->wordlist[nodeidx].help_local == array->wordlist[nodeidx].help_en)
				{	/* get English help */
					array->wordlist[nodeidx].help_en_len = array->end - array->start;
					array->total_char += array->wordlist[nodeidx].help_en_len + 1;
					array->end++;
					array->start = CLI_MISC_Skip_WhiteSpace (array->end);
					array->wordlist[nodeidx].help_local_len = 0;
					if (*array->start == '#')
					{
						array->start++;
						array->end = array->start;
						array->wordlist[nodeidx].help_local = array->start;
						continue;
					}
					else
					{
						return TRUE;
					}

				}
				else
				{	/* get local help */
					array->wordlist[nodeidx].help_local_len = array->end - array->start;
					array->total_char += array->wordlist[nodeidx].help_local_len + 1;
					array->start = array->end + 1;
					return TRUE;
				}
			}
			else
			{

				array->end++;
			}
		}

		return FALSE;
	}
	else
	{
		if (array->wordlist[nodeidx].help_en)
		{
			array->total_char += array->wordlist[nodeidx].help_en_len + 1;
		}
		if (array->wordlist[nodeidx].help_local)
		{
			array->total_char += array->wordlist[nodeidx].help_local_len + 1;
		}
	}

	return TRUE;
}
/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 cli2_para_parse_syncmd_keyword
 *
 * DESCRIPTION:
 *	 Analysis keyword in CLI syntax command.
 *
 * INPUT:
 *	 array -- word array of the parameter in syntax command
 *	 nodeidx -- index of the node
 *
 * OUTPUT:
 *	 array -- word array of the parameter in syntax command
 *
 * RETURN:
 *	 TRUE -- success
 *	 FALSE -- failure
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-20 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
static BOOL_T cli2_para_parse_syncmd_keyword(
	IN OUT CLI_SYNCMD_PARA_T *array,
	IN I32_T nodeidx)
{
	/* get word end */
	array->end = array->start;
	while (CLI_MISC_Is_Keyword_Char (*array->end))
	{
		array->end++;
	}

	/* insert a word */
	if (array->end > array->start)
	{
		array->wordlist[nodeidx].type = CLI_TYPES_KEYWORD;
		array->wordlist[nodeidx].name = (I8_T *) array->start;
		array->wordlist[nodeidx].name_len = array->end - array->start;
	}
	else
	{
		return FALSE;
	}
	array->total_char += array->wordlist[nodeidx].name_len + 1;

	array->start = CLI_MISC_Skip_WhiteSpace(array->end);
	/* keyword with (<number>) => enum */
	if (* array->start == '(')
	{
		 array->start++; /* skip ( */
		array->wordlist[nodeidx].lparam = strtol(array->start, &array->end, 10);
		array->start = CLI_MISC_Skip_WhiteSpace(array->end);
		if (*array->start != ')')
		{
			return FALSE;
		}
		array->wordlist[nodeidx].type = CLI_TYPES_ENUM;
		array->start++;
	}
	else
	{
		array->wordlist[nodeidx].lparam = 0;
	}

	/* get help */
	array->start = CLI_MISC_Skip_WhiteSpace(array->start);
	array->wordlist[nodeidx].help_en = 0;
	array->wordlist[nodeidx].help_local_len = 0;

	array->wordlist[nodeidx].help_en_len = 0;
	array->wordlist[nodeidx].help_local_len = 0;
	if (*array->start == '#')
	{
		array->start++;
		array->end = array->start;
		array->wordlist[nodeidx].help_en = array->start;
		array->wordlist[nodeidx].help_local = array->wordlist[nodeidx].help_en;
		while (*array->end)
		{
			if (*array->end == '#')
			{
				if (array->wordlist[nodeidx].help_local == array->wordlist[nodeidx].help_en)
				{	/* get English help */
					array->wordlist[nodeidx].help_en_len = array->end - array->start;
					array->total_char += array->wordlist[nodeidx].help_en_len + 1;
					array->end++;
					array->start = CLI_MISC_Skip_WhiteSpace (array->end);
					array->wordlist[nodeidx].help_local_len = 0;
					if (*array->start == '#')
					{
						array->start++;
						array->end = array->start;
						array->wordlist[nodeidx].help_local = array->start;
						continue;
					}
					else
					{
						return TRUE;
					}

				}
				else
				{	/* get local help */
					array->wordlist[nodeidx].help_local_len = array->end - array->start;
					array->total_char += array->wordlist[nodeidx].help_local_len + 1;
					array->start = array->end + 1;
					return TRUE;
				}
			}
			else
			{
				array->end++;
			}
		}

		return FALSE;
	}

	return TRUE;
}

/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 cli2_para_parse_syncmd_para
 *
 * DESCRIPTION:
 *	 Check the correction of parameter string, and change it to a word array.
 *
 * INPUT:
 *	 array -- pointer of the word array
 *	 fatheridx -- -1: parameter word is out of all REQUIRED or OPTIONAL group
 *			   >= 0: the group node of REQUIRED or OPTIONAL group
 *
 * OUTPUT:
 *	 array -- all word in the group has been inserted to it.
 *
 * RETURN:
 *	 TRUE -- success
 *	 FALSE -- failure
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-20 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
static BOOL_T cli2_para_parse_syncmd_para(
	IN OUT CLI_SYNCMD_PARA_T *array,
	IN OUT I32_T fatheridx)
{
	I32_T 	nodeidx;
	I32_T 	ret_value;
	RPARAM 	count; /* count of the childs in OPTIONAL or REQUIRED group */
	I8_T 	*ptr;

	CLI_MISC_Assert(array);
	count = 1;

	array->start = CLI_MISC_Skip_WhiteSpace(array->start);

	while (*array->start)
	{
		switch (*array->start)
		{
		case CLI_DELIM_OPTIONAL_START:
			nodeidx = cli2_para_malloc_syncmd_node();
			if (nodeidx < 0)
			{
				return FALSE;
			}

			array->wordlist[nodeidx].type = CLI_TYPES_OPTIONAL;
			array->start++; /* skip symbol */
			if (cli2_para_parse_syncmd_para(array, nodeidx) != TRUE)
			{
				return FALSE;
			}
			break;

		case CLI_DELIM_REQUIRED_START:
			/* get an empty node */
			nodeidx = cli2_para_malloc_syncmd_node();
			if (nodeidx < 0)
			{
				return FALSE;
			}

			array->wordlist[nodeidx].type = CLI_TYPES_REQUIRED;
			array->start++; /* skip symbol */
			if (cli2_para_parse_syncmd_para(array, nodeidx) != TRUE)
			{
				return FALSE;
			}

			break;

		case '|':
			if (fatheridx < 0) /* not element list */
			{
				return FALSE;
			}

			array->start++; /* skip symbol */
			/* get an empty node */
			nodeidx = cli2_para_malloc_syncmd_node();
			if (nodeidx < 0)
			{
				return FALSE;
			}

			array->wordlist[nodeidx].type = CLI_TYPES_ELEMENT;
			array->nouse++;
			count++;
			break;

		case CLI_DELIM_OPTIONAL_END:
			if ((fatheridx < 0) || (array->wordlist[fatheridx].type != CLI_TYPES_OPTIONAL))
			{	/* symbol not matched */
				return FALSE;
			}

			/* get an empty node */
			nodeidx = cli2_para_malloc_syncmd_node();
			if (nodeidx < 0)
			{
				return FALSE;
			}

			array->wordlist[nodeidx].type = CLI_DELIM_OPTIONAL_END;
			array->wordlist[fatheridx].rparam = count;
			array->wordlist[fatheridx].lparam = 0;
			array->start++;

			/* check the [](n) that means the options must choose n items at least, choose n~count items */
			array->start = CLI_MISC_Skip_WhiteSpace(array->start);
			if (*array->start == '(')
			{
				array->start++;
				array->wordlist[fatheridx].lparam = strtoul(array->start, &array->end, 10);
				array->start = CLI_MISC_Skip_WhiteSpace(array->end);
				if (*array->start != ')')
				{
					return FALSE;
				}

				array->start++;
			}

			array->nouse++;
			return TRUE;
			break;

		case CLI_DELIM_REQUIRED_END:
			if ((fatheridx < 0) || (array->wordlist[fatheridx].type != CLI_TYPES_REQUIRED))
			{	/* symbol not matched */
				return FALSE;
			}

			/* get an empty node */
			nodeidx = cli2_para_malloc_syncmd_node();
			if (nodeidx < 0)
			{
				return FALSE;
			}

			array->wordlist[nodeidx].type = CLI_DELIM_REQUIRED_END;
			array->wordlist[fatheridx].rparam = count;
			array->wordlist[fatheridx].lparam = 1;
			array->start++;

			/* check the {}(+n) that means the options can repeat n times */
			array->start = CLI_MISC_Skip_WhiteSpace(array->start);
			if (*array->start == '(')
			{
				array->start++;
				array->start = CLI_MISC_Skip_WhiteSpace(array->start);
				if (*array->start == '+')
				{
					array->start++;
					array->wordlist[fatheridx].lparam = strtoul(array->start, &array->end, 10);
				}
				else
				{
					/* just skip the number */
					strtoul(array->start, &array->end, 10);
				}

				array->start = CLI_MISC_Skip_WhiteSpace(array->end);
				if (*array->start != ')')
				{
					return FALSE;
				}

				array->start++;
			}

			array->nouse++;
			return TRUE;
			break;

		case '<': /* alias in "<>" */
			array->start++; /* skip '<' */
			array->end = array->start;
			while (*array->end && (*array->end != '>'))
			{
				array->end++;
			}

			if (*array->end != '>')
			{
				return FALSE;
			}

			/* get an empty node */
			nodeidx = cli2_para_malloc_syncmd_node();
			if (nodeidx < 0)
			{
				return FALSE;
			}

			ret_value = CLI_ALIAS_Parse(array->start, array->end, &array->wordlist[nodeidx]);
			if (ret_value != TRUE)
			{
				return FALSE;
			}

			if (array->wordlist[nodeidx].help_local == NULL)
			{
				array->wordlist[nodeidx].help_local = array->wordlist[nodeidx].help_en;
			}

			array->total_char += array->wordlist[nodeidx].name_len + 1;
			array->start = array->end + 1; // skip '>'
			cli2_para_parse_help_msg(array, nodeidx);
			break;

		case ' ': /* fall through (skip ' ' and <tab>) */
		case '\t':
			array->start++;
			break;

		default: /* add a keyword */
			/* get an empty node */
			nodeidx = cli2_para_malloc_syncmd_node();
			if (nodeidx < 0)
			{
				return FALSE;
			}

			if (isupper(*array->start))
			{
				/* first check if the word is a keyword (in CLIG1) like SE0(n)
				 * for the word which firt character is upper but the end attach number include by brace
				 * the word should be keyword */
				ptr = array->start;
				while (CLI_MISC_Is_Keyword_Char (*ptr))
				{
					ptr++;
				}

				ptr = CLI_MISC_Skip_WhiteSpace(ptr);
				if (*ptr != '(')
				{
					/* alias in uppercase */
					array->end = array->start;
					while (CLI_MISC_Is_Alias_Char_OutAngleBrackets(*array->end))
					{
						array->end++;
					}

					ret_value = CLI_ALIAS_Parse (array->start, array->end, &array->wordlist[nodeidx]);
					if (ret_value != TRUE)
					{
						return FALSE;
					}

					array->start = array->end;
					array->total_char += array->wordlist[nodeidx].name_len + 1;
					cli2_para_parse_help_msg(array, nodeidx);
					break;
				}
			}

			/* keyword */
			ret_value = cli2_para_parse_syncmd_keyword(array, nodeidx);
			if (ret_value != TRUE)
			{
				return FALSE;
			}
			break;
		}
	}

	if (fatheridx >= 0)
	{
		return FALSE;
	}

	return TRUE;
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 cli2_para_reg_syncmd_tree
 *
 * DESCRIPTION:
 *	 Register all words in parameter to parameter tree.
 *
 * INPUT:
 *	 array -- word info of the parameter and buffer info of the syntax tree.
 *	 parent -- NULL: nodes is out of all REQUIRED or OPTIONAL group
 *			   not NULL: the group node of REQUIRED or OPTIONAL group
 * OUTPUT:
 *	 array -- word info and buffer info updated.
 *	 parent -- NULL: nodes is out of all REQUIRED or OPTIONAL group
 *			   not NULL: the group node of REQUIRED or OPTIONAL group
 *
 * RETURN:
 *	 //###
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-20 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
static I32_T cli2_para_reg_syncmd_tree(
	IN OUT CLI_SYNCMD_PARA_T *array,
	IN OUT CLI_PRIV_PARA_SYN_NODE_T *parent)
{
	CLI_PRIV_PARA_SYN_NODE_T *current;
	CLI_PRIV_PARA_SYN_NODE_T *prev;
	I32_T child; // index_of_child in the parent

	prev = NULL;
	child = 0;
	while (array->cur < array->used_word)
	{
		switch (array->wordlist[array->cur].type)
		{
			case CLI_TYPES_OPTIONAL:
			case CLI_TYPES_REQUIRED:
				/*
				 * Each element in REQUIRED or OPTIONAL is saved in the
				 *	  child[rparam] of the REQUIRED or OPTIONAL node.
				 *
				 */
				/* get an empty node */
				if ((prev == NULL) && (parent != NULL))
				{
					// first node of the element
					current = parent->child + child;
				}
				else
				{
					// get an empty node to save the word
					current = array->para_node++;
					// insert the node to para tree
					if (prev != NULL)
					{
						prev->sibling = current;
					}
				}

				// fill the node
				current->parent = parent;
				current->type = array->wordlist[array->cur].type;
				current->lparam = array->wordlist[array->cur].lparam;
				current->rparam = array->wordlist[array->cur].rparam;
				current->child = array->para_node;
				current->match_count = 0;
				array->para_node += current->rparam;
				array->cur++;

				cli2_para_reg_syncmd_tree(array, current);
				prev = current;
				break;

			case CLI_TYPES_ELEMENT: // next element in REQUIRED or OPTIONAL
				child++;
				prev = NULL;
				array->cur++; // skip the node
				break;

			case CLI_DELIM_OPTIONAL_END: // end of the REQUIRED or OPTIONAL
			case CLI_DELIM_REQUIRED_END:
				array->cur++; // skip the node
				return TRUE;
				break;

			case CLI_TYPES_KEYWORD: // fall through
			case CLI_TYPES_ENUM:
				// get an empty node
				if ((prev == NULL) && (parent != NULL))
				{
					// first node of the element
					current = parent->child + child;
				}
				else
				{
					current = array->para_node++;
					if (prev != NULL)
					{
						prev->sibling = current;
					}
				}

				// fill the node
				current->parent = parent;
				current->type = array->wordlist[array->cur].type;
				current->lparam = array->wordlist[array->cur].lparam;
				current->rparam = array->wordlist[array->cur].rparam;
				// current->help_en = array->wordlist[array->cur].help_en;
				// current->help_local = array->wordlist[array->cur].help_local;
				current->name = array->name_buf;
				strncpy(current->name, array->wordlist[array->cur].name,
						array->wordlist[array->cur].name_len);
				array->name_buf += array->wordlist[array->cur].name_len + 1;
				if (array->wordlist[array->cur].help_en_len)
				{
					current->help_en = array->name_buf;
					strncpy(current->help_en, array->wordlist[array->cur].help_en,
							array->wordlist[array->cur].help_en_len);
					current->help_en[array->wordlist[array->cur].help_en_len] = '\0';
					array->name_buf += array->wordlist[array->cur].help_en_len + 1;
				}
				else
				{
					current->help_en = NULL;
				}
				if (array->wordlist[array->cur].help_local_len)
				{
					current->help_local = array->name_buf;
					strncpy(current->help_local, array->wordlist[array->cur].help_local,
							array->wordlist[array->cur].help_local_len);
					current->help_local[array->wordlist[array->cur].help_local_len] = '\0';
					array->name_buf += array->wordlist[array->cur].help_local_len + 1;
				}
				else
				{
					current->help_local = NULL;
				}
				current->sibling = NULL;
				current->child = NULL;
				prev = current;
				array->cur++;
				break;

			default: // alias
				// get an empty node
				if ((prev == NULL) && (parent != NULL))
				{
					// first node of the element
					current = parent->child + child;
				}
				else
				{
					current = array->para_node++;
					if (prev != NULL)
					{
						prev->sibling = current;
					}
				}

				// fill the node
				current->parent = parent;
				current->type = array->wordlist[array->cur].type;
				current->lparam = array->wordlist[array->cur].lparam;
				current->rparam = array->wordlist[array->cur].rparam;
#if 0
				current->help_en = (I8_T *)array->wordlist[array->cur].help_en;
				current->help_local = (I8_T *)array->wordlist[array->cur].help_local;
#else
				if (array->wordlist[array->cur].help_en_len)
				{
					current->help_en = array->name_buf;
					strncpy(current->help_en, array->wordlist[array->cur].help_en,
							array->wordlist[array->cur].help_en_len);
					current->help_en[array->wordlist[array->cur].help_en_len] = '\0';

					array->name_buf += array->wordlist[array->cur].help_en_len + 1;
				}
				else
				{
					current->help_en = (I8_T *)array->wordlist[array->cur].help_en;

				}
				if (array->wordlist[array->cur].help_local_len)
				{
					current->help_local = array->name_buf;
					strncpy(current->help_local, array->wordlist[array->cur].help_local,
							array->wordlist[array->cur].help_local_len);
					current->help_local[array->wordlist[array->cur].help_local_len] = '\0';
					array->name_buf += array->wordlist[array->cur].help_local_len + 1;
				}
				else
				{
					current->help_local = current->help_en;
				}
#endif
				current->name = array->name_buf;
				strncpy(current->name, array->wordlist[array->cur].name,
						array->wordlist[array->cur].name_len);
				array->name_buf += array->wordlist[array->cur].name_len + 1;
				current->sibling = NULL;
				current->child = NULL;
				prev = current;
				array->cur++;
				break;
		}
	}

	return TRUE;
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 CLI_PARA_Parse_SyncmdPara
 *
 * DESCRIPTION:
 *	 Check the parameter string in syntax command is correct or not, if it is
 *		 correct, register it.
 *
 * INPUT:
 *	 str     -- parameter string in syntax command
 *	 pp_syn  -- address of the pointer to get the result parameter tree
 *
 * OUTPUT:
 *	 *pp_syn -- pointer of the parameter tree.
 *
 * RETURN:
 *	 TRUE  -- success
 *	 FALSE -- failure
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-19 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
BOOL_T CLI_PARA_Parse_SyncmdPara
	(
	IN const I8_T 						*str,
	IN OUT CLI_PRIV_PARA_SYN_NODE_T 	**pp_syn
	)
{
	CLI_DBG_ENTER(l_mdl_id);

	CLI_SYNCMD_PARA_T *array;
	I32_T count; // count of nodes in para tree
	I32_T size; // size of memory need to be allocated
#ifdef WIN32_DEBUG
	I32_T i;
#endif
	// I8_T *p;

	CLI_MISC_Assert(str);

	str = CLI_MISC_Skip_WhiteSpace(str);
	if (*str == '\0') // parameter string is empty
	{
		*pp_syn = NULL;
		CLI_DBG_LEAVE(l_mdl_id);
		return TRUE;
	}

	/* clear syntax command array for new parsing */
	array = &s_para_syn_cmd;
	cli2_para_clear_syncmd_array();
	array->para = str;
	array->start = (I8_T *)str;

	/* parse syntax parameter string to words list.
	 * lexical for parameter part of the syntax command
	 */
	if (cli2_para_parse_syncmd_para(array, -1) != TRUE)
	{
		*pp_syn = NULL;
		CLI_DBG_LEAVE(l_mdl_id);
		return FALSE;
	}

	// syntax for parameter part of the syntax command(Generate parameter tree).

	// get all memory of the params and names
	count = array->used_word - array->nouse;
	size = array->total_char + (count) * sizeof(CLI_PRIV_PARA_SYN_NODE_T);
	array->para_node = CLI_MISC_Malloc(size);
	*pp_syn = array->para_node;
	if (array->para_node == NULL)
	{
		CLI_DBG_LEAVE(l_mdl_id);
		return FALSE;
	}

	memset(array->para_node, 0, size);
	array->name_buf = (I8_T *) (array->para_node + count);
	cli2_para_reg_syncmd_tree(array, NULL);

	CLI_DBG_LEAVE(l_mdl_id);
	return TRUE;
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 CLI_Para_Check_FirstUnitIsStringLike
 *
 * DESCRIPTION:
 *	 Check the first word of parameter is StringLike or not.
 *
 * INPUT:
 *	 root -- start node of the parameter tree.
 *
 * OUTPUT:
 *	 *count -- Count of the string like nodes in the first word.
 *
 * RETURN:
 *	 NA
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-20 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
void CLI_Para_Check_FirstUnitIsStringLike(
	IN const CLI_PRIV_PARA_SYN_NODE_T * root,
	OUT I32_T *count)
{
	const CLI_PRIV_PARA_SYN_NODE_T *current;
	I32_T i;

	if (root == NULL)
	{
		return;
	}
	current = root;
	switch (current->type)
	{
		case CLI_TYPES_OPTIONAL: // fall through
		case CLI_TYPES_REQUIRED:
			for (i = 0; i < current->rparam; i++)
			{
				CLI_Para_Check_FirstUnitIsStringLike(
					current->child + i, count);
			}
			return;

		case CLI_TYPES_STRING:
		case CLI_TYPES_STRING_WITHOUT_WHITESPACE:
		case CLI_TYPES_NAME:
			(*count)++;
			return;

		default:
			return;
	}

	return;
}

/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 bc_cli_para_init
 *
 * DESCRIPTION:
 *	 Init resources for CLI para
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
 *	 2009-Mar-20 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
I32_T bc_cli_para_init(void)
{
	BOOL_T ret_bool;

	CLI_TYPES_Init();
	ret_bool = cli2_para_init_syncmd_array();
	if (FALSE == ret_bool)
	{
		return -1;
	}

	return 0;
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 CLI_PARA_Destroy
 *
 * DESCRIPTION:
 *	 Release resources allocated by CLI para
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
 *	 2009-Mar-20 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
void CLI_PARA_Destroy(void)
{
	cli2_para_destroy_syncmd_array();
}

/**************************************************************************
FUNCTION NAME:
	cli2_para_clear_all_match_tag

DESCRIPTION:
	Clear all parameter node tag(all sibling and child of input node).

INPUT:
	root		: root parameter node

OUTPUT:
	NA

RETURN:
	NA

NOTES:

HISTORY:

**************************************************************************/
static void cli2_para_clear_all_match_tag(CLI_PRIV_PARA_SYN_NODE_T *root)
{
	I32_T i;

	while (root)
	{
		switch (root->type)
		{
			case CLI_TYPES_REQUIRED: /* fall through */
			case CLI_TYPES_OPTIONAL:
				for (i = 0; i < root->rparam; i++)
				{
					cli2_para_clear_all_match_tag(root->child + i);
				}

				root->match_count = 0;
				root = root->sibling;
				continue;
				break;

			default:
				root->match_count = 0;
				root = root->sibling;
				continue;
		}
	}
}

/**************************************************************************
FUNCTION NAME:
	cli2_para_clear_child_tag

DESCRIPTION:
	Clear children tag of input parameter node.

INPUT:
	para_node		: parent node

OUTPUT:
	NA

RETURN:
	NA

NOTES:

HISTORY:

**************************************************************************/
static void cli2_para_clear_child_tag(CLI_PRIV_PARA_SYN_NODE_T *para_node)
{
	I32_T i;

	switch (para_node->type)
	{
	case CLI_TYPES_REQUIRED: /* fall through */
	case CLI_TYPES_OPTIONAL:
		for (i = 0; i < para_node->rparam; i++)
		{
			cli2_para_clear_all_match_tag(para_node->child + i);
		}
		break;

	default: /* other types of nodes don't have child */
		break;
	}
}

/**************************************************************************
FUNCTION NAME:
	cli2_para_check_matchChildNum

DESCRIPTION:
	Check the matched children number of input parameter node.

INPUT:
	para_node		: parent node

OUTPUT:
	NA

RETURN:
	NA

NOTES:

HISTORY:

**************************************************************************/
static I32_T cli2_para_check_matchChildNum(CLI_PRIV_PARA_SYN_NODE_T *para_node)
{
	I32_T matched_num, temp_num;
	UI32_T i;
	CLI_PRIV_PARA_SYN_NODE_T *node_sibling;

	matched_num = 0;

	if ((para_node->type  == CLI_TYPES_REQUIRED)
		|| (para_node->type  == CLI_TYPES_OPTIONAL))
	{
		/* check the chosen children number */
		for (i = 0; i < para_node->rparam; i++)
		{
			temp_num = 0;

			switch (para_node->child[i].type)
			{
				case CLI_TYPES_REQUIRED:
					temp_num = cli2_para_check_matchChildNum(&para_node->child[i]);
					break;

				case CLI_TYPES_OPTIONAL:
					temp_num = cli2_para_check_matchChildNum(&para_node->child[i]);
					/* for this case /test {aaa | [xxx] bbb | ccc} */
					if (temp_num >= para_node->child[i].lparam)
					{
						if (temp_num == 0)
						{
							/* check the next element and decide this if this layer optional is matched */
							node_sibling = para_node->child[i].sibling;
							while (node_sibling)
							{
								if ((node_sibling->type == CLI_TYPES_REQUIRED)
									|| (node_sibling->type == CLI_TYPES_OPTIONAL))
								{
									temp_num = cli2_para_check_matchChildNum(node_sibling);
									if (node_sibling->type == CLI_TYPES_OPTIONAL)
									{
										if (temp_num >= node_sibling->lparam)
										{
											if (temp_num == 0)
											{
												node_sibling = node_sibling->sibling;
												continue;
											}
										}
										else
										{
											/* first element don't match */
											temp_num = 0;
										}
									}
								}
								else
								{
									temp_num = node_sibling->match_count;
								}
								break;
							}
						}
					}
					else
					{
						/* first element don't match */
						temp_num = 0;
					}
					break;

				default:
					temp_num = para_node->child[i].match_count;
					break;
			}

			/* the child has been chosen, match number ++ */
			if (temp_num > 0)
			{
				matched_num++;
			}
		}

		/* for the required can be repeated, so need add the repeated time */
		if (para_node->type  == CLI_TYPES_REQUIRED)
		{
			/* the repeated time can be increased and has matched child */
			if ((para_node->flag & CLI_PARA_REQUIRE_REPEAT_FLAG) && (matched_num > 0))
			{
				matched_num += para_node->match_count;
			}
			else
			{
				/* it's not time for increasing repeated time or don't have matched child */
				matched_num = para_node->match_count;
			}
		}
	}

	return matched_num;
}

/**************************************************************************
FUNCTION NAME:
	cli2_para_update_all_tag

DESCRIPTION:
	Update all parameter tag.

INPUT:
	root		: root node

OUTPUT:
	NA

RETURN:
	NA

NOTES:

HISTORY:

**************************************************************************/
static void cli2_para_update_all_tag(CLI_PRIV_PARA_SYN_NODE_T *root)
{
	CLI_PRIV_PARA_SYN_NODE_T *sibling_node;
	UI32_T i, matchNum;

	sibling_node = root;

	while (sibling_node)
	{
		/* only the {} or [] need update the matched tag */
		if ((sibling_node->type  == CLI_TYPES_REQUIRED)
			|| (sibling_node->type  == CLI_TYPES_OPTIONAL))
		{
			matchNum = cli2_para_check_matchChildNum(sibling_node);
			/* check the required repeated time increase */
			if (sibling_node->type  == CLI_TYPES_REQUIRED)
			{
				if ((sibling_node->flag & CLI_PARA_REQUIRE_REPEAT_FLAG)
					&& (matchNum > sibling_node->match_count))
				{
					/* already increased, set the repeat flag is FALSE and before next repeat don't change the time */
					sibling_node->flag &= (~CLI_PARA_REQUIRE_REPEAT_FLAG);
				}
			}
			sibling_node->match_count = matchNum;

			/* for update the children */
			for (i = 0; i < sibling_node->rparam; i++)
			{
				cli2_para_update_all_tag(&sibling_node->child[i]);
			}
		}

		sibling_node = sibling_node->sibling;
	}
}

/**************************************************************************
FUNCTION NAME:
	cli2_para_get_all_current_node

DESCRIPTION:
	Get all current possible parameter node.

INPUT:
	p_node			: current input node

OUTPUT:
	p_result_node	: current possible parameter node
	count			: possible parameter node number
	finish			: end flag (if could input <CR>)

RETURN:
	NA

NOTES:

HISTORY:

**************************************************************************/
static void cli2_para_get_all_current_node(
	IN CLI_PRIV_PARA_SYN_NODE_T*p_node,
	IN OUT CLI_PRIV_PARA_SYN_NODE_T **p_result_node,
	IN OUT I32_T *count,
	OUT BOOL_T *finish)
{
	I32_T i;
	I32_T match_count_max = 0;

	if (!p_node)
	{
		*finish = TRUE;
		return;
	}

	while (p_node)
	{
		/* for CLI G2 such as :  [a | b] <c> , the "a", "b", "c" can be chosen next,
		 * so the current nodes are "a", "b", "c"
		 * p_node->match_count means the chosen optionals number for this parameter layer
		 */
		if (p_node->type == CLI_TYPES_OPTIONAL)
		{
			match_count_max = p_node->rparam;

			if (p_node->match_count < match_count_max)
			{
				for (i = 0; i < p_node->rparam; i++)
				{
					cli2_para_get_all_current_node(p_node->child + i, p_result_node, count, finish);
				}
			}

			if (p_node->match_count >= p_node->lparam)
			{
				if (!p_node->sibling && !p_node->parent)
				{
					*finish = TRUE;
				}

				p_node = p_node->sibling;
			}
			else
			{
				return;
			}
		}

		/* for CLI G2 such as :  {a | b} <c> , the "a" or "b" can be chosen next,
		 * so the current nodes are "a", "b"
		 * for {a | b}(+n) c, the "a" and "b" can repeat n times
		 * and if n>1 and "a" or "b" has been chosen, the "c" could been chosen too.
		 * p_node->lparam means the times that can be repeatted.
		 * p_node->match_count means the repeatted times for this parameter layer
		 */
		else if (p_node->type == CLI_TYPES_REQUIRED)
		{
			/* get the times that can be repeatted */
			match_count_max = p_node->lparam;

			if (p_node->match_count < match_count_max)
			{
				/* the required optional can be repeatted, so clear the child chosen tag */
				cli2_para_clear_child_tag(p_node);
				/* set the repeat flag is TRUE, that means the required repeated time can be increased */
				p_node->flag |= CLI_PARA_REQUIRE_REPEAT_FLAG;

				for (i = 0; i < p_node->rparam; i++)
				{
					cli2_para_get_all_current_node(p_node->child + i, p_result_node, count, finish);
				}
			}

			/* has been chosen */
			if (p_node->match_count > 0)
			{
				if (!p_node->sibling && !p_node->parent)
				{
					*finish = TRUE;
				}

				p_node = p_node->sibling;
			}
			else
			{
				return;
			}
		}
		/* such as : <a> {b | c} , must choose "a" first, so the current node is "a" */
		else
		{
			if (p_node->match_count <= 0)
			{
				p_result_node[*count] = p_node;
				*count += 1;
			}

			return;
		}

	}
}



/**************************************************************************
FUNCTION NAME:
	cli2_para_get_parent_node_loop

DESCRIPTION:
	Get possible parameter nodes on parent node. (loop check)

INPUT:
	p_node			: current input node

OUTPUT:
	p_result_node		: current possible parameter node
	count			: possible parameter node number
	finish			: end flag (if could input <CR>)

RETURN:
	NA

NOTES:

HISTORY:

**************************************************************************/
static void cli2_para_get_parent_node_loop(
	IN CLI_PRIV_PARA_SYN_NODE_T*p_node,
	IN OUT CLI_PRIV_PARA_SYN_NODE_T **p_result_node,
	IN OUT I32_T *count,
	OUT BOOL_T *finish)
{
	if (!p_node)
	{
		return;
	}
	if (!p_node->parent)
	{
		*finish = TRUE;
		return;
	}

	p_node = p_node->parent;

	/* get all possible child and sibling */
	if ((p_node->type == CLI_TYPES_OPTIONAL)
		|| (p_node->type == CLI_TYPES_REQUIRED))
	{
		cli2_para_get_all_current_node(p_node, p_result_node, count, finish);
	}
	else
	{
		cli2_para_get_all_current_node(p_node->sibling, p_result_node, count, finish);
	}

	/* get possible parent */
	while (((p_node->type == CLI_TYPES_OPTIONAL) && (p_node->match_count >= p_node->lparam))
		    || ((p_node->type == CLI_TYPES_REQUIRED) && (p_node->match_count > 0)))
	{
		*finish = FALSE;
		if (p_node->sibling)
		{
			p_node = p_node->sibling;
			continue;
		}
		else if (p_node->parent)
		{
			cli2_para_get_parent_node_loop (p_node, p_result_node, count, finish);
			return;
		}
		else
		{
			*finish = TRUE;
			return;
		}
	}

}

/**************************************************************************
FUNCTION NAME:
	cli2_para_get_all_parent_node

DESCRIPTION:
	Get possible parameter nodes on parent node.

INPUT:
	p_node			: current input node

OUTPUT:
	p_result_node		: possible parameter node on parent node
	count			: possible parameter node number
	finish			: end flag (if could input <CR>)

RETURN:
	NA

NOTES:

HISTORY:

**************************************************************************/
static void cli2_para_get_all_parent_node(
	IN CLI_PRIV_PARA_SYN_NODE_T*p_node,
	IN OUT CLI_PRIV_PARA_SYN_NODE_T **p_result_node,
	IN OUT I32_T *count,
	OUT BOOL_T *finish)
{
	I32_T i, j, k;

	cli2_para_get_parent_node_loop(p_node, p_result_node, count, finish);

	if (*count < 2)
	{
		return;
	}

	/* maybe have same nodes ex: [[aa | bb | cc](1) | a | b | c] */
	for (i = 0; i < (*count - 1); i++)
	{
		for (j = i + 1; j < *count; j++)
		{
			/* has the same parameter node */
			if (p_result_node[i] == p_result_node[j])
			{
				/* remove the same node */
				for (k = j; k < (*count - 1); k++)
				{
					p_result_node[k] = p_result_node[k+1];
				}
				p_result_node[k] = NULL;
				*count -= 1;
				j--;
			}
		}
	}
}

/**************************************************************************
FUNCTION NAME:
	cli2_para_get_all_next_node

DESCRIPTION:
	Get possible next parameter nodes for input node.

INPUT:
	p_node			: current input node

OUTPUT:
	p_result_node		: possible next parameter node
	count			: possible parameter node number
	finish			: end flag (if could input <CR>)

RETURN:
	NA

NOTES:

HISTORY:

**************************************************************************/
static void cli2_para_get_all_next_node(
	IN CLI_PRIV_PARA_SYN_NODE_T*p_node,
	OUT CLI_PRIV_PARA_SYN_NODE_T **p_result_node,
	OUT I32_T *count,
	OUT BOOL_T *finish)
{
	BOOL_T finish_sibling = FALSE;
	BOOL_T finish_parent = FALSE;

	if (!p_node->sibling)
	{
		cli2_para_get_all_parent_node (p_node, p_result_node, count, &finish_parent);
		*finish = finish_parent;
		return;
	}
	else
	{
		cli2_para_get_all_current_node(p_node->sibling, p_result_node, count, &finish_sibling);

		p_node = p_node->sibling;
		/* get possible parent */
		while ((p_node->type == CLI_TYPES_OPTIONAL && p_node->match_count >= p_node->lparam)
			|| (p_node->type == CLI_TYPES_REQUIRED && p_node->match_count > 0))
		{
			if (p_node->sibling)
			{
				p_node = p_node->sibling;
				continue;
			}
			else
			{
				cli2_para_get_all_parent_node (p_node, p_result_node, count, &finish_parent);
				*finish = finish_parent;
				return;
			}
		}
	}

	*finish = finish_sibling;
	return;
}

/**************************************************************************
FUNCTION NAME:
	cli2_para_check_most_match_node

DESCRIPTION:
	Check if has most matched node.

INPUT:
	para_string		: parameter string
	result			: find result (need to change)

OUTPUT:
	result			: find result

RETURN:
	TRUE			: found the most matched node
	FALSE			: didn't find

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_para_check_most_match_node(
	IN I8_T *para_string,
	IN OUT CLI_PARA_CMD_TAB_LIST_T *result)
{
	CLI_DBG_ENTER(l_mdl_id);
	CLI_DBG_CPL(l_mdl_id, "para_string=%s,count=%d,most_match=%d\r\n", para_string, result->count, result->most_match);

	I32_T i;
	I32_T lowPriortyNum, highPriortyNum, matchSite;

	if (result->count == 0)
	{
		/* no nodes match */
		CLI_DBG_LEAVE(l_mdl_id);
		return FALSE;
	}

	if ((result->most_match == FALSE) && (result->count > 1))
	{
		/* match too many nodes, need to check */
		lowPriortyNum = 0;
		highPriortyNum = 0;
		matchSite = 0;

		for (i = 0; i < result->count; i++)
		{
			switch (result->list[i]->type)
			{
			case CLI_TYPES_STRING:
			case CLI_TYPES_STRING_WITHOUT_WHITESPACE:
			case CLI_TYPES_NAME:
				lowPriortyNum++;
				break;

			default:
				matchSite = i;
				highPriortyNum++;
				break;
			}
		}

		if (highPriortyNum == 1)
		{
			/* set the high priorty node is the most match node and change the result */
			result->list[0] = result->list[matchSite];
			/* attach the most match parameter value at the end of current value */
			CLI_TYPES_GetValue(result->list[0], para_string, result);
			result->count = 1;

			CLI_DBG_LEAVE(l_mdl_id);
			return TRUE;
		}
		else
		{
			/* highPriortyNum = 0 && lowPriortyNum > 1 or highPriortyNum > 1*/
			CLI_DBG_LEAVE(l_mdl_id);
			return FALSE;
		}
	}

	/* have most match node or just one node match */
	CLI_DBG_LEAVE(l_mdl_id);
	return TRUE;
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 cli2_para_get_match_list
 *
 * DESCRIPTION:
 *	 Check an user command and get it's value or help.
 *
 * INPUT:
 *	 cmd    -- user command
 *	 root   -- parameter tree
 *	 result -- point to the result buffer
 *
 * OUTPUT:
 *	 result -- the result
 *
 * RETURN:
 *	 TRUE : success
 *	 FALSE: failure
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-23 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
static BOOL_T cli2_para_get_match_list(
	IN CLI_PRIV_USRCMD_WORDLIST_T *pwords,
	IN CLI_PRIV_PARA_SYN_NODE_T *root,
	IN OUT CLI_PARA_CMD_TAB_LIST_T *result,
	IN I32_T flags)
{
	CLI_DBG_ENTER(l_mdl_id);

	I8_T word[CLI_MAX_CMD_PARA_LEN + 1];
	CLI_PRIV_PARA_SYN_NODE_T *current;
	CLI_PRIV_PARA_SYN_NODE_T *cur_posible_node[CLI_PARA_CMD_MAX_POSIBLE_NODE];
	I32_T count;
	I32_T max_word;
	BOOL_T first;
	cli_value_t *p;
	I32_T i, restore_index;

	switch (flags)
	{
	case CLI_PARA_GET_CUR_WORDLIST:
		max_word = pwords->count - 2;
		break;

	case CLI_PARA_GET_VALUE: /* fall through */
	case CLI_PARA_GET_NEXT_WORDLIST:
		max_word = pwords->count - 1;
		break;

	default:
		max_word = pwords->count - 1;
		break;
	}

	current = root;
	result->count = 0;
	first = TRUE;
	while (pwords->index < max_word)
	{
		restore_index = pwords->index;
		count = 0;
		result->finish = FALSE;

		if (first)
		{
			cli2_para_get_all_current_node(current, cur_posible_node, &count, &result->finish);
			first = FALSE;
		}
		else
		{
			cli2_para_get_all_next_node(current, cur_posible_node, &count, &result->finish);
		}
		CLI_DBG_CPL(l_mdl_id, "count=%d, result->finish=%d\r\n", count, result->finish);

		/* match all posible node */
		if (pwords->len[pwords->index] > ( CLI_MAX_CMD_PARA_LEN - 1))
		{
			pwords->len[pwords->index] = CLI_MAX_CMD_PARA_LEN - 1;
		}

		strncpy(word, pwords->word[pwords->index], pwords->len[pwords->index]);
		word[pwords->len[pwords->index]] = '\0';
		result->lastword = result->tail; /* save it for memory free */
		result->cur_posible_node_count = 0;
		result->most_match = FALSE;
		result->count = 0;
		result->error_pos = pwords->word[pwords->index] - pwords->usrcmd;

		for (i = 0; i < count; i++)
		{
			CLI_DBG_CPL(l_mdl_id, "match_count=%d, type=%d\r\n", cur_posible_node[i]->match_count, cur_posible_node[i]->type);
			if (cur_posible_node[i]->match_count == 0)
			{
				if (CLI_TYPES_GetValue(cur_posible_node[i], word, result) == TRUE)
				{
					if (cur_posible_node[i]->type != CLI_TYPES_SENTENCE)
					{
						/* if the same layer have sentence parameter, now the other type parameter is matched
						 * so the index should be restored and search the next word */
						pwords->index = restore_index;
					}

					if (result->most_match)
					{
						break;
					}
				}
			}
		}

		if (cli2_para_check_most_match_node(word, result) == FALSE)
		{
			/* don't find the most matched node */
			CLI_DBG_LEAVE(l_mdl_id);
			return FALSE;
		}

		/* the match_count should changed as below */
		result->list[0]->match_count = 1;
		cli2_para_update_all_tag(root);

		/* release not the most matched nodes */
		if (result->tail)
		{
			while (result->lastword->next != result->tail)
			{
				// free nodes.
				p = result->lastword->next;
				result->lastword->next = p->next;
				CLI_MISC_Free(p->value);
				if (p->name != NULL)
				{
					CLI_MISC_Free(p->name);
				}
				CLI_MISC_Free(p);
			}
		}

		/* skip forword a word */
		current = result->list[0];
		pwords->index++;
	}

	/* get last word's list */
	result->finish = FALSE;
	count = 0;
	if (first)
	{
		cli2_para_get_all_current_node(current, cur_posible_node, &count, &result->finish);
	}
	else
	{
		cli2_para_get_all_next_node(current, cur_posible_node, &count, &result->finish);
	}

	switch (flags)
	{
	case CLI_PARA_GET_VALUE: /* fall through */
		if ((result->finish != TRUE) || (pwords->index < pwords->count - 1))
		{
			/* command not finished */
			if (pwords->index == pwords->count - 1)
			{
				result->error_pos = pwords->word[pwords->index] - pwords->usrcmd;
			}

			CLI_DBG_LEAVE(l_mdl_id);
			return FALSE;
		}

		result->list[0] = current;
		result->cur_posible_node_count = 1;

		CLI_DBG_LEAVE(l_mdl_id);
		return TRUE;
		break;

	case CLI_PARA_GET_CUR_WORDLIST:
		/* match all posible node */
		result->finish = FALSE;
		if (pwords->len[pwords->index] >( CLI_MAX_CMD_PARA_LEN - 1))
		{
			pwords->len[pwords->index] = CLI_MAX_CMD_PARA_LEN - 1;
		}

		strncpy(word, pwords->word[pwords->index], pwords->len[pwords->index]);
		word[pwords->len[pwords->index]] = '\0';
		result->lastword = result->tail; /* save it for memory free */
		result->cur_posible_node_count = 0;
		result->most_match = FALSE;
		result->count = 0;
		result->error_pos = pwords->word[pwords->index] - pwords->usrcmd;

		for (i = 0; i < count; i++)
		{
			if (cur_posible_node[i]->match_count == 0)
			{
				CLI_TYPES_Get_CurrentHelp (cur_posible_node[i], word, result);
			}
		}
		if (result->count == 0)
		{
			CLI_DBG_LEAVE(l_mdl_id);
			return FALSE;
		}

		/* release matched nodes */
		if (result->tail)
		{
			while (result->lastword->next != result->tail)
			{
				// free nodes.
				p = result->lastword->next;
				result->lastword->next = p->next;
				CLI_MISC_Free(p->value);
				CLI_MISC_Free(p);
			}
		}

		CLI_DBG_LEAVE(l_mdl_id);
		return TRUE;
		break;

	case CLI_PARA_GET_NEXT_WORDLIST:
		for (i = 0; i < count; i++)
		{
			result->list[i] = cur_posible_node[i];
		}

		result->count = count;
		if (result->count == 0) /* set finish tag */
		{
			result->finish = TRUE;
		}

		break;
	}

	CLI_DBG_LEAVE(l_mdl_id);
	return TRUE;
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 CLI_PARA_Get_Help
 *
 * DESCRIPTION:
 *	 Get word list match the last word in user command or all the probably
 *		word after the user command for the help system
 *
 * INPUT:
 *	 pwords -- word list in the user command.
 *	 root -- parameter tree
 *	 result -- point to the result buffer
 *	 flags -- CLI_PARA_GET_CUR_WORDLIST, CLI_PARA_GET_NEXT_WORDLIST
 *
 * OUTPUT:
 *	 result -- word list
 *
 * RETURN:
 *	 < 0 -- failure
 *	 = 0 -- success
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-23 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
I32_T CLI_PARA_Get_Help(
	IN CLI_PRIV_USRCMD_WORDLIST_T *pwords,
	IN CLI_PRIV_PARA_SYN_NODE_T * root,
	IN OUT CLI_PRIV_HELPLIST_T *helplist,
	IN I32_T flags)
{
	CLI_PARA_CMD_TAB_LIST_T *tab_list;
	CLI_TYPES_PRT_RANGE_FUNC_T *prt_range;
	I32_T help_name_len;
	I32_T buf_len;
	BOOL_T ret_value;
	I32_T i;

	// printf ("\r\n%s(%d)\r\n", pwords->word[pwords->index], pwords->index);
	tab_list = CLI_MISC_Malloc(sizeof(CLI_PARA_CMD_TAB_LIST_T));
	if (!tab_list)
	{
		return -1;
	}

	memset (tab_list, 0, sizeof(CLI_PARA_CMD_TAB_LIST_T));
	tab_list->tail = NULL;
	tab_list->cur_posible_node_count = -1;
	tab_list->finish = FALSE;
	ret_value = cli2_para_get_match_list(pwords, root, tab_list, flags);
	cli2_para_clear_all_match_tag(root);
	helplist->error_pos = tab_list->error_pos;
	// printf ("\r\n%d\r\n", helplist->error_pos);
	if (ret_value == FALSE)
	{
		/* for free the value list */
		CLI_PARA_Free_ValueList(tab_list->head.next);
		CLI_MISC_Free(tab_list);
		return -1;
	}

	// get result string
	// result->count = tab_list->count;
	for (i = 0; i < tab_list->count; i++)
	{
		helplist->name[helplist->count] = helplist->name_buf + helplist->name_buf_used;
		buf_len = 0;
		{
			switch (tab_list->list[i]->type)
			{
				case CLI_TYPES_KEYWORD:
				case CLI_TYPES_ENUM:
					strcpy(helplist->name[helplist->count], tab_list->list[i]->name);
					helplist->name_buf_used += strlen (tab_list->list[i]->name) + 1;
					if (helplist->local_help
						&& tab_list->list[i]->help_local
						&& tab_list->list[i]->help_local[0])
					{
						helplist->help[helplist->count] = tab_list->list[i]->help_local;
					}
					else
					{
						if (tab_list->list[i]->help_en && tab_list->list[i]->help_en[0])
						{
							helplist->help[helplist->count] = tab_list->list[i]->help_en;
						}
						else
						{
							helplist->help[helplist->count] = NULL;
						}
					}

					help_name_len = strlen (helplist->name[helplist->count]);
					if (helplist->max_name_len < help_name_len)
					{
						helplist->max_name_len = help_name_len;
					}
					helplist->count++;
					break;

				default:
					prt_range = CLI_TYPES_GetPrtRangeFunc (tab_list->list[i]->type);
					buf_len = sprintf(helplist->name[helplist->count], "<%s ", tab_list->list[i]->name);

					if (prt_range)
					{
						buf_len += prt_range (helplist->name[helplist->count] + buf_len,
							tab_list->list[i]->lparam,
							tab_list->list[i]->rparam);
					}
					else
					{
						buf_len += sprintf(helplist->name[helplist->count] + buf_len,
							"%d - %d", tab_list->list[i]->lparam,
							tab_list->list[i]->rparam);
					}
					/* remove the end blank which don't have mean */
					while (buf_len)
					{
						if (helplist->name[helplist->count][buf_len-1] != ' ')
						{
							break;
						}
						buf_len--;
					}
					buf_len += sprintf(helplist->name[helplist->count] + buf_len, ">");
					if (helplist->local_help
						&& tab_list->list[i]->help_local
						&& tab_list->list[i]->help_local[0])
					{
						helplist->help[helplist->count] = tab_list->list[i]->help_local;
					}
					else
					{
						if (tab_list->list[i]->help_en && tab_list->list[i]->help_en[0])
						{
							helplist->help[helplist->count] = tab_list->list[i]->help_en;
						}
						else
						{
							helplist->help[helplist->count] = NULL;
						}
					}

					help_name_len = strlen (helplist->name[helplist->count]);
					helplist->name_buf_used += help_name_len + 1;
					if (helplist->max_name_len < help_name_len)
					{
						helplist->max_name_len = help_name_len;
					}
					helplist->count++;
					/* it's <parameter> which need to parse, increase the para_count */
					helplist->para_count++;
					break;
			}
		}
	}

	if (tab_list->finish)
	{
		helplist->name[helplist->count] = helplist->name_buf + helplist->name_buf_used;
		strcpy(helplist->name[helplist->count], "<cr>");
		helplist->name_buf_used += strlen("<cr>") + 1;
		helplist->help[helplist->count] = NULL;
		helplist->count++; // <cr>
	}

	/* for free the value list */
	CLI_PARA_Free_ValueList(tab_list->head.next);
	CLI_MISC_Free(tab_list);

	return 0;
}


/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 CLI_PARA_Free_ValueList
 *
 * DESCRIPTION:
 *	 Free memory allocated in cli_value_t list
 *
 * INPUT:
 *	 value -- pointer of the value list
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
 *	 2009-Mar-23 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
void CLI_PARA_Free_ValueList(cli_value_t * value)
{
	cli_value_t *cur;
	cli_value_t *next;

	for (cur = value; cur; cur = next)
	{
		next = cur->next;
		if (cur->name)
		{
			CLI_MISC_Free(cur->name);
		}

		if (cur->value)
		{
			CLI_MISC_Free(cur->value);
		}

		CLI_MISC_Free(cur);
	}
}

/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 CLI_PARA_Get_Value
 *
 * DESCRIPTION:
 *	 Check parameter in a user command and get it's value
 *
 * INPUT:
 *	 pwords -- word list in the user command.
 *	 root   -- parameter tree
 *	 result -- point to the result buffer
 *	 flags  -- CLI_PARA_GET_VALUE
 *
 * OUTPUT:
 *	 result -- list of the cli_value_t
 *
 * RETURN:
 *	 < 0 -- failure
 *	 = 0 -- success
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-23 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
I32_T CLI_PARA_Get_Value(
	IN CLI_PRIV_USRCMD_WORDLIST_T *pwords,
	IN CLI_PRIV_PARA_SYN_NODE_T *root,
	IN OUT cli_value_t **value,
	OUT I32_T *error_position)
{
	CLI_DBG_ENTER(l_mdl_id);
	CLI_DBG_CPL(l_mdl_id, "pwords:usrcmd=%s,word=%s,len=%d,count=%d,index=%d\r\n", pwords->usrcmd, pwords->word[0], pwords->len[0], pwords->count, pwords->index);

	CLI_PARA_CMD_TAB_LIST_T 	*tab_list;
	BOOL_T 						ret_value;

	if (!root)
	{
		*error_position = pwords->word[pwords->index] - pwords->usrcmd;
		*value = NULL;
		if (*pwords->word[pwords->index] == '\0')
		{
			CLI_DBG_LEAVE(l_mdl_id);
			return 0;
		}
		else
		{
			CLI_DBG_LEAVE(l_mdl_id);
			return -1;
		}
	}

	tab_list = CLI_MISC_Malloc(sizeof(CLI_PARA_CMD_TAB_LIST_T));
	if (!tab_list)
	{
		CLI_DBG_LEAVE(l_mdl_id);
		return -1;
	}

	memset (tab_list, 0, sizeof(CLI_PARA_CMD_TAB_LIST_T));
	tab_list->tail = &tab_list->head;
	tab_list->head.next = NULL;
	tab_list->cur_posible_node_count = -1;
	tab_list->most_match = FALSE;

	ret_value = cli2_para_get_match_list(pwords, root, tab_list, CLI_PARA_GET_VALUE);
	cli2_para_clear_all_match_tag(root);
	*error_position = tab_list->error_pos;
	if (ret_value == FALSE)
	{
		//printf("pos = %d\r\n", tab_list->error_pos);
		CLI_PARA_Free_ValueList(tab_list->head.next);
		CLI_MISC_Free(tab_list);
		CLI_DBG_LEAVE(l_mdl_id);
		return -1;
	}

	*value = tab_list->head.next;
	if (tab_list->count > 1) /* count = 0 means the para may be omitted */
	{

		CLI_MISC_Free(tab_list);
		CLI_PARA_Free_ValueList(*value);

		*value = NULL;
		CLI_DBG_LEAVE(l_mdl_id);
		return -1;
	}

	CLI_MISC_Free(tab_list);
	CLI_DBG_LEAVE(l_mdl_id);
	return 0;
}



/**************************************************************************
FUNCTION NAME:
	CLI_PARA_Generate_ValueList

DESCRIPTION:
	Generate value list by input value list(alloc memory and generate).

INPUT:
	node_param	: input value list

OUTPUT:
	NA

RETURN:
	generated value list

NOTES:

HISTORY:
	Creat by bain.wang@outlook.com 2011.3.2

**************************************************************************/
cli_value_t *CLI_PARA_Generate_ValueList(IN cli_value_t *node_param)
{
	cli_value_t 	*ptr_param, *temp_param, *next_param;
	UI32_T 			value_size;

	if (NULL == node_param)
	{
		return NULL;
	}

	/* generate parameter list */
	/* root->node_param->node_param->node_param */
	ptr_param = CLI_MISC_Malloc(sizeof(cli_value_t));
	memset(ptr_param, 0, sizeof(cli_value_t));
	temp_param = ptr_param;

	while (node_param)
	{
		next_param = CLI_MISC_Malloc(sizeof(cli_value_t));
		memset(next_param, 0, sizeof(cli_value_t));
		next_param->type = node_param->type;
		next_param->priority = node_param->priority;
		next_param->next = NULL;

		if (node_param->name)
		{
			next_param->name = CLI_MISC_Malloc(strlen(node_param->name) + 1);
			strcpy(next_param->name, node_param->name);
		}

		if (node_param->value)
		{
			value_size = CLI_ALIAS_Clac_ParaValueSize(node_param->type, node_param->value);
			next_param->value = CLI_MISC_Malloc(value_size);
			memcpy(next_param->value, node_param->value, value_size);
		}

		temp_param->next = next_param;
		temp_param = temp_param->next;

		node_param = node_param->next;
	}

	return ptr_param->next;
}



/* End of file */
