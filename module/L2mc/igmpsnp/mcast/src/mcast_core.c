/*******************************************************************************
  [File name]	: mcast_core.c
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

#include "mcast_core.h"

#if BC_MULTICAST_INCLUDE

#include "mcast_cfg_grp.h"
#include "mcast_utl.h"
#include "mcast_pkt.h"
#include "mcast_call.h"
#include "bc_platform_thread.h"
#include "mcast_cfg.h"
#if 1
#define MAX_OLT_CHIP_COUNTS 12

#if 1
//SEM
bc_sem_t *mcast_sem;
#define __BC_MCAST_SEM	"bc mcast sem"	/*MCAST 全局信号量*/
//THREAD
static bc_thread_t *bc_mcast_thread;
#define MCAST_THREAD 	"bc mcast thread"
#define MCAST_THREAD_PRI	12

#define BC_MCAST_SEM_LOCK() bc_platform_sem_wait(mcast_sem, BC_SEM_WAIT_FOREVER);
#define BC_MCAST_SEM_UNLOCK()   bc_platform_sem_post(mcast_sem);	

#endif


/*1 - enable, 0 - disable*/
static mcast_ret_code mcast_core_igmp_enable_set(bc_uint8 enable)
{
	drv_mcast_enable(enable);
		
	return MCAST_RET_OK;
}

mcast_ret_code mcast_core_igmp_enable(void)
{
	mcast_core_igmp_enable_set(1);
	
	mcast_cfg_set_state(1);
	/* register igmp rx call back function */
	return MCAST_RET_OK;
}

mcast_ret_code mcast_core_igmp_disable(void)
{
	BC_MCAST_SEM_LOCK();
	drv_mcast_clear();
	mcast_rt_node_clear_all();
	mcast_host_node_clear();
	mcast_host_dyn_router_port_clear();
	mcast_rt_send_query_clear();
	mcast_host_delay_report_clear();
	mcast_host_ver_reset();
	
	mcast_core_igmp_enable_set(0);

	mcast_cfg_def();

	mcast_cfg_set_state(0);
	/* de-register igmp rx call back function */
	BC_MCAST_SEM_UNLOCK();
	return MCAST_RET_OK;
}

mcast_ret_code mcast_core_igmp_ver_proc(IN mcast_igmp_version_e old_ver, IN mcast_igmp_version_e new_ver)
{
	mcast_mode_e mode = 0;
	
	BC_MCAST_SEM_LOCK();
	mcast_host_ver_set(new_ver);
	BC_MCAST_SEM_UNLOCK();

	mcast_cfg_get_mode(&mode);
	
	mcast_core_igmp_disable();

	mcast_core_igmp_enable();

	mcast_cfg_set_mode(mode);

	return MCAST_RET_OK;
}

#if 0 /*bain.wang@outlook.com*/
#include "mcast_ctc_api.h"
#endif

mcast_ret_code mcast_core_igmp_mode_proc(IN mcast_mode_e old_mode, IN mcast_mode_e new_mode)
{
    igmp_dbg("\n");

	if (new_mode == MCAST_MODE_CENTRALIZED)
		MCAST_RET_ERR(MCAST_MODULE_CORE, MCAST_RET_ERR_UNSUPPORT, TRUE);

	if (old_mode == new_mode)
		return MCAST_RET_OK;
	
	if (new_mode == MCAST_MODE_DISABLE)
		mcast_core_igmp_disable();
	else
		mcast_core_igmp_enable();

	return MCAST_RET_OK;
}

#endif
#if 1

