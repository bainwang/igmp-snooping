
/*******************************************************************************
  [File name]  : bc_igmp.c
  [Author]     : bin.wang
  [Version]    : 1.0
  [Date]       : 2017-06-10
  [Description]:

  [Others]     :

  [Function List]:  
    1. ....
    2. ....
  [History]:
	 D a t e    Modification 										Initials
	---------- --------------                                       ----------
	2017-06-08  Created												bin.wang
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								Í·   ÎÄ   ¼þ								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>

#include "mcast_init.h"
#include "bc_cfg_mgmt.h"
#include "mcast_mgmt.h"
#include "bc_msg.h"
#include "bc_igmp_def.h"
#include "bc_sys_event.h"

#if 1

static bc_igmp_xx_t g_xx_igmp;
static unsigned int l_mdl_id = BC_MODULE_IGMP;

#define LOG_FLAG_MODULE LOG_BIT_ALL

bc_pthread_mutex_t * bc_igmp_mutex = NULL;

#if 0

static void __bc_igmp_evt_port_valid_change(bc_port_valid_chg_cb_msg_t *msg)
{
	bc_port_index_t port_index;
	
	BC_PT_FUN_ENTER(l_mdl_id);
	if (msg == NULL)
		return;
	memset(&port_index, 0, sizeof(bc_port_index_t));
	port_index.port_id = msg->port_index.port_id;
	port_index.slot_id = msg->port_index.slot_id;
	port_index.port_type = msg->port_index.port_type;
	if (msg->port_valid == BC_PORT_VALID_TYPE_VALID)
	{
		if ((port_index.port_type == PORT_TYPE_OLT_GEEPON)||(port_index.port_type == PORT_TYPE_OLT_XGEPON))
		{
			mcast_port_update_down_port_state(port_index, TRUE);
		}
		else if ((port_index.port_type == PORT_TYPE_OLT_GESNI)||(port_index.port_type == PORT_TYPE_OLT_XGSNI))
		{
			mcast_port_update_down_port_state(port_index, TRUE);
		}
		else
		{
			//do nothing
		}
	}
	else
	{
		if ((port_index.port_type == PORT_TYPE_OLT_GEEPON)||(port_index.port_type == PORT_TYPE_OLT_XGEPON))
		{
			mcast_port_update_down_port_state(port_index, FALSE);
		}
		else if ((port_index.port_type == PORT_TYPE_OLT_GESNI)||(port_index.port_type == PORT_TYPE_OLT_XGSNI))
		{
			mcast_port_update_down_port_state(port_index, FALSE);
		}
		else
		{
			//do nothing
		}
	}
	BC_PT_FUN_LEAVE(l_mdl_id);
	
	return;	
}

#endif


#if 1
bc_err_e bc_igmp_xx_db_init(void)
{
	bc_int32 i;
	memset(&g_xx_igmp, 0x00, sizeof(bc_igmp_xx_t));
	/*cfg init*/
	g_xx_igmp.igmp_cfg.igmp_mode = BC_IGMP_MODE_DEFAULT;
	g_xx_igmp.igmp_cfg.mqrt = BC_IGMP_MQRT_DEFAULT;
	g_xx_igmp.igmp_cfg.robust_var = BC_IGMP_ROBUST_VAR_DEFAULT;
	g_xx_igmp.igmp_cfg.query_interval = BC_IGMP_QUERY_INTERVAL_DEFAULT;
	g_xx_igmp.igmp_cfg.lmqi = BC_IGMP_LMQI_DEFAULT;
	g_xx_igmp.igmp_cfg.lmqc = BC_IGMP_LMQC_DEFAULT;
	g_xx_igmp.igmp_cfg.ver = BC_IGMP_VER_DEFAULT;

	/*mltcst init*/
	g_xx_igmp.mc_vid_start = 0;
	g_xx_igmp.mc_vid_cnt = 0;
	memset(g_xx_igmp.igmp_mltcst_info, 0, sizeof(bc_igmp_mltcst_xx_info_t)*BC_IGMP_OLT_MLTCST_VLAN_COUNT);

	return BC_ERR_OK;
}

