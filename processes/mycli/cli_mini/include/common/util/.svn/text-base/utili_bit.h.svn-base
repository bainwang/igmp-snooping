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

 #ifndef __UTILI_BIT_H__
 #define __UTILI_BIT_H__

#include "bc_common_defs.h"

#define INVALID_BIT				-1


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
bc_boolean utili_bit_set_bit(IN OUT bc_uint8 *list, IN bc_uint32 bit, IN bc_uint32 list_len);

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
void utili_bit_set_allbit(OUT bc_uint8 *list, IN bc_uint32 listLen);

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
bc_boolean utili_bit_clear_bit(IN OUT bc_uint8 *list, IN bc_uint32 bit, IN bc_uint32 listLen);

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
void utili_bit_clear_list(OUT bc_uint8 *list, IN bc_uint32 listLen);

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
int utili_bit_get_firstbit(IN const bc_uint8 *list, IN bc_uint32 listLen);

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
bc_boolean utili_bit_get_nextbit(IN const bc_uint8 *list, IN OUT bc_uint32 *bit, IN bc_uint32 listLen);

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
bc_boolean utili_bit_get_prevbit(IN const bc_uint8 *list, IN OUT bc_uint32 *bit, IN bc_uint32 listLen);

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
bc_boolean utili_bit_is_bitset(IN const bc_uint8 *list, IN bc_uint32 bit, IN bc_uint32 listLen);

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
bc_boolean utili_bit_is_anybitset(IN const bc_uint8 *list, IN bc_uint32 listLen);

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
int utili_bit_get_members(IN const bc_uint8 *list, IN bc_uint32 listLen);

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
bc_boolean utili_bit_is_overlap(IN const bc_uint8 *list1, IN const bc_uint8 *list2, IN bc_uint32 listLen);

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
bc_boolean utili_bit_is_subset(IN const bc_uint8 *src, IN const bc_uint8 *sub, IN bc_uint32 listLen);

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
void utili_bit_or_2list(OUT bc_uint8 *dest, IN const bc_uint8 *src1, IN const bc_uint8 *src2, IN bc_uint32 listLen);

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
void utili_bit_and_2list(OUT bc_uint8 *dest, IN const bc_uint8 *src1, IN const bc_uint8 *src2, IN bc_uint32 listLen);

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
void utili_bit_xor_2list(OUT bc_uint8 *dest, IN const bc_uint8 *src1, IN const bc_uint8 *src2, IN bc_uint32 listLen);

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
void utili_bit_maskout_list(OUT bc_uint8 *dest, IN const bc_uint8 *src, IN const bc_uint8 *mask, IN bc_uint32 listLen);

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
void utili_bit_not(OUT bc_uint8 *dest, IN const bc_uint8 *src, IN bc_uint32 listLen);

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
bc_boolean utili_bit_is_equal(IN const bc_uint8 *list1, IN const bc_uint8 *list2, IN bc_uint32 listLen);

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
bc_boolean utili_bit_reverse_list(IN bc_uint8 *list, IN OUT bc_uint8 *revList, IN bc_uint32 listLen);

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
	IN bc_uint32 offset);

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
	IN bc_uint32 offset);

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
	IN bc_uint32 offset);

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
	IN bc_uint32 offset);

 /*************************************************
  Function: utili_bit_not_difffize
  Description: 
  Input: 
  Output:
  Return:
  Note: 
  History: 
*************************************************/
bc_boolean utili_bit_not_difffize(IN OUT bc_uint8 *longList, IN bc_uint32 longLen, IN bc_uint32 shortLen, IN bc_uint32 offset);

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
	IN bc_uint32 offset);

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
	IN bc_uint32 offset);

/*************************************************
  Function: utili_bit_clear_list_diffsize
  Description: 
  Input: 
  Output:
  Return:
  Note: 
  History: 
*************************************************/
bc_boolean utili_bit_clear_list_diffsize(IN OUT bc_uint8 *longList, IN bc_uint32 longLen, IN bc_uint32 shortLen, IN bc_uint32 offset);

/*************************************************
  Function: utili_bit_is_overlap_diffsize
  Description: 
  Input: 
  Output:
  Return:
  Note: 
  History: 
*************************************************/
bc_boolean utili_bit_is_overlap_diffsize(IN bc_uint8 *longList, IN bc_uint8 *shortList, IN bc_uint32 longLen, IN bc_uint32 shortLen, IN bc_uint32 offset);

/*************************************************
  Function: utili_bit_get_members_diffsize
  Description: 
  Input: 
  Output:
  Return:
  Note: 
  History: 
*************************************************/
int utili_bit_get_members_diffsize(IN bc_uint8 *longList, IN bc_uint32 longLen, IN bc_uint32 shortLen, IN bc_uint32 offset);

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
	IN bc_uint32 offset);

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
	IN bc_uint32 offset);

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
	IN bc_uint32 offset);

/*************************************************
  Function: utili_bit_get_members_except_specificsize
  Description: 
  Input: 
  Output:
  Return:
  Note: 
  History: 
*************************************************/
int utili_bit_get_members_except_specificsize(IN const bc_uint8 *list, IN bc_uint32 longLen, IN bc_uint32 shortLen, IN bc_uint32 offset);

/*************************************************
  Function: utili_bit_to_portstring
  Description: 
  Input: 
  Output:
  Return:
  Note: 
  History: 
*************************************************/
char *utili_bit_to_portstring(IN bc_uint8 *list, bc_uint32 listLen, char *buf);

/*************************************************
  Function: utili_bit_tostr
  Description: 
  Input: 
  Output:
  Return:
  Note: 
  History: 
*************************************************/
char *utili_bit_tostr(IN bc_uint8 *list, bc_uint32 listLen);

#endif

