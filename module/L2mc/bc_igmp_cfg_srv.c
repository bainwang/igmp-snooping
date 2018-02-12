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
#include "bc_ipc_def.h"
#include "bc_igmp_cfg.h"
#include "bc_onu_srv.h"
#include "mcast_mgmt.h"
#include "bc_igmp_mltcst_package.h"
#include "bc_igmp_proxy_srv.h"
#include "bc_oam_api.h"
#include "bc_igmp.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

#define LOG_FLAG_MODULE LOG_BIT_ALL

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
#if 0

#if 1
/******************************************************************************\
  Function   : bc_init_igmp_cfg
  Description: 初始化，只配置OLT，ONU暂不支持。进程间调用直接返回BCEP_NO_ERROR，不作任何处理。
  Return     : 
  Others     : 
\******************************************************************************/

bc_err_e bc_local_igmp_cfg_download_to_chip(void)
{	
	bc_err_e ret = BC_ERR_OK;
	mcast_mgmt_cfg_t mcast_mgmt_cfg;
	bc_igmp_cfg_t	 igmp_cfg;

	memset(&igmp_cfg, 0x00, sizeof(bc_igmp_cfg_t));
	memset(&mcast_mgmt_cfg, 0x00, sizeof(mcast_mgmt_cfg_t));
	
	bc_igmp_get_igmp_cfg_info(&igmp_cfg);
	if (igmp_cfg.igmp_enable_flag)
	{
		if (igmp_cfg.igmp_mode == BC_IGMP_MODE_DISABLE)
		{
			igmp_cfg.igmp_mode = BC_IGMP_MODE_DISTRIBUTEDWOCM;
		}
		else
		{
			mcast_mgmt_cfg.mode = igmp_cfg.igmp_mode;
		}	

		/*drv*/
		ret = mcast_mgmt_xx_cfg_set(MCAST_MGMT_CFG_MODE, &mcast_mgmt_cfg);
		if (ret != BC_ERR_OK)
		{
			bc_igmp_dbg("mcast_mgmt_xx_cfg_set() faile!!\r\n");
			ret = BC_ERR_IGMP_DRIVER_ERROR;
			goto EXIT;
		}
		
	}
	bc_igmp_set_igmp_cfg_info(&igmp_cfg);
/*
	if (g_xx_igmp.igmp_cfg.mqrt != MQRT_DEFAULT)
	{
		mcast_mgmt_cfg.mqrt = g_xx_igmp.igmp_cfg.mqrt;
		ret = mcast_mgmt_xx_cfg_set(MCAST_MGMT_CFG_MQRT, &mcast_mgmt_cfg);
		if (ret != BC_ERR_OK)
		{
			bc_igmp_dbg("mcast_mgmt_xx_cfg_set() faile!!\r\n");
			ret = BC_ERR_IGMP_DRIVER_ERROR;
			goto EXIT;
		}
	}

	if (g_xx_igmp.igmp_cfg.robust_var != ROBUST_VAR_DEFAULT)
	{
		mcast_mgmt_cfg.robust_var = g_xx_igmp.igmp_cfg.robust_var;
		ret = mcast_mgmt_xx_cfg_set(MCAST_MGMT_CFG_ROBUST_VAR, &mcast_mgmt_cfg);
		if (ret != BC_ERR_OK)
		{
			bc_igmp_dbg("mcast_mgmt_xx_cfg_set() faile!!\r\n");
			ret = BC_ERR_IGMP_DRIVER_ERROR;
			goto EXIT;
		}
	}
	
	if (g_xx_igmp.igmp_cfg.query_interval != QUERY_INTERVAL_DEFAULT)
	{
		mcast_mgmt_cfg.query_interval = g_xx_igmp.igmp_cfg.query_interval;
		ret = mcast_mgmt_xx_cfg_set(MCAST_MGMT_CFG_QUERY_INTERVAL, &mcast_mgmt_cfg);
		if (ret != BC_ERR_OK)
		{
			bc_igmp_dbg("mcast_mgmt_xx_cfg_set faile!!\r\n");
			ret = BC_ERR_IGMP_DRIVER_ERROR;
			goto EXIT;
		}
	}

	if (g_xx_igmp.igmp_cfg.lmqi != LMQI_DEFAULT)
	{
		mcast_mgmt_cfg.lmqi = g_xx_igmp.igmp_cfg.lmqi;
		ret = mcast_mgmt_xx_cfg_set(MCAST_MGMT_CFG_LMQI, &mcast_mgmt_cfg);
		if (ret != BC_ERR_OK)
		{
			bc_igmp_dbg("mcast_mgmt_xx_cfg_set() faile:ret = 0x%x\r\n\r\n", ret);
			ret = BC_ERR_IGMP_DRIVER_ERROR;
			goto EXIT;
		}
	}

	if (g_xx_igmp.igmp_cfg.lmqc != LMQC_DEFAULT)
	{
		mcast_mgmt_cfg.lmqc = g_xx_igmp.igmp_cfg.lmqc;
		ret = mcast_mgmt_xx_cfg_set(MCAST_MGMT_CFG_LMQC, &mcast_mgmt_cfg);
		if (ret != BC_ERR_OK)			
		{
			bc_igmp_dbg("mcast_mgmt_xx_cfg_set() faile!!\r\n");
			ret = BC_ERR_IGMP_DRIVER_ERROR;
			goto EXIT;
		}
	}

	if (g_xx_igmp.igmp_cfg.ver != VER_DEFAULT)
	{
		mcast_mgmt_cfg.ver = g_xx_igmp.igmp_cfg.ver;
		ret = mcast_mgmt_xx_cfg_set(MCAST_MGMT_CFG_VER, &mcast_mgmt_cfg);
		if (ret != BC_ERR_OK)
		{
			bc_igmp_dbg("mcast_mgmt_xx_cfg_set() faile!!\r\n");
			ret = BC_ERR_IGMP_DRIVER_ERROR;
			goto EXIT;
		}
	}
	*/
EXIT:
	return BC_ERR_OK;
}