bc_err_e bc_igmp_init()
{		
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);

	bc_igmp_mutex = bc_platform_mutex_create("BC Igmp Mutex");
	if (!bc_igmp_mutex)
	{
		bc_igmp_dbg( "igmp mutex init fail.\n");
	}

	bc_igmp_xx_db_init();
	mcast_init();
	drv_mcst_init();

#if 0	/* todo: event - port valid change */
	ret = bc_port_board_add_evt_reg(BC_MODULE_IGMP,  __bc_igmp_evt_port_valid_change);
	if (ret != BC_ERR_OK)
	{
		BC_PT_DBG_PRINT(l_mdl_id, "%s bc_port_board_add_evt_reg fail:%s.\n", bc_modules_get_module_name(l_mdl_id), bc_msg_err_get(ret, KT_LAN_ENGLISH_E));
	}
#endif
		
	BC_PT_FUN( "Igmp procotol init finished, operation successful.\n");
	
	/* vir rx igmp pkt */					
	vir_rx_igmp_pkt();
		
	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
		
	return BC_ERR_OK;
}

#endif

#if 0
bc_err_e bc_igmp_get_igmp_cfg_info(bc_igmp_cfg_t *igmp_cfg)
{
	if (!igmp_cfg)
		return BC_ERR_PARA;
	
	bc_platform_mutex_lock(bc_igmp_mutex);
	memcpy(igmp_cfg, &g_xx_igmp.igmp_cfg, sizeof(bc_igmp_cfg_t));
	bc_platform_mutex_unlock(bc_igmp_mutex);
	return BC_ERR_OK;
}

bc_err_e bc_igmp_set_igmp_cfg_info(bc_igmp_cfg_t *igmp_cfg)
{
	if (!igmp_cfg)
		return BC_ERR_PARA;
	
	bc_platform_mutex_lock(bc_igmp_mutex);
	memcpy(&g_xx_igmp.igmp_cfg, igmp_cfg,  sizeof(bc_igmp_cfg_t));
	bc_platform_mutex_unlock(bc_igmp_mutex);
	return BC_ERR_OK;
}
#endif


#if 0
bc_err_e bc_igmp_get_igmp_info(bc_igmp_xx_t *igmp_info)
{
	if (!igmp_info)
		return BC_ERR_PARA;
	
	bc_platform_mutex_lock(bc_igmp_mutex);
	memcpy(igmp_info, &g_xx_igmp, sizeof(bc_igmp_xx_t));
	bc_platform_mutex_unlock(bc_igmp_mutex);
	return BC_ERR_OK;
}

bc_err_e bc_igmp_set_igmp_info(bc_igmp_xx_t *igmp_info)
{
	if (!igmp_info)
		return BC_ERR_PARA;
	
	bc_platform_mutex_lock(bc_igmp_mutex);
	memcpy(&g_xx_igmp, igmp_info,  sizeof(bc_igmp_xx_t));
	bc_platform_mutex_unlock(bc_igmp_mutex);
	return BC_ERR_OK;
}

#endif


#if 1

bc_int32 bc_igmp_compar_int32(const void *a ,const void *b)
{
	bc_int32 *aa = (bc_int32*)a;
	bc_int32 *bb = (bc_int32*)b;
    
	if(*aa > *bb)
	{
		return 1;
	}
	else if(*aa == *bb)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}


bc_int32 bc_igmp_compar_port_id(const void *a ,const void *b)
{
	bc_port_index_t *aa = (bc_port_index_t*)a;
	bc_port_index_t *bb = (bc_port_index_t*)b;
    
	if(aa->slot_id > bb->slot_id)
	{
		return 1;
	}
	else if(aa->slot_id == bb->slot_id)
	{
		if(aa->port_type > bb->port_type)
		{
			return 1;
		}
		else if(aa->port_type == bb->port_type)
		{
			if (aa->port_id > bb->port_id)
			{
				return 1;
			}
			else if (aa->port_id == bb->port_id)
			{
				return 0;
			}
			else
			{
				return -1;
			}
		}
		else
		{
			return -1;
		}
	}
	else
	{
		return -1;
	}
}
#endif

#endif

