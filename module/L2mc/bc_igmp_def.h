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

#ifndef __BC_IGMP_DEF_H__
#define __BC_IGMP_DEF_H__


#include "bc_common_defs.h"
#include "bc_port_def.h"
#include "bc_print.h"
//#include "drv_def.h"

#include "bc_ipc_client.h"
#include "bc_ipc_package.h"

#include "bc_ipc_def.h"
#include "bc_ipc_dev_client.h"


////////////////////////////////////////////////////////////////////////////////
//																			  //
//								igmp_cfg									  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
 
typedef enum
{
	BC_IGMP_MODE_CENTRALIZED = 1,
	BC_IGMP_MODE_DISTRIBUTEDWITHCM = 2,
	BC_IGMP_MODE_DISABLE = 3,
	BC_IGMP_MODE_DISTRIBUTEDWOCM = 4
} bc_igmp_mode_e;

typedef enum
{
	BC_IGMP_VER_V1 = 1,
	BC_IGMP_VER_V2 = 2,
	BC_IGMP_VER_V3 = 3,
} bc_igmp_ver_e;

//参数取值范围
#define BC_IGMP_MODE_DEFAULT	BC_IGMP_MODE_DISTRIBUTEDWOCM
#define BC_IGMP_MQRT_MIN		10
#define BC_IGMP_MQRT_MAX		0x3C00
#define BC_IGMP_MQRT_DEFAULT	10

#define BC_IGMP_ROBUST_VAR_MIN	2
#define BC_IGMP_ROBUST_VAR_MAX	7
#define BC_IGMP_ROBUST_VAR_DEFAULT	2

#define BC_IGMP_QUERY_INTERVAL_MIN 10
#define BC_IGMP_QUERY_INTERVAL_MAX 0x3C00
#define BC_IGMP_QUERY_INTERVAL_DEFAULT 125

#define BC_IGMP_LMQI_MIN 		10
#define BC_IGMP_LMQI_MAX		0x3C00
#define BC_IGMP_LMQI_DEFAULT	10

#define BC_IGMP_LMQC_MIN		2
#define BC_IGMP_LMQC_MAX		7
#define BC_IGMP_LMQC_DEFAULT	2

#define BC_IGMP_VER_DEFAULT		BC_IGMP_VER_V2

#define BC_IGMP_ONU_UNI_MAX_NUM              4

/*
* OLT:支持所有参数
*/
typedef struct
{
	bc_boolean				igmp_enable_flag;
	bc_igmp_mode_e			igmp_mode;
	bc_int32				mqrt;	/* max_query_resp_time; default:10*///10~0x3c00
	bc_int32				robust_var;//2~7
	bc_int32				query_interval;//10~0x3c00
	bc_int32				lmqi; 	/* last_mem_query_interval; */	//10~0x3c00
	bc_int32				lmqc; 	/* last_member_query_count; */	// 2~7
	bc_igmp_ver_e			ver;
} bc_igmp_cfg_t;

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								igmp_fwd									  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
#define BC_IGMP_OLT_FWD_CFG_MAX_COUNT	1024
#define BC_IGMP_ONU_FWD_CFG_NUMBER		64

typedef struct
{
	bc_uint16			vid;
	bc_ipv4				ip;
	bc_port_index_t	    port_list[BC_PORT_PON_MAX_COUNT + BC_PORT_SNI_MAX_COUNT];
} bc_igmp_fwd_t;


////////////////////////////////////////////////////////////////////////////////
//																			  //
//								igmp_mltcst									  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
#define BC_IGMP_ONU_MLTCST_MAX_COUNT		8
#define BC_IGMP_OLT_MLTCST_MAX_COUNT		BC_ONU_MAX_ONU_COUNTS * BC_IGMP_ONU_MLTCST_MAX_COUNT

