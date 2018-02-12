/*******************************************************************************
  [File name]	: mcast_router.c
  [Author]     	: bain.wang@outlook.com
  [Version]    	: 1.0
  [Date]       	: 2017-09-05
  [Description]	:
	Do igmp router behavior on downstream ports
  [Others]     	:
	NULL
  [Function List]:  
    1. ....
    2. ....
  [History]:
	 D a t e      	Modification 							 Initials
	---------- 	--------------                                        ----------
	2017-09-05  	Created								 bain.wang@outlook.com
*******************************************************************************/

#include "mcast_router.h"

#if BC_MULTICAST_INCLUDE

#include "mcast_utl.h"
#include "mcast_host.h"
#include "mcast_core.h"
#include "utili_ip_mac.h"

#if 1 /*bain.wang@outlook.com*/
#include "stdlib.h"
#include "string.h"
#endif

#if 1

static mcast_avltree_t *mcast_grp_tree = NULL;

static bc_int32 __mc_rt_cmp(const void *f, const void *s, void *param)
{
	mcast_grp_t *a;
	mcast_grp_t *b;

	a = (mcast_grp_t*)f;
	b = (mcast_grp_t*)s;

	if (a->grp > b->grp)
		return 1;
	else if (a->grp < b->grp)
		return -1;
	else
		return 0;
}

mcast_grp_t* mcast_rt_node_get(IN bc_ip grp)
{
	mcast_grp_t find_node;
	mcast_grp_t **grp_node_p;

	memset(&find_node, 0x00, sizeof(mcast_grp_t));
	find_node.grp = grp;

	if(!mcast_grp_tree)
	{
		BC_PT_DBG_FUN(BC_MODULE_IGMP, "mcast_grp_tree is NULL\n");
	}
	
	grp_node_p = (mcast_grp_t **)mcast_avltree_find(mcast_grp_tree, &find_node);
	if (grp_node_p == NULL || *grp_node_p == NULL)
		return NULL;

	return *grp_node_p;
}

mcast_grp_t* mcast_rt_node_get_next(IN mcast_grp_t *grp_node)
{
	mcast_grp_t **grp_node_p = NULL;

	if (grp_node)
	{
		grp_node_p = (mcast_grp_t **)mcast_avltree_find(mcast_grp_tree, grp_node);
		if (grp_node_p == NULL || *grp_node_p == NULL)
			return NULL;
	}

	grp_node_p = (mcast_grp_t **)mcast_avltree_get_next(mcast_grp_tree, (void**)grp_node_p);
	if (grp_node_p == NULL || *grp_node_p == NULL)
		return NULL;

	return *grp_node_p;
}

static bc_boolean __mcast_rt_node_insert(IN mcast_grp_t *grp_node)
{
	grp_node = (mcast_grp_t *)mcast_avltree_insert(mcast_grp_tree, grp_node);
	return (grp_node) ? FALSE : TRUE;
}


static bc_boolean __mcast_rt_node_delete(IN mcast_grp_t *grp_node)
{
	mcast_avltree_delete(mcast_grp_tree, grp_node);
	return (grp_node) ? TRUE : FALSE;
}


#endif
#if 1
static bc_boolean fwd_port_flag = FALSE;
static bc_boolean src_node_flag = FALSE;


/*
	只处理MCAST_PBC_RECORD_IS_EXCLUDE模式；
	1. 递减grp_tic值，为0时:
		1.1 设置为MCAST_PBC_RECORD_IS_INCLUDE模式； 
		1.2 始能fwd_port_flag；
		1.3 遍历源列表的各结点，如果TIC为0时，删除结点
*/
static void __mcast_rt_exclude_tic(IN mcast_grp_port_t *port_grp)
{
	mcast_grp_src_t *node_p;
	mcast_grp_src_t *delete_node_p;

	//只处理MCAST_PBC_RECORD_IS_EXCLUDE模式
	if (port_grp->mode != MCAST_PBC_RECORD_IS_EXCLUDE)
		return ;

	//递减grp_tic值，为0时设置为MCAST_PBC_RECORD_IS_INCLUDE模式，并处理源列表中各结点
	if (port_grp->grp_tic > 0)
	{
		port_grp->grp_tic--;
	}

	if (port_grp->grp_tic <= 0)
	{
		port_grp->grp_tic = 0;
		port_grp->mode = MCAST_PBC_RECORD_IS_INCLUDE;

		delete_node_p = NULL;
		fwd_port_flag = TRUE;

		//遍历源列表的各结点，如果TIC为0时，删除结点
		if ((node_p = (mcast_grp_src_t*)mcast_list_first(&port_grp->src_list)) != NULL)
		{
			do
			{
				if (delete_node_p != NULL)
				{
					mcast_list_delete(&port_grp->src_list, delete_node_p);
					mcast_free(delete_node_p);
					delete_node_p = NULL;
				}

				if (node_p->tic == 0)
					delete_node_p = node_p;
			} while ((node_p = (mcast_grp_src_t*)mcast_list_next(node_p)) != NULL);
		}

		if (delete_node_p != NULL)
		{
			mcast_list_delete(&port_grp->src_list, delete_node_p);
			mcast_free(delete_node_p);
			delete_node_p = NULL;
		}
	}
}

//递减port_grp的源列表中各结点TIC，为0时且为MCAST_PBC_RECORD_IS_INCLUDE时删除该结点并设置src_node_flag
static void __mcast_rt_src_tic(IN mcast_grp_port_t *port_grp)
{
	mcast_grp_src_t *node_p;
	mcast_grp_src_t *delete_node_p;

	delete_node_p = NULL;
	if ((node_p = (mcast_grp_src_t*)mcast_list_first(&port_grp->src_list)) != NULL)
	{
		do
		{
			if (delete_node_p != NULL)
			{
				mcast_list_delete(&port_grp->src_list, delete_node_p);
				mcast_free(delete_node_p);
				delete_node_p = NULL;
				src_node_flag = TRUE;
			}

			if (node_p->tic > 0)
				node_p->tic--;

			if ((node_p->tic <= 0) && (port_grp->mode == MCAST_PBC_RECORD_IS_INCLUDE))
				delete_node_p = node_p;
		} while ((node_p = (mcast_grp_src_t*)mcast_list_next(node_p)) != NULL);
	}

	if (delete_node_p != NULL)
	{
		mcast_list_delete(&port_grp->src_list, delete_node_p);
		mcast_free(delete_node_p);
		delete_node_p = NULL;
		src_node_flag = TRUE;
	}
}

static void __mcast_rt_old_ver_tic(IN bc_int16 port_idx, IN bc_ip grp, IN mcast_grp_port_t *port_grp)
{
	if (port_grp->v1_tic > 0)
		port_grp->v1_tic--;

	if (port_grp->v2_tic > 0)
		port_grp->v2_tic--;
}

static bc_boolean __mcast_rt_grp_delete_check(IN mcast_grp_t *grp_node_p)
{
	bc_int32 i;

	for (i = 0; i < BC_PORT_PON_MAX_COUNT + BC_PORT_SNI_MAX_COUNT; i++)
	{
		if (grp_node_p->port_grp[i].mode == MCAST_PBC_RECORD_IS_EXCLUDE)
		{
			igmp_dbg("$$$ grp: %x, vid: %d, pid: %d\n", (bc_uint32)grp_node_p->grp, (bc_uint16)grp_node_p->vid, i);
			return FALSE;
		}
		else if (grp_node_p->port_grp[i].mode == MCAST_PBC_RECORD_IS_INCLUDE &&
			mcast_list_count(&grp_node_p->port_grp[i].src_list) != 0)
		{
		//	igmp_dbg("### grp: %x, vid: %d, pid: %d\n", (bc_uint32)grp_node_p->grp, (bc_uint16)grp_node_p->vid, i);
			return FALSE;
		}
		else if (grp_node_p->port_grp[i].mode == MCAST_PBC_RECORD_IS_INCLUDE &&
			mcast_list_count(&grp_node_p->port_grp[i].src_list) == 0)
			continue;
		else  /* the node mode not equal isex and isin, it's a exception */
			return TRUE;
	}

	return TRUE;
}

static void __mcast_rt_grp_delete(mcast_grp_t *delete_grp_node_p)
{
	bc_int16 idx;
	
	__mcast_rt_node_delete(delete_grp_node_p);
	
	for (idx = 0; idx < BC_PORT_PON_MAX_COUNT + BC_PORT_SNI_MAX_COUNT; idx++)
		mcast_src_list_free(&(delete_grp_node_p->port_grp[idx].src_list));
	
	mcast_free(delete_grp_node_p);
}

