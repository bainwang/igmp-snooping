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

#include "mcast_cfg.h"

#if BC_MULTICAST_INCLUDE

#if 1

static mcast_cfg_t mcast_cfg_db;

void mcast_cfg_get(OUT mcast_cfg_t *mcast_cfg)
{
	memcpy(mcast_cfg, &mcast_cfg_db, sizeof(mcast_cfg_t));
}

bc_boolean mcast_cfg_set_state(IN bc_boolean en)
{
	mcast_cfg_db.enable = en ? TRUE : FALSE;
	return TRUE;
}

bc_boolean mcast_cfg_set_query_rsp_interval(IN bc_uint16 query_rsp_interval)
{
	if (query_rsp_interval < MCAST_MAX_RESP_TIME_MIN || MCAST_MAX_RESP_TIME_MAX < query_rsp_interval)
		return FALSE;

	if (query_rsp_interval > mcast_cfg_db.query_interval)
		return FALSE;

	mcast_cfg_db.query_rsp_interval 	= query_rsp_interval;
	mcast_cfg_db.member_interval 		= (mcast_cfg_db.robustness * mcast_cfg_db.query_interval) + mcast_cfg_db.query_rsp_interval;
	mcast_cfg_db.other_querier_present_interval 	= (mcast_cfg_db.robustness * mcast_cfg_db.query_interval) 
											+ (mcast_cfg_db.query_rsp_interval / 2);
	
	mcast_cfg_db.older_ver_querier_present_timeout = (mcast_cfg_db.robustness * mcast_cfg_db.query_interval) + mcast_cfg_db.query_rsp_interval;
	mcast_cfg_db.older_host_present_interval 	= (mcast_cfg_db.robustness * mcast_cfg_db.query_interval) + mcast_cfg_db.query_rsp_interval;

	return TRUE;
}


bc_boolean mcast_cfg_set_robustness(IN bc_uint16 robustness)
{
	if (robustness < MCAST_ROBUSTNESS_MIN || MCAST_ROBUSTNESS_MAX < robustness)
		return FALSE;

	mcast_cfg_db.robustness 		= robustness;
	mcast_cfg_db.member_interval 	= (mcast_cfg_db.robustness * mcast_cfg_db.query_interval) + mcast_cfg_db.query_rsp_interval;
	mcast_cfg_db.other_querier_present_interval 	= (mcast_cfg_db.robustness * mcast_cfg_db.query_interval) 
											+ (mcast_cfg_db.query_rsp_interval / 2);
	
	mcast_cfg_db.startup_query_count 		= mcast_cfg_db.robustness;

	mcast_cfg_db.older_ver_querier_present_timeout = (mcast_cfg_db.robustness * mcast_cfg_db.query_interval) + mcast_cfg_db.query_rsp_interval;
	mcast_cfg_db.older_host_present_interval 	= (mcast_cfg_db.robustness * mcast_cfg_db.query_interval) + mcast_cfg_db.query_rsp_interval;

	return TRUE;
}


bc_boolean mcast_cfg_set_query_interval(IN bc_uint16 query_interval)
{
	if (query_interval < MCAST_QUERY_INTERVAL_MIN || MCAST_QUERY_INTERVAL_MAX < query_interval)
		return FALSE;

	if (query_interval < mcast_cfg_db.query_rsp_interval)
		return FALSE;

	mcast_cfg_db.query_interval 	= query_interval;
	mcast_cfg_db.member_interval 	= (mcast_cfg_db.robustness * mcast_cfg_db.query_interval) + mcast_cfg_db.query_rsp_interval;
	mcast_cfg_db.other_querier_present_interval 	= (mcast_cfg_db.robustness * mcast_cfg_db.query_interval) 
											+ (mcast_cfg_db.query_rsp_interval / 2);

	mcast_cfg_db.startup_query_interval	= mcast_cfg_db.query_interval / 4;
	mcast_cfg_db.older_ver_querier_present_timeout = (mcast_cfg_db.robustness * mcast_cfg_db.query_interval) + mcast_cfg_db.query_rsp_interval;
	mcast_cfg_db.older_host_present_interval 	= (mcast_cfg_db.robustness * mcast_cfg_db.query_interval) + mcast_cfg_db.query_rsp_interval;

	return TRUE;
}


