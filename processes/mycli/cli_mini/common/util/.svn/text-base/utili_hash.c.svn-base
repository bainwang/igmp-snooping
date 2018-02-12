/*******************************************************************************
  Copyright (C), 1988-2013, xxxxx Tech. Co., Ltd.
  [File name]	: utili_hash.c
  [Author]     	: wangbin
  [Version]    	: 1.0
  [Date]       	: 2013-03-12
  [Description]	:
	hash api porting from cortina
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


/************************************************************************
Example:

-Data structure define:
  typedef struct 
  {
        utili_hash_node  node;    //the declaration must be put on the header of your structure
        signed int  data[20];
        signed int  key;
  }tTest;

#define YOUR_HASH_SIZE 128

unsigned int hashkey_generate(void *pNode)
{
    tTest *pTest = (tTest *)pNode;

    return (pTest->key%YOUR_HASH_SIZE);
}

signed int your_compare_func(void *pNode , unsigned int key)
{
    tTest *pTest = (tTest *)pNode;

    if(pTest->key > key) 
        return 1;
    else if(pTest->key < key)
        return -1;
    else
        return 0;
}

-- Create hash table
    utili_hash_tbl *your_hash_tbl = NULL;
    your_hash_tbl = utili_hash_create(YOUR_HASH_SIZE , hashkey_generate , your_compare_func);
    if(yor_hash_tbl == NULL)
        return ERROR;

-- Add a record to hash table
    tTest *add_node = NULL;
    add_node = (tTest *)iros_malloc(sizeof(tTest));
    if(add_node == NULL)
        return ERROR;
    add_node->key = 123;
    utili_hash_add(your_hash_tbl , (void *)add_node);

-- Find a record from hash table
-- Del a record from hash table  
      tTest *pDelNode=NULL;
      pDelNode = utili_hash_find(your_hash_tbl , 123);
      if(pDelNode != NULL) {
        utili_hash_del(your_hash_tbl , (void *)pDelNode);
      }

-- scan hash table
    Method-1:(use 'utili_hash_first' and 'utili_hash_next')
        tTest *prev=NULL,*next=NULL;
        unsigned int prev_buck=0,next_buck=0;
        int ret = BC_ERR_PARA;
        ret = utili_hash_first(your_hash_tbl , (void *)&prev , &prev_buck);
        while(ret == CS_HASH_OK)
        {
            next = NULL;
            next_buck = 0;
            ... //do what you want to do
            ret = utili_hash_next(your_hash_tbl , prev , prev_buck , (void *)&next , &next_buck);
            prev = next;
            prev_buck = next_buck;
        }

    Method-2:(use 'utili_scan_hash_bucket' and 'utili_scan_hash_record')(recommend)
        signed int hash_index;
        tTest *pNode=NULL;
        utili_scan_hash_bucket(your_hash_tbl , hash_index)
            utili_scan_hash_record(&your_hash_tbl->hash_list[hash_index] , pNode , tTest *)
        {
            ...  //do what you want to do
        }    

-- flush all records in hash table
        tTest *pNode=NULL;
        while((pNode=(tTest *)utili_hash_get(your_hash_tbl)) != NULL)
        {
            ... //call your own free function to free the node
        }

************************************************************************/

#if 1

#include <stdio.h>
#include <string.h>
#include "utili_hash.h"
#include "bc_modules.h"

utili_hash_tbl *utili_hash_create
    (
    unsigned int hash_size ,
    unsigned int(*hashkey_gen)(void *pNode),
    signed int (*compare)(void *pNode , unsigned int key)
    )
{
    utili_hash_tbl *pHashTbl = (utili_hash_tbl *)0;
    char hash_name[20];
    signed int i;

    if (hashkey_gen == NULL || compare == NULL || hash_size == 0) {
        return (utili_hash_tbl *)NULL;
    }

    pHashTbl = (utili_hash_tbl *)bc_platform_mem_malloc(BC_MODULE_UTILI ,
                                          sizeof(utili_hash_tbl) + (hash_size - 1) * sizeof(utili_list));
    if (pHashTbl == NULL) {
        return NULL;
    }
    memset(pHashTbl , 0 , sizeof(utili_hash_tbl));

    for (i = 0 ; i < hash_size ; i++) {
        utili_lst_init(&pHashTbl->hash_list[i] , NULL);
    }

    memset(hash_name , 0 , sizeof(hash_name));
    sprintf(hash_name , "hash%d" , (unsigned int)pHashTbl);
	pHashTbl->hash_mutex_id = bc_platform_mutex_create(hash_name);
    if (pHashTbl->hash_mutex_id == NULL) {
        bc_platform_mem_free(BC_MODULE_UTILI, pHashTbl);
        return NULL;
    }

    pHashTbl->hashkey_gen = hashkey_gen;
    pHashTbl->compare = compare;
    pHashTbl->hash_size = hash_size;

    return (utili_hash_tbl *)pHashTbl;
}

signed int utili_hash_destroy
    (
    utili_hash_tbl *pHashTbl
    )
{
    if(pHashTbl == NULL)
        return BC_ERR_PARA;

    bc_platform_mutex_destroy(pHashTbl->hash_mutex_id);

    bc_platform_mem_free(BC_MODULE_UTILI, pHashTbl);

    return BC_ERR_OK;
}


