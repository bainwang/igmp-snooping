/************************************************************
  Copyright (C), 1988-2014, xxxxx Tech. Co., Ltd.
  FileName: bc_modules.c
  Author: wangbin       Version : 1.0         Date: 2014-2-10
  Description: olt 进程启动文件
  Version: 1.0
  History: 
***********************************************************/


#include "bc_modules.h"
//#include "bc_modules_com_para.h"
#include "bc_err.h"

typedef struct {
	bc_modules_e 	module_id;
	bc_char				module_name[BC_MODULE_NAME_LENGTH];
} bc_module_node_t;

static bc_module_node_t bc_modules_db[] = {
		{BC_MODULE_SYSTEM, 		"SYSTEM"},
			{BC_MODULE_SYSTEM_PCPS, "SYSTEM_PCPS"},
				{BC_MODULE_SYSTEM_PCPS_CLIENT, "SYSTEM_PCPS_CLIENT"},
				{BC_MODULE_SYSTEM_PCPS_SERVER, "SYSTEM_PCPS_SERVER"},
				{BC_MODULE_SYSTEM_PCPS_DEV_FAN, "SYSTEM_PCPS_FAN"},
				{BC_MODULE_SYSTEM_PCPS_DEV_POWER, "SYSTEM_PCPS_POWER"},
				{BC_MODULE_SYSTEM_PCPS_DEV_EDFA, "SYSTEM_PCPS_EDFA"},
				{BC_MODULE_SYSTEM_PCPS_DISPATCHER, "SYSTEM_PCPS_DISPATCHER"},
				{BC_MODULE_SYSTEM_PCPS_DRV_RS485, "SYSTEM_PCPS_DRV_RS485"},

		{BC_MODULE_VLAN, 			"VLAN"},

		{BC_MODULE_VLAN_DRV,				"VLAN_DRV"},
			{BC_MODULE_VLAN_DRV_BCM56540, 		"VLAN_DRV_BCM56540"},
			{BC_MODULE_VLAN_DRV_CS8022,			"VLAN_DRV_CS8022"},
	      	{BC_MODULE_VLAN_CLI, 				"VLAN_CLI"},
			{BC_MODULE_VLAN_DB,			  		"VLAN_DBB"},
			{BC_MODULE_VLAN_SNMP,			  		"VLAN_SNMP"},

			{BC_MODULE_VLAN_ONU, 		  		"VLAN_ONU"},
			{BC_MODULE_VLAN_ONU_CLI,			"VLAN_ONU_CLI"},
			{BC_MODULE_VLAN_ONU_OAM,			"VLAN_ONU_OAM"},
			{BC_MODULE_VLAN_ONU_DB, 		  	"VLAN_ONU_DB"},
		
		{BC_MODULE_PORT, 			"PORT"},
		
			{BC_MODULE_PORT_SYS, 			"PORT_SYS"},
			{BC_MODULE_PORT_DB, 			"PORT_DB"},
			{BC_MODULE_PORT_DRV, 				"PORT_DRV"},
			{BC_MODULE_PORT_DRV_BCM56540,		"PORT_DRV_BCM56540"},
			{BC_MODULE_PORT_DRV_CS8022,			"PORT_DRV_CS8022"},
			{BC_MODULE_PORT_CLI, 				"PORT_CLI"},
			{BC_MODULE_PORT_UNI, 				"PORT_UNI"},
		
        {BC_MODULE_QOS, 						"QOS"},
			{BC_MODULE_QOS_MAP, 						"QOS_MAP"},
			{BC_MODULE_QOS_POLICY, 						"QOS_POLICY"},
		{BC_MODULE_ONU_CLS,                     "ONU_CLS"},
		{BC_MODULE_DBA, 						"DBA"},



		{BC_MODULE_STP, 			"STP"},
			{BC_MODULE_STP_DRV, 				"STP_DRV"},
				{BC_MODULE_STP_DRV_BCM,				"STP_DRV_BCM"},
				{BC_MODULE_STP_DRV_BCM_DEBUG,		"STP_DRV_BCM_DBG"},
				{BC_MODULE_STP_DRV_CS, 				"STP_DRV_CS"},
			{BC_MODULE_STP_API, 				"STP_API"},
				{BC_MODULE_STP_API_SERVER,			"STP_API_SERVER"},
				{BC_MODULE_STP_API_COMMON,			"STP_API_COMMON"},
				{BC_MODULE_STP_API_CLIENT,			"STP_API_CLIENT"},
				{BC_MODULE_STP_API_RX,				"STP_API_RX"},
				{BC_MODULE_STP_API_CALLBACK,		"STP_API_CALLBACK"},

			{BC_MODULE_STP_PROT, 				"STP_PROTOCOL"},
				{BC_MODULE_STP_PROT_IPI,			"STP_PROTOCOL_IPI"},
					{BC_MODULE_STP_PROT_IPI_THREAD, 		"STP_PROTOCOL_IPI_THREAD"},
					{BC_MODULE_STP_PROT_IPI_API,	 		"STP_PROTOCOL_IPI_API"},
						
					{BC_MODULE_STP_PROT_IPI_CALL, 			"STP_PROTOCOL_IPI_CALL"},
					{BC_MODULE_STP_PROT_IPI_NSM_CLIENT, 	"STP_PROTOCOL_IPI_NSM_CLIENT"},
					{BC_MODULE_STP_PROT_IPI_BPDU_RX, 		"STP_PROTOCOL_IPI_BPDU_RX"},
					{BC_MODULE_STP_PROT_IPI_BPDU_PARSE, 	"STP_PROTOCOL_IPI_BPDU_PARSE"},
					{BC_MODULE_STP_PROT_IPI_BPDU_TX, 		"STP_PROTOCOL_IPI_BPDU_TX"},
					{BC_MODULE_STP_PROT_IPI_BPDU_SET_TC, 	"STP_PROTOCOL_IPI_BPDU_SET_TC"},
					{BC_MODULE_STP_PROT_IPI_BPDU_PROCESS, 	"STP_PROTOCOL_IPI_BPDU_PROCESS"},
					{BC_MODULE_STP_PROT_IPI_MSTI_PROTO, 	"STP_PROTOCOL_IPI_MSTI_PROTO"},
					{BC_MODULE_STP_PROT_IPI_ROLE_CIST, 		"STP_PROTOCOL_IPI_ROLE_CIST"},
					{BC_MODULE_STP_PROT_IPI_ROLE_MSTI, 		"STP_PROTOCOL_IPI_ROLE_MSTI"},
					{BC_MODULE_STP_PROT_IPI_STAT_CIST, 		"STP_PROTOCOL_IPI_STAT_CIST"},
					{BC_MODULE_STP_PROT_IPI_STAT_MSTI, 		"STP_PROTOCOL_IPI_STAT_MSTI"},



		{BC_MODULE_STATS, 		"STATS"},
		{BC_MODULE_IGMP, 			"IGMP"},
		{BC_MODULE_IGMP_CLI, 			"IGMP_CLI"},
		{BC_MODULE_IGMP_DRV, 			"IGMP_DRV"},
		{BC_MODULE_ALARM, 		"ALARM"},		
		{BC_MODULE_ALARM_CLI, 		"ALARM_CLI"},
		{BC_MODULE_ALARM_API, 		"ALARM_API"},
		{BC_MODULE_ALARM_THREAD, 		"ALARM_THREAD"},
	
		{BC_MODULE_ACL, 			"ACL"},
		{BC_MODULE_ACL_CLI,					"ACL_CLI"},
		{BC_MODULE_ACL_API, 				"ACL_API"},
		{BC_MODULE_ACL_DRV, 				"ACL_DRV"},
		
		{BC_MODULE_MPCP, 			"MPCP"},
		
		{BC_MODULE_OAM, 			"OAM"},
			{BC_MODULE_OAM_API, 			"OAM API"},
			{BC_MODULE_OAM_API_SERVER, 			"OAM_API_SERVER"},
			{BC_MODULE_OAM_API_CLIENT, 			"OAM_API_CLIENT"},
			{BC_MODULE_OAM_EVENT, 				"OAM_EVENT"},
			{BC_MODULE_OAM_UPGRADE, 			"OAM_UPGRADE"},
			
		{BC_MODULE_PSG, 			"PSG"},
		{BC_MODULE_MIRROR, 		"MIRROR"},
		{BC_MODULE_TRUNK, 		"TRUNK"},
		{BC_MODULE_TRUNK_DRV, 		"TRUNK_DRV"},
		{BC_MODULE_P2P, 			"P2P"},
		
		{BC_MODULE_BCMP, 			"BCMP"},

		{BC_MODULE_CLI, 			"CLI"},
			{BC_MODULE_CLI_KERNEL,		"CLI_KERNEL"},
				{BC_MODULE_CLI_KERNEL_ALIAS,		"CLI_KERNEL_ALIAS"},
				{BC_MODULE_CLI_KERNEL_CORE,			"CLI_KERNEL_CORE"},
				{BC_MODULE_CLI_KERNEL_EDIT,			"CLI_KERNEL_EDIT"},
				{BC_MODULE_CLI_KERNEL_MAINPROCESS,	"CLI_KERNEL_MAINPROCESS"},
				{BC_MODULE_CLI_KERNEL_PARA,			"CLI_KERNEL_PARA"},
				{BC_MODULE_CLI_KERNEL_VIO,			"CLI_KERNEL_VIO"},
				{BC_MODULE_CLI_KERNEL_VT100,		"CLI_KERNEL_VT100"},
				{BC_MODULE_CLI_KERNEL_SYS_CMD,		"CLI_KERNEL_SYS_CMD"},
				{BC_MODULE_CLI_KERNEL_BNR,			"CLI_KERNEL_BNR"},
				{BC_MODULE_CLI_KERNEL_BNR_CMD,		"CLI_KERNEL_BNR_CMD"},
				{BC_MODULE_CLI_KERNEL_PSEUDO, 		"CLI_KERNEL_PSEUDO"},

			{BC_MODULE_CLI_CMDS,		"CLI_CMDS"},
				{BC_MODULE_CLI_CMD_BASE, 			"CLI_CMD_BASE"},
				{BC_MODULE_CLI_CMD_DEMOMODULE,		"CLI_CMD_DEMOMODULE"},
				{BC_MODULE_CLI_CMD_FDB,				"CLI_CMD_FDB"},
				{BC_MODULE_CLI_CMD_FDB_DBG, 		"CLI_CMD_FDB_DBG"},
				{BC_MODULE_CLI_CMD_PCPS,			"CLI_CMD_PCPS"},
				{BC_MODULE_CLI_CMD_PCPS_DBG,		"CLI_CMD_PCPS_DBG"},
				{BC_MODULE_CLI_CMD_STP,				"CLI_CMD_STP"},
				{BC_MODULE_CLI_CMD_STP_DBG,			"CLI_CMD_STP_DBG"},
				{BC_MODULE_CLI_CMD_IPCDEBUG,		"CLI_CMD_IPCDEBUG"},
				{BC_MODULE_CLI_CMD_ACL,				"CLI_CMD_ACL"},
		
		{BC_MODULE_SNMP, 			"SNMP"},
		{BC_MODULE_TRAP, 			"TRAP"},
		{BC_MODULE_WEB,				"WEB"},
		
		{BC_MODULE_PLATFORM, 	         "PLATFORM"},
		{BC_MODULE_PLATFORM_UART,        "PLATFORM_UART"},
		{BC_MODULE_PLATFORM_CLOCK_CLI,   "PLATFORM_CLOCK"},
		{BC_MODULE_PLATFORM_MONITOR_CLI, "PLATFORM_MONITOR"},
		{BC_MODULE_PLATFORM_DEBUG_CLI,   "PLATFORM_DEBUG"},
		{BC_MODULE_PLATFORM_I2C,         "PLATFORM_I2C"},
		
		{BC_MODULE_UTILI,			"UTILI"},
		{BC_MODULE_PRINT,			"PT"},
		{BC_MODULE_IPC,				"IPC"},
		{BC_MODULE_IPC_TRANS,		"IPC_TRANS"},
		{BC_MODULE_SESSION,	"SESSION"},
		
		{BC_MODULE_FS,				"FILESYS"},
		{BC_MODULE_FILETRANS,	"FILETRANS"},
		{BC_MODULE_BOARD, 		"BOARD"},
		{BC_MODULE_VFS,				"VFS"},
		{BC_MODULE_SWAP,			"SWAP"},
		{BC_MODULE_FDB, 			"FDB"},

		{BC_MODULE_FDB_DRV,						"FDB_DRV"},
		{BC_MODULE_FDB_DRV_UTIL,				"FDB_DRV_UTIL"},
		{BC_MODULE_FDB_DRV_BCM,			"FDB_DRV_BCM"},
		{BC_MODULE_FDB_DRV_BCM_DBG,		"FDB_DRV_BCM_DBG"},
		{BC_MODULE_FDB_DRV_CS8022,				"FDB_DRV_CS8022"},
		{BC_MODULE_FDB_DRV_CS8022_DBG,			"FDB_DRV_CS8022_DBG"},
		{BC_MODULE_FDB_API_SERVER,				"FDB_API_SERVER"},
              {BC_MODULE_FDB_API_SERVER_CS8022_DBG, "FDB_ARP_SERVER_CS8022_DBG"},      
		{BC_MODULE_FDB_API_CLIENT,				"FDB_API_CLIENT"},
              {BC_MODULE_FDB_API_CLIENT_CS8022_DBG,  "FDB_API_CLIENT_CS8022_DBG"},      
		
		{BC_MODULE_LOG,			"LOG"},
		{BC_MODULE_PKT,				"PKT"},
		{BC_MODULE_ACCOUNT,	"ACCOUNT"},
		{BC_MODULE_INTF,			"INTF"},
		{BC_MODULE_STORMCTRL, "STORMCTRL"},
		
		{BC_MODULE_RATECTRL,	"RATECTRL"},
		{BC_MODULE_PORTISO,	"PORTISO"},
		{BC_MODULE_SNTP,			"SNTP"},
		{BC_MODULE_ONUMGMT,	"ONUMGMT"},
		{BC_MODULE_PING,			"PING"},

		{BC_MODULE_8022,			"8022"},
		{BC_MODULE_SWCHIP,		"SWCHIP"},
		{BC_MODULE_CFGMGMT,	"CFGMGMT"},
		{BC_MODULE_USERMGMT,	"USERMGMT"},
		{BC_MODULE_TEMP,		"TEMP"},
		{BC_MODULE_MEM,		"MEM"},
		{BC_MODULE_FAN,			"FAN"},
		{BC_MODULE_PWR,		"POWER"},
		{BC_MODULE_LWIP,		"LWIP"},
		{BC_MODULE_L3,          "L3"},
		{BC_MODULE_EDFA,      "EDFA"},
};