mcast_ret_code mcast_core_xx_fwd_get_all(INOUT mcast_core_fwd_t *fwd_block, OUT bc_uint16 *actual_num)
{
	drv_mcast_node_t	mcast_node;
	bc_mac mac;
	bc_uint16 port_idx;
	bc_uint16 fwd_port_idx;
	bc_uint32 cnt;
	bc_char tmp[20];
	
	BC_MCAST_SEM_LOCK();

	*actual_num = 0;
	memset(&mcast_node, 0x00, sizeof(drv_mcast_node_t));
	while (drv_mcsat_get_next(&mcast_node) == BC_ERR_OK)
	{
		fwd_block[*actual_num].grp = mcast_node.grp;
		fwd_block[*actual_num].vid = mcast_node.vid;
		mcast_ip_cvrt_mac(mcast_node.grp, mac);
		memcpy(fwd_block[*actual_num].mac, mac, sizeof(bc_mac));

		fwd_port_idx = 0;
		for (port_idx = 0; port_idx < BC_PORT_PON_MAX_COUNT + BC_PORT_SNI_MAX_COUNT; port_idx++)
		{
			if (mcast_node.grp_fwd_list[port_idx] == TRUE)
			{
				igmp_dbg("pid: %d, group: %s\n", port_idx, ip_format_get(mcast_node.grp, tmp));
				if (port_idx < BC_PORT_SNI_MAX_COUNT)
				{
					fwd_block[*actual_num].port_list[fwd_port_idx].slot_id= BC_PORT_SNI_MAX_SLOTNUM;
					fwd_block[*actual_num].port_list[fwd_port_idx].port_id= port_idx + 1;
					if (port_idx < 4)
						fwd_block[*actual_num].port_list[fwd_port_idx].port_type= PORT_TYPE_OLT_XGSNI;
					else
						fwd_block[*actual_num].port_list[fwd_port_idx].port_type= PORT_TYPE_OLT_GESNI;
				}
				else
				{
					fwd_block[*actual_num].port_list[fwd_port_idx].slot_id= BC_PORT_PON_MIN_SLOTNUM + (port_idx -BC_PORT_SNI_MAX_COUNT)/BC_PORT_PON_MAX_PORTNUM;
					fwd_block[*actual_num].port_list[fwd_port_idx].port_id= (port_idx -BC_PORT_SNI_MAX_COUNT)%BC_PORT_PON_MAX_PORTNUM + 1;
					fwd_block[*actual_num].port_list[fwd_port_idx].port_type= PORT_TYPE_OLT_GEEPON;
				}
				fwd_port_idx++;
			}
		}
		
		(*actual_num)++;
	}
	
	BC_MCAST_SEM_UNLOCK();

	igmp_dbg("group num: %d\n", *actual_num);
	for (cnt = 0; cnt < *actual_num; cnt++)
	{
		igmp_dbg("grp: %s - mac: %02x%02x.%02x%02x.%02x%02x\n",
			ip_format_get(fwd_block[cnt].grp, tmp),
			fwd_block[cnt].mac[0], fwd_block[cnt].mac[1],
			fwd_block[cnt].mac[2], fwd_block[cnt].mac[3],
			fwd_block[cnt].mac[4], fwd_block[cnt].mac[5]);
	}
	//#endif
    
	return MCAST_RET_OK;
}

#endif
#if 1


#endif


#if 1
/* 
		Get all the sources(forward) from grp_node_p, each source is different. 
		Ex.
			grp_node_p.port_grp[port_idx++].src_list	fwd_node_p.src_list[src_num++]
			----------------------------------------	------------------------------
			[0] = {a, b, c}								[0] = a
														[1] = b
														[2] = c
			[1] = {a, c, d}
														[3] = d
			[2]	= {d, e, f}
														[4] = e
														[5] = f
			[3]	= {b, f, g}
														[6] = g
			-------------------------------format-------------------------------------
			[port_idx] = {src-list}						[src-idx] = src
														
														src_num = 7
*/
static mcast_ret_code __mcast_core_chip_src_list_collect(	
	IN mcast_grp_t *grp_node_p, 
	OUT drv_mcast_node_t *fwd_node_p)
{
	bc_int32 i;
	mcast_grp_src_t *src_node_p = NULL;
	bc_int32 src_idx;
	bc_boolean find_src = FALSE;

	fwd_node_p->src_num = 0;
	for (i = 0; i < BC_PORT_PON_MAX_COUNT + BC_PORT_SNI_MAX_COUNT; i++)
	{
		mcast_list_scan(&grp_node_p->port_grp[i].src_list, src_node_p, mcast_grp_src_t*)
		{
			find_src = FALSE;
			for (src_idx = 0; src_idx < fwd_node_p->src_num; src_idx++)
			{
				if (fwd_node_p->src_list[src_idx].src == src_node_p->src)
				{
					find_src = TRUE;	/* avoid repeat */
					break;
				}
			}

			if (find_src == FALSE)
			{
				if (fwd_node_p->src_num >= DRV_MCAST_SRC_MAX)
					MCAST_RET_ERR(MCAST_MODULE_CORE, MCAST_RET_ERR_NORES, TRUE);

				/*
					rfc3367-6.4.1
					A of EXCLUDE(A, B)
					A = a set of source records whose source timers > 0 (Sources that at least one host has requested to be forwarded)
					B = a set of source records whose source timers = 0 (Sources that IGMP will suggest to the routing protocol not to forward)

					If there is a one grp_node_p->port_grp[i].mode is EXLUDE, fwd_node_p->mode must be EXCLUDE, then source-list contain of no forward srcs(B).
				*/
				if (grp_node_p->port_grp[i].mode == MCAST_PBC_RECORD_IS_EXCLUDE && /*this mode of fwd_node_p also is EX*/
					src_node_p->tic != 0) /* !=0 means forward, 0 means no forward. */
					continue; /* because EX contained no forward src. */

				fwd_node_p->src_list[fwd_node_p->src_num].src = src_node_p->src;
				fwd_node_p->src_num++;
			}
		}
	}

	return MCAST_RET_OK;
}

