/*******************************************************************************
  [File name]	: mcast_core.h
  [Author]     	: bain.wang@outlook.com
  [Version]    	: 1.0
  [Date]       	: 2017-06-15
  [Description]	:
	Multicast module core process for pkt deal / timer / configure
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

#ifndef __mcast_core_h__
#define __mcast_core_h__

#include "mcast_def.h"
#include "mcast_utl.h"
#include "mcast_pkt.h"
#include "mcast_rx.h"
#include "mcast_cfg.h"
#include "mcast_host.h"
#include "mcast_router.h"
#if 0 /*bain.wang@outlook.com*/
#include "mcast_ctrlmc.h"
#endif
#include "drv_mcast.h"

#if BC_MULTICAST_INCLUDE
#if 1

void mcast_core_task_init(void);
void mcast_core_init(void);

#endif
#if 1

mcast_ret_code mcast_core_igmp_enable(void);
mcast_ret_code mcast_core_igmp_disable(void);
mcast_ret_code mcast_core_igmp_ver_proc(IN mcast_igmp_version_e old_ver, IN mcast_igmp_version_e new_ver);
mcast_ret_code mcast_core_igmp_mode_proc(IN mcast_mode_e old_mode, IN mcast_mode_e new_mode);

#endif
#if 1

typedef struct {
	bc_ip 	grp;
	bc_uint16	vid;
	
	bc_mac	mac;  /* mapping from grp */
	bc_port_index_t port_list[BC_PORT_PON_MAX_COUNT + BC_PORT_SNI_MAX_COUNT];
} mcast_core_fwd_t;
mcast_ret_code mcast_core_xx_fwd_get_all(INOUT mcast_core_fwd_t *fwd_block, OUT bc_uint16 *actual_num);

mcast_ret_code mcast_core_proxy_cfg_add(IN mcast_cfg_grp_t *cfg_grp_p);
mcast_ret_code mcast_core_proxy_cfg_update(IN mcast_cfg_grp_t *cfg_grp_p);
mcast_ret_code mcast_core_proxy_cfg_del(IN bc_uint16 index);

#if 0 /*bain.wang@outlook.com*/
mcast_ret_code mcast_core_cm_package_add(IN mcast_ctrlmc_package_t *package);
mcast_ret_code mcast_core_cm_package_update(IN mcast_ctrlmc_package_t *package);
mcast_ret_code mcast_core_cm_package_del(IN bc_uint16 cm_idx);
mcast_ret_code mcast_core_cm_package_get(IN bc_uint16 cm_idx, OUT mcast_ctrlmc_package_t *package);

mcast_ret_code mcast_core_cm_authority_entry_add(IN mcast_ctrlmc_authority_entry_t *entry);
mcast_ret_code mcast_core_cm_authority_entry_update(IN mcast_ctrlmc_authority_entry_t *entry);
mcast_ret_code mcast_core_cm_authority_entry_del(IN bc_uint16 onu_id, IN bc_uint16 slot_id, IN bc_uint16 uni_port);
mcast_ret_code mcast_core_cm_authority_entry_get(INOUT mcast_ctrlmc_authority_entry_t *entry);
#endif

#endif
#if 1

mcast_ret_code mcast_core_update_grp_node_to_chip(IN mcast_grp_t *grp_node_p);
mcast_ret_code mcast_core_igmp_process(IN mcast_rx_node_t *pkt, IN mcast_pkt_igmp_t *igmp);

#endif
#endif
#endif

