/************************************************************
  -------------------------------------------------------------------------
  FileName: bc_cli_cmd_baseinfo.c
  Author:  bain.wang@outlook.com      Version :  1.0        Date:2016-10-10
  Description: proj depend parameter define       
  Version:                        
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "bc_cli.h"
#include "bc_cli_type.h"
#include "bc_cli_vkey.h"
#include "bc_cli_paratype.h"
#include "bc_sys_defs.h"
#include "bc_sys_ipc_client.h"
#include "bc_cli_base.h"
#include "bc_cli_text.h"
//#include "bc_intf.h"
#include "bc_msg.h"
//#include "bc_cli_cmd_intf.h"


static unsigned int 	l_mdl_id = BC_MODULE_SYSTEM;
extern void bc_cli_cmd_baseinfo_dbg_reg(void);
extern bc_err_e bc_sys_reboot_client(void);
static I32_T __sys_reboot
	(
	IN const UI32_T 	sid,
	IN cli_value_t 		*ptrCliValue,
	IN void 			*ptrUserData
    )
{
	bc_err_e   ret  = BC_ERR_OK;
	bc_char in_buf[1024] = {0};
	I32_T trigger[] =
    {
        CLI_VKEY_CTRL_ENTER, CLI_VKEY_CR, 0
    };
	
//	CLI_DBG_ENTER(l_mdl_id);

	BC_PT_COMMAND((l_mdl_id), "This will reboot the device! If you do not save the settings, all changes made will be lost!\r\n");
	BC_PT_COMMAND((l_mdl_id), "Are you sure you want to reboot the device?(y/n)\r\n");

	bc_cli_get_line(sid, 0, CLI_OUTPUT_NORMAL, in_buf, sizeof(in_buf), 60, trigger);
	if (!((1 == strlen(in_buf)) && (in_buf[0] == 'y')))
	{
		BC_PT_COMMAND(l_mdl_id, "\r\n");
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}

#if 1
	CLI_API_Printf(sid, "\r\n*** not supported warning ***\r\n");
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
#endif
	ret = bc_sys_reboot_client();
	if (ret != BC_ERR_OK)
	{
		CLI_API_Printf(sid, "\r\n Failed to olt reboot ret = %d!\r\n", ret);
	}
//	CLI_DBG_LEAVE(l_mdl_id);
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

static I32_T __sys_reset
	(
	IN const UI32_T 	sid,
	IN cli_value_t 		*ptrCliValue,
	IN void 			*ptrUserData
    )
{
	bc_err_e   ret  = BC_ERR_OK;
	
//	CLI_DBG_ENTER(l_mdl_id);
	
	ret = bc_sys_reset_client();
	if (ret != BC_ERR_OK)
	{
		CLI_API_Printf(sid, "\r\n Failed to olt reset ret = %d!\r\n", ret);
	}
//	CLI_DBG_LEAVE(l_mdl_id);
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

static I32_T __sys_info
	(
	IN const UI32_T 	sid,
	IN cli_value_t 		*ptrCliValue,
	IN void 			*ptrUserData
    )
{
	bc_err_e   ret  = BC_ERR_OK;
#if 0	/*bain.wang@outlook.com for cli*/
	bc_sys_baseinfo_t base_info;
    bc_intf_outband_t outbandpara ;
    struct in_addr    ip_value;
	cli_lan_t lan;
	
	CLI_DBG_ENTER(l_mdl_id);

	memset(&base_info, 0, sizeof(bc_sys_baseinfo_t));
	lan = bc_cli_get_lan();
	
	ret = bc_sys_ipc_baseinfo(&base_info);
	if (ret != BC_ERR_OK)
	{
		CLI_API_Printf(sid, "\r\n Failed to get baseinfo ret = %d!\r\n", ret);
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	
	CLI_API_Printf(sid, "\r\n");

	CLI_API_Printf(sid, "[%s]\r\n", bc_msg_get(BC_MSG_SYS_VERINFO, lan));

	CLI_API_Printf(sid, "%25s: %s\r\n", bc_msg_get(BC_MSG_SYS_SOFTVER, lan), base_info.sw);
	CLI_API_Printf(sid, "%25s: %s\r\n", bc_msg_get(BC_MSG_SYS_HARDVER, lan), base_info.hw);
	CLI_API_Printf(sid, "\r\n");

	ret = bc_intf_outband_get(&outbandpara);
	if(ret == BC_ERR_OK)
	{
        CLI_API_Printf(sid, "[%s]\r\n", bc_msg_get(BC_MSG_SYS_MGNTOUT, lan)); 
        ip_value.s_addr = outbandpara.outband_ipaddress;
        CLI_API_Printf(sid, "%25s: %s\r\n", bc_msg_get(BC_MSG_INTF_IP_ADDR, lan), inet_ntoa(ip_value));
        ip_value.s_addr = outbandpara.outband_subnetmask;
        CLI_API_Printf(sid, "%25s: %s\r\n", bc_msg_get(BC_MSG_INTF_NET_MASK, lan), inet_ntoa(ip_value));
        ip_value.s_addr = outbandpara.outband_gateway;
        CLI_API_Printf(sid, "%25s: %s\r\n", bc_msg_get(BC_MSG_INTF_GATEWAY, lan), inet_ntoa(ip_value));
		CLI_API_Printf(sid, "%25s: %02x:%02x:%02x:%02x:%02x:%02x\n\r", bc_msg_get(BC_MSG_INTF_HW_ADDR, lan), \
															outbandpara.outband_macaddress[0], \
															outbandpara.outband_macaddress[1], \
															outbandpara.outband_macaddress[2], \
															outbandpara.outband_macaddress[3], \
															outbandpara.outband_macaddress[4], \
															outbandpara.outband_macaddress[5]);
		CLI_API_Printf(sid, "\r\n");
	}
	else
	{
		CLI_API_Printf(sid, "send outband show resquest error\r\n");
	}   

	bc_intf_knet_info_show_all();
	CLI_API_Printf(sid, "\r\n");
#else
	CLI_API_Printf(sid, "\r\n*** not supported warning ***\r\n");
#endif
//	CLI_DBG_LEAVE(l_mdl_id);
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

static I32_T __sys_runtime
	(
	IN const UI32_T 	sid,
	IN cli_value_t 		*ptrCliValue,
	IN void 			*ptrUserData
    )
{
	bc_sys_baseinfo_t baseinfo;
	bc_err_e ret = BC_ERR_OK;
	cli_lan_t lan;
	bc_uint32 run_day = 0;
	bc_uint32 run_hour = 0;
	bc_uint32 run_min = 0;
	bc_uint32 run_sec = 0;

	lan = bc_cli_get_lan();
	memset(&baseinfo, 0x00, sizeof(bc_sys_baseinfo_t));
	ret = bc_sys_ipc_baseinfo(&baseinfo);
	if (ret != BC_ERR_OK)
	{
		CLI_API_Printf(sid, " %s\r\n", bc_msg_err_get(ret, lan));
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}

	BC_PT_DBG_CPL(BC_MODULE_SYSTEM, "run_time = %lu\r\n", baseinfo.run_time);
	run_day = baseinfo.run_time / (24*60*60);
	run_hour = (baseinfo.run_time % (24*60*60))/(60*60);
	run_min = ((baseinfo.run_time % (24*60*60))%(60*60))/60;
	run_sec = ((baseinfo.run_time % (24*60*60))%(60*60))%60;
	CLI_API_Printf(sid, "\r\n");
	CLI_API_Printf(sid, " %u day %u hour %u minute %u second\r\n", 
						run_day, run_hour, run_min, run_sec);

	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

static I32_T __sys_mac_set
	(
	IN const UI32_T 	sid,
	IN cli_value_t 		*ptrCliValue,
	IN void 			*ptrUserData
    )

{
	unsigned char 	mac[6] = {0};
	bc_mac sys_mac = {0};
	memcpy(mac, (char *)ptrCliValue->value, 6);
	memcpy(sys_mac, mac, sizeof(bc_mac));
	bc_sys_mac_set_client(mac);
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}
static I32_T __show_sys_mac
	(
	IN const UI32_T 	sid,
	IN cli_value_t 		*ptrCliValue,
	IN void 			*ptrUserData
    )
{
	bc_err_e   ret  = BC_ERR_OK;
#if 0
	cli_lan_t lan;
	bc_mac mac ={0};
	
	lan = bc_cli_get_lan();
	
	ret = bc_sys_mac_get_client(mac);
	if(ret == BC_ERR_OK)
	{
		CLI_API_Printf(sid, "%25s: %02x:%02x:%02x:%02x:%02x:%02x\n\r", bc_msg_get(BC_MSG_INTF_HW_ADDR, lan), \
															mac[0], \
															mac[1], \
															mac[2], \
															mac[3], \
															mac[4], \
															mac[5]);
		CLI_API_Printf(sid, "\r\n");
	}
#else
	CLI_API_Printf(sid, "*** not supported ***\r\n");
#endif
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

/*************************************************
  Function: bc_cli_cmd_cfg_reg
  Description: system basic info command
  Input:   
  		void
  Output:
  		NULL
  Return:
  		void
  Note: 
  History: 
*************************************************/
void bc_cli_cmd_baseinfo_reg(void)
{
	bc_cli_cmd_baseinfo_dbg_reg();
	bc_cli_reg_cmd(
		CLI_MOD_PRIVI_PATH
		"/reboot ",
		__sys_reboot,
		CLI_ACC_LVL_USER,
		"DEV reboot",
		"",
		NULL
		);

	bc_cli_reg_cmd(
		CLI_MOD_PRIVI_PATH
		"/reset ",
		__sys_reset,
		CLI_ACC_LVL_USER,
		"DEV reset",
		"",
		NULL
		);

	bc_cli_reg_cmd(
		CLI_MOD_GLOBAL_PATH
		"/show system ",
		__sys_info,
		CLI_ACC_LVL_USER,
		"DEV system info",
		"",
		NULL
		);

	bc_cli_reg_cmd(
		CLI_MOD_GLOBAL_PATH
		"/show device runtime ",
		__sys_runtime,
		CLI_ACC_LVL_USER,
		"DEV system run time",
		"查询设备运行时间",
		NULL
		);
	
	bc_cli_reg_cmd(
		CLI_MOD_DEBUG_PATH
		"/system "
		"sys_mac_set "	
		"<unitcast-mac-address> ",
		__sys_mac_set,
		CLI_ACC_LVL_USER,
		"DEV system info",
		"",
		NULL
		);

	bc_cli_reg_cmd(
		CLI_MOD_DEBUG_PATH
		"/show "
		"sys_mac ",
		__show_sys_mac,
		CLI_ACC_LVL_USER,
		"DEV system info",
		"",
		NULL
		);

}


