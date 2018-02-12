/*************************************************
  -------------------------------------------------------------------------
  File name: bc_cli_cmd_clock.c
  Author:       Version:        Date:  
  huwp         1.0               2016-2-10
  Description:  System clock command register 
  Others:                     
  History:        
*************************************************/
#include "bc_modules.h"
#include "bc_cli_type.h"
#include "bc_cli_paratype.h"
#include "bc_cli.h"
#include "bc_common_defs.h"
#include "bc_system_clock.h"
#include "bc_err.h"

static  bc_uint32 l_mdl_id = BC_MODULE_PLATFORM_CLOCK_CLI;


static I32_T __bc_clock_date_set(
	bc_uint32 session_id,
	cli_value_t *p_cli2_value, 
	void *p_user_data
)
{
	struct tm sys_date;
	cli_cmd_ret_e ret = CLI_CMD_SUCCESS_PRT_NEWLINE;
	cli_value_t *p = p_cli2_value;

	CLI_DBG_ENTER(l_mdl_id);
	
	memset(&sys_date, 0,sizeof(struct tm));

	sys_date.tm_year = ((CLI_TYPE_DATE_T *)p->value)->year -1900;
	sys_date.tm_mon  = ((CLI_TYPE_DATE_T *)p->value)->month - 1;
	sys_date.tm_mday = ((CLI_TYPE_DATE_T *)p->value)->day;
	p = p->next;
	sys_date.tm_hour = ((CLI_TYPE_TIME_T *)p->value)->hour;
	sys_date.tm_min  = ((CLI_TYPE_TIME_T *)p->value)->minute;
	sys_date.tm_sec  = ((CLI_TYPE_TIME_T *)p->value)->second;	

	if (bc_clock_date_set(&sys_date) == BC_ERR_OK)
	{
		BC_PT_COMMAND(BC_MODULE_PLATFORM_CLOCK_CLI, "System date: %d-%02d-%02d %02d:%02d:%02d  System date change\n",
		                      sys_date.tm_year + 1900, sys_date.tm_mon + 1, sys_date.tm_mday,
		                      sys_date.tm_hour, sys_date.tm_min, sys_date.tm_sec);
		ret = CLI_CMD_SUCCESS_PRT_NEWLINE;
	}
	else
	{
		BC_PT_COMMAND(BC_MODULE_PLATFORM_CLOCK_CLI, "System date change fail\n");
		ret = CLI_CMD_FAIL_PRT_NEWLINE;
	}

	CLI_DBG_LEAVE(l_mdl_id);
	
	return ret;
}


static I32_T __bc_clock_tz_set(
	bc_uint32 session_id,
	cli_value_t *p_cli2_value, 
	void *p_user_data
)
{
	bc_int8 timezone;
	cli_cmd_ret_e ret = CLI_CMD_SUCCESS_PRT_NEWLINE;
	cli_value_t *p = p_cli2_value;

	CLI_DBG_ENTER(l_mdl_id);
	
	timezone = *((bc_int32 *)p->value);

	if ((timezone < -12)||(timezone > 12))
	{
		BC_PT_COMMAND(BC_MODULE_PLATFORM_CLOCK_CLI,"Timezone is invalid, the range is from -12 to 12!\n");
		ret = CLI_CMD_FAIL_PRT_NEWLINE;
		CLI_DBG_ENTER(l_mdl_id);
		return ret;
	}

	if (bc_clock_tz_set(timezone) == BC_ERR_OK)
	{
		//BC_PT_COMMAND(BC_MODULE_PLATFORM_CLOCK_CLI,"timezone: %d  System date change\n",timezone);
		ret = CLI_CMD_SUCCESS_PRT_NEWLINE;
	}
	else
	{
		BC_PT_COMMAND(BC_MODULE_PLATFORM_CLOCK_CLI,"System date change fail\n");
		ret = CLI_CMD_FAIL_PRT_NEWLINE;
	}

	CLI_DBG_LEAVE(l_mdl_id);
	
	return ret;
}


