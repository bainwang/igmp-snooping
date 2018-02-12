/*******************************************************************************
  [Author]	   : bain.wang@outlook.com.uestc@gmail.com
  [Version]    : 1.0
  [Date]       : 2017-03-01
  [Description]:

  [Others]     :

  [History]:
	 Date          Modification 							    Initials
	----------     ----------                                   -------
	2017-03-01      Created								   		bain.wang@outlook.com
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

#include "snmp_mib2_ifTable.h"
#include "snmp_mib2_ifxTable.h"
#include "snmp_global.h"
#include "snmp_core_ex.h"



///////////////////////////////////////////////////////////////////////////////
//                                                               			 //
//																			 //
//						外 部 变 量、 函 数 引 用					         //
//																			 //
///////////////////////////////////////////////////////////////////////////////
static snmp_find_var_callback   __snmp_mib2_ifx_handler;


///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//																			 //
//						结   构   体   宏   定   义							 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
#if 1


#define SNMP_PON_PORT_TBL_STORAGE_QUERY(StorageTmp)	\
									do{ \
										size_t	newlen =  name_len - (ifx_variables_oid_len + 3 - 1);\
										if(!(StorageTmp = header_complex(ifxStorage, NULL, &name[ifx_variables_oid_len + 3 - 1], &newlen, 1, NULL, NULL)))\
										{\
											BC_PT_FUN_TAG(BC_MODULE_SNMP);\
											return SNMP_ERR_NOSUCHNAME; \
										}\
									}while(0)

#define SNMP_NODE_INDEX_GET(idx)	\
	do{	\
		idx = node->ifIndex;	\
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

static oid ifxTable_variables_oid[] = { 1, 3, 6, 1, 2, 1, 31, 1, 1 };
struct variable2 ifxTable_variables[] =
{
	{NETSNMP_IFNAME, ASN_OCTET_STR, NETSNMP_OLDAPI_RONLY,
	__snmp_mib2_ifx_handler, 2, {1, 1}},
	{NETSNMP_IFINMULTICASTPKTS, ASN_COUNTER, NETSNMP_OLDAPI_RONLY,
	__snmp_mib2_ifx_handler, 2, {1, 2}},
	{NETSNMP_IFINBROADCASTPKTS, ASN_COUNTER, NETSNMP_OLDAPI_RONLY,
	__snmp_mib2_ifx_handler, 2, {1, 3}},
	{NETSNMP_IFOUTMULTICASTPKTS, ASN_COUNTER, NETSNMP_OLDAPI_RONLY,
	__snmp_mib2_ifx_handler, 2, {1, 4}},
	{NETSNMP_IFOUTBROADCASTPKTS, ASN_COUNTER, NETSNMP_OLDAPI_RONLY,
	__snmp_mib2_ifx_handler, 2, {1, 5}},
	{NETSNMP_IFHCINOCTETS, ASN_COUNTER64, NETSNMP_OLDAPI_RONLY,
	__snmp_mib2_ifx_handler, 2, {1, 6}},
	{NETSNMP_IFHCINUCASTPKTS, ASN_COUNTER64, NETSNMP_OLDAPI_RONLY,
	__snmp_mib2_ifx_handler, 2, {1, 7}},
	{NETSNMP_IFHCINMULTICASTPKTS, ASN_COUNTER64, NETSNMP_OLDAPI_RONLY,
	__snmp_mib2_ifx_handler, 2, {1, 8}},
	{NETSNMP_IFHCINBROADCASTPKTS, ASN_COUNTER64, NETSNMP_OLDAPI_RONLY,
	__snmp_mib2_ifx_handler, 2, {1, 9}},
	{NETSNMP_IFHCOUTOCTETS, ASN_COUNTER64, NETSNMP_OLDAPI_RONLY,
	__snmp_mib2_ifx_handler, 2, {1, 10}},
	{NETSNMP_IFHCOUTUCASTPKTS, ASN_COUNTER64, NETSNMP_OLDAPI_RONLY,
	__snmp_mib2_ifx_handler, 2, {1, 11}},
	{NETSNMP_IFHCOUTMULTICASTPKTS, ASN_COUNTER64, NETSNMP_OLDAPI_RONLY,
	__snmp_mib2_ifx_handler, 2, {1, 12}},
	{NETSNMP_IFHCOUTBROADCASTPKTS, ASN_COUNTER64, NETSNMP_OLDAPI_RONLY,
	__snmp_mib2_ifx_handler, 2, {1, 13}},
	{NETSNMP_IFLINKUPDOWNTRAPENABLE, ASN_INTEGER, NETSNMP_OLDAPI_RWRITE,
	__snmp_mib2_ifx_handler, 2, {1, 14}},
	{NETSNMP_IFHIGHSPEED, ASN_GAUGE, NETSNMP_OLDAPI_RONLY,
	__snmp_mib2_ifx_handler, 2, {1, 15}},
	{NETSNMP_IFPROMISCUOUSMODE, ASN_INTEGER, NETSNMP_OLDAPI_RWRITE,
	__snmp_mib2_ifx_handler, 2, {1, 16}},
	{NETSNMP_IFCONNECTORPRESENT, ASN_INTEGER, NETSNMP_OLDAPI_RONLY,
	__snmp_mib2_ifx_handler, 2, {1, 17}},
	{NETSNMP_IFALIAS, ASN_OCTET_STR, NETSNMP_OLDAPI_RWRITE,
	__snmp_mib2_ifx_handler, 2, {1, 18}},
	{NETSNMP_IFCOUNTERDISCONTINUITYTIME, ASN_TIMETICKS, NETSNMP_OLDAPI_RONLY,
	__snmp_mib2_ifx_handler, 2, {1, 19}}
};

static struct header_complex_index *mib2IfxStorage = NULL;
static time_t update_time;


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
struct snmp_ifx_entry *__snmp_create_mib2_ifx_data(void)
{
	BC_PT_FUN_TAG(BC_MODULE_SNMP);
	
	struct snmp_ifx_entry *StorageNew = NULL;
	StorageNew = SNMP_MALLOC_STRUCT(snmp_ifx_entry);
	if (StorageNew == NULL)
	{
		return NULL;
	}

	memset(StorageNew, 0, sizeof(struct snmp_ifx_entry));
	
	StorageNew->ifIndex = 1;
	StorageNew->storageType = ST_NONVOLATILE;
	
	return StorageNew;
}

static void __snmp_free_mib2_ifx_data(struct snmp_ifx_entry *StorageDel)
{
	BC_PT_FUN_TAG(BC_MODULE_SNMP);
	
	netsnmp_assert(StorageDel);
	free(StorageDel);
}

int __snmp_mib2_ifx_add(struct snmp_ifx_entry *thedata)
{
	BC_PT_FUN_TAG(BC_MODULE_SNMP);

	netsnmp_variable_list *vars = NULL;

    /*
     * add the index variables to the varbind list, which is 
     * used by header_complex to index the data 
     */
	snmp_varlist_add_variable(&vars, NULL, 0, ASN_INTEGER,
                              &thedata->ifIndex,
                              sizeof(thedata->ifIndex));
	
	header_complex_add_data(&mib2IfxStorage, vars, thedata);

	return SNMPERR_SUCCESS;
}

