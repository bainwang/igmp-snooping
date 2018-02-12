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

#include "snmp_snmpCommunityNameTable.h"
#include "snmp_global.h"
#include "snmp_core_ex.h"



///////////////////////////////////////////////////////////////////////////////
//                                                               			 //
//																			 //
//						外 部 变 量、 函 数 引 用					         //
//																			 //
///////////////////////////////////////////////////////////////////////////////
static snmp_find_var_callback   __snmp_snmpCommunityNameTable_handler;


///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//																			 //
//						结   构   体   宏   定   义							 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
#if 1


#define SNMP_PON_PORT_TBL_STORAGE_QUERY(StorageTmp)	\
									do{ \
										size_t	newlen =  name_len - (snmpCommunityNameTable_variables_oid_len + 3 - 1);\
										if(!(StorageTmp = header_complex(snmpCommunityNameTableStorage, NULL, &name[snmpCommunityNameTable_variables_oid_len + 3 - 1], &newlen, 1, NULL, NULL)))\
										{\
											BC_PT_FUN_TAG(BC_MODULE_SNMP);\
											return SNMP_ERR_NOSUCHNAME; \
										}\
									}while(0)

#define SNMP_NODE_INDEX_GET(idx)	\
	do{	\
		idx = node->snmpCommunityIndex;	\
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
static struct variable2 snmpCommunityNameTable_variables[] = 
{
	{COLUMN_SNMPCOMMUNITYINDEX, ASN_INTEGER, NETSNMP_OLDAPI_RONLY, 
		__snmp_snmpCommunityNameTable_handler, 2, {1, 1}},
	{COLUMN_SNMPCOMMUNITYNAME, ASN_OCTET_STR, NETSNMP_OLDAPI_RONLY, 
		__snmp_snmpCommunityNameTable_handler, 2, {1, 2}}
};

static oid snmpCommunityNameTable_variables_oid[] = {1,3,6,1,4,1,11408,11,1,3,5};
static const int snmpCommunityNameTable_variables_oid_len = SNMPCOMMUNITYNAMETABLE_OID_LEN;
static struct header_complex_index *snmpCommunityNameTableStorage = NULL;

static time_t update_time;

//这里定义包含全部索引的全局指针
static int *snmpCommunityNameTable_idxs = NULL;
//这里定义表最大索引数
#define snmpCommunityNameTable_num	2

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

static bc_boolean vir_api_get_idxs(int __snmpCommunityNameTable_idxs[snmpCommunityNameTable_num], int *snmpCommunityIndex_num)
{
	int i = 0;

	for(; i<snmpCommunityNameTable_num; i++)
	{
		__snmpCommunityNameTable_idxs[i] = i+1;
	}
	*snmpCommunityIndex_num = snmpCommunityNameTable_num;

	return TRUE;
}

static bc_boolean vir_api_get_data(struct snmpCommunityNameTable_entry data[snmpCommunityNameTable_num], int *snmpCommunityIndex_num)
{
	int i = 0;

	for(; i<snmpCommunityNameTable_num; i++)
	{
		data[i].snmpCommunityIndex = i+1;
		strcpy(data[i].snmpCommunityName, "public");
	}
	*snmpCommunityIndex_num = snmpCommunityNameTable_num;

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
static bc_int32 __snmp_snmpCommunityNameTable_add(struct snmpCommunityNameTable_entry *node)
{
   	netsnmp_variable_list *vars = NULL;
		
	snmp_varlist_add_variable(&vars, NULL, 0, ASN_INTEGER,
		&node->snmpCommunityIndex, sizeof(node->snmpCommunityIndex));

	header_complex_add_data(&snmpCommunityNameTableStorage, vars, node);

	return SNMPERR_SUCCESS;
}

static struct snmpCommunityNameTable_entry *__snmp_snmpCommunityNameTable_create(void)
{
	struct snmpCommunityNameTable_entry *entry = SNMP_MALLOC_STRUCT(snmpCommunityNameTable_entry);
	if(!entry)
	{
		return NULL;
	}
	memset(entry, 0, sizeof(struct snmpCommunityNameTable_entry));
	entry->storageType =  ST_NONVOLATILE;
	
	return entry;
}

#if 1
static void __snmp_free_snmpCommunityNameTable_data(struct snmpCommunityNameTable_entry *StorageDel)
{
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	
    netsnmp_assert(StorageDel);
    free(StorageDel);
}
#endif



bc_boolean __snmp_snmpCommunityNameTable_update_x86(bc_int32 __snmpCommunityIndex)
{
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	
	if (NULL == snmpCommunityNameTableStorage)
	{
		BC_PT_FUN_TAG(BC_MODULE_SNMP);
		struct snmpCommunityNameTable_entry *StorageTmp = NULL;
		StorageTmp = __snmp_snmpCommunityNameTable_create();
		
		StorageTmp->snmpCommunityIndex = 1;
		
		__snmp_snmpCommunityNameTable_add(StorageTmp);
	}
	
	BC_PT_FUN_LEAVE(BC_MODULE_SNMP);
	return TRUE;
}

bc_boolean __snmp_snmpCommunityNameTable_index_update(bc_int32 *snmpCommunityIndex_num)
{	
	bc_boolean ret = TRUE;
	
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	struct snmpCommunityNameTable_entry *StorageTmp = NULL;
	struct header_complex_index *snmpCommunityNameTableTemp = NULL;

	bc_int32 i = 0; 
	
	bc_int32 __snmpCommunityNameTable_idxs[snmpCommunityNameTable_num];

	vir_api_get_idxs(__snmpCommunityNameTable_idxs, snmpCommunityIndex_num);
	
	SNMP_MEM_GET(snmpCommunityNameTable_idxs, int, snmpCommunityNameTable_num);
	memcpy(snmpCommunityNameTable_idxs, __snmpCommunityNameTable_idxs, sizeof(__snmpCommunityNameTable_idxs));

	for (i = 0; i < *snmpCommunityIndex_num; i++)
	{
		snmpCommunityNameTableTemp = snmpCommunityNameTableStorage;
		StorageTmp = NULL;
		while(snmpCommunityNameTableTemp)
		{
			StorageTmp = (struct snmpCommunityNameTable_entry *)snmpCommunityNameTableTemp->data;
			if (StorageTmp->snmpCommunityIndex == __snmpCommunityNameTable_idxs[i] )
			{
				break;
			}
			snmpCommunityNameTableTemp = snmpCommunityNameTableTemp->next;
		}
		
		if (!snmpCommunityNameTableTemp)
		{
			StorageTmp = __snmp_snmpCommunityNameTable_create();

			StorageTmp->snmpCommunityIndex = __snmpCommunityNameTable_idxs[i];	//modiry
			__snmp_snmpCommunityNameTable_add(StorageTmp);
		}

	}	

	snmpCommunityNameTableTemp = snmpCommunityNameTableStorage;
	while (snmpCommunityNameTableTemp)
	{
		StorageTmp = (struct snmpCommunityNameTable_entry *)snmpCommunityNameTableTemp->data;
		for(i = 0; i < *snmpCommunityIndex_num; i++)
		{
			if (StorageTmp->snmpCommunityIndex == __snmpCommunityNameTable_idxs[i])				
			{
				break;
			}
		}	

		if (i == *snmpCommunityIndex_num)
		{
			struct header_complex_index *hciptrn = snmpCommunityNameTableTemp->next;
			BC_PT_DBG_FUN(BC_MODULE_SNMP, "FREE!!!!\n");
			struct snmpCommunityNameTable_entry *StorageDel = header_complex_extract_entry(&snmpCommunityNameTableStorage, snmpCommunityNameTableTemp);
			__snmp_free_snmpCommunityNameTable_data(StorageDel);

			snmpCommunityNameTableTemp = hciptrn;
		}
		else
		{
			snmpCommunityNameTableTemp = snmpCommunityNameTableTemp->next;
		}
	}

	BC_PT_FUN_LEAVE(BC_MODULE_SNMP);
	return ret;
}


bc_boolean __snmp_snmpCommunityNameTable_update_dev(bc_int32 __snmpCommunityIndex)
{
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);

	struct snmpCommunityNameTable_entry *StorageTmp = NULL;
	struct header_complex_index *snmpCommunityNameTableTemp = NULL;

	bc_int32 __snmpCommunityIndex_tmp = 0;
	bc_int32 __update_count = 0;
	
	bc_int32 snmpCommunityIndex_num;
	bc_int32 next_is_chk = TRUE;

	struct snmpCommunityNameTable_entry data_tmp[snmpCommunityNameTable_num];
	int data_cnt = 0;

	int i = 0;
	
	BC_PT_FUN_TAG(BC_MODULE_SNMP);

	if(snmp_is_update(&update_time))
	{
		if (!__snmp_snmpCommunityNameTable_index_update(&snmpCommunityIndex_num))
		{
			BC_PT_DBG_CPL(BC_MODULE_SNMP, "__snmp_snmpCommunityNameTable_index_update() failed!\r\n");
			return FALSE;
		}

		snmpCommunityNameTableTemp = snmpCommunityNameTableStorage;
		while(snmpCommunityNameTableTemp)
		{
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			StorageTmp = (struct snmpCommunityNameTable_entry *)snmpCommunityNameTableTemp->data;

			__snmpCommunityIndex_tmp = StorageTmp->snmpCommunityIndex;

			BC_PT_DBG_FUN(BC_MODULE_SNMP, "next_is_chk=%d\n",next_is_chk);
			
			if((__snmpCommunityIndex_tmp != __snmpCommunityIndex) && (next_is_chk == TRUE))
			{
				snmpCommunityNameTableTemp = snmpCommunityNameTableTemp->next;			
			}
			else	
			{
				next_is_chk = FALSE;
				
				vir_api_get_data(data_tmp, &data_cnt);

				for(i=0; i<data_cnt; i++)
				{
					if(data_tmp[i].snmpCommunityIndex == __snmpCommunityIndex_tmp)
					{
						memcpy(StorageTmp, data_tmp+i, sizeof(struct snmpCommunityNameTable_entry));
						break;
					}
				}
				#if 0
				printf("StorageTmp->snmpCommunityIndex = %d\n", StorageTmp->snmpCommunityIndex);
				printf("StorageTmp->snmpCommunityName = %s\n", StorageTmp->snmpCommunityName);
				#endif
				
				snmpCommunityNameTableTemp = snmpCommunityNameTableTemp->next;			

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
	SNMP_MEM_FREE(snmpCommunityNameTable_idxs);
	return TRUE;
}		




static bc_boolean __snmp_snmpCommunityNameTable_update(bc_int32 __snmpCommunityIndex)
{
#ifdef SNMP_PRJ_SNMP_X86
		return __snmp_snmpCommunityNameTable_update_x86(__snmpCommunityIndex);
#else
		return __snmp_snmpCommunityNameTable_update_dev(__snmpCommunityIndex);
#endif
}


static unsigned char *__snmp_snmpCommunityNameTable_handler(struct variable *vp,
																		oid *name,
																		size_t *length,
																		int exact,
																		size_t *var_len,
																		WriteMethod **write_method)
{	
	struct snmpCommunityNameTable_entry *node = NULL;

	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	bc_int32 __snmpCommunityIndex = 0;

	SNMP_NODE_OID_PT(name, *length);
	
	if (*length == SNMPCOMMUNITYNAMETABLE_OID_FULL_LEN)
	{
		BC_PT_FUN_TAG(BC_MODULE_SNMP);
		__snmpCommunityIndex = name[*length - 1];
	}
	
	else if (*length < SNMPCOMMUNITYNAMETABLE_OID_FULL_LEN)
	{
		BC_PT_DBG_FUN(BC_MODULE_SNMP, "*length=%d\n",*(size_t *)length);
		__snmpCommunityIndex = 1;
	}
	
	if(!__snmp_snmpCommunityNameTable_update(__snmpCommunityIndex))
	{
		BC_PT_DBG_FUN(BC_MODULE_SNMP, "__snmp_snmpCommunityNameTable_update() failed!!\r\n");
		return NULL;
	}
	
	SNMP_HDL_HEADER_COMPLEX(snmpCommunityNameTableStorage, vp, name, length, exact, var_len, write_method, NULL, SNMP_TABLE_NO_ROW_STATUS);

	switch(vp->magic)
	{
		case COLUMN_SNMPCOMMUNITYINDEX:
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			*var_len = sizeof(node->snmpCommunityIndex);
			return (u_char *)&node->snmpCommunityIndex;
		case COLUMN_SNMPCOMMUNITYNAME:
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			*var_len = strlen(node->snmpCommunityName);
			return (u_char *)node->snmpCommunityName;
		default:
			BC_PT_DBG_FUN(BC_MODULE_SNMP, "colunm error!!\r\n");
	}
	return NULL;
}
#endif

void snmp_snmpCommunityNameTable_init(void)
{
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	
	SNMP_REGISTER_TABLE(snmpCommunityNameTable);

	SNMP_MIB_FFLUSH_INIT();

	BC_PT_FUN_LEAVE(BC_MODULE_SNMP);
}