void print_igmp_cfg(bc_igmp_cfg_t *igmp_cfg)
{
	bc_igmp_dbg("igmp_mode = %d mqrt = %d robust_var = %d query_interval = %d lmqi = %d lmqc = %d ver = %d\r\n",
				igmp_cfg->igmp_mode, igmp_cfg->mqrt, igmp_cfg->robust_var, igmp_cfg->query_interval, igmp_cfg->lmqi, igmp_cfg->lmqc, igmp_cfg->ver);
}

/******************************************************************************\
  Function   : bc_set_igmp_version
  Description: 获取igmp版本
  Return     : bc_err_e  成功，失败
  Others     : 
\******************************************************************************/
static bc_err_e bc_local_set_igmp_version(bc_igmp_ver_e ver)
{
	bc_igmp_dbg("bc_set_igmp_version():ver = %d\r\n", ver);
	bc_err_e ret = BC_ERR_OK;
    	mcast_mgmt_cfg_t mcast_mgmt_cfg;
	bc_igmp_cfg_t	 igmp_cfg;
	
    	memset(&mcast_mgmt_cfg, 0, sizeof(mcast_mgmt_cfg));
	memset(&igmp_cfg, 0x00, sizeof(bc_igmp_cfg_t));

	bc_igmp_get_igmp_cfg_info(&igmp_cfg);	
	

	if (ver < BC_IGMP_VER_V1 || ver > BC_IGMP_VER_V3)
	{
		bc_igmp_dbg("igmp version value error!!\r\n");
		ret = BC_ERR_IGMP_CFG_VALUE_ERROR;
		goto EXIT;
	}

	mcast_mgmt_cfg.ver = ver;
	ret = mcast_mgmt_xx_cfg_set(MCAST_MGMT_CFG_VER, &mcast_mgmt_cfg);
	if (ret != BC_ERR_OK)
	{
		bc_igmp_dbg("mcast_mgmt_xx_cfg_set() faile!!\r\n");
		goto EXIT;
	}
	bc_igmp_dbg("mcast_mgmt_xx_cfg_set() finished!!\r\n");
	igmp_cfg.ver = ver;
	bc_igmp_set_igmp_cfg_info(&igmp_cfg);	
EXIT:
	return ret;
}

