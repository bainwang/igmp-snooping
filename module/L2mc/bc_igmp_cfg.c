/*******************************************************************************
  
  [File name]  : \\OLT\bcapi\api_igmp\bcapi_igmp_cfg.c
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
	2017-06-12  Created												   bin.wang
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								ͷ   ��   ��								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "bc_igmp_cfg.h"
//#include "bc_ipc_client.h"
//#include "bc_ipc_package.h"
#include "bc_func.h"
////////////////////////////////////////////////////////////////////////////////
//																			  //
//						�� �� �� ���� �� �� �� ��			 				  //
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

#if 0


#define LOG_FLAG_MODULE LOG_BIT_ALL


#define BC_IGMP_DEFINE_VAR_AND_MALLOC_IPC_BUF                                                       \
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
//								��  ��  ��  ��							  	  //
//																			  //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//																			  //
//								��  ��  ��  ��								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
/******************************************************************************\
  Function   : bc_get_igmp_cfg
  Description: ��ȡigmp���ò���
  Return     : bc_err_e  �ɹ���ʧ��
  Others     : 
\******************************************************************************/
bc_err_e bc_get_igmp_cfg(bc_igmp_cfg_t *igmp_cfg)
{
	BC_IGMP_DEFINE_VAR_AND_MALLOC_IPC_BUF;


    	BC_IGMP_IPC_REQUEST(BC_FUNC_ENUM(bc_get_igmp_cfg_srv), pbuf, tbuf);

    	BC_IGMP_IPC_RET_READ(tbuf, ret);
    	BC_IGMP_IPC_DATA_READ(tbuf, igmp_cfg, sizeof(*igmp_cfg));

    	BC_IGMP_IPC_FREE(pbuf);
    
	return ret;	 
}
 
/******************************************************************************\
  Function   : bc_set_igmp_mode
  Description: ��ȡigmpģʽ
  Return     : bc_err_e  �ɹ���ʧ��
  Others     : 
\******************************************************************************/
bc_err_e bc_set_igmp_enable(bc_boolean enable_flag)
{
	BC_IGMP_DEFINE_VAR_AND_MALLOC_IPC_BUF;

	BC_IGMP_IPC_WRITE_P(tbuf, enable_flag);

    	BC_IGMP_IPC_REQUEST(BC_FUNC_ENUM(bc_set_igmp_enable_srv), pbuf, tbuf);

    	BC_IGMP_IPC_RET_READ(tbuf, ret);

    	BC_IGMP_IPC_FREE(pbuf);
	return ret;  
}

/******************************************************************************\
  Function   : bc_set_igmp_mode
  Description: ��ȡigmpģʽ
  Return     : bc_err_e  �ɹ���ʧ��
  Others     : 
\******************************************************************************/
bc_err_e bc_set_igmp_mode(bc_igmp_mode_e igmp_mode)  //only support 3,4
{
	BC_IGMP_DEFINE_VAR_AND_MALLOC_IPC_BUF;

    	BC_IGMP_IPC_WRITE_P(tbuf, igmp_mode);
    
    	BC_IGMP_IPC_REQUEST(BC_FUNC_ENUM(bc_set_igmp_mode_srv), pbuf, tbuf);

    	BC_IGMP_IPC_RET_READ(tbuf, ret);

    	BC_IGMP_IPC_FREE(pbuf);

	return ret;  
}

/******************************************************************************\
  Function   : bc_set_igmp_mode_default
  Description: ��ȡigmpģʽĬ��ֵ
  Return     : bc_err_e  �ɹ���ʧ��
  Others     : 
\******************************************************************************/
bc_err_e bc_set_igmp_mode_default(void)
{
	BC_IGMP_DEFINE_VAR_AND_MALLOC_IPC_BUF;


    	BC_IGMP_IPC_REQUEST(BC_FUNC_ENUM(bc_set_igmp_mode_default_srv), pbuf, tbuf);

    	BC_IGMP_IPC_RET_READ(tbuf, ret);

    	BC_IGMP_IPC_FREE(pbuf);

	return ret; 
}

