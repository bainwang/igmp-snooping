/*******************************************************************************
  Copyright (C), 1988-2013, xxxxx Tech. Co., Ltd.
  [File name]	: utili_bit.h
  [Author]     	: wangbin
  [Version]    	: 1.0
  [Date]       	: 2014-04-29
  [Description]	:
	define avlt api
  [Others]     	:
	NULL
  [Function List]:  
    1. ....
    2. ....
  [History]:
	 Date       	Modification 							 Initials
	---------- 	--------------                                        ----------
	2014-04-29  	Created								 wangbin
*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include "utili_bit.h"

#define BM_MSB					0x80U			/* Most Significant Bit */
#define BM_BYTEBITS				8				/* bits of array element */
#define BM_BYTEPOS(bit)			(((bit)-1)/BM_BYTEBITS)
#define BM_BITPOS(bit)			(BM_MSB>>(((bit)-1)%BM_BYTEBITS))
#define BM_BYTEMASK			0xFFU
#define BM_VALID(bit,listLen)		(((bit)<1)||((bit)>(listLen)*8))
#define BM_TOTALBITS(listLen)	(8*(listLen))

static int BM_BitsLen[16]={0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4};	/* length of 4 bits */

static unsigned char  BM_HighestSetBit[]={
	0,1,2,2,3,3,3,3,4,4,4,4,4,4,4,4,
	5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
	6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
	7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
	7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
	7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
	7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8
};
static unsigned char  BM_LowestSetBit[]={
	0,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1,
	5,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1,
	6,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1,
	5,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1,
	7,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1,
	5,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1,
	6,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1,
	5,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1,
	8,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1,
	5,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1,
	6,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1,
	5,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1,
	7,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1,
	5,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1,
	6,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1,
	5,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1
};



/*************************************************
  Function: utili_bit_set_bit
  Description: add a bit into bitlist
  Input: 
		bit :  bit number in unit
		list	: operate bitlist
  Output:
		result bitlist
  Return:
		TRUE  : success
		FALSE : invalid bit
  Note: 
  History: 
*************************************************/
bc_boolean utili_bit_set_bit(IN OUT bc_uint8 *list, IN bc_uint32 bit, IN bc_uint32 list_len)
{
	if (BM_VALID(bit, list_len))
		return FALSE;
	
	list[BM_BYTEPOS(bit)] |=  BM_BITPOS(bit);
	return TRUE;
}

/*************************************************
  Function: utili_bit_set_allbit
  Description: set all bit in unit to the bitlist
  Input: 
		list: operate bitlist
		listLen: list len
  Output:
		list: all bit is setted
  Return:
		TRUE  : success
		FALSE : invalid bit
  Note: 
  History: 
*************************************************/
void utili_bit_set_allbit(OUT bc_uint8 *list, IN bc_uint32 listLen)
{
	int i;

	/* set all bits */
	for (i=0; i<listLen; i++)
	{
		list[i] = BM_BYTEMASK;
	}
}

/*************************************************
  Function: utili_bit_clear_bit
  Description: clear a bit from bitlist
  Input: 
	bit :  bit number in unit
	list	: operate bitlist
  Output:
	list	: result bitlist
  Return:
		TRUE  : success
		FALSE : invalid bit
  Note: 
  History: 
*************************************************/
bc_boolean utili_bit_clear_bit(IN OUT bc_uint8 *list, IN bc_uint32 bit, IN bc_uint32 listLen)
{
	if (BM_VALID(bit,listLen))
		return FALSE;
	
	list[BM_BYTEPOS(bit)] &= (~(BM_BITPOS(bit)));
	return TRUE;
}

/*************************************************
  Function: utili_bit_clear_list
  Description: clear all bit in unit from the bitlist
  Input: 
		list: operate bitlist
		listLen: list len
  Output:
	list	: result bitlist
  Return:
  Note: 
  History: 
*************************************************/
void utili_bit_clear_list(OUT bc_uint8 *list, IN bc_uint32 listLen)
{
	int i;

	for (i = 0; i < listLen; i++)
	{
		list[i] = 0;
	}
}