/*
	1. 从mcast_grp_tree中取出各组结点:
		1.1 处理组结点中各端口组的TIC。
		1.2 检测grp_node_p中各端口组的状态:
			1.2.1 如果不为INCLUDE及EXCLUDE，或者为INCLUDE但源列表为空，则从drv_mcast_tree中删除该结点，并将该结点信息存放到mcast_host_tree及mcast_delay_report_tre中
			1.2.2 如果fwd_port_flag被始能，形成转发结点，添加到drv_mcast_tree中
			1.2.3 如果src_node_flag或者fwd_port_flag被始能，添加到mcast_host_tree中并进行行为处理后加入到mcast_delay_report_tree中。
*/
void mcast_rt_grp_tic(void)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	mcast_grp_t *grp_node_p = NULL;
	mcast_grp_t *delete_grp_node_p = NULL;
	bc_int16 port_idx = 0;
	//bc_char tmp[20];
	
#if 0 /*bain.wang@outlook.com*/
	mcast_ctrlmc_fwd_node_t node;
	mcast_ctrlmc_package_t pkg;

	memset(&node, 0, sizeof(node));
	memset(&pkg, 0, sizeof(pkg));
#endif

	delete_grp_node_p = NULL;

	//从mcast_grp_tree中取出各组结点
	while ((grp_node_p = mcast_rt_node_get_next(grp_node_p)) != NULL)
	{
		//igmp_dbg("idx: %d, grp: %lu, vid: %d\n", ++idx, (bc_ip)grp_node_p->grp, grp_node_p->vid);
		if (delete_grp_node_p != NULL)
		{
			__mcast_rt_grp_delete(delete_grp_node_p);
			delete_grp_node_p = NULL;
		}
#if 0
		/*可控组播认证模式为permit时,不应老化*/
		if (mcast_ctc_mode)
		{
			while (mcast_ctrlmc_fwd_node_get_next(&node) != FALSE)
			{
				//igmp_dbg("node.vid: %d, p_node.vid: %d, node.grp: %s, p_node.grp: %s\n",
				//	node.vid, grp_node_p->vid, ip_format_get(node.grp, tmp), ip_format_get(grp_node_p->grp, tmp));
				
				if (node.vid != grp_node_p->vid || node.grp != grp_node_p->grp)
					continue;
				
				if (mcast_ctrlmc_package_get(node.cm_idx, &pkg) != MCAST_RET_OK)
				{
					igmp_dbg("not found package by cm_idx %d!\n", node.cm_idx);
					continue;
				}

				if (pkg.user_authority == mcast_ctrlmc_authority_permit)
				{
					//igmp_dbg("authority permit\n");
					goto ctrl_mcast_proc;
				}
			}
		}
#endif
		//处理组结点中各端口组的TIC
		for (port_idx = 0; port_idx < BC_PORT_PON_MAX_COUNT + BC_PORT_SNI_MAX_COUNT; port_idx++)
		{
			/*
				只处理MCAST_PBC_RECORD_IS_EXCLUDE模式；
				1. 递减grp_tic值，为0时:
					1.1 设置为MCAST_PBC_RECORD_IS_INCLUDE模式； 
					1.2 始能fwd_port_flag；
					1.3 遍历源列表的各结点，如果TIC为0时，删除结点
			*/
			__mcast_rt_exclude_tic(&grp_node_p->port_grp[port_idx]);
			
			//递减port_grp的源列表中各结点TIC，为0时且为MCAST_PBC_RECORD_IS_INCLUDE时删除该结点并设置src_node_flag
			__mcast_rt_src_tic(&grp_node_p->port_grp[port_idx]);

			//递减grp_node_p->port_grp[port_idx]的v1_tic和v2_tic
			__mcast_rt_old_ver_tic(port_idx, grp_node_p->grp, &grp_node_p->port_grp[port_idx]);
		}

		//检测grp_node_p中各端口组的状态，
		//如果不为INCLUDE及EXCLUDE，或者为INCLUDE但源列表为空，则从drv_mcast_tree中删除该结点
		if (__mcast_rt_grp_delete_check(grp_node_p) == TRUE)
		{
		    igmp_dbg("del drv fwd entry\n");
           // #if defined (__BC_IGMP_HAVE_DRV__)
			drv_mcast_delete(grp_node_p->grp, grp_node_p->vid);
		//	#endif

			//将该结点信息存放到mcast_host_tree及mcast_delay_report_tre中
			mcast_host_trigger_report(grp_node_p);

			//删除该结点
			delete_grp_node_p = grp_node_p;
		}
	#if 0
		else  /* state change, trigger host report */
		{
			mcast_core_update_grp_node_to_chip(grp_node_p);
			
			mcast_host_trigger_report(grp_node_p);
		}
#endif
		//形成转发结点，添加到drv_mcast_tree中
		if (fwd_port_flag)
		{
			mcast_core_update_grp_node_to_chip(grp_node_p);
		}

		//加入到mcast_host_tree中并进行行为处理后加入到mcast_delay_report_tree中。
		if ((fwd_port_flag)||(src_node_flag))
		{
			mcast_host_trigger_report(grp_node_p);
			fwd_port_flag = FALSE;
			src_node_flag = FALSE;
		}
//ctrl_mcast_proc:
//			;
	}

	if (delete_grp_node_p != NULL)
	{
		__mcast_rt_grp_delete(delete_grp_node_p);
	}

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
}


#endif
#if 1

typedef struct {
	mcast_list_node_t list_node;

	bc_port_index_t 	send_port;

	bc_ip 		grp;
	mcast_list_t 	src_list;
	
	mcast_pkt_query_e 	query_type;
	bc_int32 				query_count;
	bc_int32 				query_interval;
} mc_send_query_node_t;


static mcast_list_t mcast_send_query_list;

static bc_boolean __mcast_rt_send_query_add(IN mc_send_query_node_t *query_node_p)
{
	mcast_list_add(&mcast_send_query_list, query_node_p);
	return TRUE;
}

static bc_boolean __mcast_rt_send_query_del(IN mc_send_query_node_t *query_node_p)
{
	mcast_list_delete(&mcast_send_query_list, query_node_p);
	return TRUE;
}


static mc_send_query_node_t* __mcast_rt_send_query_get_first(void)
{
	return (mc_send_query_node_t*)mcast_list_first(&mcast_send_query_list);
}

static mc_send_query_node_t* __mcast_rt_send_query_get_next(IN mc_send_query_node_t *query_node_p)
{
	return (mc_send_query_node_t*)mcast_list_next(query_node_p);
}

/*
rfc3376-page35
--------------
6.6.3.2. Building and Sending Group and Source Specific Queries

When a table action "Send Q(G,X)" is encountered by a querier in the
table in section 6.4.2, the following actions must be performed for
each of the sources in X of group G, with source timer larger than LMQT:
	o Set number of retransmissions for each source to [Last Member Query Count].
	o Lower source timer to LMQT.
	
The router must then immediately send a group and source specific
query as well as schedule [Last Member Query Count - 1] query
retransmissions to be sent every [Last Member Query Interval] over
[Last Member Query Time]. The contents of these queries are calculated as follows.

When building a group and source specific query for a group G, two
separate query messages are sent for the group. The first one has
the "Suppress Router-Side Processing" bit set and contains all the
sources with retransmission state and timers greater than LMQT. The
second has the "Suppress Router-Side Processing" bit clear and
contains all the sources with retransmission state and timers lower
or equal to LMQT. If either of the two calculated messages does not
contain any sources, then its transmission is suppressed.

Note: If a group specific query is scheduled to be transmitted at the
same time as a group and source specific query for the same group,
then transmission of the group and source specific message with the
"Suppress Router-Side Processing" bit set may be suppressed.

*/
static mcast_ret_code __mcast_rt_send_grp_src_spec_query(
	IN bc_port_index_t send_port,
	IN bc_ip grp, 
	IN mcast_list_t *src_list)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	mc_send_query_node_t *query_node_p = NULL;
	mcast_cfg_t mcast_cfg;

	/*send first msg*/
	mcast_tx_grp_src_query(send_port, grp, src_list);

	query_node_p = (mc_send_query_node_t*)mcast_alloc(sizeof(mc_send_query_node_t));
	if (query_node_p == NULL)
		MCAST_RET_ERR(MCAST_MODULE_RT, MCAST_RET_ERR_NORES, TRUE);

	mcast_cfg_get(&mcast_cfg);

	memset(query_node_p, 0x00, sizeof(mc_send_query_node_t));
	query_node_p->send_port = send_port;
	query_node_p->grp = grp;
	mcast_list_init(&query_node_p->src_list, mcast_utl_src_cmp);
	if (mcast_src_list_copy(&query_node_p->src_list, src_list) == FALSE)
	{
		mcast_free(query_node_p);
		MCAST_RET_ERR(MCAST_MODULE_RT, MCAST_RET_ERR_NORES, TRUE);
	}

	query_node_p->query_type = MCAST_PBC_QUERY_SRC_GRP;
	query_node_p->query_count = mcast_cfg.last_member_query_count - 1;
	igmp_dbg("query_count: %d\n", query_node_p->query_count);
	query_node_p->query_interval = mcast_random(MCAST_TIC_CAL(mcast_cfg.last_member_query_interval));
	/* add this msg to mcast_send_query_list, use the timer to send a rest of the msg*/
	if (__mcast_rt_send_query_add(query_node_p) == FALSE)
	{
		mcast_src_list_free(&query_node_p->src_list);
		mcast_free(query_node_p);
		MCAST_RET_ERR(MCAST_MODULE_RT, MCAST_RET_ERR_UNKNOW, TRUE);
	}

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return MCAST_RET_OK;	
}

