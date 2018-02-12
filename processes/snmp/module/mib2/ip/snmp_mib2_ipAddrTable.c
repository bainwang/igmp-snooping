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
//								Í·   ÎÄ   ¼þ								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include <net-snmp/agent/header_complex.h>

#include "snmp_mib2_ipAddrTable.h"
#include "snmp_global.h"
#include "snmp_core_ex.h"


static time_t update_time;



#ifndef RFC_1213_MIB
///////////////////////////////////////////////////////////////////////////////
//                                                               			 //
//																			 //
//						Íâ ²¿ ±ä Á¿¡¢ º¯ Êý Òý ÓÃ					         //
//																			 //
///////////////////////////////////////////////////////////////////////////////
static snmp_find_var_callback   __snmp_ipAddrTable_handler;


///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//																			 //
//						½á   ¹¹   Ìå   ºê   ¶¨   Òå							 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
#if 1


#define SNMP_PON_PORT_TBL_STORAGE_QUERY(StorageTmp)	\
									do{ \
										size_t	newlen =  name_len - (ipAddrTable_variables_oid_len + 3 - 1);\
										if(!(StorageTmp = header_complex(ipAddrTableStorage, NULL, &name[ipAddrTable_variables_oid_len + 3 - 1], &newlen, 1, NULL, NULL)))\
										{\
											BC_PT_FUN_TAG(BC_MODULE_SNMP);\
											return SNMP_ERR_NOSUCHNAME; \
										}\
									}while(0)

