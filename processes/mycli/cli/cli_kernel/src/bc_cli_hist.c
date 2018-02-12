/*==============================================================================
 * FILE NAME  : cli2_hist.c
 * VERSION    : 1.0.0
 * DESCRIPTION:
 * NOTES:
 *
 * HISTORY:
 * -----------------------------------------------------------------------------
 * Version 1.0 -  2008-Dec-17 by bain.wang@outlook.com
 * [NEW FEATURE]
 * <DESCRIPTION> Create
 *============================================================================*/

////////////////////////////////////////////////////////////////////////////////
// 																			  //
// 							 	头   文   件								  //
// 																			  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_modules.h"
#include "bc_cli_type.h"
#include "bc_cli_kernel_cfg.h"
#include "bc_cli_misc.h"
#include "bc_cli_hist.h"
#include "bc_cli_msg.h"



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

typedef I8_T CLI_HIST_NODE_T[CLI_API_MAX_CMD_LEN + 1];

typedef struct tagCLI_HIST_HEAD 
{
	BOOL_T 				enable;				// TRUE -- enable history, FALSE -- disable history
	I32_T 				size;
	I32_T 				first;
	I32_T 				last;
	I32_T 				cur;
	CLI_HIST_NODE_T 	node[1];
} CLI_HIST_HEAD_T;



////////////////////////////////////////////////////////////////////////////////
//																			  //
//							全 局 变 量 定 义								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

static unsigned int 	l_mdl_id = BC_MODULE_CLI_KERNEL;



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
 * Func:   CLI_HIST_Create
 * DESCRIPTION: Create a new history handle, allocate resources for the history handle
 * INPUT:  hist_size -- the max item size of the history
 * OUTPUT: NA
 * RETURN: HANDLE_T -- handle of the new history
 * NOTES:  NA
 * HISTORY:
 *	 2008-Dec-17 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
HANDLE_T CLI_HIST_Create(IN UI32_T hist_size)
{
	CLI_HIST_HEAD_T *p;

	p = CLI_MISC_Malloc(sizeof(CLI_HIST_HEAD_T)
						 + hist_size * sizeof(CLI_HIST_NODE_T));
	if (!p)
	{
		CLI_MSG_ERR(l_mdl_id, UTL_MISC_ERR_MEMORY_OVERFLOW);
		return NULL;
	}

	p->size = hist_size;
	p->first = -1;
	p->last = -1;
	p->cur = -1;
	p->enable = TRUE;
	return (HANDLE_T) p;
}