static bc_boolean __snmp_mib2_ifx_update()
{	
	if (snmp_is_update(&update_time))
	{
		struct	snmp_ifx_entry ifx_mib[MIB2_SNMP_INTERFACE_COUNT];
		bc_int32 	count = 0;
		bc_int32	index = 0;
		struct header_complex_index *mib2_if_tmp = NULL;
		struct snmp_ifx_entry *StorageTmp = NULL;

		memset(ifx_mib, 0, sizeof(ifx_mib));
		if (!snmp_ifx_mib_get(ifx_mib, &count))
		{
			BC_PT_DBG_FUN(BC_MODULE_SNMP, "snmp_ifx_mib_get() failed!\r\n");
			return FALSE;
		}
		
		
		BC_PT_DBG_FUN(BC_MODULE_SNMP, "count = %d\r\n", count);
		for (index = 0; index < count; index++)
		{
			BC_PT_DBG_FUN(BC_MODULE_SNMP, "index = %d ifDescr:%s\r\n", ifx_mib[index].ifIndex, ifx_mib[index].ifName);
		}
		
		for (index = 0; index < count; index++)
		{
			mib2_if_tmp = mib2IfxStorage;
			StorageTmp = NULL;
			
			while (mib2_if_tmp)
			{
				StorageTmp = (struct snmp_ifx_entry *)mib2_if_tmp->data;
				
				if (StorageTmp->ifIndex == ifx_mib[index].ifIndex)
				{
					memcpy(StorageTmp, &ifx_mib[index], sizeof(ifx_mib[index]));
					break;
				}

				mib2_if_tmp = mib2_if_tmp->next;
			}	

			if (!mib2_if_tmp)
			{
				StorageTmp = __snmp_create_mib2_ifx_data();
				memcpy(StorageTmp, &ifx_mib[index], sizeof(ifx_mib[index]));
    			StorageTmp->storageType = ST_NONVOLATILE;
				__snmp_mib2_ifx_add(StorageTmp);
			}
		}

		mib2_if_tmp = mib2IfxStorage;
		while (mib2_if_tmp)
		{
			StorageTmp = (struct snmp_ifx_entry *)mib2_if_tmp->data;
			for(index = 0; index < count; index++)
			{
				if (StorageTmp->ifIndex == ifx_mib[index].ifIndex)
				{
					break;
				}
			}	

			if (index == count)
			{
	            struct header_complex_index *hciptrn = mib2_if_tmp->next;
	            struct snmp_ifx_entry *StorageDel = header_complex_extract_entry(&mib2IfxStorage, hciptrn);
	            __snmp_free_mib2_ifx_data(StorageDel);

				mib2_if_tmp = hciptrn;
			}
			else
			{
				mib2_if_tmp = mib2_if_tmp->next;
			}			
		}
	}	

	return TRUE;
}

