/*
	此统计模块于2017年工作于武汉烽火完成，运行于PTN产品中。
*/

#ifndef __BC_STATS_DEF_H__
#define __BC_STATS_DEF_H__

#include <time.h>

#include "bc_common_defs.h"


#if 1
/*修改各统计模块的最大值*/
#define BC_STATS_MAX_OAM_PORT_COUNT			1
#define BC_STATS_MAX_OPTICAL_COUNT			4
#define BC_STATS_MAX_PORT_COUNT				3
#define BC_STATS_MAX_PTP_PORT_COUNT			3
#define BC_STATS_MAX_PTP_COUNT				1
#define BC_STATS_MAX_VP_COUNT					4
#define BC_STATS_MAX_VC_COUNT					4
#define BC_STATS_MAX_E1_COUNT					2

#define BC_STATS_PORT_SFP_START_ID			3


#define BC_STATS_15MIN_SEC_COUNT					(60*15)
#define BC_STATS_24HOUR_SEC_COUNT				(60*60*24)
#define BC_STATS_15MIN_N_OF_1HOUR				(3600/BC_STATS_15MIN_SEC_COUNT)
#define BC_STATS_24HOUR_N_OF_1DAY				(24/24)

#define BC_STATS_RECODE_INTERVAL_INDEX				2	/*有效的起始ID*/
//-------------------------------------------------------

/*修改15分钟统计的小时数，请修改这里*/
#define BC_STATS_15MIN_HOURS_COUNT			24

/*修改24小时统计的天数，请修改这里*/
#define BC_STATS_24HOUR_DAY_COUNT			30	
//-------------------------------------------------------


#define BC_STATS_MIN_RECORD_COUNT			1
#define BC_STATS_MAX_15MIN_RECORD_COUNT		(BC_STATS_15MIN_N_OF_1HOUR*BC_STATS_15MIN_HOURS_COUNT)	/*24小时内15分钟条目数*/
#define BC_STATS_MAX_24HOUR_RECORD_COUNT	(BC_STATS_24HOUR_N_OF_1DAY*BC_STATS_24HOUR_DAY_COUNT)	/*30天内15分钟条目数*/

#define BC_STATS_UN_USED_INDEX				-1

#endif



/*
	--------------------------------------------------------------------------------
	stats info 
*/
#if 1

//---------------------------------
/*oam port*/
typedef struct{
	bc_uint16 port_num;
	bc_uint32 tx_packs;
	bc_uint32 rx_packs;
}oam_port_info_t;

typedef struct{
	oam_port_info_t info[BC_STATS_MAX_OAM_PORT_COUNT];
	int num;
}bc_stats_oam_port_info_t;

//---------------------------------
/*optical*/
typedef struct{
	bc_uint8    opticalPortId;
	float iop;  /**< 采样的光接收功率  */
	float oop;  /**< 采样的光发送功率  */
}optical_info_t;

typedef struct{
	optical_info_t info[BC_STATS_MAX_OPTICAL_COUNT];
	int num;
}bc_stats_optical_info_t;

