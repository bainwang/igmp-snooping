/*******************************************************************************
  [Author]	   : bain.wang@outlook.com.uestc@gmail.com
  [Version]    : 1.0
  [Date]       : 2017-02-25
  [Description]:

  [Others]     :

  [History]:
	 Date          Modification 							    Initials
	----------     ----------                                   -------
	2017-02-25      Created								   		bain.wang@outlook.com
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

#include "snmp_fhEntitySlotInfoTable.h"
#include "snmp_global.h"
#include "snmp_core_ex.h"



///////////////////////////////////////////////////////////////////////////////
//                                                               			 //
//																			 //
//						外 部 变 量、 函 数 引 用					         //
//																			 //
///////////////////////////////////////////////////////////////////////////////
static snmp_find_var_callback   __snmp_fhEntitySlotInfoTable_handler;


///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//																			 //
//						结   构   体   宏   定   义							 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
#if 1


#define SNMP_PON_PORT_TBL_STORAGE_QUERY(StorageTmp)	\
									do{ \
										size_t	newlen =  name_len - (fhEntitySlotInfoTable_variables_oid_len + 3 - 1);\
										if(!(StorageTmp = header_complex(fhEntitySlotInfoTableStorage, NULL, &name[fhEntitySlotInfoTable_variables_oid_len + 3 - 1], &newlen, 1, NULL, NULL)))\
										{\
											BC_PT_FUN_TAG(BC_MODULE_SNMP);\
											return SNMP_ERR_NOSUCHNAME; \
										}\
									}while(0)

#define SNMP_NODE_INDEX_GET(idx)	\
	do{	\
		idx = node->fhSlotEntityIndex;	\
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
static struct variable2 fhEntitySlotInfoTable_variables[] = 
{
	{COLUMN_FHSLOTENTITYINDEX, ASN_INTEGER, NETSNMP_OLDAPI_RONLY, 
		__snmp_fhEntitySlotInfoTable_handler, 2, {1, 1}},
	{COLUMN_FHSLOTSEQ, ASN_INTEGER, NETSNMP_OLDAPI_RONLY, 
		__snmp_fhEntitySlotInfoTable_handler, 2, {1, 2}},
	{COLUMN_FHSLOTTYPE, ASN_OCTET_STR, NETSNMP_OLDAPI_RONLY, 
		__snmp_fhEntitySlotInfoTable_handler, 2, {1, 3}},
	{COLUMN_FHSLOTNAME, ASN_OCTET_STR, NETSNMP_OLDAPI_RONLY, 
		__snmp_fhEntitySlotInfoTable_handler, 2, {1, 4}},
	{COLUMN_FHSLOTOCCUPYSTATUS, ASN_OCTET_STR, NETSNMP_OLDAPI_RONLY, 
		__snmp_fhEntitySlotInfoTable_handler, 2, {1, 5}}
};

static oid fhEntitySlotInfoTable_variables_oid[] = {1,3,6,1,4,1,11408,11,1,1,3};
static const int fhEntitySlotInfoTable_variables_oid_len = FHENTITYSLOTINFOTABLE_OID_LEN;
static struct header_complex_index *fhEntitySlotInfoTableStorage = NULL;

static time_t update_time;

//这里定义包含全部索引的全局指针
static int *fhEntitySlotInfoTable_idxs = NULL;
//这里定义表最大索引数
#define fhEntitySlotInfoTable_num		3

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

static bc_boolean vir_api_get_idxs(int __fhEntitySlotInfoTable_idxs[fhEntitySlotInfoTable_num], int *fhSlotEntityIndex_num)
{
	int i = 0;

	for(; i<fhEntitySlotInfoTable_num; i++)
	{
		__fhEntitySlotInfoTable_idxs[i] = i+1;
	}
	*fhSlotEntityIndex_num = fhEntitySlotInfoTable_num;

	return TRUE;
}

static bc_boolean vir_api_get_data(struct fhEntitySlotInfoTable_entry data[fhEntitySlotInfoTable_num], int *fhSlotEntityIndex_num)
{
	int i = 0;

	for(; i<fhEntitySlotInfoTable_num; i++)
	{
		data[i].fhSlotEntityIndex = i+1;
		data[i].fhSlotSeq = i+5;
		strcpy(data[i].fhSlotType, "fhSlotType");
		strcpy(data[i].fhSlotName, "fhSlotName");
		strcpy(data[i].fhSlotOccupyStatus, "fhSlotOccupyStatus");
	}
	*fhSlotEntityIndex_num = fhEntitySlotInfoTable_num;

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
static bc_int32 __snmp_fhEntitySlotInfoTable_add(struct fhEntitySlotInfoTable_entry *node)
{
   	netsnmp_variable_list *vars = NULL;
		
	snmp_varlist_add_variable(&vars, NULL, 0, ASN_INTEGER,
		&node->fhSlotEntityIndex, sizeof(node->fhSlotEntityIndex));

	header_complex_add_data(&fhEntitySlotInfoTableStorage, vars, node);

	return SNMPERR_SUCCESS;
}

static struct fhEntitySlotInfoTable_entry *__snmp_fhEntitySlotInfoTable_create(void)
{
	struct fhEntitySlotInfoTable_entry *entry = SNMP_MALLOC_STRUCT(fhEntitySlotInfoTable_entry);
	if(!entry)
	{
		return NULL;
	}
	memset(entry, 0, sizeof(struct fhEntitySlotInfoTable_entry));
	entry->storageType =  ST_NONVOLATILE;
	
	return entry;
}

#if 1
static void __snmp_free_fhEntitySlotInfoTable_data(struct fhEntitySlotInfoTable_entry *StorageDel)
{
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	
    netsnmp_assert(StorageDel);
    free(StorageDel);
}
#endif



bc_boolean __snmp_fhEntitySlotInfoTable_update_x86(bc_int32 __fhSlotEntityIndex)
{
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	
	if (NULL == fhEntitySlotInfoTableStorage)
	{
		BC_PT_FUN_TAG(BC_MODULE_SNMP);
		struct fhEntitySlotInfoTable_entry *StorageTmp = NULL;
		StorageTmp = __snmp_fhEntitySlotInfoTable_create();
		
		StorageTmp->fhSlotEntityIndex = 1;
		
		__snmp_fhEntitySlotInfoTable_add(StorageTmp);
	}
	
	BC_PT_FUN_LEAVE(BC_MODULE_SNMP);
	return TRUE;
}

bc_boolean __snmp_fhEntitySlotInfoTable_index_update(bc_int32 *fhSlotEntityIndex_num)
{	
	bc_boolean ret = TRUE;
	
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	struct fhEntitySlotInfoTable_entry *StorageTmp = NULL;
	struct header_complex_index *fhEntitySlotInfoTableTemp = NULL;

	bc_int32 i = 0; 
	
	bc_int32 __fhEntitySlotInfoTable_idxs[fhEntitySlotInfoTable_num];

	vir_api_get_idxs(__fhEntitySlotInfoTable_idxs, fhSlotEntityIndex_num);
	
	SNMP_MEM_GET(fhEntitySlotInfoTable_idxs, int, fhEntitySlotInfoTable_num);
	memcpy(fhEntitySlotInfoTable_idxs, __fhEntitySlotInfoTable_idxs, sizeof(__fhEntitySlotInfoTable_idxs));

	for (i = 0; i < *fhSlotEntityIndex_num; i++)
	{
		fhEntitySlotInfoTableTemp = fhEntitySlotInfoTableStorage;
		StorageTmp = NULL;
		while(fhEntitySlotInfoTableTemp)
		{
			StorageTmp = (struct fhEntitySlotInfoTable_entry *)fhEntitySlotInfoTableTemp->data;
			if (StorageTmp->fhSlotEntityIndex == __fhEntitySlotInfoTable_idxs[i] )
			{
				break;
			}
			fhEntitySlotInfoTableTemp = fhEntitySlotInfoTableTemp->next;
		}
		
		if (!fhEntitySlotInfoTableTemp)
		{
			StorageTmp = __snmp_fhEntitySlotInfoTable_create();

			StorageTmp->fhSlotEntityIndex = __fhEntitySlotInfoTable_idxs[i];
			__snmp_fhEntitySlotInfoTable_add(StorageTmp);
		}

	}	

	fhEntitySlotInfoTableTemp = fhEntitySlotInfoTableStorage;
	while (fhEntitySlotInfoTableTemp)
	{
		StorageTmp = (struct fhEntitySlotInfoTable_entry *)fhEntitySlotInfoTableTemp->data;
		for(i = 0; i < *fhSlotEntityIndex_num; i++)
		{
			if (StorageTmp->fhSlotEntityIndex == __fhEntitySlotInfoTable_idxs[i])				
			{
				break;
			}
		}	

		if (i == *fhSlotEntityIndex_num)
		{
			struct header_complex_index *hciptrn = fhEntitySlotInfoTableTemp->next;
			BC_PT_DBG_FUN(BC_MODULE_SNMP, "FREE!!!!\n");
			struct fhEntitySlotInfoTable_entry *StorageDel = header_complex_extract_entry(&fhEntitySlotInfoTableStorage, fhEntitySlotInfoTableTemp);
			__snmp_free_fhEntitySlotInfoTable_data(StorageDel);

			fhEntitySlotInfoTableTemp = hciptrn;
		}
		else
		{
			fhEntitySlotInfoTableTemp = fhEntitySlotInfoTableTemp->next;
		}
	}

	BC_PT_FUN_LEAVE(BC_MODULE_SNMP);
	return ret;
}


bc_boolean __snmp_fhEntitySlotInfoTable_update_dev(bc_int32 __fhSlotEntityIndex)
{
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
//	bc_boolean ret = TRUE;
//	bc_int32 api_ret;
	struct fhEntitySlotInfoTable_entry *StorageTmp = NULL;
	struct header_complex_index *fhEntitySlotInfoTableTemp = NULL;

	bc_int32 __fhSlotEntityIndex_tmp = 0;
	bc_int32 __update_count = 0;
	
	bc_int32 fhSlotEntityIndex_num;
//	bc_int32 count = 0;
	bc_int32 next_is_chk = TRUE;

	struct fhEntitySlotInfoTable_entry data_tmp[fhEntitySlotInfoTable_num];
	int data_cnt = 0;

	int i = 0;
	
	BC_PT_FUN_TAG(BC_MODULE_SNMP);

	if(snmp_is_update(&update_time))
	{
		if (!__snmp_fhEntitySlotInfoTable_index_update(&fhSlotEntityIndex_num))
		{
			BC_PT_DBG_CPL(BC_MODULE_SNMP, "__snmp_fhEntitySlotInfoTable_index_update() failed!\r\n");
			return FALSE;
		}

		fhEntitySlotInfoTableTemp = fhEntitySlotInfoTableStorage;
		while(fhEntitySlotInfoTableTemp)
		{
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			StorageTmp = (struct fhEntitySlotInfoTable_entry *)fhEntitySlotInfoTableTemp->data;

			__fhSlotEntityIndex_tmp = StorageTmp->fhSlotEntityIndex;

			BC_PT_DBG_FUN(BC_MODULE_SNMP, "next_is_chk=%d\n",next_is_chk);
			
			if((__fhSlotEntityIndex_tmp != __fhSlotEntityIndex) && (next_is_chk == TRUE))
			{
				fhEntitySlotInfoTableTemp = fhEntitySlotInfoTableTemp->next;			
			}
			else	
			{
				next_is_chk = FALSE;
				
				vir_api_get_data(data_tmp, &data_cnt);

				for(i=0; i<data_cnt; i++)
				{
					if(data_tmp[i].fhSlotEntityIndex == __fhSlotEntityIndex_tmp)
					{
						memcpy(StorageTmp, data_tmp+i, sizeof(struct fhEntitySlotInfoTable_entry));
						break;
					}
				}
				#if 0
				printf("StorageTmp->fhSlotEntityIndex = %d\n", StorageTmp->fhSlotEntityIndex);
				printf("StorageTmp->fhSlotSeq = %d\n", StorageTmp->fhSlotSeq);
				printf("StorageTmp->fhSlotType = %s\n", StorageTmp->fhSlotType);
				printf("StorageTmp->fhSlotType = %s\n", StorageTmp->fhSlotType);
				printf("StorageTmp->fhSlotType = %s\n", StorageTmp->fhSlotType);
				#endif
				
				fhEntitySlotInfoTableTemp = fhEntitySlotInfoTableTemp->next;			

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
	SNMP_MEM_FREE(fhEntitySlotInfoTable_idxs);
	return TRUE;
}		




static bc_boolean __snmp_fhEntitySlotInfoTable_update(bc_int32 __fhSlotEntityIndex)
{
#ifdef SNMP_PRJ_SNMP_X86
		return __snmp_fhEntitySlotInfoTable_update_x86(__fhSlotEntityIndex);
#else
		return __snmp_fhEntitySlotInfoTable_update_dev(__fhSlotEntityIndex);
#endif
}


static unsigned char *__snmp_fhEntitySlotInfoTable_handler(struct variable *vp,
																		oid *name,
																		size_t *length,
																		int exact,
																		size_t *var_len,
																		WriteMethod **write_method)
{	
	struct fhEntitySlotInfoTable_entry *node = NULL;

	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	bc_int32 __fhSlotEntityIndex = 0;

	SNMP_NODE_OID_PT(name, *length);
	
	if (*length == FHENTITYSLOTINFOTABLE_OID_FULL_LEN)
	{
		BC_PT_FUN_TAG(BC_MODULE_SNMP);
		__fhSlotEntityIndex = name[*length - 1];
	}
	
	else if (*length < FHENTITYSLOTINFOTABLE_OID_FULL_LEN)
	{
		BC_PT_DBG_FUN(BC_MODULE_SNMP, "*length=%d\n",*(size_t *)length);
		__fhSlotEntityIndex = 1;
	}
	
	if(!__snmp_fhEntitySlotInfoTable_update(__fhSlotEntityIndex))
	{
		BC_PT_DBG_FUN(BC_MODULE_SNMP, "__snmp_fhEntitySlotInfoTable_update() failed!!\r\n");
		return NULL;
	}
	
	SNMP_HDL_HEADER_COMPLEX(fhEntitySlotInfoTableStorage, vp, name, length, exact, var_len, write_method, NULL, SNMP_TABLE_NO_ROW_STATUS);

	switch(vp->magic)
	{
		case COLUMN_FHSLOTENTITYINDEX:
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			*var_len = sizeof(node->fhSlotEntityIndex);
			return (u_char *)&node->fhSlotEntityIndex;
		case COLUMN_FHSLOTSEQ:
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			*var_len = sizeof(node->fhSlotSeq);
			return (u_char *)&node->fhSlotSeq;
		case COLUMN_FHSLOTTYPE:
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			*var_len = strlen(node->fhSlotType);
			return (u_char *)&node->fhSlotType;
		case COLUMN_FHSLOTNAME:
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			*var_len = strlen(node->fhSlotName);
			return (u_char *)&node->fhSlotName;
		case COLUMN_FHSLOTOCCUPYSTATUS:
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			*var_len = strlen(node->fhSlotOccupyStatus);
			return (u_char *)node->fhSlotOccupyStatus;
		default:
			BC_PT_DBG_FUN(BC_MODULE_SNMP, "colunm error!!\r\n");
	}
	return NULL;
}
#endif

void snmp_fhEntitySlotInfoTable_init(void)
{
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);

	SNMP_REGISTER_TABLE(fhEntitySlotInfoTable);

	SNMP_MIB_FFLUSH_INIT();

	BC_PT_FUN_LEAVE(BC_MODULE_SNMP);
}