bc_boolean mcast_cfg_set_last_member_query_interval(IN bc_uint16 last_member_query_interval)
{
	if (last_member_query_interval < MCAST_LAST_MEMBER_QUERY_INTERVAL_MIN || 
		MCAST_LAST_MEMBER_QUERY_INTERVAL_MAX < last_member_query_interval)
		return FALSE;

	if (last_member_query_interval > mcast_cfg_db.query_interval)
		return FALSE;

	mcast_cfg_db.last_member_query_interval 	= last_member_query_interval;
	mcast_cfg_db.last_member_query_time 		= mcast_cfg_db.last_member_query_interval * mcast_cfg_db.last_member_query_count;

	return TRUE;
}


bc_boolean mcast_cfg_set_last_member_query_count(IN bc_uint16 last_member_query_count)
{
	if (last_member_query_count < MCAST_LAST_MEMBER_QUERY_COUNT_MIN || 
		MCAST_LAST_MEMBER_QUERY_COUNT_MAX < last_member_query_count)
		return FALSE;

	mcast_cfg_db.last_member_query_count 	= last_member_query_count;
	mcast_cfg_db.last_member_query_time 	= mcast_cfg_db.last_member_query_interval * mcast_cfg_db.last_member_query_count;

	return TRUE;
}


bc_boolean mcast_cfg_set_igmp_version(IN mcast_igmp_version_e ver)
{
	if (ver < MCAST_IGMP_V1 || MCAST_IGMP_V3 < ver)
		return FALSE;

	mcast_cfg_db.igmp_version = ver;
	return TRUE;
}


bc_boolean mcast_cfg_set_mode(IN mcast_mode_e mode)
{
	if (mode < MCAST_MODE_CENTRALIZED || MCAST_MODE_DISTRIBUTEDWOCM < mode)
		return FALSE;

	igmp_dbg("mcast_cfg_db: %p, mode_addr: %p, mode: %d\n", &mcast_cfg_db, &mcast_cfg_db.mode, mode);
	mcast_cfg_db.mode = mode;
    	igmp_dbg("\n");
	return TRUE;
}

bc_boolean mcast_cfg_get_mode(OUT mcast_mode_e *mode)
{
	*mode = mcast_cfg_db.mode;

	return TRUE;
}

void mcast_cfg_def(void)
{
	mcast_cfg_db.enable = FALSE;
	mcast_cfg_db.mode = MCAST_MODE_DISABLE;
}

static void __mcast_cfg_local_init(void)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
#if 0 /*bain.wang@outlook.com*/
	mcast_cfg_db.enable = FALSE;
	mcast_cfg_db.mode = MCAST_MODE_DISABLE;
#else
	mcast_cfg_db.enable = TRUE;
	mcast_cfg_db.mode = MCAST_MODE_DISTRIBUTEDWOCM;