/*
rfc2236-page5
-------------
When a Querier receives a Leave Group message for a group that has
group members on the reception interface, it sends [Last Member Query
Count] Group-Specific Queries every [Last Member Query Interval] to
the group being left. These Group-Specific Queries have their Max
Response time set to [Last Member Query Interval]. If no Reports are
received after the response time of the last query expires, the
routers assume that the group has no local members, as above. Any
Querier to non-Querier transition is ignored during this time; the
same router keeps sending the Group-Specific Queries.

rfc3376-page34
--------------
6.6.3.1. Building and Sending Group Specific Queries.
When a table action "Send Q(G)" is encountered, then the group timer must be lowered to LMQT. 
The router must then immediately send a group specific query as well as schedule 
[Last Member Query Count -1] query retransmissions to be sent every 
[Last Member Query Interval] over [Last Member Query Time].
When transmitting a group specific query, if the group timer is larger than LMQT, 
the "Suppress Router-Side Processing" bit is set in the query message.
*/
static mcast_ret_code __mcast_rt_send_grp_spec_query(
	IN bc_port_index_t send_port,
	IN bc_ip grp)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	mc_send_query_node_t *query_node_p = NULL;
	mcast_cfg_t mcast_cfg;

	igmp_dbg("rt send grp spec query.\n");

	/* first msg */ 
	mcast_tx_grp_query(send_port, grp);

	query_node_p = (mc_send_query_node_t*)mcast_alloc(sizeof(mc_send_query_node_t));
	if (query_node_p == NULL)
		MCAST_RET_ERR(MCAST_MODULE_RT, MCAST_RET_ERR_NORES, TRUE);

	mcast_cfg_get(&mcast_cfg);

	memset(query_node_p, 0x00, sizeof(mc_send_query_node_t));
	query_node_p->send_port = send_port;
	query_node_p->grp = grp;
	mcast_list_init(&query_node_p->src_list, mcast_utl_src_cmp);
	query_node_p->query_type = MCAST_PBC_QUERY_GRP;
	query_node_p->query_count = mcast_cfg.last_member_query_count - 1;
	igmp_dbg("query_count: %d\n", query_node_p->query_count);
	query_node_p->query_interval = mcast_random(MCAST_TIC_CAL(mcast_cfg.last_member_query_interval));/*Max Response Time*/
	/* add this msg to mcast_send_query_list, use the timer to send a rest of the msg*/
	if (__mcast_rt_send_query_add(query_node_p) == FALSE)
	{
		mcast_free(query_node_p);
		MCAST_RET_ERR(MCAST_MODULE_RT, MCAST_RET_ERR_UNKNOW, TRUE);
	}

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return MCAST_RET_OK;
}


/*
	1. 递减路由查询TIC，为0时，组Gen Query包，在各VID的各下行口发出。
	2. 遍历mcast_send_query_list中各结点，对各结点:
		2.1 递减query_interval值，为0时，向结点的发送端口发出指定组或指定源组的查询报文。
		2.2 递减query_count值，为0时，删除结点，否则设置query_interval值； 
*/
static bc_int32 mcast_gen_query_tic;
void mcast_rt_send_query_tic(void)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	mcast_cfg_t mcast_cfg;
	mc_send_query_node_t *query_node_p = NULL;
	mc_send_query_node_t *query_delete_node_p = NULL;
	bc_uint32 ret = MCAST_RET_OK;

	memset(&mcast_cfg, 0x00, sizeof(mcast_cfg));
	mcast_cfg_get(&mcast_cfg);

	//递减路由查询TIC，为0时，组Gen Query包，在各VID的各下行口发出。
	if (mcast_gen_query_tic != 0)
	{
		mcast_gen_query_tic--;
		if (mcast_gen_query_tic == 0)
		{
			mcast_gen_query_tic = MCAST_TIC_CAL(mcast_cfg.query_interval);
			igmp_dbg("mcast_gen_query_tic: %d\n", mcast_gen_query_tic);
			mcast_tx_gen_query();
		}
	}
	query_delete_node_p = NULL;

	//遍历mcast_send_query_list中各结点
	query_node_p = __mcast_rt_send_query_get_first();
	while (query_node_p)
	{
		if (query_delete_node_p)
		{
			igmp_dbg("del send query list\n");
			__mcast_rt_send_query_del(query_delete_node_p);
			mcast_src_list_free(&(query_delete_node_p->src_list));
			mcast_free(query_delete_node_p);
			query_delete_node_p = NULL;
		}

		//递减query_interval值，为0时，发送查询报文
		query_node_p->query_interval--;
		if (query_node_p->query_interval <= 0)
		{
			igmp_dbg("query interval <= 0\n");

			//遍历各VID上的端口，一致时，向该端口发出指定组查询报文。
			if (query_node_p->query_type == MCAST_PBC_QUERY_GRP)
			{
				mcast_tx_grp_query(query_node_p->send_port, query_node_p->grp);
			}
			//向send_port端口发出指定源查询报文，组为grp，VID为grp所在的VID，源列表为src_list
			else if (query_node_p->query_type == MCAST_PBC_QUERY_SRC_GRP)
			{
				if (MCAST_RET_OK != (ret = mcast_tx_grp_src_query(query_node_p->send_port, query_node_p->grp, &query_node_p->src_list)))
				{
					igmp_dbg("send grp src query failed!\n");
				}
			}
			else
				{/* do nothing */}

			//递减query_count，为0时，删除结点，否则设置query_interval
			if (query_node_p->query_count > 0)
				query_node_p->query_count--;
			
			if (query_node_p->query_count != 0)
				query_node_p->query_interval = mcast_random(MCAST_TIC_CAL(mcast_cfg.last_member_query_interval));
			else
				query_delete_node_p = query_node_p;
		}

		query_node_p = __mcast_rt_send_query_get_next(query_node_p);
	}
	if (query_delete_node_p)//处理while中遗留的最后一个动作
	{
		__mcast_rt_send_query_del(query_delete_node_p);
		mcast_src_list_free(&(query_delete_node_p->src_list));
		mcast_free(query_delete_node_p);
		query_delete_node_p = NULL;
	}

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
}


bc_boolean mcast_rt_send_query_clear(void)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);

	mc_send_query_node_t *query_node_p = NULL;

	while ((query_node_p = __mcast_rt_send_query_get_first()) != NULL)
	{
		__mcast_rt_send_query_del(query_node_p);
		mcast_src_list_free(&(query_node_p->src_list));
		mcast_free(query_node_p);
	}

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return TRUE;
}


#endif
#if 1

static int __mc_rt_src_cmp(IN void *node, IN bc_uint32 key)
{
	mcast_grp_src_t *a;

	a = (mcast_grp_src_t*)node;

	if (a->src > key)
		return 1;
	else if (a->src < key)
		return -1;
	else
		return 0;
}