static bc_err_e bc_local_set_igmp_enable(bc_boolean enable_flag)
{
	bc_igmp_dbg("bc_local_set_igmp_enable(): enable_flag = %d\r\n",enable_flag);	
	
	bc_err_e ret = BC_ERR_OK;
	mcast_mgmt_cfg_t mcast_mgmt_cfg;
	bc_igmp_cfg_t	 igmp_cfg;

	memset(&igmp_cfg, 0x00, sizeof(bc_igmp_cfg_t));
	memset(&mcast_mgmt_cfg, 0x00, sizeof(mcast_mgmt_cfg_t));
	bc_igmp_get_igmp_cfg_info(&igmp_cfg);
	
	if (igmp_cfg.igmp_enable_flag == enable_flag)
	{
		return BC_ERR_OK;
	}
	
	if (enable_flag == TRUE)
	{
		if (igmp_cfg.igmp_mode == BC_IGMP_MODE_DISABLE)
		{
			igmp_cfg.igmp_mode = BC_IGMP_MODE_DISTRIBUTEDWOCM;
			bc_igmp_set_igmp_cfg_info(&igmp_cfg);
		}
		else
		{
			mcast_mgmt_cfg.mode = igmp_cfg.igmp_mode;
		}
	}
	else
	{
		mcast_mgmt_cfg.mode = BC_IGMP_MODE_DISABLE;
	}		
	ret = mcast_mgmt_xx_cfg_set(MCAST_MGMT_CFG_MODE, &mcast_mgmt_cfg);
	if (ret != BC_ERR_OK)
	{
		goto EXIT;
	}
	igmp_cfg.igmp_enable_flag = enable_flag;
	bc_igmp_set_igmp_cfg_info(&igmp_cfg);
EXIT:
	return ret;
}

bc_err_e bc_local_set_igmp_mode(bc_int32 resource_id, bc_igmp_mode_e igmp_mode)//only support 2,3,4
{
	bc_igmp_dbg("bc_set_igmp_mode():igmp_mode = %d\r\n", igmp_mode);	
	bc_err_e ret = BC_ERR_OK;
    	mcast_mgmt_cfg_t mcast_mgmt_cfg;
    	bc_igmp_cfg_t	 igmp_cfg;
		
    	memset(&mcast_mgmt_cfg, 0, sizeof(mcast_mgmt_cfg));
	memset(&igmp_cfg, 0x00, sizeof(bc_igmp_cfg_t));
	
	bc_igmp_get_igmp_cfg_info(&igmp_cfg);
	
	if (igmp_mode < BC_IGMP_MODE_CENTRALIZED || igmp_mode > BC_IGMP_MODE_DISTRIBUTEDWOCM)
	{
		bc_igmp_dbg("igmp mode value error!!\r\n");
		ret = BC_ERR_IGMP_CFG_VALUE_ERROR;
		goto EXIT;
	}
    
	if (igmp_cfg.igmp_mode == igmp_mode)
	{
		return BC_ERR_OK;
	}

	mcast_mgmt_cfg.mode = igmp_mode;
	ret = mcast_mgmt_xx_cfg_set(MCAST_MGMT_CFG_MODE, &mcast_mgmt_cfg);
	if (ret != BC_ERR_OK)
	{
		bc_igmp_dbg("mcast_mgmt_xx_cfg_set() faile!!\r\n");
		goto EXIT;
	}
	bc_igmp_dbg("mcast_mgmt_xx_cfg_set() finished!!\r\n");
		
	/*bcapi*/
	igmp_cfg.igmp_mode = igmp_mode;
	bc_igmp_set_igmp_cfg_info(&igmp_cfg);
EXIT:
	return ret;
}

bc_err_e bc_local_set_onu_igmp_mode(bc_int32 resource_id, bc_uint16 onu_id, bc_igmp_mode_e igmp_mode)
{
	
	bc_err_e ret = BC_ERR_OK;
	mcast_mgmt_cfg_t mcast_mgmt_cfg;
		
    	memset(&mcast_mgmt_cfg, 0, sizeof(mcast_mgmt_cfg));	
	BC_IGMP_ONU_ID_CHECK(onu_id);
	mcast_mgmt_cfg.mode = igmp_mode;
	ret = mcast_mgmt_onu_cfg_set(resource_id, onu_id, MCAST_MGMT_CFG_MODE, &mcast_mgmt_cfg);
	if (ret != BC_ERR_OK)
	{
		bc_igmp_dbg("mcast_mgmt_xx_cfg_set() faile!!\r\n");
		goto EXIT;
	}
EXIT:
	return ret;
}

