/*******************************************************************************
  [File name]	: mcast_init.c
  [Author]     	: bain.wang@outlook.com
  [Version]    	: 1.0
  [Date]       	: 2017-06-13
  [Description]	:
	Multicast module init
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

#include "mcast_init.h"

#if BC_MULTICAST_INCLUDE

#include "mcast_cfg.h"
#include "mcast_cfg_grp.h"
#include "mcast_router.h"
#include "mcast_host.h"
#include "mcast_core.h"
#include "mcast_call.h"

void mcast_init(void)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	/* database init */
	mcast_cfg_init();
	mcast_cfg_grp_init();

	mcast_core_init();
	
	mcast_rt_init();
	mcast_host_init();
	
	/* task init */
	mcast_core_task_init();

	mcast_call_pkt_register();

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return;
}

#endif

