
#ifndef __SNMP_TRAP_COMMON_H__
#define __SNMP_TRAP_COMMON_H__

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include <net-snmp/agent/snmp_vars.h>

#include "bc_common_defs.h"
#include "snmp_global.h"
#include "snmp_core_ex.h"
//#include "snmp_trap.h"

/* fhHardwareTraps */
typedef enum
{
	SNMP_ALARM_CODE_MIN=0X100,	
		
	SNMP_ALARM_CODE_LINK_DOWN,				/*设备故障*/
	SNMP_ALARM_CODE_BOARD_NO_EXIST,
	SNMP_ALARM_CODE_BOARD_FAULT,

	
	SNMP_ALARM_CODE_INTF_TRAFFIC_EXCEED=0X200,		/*interface*/
	SNMP_ALARM_CODE_INTF_RX_BAD_PKT_EXCEED,
	SNMP_ALARM_CODE_PHYSICAL_INTERFACE_DOWN,
	SNMP_ALARM_CODE_INTF_PKT_LOSS_EXCEED,

	
	SNMP_ALARM_CODE_BOARD_TEMP_EXCEED=0X300,		/*温度电源类*/
	SNMP_ALARM_CODE_MEMORY_USAGE_EXCEED,
	SNMP_ALARM_CODE_CPU_USAGE_EXCEED,
	SNMP_ALARM_CODE_POWER_SUPPLY_SHORTAGE,
	
	
	SNMP_ALARM_CODE_LASER_SEND_FAULT=0X400,		/*激光器*/
	SNMP_ALARM_CODE_LASER_TEMP_EXCEED,
	
	
	SNMP_ALARM_CODE_POWER_OUT_SHORTAGE=0X500,	/*光功率*/
	SNMP_ALARM_CODE_POWER_OUT_EXCEED,
	SNMP_ALARM_CODE_POWER_IN_SHORTAGE,
	SNMP_ALARM_CODE_POWER_IN_EXCEED,
	
	
	SNMP_ALARM_CODE_VC_DOWN=0X600,					/*VC*/
	SNMP_ALARM_CODE_VC_UP,
	SNMP_ALARM_CODE_PWE3_VC_W2P,
	SNMP_ALARM_CODE_PWE3_VC_P2W,
	
	SNMP_ALARM_CODE_CODE_MAX
}snmp_alarm_code_e;


#if 1	
typedef enum
{
	BOARD_STATUS_UP=1,
	BOARD_STATUS_DOWN=2
}snmp_alarm_board_status_e;

typedef enum
{
	BOARD_TYPE_1=1,
	BOARD_TYPE_2=2,
	BOARD_TYPE_3=3,
	BOARD_TYPE_4=4
}snmp_alarm_board_type_e;

typedef struct 
{
	int slot_id;
	int s_slot_id;
	snmp_alarm_board_type_e board_type;
	snmp_alarm_board_status_e board_status;
	char name[SNMP_DEV_NAME_LEN];
}snmp_alarm_board_base_info_t;


typedef struct 
{
	snmp_alarm_board_base_info_t board_base_info;
	char ifname[SNMP_DEV_NAME_LEN];
	int port_id;
}snmp_alarm_board_info_t;

/* fhIntfTraps */
typedef struct
{
	char if_in_rate[SNMP_DEV_NAME_LEN];
	char if_out_rate[SNMP_DEV_NAME_LEN];
}snmp_alarm_if_rate_info_t;

typedef struct
{
	int if_in_err;
	int if_out_err;
}snmp_alarm_if_err_info_t;

typedef struct
{
	char ifname[SNMP_DEV_NAME_LEN];
	int if_index;
	snmp_alarm_if_rate_info_t if_rate;
	snmp_alarm_if_err_info_t if_err;
}snmp_alarm_if_info_t;

/*fhVCTraps*/
typedef enum
{
	VC_TYPE_1=1,
	VC_TYPE_2=2,
	VC_TYPE_3=3
}snmp_alarm_vc_type_e;

typedef enum
{
	SNMP_TRAP_DISABLE=0,
	SNMP_TRAP_ENABLE = 1,
	SNMP_TRAP_MAX
}snmp_trap_enable_e;

