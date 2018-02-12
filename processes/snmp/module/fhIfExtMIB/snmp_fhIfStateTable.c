/*******************************************************************************
  [Author]	   : bain.wang@outlook.com.uestc@gmail.com
  [Version]    : 1.0
  [Date]       : 2017-02-20
  [Description]:

  [Others]     :

  [History]:
	 Date          Modification 							    Initials
	----------     ----------                                   -------
	2017-02-20      Created								   		bain.wang@outlook.com
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//																			  //
//								头   文   件								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include <net-snmp/agent/header_complex.h>

#include "snmp_fhIfStateTable.h"
#include "snmp_global.h"
#include "snmp_core_ex.h"


///////////////////////////////////////////////////////////////////////////////
//                                                               			 //
//																			 //
//						外 部 变 量、 函 数 引 用					         //
//																			 //
///////////////////////////////////////////////////////////////////////////////
static snmp_find_var_callback   __snmp_fhIfStateTable_handler;


///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//																			 //
//						结   构   体   宏   定   义							 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
#if 1


#define SNMP_PON_PORT_TBL_STORAGE_QUERY(StorageTmp)	\
									do{ \
										size_t	newlen =  name_len - (fhIfStateTable_variables_oid_len + 3 - 1);\
										if(!(StorageTmp = header_complex(fhIfStateTableStorage, NULL, &name[fhIfStateTable_variables_oid_len + 3 - 1], &newlen, 1, NULL, NULL)))\
										{\
											BC_PT_FUN_TAG(BC_MODULE_SNMP);\
											return SNMP_ERR_NOSUCHNAME; \
										}\
									}while(0)

#define SNMP_NODE_INDEX_GET(idx)	\
	do{	\
		idx = node->fhIfStateIndex;	\
	}while(0)

		
	
#define SNMP_TABLE_RM_LIST(list, type)	\
	do{	\
		struct header_complex_index *t_list = list;	\
		while(t_list){	\
			struct header_complex_index *listn = t_list->next;	\
			type *t_node = header_complex_extract_entry(&list, t_list);	\
			netsnmp_assert(t_node);	\
			SNMP_FREE(t_node);	\
			t_list = listn;	\
		}	\
	}while(0)				
#endif 



/*
 *		当源文件需要定义宏，而头文件又与其它模块头文件中的宏定义有重复定义嫌疑
 *	时，在此处定义。
 */

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//																			 //
//							全 局 变 量 定 义							     //
//																			 //
///////////////////////////////////////////////////////////////////////////////

/* 
 *	外部全局变量，提供整个工程调用，在头文件中提供调用接口(外部引用声明)。
 */

/* 
 *	内部全局变量，只提供给该文件内部函数调用，不在头文件中提供调用接口。
 */
#if 1
static struct variable2 fhIfStateTable_variables[] = 
{
	{COLUMN_FHIFSTATEINDEX, ASN_INTEGER, NETSNMP_OLDAPI_RONLY, 
		__snmp_fhIfStateTable_handler, 2, {1, 1}},
	{COLUMN_FHIFDESCR, ASN_OCTET_STR, NETSNMP_OLDAPI_RONLY, 
		__snmp_fhIfStateTable_handler, 2, {1, 2}},
	{COLUMN_FHIFMODE, ASN_INTEGER, NETSNMP_OLDAPI_RONLY, 
		__snmp_fhIfStateTable_handler, 2, {1, 3}}
};

static oid fhIfStateTable_variables_oid[] = {1,3,6,1,4,1,11408,11,1,2,1};
static const int fhIfStateTable_variables_oid_len = FHIFSTATETABLE_OID_LEN;
static struct header_complex_index *fhIfStateTableStorage = NULL;

static time_t update_time;

//这里定义包含全部索引的全局指针
static int *fhIfStateTable_idxs = NULL;
//这里定义表最大索引数
#define fhIfStateTable_num	2

#endif


///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//																			 //
//								函  数  声  明								 //
//																			 //
///////////////////////////////////////////////////////////////////////////////

	
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//																			 //
//								函  数  定  义								 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
#if 1	/*虚拟API，用于X86测试*/

static bc_boolean vir_api_get_idxs(int __fhIfStateTable_idxs[fhIfStateTable_num], int *fhIfStateIndex_num)
{
	int i = 0;

	for(; i<fhIfStateTable_num; i++)
	{
		__fhIfStateTable_idxs[i] = i+1;
	}
	*fhIfStateIndex_num = fhIfStateTable_num;

	return TRUE;
}

static bc_boolean vir_api_get_data(struct fhIfStateTable_entry data[fhIfStateTable_num], int *fhIfStateIndex_num)
{
	int i = 0;

	for(; i<fhIfStateTable_num; i++)
	{
		data[i].fhIfStateIndex = i+1;
		strcpy(data[i].fhIfDescr, "192.168.5.198");
   		data[i].fhIfMode = i+5;
	}
	*fhIfStateIndex_num = fhIfStateTable_num;

	return TRUE;
}
#endif