static void __mcast_rt_cal_ex2xy(
	INOUT mcast_list_t *ex_list, 
	OUT mcast_list_t *x, 
	OUT mcast_list_t *y)
{
	mcast_grp_src_t *node_p = NULL;

	while((node_p = (mcast_grp_src_t*)mcast_list_first(ex_list)) != NULL)
	{
		mcast_list_delete(ex_list, node_p);
		if (node_p->tic != 0)
			mcast_list_add(x, node_p);
		else
			mcast_list_add(y, node_p);
	}
}


/*  INCLUDE (A)    IS_IN (B)     INCLUDE (A+B)            (B)=GMI */
static mcast_ret_code __mcast_rt_cal_inin(
	IN bc_port_index_t port,
	IN bc_ip grp,
	IN mcast_pkt_record_type_e new_type,
	IN mcast_list_t *new_src_list,
	INOUT mcast_grp_port_t *port_grp_info)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	mcast_cfg_t mcast_cfg;
	mcast_grp_src_t *src_node_p = NULL;
	
	mcast_list_t minus_list;
	mcast_list_t union_list;

	mcast_cfg_get(&mcast_cfg);
	mcast_list_scan(new_src_list, src_node_p, mcast_grp_src_t*)
	{
		src_node_p->tic = MCAST_TIC_CAL(mcast_cfg.member_interval);  /* (B)=GMI */
	}

	mcast_list_init(&minus_list, mcast_utl_src_cmp);
	mcast_src_list_minus(&port_grp_info->src_list, new_src_list, &minus_list);
	mcast_src_list_free(&minus_list);

	mcast_list_init(&union_list, mcast_utl_src_cmp);
	mcast_src_list_union(&port_grp_info->src_list, new_src_list, &union_list);  /* INCLUDE (A+B) */
	mcast_src_list_move(&port_grp_info->src_list, &union_list);

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return MCAST_RET_OK;
}

/*
   INCLUDE (A)    IS_EX (B)     EXCLUDE (A*B,B-A)        (B-A)=0
                                                         			     Delete (A-B)
                                                                                  Group Timer=GMI
*/
static mcast_ret_code __mcast_rt_cal_inex(	
	IN bc_port_index_t port,
	IN bc_ip grp,
	IN mcast_pkt_record_type_e new_type,
	IN mcast_list_t *new_src_list,
	INOUT mcast_grp_port_t *port_grp_info)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	mcast_list_t allow_list;
	mcast_list_t fwd_list;
	mcast_grp_src_t *src_node_p = NULL;

	mcast_cfg_t mcast_cfg;

	port_grp_info->mode = MCAST_PBC_RECORD_IS_EXCLUDE;
	mcast_list_init(&allow_list, mcast_utl_src_cmp);
	mcast_src_list_minus(new_src_list, &port_grp_info->src_list, &allow_list);
	mcast_list_scan(new_src_list, src_node_p, mcast_grp_src_t*)
	{
		src_node_p->tic = 0; /* (B-A)=0 */
	}

	mcast_list_init(&fwd_list, mcast_utl_src_cmp);
	mcast_src_list_minus(&port_grp_info->src_list, &allow_list, &fwd_list);
	mcast_src_list_free(&port_grp_info->src_list); /* Delete (A-B) */
	mcast_src_list_free(&allow_list);
	
	/* EXCLUDE (A*B,B-A)  */
	mcast_src_list_union(new_src_list, &fwd_list, &port_grp_info->src_list);

	mcast_cfg_get(&mcast_cfg);
	port_grp_info->grp_tic = MCAST_TIC_CAL(mcast_cfg.member_interval); /* Group Timer=GMI */
//	igmp_dbg("grp_tic: %d\n", port_grp_info->grp_tic);

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return MCAST_RET_OK;
}


/*
INCLUDE (A)    TO_IN (B)    INCLUDE (A+B)           (B)=GMI
                                                                           Send Q(G,A-B)
*/
static mcast_ret_code __mcast_rt_cal_intoin(	
	IN bc_port_index_t port,
	IN bc_ip grp,
	IN mcast_pkt_record_type_e new_type,
	IN mcast_list_t *new_src_list,
	INOUT mcast_grp_port_t *port_grp_info)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	mcast_cfg_t mcast_cfg;
	mcast_grp_src_t *src_node_p = NULL;
	
	mcast_list_t minus_list;
	mcast_list_t union_list;

	mcast_cfg_get(&mcast_cfg);
	mcast_list_scan(new_src_list, src_node_p, mcast_grp_src_t*)
	{
		src_node_p->tic = MCAST_TIC_CAL(mcast_cfg.member_interval);  /* (B)=GMI */
	}

	mcast_list_init(&minus_list, mcast_utl_src_cmp);
	mcast_src_list_minus(&port_grp_info->src_list, new_src_list, &minus_list);
	mcast_src_list_free(&minus_list);
	__mcast_rt_send_grp_src_spec_query(port, grp, &port_grp_info->src_list); /* Send Q(G,A-B) */
	mcast_list_scan(&port_grp_info->src_list, src_node_p, mcast_grp_src_t*)
	{
		if (src_node_p->tic > MCAST_TIC_CAL(mcast_cfg.last_member_query_time))
			src_node_p->tic = MCAST_TIC_CAL(mcast_cfg.last_member_query_time);
	}

	mcast_list_init(&union_list, mcast_utl_src_cmp);
	mcast_src_list_union(&port_grp_info->src_list, new_src_list, &union_list);  /* INCLUDE (A+B) */
	
	mcast_src_list_move(&port_grp_info->src_list, &union_list);

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return MCAST_RET_OK;
}


/*
INCLUDE (A)    TO_EX (B)    EXCLUDE (A*B,B-A)       (B-A)=0
                                                                              Delete (A-B)
                                                                              Send Q(G,A*B)
                                                                              Group Timer=GMI
*/
static mcast_ret_code __mcast_rt_cal_intoex(	
	IN bc_port_index_t port,
	IN bc_ip grp,
	IN mcast_pkt_record_type_e new_type,
	IN mcast_list_t *new_src_list,
	INOUT mcast_grp_port_t *port_grp_info)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	mcast_list_t allow_list;
	mcast_list_t fwd_list;
	mcast_grp_src_t *src_node_p = NULL;

	mcast_cfg_t mcast_cfg;

	port_grp_info->mode = MCAST_PBC_RECORD_IS_EXCLUDE;

	mcast_list_init(&allow_list, mcast_utl_src_cmp);
	mcast_src_list_minus(new_src_list, &port_grp_info->src_list, &allow_list);
	mcast_list_scan(new_src_list, src_node_p, mcast_grp_src_t*)
	{
		src_node_p->tic = 0; /* (B-A)=0 */
	}

	mcast_list_init(&fwd_list, mcast_utl_src_cmp);
	mcast_src_list_minus(&port_grp_info->src_list, &allow_list, &fwd_list);
	mcast_src_list_free(&port_grp_info->src_list); /* Delete (A-B) */
	mcast_src_list_free(&allow_list);

	mcast_cfg_get(&mcast_cfg);
	__mcast_rt_send_grp_src_spec_query(port, grp, &fwd_list); /* Send Q(G,A*B) */
	mcast_list_scan(&fwd_list, src_node_p, mcast_grp_src_t*)
	{
		if (src_node_p->tic > MCAST_TIC_CAL(mcast_cfg.last_member_query_time))
			src_node_p->tic = MCAST_TIC_CAL(mcast_cfg.last_member_query_time);
	}
	
	/* EXCLUDE (A*B,B-A)  */
	mcast_src_list_union(new_src_list, &fwd_list, &port_grp_info->src_list);

	port_grp_info->grp_tic = MCAST_TIC_CAL(mcast_cfg.member_interval); /* Group Timer=GMI */
	igmp_dbg("grp_tic: %d\n", port_grp_info->grp_tic);

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return MCAST_RET_OK;
}


/* INCLUDE (A)    ALLOW (B)    INCLUDE (A+B)           (B)=GMI */
static mcast_ret_code __mcast_rt_cal_inallow(	
	IN bc_port_index_t port,
	IN bc_ip grp,
	IN mcast_pkt_record_type_e new_type,
	IN mcast_list_t *new_src_list,
	INOUT mcast_grp_port_t *port_grp_info)
{
	return __mcast_rt_cal_inin(port, grp, new_type, new_src_list, port_grp_info);
}


