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
#ifndef __SNMP_TRAP_610A_H__
#define __SNMP_TRAP_610A_H__

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//																			  //
//								头   文   件								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include <net-snmp/agent/snmp_vars.h>

#include "bc_common_defs.h"
#include "snmp_global.h"
#include "snmp_core_ex.h"
#include "snmp_trap_comm.h"


#include "mBase.h"
#include "event/event_eth_port.h"
#include "mpapi.h"
#include "comm/lr_errors.h"


#define API_ALARM_TYPE_DEF_MAX	__MAX_EVENT_TYPE	/*系统最大事件数*/
#define SNMP_ALARM_LEVEL_DEF		0xFFFF				/*事件级别掩码*/

#define SNMP_TRAP_ALARM_NAME "snmp_trap"

#define SNMP_ALARM_EVENT_SET(collect, i, m, p, type, events)	\
	do{	\
		CARE_EVENT(collect, type, i,  m,  p, events);	\
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
	char name[32];
	struct event_collect collect;	/*collect of event type*/
	event_type_t type;			/*cur event*/
	AlarmEachEventTypeProc hr;	/*cur event proc func*/
	int important_flag;
	int minor_flag;
	int prompt_flag;
	int events;					/*events of event type*/
}snmp_alarm_event_info_t;


#define EVENT_TYPE_BASE EVENT_DEV_BOARD	// 1

#define ALARM_EVENTS_INFO_TABLE	__alarm_events_info					/*局部变量，不可全局使用*/

/*注册的事件数*/
#define SNMP_ALARM_TYPE_REG_NUM	\
				(sizeof(ALARM_EVENTS_INFO_TABLE)/sizeof(snmp_alarm_event_info_t))

#define SNMP_ALARM_TYPE_REG_SIZE	(sizeof(__alarm_events_info))							/*SNMP已注册的事件SIZE*/
#define API_ALARM_TYPE_REG_SIZE (sizeof(snmp_alarm_event_info_t)*API_ALARM_TYPE_DEF_MAX)	/*API已定义的事件SIZE*/


typedef bc_boolean (*alarm_signal_process)(struct mBase_signal_data *);	/*发生告警时的触发函数*/

int snmp_trap_cfg_get(snmp_alarm_cfg_t *alarm_info);
int snmp_trap_cfg_set(snmp_alarm_cfg_t alarm_info);
void snmp_alarm_event_item_pt(void);
int snmp_trap_init_610a();

#endif	/*__SNMP_TRAP_610A_H__*/