/*
	fill in fwd_node_p:
		filter-mode: IN or EX
		src-list: can be forwards
		src-num:
		src_list[src].src_fwd_list[port] = TRUE or FALSE, means: forwards or no forward.
*/
static mcast_ret_code __mcast_core_chip_fwd_list_collect(
	IN mcast_grp_t *grp_node_p, /*from*/
	OUT drv_mcast_node_t *fwd_node_p)/*to*/
{
	bc_int32 src_idx;
	bc_int32 port_idx;
	mcast_grp_src_t *src_node_p = NULL;
	mcast_pkt_record_type_e fwd_node_mode = MCAST_PBC_RECORD_IS_INCLUDE;

	mcast_ret_code ret = MCAST_RET_OK;

	/* 
		decide filter-mode 

		6.2.1. Definition of Router Filter-Mode
			Conceptually, when a group record is received, the router filter-mode for that group is updated to cover all the requested sources using the least amount of state. 
			As a rule, once a group record with a filter-mode of EXCLUDE is received, the router filter-mode for that group will be EXCLUDE.
	*/
	fwd_node_mode = MCAST_PBC_RECORD_IS_INCLUDE; /* default */
	for (port_idx = 0; port_idx < BC_PORT_PON_MAX_COUNT + BC_PORT_SNI_MAX_COUNT; port_idx++)
	{
		if (grp_node_p->port_grp[port_idx].mode == MCAST_PBC_RECORD_IS_EXCLUDE)
		{	
			fwd_node_p->grp_fwd_list[port_idx] = TRUE; /* at this moment, filter-mode is EX and src-list is null, so this port forward.*/
			fwd_node_mode = MCAST_PBC_RECORD_IS_EXCLUDE; /* decide */
		}
		else
		{
			fwd_node_p->grp_fwd_list[port_idx] = FALSE;/* at this moment, filter-mode is IN and src-list is null, so this port no forward.*/
		}
	}

	/* 
		Get all the sources(forward) from grp_node_p, each source is different. 
		Ex.
			grp_node_p.port_grp[port_idx++].src_list	fwd_node_p.src_list[src_num++]
			----------------------------------------	------------------------------
			[0] = {a, b, c}								[0] = a
														[1] = b
														[2] = c
			[1] = {a, c, d}
														[3] = d
			[2]	= {d, e, f}
														[4] = e
														[5] = f
			[3]	= {b, f, g}
														[6] = g
			-------------------------------format-------------------------------------
			[port_idx] = {src-list}						[src-idx] = src
														
														src_num = 7
	*/
	if ((ret = __mcast_core_chip_src_list_collect(grp_node_p, fwd_node_p)) != MCAST_RET_OK)
	{
		return ret; /* src too much > DRV_MCAST_SRC_MAX */
	}

	/*
		fwd_node_p.src_list		fwd_node_p->src_list[src_idx++].src_fwd_list[port_idx++]	explain
		-------------------		--------------------------------------------------------	----------------------
		[0] = a					[0].src_fwd_list[0] = TRUE									src(a) can to port-0
								[0].src_fwd_list[1] = TRUE									src(a) can to port-1
								[0].src_fwd_list[2] = FALSE									src(a) cannot to port-2
								[0].src_fwd_list[3] = FALSE									src(a) cannot to port-3
		[1] = b
								[1].src_fwd_list[0] = TRUE									src(b) can to port-0
								[1].src_fwd_list[1] = FALSE									src(b) cannot to port-1
								[1].src_fwd_list[2] = FALSE									src(b) cannot to port-2
								[1].src_fwd_list[3] = TRUE									src(b) can to port-3
		[2] = c
								[2].src_fwd_list[0] = TRUE									src(c) can to port-0
								[2].src_fwd_list[1] = TRUE									src(c) can to port-1
								[2].src_fwd_list[2] = FALSE									src(c) cannot to port-2
								[2].src_fwd_list[3] = FALSE									src(c) cannot to port-3
		[3] = d
								[3].src_fwd_list[0] = FALSE									src(d) cannot to port-0
								[3].src_fwd_list[1] = TRUE									src(d) can to port-1
								[3].src_fwd_list[2] = TRUE									src(d) can to port-2
								[3].src_fwd_list[3] = FALSE									src(d) cannot to port-3
		[4] = e
								[4].src_fwd_list[0] = FALSE									src(e) cannot to port-0
								[4].src_fwd_list[1] = FALSE									src(e) cannot to port-1
								[4].src_fwd_list[2] = TRUE									src(e) can to port-2
								[4].src_fwd_list[3] = FALSE									src(e) can to port-3
		[5] = f
								[5].src_fwd_list[0] = FALSE									src(f) cannot to port-0
								[5].src_fwd_list[1] = FALSE									src(f) cannot to port-1
								[5].src_fwd_list[2] = TRUE									src(f) can to port-2
								[5].src_fwd_list[3] = TRUE									src(f) can to port-3
		[6] = g
								[6].src_fwd_list[0] = FALSE									src(g) cannot to port-0
								[6].src_fwd_list[1] = FALSE									src(g) cannot to port-1
								[6].src_fwd_list[1] = FALSE									src(g) cannot to port-2
								[6].src_fwd_list[1] = TRUE									src(g) can to port-3
		-----------------------------------------------format------------------------------------------------------
		[src-idx] = src			[src-idx].[port-idx] = whetherForward						src    whetherForards port-idx		
		
	*/
	/* find ports that each src appeared. */
	for (src_idx = 0; src_idx < fwd_node_p->src_num; src_idx++)
	{
		for (port_idx = 0; port_idx < BC_PORT_PON_MAX_COUNT + BC_PORT_SNI_MAX_COUNT; port_idx++)
		{
			src_node_p = (mcast_grp_src_t*)mcast_list_find(&grp_node_p->port_grp[port_idx].src_list, fwd_node_p->src_list[src_idx].src);
			if (src_node_p != NULL) /* appear this port. */
			{
				/*
				rfc3367-6.2.3
				Source timers are treated differently when a router filter-mode for a group is EXCLUDE.	
				If a source record has a running timer with a router filter-mode for the group of EXCLUDE, it means that at least one system desires the source.	
				It should therefore be forwarded  by a router on the network.

				rfc3367-6.2.1
				When a router filter-mode for a group is EXCLUDE, the source record list contains two types of sources.	
				The first type is the  set which represents conflicts in the desired reception state; this set must be forwarded by some router on  the network.	
				The second type is the set of sources which hosts have requested to not be forwarded.

				rfc3367-6.4.1
				format:
				EXCLUDE(A, B)
				The notation ( A, B ) will be used to represent the total number of sources for a particular group, where
				A = set of source records whose source timers > 0 (Sources that at least one host has requested to be forwarded)
				B = set of source records whose source timers = 0 (Sources that IGMP will suggest to the routing protocol not to forward)

				Group
				Filter-Mode 	Source Timer Value		Action
				----------- 	------------------		------
				EXCLUDE 		TIMER > 0				Suggest to forward traffic from source
				EXCLUDE 		TIMER == 0				Suggest to not forward traffic from source (DO NOT remove record)
				*/
				if (grp_node_p->port_grp[port_idx].mode == MCAST_PBC_RECORD_IS_EXCLUDE) /*all src in fwd_node_p no forard.*/
				{
					if (src_node_p->tic != 0) /* mode is EX, but tic is not zero, forward. */
						fwd_node_p->src_list[src_idx].src_fwd_list[port_idx] = TRUE;
					else
						fwd_node_p->src_list[src_idx].src_fwd_list[port_idx] = FALSE;
				}
				/*
				rfc3367-6.4.1
				Note that there will only be two sets when a router's filter-mode for a group is EXCLUDE.	
				When a router's filter-mode for a group is INCLUDE, a single set is used to describe the set of sources requested to be forwarded (e.g., simply (A)).
				*/
				else /* MCAST_PBC_RECORD_IS_INCLUDE */
				{
					fwd_node_p->src_list[src_idx].src_fwd_list[port_idx] = TRUE;
				}
			}
			else /* no find, means: this port was not set this src. */
			{
				if (fwd_node_mode == MCAST_PBC_RECORD_IS_INCLUDE)/* all port is IN */
				{
					fwd_node_p->src_list[src_idx].src_fwd_list[port_idx] = FALSE; /* IN but no set this src. */
				}
				else /* fwd_node_mode == MCAST_PBC_RECORD_IS_EXCLUDE, at least one port is EX*/
				{
					if (grp_node_p->port_grp[port_idx].mode == MCAST_PBC_RECORD_IS_EXCLUDE)
						fwd_node_p->src_list[src_idx].src_fwd_list[port_idx] = TRUE;/* EX but no set this src. */
					else
						fwd_node_p->src_list[src_idx].src_fwd_list[port_idx] = FALSE;/* IN but no set this src. */
				}
			}
		}
	}

	return MCAST_RET_OK;
}
//#endif

