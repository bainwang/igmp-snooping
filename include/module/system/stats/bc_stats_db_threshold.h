#ifndef __BC_STATS_DB_THRESHOLD_H__
#define __BC_STATS_DB_THRESHOLD_H__

#include "bc_stats_def.h"
#include "bc_stats_db_perf.h"


/*
	threshold info
*/


/*
	alarm info
*/
#if 1

typedef enum{
	STATS_ALARM_SEVERITY_CRITICAL = 0,
	STATS_ALARM_SEVERITY_IMPORTANT,
	STATS_ALARM_SEVERITY_MINOR,
	STATS_ALARM_SEVERITY_PROMPT,
	STATS_ALARM_SEVERITY_MAX
}stats_alarm_severity_e;

typedef struct{
	int index;	/*ex: port_num*/
	int val;
	stats_alarm_severity_e severity;
	int eventid;
	int sub_eventid;
	int en;		/*alarm or clear*/
}bc_stats_alrm_info_t;
#endif



/******************************************************************************\
  Function   : bc_stats_alarm_get_threshold_info
  Description:获取门限信息
  Return     : TRUEN or FALSE
  Others     : 
\******************************************************************************/
int bc_stats_db_threshold_get_info(bc_stats_threshold_info_t *threshold_info);

/******************************************************************************\
  Function   : bc_stats_alarm_get_threshold_info
  Description:获取门限信息
  Return     : TRUEN or FALSE
  Others     : 
\******************************************************************************/
int bc_stats_db_threshold_set_info(bc_stats_threshold_info_t threshold_info);

/******************************************************************************\
  Function   : bc_stats_threshold_alarm
  Description: 门限 告警
  Return     : TRUEN or FALSE
  Others     : 门限检测并触发事件
\******************************************************************************/
int bc_stats_db_threshold_alarm(int cbc_flag, bc_stats_info_t incream_stats_info);

/******************************************************************************\
  Function   : bc_stats_db_threshold_init
  Description: 性能统计的门限与CC相关初始化
  Return     :
  Others     : 
\******************************************************************************/
int bc_stats_db_threshold_init();


#endif /*__BC_STATS_DB_THRESHOLD_H__*/
