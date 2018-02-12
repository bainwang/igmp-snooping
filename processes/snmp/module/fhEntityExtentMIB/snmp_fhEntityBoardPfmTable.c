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

#include "snmp_fhEntityBoardPfmTable.h"
#include "snmp_global.h"
#include "snmp_core_ex.h"



///////////////////////////////////////////////////////////////////////////////
//                                                               			 //
//																			 //
//						外 部 变 量、 函 数 引 用					         //
//																			 //
///////////////////////////////////////////////////////////////////////////////
static snmp_find_var_callback   __snmp_fhEntityBoardPfmTable_handler;


///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//																			 //
//						结   构   体   宏   定   义							 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
#if 1	
		

#define SNMP_PON_PORT_TBL_STORAGE_QUERY(StorageTmp)	\
									do{ \
										size_t	newlen =  name_len - (fhEntityBoardPfmTable_variables_oid_len + 3 - 1);\
										if(!(StorageTmp = header_complex(fhEntityBoardPfmTableStorage, NULL, &name[fhEntityBoardPfmTable_variables_oid_len + 3 - 1], &newlen, 1, NULL, NULL)))\
										{\
											BC_PT_FUN_TAG(BC_MODULE_SNMP);\
											return SNMP_ERR_NOSUCHNAME; \
										}\
									}while(0)