#endif
	mcast_cfg_db.igmp_version = MCAST_IGMP_V3;

	mcast_cfg_db.robustness 			= MCAST_ROBUSTNESS_VARIABLE;
	mcast_cfg_db.query_interval 		= MCAST_QUERY_INTERVAL;
	mcast_cfg_db.query_rsp_interval 	= MCAST_QUERY_RESPONSE_INTERVAL;
	mcast_cfg_db.member_interval 		= (mcast_cfg_db.robustness * mcast_cfg_db.query_interval) + mcast_cfg_db.query_rsp_interval;

	mcast_cfg_db.other_querier_present_interval 	= (mcast_cfg_db.robustness * mcast_cfg_db.query_interval) 
											+ (mcast_cfg_db.query_rsp_interval / 2);
	
	mcast_cfg_db.startup_query_interval	= mcast_cfg_db.query_interval / 4;
	mcast_cfg_db.startup_query_count 	= mcast_cfg_db.robustness;
	
	mcast_cfg_db.last_member_query_interval 	= MCAST_LAST_MEMBER_QUERY_INTERVAL;
	mcast_cfg_db.last_member_query_count 		= mcast_cfg_db.robustness;
	mcast_cfg_db.last_member_query_time 		= mcast_cfg_db.last_member_query_interval * mcast_cfg_db.last_member_query_count;
	
	mcast_cfg_db.unsolicited_report_interval 		= MCAST_UNSOLICITED_REPORT_INTERVAL;
	
	mcast_cfg_db.older_ver_querier_present_timeout = (mcast_cfg_db.robustness * mcast_cfg_db.query_interval) + mcast_cfg_db.query_rsp_interval;
	mcast_cfg_db.older_host_present_interval 	= (mcast_cfg_db.robustness * mcast_cfg_db.query_interval) + mcast_cfg_db.query_rsp_interval;

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
}


/* The API can't be used except debug */
void mcast_cfg_dbg_dump(void)
{
	char *mode_str[] = {
		"CENTRALIZED",
		"DISTRIBUTEDWITHCM",
		"DISABLE",
		"DISTRIBUTEDWOCM"
	};

	char *ver_str[] = {
		"V1",
		"V2",
		"V3"
	};

	MCAST_DBG_PRT("\t--------------- CFG DB ---------------");

	MCAST_DBG_PRT("\n\t%-32s:%s", "enable", mcast_cfg_db.enable ? "Enabled" : "Disabled");
	MCAST_DBG_PRT("\n\t%-32s:%s", "mode", mode_str[mcast_cfg_db.mode-1]);
	MCAST_DBG_PRT("\n\t%-32s:%s", "igmp_version", ver_str[mcast_cfg_db.igmp_version-1]);

	MCAST_DBG_PRT("\n\t%-32s:%d", "robustness", mcast_cfg_db.robustness);
	MCAST_DBG_PRT("\n\t%-32s:%ds", "query_interval", mcast_cfg_db.query_interval);
	MCAST_DBG_PRT("\n\t%-32s:%ds", "query_rsp_interval", mcast_cfg_db.query_rsp_interval);
	MCAST_DBG_PRT("\n\t%-32s:%ds", "member_interval", mcast_cfg_db.member_interval);

	MCAST_DBG_PRT("\n\t%-32s:%ds", "other_querier_present_interval", mcast_cfg_db.other_querier_present_interval);

	MCAST_DBG_PRT("\n\t%-32s:%ds", "startup_query_interval", mcast_cfg_db.startup_query_interval);
	MCAST_DBG_PRT("\n\t%-32s:%d", "startup_query_count", mcast_cfg_db.startup_query_count);

	MCAST_DBG_PRT("\n\t%-32s:%ds", "last_member_query_interval", mcast_cfg_db.last_member_query_interval);
	MCAST_DBG_PRT("\n\t%-32s:%d", "last_member_query_count", mcast_cfg_db.last_member_query_count);
	MCAST_DBG_PRT("\n\t%-32s:%ds", "last_member_query_time", mcast_cfg_db.last_member_query_time);

	MCAST_DBG_PRT("\n\t%-32s:%ds", "unsolicited_report_interval", mcast_cfg_db.unsolicited_report_interval);

	MCAST_DBG_PRT("\n\t%-32s:%ds", "older_ver_querier_present_timeout", mcast_cfg_db.older_ver_querier_present_timeout);
	MCAST_DBG_PRT("\n\t%-32s:%ds", "older_host_present_interval", mcast_cfg_db.older_host_present_interval);

	MCAST_DBG_PRT("\n");
}


#endif
#if 1

