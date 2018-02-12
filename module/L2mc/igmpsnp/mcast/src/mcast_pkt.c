/*******************************************************************************
  [File name]	: mcast_pkt.c
  [Author]     	: bain.wang@outlook.com
  [Version]    	: 1.0
  [Date]       	: 2017-06-15
  [Description]	:
	Multicast module packet parser
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

#include "mcast_pkt.h"
#include "mcast_cfg.h"

#if BC_MULTICAST_INCLUDE

#include "mcast_utl.h"

#if 1


static bc_uint16 __checksum(IN bc_uint8 *buf, IN bc_uint16 len, IN bc_uint16 resid)
{
	bc_uint32 csum = resid;
	/* flag for indicates the len of date to be calculated is odd or even.
	    odd -> 1, even -> 0 */
	bc_uint16 odd = 0; 

	if (len & 1) 
		odd = 1;

	/* len divide by 2 */
	for (len = len >> 1; len > 0; len--, buf+=2)
	{
		csum += M_MCAST_16_N2H(buf);
	}
	
	if (odd)
	{
		csum += (*buf << 8) & 0xff00;
	}

	/* take care of 1's complement ??? */
	csum = (csum & 0xffff) + (csum >> 16);
	csum = (csum & 0xffff) + (csum >> 16);
	if (csum == 0xffff)
		csum = 0;
	
	return (bc_uint16)csum;
}

bc_boolean __mcast_pkt_checksum(IN bc_uint8 *buf, IN bc_uint16 buf_len, IN bc_uint16 check_sum_off)
{
	bc_uint16 csum = 0;

	M_MCAST_16_H2N(csum, buf+check_sum_off);
	csum = __checksum(buf, buf_len, 0);
	M_MCAST_16_H2N(~csum, buf+check_sum_off);

	return TRUE;
}


static bc_boolean __mcast_pkt_valid_checksum(IN bc_uint8 *buf, IN bc_uint16 buf_len, IN bc_uint16 check_sum_off)
{
	bc_uint16 csum = 0;

	csum = __checksum(buf, buf_len, 0);
	return (csum == 0) ? TRUE : FALSE;
}


#endif
#if 1

static bc_uint16 __mcast_pkt_eth_hdr_decode(IN bc_uint8 *eth_hdr, OUT mcast_pkt_eth_t *eth)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	bc_uint16 eth_hdr_len = 14;	/* dst mac + src mac + type */
#if 0
	int idx;
	for (idx = 0; idx < 20; idx++)
	{
		fprintf(stderr, "[%s, %d] - %x \n", __FILE__, __LINE__, (bc_uint8)eth_hdr[idx]);
	}
#endif
	memcpy(eth->dst_mac, eth_hdr, 6);
	memcpy(eth->src_mac, eth_hdr+6, 6);
	eth_hdr += 12;

	if (eth_hdr[0] == 0x81 && eth_hdr[1] == 0x00)
	{
		eth_hdr += 2;
		eth->cvlan.type = 0x8100;
		eth->cvlan.prio = (eth_hdr[0] & 0xe0) >> 5;
		eth->cvlan.vlan_id = ((eth_hdr[0] & 0x1F) << 8) + eth_hdr[1];
		
		eth_hdr += 2;
		eth_hdr_len += 4;
	}

	eth->type = (eth_hdr[0] << 8) + eth_hdr[1];

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return eth_hdr_len;
}


static bc_uint16 __mcast_pkt_ip_hdr_decode(IN bc_uint8* ip_hdr, OUT mcast_pkt_ip_t *ip)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	memcpy(ip, ip_hdr, 20);
	ip->tot_len = M_MCAST_16_N2H(ip_hdr+2);
	ip->id = M_MCAST_16_N2H(ip_hdr+4);
	ip->src_ip = M_MCAST_32_N2H(ip_hdr+12);
	ip->dst_ip = M_MCAST_32_N2H(ip_hdr+16);

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return (ip->ver_ihl & 0x0F)*4;
}

#define M_MCAST_PBC_IGMP_MAX_RESP_TIME(mrt)	(((mrt) < 128) ? \
			(mrt) : ((((mrt) & 0x0F) | 0x10) << ((((mrt) & 0x70) >> 4) + 3)))

