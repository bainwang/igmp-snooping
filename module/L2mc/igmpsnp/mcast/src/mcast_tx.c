/*******************************************************************************
  [File name]	: mcast_tx.c
  [Author]     	: bain.wang@outlook.com
  [Version]    	: 1.0
  [Date]       	: 2017-06-15
  [Description]	:
	Multicast module send protocol packet
  [Others]     	:
	NULL
  [Function List]:  
    1. ....
    2. ....
  [History]:
	 D a t e      	Modification 							 Initials
	---------- 	--------------                                        ----------
	2017-06-15  	Created								 bain.wang@outlook.com
*******************************************************************************/

#include "mcast_tx.h"

#if BC_MULTICAST_INCLUDE

#include "mcast_cfg.h"
#include "mcast_host.h"
#include "mcast_call.h"
#include "bc_port_def.h"

#if 0 /*bain.wang@outlook.com*/
#include "drv_port.h"
#include "bc_igmp_mltcst_srv.h"
#include "bc_sys_ip.h"
#include "bc_sys_mac.h"
#endif

#if 1 /*bain.wang@outlook.com*/
#include "stdlib.h"
#include "string.h"
#include "bc_igmp_def.h"
#endif

static void __mcast_tx_dump(IN char* desc, bc_port_index_t port, IN bc_uint8 *buf, IN bc_uint16 len)
{
	bc_uint16 i;
	
	MCAST_DBG_PRT("\n\t(type: %d, slot: %d, pid: %d)TX %s", port.port_type, port.slot_id, port.port_id, desc);
	for (i = 0; i < len; i++)
	{
		if (i%16 == 0)
			MCAST_DBG_PRT("\n\t");

		if (i%8 == 0)
			MCAST_DBG_PRT(" ");

		MCAST_DBG_PRT("%02x ", buf[i]);
	}

	MCAST_DBG_PRT("\n");
}

static void __mcast_tx_free(void *p)
{
	bc_platform_mem_free(BC_MODULE_IGMP, p);
}

static void __mcast_tx_report_eth_info(
	IN bc_port_index_t send_port, 
	IN mcast_tx_report_node_t *report_node_p, 
	OUT mcast_pkt_eth_t *eth_header)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	bc_ip grp;
	mcast_igmp_version_e cur_ver;

	bc_int16 pvid = 0;
	bc_boolean tag = FALSE;
	
	cur_ver = mcast_host_ver_get();
	grp = (cur_ver == MCAST_IGMP_V3) ? MCAST_V3_REPORT_IP : report_node_p->grp;
	mcast_ip_cvrt_mac(grp, eth_header->dst_mac);
	mcast_call_get_host_mac(eth_header->src_mac);
	eth_header->type = 0x0800;

	mcast_call_get_port_vlan_state(send_port, &pvid, &tag);
	if (tag == TRUE)
	{
		eth_header->cvlan.type = 0x8100;
		eth_header->cvlan.prio = MCAST_PBC_DEFAULT_PRIO;
		eth_header->cvlan.vlan_id = pvid;
	}

	/* don't support qinq */
	eth_header->svlan.type = 0;
	eth_header->svlan.prio = 0;
	eth_header->svlan.vlan_id = 0;

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
}


static void __mcast_tx_report_ip_info(
	IN mcast_tx_report_node_t *report_node_p, 
	OUT mcast_pkt_ip_t *ip_header)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	mcast_igmp_version_e cur_ver;

	ip_header->ver_ihl = MCAST_PBC_IPv4_VER << 4;
	ip_header->tos = 0;
	ip_header->tot_len = 0;
	ip_header->id = mcast_random(65535);
	ip_header->frag_off = 0;
	ip_header->ttl = 1;
	ip_header->pro = MCAST_PBC_IP_PRO_IGMP;
	ip_header->check_sum = 0;
	mcast_call_get_host_ip(&ip_header->src_ip);

	cur_ver = mcast_host_ver_get();
	ip_header->dst_ip = (cur_ver == MCAST_IGMP_V3) ? MCAST_V3_REPORT_IP : report_node_p->grp;

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
}