static mcast_port_t mcast_port_db;

void mcast_port_get_up_ports(OUT mcast_up_port_node_t *up_ports)
{
	memcpy(up_ports, mcast_port_db.up_port, sizeof(mcast_up_port_node_t)*BC_PORT_SNI_MAX_COUNT);
}

void mcast_port_get_up_port(IN bc_port_index_t port, OUT mcast_up_port_node_t *up_port)
{
	bc_int32 index;
	index = (port.port_id-1) +(port.slot_id - BC_PORT_SNI_MIN_SLOTNUM)* BC_PORT_SNI_MAX_PORTNUM;
	memcpy(up_port, &mcast_port_db.up_port[index], sizeof(mcast_up_port_node_t));
}

void mcast_port_update_up_ports(IN mcast_up_port_node_t *up_ports)
{
	memcpy(mcast_port_db.up_port, up_ports, sizeof(mcast_up_port_node_t)*BC_PORT_SNI_MAX_COUNT);
}

void mcast_port_update_up_rt_port(IN bc_port_index_t port, IN mcast_router_port_e rt_type, IN bc_uint16 sec)
{
	bc_int32 index;
	index = (port.port_id-1) +(port.slot_id - BC_PORT_SNI_MIN_SLOTNUM)* BC_PORT_SNI_MAX_PORTNUM;
	
	mcast_port_db.up_port[index].router_port = rt_type;
	mcast_port_db.up_port[index].dyn_tic = MCAST_TIC_CAL(sec);
}

void mcast_port_update_up_port_state(IN bc_port_index_t port, IN bc_boolean state)
{
	bc_int32 index;
	index = (port.port_id-1) +(port.slot_id - BC_PORT_SNI_MIN_SLOTNUM)* BC_PORT_SNI_MAX_PORTNUM;
	state = state ? TRUE : FALSE;
	mcast_port_db.up_port[index].en = state;
}

void mcast_port_get_down_ports(OUT mcast_down_port_node_t *down_ports)
{
	memcpy(down_ports, mcast_port_db.down_port, sizeof(mcast_down_port_node_t)*BC_PORT_PON_MAX_COUNT);
}

void mcast_port_get_down_port(IN bc_port_index_t port, OUT mcast_down_port_node_t *down_port)
{
	bc_int32 index;
	index = (port.port_id-1) +(port.slot_id - BC_PORT_PON_MIN_SLOTNUM)* BC_PORT_PON_MAX_PORTNUM;
	memcpy(down_port, &mcast_port_db.down_port[index], sizeof(mcast_down_port_node_t));
}

void mcast_port_update_down_port_state(IN bc_port_index_t port, IN bc_boolean state)
{
	bc_int32 index;
	index = (port.port_id-1) +(port.slot_id - BC_PORT_PON_MIN_SLOTNUM)* BC_PORT_PON_MAX_PORTNUM;
	state = state ? TRUE : FALSE;
	mcast_port_db.down_port[index].en = state;
}

static void __mcast_port_init(void)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	bc_uint32 i;

	/* collect device sni port information and pon port information */

	memset(&mcast_port_db, 0x00, sizeof(mcast_port_t));
	
	mcast_port_db.up_port_num = BC_PORT_SNI_MAX_COUNT;
	for (i = 0; i < BC_PORT_SNI_MAX_COUNT; i++)
	{
		
		mcast_port_db.up_port[i].port_id.slot_id = 1;
		mcast_port_db.up_port[i].port_id.port_type = BC_PORT_SNI_MIN_SLOTNUM + i /BC_PORT_SNI_MAX_PORTNUM ;
		mcast_port_db.up_port[i].port_id.port_id = i % BC_PORT_SNI_MAX_PORTNUM + 1;

		mcast_port_db.up_port[i].en = FALSE;

		mcast_port_db.up_port[i].router_port = MCAST_NONE_ROUTER_PORT;

		memset(&(mcast_port_db.up_port[i].stats), 0x00, sizeof(mcast_port_stats_t));
	}

	mcast_port_db.down_port_num = BC_PORT_PON_MAX_COUNT;
	for (i = 0; i < BC_PORT_PON_MAX_COUNT; i++)
	{
		mcast_port_db.down_port[i].port_id.slot_id = BC_PORT_PON_MIN_SLOTNUM + i / BC_PORT_PON_MAX_PORTNUM;
		mcast_port_db.down_port[i].port_id.port_type = PORT_TYPE_OLT_GEEPON;
		mcast_port_db.down_port[i].port_id.port_id = i % BC_PORT_PON_MAX_PORTNUM + 1;

		mcast_port_db.down_port[i].en = FALSE;
	
		memset(&(mcast_port_db.down_port[i].stats), 0x00, sizeof(mcast_port_stats_t));
	}

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
}


