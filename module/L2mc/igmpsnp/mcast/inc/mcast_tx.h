/*******************************************************************************
  [File name]	: mcast_tx.h
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

#ifndef __mcast_tx_h__
#define __mcast_tx_h__

#include "mcast_def.h"
#include "mcast_pkt.h"
#include "mcast_call.h"
#include "mcast_cfg.h"
#include "mcast_utl.h"
#include "mcast_cfg_grp.h"
#include "mcast_router.h"

#if BC_MULTICAST_INCLUDE

typedef struct {
	mcast_list_node_t	list_node;

	bc_ip 	grp;
	bc_uint16	vid;
	mcast_pkt_record_type_e type;
	mcast_list_t src_list;
} mcast_tx_report_node_t;

mcast_ret_code mcast_tx_report(IN mcast_list_t *report_list);

mcast_ret_code mcast_tx_grp_src_query(IN bc_port_index_t send_port, IN bc_ip grp, IN mcast_list_t *src_list);
mcast_ret_code mcast_tx_grp_query(IN bc_port_index_t send_port, IN bc_ip grp);
mcast_ret_code mcast_tx_gen_query(void);

#endif
#endif