#define SNMP_NODE_INDEX_GET(idx)	\
	do{	\
		idx = node->fhBoardPfmIndex;	\
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
static struct variable2 fhEntityBoardPfmTable_variables[] = 
{
	{COLUMN_FHBOARDPFMINDEX, ASN_INTEGER, NETSNMP_OLDAPI_RONLY, 
		__snmp_fhEntityBoardPfmTable_handler, 2, {1, 1}},
	{COLUMN_FHBOARDTEMPERATURE, ASN_OCTET_STR, NETSNMP_OLDAPI_RONLY, 
		__snmp_fhEntityBoardPfmTable_handler, 2, {1, 3}},
	{COLUMN_FHBOARDVOLTAGE, ASN_OCTET_STR, NETSNMP_OLDAPI_RONLY, 
		__snmp_fhEntityBoardPfmTable_handler, 2, {1, 4}}
};

static oid fhEntityBoardPfmTable_variables_oid[] = {1,3,6,1,4,1,11408,11,1,1,1,3};
static const int fhEntityBoardPfmTable_variables_oid_len = FHENTITYBOARDPFMTABLE_OID_LEN;
static struct header_complex_index *fhEntityBoardPfmTableStorage = NULL;

static time_t update_time;

//这里定义包含全部索引的全局指针
static int *fhEntityBoardPfmTable_idxs = NULL;
//这里定义表最大索引数
#define fhEntityBoardPfmTable_num	1

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

static bc_boolean vir_api_get_idxs(int __fhEntityBoardPfmTable_idxs[fhEntityBoardPfmTable_num], int *fhBoardPfmIndex_num)
{
	int i = 0;

	for(; i<fhEntityBoardPfmTable_num; i++)
	{
		__fhEntityBoardPfmTable_idxs[i] = i+1;
	}
	*fhBoardPfmIndex_num = fhEntityBoardPfmTable_num;

	return TRUE;
}

static bc_boolean vir_api_get_data(struct fhEntityBoardPfmTable_entry data[fhEntityBoardPfmTable_num], int *fhBoardPfmIndex_num)
{
	int i = 0;

	for(; i<fhEntityBoardPfmTable_num; i++)
	{
		data[i].fhBoardPfmIndex = i+1;
		strcpy(data[i].fhBoardTemperature, "30 'C");
		strcpy(data[i].fhBoardVoltage, "27 V");
	}
	*fhBoardPfmIndex_num = fhEntityBoardPfmTable_num;

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
static bc_int32 __snmp_fhEntityBoardPfmTable_add(struct fhEntityBoardPfmTable_entry *node)
{
   	netsnmp_variable_list *vars = NULL;
		
	snmp_varlist_add_variable(&vars, NULL, 0, ASN_INTEGER,
		&node->fhBoardPfmIndex, sizeof(node->fhBoardPfmIndex));

	header_complex_add_data(&fhEntityBoardPfmTableStorage, vars, node);

	return SNMPERR_SUCCESS;
}

static struct fhEntityBoardPfmTable_entry *__snmp_fhEntityBoardPfmTable_create(void)
{
	struct fhEntityBoardPfmTable_entry *entry = SNMP_MALLOC_STRUCT(fhEntityBoardPfmTable_entry);
	if(!entry)
	{
		return NULL;
	}
	memset(entry, 0, sizeof(struct fhEntityBoardPfmTable_entry));
	entry->storageType =  ST_NONVOLATILE;
	
	return entry;
}

#if 1
static void __snmp_free_fhEntityBoardPfmTable_data(struct fhEntityBoardPfmTable_entry *StorageDel)
{
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	
    netsnmp_assert(StorageDel);
    free(StorageDel);
}
#endif



bc_boolean __snmp_fhEntityBoardPfmTable_update_x86(bc_int32 __fhBoardPfmIndex)
{
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	
	if (NULL == fhEntityBoardPfmTableStorage)
	{
		BC_PT_FUN_TAG(BC_MODULE_SNMP);
		struct fhEntityBoardPfmTable_entry *StorageTmp = NULL;
		StorageTmp = __snmp_fhEntityBoardPfmTable_create();
		
		StorageTmp->fhBoardPfmIndex = 1;
		
		__snmp_fhEntityBoardPfmTable_add(StorageTmp);
	}
	
	BC_PT_FUN_LEAVE(BC_MODULE_SNMP);
	return TRUE;
}

bc_boolean __snmp_fhEntityBoardPfmTable_index_update(bc_int32 *fhBoardPfmIndex_num)
{	
	bc_boolean ret = TRUE;
	
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	
	struct fhEntityBoardPfmTable_entry *StorageTmp = NULL;
	struct header_complex_index *fhEntityBoardPfmTableTemp = NULL;

	bc_int32 i = 0; 
	
	bc_int32 __fhEntityBoardPfmTable_idxs[fhEntityBoardPfmTable_num];

	vir_api_get_idxs(__fhEntityBoardPfmTable_idxs, fhBoardPfmIndex_num);
	
	SNMP_MEM_GET(fhEntityBoardPfmTable_idxs, int, fhEntityBoardPfmTable_num);
	memcpy(fhEntityBoardPfmTable_idxs, __fhEntityBoardPfmTable_idxs, sizeof(__fhEntityBoardPfmTable_idxs));

	for (i = 0; i < *fhBoardPfmIndex_num; i++)
	{
		fhEntityBoardPfmTableTemp = fhEntityBoardPfmTableStorage;
		StorageTmp = NULL;
		while(fhEntityBoardPfmTableTemp)
		{
			StorageTmp = (struct fhEntityBoardPfmTable_entry *)fhEntityBoardPfmTableTemp->data;
			if (StorageTmp->fhBoardPfmIndex == __fhEntityBoardPfmTable_idxs[i] )
			{
				break;
			}
			fhEntityBoardPfmTableTemp = fhEntityBoardPfmTableTemp->next;
		}
		
		if (!fhEntityBoardPfmTableTemp)
		{
			StorageTmp = __snmp_fhEntityBoardPfmTable_create();

			StorageTmp->fhBoardPfmIndex = __fhEntityBoardPfmTable_idxs[i];
			__snmp_fhEntityBoardPfmTable_add(StorageTmp);
		}

	}	

	fhEntityBoardPfmTableTemp = fhEntityBoardPfmTableStorage;
	while (fhEntityBoardPfmTableTemp)
	{
		StorageTmp = (struct fhEntityBoardPfmTable_entry *)fhEntityBoardPfmTableTemp->data;
		for(i = 0; i < *fhBoardPfmIndex_num; i++)
		{
			if (StorageTmp->fhBoardPfmIndex == __fhEntityBoardPfmTable_idxs[i])				
			{
				break;
			}
		}	

		if (i == *fhBoardPfmIndex_num)
		{
			struct header_complex_index *hciptrn = fhEntityBoardPfmTableTemp->next;
			BC_PT_DBG_FUN(BC_MODULE_SNMP, "FREE!!!!\n");
			struct fhEntityBoardPfmTable_entry *StorageDel = header_complex_extract_entry(&fhEntityBoardPfmTableStorage, fhEntityBoardPfmTableTemp);
			__snmp_free_fhEntityBoardPfmTable_data(StorageDel);

			fhEntityBoardPfmTableTemp = hciptrn;
		}
		else
		{
			fhEntityBoardPfmTableTemp = fhEntityBoardPfmTableTemp->next;
		}
	}

	BC_PT_FUN_LEAVE(BC_MODULE_SNMP);
	return ret;
}


bc_boolean __snmp_fhEntityBoardPfmTable_update_dev(bc_int32 __fhBoardPfmIndex)
{
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	
	struct fhEntityBoardPfmTable_entry *StorageTmp = NULL;
	struct header_complex_index *fhEntityBoardPfmTableTemp = NULL;

	bc_int32 __fhBoardPfmIndex_tmp = 0;
	bc_int32 __update_count = 0;
	
	bc_int32 fhBoardPfmIndex_num;
	bc_int32 next_is_chk = TRUE;

	struct fhEntityBoardPfmTable_entry data_tmp[fhEntityBoardPfmTable_num];
	int data_cnt = 0;

	int i = 0;
	
	BC_PT_FUN_TAG(BC_MODULE_SNMP);

	if(snmp_is_update(&update_time))
	{
		if (!__snmp_fhEntityBoardPfmTable_index_update(&fhBoardPfmIndex_num))
		{
			BC_PT_DBG_CPL(BC_MODULE_SNMP, "__snmp_fhEntityBoardPfmTable_index_update() failed!\r\n");
			return FALSE;
		}

		fhEntityBoardPfmTableTemp = fhEntityBoardPfmTableStorage;
		while(fhEntityBoardPfmTableTemp)
		{
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			StorageTmp = (struct fhEntityBoardPfmTable_entry *)fhEntityBoardPfmTableTemp->data;

			__fhBoardPfmIndex_tmp = StorageTmp->fhBoardPfmIndex;

			BC_PT_DBG_FUN(BC_MODULE_SNMP, "next_is_chk=%d\n",next_is_chk);

			//list
			if((__fhBoardPfmIndex_tmp != __fhBoardPfmIndex) && (next_is_chk == TRUE))
			{
				fhEntityBoardPfmTableTemp = fhEntityBoardPfmTableTemp->next;			
			}
			else		//used API
			{
				next_is_chk = FALSE;
				
				// get data of table				
				vir_api_get_data(data_tmp, &data_cnt);

				for(i=0; i<data_cnt; i++)
				{
					if(data_tmp[i].fhBoardPfmIndex == __fhBoardPfmIndex_tmp)
					{
						memcpy(StorageTmp, data_tmp+i, sizeof(struct fhEntityBoardPfmTable_entry));
						break;
					}
				}
				#if 0
				printf("StorageTmp->fhBoardPfmIndex = %d\n", StorageTmp->fhBoardPfmIndex);
				printf("StorageTmp->fhBoardTemperature = %s\n", StorageTmp->fhBoardTemperature);
				printf("StorageTmp->fhBoardVoltage = %s\n", StorageTmp->fhBoardVoltage);
				#endif
				
				fhEntityBoardPfmTableTemp = fhEntityBoardPfmTableTemp->next;			

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
	SNMP_MEM_FREE(fhEntityBoardPfmTable_idxs);
	return TRUE;
}		




static bc_boolean __snmp_fhEntityBoardPfmTable_update(bc_int32 __fhBoardPfmIndex)
{
#ifdef SNMP_PRJ_SNMP_X86
		return __snmp_fhEntityBoardPfmTable_update_x86(__fhBoardPfmIndex);
#else
		return __snmp_fhEntityBoardPfmTable_update_dev(__fhBoardPfmIndex);
#endif
}


static unsigned char *__snmp_fhEntityBoardPfmTable_handler(struct variable *vp,
																		oid *name,
																		size_t *length,
																		int exact,
																		size_t *var_len,
																		WriteMethod **write_method)
{	
	struct fhEntityBoardPfmTable_entry *node = NULL;

	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	bc_int32 __fhBoardPfmIndex = 0;

	SNMP_NODE_OID_PT(name, *length);
	
	if (*length == FHENTITYBOARDPFMTABLE_OID_FULL_LEN)
	{
		BC_PT_FUN_TAG(BC_MODULE_SNMP);
		__fhBoardPfmIndex = name[*length - 1];
	}
	
	else if (*length < FHENTITYBOARDPFMTABLE_OID_FULL_LEN)
	{
		BC_PT_DBG_FUN(BC_MODULE_SNMP,  "*length=%d\n",*(size_t *)length);
		__fhBoardPfmIndex = 1;
	}
	
	if(!__snmp_fhEntityBoardPfmTable_update(__fhBoardPfmIndex))
	{
		BC_PT_DBG_FUN(BC_MODULE_SNMP,  "__snmp_fhEntityBoardPfmTable_update() failed!!\r\n");
		return NULL;
	}
	
	SNMP_HDL_HEADER_COMPLEX(fhEntityBoardPfmTableStorage, vp, name, length, exact, var_len, write_method, NULL, SNMP_TABLE_NO_ROW_STATUS);

	switch(vp->magic)
	{
		case COLUMN_FHBOARDPFMINDEX:
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			*var_len = sizeof(node->fhBoardPfmIndex);
			return (u_char *)&node->fhBoardPfmIndex;
		case COLUMN_FHBOARDTEMPERATURE:
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			*var_len = strlen(node->fhBoardTemperature);
			return (u_char *)node->fhBoardTemperature;
		case COLUMN_FHBOARDVOLTAGE:
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			*var_len = strlen(node->fhBoardVoltage);
			return (u_char *)node->fhBoardVoltage;
		default:
			BC_PT_DBG_FUN(BC_MODULE_SNMP,  "colunm error!!\r\n");
	}
	return NULL;
}
#endif

void snmp_fhEntityBoardPfmTable_init(void)
{
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);

	SNMP_REGISTER_TABLE(fhEntityBoardPfmTable);

	SNMP_MIB_FFLUSH_INIT();

	BC_PT_FUN_LEAVE(BC_MODULE_SNMP);
}

