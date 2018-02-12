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



/* note: ģ������Ϊ�˸�ĳЩģ�������ģ�鲿��������չ���� */
#define BC_MODULE_INTERVAL  		0x10000

/* note: �����ģ��IDʱ����Ҫ��bc_modules.c����Ӷ�Ӧ��Ϣ */
/* �����ģ��IDʱ������ĩβ���δ�ţ����޸�bc_func_e�еĶ��塣 */
/*ͬ����bc_err_e��������ģ���MSG*/


#if 1	
/*���APIʱ��ע��������²��裬�����ָ������ڵ�˳��*/

/*
BINCHIE_ADD_API_STEP_A		-	����ģ��ID
BINCHIE_ADD_API_STEP_B		-	����ģ��FUNC����
BINCHIE_ADD_API_STEP_C		-	����ģ��SRV
BINCHIE_ADD_API_STEP_D		-	����ģ��SRV HDL
BINCHIE_ADD_API_STEP_E		-	����ģ��SRV HDL
BINCHIE_ADD_API_STEP_F		-	����ģ�����/��ϢID
BINCHIE_ADD_API_STEP_G		-	����ģ������ַ���
BINCHIE_ADD_API_STEP_H		-	��������ģ������ַ���
BINCHIE_ADD_API_STEP_I		-	����ģ������ַ���
BINCHIE_ADD_API_STEP_J		-     ����ģ�������
BINCHIE_ADD_API_STEP_K		-	����ģ��ID����
BINCHIE_ADD_API_STEP_L		-	����SRVͷ�ļ�

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

	/*�������̲���*/
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

	/*����������µ�ģ��ID*/

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

