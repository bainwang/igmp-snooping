/*******************************************************************************
  [Author]	   : bain.wang@outlook.com.uestc@gmail.com
  [Version]    : 1.0
  [Date]       : 2017-02-27
  [Description]:

  [Others]     :

  [History]:
	 Date          Modification 							    Initials
	----------     ----------                                   -------
	2017-02-27      Created								   		bain.wang@outlook.com
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

#include "snmp_fhSysExtMIB_scalar.h"
#include "snmp_global.h"
#include "snmp_core_ex.h"


///////////////////////////////////////////////////////////////////////////////
//                                                               			 //
//																			 //
//						外 部 变 量、 函 数 引 用					         //
//																			 //
///////////////////////////////////////////////////////////////////////////////

static time_t update_time;

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//																			 //
//						结   构   体   宏   定   义							 //
//																			 //
///////////////////////////////////////////////////////////////////////////////

/*
 *		当源文件需要定义宏，而头文件又与其它模块头文件中的宏定义有重复定义嫌疑
 *	时，在此处定义。
 */
#if 1
typedef struct
{
	char devType[SNMP_DEV_NAME_LEN];
	bc_ipv4 loopback;
	int enable;
	char snmpVer[SNMP_DEV_NAME_LEN];
	char hostName[SNMP_DEV_NAME_LEN];
	char passWord[SNMP_DEV_NAME_LEN];
	char rcuVersion[SNMP_DEV_NAME_LEN];
}vir_data_fhSysExtMIB_scalar_t;
static vir_data_fhSysExtMIB_scalar_t g_vir_data_fhSysExtMIB_scalar;
#endif
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
static bc_boolean vir_api_get_data()
{
	char buf_ip[32];
	
	memset(&g_vir_data_fhSysExtMIB_scalar, 0 , sizeof(g_vir_data_fhSysExtMIB_scalar));
	strcpy(g_vir_data_fhSysExtMIB_scalar.devType, "devType");
	g_vir_data_fhSysExtMIB_scalar.loopback;
	g_vir_data_fhSysExtMIB_scalar.enable = 1;
	strcpy(g_vir_data_fhSysExtMIB_scalar.snmpVer, "snmpVer");
	strcpy(g_vir_data_fhSysExtMIB_scalar.hostName, "hostName");
	strcpy(g_vir_data_fhSysExtMIB_scalar.passWord, "passWord");
	strcpy(g_vir_data_fhSysExtMIB_scalar.rcuVersion, "rcuVersion");

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

static bc_boolean __snmp_fhSysExtMIB_scalar_update()
{
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	BC_PT_FUN_TAG(BC_MODULE_SNMP);

	if(snmp_is_update(&update_time))
	{
		vir_api_get_data();
	}
	return TRUE;
}		
#if 1
static bc_int32 __handle_devType(netsnmp_mib_handler *handler,
                  netsnmp_handler_registration *reginfo,
                  netsnmp_agent_request_info *reqinfo,
                  netsnmp_request_info *requests)
{
	int ret = SNMP_ERR_NOERROR;
	
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
		
	switch (reqinfo->mode)
	{
	case MODE_GET:
		if (!__snmp_fhSysExtMIB_scalar_update())
		{
			return SNMP_ERR_GENERR;
		}
		snmp_set_var_typed_value(requests->requestvb, ASN_OCTET_STR, &g_vir_data_fhSysExtMIB_scalar.devType, strlen(g_vir_data_fhSysExtMIB_scalar.devType));
		break;
	default:
		snmp_log(LOG_ERR, "unknown mode (%d) in handle_devType\n", reqinfo->mode);
		return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}

static bc_int32 __handle_loopback(netsnmp_mib_handler *handler,
                  netsnmp_handler_registration *reginfo,
                  netsnmp_agent_request_info *reqinfo,
                  netsnmp_request_info *requests)
{
	int ret = SNMP_ERR_NOERROR;
	bc_char ipstr[SNMP_IP_ADDR_LEN];	
	struct sockaddr_in sockaddr;
	
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
		
	switch (reqinfo->mode)
	{
	case MODE_GET:		
		snmp_get_addr_by_name("lo", ipstr);
		sockaddr.sin_addr.s_addr = inet_addr(ipstr);
		/*
		if (!__snmp_fhSysExtMIB_scalar_update())
		{
			return SNMP_ERR_GENERR;
		}*/
		snmp_set_var_typed_value(requests->requestvb, ASN_IPADDRESS, &sockaddr.sin_addr.s_addr, sizeof(sockaddr.sin_addr.s_addr));
	//	snmp_set_var_typed_value(requests->requestvb, ASN_IPADDRESS, &g_vir_data_fhSysExtMIB_scalar.loopback, sizeof(g_vir_data_fhSysExtMIB_scalar.loopback));
		break;
	default:
		snmp_log(LOG_ERR, "unknown mode (%d) in handle_loopback\n", reqinfo->mode);
		return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}

static bc_int32 __handle_enable(netsnmp_mib_handler *handler,
                  netsnmp_handler_registration *reginfo,
                  netsnmp_agent_request_info *reqinfo,
                  netsnmp_request_info *requests)
{
	int ret = SNMP_ERR_NOERROR;
	
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
		
	switch (reqinfo->mode)
	{
	case MODE_GET:
		if (!__snmp_fhSysExtMIB_scalar_update())
		{
			return SNMP_ERR_GENERR;
		}
		snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER, &g_vir_data_fhSysExtMIB_scalar.enable, sizeof(g_vir_data_fhSysExtMIB_scalar.enable));
		break;
	default:
		snmp_log(LOG_ERR, "unknown mode (%d) in handle_enable\n", reqinfo->mode);
		return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}

static bc_int32 __handle_snmpVer(netsnmp_mib_handler *handler,
                  netsnmp_handler_registration *reginfo,
                  netsnmp_agent_request_info *reqinfo,
                  netsnmp_request_info *requests)
{
	int ret = SNMP_ERR_NOERROR;
	
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
		
	switch (reqinfo->mode)
	{
	case MODE_GET:
		if (!__snmp_fhSysExtMIB_scalar_update())
		{
			return SNMP_ERR_GENERR;
		}
		snmp_set_var_typed_value(requests->requestvb, ASN_OCTET_STR, &g_vir_data_fhSysExtMIB_scalar.snmpVer, strlen(g_vir_data_fhSysExtMIB_scalar.snmpVer));
		break;
	default:
		snmp_log(LOG_ERR, "unknown mode (%d) in handle_snmpVer\n", reqinfo->mode);
		return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}

static bc_int32 __handle_hostName(netsnmp_mib_handler *handler,
                  netsnmp_handler_registration *reginfo,
                  netsnmp_agent_request_info *reqinfo,
                  netsnmp_request_info *requests)
{
	int ret = SNMP_ERR_NOERROR;
	
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
		
	switch (reqinfo->mode)
	{
	case MODE_GET:
		if (!__snmp_fhSysExtMIB_scalar_update())
		{
			return SNMP_ERR_GENERR;
		}
		snmp_set_var_typed_value(requests->requestvb, ASN_OCTET_STR, g_vir_data_fhSysExtMIB_scalar.hostName, strlen(g_vir_data_fhSysExtMIB_scalar.hostName));
		break;
	default:
		snmp_log(LOG_ERR, "unknown mode (%d) in handle_hostName\n", reqinfo->mode);
		return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}

static bc_int32 __handle_passWord(netsnmp_mib_handler *handler,
                  netsnmp_handler_registration *reginfo,
                  netsnmp_agent_request_info *reqinfo,
                  netsnmp_request_info *requests)
{
	int ret = SNMP_ERR_NOERROR;
	
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
		
	switch (reqinfo->mode)
	{
	case MODE_GET:
		if (!__snmp_fhSysExtMIB_scalar_update())
		{
			return SNMP_ERR_GENERR;
		}
		snmp_set_var_typed_value(requests->requestvb, ASN_OCTET_STR, g_vir_data_fhSysExtMIB_scalar.passWord, strlen(g_vir_data_fhSysExtMIB_scalar.passWord));
		break;
	default:
		snmp_log(LOG_ERR, "unknown mode (%d) in handle_passWord\n", reqinfo->mode);
		return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}

static bc_int32 __handle_rcuVersion(netsnmp_mib_handler *handler,
                  netsnmp_handler_registration *reginfo,
                  netsnmp_agent_request_info *reqinfo,
                  netsnmp_request_info *requests)
{
	int ret = SNMP_ERR_NOERROR;
	
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
		
	switch (reqinfo->mode)
	{
	case MODE_GET:
		if (!__snmp_fhSysExtMIB_scalar_update())
		{
			return SNMP_ERR_GENERR;
		}
		snmp_set_var_typed_value(requests->requestvb, ASN_OCTET_STR, g_vir_data_fhSysExtMIB_scalar.rcuVersion, strlen(g_vir_data_fhSysExtMIB_scalar.rcuVersion));
		break;
	default:
		snmp_log(LOG_ERR, "unknown mode (%d) in handle_rcuVersion\n", reqinfo->mode);
		return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
#endif

#if 1
const oid devType_oid[] = { 1, 3, 6, 1, 4, 1, 11408, 11, 1, 3, 1 };
const oid loopback_oid[] = { 1, 3, 6, 1, 4, 1, 11408, 11, 1, 3, 2 };
const oid enable_oid[] = { 1, 3, 6, 1, 4, 1, 11408, 11, 1, 3, 3 };
const oid snmpVer_oid[] = { 1, 3, 6, 1, 4, 1, 11408, 11, 1, 3, 4 };
const oid hostName_oid[] = { 1, 3, 6, 1, 4, 1, 11408, 11, 1, 3, 6 };
const oid passWord_oid[] = { 1, 3, 6, 1, 4, 1, 11408, 11, 1, 3, 7 };
const oid rcuVersion_oid[] = { 1, 3, 6, 1, 4, 1, 11408, 11, 1, 3, 8 };

static snmp_scalar_type_t fhSysExtMIB_scalar_variables[] = 
{
	{SNMP_MIB_SCALAR_INFO_INIT(devType, HANDLER_CAN_RONLY)},
	{SNMP_MIB_SCALAR_INFO_INIT(loopback, HANDLER_CAN_RONLY)},
	{SNMP_MIB_SCALAR_INFO_INIT(enable, HANDLER_CAN_RONLY)},
	{SNMP_MIB_SCALAR_INFO_INIT(snmpVer, HANDLER_CAN_RONLY)},
	{SNMP_MIB_SCALAR_INFO_INIT(hostName, HANDLER_CAN_RONLY)},
	{SNMP_MIB_SCALAR_INFO_INIT(passWord, HANDLER_CAN_RONLY)},
	{SNMP_MIB_SCALAR_INFO_INIT(rcuVersion, HANDLER_CAN_RONLY)}
};
#endif


void snmp_fhSysExtMIB_scalar_init(void)
{
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	SNMP_MIB_FFLUSH_INIT();

	DEBUGMSGTL(("fhSysExtMIB_scalar", "Initializing\n"));
	SNMP_REGISTER_SCALAR(fhSysExtMIB_scalar_variables);

	BC_PT_FUN_LEAVE(BC_MODULE_SNMP);
}