/*
 * var_snmpCommunityTable():
 *   Handle this table separately from the scalar value case.
 *   The workings of this are basically the same as for var_mteObjectsTable above.
 */
static unsigned char *__snmp_mib2_ifx_handler(struct variable *vp,
                 oid * name,
                 size_t *length,
                 int exact, size_t *var_len, WriteMethod ** write_method)
{
	struct snmp_ifx_entry *StorageTmp = NULL;
	
	BC_PT_FUN_TAG(BC_MODULE_SNMP);

	if (vp)
	{
		BC_PT_DBG_FUN(BC_MODULE_SNMP, "magic = %d type = %d acl = %d namelen = %d\r\n", vp->magic, vp->type, vp->acl, vp->namelen);
	}
	
	bc_int32 i = 0;
	for (i = 0; i < vp->namelen; i++)
	{
		if (i == 0)
		{
			BC_PT_DBG_FUN(BC_MODULE_SNMP, "vp->name:%d", (bc_int32)vp->name[i]);
		}
		else
		{
			BC_PT_DBG_SMP(BC_MODULE_SNMP, ".%d", (bc_int32)vp->name[i]);
		}
	}
	if (vp->namelen)
	{
		BC_PT_DBG_SMP(BC_MODULE_SNMP, "\r\n");
	}

	/**/
	if (length)
	{
		BC_PT_DBG_FUN(BC_MODULE_SNMP, "length = %d\r\n", *length);
	}
	for (i = 0; i < *length; i++)
	{
		if (i == 0)
		{
			BC_PT_DBG_FUN(BC_MODULE_SNMP, "name:%d", (bc_int32)name[i]);
		}
		else
		{
			BC_PT_DBG_SMP(BC_MODULE_SNMP, ".%d", (bc_int32)name[i]);
		}
	}
	if (*length)
	{
		BC_PT_DBG_SMP(BC_MODULE_SNMP, "\r\n");
	}
	
	if (!__snmp_mib2_ifx_update())
	{
		BC_PT_DBG_FUN(BC_MODULE_SNMP, "snmp_mib2_interface_update() failed!!\r\n");
		return NULL;
	}

    /*
     * this assumes you have registered all your data properly
     */
	if ((StorageTmp = header_complex(mib2IfxStorage, vp, name, length, exact, var_len, write_method)) == NULL)
	{
#if 0    
		if (vp->magic == COLUMN_SNMPCOMMUNITYROWSTATUS)
		{
			*write_method = kt_snmp_write_snmpCommunityRowStatus;
		}
#endif		
		BC_PT_FUN_TAG(BC_MODULE_SNMP);
		return NULL;
	}

/*
struct snmp_ifx_entry
{
	bc_int32	ifIndex;
	bc_char		[256];
	bc_int32	;
	bc_int32	;
	bc_int32	;
	bc_int32	;
	kt_int64	ifHCInOctets;
	kt_int64	ifHCInUcastPkts;
	kt_int64	ifHCInMulticastPkts;
	kt_int64	ifHCInBroadcastPkts;
	kt_int64	ifHCOutOctets;
	kt_int64	ifHCOutUcastPkts;
	kt_int64	ifHCOutMulticastPkts;
	kt_int64	ifHCOutBroadcastPkts;
	bc_int32	ifLinkUpDownTrapEnable;
	bc_int32	ifHighSpeed;
	bc_int32	ifPromiscuousMode;
	bc_int32	ifConnectorPresent;
	bc_char		ifAlias[64];
	bc_int32	ifCounterDiscontinuityTime;
	
    bc_int32	storageType;
};
*/
    /*
     * this is where we do the value assignments for the mib results.
     */     
	switch (vp->magic)
	{
		case NETSNMP_IFNAME:
			memcpy(return_buf, StorageTmp->ifName, sizeof(StorageTmp->ifName));
			*var_len = strlen(StorageTmp->ifName);
			return (u_char *)return_buf;
		case NETSNMP_IFINMULTICASTPKTS:
			long_return = StorageTmp->ifInMulticastPkts;
			*var_len = sizeof(long_return);
			return (u_char *) & long_return;
		case NETSNMP_IFINBROADCASTPKTS:
			long_return = StorageTmp->ifInBroadcastPkts;
			*var_len = sizeof(long_return);
			return (u_char *) & long_return;
		case NETSNMP_IFOUTMULTICASTPKTS:
			long_return = StorageTmp->ifOutMulticastPkts;
			*var_len = sizeof(long_return);
			return (u_char *) & long_return;
		case NETSNMP_IFOUTBROADCASTPKTS:
			long_return = StorageTmp->ifOutBroadcastPkts;
			*var_len = sizeof(long_return);
			return (u_char *) & long_return;
		case NETSNMP_IFHCINOCTETS:
			memcpy(return_buf, &StorageTmp->ifHCInOctets, sizeof(StorageTmp->ifHCInOctets));
			*var_len = sizeof(StorageTmp->ifHCInOctets);
			return (u_char *)return_buf;
		case NETSNMP_IFHCINUCASTPKTS:
			memcpy(return_buf, &StorageTmp->ifHCInUcastPkts, sizeof(StorageTmp->ifHCInUcastPkts));
			*var_len = sizeof(StorageTmp->ifHCInUcastPkts);
			return (u_char *)return_buf;
		case NETSNMP_IFHCINMULTICASTPKTS:
			memcpy(return_buf, &StorageTmp->ifHCInMulticastPkts, sizeof(StorageTmp->ifHCInMulticastPkts));
			*var_len = sizeof(StorageTmp->ifHCInMulticastPkts);
			return (u_char *)return_buf;
		case NETSNMP_IFHCINBROADCASTPKTS:
			memcpy(return_buf, &StorageTmp->ifHCInBroadcastPkts, sizeof(StorageTmp->ifHCInBroadcastPkts));
			*var_len = sizeof(StorageTmp->ifHCInBroadcastPkts);
			return (u_char *)return_buf;
		case NETSNMP_IFHCOUTOCTETS:
			memcpy(return_buf, &StorageTmp->ifHCOutOctets, sizeof(StorageTmp->ifHCOutOctets));
			*var_len = sizeof(StorageTmp->ifHCOutOctets);
			return (u_char *)return_buf;
		case NETSNMP_IFHCOUTUCASTPKTS:		
			memcpy(return_buf, &StorageTmp->ifHCOutUcastPkts, sizeof(StorageTmp->ifHCOutUcastPkts));
			*var_len = sizeof(StorageTmp->ifHCOutUcastPkts);
			return (u_char *)return_buf;
		case NETSNMP_IFHCOUTMULTICASTPKTS:		
			memcpy(return_buf, &StorageTmp->ifHCOutMulticastPkts, sizeof(StorageTmp->ifHCOutMulticastPkts));
			*var_len = sizeof(StorageTmp->ifHCOutMulticastPkts);
			return (u_char *)return_buf;
		case NETSNMP_IFHCOUTBROADCASTPKTS:
			memcpy(return_buf, &StorageTmp->ifHCOutBroadcastPkts, sizeof(StorageTmp->ifHCOutBroadcastPkts));
			*var_len = sizeof(StorageTmp->ifHCOutBroadcastPkts);
			return (u_char *)return_buf;
		case NETSNMP_IFLINKUPDOWNTRAPENABLE:
			long_return = StorageTmp->ifLinkUpDownTrapEnable;
			*var_len = sizeof(long_return);
			return (u_char *) & long_return;
		case NETSNMP_IFHIGHSPEED:
			long_return = StorageTmp->ifHighSpeed;
			*var_len = sizeof(long_return);
			return (u_char *) & long_return;
		case NETSNMP_IFPROMISCUOUSMODE:
			long_return = StorageTmp->ifPromiscuousMode;
			*var_len = sizeof(long_return);
			return (u_char *) & long_return;
		case NETSNMP_IFCONNECTORPRESENT:
			long_return = StorageTmp->ifConnectorPresent;
			*var_len = sizeof(long_return);
			return (u_char *) & long_return;
		case NETSNMP_IFALIAS:
			memcpy(return_buf, StorageTmp->ifAlias, sizeof(StorageTmp->ifAlias));
			*var_len = strlen(StorageTmp->ifAlias);
			return (u_char *)return_buf;
		case NETSNMP_IFCOUNTERDISCONTINUITYTIME:
			long_return = StorageTmp->ifCounterDiscontinuityTime;
			*var_len = sizeof(long_return);
			return (u_char *) & long_return;
		default:
			return 0;
	}
	
    return NULL;
}

/** Initializes the ifxTable module */
void snmp_mib2_ifx_init(void)
{
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	
	SNMP_REGISTER_TABLE(ifxTable);

	SNMP_MIB_FFLUSH_INIT();

	BC_PT_FUN_LEAVE(BC_MODULE_SNMP);
}