#define M_MCAST_PBC_IGMP_QQIC(qqic)	(((qqic) < 128) ? \
			(qqic) : ((((qqic) & 0x0F) | 0x10) << ((((qqic) & 0x70) >> 4) + 3)))

static mcast_ret_code __mcast_pkt_igmp_query_decode(
	IN bc_uint8 *igmp_hdr_buf, 
	IN bc_uint16 igmp_len, 
	OUT mcast_pkt_igmp_query_t *query)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
//	bc_uint16 check_sum;
	bc_uint16 i;

	if (igmp_hdr_buf[0] != MCAST_PBC_TYPE_QUERY)
		MCAST_RET_ERR(MCAST_MODULE_PBC, MCAST_RET_ERR_PBCINFO, TRUE);

//	check_sum = (igmp_hdr_buf[2] << 8) | igmp_hdr_buf[3];
	if (__mcast_pkt_valid_checksum(igmp_hdr_buf, igmp_len, 2) == FALSE)
		MCAST_RET_ERR(MCAST_MODULE_PBC, MCAST_RET_ERR_PBCINFO, TRUE);

	query->max_resp_time = M_MCAST_PBC_IGMP_MAX_RESP_TIME(igmp_hdr_buf[1]);
	query->grp = M_MCAST_32_N2H(igmp_hdr_buf + 4);

	if (igmp_len == 8)	/* general query, group specific query */
	{
		query->query_ver = MCAST_IGMP_V2;
		if (query->max_resp_time == 0)
		{
			query->query_ver = MCAST_IGMP_V1;
			query->max_resp_time = MCAST_QUERY_RESPONSE_INTERVAL;
		}
		
		query->s_flag = 0;
		query->qrv = MCAST_ROBUSTNESS_VARIABLE;
		query->qqic = MCAST_QUERY_INTERVAL;
		query->num_of_src = 0;
		query->src = NULL;
	}
	else		/* group source specific query */
	{
		query->query_ver = MCAST_IGMP_V3;
		query->s_flag = (igmp_hdr_buf[8] & 0x08) >> 3;
		query->qrv = ((igmp_hdr_buf[8] & 0x07) == 0x00) ? MCAST_ROBUSTNESS_VARIABLE : igmp_hdr_buf[8] & 0x07;
		query->qqic = M_MCAST_PBC_IGMP_QQIC(igmp_hdr_buf[9]);
		query->num_of_src = M_MCAST_16_N2H(igmp_hdr_buf+10);
		if (query->num_of_src != 0)
		{
			query->src = (bc_ip*)mcast_alloc(sizeof(bc_ip)*query->num_of_src);
			if (query->src == NULL)
				MCAST_RET_ERR(MCAST_MODULE_PBC, MCAST_RET_ERR_NORES, TRUE);

			for (i = 0; i < query->num_of_src; i++)
			{
				query->src[i] = M_MCAST_32_N2H(igmp_hdr_buf + 12 + i*sizeof(bc_uint32));
			}
		}
	}

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return MCAST_RET_OK;
}

static mcast_ret_code __mcast_pkt_igmp_v1v2_report_decode(
	IN bc_uint16 vid,
	IN bc_uint8 *igmp_hdr_buf, 
	IN bc_uint16 igmp_len, 
	OUT mcast_pkt_igmp_report_t *report)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
//	bc_uint16 check_sum;

	if (igmp_hdr_buf[0] != MCAST_PBC_TYPE_V1_REPORT &&
		igmp_hdr_buf[0] != MCAST_PBC_TYPE_V2_REPORT)
		MCAST_RET_ERR(MCAST_MODULE_PBC, MCAST_RET_ERR_PBCINFO, TRUE);
	