/* INCLUDE (A)    BLOCK (B)    INCLUDE (A)             Send Q(G,A*B) */
static mcast_ret_code __mcast_rt_cal_inblock(	
	IN bc_port_index_t port,
	IN bc_ip grp,
	IN mcast_pkt_record_type_e new_type,
	IN mcast_list_t *new_src_list,
	INOUT mcast_grp_port_t *port_grp_info)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	mcast_list_t query_list;
	mcast_list_t union_list;

	mcast_grp_src_t *src_node_p = NULL;
	mcast_cfg_t mcast_cfg;

	mcast_list_init(&query_list, mcast_utl_src_cmp);
	mcast_src_list_minus(&port_grp_info->src_list, new_src_list, &query_list);

	mcast_cfg_get(&mcast_cfg);
	__mcast_rt_send_grp_src_spec_query(port, grp, &query_list); /* Send Q(G,A*B) */
	mcast_list_scan(&query_list, src_node_p, mcast_grp_src_t*)
	{
		if (src_node_p->tic > MCAST_TIC_CAL(mcast_cfg.last_member_query_time))
			src_node_p->tic = MCAST_TIC_CAL(mcast_cfg.last_member_query_time);
	}

	mcast_list_init(&union_list, mcast_utl_src_cmp);
	mcast_src_list_union(&port_grp_info->src_list, &query_list, &union_list);
	mcast_src_list_move(&port_grp_info->src_list, &union_list);

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return MCAST_RET_OK;
}


/* EXCLUDE (X,Y)  IS_IN (A)     EXCLUDE (X+A,Y-A)        (A)=GMI */
static mcast_ret_code __mcast_rt_cal_exin(	
	IN bc_port_index_t port,
	IN bc_ip grp,
	IN mcast_pkt_record_type_e new_type,
	IN mcast_list_t *new_src_list,
	INOUT mcast_grp_port_t *port_grp_info)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	mcast_cfg_t mcast_cfg;
	mcast_grp_src_t *src_node_p = NULL;

	mcast_list_t minus_list;
	mcast_list_t union_list;
	
	mcast_cfg_get(&mcast_cfg);
	mcast_list_scan(new_src_list, src_node_p, mcast_grp_src_t*)
	{
		src_node_p->tic = MCAST_TIC_CAL(mcast_cfg.member_interval);  /* (A)=GMI */
	}

	mcast_list_init(&minus_list, mcast_utl_src_cmp);
	mcast_src_list_minus(&port_grp_info->src_list, new_src_list, &minus_list);
	mcast_src_list_free(&minus_list);

	mcast_list_init(&union_list, mcast_utl_src_cmp);
	mcast_src_list_union(&port_grp_info->src_list, new_src_list, &union_list);

	mcast_src_list_move(&port_grp_info->src_list, &union_list);

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return MCAST_RET_OK;	
}


/*
   EXCLUDE (X,Y)  IS_EX (A)     EXCLUDE (A-Y,Y*A)        (A-X-Y)=GMI
                                                                                   Delete (X-A)
                                                                                   Delete (Y-A)
                                                                                   Group Timer=GMI
*/
static mcast_ret_code __mcast_rt_cal_exex(	
	IN bc_port_index_t port,
	IN bc_ip grp,
	IN mcast_pkt_record_type_e new_type,
	IN mcast_list_t *new_src_list,
	INOUT mcast_grp_port_t *port_grp_info)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	mcast_cfg_t mcast_cfg;
	mcast_grp_src_t *src_node_p = NULL;
	mcast_list_t minus_list;

	mcast_list_t x_list;
	mcast_list_t y_list;

	mcast_list_t x_fwd_list;
	mcast_list_t y_block_list;

	mcast_list_t union_fwd_list;
	
	mcast_list_init(&minus_list, mcast_utl_src_cmp);
	mcast_src_list_minus(new_src_list, &port_grp_info->src_list, &minus_list);
	mcast_cfg_get(&mcast_cfg);
	port_grp_info->grp_tic = MCAST_TIC_CAL(mcast_cfg.member_interval);
	igmp_dbg("grp_tic: %d\n", port_grp_info->grp_tic);
	mcast_list_scan(new_src_list, src_node_p, mcast_grp_src_t*)
	{
		src_node_p->tic = MCAST_TIC_CAL(mcast_cfg.member_interval);  /* (A-X-Y)=GMI */
	}

	mcast_list_init(&x_list, mcast_utl_src_cmp);
	mcast_list_init(&y_list, mcast_utl_src_cmp);
	__mcast_rt_cal_ex2xy(&port_grp_info->src_list, &x_list, &y_list);

	mcast_list_init(&x_fwd_list, mcast_utl_src_cmp);
	mcast_src_list_minus(&x_list, &minus_list, &x_fwd_list); /* Delete (X-A) */
	mcast_src_list_free(&x_list);
	
	mcast_list_init(&y_block_list, mcast_utl_src_cmp);
	mcast_src_list_minus(&y_list, &minus_list, &y_block_list); /* Delete (Y-A) */
	mcast_src_list_free(&y_list);

	mcast_src_list_free(&minus_list);

	mcast_list_init(&union_fwd_list, mcast_utl_src_cmp);
	mcast_src_list_union(&x_fwd_list, new_src_list, &union_fwd_list);

	mcast_src_list_union(&union_fwd_list, &y_block_list, &port_grp_info->src_list);

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return MCAST_RET_OK;
}


/*
EXCLUDE (X,Y)  TO_IN (A)    EXCLUDE (X+A,Y-A)       (A)=GMI
                                                                               Send Q(G,X-A)
                                                                               Send Q(G)
*/
static mcast_ret_code __mcast_rt_cal_extoin(	
	IN bc_port_index_t port,
	IN bc_ip grp,
	IN mcast_pkt_record_type_e new_type,
	IN mcast_list_t *new_src_list,
	INOUT mcast_grp_port_t *port_grp_info)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	mcast_cfg_t mcast_cfg;
	mcast_grp_src_t *src_node_p = NULL;

	mcast_list_t x_list;
	mcast_list_t y_list;

	mcast_list_t x_minus_list;
	mcast_list_t x_union_list;

	mcast_list_t y_minus_list;

	mcast_cfg_get(&mcast_cfg);
	mcast_list_scan(new_src_list, src_node_p, mcast_grp_src_t*)
	{
		src_node_p->tic = MCAST_TIC_CAL(mcast_cfg.member_interval);   /* (A)=GMI */
	}

	mcast_list_init(&x_list, mcast_utl_src_cmp);
	mcast_list_init(&y_list, mcast_utl_src_cmp);
	__mcast_rt_cal_ex2xy(&port_grp_info->src_list, &x_list, &y_list);

	mcast_list_init(&x_minus_list, mcast_utl_src_cmp);
	mcast_src_list_minus(&x_list, new_src_list, &x_minus_list);
	__mcast_rt_send_grp_src_spec_query(port, grp, &x_list);	/* Send Q(G,X-A) */
	mcast_list_scan(&x_list, src_node_p, mcast_grp_src_t*)
	{
		if (src_node_p->tic > MCAST_TIC_CAL(mcast_cfg.last_member_query_time))
			src_node_p->tic = MCAST_TIC_CAL(mcast_cfg.last_member_query_time);
	}
	
	mcast_src_list_free(&x_minus_list);

	mcast_list_init(&y_minus_list, mcast_utl_src_cmp);
	mcast_src_list_minus(&y_list, new_src_list, &y_minus_list); /* Y-A */
	mcast_src_list_free(&y_minus_list);

	mcast_list_init(&x_union_list, mcast_utl_src_cmp);
	mcast_src_list_union(&x_list, new_src_list, &x_union_list);  /* X+A */

	mcast_src_list_union(&x_union_list, &y_list, &port_grp_info->src_list);  /* EXCLUDE (X+A,Y-A) */

	__mcast_rt_send_grp_spec_query(port, grp);  /* Send Q(G) */
	if (port_grp_info->grp_tic > MCAST_TIC_CAL(mcast_cfg.last_member_query_time))
	{
		port_grp_info->grp_tic = MCAST_TIC_CAL(mcast_cfg.last_member_query_time);
		igmp_dbg("grp_tic: %d\n", port_grp_info->grp_tic);
	}

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return MCAST_RET_OK;
}