mcast_ret_code mcast_tx_report(IN mcast_list_t *report_list)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);

	mcast_tx_report_node_t *report_node_p;
	mcast_up_port_node_t up_port[BC_PORT_SNI_MAX_COUNT];
	bc_int16 port_idx = 0;

	mcast_pkt_igmp_t igmp_info;
	mcast_igmp_version_e cur_ver;

	bc_uint8 *buf = NULL;
	bc_uint16 actual_length = 0;

	mcast_port_get_up_ports(up_port);

	mcast_list_scan(report_list, report_node_p, mcast_tx_report_node_t*)
	{
		for (port_idx = 0; port_idx < BC_PORT_SNI_MAX_COUNT; port_idx++)
		{
			if (up_port[port_idx].en == FALSE || 
				up_port[port_idx].router_port == MCAST_NONE_ROUTER_PORT)
				continue;
		
			actual_length = MCAST_PBC_LEN_MAX;
			buf = (bc_uint8*)mcast_alloc(MCAST_PBC_LEN_MAX);
			if (buf == NULL)
			{
				MCAST_LOG(MCAST_MODULE_TX, MCAST_RET_ERR_NORES, TRUE);
				continue;
			}
			
			memset(buf, 0x00, sizeof(bc_uint8)*MCAST_PBC_LEN_MAX);

			memset(&igmp_info, 0x00, sizeof(mcast_pkt_igmp_t));
			__mcast_tx_report_eth_info(up_port[port_idx].port_id, report_node_p, &(igmp_info.eth_hdr));
			__mcast_tx_report_ip_info(report_node_p, &(igmp_info.ip_hdr));

			igmp_dbg("vid: %d, pid: %d\n", igmp_info.eth_hdr.cvlan.vlan_id, port_idx);
			
			cur_ver = mcast_host_ver_get();
			igmp_info.pkt_type = (cur_ver == MCAST_IGMP_V1) ? MCAST_PBC_TYPE_V1_REPORT : 
								((cur_ver == MCAST_IGMP_V2) ? MCAST_PBC_TYPE_V2_REPORT : MCAST_PBC_TYPE_V3_REPORT);

			igmp_info.info.report.num_of_record = 1;
			igmp_info.info.report.record = (mcast_pkt_igmp_report_record_t*)mcast_alloc(sizeof(mcast_pkt_igmp_report_record_t));
			if (igmp_info.info.report.record == NULL)
			{
				mcast_free(buf);
				MCAST_LOG(MCAST_MODULE_TX, MCAST_RET_ERR_NORES, TRUE);
				continue;
			}

			memset(igmp_info.info.report.record, 0x00, sizeof(mcast_pkt_igmp_report_record_t));
			igmp_info.info.report.record[0].record_type = report_node_p->type;
			igmp_info.info.report.record[0].grp = report_node_p->grp;
			igmp_info.info.report.record[0].num_of_src = mcast_list_count(&report_node_p->src_list);
			if (igmp_info.info.report.record[0].num_of_src != 0)
			{
				igmp_info.info.report.record[0].src = mcast_src_list_2_block(&(report_node_p->src_list), &(igmp_info.info.report.record[0].num_of_src));
				if (igmp_info.info.report.record[0].src == NULL)
				{
					mcast_free(igmp_info.info.report.record);
					mcast_free(buf);
					MCAST_LOG(MCAST_MODULE_TX, MCAST_RET_ERR_NORES, TRUE);
					continue;
				}
			}
			
			if (mcast_pkt_igmp_encode(&igmp_info, buf, &actual_length) != MCAST_RET_OK)
			{
				mcast_free(igmp_info.info.report.record[0].src);
				mcast_free(igmp_info.info.report.record);
				mcast_free(buf);
				continue;
			}

			__mcast_tx_dump("Report", up_port[port_idx].port_id, buf, actual_length);
			mcast_call_tx(up_port[port_idx].port_id, actual_length, buf, MCAST_PBC_DEFAULT_PRIO, igmp_info.eth_hdr.cvlan.vlan_id, __mcast_tx_free);
			mcast_free(igmp_info.info.report.record[0].src);
			mcast_free(igmp_info.info.report.record);
		}
	}

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return MCAST_RET_OK;
}


static void __mcast_tx_query_eth_info(
	IN bc_uint16 vid, 
	IN bc_ip grp,
	IN mcast_pkt_query_e query_type, 
	OUT mcast_pkt_eth_t *eth_header)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	bc_ip dst_ip;

	dst_ip = (query_type == MCAST_PBC_QUERY_GEN) ? MCAST_QUERY_IP : grp;
	mcast_ip_cvrt_mac(dst_ip, eth_header->dst_mac);
#if 0 /*bain.wang@outlook.com*/
	bc_sys_mac_get_by_sys_type(BC_SYS_MAC_TYPE_SWITCH_CPU_E, eth_header->src_mac);
