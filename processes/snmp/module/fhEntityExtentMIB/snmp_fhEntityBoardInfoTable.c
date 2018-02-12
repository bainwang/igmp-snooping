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

#include "snmp_fhEntityBoardInfoTable.h"
#include "snmp_global.h"
#include "snmp_core_ex.h"



///////////////////////////////////////////////////////////////////////////////
//                                                               			 //
//																			 //
//						外 部 变 量、 函 数 引 用					         //
//																			 //
///////////////////////////////////////////////////////////////////////////////
static snmp_find_var_callback   __snmp_fhEntityBoardInfoTable_handler;


///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//																			 //
//						结   构   体   宏   定   义							 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
#if 1


#define SNMP_PON_PORT_TBL_STORAGE_QUERY(StorageTmp)	\
									do{ \
										size_t	newlen =  name_len - (fhEntityBoardInfoTable_variables_oid_len + 3 - 1);\
										if(!(StorageTmp = header_complex(fhEntityBoardInfoTableStorage, NULL, &name[fhEntityBoardInfoTable_variables_oid_len + 3 - 1], &newlen, 1, NULL, NULL)))\
										{\
											BC_PT_FUN_TAG(BC_MODULE_SNMP);\
											return SNMP_ERR_NOSUCHNAME; \
										}\
									}while(0)

