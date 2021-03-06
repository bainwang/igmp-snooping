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

#include "snmp_fhEntityIfPfmTable.h"
#include "snmp_global.h"
#include "snmp_core_ex.h"



///////////////////////////////////////////////////////////////////////////////
//                                                               			 //
//																			 //
//						外 部 变 量、 函 数 引 用					         //
//																			 //
///////////////////////////////////////////////////////////////////////////////
static snmp_find_var_callback   __snmp_fhEntityIfPfmTable_handler;


///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//																			 //
//						结   构   体   宏   定   义							 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
#if 1


#define SNMP_PON_PORT_TBL_STORAGE_QUERY(StorageTmp)	\
									do{ \
										size_t	newlen =  name_len - (fhEntityIfPfmTable_variables_oid_len + 3 - 1);\
										if(!(StorageTmp = header_complex(fhEntityIfPfmTableStorage, NULL, &name[fhEntityIfPfmTable_variables_oid_len + 3 - 1], &newlen, 1, NULL, NULL)))\
										{\
											BC_PT_FUN_TAG(BC_MODULE_SNMP);\
											return SNMP_ERR_NOSUCHNAME; \
										}\
									}while(0)

#define SNMP_NODE_INDEX_GET(idx)	\
	do{	\
		idx = node->fhIfPfmIndex;	\
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
static struct variable2 fhEntityIfPfmTable_variables[] = 
{
	{COLUMN_FHIFPFMINDEX, ASN_INTEGER, NETSNMP_OLDAPI_RONLY, 
		__snmp_fhEntityIfPfmTable_handler, 2, {1, 1}}
};

static oid fhEntityIfPfmTable_variables_oid[] = {1,3,6,1,4,1,11408,11,1,1,1,4};
static const int fhEntityIfPfmTable_variables_oid_len = FHENTITYIFPFMTABLE_OID_LEN;
static struct header_complex_index *fhEntityIfPfmTableStorage = NULL;

static time_t update_time;

//这里定义包含全部索引的全局指针
static int *fhEntityIfPfmTable_idxs = NULL;
//这里定义表最大索引数
#define fhEntityIfPfmTable_num	1

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

static bc_boolean vir_api_get_idxs(int __fhEntityIfPfmTable_idxs[fhEntityIfPfmTable_num], int *fhIfPfmIndex_num)
{
	int i = 0;

	for(; i<fhEntityIfPfmTable_num; i++)
	{
		__fhEntityIfPfmTable_idxs[i] = i+1;
	}
	*fhIfPfmIndex_num = fhEntityIfPfmTable_num;

	return TRUE;
}

static bc_boolean vir_api_get_data(struct fhEntityIfPfmTable_entry data[fhEntityIfPfmTable_num], int *fhIfPfmIndex_num)
{
	int i = 0;

	for(; i<fhEntityIfPfmTable_num; i++)
	{
		data[i].fhIfPfmIndex = i+1;
	}
	*fhIfPfmIndex_num = fhEntityIfPfmTable_num;

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
static bc_int32 __snmp_fhEntityIfPfmTable_add(struct fhEntityIfPfmTable_entry *node)
{
   	netsnmp_variable_list *vars = NULL;
		
	snmp_varlist_add_variable(&vars, NULL, 0, ASN_INTEGER,
		&node->fhIfPfmIndex, sizeof(node->fhIfPfmIndex));

	header_complex_add_data(&fhEntityIfPfmTableStorage, vars, node);

	return SNMPERR_SUCCESS;
}

static struct fhEntityIfPfmTable_entry *__snmp_fhEntityIfPfmTable_create(void)
{
	struct fhEntityIfPfmTable_entry *entry = SNMP_MALLOC_STRUCT(fhEntityIfPfmTable_entry);
	if(!entry)
	{
		return NULL;
	}
	memset(entry, 0, sizeof(struct fhEntityIfPfmTable_entry));
	entry->storageType =  ST_NONVOLATILE;
	
	return entry;
}

#if 1
static void __snmp_free_fhEntityIfPfmTable_data(struct fhEntityIfPfmTable_entry *StorageDel)
{
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	
    netsnmp_assert(StorageDel);
    free(StorageDel);
}
#endif



bc_boolean __snmp_fhEntityIfPfmTable_update_x86(bc_int32 __fhIfPfmIndex)
{
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	
	if (NULL == fhEntityIfPfmTableStorage)
	{
		BC_PT_FUN_TAG(BC_MODULE_SNMP);
		struct fhEntityIfPfmTable_entry *StorageTmp = NULL;
		StorageTmp = __snmp_fhEntityIfPfmTable_create();
		
		StorageTmp->fhIfPfmIndex = 1;
		
		__snmp_fhEntityIfPfmTable_add(StorageTmp);
	}
	
	BC_PT_FUN_LEAVE(BC_MODULE_SNMP);
	return TRUE;
}

bc_boolean __snmp_fhEntityIfPfmTable_index_update(bc_int32 *fhIfPfmIndex_num)
{	
	bc_boolean ret = TRUE;
	
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	
	struct fhEntityIfPfmTable_entry *StorageTmp = NULL;
	struct header_complex_index *fhEntityIfPfmTableTemp = NULL;

	bc_int32 i = 0; 
	
	bc_int32 __fhEntityIfPfmTable_idxs[fhEntityIfPfmTable_num];

	vir_api_get_idxs(__fhEntityIfPfmTable_idxs, fhIfPfmIndex_num);
	
	SNMP_MEM_GET(fhEntityIfPfmTable_idxs, int, fhEntityIfPfmTable_num);
	memcpy(fhEntityIfPfmTable_idxs, __fhEntityIfPfmTable_idxs, sizeof(__fhEntityIfPfmTable_idxs));

	for (i = 0; i < *fhIfPfmIndex_num; i++)
	{
		fhEntityIfPfmTableTemp = fhEntityIfPfmTableStorage;
		StorageTmp = NULL;
		while(fhEntityIfPfmTableTemp)
		{
			StorageTmp = (struct fhEntityIfPfmTable_entry *)fhEntityIfPfmTableTemp->data;
			if (StorageTmp->fhIfPfmIndex == __fhEntityIfPfmTable_idxs[i] )	// modiry
			{
				break;
			}
			fhEntityIfPfmTableTemp = fhEntityIfPfmTableTemp->next;
		}
		
		if (!fhEntityIfPfmTableTemp)
		{
			StorageTmp = __snmp_fhEntityIfPfmTable_create();

			StorageTmp->fhIfPfmIndex = __fhEntityIfPfmTable_idxs[i];	//modiry
			__snmp_fhEntityIfPfmTable_add(StorageTmp);
		}

	}	

	fhEntityIfPfmTableTemp = fhEntityIfPfmTableStorage;
	while (fhEntityIfPfmTableTemp)
	{
		StorageTmp = (struct fhEntityIfPfmTable_entry *)fhEntityIfPfmTableTemp->data;
		for(i = 0; i < *fhIfPfmIndex_num; i++)
		{
			if (StorageTmp->fhIfPfmIndex == __fhEntityIfPfmTable_idxs[i])				
			{
				break;
			}
		}	

		if (i == *fhIfPfmIndex_num)
		{
			struct header_complex_index *hciptrn = fhEntityIfPfmTableTemp->next;
			BC_PT_DBG_FUN(BC_MODULE_SNMP, "FREE!!!!\n");
			struct fhEntityIfPfmTable_entry *StorageDel = header_complex_extract_entry(&fhEntityIfPfmTableStorage, fhEntityIfPfmTableTemp);
			__snmp_free_fhEntityIfPfmTable_data(StorageDel);

			fhEntityIfPfmTableTemp = hciptrn;
		}
		else
		{
			fhEntityIfPfmTableTemp = fhEntityIfPfmTableTemp->next;
		}
	}

	BC_PT_FUN_LEAVE(BC_MODULE_SNMP);
	return ret;
}


bc_boolean __snmp_fhEntityIfPfmTable_update_dev(bc_int32 __fhIfPfmIndex)
{
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);

	struct fhEntityIfPfmTable_entry *StorageTmp = NULL;
	struct header_complex_index *fhEntityIfPfmTableTemp = NULL;

	bc_int32 __fhIfPfmIndex_tmp = 0;
	bc_int32 __update_count = 0;
	
	bc_int32 fhIfPfmIndex_num;
	bc_int32 next_is_chk = TRUE;

	struct fhEntityIfPfmTable_entry data_tmp[fhEntityIfPfmTable_num];
	int data_cnt = 0;

	int i = 0;
	
	BC_PT_FUN_TAG(BC_MODULE_SNMP);

	if(snmp_is_update(&update_time))
	{
		if (!__snmp_fhEntityIfPfmTable_index_update(&fhIfPfmIndex_num))
		{
			BC_PT_DBG_CPL(BC_MODULE_SNMP, "__snmp_fhEntityIfPfmTable_index_update() failed!\r\n");
			return FALSE;
		}

		fhEntityIfPfmTableTemp = fhEntityIfPfmTableStorage;
		while(fhEntityIfPfmTableTemp)
		{
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			StorageTmp = (struct fhEntityIfPfmTable_entry *)fhEntityIfPfmTableTemp->data;

			__fhIfPfmIndex_tmp = StorageTmp->fhIfPfmIndex;

			BC_PT_DBG_FUN(BC_MODULE_SNMP, "next_is_chk=%d\n",next_is_chk);
			
			if((__fhIfPfmIndex_tmp != __fhIfPfmIndex) && (next_is_chk == TRUE))
			{
				fhEntityIfPfmTableTemp = fhEntityIfPfmTableTemp->next;			
			}
			else	
			{
				next_is_chk = FALSE;
				
				vir_api_get_data(data_tmp, &data_cnt);

				for(i=0; i<data_cnt; i++)
				{
					if(data_tmp[i].fhIfPfmIndex == __fhIfPfmIndex_tmp)
					{
						memcpy(StorageTmp, data_tmp+i, sizeof(struct fhEntityIfPfmTable_entry));
						break;
					}
				}
				#if 0
				printf("StorageTmp->fhIfPfmIndex = %d\n", StorageTmp->fhIfPfmIndex);
				#endif
				
				fhEntityIfPfmTableTemp = fhEntityIfPfmTableTemp->next;			

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
	SNMP_MEM_FREE(fhEntityIfPfmTable_idxs);
	return TRUE;
}		




static bc_boolean __snmp_fhEntityIfPfmTable_update(bc_int32 __fhIfPfmIndex)
{
#ifdef SNMP_PRJ_SNMP_X86
		return __snmp_fhEntityIfPfmTable_update_x86(__fhIfPfmIndex);
#else
		return __snmp_fhEntityIfPfmTable_update_dev(__fhIfPfmIndex);
#endif
}


static unsigned char *__snmp_fhEntityIfPfmTable_handler(struct variable *vp,
																		oid *name,
																		size_t *length,
																		int exact,
																		size_t *var_len,
																		WriteMethod **write_method)
{	
	struct fhEntityIfPfmTable_entry *node = NULL;

	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	bc_int32 __fhIfPfmIndex = 0;

	SNMP_NODE_OID_PT(name, *length);
	
	if (*length == FHENTITYIFPFMTABLE_OID_FULL_LEN)
	{
		BC_PT_FUN_TAG(BC_MODULE_SNMP);
		__fhIfPfmIndex = name[*length - 1];
	}
	
	else if (*length < FHENTITYIFPFMTABLE_OID_FULL_LEN)
	{
		BC_PT_DBG_FUN(BC_MODULE_SNMP, "*length=%d\n",*(size_t *)length);
		__fhIfPfmIndex = 1;
	}
	
	if(!__snmp_fhEntityIfPfmTable_update(__fhIfPfmIndex))
	{
		BC_PT_DBG_FUN(BC_MODULE_SNMP, "__snmp_fhEntityIfPfmTable_update() failed!!\r\n");
		return NULL;
	}
	
	SNMP_HDL_HEADER_COMPLEX(fhEntityIfPfmTableStorage, vp, name, length, exact, var_len, write_method, NULL, SNMP_TABLE_NO_ROW_STATUS);

	switch(vp->magic)
	{
		case COLUMN_FHIFPFMINDEX:
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			*var_len = sizeof(node->fhIfPfmIndex);
			return (u_char *)&node->fhIfPfmIndex;
		default:
			BC_PT_DBG_FUN(BC_MODULE_SNMP, "colunm error!!\r\n");
	}
	return NULL;
}
#endif

void snmp_fhEntityIfPfmTable_init(void)
{
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);

	SNMP_REGISTER_TABLE(fhEntityIfPfmTable);

	SNMP_MIB_FFLUSH_INIT();

	BC_PT_FUN_LEAVE(BC_MODULE_SNMP);
}