//---------------------------------
/*port*/
typedef struct{
	bc_uint16 port_num;
	bc_uint32 rx_bdpk;             /**< 接收坏包数 */
	bc_uint32 tx_bdpk;		     /**< 发送坏包数 */
	bc_uint32 rx_packs_64;         /**< 收到的包(64字节) */
	bc_uint32 rx_packs_65_to_127;  /**< 收到的包(65-127字节)  */
	bc_uint32 rx_packs_128_to_255; /**< 收到的包(128-255字节) */
	bc_uint32 rx_packs_256_to_511; /**< 收到的包(256-511字节)  */
	bc_uint32 rx_packs_512_to_1023;/**< 收到的包(512-1023字节)  */
	bc_uint32 rx_packs_1024_to_1518;/**< 收到的包(1024-1518字节) */
	bc_uint32 rx_packs_1519_to_max;/**< 收到的包(1519-MAX字节)*/
	bc_uint32 tx_packs_64;         /**< 发送的包(64字节)  */
	bc_uint32 tx_packs_65_to_127;  /**< 发送的包(65-127字节)  */
	bc_uint32 tx_packs_128_to_255; /**< 发送的包(128-255字节)  */
	bc_uint32 tx_packs_256_to_511; /**<  发送的包(256-511字节) */
	bc_uint32 tx_packs_512_to_1023;/**<  发送的包(512-1023字节)*/
	bc_uint32 tx_packs_1024_to_1518;/**< 发送的包(1024-1518字节)  */
	bc_uint32 tx_packs_1519_to_max; /**< 发送的包(1519-MAX字节)*/
	bc_uint32 crc_err;   /**< CRC校验错 */
	bc_uint32 stat_usz;  /**< 短包数统计  */
	bc_uint32 stat_osz;  /**< 长包数统计  */
	bc_uint32 fragment;  /**<	碎片包数    */
	bc_uint32 jabber;    /**< Jabbers包统计 */
	bc_uint32 alignment;/**< ALIGMENT包统计  */
	bc_uint32 rx_bcast;/**<   */
	bc_uint32 rx_mcast;/**<   */
	bc_uint32 rx_packs;/**<   */
	bc_uint32 rx_pause;/**<   */
	bc_uint32 rx_drop; /**<   */
	bc_uint32 tx_bcast;/**<   */
	bc_uint32 tx_mcast;/**<   */
	bc_uint32 tx_packs;/**<   */
	bc_uint32 tx_pause;/**<   */
	bc_uint32 tx_flow; /**<   */
	bc_uint32 rx_flow; /**<   */
	bc_uint64 rx_bytes;/**<   */
	bc_uint64 tx_bytes;/**<   */
	bc_uint32 vs_rx_cv;/**< MPLS-TP虚段接收CV包统计  */
	bc_uint32 vs_tx_cv;/**< MPLS-TP虚段发送CV包统计  */
	bc_uint32 single_packlosr_near;   /**<   */
	bc_uint32 single_packlosr_far;	/**<   */
	bc_uint32 double_packlosr_near;   /**<   */
	bc_uint32 double_packlosr_far;    /**<   */
	bc_uint32 packdelay_s;            /**<  时延秒 */
	bc_uint32 packdelay_ns;           /**<  时延纳秒 */
	bc_uint32 packdelayvar_s;         /**<  时延变化秒 */
	bc_uint32 packdelayvar_ns;        /**<  时延变化纳秒 */
	/*from optical_info_t to port_info_t, 端口1-2非光口，无光功率数据，3-6才有数据*/
	bc_uint8    opticalPortId;	//无效值
	float iop;  /**< 采样的光接收功率  */
	float oop;  /**< 采样的光发送功率  */
}port_info_t;

typedef struct{
	port_info_t info[BC_STATS_MAX_PORT_COUNT];
	int num;
}bc_stats_port_info_t;

//---------------------------------
/*ptp port*/
typedef struct{
	bc_uint16 ptp_port_num;
	bc_uint32 pdelay_req_tx;
	bc_uint32 pdelay_req_rx;
	bc_uint32 pdelay_req_rx_err;
	bc_uint32 pdelay_resp_tx;
	bc_uint32 pdelay_resp_rx;
	bc_uint32 pdelay_resp_rx_err;
	bc_uint32 pdelay_resp_follow_up_tx;
	bc_uint32 pdelay_resp_follow_up_rx;
	bc_uint32 pdelay_resp_follow_up_rx_err;
	bc_uint32 sync_tx;
	bc_uint32 sync_rx;
	bc_uint32 sync_rx_err;
	bc_uint32 follow_up_tx;
	bc_uint32 follow_up_rx;
	bc_uint32 follow_up_rx_err;
	bc_uint32 delay_req_tx;
	bc_uint32 delay_req_rx;
	bc_uint32 delay_req_rx_err;
	bc_uint32 delay_resp_tx;
	bc_uint32 delay_resp_rx;
	bc_uint32 delay_resp_rx_err;
	bc_uint32 announce_tx;
	bc_uint32 announce_rx;
	bc_uint32 announce_rx_err;
}ptp_port_info_t;

typedef struct{
	ptp_port_info_t info[BC_STATS_MAX_PTP_PORT_COUNT];
	int num;
}bc_stats_ptp_port_info_t;