//	check_sum = (igmp_hdr_buf[2] << 8) | igmp_hdr_buf[3];
	if (__mcast_pkt_valid_checksum(igmp_hdr_buf, igmp_len, 2) == FALSE)
		MCAST_RET_ERR(MCAST_MODULE_PBC, MCAST_RET_ERR_PBCINFO, TRUE);

	report->num_of_record = 1;
	report->record = (mcast_pkt_igmp_report_record_t*)mcast_alloc(sizeof(mcast_pkt_igmp_report_record_t));
	if (report->record == NULL)
		MCAST_RET_ERR(MCAST_MODULE_PBC, MCAST_RET_ERR_NORES, TRUE);

	memset(report->record, 0x00, sizeof(mcast_pkt_igmp_report_record_t));
	report->record[0].record_type = MCAST_PBC_RECORD_IS_EXCLUDE;
	report->record[0].grp = M_MCAST_32_N2H(igmp_hdr_buf+4);
	report->record[0].vid = vid;
	report->record[0].num_of_src = 0;
	report->record[0].src = NULL;

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return MCAST_RET_OK;
}

static mcast_ret_code __mcast_pkt_igmp_leave_decode(
	IN bc_uint16 vid,
	IN bc_uint8 *igmp_hdr_buf, 
	IN bc_uint16 igmp_len, 
	OUT mcast_pkt_igmp_report_t *leave)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
//	bc_uint16 check_sum;

	if (igmp_hdr_buf[0] != MCAST_PBC_TYPE_LEAVE)
		MCAST_RET_ERR(MCAST_MODULE_PBC, MCAST_RET_ERR_PBCINFO, TRUE);
	
//	check_sum = (igmp_hdr_buf[2] << 8) | igmp_hdr_buf[3];
	if (__mcast_pkt_valid_checksum(igmp_hdr_buf, igmp_len, 2) == FALSE)
		MCAST_RET_ERR(MCAST_MODULE_PBC, MCAST_RET_ERR_PBCINFO, TRUE);

	leave->num_of_record = 1;
	leave->record = (mcast_pkt_igmp_report_record_t*)mcast_alloc(sizeof(mcast_pkt_igmp_report_record_t));
	if (leave->record == NULL)
		MCAST_RET_ERR(MCAST_MODULE_PBC, MCAST_RET_ERR_NORES, TRUE);

	memset(leave->record, 0x00, sizeof(mcast_pkt_igmp_report_record_t));
	leave->record[0].record_type = MCAST_PBC_RECORD_IS_INCLUDE;
	leave->record[0].grp = M_MCAST_32_N2H(igmp_hdr_buf+4);
	leave->record[0].vid = vid;
	leave->record[0].num_of_src = 0;
	leave->record[0].src = NULL;

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return MCAST_RET_OK;
}

#define M_MCAST_PBC_FREE_RECORD(record, num) \
	do \
	{ \
		bc_int32 i; \
		for (i = 0; i < (num); i++) \
		{ \
			if ((record)[i].src != NULL) \
			{ \
				mcast_free((record)[i].src); \
				(record)[i].src = NULL; \
			} \
		} \
		mcast_free(record); \
		(record) = NULL; \
	}while (0)

static mcast_ret_code __mcast_pkt_igmp_v3_report_decode(
	IN bc_uint16 vid,
	IN bc_uint8 *igmp_hdr_buf, 
	IN bc_uint16 igmp_len, 
	OUT mcast_pkt_igmp_report_t *report)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
//	bc_uint16 check_sum;
	bc_uint16 i;
	bc_uint16 src_idx;
	bc_uint8	*record_p = NULL;
	bc_uint16 record_len = 0;
	bc_uint16 cal_len = 0;

	if (igmp_hdr_buf[0] != MCAST_PBC_TYPE_V3_REPORT)
		MCAST_RET_ERR(MCAST_MODULE_PBC, MCAST_RET_ERR_PBCINFO, TRUE);
	