/*
EXCLUDE (X,Y)  TO_EX (A)    EXCLUDE (A-Y,Y*A)       (A-X-Y)=Group Timer
                                                                               Delete (X-A)
                                                                               Delete (Y-A)
                                                                               Send Q(G,A-Y)
                                                                               Group Timer=GMI
*/
static mcast_ret_code __mcast_rt_cal_extoex(	
	IN bc_port_index_t port,
	IN bc_ip grp,
	IN mcast_pkt_record_type_e new_type,
	IN mcast_list_t *new_src_list,
	INOUT mcast_grp_port_t *port_grp_info)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	mcast_cfg_t mcast_cfg;
	mcast_grp_src_t *src_node_p = NULL;
	mcast_list_t minus_list;

	mcast_list_t x_list;
	mcast_list_t y_list;

	mcast_list_t x_fwd_list;
	mcast_list_t y_block_list;

	mcast_list_t union_fwd_list;
	
	mcast_list_init(&minus_list, mcast_utl_src_cmp);
	mcast_src_list_minus(new_src_list, &port_grp_info->src_list, &minus_list);
	mcast_cfg_get(&mcast_cfg);
	mcast_list_scan(new_src_list, src_node_p, mcast_grp_src_t*)
	{
		src_node_p->tic = port_grp_info->grp_tic;  /* (A-X-Y)=Group Timer */
	}
	port_grp_info->grp_tic = MCAST_TIC_CAL(mcast_cfg.member_interval);
	igmp_dbg("grp_tic: %d\n", port_grp_info->grp_tic);
	
	mcast_list_init(&x_list, mcast_utl_src_cmp);
	mcast_list_init(&y_list, mcast_utl_src_cmp);
	__mcast_rt_cal_ex2xy(&port_grp_info->src_list, &x_list, &y_list);

	mcast_list_init(&x_fwd_list, mcast_utl_src_cmp);
	mcast_src_list_minus(&x_list, &minus_list, &x_fwd_list); /* Delete (X-A) */
	mcast_src_list_free(&x_list);
	
	mcast_list_init(&y_block_list, mcast_utl_src_cmp);
	mcast_src_list_minus(&y_list, &minus_list, &y_block_list); /* Delete (Y-A) */
	mcast_src_list_free(&y_list);

	mcast_src_list_free(&minus_list);

	mcast_list_init(&union_fwd_list, mcast_utl_src_cmp);
	mcast_src_list_union(&x_fwd_list, new_src_list, &union_fwd_list);
	__mcast_rt_send_grp_src_spec_query(port, grp, &union_fwd_list);
	mcast_list_scan(&union_fwd_list, src_node_p, mcast_grp_src_t*)
	{
		if (src_node_p->tic > MCAST_TIC_CAL(mcast_cfg.last_member_query_time))
			src_node_p->tic = MCAST_TIC_CAL(mcast_cfg.last_member_query_time);
	}

	mcast_src_list_union(&union_fwd_list, &y_block_list, &port_grp_info->src_list);

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return MCAST_RET_OK;
}


/* EXCLUDE (X,Y)  ALLOW (A)    EXCLUDE (X+A,Y-A)       (A)=GMI */
static mcast_ret_code __mcast_rt_cal_exallow(	
	IN bc_port_index_t port,
	IN bc_ip grp,
	IN mcast_pkt_record_type_e new_type,
	IN mcast_list_t *new_src_list,
	INOUT mcast_grp_port_t *port_grp_info)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	mcast_cfg_t mcast_cfg;
	mcast_grp_src_t *src_node_p = NULL;

	mcast_list_t x_list;
	mcast_list_t y_list;

	mcast_list_t x_minus_list;
	mcast_list_t x_union_list;
	mcast_list_t y_minus_list;

	mcast_cfg_get(&mcast_cfg);
	mcast_list_scan(new_src_list, src_node_p, mcast_grp_src_t*)
	{
		src_node_p->tic = MCAST_TIC_CAL(mcast_cfg.member_interval); 
	}

	mcast_list_init(&x_list, mcast_utl_src_cmp);
	mcast_list_init(&y_list, mcast_utl_src_cmp);
	__mcast_rt_cal_ex2xy(&port_grp_info->src_list ,&x_list, &y_list);	

	mcast_list_init(&x_minus_list, mcast_utl_src_cmp);
	mcast_src_list_minus(&x_list, new_src_list, &x_minus_list);
	mcast_src_list_free(&x_minus_list);

	mcast_list_init(&y_minus_list, mcast_utl_src_cmp);
	mcast_src_list_minus(&y_list, new_src_list, &y_minus_list);
	mcast_src_list_free(&y_minus_list);

	mcast_list_init(&x_union_list, mcast_utl_src_cmp);
	mcast_src_list_union(&x_list, new_src_list, &x_union_list);

	mcast_src_list_union(&x_union_list, &y_list, &port_grp_info->src_list);

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return MCAST_RET_OK;
}


/*
EXCLUDE (X,Y)  BLOCK (A)    EXCLUDE (X+(A-Y),Y)     (A-X-Y)=Group Timer
                                                                                Send Q(G,A-Y)
*/
static mcast_ret_code __mcast_rt_cal_exblock(	
	IN bc_port_index_t port,
	IN bc_ip grp,
	IN mcast_pkt_record_type_e new_type,
	IN mcast_list_t *new_src_list,
	INOUT mcast_grp_port_t *port_grp_info)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	mcast_list_t minus_list;
	mcast_grp_src_t *src_node_p = NULL;
	mcast_cfg_t mcast_cfg;

	mcast_list_t x_list;
	mcast_list_t y_list;
	mcast_list_t x_list_ex;
	mcast_list_t union_list;

	mcast_list_init(&x_list, mcast_utl_src_cmp);
	mcast_list_init(&y_list, mcast_utl_src_cmp);
	__mcast_rt_cal_ex2xy(&port_grp_info->src_list ,&x_list, &y_list);	


	mcast_list_init(&minus_list, mcast_utl_src_cmp);
	mcast_src_list_minus(new_src_list, &y_list, &minus_list);
	mcast_src_list_free(&minus_list);
	__mcast_rt_send_grp_src_spec_query(port, grp, new_src_list);

	mcast_list_init(&minus_list, mcast_utl_src_cmp);
	mcast_src_list_minus(new_src_list, &x_list, &minus_list);
	mcast_list_init(&x_list_ex, mcast_utl_src_cmp);
	mcast_src_list_minus(&x_list, &minus_list, &x_list_ex);
	mcast_src_list_free(&minus_list);
	mcast_list_scan(new_src_list, src_node_p, mcast_grp_src_t*)
	{
		src_node_p->tic = port_grp_info->grp_tic;  /* (A-X-Y)=Group Timer */
	}

	mcast_cfg_get(&mcast_cfg);
	mcast_list_scan(&x_list_ex, src_node_p, mcast_grp_src_t*)
	{
		if (src_node_p->tic > MCAST_TIC_CAL(mcast_cfg.last_member_query_time))
			src_node_p->tic = MCAST_TIC_CAL(mcast_cfg.last_member_query_time);
	}

	mcast_list_init(&union_list, mcast_utl_src_cmp);
	mcast_src_list_union(&x_list,  &x_list_ex, &union_list);
	mcast_src_list_move(&x_list, &union_list);
	mcast_src_list_union(&x_list, new_src_list, &union_list);
	mcast_src_list_union(&union_list, &y_list, &port_grp_info->src_list);

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return MCAST_RET_OK;
}


typedef mcast_ret_code (*rt_cal_per_port_grp_info_func)(IN bc_port_index_t port, IN bc_ip grp, IN mcast_pkt_record_type_e new_type,
														IN mcast_list_t *new_src_list, INOUT mcast_grp_port_t *port_grp_info);

static rt_cal_per_port_grp_info_func rt_cal_func[] = {
		__mcast_rt_cal_inin,
		__mcast_rt_cal_inex,
		__mcast_rt_cal_intoin,
		__mcast_rt_cal_intoex,
		__mcast_rt_cal_inallow,
		__mcast_rt_cal_inblock,
		
		__mcast_rt_cal_exin,
		__mcast_rt_cal_exex,
		__mcast_rt_cal_extoin,
		__mcast_rt_cal_extoex,
		__mcast_rt_cal_exallow,
		__mcast_rt_cal_exblock
	};

