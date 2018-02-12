/************************************************************
  FileName:
  Author:  bain.wang@outlook.com      Version :  1.0        Date:2017-04-04
  Description:                   
  Version:                        
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/

#ifndef __bc_modules_h__
#define __bc_modules_h__

#include "bc_common_defs.h"
#include "bc_modules_com_para.h"



/* note: 模块间隔是为了给某些模块加入子模块部分做的扩展保留 */
#define BC_MODULE_INTERVAL  		0x10000

/* note: 添加新模块ID时，需要在bc_modules.c中添加对应信息 */
/* 添加新模块ID时，请在末尾依次存放，并修改bc_func_e中的定义。 */
/*同步在bc_err_e中添加相关模块的MSG*/


#if 1	
/*添加API时请注意完成如下步骤，并保持各步骤内的顺序*/

/*
BINCHIE_ADD_API_STEP_A		-	定义模块ID
BINCHIE_ADD_API_STEP_B		-	集合模块FUNC类型
BINCHIE_ADD_API_STEP_C		-	定义模块SRV
BINCHIE_ADD_API_STEP_D		-	集合模块SRV HDL
BINCHIE_ADD_API_STEP_E		-	定义模块SRV HDL
BINCHIE_ADD_API_STEP_F		-	定义模块错误/消息ID
BINCHIE_ADD_API_STEP_G		-	集合模块错误字符串
BINCHIE_ADD_API_STEP_H		-	集合所有模块错误字符串
BINCHIE_ADD_API_STEP_I		-	定义模块错误字符串
BINCHIE_ADD_API_STEP_J		-     集合模块错误码
BINCHIE_ADD_API_STEP_K		-	定义模块ID名称
BINCHIE_ADD_API_STEP_L		-	包含SRV头文件

*/

#endif


#define BINCHIE_ADD_API_STEP_A

typedef enum
{
	BC_FIRST_MODULE 				= 0, 

	BC_MODULE_SYSTEM 			= BC_MODULE_INTERVAL + BC_FIRST_MODULE,
	
	BC_MODULE_IGMP 				= BC_MODULE_INTERVAL + BC_MODULE_SYSTEM,
	     BC_MODULE_IGMP_DRV,
	
	BC_MODULE_PLATFORM			= BC_MODULE_INTERVAL + BC_MODULE_IGMP,
		BC_MODULE_PLATFORM_MONITOR_CLI,
		BC_MODULE_PLATFORM_CLOCK_CLI,

	BC_MODULE_UTILI				= BC_MODULE_INTERVAL + BC_MODULE_PLATFORM,
	BC_MODULE_PRINT				= BC_MODULE_INTERVAL + BC_MODULE_UTILI,
	BC_MODULE_VFS					= BC_MODULE_INTERVAL + BC_MODULE_PRINT,

	BC_MODULE_LOG					= BC_MODULE_INTERVAL + BC_MODULE_VFS,
	
	BC_MODULE_IPC					= BC_MODULE_INTERVAL + BC_MODULE_LOG,
		BC_MODULE_IPC_TRANS,

	BC_MODULE_SESSION			= BC_MODULE_INTERVAL + BC_MODULE_IPC,

	/*非主进程测试*/
	BC_MODULE_TEST_PROC 			= BC_MODULE_INTERVAL + BC_MODULE_SESSION,
	
	BC_MODULE_TEST 				= BC_MODULE_INTERVAL + BC_MODULE_TEST_PROC,
	
	BC_MODULE_SNMP 				= BC_MODULE_INTERVAL + BC_MODULE_TEST,

	BC_MODULE_CLI 				= BC_MODULE_INTERVAL + BC_MODULE_SNMP,
		BC_MODULE_CLI_KERNEL,
		BC_MODULE_CLI_KERNEL_ALIAS,
		BC_MODULE_CLI_KERNEL_CORE,
		BC_MODULE_CLI_KERNEL_EDIT,
		BC_MODULE_CLI_KERNEL_MAINPROCESS,
		BC_MODULE_CLI_KERNEL_PARA,
		BC_MODULE_CLI_KERNEL_VIO,
		BC_MODULE_CLI_KERNEL_VT100,
		BC_MODULE_CLI_KERNEL_SYS_CMD,
		BC_MODULE_CLI_KERNEL_BNR,
		BC_MODULE_CLI_KERNEL_BNR_CMD,
		BC_MODULE_CLI_KERNEL_PSEUDO,
		BC_MODULE_CLI_CMDS,
		BC_MODULE_CLI_CMD_BASE,
		BC_MODULE_CLI_CMD_DEMOMODULE,
		BC_MODULE_CLI_CMD_FDB,
		BC_MODULE_CLI_CMD_FDB_DBG,
		BC_MODULE_CLI_CMD_PCPS,
		BC_MODULE_CLI_CMD_PCPS_DBG,
		BC_MODULE_CLI_CMD_STP,
		BC_MODULE_CLI_CMD_STP_DBG,
		BC_MODULE_CLI_CMD_IPCDEBUG,
		BC_MODULE_CLI_CMD_ACL,
		BC_MODULE_CLI_CMD_DBA,
		BC_MODULE_CLI_CMD_QOS,
		BC_MODULE_CLI_CMD_IGMP,
		BC_MODULE_CLI_CMD_STATS,

	BC_MODULE_USERMGMT 				= BC_MODULE_INTERVAL + BC_MODULE_CLI,
	
	BC_MODULE_BINCHIE 				= BC_MODULE_INTERVAL + BC_MODULE_USERMGMT,

	BC_MODULE_FILETRANS 				= BC_MODULE_INTERVAL + BC_MODULE_BINCHIE,

	BC_MODULE_CFGMGMT					= BC_MODULE_INTERVAL + BC_MODULE_FILETRANS,

	BC_MODULE_STATS					= BC_MODULE_INTERVAL + BC_MODULE_CFGMGMT,

	/*在这里添加新的模块ID*/

	BC_LAST_MODULE					= BC_MODULE_INTERVAL + BC_MODULE_STATS,
	
} bc_modules_e;

#define BC_MODULES_NUM (BC_LAST_MODULE/BC_MODULE_INTERVAL)

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
extern bc_char *bc_modules_get_module_name(bc_modules_e module_id);

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
extern bc_int32 bc_modules_valid_id(bc_modules_e module_id);

#endif

