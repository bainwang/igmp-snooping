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

#include "snmp_mib2_system_scalar.h"
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
bc_boolean snmp_mib2_system_get(snmp_mib2_sys_mib_t *sys_mib)	
{
	if(!sys_mib)
		return FALSE;

	oid sys_obj_id[] = {1, 3, 6, 1, 4, 1, 11408, 11};

	memset(sys_mib, 0, sizeof(snmp_mib2_sys_mib_t));
	strcpy(sys_mib->sysDescr, "PTN:xxxx v1.0");
	memcpy(sys_mib->sysObjectID, sys_obj_id, sizeof(sys_obj_id));
	sys_mib->sysObjectID_len = sizeof(sys_obj_id) / sizeof(oid);
	sys_mib->sysUpTime = 1000;
	strcpy(sys_mib->sysContact, "FiberHome(www.FiberHome.com)");
	strcpy(sys_mib->sysName, "PTN");
	strcpy(sys_mib->sysLocation, "sample sysLocation factory default");
	sys_mib->sysServices = 75;
}
#if 1
static bc_int32 __handle_sysDescr(netsnmp_mib_handler *handler,
                  netsnmp_handler_registration *reginfo,
                  netsnmp_agent_request_info *reqinfo,
                  netsnmp_request_info *requests)
{
	int ret = SNMP_ERR_NOERROR;
	snmp_mib2_sys_mib_t	sys_mib;
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
		
	switch (reqinfo->mode)
	{
	case MODE_GET:
		if (!snmp_mib2_system_get(&sys_mib))
		{
			return SNMP_ERR_GENERR;
		}
		BC_PT_DBG_FUN(BC_MODULE_SNMP, "sysDescr:%s\r\n", sys_mib.sysDescr);
		snmp_set_var_typed_value(
									requests->requestvb, 
									ASN_OCTET_STR, 
									sys_mib.sysDescr, 
									strlen(sys_mib.sysDescr));
		break;
	default:
		snmp_log(LOG_ERR, "unknown mode (%d) in handle_sysDescr\n", reqinfo->mode);
		return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
static bc_int32 __handle_sysObjectID(netsnmp_mib_handler *handler,
                  netsnmp_handler_registration *reginfo,
                  netsnmp_agent_request_info *reqinfo,
                  netsnmp_request_info *requests)
{
	int ret = SNMP_ERR_NOERROR;
	snmp_mib2_sys_mib_t	sys_mib;
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
		
	switch (reqinfo->mode)
	{
	case MODE_GET:
		if (!snmp_mib2_system_get(&sys_mib))
		{
			return SNMP_ERR_GENERR;
		}
		BC_PT_DBG_FUN(BC_MODULE_SNMP, "sysDescr:%s\r\n", sys_mib.sysDescr);
		snmp_set_var_typed_value(
									requests->requestvb, 
									ASN_OBJECT_ID, 
									&sys_mib.sysObjectID, 
									sizeof(sys_mib.sysObjectID));
		break;
	default:
		snmp_log(LOG_ERR, "unknown mode (%d) in handle_sysObjectID\n", reqinfo->mode);
		return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
#if 0
static bc_int32 __handle_sysUpTime(netsnmp_mib_handler *handler,
                  netsnmp_handler_registration *reginfo,
                  netsnmp_agent_request_info *reqinfo,
                  netsnmp_request_info *requests)
{
	int ret = SNMP_ERR_NOERROR;
	snmp_mib2_sys_mib_t	sys_mib;
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
		
	switch (reqinfo->mode)
	{
	case MODE_GET:
		if (!snmp_mib2_system_get(&sys_mib))
		{
			return SNMP_ERR_GENERR;
		}
		BC_PT_DBG_FUN(BC_MODULE_SNMP, "sysDescr:%s\r\n", sys_mib.sysDescr);
		snmp_set_var_typed_value(
									requests->requestvb, 
									ASN_TIMETICKS, 
									&sys_mib.sysUpTime, 
									sizeof(sys_mib.sysUpTime));
		break;
	default:
		snmp_log(LOG_ERR, "unknown mode (%d) in handle_sysUpTime\n", reqinfo->mode);
		return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}

static bc_int32 __handle_sysContact(netsnmp_mib_handler *handler,
                  netsnmp_handler_registration *reginfo,
                  netsnmp_agent_request_info *reqinfo,
                  netsnmp_request_info *requests)
{
	int ret = SNMP_ERR_NOERROR;
	snmp_mib2_sys_mib_t	sys_mib;
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
		
	switch (reqinfo->mode)
	{
	case MODE_GET:
		if (!snmp_mib2_system_get())
		{
			return SNMP_ERR_GENERR;
		}
		BC_PT_DBG_FUN(BC_MODULE_SNMP, "sysContact:%s\r\n", sys_mib.sysContact);
		snmp_set_var_typed_value(
									requests->requestvb, 
									ASN_OCTET_STR, 
									sys_mib.sysContact, 
									strlen(sys_mib.sysContact));
		break;

	default:
		snmp_log(LOG_ERR, "unknown mode (%d) in handle_sysContact\n", reqinfo->mode);
		return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
#endif
static bc_int32 __handle_sysName(netsnmp_mib_handler *handler,
                  netsnmp_handler_registration *reginfo,
                  netsnmp_agent_request_info *reqinfo,
                  netsnmp_request_info *requests)
{
	int ret = SNMP_ERR_NOERROR;
	snmp_mib2_sys_mib_t	sys_mib;
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
		
	switch (reqinfo->mode)
	{
	case MODE_GET:
		if (!snmp_mib2_system_get(&sys_mib))
		{
			return SNMP_ERR_GENERR;
		}
		BC_PT_DBG_FUN(BC_MODULE_SNMP, "sysName:%s\r\n", sys_mib.sysName);
		snmp_set_var_typed_value(
									requests->requestvb, 
									ASN_OCTET_STR, 
									sys_mib.sysName, 
									strlen(sys_mib.sysName));
		break;

	default:
		snmp_log(LOG_ERR, "unknown mode (%d) in handle_sysContact\n", reqinfo->mode);
		return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
#if 0
static bc_int32 __handle_sysLocation(netsnmp_mib_handler *handler,
                  netsnmp_handler_registration *reginfo,
                  netsnmp_agent_request_info *reqinfo,
                  netsnmp_request_info *requests)
{
	int ret = SNMP_ERR_NOERROR;
	snmp_mib2_sys_mib_t	sys_mib;
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
		
	switch (reqinfo->mode)
	{
	case MODE_GET:
		/*更新到全局结构体中*/
		if (!snmp_mib2_system_get())
		{
			return SNMP_ERR_GENERR;
		}
		BC_PT_DBG_FUN(BC_MODULE_SNMP, "sysLocation:%s\r\n", sys_mib.sysLocation);
		snmp_set_var_typed_value(
									requests->requestvb, 
									ASN_OCTET_STR, 
									sys_mib.sysLocation, 
									strlen(sys_mib.sysLocation));
		break;

	default:
		snmp_log(LOG_ERR, "unknown mode (%d) in handle_sysLocation\n", reqinfo->mode);
		return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}

static bc_int32 __handle_sysServices(netsnmp_mib_handler *handler,
                  netsnmp_handler_registration *reginfo,
                  netsnmp_agent_request_info *reqinfo,
                  netsnmp_request_info *requests)
{
	int ret = SNMP_ERR_NOERROR;
	snmp_mib2_sys_mib_t	sys_mib;
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
		
	switch (reqinfo->mode)
	{
	case MODE_GET:
		if (!snmp_mib2_system_get())
		{
			return SNMP_ERR_GENERR;
		}
		BC_PT_DBG_FUN(BC_MODULE_SNMP, "sysDescr:%d\r\n", sys_mib.sysServices);
		snmp_set_var_typed_value(
									requests->requestvb, 
									ASN_INTEGER, 
									&sys_mib.sysServices, 
									sizeof(sys_mib.sysServices));
		break;

	default:
		snmp_log(LOG_ERR, "unknown mode (%d) in handle_sysServices\n", reqinfo->mode);
		return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
#endif
#endif

#if 1
const oid sysDescr_oid[] = { 1, 3, 6, 1, 2, 1, 1, 1 };
const oid sysObjectID_oid[] = { 1, 3, 6, 1, 2, 1, 1, 2 };/*
const oid sysUpTime_oid[] = { 1, 3, 6, 1, 2, 1, 1, 3 };
const oid sysContact_oid[] = { 1, 3, 6, 1, 2, 1, 1, 4 };*/
const oid sysName_oid[] = { 1, 3, 6, 1, 2, 1, 1, 5 };/*
const oid sysLocation_oid[] = { 1, 3, 6, 1, 2, 1, 1, 6 };
const oid sysServices_oid[] = { 1, 3, 6, 1, 2, 1, 1, 7 };
const oid ifNumber_oid[] = { 1, 3, 6, 1, 2, 1, 2, 1 };*/

static snmp_scalar_type_t mib2_system_scalar_variables[] = {
	{SNMP_MIB_SCALAR_INFO_INIT(sysDescr, HANDLER_CAN_RONLY)},
	{SNMP_MIB_SCALAR_INFO_INIT(sysObjectID, HANDLER_CAN_RONLY)},
	{SNMP_MIB_SCALAR_INFO_INIT(sysName, HANDLER_CAN_RWRITE)}
};
#endif
void snmp_mib2_system_scalar_init(void)
{
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	SNMP_MIB_FFLUSH_INIT();
	
	DEBUGMSGTL(("mib2_system", "Initializing\n"));
	SNMP_REGISTER_SCALAR(mib2_system_scalar_variables);
	
	BC_PT_FUN_LEAVE(BC_MODULE_SNMP);
}