//	check_sum = (igmp_hdr_buf[2] << 8) | igmp_hdr_buf[3];
	if (__mcast_pkt_valid_checksum(igmp_hdr_buf, igmp_len, 2) == FALSE)
		MCAST_RET_ERR(MCAST_MODULE_PBC, MCAST_RET_ERR_PBCINFO, TRUE);

	report->num_of_record = M_MCAST_16_N2H(igmp_hdr_buf+6);
	report->record = (mcast_pkt_igmp_report_record_t*)mcast_alloc(sizeof(mcast_pkt_igmp_report_record_t)*report->num_of_record);
	if (report->record == NULL)
		MCAST_RET_ERR(MCAST_MODULE_PBC, MCAST_RET_ERR_NORES, TRUE);
	memset(report->record, 0x00, sizeof(mcast_pkt_igmp_report_record_t)*report->num_of_record);

	cal_len = MCAST_PBC_COMMON_LEN;
	record_p = igmp_hdr_buf + MCAST_PBC_COMMON_LEN;
	for (i = 0; i < report->num_of_record; i++)
	{
		if (record_p[0] < MCAST_PBC_RECORD_IS_INCLUDE || MCAST_PBC_RECORD_BLOCK_OLD_SOURCES < record_p[0])
		{
			M_MCAST_PBC_FREE_RECORD(report->record, i);
			MCAST_RET_ERR(MCAST_MODULE_PBC, MCAST_RET_ERR_PBCINFO, TRUE);
		}
		
		report->record[i].record_type = record_p[0];
		report->record[i].num_of_src = M_MCAST_16_N2H(record_p+2);
		report->record[i].grp = M_MCAST_32_N2H(record_p+4);
		report->record[i].vid = vid;
		if (report->record[i].num_of_src != 0)
		{
			report->record[i].src = (bc_ip*)mcast_alloc(sizeof(bc_ip)*(report->record[i].num_of_src));
			if (report->record[i].src == NULL)
			{
				M_MCAST_PBC_FREE_RECORD(report->record, i);
				MCAST_RET_ERR(MCAST_MODULE_PBC, MCAST_RET_ERR_NORES, TRUE);
			}

			for (src_idx = 0; src_idx < report->record[i].num_of_src; src_idx++)
			{
				report->record[i].src[src_idx] = M_MCAST_32_N2H(record_p + 8 + src_idx*sizeof(bc_uint32));
			}
		}
		record_len = 8 + record_p[1] + (report->record[i].num_of_src)*sizeof(bc_uint32);
		record_p += record_len;
		cal_len += record_len;
		if (cal_len > igmp_len)
		{
			M_MCAST_PBC_FREE_RECORD(report->record, i+1);
			MCAST_RET_ERR(MCAST_MODULE_PBC, MCAST_RET_ERR_PBCINFO, TRUE);
		}
	}

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return MCAST_RET_OK;
}

static mcast_ret_code __mcast_pkt_igmp_hdr_decode(
	IN bc_uint16 vid,
	IN bc_uint8 *igmp_hdr_buf, 
	IN bc_uint16 igmp_len, 
	OUT mcast_pkt_igmp_t *igmp)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	mcast_ret_code ret = MCAST_RET_OK;

	igmp->pkt_type = igmp_hdr_buf[0];
	switch (igmp_hdr_buf[0])
	{
	case MCAST_PBC_TYPE_QUERY:
		ret = __mcast_pkt_igmp_query_decode(igmp_hdr_buf, igmp_len, &(igmp->info.query));
		break;
	case MCAST_PBC_TYPE_V1_REPORT:
	case MCAST_PBC_TYPE_V2_REPORT:
		ret = __mcast_pkt_igmp_v1v2_report_decode(vid, igmp_hdr_buf, igmp_len, &(igmp->info.report));
		break;
	case MCAST_PBC_TYPE_LEAVE:
		ret = __mcast_pkt_igmp_leave_decode(vid, igmp_hdr_buf, igmp_len, &(igmp->info.report));
		break;
	case MCAST_PBC_TYPE_V3_REPORT:
		ret = __mcast_pkt_igmp_v3_report_decode(vid, igmp_hdr_buf, igmp_len, &(igmp->info.report));
		break;
	default:
		MCAST_RET_ERR(MCAST_MODULE_PBC, MCAST_RET_ERR_UNTYPE, TRUE); /* silent drop */
		break;
	}

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return ret;
}

