/*******************************************************************************
  
  [File name]  : \\OLT\
  [Author]     : bin.wang
  [Version]    : 1.0
  [Date]       : 2017-06-10
  [Description]:

  [Others]     :

  [Function List]:
	1. ....
	2. ....
  [History]:
	 D a t e	Modification										  Initials
	---------- --------------										 ----------
	2010-06-10	Created 											  bin.wang
*******************************************************************************/
#if 0

#ifndef __BCAPI_IGMP_FWD_H__
#define __BCAPI_IGMP_FWD_H__

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								ͷ   ��   ��								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
#include "bc_common_defs.h"
#include "bc_igmp_def.h"
/*
////////////////////////////////////////////////////////////////////////////////
//																			  //
//								��   ��   ��								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
#define OLT_IGMP_FWD_CFG_MAX_COUNT	1024
#define ONU_IGMP_FWD_CFG_NUMBER		64

////////////////////////////////////////////////////////////////////////////////
//																			  //
//					�� �� �� ���� �� �塢ö �� �� ��				  		  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	bc_uint16			vid;
	bc_ipv4				ip;
	bc_port_index_t	    port_list[BC_PORT_PON_MAX_COUNT];		// �˿�������OLT��PON����һ�£��ݲ�֧��ONU��ֱ�Ӷ�ȡ�豸���Եõ���Ӧ����ֵ��
} bcep_igmp_fwd_t;
*/

////////////////////////////////////////////////////////////////////////////////
//																			  //
//						�� �� �� ���� �� �� �� ��					  		  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
bc_err_e bc_query_igmp_fwd(bc_igmp_fwd_t igmp_fwd[BC_IGMP_OLT_FWD_CFG_MAX_COUNT], bc_int32 *num);
#endif /* __BCAPI_IGMP_FWD_H__ */

#endif