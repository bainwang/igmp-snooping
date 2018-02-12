/*******************************************************************************
  [File name]	: mcast_cfg.h
  [Author]     	: bain.wang@outlook.com
  [Version]    	: 1.0
  [Date]       	: 2017-06-13
  [Description]	:
	Multicast module configure information
  [Others]     	:
	NULL
  [Function List]:  
    1. ....
    2. ....
  [History]:
	 D a t e      	Modification 							 Initials
	---------- 	--------------                                        ----------
	2017-06-13  	Created								 bain.wang@outlook.com
*******************************************************************************/

#ifndef __mcast_cfg_h__
#define __mcast_cfg_h__

#include "mcast_def.h"
#include "mcast_utl.h"

#if BC_MULTICAST_INCLUDE
#if 1

typedef struct {
	bc_boolean		enable;
	mcast_mode_e	mode;
	mcast_igmp_version_e	igmp_version;

	/* protocol parameters */
	bc_uint16   robustness;			/* 8.1. Robustness Variable */
	bc_uint16   query_interval;			/* 8.2. Query Interval */
	bc_uint16   query_rsp_interval;	/* 8.3. Query Response Interval */
	bc_uint16   member_interval;		/* 8.4. Group Membership Interval */
	
	bc_uint16	  other_querier_present_interval; /* 8.5. Other Querier Present Interval */

	bc_uint16   startup_query_interval; /* 8.6. Startup Query Interval */
	bc_uint16   startup_query_count;	/* 8.7. Startup Query Count */

	bc_uint16   last_member_query_interval; /* 8.8. Last Member Query Interval */
	bc_uint16   last_member_query_count; 	/* 8.9. Last Member Query Count */
	bc_uint16   last_member_query_time; 	/* 8.10. Last Member Query Time */

	bc_uint16	  unsolicited_report_interval;	/* 8.11. Unsolicited Report Interval */
	bc_uint16   older_ver_querier_present_timeout; /* 8.12. Older Version Querier Present Timeout */
	bc_uint16	  older_host_present_interval; /* 8.13. Older Host Present Interval */
} mcast_cfg_t;

void mcast_cfg_get(OUT mcast_cfg_t *mcast_cfg);

bc_boolean mcast_cfg_set_state(IN bc_boolean en);
bc_boolean mcast_cfg_set_query_rsp_interval(IN bc_uint16 query_rsp_interval);
bc_boolean mcast_cfg_set_robustness(IN bc_uint16 robustness);
bc_boolean mcast_cfg_set_query_interval(IN bc_uint16 query_interval);
bc_boolean mcast_cfg_set_last_member_query_interval(IN bc_uint16 last_member_query_interval);
bc_boolean mcast_cfg_set_last_member_query_count(IN bc_uint16 last_member_query_count);
bc_boolean mcast_cfg_set_igmp_version(IN mcast_igmp_version_e ver);
bc_boolean mcast_cfg_set_mode(IN mcast_mode_e mode);
bc_boolean mcast_cfg_get_mode(OUT mcast_mode_e *mode);

/* The API can't be used except debug */
void mcast_cfg_dbg_dump(void);

#endif
#if 1

typedef enum {
	MCAST_NONE_ROUTER_PORT = 0x00,
	MCAST_DYNAMIC_ROUTER_PORT = 0x01,
	MCAST_STATIC_ROUTER_PORT = 0x02
} mcast_router_port_e;

typedef struct {
	/* rx */
	bc_uint64     in_igmp_query;
	bc_uint64     in_igmpv1_report;
	bc_uint64     in_igmpv2_report;
	bc_uint64     in_igmpv2_leave;
	bc_uint64     in_igmpv3_report;

	/* tx */
	bc_uint64     out_igmp_query;
	bc_uint64     out_igmpv1_report;
	bc_uint64     out_igmpv2_report;
	bc_uint64     out_igmpv2_leave;
	bc_uint64     out_igmpv3_report;
} mcast_port_stats_t;

typedef struct {
	bc_port_index_t		port_id;
	bc_boolean 			en;
	mcast_router_port_e	router_port;
	bc_uint16				dyn_tic;
	
	mcast_port_stats_t 	stats;
} mcast_up_port_node_t;

typedef struct {
	bc_port_index_t	port_id;
	bc_boolean		en;
	
	mcast_port_stats_t		stats;
} mcast_down_port_node_t;

typedef struct {
	bc_uint8	up_port_num;
	mcast_up_port_node_t up_port[BC_PORT_SNI_MAX_COUNT];

	bc_uint8 	down_port_num;
	mcast_down_port_node_t down_port[BC_PORT_PON_MAX_COUNT];
} mcast_port_t;

void mcast_port_get_up_ports(OUT mcast_up_port_node_t *up_ports);
void mcast_port_get_up_port(IN bc_port_index_t port, OUT mcast_up_port_node_t *up_port);
void mcast_port_update_up_ports(IN mcast_up_port_node_t *up_ports);
void mcast_port_update_up_rt_port(IN bc_port_index_t port, IN mcast_router_port_e rt_type, IN bc_uint16 sec);
void mcast_port_update_up_port_state(IN bc_port_index_t port, IN bc_boolean state);

void mcast_port_get_down_ports(OUT mcast_down_port_node_t *down_ports);
void mcast_port_get_down_port(IN bc_port_index_t port, OUT mcast_down_port_node_t *down_port);
void mcast_port_update_down_port_state(IN bc_port_index_t port, IN bc_boolean state);

/* The API can't be used except debug */
void mcast_cfg_port_dbg_dump(void);

/* The API can't be used except debug */
void mcast_cfg_port_stats_dbg_dump(void);

#endif
#if 1

typedef struct {
	bc_uint16		vid;

	bc_port_index_t	sni_port[BC_PORT_SNI_MAX_COUNT];
	bc_port_index_t epon_port[BC_PORT_PON_MAX_COUNT];
} mcast_vlan_t;

bc_boolean mcast_vlan_add(IN mcast_vlan_t *vlan);
bc_boolean mcast_vlan_del(IN bc_uint16 vid);
bc_boolean mcast_vlan_get(INOUT mcast_vlan_t *vlan);
bc_boolean mcast_vlan_get_next(IN bc_int16 in_vid, OUT bc_int16 *out_vid);
bc_boolean mcast_vlan_create_rule_check(IN bc_uint16 vid);
/* the API only used when system work in the multi vlan mode */
bc_boolean mcast_vlan_get_continue_vlan(OUT bc_uint16 *start_vid, OUT bc_uint16 *num);

/* The API can't be used except debug */
void mcast_cfg_vlan_dbg_dump(void);

#endif
#if 1
void mcast_cfg_def(void);

void mcast_cfg_init(void);

#endif
#endif
#endif