///////////////////////////////////////////////////////////////////////////////
//                                                               			 //
//																			 //
//						外 部 变 量、 函 数 引 用					         //
//																			 //
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//																			 //
//								函  数  定  义								 //
//																			 //
///////////////////////////////////////////////////////////////////////////////


#if 1
static bc_int32 __snmp_fhIfStateTable_add(struct fhIfStateTable_entry *node)
{
   	netsnmp_variable_list *vars = NULL;
		
	snmp_varlist_add_variable(&vars, NULL, 0, ASN_INTEGER,
		&node->fhIfStateIndex, sizeof(node->fhIfStateIndex));

	header_complex_add_data(&fhIfStateTableStorage, vars, node);

	return SNMPERR_SUCCESS;
}

static struct fhIfStateTable_entry *__snmp_fhIfStateTable_create(void)
{
	struct fhIfStateTable_entry *entry = SNMP_MALLOC_STRUCT(fhIfStateTable_entry);
	if(!entry)
	{
		return NULL;
	}
	memset(entry, 0, sizeof(struct fhIfStateTable_entry));
	entry->storageType =  ST_NONVOLATILE;
	
	return entry;
}

#if 1
static void __snmp_free_fhIfStateTable_data(struct fhIfStateTable_entry *StorageDel)
{
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	
    netsnmp_assert(StorageDel);
    free(StorageDel);
}
#endif



bc_boolean __snmp_fhIfStateTable_update_x86(bc_int32 __fhIfStateIndex)
{
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	
	if (NULL == fhIfStateTableStorage)
	{
		BC_PT_FUN_TAG(BC_MODULE_SNMP);
		struct fhIfStateTable_entry *StorageTmp = NULL;
		StorageTmp = __snmp_fhIfStateTable_create();
		
		StorageTmp->fhIfStateIndex = 1;
		
		__snmp_fhIfStateTable_add(StorageTmp);
	}
	
	BC_PT_FUN_LEAVE(BC_MODULE_SNMP);
	return TRUE;
}

bc_boolean __snmp_fhIfStateTable_index_update(bc_int32 *fhIfStateIndex_num)
{	
	bc_boolean ret = TRUE;
	
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	struct fhIfStateTable_entry *StorageTmp = NULL;
	struct header_complex_index *fhIfStateTableTemp = NULL;

	bc_int32 i = 0; 
	
	bc_int32 __fhIfStateTable_idxs[fhIfStateTable_num];

	vir_api_get_idxs(__fhIfStateTable_idxs, fhIfStateIndex_num);
	
	SNMP_MEM_GET(fhIfStateTable_idxs, int, fhIfStateTable_num);
	memcpy(fhIfStateTable_idxs, __fhIfStateTable_idxs, sizeof(__fhIfStateTable_idxs));

	for (i = 0; i < *fhIfStateIndex_num; i++)
	{
		fhIfStateTableTemp = fhIfStateTableStorage;
		StorageTmp = NULL;
		while(fhIfStateTableTemp)
		{
			StorageTmp = (struct fhIfStateTable_entry *)fhIfStateTableTemp->data;
			if (StorageTmp->fhIfStateIndex == __fhIfStateTable_idxs[i] )
			{
				break;
			}
			fhIfStateTableTemp = fhIfStateTableTemp->next;
		}
		
		if (!fhIfStateTableTemp)
		{
			StorageTmp = __snmp_fhIfStateTable_create();

			StorageTmp->fhIfStateIndex = __fhIfStateTable_idxs[i];	//modiry
			__snmp_fhIfStateTable_add(StorageTmp);
		}

	}	

	fhIfStateTableTemp = fhIfStateTableStorage;
	while (fhIfStateTableTemp)
	{
		StorageTmp = (struct fhIfStateTable_entry *)fhIfStateTableTemp->data;
		for(i = 0; i < *fhIfStateIndex_num; i++)
		{
			if (StorageTmp->fhIfStateIndex == __fhIfStateTable_idxs[i])				
			{
				break;
			}
		}	

		if (i == *fhIfStateIndex_num)
		{
			struct header_complex_index *hciptrn = fhIfStateTableTemp->next;
			BC_PT_DBG_FUN(BC_MODULE_SNMP, "FREE!!!!\n");
			struct fhIfStateTable_entry *StorageDel = header_complex_extract_entry(&fhIfStateTableStorage, fhIfStateTableTemp);
			__snmp_free_fhIfStateTable_data(StorageDel);

			fhIfStateTableTemp = hciptrn;
		}
		else
		{
			fhIfStateTableTemp = fhIfStateTableTemp->next;
		}
	}

	BC_PT_FUN_LEAVE(BC_MODULE_SNMP);
	return ret;
}