/* The API can't be used except debug */
void mcast_cfg_port_dbg_dump(void)
{
	bc_uint16 up_idx;
	bc_uint16 down_idx;

	char *rt_port_str[] = {
		"Non",
		"Dyn",
		"Static"
	};

	char buf[20] = {0};

	MCAST_DBG_PRT("\t--------------- CFG PORT DB ---------------");

	MCAST_DBG_PRT("\n\tUpstream Port Number: %d", mcast_port_db.up_port_num);
	MCAST_DBG_PRT("\n\t%-9s%-9s%-11s%-8s", "Port Idx", "State", "Route Port", "DRP Tic");
	MCAST_DBG_PRT("\n\t%-9s%-9s%-11s%-8s", "--------", "---------", "----------", "-------");
	for (up_idx = 0; up_idx < BC_PORT_SNI_MAX_COUNT; up_idx++)
	{
		MCAST_DBG_PRT("\n\t");
	
		memset(buf, 0x00, 20);
		sprintf(buf, "s%d:t%d:p%d", mcast_port_db.up_port[up_idx].port_id.slot_id, mcast_port_db.up_port[up_idx].port_id.port_type, 
								mcast_port_db.up_port[up_idx].port_id.port_id);
		MCAST_DBG_PRT("%-9s", buf);
		MCAST_DBG_PRT("%-9s", mcast_port_db.up_port[up_idx].en ? "Enabled" : "Disabled");
		MCAST_DBG_PRT("%-11s", rt_port_str[mcast_port_db.up_port[up_idx].router_port]);
		MCAST_DBG_PRT("%-8d", mcast_port_db.up_port[up_idx].dyn_tic);
	}

	MCAST_DBG_PRT("\n");

	MCAST_DBG_PRT("\n\tDownstream Port Number: %d", mcast_port_db.down_port_num);
	MCAST_DBG_PRT("\n\t%-9s%-9s", "Port Idx", "State");
	MCAST_DBG_PRT("\n\t%-9s%-9s", "--------", "---------");
	for (down_idx = 0; down_idx < BC_PORT_PON_MAX_COUNT; down_idx++)
	{
		MCAST_DBG_PRT("\n\t");
	
		memset(buf, 0x00, 20);
		sprintf(buf, "s%d:t%d:p%d", mcast_port_db.down_port[down_idx].port_id.slot_id, mcast_port_db.down_port[down_idx].port_id.port_type, 
								mcast_port_db.down_port[down_idx].port_id.port_id);
		MCAST_DBG_PRT("%-9s", buf);
		MCAST_DBG_PRT("%-9s", mcast_port_db.down_port[down_idx].en ? "Enabled" : "Disabled");
	}

	MCAST_DBG_PRT("\n");
}


