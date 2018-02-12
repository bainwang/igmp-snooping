/*******************************************************************************
  Copyright (C), 1988-2013, xxxxx Tech. Co., Ltd.
  [File name]	: utili_list.c
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

/******************************************************
*
* Example:
*
*
*
*    typedef struct{
*        utili_node node;
*        int a;
*        int b;
*        int c[100];
*    }structA;
*
*   utili_list myList;
*
*   lstInit(&myList);
*   for(i = 0 ; i < 50 ; i++)
*   {
*        structA *p;
*        p = (structA *)iros_malloc(IROS_MODULE_ID_SYS,sizeof(structA));
*        p->a = i;
*        p->b = i;
*        lstAdd(&myList , (utili_node *)p);
*   }
*
*   for(p = (structA *)lstFirst(&myList) ; p ; p = (structA *)lstNext((utili_node *)p))
*   {
*        <scan the list>
*   }

Description:
    init list with the compare function, the compare function is necessary for
    remove the specific node and find the specific node
    compare function has two arguments,Eg.
    compare(pNodeA , pNodeB)
    if(pNodeA < pNodeB) return -1;
    if(pNodeA = pNodeB) return 0;
    if(pNodeA > pNodeB) return 1;
    typedef struct {
        utili_node node;
        int key1;
        int key2;
        int key3;
        char data[1000];
    }tStruct;

    yourself_compre((tStruct *)TA , (tStruct *)TB)
    {
        if(TA->key1 > TB->key1) return 1;
        else if(TA->key1 < TB->key1) return -1;
        else ;

        if(TA->key2 > TB->key2) return 1;
        else if(TA->key2 < TB->key2) return -1;
        else ;

        if(TA->key3 > TB->key3) return 1;
        else if(TA->key3 < TB->key3) return -1;
        else return 0;
    }
**********************************************************/

#include <string.h>
#include "bc_common_defs.h"
#include "utili_list.h"

void utili_lst_init(utili_list * pLst , signed int (*compare)(void * , unsigned int))
{
    pLst->utili_head = NULL;
    pLst->utili_tail = NULL;
    pLst->count = 0;
    pLst->compare = compare;
}

/**********************************************************
Description:
   insert a new node 'pNode' after  the specific node  'pPrevious'
**********************************************************/
void utili_lst_insert(utili_list * pLst, utili_node * pPrevious, utili_node * pNode)
{
    utili_node * pNext = NULL;

    if (NULL == pPrevious) {
        pNext = pLst->utili_head;
        pLst->utili_head = pNode;
    } else {
        pNext = pPrevious->next;
        pPrevious->next = pNode;
    }

    if (NULL == pNext) {
        pLst->utili_tail = pNode;
    } else {
        pNext->previous = pNode;
    }

    pNode->previous = pPrevious;
    pNode->next = pNext;

    pLst->count++;
}

/**********************************************************
Description:
   add a new node to the tail of 'pLst'
**********************************************************/
void utili_lst_add(utili_list * pLst, utili_node * pNode)
{
    utili_lst_insert(pLst, pLst->utili_tail, pNode);
}

/**********************************************************
Description:
   Find the actual node according to the 'key' and remove it from 'pLst',
   The operatoin doesn't mean to free the node , it is only cut off from 'pLst'
**********************************************************/
utili_node *utili_lst_remove(utili_list * pLst , unsigned int key)
{
    utili_node *remove_node = (utili_node *)NULL;

    if (pLst->compare == NULL) {
        return (utili_node *)remove_node;
    }

    utili_lst_scan(pLst , remove_node , utili_node *) {
        if (pLst->compare((void *)remove_node , key) == 0) {
            utili_lst_delete(pLst , remove_node);
            return (utili_node *)remove_node;
        }
    }

    return (utili_node *)NULL;
}

/**********************************************************
Description:
   The operatoin doesn't mean to free the node , it is only cut off from 'pLst'
**********************************************************/
void utili_lst_delete(utili_list * pLst, utili_node * pNode)
{
    if (pNode->previous == NULL) {
        pLst->utili_head = pNode->next;
    } else {
        pNode->previous->next = pNode->next;
    }

    if (pNode->next == NULL) {
        pLst->utili_tail = pNode->previous;
    } else {
        pNode->next->previous = pNode->previous;
    }

    pLst->count--;
}

utili_node * utili_lst_first(utili_list * pLst)
{
    return pLst->utili_head;
}

utili_node * utili_lst_last(utili_list * pLst)
{
    return pLst->utili_tail;
}

/**********************************************************
Description:
   get the pointer of the first node in the list , and the node will be cutted off
   from the header of the list
**********************************************************/
utili_node * utili_lst_get(utili_list * pLst)
{
    utili_node * pNode = NULL;

    pNode = pLst->utili_head;

    if (pNode != NULL) {
        pLst->utili_head = pNode->next;

        if (pNode->next == NULL) {
            pLst->utili_tail = NULL;
        } else {
            pNode->next->previous = NULL;
        }

        pLst->count--;
    }

    return pNode;
}


utili_node * utili_lst_nth(utili_list * pLst, int nodeNum)
{
    utili_node * pNode = NULL;

    if (nodeNum < 1 || nodeNum > pLst->count) {
        return NULL;
    }

    if (nodeNum < ((pLst->count + 1) >> 1)) {
        pNode = pLst->utili_head;

        while (--nodeNum > 0) {
            pNode = pNode->next;
        }
    } else {
        nodeNum -= pLst->count;
        pNode = pLst->utili_tail;

        while (nodeNum++ < 0) {
            pNode = pNode->previous;
        }
    }

    return pNode;
}

/**********************************************************
Description:
   Get the pointer of the actual node according to the 'key'
**********************************************************/
utili_node *utili_lst_find(utili_list *pLst , unsigned int key)
{
    utili_node *find_node = NULL;

    if (pLst->compare == NULL) {
        return (utili_node *)find_node;
    }

    utili_lst_scan(pLst , find_node , utili_node *) {
        if (pLst->compare((void *)find_node , key) == 0)
            return (utili_node *)find_node;
    }

    return (utili_node *)NULL;
}

utili_node * utili_lst_prev(utili_node * pNode)
{
    return pNode->previous;
}

utili_node * utili_lst_next(utili_node * pNode)
{
    return pNode->next;
}

unsigned int utili_lst_count(utili_list * pLst)
{
    return pLst->count;
}

utili_list *utili_lst_concat(utili_list *pDst , utili_list *pSrc)
{
    if(pDst == NULL || pSrc == NULL){
        return NULL;
    }

    if(pDst->compare != pSrc->compare) {
        return NULL;
    }

    if(pDst->count == 0) {
        memcpy(pDst , pSrc , sizeof(utili_list));
        return (utili_list *)pDst;
    }

    if(pSrc->count == 0) {
        return (utili_list *)pDst;
    }

    pDst->utili_tail->next = pSrc->utili_head;
    pSrc->utili_head->previous = pDst->utili_tail;    
    pDst->utili_tail = pSrc->utili_tail;
    
    pDst->count += pSrc->count;

    utili_lst_init(pSrc , pSrc->compare);

    return (utili_list *)pDst;
}