mcast_ret_code mcast_pkt_igmp_decode(
	IN bc_uint16 vid,
	IN bc_uint8 *buf, 
	IN bc_uint16 buf_len, 
	OUT mcast_pkt_igmp_t *igmp)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	bc_uint16 eth_hdr_len;
	bc_uint16 ip_hdr_len;
	bc_uint16 igmp_len;

	mcast_ret_code ret;

	if (MCAST_PBC_LEN_MAX < buf_len)
		MCAST_RET_ERR(MCAST_MODULE_PBC, MCAST_RET_ERR_PAR, TRUE);
	eth_hdr_len = __mcast_pkt_eth_hdr_decode(buf, &(igmp->eth_hdr));

	if (igmp->eth_hdr.type != 0x0800)
		MCAST_RET_ERR(MCAST_MODULE_PBC, MCAST_RET_ERR_PAR, TRUE);

	buf += eth_hdr_len;
	ip_hdr_len = __mcast_pkt_ip_hdr_decode(buf, &(igmp->ip_hdr));
	if (__mcast_pkt_valid_checksum(buf, ip_hdr_len, 10) == FALSE)
		MCAST_RET_ERR(MCAST_MODULE_PBC, MCAST_RET_ERR_PBCINFO, TRUE);
	if (((igmp->ip_hdr.ver_ihl & 0xF0) >> 4) != MCAST_PBC_IPv4_VER)
		MCAST_RET_ERR(MCAST_MODULE_PBC, MCAST_RET_ERR_PBCINFO, TRUE);

	if (igmp->ip_hdr.pro != MCAST_PBC_IP_PRO_IGMP || igmp->ip_hdr.ttl != 1)
		MCAST_RET_ERR(MCAST_MODULE_PBC, MCAST_RET_ERR_PBCINFO, TRUE);

	buf += ip_hdr_len;
	igmp_len = igmp->ip_hdr.tot_len - ip_hdr_len;

	if ((ret = __mcast_pkt_igmp_hdr_decode(vid, buf, igmp_len, igmp)) != MCAST_RET_OK)
		return ret;

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return MCAST_RET_OK;
}


void mcast_pkt_decode_node_free(INOUT mcast_pkt_igmp_t *igmp)
{
	bc_uint32 record_idx;

	if (!igmp)
		return ;

	if (igmp->pkt_type == MCAST_PBC_TYPE_QUERY)
	{
		if (igmp->info.query.src)
			mcast_free(igmp->info.query.src);
	}
	else if (igmp->pkt_type == MCAST_PBC_TYPE_V1_REPORT
		|| igmp->pkt_type == MCAST_PBC_TYPE_V2_REPORT
		|| igmp->pkt_type == MCAST_PBC_TYPE_LEAVE
		|| igmp->pkt_type == MCAST_PBC_TYPE_V3_REPORT)
	{
		for (record_idx = 0; record_idx < igmp->info.report.num_of_record; record_idx++)
		{
			if (igmp->info.report.record[record_idx].src)
				mcast_free(igmp->info.report.record[record_idx].src);
		}

		if (igmp->info.report.record)
			mcast_free(igmp->info.report.record);
	}
	else
	{
		/* unknow type, don't care */
	}
}


#endif
#if 1

static bc_uint16 __mcast_pkt_eth_hdr_encode(IN mcast_pkt_eth_t *eth_hdr, OUT bc_uint8 *eth_buf)
{
	bc_uint16 actual_len = 14;

	memcpy(eth_buf, eth_hdr->dst_mac, 6);
	eth_buf += 6;
	
	memcpy(eth_buf, eth_hdr->src_mac, 6);
	eth_buf += 6;
	
	if (eth_hdr->svlan.vlan_id != 0)
	{
		actual_len += 4;

		M_MCAST_16_H2N(eth_hdr->svlan.type, eth_buf);
		eth_buf += 2;

		eth_buf[0] = (eth_hdr->svlan.prio & 0x07) << 5;
		eth_buf[0] |= (bc_uint8)((eth_hdr->svlan.vlan_id & 0x1F00) >> 8);
		eth_buf[1] = (bc_uint8)(eth_hdr->svlan.vlan_id & 0x00FF);
		eth_buf += 2;
	}
#if 0
	if (eth_hdr->cvlan.vlan_id != 0)
	{
		actual_len += 4;

		M_MCAST_16_H2N(eth_hdr->cvlan.type, eth_buf);
		eth_buf += 2;

		eth_buf[0] = (eth_hdr->cvlan.prio & 0x07) << 5;
		eth_buf[0] |= (bc_uint8)((eth_hdr->cvlan.vlan_id & 0x1F00) >> 8);
		eth_buf[1] = (bc_uint8)(eth_hdr->cvlan.vlan_id & 0x00FF);
		eth_buf += 2;
	}
#endif
	M_MCAST_16_H2N(eth_hdr->type, eth_buf);
	eth_buf += 2;
	
	return actual_len;
}

