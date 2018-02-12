/*******************************************************************************
  
  [File name]	: drv_53724_mcast.h
  [Author]     	: yangl
  [Version]    	: 1.0
  [Date]       	: 2013-04-01
  [Description]	:
	mcast driver
  [Others]     	:
	NULL
  [Function List]:  
    1. ....
    2. ....
  [History]:
	 D a t e      	Modification 							 Initials
	---------- 	--------------                                        ----------
	2013-04-01  	Created								 yangl
*******************************************************************************/

#ifndef __DRV_MCAST_H__
#define __DRV_MCAST_H__
#include "bc_common_defs.h"
#include "bc_err.h"
#include "bc_port_def.h"

#if 1
#define DRV_MCAST_SRC_MAX		64
#define DRV_MCAST_NODE_MAX		1024
typedef struct {
	bc_ip	src;
	bc_boolean	in_chip;  /* only use for get, mean the entry is whether or not in chip */
	bc_boolean 	src_fwd_list[BC_PORT_PON_MAX_COUNT + BC_PORT_SNI_MAX_COUNT];
} drv_mcast_src_node_t;

typedef struct {

	bc_ip 	grp;
	bc_uint16	vid;
	bc_boolean 	grp_fwd_list[BC_PORT_PON_MAX_COUNT + BC_PORT_SNI_MAX_COUNT];
	bc_int32	src_num;
	drv_mcast_src_node_t  src_list[DRV_MCAST_SRC_MAX];
} drv_mcast_node_t;

bc_err_e drv_mcast_update(IN drv_mcast_node_t *fwd_node);
bc_err_e drv_mcast_delete(IN bc_ip grp, IN bc_uint16 vid);
bc_err_e drv_mcsat_get_next( drv_mcast_node_t * node);
bc_err_e drv_mcast_clear(void);
bc_err_e drv_mcast_enable(bc_uint8 flag);
bc_err_e drv_mcst_init(void);
#endif


#endif
