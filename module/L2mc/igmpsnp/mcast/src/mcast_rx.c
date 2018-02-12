/*******************************************************************************
  [File name]	: mcast_rx.c
  [Author]     	: bain.wang@outlook.com
  [Version]    	: 1.0
  [Date]       	: 2017-06-15
  [Description]	:
	Multicast module receive protocol packet
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

#include "mcast_rx.h"
#include "mcast_pkt.h"
#include "mcast_core.h"
#include "utili_ip_mac.h"

#if 1 /*bain.wang@outlook.com*/
#include "stdlib.h"
#include "string.h"
#endif

#if BC_MULTICAST_INCLUDE

extern bc_sem_t * mcast_sem;

static mcast_ret_code __mcast_rx_pkt_check_eth(IN mcast_pkt_eth_t *eth)
{
	bc_mac zero_mac = {0};
	
	if (memcmp(eth->dst_mac, zero_mac, 6) == 0)
		MCAST_RET_ERR(MCAST_MODULE_RX, MCAST_RET_ERR_PAR, TRUE);

	if (mcast_utl_is_mc_mac(eth->src_mac))
		MCAST_RET_ERR(MCAST_MODULE_RX, MCAST_RET_ERR_PAR, TRUE);
	
	if (eth->type != 0x0800)
		MCAST_RET_ERR(MCAST_MODULE_RX, MCAST_RET_ERR_PAR, TRUE);

	if (eth->svlan.vlan_id != 0)
		MCAST_RET_ERR(MCAST_MODULE_RX, MCAST_RET_ERR_PAR, TRUE);

	if (eth->cvlan.vlan_id != 0)
	{
		if (eth->cvlan.type != 0x8100)
			MCAST_RET_ERR(MCAST_MODULE_RX, MCAST_RET_ERR_PAR, TRUE);

		if (eth->cvlan.prio > 7)
			MCAST_RET_ERR(MCAST_MODULE_RX, MCAST_RET_ERR_PAR, TRUE);

		if (eth->cvlan.vlan_id > 4094)
			MCAST_RET_ERR(MCAST_MODULE_RX, MCAST_RET_ERR_PAR, TRUE);
	}

	return MCAST_RET_OK;
}


static mcast_ret_code __mcast_rx_pkt_check_ip(IN mcast_pkt_ip_t *ip)
{
	/* some option is checked when packet parse, it's not clearly ??? */
	if (ip->ttl != 1)
		MCAST_LOG(MCAST_MODULE_RX, MCAST_RET_ERR_PAR, TRUE);

	if (ip->dst_ip == 0)
		MCAST_RET_ERR(MCAST_MODULE_RX, MCAST_RET_ERR_PAR, TRUE);

	if (mcast_utl_valid_mc_ip(ip->src_ip))
		MCAST_RET_ERR(MCAST_MODULE_RX, MCAST_RET_ERR_PAR, TRUE);

	return MCAST_RET_OK;
}


static mcast_ret_code __mcast_rx_pkt_check_igmp_query(IN mcast_pkt_igmp_query_t *query)
{
	bc_uint16 src_idx;

	if (query->query_ver < MCAST_IGMP_V1 || query->query_ver > MCAST_IGMP_V3)
		MCAST_RET_ERR(MCAST_MODULE_RX, MCAST_RET_ERR_PAR, TRUE);

	/* query->max_resp_time */ 

	if (query->grp != 0 && mcast_utl_valid_mc_ip(query->grp) == FALSE)
		MCAST_RET_ERR(MCAST_MODULE_RX, MCAST_RET_ERR_PAR, TRUE);

	/* query->s_flag */

	if (query->qrv < MCAST_ROBUSTNESS_VARIABLE || MCAST_ROBUSTNESS_VARIABLE_MAX < query->qrv)
		MCAST_RET_ERR(MCAST_MODULE_RX, MCAST_RET_ERR_PAR, TRUE);

	/* query->qqic */

	if (query->num_of_src != 0 && query->src == NULL)
		MCAST_RET_ERR(MCAST_MODULE_RX, MCAST_RET_ERR_PAR, TRUE);

	for (src_idx = 0; src_idx < query->num_of_src; src_idx++)
	{
		if (mcast_utl_valid_uc_ip(query->src[src_idx]) == FALSE)
			MCAST_RET_ERR(MCAST_MODULE_RX, MCAST_RET_ERR_PAR, TRUE);
	}
	
	return MCAST_RET_OK;
}


