/*******************************************************************************
  Copyright (C), 1988-2013, xxxxx Tech. Co., Ltd.
  [File name]	: utili_blcok.c
  [Author]     	: wangbin
  [Version]    	: 1.0
  [Date]       	: 2014-04-23
  [Description]	:
	block use
  [Others]     	:
	NULL
  [Function List]:  
    1. ....
    2. ....
  [History]:
	 Date       	Modification 							 Initials
	---------- 	--------------                                        ----------
	2013-03-12  	Created								 wangbin
*******************************************************************************/

#include "utili_block.h"

/*************************************************
FUNCTION NAME:
	utili_block_init

DESCRIPTION:
	Initialize the red-black tree node array as free-list

INPUT:
	block		: the block struct pointer
	nodes		: the node array start pointer
	node_size	: the node size (include red-black node and real-data)
	nodes_num	: the number of nodes

*************************************************/
void utili_block_init(utili_block_t *block, void *nodes, bc_uint32 node_size, bc_uint32 nodes_num)
{
	bc_uint32	addr, aligned_size, mask;

	/* align the node size */
	mask = sizeof(utili_block_list_t *) - 1;
	aligned_size = (node_size + mask) &  (~mask);

	/* Initialize the freenode list to empty */
	block->list_head = NULL;

	/* save the aligned base&end address */
	addr = (bc_uint32)nodes;
	addr = (addr + mask) &  (~mask);
	block->base = (void *)addr;

	addr = (bc_uint32)nodes + node_size * (nodes_num-1);
	addr = (addr + mask) &  (~mask);
	block->end = (void *)addr;

	/* zero the counter */
	block->free_count = block->node_num = 0;

	/* insert each node into list */
	for (addr = (bc_uint32)block->end;
		addr>=(bc_uint32)block->base; addr-=aligned_size)
	{
		block->node_num++;
		((utili_block_list_t *)addr)->next = block->list_head;
		block->list_head = (utili_block_list_t *)addr;
	}

	block->free_count = block->node_num;
}

/*************************************************
FUNCTION NAME:
	utili_block_alloc

DESCRIPTION:
	allocate a node from nodes free-list

INPUT:
	block		: the block struct pointer

RETURN:
	NULL		: no node for allocatte
	pointer		: a free node

*************************************************/
void  *utili_block_alloc(utili_block_t *block)
{
	utili_block_list_t 	*node;

	node = block->list_head;

	/* check list is empty */
	if (node)
	{
		/* remove it from free-list */
		block->list_head = node->next;

		/* update the counter */
		block->free_count--;
	}

	return node;
}

/*************************************************
FUNCTION NAME:
	utili_block_free

DESCRIPTION:
	free a node

INPUT:
	tree			: the block struct pointer
	ptr			: the node pointer

*************************************************/
void utili_block_free(utili_block_t *block, void *ptr)
{
	utili_block_list_t 	*node;

	if ((ptr >= block->base) && (ptr <= block->end))
	{
		node = (utili_block_list_t *)ptr;
		node->next = block->list_head;
		block->list_head = node;

		/* update the counter */
		block->free_count++;
	}
}