/*******************************************************************************
 *
 * Func:   CLI_HIST_Destroy
 * DESCRIPTION: Destroy history handle, Release history resources
 * INPUT:  h_hist -- Handle of the history, it must be returned by CLI_HIST_Create
 * OUTPUT: NA
 * RETURN: NA
 * NOTES:  use h_hist after called CLI_HIST_Destroy will cause fatal errors
 * HISTORY:
 *	 2008-Dec-17 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
void CLI_HIST_Destroy(IN HANDLE_T h_hist)
{
	CLI_MISC_Free(h_hist);
	return;
}

/*******************************************************************************
 *
 * Func:   CLI_HIST_GetPrevItem
 * DESCRIPTION: Get the previous history string
 * INPUT:  h_hist -- Handle of the history, it must be returned by CLI_HIST_Create
 * OUTPUT: NA
 * RETURN: NULL -- There is no previous history item, not NULL -- the address of the
 *			 previous history string
 * NOTES:  NA
 * HISTORY:
 *	 2008-Dec-17 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
I8_T *CLI_HIST_GetPrevItem(IN HANDLE_T h_hist)
{
	CLI_HIST_HEAD_T *p;
	I8_T *ret_str;

	p = (CLI_HIST_HEAD_T *) h_hist;
	if (p->enable == FALSE)
	{
		return NULL;
	}

	if (p->cur < 0)
	{
		return NULL;
	}

	ret_str = p->node[p->cur];
	if (p->last < p->first)
	{
		if (p->cur == 0)
		{
			p->cur = p->size - 1;
		}
		else
		{
			p->cur--;
		}
	}
	else
	{
		if (p->cur == p->first)
		{
			p->cur = p->last;
		}
		else
		{
			p->cur--;
		}
	}

	return ret_str;
}



/*******************************************************************************
 *
 * Func:   CLI_HIST_GetCurItem
 * DESCRIPTION: Get the current history string
 * INPUT:  h_hist -- Handle of the history, it must be returned by CLI_HIST_Create
 * OUTPUT: NA
 * RETURN: NULL -- There is no history item, not NULL -- the address of the
 *			 current history string
 * NOTES:  NA
 * HISTORY:
 *	 2008-Dec-17 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
I8_T *CLI_HIST_GetCurItem(IN HANDLE_T h_hist)
{
	CLI_HIST_HEAD_T *p;

	p = (CLI_HIST_HEAD_T *) h_hist;

	if (p->enable == FALSE)
	{
		return NULL;
	}
	if (p->cur >= 0)
	{
		return p->node[p->cur];
	}
	else
	{
		return NULL;
	}
}



/*******************************************************************************
 *
 * Func:   CLI_HIST_GetNextItem
 * DESCRIPTION: Get the next history string
 * INPUT:  h_hist -- Handle of the history, it must be returned by CLI_HIST_Create
 * OUTPUT: NA
 * RETURN: NULL -- There is no next history item, not NULL -- the address of the
 *			 next history string
 * NOTES:  NA
 * HISTORY:
 *	 2008-Dec-17 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
I8_T *CLI_HIST_GetNextItem(IN HANDLE_T h_hist)
{
	CLI_HIST_HEAD_T *p;

	p = (CLI_HIST_HEAD_T *) h_hist;
	if (p->enable == FALSE)
	{
		return NULL;
	}

	if (p->cur < 0)
	{
		return NULL;
	}

	if (p->last < p->first)
	{
		if (p->cur == p->size - 1)
		{
			p->cur = 0;
		}
		else
		{
			p->cur++;
		}
	}
	else
	{
		if (p->cur == p->last)
		{
			p->cur = p->first;
		}
		else
		{
			p->cur++;
		}
	}

	return p->node[p->cur];
}



/*******************************************************************************
 *
 * Func:   CLI_HIST_InsertItem
 * DESCRIPTION: add a new history to the end of history buffer, if history buffer
 *		 is full, the first history item will be removed from it.
 * INPUT:  h_hist -- Handle of the history, it must be returned by CLI_HIST_Create
 *		   buf -- The new history string
 * OUTPUT: NA
 * RETURN: NULL -- insert failed, not NULL -- The address of the new history item
 * NOTES:  ###
 * HISTORY:
 *	 2008-Dec-17 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
I8_T *CLI_HIST_InsertItem(IN HANDLE_T h_hist, IN const I8_T *buf)
{
	CLI_HIST_HEAD_T *p;
	I8_T *tmp;

	p = (CLI_HIST_HEAD_T *) h_hist;
	if (p->enable == FALSE)
	{
		return NULL;
	}

	if (p->first < 0)
	{
		p->first = 0;
		p->cur = 0;
		p->last = 0;
	}
	else
	{
		tmp = (I8_T *)p->node[p->last];
		// the buf is same as the last history
		if (strcmp(tmp, buf) == 0)
		{
			p->cur = p->last;
			return tmp;
		}

		if (p->last < p->first)
		{
			p->first = (p->first + 1) % p->size;
			p->last = (p->last + 1) % p->size;
		}
		else
		{
			p->last = (p->last + 1) % p->size;
			if (p->last == p->first)
			{
				p->first = (p->first + 1) % p->size;
			}
		}
		p->cur = p->last;
	}
	tmp = (I8_T *)p->node[p->cur];
	strcpy(tmp, buf);

	return tmp;
}



/*******************************************************************************
 *
 * Func:   CLI_HIST_SetSize
 * DESCRIPTION: Set a new size to history
 * INPUT:  h_hist -- Handle of the history, it must be returned by CLI_HIST_Create
 *		   new_size -- The new size of the history
 * OUTPUT: NA
 * RETURN: if (new_size == old_size) The history buffer not changed
 *		   if (new_size < old_size) The HANDLE_T not changed, but all history
 *			   data was cleared
 *		   if (new_size > old_size) The HANDLE_T changed to new, all history data
 *			   was cleared, and old resources was released. If memory allocate
 *			   failed, this function will return (HANDLE_T)0 in this case.
 *
 * NOTES:  NA
 * HISTORY:
 *	 2008-Dec-17 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
HANDLE_T CLI_HIST_SetSize(IN HANDLE_T h_hist, IN I32_T new_size)
{
	CLI_HIST_HEAD_T *p_new;
	CLI_HIST_HEAD_T *p_old;

	p_old = (CLI_HIST_HEAD_T *) h_hist;
	if (p_old->size == new_size)
	{
		return p_old;
	}

	if (p_old->size > new_size)
	{
		p_new = p_old;
	}
	else
	{
		p_new = CLI_MISC_Malloc(sizeof(CLI_HIST_HEAD_T) + new_size * sizeof(CLI_HIST_NODE_T));
		if (!p_new)
		{
			CLI_MSG_ERR(l_mdl_id, UTL_MISC_ERR_MEMORY_OVERFLOW);
			return p_old;
		}

		p_new->enable = p_old->enable;
	}
	p_new->size = new_size;
	p_new->first = -1;
	p_new->last = -1;
	p_new->cur = -1;
	if (p_new != p_old)
	{
		CLI_MISC_Free(p_old);
	}

	return (HANDLE_T) p_new;
}



/*******************************************************************************
 *
 * Func:   CLI_HIST_ShowAllHist
 * DESCRIPTION: Show all histories
 * INPUT:  h_hist -- Handle of the history, it must be returned by CLI_HIST_Create
 *		   start -- TRUE(return the first item in the history buffer)
 *					FALSE (return the next item in the history buffer)
 * OUTPUT: NA
 * RETURN: not NULL -- the pointer of the history buffer, NULL -- There is no more
 *				 item in the history buffer, the operation may be stopped
 * USAGE:
 *		  {
 *			 I8_T *p;
 *
 *			 p = CLI_HIST_ShowAllHist (h_hist, TRUE);
 *			 printf ("%s\n", p);
 *			 while ((p = CLI_HIST_ShowAllHist (h_hist, FALSE)) != NULL)
 *			 {
 *				 printf ("%s\n", p);
 *			 }
 *		  }
 * HISTORY:
 *	 2008-Dec-17 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
I8_T *CLI_HIST_ShowAllHist(IN HANDLE_T h_hist, IN BOOL_T start)
{
	static I32_T 		pos = -1;
	I8_T 				*ret;
	CLI_HIST_HEAD_T 	*p;

	p = (CLI_HIST_HEAD_T *) h_hist;
	if (p->enable == FALSE)
	{
		return NULL;
	}

	if (start == TRUE)
	{
		pos = p->first;
	}

	if (pos == -1)
	{
		return NULL;
	}

	ret = (I8_T *)p->node[pos];
	if (pos == p->last)
	{
		/* finish show all history */
		pos = -1;
	}
	else
	{
		pos = (pos + 1) % p->size;
	}

	return ret;
}