static mcast_ret_code __mcast_rx_pkt_check_igmp_report(IN mcast_pkt_igmp_report_t *report)
{
	bc_uint16 record_idx;
	bc_uint16 src_idx;

	if (report->num_of_record == 0)
		MCAST_RET_ERR(MCAST_MODULE_RX, MCAST_RET_ERR_PAR, TRUE);

	for (record_idx = 0; record_idx < report->num_of_record; record_idx++)
	{
		if (report->record[record_idx].record_type < MCAST_PBC_RECORD_IS_INCLUDE || 
			MCAST_PBC_RECORD_BLOCK_OLD_SOURCES < report->record[record_idx].record_type)
			MCAST_RET_ERR(MCAST_MODULE_RX, MCAST_RET_ERR_PAR, TRUE);

		if (mcast_utl_valid_mc_ip(report->record[record_idx].grp) == FALSE)
			MCAST_RET_ERR(MCAST_MODULE_RX, MCAST_RET_ERR_PAR, TRUE);

		if (report->record[record_idx].num_of_src != 0 && report->record[record_idx].src == NULL)
			MCAST_RET_ERR(MCAST_MODULE_RX, MCAST_RET_ERR_PAR, TRUE);

		for (src_idx = 0; src_idx < report->record[record_idx].num_of_src; src_idx++)
		{
			if (mcast_utl_valid_uc_ip(report->record[record_idx].src[src_idx]) == FALSE)
				MCAST_RET_ERR(MCAST_MODULE_RX, MCAST_RET_ERR_PAR, TRUE);
		}
	}

	return MCAST_RET_OK;	
}


static mcast_ret_code __mcast_rx_pkt_check_igmp(IN mcast_pkt_igmp_t *igmp)
{
	mcast_ret_code ret = MCAST_RET_OK;

	if (!igmp)
		MCAST_RET_ERR(MCAST_MODULE_RX, MCAST_RET_ERR_PAR, TRUE);

	switch (igmp->pkt_type)
	{
	case MCAST_PBC_TYPE_QUERY:
		ret = __mcast_rx_pkt_check_igmp_query(&(igmp->info.query));
		break;
	case MCAST_PBC_TYPE_V1_REPORT:
	case MCAST_PBC_TYPE_V2_REPORT:
	case MCAST_PBC_TYPE_LEAVE:
		if (igmp->info.report.num_of_record > 1)
			MCAST_RET_ERR(MCAST_MODULE_RX, MCAST_RET_ERR_PAR, TRUE);

		ret = __mcast_rx_pkt_check_igmp_report(&(igmp->info.report));
		break;
	case MCAST_PBC_TYPE_V3_REPORT:
		ret = __mcast_rx_pkt_check_igmp_report(&(igmp->info.report));
		break;
	default:
		MCAST_RET_ERR(MCAST_MODULE_RX, MCAST_RET_ERR_PAR, TRUE);
		break;
	}

	return ret;
}


static mcast_ret_code __mcast_rx_is_valid_pkt(IN mcast_rx_node_t *pkt, IN mcast_pkt_igmp_t *igmp)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);

	mcast_cfg_t mcast_cfg;
	mcast_ret_code ret = MCAST_RET_OK;

	/* baisc check */
	/* vlan/onu valid/port/pon port rx query/sni rx report/etc.. */
	if (!pkt || !igmp)
		MCAST_RET_ERR(MCAST_MODULE_RX, MCAST_RET_ERR_PAR, TRUE);

	mcast_cfg_get(&mcast_cfg);
	if (mcast_cfg.enable == FALSE)
		MCAST_RET_ERR(MCAST_MODULE_RX, MCAST_RET_ERR_NOENABLE, FALSE);
