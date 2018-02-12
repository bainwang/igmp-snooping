#ifndef __BC_STATS_DB_PERF_H__
#define __BC_STATS_DB_PERF_H__


#include "bc_stats_def.h"
#include "bc_stats_db_threshold.h"
#include "bc_err.h"


/*
	ex cc info
	内部宏
*/
#if 1

#define BC_STATS_DB_EX_CC_TTL		20
#define BC_STATS_DB_EX_CC_NUM		20

typedef struct{
	int en;		/*是否有告警*/
	int bak_en;	/*是否有备份*/
	int val;		/*周期CC计数值*/
	int bak_val;	/*周期初始值*/
	int index;	/*索引编号*/
}per_stats_ex_cc_info_t;

typedef struct{
	int en;
	int vp_en;
	int vc_en;
	int vs_en;
}ex_cc_en_cache;

typedef struct{
	int tic;
	ex_cc_en_cache en_cache;
	per_stats_ex_cc_info_t vp_info[BC_STATS_MAX_VP_COUNT];
	per_stats_ex_cc_info_t vc_info[BC_STATS_MAX_VC_COUNT];
	per_stats_ex_cc_info_t vs_info[BC_STATS_MAX_PORT_COUNT];
}stats_ex_cc_info_t;

typedef struct{
	int idx_cache;
	stats_ex_cc_info_t cc_info[BC_STATS_DB_EX_CC_NUM];
}bc_stats_ex_cc_info_t;
#endif



/******************************************************************************\
  Function   : bc_stats_platform_get_ipc_continuity
  Description: 取IPC连通性状态
  Return     : TRUEN or FALSE
  Others     : 
\******************************************************************************/
int bc_stats_platform_get_ipc_continuity();


#if 1

int bc_stats_db_excc_get_valid_vp_info(per_stats_ex_cc_info_t vp_info[BC_STATS_MAX_VP_COUNT], int *num);
int bc_stats_db_excc_get_valid_vc_info(per_stats_ex_cc_info_t vc_info[BC_STATS_MAX_VC_COUNT], int *num);
int bc_stats_db_excc_get_valid_vs_info(per_stats_ex_cc_info_t vs_info[BC_STATS_MAX_PORT_COUNT], int *num);
int bc_stats_db_excc_get_info(bc_stats_ex_cc_info_t *info);
#endif


int bc_stats_db_perf_get_update_counter_info(bc_stats_db_update_count_t *info);

#if 1


/******************************************************************************\
  Function   : bc_stats_db_get_cur_info
  Description: 获取当前完整的统计
  Return     : TRUEN or FALSE
  Others     : per 1s fflush
\******************************************************************************/
int bc_stats_db_get_cur_info(bc_stats_info_t *stats_info);

/******************************************************************************\
  Function   : bc_stats_db_get_cur_valid_info
  Description: 获取当前有效统计
  Return     : TRUEN or FALSE
  Others     : per 1s fflush
\******************************************************************************/
int bc_stats_db_get_cur_valid_info(bc_stats_info_t *stats_info);

/******************************************************************************\
  Function   : bc_stats_db_get_15min_info
  Description: 获取最新的15分钟统计
  Return     :
  Others     : per 1s fflush
\******************************************************************************/
int bc_stats_db_get_15min_info(bc_stats_info_t *stats_info);

/******************************************************************************\
  Function   : bc_stats_db_get_24hour_info
  Description: 获取最新的24小时统计
  Return     :
  Others     : per 1s fflush
\******************************************************************************/
int bc_stats_db_get_24hour_info(bc_stats_info_t *stats_info);

/******************************************************************************\
  Function   : bc_stats_db_get_last_15min_incream
  Description: 获取最新15分钟与当前统计的差值
  Return     :
  Others     : per 1s fflush
\******************************************************************************/
int bc_stats_db_get_last_15min_incream(bc_stats_info_t *stats_info);

/******************************************************************************\
  Function   : bc_stats_db_get_last_24hour_incream
  Description: 获取最新24小时与当前统计的差值
  Return     :
  Others     : per 1s fflush
\******************************************************************************/
int bc_stats_db_get_last_24hour_incream(bc_stats_info_t *stats_info);

/******************************************************************************\
  Function   : bc_stats_db_get_15min_item_num
  Description: 取15分钟记录条数
  Return     :
  Others     : 
\******************************************************************************/
int bc_stats_db_get_15min_item_num(int *num);

/******************************************************************************\
  Function   : bc_stats_db_get_24hour_item_num
  Description: 取24小时记录条数
  Return     :
  Others     : 
\******************************************************************************/
int bc_stats_db_get_24hour_item_num(int *num);

/******************************************************************************\
  Function   : bc_stats_db_get_15min_item_total_num
  Description: 取15分钟记录总条数
  Return     : TRUEN or FALSE
  Others     : 
\******************************************************************************/
int bc_stats_db_get_15min_item_total_num(int *num);

/******************************************************************************\
  Function   : bc_stats_db_get_24hour_item_total_num
  Description: 取24小时记录总条数
  Return     :
  Others     : 
\******************************************************************************/
int bc_stats_db_get_24hour_item_total_num(int *num);

/******************************************************************************\
  Function   : bc_stats_db_del_info
  Description: 清除所有性能
  Return     : TRUEN or FALSE
  Others     : per 1s fflush
  	清除时禁止更新
  	清除所有保存的15分钟及24小时性能
  	重置性能统计模块
  	备份当前值，作为后续所有性能的基数
\******************************************************************************/
int bc_stats_db_del_info();

/******************************************************************************\
  Function   : bc_stats_db_del_15min_info
  Description: 清除15分钟所有性能
  Return     : TRUEN or FALSE
  Others     : per 1s fflush
\******************************************************************************/
int bc_stats_db_del_15min_info();

/******************************************************************************\
  Function   : bc_stats_db_del_24hour_info
  Description: 清除24小时所有性能
  Return     : TRUEN or FALSE
  Others     : per 1s fflush
\******************************************************************************/
int bc_stats_db_del_24hour_info();
#endif

/******************************************************************************\
  Function   : bc_stats_db_update
  Description:
  Return     : bc_stats_err_e
  Others     : per 1s fflush
\******************************************************************************/
bc_err_e bc_stats_db_update();

/******************************************************************************\
  Function   : bc_stats_db_init
  Description:
  Return     :
  Others     :
\******************************************************************************/
int bc_stats_db_perf_init();

/* debug */
void bc_stats_db_debug_cur_info_smp();
void bc_stats_db_debug_last_15min_info_smp();
void bc_stats_db_debug_last_24hour_info_smp();
void bc_stats_db_debug_base_info();

#endif