/******************************************************************************\
  Function   : bc_set_igmp_mqrt
  Description: 获取igmp最大响应查询时间
  Return     : bc_err_e  成功，失败
  Others     : 
\******************************************************************************/
static bc_err_e bc_local_set_igmp_mqrt(bc_int32 mqrt)
{
	bc_igmp_dbg("bc_set_igmp_mqrt():mqrt = %d\r\n", mqrt);
    	mcast_mgmt_cfg_t mcast_mgmt_cfg;
    	bc_err_e ret = BC_ERR_OK;
	bc_igmp_cfg_t	 igmp_cfg;
    	memset(&mcast_mgmt_cfg, 0, sizeof(mcast_mgmt_cfg));
	memset(&igmp_cfg, 0x00, sizeof(bc_igmp_cfg_t));
		
    	bc_igmp_get_igmp_cfg_info(&igmp_cfg);

	if (mqrt < BC_IGMP_MQRT_MIN || mqrt > BC_IGMP_MQRT_MAX)
	{
		bc_igmp_dbg("igmp mqrt value error!!\r\n");
		ret = BC_ERR_IGMP_CFG_VALUE_ERROR;
		goto EXIT;
	}
		
	mcast_mgmt_cfg.mqrt = mqrt;
	ret = mcast_mgmt_xx_cfg_set(MCAST_MGMT_CFG_MQRT, &mcast_mgmt_cfg);
	if (ret != BC_ERR_OK)
	{
		bc_igmp_dbg("mcast_mgmt_xx_cfg_set() faile!!\r\n");
		goto EXIT;
	}
	bc_igmp_dbg("mcast_mgmt_xx_cfg_set() finished!!\r\n");
	igmp_cfg.mqrt = mqrt;
	bc_igmp_set_igmp_cfg_info(&igmp_cfg);
EXIT:
	return ret;

}

/******************************************************************************\
  Function   : bc_set_igmp_rbst_var
  Description: 获取igmp健壮性变量
  Return     : bc_err_e  成功，失败
  Others     : 
\******************************************************************************/
static bc_err_e bc_local_set_igmp_rbst_var(bc_int32 robust_var)
{
	bc_igmp_dbg("bc_set_igmp_rbst_var():robust_var = %d\r\n", robust_var);
    	mcast_mgmt_cfg_t mcast_mgmt_cfg;
    	bc_err_e ret = BC_ERR_OK;
	bc_igmp_cfg_t	 igmp_cfg;
    	memset(&mcast_mgmt_cfg, 0, sizeof(mcast_mgmt_cfg));
	memset(&igmp_cfg, 0x00, sizeof(bc_igmp_cfg_t));
		
    	bc_igmp_get_igmp_cfg_info(&igmp_cfg);

	if (robust_var < BC_IGMP_ROBUST_VAR_MIN || robust_var > BC_IGMP_ROBUST_VAR_MAX)
	{
		bc_igmp_dbg("igmp rbst value error!!\r\n");
		ret = BC_ERR_IGMP_CFG_VALUE_ERROR;
		goto EXIT;
	}

	mcast_mgmt_cfg.robust_var = robust_var;
	ret = mcast_mgmt_xx_cfg_set(MCAST_MGMT_CFG_ROBUST_VAR, &mcast_mgmt_cfg);
	if (ret != BC_ERR_OK)
	{
		bc_igmp_dbg("mcast_mgmt_xx_cfg_set() faile!!\r\n");
		ret = BC_ERR_IGMP_DRIVER_ERROR;
		goto EXIT;
	}
	bc_igmp_dbg("mcast_mgmt_xx_cfg_set() finished!!\r\n");
	igmp_cfg.robust_var = robust_var;
	bc_igmp_set_igmp_cfg_info(&igmp_cfg);
EXIT:
	return ret;
}