/*
	process rx report msg.
	
	as route:
		1. get src-list from record of this report. (for merge)
		2. merge this src-list and existed src-list in router, update this new src-list to router. (for update mcast_grp_tree)
	other:
		transition new src-list to forward table, and update this table to chip.
	as host:
		1. get src-list from record of this report. (for update mcast_host_tree)
		2. merge this src-list and existed src-list in host, update this new src-list to host. (for merge with mcast_delay_report_tree)
		3. merge this src-list and src-list of pending host record, and update new src-list to mcast_delay_report_tree. (for update mcast_delay_report_tree)

	refrences:
		6.4. Action on Reception of Reports 
		switch chip
		5.1. Action on Change of Interface State
*/
static mcast_ret_code __mcast_core_proc_report_record(
	IN bc_port_index_t rx_port, 
	IN mcast_pkt_type_e pkt_type, 
	IN mcast_pkt_igmp_report_record_t *record)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);

#if 1	/*debug*/
	int i = 0;
	bc_char tmp[20];
	BC_PT_DBG_SMP(BC_MODULE_IGMP, "  grp:%s, vid:%d, pkt_type:0x%x, record_type:0x%x, num_of_src:%d\n",
					ip_format_get(record->grp, tmp), record->vid, pkt_type, record->record_type, record->num_of_src);
	for(i=0; i<record->num_of_src; i++)
	{
		BC_PT_DBG_SMP(BC_MODULE_IGMP, "  [%d]: %s\n", i+1, ip_format_get(record->src[i], tmp));
	}
