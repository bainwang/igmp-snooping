/*******************************************************************************
  Copyright (C), 1988-2018, xxxxx Tech. Co., Ltd.
  [Author]     : bain.wang@outlook.com
  [Version]    : 1.0
  [Date]       : 2017-7-5
  [Description]:

  [Others]     :

  [Function List]:
	1. ....
	2. ....
  [History]:
	 D a t e	Modification										  Initials
	---------- --------------										 ----------
	2017-07-05	Created 										      bain.wang@outlook.com
*******************************************************************************/

#ifndef __BC_STATS_CLIENT_H__
#define __BC_STATS_CLIENT_H__

#include "bc_stats_def.h"
#include "bc_stats_db_threshold.h"
#include "bc_stats_db_perf.h"
#include "bc_err.h"
#include "bc_ipc_def.h"
#include "bc_modules_com_para.h"
////////////////////////////////////////////////////////////////////////////////
//																			  //
//								头   文   件								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//																			  //
//								宏   定   义								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//																			  //
//					结 构 体 、联 合 体、枚 举 定 义				          //
//																			  //
////////////////////////////////////////////////////////////////////////////////




#if 1
/******************************************************************************\
  Function   : bc_stats_get_board_temp
  Description: stats get xxx
  Return     : bc_err_e  成功、失败
  Others     : 
\******************************************************************************/
bc_err_e bc_stats_get_board_temp(OUT bc_int16 *val);

/******************************************************************************\
  Function   : bc_stats_get_board_temp
  Description: stats get xxx
  Return     : bc_err_e  成功、失败
  Others     : 
\******************************************************************************/
bc_err_e bc_stats_get_oamport_info(IN bc_int32 id, OUT oam_port_info_t *info);

/******************************************************************************\
  Function   : bc_stats_get_board_temp
  Description: stats get xxx
  Return     : bc_err_e  成功、失败
  Others     : 
\******************************************************************************/
bc_err_e bc_stats_get_oamport_list(OUT bc_stats_oam_port_info_t *info);

/******************************************************************************\
  Function   : bc_stats_get_board_temp
  Description: stats get xxx
  Return     : bc_err_e  成功、失败
  Others     : 
\******************************************************************************/
bc_err_e bc_stats_get_port_info(IN bc_int32 id, OUT port_info_t *info);

/******************************************************************************\
  Function   : bc_stats_get_board_temp
  Description: stats get xxx
  Return     : bc_err_e  成功、失败
  Others     : 
\******************************************************************************/
bc_err_e bc_stats_get_port_list(OUT bc_stats_port_info_t *info);

/******************************************************************************\
  Function   : bc_stats_get_board_temp
  Description: stats get xxx
  Return     : bc_err_e  成功、失败
  Others     : 
\******************************************************************************/
bc_err_e bc_stats_get_ptpport_info(IN bc_int32 id, OUT ptp_port_info_t *info);

/******************************************************************************\
  Function   : bc_stats_get_ptpport_list
  Description: stats get xxx
  Return     : bc_err_e  成功、失败
  Others     : 
\******************************************************************************/
bc_err_e bc_stats_get_ptpport_list(OUT bc_stats_ptp_port_info_t *info);

/******************************************************************************\
  Function   : bc_stats_get_board_temp
  Description: stats get xxx
  Return     : bc_err_e  成功、失败
  Others     : 
\******************************************************************************/
bc_err_e bc_stats_get_ptp_info(OUT ptp_info_t *info);

/******************************************************************************\
  Function   : bc_stats_get_board_temp
  Description: stats get xxx
  Return     : bc_err_e  成功、失败
  Others     : 
\******************************************************************************/
bc_err_e bc_stats_get_vp_info(IN bc_int32 id, OUT vp_info_t *info);

/******************************************************************************\
  Function   : bc_stats_get_board_temp
  Description: stats get xxx
  Return     : bc_err_e  成功、失败
  Others     : 
\******************************************************************************/
bc_err_e bc_stats_get_vp_list(OUT bc_stats_vp_info_t *info);

/******************************************************************************\
  Function   : bc_stats_get_board_temp
  Description: stats get xxx
  Return     : bc_err_e  成功、失败
  Others     : 
\******************************************************************************/
bc_err_e bc_stats_get_vc_info(IN bc_int32 id, OUT vc_info_t *info);