#define BC_IGMP_OLT_MLTCST_VLAN_COUNT		256
////////////////////////////////////////////////////////////////////////////////
//																			  //
//					结 构 体 、联 合 体、枚 举 定 义						  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	bc_uint16			mltcst_vid;
	bc_port_index_t	    olt_port_lst[BC_PORT_PON_MAX_COUNT + BC_PORT_SNI_MAX_COUNT];
} bc_igmp_mltcst_xx_info_t;							// 默认为空

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								igmp_proxy									  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
#define BC_IGMP_OLT_PROXY_CFG_MAX_COUNT			256
#define BC_IGMP_OLT_PROXY_CFG_INVALID_INDEX		-1
#define BC_IGMP_PROXY_NAME_LEN						30

////////////////////////////////////////////////////////////////////////////////
//																			  //
//					结 构 体 、联 合 体、枚 举 定 义				  		  //
//																			  //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//																			  //
//					igmp_tagstrp									 		  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	bc_port_index_t	    port_id;
	bc_uint8			tag;
} bc_igmp_tagstrp_t;			// 默认不带tag

typedef struct
{
	bc_igmp_cfg_t			igmp_cfg;

	/*mltcst vlan*/
	bc_uint16 				mc_vid_start;
	bc_uint16 				mc_vid_cnt;
	bc_igmp_mltcst_xx_info_t igmp_mltcst_info[BC_IGMP_OLT_MLTCST_VLAN_COUNT];
} bc_igmp_xx_t;


#define BC_8022_CHIP_ONLINE(chip_id)        TRUE

#define BC_IGMP_ONU_UNUSED_INDEX  (bc_uint32)(-1)

#define BC_IGMP_PORT_TYPE_IS_SNI(pid)    (((pid).port_type == PORT_TYPE_OLT_GESNI || (pid).port_type == PORT_TYPE_OLT_XGSNI) ? TRUE : FALSE)
#define BC_IGMP_PORT_TYPE_IS_PON(pid)    (((pid).port_type == PORT_TYPE_OLT_GEEPON || (pid).port_type == PORT_TYPE_OLT_XGEPON) ? TRUE : FALSE)
                                                                                                                                                                                                                                                                                               

#define BC_IGMP_IPC_DATA_READ(src, dst, size)   BC_IPC_PACK_READ((src), (dst), (size))
#define BC_IGMP_IPC_READ_P(src, dst)            BC_IPC_PACK_READ((src), &(dst), (sizeof(dst)))

#define BC_IGMP_IPC_WRITE(dst, src, size)       BC_IPC_PACK_WRITE((dst), (src), (size))
#define BC_IGMP_IPC_WRITE_P(dst, src)           BC_IPC_PACK_WRITE((dst), &(src), (sizeof(src)))

#define BC_IGMP_IPC_RET(buf, value)             BC_IPC_PACK_READ_FUN_RET((buf), (value))
#define BC_IGMP_IPC_RET_READ(buf, value)        BC_IPC_PACK_READ_FUN_RET((buf), &(value))

//#define BC_IGMP_IPC_REQUEST(fun_id, buf)        kt_ipc_xx_client_request((fun_id), (bc_ipc_package_t *)(buf))


#define bc_igmp_malloc(size)                    bc_platform_mem_malloc(BC_MODULE_IGMP, size)
#define bc_igmp_free(buf)                       bc_platform_mem_free(BC_MODULE_IGMP, buf)


#define BC_IGMP_IPC_FREE(buf)                                                                       \
    BC_IPC_PPACK_FREE_RETPROC(buf);                                                                 \
    BC_PT_FUN_LEAVE(BC_MODULE_IGMP);                                                                \


#define BC_IGMP_IPC_REQUEST(fun_id, buf, tbuf)                                                      \
    (tbuf) = (buf);                                                                                 \
    if (BC_ERR_OK != (ret = bc_ipc_dev_client_request((fun_id), (bc_ipc_package_t *)(tbuf))))     \
    {                                                                                               \
        BC_IGMP_IPC_FREE(buf);                                                                      \
        return ret;                                                                                 \
    }



#if 0
    #define bc_igmp_dbg(fmt, args...) 	do {printf("[%s, %d] - " fmt, __FILE__, __LINE__, ##args);}while(0)
#else
    #define bc_igmp_dbg(fmt, args...)   do {BC_PT_DBG_SMP(BC_MODULE_IGMP, fmt, ##args);}while(0)
#endif

 
#endif /* __KTAPI_IGMP_DEF_H__ */

