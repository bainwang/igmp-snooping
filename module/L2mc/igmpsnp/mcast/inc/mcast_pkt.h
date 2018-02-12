/*******************************************************************************
  [File name]	: mcast_pkt.h
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

#ifndef __mcast_pkt_h__
#define __mcast_pkt_h__

#include "mcast_def.h"
#include "mcast_utl.h"

#if BC_MULTICAST_INCLUDE

#define MCAST_PBC_LEN_MIN 		64
#define MCAST_PBC_LEN_MAX		1518	

#define MCAST_PBC_IPv4_VER	4
#define MCAST_PBC_IP_PRO_IGMP 	2

#define MCAST_PBC_COMMON_LEN	8

typedef struct {
	bc_uint16	type;
	bc_uint8	prio;
	bc_uint16 vlan_id;
} mcast_pkt_vlan_t;

typedef struct {
	bc_mac	dst_mac;
	bc_mac	src_mac;
	bc_uint16 type;

	mcast_pkt_vlan_t	svlan;	/* if no exist, vid equal 0 */
	mcast_pkt_vlan_t	cvlan;
} mcast_pkt_eth_t;

#pragma pack(push)
#pragma pack(1)

typedef struct {
	bc_uint8 	ver_ihl;
	bc_uint8	tos;
	bc_uint16	tot_len;
	bc_uint16	id;
	bc_uint16 frag_off;
	bc_uint8	ttl;
	bc_uint8	pro;
	bc_uint16	check_sum;
	bc_uint32	src_ip;
	bc_uint32 dst_ip;
} mcast_pkt_ip_t;

#pragma pack(pop)

typedef enum {
	MCAST_PBC_TYPE_QUERY			= 0x11,
		
	MCAST_PBC_TYPE_V1_REPORT 	= 0x12,
	MCAST_PBC_TYPE_V2_REPORT 	= 0x16,
	MCAST_PBC_TYPE_LEAVE			= 0x17,
	MCAST_PBC_TYPE_V3_REPORT	= 0x22
} mcast_pkt_type_e;

typedef enum {
	MCAST_PBC_RECORD_IS_INCLUDE				= 0x01,
	MCAST_PBC_RECORD_IS_EXCLUDE				= 0x02,
	MCAST_PBC_RECORD_CHANGE_TO_INCLUDE	= 0x03,
	MCAST_PBC_RECORD_CHANGE_TO_EXCLUDE	= 0x04,
	MCAST_PBC_RECORD_ALLOW_NEW_SOURCES	= 0x05,
	MCAST_PBC_RECORD_BLOCK_OLD_SOURCES	= 0x06
} mcast_pkt_record_type_e;


typedef enum {
	MCAST_PBC_QUERY_GEN 		= 0x00,
	MCAST_PBC_QUERY_GRP 		= 0x01,
	MCAST_PBC_QUERY_SRC_GRP	= 0x02
} mcast_pkt_query_e;


typedef struct {
	mcast_igmp_version_e	query_ver;
	bc_uint16		max_resp_time;
	bc_ip		grp;
	bc_boolean	s_flag;  	/* Suppress Router-Side Processing */
	bc_uint8		qrv;		/* Querier's Robustness Variable */
	bc_uint16		qqic;	/* Querier's Query Interval Code */
	bc_uint16		num_of_src;
	bc_ip		*src;
} mcast_pkt_igmp_query_t;

typedef struct {
	mcast_pkt_record_type_e	record_type;
	bc_ip		grp;
	bc_uint16	vid;
	bc_uint16		num_of_src;
	bc_ip		*src;
} mcast_pkt_igmp_report_record_t;

typedef struct {
	bc_uint16		num_of_record;
	mcast_pkt_igmp_report_record_t	*record;
} mcast_pkt_igmp_report_t;

typedef struct {
	mcast_pkt_eth_t	eth_hdr;
	mcast_pkt_ip_t	ip_hdr;

	mcast_pkt_type_e 		pkt_type;
	union {
		mcast_pkt_igmp_query_t 	query;
		mcast_pkt_igmp_report_t 	report;
	} info;

#define qy	info.query
#define rept	info.report
#define recd 	info.report.record
} mcast_pkt_igmp_t;


mcast_ret_code mcast_pkt_igmp_decode(
	IN bc_uint16 vid,
	IN bc_uint8 *buf, 
	IN bc_uint16 buf_len, 
	OUT mcast_pkt_igmp_t *igmp);

void mcast_pkt_decode_node_free(INOUT mcast_pkt_igmp_t *igmp);


mcast_ret_code mcast_pkt_igmp_encode(
	IN mcast_pkt_igmp_t *igmp, 
	OUT bc_uint8 *buf, 
	INOUT bc_uint16 *buf_len);


#endif
#endif

