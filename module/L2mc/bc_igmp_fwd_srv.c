
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
	 D a t e    Modification 										  Initials
	---------- --------------                                        ----------
	2017-06-10  Created												  bin.wang
*******************************************************************************/
#if 0

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								ͷ   ��   ��								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "bc_ipc_def.h"
#include "bc_igmp_fwd.h"
#include "bc_onu_srv.h"
#include "bc_igmp.h"
#include "mcast_mgmt.h"

////////////////////////////////////////////////////////////////////////////////
//																			  //
//						�� �� �� ���� �� �� �� ��							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//																			  //
//						��   ��   ��   ��   ��   ��							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
/*
 *		��Դ�ļ���Ҫ����꣬��ͷ�ļ���������ģ��ͷ�ļ��еĺ궨�����ظ���������
 *	ʱ���ڴ˴����塣
 */

#define LOG_FLAG_MODULE LOG_BIT_ALL



////////////////////////////////////////////////////////////////////////////////
//																			  //
//							ȫ �� �� �� �� ��								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
/* 
 *	�ⲿȫ�ֱ������ṩ�������̵��ã���ͷ�ļ����ṩ���ýӿ�(�ⲿ��������)��
 */

/* 
 *	�ڲ�ȫ�ֱ�����ֻ�ṩ�����ļ��ڲ��������ã�����ͷ�ļ����ṩ���ýӿڡ�
 */

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								��  ��  ��  ��								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								��  ��  ��  ��								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
/******************************************************************************\
  Function   : bc_query_igmp_fwd
  Description: ��ѯigmpת����
  Return     : bc_err_e  �ɹ���ʧ��
  Others     : 
\******************************************************************************/
bc_err_e bc_query_igmp_fwd_srv(bc_ipc_package_t *buf)
{	
	bc_err_e ret = BC_ERR_NOT_SUPPORT;
		
#if BC_PROJ_DEFS_IGMP
	bc_igmp_fwd_t igmp_fwd[BC_IGMP_OLT_FWD_CFG_MAX_COUNT];
	bc_uint16 igmp_fwd_count = 0;
	bc_int32 i = 0;
	bc_int32 j = 0;
	bc_int32 index = 0;
	mcast_mgmt_fwd_t fwd_block[BC_IGMP_OLT_FWD_CFG_MAX_COUNT];
	bc_ipc_package_t *tmp = buf;
    
	memset(igmp_fwd, 0, sizeof(igmp_fwd));	
	
		
	memset(fwd_block, 0, sizeof(mcast_mgmt_fwd_t) * BC_IGMP_OLT_FWD_CFG_MAX_COUNT);
	ret = mcast_mgmt_xx_fwd_get_all(fwd_block, &igmp_fwd_count);
	if (ret != BC_ERR_OK)
	{
		bc_igmp_dbg("mcast_mgmt_xx_fwd_get_all() faile:ret = 0x%x\r\n", ret);
		bc_igmp_free(fwd_block);
		return ret;
	}
	for (i = 0; i < igmp_fwd_count; i ++)
	{
		igmp_fwd[i].ip = fwd_block[i].grp;
		igmp_fwd[i].vid = fwd_block[i].vid;

		index = 0;
		for (j = 0; j < BC_PORT_PON_MAX_COUNT + BC_PORT_SNI_MAX_COUNT; j ++)
		{
			if (fwd_block[i].port_list[j].slot_id != 0 && fwd_block[i].port_list[j].port_id != 0)
			{
				igmp_fwd[i].port_list[index].slot_id = fwd_block[i].port_list[j].slot_id;
				igmp_fwd[i].port_list[index].port_type = fwd_block[i].port_list[j].port_type;
				igmp_fwd[i].port_list[index].port_id = fwd_block[i].port_list[j].port_id;
				index++;
			}
		}
	}	
	buf = tmp;
	BC_IPC_INIT_PACK(buf);
	BC_IGMP_IPC_WRITE_P(buf, igmp_fwd_count);
	BC_IGMP_IPC_WRITE(buf, igmp_fwd, sizeof(bc_igmp_fwd_t) * igmp_fwd_count);
#endif
	return ret;
}

#endif
