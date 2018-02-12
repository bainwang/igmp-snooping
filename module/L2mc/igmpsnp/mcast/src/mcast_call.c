/*******************************************************************************
  [File name]	: mcast_call.c
  [Author]     	: bain.wang@outlook.com
  [Version]    	: 1.0
  [Date]       	: 2017-06-13
  [Description]	:
	Multicast module CALL for multicast access other module
  [Others]     	:
	NULL
  [Function List]:  
    1. ....
    2. ....
  [History]:
	 D a t e      	Modification 							 Initials
	---------- 	--------------                               ----------
	2017-06-15  	Created								 bain.wang@outlook.com
*******************************************************************************/

#include "mcast_call.h"

#if BC_MULTICAST_INCLUDE

#include "mcast_rx.h"

#if 0 /*bain.wang@outlook.com*/
#include "Drv_sys.h"
#include "drv_pkt.h"
#include "Drv_def.h"
#include "mcast_ctc_api.h"
#endif
#include "mcast_cfg.h"

#if 0 /*bain.wang@outlook.com*/
#include "bc_pkt.h"
#include "bc_onu_api.h"
#endif

#include "bc_igmp_def.h"    /*for BC_IGMP_PORT_TYPE_IS_PON() & bc_onu_id_get()*/
#include "bc_platform_thread.h"

#if 1 /*bain.wang@outlook.com*/
#include "bc_proj_onumgmt_defs.h"
#include "stdlib.h"
#include "string.h"
#endif

#define MAX_SNI_PORT_NUM         8  /* 最大的SNI 端口数 */

#if 1
static bc_err_e mcast_rx_callback(bc_pkt_rx_t *pkt)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	mcast_rx_node_t mc_pkt;

	mcast_cfg_t cfg;
	mcast_cfg_get(&cfg);

	if (MCAST_MODE_DISABLE == cfg.mode)
	{
		return BC_ERR_NOT_SUPPORT;
	}
	memset(&cfg, 0x00, sizeof(mcast_cfg_t));
	memset(&mc_pkt, 0x00, sizeof(mcast_rx_node_t));
	mc_pkt.rx_port = pkt->recv_src_port;

	igmp_dbg("receive pkt from port: %d(slot: %d, pid: %d)\n",
		pkt->recv_src_port.port_id, pkt->recv_src_port.slot_id, pkt->recv_src_port.port_id);
#if 0 /*bain.wang@outlook.com*/
	mc_pkt.llid = pkt->llid;
#endif
	mc_pkt.vid = pkt->vid;
	mc_pkt.buf_len = pkt->pkt_buf_len;
	mc_pkt.buf = (bc_uint8*)pkt->pkt_buf;
	mc_pkt.free = NULL;

	mcast_rx_receive_pkt(&mc_pkt);

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return BC_ERR_OK;
}

void mcast_call_pkt_register(void)
{
#if 0 /*todo*/
	if (bc_pkt_rx_reg(BC_MODULE_IGMP, BC_PBC_TYPE_IGMP_E, mcast_rx_callback) != BC_ERR_PBC_OK)
	{
		MCAST_LOG(MCAST_MODEULE_CALL, MCAST_RET_ERR_DRVERR, TRUE);
	}
#endif
}



void mcast_call_get_host_mac(OUT bc_mac mac)
{

}


void mcast_call_get_host_ip(OUT bc_uint32 *host_ip)
{

}


void mcast_call_get_port_vlan_state(IN bc_port_index_t port, OUT bc_int16 *pvid, OUT bc_boolean *tag)
{

}


bc_boolean mcast_call_get_xx_ports(IN bc_port_index_t *sni_ports, IN bc_port_index_t *epon_ports)
{
	bc_uint16 idx;

	for (idx = 0; idx < BC_PORT_SNI_MAX_COUNT; idx++)
	{
		sni_ports[idx].slot_id = 0;
		sni_ports[idx].port_type = PORT_TYPE_OLT_GESNI;
		sni_ports[idx].port_id = idx+1;
	}

	for (idx = 0; idx < BC_PORT_PON_MAX_COUNT; idx++)
	{
		epon_ports[idx].slot_id = 0;
		epon_ports[idx].port_type = PORT_TYPE_OLT_GEEPON;
		epon_ports[idx].port_id = idx+1;
	}

	return TRUE;
}