static bc_uint16 __mcast_pkt_ip_hdr_encode(IN mcast_pkt_ip_t *ip_hdr, OUT bc_uint8 *ip_buf)
{
	bc_uint16 actual_len = 20;

	ip_buf[0] = MCAST_PBC_IPv4_VER << 4;			/* Version */

	ip_buf[1] = ip_hdr->tos;						/* Type of Service */

	M_MCAST_16_H2N(0, ip_buf+2);				/* total length, temp use 0 */
	
	M_MCAST_16_H2N(ip_hdr->id, ip_buf+4); 		/* Identification */
	M_MCAST_16_H2N(ip_hdr->frag_off, ip_buf+6);	/* Flags+Fragment Offset */

	ip_buf[8] = ip_hdr->ttl; 						/* TTL */
	ip_buf[9] = MCAST_PBC_IP_PRO_IGMP; 			/* protocol */

	M_MCAST_16_H2N(0, ip_buf+10);				/* check sum, tmp use 0 */

	M_MCAST_32_H2N(ip_hdr->src_ip, ip_buf+12);
	M_MCAST_32_H2N(ip_hdr->dst_ip, ip_buf+16);

	/* we SHOULD add option */

	ip_buf[0] |= (actual_len / 4);					/* IHL */
	
	return actual_len;
}

#define M_MCAST_PBC_IGMP_CAL_TIME(time, value)		\
		do	\
		{	\
			bc_uint8 i = 0;	\
			if (time < 128)	\
			{	\
				value = time;	\
			}	\
			else	\
			{	\
				while (time & 0xFFE0)	\
				{	\
					time = time >> 1;	\
					i++;	\
				}	\
				if (i > 3)	\
					i -= 3;	\
				value = ((bc_uint8)(time & 0x000F)) | ((i << 4) & 0x70) | 0x80;	\
			}	\
		} while(0)
		
/*
4.1. Membership Query Message

0 					1 					2 					3
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| Type = 0x11 | Max Resp Code | 			Checksum 			|
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| 							Group Address 						|
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| Resv |S| QRV| 	QQIC 	  | 	Number of Sources (N) 		|
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| 						Source Address [1] 						|
+- 															   -+
| 						Source Address [2] 						|
+- 								. 							   -+
. 								. 								.
. 								. 								.
+- 															   -+
| 						Source Address [N] 						|
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*/
static mcast_ret_code __mcast_pkt_igmp_query_encode(
	IN mcast_pkt_igmp_query_t *query, 
	INOUT bc_uint16 *buf_len, 
	OUT bc_uint8 *buf)
{
	bc_uint16 actual_len = MCAST_PBC_COMMON_LEN;
	bc_uint16 i = 0;

	if (*buf_len < MCAST_PBC_COMMON_LEN)
		MCAST_RET_ERR(MCAST_MODULE_PBC, MCAST_RET_ERR_PAR, TRUE);

	buf[0] = MCAST_PBC_TYPE_QUERY;
	M_MCAST_PBC_IGMP_CAL_TIME(query->max_resp_time, buf[1]);

	M_MCAST_32_H2N(query->grp ,buf+4);

	if (query->query_ver == MCAST_IGMP_V3)
	{
		actual_len += query->num_of_src*sizeof(bc_uint32) + 4;
		if (*buf_len < actual_len)
			MCAST_RET_ERR(MCAST_MODULE_PBC, MCAST_RET_ERR_PAR, TRUE);

		buf[8] = (((query->s_flag ? 1 : 0) << 3) & 0x08) | (query->qrv & 0x07);
		M_MCAST_PBC_IGMP_CAL_TIME(query->qqic, buf[9]);

		M_MCAST_16_H2N(query->num_of_src, buf+10);
		for (i = 0; i < query->num_of_src; i++)
		{
			M_MCAST_32_H2N(query->src[i], buf + 12 + i*sizeof(bc_uint32));
		}
	}

	__mcast_pkt_checksum(buf, actual_len, 2);

	*buf_len = actual_len;
	return MCAST_RET_OK;
}

