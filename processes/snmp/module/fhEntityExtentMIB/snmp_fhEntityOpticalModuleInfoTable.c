/*******************************************************************************
  [Author]	   : wangb@longraise.com
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

#include "snmp_fhEntityOpticalModuleInfoTable.h"
#include "snmp_global.h"
#include "snmp_core_ex.h"



///////////////////////////////////////////////////////////////////////////////
//                                                               			 //
//																			 //
//						外 部 变 量、 函 数 引 用					         //
//																			 //
///////////////////////////////////////////////////////////////////////////////
static snmp_find_var_callback   __snmp_fhEntityOpticalModuleInfoTable_handler;


///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//																			 //
//						结   构   体   宏   定   义							 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
#if 1


#define SNMP_PON_PORT_TBL_STORAGE_QUERY(StorageTmp)	\
									do{ \
										size_t	newlen =  name_len - (fhEntityOpticalModuleInfoTable_variables_oid_len + 3 - 1);\
										if(!(StorageTmp = header_complex(fhEntityOpticalModuleInfoTableStorage, NULL, &name[fhEntityOpticalModuleInfoTable_variables_oid_len + 3 - 1], &newlen, 1, NULL, NULL)))\
										{\
											BC_PT_FUN_TAG(BC_MODULE_SNMP);\
											return SNMP_ERR_NOSUCHNAME; \
										}\
									}while(0)

#define SNMP_NODE_INDEX_GET(idx)	\
	do{	\
		idx = node->fhEntityOpticalIndex;	\
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
static struct variable2 fhEntityOpticalModuleInfoTable_variables[] = 
{
	{COLUMN_FHENTITYOPTICALINDEX, ASN_INTEGER, NETSNMP_OLDAPI_RONLY, 
		__snmp_fhEntityOpticalModuleInfoTable_handler, 2, {1, 1}},
	{COLUMN_FHENTITYOPTICALWAVELENGTH, ASN_INTEGER, NETSNMP_OLDAPI_RONLY, 
		__snmp_fhEntityOpticalModuleInfoTable_handler, 2, {1, 3}},
	{COLUMN_FHENTITYOPTICALTRANSDISTANCE, ASN_INTEGER, NETSNMP_OLDAPI_RONLY, 
		__snmp_fhEntityOpticalModuleInfoTable_handler, 2, {1, 4}},
	{COLUMN_FHENTITYOPTICALMEDIATYPE, ASN_INTEGER, NETSNMP_OLDAPI_RONLY, 
		__snmp_fhEntityOpticalModuleInfoTable_handler, 2, {1, 5}},
	{COLUMN_FHENTITYRXOPTICALPOWER, ASN_INTEGER, NETSNMP_OLDAPI_RONLY, 
		__snmp_fhEntityOpticalModuleInfoTable_handler, 2, {1, 6}},
	{COLUMN_FHENTITYTXOPTICALPOWER, ASN_INTEGER, NETSNMP_OLDAPI_RONLY, 
		__snmp_fhEntityOpticalModuleInfoTable_handler, 2, {1, 7}},
	{COLUMN_FHENTITYOPTICALSPEED, ASN_OCTET_STR, NETSNMP_OLDAPI_RONLY, 
		__snmp_fhEntityOpticalModuleInfoTable_handler, 2, {1, 12}}
};

static oid fhEntityOpticalModuleInfoTable_variables_oid[] = {1,3,6,1,4,1,11408,11,1,1,2};
static const int fhEntityOpticalModuleInfoTable_variables_oid_len = FHENTITYOPTICALMODULEINFOTABLE_OID_LEN;
static struct header_complex_index *fhEntityOpticalModuleInfoTableStorage = NULL;

static time_t update_time;

//这里定义包含全部索引的全局指针
static int *fhEntityOpticalModuleInfoTable_idxs = NULL;
//这里定义表最大索引数
#define fhEntityOpticalModuleInfoTable_num	5

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

static bc_boolean vir_api_get_idxs(int __fhEntityOpticalModuleInfoTable_idxs[fhEntityOpticalModuleInfoTable_num], int *fhEntityOpticalIndex_num)
{
	int i = 0;

	for(; i<fhEntityOpticalModuleInfoTable_num; i++)
	{
		__fhEntityOpticalModuleInfoTable_idxs[i] = i+1;
	}
	*fhEntityOpticalIndex_num = fhEntityOpticalModuleInfoTable_num;

	return TRUE;
}

static bc_boolean vir_api_get_data(struct fhEntityOpticalModuleInfoTable_entry data[fhEntityOpticalModuleInfoTable_num], int *fhEntityOpticalIndex_num)
{
	int i = 0;

	for(; i<fhEntityOpticalModuleInfoTable_num; i++)
	{
		data[i].fhEntityOpticalIndex = i+1;
		data[i].fhEntityOpticalWavelength = i+10;
    		data[i].fhEntityOpticalTransDistance = i+20;
    		data[i].fhEntityOpticalMediaType = i+30;
    		data[i].fhEntityRxOpticalPower = i+40;
   		data[i].fhEntityTxOpticalPower = i+50;
		strcpy(data[i].fhEntityOpticalSpeed, "fhEntityOpticalSpeed");
	}
	*fhEntityOpticalIndex_num = fhEntityOpticalModuleInfoTable_num;

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
static bc_int32 __snmp_fhEntityOpticalModuleInfoTable_add(struct fhEntityOpticalModuleInfoTable_entry *node)
{
   	netsnmp_variable_list *vars = NULL;
		
	snmp_varlist_add_variable(&vars, NULL, 0, ASN_INTEGER,
		&node->fhEntityOpticalIndex, sizeof(node->fhEntityOpticalIndex));

	header_complex_add_data(&fhEntityOpticalModuleInfoTableStorage, vars, node);

	return SNMPERR_SUCCESS;
}

static struct fhEntityOpticalModuleInfoTable_entry *__snmp_fhEntityOpticalModuleInfoTable_create(void)
{
	struct fhEntityOpticalModuleInfoTable_entry *entry = SNMP_MALLOC_STRUCT(fhEntityOpticalModuleInfoTable_entry);
	if(!entry)
	{
		return NULL;
	}
	memset(entry, 0, sizeof(struct fhEntityOpticalModuleInfoTable_entry));
	entry->storageType =  ST_NONVOLATILE;
	
	return entry;
}

#if 1
static void __snmp_free_fhEntityOpticalModuleInfoTable_data(struct fhEntityOpticalModuleInfoTable_entry *StorageDel)
{
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	
    netsnmp_assert(StorageDel);
    free(StorageDel);
}
#endif



bc_boolean __snmp_fhEntityOpticalModuleInfoTable_update_x86(bc_int32 __fhEntityOpticalIndex)
{
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	
	if (NULL == fhEntityOpticalModuleInfoTableStorage)
	{
		BC_PT_FUN_TAG(BC_MODULE_SNMP);
		struct fhEntityOpticalModuleInfoTable_entry *StorageTmp = NULL;
		StorageTmp = __snmp_fhEntityOpticalModuleInfoTable_create();
		
		StorageTmp->fhEntityOpticalIndex = 1;
		
		__snmp_fhEntityOpticalModuleInfoTable_add(StorageTmp);
	}
	
	BC_PT_FUN_LEAVE(BC_MODULE_SNMP);
	return TRUE;
}

bc_boolean __snmp_fhEntityOpticalModuleInfoTable_index_update(bc_int32 *fhEntityOpticalIndex_num)
{	
	bc_boolean ret = TRUE;
	
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	struct fhEntityOpticalModuleInfoTable_entry *StorageTmp = NULL;
	struct header_complex_index *fhEntityOpticalModuleInfoTableTemp = NULL;

	bc_int32 i = 0; 
	
	bc_int32 __fhEntityOpticalModuleInfoTable_idxs[fhEntityOpticalModuleInfoTable_num];

	vir_api_get_idxs(__fhEntityOpticalModuleInfoTable_idxs, fhEntityOpticalIndex_num);
	
	SNMP_MEM_GET(fhEntityOpticalModuleInfoTable_idxs, int, fhEntityOpticalModuleInfoTable_num);
	memcpy(fhEntityOpticalModuleInfoTable_idxs, __fhEntityOpticalModuleInfoTable_idxs, sizeof(__fhEntityOpticalModuleInfoTable_idxs));

	for (i = 0; i < *fhEntityOpticalIndex_num; i++)
	{
		fhEntityOpticalModuleInfoTableTemp = fhEntityOpticalModuleInfoTableStorage;
		StorageTmp = NULL;
		while(fhEntityOpticalModuleInfoTableTemp)
		{
			StorageTmp = (struct fhEntityOpticalModuleInfoTable_entry *)fhEntityOpticalModuleInfoTableTemp->data;
			if (StorageTmp->fhEntityOpticalIndex == __fhEntityOpticalModuleInfoTable_idxs[i] )	// modiry
			{
				break;
			}
			fhEntityOpticalModuleInfoTableTemp = fhEntityOpticalModuleInfoTableTemp->next;
		}
		
		if (!fhEntityOpticalModuleInfoTableTemp)
		{
			StorageTmp = __snmp_fhEntityOpticalModuleInfoTable_create();

			StorageTmp->fhEntityOpticalIndex = __fhEntityOpticalModuleInfoTable_idxs[i];	//modiry
			__snmp_fhEntityOpticalModuleInfoTable_add(StorageTmp);
		}

	}	

	fhEntityOpticalModuleInfoTableTemp = fhEntityOpticalModuleInfoTableStorage;
	while (fhEntityOpticalModuleInfoTableTemp)
	{
		StorageTmp = (struct fhEntityOpticalModuleInfoTable_entry *)fhEntityOpticalModuleInfoTableTemp->data;
		for(i = 0; i < *fhEntityOpticalIndex_num; i++)
		{
			if (StorageTmp->fhEntityOpticalIndex == __fhEntityOpticalModuleInfoTable_idxs[i])				
			{
				break;
			}
		}	

		if (i == *fhEntityOpticalIndex_num)
		{
			struct header_complex_index *hciptrn = fhEntityOpticalModuleInfoTableTemp->next;
			BC_PT_DBG_FUN(BC_MODULE_SNMP, "FREE!!!!\n");
			struct fhEntityOpticalModuleInfoTable_entry *StorageDel = header_complex_extract_entry(&fhEntityOpticalModuleInfoTableStorage, fhEntityOpticalModuleInfoTableTemp);
			__snmp_free_fhEntityOpticalModuleInfoTable_data(StorageDel);

			fhEntityOpticalModuleInfoTableTemp = hciptrn;
		}
		else
		{
			fhEntityOpticalModuleInfoTableTemp = fhEntityOpticalModuleInfoTableTemp->next;
		}
	}

	BC_PT_FUN_LEAVE(BC_MODULE_SNMP);
	return ret;
}


bc_boolean __snmp_fhEntityOpticalModuleInfoTable_update_dev(bc_int32 __fhEntityOpticalIndex)
{
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);

	struct fhEntityOpticalModuleInfoTable_entry *StorageTmp = NULL;
	struct header_complex_index *fhEntityOpticalModuleInfoTableTemp = NULL;

	bc_int32 __fhEntityOpticalIndex_tmp = 0;
	bc_int32 __update_count = 0;
	
	bc_int32 fhEntityOpticalIndex_num;
	bc_int32 next_is_chk = TRUE;

	struct fhEntityOpticalModuleInfoTable_entry data_tmp[fhEntityOpticalModuleInfoTable_num];
	int data_cnt = 0;

	int i = 0;
	
	BC_PT_FUN_TAG(BC_MODULE_SNMP);

	if(snmp_is_update(&update_time))
	{
		if (!__snmp_fhEntityOpticalModuleInfoTable_index_update(&fhEntityOpticalIndex_num))
		{
			BC_PT_DBG_CPL(BC_MODULE_SNMP, "__snmp_fhEntityOpticalModuleInfoTable_index_update() failed!\r\n");
			return FALSE;
		}

		fhEntityOpticalModuleInfoTableTemp = fhEntityOpticalModuleInfoTableStorage;
		while(fhEntityOpticalModuleInfoTableTemp)
		{
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			StorageTmp = (struct fhEntityOpticalModuleInfoTable_entry *)fhEntityOpticalModuleInfoTableTemp->data;

			__fhEntityOpticalIndex_tmp = StorageTmp->fhEntityOpticalIndex;

			BC_PT_DBG_FUN(BC_MODULE_SNMP, "next_is_chk=%d\n",next_is_chk);
			
			if((__fhEntityOpticalIndex_tmp != __fhEntityOpticalIndex) && (next_is_chk == TRUE))
			{
				fhEntityOpticalModuleInfoTableTemp = fhEntityOpticalModuleInfoTableTemp->next;			
			}
			else	
			{
				next_is_chk = FALSE;
				
				vir_api_get_data(data_tmp, &data_cnt);

				for(i=0; i<data_cnt; i++)
				{
					if(data_tmp[i].fhEntityOpticalIndex == __fhEntityOpticalIndex_tmp)
					{
						memcpy(StorageTmp, data_tmp+i, sizeof(struct fhEntityOpticalModuleInfoTable_entry));
						break;
					}
				}
				#if 0
				printf("StorageTmp->fhEntityOpticalIndex = %d\n", StorageTmp->fhEntityOpticalIndex);
				printf("StorageTmp->fhEntityOpticalWavelength = %d\n", StorageTmp->fhEntityOpticalWavelength);
				printf("StorageTmp->fhEntityOpticalTransDistance = %d\n", StorageTmp->fhEntityOpticalTransDistance);
				printf("StorageTmp->fhEntityOpticalMediaType = %d\n", StorageTmp->fhEntityOpticalMediaType);
				printf("StorageTmp->fhEntityRxOpticalPower = %d\n", StorageTmp->fhEntityRxOpticalPower);
				printf("StorageTmp->fhEntityTxOpticalPower = %d\n", StorageTmp->fhEntityTxOpticalPower);
				printf("StorageTmp->fhEntityOpticalSpeed = %s\n", StorageTmp->fhEntityOpticalSpeed);
				#endif
				
				fhEntityOpticalModuleInfoTableTemp = fhEntityOpticalModuleInfoTableTemp->next;			

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
	SNMP_MEM_FREE(fhEntityOpticalModuleInfoTable_idxs);
	return TRUE;
}		




static bc_boolean __snmp_fhEntityOpticalModuleInfoTable_update(bc_int32 __fhEntityOpticalIndex)
{
#ifdef SNMP_PRJ_SNMP_X86
		return __snmp_fhEntityOpticalModuleInfoTable_update_x86(__fhEntityOpticalIndex);
#else
		return __snmp_fhEntityOpticalModuleInfoTable_update_dev(__fhEntityOpticalIndex);
#endif
}


static unsigned char *__snmp_fhEntityOpticalModuleInfoTable_handler(struct variable *vp,
																		oid *name,
																		size_t *length,
																		int exact,
																		size_t *var_len,
																		WriteMethod **write_method)
{	
	struct fhEntityOpticalModuleInfoTable_entry *node = NULL;

	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	bc_int32 __fhEntityOpticalIndex = 0;

	SNMP_NODE_OID_PT(name, *length);
	
	if (*length == FHENTITYOPTICALMODULEINFOTABLE_OID_FULL_LEN)
	{
		BC_PT_FUN_TAG(BC_MODULE_SNMP);
		__fhEntityOpticalIndex = name[*length - 1];
	}
	
	else if (*length < FHENTITYOPTICALMODULEINFOTABLE_OID_FULL_LEN)
	{
		BC_PT_DBG_FUN(BC_MODULE_SNMP, "*length=%d\n",*(size_t *)length);
		__fhEntityOpticalIndex = 1;
	}
	
	if(!__snmp_fhEntityOpticalModuleInfoTable_update(__fhEntityOpticalIndex))
	{
		BC_PT_DBG_FUN(BC_MODULE_SNMP, "__snmp_fhEntityOpticalModuleInfoTable_update() failed!!\r\n");
		return NULL;
	}
	
	SNMP_HDL_HEADER_COMPLEX(fhEntityOpticalModuleInfoTableStorage, vp, name, length, exact, var_len, write_method, NULL, SNMP_TABLE_NO_ROW_STATUS);

	switch(vp->magic)
	{
		case COLUMN_FHENTITYOPTICALINDEX:
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			*var_len = sizeof(node->fhEntityOpticalIndex);
			return (u_char *)&node->fhEntityOpticalIndex;
		case COLUMN_FHENTITYOPTICALWAVELENGTH:
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			*var_len = sizeof(node->fhEntityOpticalWavelength);
			return (u_char *)&node->fhEntityOpticalWavelength;
		case COLUMN_FHENTITYOPTICALTRANSDISTANCE:
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			*var_len = sizeof(node->fhEntityOpticalTransDistance);
			return (u_char *)&node->fhEntityOpticalTransDistance;
		case COLUMN_FHENTITYOPTICALMEDIATYPE:
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			*var_len = sizeof(node->fhEntityOpticalMediaType);
			return (u_char *)&node->fhEntityOpticalMediaType;
		case COLUMN_FHENTITYRXOPTICALPOWER:
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			*var_len = sizeof(node->fhEntityRxOpticalPower);
			return (u_char *)&node->fhEntityRxOpticalPower;
		case COLUMN_FHENTITYTXOPTICALPOWER:
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			*var_len = sizeof(node->fhEntityTxOpticalPower);
			return (u_char *)&node->fhEntityTxOpticalPower;
		case COLUMN_FHENTITYOPTICALSPEED:
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			*var_len = strlen(node->fhEntityOpticalSpeed);
			return (u_char *)node->fhEntityOpticalSpeed;
		default:
			BC_PT_DBG_FUN(BC_MODULE_SNMP, "colunm error!!\r\n");
	}
	return NULL;
}
#endif

void snmp_fhEntityOpticalModuleInfoTable_init(void)
{
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	
	SNMP_REGISTER_TABLE(fhEntityOpticalModuleInfoTable);

	SNMP_MIB_FFLUSH_INIT();

	BC_PT_FUN_LEAVE(BC_MODULE_SNMP);
}