void mcast_call_tx(
	IN bc_port_index_t send_port, 
	IN bc_int16 pkt_length, 
	IN bc_uint8 *pkt, 
	IN bc_int8 cos,
	IN bc_int16 vlan, 
	IN mcast_tx_free_func free_func)
{
#if 0 /*todo*/
	bc_pkt_tx_t send_pkt;
	bc_port_index_t tag_ports[1];

	memset(&send_pkt, 0x00, sizeof(send_pkt));
    memcpy(send_pkt.pkt_buf, pkt, pkt_length);
	//send_pkt.pkt_buf = (bc_int8*)pkt;
	send_pkt.pkt_buf_len = pkt_length;

    send_pkt.priority = cos;
	send_pkt.vid = vlan;

	send_pkt.tag_ports_num = 0;
	
	//send_pkt.untag_ports_num = 1;
	//send_pkt.untag_ports = &send_port;
	send_pkt.tag_ports_num = 1;
	send_pkt.tag_ports = tag_ports;
	tag_ports[0] = send_port;
	
	if (bc_pkt_tx(BC_MODULE_IGMP, &send_pkt) != BC_ERR_PBC_OK)
	{
		MCAST_LOG(MCAST_MODEULE_CALL, MCAST_RET_ERR_TXERRR, TRUE);
	}
	igmp_dbg("free_func\n");
	if (free_func)
		(*free_func)(pkt);
#endif
}

#endif

#if 1

void mcast_os_sem_create(IN bc_sem_t ** sem)
{
	if (NULL == (*sem = bc_platform_sem_create("bc mcast sem", 1)))
		MCAST_DBG_PRT("multicast core semaphore create fail.\n");
}

void mcast_os_sem_delete(IN bc_sem_t * sem)
{
	bc_platform_sem_destroy(sem);
}

static bc_thread_t * n_tid;
void mcast_os_task_create(void*(*task)(void*argv))
{
	n_tid = bc_platform_thread_create("BC IGMP", 1024 * BC_THREAD_1K_STACK_SIAE, 12, (const void *)task, NULL);
	if (n_tid == NULL)
		MCAST_DBG_PRT("create thread fail\n");
}

void mcast_os_task_sleep(IN bc_uint32 millisecond)
{
	usleep(millisecond);
}

/* 0 ~ max_limit */
bc_uint16 mcast_random(IN bc_uint16 max_limit)
{
	return rand()%max_limit+1;
}

#endif

#endif


#if 1 /*bain.wang@outlook.com*/
/*add by bain.wang@outlook.com for fix vir igmp packet*/

void vir_fix_igmp_pkt(bc_pkt_rx_t *pkt)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
#if 0
	//query
	unsigned char array1[] = {
    0x01, 0x00, 0x5e, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x08, 0x00, 0x45, 0xc0, 
    0x00, 0x2c, 0x00, 0x01, 0x00, 0x00, 0x01, 0x02, 0x13, 0x03, 0xc0, 0xa8, 0x05, 0x63, 0xe0, 0x00, 
    0x00, 0x01, 0x11, 0x1e, 0xa1, 0xdb, 0x00, 0x00, 0x00, 0x00, 0x02, 0x41, 0x00, 0x03, 0xc0, 0xa8, 
    0x01, 0x6f, 0xc0, 0xa8, 0x01, 0xde, 0xc0, 0xa8, 0x05, 0x7b, };