/*************************************************
  Function: bc_modules_get_module_name
  Description: get the module name
  Input: 
  			module_id:	module id
  Output:
  			NULL
  Return:
  			if module id exist 
  			    return module name
  			else
  			    return NULL
  Note:           
  History:        
    1. Date:
       Author:
       Modification:
*************************************************/
extern bc_char *bc_modules_get_module_name(bc_modules_e module_id)
{
	bc_uint32 idx;
	bc_uint32 modules_num = sizeof(bc_modules_db)/sizeof(bc_module_node_t);
	
	for (idx = 0; idx < modules_num; idx++)
	{
		if (bc_modules_db[idx].module_id == module_id)
			return bc_modules_db[idx].module_name;
	}

	return NULL;
}


/*************************************************
  Function: bc_modules_valid_id
  Description: check the module id is whether or not valid
  Input: 
  			module_id:	module id
  Output:
  			NULL
  Return:
  			if equal BC_ERR_OK: valid
  			else: invalid
  Note:           
			the module id check:
				1. the module range
				2. module id % BC_MODULE_INTERVAL == 0
*************************************************/
extern bc_int32 bc_modules_valid_id(bc_modules_e module_id)
{
	if (module_id < BC_MODULE_SYSTEM || module_id >= BC_LAST_MODULE)
	{
		return BC_ERR_OUT_OF_RANGE;
	}

#if 0
	if (module_id%BC_MODULE_INTERVAL != 0)
	{
		return BC_ERR_INVALID_INDEX;
	}
#endif
	
	return BC_ERR_OK;
}



