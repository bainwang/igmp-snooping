
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
//								头   文   件								  //
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
//						外 部 变 量、 函 数 引 用							  //
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
//								函  数  声  明								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								函  数  定  义								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
/******************************************************************************\
  Function   : bc_query_igmp_fwd
  Description: 查询igmp转发表
  Return     : bc_err_e  成功，失败
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