/*
	don't check this item, protocol packet maybe use unicast pakcet
	if (pkt->llid != 0xFFFF)
		MCAST_RET_ERR(MCAST_MODULE_RX, MCAST_RET_ERR_PAR, TRUE);
*/

	if (MCAST_PBC_LEN_MAX < pkt->buf_len)
		MCAST_RET_ERR(MCAST_MODULE_RX, MCAST_RET_ERR_PAR, TRUE);

	if (!pkt->buf)
		MCAST_RET_ERR(MCAST_MODULE_RX, MCAST_RET_ERR_PAR, TRUE);


	if ((ret = __mcast_rx_pkt_check_eth(&igmp->eth_hdr)) != MCAST_RET_OK)
		return ret;

	if ((ret = __mcast_rx_pkt_check_ip(&igmp->ip_hdr)) != MCAST_RET_OK)
		return ret;

	if ((ret = __mcast_rx_pkt_check_igmp(igmp)) != MCAST_RET_OK)
		return ret;

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return MCAST_RET_OK;
}


static void __mcast_rx_pkt_dump(IN mcast_rx_node_t *pkt, IN mcast_pkt_igmp_t *igmp)
{
	int i;
	int j;
	char buf[40];

	char *ver_str[] = {
		"V1",
		"V2",
		"V3"
	};

	char *record_type_str[] = {
		"IS_IN",
		"IS_EX",
		"TO_IN",
		"TO_EX",
		"ALLOW",
		"BLOCK"
	};

	MCAST_DBG_PRT("\n\tReceive A IGMP Packet");
	MCAST_DBG_PRT("\n\tSlot:%d Type:%d Port:%d Llid:%0x bufLen:%d", pkt->rx_port.slot_id, pkt->rx_port.port_type, 
																pkt->rx_port.port_id, pkt->llid, pkt->buf_len);
	for (i = 0; i < pkt->buf_len; i++)
	{
		if (i%16 == 0)
			MCAST_DBG_PRT("\n\t");

		if (i%8 == 0)
			MCAST_DBG_PRT(" ");

		MCAST_DBG_PRT("%02x ", pkt->buf[i]);
	}

	MCAST_DBG_PRT("\n");
	MCAST_DBG_PRT("\n\tPacket Parse:");
	MCAST_DBG_PRT("\n\ttype:0x%04x ", igmp->eth_hdr.type);
	MCAST_DBG_SPRT_MAC(buf, 40, igmp->eth_hdr.dst_mac);
	MCAST_DBG_PRT("dmac:%s ", buf);
	MCAST_DBG_SPRT_MAC(buf, 40, igmp->eth_hdr.src_mac);
	MCAST_DBG_PRT("smac:%s", buf);
	if (igmp->eth_hdr.cvlan.vlan_id != 0)
		MCAST_DBG_PRT("\n\tcvlan:0x%04x pri:%d vid:%d", igmp->eth_hdr.cvlan.type, igmp->eth_hdr.cvlan.prio, igmp->eth_hdr.cvlan.vlan_id);
	if (igmp->eth_hdr.svlan.vlan_id != 0)
		MCAST_DBG_PRT("\n\tsvlan:0x%04x pri:%d vid:%d", igmp->eth_hdr.svlan.type, igmp->eth_hdr.svlan.prio, igmp->eth_hdr.svlan.vlan_id);

	MCAST_DBG_SPRT_IP(buf, 40, ((bc_uint8*)&(igmp->ip_hdr.dst_ip)));
	MCAST_DBG_PRT("\n\tdst ip:%s", buf);
	MCAST_DBG_SPRT_IP(buf, 40, ((bc_uint8*)&(igmp->ip_hdr.src_ip)));
	MCAST_DBG_PRT("\n\tsrc ip:%s", buf);
	MCAST_DBG_PRT("\n\tver_ihl:%02x tos:%d totlen:%d checksum:%04x ttl:%d", igmp->ip_hdr.ver_ihl, igmp->ip_hdr.tos, 
		igmp->ip_hdr.tot_len, igmp->ip_hdr.check_sum, igmp->ip_hdr.ttl);
	MCAST_DBG_PRT("\n\tfragoff:%02x id:%d pro:%d", igmp->ip_hdr.frag_off, igmp->ip_hdr.id, igmp->ip_hdr.pro);

	MCAST_DBG_PRT("\n\tigmp: %02x", igmp->pkt_type);
	if (igmp->pkt_type == 0x11)
	{
		MCAST_DBG_PRT(" query ver:%s mrt:%d", ver_str[igmp->qy.query_ver-1], igmp->qy.max_resp_time);
		MCAST_DBG_SPRT_IP(buf, 40, ((bc_uint8*)&(igmp->qy.grp)));
		MCAST_DBG_PRT("\n\tgrp:%s sflag:%d qrv:%d qqic:%d srcnum:%d", buf, igmp->qy.s_flag, igmp->qy.qrv, igmp->qy.qqic, igmp->qy.num_of_src);
		for (i = 0; i < igmp->qy.num_of_src; i++)
		{
			MCAST_DBG_SPRT_IP(buf, 40, ((bc_uint8*)&(igmp->qy.src[i])));
			MCAST_DBG_PRT("\n\t%s", buf);
		}
	}
	else if (igmp->pkt_type == 0x12 ||
		igmp->pkt_type == 0x16 ||
		igmp->pkt_type == 0x17 ||
		igmp->pkt_type == 0x22)
	{
		MCAST_DBG_PRT(" report record num:%d", igmp->rept.num_of_record);
		for (i = 0; i < igmp->rept.num_of_record; i++)
		{
			MCAST_DBG_PRT("\n\t%-6s ", record_type_str[igmp->recd[i].record_type-1]);
			MCAST_DBG_SPRT_IP(buf, 40, ((bc_uint8*)&(igmp->recd[i].grp)));
			MCAST_DBG_PRT("grp:%s srcnum:%d", buf, igmp->recd[i].num_of_src);
			for (j = 0; j < igmp->recd[i].num_of_src; j++)
			{
				if (j%2 == 0)
					MCAST_DBG_PRT("\n\t\t");
			
				MCAST_DBG_SPRT_IP(buf, 40, ((bc_uint8*)&(igmp->recd[i].src[j])));
				MCAST_DBG_PRT("%s ", buf);
			}
		}
	}
	else
	{
		MCAST_DBG_PRT("\n\tError");
	}
	MCAST_DBG_PRT("\n");
}