signed int utili_hash_add(utili_hash_tbl * pHashTbl , void *pNode)
{
    unsigned int hash_key;

    if (pHashTbl == NULL || pNode == NULL) {
        return BC_ERR_PARA;
    }

    hash_key = pHashTbl->hashkey_gen((void *)pNode);
    if (hash_key >= pHashTbl->hash_size) {
        return BC_ERR_PARA;
    }

    HASH_TBL_LOCK(pHashTbl);
    utili_lst_add(&pHashTbl->hash_list[hash_key] , (utili_node *)pNode);
    pHashTbl->count++;
    HASH_TBL_UNLOCK(pHashTbl);

    return BC_ERR_OK;
}

signed int utili_hash_del(utili_hash_tbl * pHashTbl , void *pNode)
{
    int hash_key;

    if (pHashTbl == NULL || pNode == NULL) {
        return BC_ERR_PARA;
    }

    hash_key = pHashTbl->hashkey_gen((void *)pNode);
    if (hash_key >= pHashTbl->hash_size) {
        return BC_ERR_PARA;
    }


    HASH_TBL_LOCK(pHashTbl);
    utili_lst_delete(&pHashTbl->hash_list[hash_key] , (utili_node *)pNode);
    pHashTbl->count--;
    HASH_TBL_UNLOCK(pHashTbl);

    return BC_ERR_OK;
}

signed int utili_hash_first
    (
    utili_hash_tbl * pHashTbl ,
    void **pFirst ,
    unsigned int *bucket_idx
    )
{
    int hash_key;

    if (pHashTbl == NULL) {
        return BC_ERR_PARA;
    }

    HASH_TBL_LOCK(pHashTbl);
    utili_scan_hash_bucket(pHashTbl, hash_key) {
        if (utili_lst_count(&pHashTbl->hash_list[hash_key])) {
            *pFirst = (void *)utili_lst_first(&pHashTbl->hash_list[hash_key]);
            *bucket_idx = hash_key;
            HASH_TBL_UNLOCK(pHashTbl);
            return BC_ERR_OK;
        }
    }
    HASH_TBL_UNLOCK(pHashTbl);

    return BC_ERR_PARA;
}

signed int utili_hash_next
    (
    utili_hash_tbl * pHashTbl ,
    void *pPrev,
    unsigned int prev_bucket_idx,
    void **pNext ,
    unsigned int *bucket_idx
    )
{
    int hash_key;

    if (pHashTbl == NULL) {
        return BC_ERR_PARA;
    }

    HASH_TBL_LOCK(pHashTbl);
    *pNext = (void *)utili_lst_next((utili_node *)pPrev);
    if (*pNext == NULL) {
        if (prev_bucket_idx >= pHashTbl->hash_size) {
            HASH_TBL_UNLOCK(pHashTbl);
            return BC_ERR_PARA;
        } else {
            for (hash_key = prev_bucket_idx + 1 ; hash_key < pHashTbl->hash_size ; hash_key++) {
                *pNext = (void *)utili_lst_first(&pHashTbl->hash_list[hash_key]);
                if (*pNext != NULL) {
                    *bucket_idx = hash_key;
                    HASH_TBL_UNLOCK(pHashTbl);
                    return BC_ERR_OK;
                }
            }
        }
    } else {
        *bucket_idx = prev_bucket_idx;
        HASH_TBL_UNLOCK(pHashTbl);
        return BC_ERR_OK;
    }
    HASH_TBL_UNLOCK(pHashTbl);

    return BC_ERR_PARA;
}

utili_hash_node *utili_hash_find
    (
    utili_hash_tbl * pHashTbl ,
    unsigned int key
    )
{
    unsigned int hash_key;
    utili_hash_node *pNode = NULL;

    if(pHashTbl == NULL)
    {
        return NULL;
    }

    HASH_TBL_LOCK(pHashTbl);
    utili_scan_hash_bucket(pHashTbl, hash_key)
        utili_scan_hash_record(&pHashTbl->hash_list[hash_key], pNode, utili_hash_node *)
    {
        if(pHashTbl->compare((void *)pNode , key) == 0) {
            HASH_TBL_UNLOCK(pHashTbl);
            return pNode;
        }
    }
    HASH_TBL_UNLOCK(pHashTbl);

    return NULL;
}

utili_hash_node *utili_hash_get(utili_hash_tbl * pHashTbl)
{
    unsigned int hash_key;
    utili_hash_node *pNode = NULL;
    
    if(pHashTbl == NULL) {
        return NULL;
    }

    HASH_TBL_LOCK(pHashTbl);
    utili_scan_hash_bucket(pHashTbl, hash_key)
    {
        pNode = (utili_hash_node *)utili_lst_get(&pHashTbl->hash_list[hash_key]);
        if(pNode == NULL) {
            continue;
        }

        pHashTbl->count--;
        HASH_TBL_UNLOCK(pHashTbl);
        return pNode;
    }
    
    HASH_TBL_UNLOCK(pHashTbl);
    return NULL;
}

unsigned int utili_hash_count(utili_hash_tbl * pHashTbl)
{
    if(pHashTbl == NULL) {
        return 0;
    }

    return pHashTbl->count;
}

#endif