//---------------------------------
/*ptp*/
typedef struct{
	bc_uint32 ptp_offset_value;
	bc_uint32 ptp_offset_max;
	bc_uint32 ptp_offset_min;
	bc_uint32 ptp_offset_mean;
	bc_uint32 ptp_mts_path_delay_value;
	bc_uint32 ptp_mts_path_delay_max;
	bc_uint32 ptp_mts_path_delay_min;
	bc_uint32 ptp_mts_path_delay_mean;
	bc_uint32 ptp_stm_path_delay_value;
	bc_uint32 ptp_stm_path_delay_max;
	bc_uint32 ptp_stm_path_delay_min;
	bc_uint32 ptp_stm_path_delay_mean;
	bc_uint32 ptp_mean_path_delay_value;
	bc_uint32 ptp_mean_path_delay_max;
	bc_uint32 ptp_mean_path_delay_min;
	bc_uint32 ptp_mean_path_delay_mean;
	bc_uint32 ptp_total_offset_value;
	bc_uint32 ptp_total_offset_ptop;
	bc_uint32 ptp_total_offset_mean;
	bc_uint32 ptp_total_offset_end;
	bc_uint32 ptp_passive_offset_value;
	bc_uint32 ptp_passive_offset_max;
	bc_uint32 ptp_passive_offset_min;
	bc_uint32 ptp_passive_offset_mean;
	bc_uint32 outside_ptp_offset_value;
	bc_uint32 outside_ptp_offset_max;
	bc_uint32 outside_ptp_offset_min;
	bc_uint32 outside_ptp_offset_mean;
}ptp_info_t;

typedef struct{
	ptp_info_t info;
	int num;	/*fix is 1*/
}bc_stats_ptp_info_t;

//---------------------------------
/*vp*/
typedef struct{
	bc_uint16 vp_num;
	bc_uint32 rx_packs;
	bc_uint32 tx_packs;
	bc_uint64 tx_bytes;
	bc_uint64 rx_bytes;
	bc_uint32 vp_rx_cv;         /**< MPLS-TP虚通路接收CV包统计 */
	bc_uint32 vp_tx_cv;         /**< MPLS-TP虚通路发送CV包统计 */
	bc_uint32 packlosr_near;
	bc_uint32 packlosr_far;
	bc_uint32 packdelay_s;
	bc_uint32 packdelay_ns;
	bc_uint32 packdelayvar_s;
	bc_uint32 packdelayvar_ns;
	bc_uint32 bfd_rx_packs;    /**< BFD接收总包数 */
	bc_uint32 bfd_tx_packs;    /**< BFD发送总包数 */
}vp_info_t;

typedef struct{
	vp_info_t info[BC_STATS_MAX_VP_COUNT];
	int num;
}bc_stats_vp_info_t;

//---------------------------------
/*vc*/
typedef struct{
	bc_uint16 vc_num;
	bc_uint32 rx_packs;
	bc_uint32 tx_packs;
	bc_uint64 tx_bytes;
	bc_uint64 rx_bytes;
	bc_uint32 vc_rx_cv;         /**<  MPLS-TP虚通道接收CV包统计 */
	bc_uint32 vc_tx_cv;         /**<  MPLS-TP虚通道发送CV包统计 */
	bc_uint32 packlosr_near;    /**<  近端丢包率%,采样值/10000 ,实数方式显示 */
	bc_uint32 packlosr_far;     /**<  远端丢包率%,采样值/10000 ,实数方式显示 */
	bc_uint32 packdelay_s;      /**<  时延秒 */
	bc_uint32 packdelay_ns;     /**<  时延纳秒 */
	bc_uint32 packdelayvar_s;   /**<  时延变化秒 */
	bc_uint32 packdelayvar_ns;  /**<  时延变化纳秒 */
}vc_info_t;

typedef struct{
	vc_info_t info[BC_STATS_MAX_VC_COUNT];
	int num;
}bc_stats_vc_info_t;

//---------------------------------
/*e1*/
typedef struct{
	bc_uint16 e1_num;
	bc_uint32 context_rx_pkts;	    /**< 链路接收的包数 */
	bc_uint32 context_tx_pkts;	    /**< 链路发送的包数 */
	bc_uint32 context_early_pkts;		/**< 链路收到早到的包数 */
	bc_uint32 context_late_pkts;	    /**< 链路收到晚到的包数 */
	bc_uint32 context_loss_pkts;		/**< 链路收丢包数 */
	bc_uint32 context_underrun_pkts;	/**< 链路下插空包数 */
	bc_uint32 es;						/**< 误码秒 */
	bc_uint32 ses;					/**< 严重误码秒 */
	bc_uint32 bbe;					/**< 背景误码块 */
	bc_uint32 uas;					/**< 不可用秒 */
	bc_uint32 e1_hdb3_err;		    /**< HDB3误码计数 */
	bc_uint32 e1_crc_err;				/**< TDM CRC误码计数 */
}e1_info_t;

