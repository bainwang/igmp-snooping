/*******************************************************************************
  [File name]	: mcast_router.h
  [Author]     	: bain.wang@outlook.com
  [Version]    	: 1.0
  [Date]       	: 2017-09-05
  [Description]	:
	Do igmp router behavior on downstream ports
  [Others]     	:
	NULL
  [Function List]:  
    1. ....
    2. ....
  [History]:
	 D a t e      	Modification 							 Initials
	---------- 	--------------                                        ----------
	2017-09-05  	Created								 bain.wang@outlook.com
*******************************************************************************/

#ifndef __mcast_router_h__
#define __mcast_router_h__

#include "mcast_def.h"
#include "mcast_utl.h"
#include "mcast_pkt.h"
#include "mcast_cfg.h"
#include "mcast_call.h"
#include "mcast_tx.h"

#if BC_MULTICAST_INCLUDE


typedef struct {
	mcast_list_node_t src_list_node;

	bc_ip	src;
	bc_uint16 tic;
	
	bc_uint8	reserve[2];
} mcast_grp_src_t;

typedef struct {
	bc_uint16 grp_tic;
	bc_uint16 v1_tic;
	bc_uint16 v2_tic;
	mcast_pkt_record_type_e mode;
	mcast_list_t src_list;
} mcast_grp_port_t;

typedef struct {
	bc_ip	grp;		/* key */
	bc_uint16	vid;		/* furture use for key: no use */
	mcast_grp_port_t	port_grp[BC_PORT_PON_MAX_COUNT + BC_PORT_SNI_MAX_COUNT];
} mcast_grp_t;

#if 1

mcast_grp_t* mcast_rt_node_get(IN bc_ip grp);
mcast_grp_t* mcast_rt_node_get_next(IN mcast_grp_t *grp_node);
mcast_ret_code mcast_rt_node_clear_all(void);

#endif
#if 1

void mcast_rt_grp_tic(void);

#endif
#if 1

bc_boolean mcast_rt_send_query_clear(void);
void mcast_rt_send_query_tic(void);

#endif
#if 1


mcast_ret_code mcast_rt_proc_port_grp_info(
	IN bc_port_index_t port,
	IN bc_ip grp,
	IN bc_uint16 vid,
	IN mcast_pkt_type_e pkt_type,
	IN mcast_pkt_record_type_e record_type,
	IN mcast_list_t *src_list);

mcast_ret_code mcast_rt_proc_leave(IN bc_port_index_t port, IN bc_ip grp);

#endif
#if 1

mcast_ret_code mcast_rt_mgt_del_grp(IN bc_ip grp);

#endif
#if 1


/* The API can't be used except debug */
void mcast_rt_grp_dump(void);
/* The API can't be used except debug */
void mcast_rt_query_list_dump(void);
/* The API can't be used except debug */
void mcast_rt_gen_query_dump(void);

void mcast_rt_init(void);

#endif


#endif
#endif