#define SNMP_NODE_INDEX_GET(idx)	\
	do{	\
		idx = node->ipAdEntAddr;	\
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
 *		µ±Ô´ÎÄ¼þÐèÒª¶¨Òåºê£¬¶øÍ·ÎÄ¼þÓÖÓëÆäËüÄ£¿éÍ·ÎÄ¼þÖÐµÄºê¶¨ÒåÓÐÖØ¸´¶¨ÒåÏÓÒÉ
 *	Ê±£¬ÔÚ´Ë´¦¶¨Òå¡£
 */

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//																			 //
//							È« ¾Ö ±ä Á¿ ¶¨ Òå							     //
//																			 //
///////////////////////////////////////////////////////////////////////////////

/* 
 *	Íâ²¿È«¾Ö±äÁ¿£¬Ìá¹©Õû¸ö¹¤³Ìµ÷ÓÃ£¬ÔÚÍ·ÎÄ¼þÖÐÌá¹©µ÷ÓÃ½Ó¿Ú(Íâ²¿ÒýÓÃÉùÃ÷)¡£
 */

/* 
 *	ÄÚ²¿È«¾Ö±äÁ¿£¬Ö»Ìá¹©¸ø¸ÃÎÄ¼þÄÚ²¿º¯Êýµ÷ÓÃ£¬²»ÔÚÍ·ÎÄ¼þÖÐÌá¹©µ÷ÓÃ½Ó¿Ú¡£
 */
#if 1
static struct variable2 ipAddrTable_variables[] = 
{
	{COLUMN_IPADENTADDR, ASN_IPADDRESS, NETSNMP_OLDAPI_RONLY, 
		__snmp_ipAddrTable_handler, 2, {1, 1}},
	{COLUMN_IPADENTIFINDEX, ASN_INTEGER, NETSNMP_OLDAPI_RONLY, 
		__snmp_ipAddrTable_handler, 2, {1, 2}},
	{COLUMN_IPADENTNETMASK, ASN_IPADDRESS, NETSNMP_OLDAPI_RONLY, 
		__snmp_ipAddrTable_handler, 2, {1, 3}},
	{COLUMN_IPADENTBCASTADDR, ASN_INTEGER, NETSNMP_OLDAPI_RONLY, 
		__snmp_ipAddrTable_handler, 2, {1, 4}},
	{COLUMN_IPADENTREASMMAXSIZE, ASN_INTEGER, NETSNMP_OLDAPI_RONLY, 
		__snmp_ipAddrTable_handler, 2, {1, 5}}
};


static oid ipAddrTable_variables_oid[] = {1,3,6,1,2,1,4,20};
static const int ipAddrTable_variables_oid_len = IPADDRTABLE_OID_LEN;
static struct header_complex_index *ipAddrTableStorage = NULL;

static time_t update_time;

//ÕâÀï¶¨Òå°üº¬È«²¿Ë÷ÒýµÄÈ«¾ÖÖ¸Õë
static in_addr_t *ipAddrTable_idxs = NULL;

//ÕâÀï¶¨Òå±í×î´óË÷ÒýÊý
#define ipAddrTable_num		2


long ret_val = 0;

#endif


///////////////////////////////////////////////////////////////////////////////
//                                                                          								 //
//																			 //
//								º¯  Êý  Éù  Ã÷							 //
//																			 //
///////////////////////////////////////////////////////////////////////////////

	
///////////////////////////////////////////////////////////////////////////////
//                                                                                                                                   //
//																			 //
//								º¯  Êý  ¶¨  Òå							 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
#if 1	/*ÐéÄâAPI£¬ÓÃÓÚX86²âÊÔ*/

static bc_boolean vir_api_get_idxs(in_addr_t __ipAddrTable_idxs[ipAddrTable_num], int *ipAdEntAddr_num)
{
//	int i = 0;
// inet_addr(ipstr);
//	for(; i<ipAddrTable_num; i++)
//	{
		__ipAddrTable_idxs[0] = inet_addr("192.168.5.101");
		__ipAddrTable_idxs[1] = inet_addr("127.0.0.0");
//	}
	*ipAdEntAddr_num = ipAddrTable_num;

	return TRUE;
}

static bc_boolean vir_api_get_data(struct ipAddrTable_entry data[ipAddrTable_num], int *ipAdEntAddr_num)
{
	int i = 0;

//	for(; i<ipAddrTable_num; i++)
//	{
		
		data[0].ipAdEntAddr = inet_addr("192.168.5.101");
		data[0].ipAdEntIfIndex = 1;
		data[0].ipAdEntNetMask = inet_addr("255.255.255.0");
		data[0].ipAdEntBcastAddr = inet_addr("255.0.0.0");
		data[0].ipAdEntReasmMaxSize = 1000;

		data[1].ipAdEntAddr = inet_addr("127.0.0.0");
		data[1].ipAdEntIfIndex = 2;
		data[1].ipAdEntNetMask = inet_addr("255.1.255.0");
		data[1].ipAdEntBcastAddr = inet_addr("255.0.0.0");
		data[1].ipAdEntReasmMaxSize = 2000;
//	}
	*ipAdEntAddr_num = ipAddrTable_num;

	return TRUE;
}
#endif


///////////////////////////////////////////////////////////////////////////////
//                                                               			 //
//																			 //
//						Íâ ²¿ ±ä Á¿¡¢ º¯ Êý Òý ÓÃ					         //
//																			 //
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//																			 //
//								º¯  Êý  ¶¨  Òå								 //
//																			 //
///////////////////////////////////////////////////////////////////////////////


#if 1
static bc_int32 __snmp_ipAddrTable_add(struct ipAddrTable_entry *node)
{
   	netsnmp_variable_list *vars = NULL;
		
	snmp_varlist_add_variable(&vars, NULL, 0, ASN_OCTET_STR,
		&node->ipAdEntAddr, sizeof(node->ipAdEntAddr));

	header_complex_add_data(&ipAddrTableStorage, vars, node);

	return SNMPERR_SUCCESS;
}

static struct ipAddrTable_entry *__snmp_ipAddrTable_create(void)
{
	struct ipAddrTable_entry *entry = SNMP_MALLOC_STRUCT(ipAddrTable_entry);
	if(!entry)
	{
		return NULL;
	}
	memset(entry, 0, sizeof(struct ipAddrTable_entry));
	entry->storageType =  ST_NONVOLATILE;
	
	return entry;
}

#if 1
static void __snmp_free_ipAddrTable_data(struct ipAddrTable_entry *StorageDel)
{
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	
    netsnmp_assert(StorageDel);
    free(StorageDel);
}
#endif



bc_boolean __snmp_ipAddrTable_update_x86(in_addr_t __ipAdEntAddr)
{
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	
	if (NULL == ipAddrTableStorage)
	{
		BC_PT_FUN_TAG(BC_MODULE_SNMP);
		struct ipAddrTable_entry *StorageTmp = NULL;
		StorageTmp = __snmp_ipAddrTable_create();
		
		StorageTmp->ipAdEntAddr = inet_addr("192.168.5.101");
		
		__snmp_ipAddrTable_add(StorageTmp);
	}
	
	BC_PT_FUN_LEAVE(BC_MODULE_SNMP);
	return TRUE;
}

bc_boolean __snmp_ipAddrTable_index_update(bc_int32 *ipAdEntAddr_num)
{	
	bc_boolean ret = TRUE;
	
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	struct ipAddrTable_entry *StorageTmp = NULL;
	struct header_complex_index *ipAddrTableTemp = NULL;

	bc_int32 i = 0; 
	
	in_addr_t __ipAddrTable_idxs[ipAddrTable_num];

	vir_api_get_idxs(__ipAddrTable_idxs, ipAdEntAddr_num);
	
	SNMP_MEM_GET(ipAddrTable_idxs, in_addr_t, ipAddrTable_num);
	memcpy(ipAddrTable_idxs, __ipAddrTable_idxs, sizeof(__ipAddrTable_idxs));

	for (i = 0; i < *ipAdEntAddr_num; i++)
	{
		ipAddrTableTemp = ipAddrTableStorage;
		StorageTmp = NULL;
		while(ipAddrTableTemp)
		{
			StorageTmp = (struct ipAddrTable_entry *)ipAddrTableTemp->data;
			if (StorageTmp->ipAdEntAddr == __ipAddrTable_idxs[i] )	
			{
				break;
			}
			ipAddrTableTemp = ipAddrTableTemp->next;
		}
		
		if (!ipAddrTableTemp)
		{
			StorageTmp = __snmp_ipAddrTable_create();

			StorageTmp->ipAdEntAddr = __ipAddrTable_idxs[i];
			__snmp_ipAddrTable_add(StorageTmp);
		}

	}	

	ipAddrTableTemp = ipAddrTableStorage;
	while (ipAddrTableTemp)
	{
		StorageTmp = (struct ipAddrTable_entry *)ipAddrTableTemp->data;
		for(i = 0; i < *ipAdEntAddr_num; i++)
		{
			if (StorageTmp->ipAdEntAddr == __ipAddrTable_idxs[i])				
			{
				break;
			}
		}	

		if (i == *ipAdEntAddr_num)
		{
			struct header_complex_index *hciptrn = ipAddrTableTemp->next;
			BC_PT_DBG_FUN(BC_MODULE_SNMP, "FREE!!!!\n");
			struct ipAddrTable_entry *StorageDel = header_complex_extract_entry(&ipAddrTableStorage, ipAddrTableTemp);
			__snmp_free_ipAddrTable_data(StorageDel);

			ipAddrTableTemp = hciptrn;
		}
		else
		{
			ipAddrTableTemp = ipAddrTableTemp->next;
		}
	}

	BC_PT_FUN_LEAVE(BC_MODULE_SNMP);
	return ret;
}


bc_boolean __snmp_ipAddrTable_update_dev(in_addr_t __ipAdEntAddr)
{
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);

	struct ipAddrTable_entry *StorageTmp = NULL;
	struct header_complex_index *ipAddrTableTemp = NULL;

	in_addr_t __ipAdEntAddr_tmp = 0;
	bc_int32 __update_count = 0;
	
	bc_int32 ipAdEntAddr_num;
	bc_int32 next_is_chk = TRUE;

	struct ipAddrTable_entry data_tmp[ipAddrTable_num];
	int data_cnt = 0;

	int i = 0;
	
	BC_PT_FUN_TAG(BC_MODULE_SNMP);

	if(snmp_is_update(&update_time))
	{
		if (!__snmp_ipAddrTable_index_update(&ipAdEntAddr_num))
		{
			BC_PT_DBG_CPL(BC_MODULE_SNMP, "__snmp_ipAddrTable_index_update() failed!\r\n");
			return FALSE;
		}

		ipAddrTableTemp = ipAddrTableStorage;
		while(ipAddrTableTemp)
		{
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			StorageTmp = (struct ipAddrTable_entry *)ipAddrTableTemp->data;

			__ipAdEntAddr_tmp = StorageTmp->ipAdEntAddr;
			BC_PT_DBG_FUN(BC_MODULE_SNMP, "__ipAdEntAddr_tmp:%d   __ipAdEntAddr:%d\n", __ipAdEntAddr_tmp, __ipAdEntAddr);

			BC_PT_DBG_FUN(BC_MODULE_SNMP, "next_is_chk=%d\n",next_is_chk);
			
			if((__ipAdEntAddr_tmp != __ipAdEntAddr) && (next_is_chk == TRUE))
			{
				ipAddrTableTemp = ipAddrTableTemp->next;			
			}
			else
			{
				BC_PT_FUN_TAG(BC_MODULE_SNMP);
				next_is_chk = FALSE;
				
				vir_api_get_data(data_tmp, &data_cnt);

				for(i=0; i<data_cnt; i++)
				{
					if(data_tmp[i].ipAdEntAddr == __ipAdEntAddr_tmp)
					{
						BC_PT_FUN_TAG(BC_MODULE_SNMP);
						BC_PT_DBG_FUN(BC_MODULE_SNMP, "__ipAdEntAddr_tmp1:%d   __ipAdEntAddr1:%d\n", __ipAdEntAddr_tmp, __ipAdEntAddr);
						memcpy(StorageTmp, data_tmp+i, sizeof(struct ipAddrTable_entry));
						break;
					}
				}
				#if 0
				printf("StorageTmp->ipAdEntAddr = %d\n", StorageTmp->ipAdEntAddr);
				printf("StorageTmp->fhSlotSeq = %d\n", StorageTmp->fhSlotSeq);
				printf("StorageTmp->fhSlotType = %s\n", StorageTmp->fhSlotType);
				printf("StorageTmp->fhSlotType = %s\n", StorageTmp->fhSlotType);
				printf("StorageTmp->fhSlotType = %s\n", StorageTmp->fhSlotType);
				#endif
				
				ipAddrTableTemp = ipAddrTableTemp->next;			

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
	SNMP_MEM_FREE(ipAddrTable_idxs);
	return TRUE;
}		




static bc_boolean __snmp_ipAddrTable_update(in_addr_t __ipAdEntAddr)
{
#ifdef SNMP_PRJ_SNMP_X86
		return __snmp_ipAddrTable_update_x86(__ipAdEntAddr);
#else
		return __snmp_ipAddrTable_update_dev(__ipAdEntAddr);
#endif
}


static unsigned char *__snmp_ipAddrTable_handler(struct variable *vp,
																		oid *name,
																		size_t *length,
																		int exact,
																		size_t *var_len,
																		WriteMethod **write_method)
{	
	struct ipAddrTable_entry *node = NULL;

	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	in_addr_t __ipAdEntAddr = 0;

	bc_char ipstr[256];
	
	memset(ipstr, 0, sizeof(ipstr));

	SNMP_NODE_OID_PT(name, *length);
	
	if (*length == IPADDRTABLE_OID_FULL_LEN)
	{
		BC_PT_FUN_TAG(BC_MODULE_SNMP);
		snprintf(ipstr, sizeof(ipstr), "%d.%d.%d.%d", name[*length - 4], name[*length - 3], name[*length - 2], name[*length - 1]);
		BC_PT_DBG_FUN(BC_MODULE_SNMP, "ipstr: %s\n", ipstr);
		
		__ipAdEntAddr = inet_addr(ipstr);
	}
	
	else if (*length < IPADDRTABLE_OID_FULL_LEN)
	{
		BC_PT_DBG_FUN(BC_MODULE_SNMP, "*length=%d\n",*(size_t *)length);
		__ipAdEntAddr = inet_addr("192.168.5.101");
	}
	BC_PT_DBG_FUN(BC_MODULE_SNMP, "__ipAdEntAddr: %d\n", __ipAdEntAddr);
	
	if(!__snmp_ipAddrTable_update(__ipAdEntAddr))
	{
		BC_PT_DBG_FUN(BC_MODULE_SNMP, "__snmp_ipAddrTable_update() failed!!\r\n");
		return NULL;
	}
	
	SNMP_HDL_HEADER_COMPLEX(ipAddrTableStorage, vp, name, length, exact, var_len, write_method, NULL, SNMP_TABLE_NO_ROW_STATUS);

	switch(vp->magic)
	{
		case COLUMN_IPADENTADDR:
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			*var_len = sizeof(node->ipAdEntAddr);
			return (u_char *)&node->ipAdEntAddr;
		case COLUMN_IPADENTIFINDEX:
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			*var_len = sizeof(node->ipAdEntIfIndex);
			return (u_char *)&node->ipAdEntIfIndex;
		case COLUMN_IPADENTNETMASK:
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			*var_len = sizeof(node->ipAdEntNetMask);
			return (u_char *)&node->ipAdEntNetMask;
		case COLUMN_IPADENTBCASTADDR:
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			*var_len = sizeof(long);
			ret_val = ntohl(node->ipAdEntBcastAddr) & 1;
			return (u_char *)&ret_val;
		case COLUMN_IPADENTREASMMAXSIZE:
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			*var_len = sizeof(node->ipAdEntReasmMaxSize);
			return (u_char *)&node->ipAdEntReasmMaxSize;
		default:
			BC_PT_DBG_FUN(BC_MODULE_SNMP, "colunm error!!\r\n");
	}
	return NULL;
}
#endif

void snmp_ipAddrTable_init(void)
{
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	
#if 0
	SNMP_REGISTER_MIB("ipAddrTable", ipAddrTable_variables, variable2, ipAddrTable_variables_oid);
#else
	init_ip();
#endif

//	init_interfaces();
//	init_ifXTable();
	SNMP_MIB_FFLUSH_INIT();

	BC_PT_FUN_LEAVE(BC_MODULE_SNMP);
}

#else

#if 1
/*
 *  IP MIB group implementation - ip.c
 *
 */

/* Portions of this file are subject to the following copyright(s).  See
 * the Net-SNMP's COPYING file for more details and other copyrights
 * that may apply:
 */
/*
 * Portions of this file are copyrighted by:
 * Copyright © 2003 Sun Microsystems, Inc. All rights reserved.
 * Use is subject to license terms specified in the COPYING file
 * distributed with the Net-SNMP package.
 */

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-features.h>

#if defined(NETSNMP_IFNET_NEEDS_KERNEL) && !defined(_KERNEL)
#define _KERNEL 1
#define _I_DEFINED_KERNEL
#endif
#if HAVE_SYS_PARAM_H
#include <sys/param.h>
#endif
#if HAVE_UNISTD_H
#ifdef irix6
#define _STANDALONE 1
#endif
#include <unistd.h>
#endif
#if HAVE_SYS_SOCKET_H
#include <sys/socket.h>
#endif

#if HAVE_STRING_H
#include <string.h>
#else
#include <strings.h>
#endif
#include <sys/types.h>
#if HAVE_SYS_SYSCTL_H
#ifdef _I_DEFINED_KERNEL
#undef _KERNEL
#endif
#include <sys/sysctl.h>
#ifdef _I_DEFINED_KERNEL
#define _KERNEL 1
#endif
#endif
#if HAVE_SYS_SYSMP_H
#include <sys/sysmp.h>
#endif
#if HAVE_SYS_TCPIPSTATS_H
#include <sys/tcpipstats.h>
#endif
#if HAVE_NETINET_IN_H
#include <netinet/in.h>
#endif
#if HAVE_NET_IF_H
#include <net/if.h>
#endif
#if HAVE_NET_IF_VAR_H
#include <net/if_var.h>
#endif
#ifdef _I_DEFINED_KERNEL
#undef _KERNEL
#endif
#if HAVE_NETINET_IN_SYSTM_H
#include <netinet/in_systm.h>
#endif
#if HAVE_SYS_HASHING_H
#include <sys/hashing.h>
#endif
#if HAVE_NETINET_IN_VAR_H
#include <netinet/in_var.h>
#endif
#if HAVE_NETINET_IP_H
#include <netinet/ip.h>
#endif
#if HAVE_NETINET_IP_VAR_H
#include <netinet/ip_var.h>
#endif
#if HAVE_INET_MIB2_H
#include <inet/mib2.h>
#endif
#if HAVE_SYS_STREAM_H
#include <sys/stream.h>
#endif
#if HAVE_NET_ROUTE_H
#include <net/route.h>
#endif
#if HAVE_SYSLOG_H
#include <syslog.h>
#endif
#if HAVE_SYS_IOCTL_H
#include <sys/ioctl.h>
#endif

#if defined(MIB_IPCOUNTER_SYMBOL) || defined(hpux11)
#include <sys/mib.h>
#include <netinet/mib_kern.h>
#endif                          /* MIB_IPCOUNTER_SYMBOL || hpux11 */

#ifdef solaris2
#include "kernel_sunos5.h"
#else
//#include "kernel.h"
#endif

#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include <net-snmp/agent/auto_nlist.h>
#include <net-snmp/data_access/interface.h>

//#include "ip.h"
//#include "interfaces.h"

#ifdef cygwin
#include <windows.h>
#endif

struct ip_mib {
    unsigned long   ipForwarding;
    unsigned long   ipDefaultTTL;
    unsigned long   ipInReceives;
    unsigned long   ipInHdrErrors;
    unsigned long   ipInAddrErrors;
    unsigned long   ipForwDatagrams;
    unsigned long   ipInUnknownProtos;
    unsigned long   ipInDiscards;
    unsigned long   ipInDelivers;
    unsigned long   ipOutRequests;
    unsigned long   ipOutDiscards;
    unsigned long   ipOutNoRoutes;
    unsigned long   ipReasmTimeout;
    unsigned long   ipReasmReqds;
    unsigned long   ipReasmOKs;
    unsigned long   ipReasmFails;
    unsigned long   ipFragOKs;
    unsigned long   ipFragFails;
    unsigned long   ipFragCreates;
    unsigned long   ipRoutingDiscards;
};

netsnmp_feature_require(interface_legacy)

        /*********************
	 *
	 *  Kernel & interface information,
	 *   and internal forward declarations
	 *
	 *********************/

        /*********************
	 *
	 *  Initialisation & common implementation functions
	 *
	 *********************/

        /*********************
	 *
	 *  System specific implementation functions
	 *
	 *********************/

#if !defined (WIN32) && !defined (cygwin)

#if !defined(NETSNMP_CAN_USE_SYSCTL) || !defined(IPCTL_STATS)
#ifndef solaris2

#if defined(freebsd2) || defined(hpux11) || defined(linux)
static void     Address_Scan_Init(void);
#ifdef freebsd2
static int      Address_Scan_Next(short *, struct in_ifaddr *);
#else
#ifdef linux
static struct ifconf ifc;
static int      Address_Scan_Next(short *, struct ifnet *);
#else
static int      Address_Scan_Next(short *, mib_ipAdEnt *);
#endif
#endif
#endif

/*
 * var_ipAddrEntry(...
 * Arguments:
 * vp     IN      - pointer to variable entry that points here
 * name    IN/OUT  - IN/name requested, OUT/name found
 * length  IN/OUT  - length of IN/OUT oid's 
 * exact   IN      - TRUE if an exact match was requested
 * var_len OUT     - length of variable or 0 if function returned
 * write_method
 * 
 */

u_char         *
var_ipAddrEntry(struct variable *vp,
                oid * name,
                size_t * length,
                int exact, size_t * var_len, WriteMethod ** write_method)
{
    /*
     * object identifier is of form:
     * 1.3.6.1.2.1.4.20.1.?.A.B.C.D,  where A.B.C.D is IP address.
     * IPADDR starts at offset 10.
     */
    oid             lowest[14];
    oid             current[14], *op;
    u_char         *cp;
    int             lowinterface = 0;
#ifndef freebsd2
    short           interface;
#endif
#ifdef hpux11
    static mib_ipAdEnt in_ifaddr, lowin_ifaddr;
#else
#if !defined(linux) && !defined(sunV3)
    static struct in_ifaddr in_ifaddr, lowin_ifaddr;
#else
    static struct ifnet lowin_ifnet;
#endif
    static struct ifnet ifnet;
#endif                          /* hpux11 */
    static in_addr_t	addr_ret;

    /*
     * fill in object part of name for current (less sizeof instance part) 
     */

    memcpy((char *) current, (char *) vp->name,
           (int) vp->namelen * sizeof(oid));

#if !defined(freebsd2) && !defined(hpux11) && !defined(linux)
    Interface_Scan_Init();
#else
    Address_Scan_Init();
#endif
    for (;;) {

#if !defined(freebsd2) && !defined(hpux11) && !defined(linux)
        if (Interface_Scan_Next(&interface, NULL, &ifnet, &in_ifaddr) == 0)
            break;
#ifdef HAVE_STRUCT_IFNET_IF_ADDRLIST
        if (ifnet.if_addrlist == 0)
            continue;           /* No address found for interface */
#endif
#else                           /* !freebsd2 && !hpux11 */
#if defined(linux)
        if (Address_Scan_Next(&interface, &ifnet) == 0)
            break;
#else
        if (Address_Scan_Next(&interface, &in_ifaddr) == 0)
            break;
#endif
#endif                          /* !freebsd2 && !hpux11 && !linux */

#ifdef hpux11
        cp = (u_char *) & in_ifaddr.Addr;
#elif defined(linux) || defined(sunV3)
        cp = (u_char *) & (((struct sockaddr_in *) &(ifnet.if_addr))->
                           sin_addr.s_addr);
#else
        cp = (u_char *) & (((struct sockaddr_in *) &(in_ifaddr.ia_addr))->
                           sin_addr.s_addr);
#endif

        op = current + 10;
        *op++ = *cp++;
        *op++ = *cp++;
        *op++ = *cp++;
        *op++ = *cp++;
        if (exact) {
            if (snmp_oid_compare(current, 14, name, *length) == 0) {
                memcpy((char *) lowest, (char *) current,
                       14 * sizeof(oid));
                lowinterface = interface;
#if defined(linux) || defined(sunV3)
                lowin_ifnet = ifnet;
#else
                lowin_ifaddr = in_ifaddr;
#endif
                break;          /* no need to search further */
            }
        } else {
            if ((snmp_oid_compare(current, 14, name, *length) > 0) &&
                (!lowinterface
                 || (snmp_oid_compare(current, 14, lowest, 14) < 0))) {
                /*
                 * if new one is greater than input and closer to input than
                 * previous lowest, save this one as the "next" one.
                 */
                lowinterface = interface;
#if defined(linux) || defined(sunV3)
                lowin_ifnet = ifnet;
#else
                lowin_ifaddr = in_ifaddr;
#endif
                memcpy((char *) lowest, (char *) current,
                       14 * sizeof(oid));
            }
        }
    }

#if defined(linux)
    SNMP_FREE(ifc.ifc_buf);
#endif

    if (!lowinterface)
        return (NULL);
    memcpy((char *) name, (char *) lowest, 14 * sizeof(oid));
    *length = 14;
    *write_method = (WriteMethod*)0;
    *var_len = sizeof(long_return);
    switch (vp->magic) {
    case IPADADDR:
    	*var_len = sizeof(addr_ret);
#ifdef hpux11
        addr_ret = lowin_ifaddr.Addr;
        return (u_char *) & addr_ret;
#elif defined(linux) || defined(sunV3)
        return (u_char *) & ((struct sockaddr_in *) &lowin_ifnet.if_addr)->
            sin_addr.s_addr;
#else
        return (u_char *) & ((struct sockaddr_in *) &lowin_ifaddr.
                             ia_addr)->sin_addr.s_addr;
#endif
    case IPADIFINDEX:
        long_return = lowinterface;
        return (u_char *) & long_return;
    case IPADNETMASK:
        *var_len = sizeof(addr_ret);
#ifdef hpux11
        addr_ret = lowin_ifaddr.NetMask;
        return (u_char *) & addr_ret;
#elif defined(linux)
        return (u_char *) & ((struct sockaddr_in *) &lowin_ifnet.
                             ia_subnetmask)->sin_addr.s_addr;
#elif !defined(sunV3)
        addr_ret = lowin_ifaddr.ia_subnetmask;
        return (u_char *) & addr_ret;
#endif
    case IPADBCASTADDR:
#ifdef hpux11
        long_return = lowin_ifaddr.BcastAddr & 1;
#elif defined(linux) || defined(sunV3)
        *var_len = sizeof(long_return);
        long_return =
            ntohl(((struct sockaddr_in *) &lowin_ifnet.ifu_broadaddr)->
                  sin_addr.s_addr) & 1;
#elif defined(netbsd1)
        long_return =
            ((struct sockaddr_in *) &lowin_ifaddr.ia_broadaddr)->sin_addr.
            s_addr & 1;
#else
        long_return =
            ntohl(((struct sockaddr_in *) &lowin_ifaddr.ia_broadaddr)->
                  sin_addr.s_addr) & 1;
#endif
        return (u_char *) & long_return;
    case IPADREASMMAX:
#ifdef hpux11
        long_return = lowin_ifaddr.ReasmMaxSize;
        return (u_char *) & long_return;
#elif defined(NETSNMP_NO_DUMMY_VALUES)
        return NULL;
#else
        long_return = -1;
        return (u_char *) & long_return;
#endif
    default:
        DEBUGMSGTL(("snmpd", "unknown sub-id %d in var_ipAddrEntry\n",
                    vp->magic));
    }
    return NULL;
}

#ifdef freebsd2
static struct in_ifaddr *in_ifaddraddr = NULL;

static void
Address_Scan_Init(void)
{
    int rc = auto_nlist(IFADDR_SYMBOL, (char *) &in_ifaddraddr,
               sizeof(in_ifaddraddr));
    if (0 == rc)
        in_ifaddraddr = NULL;
}

/*
 * NB: Index is the number of the corresponding interface, not of the address 
 */
static int
Address_Scan_Next(Index, Retin_ifaddr)
     short          *Index;
     struct in_ifaddr *Retin_ifaddr;
{
    struct in_ifaddr in_ifaddr;
    struct ifnet    ifnet, *ifnetaddr;  /* NOTA: same name as another one */
    short           iindex = 1;

    while (in_ifaddraddr) {
        /*
         *      Get the "in_ifaddr" structure
         */
        if (!NETSNMP_KLOOKUP(in_ifaddraddr, (char *) &in_ifaddr, sizeof in_ifaddr)) {
            DEBUGMSGTL(("mibII/ip:Address_Scan_Next", "klookup failed\n"));
            return 0;
        }

        in_ifaddraddr = in_ifaddr.ia_next;

        if (Retin_ifaddr)
            *Retin_ifaddr = in_ifaddr;

        /*
         * Now, more difficult, find the index of the interface to which
         * this address belongs
         */

        auto_nlist(IFNET_SYMBOL, (char *) &ifnetaddr, sizeof(ifnetaddr));
        while (ifnetaddr && ifnetaddr != in_ifaddr.ia_ifp) {
            if (!NETSNMP_KLOOKUP(ifnetaddr, (char *) &ifnet, sizeof ifnet)) {
                DEBUGMSGTL(("mibII/ip:Address_Scan_Next", "klookup failed\n"));
                return 0;
            }
            ifnetaddr = ifnet.if_next;
            iindex++;
        }

        /*
         * XXX - might not find it? 
         */

        if (Index)
            *Index = iindex;

        return (1);             /* DONE */
    }
    return (0);                 /* EOF */
}

#elif defined(hpux11)

static int      iptab_size, iptab_current;
static mib_ipAdEnt *ip = (mib_ipAdEnt *) 0;

static void
Address_Scan_Init(void)
{
    int             fd;
    struct nmparms  p;
    int             val;
    unsigned int    ulen;
    int             ret;

    if (ip)
        free(ip);
    ip = (mib_ipAdEnt *) 0;
    iptab_size = 0;

    if ((fd = open_mib("/dev/ip", O_RDONLY, 0, NM_ASYNC_OFF)) >= 0) {
        p.objid = ID_ipAddrNumEnt;
        p.buffer = (void *) &val;
        ulen = sizeof(int);
        p.len = &ulen;
        if ((ret = get_mib_info(fd, &p)) == 0)
            iptab_size = val;

        if (iptab_size > 0) {
            ulen = (unsigned) iptab_size *sizeof(mib_ipAdEnt);
            ip = (mib_ipAdEnt *) malloc(ulen);
            p.objid = ID_ipAddrTable;
            p.buffer = (void *) ip;
            p.len = &ulen;
            if ((ret = get_mib_info(fd, &p)) < 0)
                iptab_size = 0;
        }

        close_mib(fd);
    }

    iptab_current = 0;
}

/*
 * NB: Index is the number of the corresponding interface, not of the address 
 */
static int
Address_Scan_Next(Index, Retin_ifaddr)
     short          *Index;
     mib_ipAdEnt    *Retin_ifaddr;
{
    if (iptab_current < iptab_size) {
        /*
         * copy values 
         */
        *Index = ip[iptab_current].IfIndex;
        *Retin_ifaddr = ip[iptab_current];
        /*
         * increment to point to next entry 
         */
        iptab_current++;
        /*
         * return success 
         */
        return (1);
    }

    /*
     * return done 
     */
    return (0);
}

#elif defined(linux)
static struct ifreq *ifr;
static int ifr_counter;

static void
Address_Scan_Init(void)
{
    int num_interfaces = 0;
    int fd;

    /* get info about all interfaces */

    ifc.ifc_len = 0;
    SNMP_FREE(ifc.ifc_buf);
    ifr_counter = 0;

    do
    {
	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
	    DEBUGMSGTL(("snmpd", "socket open failure in Address_Scan_Init\n"));
	    return;
	}
	num_interfaces += 16;

	ifc.ifc_len = sizeof(struct ifreq) * num_interfaces;
	ifc.ifc_buf = (char*) realloc(ifc.ifc_buf, ifc.ifc_len);
	
	    if (ioctl(fd, SIOCGIFCONF, &ifc) < 0)
	    {
		ifr=NULL;
		close(fd);
	   	return;
	    }
	    close(fd);
    }
    while (ifc.ifc_len >= (sizeof(struct ifreq) * num_interfaces));
    
    ifr = ifc.ifc_req;
    close(fd);
}

/*
 * NB: Index is the number of the corresponding interface, not of the address 
 */
static int
Address_Scan_Next(short *Index, struct ifnet *Retifnet)
{
    struct ifnet   ifnet_store;
    int fd;
    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
	DEBUGMSGTL(("snmpd", "socket open failure in Address_Scan_Next\n"));
	return(0);
    }

    while (ifr) {
	
	ifnet_store.if_addr = ifr->ifr_addr;

        if (Retifnet)
	{
	    Retifnet->if_addr = ifr->ifr_addr;
	    
	    if (ioctl(fd, SIOCGIFBRDADDR, ifr) < 0)
	    {
		memset((char *) &Retifnet->ifu_broadaddr, 0, sizeof(Retifnet->ifu_broadaddr));
	    }
	    else
		Retifnet->ifu_broadaddr = ifr->ifr_broadaddr;

	    ifr->ifr_addr = Retifnet->if_addr;
	    if (ioctl(fd, SIOCGIFNETMASK, ifr) < 0)
	    {
		memset((char *) &Retifnet->ia_subnetmask, 0, sizeof(Retifnet->ia_subnetmask));
	    }
	    else
		Retifnet->ia_subnetmask = ifr->ifr_netmask;

	}

        if (Index)
	{
	    ifr->ifr_addr = ifnet_store.if_addr;
            *Index = netsnmp_access_interface_index_find(ifr->ifr_name);
	}
	
	ifr++;
	ifr_counter+=sizeof(struct ifreq);
	if (ifr_counter >= ifc.ifc_len)
	{
	    ifr = NULL;	/* beyond the end */
	}

        close(fd);
        return (1);             /* DONE */
    }
    close(fd);
    return (0);                 /* EOF */
}

#endif                          /* freebsd,hpux11,linux */

#else                           /* solaris2 */


static int
IP_Cmp(void *addr, void *ep)
{
    if (((mib2_ipAddrEntry_t *) ep)->ipAdEntAddr == *(IpAddress *) addr)
        return (0);
    else
        return (1);
}

u_char         *
var_ipAddrEntry(struct variable * vp,
                oid * name,
                size_t * length,
                int exact, size_t * var_len, WriteMethod ** write_method)
{
    /*
     * object identifier is of form:
     * 1.3.6.1.2.1.4.20.1.?.A.B.C.D,  where A.B.C.D is IP address.
     * IPADDR starts at offset 10.
     */
#define IP_ADDRNAME_LENGTH	14
#define IP_ADDRINDEX_OFF	10
    oid             lowest[IP_ADDRNAME_LENGTH];
    oid             current[IP_ADDRNAME_LENGTH], *op;
    u_char         *cp;
    IpAddress       NextAddr;
    mib2_ipAddrEntry_t entry;
    static mib2_ipAddrEntry_t Lowentry;
    int             Found = 0;
    req_e           req_type;
    static in_addr_t addr_ret;

    /*
     * fill in object part of name for current (less sizeof instance part) 
     */

    DEBUGMSGTL(("mibII/ip", "var_ipAddrEntry: "));
    DEBUGMSGOID(("mibII/ip", name, *length));
    DEBUGMSG(("mibII/ip", " %d\n", exact));

    memset(&Lowentry, 0, sizeof(Lowentry));
    memcpy((char *) current, (char *) vp->name,
           (int) vp->namelen * sizeof(oid));
    if (*length == IP_ADDRNAME_LENGTH)  /* Assume that the input name is the lowest */
        memcpy((char *) lowest, (char *) name,
               IP_ADDRNAME_LENGTH * sizeof(oid));
    else
	lowest[0] = 0xff;
    for (NextAddr = (u_long) - 1, req_type = GET_FIRST;;
         NextAddr = entry.ipAdEntAddr, req_type = GET_NEXT) {
        if (getMibstat
            (MIB_IP_ADDR, &entry, sizeof(mib2_ipAddrEntry_t), req_type,
             &IP_Cmp, &NextAddr) != 0)
            break;
        COPY_IPADDR(cp, (u_char *) & entry.ipAdEntAddr, op,
                    current + IP_ADDRINDEX_OFF);
        if (exact) {
            if (snmp_oid_compare
                (current, IP_ADDRNAME_LENGTH, name, *length) == 0) {
                memcpy((char *) lowest, (char *) current,
                       IP_ADDRNAME_LENGTH * sizeof(oid));
                Lowentry = entry;
                Found++;
                break;          /* no need to search further */
            }
        } else {
            if ((snmp_oid_compare
                 (current, IP_ADDRNAME_LENGTH, name, *length) > 0)
                && (((NextAddr == (u_long) - 1))
                    ||
                    (snmp_oid_compare
                     (current, IP_ADDRNAME_LENGTH, lowest,
                      IP_ADDRNAME_LENGTH) < 0)
                    ||
                    (snmp_oid_compare
                     (name, *length, lowest, IP_ADDRNAME_LENGTH) == 0))) {
                /*
                 * if new one is greater than input and closer to input than
                 * previous lowest, and is not equal to it, save this one as the "next" one.
                 */
                Lowentry = entry;
                Found++;
                memcpy((char *) lowest, (char *) current,
                       IP_ADDRNAME_LENGTH * sizeof(oid));
            }
        }
    }
    DEBUGMSGTL(("mibII/ip", "... Found = %d\n", Found));
    if (Found == 0)
        return (NULL);
    memcpy((char *) name, (char *) lowest,
           IP_ADDRNAME_LENGTH * sizeof(oid));
    *length = IP_ADDRNAME_LENGTH;
    *write_method = 0;
    *var_len = sizeof(long_return);
    switch (vp->magic) {
    case IPADADDR:
	*var_len = sizeof(addr_ret);
        addr_ret = Lowentry.ipAdEntAddr;
        return (u_char *) & addr_ret;
    case IPADIFINDEX:
#ifdef NETSNMP_INCLUDE_IFTABLE_REWRITES
        Lowentry.ipAdEntIfIndex.o_bytes[Lowentry.ipAdEntIfIndex.o_length] = '\0';
        long_return =
            netsnmp_access_interface_index_find(Lowentry.
                                                ipAdEntIfIndex.o_bytes);
#else
        long_return =
           Interface_Index_By_Name(Lowentry.ipAdEntIfIndex.o_bytes,
                                   Lowentry.ipAdEntIfIndex.o_length);
#endif
        return (u_char *) & long_return;
    case IPADNETMASK:
	*var_len = sizeof(addr_ret);
        addr_ret = Lowentry.ipAdEntNetMask;
        return (u_char *) & addr_ret;
    case IPADBCASTADDR:
	long_return = Lowentry.ipAdEntBcastAddr;
	return (u_char *) & long_return;
    case IPADREASMMAX:
	long_return = Lowentry.ipAdEntReasmMaxSize;
	return (u_char *) & long_return;
    default:
        DEBUGMSGTL(("snmpd", "unknown sub-id %d in var_ipAddrEntry\n",
                    vp->magic));
    }
    return NULL;
}

#endif                          /* solaris2 */



        /*********************
	 *
	 *  Internal implementation functions
	 *
	 *********************/


#else                           /* NETSNMP_CAN_USE_SYSCTL && IPCTL_STATS */

/*
 * Ideally, this would be combined with the code in interfaces.c.
 * Even separate, it's still better than what went before.
 */
struct iflist {
    int             flags;
    int             index;
    struct in_addr  addr;
    struct in_addr  mask;
    struct in_addr  bcast;
};
static struct iflist *ifs;
static int      nifs;

static void
get_iflist(void)
{
    int             naddrs, bit;
    static int      mib[6]
    = { CTL_NET, PF_ROUTE, 0, AF_INET, NET_RT_IFLIST, 0 };
    char           *cp, *ifbuf;
    size_t          len;
    struct rt_msghdr *rtm;
    struct if_msghdr *ifm;
    struct ifa_msghdr *ifam;
    struct sockaddr *sa;
    int             flags;

    naddrs = 0;
    if (ifs)
        free(ifs);
    ifs = 0;
    nifs = 0;
    len = 0;
    if (sysctl(mib, 6, 0, &len, 0, 0) < 0)
        return;

    ifbuf = malloc(len);
    if (ifbuf == 0)
        return;
    if (sysctl(mib, 6, ifbuf, &len, 0, 0) < 0) {
        syslog(LOG_WARNING, "sysctl net-route-iflist: %m");
        free(ifbuf);
        return;
    }

  loop:
    cp = ifbuf;
    while (cp < &ifbuf[len]) {
        int             gotaddr;

        gotaddr = 0;
        rtm = (struct rt_msghdr *) cp;
        if (rtm->rtm_version != RTM_VERSION || rtm->rtm_type != RTM_IFINFO) {
            free(ifs);
            ifs = 0;
            nifs = 0;
            free(ifbuf);
            return;
        }
        ifm = (struct if_msghdr *) rtm;
        flags = ifm->ifm_flags;
        cp += ifm->ifm_msglen;
        rtm = (struct rt_msghdr *) cp;
        while (cp < &ifbuf[len] && rtm->rtm_type == RTM_NEWADDR) {
            ifam = (struct ifa_msghdr *) rtm;
            cp += sizeof(*ifam);
            /*
             * from route.c 
             */
#define ROUND(a) \
        ((a) > 0 ? (1 + (((a) - 1) | (sizeof(long) - 1))) : sizeof(long))
            for (bit = 1; bit && cp < &ifbuf[len]; bit <<= 1) {
                if (!(ifam->ifam_addrs & bit))
                    continue;
                sa = (struct sockaddr *) cp;
                cp += ROUND(sa->sa_len);

                /*
                 * Netmasks are returned as bit
                 * strings of type AF_UNSPEC.  The
                 * others are pretty ok.
                 */
                if (bit == RTA_IFA) {
#define satosin(sa) ((struct sockaddr_in *)(sa))
                    if (ifs) {
                        ifs[naddrs].addr = satosin(sa)->sin_addr;
                        ifs[naddrs].index = ifam->ifam_index;
                        ifs[naddrs].flags = flags;
                    }
                    gotaddr = 1;
                } else if (bit == RTA_NETMASK) {
                    if (ifs)
                        ifs[naddrs].mask = satosin(sa)->sin_addr;
                } else if (bit == RTA_BRD) {
                    if (ifs)
                        ifs[naddrs].bcast = satosin(sa)->sin_addr;
                }
            }
            if (gotaddr)
                naddrs++;
            cp = (char *) rtm + rtm->rtm_msglen;
            rtm = (struct rt_msghdr *) cp;
        }
    }
    if (ifs) {
        nifs = naddrs;
        free(ifbuf);
        return;
    }
    ifs = malloc(naddrs * sizeof(*ifs));
    if (ifs == 0) {
        free(ifbuf);
        return;
    }
    naddrs = 0;
    goto loop;
}

u_char         *
var_ipAddrEntry(struct variable *vp,
                oid * name,
                size_t * length,
                int exact, size_t * var_len, WriteMethod ** write_method)
{
    /*
     * object identifier is of form:
     * 1.3.6.1.2.1.4.20.1.?.A.B.C.D,  where A.B.C.D is IP address.
     * IPADDR starts at offset 10.
     */
    oid             lowest[14];
    oid             current[14], *op;
    u_char         *cp;
    int             lowinterface = -1;
    int             i;
    static in_addr_t	addr_ret;
    
    /*
     * fill in object part of name for current (less sizeof instance part) 
     */
    memcpy(current, vp->name, (int) vp->namelen * sizeof(oid));

    /*
     * Get interface table from kernel.
     */
    get_iflist();

    for (i = 0; i < nifs; i++) {
        op = &current[10];
        cp = (u_char *) & ifs[i].addr;
        *op++ = *cp++;
        *op++ = *cp++;
        *op++ = *cp++;
        *op++ = *cp++;
        if (exact) {
            if (snmp_oid_compare(current, 14, name, *length) == 0) {
                memcpy(lowest, current, 14 * sizeof(oid));
                lowinterface = i;
                break;          /* no need to search further */
            }
        } else {
            if ((snmp_oid_compare(current, 14, name, *length) > 0) &&
                (lowinterface < 0
                 || (snmp_oid_compare(current, 14, lowest, 14) < 0))) {
                /*
                 * if new one is greater than input
                 * and closer to input than previous
                 * lowest, save this one as the "next"
                 * one.  
                 */
                lowinterface = i;
                memcpy(lowest, current, 14 * sizeof(oid));
            }
        }
    }

    if (lowinterface < 0)
        return NULL;
    i = lowinterface;
    memcpy(name, lowest, 14 * sizeof(oid));
    *length = 14;
    *write_method = 0;
    *var_len = sizeof(long_return);
    switch (vp->magic) {
    case IPADADDR:
        *var_len = sizeof(addr_ret);
        addr_ret = ifs[i].addr.s_addr;
        return (u_char *) & addr_ret;

    case IPADIFINDEX:
        long_return = ifs[i].index;
        return (u_char *) & long_return;

    case IPADNETMASK:
        *var_len = sizeof(addr_ret);
        addr_ret = ifs[i].mask.s_addr;
        return (u_char *) & addr_ret;

    case IPADBCASTADDR:
        long_return = ntohl(ifs[i].bcast.s_addr) & 1;
        return (u_char *) & long_return;

    case IPADREASMMAX:
#if NETSNMP_NO_DUMMY_VALUES
        return NULL;
#else
        long_return = -1;
        return (u_char *) & long_return;
#endif

    default:
        DEBUGMSGTL(("snmpd", "unknown sub-id %d in var_ipAddrEntry\n",
                    vp->magic));
    }
    return NULL;
}

#endif                          /* NETSNMP_CAN_USE_SYSCTL && IPCTL_STATS */

#elif defined(HAVE_IPHLPAPI_H)  /* WIN32 cygwin */
#include <iphlpapi.h>
u_char         *
var_ipAddrEntry(struct variable *vp,
                oid * name,
                size_t * length,
                int exact, size_t * var_len, WriteMethod ** write_method)
{
    /*
     * object identifier is of form:
     * 1.3.6.1.2.1.4.20.1.?.A.B.C.D,  where A.B.C.D is IP address.
     * IPADDR starts at offset 10.
     */
    oid             lowest[14];
    oid             current[14], *op;
    u_char         *cp;
    int             lowinterface = -1;
    int             i;
    PMIB_IPADDRTABLE pIpAddrTable = NULL;
    DWORD           status = NO_ERROR;
    DWORD           statusRetry = NO_ERROR;
    DWORD           dwActualSize = 0;
    void           *result = NULL;
    static in_addr_t 	addr_ret;
    
    /*
     * fill in object part of name for current (less sizeof instance part) 
     */
    memcpy(current, vp->name, (int) vp->namelen * sizeof(oid));

    /*
     * Get interface table from kernel.
     */
    status = GetIpAddrTable(pIpAddrTable, &dwActualSize, TRUE);
    if (status == ERROR_INSUFFICIENT_BUFFER) {
        pIpAddrTable = (PMIB_IPADDRTABLE) malloc(dwActualSize);
        if (pIpAddrTable != NULL) {
            statusRetry =
                GetIpAddrTable(pIpAddrTable, &dwActualSize, TRUE);
        }
    }

    if (statusRetry == NO_ERROR || status == NO_ERROR) {

        for (i = 0; i < (int) pIpAddrTable->dwNumEntries; ++i) {
            op = &current[10];
            cp = (u_char *) & pIpAddrTable->table[i].dwAddr;
            *op++ = *cp++;
            *op++ = *cp++;
            *op++ = *cp++;
            *op++ = *cp++;
            if (exact) {
                if (snmp_oid_compare(current, 14, name, *length) == 0) {
                    memcpy(lowest, current, 14 * sizeof(oid));
                    lowinterface = i;
                    break;      /* no need to search further */
                }
            } else {
                if (snmp_oid_compare(current, 14, name, *length) > 0) {
                    lowinterface = i;
                    memcpy(lowest, current, 14 * sizeof(oid));
                    break;      /* Since the table is sorted, no need to search further  */
                }
            }
        }
    }

    if (lowinterface < 0)
        goto out;

    i = lowinterface;
    memcpy(name, lowest, 14 * sizeof(oid));
    *length = 14;
    *write_method = 0;
    switch (vp->magic) {
    case IPADADDR:
        *var_len = sizeof(addr_ret);
        addr_ret = pIpAddrTable->table[i].dwAddr;
        result = &addr_ret;
        break;

    case IPADIFINDEX:
        *var_len = sizeof(long_return);
        long_return = pIpAddrTable->table[i].dwIndex;
        result = &long_return;
        break;

    case IPADNETMASK:
        *var_len = sizeof(addr_ret);
        addr_ret = pIpAddrTable->table[i].dwMask;
        result = &addr_ret;
        break;

    case IPADBCASTADDR:
        *var_len = sizeof(long_return);
        long_return = pIpAddrTable->table[i].dwBCastAddr;
        result = &long_return;
        break;

    case IPADREASMMAX:
        *var_len = sizeof(long_return);
        long_return = pIpAddrTable->table[i].dwReasmSize;
        result = &long_return;
        break;

    default:
        DEBUGMSGTL(("snmpd", "unknown sub-id %d in var_ipAddrEntry\n",
                    vp->magic));
        break;
    }

out:
    free(pIpAddrTable);
    return result;
}
#endif                          /* WIN32 cygwin */

#endif

#if 1
/*
 *  IP MIB group implementation - ip.c
 *
 */

#include <net-snmp/net-snmp-config.h>
//#include "mibII_common.h"

#if HAVE_SYS_HASHING_H
#include <sys/hashing.h>
#endif
#if HAVE_NETINET_IN_VAR_H
#include <netinet/in_var.h>
#endif
#if HAVE_SYSLOG_H
#include <syslog.h>
#endif

#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include <net-snmp/agent/auto_nlist.h>
#include <net-snmp/agent/sysORTable.h>

//#include "util_funcs/MIB_STATS_CACHE_TIMEOUT.h"
//#include "ip.h"
////////////////////////////////////////////////////#include "ipAddr.h"
/*
 *  Template MIB group interface - ipAddr.h
 *
 */
#ifndef _MIBGROUP_IPADDR_H
#define _MIBGROUP_IPADDR_H

#if !defined(NETSNMP_ENABLE_MFD_REWRITES)
config_require(mibII/ip)
#endif

     extern snmp_find_var_callback var_ipAddrEntry;

#endif                          /* _MIBGROUP_IPADDR_H */

////////////////////#include "interfaces.h"
/*
 *  Interfaces MIB group interface - interfaces.h
 *
 */
#ifndef _MIBGROUP_INTERFACES_H
#define _MIBGROUP_INTERFACES_H

/***********************************************************************
 * configure macros
 */
config_require(util_funcs/header_generic)

/*
 * conflicts with the new MFD rewrite
 */
config_exclude(if-mib/ifTable/ifTable)

#if !defined(WIN32) && !defined(cygwin)
config_require(if-mib/data_access/interface)
#endif

config_arch_require(solaris2, kernel_sunos5)
/*
 * need get_address in var_route for some platforms (USE_SYSCTL_IFLIST).
 * Not sure if that can be translated into a config_arch_require, so be
 * indiscriminate for now.
 */
config_require(mibII/var_route)

/***********************************************************************
 */
#ifndef USING_IF_MIB_IFTABLE_MODULE
#ifdef hpux11
#include <sys/mib.h>
#else
     struct in_ifaddr;
     struct ifnet;
#endif

     int             Interface_Scan_Get_Count(void);
     int             Interface_Index_By_Name(char *, int);
     void            Interface_Scan_Init(void);
#if defined(linux) || defined(sunV3)
     struct in_ifaddr {
         int             dummy;
     };
#endif
#if defined(hpux11)
     int             Interface_Scan_Next(short *, char *, nmapi_phystat *);
     int             Interface_Scan_NextInt(int *, char *, nmapi_phystat *);
#else
     int             Interface_Scan_Next(short *, char *, struct ifnet *,
                                         struct in_ifaddr *);
     int             Interface_Scan_NextInt(int *, char *, struct ifnet *,
                                         struct in_ifaddr *);
#endif

     void            init_interfaces(void);
     extern snmp_find_var_callback var_interfaces;
     extern snmp_find_var_callback var_ifEntry;

#endif /* USING_IF_MIB_IFTABLE_MODULE */

#define NETSNMP_IFNUMBER        0
#define NETSNMP_IFINDEX         1
#define NETSNMP_IFDESCR         2
#define NETSNMP_IFTYPE          3
#define NETSNMP_IFMTU           4
#define NETSNMP_IFSPEED         5
#define NETSNMP_IFPHYSADDRESS   6
#define NETSNMP_IFADMINSTATUS   7
#define NETSNMP_IFOPERSTATUS    8
#define NETSNMP_IFLASTCHANGE    9
#define NETSNMP_IFINOCTETS      10
#define NETSNMP_IFINUCASTPKTS   11
#define NETSNMP_IFINNUCASTPKTS  12
#define NETSNMP_IFINDISCARDS    13
#define NETSNMP_IFINERRORS      14
#define NETSNMP_IFINUNKNOWNPROTOS 15
#define NETSNMP_IFOUTOCTETS     16
#define NETSNMP_IFOUTUCASTPKTS  17
#define NETSNMP_IFOUTNUCASTPKTS 18
#define NETSNMP_IFOUTDISCARDS   19
#define NETSNMP_IFOUTERRORS     20
#define NETSNMP_IFOUTQLEN       21
#define NETSNMP_IFSPECIFIC      22

#ifdef linux
/*
 * this struct ifnet is cloned from the generic type and somewhat modified.
 * it will not work for other un*x'es...
 */

     struct ifnet {
         char           *if_name;       /* name, e.g. ``en'' or ``lo'' */
         char           *if_unit;       /* sub-unit for lower level driver */
         short           if_mtu;        /* maximum transmission unit */
         short           if_flags;      /* up/down, broadcast, etc. */
         int             if_metric;     /* routing metric (external only) */
         char            if_hwaddr[6];  /* ethernet address */
         int             if_type;       /* interface type: 1=generic,
                                         * 28=slip, ether=6, loopback=24 */
         u_long          if_speed;      /* interface speed: in bits/sec */

         struct sockaddr if_addr;       /* interface's address */
         struct sockaddr ifu_broadaddr; /* broadcast address */
         struct sockaddr ia_subnetmask; /* interface's mask */

         struct ifqueue {
             int             ifq_len;
             int             ifq_drops;
         } if_snd;              /* output queue */
         u_long          if_ibytes;     /* octets received on interface */
         u_long          if_ipackets;   /* packets received on interface */
         u_long          if_ierrors;    /* input errors on interface */
         u_long          if_iqdrops;    /* input queue overruns */
         u_long          if_obytes;     /* octets sent on interface */
         u_long          if_opackets;   /* packets sent on interface */
         u_long          if_oerrors;    /* output errors on interface */
         u_long          if_collisions; /* collisions on csma interfaces */
         /*
          * end statistics 
          */
         struct ifnet   *if_next;
     };
#endif   /* linux */
#endif                          /* _MIBGROUP_INTERFACES_H */


#ifndef MIB_STATS_CACHE_TIMEOUT
#define MIB_STATS_CACHE_TIMEOUT	5
#endif
#ifndef IP_STATS_CACHE_TIMEOUT
#define IP_STATS_CACHE_TIMEOUT	MIB_STATS_CACHE_TIMEOUT
#endif

#if defined(HAVE_LIBPERFSTAT_H) && (defined(aix4) || defined(aix5) || defined(aix6) || defined(aix7)) && !defined(FIRST_PROTOCOL)
#ifdef HAVE_SYS_PROTOSW_H
#include <sys/protosw.h>
#endif
#include <libperfstat.h>
#ifdef FIRST_PROTOCOL
perfstat_protocol_t ps_proto;
perfstat_id_t ps_name;
#define _USE_PERFSTAT_PROTOCOL 1
#endif
#endif

        /*********************
	 *
	 *  Kernel & interface information,
	 *   and internal forward declarations
	 *
	 *********************/


        /*********************
	 *
	 *  Initialisation & common implementation functions
	 *
	 *********************/

extern void     init_routes(void);


/*
 * define the structure we're going to ask the agent to register our
 * information at 
 */
struct variable1 ipaddr_variables[] = {
    {IPADADDR,      ASN_IPADDRESS, NETSNMP_OLDAPI_RONLY,
     var_ipAddrEntry, 1, {1}},
    {IPADIFINDEX,   ASN_INTEGER,   NETSNMP_OLDAPI_RONLY,
     var_ipAddrEntry, 1, {2}},
#ifndef sunV3
    {IPADNETMASK,   ASN_IPADDRESS, NETSNMP_OLDAPI_RONLY,
     var_ipAddrEntry, 1, {3}},
#endif
    {IPADBCASTADDR, ASN_INTEGER,   NETSNMP_OLDAPI_RONLY,
     var_ipAddrEntry, 1, {4}},
    {IPADREASMMAX,  ASN_INTEGER,   NETSNMP_OLDAPI_RONLY,
     var_ipAddrEntry, 1, {5}}
};

struct variable1 iproute_variables[] = {
    {IPROUTEDEST,    ASN_IPADDRESS, NETSNMP_OLDAPI_RWRITE,
     var_ipRouteEntry, 1, {1}},
    {IPROUTEIFINDEX, ASN_INTEGER,   NETSNMP_OLDAPI_RWRITE,
     var_ipRouteEntry, 1, {2}},
    {IPROUTEMETRIC1, ASN_INTEGER,   NETSNMP_OLDAPI_RWRITE,
     var_ipRouteEntry, 1, {3}},
    {IPROUTEMETRIC2, ASN_INTEGER,   NETSNMP_OLDAPI_RWRITE,
     var_ipRouteEntry, 1, {4}},
    {IPROUTEMETRIC3, ASN_INTEGER,   NETSNMP_OLDAPI_RWRITE,
     var_ipRouteEntry, 1, {5}},
    {IPROUTEMETRIC4, ASN_INTEGER,   NETSNMP_OLDAPI_RWRITE,
     var_ipRouteEntry, 1, {6}},
    {IPROUTENEXTHOP, ASN_IPADDRESS, NETSNMP_OLDAPI_RWRITE,
     var_ipRouteEntry, 1, {7}},
    {IPROUTETYPE,    ASN_INTEGER,   NETSNMP_OLDAPI_RWRITE,
     var_ipRouteEntry, 1, {8}},
    {IPROUTEPROTO,   ASN_INTEGER,   NETSNMP_OLDAPI_RONLY,
     var_ipRouteEntry, 1, {9}},
    {IPROUTEAGE,     ASN_INTEGER,   NETSNMP_OLDAPI_RWRITE,
     var_ipRouteEntry, 1, {10}},
    {IPROUTEMASK,    ASN_IPADDRESS, NETSNMP_OLDAPI_RWRITE,
     var_ipRouteEntry, 1, {11}},
    {IPROUTEMETRIC5, ASN_INTEGER,   NETSNMP_OLDAPI_RWRITE,
     var_ipRouteEntry, 1, {12}},
    {IPROUTEINFO,    ASN_OBJECT_ID, NETSNMP_OLDAPI_RONLY,
     var_ipRouteEntry, 1, {13}}
};

struct variable1 ipmedia_variables[] = {
#ifdef USING_MIBII_AT_MODULE
#if defined (WIN32) || defined (cygwin)
    {IPMEDIAIFINDEX,     ASN_INTEGER,   NETSNMP_OLDAPI_RWRITE,
     var_atEntry, 1, {1}},
    {IPMEDIAPHYSADDRESS, ASN_OCTET_STR, NETSNMP_OLDAPI_RWRITE,
     var_atEntry, 1, {2}},
    {IPMEDIANETADDRESS,  ASN_IPADDRESS, NETSNMP_OLDAPI_RWRITE,
     var_atEntry, 1, {3}},
    {IPMEDIATYPE,        ASN_INTEGER,   NETSNMP_OLDAPI_RWRITE,
     var_atEntry, 1, {4}}
#else
    {IPMEDIAIFINDEX,     ASN_INTEGER,   NETSNMP_OLDAPI_RONLY,
     var_atEntry, 1, {1}},
    {IPMEDIAPHYSADDRESS, ASN_OCTET_STR, NETSNMP_OLDAPI_RONLY,
     var_atEntry, 1, {2}},
    {IPMEDIANETADDRESS,  ASN_IPADDRESS, NETSNMP_OLDAPI_RONLY,
     var_atEntry, 1, {3}},
    {IPMEDIATYPE,        ASN_INTEGER,   NETSNMP_OLDAPI_RONLY,
     var_atEntry, 1, {4}}
#endif
#endif
};

/*
 * Define the OID pointer to the top of the mib tree that we're
 * registering underneath, and the OID of the MIB module 
 */
oid             ip_oid[]                = { SNMP_OID_MIB2, 4 };

oid             ipaddr_variables_oid[]  = { SNMP_OID_MIB2, 4, 20, 1 };
oid             iproute_variables_oid[] = { SNMP_OID_MIB2, 4, 21, 1 };
oid             ipmedia_variables_oid[] = { SNMP_OID_MIB2, 4, 22, 1 };
oid             ip_module_oid[] = { SNMP_OID_MIB2, 4 };
oid             ip_module_oid_len = sizeof(ip_module_oid) / sizeof(oid);
int             ip_module_count = 0;    /* Need to liaise with icmp.c */

void
__init_ip(void)
{
    netsnmp_handler_registration *reginfo;
    int rc;

    /*
     * register ourselves with the agent as a group of scalars...
     */
    DEBUGMSGTL(("mibII/ip", "Initialising IP group\n"));
    reginfo = netsnmp_create_handler_registration("ip", ip_handler,
                            ip_oid, OID_LENGTH(ip_oid), HANDLER_CAN_RONLY);
    rc = netsnmp_register_scalar_group(reginfo, IPFORWARDING, IPROUTEDISCARDS);
    if (rc != SNMPERR_SUCCESS)
        return;

    /*
     * .... with a local cache
     *    (except for HP-UX 11, which extracts objects individually)
     */
#ifndef hpux11
    netsnmp_inject_handler( reginfo,
		    netsnmp_get_cache_handler(IP_STATS_CACHE_TIMEOUT,
			   		ip_load, ip_free,
					ip_oid, OID_LENGTH(ip_oid)));
#endif

	SNMP_REGISTER_TABLE_FOR_MIB2_IPADDR(ipaddr);		//"mibII/ipaddr"
//	SNMP_REGISTER_TABLE_FOR_MIB2_IPADDR(iproute);		//"mibII/iproute"
//	SNMP_REGISTER_TABLE_FOR_MIB2_IPADDR(ipmedia);		//"mibII/ipmedia"


    if (++ip_module_count == 2)
        REGISTER_SYSOR_ENTRY(ip_module_oid,
                             "The MIB module for managing IP and ICMP implementations");


    /*
     * for speed optimization, we call this now to do the lookup 
     */
#ifndef _USE_PERFSTAT_PROTOCOL
#ifdef IPSTAT_SYMBOL
    auto_nlist(IPSTAT_SYMBOL, 0, 0);
#endif
#ifdef IP_FORWARDING_SYMBOL
    auto_nlist(IP_FORWARDING_SYMBOL, 0, 0);
#endif
#ifdef TCP_TTL_SYMBOL
    auto_nlist(TCP_TTL_SYMBOL, 0, 0);
#endif
#ifdef MIB_IPCOUNTER_SYMBOL
    auto_nlist(MIB_IPCOUNTER_SYMBOL, 0, 0);
#endif
#ifdef solaris2
    init_kernel_sunos5();
#endif
#endif
}


        /*********************
	 *
	 *  System specific data formats
	 *
	 *********************/

#ifdef hpux11
#define IP_STAT_STRUCTURE	int
#endif

#ifdef linux
#define IP_STAT_STRUCTURE	struct ip_mib
#define	USES_SNMP_DESIGNED_IPSTAT
#endif

#ifdef solaris2
#define IP_STAT_STRUCTURE	mib2_ip_t
#define	USES_SNMP_DESIGNED_IPSTAT
#endif

#ifdef NETBSD_STATS_VIA_SYSCTL
#define IP_STAT_STRUCTURE	struct ip_mib
#define USES_SNMP_DESIGNED_IPSTAT
#undef IP_NSTATS
#endif

#ifdef HAVE_IPHLPAPI_H
#include <iphlpapi.h>
#define IP_STAT_STRUCTURE MIB_IPSTATS
long            ipForwarding;
long            oldipForwarding;
long            ipTTL, oldipTTL;
#endif                          /* WIN32 cygwin */

#ifdef HAVE_SYS_TCPIPSTATS_H
#define IP_STAT_STRUCTURE	struct kna
#define	USES_TRADITIONAL_IPSTAT
#endif

#ifdef dragonfly
#define IP_STAT_STRUCTURE	struct ip_stats
#define	USES_TRADITIONAL_IPSTAT
#endif

#if !defined(IP_STAT_STRUCTURE)
#define IP_STAT_STRUCTURE	struct ipstat
#define	USES_TRADITIONAL_IPSTAT
#endif

IP_STAT_STRUCTURE ipstat;



        /*********************
	 *
	 *  System independent handler
	 *      (mostly)
	 *
	 *********************/


int
ip_handler(netsnmp_mib_handler          *handler,
           netsnmp_handler_registration *reginfo,
           netsnmp_agent_request_info   *reqinfo,
           netsnmp_request_info         *requests)
{
    netsnmp_request_info  *request;
    netsnmp_variable_list *requestvb;
    long     ret_value;
    oid      subid;
    int      type = ASN_COUNTER;

    /*
     * The cached data should already have been loaded by the
     *    cache handler, higher up the handler chain.
     */
#ifdef _USE_PERFSTAT_PROTOCOL
    ip_load(NULL, NULL);
#endif


    /*
     * 
     *
     */
    DEBUGMSGTL(("mibII/ip", "Handler - mode %s\n",
                    se_find_label_in_slist("agent_mode", reqinfo->mode)));
    switch (reqinfo->mode) {
    case MODE_GET:
        for (request=requests; request; request=request->next) {
            requestvb = request->requestvb;
            subid = requestvb->name[OID_LENGTH(ip_oid)];  /* XXX */
            DEBUGMSGTL(( "mibII/ip", "oid: "));
            DEBUGMSGOID(("mibII/ip", requestvb->name,
                                     requestvb->name_length));
            DEBUGMSG((   "mibII/ip", "\n"));

            switch (subid) {
#ifdef USES_SNMP_DESIGNED_IPSTAT
    case IPFORWARDING:
        ret_value = ipstat.ipForwarding;
        type = ASN_INTEGER;
        break;
    case IPDEFAULTTTL:
        ret_value = ipstat.ipDefaultTTL;
        type = ASN_INTEGER;
        break;
    case IPINRECEIVES:
        ret_value = ipstat.ipInReceives & 0xffffffff;
        break;
    case IPINHDRERRORS:
        ret_value = ipstat.ipInHdrErrors;
        break;
    case IPINADDRERRORS:
        ret_value = ipstat.ipInAddrErrors;
        break;
    case IPFORWDATAGRAMS:
        ret_value = ipstat.ipForwDatagrams;
        break;
    case IPINUNKNOWNPROTOS:
        ret_value = ipstat.ipInUnknownProtos;
        break;
    case IPINDISCARDS:
        ret_value = ipstat.ipInDiscards;
        break;
    case IPINDELIVERS:
        ret_value = ipstat.ipInDelivers & 0xffffffff;
        break;
    case IPOUTREQUESTS:
        ret_value = ipstat.ipOutRequests & 0xffffffff;
        break;
    case IPOUTDISCARDS:
        ret_value = ipstat.ipOutDiscards;
        break;
    case IPOUTNOROUTES:
        ret_value = ipstat.ipOutNoRoutes;
        break;
    case IPREASMTIMEOUT:
        ret_value = ipstat.ipReasmTimeout;
        type = ASN_INTEGER;
        break;
    case IPREASMREQDS:
        ret_value = ipstat.ipReasmReqds;
        break;
    case IPREASMOKS:
        ret_value = ipstat.ipReasmOKs;
        break;
    case IPREASMFAILS:
        ret_value = ipstat.ipReasmFails;
        break;
    case IPFRAGOKS:
        ret_value = ipstat.ipFragOKs;
        break;
    case IPFRAGFAILS:
        ret_value = ipstat.ipFragFails;
        break;
    case IPFRAGCREATES:
        ret_value = ipstat.ipFragCreates;
        break;
    case IPROUTEDISCARDS:
        ret_value = ipstat.ipRoutingDiscards;
        break;

#elif defined(USES_TRADITIONAL_IPSTAT) && !defined(_USE_PERFSTAT_PROTOCOL)
#ifdef HAVE_SYS_TCPIPSTATS_H
    /*
     * This actually reads statistics for *all* the groups together,
     * so we need to isolate the IP-specific bits.  
     */
#define	ipstat		ipstat.ipstat
#endif
    case IPFORWARDING:
    case IPDEFAULTTTL:
        /* 
         * Query these two individually
         */
        ret_value = ip_load(NULL, (void *)subid);
        if (ret_value == -1 ) {
            snmp_set_request_error(reqinfo, request, SNMP_NOSUCHOBJECT);
            continue;
	}
        type = ASN_INTEGER;
        break;
    case IPINRECEIVES:
        ret_value = ipstat.ips_total & 0xffffffff;
        break;
    case IPINHDRERRORS:
        ret_value = ipstat.ips_badsum
            + ipstat.ips_tooshort
            + ipstat.ips_toosmall + ipstat.ips_badhlen + ipstat.ips_badlen;
        break;
    case IPINADDRERRORS:
        ret_value = ipstat.ips_cantforward;
        break;
    case IPFORWDATAGRAMS:
        ret_value = ipstat.ips_forward;
        break;
    case IPINUNKNOWNPROTOS:
#if HAVE_STRUCT_IPSTAT_IPS_NOPROTO
        ret_value = ipstat.ips_noproto;
        break;
#else
        snmp_set_request_error(reqinfo, request, SNMP_NOSUCHOBJECT);
        continue;
#endif
    case IPINDISCARDS:
#if HAVE_STRUCT_IPSTAT_IPS_FRAGDROPPED
        ret_value = ipstat.ips_fragdropped;   /* ?? */
        break;
#else
        snmp_set_request_error(reqinfo, request, SNMP_NOSUCHOBJECT);
        continue;
#endif
    case IPINDELIVERS:
#if HAVE_STRUCT_IPSTAT_IPS_DELIVERED
        ret_value = ipstat.ips_delivered & 0xffffffff;
        break;
#else
        snmp_set_request_error(reqinfo, request, SNMP_NOSUCHOBJECT);
        continue;
#endif
    case IPOUTREQUESTS:
#if HAVE_STRUCT_IPSTAT_IPS_LOCALOUT
        ret_value = ipstat.ips_localout & 0xffffffff;
        break;
#else
        snmp_set_request_error(reqinfo, request, SNMP_NOSUCHOBJECT);
        continue;
#endif
    case IPOUTDISCARDS:
#if HAVE_STRUCT_IPSTAT_IPS_ODROPPED
        ret_value = ipstat.ips_odropped;
        break;
#else
        snmp_set_request_error(reqinfo, request, SNMP_NOSUCHOBJECT);
        continue;
#endif
    case IPOUTNOROUTES:
        /*
         * XXX: how to calculate this (counts dropped routes, not packets)?
         * ipstat.ips_cantforward isn't right, as it counts packets.
         * ipstat.ips_noroute is also incorrect.
         */
        snmp_set_request_error(reqinfo, request, SNMP_NOSUCHOBJECT);
        continue;
    case IPREASMTIMEOUT:
        ret_value = IPFRAGTTL;
        type = ASN_INTEGER;
        break;
    case IPREASMREQDS:
        ret_value = ipstat.ips_fragments;
        break;
    case IPREASMOKS:
#if HAVE_STRUCT_IPSTAT_IPS_REASSEMBLED
        ret_value = ipstat.ips_reassembled;
        break;
#else
        snmp_set_request_error(reqinfo, request, SNMP_NOSUCHOBJECT);
        continue;
#endif
    case IPREASMFAILS:
        ret_value = ipstat.ips_fragdropped + ipstat.ips_fragtimeout;
        break;
    case IPFRAGOKS:
#if HAVE_STRUCT_IPSTAT_IPS_FRAGMENTED
        ret_value = ipstat.ips_fragments;
        break;
#else            /* XXX */
        ret_value = ipstat.ips_fragments
            - (ipstat.ips_fragdropped + ipstat.ips_fragtimeout);
        break;
#endif
    case IPFRAGFAILS:
#if HAVE_STRUCT_IPSTAT_IPS_CANTFRAG
        ret_value = ipstat.ips_cantfrag;
        break;
#else
        snmp_set_request_error(reqinfo, request, SNMP_NOSUCHOBJECT);
        continue;
#endif
    case IPFRAGCREATES:
#if HAVE_STRUCT_IPSTAT_IPS_OFRAGMENTS
        ret_value = ipstat.ips_ofragments;
        break;
#else
        snmp_set_request_error(reqinfo, request, SNMP_NOSUCHOBJECT);
        continue;
#endif
    case IPROUTEDISCARDS:
#if HAVE_STRUCT_IPSTAT_IPS_NOROUTE
        ret_value = ipstat.ips_noroute;
        break;
#else
        snmp_set_request_error(reqinfo, request, SNMP_NOSUCHOBJECT);
        continue;
#endif
#ifdef HAVE_SYS_TCPIPSTATS_H
#undef ipstat
#endif
#elif defined(hpux11)
    case IPFORWARDING:
    case IPDEFAULTTTL:
    case IPREASMTIMEOUT:
        type = ASN_INTEGER;
    case IPINRECEIVES:
    case IPINHDRERRORS:
    case IPINADDRERRORS:
    case IPFORWDATAGRAMS:
    case IPINUNKNOWNPROTOS:
    case IPINDISCARDS:
    case IPINDELIVERS:
    case IPOUTREQUESTS:
    case IPOUTDISCARDS:
    case IPOUTNOROUTES:
    case IPREASMREQDS:
    case IPREASMOKS:
    case IPREASMFAILS:
    case IPFRAGOKS:
    case IPFRAGFAILS:
    case IPFRAGCREATES:
    case IPROUTEDISCARDS:
	/*
	 * This is a bit of a hack, to shoehorn the HP-UX 11
	 * single-object retrieval approach into the caching
	 * architecture.
	 */
	if (ip_load(NULL, (void*)subid) == -1 ) {
            snmp_set_request_error(reqinfo, request, SNMP_NOSUCHOBJECT);
            continue;
	}
        ret_value = ipstat;
        break;
#elif defined (WIN32) || defined (cygwin)
    case IPFORWARDING:
        ipForwarding = ipstat.dwForwarding;
        ret_value    = ipstat.dwForwarding;
        type = ASN_INTEGER;
        break;
    case IPDEFAULTTTL:
        ipTTL     = ipstat.dwDefaultTTL;
        ret_value = ipstat.dwDefaultTTL;
        type = ASN_INTEGER;
        break;
    case IPINRECEIVES:
        ret_value = ipstat.dwInReceives;
        break;
    case IPINHDRERRORS:
        ret_value = ipstat.dwInHdrErrors;
        break;
    case IPINADDRERRORS:
        ret_value = ipstat.dwInAddrErrors;
        break;
    case IPFORWDATAGRAMS:
        ret_value = ipstat.dwForwDatagrams;
        break;
    case IPINUNKNOWNPROTOS:
        ret_value = ipstat.dwInUnknownProtos;
        break;
    case IPINDISCARDS:
        ret_value = ipstat.dwInDiscards;
        break;
    case IPINDELIVERS:
        ret_value = ipstat.dwInDelivers;
        break;
    case IPOUTREQUESTS:
        ret_value = ipstat.dwOutRequests;
        break;
    case IPOUTDISCARDS:
        ret_value = ipstat.dwOutDiscards;
        break;
    case IPOUTNOROUTES:
        ret_value = ipstat.dwOutNoRoutes;
        break;
    case IPREASMTIMEOUT:
        ret_value = ipstat.dwReasmTimeout;
        type = ASN_INTEGER;
        break;
    case IPREASMREQDS:
        ret_value = ipstat.dwReasmReqds;
        break;
    case IPREASMOKS:
        ret_value = ipstat.dwReasmOks;
        break;
    case IPREASMFAILS:
        ret_value = ipstat.dwReasmFails;
        break;
    case IPFRAGOKS:
        ret_value = ipstat.dwFragOks;
        break;
    case IPFRAGFAILS:
        ret_value = ipstat.dwFragFails;
        break;
    case IPFRAGCREATES:
        ret_value = ipstat.dwFragCreates;
        break;
    case IPROUTEDISCARDS:
        ret_value = ipstat.dwRoutingDiscards;
        break;
#elif defined(_USE_PERFSTAT_PROTOCOL)
    case IPFORWARDING:
        ret_value    = 0;
        type = ASN_INTEGER;
        break;
    case IPDEFAULTTTL:
        ret_value = 0;
        type = ASN_INTEGER;
        break;
    case IPINRECEIVES:
        ret_value = ps_proto.u.ip.ipackets;
        break;
    case IPINHDRERRORS:
    case IPINADDRERRORS:
    case IPFORWDATAGRAMS:
        ret_value = 0;
        break;
    case IPINUNKNOWNPROTOS:
        ret_value = ps_proto.u.ip.ierrors;
        break;
    case IPINDISCARDS:
        ret_value = 0;
        break;
    case IPINDELIVERS:
    case IPOUTREQUESTS:
        ret_value = ps_proto.u.ip.opackets;
        break;
    case IPOUTDISCARDS:
    case IPOUTNOROUTES:
        ret_value = 0;
        break;
    case IPREASMTIMEOUT:
        ret_value = 0;
        type = ASN_INTEGER;
        break;
    case IPREASMREQDS:
    case IPREASMOKS:
    case IPREASMFAILS:
    case IPFRAGOKS:
    case IPFRAGFAILS:
    case IPFRAGCREATES:
        ret_value = 0;
        break;
    case IPROUTEDISCARDS:
        ret_value = ps_proto.u.ip.oerrors;
        break;
#endif			/* USES_SNMP_DESIGNED_IPSTAT */

    case IPADDRTABLE:
    case IPROUTETABLE:
    case IPMEDIATABLE:
        /*
	 * These are not actually valid scalar objects.
	 * The relevant table registrations should take precedence,
	 *   so skip these three subtrees, regardless of architecture.
	 */
        snmp_set_request_error(reqinfo, request, SNMP_NOSUCHOBJECT);
        continue;

	    }
	    snmp_set_var_typed_value(request->requestvb, (u_char)type,
			             (u_char *)&ret_value, sizeof(ret_value));
	}
        break;

    case MODE_GETNEXT:
    case MODE_GETBULK:
#ifndef NETSNMP_NO_WRITE_SUPPORT
    case MODE_SET_RESERVE1:
		/* XXX - Windows currently supports setting this */
    case MODE_SET_RESERVE2:
    case MODE_SET_ACTION:
    case MODE_SET_COMMIT:
    case MODE_SET_FREE:
    case MODE_SET_UNDO:
        snmp_log(LOG_WARNING, "mibII/ip: Unsupported mode (%d)\n",
                               reqinfo->mode);
        break;
#endif /* !NETSNMP_NO_WRITE_SUPPORT */
    default:
        snmp_log(LOG_WARNING, "mibII/ip: Unrecognised mode (%d)\n",
                               reqinfo->mode);
        break;
    }

    return SNMP_ERR_NOERROR;
}



        /*********************
	 *
	 *  Internal implementation functions
	 *
	 *********************/


#ifdef hpux11	/*modify by bain.wang@outlook.com on 2017-03-01*/
int
ip_load(netsnmp_cache *cache, void *vmagic)
{
    int             fd;
    struct nmparms  p;
    unsigned int    ulen;
    int             ret;
    int             magic = (int) vmagic;
    
    if ((fd = open_mib("/dev/ip", O_RDONLY, 0, NM_ASYNC_OFF)) < 0) {
        DEBUGMSGTL(("mibII/ip", "Failed to load IP object %d (hpux11)\n", magic));
        return (-1);            /* error */
    }

    switch (magic) {
    case IPFORWARDING:
        p.objid = ID_ipForwarding;
        break;
    case IPDEFAULTTTL:
        p.objid = ID_ipDefaultTTL;
        break;
    case IPINRECEIVES:
        p.objid = ID_ipInReceives;
        break;
    case IPINHDRERRORS:
        p.objid = ID_ipInHdrErrors;
        break;
    case IPINADDRERRORS:
        p.objid = ID_ipInAddrErrors;
        break;
    case IPFORWDATAGRAMS:
        p.objid = ID_ipForwDatagrams;
        break;
    case IPINUNKNOWNPROTOS:
        p.objid = ID_ipInUnknownProtos;
        break;
    case IPINDISCARDS:
        p.objid = ID_ipInDiscards;
        break;
    case IPINDELIVERS:
        p.objid = ID_ipInDelivers;
        break;
    case IPOUTREQUESTS:
        p.objid = ID_ipOutRequests;
        break;
    case IPOUTDISCARDS:
        p.objid = ID_ipOutDiscards;
        break;
    case IPOUTNOROUTES:
        p.objid = ID_ipOutNoRoutes;
        break;
    case IPREASMTIMEOUT:
        p.objid = ID_ipReasmTimeout;
        break;
    case IPREASMREQDS:
        p.objid = ID_ipReasmReqds;
        break;
    case IPREASMOKS:
        p.objid = ID_ipReasmOKs;
        break;
    case IPREASMFAILS:
        p.objid = ID_ipReasmFails;
        break;
    case IPFRAGOKS:
        p.objid = ID_ipFragOKs;
        break;
    case IPFRAGFAILS:
        p.objid = ID_ipFragFails;
        break;
    case IPFRAGCREATES:
        p.objid = ID_ipFragCreates;
        break;
    case IPROUTEDISCARDS:
        p.objid = ID_ipRoutingDiscards;
        break;
    default:
        ipstat = 0;
        close_mib(fd);
        return (0);
    }

    p.buffer = (void *)&ipstat;
    ulen = sizeof(IP_STAT_STRUCTURE);
    p.len = &ulen;
    ret = get_mib_info(fd, &p);
    close_mib(fd);

    DEBUGMSGTL(("mibII/ip", "%s IP object %d (hpux11)\n",
               (ret < 0 ? "Failed to load" : "Loaded"),  magic));
    return (ret);         /* 0: ok, < 0: error */
}
#elif defined(linux)
int
ip_load(netsnmp_cache *cache, void *vmagic)
{
    long ret_value = -1;

    ret_value = linux_read_ip_stat(&ipstat);

    if ( ret_value < 0 ) {
        DEBUGMSGTL(("mibII/ip", "Failed to load IP Group (linux)\n"));
    } else {
        DEBUGMSGTL(("mibII/ip", "Loaded IP Group (linux)\n"));
    }
    return ret_value;
}
#elif defined(solaris2)
int
ip_load(netsnmp_cache *cache, void *vmagic)
{
    long ret_value = -1;

    ret_value =
        getMibstat(MIB_IP, &ipstat, sizeof(mib2_ip_t), GET_FIRST,
                   &Get_everything, NULL);

    if ( ret_value < 0 ) {
        DEBUGMSGTL(("mibII/ip", "Failed to load IP Group (solaris)\n"));
    } else {
        DEBUGMSGTL(("mibII/ip", "Loaded IP Group (solaris)\n"));
    }
    return ret_value;
}
#elif defined (NETBSD_STATS_VIA_SYSCTL)
int
ip_load(netsnmp_cache *cache, void *vmagic)
{
    long ret_value = -1;

    ret_value = netbsd_read_ip_stat(&ipstat);

    if ( ret_value < 0) {
	DEBUGMSGTL(("mibII/ip", "Failed to load IP Group (netbsd)\n"));
    } else {
	DEBUGMSGTL(("mibII/ip", "Loaded IP Group (netbsd)\n"));
    }
    return ret_value;
}
#elif defined (WIN32) || defined (cygwin)
int
ip_load(netsnmp_cache *cache, void *vmagic)
{
    long ret_value = -1;

    ret_value = GetIpStatistics(&ipstat);

    if ( ret_value < 0 ) {
        DEBUGMSGTL(("mibII/ip", "Failed to load IP Group (win32)\n"));
    } else {
        DEBUGMSGTL(("mibII/ip", "Loaded IP Group (win32)\n"));
    }
    return ret_value;
}
#elif defined(_USE_PERFSTAT_PROTOCOL)
int
ip_load(netsnmp_cache *cache, void *vmagic)
{
    long ret_value = -1;

    strcpy(ps_name.name, "ip");
    ret_value = perfstat_protocol(&ps_name, &ps_proto, sizeof(ps_proto), 1);

    if ( ret_value < 0 ) {
        DEBUGMSGTL(("mibII/ip", "Failed to load IP Group (AIX)\n"));
    } else {
        ret_value = 0;
        DEBUGMSGTL(("mibII/ip", "Loaded IP Group (AIX)\n"));
    }
    return ret_value;
}
#elif defined(NETSNMP_CAN_USE_SYSCTL) && defined(IPCTL_STATS)
int
ip_load(netsnmp_cache *cache, void *vmagic)
{
    long            ret_value = 0;
    int             i;
    static int      sname[4] = { CTL_NET, PF_INET, IPPROTO_IP, 0 };
    size_t          len;
    int             magic = (int) vmagic;

    switch (magic) {
    case IPFORWARDING:
        len = sizeof i;
        sname[3] = IPCTL_FORWARDING;
        if (sysctl(sname, 4, &i, &len, 0, 0) < 0)
            return -1;
        else
            return (i ? 1 /* GATEWAY */
                      : 2 /* HOST    */ );

    case IPDEFAULTTTL:
        len = sizeof i;
        sname[3] = IPCTL_DEFTTL;
        if (sysctl(sname, 4, &i, &len, 0, 0) < 0)
            return -1;
        else
            return i;

    default:
        len = sizeof(ipstat);
        sname[3] = IPCTL_STATS;
        ret_value = sysctl(sname, 4, &ipstat, &len, 0, 0);

        if ( ret_value < 0 ) {
            DEBUGMSGTL(("mibII/ip", "Failed to load IP Group (sysctl)\n"));
        } else {
            DEBUGMSGTL(("mibII/ip", "Loaded IP Group (sysctl)\n"));
        }
        return ret_value;
    }
}
#elif defined(HAVE_SYS_TCPIPSTATS_H)
int
ip_load(netsnmp_cache *cache, void *vmagic)
{
    long ret_value = -1;
    int  magic     = (int) vmagic;

    switch (magic) {
    case IPFORWARDING:
        if (!auto_nlist
            (IP_FORWARDING_SYMBOL, (char *) &ret_value, sizeof(ret_value)))
            return -1;
        else
            return (ret_value ? 1 /* GATEWAY */
                              : 2 /* HOST    */ );

    case IPDEFAULTTTL:
        if (!auto_nlist
            (TCP_TTL_SYMBOL, (char *) &ret_value, sizeof(ret_value)))
            return -1;
        else
            return ret_value;

    default:
        ret_value = sysmp(MP_SAGET, MPSA_TCPIPSTATS, &ipstat, sizeof ipstat);

        if ( ret_value < 0 ) {
            DEBUGMSGTL(("mibII/ip", "Failed to load IP Group (tcpipstats)\n"));
        } else {
            DEBUGMSGTL(("mibII/ip", "Loaded IP Group (tcpipstats)\n"));
        }
        return ret_value;
    }
}
#elif defined(IPSTAT_SYMBOL)
int
ip_load(netsnmp_cache *cache, void *vmagic)
{
    long ret_value = -1;
    int  magic     = (int) vmagic;

    switch (magic) {
    case IPFORWARDING:
        if (!auto_nlist
            (IP_FORWARDING_SYMBOL, (char *) &ret_value, sizeof(ret_value)))
            return -1;
        else
            return (ret_value ? 1 /* GATEWAY */
                              : 2 /* HOST    */ );

    case IPDEFAULTTTL:
        if (!auto_nlist
            (TCP_TTL_SYMBOL, (char *) &ret_value, sizeof(ret_value)))
            return -1;
        else
            return ret_value;

    default:
        if (auto_nlist(IPSTAT_SYMBOL, (char *)&ipstat, sizeof(ipstat)))
            ret_value = 0;

        if ( ret_value < 0 ) {
            DEBUGMSGTL(("mibII/ip", "Failed to load IP Group (ipstat)\n"));
        } else {
            DEBUGMSGTL(("mibII/ip", "Loaded IP Group (ipstat)\n"));
        }
        return ret_value;
    }
}
#else				/* IPSTAT_SYMBOL */
int
ip_load(netsnmp_cache *cache, void *vmagic)
{
    long ret_value = -1;

    DEBUGMSGTL(("mibII/ip", "Failed to load IP Group (null)\n"));
    return ret_value;
}
#endif                          /* hpux11 */

void
ip_free(netsnmp_cache *cache, void *magic)
{
#if defined(_USE_PERFSTAT_PROTOCOL)
    memset(&ps_proto, 0, sizeof(ps_proto));
#else
    memset(&ipstat, 0, sizeof(ipstat));
#endif
}

#endif

void snmp_ipAddrTable_init(void)
{
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);

	__init_ip();
	SNMP_MIB_FFLUSH_INIT();

	BC_PT_FUN_LEAVE(BC_MODULE_SNMP);
}

#endif	/*RFC_1213_MIB*/