#endif
	BC_PT_DBG_SMP(BC_MODULE_IGMP, "-------------------------------------------\n");

	mcast_list_t new_src_list;
	mcast_grp_t *grp_node_p = NULL;
	//bc_int16 vid = 0, tmp = 0;
	mcast_ret_code ret = MCAST_RET_OK;

	mcast_list_init(&new_src_list, mcast_utl_src_cmp);

	/*get new_src_list from rx*/
	if (mcast_src_list_alloc(record->num_of_src, record->src, &new_src_list) == FALSE)
	{
		BC_PT_DBG_FUN(BC_MODULE_IGMP, "process mcast_src_list_alloc failure\n");
		MCAST_RET_ERR(MCAST_MODULE_CORE, MCAST_RET_ERR_NORES, TRUE);
	}
	BC_PT_DBG_FUN(BC_MODULE_IGMP, "<1> process new_src_list successful\n");
	
	//mcast_vlan_get_next(tmp, &vid);
	
	/* merge new_src_list and old from mcast_grp_tree, update to this tree */
	ret = mcast_rt_proc_port_grp_info(rx_port, record->grp, record->vid, pkt_type, record->record_type, &new_src_list);
	mcast_src_list_free(&new_src_list);
	if (ret != MCAST_RET_OK)
	{
		BC_PT_DBG_FUN(BC_MODULE_IGMP, "process route node endpoint failure\n");
		return ret;
	}
	BC_PT_DBG_FUN(BC_MODULE_IGMP, "<2> process route node endpoint successful\n");

	grp_node_p = mcast_rt_node_get(record->grp);
	if (grp_node_p == NULL)
	{
		MCAST_RET_ERR(MCAST_MODULE_CORE, MCAST_RET_ERR_NOTFOUND, TRUE);
	}

	/* above src-list transition to fwd list, and update switch chip. */
	if((ret = mcast_core_update_grp_node_to_chip(grp_node_p)) != MCAST_RET_OK)
	{
		BC_PT_DBG_FUN(BC_MODULE_IGMP, "process drv node endpoint failure\n");
		return ret;
	}
	BC_PT_DBG_FUN(BC_MODULE_IGMP, "<3> process drv node endpoint successful\n");

	/*
	trigger report and update host grp state
		5.1. Action on Change of Interface State
	*/
	if((ret = mcast_host_trigger_report(grp_node_p)) != MCAST_RET_OK)
	{
		BC_PT_DBG_FUN(BC_MODULE_IGMP, "process host node endpoint failure\n");
		return ret;
	}
	BC_PT_DBG_FUN(BC_MODULE_IGMP, "<4> process host node endpoint successful\n");

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return ret;
}