#endif
	eth_header->type = 0x0800;

	eth_header->cvlan.type = 0x8100;
	eth_header->cvlan.prio = MCAST_PBC_DEFAULT_PRIO;
	eth_header->cvlan.vlan_id = vid;
	
	/* don't support qinq */
	eth_header->svlan.type = 0;
	eth_header->svlan.prio = 0;
	eth_header->svlan.vlan_id = 0;

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
}


static void __mcast_tx_query_ip_info(
	IN bc_ip grp,
	IN IN mcast_pkt_query_e query_type,
	OUT mcast_pkt_ip_t *ip_header)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	bc_ip dst_ip;

	ip_header->ver_ihl = MCAST_PBC_IPv4_VER << 4;
	ip_header->tos = 0;
	ip_header->tot_len = 0;
	ip_header->id = mcast_random(65535);
	ip_header->frag_off = 0;
	ip_header->ttl = 1;
	ip_header->pro = MCAST_PBC_IP_PRO_IGMP;
	ip_header->check_sum = 0;
	mcast_call_get_host_ip(&ip_header->src_ip);

	dst_ip = (query_type == MCAST_PBC_QUERY_GEN) ? MCAST_QUERY_IP : grp;
	ip_header->dst_ip = dst_ip;

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
}

/*
	fill and send a group-and-source-specific query msg.
*/
mcast_ret_code mcast_tx_grp_src_query(IN bc_port_index_t send_port, IN bc_ip grp, IN mcast_list_t *src_list)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	mcast_down_port_node_t down_port;
	bc_uint16 send_vid;
	bc_uint8 *buf = NULL;
	bc_uint16 actual_length = 0;

	mcast_pkt_igmp_t igmp_info;
	mcast_cfg_t mcast_cfg;
	mcast_grp_t *grp_node_p = NULL;

	mcast_ret_code ret;

	mcast_port_get_down_port(send_port, &down_port);
	if (down_port.en == FALSE)
		return MCAST_RET_OK;

	if (mcast_cfg_grp_get_vid_by_grp(grp, &send_vid) == FALSE)
		MCAST_RET_ERR(MCAST_MODULE_TX, MCAST_RET_ERR_NOTFOUND, TRUE);

	actual_length = MCAST_PBC_LEN_MAX;
	buf = (bc_uint8*)mcast_alloc(MCAST_PBC_LEN_MAX);
	if (buf == NULL)
		MCAST_RET_ERR(MCAST_MODULE_TX, MCAST_RET_ERR_NORES, TRUE);
	memset(buf, 0x00, sizeof(bc_uint8)*MCAST_PBC_LEN_MAX);

	memset(&igmp_info, 0x00, sizeof(mcast_pkt_igmp_t));
	__mcast_tx_query_eth_info(send_vid, grp, MCAST_PBC_QUERY_SRC_GRP, &(igmp_info.eth_hdr));
	__mcast_tx_query_ip_info(grp, MCAST_PBC_QUERY_SRC_GRP, &(igmp_info.ip_hdr));

	igmp_dbg("vid: %d, pid: %d\n", igmp_info.eth_hdr.cvlan.vlan_id, down_port.port_id.port_id);

	mcast_cfg_get(&mcast_cfg);
	grp_node_p = mcast_rt_node_get(grp);
	if (grp_node_p == NULL)
	{
		mcast_free(buf);
		MCAST_RET_ERR(MCAST_MODULE_TX, MCAST_RET_ERR_NOTFOUND, TRUE);
	}

	igmp_info.pkt_type = MCAST_PBC_TYPE_QUERY;
	/*
	Group Compatibility Mode 	Timer State
	------------------------ 	-----------
	IGMPv3 (default) 			IGMPv2 Host Present not running
								and IGMPv1 Host Present not running
	IGMPv2 						IGMPv2 Host Present running
								and IGMPv1 Host Present not running
	IGMPv1 						IGMPv1 Host Present running
	*/
	igmp_info.info.query.query_ver = (grp_node_p->port_grp[send_port.port_id-1].v1_tic != 0) ? MCAST_IGMP_V1 : 
									(grp_node_p->port_grp[send_port.port_id-1].v2_tic != 0) ? MCAST_IGMP_V2 : MCAST_IGMP_V3;
	igmp_info.info.query.max_resp_time = mcast_cfg.last_member_query_interval;
	igmp_info.info.query.grp = 0;
	igmp_info.info.query.s_flag = 1;
	igmp_info.info.query.qrv = mcast_cfg.robustness;
	igmp_info.info.query.qqic = mcast_cfg.query_interval;
	igmp_info.info.query.num_of_src = mcast_list_count(src_list);
	if (igmp_info.info.query.num_of_src != 0)
	{
		if ((igmp_info.info.query.src = mcast_src_list_2_block(src_list,  &(igmp_info.info.query.num_of_src))) == NULL)
		{
			mcast_free(buf);
			MCAST_RET_ERR(MCAST_MODULE_TX, MCAST_RET_ERR_NORES, TRUE);
		}
	}

	if ((ret = mcast_pkt_igmp_encode(&igmp_info, buf, &actual_length)) != MCAST_RET_OK)
	{
		mcast_free(igmp_info.info.query.src);
		mcast_free(buf);
		return ret;
	}

	__mcast_tx_dump("Grp Src Query", down_port.port_id, buf, actual_length);
	mcast_call_tx(down_port.port_id, actual_length, buf, MCAST_PBC_DEFAULT_PRIO, igmp_info.eth_hdr.cvlan.vlan_id, __mcast_tx_free);
	mcast_free(igmp_info.info.query.src);

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return MCAST_RET_OK;
}