/*************************************************
  Function: utili_bit_get_firstbit
  Description: get first bit number of bitlist
  Input: 
		list: operate bitlist
		listLen: list len
  Output:
  Return:
		bit number if any bitset in bitlist
		0 otherwise
  Note: 
		Don't use this function in loop to fetch out all bit in bitlist
  History: 
*************************************************/
int utili_bit_get_firstbit(IN const bc_uint8 *list, IN bc_uint32 listLen)
{
	int	idx;

	for (idx = 0; idx < listLen; idx++)
	{
		if(BM_HighestSetBit[list[idx]])
			return (idx<<3)+9-BM_HighestSetBit[list[idx]];
	}
	return INVALID_BIT;
}

/*************************************************
  Function: utili_bit_get_nextbit
  Description: get the bit number after bitno of bitlist
  Input: 
		list: operate bitlist
		bitno: the last bit number
		listLen: list len
  Output:
  		bitno:the next bit bigger number
  Return:
		TRUE:if any bit number bigger than bitno in bitlist
		FALSE:given bitno is the biggest bit in bitlist
  Note: 
		you can use this function in loop to fetch out all bit in bitlist
  History: 
*************************************************/
bc_boolean utili_bit_get_nextbit(IN const bc_uint8 *list, IN OUT bc_uint32 *bit, IN bc_uint32 listLen)
{
	int idx;
	int value;

	/* the last bit, no next exist */
	if (*bit >= listLen * BM_BYTEBITS)
	{
		return FALSE;
	}

	idx = BM_BYTEPOS(*bit+1);
	value = list[idx]&((BM_BITPOS(*bit+1)<<1)-1);
	
	/* 1st byte */
	if(value)
	{
		*bit = (idx<<3)+9-BM_HighestSetBit[value];
		return TRUE;
	}
	/* next bytes */
	for(idx++; idx<listLen; idx++)
	{
		if(BM_HighestSetBit[list[idx]])
		{
			*bit = (idx<<3)+9-BM_HighestSetBit[list[idx]];
			return TRUE;
		}
	}

	return FALSE;
}


/*************************************************
  Function: utili_bit_get_prevbit
  Description: get the bit number before bitno of bitlist
  Input: 
		list: operate bitlist
		bitno: the last bit number
		listLen: list len
  Output:
  		bitno: the previous bit number
  Return:
		TRUE:if any bit number lower than bitno in bitlist
		FALSE:given bitno is the lowest bit in bitlist
  Note: 
		you can use this function in loop to fetch out all bit in bitlist
  History: 
*************************************************/
bc_boolean utili_bit_get_prevbit(IN const bc_uint8 *list, IN OUT bc_uint32 *bit, IN bc_uint32 listLen)
{
	int idx;
	int value;

	/* the first bit, no prev exist */
	if (*bit <= 1)
	{
		return FALSE;
	}

	/* get the index */
	idx = BM_BYTEPOS(*bit);
	/* if index < length, check the rest bit */
	if (idx < listLen)
	{
		value = list[idx]&(~((BM_BITPOS(*bit)<<1)-1));
		if(value)
		{
			*bit = (idx<<3)+9-BM_LowestSetBit[value];
			return TRUE;
		}
	}
	else
	{
		/* start from the last byte (in for() will do idx--) */
		idx = listLen;
	}

	/* next bytes */
	for(idx--; idx>=0; idx--)
	{
		if(BM_LowestSetBit[list[idx]])
		{
			*bit = (idx<<3)+9-BM_LowestSetBit[list[idx]];
			return TRUE;
		}
	}

	return FALSE;
}