/* above src-list transition to fwd list, and update switch chip. */
mcast_ret_code mcast_core_update_grp_node_to_chip(IN mcast_grp_t *grp_node_p)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
   // #if defined (__BC_IGMP_HAVE_DRV__)
	drv_mcast_node_t 	fwd_node;

	mcast_ret_code ret;
	bc_err_e drv_ret;

	/* generate forward table */
	memset(&fwd_node, 0x00, sizeof(drv_mcast_node_t));
	fwd_node.grp = grp_node_p->grp;
	fwd_node.vid = grp_node_p->vid;
	/*
		fill in fwd_node:
			filter-mode: IN or EX
			src-list: can be forwards
			src-num:
			src_list[src].src_fwd_list[port] = TRUE or FALSE, means: forwards or no forward.
	*/
	if ((ret = __mcast_core_chip_fwd_list_collect(grp_node_p, &fwd_node)) != MCAST_RET_OK)
	{
		BC_PT_DBG_FUN(BC_MODULE_IGMP, "__mcast_core_chip_fwd_list_collect failure!\n");
		return ret;
	}
	BC_PT_DBG_FUN(BC_MODULE_IGMP, "__mcast_core_chip_fwd_list_collect successful!\n");

	/* update mcast forward table in chip. */
	if ((drv_ret = drv_mcast_update(&fwd_node)) != BC_ERR_OK)
	{
		BC_PT_DBG_FUN(BC_MODULE_IGMP, "drv_mcast_update failure!\n");
		MCAST_RET_ERR(MCAST_MODULE_CORE, MCAST_RET_ERR_DRVERR, TRUE);	
	}
  //  #endif
	BC_PT_DBG_FUN(BC_MODULE_IGMP, "drv_mcast_update successful!\n");
  
  	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
  
	return MCAST_RET_OK;
}

