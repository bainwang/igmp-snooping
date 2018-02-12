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
#if 0


#ifndef __BCAPI_IGMP_CFG_SRV_H__
#define __BCAPI_IGMP_CFG_SRV_H__

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								头   文   件								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
#include "bc_common_defs.h"
#include "bc_igmp_def.h"
#include "bc_err.h"
////////////////////////////////////////////////////////////////////////////////
//																			  //
//								宏   定   义								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//																			  //
//					结 构 体 、联 合 体、枚 举 定 义				  		  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
	
////////////////////////////////////////////////////////////////////////////////
//																			  //
//						外 部 变 量、 函 数 声 明							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
bc_err_e bc_local_igmp_cfg_download_to_chip(void);
bc_err_e bc_local_set_igmp_mode(bc_int32 resource_id, bc_igmp_mode_e igmp_mode);//only support 3,4
bc_err_e bc_get_igmp_cfg_srv(bc_ipc_package_t * buf);
bc_err_e bc_set_igmp_enable_srv(bc_ipc_package_t * buf);
bc_err_e bc_set_igmp_mode_srv(bc_ipc_package_t * buf);
bc_err_e bc_set_igmp_mode_default_srv(bc_ipc_package_t * buf);
bc_err_e bc_set_igmp_mqrt_srv(bc_ipc_package_t * buf);
bc_err_e bc_set_igmp_mqrt_default_srv(bc_ipc_package_t * buf);
bc_err_e bc_set_igmp_rbst_var_srv(bc_ipc_package_t * buf);
bc_err_e bc_set_igmp_rbst_var_default_srv(bc_ipc_package_t * buf);
bc_err_e bc_set_igmp_query_intrvl_srv(bc_ipc_package_t * buf);
bc_err_e bc_set_igmp_query_intrvl_default_srv(bc_ipc_package_t * buf);
bc_err_e bc_set_igmp_lmqi_srv(bc_ipc_package_t * buf);
bc_err_e bc_set_igmp_lmqi_default_srv(bc_ipc_package_t * buf);
bc_err_e bc_set_igmp_lmqc_srv(bc_ipc_package_t * buf);
bc_err_e bc_set_igmp_lmqc_default_srv(bc_ipc_package_t * buf);
bc_err_e bc_set_igmp_version_srv(bc_ipc_package_t * buf);
bc_err_e bc_set_igmp_version_default_srv(bc_ipc_package_t * buf);

#endif /* __BCAPI_IGMP_CFG_SRV_H__ */

#endif
