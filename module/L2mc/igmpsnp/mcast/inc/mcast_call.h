/*******************************************************************************
  [File name]	: mcast_call.h
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
	---------- 	--------------                                        ----------
	2017-06-15  	Created								 bain.wang@outlook.com
*******************************************************************************/

#ifndef __mcast_call_h__
#define __mcast_call_h__

#include "mcast_def.h"
#include "utili_list.h"
#include "utili_avlt.h"
#include "bc_platform_mem.h"
#include "bc_platform_sem.h"
#include "bc_print.h"

#if BC_MULTICAST_INCLUDE

#if MCAST_WINDOWS_TEST
#include "../../../../../inc/winpcap.h"
#include "../../../../../inc/platform.h"
#else
#include <semaphore.h>
#include <pthread.h>
#endif

#if 1 /*add by bain.wang@outlook.com*/

#define BC_PBC_LEN 2048

typedef enum {
	BC_PBC_TYPE_UNK_E 	= 0x00,
	BC_PBC_TYPE_STP_E,
	BC_PBC_TYPE_BCMP_E,
	BC_PBC_TYPE_IP_E,
	BC_PBC_TYPE_ARP_E,
	BC_PBC_TYPE_IPv6_E,
	BC_PBC_TYPE_OAM_E,
	BC_PBC_TYPE_IGMP_E,
	
	BC_PBC_TYPE_NUM_E,
} bc_pkt_type_e;

typedef struct {
	bc_int32 	 	cos;
	bc_int16		llid;
	bc_boolean 	tagged;
	bc_int16		vid;
	bc_int8		priority;

	bc_port_index_t recv_src_port;

	bc_pkt_type_e pkt_type;

	bc_int8		pkt_buf[BC_PBC_LEN];
	bc_int32		pkt_buf_len;
} bc_pkt_rx_t;


#endif



#if 1

#define mcast_list_t			utili_list
#define mcast_list_node_t	utili_node

#define mcast_list_init(list_p, cmp)		utili_lst_init((utili_list*)(list_p), cmp)
#define mcast_list_count(list_p)			utili_lst_count((utili_list*)(list_p))
#define mcast_list_first(list_p)			utili_lst_first((utili_list*)(list_p))
#define mcast_list_next(node_p)			utili_lst_next((utili_node*)(node_p))
#define mcast_list_add(list_p, node_p)		utili_lst_add((utili_list*)(list_p), (utili_node*)(node_p))
#define mcast_list_delete(list_p, node_p) 	utili_lst_delete((utili_list*)(list_p), (utili_node*)(node_p))
#define mcast_list_find(list_p, key)		utili_lst_find((utili_list*)(list_p), (unsigned int)(key))

#define mcast_list_scan(list_p , node_p , type)	utili_lst_scan(list_p , node_p , type)

#endif
#if 1

#define mcast_avltree_t 		utili_avlt_tree_t
#define mcast_avltree_comp_func utili_avlt_comp_func

#define mcast_avltree_create(cmp, param)	 	utili_avlt_create(cmp, param)
#define mcast_avltree_find(tree, item)		 	utili_avlt_find(tree, item)
#define mcast_avltree_get_next(tree, item) 		utili_avlt_next(tree, item)
#define mcast_avltree_insert(tree, item)	 	utili_avlt_insert(tree, item)
#define mcast_avltree_delete(tree, item)		utili_avlt_delete(tree, item)

#endif
#if 1

void mcast_call_get_host_mac(OUT bc_mac mac);
void mcast_call_get_host_ip(OUT bc_uint32 *host_ip);
void mcast_call_get_port_vlan_state(IN bc_port_index_t port, OUT bc_int16 *pvid, OUT bc_boolean *tag);
bc_boolean mcast_call_get_xx_ports(IN bc_port_index_t *sni_ports, IN bc_port_index_t *epon_ports);

typedef void (*mcast_tx_free_func)(void*);

void mcast_call_tx(
	IN bc_port_index_t send_port, 
	IN bc_int16 pkt_length, 
	IN bc_uint8 *pkt, 
	IN bc_int8 cos,
	IN bc_int16 vlan, 
	IN mcast_tx_free_func free);


void mcast_call_pkt_register(void);

#endif
#if 1

#if MCAST_WINDOWS_TEST 
typedef OS_SEM_HANDLE	mcast_sem_handle;
#define mcast_os_sem_lock(sem) 		OS_Sem_Lock(&(sem))
#define mcast_os_sem_unlock(sem) 	OS_Sem_Unlock(&(sem))
#else
typedef bc_uint32 mcast_sem_handle;
#define mcast_os_sem_lock(sem)		bc_platform_sem_wait_ex(sem, BC_SEM_WAIT_FOREVER, (bc_char *)__FUNCTION__, __LINE__);
#define mcast_os_sem_unlock(sem)	bc_platform_sem_post(sem)
#endif

void mcast_os_sem_create(IN bc_sem_t ** sem);
void mcast_os_sem_delete(IN bc_sem_t * sem);

void mcast_os_task_create(void*(*task)(void*argv));
void mcast_os_task_sleep(IN bc_uint32 millisecond);


#define mcast_alloc(size) 	bc_platform_mem_malloc(BC_MODULE_IGMP, size)
#define mcast_free(p) 		do {if (p != NULL) bc_platform_mem_free(BC_MODULE_IGMP, p);}while(0)
bc_uint16 mcast_random(IN bc_uint16 max_limit);


#if 0
#define igmp_dbg(fmt, args...) \
	do{fprintf(stderr, "[%s, %d] - " fmt, __FILE__, __LINE__, ##args);}while(0)
#else
//#define igmp_dbg(fmt, args...)
#define igmp_dbg(fmt, args...)  BC_PT_DBG_SMP(BC_MODULE_IGMP, fmt, ##args)
#endif

#endif
#endif
#endif