/* The API can't be used except debug */
void mcast_cfg_port_stats_dbg_dump(void)
{
	bc_uint16 up_idx;
	bc_uint16 down_idx;

	MCAST_DBG_PRT("\t--------------- CFG PORT STATS ---------------");

	MCAST_DBG_PRT("\n\tUpstream Port Number: %d", mcast_port_db.up_port_num);
	for (up_idx = 0; up_idx < BC_PORT_SNI_MAX_COUNT; up_idx++)
	{
		MCAST_DBG_PRT("\n\tUpstream Port slotid:%d porttype:%d portid:%d", mcast_port_db.up_port[up_idx].port_id.slot_id,
							mcast_port_db.up_port[up_idx].port_id.port_type, mcast_port_db.up_port[up_idx].port_id.port_id);
		MCAST_DBG_PRT("\n\t%-20s:%-8llu", "in_igmp_query", mcast_port_db.up_port[up_idx].stats.in_igmp_query);
		MCAST_DBG_PRT("\n\t%-20s:%-8llu", "in_igmpv1_report", mcast_port_db.up_port[up_idx].stats.in_igmpv1_report);
		MCAST_DBG_PRT("\n\t%-20s:%-8llu", "in_igmpv2_report", mcast_port_db.up_port[up_idx].stats.in_igmpv2_report);
		MCAST_DBG_PRT("\n\t%-20s:%-8llu", "in_igmpv2_leave", mcast_port_db.up_port[up_idx].stats.in_igmpv2_leave);
		MCAST_DBG_PRT("\n\t%-20s:%-8llu", "in_igmpv3_report", mcast_port_db.up_port[up_idx].stats.in_igmpv3_report);

		MCAST_DBG_PRT("\n\t%-20s:%-8llu", "out_igmp_query", mcast_port_db.up_port[up_idx].stats.out_igmp_query);
		MCAST_DBG_PRT("\n\t%-20s:%-8llu", "out_igmpv1_report", mcast_port_db.up_port[up_idx].stats.out_igmpv1_report);
		MCAST_DBG_PRT("\n\t%-20s:%-8llu", "out_igmpv2_report", mcast_port_db.up_port[up_idx].stats.out_igmpv2_report);
		MCAST_DBG_PRT("\n\t%-20s:%-8llu", "out_igmpv2_leave", mcast_port_db.up_port[up_idx].stats.out_igmpv2_leave);
		MCAST_DBG_PRT("\n\t%-20s:%-8llu", "out_igmpv3_report", mcast_port_db.up_port[up_idx].stats.out_igmpv3_report);

		MCAST_DBG_PRT("\n");
	}

	MCAST_DBG_PRT("\n\tDownstream Port Number: %d", mcast_port_db.down_port_num);
	for (down_idx = 0; down_idx < BC_PORT_PON_MAX_COUNT; down_idx++)
	{
		MCAST_DBG_PRT("\n\tDownstream Port slotid:%d porttype:%d portid:%d", mcast_port_db.down_port[down_idx].port_id.slot_id,
							mcast_port_db.down_port[down_idx].port_id.port_type, mcast_port_db.down_port[down_idx].port_id.port_id);
		MCAST_DBG_PRT("\n\t%-20s:%-8llu", "in_igmp_query", mcast_port_db.down_port[down_idx].stats.in_igmp_query);
		MCAST_DBG_PRT("\n\t%-20s:%-8llu", "in_igmpv1_report", mcast_port_db.down_port[down_idx].stats.in_igmpv1_report);
		MCAST_DBG_PRT("\n\t%-20s:%-8llu", "in_igmpv2_report", mcast_port_db.down_port[down_idx].stats.in_igmpv2_report);
		MCAST_DBG_PRT("\n\t%-20s:%-8llu", "in_igmpv2_leave", mcast_port_db.down_port[down_idx].stats.in_igmpv2_leave);
		MCAST_DBG_PRT("\n\t%-20s:%-8llu", "in_igmpv3_report", mcast_port_db.down_port[down_idx].stats.in_igmpv3_report);

		MCAST_DBG_PRT("\n\t%-20s:%-8llu", "out_igmp_query", mcast_port_db.down_port[down_idx].stats.out_igmp_query);
		MCAST_DBG_PRT("\n\t%-20s:%-8llu", "out_igmpv1_report", mcast_port_db.down_port[down_idx].stats.out_igmpv1_report);
		MCAST_DBG_PRT("\n\t%-20s:%-8llu", "out_igmpv2_report", mcast_port_db.down_port[down_idx].stats.out_igmpv2_report);
		MCAST_DBG_PRT("\n\t%-20s:%-8llu", "out_igmpv2_leave", mcast_port_db.down_port[down_idx].stats.out_igmpv2_leave);
		MCAST_DBG_PRT("\n\t%-20s:%-8llu", "out_igmpv3_report", mcast_port_db.down_port[down_idx].stats.out_igmpv3_report);

	}

	MCAST_DBG_PRT("\n");
}


