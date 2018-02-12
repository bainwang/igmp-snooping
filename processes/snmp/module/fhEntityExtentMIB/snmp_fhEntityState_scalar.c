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

#include "snmp_fhEntityState_scalar.h"
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
	int fhEntityCpuUsage;
	int fhEntityMemUsage;
}vir_data_fhEntityState_scalar_t;
static vir_data_fhEntityState_scalar_t g_vir_data_fhEntityState_scalar;
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
	memset(&g_vir_data_fhEntityState_scalar, 0 , sizeof(g_vir_data_fhEntityState_scalar));

	g_vir_data_fhEntityState_scalar.fhEntityCpuUsage = 30;
	g_vir_data_fhEntityState_scalar.fhEntityMemUsage = 40;

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

static bc_boolean __snmp_fhEntityState_scalar_update()
{
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	BC_PT_FUN_TAG(BC_MODULE_SNMP);

	if(snmp_is_update(&update_time))
	{
		vir_api_get_data();
	}
	return TRUE;
}		

static bc_int32 __handle_fhEntityCpuUsage(netsnmp_mib_handler *handler,
                  netsnmp_handler_registration *reginfo,
                  netsnmp_agent_request_info *reqinfo,
                  netsnmp_request_info *requests)
{
	int ret = SNMP_ERR_NOERROR;
	
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
		
	switch (reqinfo->mode)
	{
	case MODE_GET:
		if (!__snmp_fhEntityState_scalar_update())
		{
			return SNMP_ERR_GENERR;
		}
		snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER, &g_vir_data_fhEntityState_scalar.fhEntityCpuUsage, sizeof(g_vir_data_fhEntityState_scalar.fhEntityCpuUsage));
		break;

	default:
		snmp_log(LOG_ERR, "unknown mode (%d) in handle_fhEntityCpuUsage\n", reqinfo->mode);
		return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}

static bc_int32 __handle_fhEntityMemUsage(netsnmp_mib_handler *handler,
                  netsnmp_handler_registration *reginfo,
                  netsnmp_agent_request_info *reqinfo,
                  netsnmp_request_info *requests)
{
	int ret = SNMP_ERR_NOERROR;
	
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
		
	switch (reqinfo->mode)
	{
	case MODE_GET:
		if (!__snmp_fhEntityState_scalar_update())
		{
			return SNMP_ERR_GENERR;
		}
		snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER, &g_vir_data_fhEntityState_scalar.fhEntityMemUsage, sizeof(g_vir_data_fhEntityState_scalar.fhEntityMemUsage));
		break;

	default:
		snmp_log(LOG_ERR, "unknown mode (%d) in handle_fhEntityMemUsage\n", reqinfo->mode);
		return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}

#if 1
const oid fhEntityCpuUsage_oid[] = { 1, 3, 6, 1, 4, 1, 11408, 11, 1, 1, 1, 1 };
const oid fhEntityMemUsage_oid[] = { 1, 3, 6, 1, 4, 1, 11408, 11, 1, 1, 1, 2 };

snmp_scalar_type_t fhEntityState_scalar_variables[] = {
	{SNMP_MIB_SCALAR_INFO_INIT(fhEntityCpuUsage, HANDLER_CAN_RONLY)},
	{SNMP_MIB_SCALAR_INFO_INIT(fhEntityMemUsage, HANDLER_CAN_RONLY)}
};

#endif

void snmp_fhEntityState_scalar_init(void)
{
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	SNMP_MIB_FFLUSH_INIT();

	DEBUGMSGTL(("fhEntityState_scalar", "Initializing\n"));
	SNMP_REGISTER_SCALAR(fhEntityState_scalar_variables);

	BC_PT_FUN_LEAVE(BC_MODULE_SNMP);
}