#define SNMP_NODE_INDEX_GET(idx)	\
	do{	\
		idx = node->fhBoardEntityIndex;	\
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
static struct variable2 fhEntityBoardInfoTable_variables[] = 
{
	{COLUMN_FHBOARDENTITYINDEX, ASN_INTEGER, NETSNMP_OLDAPI_RONLY, 
		__snmp_fhEntityBoardInfoTable_handler, 2, {1, 1}},
	{COLUMN_FHBOARDENTITYNO, ASN_INTEGER, NETSNMP_OLDAPI_RONLY, 
		__snmp_fhEntityBoardInfoTable_handler, 2, {1, 2}},
	{COLUMN_FHBOARDHARDWAREREV, ASN_OCTET_STR, NETSNMP_OLDAPI_RONLY, 
		__snmp_fhEntityBoardInfoTable_handler, 2, {1, 8}},
	{COLUMN_FHBOARDSLOTSEQ, ASN_INTEGER, NETSNMP_OLDAPI_RONLY, 
		__snmp_fhEntityBoardInfoTable_handler, 2, {1, 9}},
	{COLUMN_FHBOARDSLOTNUM, ASN_INTEGER, NETSNMP_OLDAPI_RONLY, 
		__snmp_fhEntityBoardInfoTable_handler, 2, {1, 10}},
	{COLUMN_FHBOARDOPERSTATUS, ASN_OCTET_STR, NETSNMP_OLDAPI_RONLY, 
		__snmp_fhEntityBoardInfoTable_handler, 2, {1, 11}},
	{COLUMN_FHHARDWARETYPE, ASN_OCTET_STR, NETSNMP_OLDAPI_RONLY, 
		__snmp_fhEntityBoardInfoTable_handler, 2, {1, 19}},
	{COLUMN_FHBOARDIDLESTATUS, ASN_INTEGER, NETSNMP_OLDAPI_RONLY, 
		__snmp_fhEntityBoardInfoTable_handler, 2, {1, 22}}
};

static oid fhEntityBoardInfoTable_variables_oid[] = {1,3,6,1,4,1,11408,11,1,1,4};
static const int fhEntityBoardInfoTable_variables_oid_len = FHENTITYBOARDINFOTABLE_OID_LEN;
static struct header_complex_index *fhEntityBoardInfoTableStorage = NULL;

static time_t update_time;

//这里定义包含全部索引的全局指针
static int *fhEntityBoardInfoTable_idxs = NULL;
//这里定义表最大索引数
#define fhEntityBoardInfoTable_num	4

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

static bc_boolean vir_api_get_idxs(int __fhEntityBoardInfoTable_idxs[fhEntityBoardInfoTable_num], int *fhBoardEntityIndex_num)
{
	int i = 0;

	for(; i<fhEntityBoardInfoTable_num; i++)
	{
		__fhEntityBoardInfoTable_idxs[i] = i+1;
	}
	*fhBoardEntityIndex_num = fhEntityBoardInfoTable_num;

	return TRUE;
}

static bc_boolean vir_api_get_data(struct fhEntityBoardInfoTable_entry data[fhEntityBoardInfoTable_num], int *fhBoardEntityIndex_num)
{
	int i = 0;

	for(; i<fhEntityBoardInfoTable_num; i++)
	{
		data[i].fhBoardEntityIndex = i+1;
		data[i].fhBoardEntityNo = i+1;
		strcpy(data[i].fhBoardHardwareRev, "fhBoardHardwareRev");
    		data[i].fhBoardSlotSeq = i+30;
    		data[i].fhBoardSlotNum = i+40;
		strcpy(data[i].fhBoardOperStatus, "fhBoardOperStatus");
		strcpy(data[i].fhHardwareType, "fhHardwareType");
		data[i].fhBoardIdleStatus = 1;
	}
	*fhBoardEntityIndex_num = fhEntityBoardInfoTable_num;

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
static bc_int32 __snmp_fhEntityBoardInfoTable_add(struct fhEntityBoardInfoTable_entry *node)
{
   	netsnmp_variable_list *vars = NULL;
		
	snmp_varlist_add_variable(&vars, NULL, 0, ASN_INTEGER,
		&node->fhBoardEntityIndex, sizeof(node->fhBoardEntityIndex));

	header_complex_add_data(&fhEntityBoardInfoTableStorage, vars, node);

	return SNMPERR_SUCCESS;
}

static struct fhEntityBoardInfoTable_entry *__snmp_fhEntityBoardInfoTable_create(void)
{
	struct fhEntityBoardInfoTable_entry *entry = SNMP_MALLOC_STRUCT(fhEntityBoardInfoTable_entry);
	if(!entry)
	{
		return NULL;
	}
	memset(entry, 0, sizeof(struct fhEntityBoardInfoTable_entry));
	entry->storageType =  ST_NONVOLATILE;
	
	return entry;
}

#if 1
static void __snmp_free_fhEntityBoardInfoTable_data(struct fhEntityBoardInfoTable_entry *StorageDel)
{
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	
    netsnmp_assert(StorageDel);
    free(StorageDel);
}
#endif



bc_boolean __snmp_fhEntityBoardInfoTable_update_x86(bc_int32 __fhBoardEntityIndex)
{
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	
	if (NULL == fhEntityBoardInfoTableStorage)
	{
		BC_PT_FUN_TAG(BC_MODULE_SNMP);
		struct fhEntityBoardInfoTable_entry *StorageTmp = NULL;
		StorageTmp = __snmp_fhEntityBoardInfoTable_create();
		
		StorageTmp->fhBoardEntityIndex = 1;
		
		__snmp_fhEntityBoardInfoTable_add(StorageTmp);
	}
	
	BC_PT_FUN_LEAVE(BC_MODULE_SNMP);
	return TRUE;
}

bc_boolean __snmp_fhEntityBoardInfoTable_index_update(bc_int32 *fhBoardEntityIndex_num)
{	
	bc_boolean ret = TRUE;
	
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	struct fhEntityBoardInfoTable_entry *StorageTmp = NULL;
	struct header_complex_index *fhEntityBoardInfoTableTemp = NULL;

	bc_int32 i = 0; 
	bc_int32 __fhEntityBoardInfoTable_idxs[fhEntityBoardInfoTable_num];

	vir_api_get_idxs(__fhEntityBoardInfoTable_idxs, fhBoardEntityIndex_num);
	
	SNMP_MEM_GET(fhEntityBoardInfoTable_idxs, int, fhEntityBoardInfoTable_num);
	memcpy(fhEntityBoardInfoTable_idxs, __fhEntityBoardInfoTable_idxs, sizeof(__fhEntityBoardInfoTable_idxs));

	/*4. 增加新索引项*/
	for (i = 0; i < *fhBoardEntityIndex_num; i++)
	{
		fhEntityBoardInfoTableTemp = fhEntityBoardInfoTableStorage;
		StorageTmp = NULL;
		while(fhEntityBoardInfoTableTemp)
		{
			StorageTmp = (struct fhEntityBoardInfoTable_entry *)fhEntityBoardInfoTableTemp->data;
			if (StorageTmp->fhBoardEntityIndex == __fhEntityBoardInfoTable_idxs[i] )	// modiry
			{
				break;
			}
			fhEntityBoardInfoTableTemp = fhEntityBoardInfoTableTemp->next;
		}
		
		if (!fhEntityBoardInfoTableTemp)
		{
			StorageTmp = __snmp_fhEntityBoardInfoTable_create();

			StorageTmp->fhBoardEntityIndex = __fhEntityBoardInfoTable_idxs[i];	//modiry
			__snmp_fhEntityBoardInfoTable_add(StorageTmp);
		}

	}	

	fhEntityBoardInfoTableTemp = fhEntityBoardInfoTableStorage;
	while (fhEntityBoardInfoTableTemp)
	{
		StorageTmp = (struct fhEntityBoardInfoTable_entry *)fhEntityBoardInfoTableTemp->data;
		for(i = 0; i < *fhBoardEntityIndex_num; i++)
		{
			if (StorageTmp->fhBoardEntityIndex == __fhEntityBoardInfoTable_idxs[i])				
			{
				break;
			}
		}	

		if (i == *fhBoardEntityIndex_num)
		{
			struct header_complex_index *hciptrn = fhEntityBoardInfoTableTemp->next;
			BC_PT_DBG_FUN(BC_MODULE_SNMP, "FREE!!!!\n");
			struct fhEntityBoardInfoTable_entry *StorageDel = header_complex_extract_entry(&fhEntityBoardInfoTableStorage, fhEntityBoardInfoTableTemp);
			__snmp_free_fhEntityBoardInfoTable_data(StorageDel);

			fhEntityBoardInfoTableTemp = hciptrn;
		}
		else
		{
			fhEntityBoardInfoTableTemp = fhEntityBoardInfoTableTemp->next;
		}
	}

	BC_PT_FUN_LEAVE(BC_MODULE_SNMP);
	return ret;
}


bc_boolean __snmp_fhEntityBoardInfoTable_update_dev(bc_int32 __fhBoardEntityIndex)
{
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);

	struct fhEntityBoardInfoTable_entry *StorageTmp = NULL;
	struct header_complex_index *fhEntityBoardInfoTableTemp = NULL;

	bc_int32 __fhBoardEntityIndex_tmp = 0;
	bc_int32 __update_count = 0;
	
	bc_int32 fhBoardEntityIndex_num;
	bc_int32 next_is_chk = TRUE;

	struct fhEntityBoardInfoTable_entry data_tmp[fhEntityBoardInfoTable_num];
	int data_cnt = 0;

	int i = 0;
	
	BC_PT_FUN_TAG(BC_MODULE_SNMP);

	if(snmp_is_update(&update_time))
	{
		if (!__snmp_fhEntityBoardInfoTable_index_update(&fhBoardEntityIndex_num))
		{
			BC_PT_DBG_CPL(BC_MODULE_SNMP, "__snmp_fhEntityBoardInfoTable_index_update() failed!\r\n");
			return FALSE;
		}

		fhEntityBoardInfoTableTemp = fhEntityBoardInfoTableStorage;
		while(fhEntityBoardInfoTableTemp)
		{
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			StorageTmp = (struct fhEntityBoardInfoTable_entry *)fhEntityBoardInfoTableTemp->data;

			__fhBoardEntityIndex_tmp = StorageTmp->fhBoardEntityIndex;

			BC_PT_DBG_FUN(BC_MODULE_SNMP, "next_is_chk=%d\n",next_is_chk);
			
			if((__fhBoardEntityIndex_tmp != __fhBoardEntityIndex) && (next_is_chk == TRUE))
			{
				fhEntityBoardInfoTableTemp = fhEntityBoardInfoTableTemp->next;			
			}
			else	
			{
				next_is_chk = FALSE;
				
				vir_api_get_data(data_tmp, &data_cnt);

				for(i=0; i<data_cnt; i++)
				{
					if(data_tmp[i].fhBoardEntityIndex == __fhBoardEntityIndex_tmp)
					{
						memcpy(StorageTmp, data_tmp+i, sizeof(struct fhEntityBoardInfoTable_entry));
						break;
					}
				}
				#if 0
				printf("StorageTmp->fhBoardEntityIndex = %d\n", StorageTmp->fhBoardEntityIndex);
				printf("StorageTmp->fhBoardEntityNo = %d\n", StorageTmp->fhBoardEntityNo);
				printf("StorageTmp->fhBoardHardwareRev = %s\n", StorageTmp->fhBoardHardwareRev);
				printf("StorageTmp->fhBoardSlotSeq = %d\n", StorageTmp->fhBoardSlotSeq);
				printf("StorageTmp->fhBoardSlotNum = %d\n", StorageTmp->fhBoardSlotNum);
				printf("StorageTmp->fhBoardOperStatus = %s\n", StorageTmp->fhBoardOperStatus);
				printf("StorageTmp->fhHardwareType = %s\n", StorageTmp->fhHardwareType);
				printf("StorageTmp->fhBoardIdleStatus = %d\n", StorageTmp->fhBoardIdleStatus);
				#endif
				
				fhEntityBoardInfoTableTemp = fhEntityBoardInfoTableTemp->next;			

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
	SNMP_MEM_FREE(fhEntityBoardInfoTable_idxs);
	return TRUE;
}		




static bc_boolean __snmp_fhEntityBoardInfoTable_update(bc_int32 __fhBoardEntityIndex)
{
#ifdef SNMP_PRJ_SNMP_X86
		return __snmp_fhEntityBoardInfoTable_update_x86(__fhBoardEntityIndex);
#else
		return __snmp_fhEntityBoardInfoTable_update_dev(__fhBoardEntityIndex);
#endif
}


static unsigned char *__snmp_fhEntityBoardInfoTable_handler(struct variable *vp,
																		oid *name,
																		size_t *length,
																		int exact,
																		size_t *var_len,
																		WriteMethod **write_method)
{	
	struct fhEntityBoardInfoTable_entry *node = NULL;

	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	bc_int32 __fhBoardEntityIndex = 0;

	SNMP_NODE_OID_PT(name, *length);
	
	if (*length == FHENTITYBOARDINFOTABLE_OID_FULL_LEN)
	{
		BC_PT_FUN_TAG(BC_MODULE_SNMP);
		__fhBoardEntityIndex = name[*length - 1];
	}
	
	else if (*length < FHENTITYBOARDINFOTABLE_OID_FULL_LEN)
	{
		BC_PT_DBG_FUN(BC_MODULE_SNMP, "*length=%d\n",*(size_t *)length);
		__fhBoardEntityIndex = 1;
	}
	
	if(!__snmp_fhEntityBoardInfoTable_update(__fhBoardEntityIndex))
	{
		BC_PT_DBG_FUN(BC_MODULE_SNMP, "__snmp_fhEntityBoardInfoTable_update() failed!!\r\n");
		return NULL;
	}
	
	SNMP_HDL_HEADER_COMPLEX(fhEntityBoardInfoTableStorage, vp, name, length, exact, var_len, write_method, NULL, SNMP_TABLE_NO_ROW_STATUS);

	switch(vp->magic)
	{
		case COLUMN_FHBOARDENTITYINDEX:
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			*var_len = sizeof(node->fhBoardEntityIndex);
			return (u_char *)&node->fhBoardEntityIndex;
		case COLUMN_FHBOARDENTITYNO:
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			*var_len = sizeof(node->fhBoardEntityNo);
			return (u_char *)&node->fhBoardEntityNo;
		case COLUMN_FHBOARDHARDWAREREV:
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			*var_len = strlen(node->fhBoardHardwareRev);
			return (u_char *)node->fhBoardHardwareRev;
		case COLUMN_FHBOARDSLOTSEQ:
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			*var_len = sizeof(node->fhBoardSlotSeq);
			return (u_char *)&node->fhBoardSlotSeq;
		case COLUMN_FHBOARDSLOTNUM:
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			*var_len = sizeof(node->fhBoardSlotNum);
			return (u_char *)&node->fhBoardSlotNum;
		case COLUMN_FHBOARDOPERSTATUS:
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			*var_len = strlen(node->fhBoardOperStatus);
			return (u_char *)node->fhBoardOperStatus;
		case COLUMN_FHHARDWARETYPE:
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			*var_len = strlen(node->fhHardwareType);
			return (u_char *)node->fhHardwareType;
		case COLUMN_FHBOARDIDLESTATUS:
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			*var_len = sizeof(node->fhBoardIdleStatus);
			return (u_char *)&node->fhBoardIdleStatus;
		default:
			BC_PT_DBG_FUN(BC_MODULE_SNMP, "colunm error!!\r\n");
	}
	return NULL;
}
#endif

void snmp_fhEntityBoardInfoTable_init(void)
{
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);

	SNMP_REGISTER_TABLE(fhEntityBoardInfoTable);

	SNMP_MIB_FFLUSH_INIT();

	BC_PT_FUN_LEAVE(BC_MODULE_SNMP);
}