/******************************************************************************\
  Function   : bc_set_igmp_mqrt
  Description: ��ȡigmp�����Ӧ��ѯʱ��
  Return     : bc_err_e  �ɹ���ʧ��
  Others     : 
\******************************************************************************/
bc_err_e bc_set_igmp_mqrt(bc_int32 mqrt)
{
	BC_IGMP_DEFINE_VAR_AND_MALLOC_IPC_BUF;

    	BC_IGMP_IPC_WRITE_P(tbuf, mqrt);
    
    	BC_IGMP_IPC_REQUEST(BC_FUNC_ENUM(bc_set_igmp_mqrt_srv), pbuf, tbuf);

    	BC_IGMP_IPC_RET_READ(tbuf, ret);

    	BC_IGMP_IPC_FREE(pbuf);

	return ret; 
}

/******************************************************************************\
  Function   : bc_set_igmp_mqrt
  Description: ��ȡigmp�����Ӧ��ѯʱ��Ĭ��ֵ
  Return     : bc_err_e  �ɹ���ʧ��
  Others     : 
\******************************************************************************/
bc_err_e bc_set_igmp_mqrt_default(void)
{
	BC_IGMP_DEFINE_VAR_AND_MALLOC_IPC_BUF;


    	BC_IGMP_IPC_REQUEST(BC_FUNC_ENUM(bc_set_igmp_mqrt_default_srv), pbuf, tbuf);

    	BC_IGMP_IPC_RET_READ(tbuf, ret);

    	BC_IGMP_IPC_FREE(pbuf);

	return ret; 
}

/******************************************************************************\
  Function   : bc_set_igmp_rbst_var
  Description: ��ȡigmp��׳�Ա���
  Return     : bc_err_e  �ɹ���ʧ��
  Others     : 
\******************************************************************************/
bc_err_e bc_set_igmp_rbst_var(bc_int32 robust_var)
{
	BC_IGMP_DEFINE_VAR_AND_MALLOC_IPC_BUF;

    	BC_IGMP_IPC_WRITE_P(tbuf, robust_var);
    
    	BC_IGMP_IPC_REQUEST(BC_FUNC_ENUM(bc_set_igmp_rbst_var_srv), pbuf, tbuf);

    	BC_IGMP_IPC_RET_READ(tbuf, ret);

    	BC_IGMP_IPC_FREE(pbuf);

	return ret; 
}

/******************************************************************************\
  Function   : bc_set_igmp_rbst_var_default
  Description: ��ȡigmp��׳�Ա���Ĭ��ֵ
  Return     : bc_err_e  �ɹ���ʧ��
  Others     : 
\******************************************************************************/
bc_err_e bc_set_igmp_rbst_var_default(void)
{
	BC_IGMP_DEFINE_VAR_AND_MALLOC_IPC_BUF;


    	BC_IGMP_IPC_REQUEST(BC_FUNC_ENUM(bc_set_igmp_rbst_var_default_srv), pbuf, tbuf);

    	BC_IGMP_IPC_RET_READ(tbuf, ret);

    	BC_IGMP_IPC_FREE(pbuf);

	return ret;
}

/******************************************************************************\
  Function   : bc_set_igmp_query_intrvl
  Description: ��ȡigmp���Ͳ�ѯ���ĵ�ʱ����
  Return     : bc_err_e  �ɹ���ʧ��
  Others     : 
\******************************************************************************/
bc_err_e bc_set_igmp_query_intrvl( bc_int32 query_interval)
{
	BC_IGMP_DEFINE_VAR_AND_MALLOC_IPC_BUF;
	
    	BC_IGMP_IPC_WRITE_P(tbuf, query_interval);
    
    	BC_IGMP_IPC_REQUEST(BC_FUNC_ENUM(bc_set_igmp_query_intrvl_srv), pbuf, tbuf);

    	BC_IGMP_IPC_RET_READ(tbuf, ret);

    	BC_IGMP_IPC_FREE(pbuf);

	return ret;
}

/******************************************************************************\
  Function   : bc_set_igmp_query_intrvl_default
  Description: ��ȡigmp���Ͳ�ѯ���ĵ�ʱ����Ĭ��ֵ
  Return     : bc_err_e  �ɹ���ʧ��
  Others     : 
\******************************************************************************/
bc_err_e bc_set_igmp_query_intrvl_default(void)
{
	BC_IGMP_DEFINE_VAR_AND_MALLOC_IPC_BUF;


    	BC_IGMP_IPC_REQUEST(BC_FUNC_ENUM(bc_set_igmp_query_intrvl_default_srv), pbuf, tbuf);

    	BC_IGMP_IPC_RET_READ(tbuf, ret);

    	BC_IGMP_IPC_FREE(pbuf);

	return ret;
}

