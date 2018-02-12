#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include <signal.h>


#include "bc_common_defs.h"
#include "snmp_global.h"

 /*
	per module head file
*/
#include "snmp_fhEntityExtentMIB.h"
#include "snmp_fhIfExtMIB.h"
#include "snmp_fhSysExtMIB.h"
#include "snmp_privateObject.h"
#include "snmp_mib2_interfaces.h"
#include "snmp_mib2_system.h"
#include "snmp_mib2_ip.h"


#if SNMP_PRJ_NAME_X86
#include "snmp_trap_x86.h"
#else
#include "snmp_trap_610a.h"
#endif

#include "bc_ipc_dev_api.h"
#include "bc_vfs.h"
#include "bc_print.h"
#include "bc_log.h"
#include "bc_platform_init.h"
#include "bc_common_defs.h"
#include "bc_ipc_client.h"
#include "bc_log_client.h"

#include <stdio.h>
#include <string.h>

#define BC_SNMP_PROC_NAME	"snmp"

static bc_int32 keep_running;

#if 1
#define SNMP_AGENT_INIT()	\
	do{	\
		if(init_agent(SNMP_CONFIG_FILE_NAME) != 0){	\
			BC_PT_FUN_TAG(BC_MODULE_SNMP);	\
			return FALSE;	\
		}	\
	}while(0)


#define SNMP_INIT()	\
	do{	\
		init_snmp(SNMP_CONFIG_FILE_NAME);	\
	}while(0)

#define SNMP_STOP_SRV()	\
	do{	\
		signal(SIGTERM, stop_server);	\
		signal(SIGINT, stop_server);	\
	}while(0)

#endif

RETSIGTYPE
stop_server(bc_int32 a)
{
	keep_running = 0;
}

/*
bc_int32 snmp_monitor_snmp_int32()
{
	snmp_time_sleep(5);
}*/

bc_int32 snmp_netsnmp_init()
{
	bc_int32 agentx_subagent = 0;
	bc_int32 background = 0;
	bc_int32 syslog = 0;

	if(agentx_subagent)
	{
		if(netsnmp_ds_set_boolean(NETSNMP_DS_APPLICATION_ID, NETSNMP_DS_AGENT_ROLE, 1) != SNMPERR_SUCCESS)
		{
			BC_PT_FUN_TAG(BC_MODULE_SNMP);
			return FALSE;
		}
	}

	if(background && netsnmp_daemonize(1, !syslog))
	{
		BC_PT_FUN_TAG(BC_MODULE_SNMP);
		return FALSE;
	//	exit(1);	// by bain.wang@outlook.com 
	}
	SOCK_STARTUP;
	
//	snmp_set_do_debugging(0);

	SNMP_AGENT_INIT();
	
	if(!agentx_subagent)
	{
		void init_vacm_vars();
		void init_usmUser();
	}

	SNMP_INIT();
	if(!agentx_subagent)
	{
		init_master_agent();
	}
	
	SNMP_STOP_SRV();
	
	return TRUE;	
}

bc_int32 snmp_mib_init()
{
	/*
		per module init
	*/
	snmp_fhEntityExtentMIB_init();
	snmp_fhIfExtMIB_init();
	snmp_fhSysExtMIB_init();
	snmp_privateObject_init();
	snmp_mib2_system_init();
	snmp_mib2_ip_init();
	snmp_mib2_interfaces_init();

//	init_TestTraps();
//	send_testAlarmNotification_trap();
#if	SNMP_PRJ_NAME_X86
	snmp_trap_init_x86();
#elif SNMP_PRJ_NAME_610A
	if(snmp_trap_init_610a() != TRUE)
	{
		BC_PT_ERROR(BC_MODULE_SNMP,"*****snmp trap init failure!*****\n");
		return 0;
	}
#else
	BC_PT_EVENT(BC_MODULE_SNMP,"unkonw platform, has not trap function!\n");
#endif
	return 0;	
}

bc_int32 snmp_cfg_init()
{
	bc_err_e ret = BC_ERR_OK;
	
	bc_pt_init();
	bc_pt_open_prj_mdl(BC_MODULE_SNMP);
	bc_pt_prt_lvl_open(BC_LVL_BIT_ALL);
	
	bc_platform_init();
#if 1	/*“¿¿µ”⁄IPC*/
	ret = bc_ipc_create(IPC_CLIENT_TYPE_SNMP);
	bc_log_sys_dbg_wrt_client(BC_LOG_BIT_INIT, BC_MODULE_SNMP, "process "BC_SNMP_PROC_NAME" running ....\n");
	if(ret != BC_ERR_OK)
	{
		BC_PT_ERROR(BC_MODULE_SNMP, "Ipc client init failure, ret = 0x%x\n", ret);
		bc_log_sys_dbg_wrt_client(BC_LOG_BIT_ERROR, BC_MODULE_SNMP, "Ipc client init failure\n");
	}
	BC_PT_INIT(BC_MODULE_SNMP, "Ipc client init successful\n");
	bc_log_sys_dbg_wrt_client(BC_LOG_BIT_INIT, BC_MODULE_SNMP, "Ipc client init successful\n");
	
//	bc_dev_thread_show();
#endif
}

bc_int32 main(bc_int32 argc, char **argv)
{
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);

	bc_int32 syslog = 0;

	snmp_cfg_init();
	BC_PT_DBG_FUN(BC_MODULE_SNMP, "snmp_cfg_init successed\n\n");

	if(syslog)
	{
		snmp_enable_calllog();
		BC_PT_EVENT(BC_MODULE_SNMP,"enable snmp calllog...\n");
	}
	else
	{
		snmp_enable_stderrlog();
		BC_PT_EVENT(BC_MODULE_SNMP,"enable snmp stderrlog...\n");
	}

	BC_PT_EVENT(BC_MODULE_SNMP,"init net-snmp core...\n");
	if(snmp_netsnmp_init() != TRUE)
	{
		exit(0);
		BC_PT_DBG_FUN(BC_MODULE_SNMP, "snmp_netsnmp_init failure\n");
	}
	BC_PT_DBG_FUN(BC_MODULE_SNMP, "snmp_netsnmp_init successed\n");
	
	BC_PT_EVENT(BC_MODULE_SNMP,"init mib table and scalar...\n");
	snmp_mib_init();
	BC_PT_DBG_FUN(BC_MODULE_SNMP, "snmp_mib_init successed\n\n");
//	snmp_cfg_init();
//	BC_PT_DBG_FUN(BC_MODULE_SNMP, "snmp_cfg_init successed\n\n");

	keep_running = 1;

	BC_PT_EVENT(BC_MODULE_SNMP,SNMP_CONFIG_FILE_NAME" is up and running.\n\n\n");
//	snmp_log(LOG_INFO, "\n"SNMP_CONFIG_FILE_NAME" is up and running.\n\n\n");

	while(keep_running)
	{
		agent_check_and_process(1);
	}

	snmp_shutdown(SNMP_CONFIG_FILE_NAME);
	SOCK_CLEANUP;

	BC_PT_FUN_LEAVE(BC_MODULE_SNMP);
	return 0;	
}