/******************************************************************************\
  Function   : bc_stats_get_board_temp
  Description: stats get xxx
  Return     : bc_err_e  成功、失败
  Others     : 
\******************************************************************************/
bc_err_e bc_stats_get_vc_list(OUT bc_stats_vc_info_t *info);

/******************************************************************************\
  Function   : bc_stats_get_board_temp
  Description: stats get xxx
  Return     : bc_err_e  成功、失败
  Others     : 
\******************************************************************************/
bc_err_e bc_stats_get_e1_info(IN bc_int32 id, OUT e1_info_t *info);

/******************************************************************************\
  Function   : bc_stats_get_board_temp
  Description: stats get xxx
  Return     : bc_err_e  成功、失败
  Others     : 
\******************************************************************************/
bc_err_e bc_stats_get_e1_list(OUT bc_stats_e1_info_t *info);

/******************************************************************************\
  Function   : bc_stats_get_cur_info
  Description: stats get xxx
  Return     : bc_err_e  成功、失败
  Others     : 
\******************************************************************************/
bc_err_e bc_stats_get_cur_info(OUT bc_stats_info_t *info);

/******************************************************************************\
  Function   : bc_stats_get_board_temp
  Description: stats get xxx
  Return     : bc_err_e  成功、失败
  Others     : 
\******************************************************************************/
bc_err_e bc_stats_get_15min_info(OUT bc_stats_info_t *info);

/******************************************************************************\
  Function   : bc_stats_get_24hour_info
  Description: stats get xxx
  Return     : bc_err_e  成功、失败
  Others     : 
\******************************************************************************/
bc_err_e bc_stats_get_24hour_info(OUT bc_stats_info_t *info);

/******************************************************************************\
  Function   : bc_stats_get_board_temp
  Description: stats get xxx
  Return     : bc_err_e  成功、失败
  Others     : 
\******************************************************************************/
bc_err_e bc_stats_get_15min_incream_info(OUT bc_stats_info_t *info);

/******************************************************************************\
  Function   : bc_stats_get_board_temp
  Description: stats get xxx
  Return     : bc_err_e  成功、失败
  Others     : 
\******************************************************************************/
bc_err_e bc_stats_get_24hour_incream_info(OUT bc_stats_info_t *info);

/******************************************************************************\
  Function   : bc_stats_get_board_temp
  Description: stats get xxx
  Return     : bc_err_e  成功、失败
  Others     : 
\******************************************************************************/
bc_err_e bc_stats_get_15min_num(OUT bc_int32 *num);

/******************************************************************************\
  Function   : bc_stats_get_board_temp
  Description: stats get xxx
  Return     : bc_err_e  成功、失败
  Others     : 
\******************************************************************************/
bc_err_e bc_stats_get_15min_valid_num(OUT bc_int32 *num);

/******************************************************************************\
  Function   : bc_stats_get_24hour_num_info
  Description: stats get xxx
  Return     : bc_err_e  成功、失败
  Others     : 
\******************************************************************************/
bc_err_e bc_stats_get_24hour_num(OUT bc_int32 *num);

bc_err_e bc_stats_get_24hour_valid_num(OUT bc_int32 *num);

/******************************************************************************\
  Function   : bc_stats_del_info
  Description: stats get xxx
  Return     : bc_err_e  成功、失败
  Others     : 
\******************************************************************************/
bc_err_e bc_stats_del_info();

/******************************************************************************\
  Function   : bc_stats_del_15min_info
  Description: stats get xxx
  Return     : bc_err_e  成功、失败
  Others     : 
\******************************************************************************/
bc_err_e bc_stats_del_15min_info();

/******************************************************************************\
  Function   : bc_stats_del_24hour_info
  Description: stats get xxx
  Return     : bc_err_e  成功、失败
  Others     : 
\******************************************************************************/
bc_err_e bc_stats_del_24hour_info();

/******************************************************************************\
  Function   : bc_stats_threshold_get
  Description: stats get xxx
  Return     : bc_err_e  成功、失败
  Others     : 
\******************************************************************************/
bc_err_e bc_stats_threshold_get(bc_stats_threshold_info_t *info);

/******************************************************************************\
  Function   : bc_stats_threshold_set
  Description: stats get xxx
  Return     : bc_err_e  成功、失败
  Others     : 
\******************************************************************************/
bc_err_e bc_stats_threshold_set(bc_stats_threshold_info_t info);

#endif

#endif	/*__BC_STATS_CLIENT_H__*/