/******************************************************************************\
  Function   : bc_set_igmp_lmqi
  Description: ��ȡigmp lmqi
  Return     : bc_err_e  �ɹ���ʧ��
  Others     : 
\******************************************************************************/
bc_err_e bc_set_igmp_lmqi(bc_int32 lmqi)
{
	BC_IGMP_DEFINE_VAR_AND_MALLOC_IPC_BUF;

    	BC_IGMP_IPC_WRITE_P(tbuf, lmqi);
    
    	BC_IGMP_IPC_REQUEST(BC_FUNC_ENUM(bc_set_igmp_lmqi_srv), pbuf, tbuf);

    	BC_IGMP_IPC_RET_READ(tbuf, ret);

    	BC_IGMP_IPC_FREE(pbuf);

	return ret;
}

/******************************************************************************\
  Function   : bc_set_igmp_lmqi_default
  Description: ��ȡigmp lmqiĬ��ֵ
  Return     : bc_err_e  �ɹ���ʧ��
  Others     : 
\******************************************************************************/
bc_err_e bc_set_igmp_lmqi_default(void)
{
	BC_IGMP_DEFINE_VAR_AND_MALLOC_IPC_BUF;

    	BC_IGMP_IPC_REQUEST(BC_FUNC_ENUM(bc_set_igmp_lmqi_default_srv), pbuf, tbuf);

    	BC_IGMP_IPC_RET_READ(tbuf, ret);

    	BC_IGMP_IPC_FREE(pbuf);

	return ret;
}

/******************************************************************************\
  Function   : bc_set_igmp_lmqc
  Description: ��ȡigmp lmqc
  Return     : bc_err_e  �ɹ���ʧ��
  Others     : 
\******************************************************************************/
bc_err_e bc_set_igmp_lmqc(bc_int32 lmqc)
{
	BC_IGMP_DEFINE_VAR_AND_MALLOC_IPC_BUF;

    	BC_IGMP_IPC_WRITE_P(tbuf, lmqc);
    
    	BC_IGMP_IPC_REQUEST(BC_FUNC_ENUM(bc_set_igmp_lmqc_srv), pbuf, tbuf);

    	BC_IGMP_IPC_RET_READ(tbuf, ret);

    	BC_IGMP_IPC_FREE(pbuf);

	return ret;
}

/******************************************************************************\
  Function   : bc_set_igmp_lmqc_default
  Description: ��ȡigmp lmqcĬ��ֵ
  Return     : bc_err_e  �ɹ���ʧ��
  Others     : 
\******************************************************************************/
bc_err_e bc_set_igmp_lmqc_default(void)
{
	BC_IGMP_DEFINE_VAR_AND_MALLOC_IPC_BUF;


    	BC_IGMP_IPC_REQUEST(BC_FUNC_ENUM(bc_set_igmp_lmqc_default_srv), pbuf, tbuf);

    	BC_IGMP_IPC_RET_READ(tbuf, ret);

    	BC_IGMP_IPC_FREE(pbuf);

	return ret;
}

/******************************************************************************\
  Function   : bc_set_igmp_version
  Description: ��ȡigmp�汾
  Return     : bc_err_e  �ɹ���ʧ��
  Others     : 
\******************************************************************************/
bc_err_e bc_set_igmp_version( bc_igmp_ver_e ver)
{
	BC_IGMP_DEFINE_VAR_AND_MALLOC_IPC_BUF;

    	BC_IGMP_IPC_WRITE_P(tbuf, ver);
    
    	BC_IGMP_IPC_REQUEST(BC_FUNC_ENUM(bc_set_igmp_version_srv), pbuf, tbuf);

    	BC_IGMP_IPC_RET_READ(tbuf, ret);

    	BC_IGMP_IPC_FREE(pbuf);

	return ret;
}

/******************************************************************************\
  Function   : bc_set_igmp_version_default
  Description: ��ȡigmp�汾Ĭ��ֵ
  Return     : bc_err_e  �ɹ���ʧ��
  Others     : 
\******************************************************************************/
bc_err_e bc_set_igmp_version_default(void)
{
	BC_IGMP_DEFINE_VAR_AND_MALLOC_IPC_BUF;


    	BC_IGMP_IPC_REQUEST(BC_FUNC_ENUM(bc_set_igmp_version_default_srv), pbuf, tbuf);

    	BC_IGMP_IPC_RET_READ(tbuf, ret);

    	BC_IGMP_IPC_FREE(pbuf);

	return ret;
}

#endif