/*
	There are two IGMP message types of concern to the IGMPv3 protocol described in this document:
	Type Number (hex) 	Message Name
	----------------- 	------------
	0x11		 		Membership Query
	0x22 				Version 3 Membership Report 
	
	An implementation of IGMPv3 MUST also support the following three message types, 
	for interoperation with previous versions of IGMP (see section 7):
	
	0x12 				Version 1 Membership Report [RFC-1112]
	0x16 				Version 2 Membership Report [RFC-2236]
	0x17 				Version 2 Leave Group [RFC-2236]
*/
mcast_ret_code mcast_core_igmp_process(IN mcast_rx_node_t *pkt, IN mcast_pkt_igmp_t *igmp)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	bc_uint32 i;
	mcast_cfg_t cfg;
	mcast_ret_code ret = MCAST_RET_OK;
	mcast_cfg_grp_t cfg_grp;

	mcast_cfg_get(&cfg);
	switch (igmp->pkt_type)
	{
	case MCAST_PBC_TYPE_V1_REPORT:/*0x12*/
	case MCAST_PBC_TYPE_V2_REPORT:/*0x16*/
	case MCAST_PBC_TYPE_V3_REPORT:/*0x22*/
		BC_PT_DBG_SMP(BC_MODULE_IGMP, "\ntotal_record:%d, rx_port:%d-%d-%d\n", igmp->rept.num_of_record, pkt->rx_port.slot_id,pkt->rx_port.port_type,pkt->rx_port.port_id);
		for (i = 0; i < igmp->rept.num_of_record; i++)
		{
			BC_PT_DBG_SMP(BC_MODULE_IGMP, "\n-------------------------------------------\n");
			BC_PT_DBG_SMP(BC_MODULE_IGMP, "current record: %d/%d\n", i+1, igmp->rept.num_of_record);
			if (cfg.mode == MCAST_MODE_DISTRIBUTEDWITHCM)
			{
				BC_PT_DBG_SMP(BC_MODULE_IGMP, "mode: MCAST_MODE_DISTRIBUTEDWITHCM, port: %d, llid: %d, grp: %lu, vid: %d\n",
					(bc_int32)pkt->rx_port.port_id, (bc_int32)pkt->llid, igmp->recd[i].grp, (bc_int32)igmp->eth_hdr.cvlan.vlan_id);

				if (mcast_cfg_grp_search_by_ip(igmp->recd[i].grp, 1, &cfg_grp) == FALSE)
					MCAST_RET_ERR(MCAST_MODULE_CORE, MCAST_RET_ERR_NOTFOUND, TRUE);
				
				BC_PT_DBG_SMP(BC_MODULE_IGMP, "vid: %d\n", cfg_grp.vid);
				igmp->recd[i].vid = cfg_grp.vid;/*recd.vid != cfg.vid*/
			}
			else if (cfg.mode == MCAST_MODE_DISTRIBUTEDWOCM)
			{
				BC_PT_DBG_SMP(BC_MODULE_IGMP, "mode: MCAST_MODE_DISTRIBUTEDWOCM\n");
				/*
				if (mcast_cfg_grp_cfg_exist(igmp->recd[i].grp, igmp->eth_hdr.cvlan.vlan_id) == FALSE)
				{
					igmp_dbg("\n");
					continue ;
				}
				*/
			}
			else
			{
				BC_PT_DBG_SMP(BC_MODULE_IGMP, "UNKOWN mode: %d\n", cfg.mode);
				return MCAST_RET_OK;
			}
			ret |= __mcast_core_proc_report_record(pkt->rx_port, igmp->pkt_type, &(igmp->recd[i]));
			BC_PT_DBG_SMP(BC_MODULE_IGMP, "report:%d/%d process finished. op_status:%s\n", i+1, igmp->rept.num_of_record, ret==MCAST_RET_OK?"successful":"failure");
		}
		break;
		
	case MCAST_PBC_TYPE_LEAVE:/*0x17*/
		ret = mcast_rt_proc_leave(pkt->rx_port, igmp->recd[0].grp);
		break;
		
	case MCAST_PBC_TYPE_QUERY:/*0x11*/
		mcast_host_dyn_router_port_proc(pkt->rx_port);/*dyn learn port*/
		mcast_host_ver_update_tic(igmp->qy.query_ver);	/*compatibility mode*/

		/*
		1. A "General Query" 
		is sent by a multicast router to learn the
		complete multicast reception state of the neighboring interfaces
		(that is, the interfaces attached to the network on which the
		Query is transmitted). In a General Query, both the Group Address
		field and the Number of Sources (N) field are zero.
		*/
		if (igmp->qy.grp == 0)
		{
			ret = mcast_host_proc_gen_query(&(igmp->qy));
		}
		/*
		2. A "Group-Specific Query" 
		is sent by a multicast router to learn
		the reception state, with respect to a *single* multicast address,
		of the neighboring interfaces. In a Group-Specific Query, the
		Group Address field contains the multicast address of interest,
		and the Number of Sources (N) field contains zero.
		*/
		else if (igmp->qy.num_of_src == 0)
		{
			ret = mcast_host_proc_grp_spec_query(&(igmp->qy));
		}
		/*
		3. A "Group-and-Source-Specific Query" 
		is sent by a multicast router
		to learn if any neighboring interface desires reception of packets
		sent to a specified multicast address, from any of a specified
		list of sources. In a Group-and-Source-Specific Query, the Group
		Address field contains the multicast address of interest, and the
		Source Address [i] fields contain the source address(es) of interest.
		*/
		else
		{
			ret = mcast_host_proc_grp_src_spec_query(&(igmp->qy));
		}
		break;
		
	default:/*Unrecognized message types MUST be silently ignored.*/
		BC_PT_DBG_FUN(BC_MODULE_IGMP, "pkt_type is unKnow!\n");
		break;
	}
	BC_PT_DBG_SMP(BC_MODULE_IGMP, "============================================\n");
	mcast_rt_grp_dump();
	
	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return MCAST_RET_OK;
}