/*
0 					1 					2 					3
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| Type 		  | Max Resp Time | 			Checksum 			|
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| 							Group Address 						|
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*/
static mcast_ret_code __mcast_pkt_igmp_v1v2_report_encode(
	IN mcast_pkt_type_e report_type,
	IN mcast_pkt_igmp_report_t *report,
	INOUT bc_uint16 *buf_len,
	OUT bc_uint8 *buf)
{
	if (*buf_len < MCAST_PBC_COMMON_LEN)
		MCAST_RET_ERR(MCAST_MODULE_PBC, MCAST_RET_ERR_PAR, TRUE);

	buf[0] = report_type;	
	buf[1] = 0;

	if (report->num_of_record != 1)
		return FALSE;

	M_MCAST_32_H2N(report->record->grp, buf+4);

	__mcast_pkt_checksum(buf, MCAST_PBC_COMMON_LEN, 2);
	*buf_len = MCAST_PBC_COMMON_LEN;
	return MCAST_RET_OK;
}

/*
0 					1 					2 					3
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| Type 		  | Max Resp Time | 			Checksum 			|
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| 							Group Address 						|
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*/
static mcast_ret_code __mcast_pkt_igmp_leave_encode(
	IN mcast_pkt_igmp_report_t *leave,
	INOUT bc_uint16 *buf_len,
	OUT bc_uint8 *buf)
{
	if (*buf_len < MCAST_PBC_COMMON_LEN)
		MCAST_RET_ERR(MCAST_MODULE_PBC, MCAST_RET_ERR_PAR, TRUE);

	buf[0] = MCAST_PBC_TYPE_LEAVE;
	buf[1] = 0;

	if (leave->num_of_record != 1)
		MCAST_RET_ERR(MCAST_MODULE_PBC, MCAST_RET_ERR_PAR, TRUE);

	M_MCAST_32_H2N(leave->record->grp, buf+4);

	__mcast_pkt_checksum(buf, MCAST_PBC_COMMON_LEN, 2);
	*buf_len = MCAST_PBC_COMMON_LEN;
	return MCAST_RET_OK;
}

/*
4.2. Version 3 Membership Report Message

0 					1 					2 					3
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| Type = 0x22 | 	Reserved | 				Checksum 			|
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| 			Reserved 		 | 	Number of Group Records (M) 	|
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| 																|
. 																.
. 						Group Record [1] 						.
. 																.
| 																|
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| 																|
. 																.
. 						Group Record [2] 						.
. 																.
| 																|
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| 																|
. 																.
| 																|
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| 																|
. 																.
. 						Group Record [M] 						.
. 																.
| 																|
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

where each Group Record has the following internal format:

+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| Record Type | Aux Data Len | 		Number of Sources (N) 		|
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| 						Multicast Address 						|
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| 						Source Address [1] 						|
+- 															   -+
| 						Source Address [2] 						|
+- 															   -+
. 								. 								.
+- 															   -+
| 						Source Address [N] 						|
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| 																|
. 						Auxiliary Data 							.
| 																|
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+


*/
static mcast_ret_code __mcast_pkt_igmp_v3_report_encode(
	IN mcast_pkt_igmp_report_t *report,
	INOUT bc_uint16 *buf_len,
	OUT bc_uint8 *buf)
{
	bc_uint16 actual_len = MCAST_PBC_COMMON_LEN;
	bc_uint16 i;
	bc_uint16 record_off = 0;
	bc_uint16 src_idx = 0;

	if (*buf_len < MCAST_PBC_COMMON_LEN)
		MCAST_RET_ERR(MCAST_MODULE_PBC, MCAST_RET_ERR_PAR, TRUE);

	buf[0] = MCAST_PBC_TYPE_V3_REPORT;
	buf[1] = 0;

	buf[4] = buf[5] = 0; /* resv */
	
	if (report->num_of_record < 1)
		MCAST_RET_ERR(MCAST_MODULE_PBC, MCAST_RET_ERR_PAR, TRUE);
	M_MCAST_16_H2N(report->num_of_record, buf+6);

	for (i = 0; i < report->num_of_record; i++)
	{
		record_off = actual_len;
		actual_len += 8 + (report->record[i].num_of_src * sizeof(bc_uint32));
		if (actual_len > *buf_len)
			MCAST_RET_ERR(MCAST_MODULE_PBC, MCAST_RET_ERR_PAR, TRUE);

		buf[record_off] = report->record[i].record_type;
		buf[record_off+1] = 0;
		M_MCAST_16_H2N(report->record[i].num_of_src, buf+record_off+2);
		M_MCAST_32_H2N(report->record[i].grp, buf+record_off+4);
		for (src_idx = 0; src_idx < report->record[i].num_of_src; src_idx++)
		{
			M_MCAST_32_H2N(report->record[i].src[src_idx], buf+record_off+8+src_idx*sizeof(bc_uint32));
		}
	}

	__mcast_pkt_checksum(buf, actual_len, 2);
	*buf_len = actual_len;
	return MCAST_RET_OK;
}


