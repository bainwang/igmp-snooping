/*******************************************************************************
  Copyright (C), 1988-2013, xxxxx Tech. Co., Ltd.
  [File name]	: utili_list.h
  [Author]     	: wangbin
  [Version]    	: 1.0
  [Date]       	: 2013-03-12
  [Description]	:
	list api porting from cortina
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

#ifndef _UTILI_LIST_H_
#define _UTILI_LIST_H_

typedef struct bc_node_t
{
    struct bc_node_t * previous;
    struct bc_node_t * next;
} utili_node;

typedef struct bc_list
{
    utili_node node;
    unsigned int count;
    signed int (*compare)(void * , unsigned int);
} utili_list;

#define utili_tail node.previous
#define utili_head node.next

extern void utili_lst_init(utili_list * pLst , signed int (*compare)(void * , unsigned int));
extern void utili_lst_insert(utili_list * pLst, utili_node * pPrevious, utili_node * pNode);
extern void utili_lst_add(utili_list * pLst, utili_node * pNode);
utili_node *utili_lst_remove(utili_list * pLst , unsigned int key);
extern void utili_lst_delete(utili_list * pLst, utili_node * pNode);
extern utili_node * utili_lst_first(utili_list * pLst);
extern utili_node * utili_lst_last(utili_list * pLst);
extern utili_node * utili_lst_get(utili_list * pLst);
extern utili_node * utili_lst_nth(utili_list * pLst, int nodeNum);
utili_node *utili_lst_find(utili_list *pLst , unsigned int key);
extern utili_node * utili_lst_prev(utili_node * pNode);
extern utili_node * utili_lst_next(utili_node * pNode);
extern unsigned int utili_lst_count(utili_list * pLst);
extern utili_list *utili_lst_concat(utili_list *pDst , utili_list *pSrc);

#define utili_lst_scan(pList , pNode , type) for(pNode=(type)utili_lst_first(pList);pNode;pNode=(type)utili_lst_next((utili_node *)pNode))


#endif

