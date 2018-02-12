/*******************************************************************************
  [File name]	: mcast_host.h
  [Author]     	: bain.wang@outlook.com
  [Version]    	: 1.0
  [Date]       	: 2017-07-06
  [Description]	:
	Store upstream group state
  [Others]     	:
	NULL
  [Function List]:  
    1. ....
    2. ....
  [History]:
	 D a t e      	Modification 							 Initials
	---------- 	--------------                                        ----------
	2017-07-06  	Created								 bain.wang@outlook.com
*******************************************************************************/

#ifndef __mcast_host_h__
#define __mcast_host_h__

#include "mcast_def.h"
#include "mcast_utl.h"
#include "mcast_router.h"
#include "mcast_call.h"
#include "mcast_pkt.h"

#if BC_MULTICAST_INCLUDE

typedef struct {
	mcast_list_node_t src_list_node;

	bc_ip src;
	bc_uint16 robustness;		/* RFC 3376 page 20, section 4 If the interface reception-state change... */
	
	bc_uint8 reserve[2];
} mcast_host_src_t;

typedef struct {
	bc_ip 	grp;
	bc_uint16	vid;

	mcast_pkt_record_type_e type;
	mcast_list_t 	src_list;
} mcast_host_grp_t;

#if 1

mcast_host_grp_t* mcast_host_node_get(IN bc_ip grp);
mcast_ret_code mcast_host_node_clear(void);

#endif
#if 1

void mcast_host_send_report_tic(void);

mcast_ret_code mcast_host_trigger_report(IN mcast_grp_t *new_grp_node_p);


mcast_ret_code mcast_host_proc_gen_query(IN mcast_pkt_igmp_query_t *query);
mcast_ret_code mcast_host_proc_grp_spec_query(IN mcast_pkt_igmp_query_t *query);
mcast_ret_code mcast_host_proc_grp_src_spec_query(IN mcast_pkt_igmp_query_t *query);

bc_boolean mcast_host_delay_report_clear(void);

#endif
#if 1

mcast_ret_code mcast_host_mgt_del_grp(IN bc_ip grp, IN bc_uint16 vid);

#endif
#if 1

bc_boolean mcast_host_ver_set(IN mcast_igmp_version_e ver);
mcast_igmp_version_e mcast_host_ver_get(void);
void mcast_host_ver_update_tic(IN mcast_igmp_version_e ver);
bc_boolean mcast_host_ver_reset(void);
void mcast_host_ver_tic(void);

#endif
#if 1

void mcast_host_dyn_router_port_proc(IN bc_port_index_t rx_query_port);
void mcast_host_dyn_router_port_clear(void);
void mcast_host_dyn_router_port_tic(void);

#endif
#if 1


/* The API can't be used except debug */
void mcast_host_tree_dump(void);
/* The API can't be used except debug */
void mcast_host_query_dump(void);
/* The API can't be used except debug */
void mcast_host_delay_report_dump(void);
/* The API can't be used except debug */
void mcast_host_ver_dump(void);


void mcast_host_init(void);

#endif

#endif
#endif


