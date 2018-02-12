/*******************************************************************************
  [File name]	: utili_hash.h
  [Author]     	: bain.wang@outlook.com
  [Version]    	: 1.0
  [Date]       	: 2017-04-04
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
	2017-04-04  	Created								 bain.wang@outlook.com
*******************************************************************************/

#ifndef _UTILI_HASH_H_
#define _UTILI_HASH_H_

#if 1

#include "utili_list.h"
#include "bc_platform_mutex.h"
#include "bc_platform_mem.h"

typedef utili_node utili_hash_node;

typedef struct {
    unsigned int hash_size;
    bc_pthread_mutex_t *hash_mutex_id;
    unsigned int (*hashkey_gen)(void *pNode);
    int (*compare)(void *pNode , unsigned int key);
    unsigned int count;
    utili_list hash_list[1];
} utili_hash_tbl;

#define HASH_TBL_LOCK(p) do{if(p) bc_platform_mutex_lock(p->hash_mutex_id);} while(0)
#define HASH_TBL_UNLOCK(p) do{if(p) bc_platform_mutex_unlock(p->hash_mutex_id);} while(0)

#define utili_scan_hash_bucket(pHashTbl , hash_index) \
                    for(hash_index = 0 ; hash_index < pHashTbl->hash_size ; hash_index++)

#define utili_scan_hash_record(pLst , pNode , type) \
                    for(pNode=(type)utili_lst_first(pLst);pNode;pNode=(type)utili_lst_next((utili_node *)pNode))

extern utili_hash_tbl *utili_hash_create(
                unsigned int hash_size ,
                unsigned int(*hashkey_gen)(void *pNode),
                int (*compare)(void *pNode , unsigned int key));
					
extern int utili_hash_destroy(utili_hash_tbl *pHashTbl);
extern int utili_hash_add(utili_hash_tbl * pHashTbl , void *pNode);          
extern int utili_hash_del(utili_hash_tbl * pHashTbl , void *pNode);
extern int utili_hash_first(
                utili_hash_tbl * pHashTbl ,
                void **pFirst ,
                unsigned int *bucket_idx);

extern int utili_hash_next(
                utili_hash_tbl * pHashTbl ,
                void *pPrev,
                unsigned int prev_bucket_idx,
                void **pNext ,
                unsigned int *bucket_idx);

extern utili_hash_node *utili_hash_find(
                utili_hash_tbl * pHashTbl ,
                unsigned int key);

extern utili_hash_node *utili_hash_get(utili_hash_tbl * pHashTbl);

#endif
#endif