extern bc_boolean __mcast_pkt_checksum(IN bc_uint8 *buf, IN bc_uint16 buf_len, IN bc_uint16 check_sum_off);
mcast_ret_code mcast_tx_gen_query(void)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	mcast_down_port_node_t down_ports[BC_PORT_PON_MAX_COUNT];
    	bc_int32 inft_num = 0;
	bc_int16 port_idx;
	bc_mac sys_mac;
	bc_ip sys_ip;
	bc_ip msk;
	bc_ip gw;
	bc_int16 vid = 0, tmp = 0;

	bc_uint8 buf[64] = {'\0'}, *packhead = NULL;
	bc_uint16 pkt_len = 64;
	mcast_cfg_t mcast_cfg;
	bc_port_link_status_e status = 0;

	memset(&down_ports, 0x00, sizeof(mcast_down_port_node_t)*BC_PORT_PON_MAX_COUNT);
	memset(&mcast_cfg, 0x00, sizeof(mcast_cfg_t));
	memset(&sys_ip, 0x00, sizeof(bc_ip));
	memset(&msk, 0x00, sizeof(bc_ip));
	memset(&gw, 0x00, sizeof(bc_ip));

#if 0 /*bain.wang@outlook.com*/	
    	if (BC_ERR_OK != bc_sys_ip_def_get(BC_SYS_IP_TYPE_INBAND_E, &inft_num, &sys_ip, &msk, &gw))
  	{
        	igmp_dbg("get inband ip fail!\n");
        	return MCAST_RET_ERR_UNKNOW;
    	}