void mcast_rx_receive_pkt(mcast_rx_node_t *pkt)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	mcast_pkt_igmp_t igmp;
	
	memset(&igmp, 0x00, sizeof(mcast_pkt_igmp_t));
	if (mcast_pkt_igmp_decode(pkt->vid, pkt->buf, pkt->buf_len, &igmp) != MCAST_RET_OK)
	{
		BC_PT_DBG_FUN(BC_MODULE_IGMP, "mcast_pkt_igmp_decode failure\n");
		goto errorfree;
	}
	BC_PT_DBG_FUN(BC_MODULE_IGMP, "mcast_pkt_igmp_decode successful\n");
	
	if (__mcast_rx_is_valid_pkt(pkt, &igmp) != MCAST_RET_OK)
	{
		BC_PT_DBG_FUN(BC_MODULE_IGMP, "__mcast_rx_is_valid_pkt failure\n");
		goto errorfree;
	}
	BC_PT_DBG_FUN(BC_MODULE_IGMP, "__mcast_rx_is_valid_pkt successful\n");

#if 1	
	__mcast_rx_pkt_dump(pkt, &igmp);
	BC_PT_DBG_SMP(BC_MODULE_IGMP, "\n");
#endif

	mcast_os_sem_lock(mcast_sem);

	if(mcast_core_igmp_process(pkt, &igmp) != MCAST_RET_OK)
	{
		BC_PT_DBG_FUN(BC_MODULE_IGMP, "mcast_core_igmp_process failure\n");
	}
	BC_PT_DBG_FUN(BC_MODULE_IGMP, "mcast_core_igmp_process successful\n");
	
	mcast_os_sem_unlock(mcast_sem);

errorfree:
	mcast_pkt_decode_node_free(&igmp);
	if (pkt->free && pkt->buf)
		(pkt->free)(pkt->buf);

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
}


#endif