#endif
#if 1

static bc_uint16 mcast_vlan_cnt = 0;
static mcast_vlan_t mcast_vlan_db[MCAST_VLAN_MAX] = {{0}, {0}, {0}};

bc_boolean mcast_vlan_add(IN mcast_vlan_t *vlan)
{
	bc_uint16 idx;

	if (vlan->vid > 4094)
		return FALSE;

	for (idx = 0; idx < MCAST_VLAN_MAX; idx++)
	{
		if (mcast_vlan_db[idx].vid == vlan->vid)
		{
			igmp_dbg("update vid: %d\n", vlan->vid);
			memcpy(&mcast_vlan_db[idx], vlan, sizeof(mcast_vlan_t));
			return TRUE;
		}
	}

	if (mcast_vlan_cnt >= MCAST_VLAN_MAX)
		return FALSE;

	for (idx = 0; idx < MCAST_VLAN_MAX; idx++)
		if (mcast_vlan_db[idx].vid == 0)
			break;

	if (idx >= MCAST_VLAN_MAX)
		return FALSE;

	igmp_dbg("add vlan %d, idx: %d\n", vlan->vid, idx);
	memcpy(&mcast_vlan_db[idx], vlan, sizeof(mcast_vlan_t));
	mcast_vlan_cnt++;
	return TRUE;
}

bc_boolean mcast_vlan_del(IN bc_uint16 vid)
{
	bc_uint16 idx;

	if (vid > 4094)
		return FALSE;

	for (idx = 0; idx < MCAST_VLAN_MAX; idx++)
	{
		if (mcast_vlan_db[idx].vid == vid)
		{
			igmp_dbg("del vlan %d, idx: %d\n", vid, idx);
			memset(&mcast_vlan_db[idx], 0x00, sizeof(mcast_vlan_t));
			mcast_vlan_cnt--;
			return TRUE;
		}
	}

	return FALSE;
}

bc_boolean mcast_vlan_get(INOUT mcast_vlan_t *vlan)
{
	bc_uint16 idx;

	if (vlan->vid > 4094)
		return FALSE;

	for (idx = 0; idx < MCAST_VLAN_MAX; idx++)
	{
		if (mcast_vlan_db[idx].vid == vlan->vid)
		{
			memcpy(vlan, &mcast_vlan_db[idx], sizeof(mcast_vlan_t));
			return TRUE;
		}
	}

	return FALSE;
}