static mcast_ret_code __mcast_pkt_igmp_hdr_encode(IN mcast_pkt_igmp_t *igmp, INOUT bc_uint16 *buf_len, OUT bc_uint8 *igmp_buf)
{
	mcast_ret_code ret = MCAST_RET_OK;

	switch(igmp->pkt_type)
	{
	case MCAST_PBC_TYPE_QUERY:
		ret = __mcast_pkt_igmp_query_encode(&(igmp->info.query), buf_len, igmp_buf);
		break;
	case MCAST_PBC_TYPE_V1_REPORT:
	case MCAST_PBC_TYPE_V2_REPORT:
		ret = __mcast_pkt_igmp_v1v2_report_encode(igmp->pkt_type, &(igmp->info.report), buf_len, igmp_buf);
		break;
	case MCAST_PBC_TYPE_LEAVE:
		ret = __mcast_pkt_igmp_leave_encode(&(igmp->info.report), buf_len, igmp_buf);
		break;
	case MCAST_PBC_TYPE_V3_REPORT:
		ret = __mcast_pkt_igmp_v3_report_encode(&(igmp->info.report), buf_len, igmp_buf);
		break;
	default:
		MCAST_RET_ERR(MCAST_MODULE_PBC, MCAST_RET_ERR_UNTYPE, TRUE);
		break;
	}

	return ret;
}

mcast_ret_code mcast_pkt_igmp_encode(
	IN mcast_pkt_igmp_t *igmp, 
	OUT bc_uint8 *buf, 
	INOUT bc_uint16 *buf_len)
{
	bc_uint16 eth_hdr_len;
	bc_uint16 ip_hdr_len;
	bc_uint16 igmp_len;

	mcast_ret_code ret = MCAST_RET_OK;

	eth_hdr_len = __mcast_pkt_eth_hdr_encode(&(igmp->eth_hdr), buf);
	if (eth_hdr_len >= *buf_len)
		MCAST_RET_ERR(MCAST_MODULE_PBC, MCAST_RET_ERR_PAR, TRUE);

	buf += eth_hdr_len;
	ip_hdr_len = __mcast_pkt_ip_hdr_encode(&(igmp->ip_hdr), buf);
	if (eth_hdr_len + ip_hdr_len >= *buf_len)
		MCAST_RET_ERR(MCAST_MODULE_PBC, MCAST_RET_ERR_PAR, TRUE);

	buf += ip_hdr_len;
	igmp_len = *buf_len - (eth_hdr_len + ip_hdr_len);
	if ((ret = __mcast_pkt_igmp_hdr_encode(igmp, &igmp_len, buf)) != MCAST_RET_OK)
		return ret;

	if (eth_hdr_len + ip_hdr_len + igmp_len > *buf_len)
	{
		MCAST_RET_ERR(MCAST_MODULE_PBC, MCAST_RET_ERR_PAR, TRUE);
	}
	else
		*buf_len = eth_hdr_len + ip_hdr_len + igmp_len;

	/* put actual total length in ip header */
	M_MCAST_16_H2N(ip_hdr_len+igmp_len, buf-ip_hdr_len+2);
	/* calculate ip header checksum */
	__mcast_pkt_checksum(buf-ip_hdr_len, ip_hdr_len, 10);

	return MCAST_RET_OK;
}

#endif
#endif

