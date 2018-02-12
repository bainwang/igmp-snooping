/*******************************************************************************
  [File name]	: mcast_utl.c
  [Author]     	: bain.wang@outlook.com
  [Version]    	: 1.0
  [Date]       	: 2017-06-13
  [Description]	:
	Multicast module common operation
  [Others]     	:
	NULL
  [Function List]:  
    1. ....
    2. ....
  [History]:
	 D a t e      	Modification 							 Initials
	---------- 	--------------                                        ----------
	2017-06-13  	Created								 bain.wang@outlook.com
*******************************************************************************/

#include "mcast_utl.h"

#if 1 /*bain.wang@outlook.com*/
#include "stdlib.h"
#include "string.h"
#endif


#if BC_MULTICAST_INCLUDE

#if 1

void mcast_dbg_prt_str(bc_uint8 *buf, bc_uint16 len, bc_uint16 width, bc_uint16 offset, bc_boolean newline)
{
	bc_uint8 *__buf_p = buf;
	bc_uint8 __dbg_buf[80] = {0};
									
	while ((__buf_p + width-1) <= (buf + len-1))
	{
		memset(__dbg_buf, 0x00, 80);
		memcpy(__dbg_buf, __buf_p, width);

		if (newline == FALSE)
			newline = TRUE;
		else
			MCAST_DBG_PRT("\n\t%-*s", offset, " ");
			
		MCAST_DBG_PRT("%-*s", width, __dbg_buf);
		
		__buf_p += width;
	}

	if (__buf_p < (buf + len-1))
	{
		memset(__dbg_buf, 0x00, 80);
		memcpy(__dbg_buf, __buf_p, ((buf + len) - __buf_p));
		
		if (newline == FALSE)
			newline = TRUE;
		else
			MCAST_DBG_PRT("\n\t%-*s", offset, " ");

		MCAST_DBG_PRT("%-*s", width, __dbg_buf);
	}
}

#endif
#if 1

bc_int32 mcast_utl_src_cmp(IN void *node, IN bc_uint32 key)
{
	mcast_utl_src_node_t *p;

	p = (mcast_utl_src_node_t*)node;

	if (p->src > key)
		return 1;
	else if (p->src < key)
		return -1;
	else
		return 0;
}

bc_ip* mcast_src_list_2_block(IN mcast_list_t *src_list, OUT bc_uint16 *src_num)
{
	mcast_utl_src_node_t *src_node_p = NULL;
	bc_ip *src_list_block = NULL;

	*src_num = mcast_list_count(src_list);
	if (*src_num != 0)
	{
		src_list_block = (bc_ip*)mcast_alloc(sizeof(bc_ip)*(*src_num));
		if (src_list_block == NULL)
			return NULL;

		memset(src_list_block, 0x00, sizeof(bc_ip)*(*src_num));
		mcast_list_scan(src_list, src_node_p, mcast_utl_src_node_t*)
		{
			*src_list_block = src_node_p->src;
			src_list_block++;
		}
	}

	return src_list_block - *src_num;
}


void mcast_src_list_free(IN mcast_list_t *src_list)
{
	mcast_utl_src_node_t *node_p;

	while ((node_p = (mcast_utl_src_node_t*)mcast_list_first(src_list)) != NULL)
	{
		mcast_list_delete(src_list, node_p);
		mcast_free(node_p);
	}
}


bc_boolean mcast_src_list_alloc(IN bc_int32 src_num, IN bc_ip *src_list, OUT mcast_list_t *mcast_list)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	bc_int32 i;
	mcast_utl_src_node_t *node_p;

	for (i = 0; i < src_num; i++)
	{
		if (mcast_list_find(mcast_list, src_list[i]) != NULL)
			continue;
	
		node_p = (mcast_utl_src_node_t *)mcast_alloc(sizeof(mcast_utl_src_node_t));
		if (node_p == NULL)
		{
			mcast_src_list_free(mcast_list);
			return FALSE;
		}

		memset(node_p, 0x00, sizeof(mcast_utl_src_node_t));
		node_p->src = src_list[i];
		mcast_list_add(mcast_list, node_p);
	}

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return TRUE;
}


