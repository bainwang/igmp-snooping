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

#ifndef __DRV_chipname_MCAST_H__
#define __DRV_chipname_MCAST_H__

#include "drv_mcast.h"
#include "utili_ip_mac.h"


#if 1
bc_err_e drv_chipname_mcast_update(IN drv_mcast_node_t * fwd_node);
bc_err_e drv_chipname_mcast_delete(IN bc_ip grp, IN bc_uint16 vid);
bc_err_e drv_chipname_mcast_clear(void);
bc_err_e drv_chipname_mcsat_get_next( drv_mcast_node_t * node);
bc_err_e drv_chipname_mcast_enable(bc_uint8 flag);
bc_err_e drv_chipname_mcast_init(void);
#endif


#endif