/******************************************************************************\
  Function   : bc_set_igmp_query_intrvl
  Description: 获取igmp发送查询报文的时间间隔
  Return     : bc_err_e  成功，失败
  Others     : 
\******************************************************************************/
static bc_err_e bc_local_set_igmp_query_intrvl(bc_int32 query_interval)
{
	bc_igmp_dbg("bc_set_igmp_query_intrvl():query_interval = %d\r\n", query_interval);
    	mcast_mgmt_cfg_t mcast_mgmt_cfg;
    	bc_err_e ret = BC_ERR_OK;
	bc_igmp_cfg_t	 igmp_cfg;
    	memset(&mcast_mgmt_cfg, 0, sizeof(mcast_mgmt_cfg));
 	
	memset(&igmp_cfg, 0x00, sizeof(bc_igmp_cfg_t));
		
    	bc_igmp_get_igmp_cfg_info(&igmp_cfg);


	if (query_interval < BC_IGMP_QUERY_INTERVAL_MIN || query_interval > BC_IGMP_QUERY_INTERVAL_MAX)
	{
		bc_igmp_dbg("igmp query_intrvl value error!!\r\n");
		ret = BC_ERR_IGMP_CFG_VALUE_ERROR;
		goto EXIT;
	}
		
	mcast_mgmt_cfg.query_interval = query_interval;
	ret = mcast_mgmt_xx_cfg_set(MCAST_MGMT_CFG_QUERY_INTERVAL, &mcast_mgmt_cfg);
	if (ret != BC_ERR_OK)
	{
		bc_igmp_dbg("mcast_mgmt_xx_cfg_set faile!!\r\n");
		goto EXIT;
	}
	bc_igmp_dbg("mcast_mgmt_xx_cfg_set() finished!!\r\n");

	igmp_cfg.query_interval = query_interval;
	bc_igmp_set_igmp_cfg_info(&igmp_cfg);
EXIT:
	return ret;

}

/******************************************************************************\
  Function   : bc_set_igmp_lmqi
  Description: 获取igmp lmqi
  Return     : bc_err_e  成功，失败
  Others     : 
\******************************************************************************/
static bc_err_e bc_local_set_igmp_lmqi(bc_int32 lmqi)
{
	bc_igmp_dbg("bc_set_igmp_lmqi():lmqi = %d\r\n", lmqi);

    	bc_err_e ret = BC_ERR_OK;
    	mcast_mgmt_cfg_t mcast_mgmt_cfg;
	bc_igmp_cfg_t	 igmp_cfg;
    	memset(&mcast_mgmt_cfg, 0, sizeof(mcast_mgmt_cfg));
	memset(&igmp_cfg, 0x00, sizeof(bc_igmp_cfg_t));
		
    	bc_igmp_get_igmp_cfg_info(&igmp_cfg);
		
	if (lmqi < BC_IGMP_LMQI_MIN || lmqi > BC_IGMP_LMQI_MAX)
	{
		bc_igmp_dbg("igmp lmqi value error!!\r\n");
		ret = BC_ERR_IGMP_CFG_VALUE_ERROR;
		goto EXIT;
	}

	mcast_mgmt_cfg.lmqi = lmqi;
	ret = mcast_mgmt_xx_cfg_set(MCAST_MGMT_CFG_LMQI, &mcast_mgmt_cfg);
	if (ret != BC_ERR_OK)
	{
		bc_igmp_dbg("mcast_mgmt_xx_cfg_set() faile:ret = 0x%x\r\n\r\n", ret);
		goto EXIT;
	}
	bc_igmp_dbg("bc_set_igmp_lmqi() finished!!\r\n");
	igmp_cfg.lmqi = lmqi;
	bc_igmp_set_igmp_cfg_info(&igmp_cfg);
EXIT:
	return ret;
}

