/*******************************************************************************
  [Author]	   : bain.wang@outlook.com.uestc@gmail.com
  [Version]    : 1.0
  [Date]       : 2017-03-14
  [Description]:

  [Others]     :

  [History]:
	 Date          Modification 							    Initials
	----------     ----------                                   -------
	2017-03-14      Created								   		bain.wang@outlook.com
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

#include "bc_print.h"
#include "snmp_trap_fhIntfTraps.h"
#include "snmp_global.h"
#include "snmp_core_ex.h"

#include "snmp_trap_fhHardwareTraps.h"
#include "snmp_trap_fhIntfTraps.h"
#include "snmp_trap_fhVCTraps.h"
#include "snmp_trap_x86.h"
#include "snmp_trap_comm.h"
#include <pthread.h>
#include <semaphore.h>



static time_t update_time;

void __snmp_trap_cb(unsigned int alarm_clientreg, void *alarm_clientarg);

snmp_alarm_info_t g_alarm_info;


#define SNMP_TRAP_COUNTER_MAX	65535


snmp_alarm_info_t* snmp_get_trap_info()
{
	return (snmp_alarm_info_t*)&g_alarm_info;
}

#if 1
int snmp_trap_cfg_get(snmp_alarm_cfg_t *alarm_cfg)
{
	if(!alarm_cfg)
	{
		BC_PT_ERROR(BC_MODULE_SNMP, "alarm cfg is NULL!\n");
		return FALSE;
	}
	memcpy(alarm_cfg, &g_alarm_info.cfg_info, sizeof(snmp_alarm_cfg_t));
	return TRUE;
}

int snmp_trap_cfg_set(snmp_alarm_cfg_t alarm_cfg)
{
	memcpy(&g_alarm_info.cfg_info, &alarm_cfg, sizeof(snmp_alarm_cfg_t));
	return TRUE;
}

static int snmp_trap_cfg_get_counter(int *cnt)
{
	*cnt = g_alarm_info.cfg_info.counter;
	return g_alarm_info.cfg_info.counter;
}

static void snmp_trap_cfg_set_counter(int cnt)
{
	g_alarm_info.cfg_info.counter = cnt;
}

static void snmp_trap_cfg_counter_add()
{
	g_alarm_info.cfg_info.counter++;
	
	if(g_alarm_info.cfg_info.counter >= SNMP_TRAP_COUNTER_MAX)
		g_alarm_info.cfg_info.counter = 0;
}

int snmp_trap_cfg_set_regid(unsigned int id)
{
	g_alarm_info.cfg_info.regid = id;
	return TRUE;
}

#endif

int __snmp_trap_init()
{
	struct sockaddr_in sockaddr;
	
	memset(&g_alarm_info, 0, sizeof(g_alarm_info));
	
	//fhHardwareTraps
	g_alarm_info.board_info.board_base_info.slot_id = 1;
	g_alarm_info.board_info.board_base_info.s_slot_id = 2;
	g_alarm_info.board_info.board_base_info.board_type = BOARD_TYPE_1;
	g_alarm_info.board_info.board_base_info.board_status = BOARD_STATUS_UP;
	strcpy(g_alarm_info.board_info.board_base_info.name, "board_base_info_name");
	strcpy(g_alarm_info.board_info.ifname, "board_base_info_ifname");
	g_alarm_info.board_info.port_id = 3;
	//fhIntfTraps
	strcpy(g_alarm_info.if_info.ifname, "if_info_ifname");
	g_alarm_info.if_info.if_err.if_in_err = 11;
	g_alarm_info.if_info.if_err.if_out_err = 22;
	strcpy(g_alarm_info.if_info.if_rate.if_in_rate, "if_in_rate");
	strcpy(g_alarm_info.if_info.if_rate.if_out_rate, "if_out_rate");
	g_alarm_info.if_info.if_index = 7;
	//fhVCTraps
	g_alarm_info.vc_info.ctrl_word = 8;
	strcpy(g_alarm_info.vc_info.ifname, "vc_info_ifname");
	sockaddr.sin_addr.s_addr = inet_addr("192.168.5.5");
	g_alarm_info.vc_info.peer_addr = sockaddr.sin_addr.s_addr;
	g_alarm_info.vc_info.primary_pw_id = 33;
	g_alarm_info.vc_info.second_pw_id = 44;
	g_alarm_info.vc_info.vc_type = VC_TYPE_1;
	g_alarm_info.vc_info.vd_id = 1;

	//config information
	g_alarm_info.cfg_info.interval = 2;
	g_alarm_info.cfg_info.enable = SNMP_TRAP_DISABLE;
	g_alarm_info.cfg_info.counter = 0;
	g_alarm_info.cfg_info.regid = 1;
	strcpy(g_alarm_info.cfg_info.name, "ptn-snmp-trap-1");
	g_alarm_info.cfg_info.code = SNMP_ALARM_CODE_LINK_DOWN;
	g_alarm_info.cfg_info.cb = __snmp_trap_cb;
	
	return TRUE;
}

int snmp_trap_process(snmp_alarm_info_t alarm_info)
{
	int cnt;
	bc_boolean is_trap = FALSE;
	
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	
	switch(alarm_info.cfg_info.code)
	{
		case SNMP_ALARM_CODE_LINK_DOWN:
			BC_PT_FUN_NOTSUPPORTED(BC_MODULE_SNMP);
			break;
		case SNMP_ALARM_CODE_BOARD_NO_EXIST:
			send_fhBoardNotExist_trap(alarm_info);
			is_trap = TRUE;
			break;
		case SNMP_ALARM_CODE_BOARD_FAULT:
			send_fhBoardFault_trap(alarm_info);
			is_trap = TRUE;
			break;
		case SNMP_ALARM_CODE_INTF_TRAFFIC_EXCEED:
			send_fhIntfTrafficExceed_trap(alarm_info);
			is_trap = TRUE;
			break;
		case SNMP_ALARM_CODE_INTF_RX_BAD_PKT_EXCEED:
			send_fhIntfRxBadPktExceed_trap(alarm_info);
			is_trap = TRUE;
			break;
		case SNMP_ALARM_CODE_PHYSICAL_INTERFACE_DOWN:
			send_fhPhysicalInterfaceDown_trap(alarm_info);
			is_trap = TRUE;
			break;
		case SNMP_ALARM_CODE_INTF_PKT_LOSS_EXCEED:
			send_fhIntfPktLossExceed_trap(alarm_info);
			is_trap = TRUE;
			break;
		case SNMP_ALARM_CODE_BOARD_TEMP_EXCEED:
			send_fhBoardTempExceed_trap(alarm_info);
			is_trap = TRUE;
			break;
		case SNMP_ALARM_CODE_MEMORY_USAGE_EXCEED:
			send_fhMemoryUsageExceed_trap(alarm_info);
			is_trap = TRUE;
			break;
		case SNMP_ALARM_CODE_CPU_USAGE_EXCEED:
			send_fhCPUUsageExceed_trap(alarm_info);
			is_trap = TRUE;
			break;
		case SNMP_ALARM_CODE_POWER_SUPPLY_SHORTAGE:
			send_fhPowerSupplyShortage_trap(alarm_info);
			is_trap = TRUE;
			break;
		case SNMP_ALARM_CODE_LASER_SEND_FAULT:
			send_fhLaserSendFault_trap(alarm_info);
			is_trap = TRUE;
			break;
		case SNMP_ALARM_CODE_LASER_TEMP_EXCEED:
			send_fhLaserTempExceed_trap(alarm_info);
			is_trap = TRUE;
			break;
		case SNMP_ALARM_CODE_POWER_OUT_SHORTAGE:
			send_fhPowerOutShortage_trap(alarm_info);
			is_trap = TRUE;
			break;
		case SNMP_ALARM_CODE_POWER_OUT_EXCEED:
			send_fhPowerOutExceed_trap(alarm_info);
			is_trap = TRUE;
			break;
		case SNMP_ALARM_CODE_POWER_IN_SHORTAGE:
			send_fhPowerInShortage_trap(alarm_info);
			is_trap = TRUE;
			break;
		case SNMP_ALARM_CODE_POWER_IN_EXCEED:
			send_fhPowerInExceed_trap(alarm_info);
			is_trap = TRUE;
			break;
		case SNMP_ALARM_CODE_VC_DOWN:
			send_fhVCDown_trap(alarm_info);
			is_trap = TRUE;
			break;
		case SNMP_ALARM_CODE_VC_UP:
			send_fhVCUp_trap(alarm_info);
			is_trap = TRUE;
			break;
		case SNMP_ALARM_CODE_PWE3_VC_W2P:
		//	send_fhPwe3VCW2P_trap();
			BC_PT_FUN_NOTSUPPORTED(BC_MODULE_SNMP);
			break;
		case SNMP_ALARM_CODE_PWE3_VC_P2W:
		//	send_fhPwe3VCP2W_trap();
			BC_PT_FUN_NOTSUPPORTED(BC_MODULE_SNMP);
			break;
		default:
			
			return FALSE;
	}
	if(is_trap == TRUE)
	{
		snmp_trap_cfg_counter_add();	// +1
		BC_PT_EVENT(BC_MODULE_SNMP,"snmp alarm trap sucessed, code:%d conter:%d\n", alarm_info.cfg_info.code, snmp_trap_cfg_get_counter(&cnt));
	}
	else
	{
		BC_PT_WARNING(BC_MODULE_SNMP, "snmp alarm code invalid, code:%d\n", alarm_info.cfg_info.code);
	}
	
	BC_PT_FUN_LEAVE(BC_MODULE_SNMP);

	return TRUE;
}

void __snmp_trap_cb(unsigned int alarm_clientreg, void *alarm_clientarg)
{
	BC_PT_DBG_PRINT(BC_MODULE_SNMP, "\n");
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	if(g_alarm_info.cfg_info.enable == SNMP_TRAP_ENABLE)
	{
		/*这里仅测试，最低2S，否则无意义，缓冲区易被冲满*/
		if(g_alarm_info.cfg_info.interval < 2)
		{
			g_alarm_info.cfg_info.interval = 2;
		}
	//	sleep(g_alarm_info.interval);		/* do not enable this line, why ??????? */
		
		if(g_alarm_info.cfg_info.counter >= 65534)
			g_alarm_info.cfg_info.counter = 0;
		
		snmp_trap_process(g_alarm_info);
	}
	BC_PT_FUN_LEAVE(BC_MODULE_SNMP);
}