/*************************************************
  Function: utili_bit_is_bitset
  Description: check whether the bit in the bitlist set
  Input: 
		list: operate bitlist
		bitno: the last bit number
		listLen: list len
  Output:
  Return:
		TRUE  : bit is in bitlist
		FALSE : bit not in bitlist
  Note: 
  History: 
*************************************************/
bc_boolean utili_bit_is_bitset(IN const bc_uint8 *list, IN bc_uint32 bit, IN bc_uint32 listLen)
{
	if(BM_VALID(bit,listLen))
		return FALSE;
	
	if (list[BM_BYTEPOS(bit)] & (BM_BITPOS(bit)))
	{
		return TRUE;
	}

	return FALSE ;
}

/*************************************************
  Function: utili_bit_is_anybitset
  Description: check whether any bit in the bitlist set
  Input: 
		list: operate bitlist
		listLen: list len
  Output:
  Return:
		TRUE  : one or more than one bit is in bitlist
		FALSE : no bit in bitlist(NULL list)
  Note: 
  History: 
*************************************************/
bc_boolean utili_bit_is_anybitset(IN const bc_uint8 *list, IN bc_uint32 listLen)
{
	int 		i;

	for (i=0; i<listLen; i++)
	{
		if (list[i])
		{
			return TRUE;
		}
	}

	return FALSE;
}

/*************************************************
  Function: utili_bit_get_members
  Description: calculate how many bits in the bitlist
  Input: 
		list: operate bitlist
		listLen: list len
  Output:
  Return:
		bit members
  Note: 
  History: 
*************************************************/
int utili_bit_get_members(IN const bc_uint8 *list, IN bc_uint32 listLen)
{
	int		i,len=0;

	for (i=0; i<listLen; i++)
	{
		len+=BM_BitsLen[list[i]&0xF]+BM_BitsLen[(list[i]>>4)&0xF];
	}

	return len;
}

/*************************************************
  Function: utili_bit_is_overlap
  Description: check whether two bitlist is overlap
  Input: 
		list1: operate bitlist
		list2: operate bitlist
		listLen: list len
  Output:
  Return:
		TRUE:the two list have the overlap bit set
		FALSE:the two list haven't the overlap bit set
  Note: 
  History: 
*************************************************/
bc_boolean utili_bit_is_overlap(IN const bc_uint8 *list1, IN const bc_uint8 *list2, IN bc_uint32 listLen)
{
	int     i;

	for (i=0; i<listLen; i++)
	{
		if (list1[i] & list2[i])
		{
			return TRUE;
		}
	}

	return FALSE;
}

/*************************************************
  Function: utili_bit_is_subset
  Description: check if bitlist is the subset of another bitlist
  Input: 
		src: operate bitlist
		sub: subset bitlist
		listLen: list len
  Output:
  Return:
		TRUE:sub is the subset of src
		FALSE:otherwise
  Note: 
  History: 
*************************************************/
bc_boolean utili_bit_is_subset(IN const bc_uint8 *src, IN const bc_uint8 *sub, IN bc_uint32 listLen)
{
	int     i;

	for (i=0; i<listLen; i++)
	{
		if ((src[i] & sub[i]) != sub[i])
		{
			return FALSE;
		}
	}

	return TRUE;
}

/*************************************************
  Function: utili_bit_or_2list
  Description: OR two bitlist:des = src1 | src2
  Input: 
		src1	: operate bitlist
		src2	: operate bitlist
		listLen: list len
  Output:
  		dest	: result bitlist
  Return:
  Note: 
  History: 
*************************************************/
void utili_bit_or_2list(OUT bc_uint8 *dest, IN const bc_uint8 *src1, IN const bc_uint8 *src2, IN bc_uint32 listLen)
{
	int 		i;

	for (i=0; i<listLen; i++)
	{
		dest[i] = src1[i] | src2[i];
	}
}

/*************************************************
  Function: utili_bit_and_2list
  Description: AND two bitlist:des = src1 & src2
  Input: 
		src1	: operate bitlist
		src2	: operate bitlist
		listLen: list len
  Output:
  		dest	: result bitlist
  Return:
  Note: 
  History: 
*************************************************/
void utili_bit_and_2list(OUT bc_uint8 *dest, IN const bc_uint8 *src1, IN const bc_uint8 *src2, IN bc_uint32 listLen)
{
	int 		i;

	for (i=0; i<listLen; i++)
	{
		dest[i] = src1[i] & src2[i];
	}
}