/******************************************************************************\
  Function   : bc_set_igmp_lmqc
  Description: 获取igmp lmqc
  Return     : bc_err_e  成功，失败
  Others     : 
\******************************************************************************/
static bc_err_e bc_local_set_igmp_lmqc(bc_int32 lmqc)
{
	bc_igmp_dbg("bc_set_igmp_lmqc():lmqc = %d\r\n", lmqc);
    	mcast_mgmt_cfg_t mcast_mgmt_cfg;
    	bc_err_e ret = BC_ERR_OK;
	bc_igmp_cfg_t	 igmp_cfg;
	
	memset(&igmp_cfg, 0x00, sizeof(bc_igmp_cfg_t));
    	memset(&mcast_mgmt_cfg, 0, sizeof(mcast_mgmt_cfg));
		
    	bc_igmp_get_igmp_cfg_info(&igmp_cfg);
		
	if (lmqc < BC_IGMP_LMQC_MIN || lmqc > BC_IGMP_LMQC_MAX)
	{
		bc_igmp_dbg("igmp lmqc value error!!\r\n");
		ret = BC_ERR_IGMP_CFG_VALUE_ERROR;
		goto EXIT;
	}

	mcast_mgmt_cfg.lmqc = lmqc;
	ret = mcast_mgmt_xx_cfg_set(MCAST_MGMT_CFG_LMQC, &mcast_mgmt_cfg);
	if (ret != BC_ERR_OK)			
	{
		bc_igmp_dbg("mcast_mgmt_xx_cfg_set() faile!!\r\n");

		goto EXIT;
	}
	bc_igmp_dbg("mcast_mgmt_xx_cfg_set() finished!!\r\n");
	igmp_cfg.lmqc = lmqc;
	bc_igmp_set_igmp_cfg_info(&igmp_cfg);
EXIT:
	return ret;
	
}
#endif
/******************************************************************************\
  Function   : bc_set_igmp_lmqi
  Description: 获取igmp lmqi
  Return     : bc_err_e  成功，失败
  Others     : 
\******************************************************************************/
bc_err_e bc_set_igmp_lmqi_srv(bc_ipc_package_t *buf)
{	
    	bc_err_e ret = BC_ERR_NOT_SUPPORT;
		
#if BC_PROJ_DEFS_IGMP

	bc_int32 lmqi;    
	BC_IGMP_IPC_READ_P(buf, lmqi);
	
	ret = bc_local_set_igmp_lmqi(lmqi);
	
#endif
	BC_IPC_INIT_PACK(buf);
	return ret;
}

/******************************************************************************\
  Function   : bc_get_igmp_cfg
  Description: 获取igmp配置参数
  Return     : bc_err_e  成功，失败
  Others     : 
\******************************************************************************/
bc_err_e bc_get_igmp_cfg_srv(bc_ipc_package_t * buf)
{
	bc_err_e ret = BC_ERR_NOT_SUPPORT;
		
#if BC_PROJ_DEFS_IGMP

	bc_ipc_package_t *tbuf = buf;
  	bc_igmp_cfg_t	 igmp_cfg;

	memset(&igmp_cfg, 0x00, sizeof(bc_igmp_cfg_t));
	ret = bc_igmp_get_igmp_cfg_info(&igmp_cfg);
	
	BC_IPC_INIT_PACK(buf);
	BC_IGMP_IPC_WRITE_P(tbuf, igmp_cfg);
	
#endif
	return ret;
}

bc_err_e bc_set_igmp_enable_srv(bc_ipc_package_t *buf)
{
	bc_err_e ret = BC_ERR_NOT_SUPPORT;
		
#if BC_PROJ_DEFS_IGMP
	bc_igmp_dbg("bc_set_igmp_enable_srv()\r\n");
	
	bc_boolean enable_flag;
    
	BC_IGMP_IPC_READ_P(buf, enable_flag);
	
	ret = bc_local_set_igmp_enable(enable_flag);
	
#endif
	BC_IPC_INIT_PACK(buf);
	return ret;
}

/******************************************************************************\
  Function   : bc_set_igmp_mode
  Description: 获取igmp模式
  Return     : bc_err_e  成功，失败
  Others     : 
\******************************************************************************/
bc_err_e bc_set_igmp_mode_srv(bc_ipc_package_t *buf)
{
	bc_err_e ret = BC_ERR_NOT_SUPPORT;
		
#if BC_PROJ_DEFS_IGMP
	bc_igmp_dbg("bc_set_igmp_mode_srv()\r\n");
	
	bc_igmp_mode_e igmp_mode;  //only support 3,4
	
	BC_IGMP_IPC_READ_P(buf, igmp_mode);
	
	ret = bc_local_set_igmp_mode(BC_OAM_GS_RES_ASYNC_E, igmp_mode);
#endif
	BC_IPC_INIT_PACK(buf);
	return ret;
}