int snmp_trap_alarm_start(snmp_alarm_cfg_t alarm_cfg)
{
	int id = SNMP_TRAP_REGID_INVALID;

	SNMP_TRAP_REGISTER(alarm_cfg.interval, alarm_cfg.cb, NULL, id);
	if(SNMP_TRAP_REGID_INVALID == id)
	{
		BC_PT_ERROR(BC_MODULE_SNMP, "snmp alarm register failure!\n ");
		return FALSE;
	}
	snmp_trap_cfg_set_regid(id);
	BC_PT_EVENT(BC_MODULE_SNMP,"snmp alarm register successed, regid:%d\n ", id);
	
	return TRUE;
}

int snmp_trap_alarm_stop(snmp_alarm_cfg_t alarm_cfg)
{
	SNMP_TRAP_UNREGISTER(alarm_cfg.regid);
	snmp_trap_cfg_set_regid(SNMP_TRAP_REGID_INVALID);

	return TRUE;
}

int snmp_trap_alarm_reset(snmp_alarm_cfg_t alarm_cfg)
{
	if((snmp_trap_alarm_stop(alarm_cfg)) == FALSE)
		return FALSE;
	
	if((snmp_trap_alarm_start(alarm_cfg)) == FALSE)
		return FALSE;

	BC_PT_EVENT(BC_MODULE_SNMP,"snmp alarm reset successed!\n ");
	return TRUE;
}

int snmp_trap_init_x86()
{
	BC_PT_FUN_ENTER(BC_MODULE_SNMP);
	__snmp_trap_init();

	if(g_alarm_info.cfg_info.enable == TRUE)
	{
		if(g_alarm_info.cfg_info.interval != 0)
		{
			snmp_trap_alarm_start(g_alarm_info.cfg_info);
			BC_PT_EVENT(BC_MODULE_SNMP,"snmp trap start successed!\n");
		}
		else
		{
			BC_PT_ERROR(BC_MODULE_SNMP, "trap interval must be (> 0)!\n");
		}
	}
	else
	{
		BC_PT_WARNING(BC_MODULE_SNMP, ".........................snmp trap no startup!\n");
	}

	BC_PT_FUN_LEAVE(BC_MODULE_SNMP);
	
	return TRUE;
}