/*************************************************
  Function: utili_bit_xor_2list
  Description: XOR two bitlist:des = src1 ^ src2
  Input: 
		src1	: operate bitlist
		src2	: operate bitlist
		listLen: list len
  Output:
  		dest	: result bitlist
  Return:
  Note: 
  History: 
*************************************************/
void utili_bit_xor_2list(OUT bc_uint8 *dest, IN const bc_uint8 *src1, IN const bc_uint8 *src2, IN bc_uint32 listLen)
{
	int 		i;

	for (i=0; i<listLen; i++)
	{
		dest[i] = src1[i] ^ src2[i];
	}
}

/*************************************************
  Function: utili_bit_maskout_list
  Description: mask bitlist:des = src & (~mask)
  Input: 
		src	: operate bitlist
		mask: mask bitlist
		listLen: list len
  Output:
  		dest	: result bitlist
  Return:
  Note: 
  History: 
*************************************************/
void utili_bit_maskout_list(OUT bc_uint8 *dest, IN const bc_uint8 *src, IN const bc_uint8 *mask, IN bc_uint32 listLen)
{
	int 		i;

	for (i=0; i<listLen; i++)
	{
		dest[i] = src[i] &((bc_uint8)~ mask[i]);
	}
}

/*************************************************
  Function: utili_bit_not
  Description: complement bitlist:des = ~src
  Input: 
		src	: operate bitlist
		listLen: list len
  Output:
  		dest	: result bitlist
  Return:
  Note: 
  History: 
*************************************************/
void utili_bit_not(OUT bc_uint8 *dest, IN const bc_uint8 *src, IN bc_uint32 listLen)
{
	int 		i;

	for (i=0; i<listLen; i++)
	{
		dest[i] = (bc_uint8)~src[i] ;
	}
}

/*************************************************
  Function: utili_bit_is_equal
  Description: check whether two bitlist have the same bit set
  Input: 
		list1	: operate bitlist
		list2	: operate bitlist
		listLen: list len
  Output:
  Return:
		TRUE:the two list have the same bit set
		FALSE:the two list have the different bit set
  Note: 
  History: 
*************************************************/
bc_boolean utili_bit_is_equal(IN const bc_uint8 *list1, IN const bc_uint8 *list2, IN bc_uint32 listLen)
{
	int 		i;

	for (i=0; i<listLen; i++)
	{
		if (list1[i] != list2[i])
		{
			return FALSE;
		}
	}
	return TRUE;
}

 /*************************************************
  Function: utili_bit_reverse_list
  Description: Reverse list
  Input: 
		list         list to reverse
		listLen     list length to reverse.
						 !!! the length of *revList must >= *list
  Output:
  		Output:  revList     reversed list
  Return:
		TRUE            reverse ok
		FALSE           somthings wrong in list length.
  Note: 
  History: 
*************************************************/
bc_boolean utili_bit_reverse_list(IN bc_uint8 *list, IN OUT bc_uint8 *revList, IN bc_uint32 listLen)
{
	int     i, j;
	bc_uint8   bit, revBit;

	memset(revList, 0, listLen);
	for (i=0; i<listLen; i++)
	{
		if (list[i] == 0)
			continue;
		bit = 0x80;
		revBit = 0x01;
		for (j=0; j<8; j++)
		{
			if (list[i] & bit)
				revList[listLen-i-1] |= revBit;
			bit = (bc_uint8)(bit >> 1);
			revBit = (bc_uint8)(revBit << 1);
		}/* end of for */
	}/* end of for */

	return TRUE;
}/* end of PORT_MAP_Reverse_List */


/*****************************************************************************
 * different size bitlist operation functions
 ******************************************************************************/