/******************************************************************************\
  Function   : bc_set_igmp_mode_default
  Description: 获取igmp模式默认值
  Return     : bc_err_e  成功，失败
  Others     : 
\******************************************************************************/
bc_err_e bc_set_igmp_mode_default_srv(bc_ipc_package_t *buf)
{
	bc_err_e ret = BC_ERR_NOT_SUPPORT;
		
#if BC_PROJ_DEFS_IGMP
	bc_igmp_dbg("bc_set_igmp_mode_default_srv()\r\n");
	
	ret = bc_local_set_igmp_mode(BC_OAM_GS_RES_ASYNC_E, BC_IGMP_MODE_DEFAULT);
#endif
	BC_IPC_INIT_PACK(buf);
	return ret;
}

/******************************************************************************\
  Function   : bc_set_igmp_mqrt
  Description: 获取igmp最大响应查询时间
  Return     : bc_err_e  成功，失败
  Others     : 
\******************************************************************************/
bc_err_e bc_set_igmp_mqrt_srv(bc_ipc_package_t *buf)
{
	bc_err_e ret = BC_ERR_NOT_SUPPORT;
		
#if BC_PROJ_DEFS_IGMP
	bc_int32 mqrt;
    
	BC_IGMP_IPC_READ_P(buf, mqrt);

	ret = bc_local_set_igmp_mqrt(mqrt);

#endif
	BC_IPC_INIT_PACK(buf);
	return ret;
}

/******************************************************************************\
  Function   : bc_set_igmp_mqrt
  Description: 获取igmp最大响应查询时间默认值
  Return     : bc_err_e  成功，失败
  Others     : 
\******************************************************************************/
bc_err_e bc_set_igmp_mqrt_default_srv(bc_ipc_package_t *buf)
{
	bc_err_e ret = BC_ERR_NOT_SUPPORT;
		
#if BC_PROJ_DEFS_IGMP
	
	ret = bc_local_set_igmp_mqrt(BC_IGMP_MQRT_DEFAULT);
#endif
	BC_IPC_INIT_PACK(buf);
	return ret;
}

/******************************************************************************\
  Function   : bc_set_igmp_rbst_var
  Description: 获取igmp健壮性变量
  Return     : bc_err_e  成功，失败
  Others     : 
\******************************************************************************/
bc_err_e bc_set_igmp_rbst_var_srv(bc_ipc_package_t *buf)
{
	bc_err_e ret = BC_ERR_NOT_SUPPORT;
		
#if BC_PROJ_DEFS_IGMP
	bc_int32 robust_var;
    
	BC_IGMP_IPC_READ_P(buf, robust_var);
	
	ret = bc_local_set_igmp_rbst_var(robust_var);
#endif
	BC_IPC_INIT_PACK(buf);
	return ret;
}

/******************************************************************************\
  Function   : bc_set_igmp_rbst_var_default
  Description: 获取igmp健壮性变量默认值
  Return     : bc_err_e  成功，失败
  Others     : 
\******************************************************************************/
bc_err_e bc_set_igmp_rbst_var_default_srv(bc_ipc_package_t *buf)
{	
	bc_err_e ret = BC_ERR_NOT_SUPPORT;
		
#if BC_PROJ_DEFS_IGMP
	
	ret = bc_local_set_igmp_rbst_var(BC_IGMP_ROBUST_VAR_DEFAULT);
#endif
	BC_IPC_INIT_PACK(buf);
	return ret;
}

/******************************************************************************\
  Function   : bc_set_igmp_query_intrvl
  Description: 获取igmp发送查询报文的时间间隔
  Return     : bc_err_e  成功，失败
  Others     : 
\******************************************************************************/
bc_err_e bc_set_igmp_query_intrvl_srv(bc_ipc_package_t *buf)
{
	bc_err_e ret = BC_ERR_NOT_SUPPORT;
		
#if BC_PROJ_DEFS_IGMP
	bc_int32 query_interval;
    
	BC_IGMP_IPC_READ_P(buf, query_interval);
	
	ret = bc_local_set_igmp_query_intrvl(query_interval);

#endif
	BC_IPC_INIT_PACK(buf);
	return ret;
}

