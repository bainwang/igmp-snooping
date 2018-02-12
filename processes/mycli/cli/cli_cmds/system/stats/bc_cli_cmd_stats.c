/*******************************************************************************
  -------------------------------------------------------------------------
  [Author]     : bain.wang@outlook.com
  [Version]    : 1.0
  [Date]       : 2017-07-06
  [Description]:

  [Others]     :

  [Function List]:  
    1. ....
    2. ....
  [History]:
	 D a t e    Modification 										  Initials
	---------- --------------                                        ----------
	2017-07-06  Created									bain.wang@outlook.com
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								头   文   件								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>  
#include <unistd.h>  
#include <errno.h>  
#include <string.h>


#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "bc_modules.h"
#include "bc_msg.h"

#include "bc_cli_type.h"
#include "bc_cli_paratype.h"

#include "bc_cli.h"
#include "bc_stats_def.h"
#include "bc_stats.h"

#include "utili_bit.h"
static unsigned int 	l_mdl_id = BC_MODULE_STATS;

////////////////////////////////////////////////////////////////////////////////
//																			  //
//						外 部 变 量、 函 数 引 用					          //
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


#define PRT_CLI_PARA(l_mdl_id, cli_para) \
	do\
	{\
		cli_value_t *cli_para_tmp = cli_para;\
		UI32_T para_num = 1;\
		for (; NULL != cli_para_tmp; cli_para_tmp = cli_para_tmp->next, para_num++)\
		{\
			BC_PT_DBG_CPL\
			(\
				l_mdl_id,\
				"Cli Para No.%03u: Address=0x%08X type=%d, name=%s, priority=%d, next=0x%08X\r\n",\
				para_num, (int)cli_para_tmp,\
				cli_para_tmp->type, cli_para_tmp->name, cli_para_tmp->priority, (int)cli_para_tmp->next\
			);\
		}\
	} while (0)

#define CHECK_BCAPI_RET(ret_api)\
	do\
	{\
		if (ret_api != BC_ERR_OK)\
		{\
			bc_msg_err_get(ret_api, (bc_cli_get_lan() == CLI_LAN_CN ? BC_LAN_CHINESE_E : BC_LAN_ENGLISH_E));\
			return;\
		}\
	} while (0)


#if 1
typedef enum{
	CLI_STATS_OP_TEMP,
	CLI_STATS_OP_OAM_PORT,
	CLI_STATS_OP_OPTICAL,
	CLI_STATS_OP_PORT,
	CLI_STATS_OP_PTP_PORT,
	CLI_STATS_OP_PTP,
	CLI_STATS_OP_VP,
	CLI_STATS_OP_VC,
	CLI_STATS_OP_E1,
	CLI_STATS_OP_MAX
}cli_stats_op_type;

typedef enum{
	CLI_STATS_OP_15MIN_NUM,
	CLI_STATS_OP_15MIN_TOTAL_NUM,
	CLI_STATS_OP_24HOUR_NUM,
	CLI_STATS_OP_24HOUR_TOTAL_NUM,
	CLI_STATS_OP_NUM_MAX
}cli_stats_op_num_type;
#endif


////////////////////////////////////////////////////////////////////////////////
//																			  //
//							全 局 变 量 定 义							      //
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
//								函  数  声  明							      //
//																			  //
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//																			  //
//								函  数  定  义							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////


/******************************************************************************\
  Function   : __stats_show
  Description:显示统计信息
  Return     : bool true: 成功  false:非零失败
  Others     : 
\******************************************************************************/
static cli_cmd_ret_e __stats_show_info_num(const UI32_T sid, cli_stats_op_num_type type, int num)
{
	switch(type)
	{
		case CLI_STATS_OP_15MIN_NUM:
			CLI_API_Printf(sid, " 15minute stats item num of current: %d\r\n", num);
			break;
		case CLI_STATS_OP_15MIN_TOTAL_NUM:
			CLI_API_Printf(sid, " 15minute stats item num of total: %d\r\n", num);
			break;
		case CLI_STATS_OP_24HOUR_NUM:
			CLI_API_Printf(sid, " 24hour stats item num of current: %d\r\n", num);
			break;
		case CLI_STATS_OP_24HOUR_TOTAL_NUM:
			CLI_API_Printf(sid, " 24hour stats item num of total: %d\r\n", num);
			break;
		default:
			return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

static cli_cmd_ret_e __stats_show_info_mdl(const UI32_T sid, cli_stats_op_type type, bc_stats_info_t stats_info)
{
	int i = 0;
	double f1 = 0;
	double f2 = 0;
	
	switch(type)
	{
		case BC_STATS_OP_TEMP:
			CLI_API_Printf(sid, "Board temperature : %2.1f\r\n",((float)stats_info.temperature) / 10);
			break;
		case BC_STATS_OP_OAM_PORT:
			for(i = 0; i<stats_info.oam_port_info.num; i++)
			{
				CLI_API_Printf(sid, "--------------- OAM Port [%d] information --------------\r\n", stats_info.oam_port_info.info[i].port_num);
				CLI_API_Printf(sid, "  %20s %20d %20s %20d\r\n", "tx_packs:", stats_info.oam_port_info.info[i].tx_packs,"rx_packs:", stats_info.oam_port_info.info[i].rx_packs);
			}
			break;
		case BC_STATS_OP_PORT:
			for(i = 0; i<stats_info.port_info.num; i++)
			{
				CLI_API_Printf(sid, "---------------- port [%d] Stastics information --------------\r\n",stats_info.port_info.info[i].port_num);
				CLI_API_Printf(sid, "  %20s %20s %20s\r\n", "item", "send", "recev");
				CLI_API_Printf(sid, "  %20s %20d %20d\r\n", "bdpk:",stats_info.port_info.info[i].tx_bdpk,stats_info.port_info.info[i].rx_bdpk);
				CLI_API_Printf(sid, "  %20s %20d %20d\r\n", "packs_65_to_127:",stats_info.port_info.info[i].tx_packs_65_to_127,stats_info.port_info.info[i].rx_packs_65_to_127);
				CLI_API_Printf(sid, "  %20s %20d %20d\r\n", "packs_64:",stats_info.port_info.info[i].tx_packs_64,stats_info.port_info.info[i].rx_packs_64);
				CLI_API_Printf(sid, "  %20s %20d %20d\r\n","packs_128_to_255:", stats_info.port_info.info[i].tx_packs_128_to_255,stats_info.port_info.info[i].rx_packs_128_to_255);
				CLI_API_Printf(sid, "  %20s %20d %20d\r\n", "packs_256_to_511:",stats_info.port_info.info[i].tx_packs_256_to_511, stats_info.port_info.info[i].rx_packs_256_to_511);
				CLI_API_Printf(sid, "  %20s %20d %20d\r\n","packs_512_to_1023:", stats_info.port_info.info[i].tx_packs_512_to_1023, stats_info.port_info.info[i].rx_packs_512_to_1023);
				CLI_API_Printf(sid, "  %20s %20d %20d\r\n","packs_1024_to_1518:", stats_info.port_info.info[i].tx_packs_1024_to_1518, stats_info.port_info.info[i].rx_packs_1024_to_1518);
				CLI_API_Printf(sid, "  %20s %20d %20d\r\n","packs_1519_to_max:", stats_info.port_info.info[i].tx_packs_1519_to_max, stats_info.port_info.info[i].rx_packs_1519_to_max);

				CLI_API_Printf(sid, "  %20s %20d %20d\r\n", "bcast:", stats_info.port_info.info[i].tx_bcast,stats_info.port_info.info[i].rx_bcast);
				CLI_API_Printf(sid, "  %20s %20d %20d\r\n", "mcast:", stats_info.port_info.info[i].tx_mcast,stats_info.port_info.info[i].rx_mcast);
				CLI_API_Printf(sid, "  %20s %20d %20d\r\n", "packs:", stats_info.port_info.info[i].tx_packs,stats_info.port_info.info[i].rx_packs);
				CLI_API_Printf(sid, "  %20s %20d %20d\r\n", "pause:", stats_info.port_info.info[i].tx_pause,stats_info.port_info.info[i].rx_pause);
				CLI_API_Printf(sid, "  %20s %20d %20d\r\n", "flow:", stats_info.port_info.info[i].tx_flow,stats_info.port_info.info[i].rx_flow);
				CLI_API_Printf(sid, "  %20s %20lld %20lld\r\n", "bytes:", stats_info.port_info.info[i].tx_bytes, stats_info.port_info.info[i].rx_bytes);

				CLI_API_Printf(sid, "  %20s %20d\r\n", "rx_drop:", stats_info.port_info.info[i].rx_drop);
				CLI_API_Printf(sid, "  %20s %20d\r\n", "crc_err:", stats_info.port_info.info[i].crc_err);
				CLI_API_Printf(sid, "  %20s %20d\r\n", "stat_usz:", stats_info.port_info.info[i].stat_usz);
				CLI_API_Printf(sid, "  %20s %20d\r\n", "stat_osz:", stats_info.port_info.info[i].stat_osz);
				CLI_API_Printf(sid, "  %20s %20d\r\n", "fragment:", stats_info.port_info.info[i].fragment);
				CLI_API_Printf(sid, "  %20s %20d\r\n", "jabber:", stats_info.port_info.info[i].jabber);
				CLI_API_Printf(sid, "  %20s %20d\r\n", "alignment:", stats_info.port_info.info[i].alignment);
				CLI_API_Printf(sid, "  %20s %20d\r\n", "single_packlosr_near", stats_info.port_info.info[i].single_packlosr_near);
				CLI_API_Printf(sid, "  %20s %20d\r\n", "single_packlosr_far", stats_info.port_info.info[i].single_packlosr_far);	
				CLI_API_Printf(sid, "  %20s %20d\r\n", "double_packlosr_near", stats_info.port_info.info[i].double_packlosr_near);
				CLI_API_Printf(sid, "  %20s %20d\r\n", "double_packlosr_far", stats_info.port_info.info[i].double_packlosr_far);
				CLI_API_Printf(sid, "  %20s %20d\r\n", "packdelay_s:", stats_info.port_info.info[i].packdelay_s);
				CLI_API_Printf(sid, "  %20s %20d\r\n", "packdelay_ns:", stats_info.port_info.info[i].packdelay_ns);
				CLI_API_Printf(sid, "  %20s %20d\r\n", "packdelayvar_s:", stats_info.port_info.info[i].packdelayvar_s);
				CLI_API_Printf(sid, "  %20s %20d\r\n", "packdelayvar_ns:", stats_info.port_info.info[i].packdelayvar_ns);
				if(stats_info.port_info.info[i].port_num >= BC_STATS_PORT_SFP_START_ID)
				{
					CLI_API_Printf(sid, "  %20s %20.2f\r\n", "iop:", stats_info.port_info.info[i].iop);
					CLI_API_Printf(sid, "  %20s %20.2f\r\n", "oop:", stats_info.port_info.info[i].oop);
				}
				//CLI_API_Printf(sid, "  vs_rx_cv: %d\r\n", stats_info.port_info.info[i].vs_rx_cv);
				//CLI_API_Printf(sid, "  vs_tx_cv: %d\r\n", stats_info.port_info.info[i].vs_tx_cv);
			}
			break;
		case BC_STATS_OP_PTP_PORT:
			for(i = 0; i<stats_info.ptp_port_info.num; i++)
			{
				CLI_API_Printf(sid, "---------------------- PTP port [%d] information ------------------\r\n",stats_info.ptp_port_info.info[i].ptp_port_num);
				CLI_API_Printf(sid, "  %21s %15s %15s %15s\r\n", "item","send","recev","error");
				CLI_API_Printf(sid, " %21s %15d %15d %15d\r\n", "pdelay_req",stats_info.ptp_port_info.info[i].pdelay_req_tx,stats_info.ptp_port_info.info[i].pdelay_req_rx,stats_info.ptp_port_info.info[i].pdelay_req_rx_err);
				CLI_API_Printf(sid, " %21s %15d %15d %15d\r\n", "pdelay_resp",stats_info.ptp_port_info.info[i].pdelay_resp_tx,stats_info.ptp_port_info.info[i].pdelay_resp_rx,stats_info.ptp_port_info.info[i].pdelay_resp_rx_err);
				CLI_API_Printf(sid, " %21s %15d %15d %15d\r\n",  "pdelay_reap_follow_up",stats_info.ptp_port_info.info[i].pdelay_resp_follow_up_tx, stats_info.ptp_port_info.info[i].pdelay_resp_follow_up_rx, stats_info.ptp_port_info.info[i].pdelay_resp_follow_up_rx_err);
				CLI_API_Printf(sid, " %21s %15d %15d %15d\r\n",  "sync",stats_info.ptp_port_info.info[i].sync_tx, stats_info.ptp_port_info.info[i].sync_rx, stats_info.ptp_port_info.info[i].sync_rx_err);
				CLI_API_Printf(sid, " %21s %15d %15d %15d\r\n",  "follow_up", stats_info.ptp_port_info.info[i].follow_up_tx, stats_info.ptp_port_info.info[i].follow_up_rx, stats_info.ptp_port_info.info[i].follow_up_rx_err);
				CLI_API_Printf(sid, " %21s %15d %15d %15d\r\n",  "delay_req",stats_info.ptp_port_info.info[i].delay_req_tx, stats_info.ptp_port_info.info[i].delay_req_rx, stats_info.ptp_port_info.info[i].delay_req_rx_err);
				CLI_API_Printf(sid, " %21s %15d %15d %15d\r\n",  "delay_resp",stats_info.ptp_port_info.info[i].delay_resp_tx, stats_info.ptp_port_info.info[i].delay_resp_rx, stats_info.ptp_port_info.info[i].delay_resp_rx_err);
				CLI_API_Printf(sid, " %21s %15d %15d %15d\r\n",  "announce",stats_info.ptp_port_info.info[i].announce_tx, stats_info.ptp_port_info.info[i].announce_rx, stats_info.ptp_port_info.info[i].announce_rx_err);
			}
			break;
		case BC_STATS_OP_PTP:
			if(stats_info.ptp_info.num)
			{
				CLI_API_Printf(sid, "--------- PTP Module information --------------\r\n");
				CLI_API_Printf(sid, "%20s %10s %10s %10s %10s\r\n", "item", "value", "min", "max", "mean");
				CLI_API_Printf(sid, "%20s %10d %10d %10d %10d\r\n", "offset", stats_info.ptp_info.info.ptp_offset_value, stats_info.ptp_info.info.ptp_offset_min, stats_info.ptp_info.info.ptp_offset_max, stats_info.ptp_info.info.ptp_offset_mean);
				CLI_API_Printf(sid, "%20s %10d %10d %10d %10d\r\n", "mts_path_delay", stats_info.ptp_info.info.ptp_mts_path_delay_value, stats_info.ptp_info.info.ptp_mts_path_delay_min, stats_info.ptp_info.info.ptp_mts_path_delay_max, stats_info.ptp_info.info.ptp_mts_path_delay_mean);
				CLI_API_Printf(sid, "%20s %10d %10d %10d %10d\r\n", "stm_path_delay",stats_info.ptp_info.info.ptp_stm_path_delay_value, stats_info.ptp_info.info.ptp_stm_path_delay_min, stats_info.ptp_info.info.ptp_stm_path_delay_max, stats_info.ptp_info.info.ptp_stm_path_delay_mean);
				CLI_API_Printf(sid, "%20s %10d %10d %10d %10d\r\n", "mean_path_delay",stats_info.ptp_info.info.ptp_mean_path_delay_value,stats_info.ptp_info.info.ptp_mean_path_delay_min,stats_info.ptp_info.info.ptp_mean_path_delay_max,stats_info.ptp_info.info.ptp_mean_path_delay_mean);
				CLI_API_Printf(sid, "%20s %10d %10d %10d %10d\r\n", "total_offset",stats_info.ptp_info.info.ptp_total_offset_value, stats_info.ptp_info.info.ptp_total_offset_end, stats_info.ptp_info.info.ptp_total_offset_ptop, stats_info.ptp_info.info.ptp_total_offset_mean);
				CLI_API_Printf(sid, "%20s %10d %10d %10d %10d\r\n", "passive_offset",stats_info.ptp_info.info.ptp_passive_offset_value,stats_info.ptp_info.info.ptp_passive_offset_min, stats_info.ptp_info.info.ptp_passive_offset_max, stats_info.ptp_info.info.ptp_passive_offset_mean);
				CLI_API_Printf(sid, "%20s %10d %10d %10d %10d\r\n", "outside_ptp_offset",stats_info.ptp_info.info.outside_ptp_offset_value,stats_info.ptp_info.info.outside_ptp_offset_min,stats_info.ptp_info.info.outside_ptp_offset_max, stats_info.ptp_info.info.outside_ptp_offset_mean);
			}
			break;
		case BC_STATS_OP_VP:
			for(i = 0; i<stats_info.vp_info.num; i++)
			{
				CLI_API_Printf(sid, "--------------- VP [%d] information --------------\r\n", stats_info.vp_info.info[i].vp_num);
				CLI_API_Printf(sid, "  %20s %10d %20s %10d\r\n", "tx_packs:",stats_info.vp_info.info[i].tx_packs,"rx_packs:",stats_info.vp_info.info[i].rx_packs);
				CLI_API_Printf(sid, "  %20s %10lld %20s %10lld\r\n", "tx_bytes:",stats_info.vp_info.info[i].tx_bytes,"rx_bytes:", stats_info.vp_info.info[i].rx_bytes);
				CLI_API_Printf(sid, "  %20s %10d %20s %10d\r\n","vp_tx_cv:",stats_info.vp_info.info[i].vp_tx_cv,"vp_rx_cv:",stats_info.vp_info.info[i].vp_rx_cv);
				CLI_API_Printf(sid, "  %20s %10d %20s %10d\r\n", "packlosr_near:",stats_info.vp_info.info[i].packlosr_near,"packlosr_far:",stats_info.vp_info.info[i].packlosr_far);
				CLI_API_Printf(sid, "  %20s %10d %20s %10d\r\n", "bfd_tx_packs:",stats_info.vp_info.info[i].bfd_tx_packs,"bfd_rx_packs:",stats_info.vp_info.info[i].bfd_rx_packs);

				f1 = stats_info.vp_info.info[i].packdelay_s * 1000 + ((double)stats_info.vp_info.info[i].packdelay_ns / (1000 * 1000));
				f2 = stats_info.vp_info.info[i].packdelayvar_s * 1000 + ((double)stats_info.vp_info.info[i].packdelayvar_ns / (1000 * 1000));
				CLI_API_Printf(sid, "  %20s %10lfms %20s %10lfms\r\n", "packdelay:",f1,"packdelayvar:",f2);
			}
			break;
		case BC_STATS_OP_VC:
			for(i = 0; i<stats_info.vc_info.num; i++)
			{
				CLI_API_Printf(sid, "--------------- VC [%d] information --------------\r\n", stats_info.vc_info.info[i].vc_num);
				CLI_API_Printf(sid, "  %20s %10d %20s %10d\r\n", "tx_packs:",stats_info.vc_info.info[i].tx_packs,"rx_packs:",stats_info.vc_info.info[i].rx_packs);
				CLI_API_Printf(sid, "  %20s %10lld %20s %10lld\r\n", "tx_bytes:",stats_info.vc_info.info[i].tx_bytes,"rx_bytes:",stats_info.vc_info.info[i].rx_bytes);
				CLI_API_Printf(sid, "  %20s %10d %20s %10d\r\n","vc_tx_cv:",stats_info.vc_info.info[i].vc_tx_cv,"vc_rx_cv:",stats_info.vc_info.info[i].vc_rx_cv);
				CLI_API_Printf(sid, "  %20s %10d %20s %10d\r\n", "packlosr_near:",stats_info.vc_info.info[i].packlosr_near,"packlosr_far:",stats_info.vc_info.info[i].packlosr_far);
				f1 = stats_info.vc_info.info[i].packdelay_s * 1000 + ((double)stats_info.vc_info.info[i].packdelay_ns / (1000 * 1000 * 1000));
				f2 = stats_info.vc_info.info[i].packdelayvar_s * 1000 + ((double)stats_info.vc_info.info[i].packdelayvar_ns / (1000 * 1000 * 1000));
				CLI_API_Printf(sid, "  %20s %10lfms %20s %10lfms\r\n", "packdelay:",f1,"packdelayvar:",f2);
			}
			break;
		case BC_STATS_OP_E1:
			for(i = 0; i<stats_info.e1_info.num; i++)
			{
				CLI_API_Printf(sid, "--------------- E1 [%d] information --------------\r\n", stats_info.e1_info.info[i].e1_num);
				CLI_API_Printf(sid, " %22s %15d %22s %15d\r\n", "context_tx_pkts:", stats_info.e1_info.info[i].context_tx_pkts,"context_rx_pkts:", stats_info.e1_info.info[i].context_rx_pkts);
				CLI_API_Printf(sid, " %22s %15d %22s %15d\r\n", "context_early_pkts:", stats_info.e1_info.info[i].context_early_pkts,"context_late_pkts:", stats_info.e1_info.info[i].context_late_pkts);
				CLI_API_Printf(sid, " %22s %15d %22s %15d\r\n", "context_loss_pkts:", stats_info.e1_info.info[i].context_loss_pkts,"context_underrun_pkts:", stats_info.e1_info.info[i].context_underrun_pkts);
				CLI_API_Printf(sid, " %22s %15d %22s %15d\r\n", "ES:", stats_info.e1_info.info[i].es,"ses:", stats_info.e1_info.info[i].ses);
				CLI_API_Printf(sid, " %22s %15d %22s %15d\r\n", "BBE:", stats_info.e1_info.info[i].bbe,"UAS:", stats_info.e1_info.info[i].uas);
				CLI_API_Printf(sid, " %22s %15d %22s %15d\r\n", "HDB3_ERR:", stats_info.e1_info.info[i].e1_hdb3_err,"CRC_ERR:", stats_info.e1_info.info[i].e1_crc_err);
			}
			break;
		default: return CLI_CMD_FAIL_PRT_NEWLINE;
	}

	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

/******************************************************************************\
  Function   : __stats_show
  Description:显示统计信息
  Return     : bool true: 成功  false:非零失败
  Others     : 
\******************************************************************************/
static cli_cmd_ret_e __stats_show_info_list(const UI32_T sid, bc_stats_info_t stats_info)
{
	__stats_show_info_mdl(sid, CLI_STATS_OP_TEMP, stats_info);
	__stats_show_info_mdl(sid, CLI_STATS_OP_OAM_PORT, stats_info);
	__stats_show_info_mdl(sid, CLI_STATS_OP_PORT, stats_info);
	__stats_show_info_mdl(sid, CLI_STATS_OP_PTP_PORT, stats_info);
	__stats_show_info_mdl(sid, CLI_STATS_OP_PTP, stats_info);
	__stats_show_info_mdl(sid, CLI_STATS_OP_VP, stats_info);
	__stats_show_info_mdl(sid, CLI_STATS_OP_VC, stats_info);
	__stats_show_info_mdl(sid, CLI_STATS_OP_E1, stats_info);

	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

/******************************************************************************\
  Function   : __stats_show
  Description:显示统计信息
  Return     : bool true: 成功  false:非零失败
  Others     : 
\******************************************************************************/
static cli_cmd_ret_e __stats_show
(
	IN const UI32_T	sid,
	IN cli_value_t		*cli_para,
	IN void			*user_data
)
{
	PRT_CLI_PARA(l_mdl_id, cli_para);

	cli_value_t *para_tmp = cli_para;
	
	UI32_T op_id = 0;
	I32_T port_id = 0;	
	bc_stats_info_t info;
	bc_int32 num = 0;

	bc_err_e ret = BC_ERR_OK;
	bc_stats_threshold_info_t threshold_info;
	
       memset(&info, 0x00, sizeof(bc_stats_info_t));
	   
       op_id = *(UI32_T *)para_tmp->value;
	BC_PT_DBG_CPL(l_mdl_id, "Cli Para No1: option=%u\r\n", op_id);
	para_tmp = para_tmp->next;

	switch(op_id)
	{
		case 1:
			op_id = *(UI32_T *)para_tmp->value;
			BC_PT_DBG_CPL(l_mdl_id, "Cli Para No2: option=%u\r\n", op_id);
			para_tmp = para_tmp->next;
			switch(op_id)
			{
				case 11:
					BC_PT_DBG_CPL(l_mdl_id, "show stats temperature!\r\n");
					ret = bc_stats_get_board_temp(&info.temperature);
					CHECK_BCAPI_RET(ret);
					__stats_show_info_mdl(sid, BC_STATS_OP_TEMP, info);
					break;
				case 12:
					if (NULL == para_tmp)
					{
						BC_PT_DBG_CPL(l_mdl_id, "show stats oam port list!\r\n");
						ret = bc_stats_get_oamport_list(&info.oam_port_info);
					}
					else
					{
						para_tmp = para_tmp->next;
						port_id = *(I32_T *)para_tmp->value;
						BC_PT_DBG_CPL(l_mdl_id, "Cli Para oamport id: port_id=%u\r\n", port_id);
						para_tmp = para_tmp->next;
						ret = bc_stats_get_oamport_info(port_id, &info.oam_port_info.info[0]);
						info.oam_port_info.num = 1;
					}
					CHECK_BCAPI_RET(ret);
					__stats_show_info_mdl(sid, BC_STATS_OP_OAM_PORT, info);
					break;
				case 13:
					if (NULL == para_tmp)
					{
						BC_PT_DBG_CPL(l_mdl_id, "show stats port list!\r\n");
						ret = bc_stats_get_port_list(&info.port_info);
					}
					else
					{
						para_tmp = para_tmp->next;
						port_id = *(I32_T *)para_tmp->value;
						BC_PT_DBG_CPL(l_mdl_id, "Cli Para port id: port_id=%u\r\n", port_id);
						para_tmp = para_tmp->next;
						ret = bc_stats_get_port_info(port_id, &info.port_info.info[0]);
						info.port_info.num = 1;
					}
					CHECK_BCAPI_RET(ret);
					__stats_show_info_mdl(sid, BC_STATS_OP_PORT, info);
					break;
				case 14:
					if (NULL == para_tmp)
					{
						BC_PT_DBG_CPL(l_mdl_id, "show stats ptp port list!\r\n");
						ret = bc_stats_get_ptpport_list(&info.ptp_port_info);
					}
					else
					{
						para_tmp = para_tmp->next;
						port_id = *(I32_T *)para_tmp->value;
						BC_PT_DBG_CPL(l_mdl_id, "Cli Para ptpport id: port_id=%u\r\n", port_id);
						para_tmp = para_tmp->next;
						ret = bc_stats_get_ptpport_info(port_id, &info.ptp_port_info.info[0]);
						info.ptp_port_info.num = 1;
					}
					CHECK_BCAPI_RET(ret);
					__stats_show_info_mdl(sid, BC_STATS_OP_PTP_PORT, info);
					break;
				case 15:
					BC_PT_DBG_CPL(l_mdl_id, "show stats ptp list!\r\n");
					ret = bc_stats_get_ptp_info(&info.ptp_info.info);
					CHECK_BCAPI_RET(ret);
					__stats_show_info_mdl(sid, BC_STATS_OP_PTP, info);
					break;
				case 16:
					if (NULL == para_tmp)
					{
						BC_PT_DBG_CPL(l_mdl_id, "show stats vp list!\r\n");
						ret = bc_stats_get_vp_list(&info.vp_info);
					}
					else
					{
						para_tmp = para_tmp->next;
						port_id = *(I32_T *)para_tmp->value;
						BC_PT_DBG_CPL(l_mdl_id, "Cli Para vp id: port_id=%u\r\n", port_id);
						para_tmp = para_tmp->next;
						ret = bc_stats_get_vp_info(port_id, &info.vp_info.info[0]);
						info.vp_info.num = 1;
					}
					CHECK_BCAPI_RET(ret);
					__stats_show_info_mdl(sid, BC_STATS_OP_VP, info);
					break;
				case 17:
					if (NULL == para_tmp)
					{
						BC_PT_DBG_CPL(l_mdl_id, "show stats vc list!\r\n");
						ret = bc_stats_get_vc_list(&info.vc_info);
					}
					else
					{
						para_tmp = para_tmp->next;
						port_id = *(I32_T *)para_tmp->value;
						BC_PT_DBG_CPL(l_mdl_id, "Cli Para vc id: port_id=%u\r\n", port_id);
						para_tmp = para_tmp->next;
						ret = bc_stats_get_vc_info(port_id, &info.vc_info.info[0]);
						info.vc_info.num = 1;
					}
					CHECK_BCAPI_RET(ret);
					__stats_show_info_mdl(sid, BC_STATS_OP_VC, info);
					break;
				case 18:
					if (NULL == para_tmp)
					{
						BC_PT_DBG_CPL(l_mdl_id, "show stats e1 list!\r\n");
						ret = bc_stats_get_e1_list(&info.e1_info);
					}
					else
					{
						para_tmp = para_tmp->next;
						port_id = *(I32_T *)para_tmp->value;
						BC_PT_DBG_CPL(l_mdl_id, "Cli Para e1 id: port_id=%u\r\n", port_id);
						para_tmp = para_tmp->next;
						ret = bc_stats_get_e1_info(port_id, &info.e1_info.info[0]);
						info.e1_info.num = 1;
					}
					CHECK_BCAPI_RET(ret);
					__stats_show_info_mdl(sid, BC_STATS_OP_E1, info);
					break;
				case 19:
					BC_PT_DBG_CPL(l_mdl_id, "show stats cur list!\r\n");
					ret = bc_stats_get_cur_info(&info);
					CHECK_BCAPI_RET(ret);
					__stats_show_info_list(sid, info);
				default:
					BC_PT_DBG_CPL(l_mdl_id, "Cli input para unknow!\r\n");
					return CLI_CMD_FAIL_PRT_NEWLINE;
			}
			break;
		case 2:
			op_id = *(UI32_T *)para_tmp->value;
			BC_PT_DBG_CPL(l_mdl_id, "Cli Para No2: option=%u\r\n", op_id);
			para_tmp = para_tmp->next;
			switch(op_id)
			{
				case 21:
					if(NULL == para_tmp)
					{
						BC_PT_DBG_CPL(l_mdl_id, "show stats 15min list!\r\n");
						ret = bc_stats_get_15min_info(&info);
					}
					else
					{
						BC_PT_DBG_CPL(l_mdl_id, "show stats 15min inc list!\r\n");
						ret = bc_stats_get_15min_incream_info(&info);
					}
					CHECK_BCAPI_RET(ret);
					__stats_show_info_list(sid, info);
					break;
				case 22:
					if(NULL == para_tmp)
					{
						BC_PT_DBG_CPL(l_mdl_id, "show stats 15min valid num!\r\n");
						ret = bc_stats_get_15min_valid_num(&num);
						CHECK_BCAPI_RET(ret);
						__stats_show_info_num(sid, BC_STATS_OP_15MIN_NUM, num);
					}
					else
					{
						BC_PT_DBG_CPL(l_mdl_id, "show stats 15min total num!\r\n");
						ret = bc_stats_get_15min_num(&num);
						CHECK_BCAPI_RET(ret);
						__stats_show_info_num(sid, BC_STATS_OP_15MIN_TOTAL_NUM, num);
					}
					break;
			default:
					BC_PT_DBG_CPL(l_mdl_id, "Cli input para unknow!\r\n");
					return CLI_CMD_FAIL_PRT_NEWLINE;
			}
			break;
		case 3:
			op_id = *(UI32_T *)para_tmp->value;
			BC_PT_DBG_CPL(l_mdl_id, "Cli Para No2: option=%u\r\n", op_id);
			para_tmp = para_tmp->next;
			switch(op_id)
			{
				case 31:
					if(NULL == para_tmp)
					{
						BC_PT_DBG_CPL(l_mdl_id, "show stats 24hour list!\r\n");
						ret = bc_stats_get_24hour_info(&info);
					}
					else
					{
						BC_PT_DBG_CPL(l_mdl_id, "show stats 24hour inc list!\r\n");
						ret = bc_stats_get_24hour_incream_info(&info);
					}
					CHECK_BCAPI_RET(ret);
					__stats_show_info_list(sid, info);
					break;
				case 32:
					if(NULL == para_tmp)
					{
						BC_PT_DBG_CPL(l_mdl_id, "show stats 24hour valid num!\r\n");
						ret = bc_stats_get_24hour_valid_num(&num);
						CHECK_BCAPI_RET(ret);
						__stats_show_info_num(sid, BC_STATS_OP_24HOUR_NUM, num);
					}
					else
					{
						BC_PT_DBG_CPL(l_mdl_id, "show stats 24hour total num!\r\n");
						ret = bc_stats_get_24hour_num(&num);
						CHECK_BCAPI_RET(ret);
						__stats_show_info_num(sid, BC_STATS_OP_24HOUR_TOTAL_NUM, num);
					}
					break;
				default:
					BC_PT_DBG_CPL(l_mdl_id, "Cli input para unknow!\r\n");
					return CLI_CMD_FAIL_PRT_NEWLINE;
			}
			break;

		case 4:
			ret = bc_stats_threshold_get(&threshold_info);
			if(ret != BC_ERR_OK)
			{
				return CLI_CMD_FAIL_PRT_NEWLINE;
			}
			CLI_API_Printf(sid, "\nthreshold info items: %d", BC_STATS_THRESHOLD_INFO_NUM);
			CLI_API_Printf(sid, "\r\n---------------------------------------------------------------------------------------------------------");
			CLI_API_Printf(sid, "\r\n %-10s\t%-10s\t%-10s\t%-10s ", "Name", "Value", "Alarm", "Mode");
			CLI_API_Printf(sid, "\r\n---------------------------------------------------------------------------------------------------------");
			CLI_API_Printf(sid, "\r\n %-10s\t%-10d\t%-10s\t%-10s", threshold_info.temp_upper.name, threshold_info.temp_upper.val, threshold_info.temp_upper.en?"enable":"------", threshold_info.temp_upper.mod==BC_STATS_ALRM_CLR_MOD_1S?"1s":"15min");
			CLI_API_Printf(sid, "\r\n %-10s\t%-10d\t%-10s\t%-10s", threshold_info.temp_lower.name, threshold_info.temp_lower.val, threshold_info.temp_lower.en?"enable":"------", threshold_info.temp_lower.mod==BC_STATS_ALRM_CLR_MOD_1S?"1s":"15min");
			CLI_API_Printf(sid, "\r\n %-10s\t%-10d\t%-10s\t%-10s", threshold_info.port_crc_err.name, threshold_info.port_crc_err.val, threshold_info.port_crc_err.en?"enable":"------", threshold_info.port_crc_err.mod==BC_STATS_ALRM_CLR_MOD_1S?"1s":"15min");
			CLI_API_Printf(sid, "\r\n %-10s\t%-10d\t%-10s\t%-10s", threshold_info.e1_crc_err.name, threshold_info.e1_crc_err.val, threshold_info.e1_crc_err.en?"enable":"------", threshold_info.e1_crc_err.mod==BC_STATS_ALRM_CLR_MOD_1S?"1s":"15min");
			CLI_API_Printf(sid, "\r\n %-10s\t%-10d\t%-10s\t%-10s", threshold_info.drop_pkt.name, threshold_info.drop_pkt.val, threshold_info.drop_pkt.en?"enable":"------", threshold_info.drop_pkt.mod==BC_STATS_ALRM_CLR_MOD_1S?"1s":"15min");
			CLI_API_Printf(sid, "\r\n %-10s\t%-10d\t%-10s\t%-10s", threshold_info.rx_bad_pkt.name, threshold_info.rx_bad_pkt.val, threshold_info.rx_bad_pkt.en?"enable":"------", threshold_info.rx_bad_pkt.mod==BC_STATS_ALRM_CLR_MOD_1S?"1s":"15min");
			CLI_API_Printf(sid, "\r\n %-10s\t%-10d\t%-10s\t%-10s", threshold_info.align.name, threshold_info.align.val, threshold_info.align.en?"enable":"------", threshold_info.align.mod==BC_STATS_ALRM_CLR_MOD_1S?"1s":"15min");
			CLI_API_Printf(sid, "\r\n %-10s\t%-10d\t%-10s\t%-10s", threshold_info.vp_sd.name, threshold_info.vp_sd.val, threshold_info.vp_sd.en?"enable":"------", threshold_info.vp_sd.mod==BC_STATS_ALRM_CLR_MOD_1S?"1s":"15min");
			CLI_API_Printf(sid, "\r\n %-10s\t%-10d\t%-10s\t%-10s", threshold_info.vp_sf.name, threshold_info.vp_sf.val, threshold_info.vp_sf.en?"enable":"------", threshold_info.vp_sf.mod==BC_STATS_ALRM_CLR_MOD_1S?"1s":"15min");
			CLI_API_Printf(sid, "\r\n %-10s\t%-10d\t%-10s\t%-10s", threshold_info.vc_sd.name, threshold_info.vc_sd.val, threshold_info.vc_sd.en?"enable":"------", threshold_info.vc_sd.mod==BC_STATS_ALRM_CLR_MOD_1S?"1s":"15min");
			CLI_API_Printf(sid, "\r\n %-10s\t%-10d\t%-10s\t%-10s", threshold_info.vc_sf.name, threshold_info.vc_sf.val, threshold_info.vc_sf.en?"enable":"------", threshold_info.vc_sf.mod==BC_STATS_ALRM_CLR_MOD_1S?"1s":"15min");
			CLI_API_Printf(sid, "\r\n %-10s\t%-10d\t%-10s\t%-10s", threshold_info.vs_sd.name, threshold_info.vs_sd.val, threshold_info.vs_sd.en?"enable":"------", threshold_info.vs_sd.mod==BC_STATS_ALRM_CLR_MOD_1S?"1s":"15min");
			CLI_API_Printf(sid, "\r\n %-10s\t%-10d\t%-10s\t%-10s", threshold_info.vs_sf.name, threshold_info.vs_sf.val, threshold_info.vs_sf.en?"enable":"------", threshold_info.vs_sf.mod==BC_STATS_ALRM_CLR_MOD_1S?"1s":"15min");
			CLI_API_Printf(sid, "\r\n");
			break;
		default:
			return CLI_CMD_FAIL_PRT_NEWLINE;
			break;
	}

	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

/******************************************************************************\
  Function   : __stats_threshold_set
  Description:设置性能统计告警门限
  Return     : bool true: 成功  false:非零失败
  Others     : 
\******************************************************************************/
static cli_cmd_ret_e __stats_threshold_set
(
	IN const UI32_T	sid,
	IN cli_value_t		*cli_para,
	IN void			*user_data
)
{
	PRT_CLI_PARA(l_mdl_id, cli_para);

	cli_value_t *para_tmp = cli_para;
	UI32_T op_id = 0;
	I32_T val = 0;	

	bc_stats_threshold_type_e type;
	bc_stats_threshold_info_t info;
	bc_stats_threshold_get(&info);
	
	bc_err_e ret = BC_ERR_OK;
		   
       op_id = *(UI32_T *)para_tmp->value;
	BC_PT_DBG_CPL(l_mdl_id, "Cli Para No1: option=%u\r\n", op_id);
	para_tmp = para_tmp->next;

	switch(op_id)
	{
		case 1:	/*board*/
			op_id = *(UI32_T *)para_tmp->value;
			BC_PT_DBG_CPL(l_mdl_id, "Cli Para No2: option=%u\r\n", op_id);
			para_tmp = para_tmp->next;
			if(op_id == 11)
			{
				op_id = *(UI32_T *)para_tmp->value;
				BC_PT_DBG_CPL(l_mdl_id, "Cli Para No3: option=%u\r\n", op_id);
				para_tmp = para_tmp->next;
				if(op_id == 111)/*hi*/
				{
					type = BC_STATS_THRESHOLD_TYPE_TEMP_UPPER;	
				}
				else if(op_id == 112)/*lo*/
				{
					type = BC_STATS_THRESHOLD_TYPE_TEMP_LOWER;	
				}
				else
				{
					//error
					return CLI_CMD_FAIL_PRT_NEWLINE;
				}
			}
			else
			{
				//error
				return CLI_CMD_FAIL_PRT_NEWLINE;
			}
			break;
		case 2:	/*port*/
			op_id = *(UI32_T *)para_tmp->value;
			BC_PT_DBG_CPL(l_mdl_id, "Cli Para No2: option=%u\r\n", op_id);
			para_tmp = para_tmp->next;
			if(op_id == 21)/*crc-err*/
			{
				type = BC_STATS_THRESHOLD_TYPE_PORT_CRC_ERR;
			}
			else if(op_id == 22)/*drop-pkt*/
			{
				type = BC_STATS_THRESHOLD_TYPE_DROP_PKT;
			}
			else if(op_id == 23)/*rx-bad-pkt*/
			{
				type = BC_STATS_THRESHOLD_TYPE_RX_BAD_PKT;
			}
			else if(op_id == 24)/*alin*/
			{
				type = BC_STATS_THRESHOLD_TYPE_ALIGN;
			}
			else
			{
				//error
				return CLI_CMD_FAIL_PRT_NEWLINE;
			}
			break;
		case 3:	/*e1*/
			op_id = *(UI32_T *)para_tmp->value;
			BC_PT_DBG_CPL(l_mdl_id, "Cli Para No2: option=%u\r\n", op_id);
			para_tmp = para_tmp->next;
			if(op_id == 31)/*crc-err*/
			{
				type = BC_STATS_THRESHOLD_TYPE_E1_CRC_ERR;
			}
			else
			{
				//error
				return CLI_CMD_FAIL_PRT_NEWLINE;
			}
			break;
		case 4:	/*vp*/
			op_id = *(UI32_T *)para_tmp->value;
			BC_PT_DBG_CPL(l_mdl_id, "Cli Para No2: option=%u\r\n", op_id);
			para_tmp = para_tmp->next;
			if(op_id == 41)/*sd*/
			{
				type = BC_STATS_THRESHOLD_TYPE_VP_SD;
			}
			else if(op_id == 42)/*sf*/
			{
				type = BC_STATS_THRESHOLD_TYPE_VP_SF;
			}
			else
			{
				//error
				return CLI_CMD_FAIL_PRT_NEWLINE;
			}
			break;
		case 5:	/*vc*/
			op_id = *(UI32_T *)para_tmp->value;
			BC_PT_DBG_CPL(l_mdl_id, "Cli Para No2: option=%u\r\n", op_id);
			para_tmp = para_tmp->next;
			if(op_id == 51)/*sd*/
			{
				type = BC_STATS_THRESHOLD_TYPE_VC_SD;
			}
			else if(op_id == 52)/*sf*/
			{
				type = BC_STATS_THRESHOLD_TYPE_VC_SF;
			}
			else
			{
				//error
				return CLI_CMD_FAIL_PRT_NEWLINE;
			}
			break;
		case 6:	/*vs*/
			op_id = *(UI32_T *)para_tmp->value;
			BC_PT_DBG_CPL(l_mdl_id, "Cli Para No2: option=%u\r\n", op_id);
			para_tmp = para_tmp->next;
			if(op_id == 61)/*sd*/
			{
				type = BC_STATS_THRESHOLD_TYPE_VS_SD;
			}
			else if(op_id == 62)/*sf*/
			{
				type = BC_STATS_THRESHOLD_TYPE_VS_SF;
			}
			else
			{
				//error
				return CLI_CMD_FAIL_PRT_NEWLINE;
			}
			break;
		default:
			return CLI_CMD_FAIL_PRT_NEWLINE;
			break;
	}

	val = *(I32_T *)para_tmp->value;
	BC_PT_DBG_CPL(l_mdl_id, "Cli Para value: val =%u\r\n", val);
	para_tmp = para_tmp->next;

	switch(type)
	{
		case BC_STATS_THRESHOLD_TYPE_TEMP_UPPER:
			info.temp_upper.val = val;
			break;
		case BC_STATS_THRESHOLD_TYPE_TEMP_LOWER:
			info.temp_lower.val = val;
			break;
		case BC_STATS_THRESHOLD_TYPE_PORT_CRC_ERR:
			info.port_crc_err.val = val;
			break;
		case BC_STATS_THRESHOLD_TYPE_E1_CRC_ERR:
			info.e1_crc_err.val = val;
			break;
		case BC_STATS_THRESHOLD_TYPE_DROP_PKT:
			info.drop_pkt.val = val;
			break;
		case BC_STATS_THRESHOLD_TYPE_RX_BAD_PKT:
			info.rx_bad_pkt.val = val;
			break;
		case BC_STATS_THRESHOLD_TYPE_ALIGN:
			info.align.val = val;
			break;
		case BC_STATS_THRESHOLD_TYPE_VP_SD:
			info.vp_sd.val = val;
			break;
		case BC_STATS_THRESHOLD_TYPE_VP_SF:
			info.vp_sf.val = val;
			break;
		case BC_STATS_THRESHOLD_TYPE_VC_SD:
			info.vc_sd.val = val;
			break;
		case BC_STATS_THRESHOLD_TYPE_VC_SF:
			info.vc_sf.val = val;
			break;
		case BC_STATS_THRESHOLD_TYPE_VS_SD:
			info.vs_sd.val = val;
			break;
		case BC_STATS_THRESHOLD_TYPE_VS_SF:
			info.vs_sf.val = val;
			break;
		default:
			return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	
	ret = bc_stats_threshold_set(info);
	if(ret != BC_ERR_OK)	
	{
		CLI_API_Printf(sid, "Threshold value set failure!\r\n");
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}

	CLI_API_Printf(sid, "Threshold value set successful!\r\n");
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

/******************************************************************************\
  Function   : __stats_del
  Description:设置性能统计告警门限
  Return     : bool true: 成功  false:非零失败
  Others     : 
\******************************************************************************/
static cli_cmd_ret_e __stats_del
(
	IN const UI32_T	sid,
	IN cli_value_t		*cli_para,
	IN void			*user_data
)
{
	PRT_CLI_PARA(l_mdl_id, cli_para);

	cli_value_t *para_tmp = cli_para;
	UI32_T op_id = 0;
	
	bc_err_e ret = BC_ERR_OK;
		   
       op_id = *(UI32_T *)para_tmp->value;
	BC_PT_DBG_CPL(l_mdl_id, "Cli Para No1: option=%u\r\n", op_id);
	para_tmp = para_tmp->next;

	switch(op_id)
	{
		case 1:
			ret = bc_stats_del_info();
			if(ret != BC_ERR_OK)	
			{
				CLI_API_Printf(sid, "clean all stats info failure!\r\n");
				return CLI_CMD_FAIL_PRT_NEWLINE;
			}
			break;
		case 2:
			ret = bc_stats_del_15min_info();
			if(ret != BC_ERR_OK)	
			{
				CLI_API_Printf(sid, "clean 15min stats info failure!\r\n");
				return CLI_CMD_FAIL_PRT_NEWLINE;
			}
			break;
		case 3:
			ret = bc_stats_del_24hour_info();
			if(ret != BC_ERR_OK)	
			{
				CLI_API_Printf(sid, "clean 24hour stats info failure!\r\n");
				return CLI_CMD_FAIL_PRT_NEWLINE;
			}
			break;
		default:
			return CLI_CMD_FAIL_PRT_NEWLINE;
			break;
	}	

	CLI_API_Printf(sid, "clean stats info successful!\r\n");
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

#if 1
void bc_cli_cmd_stats_reg(void)
{
	CLI_DBG_ENTER(l_mdl_id);
	BOOL_T ret_reg;

/*
	show
	-----
	show stats {current{temperature|oam-port|port|ptp-port|ptp|vp|vc|e1|list} | 15min{list|counter[all]} | 24hour{list{counter[all]}}}
*/

	/*show*/
	ret_reg = bc_cli_reg_cmd(
		CLI_MOD_PRIVI_PATH
		"/show "		 	"##""##"
		"stats "		"#show stats performance #""#查看统计信息#"
		"{"
			"current(1) "			"#cur stats info#""#当前统计信息#"
			"{"
				"temperature(11) " 			"#temperature#""#温度#"
				"|"
				"oam-port(12) "		"#oam-port #""#OAM 端口#"
				"["
					"port-id "			"#port number #""#端口号#"
					"<value> "
				"]"
				"|"
				"port(13) "		"#port #""#端口#"
				"["
					"port-id "			"#port number #""#端口号#"
					"<value> "
				"]"
				"|"
				"ptp-port(14) "		"#ptp-port #""#PTP 端口#"
				"["
					"port-id "			"#port number #""#端口号#"
					"<value> "
				"]"
				"|"
				"ptp(15) "		"#ptp #""#PTP#"
				"|"
				"vp(16) "		"#vp #""#VP#"
				"["
					"port-id "			"#port number #""#端口号#"
					"<value> "
				"]"
				"|"
				"vc(17) "		"#vc #""#VC#"
				"["
					"port-id "			"#port number #""#端口号#"
					"<value> "
				"]"
				"|"
				"e1(18) "		"#ces #""#CES#"
				"["
					"port-id "			"#port number #""#端口号#"
					"<value> "
				"]"
				"|"
				"list(19) "       "#cur all stats info #""#当前所有统计信息#"
			"}"
			"|"
			"15min(2) "		"#15min stats info #""#15分钟统计信息#"
			"{"
				"list(21) "		"#last 15min all stats info #""#最新15分钟统计信息#"
				"["
					"incream"	"#last 15min all incream stats info #""#最新15分钟增量统计信息#"
				"]"
				"|"
				"counter(22) " "#15min stats counter #""#15分钟统计次数#"
				"["
					"all " 	"#15min stats total counter #""#15分钟统计累计次数#"
				"]"
			"}"
			"|"
			"24hour(3) "		"#24hour stats info #""#24小时统计信息#"
			"{"
				"list(31) "		"#last 24hour all stats info #""#最新24小时统计信息#"
				"["
					"incream"	"#last 24hour all incream stats info #""#最新24小时增量统计信息#"
				"]"
				"|"
				"counter(32) " "#24hour stats counter #""#24小时统计次数#"
				"["
					"all " 	"#24hour stats total counter #""#24小时统计累计次数#"
				"]"
			"}"
			"|"
			"theshold(4) "		"#stats threshold info #""#统计门限信息#"
		"}",
		__stats_show,
		CLI_ACC_LVL_BASIC,
		"show.",
		"显示统计信息。",
		NULL);
	CLI_DBG_CPL(l_mdl_id, "ret=%d\r\n", ret_reg);

	/*set*/
	ret_reg = bc_cli_reg_cmd(
		CLI_MOD_PRIVI_PATH
		"/stats "		 	"#stats info#""#性能统计#"
		"threshold "		"#stats alarm threshold #""#设置统计告警门限#"
		"{"
			"board(1) "			"#board threshold value #""#板卡#"
			"{"
				"temperature(11) " 			"#temperature#""#温度#"
				"{"
					"high(111) "				"#hi#""#高温#"
					"|"
					"low(112) "				"#lo#""#低温#"
				"}"
			"}"
			"|"
			"port(2) "		"#port threshold value #""#端口#"
			"{"
				"crc-err(21) "			"#crc-err #""#CRC错误#"
				"|"
				"drop-pkt(22) "		"#drop-pkt #""#丢包数#"
				"|"
				"rx-bad-pkt(23) "		"#rx-bad-pkt #""#收坏包数#"
				"|"
				"alin(24) "		"#alin #""#alin#"
			"}"
			"|"
			"e1(3) "		"#e1 threshold value #""#E1#"
			"{"
				"crc-err(31) "		"#crc-err #""#CRC错误#"
			"}"
			"|"
			"vp(4) "		"#vp cc #""#VP 收包数#"
			"{"
				"sd(41) "		"#cc sum bigger#""#cc 收包数超上限#"
				"|"
				"sf(42) " 		"#cc sum small#""#cc 收包数超下限#"
			"}"
			"|"
			"vc(5) "		"#vc cc #""#VC 收包数#"
			"{"
				"sd(51) "		"#cc sum bigger#""#cc 收包数超上限#"
				"|"
				"sf(52) " 		"#cc sum small#""#cc 收包数超下限#"
			"}"
			"|"
			"vs(6) "		"#vs cc #""#VS 收包数#"
			"{"
				"sd(61) "		"#cc sum bigger#""#cc 收包数超上限#"
				"|"
				"sf(62) " 		"#cc sum small#""#cc 收包数超下限#"
			"}"
		"}"
		"<value> ",
		__stats_threshold_set,
		CLI_ACC_LVL_BASIC,
		"stats.",
		"设置性能统计告警门限。",
		NULL);
	CLI_DBG_CPL(l_mdl_id, "ret=%d\r\n", ret_reg);

	/*set*/
	ret_reg = bc_cli_reg_cmd(
		CLI_MOD_PRIVI_PATH
		"/no "		 	"#delete stats info#""#清除性能统计#"
		"stats "		"#stats info #""#清除统计信息#"
		"{"
			"all(1) "			"#clean all stats info #""#清除所有性能统计#"
			"|"
			"15min(2) "		"#clean 15min stats info #""#清除所有15分钟性能统计#"
			"|"
			"24hour(3) "		"#clean 24hour stats info #""#清除所有24小时性能统计#"
		"}",
		__stats_del,
		CLI_ACC_LVL_BASIC,
		"delete stats info.",
		"清除性能统计",
		NULL);
	CLI_DBG_CPL(l_mdl_id, "ret=%d\r\n", ret_reg);
}




/* 
 *	预留一个注释在文件最后
 */
/******************************************************************************\
  Function   : 
  Description: 
  Return     : 
  Others     : 
\******************************************************************************/

#endif