#elif 0
	//report v2
	unsigned char array2[] = {
	0x01, 0x00, 0x5e, 0x7f, 0xff, 0xfa, 0xd4, 0xc9, 0xef, 0xfe, 0x38, 0xa6, 0x08, 0x00, 0x46, 0x00,	
	0x00, 0x20, 0x03, 0x02, 0x00, 0x00, 0x01, 0x02, 0x70, 0x29, 0xc0, 0xa8, 0x01, 0x0a, 0xef, 0xff,
	0xff, 0xfa, 0x94, 0x04, 0x00, 0x00, 0x16, 0x00, 0xfa, 0x04, 0xef, 0xff, 0xff, 0xfa, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
#elif 1
	/* length=146 */
unsigned char array3[] = {/*report V3, build five*/
    0x01, 0x00, 0x5e, 0x00, 0x00, 0x16, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x32, 0x81, 0x00, 0x00, 0x02, 
    0x08, 0x00, 0x45, 0xc0, 0x00, 0x80, 0x00, 0x01, 
    0x00, 0x00, 0x01, 0x02, 0x12, 0x9a, 0xc0, 0xa8, 
    0x05, 0x63, 0xe0, 0x00, 0x00, 0x16, 0x22, 0x1e, 
    0xbc, 0x8b, 0x22, 0x00, 0x00, 0x05, 0x01, 0x00, 
    0x00, 0x03, 0xea, 0x05, 0x06, 0x07, 0xc0, 0xa8, 
    0x00, 0x01, 0xc0, 0xa8, 0x00, 0x02, 0xc0, 0xa8, 
    0x00, 0x03, 0x01, 0x00, 0x00, 0x03, 0xea, 0x05, 
    0x06, 0x07, 0xc0, 0xa8, 0x00, 0x01, 0xc0, 0xa8, 
    0x00, 0x02, 0xc0, 0xa8, 0x00, 0x03, 0x01, 0x00, 
    0x00, 0x03, 0xea, 0x05, 0x06, 0x07, 0xc0, 0xa8, 
    0x00, 0x01, 0xc0, 0xa8, 0x00, 0x02, 0xc0, 0xa8, 
    0x00, 0x03, 0x01, 0x00, 0x00, 0x03, 0xea, 0x05, 
    0x06, 0x07, 0xc0, 0xa8, 0x00, 0x01, 0xc0, 0xa8, 
    0x00, 0x02, 0xc0, 0xa8, 0x00, 0x03, 0x01, 0x00, 
    0x00, 0x03, 0xea, 0x05, 0x06, 0x07, 0xc0, 0xa8, 
    0x00, 0x01, 0xc0, 0xa8, 0x00, 0x02, 0xc0, 0xa8, 
    0x00, 0x03, };
#else
#endif
	pkt->vid = 1;
	pkt->recv_src_port.slot_id = 5;
	pkt->recv_src_port.port_type = PORT_TYPE_OLT_GEEPON;
	pkt->recv_src_port.port_id = 1;
	memcpy(pkt->pkt_buf, array3, sizeof(array3));
	pkt->pkt_buf_len = sizeof(array3)/sizeof(unsigned char);

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
}

void vir_rx_igmp_pkt()
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	bc_pkt_rx_t pkt;
	vir_fix_igmp_pkt(&pkt);
	mcast_rx_callback(&pkt);

	BC_PT_DBG_SMP(BC_MODULE_IGMP, "\n############################################################\n");
	
	mcast_rt_grp_dump();
	BC_PT_DBG_SMP(BC_MODULE_IGMP, "\n\n");
	
	mcast_rt_query_list_dump();
	BC_PT_DBG_SMP(BC_MODULE_IGMP, "\n\n");
	
	mcast_rt_gen_query_dump();
	BC_PT_DBG_SMP(BC_MODULE_IGMP, "\n\n");
	
	mcast_host_tree_dump();
	BC_PT_DBG_SMP(BC_MODULE_IGMP, "\n\n");
	
	mcast_host_query_dump();
	BC_PT_DBG_SMP(BC_MODULE_IGMP, "\n\n");
	
	mcast_host_delay_report_dump();
	BC_PT_DBG_SMP(BC_MODULE_IGMP, "\n\n");
	
	mcast_host_ver_dump();
	BC_PT_DBG_SMP(BC_MODULE_IGMP, "\n\n");
	
	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
}
#endif