#endif

	mcast_port_get_down_ports(down_ports);
	while (mcast_vlan_get_next(tmp, &vid))
	{
		igmp_dbg("vid: %d\n", vid);
		for (port_idx = 0; port_idx < BC_PORT_PON_MAX_COUNT; port_idx++)
		{
			if (down_ports[port_idx].en == FALSE)
				continue;
			
#if 0 /*bain.wang@outlook.com*/
			drv_port_link_state_get(down_ports[port_idx].port_id, &status);
			if (PORT_LINK_UP != status)
			{
				continue;
			}
 #endif
 
			igmp_dbg("vid: %d, pid_idx: %d, pid: %d\n", vid, port_idx, down_ports[port_idx].port_id.port_id);
			packhead = buf;

			mcast_cfg_get(&mcast_cfg);
			
#if 0 /*bain.wang@outlook.com*/
			memset(&sys_mac, 0, sizeof(sys_mac));
			bc_sys_mac_get_by_sys_type(BC_SYS_MAC_TYPE_SWITCH_CPU_E, sys_mac);
#endif
			igmp_dbg("\n");
			memcpy(packhead, "\x01\x00\x5e\x00\x00\x01", 6);
			memcpy(packhead + 6, sys_mac, 6);
			packhead[12] = 0x08;//protol
			packhead[13] = 0x00;
			//-----------------
			packhead[14] = 0x46;
			//---------Total length
			packhead[15] = 0x2;
			packhead[16] = 0x00;
			packhead[17] = 0x20;
			packhead[18] = 0xcf;
			packhead[19] = 0xae;
			//-----------
			packhead[20] = 0x0;
			packhead[21] = 0x0;
			//----------		
			packhead[22] = 0x1;//TTL
			packhead[23] = MCAST_PBC_IP_PRO_IGMP;//igmp

            packhead[26] = (sys_ip >> 24) & 0xff;
			packhead[27] = (sys_ip >> 16) & 0xff;
			packhead[28] = (sys_ip >> 8) & 0xff;
			packhead[29] = sys_ip & 0xff;

			memcpy(packhead + 30, "\xe0\x00\x00\x01", 4);//group address

			packhead[34] = 0x94;
			packhead[35] = 0x4;
			packhead[36] = 0x0;
			packhead[37] = 0x0;

			//Ip Head check sum
			packhead[24] = 0;//head check
			packhead[25] = 0;
			
			/*IGMP----------------*/
			packhead[38] = 0x11;//General Query
			packhead[39] = bc_htons(mcast_cfg.query_rsp_interval);//MAX response time

			packhead[40] = 0;//cksum
			packhead[41] = 0;
			memcpy(packhead + 42, "\x00\x00\x00\x00", 4);//group address
			packhead[63] = '\0';

			//IP checksum
			__mcast_pkt_checksum(&packhead[14], 24, 10);
			//IGMP checksum
			__mcast_pkt_checksum(&packhead[38], 63 - 38, 2);
			
			__mcast_tx_dump("Gen Query", down_ports[port_idx].port_id, buf, pkt_len);
			igmp_dbg("port_id: %d\n", down_ports[port_idx].port_id.port_id);
			mcast_call_tx(down_ports[port_idx].port_id, pkt_len, buf, MCAST_PBC_DEFAULT_PRIO, vid, NULL/*mcast_free*/);
		}

		tmp = vid;
	}

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return MCAST_RET_OK;
}

static mcast_ret_code __mcast_send_pkt(bc_port_index_t port, bc_uint16 vid, bc_uint32 grp)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	bc_int32 inft_num = 0;
	bc_mac sys_mac;
	bc_ip sys_ip;
	bc_ip msk;
	bc_ip gw;
	bc_uint16 pkt_len = 64;
	mcast_cfg_t mcast_cfg;
	bc_uint8 buf[64] = {'\0'}, *packhead = NULL;

	packhead = buf;

	mcast_cfg_get(&mcast_cfg);

#if 0 /*bain.wang@outlook.com*/
	memset(&sys_mac, 0, sizeof(sys_mac));
	if (BC_ERR_OK != bc_sys_mac_get_by_sys_type(BC_SYS_MAC_TYPE_SWITCH_CPU_E, sys_mac))
	{
		return MCAST_RET_ERR_DRVERR;
	}
    
	if (BC_ERR_OK != bc_sys_ip_def_get(BC_SYS_IP_TYPE_INBAND_E, &inft_num, &sys_ip, &msk, &gw))
	{
		igmp_dbg("get inband ip fail!\n");
		return MCAST_RET_ERR_UNKNOW;
	}
#endif

	igmp_dbg("\n");
	memcpy(packhead, "\x01\x00\x5e\x00\x00\x01", 6);
	memcpy(packhead + 6, sys_mac, 6);
	packhead[12] = 0x08;//protol
	packhead[13] = 0x00;
	//-----------------
	packhead[14] = 0x46;
	//---------Total length
	packhead[15] = 0x2;
	packhead[16] = 0x00;
	packhead[17] = 0x20;
	packhead[18] = 0xcf;
	packhead[19] = 0xae;
	//-----------
	packhead[20] = 0x0;
	packhead[21] = 0x0;
	//----------		
	packhead[22] = 0x1;//TTL
	packhead[23] = MCAST_PBC_IP_PRO_IGMP;//igmp

	/*src ip address*/
	packhead[26] = (sys_ip >> 24) & 0xff;
	packhead[27] = (sys_ip >> 16) & 0xff;
	packhead[28] = (sys_ip >> 8) & 0xff;
	packhead[29] = sys_ip & 0xff;

	/*dst ip address*/
	packhead[30] = (grp >> 24) & 0xff;
	packhead[31] = (grp >> 16) & 0xff;
	packhead[32] = (grp >> 8) & 0xff;
	packhead[33] = grp & 0xff;

 	packhead[34] = 0x94;
	packhead[35] = 0x4;
	packhead[36] = 0x0;
	packhead[37] = 0x0;

	//Ip Head check sum
	packhead[24] = 0;//head check
	packhead[25] = 0;
	
	/*IGMP----------------*/
	packhead[38] = 0x11;//General Query
	packhead[39] = bc_htons(mcast_cfg.query_rsp_interval);//MAX response time

	packhead[40] = 0;//cksum
	packhead[41] = 0;
	
	/*grp address*/
 	packhead[42] = (grp >> 24) & 0xff;
	packhead[43] = (grp >> 16) & 0xff;
	packhead[44] = (grp >> 8) & 0xff;
	packhead[45] = grp & 0xff;

	packhead[63] = '\0';

	//IP checksum
	__mcast_pkt_checksum(&packhead[14], 24, 10);
	//IGMP checksum
	__mcast_pkt_checksum(&packhead[38], 63 - 38, 2);
	
	__mcast_tx_dump("Gen Query", port, buf, pkt_len);
	igmp_dbg("port_id: %d, vid: %d\n", port.port_id, vid);
	mcast_call_tx(port, pkt_len, buf, MCAST_PBC_DEFAULT_PRIO, vid, NULL/*mcast_free*/);

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return MCAST_RET_OK; 
}

