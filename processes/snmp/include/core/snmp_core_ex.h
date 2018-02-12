/*
!!!!!!!!!!!!!!!!!!!!!!!!ÇëÎðÐÞ¸Ä±¾ÎÄ¼þ!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!ÇëÎðÐÞ¸Ä±¾ÎÄ¼þ!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!ÇëÎðÐÞ¸Ä±¾ÎÄ¼þ!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!ÇëÎðÐÞ¸Ä±¾ÎÄ¼þ!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!ÇëÎðÐÞ¸Ä±¾ÎÄ¼þ!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!ÇëÎðÐÞ¸Ä±¾ÎÄ¼þ!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!ÇëÎðÐÞ¸Ä±¾ÎÄ¼þ!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!ÇëÎðÐÞ¸Ä±¾ÎÄ¼þ!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!ÇëÎðÐÞ¸Ä±¾ÎÄ¼þ!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!ÇëÎðÐÞ¸Ä±¾ÎÄ¼þ!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!ÇëÎðÐÞ¸Ä±¾ÎÄ¼þ!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!ÇëÎðÐÞ¸Ä±¾ÎÄ¼þ!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!ÇëÎðÐÞ¸Ä±¾ÎÄ¼þ!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!ÇëÎðÐÞ¸Ä±¾ÎÄ¼þ!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!ÇëÎðÐÞ¸Ä±¾ÎÄ¼þ!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!ÇëÎðÐÞ¸Ä±¾ÎÄ¼þ!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!ÇëÎðÐÞ¸Ä±¾ÎÄ¼þ!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!ÇëÎðÐÞ¸Ä±¾ÎÄ¼þ!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!ÇëÎðÐÞ¸Ä±¾ÎÄ¼þ!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!ÇëÎðÐÞ¸Ä±¾ÎÄ¼þ!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!ÇëÎðÐÞ¸Ä±¾ÎÄ¼þ!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!ÇëÎðÐÞ¸Ä±¾ÎÄ¼þ!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!ÇëÎðÐÞ¸Ä±¾ÎÄ¼þ!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!ÇëÎðÐÞ¸Ä±¾ÎÄ¼þ!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!ÇëÎðÐÞ¸Ä±¾ÎÄ¼þ!!!!!!!!!!!!!!!!!!!!!!!!
*/





/*******************************************************************************
  [Author]     : bain.wang@outlook.com.uestc@gmail.com
  [Version]    : 
  [Date]       : 
  [Description]: !!!!!!!!!!!!!!!!!!!ÇëÎðÐÞ¸Ä±¾ÎÄ¼þ!!!!!!!!!!!!!!!!!!!!!!!!

  [Others]     :

  [History]:
	 Date          	Modification 							    			Initials
	----------     ----------                                   					-------
	2017-03-16      Created								   		bain.wang@outlook.com
	2017-05-05      Modify								   			bain.wang@outlook.com
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//																			  //
//								Í·   ÎÄ   ¼þ								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
#ifndef __SNMP_CORE_EX_H__
#define __SNMP_CORE_EX_H__

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include <net-snmp/agent/snmp_vars.h>
#include <sys/time.h>

#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>   
#include <sys/ioctl.h>   
#include <netinet/in.h>   
#include <net/if.h>   
#include <net/if_arp.h>   
#include <arpa/inet.h>   
#include <errno.h>  
#include <pthread.h>
#include <semaphore.h>

#include "bc_common_defs.h"

#include "snmp_mib.h"
#include "bc_print.h"
////////////////////////////////////////////////////////////////////////////////
//																			  //
//								å®   å®š   ä¹‰								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#define SNMP_OID_INDEX_MAX			10
#define SNMP_TABLE_NO_ROW_STATUS  (-1)	/*²»¿É´´½¨ÐÐµÄ±í*/



#define SNMP_CORE_SUPPORT_SET		TRUE

#if 1

#define SNMP_NODE_TYPE_CHECK(t)	\
	do{if(var_val_type!=t){return SNMP_ERR_WRONGTYPE;}}while(0)	


#define SNMP_NODE_ACCESS_CHECK()	\
	do{if(node&&node->storageType==NETSNMP_OLDAPI_RONLY){return SNMP_ERR_NOTWRITABLE;}}while(0)

	