static I32_T __bc_clock_tz_def(
	bc_uint32 session_id,
	cli_value_t *p_cli2_value, 
	void *p_user_data
)
{
	bc_int8 timezone = 8;
	cli_cmd_ret_e ret = CLI_CMD_SUCCESS_PRT_NEWLINE;

	CLI_DBG_ENTER(l_mdl_id);

	if (bc_clock_tz_set(timezone) == BC_ERR_OK)
	{
		BC_PT_COMMAND(BC_MODULE_PLATFORM_CLOCK_CLI,"Set this timezone for the default value.\n");
		ret = CLI_CMD_SUCCESS_PRT_NEWLINE;
	}
	else
	{
		BC_PT_COMMAND(BC_MODULE_PLATFORM_CLOCK_CLI,"Can't Set this timezone for the default value.\n");
		ret = CLI_CMD_FAIL_PRT_NEWLINE;
	}

	CLI_DBG_LEAVE(l_mdl_id);
	
	return ret;
}


static I32_T __bc_clock_date_show(
	bc_uint32 session_id,
	cli_value_t *p_cli2_value, 
	void *p_user_data
)
{
	struct tm tmtime;
	bc_int8 timezone;
	cli_cmd_ret_e ret = CLI_CMD_SUCCESS_PRT_NEWLINE;

	CLI_DBG_ENTER(l_mdl_id);

	if (bc_clock_date_get(&tmtime)!= BC_ERR_OK)
	{
		ret = CLI_CMD_FAIL_PRT_NEWLINE;
	}

	if (bc_clock_tz_get(&timezone)!= BC_ERR_OK)
	{
		ret = CLI_CMD_FAIL_PRT_NEWLINE;
	}

	BC_PT_COMMAND(BC_MODULE_PLATFORM_CLOCK_CLI,"System date: %d-%02d-%02d %02d:%02d:%02d  timezone %d\n",
                     tmtime.tm_year + 1900, tmtime.tm_mon + 1, tmtime.tm_mday,
                     tmtime.tm_hour, tmtime.tm_min, tmtime.tm_sec, timezone);
	
	CLI_DBG_LEAVE(l_mdl_id);
	
	return ret;
}


/*************************************************
  Function: bc_cli_cmd_clock_reg
  Description:System clock command register
  Input: 

  Output:
  Return:
		void
  Notes:
  History: 
*************************************************/
void bc_cli_cmd_clock_reg(void)
{
	CLI_DBG_ENTER(l_mdl_id);

	BOOL_T ret_reg;

	ret_reg = bc_cli_reg_cmd(
		CLI_MOD_GLBCFG_PATH
		"/date "	        "#Set the system date#""#设置系统时间日期#"
		"<yyyy-mm-dd>"      "#Set the system date.#""#设置系统日期。#"
		"<HH:MM:SS>"        "#Set the system time.#""#设置系统时间。#"
		,
		__bc_clock_date_set,
		CLI_ACC_LVL_USER,
		"Set the system date.",
		"设置系统时钟。",
		NULL);
	
	ret_reg = bc_cli_reg_cmd(
		CLI_MOD_GLBCFG_PATH
		"/timezone"     "#Set the system timezone#""#设置系统时区。#"
		"<time-zone>"   "#Set the system timezone(-12~12).#""#设置系统时区(-12~12)。#"
		,
		__bc_clock_tz_set,
		CLI_ACC_LVL_USER,
		"Set the system timezone.",
		"设置系统时区。",
		NULL);

	ret_reg = bc_cli_reg_cmd(
		CLI_MOD_GLBCFG_PATH
		"/no "
		"timezone"     "#Set this timezone for the default value.#""#恢复默认时区。#"
		,
		__bc_clock_tz_def,
		CLI_ACC_LVL_USER,
		"Set this timezone for the default value.",
		"恢复默认时区。",
		NULL);

	ret_reg = bc_cli_reg_cmd(
		CLI_MOD_GLOBAL_PATH
		"/show "
		"date"     "#Show the system date#""#显示系统时钟#"
		,
		__bc_clock_date_show,
		CLI_ACC_LVL_USER,
		"Show the system date.",
		"显示系统时钟。",
		NULL);

	CLI_DBG_CPL(l_mdl_id, "ret=%d\r\n", ret_reg);
	
	CLI_DBG_LEAVE(l_mdl_id);
	return;
}