/*************************************************
  Function: utili_bit_or_2list_diffsize
  Description: or differ size
  Input: 
  Output:
  Return:
  Note: 
  History: 
*************************************************/
bc_boolean utili_bit_or_2list_diffsize(
	IN OUT bc_uint8 *dstListLong,
	IN const bc_uint8 *srcListShort,
	IN bc_uint32 longLen,
	IN bc_uint32 shortLen,
	IN bc_uint32 offset)
{
	int idx;

	if((offset+shortLen)>longLen)
		return FALSE;
	for (idx = 0; idx<shortLen; idx++)
	{
		dstListLong[offset + idx] |= srcListShort[idx];
	}

	return TRUE;
}

/*************************************************
  Function: utili_bit_and_2list_diffsize
  Description: 
  Input: 
  Output:
  Return:
  Note: 
  History: 
*************************************************/
bc_boolean utili_bit_and_2list_diffsize(
	IN OUT bc_uint8 *dstListLong,
	IN bc_uint8 *srcListLong,
	IN bc_uint8 *srcListShort,
	IN bc_uint32 longLen,
	IN bc_uint32 shortLen,
	IN bc_uint32 offset)
{
	int     idx;
	bc_uint8   *src, *dst;

	if((offset+shortLen)>longLen)
		return FALSE;

	src = srcListLong + offset;
	dst = dstListLong + offset;
	for (idx = 0; idx< shortLen; idx++)
	{
		dst[idx] = src[idx] & (bc_uint8)(srcListShort[idx]);
	}

	return TRUE;
}

/*************************************************
  Function: utili_bit_xor_2list_diffsize
  Description: 
  Input: 
  Output:
  Return:
  Note: 
  History: 
*************************************************/
bc_boolean utili_bit_xor_2list_diffsize(
	IN OUT bc_uint8 *dstListLong,
	IN bc_uint8 *srcListLong,
	IN bc_uint8 *srcListShort,
	IN bc_uint32 longLen,
	IN bc_uint32 shortLen,
	IN bc_uint32 offset)
{
	int     idx;
	bc_uint8   *src, *dst;

	if((offset+shortLen)>longLen)
		return FALSE;

	src = srcListLong + offset;
	dst = dstListLong + offset;
	for (idx = 0; idx< shortLen; idx++)
	{
		dst[idx] = src[idx] ^ (bc_uint8)(srcListShort[idx]);
	}

	return TRUE;
}

/*************************************************
  Function: utili_bit_maskout_list_diffsize
  Description: 
  Input: 
  Output:
  Return:
  Note: 
  History: 
*************************************************/
bc_boolean utili_bit_maskout_list_diffsize(
	IN OUT bc_uint8 *dstListLong,
	IN bc_uint8 *srcListLong,
	IN bc_uint8 *maskShort,
	IN bc_uint32 longLen,
	IN bc_uint32 shortLen,
	IN bc_uint32 offset)
{
	int     idx;
	bc_uint8   *src, *dst;

	if((offset+shortLen)>longLen)
		return FALSE;

	src  = srcListLong+ offset;
	dst = dstListLong+ offset;
	for (idx = 0; idx< shortLen; idx++)
	{
		dst[idx] = src[idx] & (bc_uint8)(~maskShort[idx]);
	}

	return TRUE;
}

/*************************************************
  Function: utili_bit_not_difffize
  Description: 
  Input: 
  Output:
  Return:
  Note: 
  History: 
*************************************************/
bc_boolean utili_bit_not_difffize(IN OUT bc_uint8 *longList, IN bc_uint32 longLen, IN bc_uint32 shortLen, IN bc_uint32 offset)
{
	int     idx;

	if((offset+shortLen)>longLen)
		return FALSE;
	for (idx = 0; idx< shortLen; idx++)
	{
		longList[idx+offset] = (bc_uint8)~longList[idx+offset];
	}

	return TRUE;
}