#define SNMP_NODE_OID_PT(oid, len)	\
	do{	\
		int _ii_ = 0;	\
		if(len)	\
		{	\
			for(_ii_=0; _ii_<len; _ii_++)	\
			{	\
				if(!_ii_)	\
				{	\
					BC_PT_DBG_FUN(BC_MODULE_SNMP, "oid:%d", (bc_int32)oid[_ii_]);	\
				}	\
				else	\
				{	\
					BC_PT_DBG_SMP(BC_MODULE_SNMP,".%d", (bc_int32)oid[_ii_]);	\
				}	\
			}BC_PT_DBG_SMP(BC_MODULE_SNMP,"\r\n");	\
		}	\
	}while(0)

/*½öµ±SETÊ±²ÅÔÚ¸÷½ÚµãµÄSETº¯ÊýÖÐÊ¹ÓÃ£¬GET/GETNEXTÊ±²»Ê¹ÓÃ*/
#define SNMP_NODE_HEADER_COMPLEX(list, vp, name, len, exact, varlen, w_method)	\
	do{	\
		if(!(node = header_complex(list, vp, name, len,exact ,varlen, w_method)))	\
		{	\
			return SNMP_ERR_NOSUCHNAME;	\
		}	\
	}while(0)

/*
	modify by bain.wang@outlook.com.
	
	Usage:
		row_status_func: when table contain of rowStatus node, row_status_func is handler function,  column_rowstatus is num of rowStatus node.
		otherwise: (no RowStatus node), row_status_func set NULL, column_rowstatus set SNMP_TABLE_NO_ROW_STATUS.(-1)
*/
#define SNMP_HDL_HEADER_COMPLEX(list, vp, name, len, exact, varlen, w_method, row_status_func, column_rowstatus)	\
		do{	\
			if(!(node = header_complex(list, vp, name, len,exact ,varlen, w_method)))	\
			{	\
				if(vp->magic == column_rowstatus)	\
				{	\
					*w_method = row_status_func;	\
				}	\
				return NULL;	\
			}	\
		}while(0)
				
#define SNMP_FIND_HEADER_COMPLEX_RETURN_NO_SUCHNAME(list, vp, name, len, exact, varlen, w_method)	\
	do{	\
		if(!(node = header_complex(list, vp, name, len,exact ,varlen, w_method)))\
		{\
			return SNMP_ERR_NOSUCHNAME;	\
		}\
	}while(0)

		
#define SNMP_FIND_HEADER_COMPLEX_RETURN_NULL(list, vp, name, len, exact, varlen, w_method)	\
	do{	\
		if(!(node = header_complex(list, vp, name, len,exact ,varlen, w_method)))	\
		{	\
			return NULL;	\
		}	\
	}while(0)

		
#define SNMP_CHECK_INT_RANGE(val, low, high)	\
	do\
	{\
		if(val < low || val > high)\
		{\
			BC_PT_FUN_TAG(BC_MODULE_SNMP);\
			return SNMP_ERR_WRONGVALUE;\
		}\
	}\
	while(0)
		
#define SNMP_VALUE_TYPE_CHECK(t)\
	do\
	{\
		if(var_val_type != t)\
		{\
			return SNMP_ERR_WRONGTYPE;\
		}\
	}\
	while(0)

#endif	

typedef FindVarMethod			snmp_find_var_callback;
typedef netsnmp_subtree		snmp_ns_subtree;
typedef Netsnmp_Node_Handler	snmp_ns_node_handler;
#define snmp_ns_pt_dbg		DEBUGMSGTL

#define	SNMP_NETSNMP_OLD_API_NAME	"old_api"

/*
	for scalar
*/

#define SNMP_NODE_SCALAR_OP_TYPE_RO			HANDLER_CAN_RONLY
#define SNMP_NODE_SCALAR_OP_TYPE_RW 		HANDLER_CAN_RWRITE
#define SNMP_NODE_SCALAR_OP_TYPE_SETONLY 	HANDLER_CAN_SET_ONLY
#define SNMP_NODE_SCALAR_OP_TYPE_DEF 		HANDLER_CAN_DEFAULT

#define SNMP_SUBTREE_ATTACHED	    	0x02

typedef struct{
	const char *descr;
	snmp_ns_node_handler *method;
	const oid *regoid;
	size_t oid_len;
	int modes;
}snmp_scalar_type_t;

#define SUBTREE_MAX_CACHE_SIZE     32
typedef struct lookup_cache_s {
   snmp_ns_subtree *next;
   snmp_ns_subtree *previous;
} lookup_cache;

typedef struct lookup_cache_context_s {
   char *context;
   struct lookup_cache_context_s *next;
   int thecachecount;
   int currentpos;
   lookup_cache cache[SUBTREE_MAX_CACHE_SIZE];
} lookup_cache_context;