mcast_ret_code mcast_tx_grp_query(IN bc_port_index_t send_port, IN bc_ip grp)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	bc_port_index_t tmp_port = {0};
	bc_port_link_status_e status = 0;

	bc_igmp_mltcst_xx_info_t igmp_mltcst_info[BC_IGMP_OLT_MLTCST_VLAN_COUNT];
	bc_uint16 count = 0, vid_idx, pid_idx;

	igmp_dbg("port (t: %d, s: %d, p: %d) MCAST_PBC_QUERY_GRP\n",
		send_port.port_type,	send_port.slot_id, send_port.port_id);

#if 0 /*bain.wang@outlook.com*/
	memset(igmp_mltcst_info, 0, sizeof(igmp_mltcst_info));
	if (BC_ERR_OK != bc_local_query_xx_igmp_all_mltcst(igmp_mltcst_info, &count))
	{
		igmp_dbg("get mltcst vlan failed!\n");
		return MCAST_RET_ERR_NOTFOUND;
	}
#endif

	tmp_port.slot_id = send_port.slot_id;
	tmp_port.port_type = send_port.port_type;
	if (send_port.port_type == PORT_TYPE_OLT_GEEPON)
	{
		tmp_port.port_id = send_port.port_id - BC_PORT_SNI_MAX_COUNT;
		igmp_dbg("type: PORT_TYPE_OLTPON, pid: %d\n", tmp_port.port_id);
	}
	else
	{
		tmp_port.port_id = send_port.port_id;
	}
	
	for (vid_idx = 0; vid_idx < count; vid_idx++)
	{
		igmp_dbg("mltcst vid: %d\n", igmp_mltcst_info[vid_idx].mltcst_vid);
		for (pid_idx = 0; pid_idx < BC_PORT_PON_MAX_COUNT + BC_PORT_SNI_MAX_COUNT; pid_idx++)
		{
			igmp_dbg("port t: %d, s: %d, p: %d\n",
				igmp_mltcst_info[vid_idx].olt_port_lst[pid_idx].port_type,
				igmp_mltcst_info[vid_idx].olt_port_lst[pid_idx].slot_id,
				igmp_mltcst_info[vid_idx].olt_port_lst[pid_idx].port_id);
			
			if (igmp_mltcst_info[vid_idx].olt_port_lst[pid_idx].slot_id == tmp_port.slot_id
				&& igmp_mltcst_info[vid_idx].olt_port_lst[pid_idx].port_type == tmp_port.port_type
				&& igmp_mltcst_info[vid_idx].olt_port_lst[pid_idx].port_id == tmp_port.port_id)
			{
				igmp_dbg("port (t: %d, s: %d, p: %d) send.......\n", tmp_port.port_type,	tmp_port.slot_id, tmp_port.port_id);
			#if 0/*bain.wang@outlook.com*/
				drv_port_link_state_get(tmp_port, &status);
			#endif
				if (PORT_LINK_UP == status)//up
				{
					__mcast_send_pkt(tmp_port, igmp_mltcst_info[vid_idx].mltcst_vid, grp);
				}
				else
				{
					igmp_dbg("port (t: %d, s: %d, p: %d) was down!\n", tmp_port.port_type, tmp_port.slot_id, tmp_port.port_id);
				}
			}
		}
	}

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return MCAST_RET_OK;
}



#endif

