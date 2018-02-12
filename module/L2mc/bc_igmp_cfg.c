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
//								头   文   件								  //
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
//						外 部 变 量、 函 数 引 用			 				  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//																			  //
//						结   构   体   宏   定   义							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
/*
 *		当源文件需要定义宏，而头文件又与其它模块头文件中的宏定义有重复定义嫌疑
 *	时，在此处定义。
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
//							全 局 变 量 定 义								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
/* 
 *	外部全局变量，提供整个工程调用，在头文件中提供调用接口(外部引用声明)。
 */

/* 
 *	内部全局变量，只提供给该文件内部函数调用，不在头文件中提供调用接口。
 */

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								函  数  声  明							  	  //
//																			  //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//																			  //
//								函  数  定  义								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
/******************************************************************************\
  Function   : bc_get_igmp_cfg
  Description: 获取igmp配置参数
  Return     : bc_err_e  成功，失败
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
  Description: 获取igmp模式
  Return     : bc_err_e  成功，失败
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
  Description: 获取igmp模式
  Return     : bc_err_e  成功，失败
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
  Description: 获取igmp模式默认值
  Return     : bc_err_e  成功，失败
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
  Description: 获取igmp最大响应查询时间
  Return     : bc_err_e  成功，失败
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
  Description: 获取igmp最大响应查询时间默认值
  Return     : bc_err_e  成功，失败
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
  Description: 获取igmp健壮性变量
  Return     : bc_err_e  成功，失败
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
  Description: 获取igmp健壮性变量默认值
  Return     : bc_err_e  成功，失败
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
  Description: 获取igmp发送查询报文的时间间隔
  Return     : bc_err_e  成功，失败
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
  Description: 获取igmp发送查询报文的时间间隔默认值
  Return     : bc_err_e  成功，失败
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
  Description: 获取igmp lmqi
  Return     : bc_err_e  成功，失败
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
  Description: 获取igmp lmqi默认值
  Return     : bc_err_e  成功，失败
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
  Description: 获取igmp lmqc
  Return     : bc_err_e  成功，失败
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
  Description: 获取igmp lmqc默认值
  Return     : bc_err_e  成功，失败
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
  Description: 获取igmp版本
  Return     : bc_err_e  成功，失败
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
  Description: 获取igmp版本默认值
  Return     : bc_err_e  成功，失败
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