/*************************************************
  Function: utili_bit_set_list_diffsize
  Description: 
  Input: 
  Output:
  Return:
  Note: 
  History: 
*************************************************/
bc_boolean utili_bit_set_list_diffsize(
	IN OUT bc_uint8 *dstListLong,
	IN const bc_uint8 *srcListShort,
	IN bc_uint32 longLen,
	IN bc_uint32 shortLen,
	IN bc_uint32 offset)
{
	int idx;

	if((offset+shortLen)>longLen)
		return FALSE;
	for (idx = 0; idx<shortLen; idx++)
	{
		dstListLong[offset + idx] = srcListShort[idx];
	}

	return TRUE;
}

/*************************************************
  Function: utili_bit_get_list_diffsize
  Description: 
  Input: 
  Output:
  Return:
  Note: 
  History: 
*************************************************/
bc_boolean utili_bit_get_list_diffsize(
	IN bc_uint8 *srcListLong,
	IN OUT bc_uint8 *dstListShort,
	IN bc_uint32 longLen,
	IN bc_uint32 shortLen,
	IN bc_uint32 offset)
{
	int idx;

	if((offset+shortLen)>longLen)
		return FALSE;
	for (idx = 0; idx<shortLen; idx++)
	{
		dstListShort[idx] = srcListLong[offset + idx];
	}

	return TRUE;
}

/*************************************************
  Function: utili_bit_clear_list_diffsize
  Description: 
  Input: 
  Output:
  Return:
  Note: 
  History: 
*************************************************/
bc_boolean utili_bit_clear_list_diffsize(IN OUT bc_uint8 *longList, IN bc_uint32 longLen, IN bc_uint32 shortLen, IN bc_uint32 offset)
{
	int     idx;

	if((offset+shortLen)>longLen)
		return FALSE;
	for (idx = 0; idx< shortLen; idx++)
	{
		longList[idx+offset] = 0x0;
	}

	return TRUE;
}

/*************************************************
  Function: utili_bit_is_overlap_diffsize
  Description: 
  Input: 
  Output:
  Return:
  Note: 
  History: 
*************************************************/
bc_boolean utili_bit_is_overlap_diffsize(IN bc_uint8 *longList, IN bc_uint8 *shortList, IN bc_uint32 longLen, IN bc_uint32 shortLen, IN bc_uint32 offset)
{
	int     idx;

	if((offset+shortLen)>longLen)
		return FALSE;
	for (idx = 0; idx< shortLen; idx++)
	{
		if(longList[idx+offset] & shortList[idx])
			return TRUE;
	}

	return FALSE;
}

/*************************************************
  Function: utili_bit_get_members_diffsize
  Description: 
  Input: 
  Output:
  Return:
  Note: 
  History: 
*************************************************/
int utili_bit_get_members_diffsize(IN bc_uint8 *longList, IN bc_uint32 longLen, IN bc_uint32 shortLen, IN bc_uint32 offset)
{
	int		idx;
	int		len=0;

	if((offset+shortLen)>longLen)
		return 0;
	for (idx=0; idx<shortLen; idx++)
	{
		len+=BM_BitsLen[longList[idx+offset]&0xF]+BM_BitsLen[(longList[idx+offset]>>4)&0xF];
	}

	return len;
}

/*****************************************************************************
 * same size bitlist operation from specific offset.
 *****************************************************************************
 */
 
/*************************************************
  Function: utili_bit_get_list_specificsize
  Description: 
  Input: 
  Output:
  Return:
  Note: 
  History: 
*************************************************/
bc_boolean utili_bit_get_list_specificsize(
	IN OUT bc_uint8 *dstListLong,
	IN bc_uint8 *srcListLong,
	IN bc_uint32 longLen,
	IN bc_uint32 shortLen,
	IN bc_uint32 offset)
{
	int     idx;

	if((offset+shortLen)>longLen)
		return FALSE;

    memset(dstListLong,0x0,longLen);
	for (idx = 0; idx< shortLen; idx++)
	{
		dstListLong[idx+offset] = (bc_uint8)srcListLong[idx+offset];
	}

	return TRUE;
}