bc_boolean mcast_src_list_copy(OUT mcast_list_t *dst, IN mcast_list_t *src)
{
	mcast_utl_src_node_t *node_p;
	mcast_utl_src_node_t *new_node_p;

	mcast_list_scan(src, node_p, mcast_utl_src_node_t*)
	{
		new_node_p = (mcast_utl_src_node_t*)mcast_alloc(sizeof(mcast_utl_src_node_t));
		if (new_node_p == NULL)
		{
			mcast_src_list_free(dst);
			return FALSE;
		}
		
		memcpy(new_node_p, node_p, sizeof(mcast_utl_src_node_t));
		mcast_list_add(dst, new_node_p);
	}

	return TRUE;
}


/* return A+B
    A = {1, 2, 3}, B = {2, 3, 4}
    return {1, 2, 3, 2 ,3, 4} and A = {NULL}, B = {NULL}
*/
void mcast_src_list_union(INOUT mcast_list_t *A, INOUT mcast_list_t *B, OUT mcast_list_t* reslt)
{
	mcast_utl_src_node_t *node_p = NULL;

	while ((node_p = (mcast_utl_src_node_t*)mcast_list_first(A)) != NULL)
	{
		mcast_list_delete(A, node_p);
		mcast_list_add(reslt, node_p);
	}

	while ((node_p = (mcast_utl_src_node_t*)mcast_list_first(B)) != NULL)
	{
		mcast_list_delete(B, node_p);
		mcast_list_add(reslt, node_p);
	}	
}

/*
	return A*B
	A = {1, 2, 3}, B = {2, 3, 4}
	return {2, 3} and A = {1}, B = {2, 3, 4}
*/
void mcast_src_list_intersection(INOUT mcast_list_t *A, IN mcast_list_t *B, OUT mcast_list_t* reslt)
{
	mcast_utl_src_node_t *node_p = NULL;
	mcast_utl_src_node_t *inter_node_p = NULL;

	mcast_list_scan(A, node_p, mcast_utl_src_node_t*)
	{
		if (inter_node_p)
		{
			mcast_list_delete(A, inter_node_p);
			mcast_list_add(reslt, inter_node_p);
			inter_node_p = NULL;
		}
		
		if (mcast_list_find(B, node_p->src) != NULL)
		{
			inter_node_p = node_p;
		}
	}

	if (inter_node_p)
	{
		mcast_list_delete(A, inter_node_p);
		mcast_list_add(reslt, inter_node_p);
		inter_node_p = NULL;
	}
}


/*
	return A xor B
	A = {1, 2, 3}, B = {2, 3, 4}
	return {1, 4} and A = {2, 3}, B = {2, 3}
*/
void mcast_src_list_xor(INOUT mcast_list_t *A, INOUT mcast_list_t *B, OUT mcast_list_t* reslt)
{
	mcast_utl_src_node_t *node_p = NULL;
	mcast_utl_src_node_t *xor_node_p = NULL;

	mcast_list_scan(A, node_p, mcast_utl_src_node_t*)
	{
		if (xor_node_p)
		{
			mcast_list_delete(A, xor_node_p);
			mcast_list_add(reslt, xor_node_p);
			xor_node_p = NULL;
		}
		
		if (mcast_list_find(B, node_p->src) == NULL)
		{
			xor_node_p = node_p;
		}
	}

	if (xor_node_p)
	{
		mcast_list_delete(A, xor_node_p);
		mcast_list_add(reslt, xor_node_p);
		xor_node_p = NULL;
	}


	mcast_list_scan(B, node_p, mcast_utl_src_node_t*)
	{
		if (xor_node_p)
		{
			mcast_list_delete(B, xor_node_p);
			mcast_list_add(reslt, xor_node_p);
			xor_node_p = NULL;
		}
		
		if (mcast_list_find(A, node_p->src) == NULL)
		{
			xor_node_p = node_p;
		}
	}

	if (xor_node_p)
	{
		mcast_list_delete(B, xor_node_p);
		mcast_list_add(reslt, xor_node_p);
		xor_node_p = NULL;
	}
}

/*  
	return A - B
	A = {1, 2, 3}, B = {2, 3, 4}
	return {2, 3} and A = {1}, B = {2, 3, 4}
*/
void mcast_src_list_minus(INOUT mcast_list_t *A, IN mcast_list_t *B, OUT mcast_list_t* reslt)
{
	mcast_utl_src_node_t *node_p = NULL;
	mcast_utl_src_node_t *minus_node_p = NULL;

	mcast_list_scan(A, node_p, mcast_utl_src_node_t*)
	{
		if (minus_node_p)
		{
			mcast_list_delete(A, minus_node_p);
			mcast_list_add(reslt, minus_node_p);
			minus_node_p = NULL;
		}
		
		if (mcast_list_find(B, node_p->src) != NULL)
		{
			minus_node_p = node_p;
		}
	}

	if (minus_node_p)
	{
		mcast_list_delete(A, minus_node_p);
		mcast_list_add(reslt, minus_node_p);
		minus_node_p = NULL;
	}	
}