typedef struct{
	e1_info_t info[BC_STATS_MAX_E1_COUNT];
	int num;
}bc_stats_e1_info_t;

//---------------------------------

/*stats info*/
typedef struct{
	bc_uint16 temperature;
	bc_stats_oam_port_info_t oam_port_info;
	bc_stats_optical_info_t optical_info;
	bc_stats_port_info_t port_info;
	bc_stats_ptp_port_info_t ptp_port_info;
	bc_stats_ptp_info_t ptp_info;
	bc_stats_vp_info_t vp_info;
	bc_stats_vc_info_t vc_info;
	bc_stats_e1_info_t e1_info;
}bc_stats_info_t;

#if 1
typedef enum{
	BC_STATS_OP_TEMP,
	BC_STATS_OP_OAM_PORT,
	BC_STATS_OP_OPTICAL,
	BC_STATS_OP_PORT,
	BC_STATS_OP_PTP_PORT,
	BC_STATS_OP_PTP,
	BC_STATS_OP_VP,
	BC_STATS_OP_VC,
	BC_STATS_OP_E1,
	BC_STATS_OP_MAX
}bc_stats_op_type;

typedef enum{
	BC_STATS_OP_CUR_LIST,
	BC_STATS_OP_15MIN_LIST,
	BC_STATS_OP_24HOUR_LIST,
	BC_STATS_OP_15MIN_INC_LIST,
	BC_STATS_OP_24HOUR_INC_LIST,
	BC_STATS_OP_LIST_MAX
}bc_stats_op_list_type;

typedef enum{
	BC_STATS_OP_15MIN_NUM,
	BC_STATS_OP_15MIN_TOTAL_NUM,
	BC_STATS_OP_24HOUR_NUM,
	BC_STATS_OP_24HOUR_TOTAL_NUM,
	BC_STATS_OP_NUM_MAX
}bc_stats_op_num_type;
#endif

/*cur stats info*/
typedef struct{
	bc_stats_info_t stats_info;
	struct tm start_time;
	struct tm last_time;
}bc_stats_cur_info_t;

/*hstry stats info*/
typedef struct{
	bc_uint8 index;
	bc_stats_info_t stats_info;
	bc_uint8 is_valid;
	struct tm start_time;
	struct tm end_time;
}bc_stats_hstry_info_t;

/*15minute stats info*/
typedef struct{
	bc_stats_hstry_info_t	stats_15min[BC_STATS_MAX_15MIN_RECORD_COUNT + 1];
	int				stats_15min_count;
}bc_stats_15minutes_info_t;

/*24hour stats info*/
typedef struct{
	bc_stats_hstry_info_t	stats_24hour[BC_STATS_MAX_24HOUR_RECORD_COUNT + 1];
	int				stats_24hour_count;	
}bc_stats_24hour_info_t;

/*stats configuration info*/
typedef struct
{
	bc_uint16		cfg_15min_max_rcrd;
	bc_uint16		cfg_24hour_max_rcrd;
} bc_stats_cfg_t;

typedef struct{
	bc_stats_cur_info_t	cur_stats;
	bc_stats_15minutes_info_t	stats_of_15min;
	bc_stats_24hour_info_t	stats_of_24hour;
	bc_stats_cfg_t	stats_cfg;
}bc_stats_info;

typedef struct{
	int total_cnt;
	int ok_cnt;
	int err_cnt;
	bc_boolean status;
}bc_stats_db_update_count_t;

#endif


/*
	--------------------------------------------------------------------------------
	threshold info 
*/
#if 1


/*清除告警的模式*/
typedef enum{
	BC_STATS_ALRM_CLR_MOD_1S = 1,
	BC_STATS_ALRM_CLR_MOD_15MIN = 2,
	BC_STATS_ALRM_CLR_MOD_MAX
}bc_stats_alrm_clr_mod_e;

