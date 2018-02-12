/*******************************************************************************
  [File name]	: mcast_mgmt.h
  [Author]     	: bain.wang@outlook.com
  [Version]    	: 1.0
  [Date]       	: 2017-06-15
  [Description]	:
	Multicast module API for CLI SNMP
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

#ifndef __mcast_mgmt_h__
#define __mcast_mgmt_h__

#include "mcast_def.h"
#include "mcast_utl.h"
#include "mcast_cfg.h"
#if 0 /*bain.wang@outlook.com*/
#include "mcast_onu_cfg.h"
#endif
#include "mcast_cfg_grp.h"

#if BC_MULTICAST_INCLUDE
#if 1

typedef struct {
	bc_boolean en;
	mcast_mode_e mode;

	bc_uint16 mqrt;			/* max query response time */
	bc_uint16 robust_var;		
	bc_uint16 query_interval;

	bc_uint16 lmqi;	/* last member query interval */
	bc_uint16 lmqc;	/* last member query count */

	mcast_igmp_version_e ver;
} mcast_mgmt_cfg_t;

#define MCAST_MGMT_CFG_STATE			0x00000001
#define MCAST_MGMT_CFG_MQRT				0x00000002
#define MCAST_MGMT_CFG_ROBUST_VAR		0x00000004
#define MCAST_MGMT_CFG_QUERY_INTERVAL	0x00000008
#define MCAST_MGMT_CFG_LMQI				0x00000010
#define MCAST_MGMT_CFG_LMQC				0x00000020
#define MCAST_MGMT_CFG_VER				0x00000040
#define MCAST_MGMT_CFG_MODE				0x00000080
#define MCAST_MGMT_CFG_ALL (MCAST_MGMT_CFG_STATE | MCAST_MGMT_CFG_MQRT | MCAST_MGMT_CFG_ROBUST_VAR | MCAST_MGMT_CFG_QUERY_INTERVAL | \
								MCAST_MGMT_CFG_LMQI | MCAST_MGMT_CFG_LMQC | MCAST_MGMT_CFG_VER | MCAST_MGMT_CFG_MODE)

/*****************************************************************************
  Function   : 	mcast_mgmt_xx_cfg_get
  Description: 	get xx multicast configure
  Return     : 
  Others     : 	
******************************************************************************/
bc_err_e mcast_mgmt_xx_cfg_get(IN bc_uint32 set_opt_flag, OUT mcast_mgmt_cfg_t *xx_cfg);

/*****************************************************************************
  Function   : 	mcast_mgmt_xx_cfg_set
  Description: 	configure xx multicast 
  Return     : 
  Others     : 	
******************************************************************************/
bc_err_e mcast_mgmt_xx_cfg_set(IN bc_uint32 set_opt_flag, IN mcast_mgmt_cfg_t *xx_cfg);

#endif
#if 1


typedef struct {
	bc_ip 	grp;
	bc_uint16	vid;
	
	bc_mac	mac;  /* mapping from grp */
	bc_port_index_t port_list[BC_PORT_PON_MAX_COUNT + BC_PORT_SNI_MAX_COUNT];
} mcast_mgmt_fwd_t;

/*****************************************************************************
  Function   : 	mcast_mgmt_xx_fwd_get_next
  Description: get xx fwd table
  Return     : 
  Others     : 	
******************************************************************************/
bc_err_e mcast_mgmt_xx_fwd_get_all(INOUT mcast_mgmt_fwd_t *fwd_block, OUT bc_uint16 *acutal_num);


#endif





#endif
#endif