/*  
	return dst
	dst = {1, 2, 3}, src = {2, 3, 4}
	return dst = {1, 2, 2, 3, 3, 4}, B = {NULL}
*/
void mcast_src_list_move(INOUT mcast_list_t *dst, INOUT mcast_list_t *src)
{
	mcast_utl_src_node_t *node_p = NULL;

	while ((node_p = (mcast_utl_src_node_t*)mcast_list_first(src)) != NULL)
	{
		mcast_list_delete(src, node_p);
		mcast_list_add(dst, node_p);
	}
}


#endif

#if 1


bc_boolean mcast_utl_bitlist_and(IN bc_uint8 *f_list, IN bc_uint8 *s_list, OUT bc_uint8 *r_list, IN bc_uint16 size)
{
	bc_uint16 idx;

	for (idx = 0; idx < size; idx++)
		r_list[idx] = f_list[idx] & s_list[idx];

	return TRUE;
}

bc_boolean mcast_utl_bitlist_xor(IN bc_uint8 *f_list, IN bc_uint8 *s_list, OUT bc_uint8 *r_list, IN bc_uint16 size)
{
	bc_uint16 idx;

	for (idx = 0; idx < size; idx++)
		r_list[idx] = f_list[idx] ^ s_list[idx];

	return TRUE;
}

bc_boolean mcast_utl_bitlist_or(IN bc_uint8 *f_list, IN bc_uint8 *s_list, OUT bc_uint8 *r_list, IN bc_uint16 size)
{
	bc_uint16 idx;

	for (idx = 0; idx < size; idx++)
		r_list[idx] = f_list[idx] | s_list[idx];

	return TRUE;
}

bc_boolean mcast_utl_bitlist_is_empty(IN bc_uint8 *list, IN bc_uint16 size)
{
	bc_uint16 idx;

	for (idx = 0; idx < size; idx++)
		if (list[idx])
			return FALSE;

	return TRUE;
}

bc_boolean mcast_utl_bit_is_set(IN bc_uint8 *list, IN bc_uint16 size, IN bc_uint32 offset)
{
	bc_uint16 offset_grid;
	bc_uint16 offset_local;

	if (offset == 0)
		return FALSE; /* error offset start from 1 */

	offset_grid = (offset-1) / 8;
	offset_local = (offset-1) % 8;

	if (offset_grid >= size)
		return FALSE;

	if (list[offset_grid] & (0x01 << offset_local))
		return TRUE;
	else
		return FALSE;
}


bc_boolean mcast_utl_bit_set(IN bc_uint8 *list, IN bc_uint16 size, IN bc_uint32 offset)
{
	bc_uint16 offset_grid;
	bc_uint16 offset_local;

	if (offset == 0)
		return FALSE; /* error offset start from 1 */

	offset_grid = (offset-1) / 8;
	offset_local = (offset-1) % 8;

	if (offset_grid >= size)
		return FALSE;

	list[offset_grid] |= 0x01 << offset_local;
	return TRUE;
}


bc_boolean mcast_utl_bit_clr(IN bc_uint8 *list, IN bc_uint16 size, IN bc_uint32 offset)
{
	bc_uint16 offset_grid;
	bc_uint16 offset_local;

	if (offset == 0)
		return FALSE; /* error offset start from 1 */

	offset_grid = (offset-1) / 8;
	offset_local = (offset-1) % 8;

	if (offset_grid >= size)
		return FALSE;

	if (mcast_utl_bit_is_set(list, size, offset))
		list[offset_grid] ^= 0x01 << offset_local;
	
	return TRUE;
}


bc_boolean mcast_utl_bit_get_next(IN bc_uint8 *list, IN bc_uint16 size, INOUT bc_uint32 *offset)
{
	bc_uint32 next;

	if (*offset > size*8)
		return FALSE;

	next = *offset + 1;
	while (next <= size*8)
	{
		if (mcast_utl_bit_is_set(list, size, next))
		{
			*offset = next;
			return TRUE;
		}

		next++;
	}

	return FALSE;
}

#endif
#endif

