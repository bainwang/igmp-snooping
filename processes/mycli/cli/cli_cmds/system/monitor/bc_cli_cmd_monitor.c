/*************************************************
  -------------------------------------------------------------------------
  File name: bc_cli_cmd_monitor.c
  Author:       Version:        Date:  
  bain.wang@outlook.com         1.0               2016-2-10
  Description:  platform monitor  cli interface 
  Others:                     
  History:        
*************************************************/
#include <stdlib.h>
#include "bc_modules.h"
#include "bc_cli_type.h"
#include "bc_cli_paratype.h"
#include "bc_cli.h"
#include "bc_common_defs.h"
#include "bc_platform_procps.h"
#include "bc_err.h"

static  bc_uint32 l_mdl_id = BC_MODULE_PLATFORM_MONITOR_CLI;

static I32_T __bc_show_memory_statistics(
	bc_uint32 session_id,
	cli_value_t *p_cli2_value, 
	void *p_user_data
)
{
	bc_ulong memtotal;
	bc_ulong memfree;
	cli_cmd_ret_e ret = CLI_CMD_SUCCESS_PRT_NEWLINE;

	CLI_DBG_ENTER(l_mdl_id);

	if (bc_platform_mem_info(&memtotal, &memfree) != BC_ERR_OK)
	{
		ret = CLI_CMD_FAIL_PRT_NEWLINE;
	}
	else
	{
		BC_PT_COMMAND(BC_MODULE_PLATFORM_MONITOR_CLI,"\rStorage Type       Storage Size       Storage Used \n");
		BC_PT_COMMAND(BC_MODULE_PLATFORM_MONITOR_CLI,"\r------------------ ------------------ ---------------\n");
		BC_PT_COMMAND(BC_MODULE_PLATFORM_MONITOR_CLI,"\rDDR2          %10luKbytes      %10luKbytes\n",memtotal,memtotal-memfree);
	}
	
	CLI_DBG_LEAVE(l_mdl_id);
	
	return ret;
}

static I32_T __bc_show_cpu_statistics(
	bc_uint32 session_id,
	cli_value_t *p_cli2_value, 
	void *p_user_data
)
{
	bc_ulong usage;
	cli_cmd_ret_e ret = CLI_CMD_SUCCESS_PRT_NEWLINE;

	CLI_DBG_ENTER(l_mdl_id);

	if (bc_platform_cpu_info(&usage) != BC_ERR_OK)
	{
		ret = CLI_CMD_FAIL_PRT_NEWLINE;
	}
	else
	{
		BC_PT_COMMAND(BC_MODULE_PLATFORM_MONITOR_CLI,"\r  Cpu       Usage:%lu%% \n",usage);
	}
	
	CLI_DBG_LEAVE(l_mdl_id);
	
	return ret;
}

static I32_T  __bc_ps(
	bc_uint32 session_id,
	cli_value_t *p_cli2_value, 
	void *p_user_data
)
{

	bc_char cmd[60]; 
	cli_cmd_ret_e ret = CLI_CMD_SUCCESS_PRT_NEWLINE;

	CLI_DBG_ENTER(l_mdl_id);
	
	sprintf(cmd,"ps %s",(bc_char *)p_cli2_value->value);
	if (system(cmd) != 0)
	{
		ret = CLI_CMD_FAIL_PRT_NEWLINE;
	}

	CLI_DBG_LEAVE(l_mdl_id);
	
	return ret;
}


static I32_T  __bc_top(
	bc_uint32 session_id,
	cli_value_t *p_cli2_value, 
	void *p_user_data
)
{
	cli_cmd_ret_e ret = CLI_CMD_SUCCESS_PRT_NEWLINE;

	CLI_DBG_ENTER(l_mdl_id);
	
	if (system("top") != 0)
	{
		ret = CLI_CMD_FAIL_PRT_NEWLINE;
	}

	CLI_DBG_LEAVE(l_mdl_id);
	
	return ret;
}

/*************************************************
  Function: bc_cli_cmd_monitor_reg
  Description:platform debug reg
  Input: 

  Output:
  Return:
		void
  Notes:
  History: 
*************************************************/
void bc_cli_cmd_monitor_reg(void)
{
	CLI_DBG_ENTER(l_mdl_id);

	BOOL_T __attribute__ ((unused))  ret_reg;

	ret_reg = bc_cli_reg_cmd(
		CLI_MOD_GLOBAL_PATH
		"/show "	
		"monitor "               "#Show system monitor info.#""#显示系统监控信息#"
		"memory-statistics"      "#Show memory statistics.#""#显示内存利用率。#"
		,
		__bc_show_memory_statistics,
		CLI_ACC_LVL_USER,
		"Show memory statistics.",
		"显示内存利用率。",
		NULL);
	
	ret_reg = bc_cli_reg_cmd(
		CLI_MOD_GLOBAL_PATH
		"/show "
		"monitor"               "#Show system monitor info.#""#显示系统监控信息#"
		"cpu-statistics"        "#Show cpu statistics.#""#显示cpu利用率。#"
		,
		__bc_show_cpu_statistics,
		CLI_ACC_LVL_USER,
		"Show cpu statistics.",
		"显示cpu利用率。",
		NULL);	

	ret_reg = bc_cli_reg_cmd(
		CLI_MOD_DEBUG_PATH
		"/platform"		 "#Platform debug info#""#Platform debug信息#"
		"ktps"           "#ktps#""#ktps#"
		"<string>"       "#ktps parameter,ex:-elf -aux -auH#""#ktps参数,例如:-elf -aux -auH#"
		,
		__bc_ps,
		CLI_ACC_LVL_DEBUG,
		"ktps",
		"ktps",
		NULL);	

	ret_reg = bc_cli_reg_cmd(
		CLI_MOD_DEBUG_PATH
		"/platform"		  "#Platform debug info#""#Platform debug信息#"
		"kttop"           "#kttop#""#kttop#"
		,
		__bc_top,
		CLI_ACC_LVL_DEBUG,
		"kttop",
		"kttop",
		NULL);
	
	CLI_DBG_LEAVE(l_mdl_id);
	return;
}



