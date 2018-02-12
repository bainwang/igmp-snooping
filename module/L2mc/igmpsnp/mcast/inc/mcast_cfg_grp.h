/*******************************************************************************
  [File name]	: mcast_cfg_grp.h
  [Author]     	: bain.wang@outlook.com
  [Version]    	: 1.0
  [Date]       	: 2017-06-13
  [Description]	:
	Multicast module configure group
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

#ifndef __mcast_cfg_grp_h__
#define __mcast_cfg_grp_h__

#include "mcast_def.h"
#include "mcast_utl.h"
#include "mcast_call.h"

#if BC_MULTICAST_INCLUDE

#define MCAST_PROXY_NAME_LEN		32

typedef struct {
	bc_uint16		idx;
	
	bc_uint16	  	vid;
	bc_ip		grp;
	bc_ip		src;
	
	bc_uint32		abw;
	bc_uint32		max_bw;
} mcast_cfg_grp_t;

void mcast_cfg_grp_init(void);

bc_boolean mcast_cfg_grp_search_by_ip(IN bc_ip grp, IN bc_uint16 vid, OUT mcast_cfg_grp_t *cfg_grp);

bc_boolean mcast_cfg_grp_get_vid_by_grp(IN bc_ip grp, OUT bc_uint16 *vid);
bc_boolean mcast_cfg_grp_cfg_exist(IN bc_ip grp, IN bc_uint16 vid);
bc_boolean mcast_cfg_grp_vid_used(IN bc_uint16 mc_vid, IN bc_uint16 except_check_idx);
bc_boolean mcast_cfg_grp_conflict(IN bc_uint16 mc_vid, IN bc_ip mc_ip, IN bc_uint16 except_check_idx);

bc_boolean mcast_cfg_grp_add(IN mcast_cfg_grp_t *cfg_grp_node);
bc_boolean mcast_cfg_grp_update(IN mcast_cfg_grp_t *cfg_grp_node);
bc_boolean mcast_cfg_grp_del(IN bc_uint32 index);
bc_boolean mcast_cfg_grp_get_by_index(IN bc_uint32 index, OUT mcast_cfg_grp_t*cfg_grp_node);

/* The API can't be used except debug */
void mcast_cfg_grp_db_dbg_dump(void);
/* The API can't be used except debug */
void mcast_cfg_grp_tree_dbg_dump(void);

#endif
#endif

