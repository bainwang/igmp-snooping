/*******************************************************************************
  
  [File name]  : \\OLT\
  [Author]     : bin.wang
  [Version]    : 1.0
  [Date]       : 2017-06-05
  [Description]:

  [Others]     :

  [Function List]:
	1. ....
	2. ....
  [History]:
	 D a t e	Modification										  Initials
	---------- --------------										 ----------
	2010-01-07	Created 											  Jash Law
*******************************************************************************/

#ifndef __BCAPI_IGMP_CFG_H__
#define __BCAPI_IGMP_CFG_H__

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								头   文   件								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
#include "bc_common_defs.h"
#include "bc_igmp_def.h"

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								宏   定   义								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//																			  //
//					结 构 体 、联 合 体、枚 举 定 义				 		 //
//																			  //
////////////////////////////////////////////////////////////////////////////////
#if 0
bc_err_e bc_get_igmp_cfg(bc_igmp_cfg_t *igmp_cfg);
bc_err_e bc_set_igmp_enable(bc_boolean enable_flag);
bc_err_e bc_set_igmp_mode(bc_igmp_mode_e igmp_mode);  //only support 2,3,4
bc_err_e bc_set_igmp_mode_default(void);
bc_err_e bc_set_igmp_mqrt(bc_int32 mqrt);
bc_err_e bc_set_igmp_mqrt_default(void);
bc_err_e bc_set_igmp_rbst_var(bc_int32 robust_var);
bc_err_e bc_set_igmp_rbst_var_default(void);
bc_err_e bc_set_igmp_query_intrvl(bc_int32 query_interval);
bc_err_e bc_set_igmp_query_intrvl_default(void);
bc_err_e bc_set_igmp_lmqi(bc_int32 lmqi);
bc_err_e bc_set_igmp_lmqi_default(void);
bc_err_e bc_set_igmp_lmqc(bc_int32 lmqc);
bc_err_e bc_set_igmp_lmqc_default(void);
bc_err_e bc_set_igmp_version(bc_igmp_ver_e ver);
bc_err_e bc_set_igmp_version_default(void);

#endif /* __BCAPI_IGMP_CFG_H__ */
#endif