bc_boolean mcast_vlan_get_next(IN bc_int16 in_vid, OUT bc_int16 *out_vid)
{
	bc_uint16 idx, nextvid;

	if (in_vid > 4094)
		return FALSE;

	igmp_dbg("vid: %d, total vlan cnt: %d\n", in_vid, mcast_vlan_cnt);
	nextvid = 4095;
	for (idx = 0; idx < MCAST_VLAN_MAX; idx++)
	{
		if (in_vid < mcast_vlan_db[idx].vid && mcast_vlan_db[idx].vid < nextvid)
		{
			igmp_dbg("get vid: %d, idx: %d\n", mcast_vlan_db[idx].vid, idx);
			nextvid = mcast_vlan_db[idx].vid;
		}
	}

	if (nextvid < 4095)
	{
		*out_vid = nextvid;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


bc_boolean mcast_vlan_create_rule_check(IN bc_uint16 vid)
{
	/* single vlan mode no rule check
	     multi vlan mode, the multicast vlan must continue */
	return TRUE;
}

/* the API only used when system work in the multi vlan mode */
bc_boolean mcast_vlan_get_continue_vlan(OUT bc_uint16 *start_vid, OUT bc_uint16 *num)
{
	bc_uint16 vid_idx;

	*start_vid = 4095;
	for (vid_idx = 0; vid_idx < MCAST_VLAN_MAX; vid_idx++)
	{
		if (mcast_vlan_db[vid_idx].vid == 0)
			continue;

		if (mcast_vlan_db[vid_idx].vid < *start_vid)
			*start_vid = mcast_vlan_db[vid_idx].vid;
	}

	*num = mcast_vlan_cnt;
	return TRUE;
}
/*
static void __mcast_vlan_init(void)
{
	mcast_vlan_cnt = 0;
	memset(mcast_vlan_db, 0x00, sizeof(mcast_vlan_t)*MCAST_VLAN_MAX);
}
*/

/* The API can't be used except debug */
void mcast_cfg_vlan_dbg_dump(void)
{
	bc_uint16 vlan_idx;

	bc_uint16 up_idx;
	bc_uint16 down_idx;

	bc_uint16 cnt = 0;

	char port_buf[5] = {0};
	char buf[40] = {0};
	
	MCAST_DBG_PRT("\t--------------- CFG VLAN DB ---------------");

	MCAST_DBG_PRT("\n\tmcast_vlan_cnt: %d", mcast_vlan_cnt);
	MCAST_DBG_PRT("\n\t%-9s%-20s%-20s", "Vlan Idx", "Up Ports(type:id)", "Down Ports(type:id)");
	MCAST_DBG_PRT("\n\t%-9s%-20s%-40s", "--------", "-------------------", "-------------------");
	cnt = 0;
	for (vlan_idx = 0; vlan_idx < MCAST_VLAN_MAX; vlan_idx++)
	{
		if (mcast_vlan_db[vlan_idx].vid == 0)
			continue;

		MCAST_DBG_PRT("\n\t");
		MCAST_DBG_PRT("%-9d", mcast_vlan_db[vlan_idx].vid);

		memset(buf, 0x00, 40);
		for (up_idx = 0; up_idx < BC_PORT_SNI_MAX_COUNT; up_idx++)
		{
			memset(port_buf, 0x00, 5);
			sprintf(port_buf, "%d:%d ", mcast_vlan_db[vlan_idx].sni_port[up_idx].port_type, 
									mcast_vlan_db[vlan_idx].sni_port[up_idx].port_id);
			sprintf(buf, "%s%s", buf, port_buf);			
		}
		MCAST_DBG_PRT("%-20s", buf);

		memset(buf, 0x00, 40);
		for (down_idx = 0; down_idx < BC_PORT_PON_MAX_COUNT; down_idx++)
		{
			memset(port_buf, 0x00, 5);
			sprintf(port_buf, "%d:%d ", mcast_vlan_db[vlan_idx].epon_port[down_idx].port_type, 
									mcast_vlan_db[vlan_idx].epon_port[down_idx].port_id);
			sprintf(buf, "%s%s", buf, port_buf);	
		}
		MCAST_DBG_PRT("%-40s", buf);

		cnt++;
	}

	MCAST_DBG_PRT("\n\tTotal Cnt: %d\n", cnt);
}

#endif
#if 1

void mcast_cfg_init(void)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	memset(&mcast_cfg_db, 0x00, sizeof(mcast_cfg_db));
	__mcast_cfg_local_init();
	__mcast_port_init();
	
	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
}

#endif
#endif