bc_boolean __snmp_fhIfStateTable_update_dev(bc_int32 __fhIfStateIndex)
{
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
//	bc_boolean ret = TRUE;
//	bc_int32 api_ret;
	struct fhIfStateTable_entry *StorageTmp = NULL;
	struct header_complex_index *fhIfStateTableTemp = NULL;

	bc_int32 __fhIfStateIndex_tmp = 0;
	bc_int32 __update_count = 0;
	
	bc_int32 fhIfStateIndex_num;
//	bc_int32 count = 0;
	bc_int32 next_is_chk = TRUE;

	struct fhIfStateTable_entry data_tmp[fhIfStateTable_num];
	int data_cnt = 0;

	int i = 0;
	
	BC_PT_FUN_TAG(BC_MODULE_SNMP);

	if(snmp_is_update(&update_time))
	{
		if (!__snmp_fhIfStateTable_index_update(&fhIfStateIndex_num))
		{
			BC_PT_DBG_CPL(BC_MODULE_SNMP, "__snmp_fhIfStateTable_index_update() failed!\r\n");
			return FALSE;
		}

		fhIfStateTableTemp = fhIfStateTableStorage;
		while(fhIfStateTableTemp)
		{
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			StorageTmp = (struct fhIfStateTable_entry *)fhIfStateTableTemp->data;

			__fhIfStateIndex_tmp = StorageTmp->fhIfStateIndex;

			BC_PT_DBG_FUN(BC_MODULE_SNMP, "next_is_chk=%d\n",next_is_chk);
			
			if((__fhIfStateIndex_tmp != __fhIfStateIndex) && (next_is_chk == TRUE))
			{
				fhIfStateTableTemp = fhIfStateTableTemp->next;			
			}
			else	
			{
				next_is_chk = FALSE;
				
				vir_api_get_data(data_tmp, &data_cnt);

				for(i=0; i<data_cnt; i++)
				{
					if(data_tmp[i].fhIfStateIndex == __fhIfStateIndex_tmp)
					{
						memcpy(StorageTmp, data_tmp+i, sizeof(struct fhIfStateTable_entry));
						break;
					}
				}
				#if 0
				printf("StorageTmp->fhIfStateIndex = %d\n", StorageTmp->fhIfStateIndex);
				printf("StorageTmp->fhIfDescr = %s\n", StorageTmp->fhIfDescr);
				printf("StorageTmp->fhIfMode = %d\n", StorageTmp->fhIfMode);
				#endif
				
				fhIfStateTableTemp = fhIfStateTableTemp->next;			

				__update_count++;
				BC_PT_DBG_FUN(BC_MODULE_SNMP, "__update_count=%d\n", __update_count);
				if (__update_count >= 2)
				{
					BC_PT_DBG_FUN(BC_MODULE_SNMP, "It's the end!!!!\n");
					next_is_chk = 0;
					break;
				}
			}
		}
	}
	SNMP_MEM_FREE(fhIfStateTable_idxs);
	return TRUE;
}		




static bc_boolean __snmp_fhIfStateTable_update(bc_int32 __fhIfStateIndex)
{
#ifdef SNMP_PRJ_SNMP_X86
		return __snmp_fhIfStateTable_update_x86(__fhIfStateIndex);
#else
		return __snmp_fhIfStateTable_update_dev(__fhIfStateIndex);
#endif
}


static unsigned char *__snmp_fhIfStateTable_handler(struct variable *vp,
																		oid *name,
																		size_t *length,
																		int exact,
																		size_t *var_len,
																		WriteMethod **write_method)
{	
	struct fhIfStateTable_entry *node = NULL;

	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	bc_int32 __fhIfStateIndex = 0;

	SNMP_NODE_OID_PT(name, *length);
	
	if (*length == FHIFSTATETABLE_OID_FULL_LEN)
	{
		BC_PT_FUN_TAG(BC_MODULE_SNMP);
		__fhIfStateIndex = name[*length - 1];
	}
	
	else if (*length < FHIFSTATETABLE_OID_FULL_LEN)
	{
		BC_PT_DBG_FUN(BC_MODULE_SNMP, "*length=%d\n",*(size_t *)length);
		__fhIfStateIndex = 1;
	}
	
	if(!__snmp_fhIfStateTable_update(__fhIfStateIndex))
	{
		BC_PT_DBG_FUN(BC_MODULE_SNMP, "__snmp_fhIfStateTable_update() failed!!\r\n");
		return NULL;
	}
	
	SNMP_HDL_HEADER_COMPLEX(fhIfStateTableStorage, vp, name, length, exact, var_len, write_method, NULL, SNMP_TABLE_NO_ROW_STATUS);

	switch(vp->magic)
	{
		case COLUMN_FHIFSTATEINDEX:
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			*var_len = sizeof(node->fhIfStateIndex);
			return (u_char *)&node->fhIfStateIndex;
	/*	case COLUMN_FHIFDESCR:
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			*var_len = strlen(node->fhIfDescr);
			return (u_char *)node->fhIfDescr;*/
		case COLUMN_FHIFMODE:
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			*var_len = sizeof(node->fhIfMode);
			return (u_char *)&node->fhIfMode;
		default:
			BC_PT_DBG_FUN(BC_MODULE_SNMP, "colunm error!!\r\n");
	}
	return NULL;
}
#endif


void snmp_fhIfStateTable_init(void)
{
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);

	SNMP_REGISTER_TABLE(fhIfStateTable);

	SNMP_MIB_FFLUSH_INIT();

	BC_PT_FUN_LEAVE(BC_MODULE_SNMP);
}