/**************************************************************************
FUNCTION NAME:
	CLI_HIST_SetState

DESCRIPTION:
	Set the history module state.

INPUT:
	h_hist	: Handle of the history, it must be returned by CLI_HIST_Create
	bEnable	: TRUE -> open the history function
			  FALSE -> close the history function

OUTPUT:
	None

RETURN:
	None

NOTES:

HISTORY:

**************************************************************************/
void CLI_HIST_SetState(
	IN HANDLE_T h_hist,
	IN BOOL_T bEnable)
{
	CLI_HIST_HEAD_T *p;

	p = (CLI_HIST_HEAD_T *) h_hist;
	p->enable = bEnable;

	return;
}



/**************************************************************************
FUNCTION NAME:
	CLI_HIST_GetState

DESCRIPTION:
	Get the history module state.

INPUT:
	h_hist	: Handle of the history, it must be returned by CLI_HIST_Create

OUTPUT:
	None

RETURN:
	TRUE	: the history function is open
	FALSE	: the history function is closen

NOTES:

HISTORY:

**************************************************************************/
BOOL_T CLI_HIST_GetState(IN HANDLE_T h_hist)
{
	CLI_HIST_HEAD_T *p;

	p = (CLI_HIST_HEAD_T *) h_hist;

	return p->enable;
}