#define snmp_reg_conti_check(_pir_)	\
	do{	\
		if(_pir_ == DEFAULT_MIB_PRIORITY)	\
			goto SUBTREE_COPY_ERR;	\
	}while(0)



#define MASTER_AGENT 0
#define SNMP_INLINE NETSNMP_INLINE
#define SNMP_STATIC_INLINE NETSNMP_STATIC_INLINE

#define VARSIZE(n)    variable##n

#define SNMP_STR(s)	#s

#define SNMP_MIB_SCALAR_INFO_INIT(node, mode)	\
	SNMP_STR(node), __handle_##node, node##_oid, OID_LENGTH(node##_oid), mode

#define SNMP_REGISTER_TABLE(name)	\
	SNMP_REGISTER_MIB(SNMP_STR(name), name##_variables, VARSIZE(2), name##_variables_oid)

/* ex define for mib2-ipAddrTable */
#define SNMP_REGISTER_TABLE_FOR_MIB2_IPADDR(name)	\
	SNMP_REGISTER_MIB(SNMP_STR(name), name##_variables, VARSIZE(1), name##_variables_oid)
	
SNMP_INLINE int
snmp_check_vb_type(const netsnmp_variable_list *var, int type );
void snmp_get_oid_index(netsnmp_variable_list *reqvb, int idxnum, int oids[SNMP_OID_INDEX_MAX]);
void snmp_pt_oid(netsnmp_variable_list *reqvb);

bc_int32 snmp_regitster_mib_proc(const char *moduleName,
                         struct variable *var,
                         size_t varsize,
                         size_t numvars,
                         const oid * mibloc,
                         size_t mibloclen,
                         int priority,
                         int range_subid,
                         oid range_ubound,
                         netsnmp_session * ss,
                         const char *context, int timeout, int flags);


#define SNMP_REGISTER_MIB(descr, var, vartype, theoid)	\
	do{	\
		if(snmp_regitster_mib_proc(descr, (struct variable *) var, sizeof(struct vartype), \
               		sizeof(var)/sizeof(struct vartype),                     \
               		theoid, sizeof(theoid)/sizeof(oid), DEFAULT_MIB_PRIORITY, 0, 0, NULL, "", -1, 0) != MIB_REGISTERED_OK)	\
		{	\
				BC_PT_ERROR(BC_MODULE_SNMP, "register_mib %s registration failed.\n", descr);	\
				snmp_ns_pt_dbg(("register_mib", "%s registration failed.\n", descr));	\
		}	\
		else	\
		{	\
			BC_PT_EVENT(BC_MODULE_SNMP, "register_mib %s registration successed.\n", descr);	\
		}	\
	}while(0)

#define SNMP_REGISTER_SCALAR_SINGLE(descr, method, regoid, oidlen, modes)	\
	do{	\
		if(snmp_scalar_register_proc(snmp_create_hr_reg	\
				(descr, method, regoid, oidlen, modes)) != MIB_REGISTERED_OK)	\
		{	\
				BC_PT_ERROR(BC_MODULE_SNMP, "register_scalar %s registration failed.\n", descr);	\
				snmp_ns_pt_dbg(("register_scalar", "%s registration failed.\n", descr));	\
		}	\
		else		\
		{	\
			BC_PT_EVENT(BC_MODULE_SNMP, "register_scalar %s registration successed.\n", descr);	\
		}	\
	}while(0)

#if 0
int snmp_scalar_register(snmp_scalar_type_t *scalars, int num);
#define L_SNMP_REGISTER_SCALAR(scalars)	\
	do{	\
		snmp_scalar_register(scalars, sizeof(scalars)/sizeof(snmp_scalar_type_t));	\
	}while(0)
	
#else	
#define SNMP_REGISTER_SCALAR(scalars)	\
	do{	\
		bc_int32 _x_ = 0;	\
		for(_x_=0; _x_<sizeof(scalars)/sizeof(snmp_scalar_type_t); _x_++){	\
			SNMP_REGISTER_SCALAR_SINGLE(scalars[_x_].descr,scalars[_x_].method, scalars[_x_].regoid, scalars[_x_].oid_len, scalars[_x_].modes);	\
		}	\
		BC_PT_DBG_FUN(BC_MODULE_SNMP, "register this scalars finished, total: %d\n", sizeof(scalars)/sizeof(snmp_scalar_type_t));	\
	}while(0)
#endif


int
snmp_set_request_error(netsnmp_agent_request_info *reqinfo,
                          netsnmp_request_info *request, int error_value);


#endif /*__SNMP_CORE_EX_H__*/