/*
	7.3.2. In the Presence of Older Version Group Members 

	IGMPv3 routers may be placed on a network where there are hosts that have not yet been upgraded to IGMPv3. 
	In order to be compatible with older version hosts, IGMPv3 routers MUST operate in version 1 and version 2 compatibility modes.
	..............
*/
bc_boolean __mcast_rt_proc_grp_ver(
	IN bc_port_index_t port, 
	IN mcast_pkt_type_e pkt_type, 
	IN mcast_grp_t *grp)
{
	 mcast_cfg_t mcast_cfg;
	 bc_uint32 num;
	if (port.slot_id <= BC_PORT_SNI_MAX_SLOTNUM)
		num = port.port_id-1;
	if (port.slot_id > BC_PORT_SNI_MAX_SLOTNUM)
		num = (port.slot_id -BC_PORT_SNI_MAX_SLOTNUM -1) *BC_PORT_PON_MAX_PORTNUM + BC_PORT_SNI_MAX_PORTNUM + port.port_id -1;
	mcast_cfg_get(&mcast_cfg);
			
	if (pkt_type == MCAST_PBC_TYPE_V1_REPORT)
	{
		/*
			The IGMPv1 Host Present timer is set to Older Version Host Present Timeout seconds 
			whenever an IGMPv1 Membership Report is received.
		*/
		grp->port_grp[num].v1_tic = MCAST_TIC_CAL(mcast_cfg.older_host_present_interval);
	}
	else if (pkt_type == MCAST_PBC_TYPE_V2_REPORT)
	{
		/*
			The IGMPv2 Host Present timer is set to Older Version Host Present Timeout seconds 
			whenever an IGMPv2 Membership Report is received.
		*/
		grp->port_grp[num].v2_tic = MCAST_TIC_CAL(mcast_cfg.older_host_present_interval);
	}
	else
	{
		/* nothing */
	}

	return TRUE;
}

/* get this grp node from mcast_grp_tree, or create this grp node to mcast_grp_tree */
static mcast_grp_t* __mcast_rt_proc_grp_node(IN bc_ip grp, IN bc_uint16 vid, IN bc_boolean createIfNotExist)
{
	mcast_grp_t 	*grp_node_p = NULL;

	bc_uint32 	i;
	mcast_cfg_t 	mcast_cfg;
	bc_char buf[20];
	
	grp_node_p = mcast_rt_node_get(grp);/* find */
	if (!grp_node_p)
	{
		if (createIfNotExist == FALSE)
			return NULL;
		
		/* no exsited, create. */
		grp_node_p = (mcast_grp_t*)mcast_alloc(sizeof(mcast_grp_t));
		if (!grp_node_p)
			return NULL;
		
		/* fill in */
		mcast_cfg_get(&mcast_cfg);
		memset(grp_node_p, 0x00, sizeof(mcast_grp_t));
		grp_node_p->grp = grp;
		grp_node_p->vid = vid;
		for (i = 0; i < BC_PORT_PON_MAX_COUNT + BC_PORT_SNI_MAX_COUNT; i++)
		{
			grp_node_p->port_grp[i].mode = MCAST_PBC_RECORD_IS_INCLUDE;	/* default */
			mcast_list_init(&(grp_node_p->port_grp[i].src_list), __mc_rt_src_cmp);
			/*
				
				6.2.2.	Definition of Group Timers
				
				The group timer is only used when a group is in EXCLUDE mode and it represents the time for the *filter-mode* of the group to expire and switch to INCLUDE mode.	
				We define a group timer as a decrementing timer with a lower bound of zero kept per group per attached network. Group timers are updated according to the types of group records received.
				A group timer expiring when a router filter-mode for the group is EXCLUDE means there are no listeners on the attached network in EXCLUDE mode. 
				At this point, a router will transition to INCLUDE filter-mode. Section 6.5 describes the actions taken when a group timer expires while in EXCLUDE mode.
				
				Group
				Filter-Mode 	Group Timer Value		Actions/Comments
				----------- 	-----------------		----------------
				INCLUDE 		Timer >= 0				All members in INCLUDE mode.
				EXCLUDE 		Timer > 0				At least one member in EXCLUDE mode.
				EXCLUDE 		Timer == 0				No more listeners to group. If all source timers have expired then delete Group Record.
														If there are still source record timers running, switch to INCLUDE filter-mode using those source records with running timers as the INCLUDE source record state.
				grp_tic = GMI.
				The variable GMI is an abbreviation for the Group Membership Interval, which is the time in which group memberships will time out.

				---------------------
				rfc2236 - page-5
				When a router receives a Report, it adds the group being reported to the list of multicast group memberships 
				on the network on which it received the Report and sets the timer 
				for the membership to the [Group Membership Interval]. 
				Repeated Reports refresh the timer.
			*/
			grp_node_p->port_grp[i].grp_tic = MCAST_TIC_CAL(mcast_cfg.member_interval);
			/*
				7.3.2. In the Presence of Older Version Group Members 
			*/
			grp_node_p->port_grp[i].v1_tic = 0;  /* init */
			grp_node_p->port_grp[i].v2_tic = 0;
		#if 0
			igmp_dbg("@@@ grp: %s, vid: %d, pid: %d, mode: %d, grp_tic: %d\n", ip_format_get(grp_node_p->grp, buf), 
				(bc_uint16)grp_node_p->vid, i, grp_node_p->port_grp[i].mode, grp_node_p->port_grp[i].grp_tic);
		#endif
			/* insert */
			__mcast_rt_node_insert(grp_node_p);
		}
	}

	return grp_node_p;
}

/* merge src_list, new and old */
mcast_ret_code mcast_rt_proc_port_grp_info(
	IN bc_port_index_t port,/* rx port */
	IN bc_ip grp,
	IN bc_uint16 vid,
	IN mcast_pkt_type_e pkt_type, /* igmp version */
	IN mcast_pkt_record_type_e record_type,/* filter-mode type */
	IN mcast_list_t *src_list)/* received */
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	mcast_grp_t *grp_node_p = NULL;
	bc_uint16 func_offset = 0;
	bc_int32 num;
	mcast_ret_code ret = MCAST_RET_OK;

	/* get this grp node from mcast_grp_tree, or create this grp node and insert to the mcast_grp_tree*/
	grp_node_p = __mcast_rt_proc_grp_node(grp, vid, TRUE);
	if (grp_node_p == NULL)
	{
		BC_PT_DBG_FUN(BC_MODULE_IGMP, "__mcast_rt_proc_grp_node failure!\n");
		MCAST_RET_ERR(MCAST_MODULE_RT, MCAST_RET_ERR_NORES, TRUE);
	}
	
	/* In order to be compatible with older version hosts, 
	IGMPv3 routers MUST operate in version 1 and version 2 compatibility modes */
	__mcast_rt_proc_grp_ver(port, pkt_type, grp_node_p);

	/*get port index through port*/
	if (port.slot_id <= BC_PORT_SNI_MAX_SLOTNUM)
		num = port.port_id-1;
	if (port.slot_id > BC_PORT_SNI_MAX_SLOTNUM)
		num = (port.slot_id -BC_PORT_SNI_MAX_SLOTNUM -1) *BC_PORT_PON_MAX_PORTNUM + BC_PORT_SNI_MAX_PORTNUM + port.port_id -1;

	/* get fileter-mode callback through port mode and run it, for merge */
	func_offset = (grp_node_p->port_grp[num].mode == MCAST_PBC_RECORD_IS_INCLUDE) ? 0 : 6;
	func_offset += (record_type - 1);
//	BC_PT_DBG_FUN(BC_MODULE_IGMP, "func_offset:%d, num:%d\n", func_offset, num);

	/* merge */
	ret = (rt_cal_func[func_offset])(port, grp, record_type, src_list, &grp_node_p->port_grp[num]);

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return ret;
}

