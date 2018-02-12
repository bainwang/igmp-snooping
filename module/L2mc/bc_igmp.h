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
	2010-01-07	Created 											  bin.wang
*******************************************************************************/

#ifndef __BCAPI_IGMP_H__
#define __BCAPI_IGMP_H__

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								头   文   件								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
#include "bc_common_defs.h"
#include "bc_igmp_cfg_srv.h"
#include "bc_igmp_fwd_srv.h"
////////////////////////////////////////////////////////////////////////////////
//																			  //
//								宏   定   义								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//																			  //
//					结 构 体 、联 合 体、枚 举 定 义						  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//																			  //
//						外 部 变 量、 函 数 声 明					  		  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#if 1
bc_err_e  bc_igmp_init(void);

bc_int32 bc_igmp_compar_int32(const void *a ,const void *b);
bc_int32 bc_igmp_compar_port_id(const void *a ,const void *b);
#if 0
bc_err_e bc_igmp_get_igmp_cfg_info(bc_igmp_cfg_t *igmp_cfg);
bc_err_e bc_igmp_set_igmp_cfg_info(bc_igmp_cfg_t *igmp_cfg);
bc_err_e bc_igmp_get_igmp_info(bc_igmp_xx_t *igmp_info);
bc_err_e bc_igmp_set_igmp_info(bc_igmp_xx_t *igmp_info);
#endif

#endif
#endif /* __BCAPI_IGMP_H__ */

