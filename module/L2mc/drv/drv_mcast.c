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
#include "bc_modules.h"
#include "bc_err.h"
#include "bc_common_defs.h"
#include "bc_print.h"
#include "drv_mcast.h"
#include "drv_chipname_mcast.h"

#if 1
bc_err_e drv_mcast_update(IN drv_mcast_node_t *fwd_node)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP_DRV);
	
	bc_err_e ret;
	if (fwd_node == NULL)
	{
		BC_PT_DBG_FUN(BC_MODULE_IGMP_DRV, "fwd_node is NULL!!!\n");
		return BC_ERR_PARA;
	}

	ret = drv_chipname_mcast_update(fwd_node);

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP_DRV);
	
	return ret;
}

bc_err_e drv_mcast_delete(IN bc_ip grp, IN bc_uint16 vid)
{
	return drv_chipname_mcast_delete(grp, vid);	 
}
bc_err_e drv_mcsat_get_next( drv_mcast_node_t * node)
{
	return drv_chipname_mcsat_get_next(node);
}
bc_err_e drv_mcast_clear(void)
{
	return drv_chipname_mcast_clear();
}

bc_err_e drv_mcast_enable(bc_uint8 flag)
{
	return drv_chipname_mcast_enable(flag);
}

bc_err_e drv_mcst_init(void)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP_DRV);
	
	bc_err_e ret;
	
	ret = drv_chipname_mcast_init();

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP_DRV);
	
	return ret;
}

#endif