/* 
	rfc2236 page5
	-------------
	When a Querier receives a Leave Group message for a group that has 
	group members on the reception interface, it sends [Last Member Query Count] 
	Group-Specific Queries every [Last Member Query Interval] to the group being left.
	........................
*/
mcast_ret_code mcast_rt_proc_leave(IN bc_port_index_t port, IN bc_ip grp)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	mcast_grp_t *grp_node_p = NULL;
	mcast_cfg_t mcast_cfg;

	mcast_ret_code ret = MCAST_RET_OK;

	/* get this grp from route, ensure this grp exist.*/
	grp_node_p = mcast_rt_node_get(grp);
	if (grp_node_p == NULL)
		MCAST_RET_ERR(MCAST_MODULE_RT, MCAST_RET_ERR_NOTFOUND, FALSE);

	ret = __mcast_rt_send_grp_spec_query(port, grp);
	if (ret != MCAST_RET_OK)
		return ret;

	/*
		When a non-Querier receives a Group-Specific Query message, if its
		existing group membership timer is greater than [Last Member Query
		Count] times the Max Response Time specified in the message, it sets
		its group membership timer to that value.
	*/
	mcast_cfg_get(&mcast_cfg);
	if (grp_node_p->port_grp[port.port_id-1].grp_tic > mcast_cfg.last_member_query_time)
	{
		/*note: LMQT = LMQI*LMQC*/
		grp_node_p->port_grp[port.port_id-1].grp_tic = MCAST_TIC_CAL(mcast_cfg.last_member_query_time);
	}

	igmp_dbg("fun %s, pid: %d -> grp_tic: %d\n", __FUNCTION__, port.port_id, grp_node_p->port_grp[port.port_id-1].grp_tic);

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return MCAST_RET_OK;
}

#endif
#if 1

mcast_ret_code mcast_rt_mgt_del_grp(IN bc_ip grp)
{
	mcast_grp_t *grp_node_p = NULL;

	grp_node_p = mcast_rt_node_get(grp);
	if (grp_node_p == NULL)
		return MCAST_RET_OK; 

	/* remove node from the tree */
	__mcast_rt_grp_delete(grp_node_p);
	return MCAST_RET_OK;
}


mcast_ret_code mcast_rt_node_clear_all(void)
{
	mcast_grp_t *grp_node_p = NULL;

	while ((grp_node_p = mcast_rt_node_get_next(NULL)) != NULL)
	{
		mcast_rt_mgt_del_grp(grp_node_p->grp);
	}

	return MCAST_RET_OK;
}

#endif
#if 1


/* The API can't be used except debug */
void mcast_rt_grp_dump(void)
{
	mcast_grp_t **grp_p;

	bc_uint16 port_idx;
	mcast_grp_port_t *port_p;

	bc_uint16 port_src_node_cnt;
	mcast_grp_src_t *port_src_node_p;
	
	bc_uint16 cnt;

	bc_uint8 *ip;
	char buf[20] = {0};

	char *record_type_str[] = {
		"IS_IN",
		"IS_EX",
		"TO_IN",
		"TO_EX",
		"ALLOW",
		"BLOCK"
	};

	MCAST_DBG_PRT("\t--------------- GRP TREE ---------------");

	MCAST_DBG_PRT("\n\t%-16s%-5s", "GRP", "VID");
	MCAST_DBG_PRT("\n\t%-16s%-5s", "---------------", "----");

	cnt = 0;

	grp_p = (mcast_grp_t**)mcast_avltree_get_next(mcast_grp_tree, NULL);
	while (grp_p && *grp_p)
	{
		MCAST_DBG_PRT("\n\t");

		memset(buf, 0x00, 20);
		ip = (bc_uint8*)&(*grp_p)->grp;
		MCAST_DBG_SPRT_IP(buf, 20, ip);
		MCAST_DBG_PRT("%-16s%-5d", buf, (*grp_p)->vid);

		MCAST_DBG_PRT("\n\t  %-5s%-6s%-7s%-5s%-5s%-15s%-5s%-15s%-5s", "Port", "Mode", "GrpTic", "V1T", "V2T", "SrcIP", "Tic", "SrcIP", "Tic");
		MCAST_DBG_PRT("\n\t  %-5s%-6s%-7s%-5s%-5s%-15s%-5s%-15s%-5s", "----", "-----", "------", 
							"----", "----", "--------------", "----", "--------------", "----");

		for (port_idx = 0; port_idx < BC_PORT_PON_MAX_COUNT + BC_PORT_SNI_MAX_COUNT; port_idx++)
		{
			port_p = &((*grp_p)->port_grp[port_idx]);

			if (port_p->mode == MCAST_PBC_RECORD_IS_INCLUDE &&
				mcast_list_count(&(port_p->src_list)) == 0)
				continue;

			MCAST_DBG_PRT("\n\t  %-5d%-6s%-7d%-5d%-5d", port_idx+1, record_type_str[port_p->mode-1], 
															port_p->grp_tic, port_p->v1_tic, port_p->v2_tic);

			port_src_node_cnt = 0;
			port_src_node_p = (mcast_grp_src_t*)mcast_list_first(&port_p->src_list);
			while (port_src_node_p)
			{
				if (port_src_node_cnt != 0 && port_src_node_cnt%2 == 0)
					MCAST_DBG_PRT("\n\t  %-28s", " ");

				memset(buf, 0x00, 20);
				ip = (bc_uint8*)&port_src_node_p->src;
				MCAST_DBG_SPRT_IP(buf, 20, ip);
				MCAST_DBG_PRT("%-15s%-5d", buf, port_src_node_p->tic);

				port_src_node_cnt++;
				port_src_node_p = (mcast_grp_src_t*)mcast_list_next(port_src_node_p);
			}
		}
		
		cnt++;

		grp_p = (mcast_grp_t**)mcast_avltree_get_next(mcast_grp_tree, (void**)grp_p);
	}

	MCAST_DBG_PRT("\n\tTotal Cnt: %d\n", cnt);
}


/* The API can't be used except debug */
void mcast_rt_query_list_dump(void)
{
	mc_send_query_node_t *query_node_p;
	mcast_utl_src_node_t *src_node_p;

	bc_uint16 src_node_cnt;
	bc_uint16 cnt = 0;

	bc_uint8 *ip;
	char buf[20] = {0};

	char *qt_str[] = {
		"GQ",
		"GSQ",
		"GSSQ"
	};

	MCAST_DBG_PRT("\t--------------- Router Query List ---------------");

	MCAST_DBG_PRT("\n\t%-16s%-6s%-6s%-5s%-6s%-32s", "Grp", "SndP", "QType", "QCnt", "QInvl", "SrcList");
	MCAST_DBG_PRT("\n\t%-16s%-6s%-6s%-5s%-6s%-32s", "---------------", "-----", "-----", "----", "-----", "-------------------------------");

	query_node_p = (mc_send_query_node_t*)mcast_list_first(&mcast_send_query_list);
	while (query_node_p)
	{
		MCAST_DBG_PRT("\n\t");

		memset(buf, 0x00, 20);
		ip = (bc_uint8*)&query_node_p->grp;
		MCAST_DBG_SPRT_IP(buf, 20, ip);
		MCAST_DBG_PRT("%-16s%-6d%-6s%-5d%-6d", buf, query_node_p->send_port.port_id, qt_str[query_node_p->query_type], 
															query_node_p->query_count, query_node_p->query_interval);
		src_node_cnt = 0;
		src_node_p = (mcast_utl_src_node_t*)mcast_list_first(&query_node_p->src_list);
		while (src_node_p)
		{
			if (src_node_cnt != 0 && src_node_cnt%2 == 0)
				MCAST_DBG_PRT("\n\t%-39s", " ");
			src_node_cnt++;

			memset(buf, 0x00, 20);
			ip = (bc_uint8*)&src_node_p->src;
			MCAST_DBG_SPRT_IP(buf, 20, ip);
			MCAST_DBG_PRT("%-16s", buf);

			src_node_p = (mcast_utl_src_node_t*)mcast_list_next(src_node_p);
		}

		cnt++;
		query_node_p = (mc_send_query_node_t*)mcast_list_next(query_node_p);
	}

	MCAST_DBG_PRT("\n\tTotal Cnt:%d\n", cnt);	
}


/* The API can't be used except debug */
void mcast_rt_gen_query_dump(void)
{
	MCAST_DBG_PRT("\t--------------- Router Gen Query ---------------");
	MCAST_DBG_PRT("\n\tRouter Gen Query %ds", mcast_gen_query_tic);
	MCAST_DBG_PRT("\n");
}


void mcast_rt_init(void)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	mcast_cfg_t mcast_cfg;

	mcast_grp_tree = mcast_avltree_create(__mc_rt_cmp, NULL);
	if (mcast_grp_tree == NULL)
	{
		/* log it */
	}

	mcast_cfg_get(&mcast_cfg);
	mcast_gen_query_tic = MCAST_TIC_CAL(mcast_cfg.query_interval);

	mcast_list_init(&mcast_send_query_list, NULL);

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
}

#endif
#endif