typedef struct
{
	int vd_id;
	snmp_alarm_vc_type_e vc_type;
	bc_ipv4 peer_addr;
	int ctrl_word;
	int primary_pw_id;
	int second_pw_id;
	char ifname[SNMP_DEV_NAME_LEN];
}snmp_alarm_vc_info_t;


#if SNMP_PRJ_NAME_X86
	typedef void    (SNMPTrapCallback) (unsigned int, void *);
#elif SNMP_PRJ_NAME_610A
	typedef int (SnmpTrapEventParse) (void *);	
#else
#endif

typedef struct 
{
	int interval;
	int counter;
	snmp_trap_enable_e enable;
	unsigned int regid;
	char name[32];
	snmp_alarm_code_e code;
#if SNMP_PRJ_NAME_X86
	SNMPTrapCallback *cb; 
#elif SNMP_PRJ_NAME_610A
	SnmpTrapEventParse *parse;
#else
#endif
	
}snmp_alarm_cfg_t;

typedef struct
{
	snmp_alarm_board_info_t board_info;
	snmp_alarm_if_info_t if_info;
	snmp_alarm_vc_info_t vc_info;
	snmp_alarm_cfg_t cfg_info;
}snmp_alarm_info_t;
#endif


#define SNMP_TRAP_REGID_INVALID	(0)

/*register alarm to net-snmp core*/	
#define SNMP_TRAP_REGISTER(sec, func, arg, id)	\
	do{	\
		struct timeval  _t_;	\
		if (0 == sec) {	\
			_t_.tv_sec = 0;	\
			_t_.tv_usec = 1;	\
		} else {	\
			_t_.tv_sec = sec;	\
			_t_.tv_usec = 0;	\
		}	\
		id = snmp_alarm_register_hr(_t_, SA_REPEAT, func, arg);	\
	}while(0)	

#define SNMP_TRAP_UNREGISTER(id)	\
	do{	\
		if(sa_find_specific(id))	\
		{	\
			snmp_alarm_unregister(id);	\
			BC_PT_EVENT(BC_MODULE_SNMP,"snmp alarm unregister successed, regid:%d\n ", id);	\
		}	\
		else	\
		{	\
			BC_PT_ERROR(BC_MODULE_SNMP,"snmp alarm unregister failure\n");	\
			return FALSE;	\
		}	\
	}while(0)	

#define SNMP_TRAP_START(info)	\
	snmp_trap_alarm_start(info);	

#define SNMP_TRAP_STOP(info)	\
	snmp_trap_alarm_stop(info)

#define SNMP_TRAP_RESET(info)	\
	snmp_trap_alarm_reset(info)


#if 0

#include "mBase.h"
#include "event/event_eth_port.h"
#include "mpapi.h"
#include "comm/lr_errors.h"

#define API_ALARM_TYPE_DEF_MAX	__MAX_EVENT_TYPE
#define SNMP_ALARM_LEVEL_DEF		0xFFFF

#define SNMP_TRAP_ALARM_NAME "snmp_trap"

#define SNMP_ALARM_EVENT_SET(collect, i, m, p, type, events)	\
	do{	\
		CARE_EVENT(	collect, type, i,  m,  p, events);	\
	}while(0)

#define SNMP_ALARM_EVENT_REG(client, collect)	\
	do{	\
		if(mBase_care_signal(client, collect) != LR_OK){	\
			BC_PT_DBG_CPL(BC_MODULE_SNMP, "mBase_care_signal() failure\n");	\
			goto API_ERR;	\
		}	\
	}while(0)


typedef bc_boolean (* AlarmEachEventTypeProc) (
											eventNotifyRes *, 
											struct event_bitmap,
											struct mBase_client *, 
											snmp_alarm_info_t);
		
typedef struct
{
	struct event_collect collect;
	event_type_t type;
	AlarmEachEventTypeProc hr;
	int important_flag;
	int minor_flag;
	int prompt_flag;
	int events;
}snmp_alarm_event_info_t;


#define ALARM_EVENTS_INFO_TABLE	__alarm_events_info

#define SNMP_ALARM_TYPE_REG_NUM	\
				(sizeof(ALARM_EVENTS_INFO_TABLE)/sizeof(snmp_alarm_event_info_t))


typedef bc_boolean (*alarm_signal_process)(struct mBase_signal_data *d);

#endif



#endif	/*__SNMP_TRAP_COMMON_H__*/