/******************************************************************************\
  Function   : bc_set_igmp_query_intrvl_default
  Description: 获取igmp发送查询报文的时间间隔默认值
  Return     : bc_err_e  成功，失败
  Others     : 
\******************************************************************************/
bc_err_e bc_set_igmp_query_intrvl_default_srv(bc_ipc_package_t *buf)
{
	bc_err_e ret = BC_ERR_NOT_SUPPORT;
		
#if BC_PROJ_DEFS_IGMP
	
	ret = bc_local_set_igmp_query_intrvl(BC_IGMP_QUERY_INTERVAL_DEFAULT);

#endif
	BC_IPC_INIT_PACK(buf);
	return ret;
}

/******************************************************************************\
  Function   : bc_set_igmp_lmqi_default
  Description: 获取igmp lmqi默认值
  Return     : bc_err_e  成功，失败
  Others     : 
\******************************************************************************/
bc_err_e bc_set_igmp_lmqi_default_srv(bc_ipc_package_t *buf)
{
	bc_err_e ret = BC_ERR_NOT_SUPPORT;
		
#if BC_PROJ_DEFS_IGMP
	
	ret = bc_local_set_igmp_lmqi(BC_IGMP_LMQI_DEFAULT);

#endif
	BC_IPC_INIT_PACK(buf);
	return ret;
}

/******************************************************************************\
  Function   : bc_set_igmp_lmqc
  Description: 获取igmp lmqc
  Return     : bc_err_e  成功，失败
  Others     : 
\******************************************************************************/
bc_err_e bc_set_igmp_lmqc_srv(bc_ipc_package_t *buf)
{
	bc_err_e ret = BC_ERR_NOT_SUPPORT;
		
#if BC_PROJ_DEFS_IGMP
	bc_int32 lmqc;
    
	BC_IGMP_IPC_READ_P(buf, lmqc);
	
	ret = bc_local_set_igmp_lmqc(lmqc);

#endif
	BC_IPC_INIT_PACK(buf);
	return ret;
}

/******************************************************************************\
  Function   : bc_set_igmp_lmqc_default
  Description: 获取igmp lmqc默认值
  Return     : bc_err_e  成功，失败
  Others     : 
\******************************************************************************/
bc_err_e bc_set_igmp_lmqc_default_srv(bc_ipc_package_t *buf)
{
	bc_err_e ret = BC_ERR_NOT_SUPPORT;
		
#if BC_PROJ_DEFS_IGMP
	
	ret = bc_local_set_igmp_lmqc(BC_IGMP_LMQC_DEFAULT);

#endif
	BC_IPC_INIT_PACK(buf);
	return ret;
}

/******************************************************************************\
  Function   : bc_set_igmp_version
  Description: 获取igmp版本
  Return     : bc_err_e  成功，失败
  Others     : 
\******************************************************************************/
bc_err_e bc_set_igmp_version_srv(bc_ipc_package_t *buf)
{
	bc_err_e ret = BC_ERR_NOT_SUPPORT;
		
#if BC_PROJ_DEFS_IGMP
	bc_igmp_ver_e ver;
    
	BC_IGMP_IPC_READ_P(buf, ver);
	
	ret = bc_local_set_igmp_version(ver);

#endif
	BC_IPC_INIT_PACK(buf);	
	return ret;
}

/******************************************************************************\
  Function   : bc_set_igmp_version_default
  Description: 获取igmp版本默认值
  Return     : bc_err_e  成功，失败
  Others     : 
\******************************************************************************/
bc_err_e bc_set_igmp_version_default_srv(bc_ipc_package_t *buf)
{
	bc_err_e ret = BC_ERR_NOT_SUPPORT;
		
#if BC_PROJ_DEFS_IGMP
	
	ret = bc_local_set_igmp_version(BC_IGMP_VER_DEFAULT);

#endif
	BC_IPC_INIT_PACK(buf);
	return ret;
} 

#endif