typedef enum{
	BC_STATS_THRESHOLD_INFO_VAL = 0,	/*门限值*/
	BC_STATS_THRESHOLD_INFO_MOD,	/*清除告警的模式，1:1秒2:15分钟*/
	BC_STATS_THRESHOLD_INFO_EN,		/*告警始能，1开2关*/
	BC_STATS_THRESHOLD_INFO_MAX		
}bc_stats_set_threshold_info_type_e;

/*
typedef struct{
	bc_stats_set_threshold_info_type_e type;	
	bc_uint32 val;
}bc_stats_set_threshold_info_t;
*/
#if 1

//门限取值范围
#if 1
#define BC_STATS_THRESHOLD_HI_TEMP_MAX	80
#define BC_STATS_THRESHOLD_HI_TEMP_MIN	50

#define BC_STATS_THRESHOLD_LO_TEMP_MAX	15
#define BC_STATS_THRESHOLD_LO_TEMP_MIN	0

#define BC_STATS_THRESHOLD_OTHER_MAX	65535
#define BC_STATS_THRESHOLD_OTHER_MIN	0
#endif

typedef enum{
	BC_STATS_THRESHOLD_TYPE_TEMP_UPPER = 0,
	BC_STATS_THRESHOLD_TYPE_TEMP_LOWER,
	BC_STATS_THRESHOLD_TYPE_PORT_CRC_ERR,
	BC_STATS_THRESHOLD_TYPE_E1_CRC_ERR,
	BC_STATS_THRESHOLD_TYPE_DROP_PKT,
	BC_STATS_THRESHOLD_TYPE_RX_BAD_PKT,
	BC_STATS_THRESHOLD_TYPE_ALIGN,
	BC_STATS_THRESHOLD_TYPE_VP_SD,
	BC_STATS_THRESHOLD_TYPE_VP_SF,
	BC_STATS_THRESHOLD_TYPE_VC_SD,
	BC_STATS_THRESHOLD_TYPE_VC_SF,
	BC_STATS_THRESHOLD_TYPE_VS_SD,
	BC_STATS_THRESHOLD_TYPE_VS_SF,
	BC_STATS_THRESHOLD_TYPE_MAX
}bc_stats_threshold_type_e;

typedef struct {
	int val;
	int en;
	char name[32];
	bc_stats_alrm_clr_mod_e mod;
}per_threshold_info_t;

typedef struct{
	per_threshold_info_t temp_upper;
	per_threshold_info_t temp_lower;
	per_threshold_info_t port_crc_err;
	per_threshold_info_t e1_crc_err;
	per_threshold_info_t drop_pkt;
	per_threshold_info_t rx_bad_pkt;
	per_threshold_info_t align;
	per_threshold_info_t vp_sd;
	per_threshold_info_t vp_sf;
	per_threshold_info_t vc_sd;
	per_threshold_info_t vc_sf;
	per_threshold_info_t vs_sd;
	per_threshold_info_t vs_sf;
}bc_stats_threshold_info_t;

#define BC_STATS_THRESHOLD_INFO_NUM	(sizeof(bc_stats_threshold_info_t)/sizeof(per_threshold_info_t))

#endif


#endif


/*err code*/
typedef enum{
	BC_STATS_ERR_OK = 0,
	BC_STATS_ERR_PARAM,
	BC_STATS_ERR_IPC,
	BC_STATS_ERR_GET,
	BC_STATS_ERR_SET,
	BC_STATS_ERR_NO_EXIST,
	BC_STATS_ERR_GET_TEMPERATURE = 0x100,
	BC_STATS_ERR_GET_OAM_PORT,
	BC_STATS_ERR_GET_OPTCAL,
	BC_STATS_ERR_GET_PORT,
	BC_STATS_ERR_GET_PTP_PORT,
	BC_STATS_ERR_GET_PTP,
	BC_STATS_ERR_GET_VP,
	BC_STATS_ERR_GET_VC,
	BC_STATS_ERR_GET_E1,
	BC_STATS_ERR_GET_ALARM = 0x200,
	BC_STATS_ERR_UNKOWN
}bc_stats_err_e;


#endif 	/*__BC_STATS_DEF_H__*/