/*************************************************
  Function: utili_bit_maskout_list_specificsize
  Description: 
  Input: 
  Output:
  Return:
  Note: 
  History: 
*************************************************/
bc_boolean utili_bit_maskout_list_specificsize(
	IN OUT bc_uint8 *dstListLong,
	IN bc_uint8 *srcListLong,
	IN bc_uint32 longLen,
	IN bc_uint32 shortLen,
	IN bc_uint32 offset)
{
	int     idx;

	if((offset+shortLen)>longLen)
		return FALSE;

	for (idx = 0; idx< shortLen; idx++)
	{
		dstListLong[idx+offset] = dstListLong[idx+offset] & (bc_uint8)(~srcListLong[idx+offset]);
	}

	return TRUE;
}

/*****************************************************************************
 * different size bitlist operation functions
 *****************************************************************************
 */

/*************************************************
  Function: utili_bit_or_2list_specificsize
  Description: 
  Input: 
  Output:
  Return:
  Note: 
  History: 
*************************************************/
bc_boolean utili_bit_or_2list_specificsize(
	IN OUT bc_uint8 *dstListLong,
	IN const bc_uint8 *srcListLong,
	IN bc_uint32 longLen,
	IN bc_uint32 shortLen,
	IN bc_uint32 offset)
{
	int idx;

	if((offset+shortLen)>longLen)
		return FALSE;
	for (idx = 0; idx<shortLen; idx++)
	{
		dstListLong[offset + idx] |= srcListLong[offset + idx];
	}

	return TRUE;
}

/*************************************************
  Function: utili_bit_get_members_except_specificsize
  Description: 
  Input: 
  Output:
  Return:
  Note: 
  History: 
*************************************************/
int utili_bit_get_members_except_specificsize(IN const bc_uint8 *list, IN bc_uint32 longLen, IN bc_uint32 shortLen, IN bc_uint32 offset)
{
	int		i,len=0;

	if((offset+shortLen)>longLen)
		return 0;

	for (i=0; i<offset; i++)
	{
		len+=BM_BitsLen[list[i]&0xF]+BM_BitsLen[(list[i]>>4)&0xF];
	}

	for (i=offset+shortLen; i<longLen; i++)
	{
		len+=BM_BitsLen[list[i]&0xF]+BM_BitsLen[(list[i]>>4)&0xF];
	}

	return len;
}

/*************************************************
  Function: utili_bit_to_portstring
  Description: 
  Input: 
  Output:
  Return:
  Note: 
  History: 
*************************************************/
char *utili_bit_to_portstring(IN bc_uint8 *list, bc_uint32 listLen, char *buf)
{
    int	port,preport=-1,flag=-1;
    char 	tmp[8];


    if (buf == NULL) {
	return buf;
    }
	
    buf[0]=0;
	
     for ((port) = 1; (port) <= listLen*8; (port)++) 
    {
	if (!utili_bit_is_bitset(list, port,listLen))
		continue;
		
	if(preport==-1)
	{/*first dscp need to print*/
		flag=0;
		sprintf(tmp, "%d",port);
		strcat(buf,tmp);
	}
	else if((port-preport)==1)
	{/*continuous dscp,print "-" and wait next*/
		if(flag==0)
		{
			flag=1;/*need print preport at next print*/
		}
	}
	else
	{/*discontinuous dscp,need print*/
		if(flag==1)
		{/*need print predscp at next print*/
			sprintf(tmp, "-%d,%d",preport,port);
			strcat(buf,tmp);
			flag=0;
		}
		else
		{
			sprintf(tmp, ",%d",port);
			strcat(buf,tmp);
		}
	}
	preport=port;
    }
    if(flag==1)
    {
		sprintf(tmp, "-%d",preport);
		strcat(buf,tmp);
    }

    return buf;
}

/*************************************************
  Function: utili_bit_tostr
  Description: 
  Input: 
  Output:
  Return:
  Note: 
  History: 
*************************************************/
static char utili_bit_port_str[255];
char *utili_bit_tostr(IN bc_uint8 *list, bc_uint32 listLen)
{
	return utili_bit_to_portstring(list,listLen, utili_bit_port_str);
}