#endif
#if 1

/* every 0.1s call the function once */
static void __mcast_core_tic(void)
{
	mcast_cfg_t mcast_cfg;

	memset(&mcast_cfg, 0x00, sizeof(mcast_cfg_t));
	
	mcast_cfg_get(&mcast_cfg);
	if (mcast_cfg.enable == FALSE)
		return;
	
#if 0 /*bain.wang@outlook.com*/
	if (mcast_ctc_mode)
	{
		mcast_ctrlmc_tic();
	}
#endif

	BC_PT_DBG_SMP(BC_MODULE_IGMP, "\nmcast_host_ver_tic begain.....\n");
	mcast_host_ver_tic();
	BC_PT_DBG_SMP(BC_MODULE_IGMP, "mcast_host_ver_tic finish.....\n");


	BC_PT_DBG_SMP(BC_MODULE_IGMP, "\nmcast_host_dyn_router_port_tic begain.....\n");
	mcast_host_dyn_router_port_tic();
	BC_PT_DBG_SMP(BC_MODULE_IGMP, "mcast_host_dyn_router_port_tic finish.....\n");

	BC_PT_DBG_SMP(BC_MODULE_IGMP, "\nmcast_host_send_report_tic begain.....\n");
	mcast_host_send_report_tic();
	BC_PT_DBG_SMP(BC_MODULE_IGMP, "mcast_host_send_report_tic finish.....\n");
	
	BC_PT_DBG_SMP(BC_MODULE_IGMP, "\nmcast_rt_send_query_tic begain.....\n");
	mcast_rt_send_query_tic();
	BC_PT_DBG_SMP(BC_MODULE_IGMP, "mcast_rt_send_query_tic finish.....\n");

	BC_PT_DBG_SMP(BC_MODULE_IGMP, "\n");

	BC_PT_DBG_SMP(BC_MODULE_IGMP, "\nmcast_rt_grp_tic begain.....\n");
	mcast_rt_grp_tic();
	BC_PT_DBG_SMP(BC_MODULE_IGMP, "mcast_rt_grp_tic finish.....\n");
	
}

static void __mcast_core_task_counter()
{
	static int d=0, h=0, m=0, s=0, ms=0;

	ms++;
	if(ms == 10){
		ms = 0;
		s++;
		if(s == 60){
			s = 0;
			m++;
			if(m==60){
				m=0;
				h++;
				if(h == 24){
					h=0;
					d++;
				}
			}
		}
	}
	BC_PT_DBG_SMP(BC_MODULE_IGMP, "\nthread __mcast_core_task active [%d - %d:%d:%d] times.....\n", d, h, m, s);
}
static void * __mcast_core_task(IN void *argv)
{
	mcast_cfg_t cfg;
	bc_platform_thread_id_get();
	memset(&cfg, 0x00, sizeof(mcast_cfg_t));

	while (1)
	{
		__mcast_core_task_counter();

		mcast_cfg_get(&cfg);
		
		if (MCAST_MODE_DISABLE != cfg.mode)
		{
			BC_MCAST_SEM_LOCK();
			__mcast_core_tic();
			BC_MCAST_SEM_UNLOCK();
			mcast_os_task_sleep(MCAST_TIC_INTERVAL);/* sleep 0.1s */
			continue;
		}
		mcast_os_task_sleep(MCAST_TIC_INTERVAL);
	}

    return NULL;
}

#endif

#if 1
void mcast_core_init(void)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);

	mcast_sem = bc_platform_sem_create((bc_char*)__BC_MCAST_SEM, 1); 
	if(NULL == mcast_sem)
	{
		BC_PT_ERROR(BC_MODULE_FILETRANS, "Failed to create mcast sem!\n");
	//	return BC_ERR_RESOURCE;
	}
	
	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
}

/* init tic */
void mcast_core_task_init(void)
{
	bc_mcast_thread = bc_platform_thread_create(
													(bc_char*)MCAST_THREAD,
													1024 * BC_THREAD_1K_STACK_SIAE, 
													MCAST_THREAD_PRI,
													(const void *)__mcast_core_task, 
													NULL);
	if (NULL == bc_mcast_thread)
	{
		BC_PT_ERROR(BC_MODULE_FILETRANS, "Failed to create mcast thread!\n");
	//	return BC_ERR_RESOURCE;
	}
}

#endif

#endif

