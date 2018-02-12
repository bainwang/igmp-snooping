
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

#include "bc_igmp_fwd.h"
//#include "bc_onu.h"
#include "bc_ipc_client.h"
#include "bc_func.h"
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

#define BC_IGMP_FWD_DEFINE_VAR_AND_MALLOC_IPC_BUF                                                   \
        BC_PT_FUN_ENTER(BC_MODULE_IGMP);                                                            \
        bc_err_e ret = BC_ERR_OK;                                                                   \
        bc_char * pbuf = NULL;                                                                      \
        bc_char * tbuf = NULL;                                                                      \
        if (BC_ERR_OK != (ret = bc_ipc_pacakge_alloc((bc_ipc_package_t**)&pbuf)))                 \
        {                                                                                           \
            bc_igmp_dbg("Failed to malloc ipc package: ret = %d\n", ret);                           \
            return ret;                                                                             \
        }                                                                                           \
        tbuf = pbuf;                                                                                \


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
bc_err_e bc_query_igmp_fwd(bc_igmp_fwd_t igmp_fwd[BC_IGMP_OLT_FWD_CFG_MAX_COUNT], bc_int32 *num)
{
    	bc_uint16 count = 0;
	BC_IGMP_FWD_DEFINE_VAR_AND_MALLOC_IPC_BUF;

    	*num = 0;
    	memset(igmp_fwd, 0, sizeof(igmp_fwd));
    

    	BC_IGMP_IPC_REQUEST(BC_FUNC_ENUM(bc_query_igmp_fwd_srv), pbuf, tbuf);

    	BC_IGMP_IPC_RET_READ(tbuf, ret);
    	BC_IGMP_IPC_DATA_READ(tbuf, &count, sizeof(count));
    	BC_IGMP_IPC_DATA_READ(tbuf, igmp_fwd, sizeof(bc_igmp_fwd_t) * count);
    	*num = count;
    
    	BC_IGMP_IPC_FREE(pbuf);

	return ret;
}

#endif
