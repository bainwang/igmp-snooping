/*******************************************************************************
  [File name]	: mcast_host.c
  [Author]     	: bain.wang
  [Version]    	: 1.0
  [Date]       	: 2018-02-02
  [Description]	:
	Store upstream group state
  [Others]     	:
	NULL
  [Function List]:  
    1. ....
    2. ....
  [History]:
	 D a t e      	Modification 							 	Initials
	---------- 		--------------            					----------
	2018-02-02  	Created								 		bain.wang
*******************************************************************************/

#include "mcast_host.h"
#include "utili_block_ext.h"

#if BC_MULTICAST_INCLUDE
#if 1

/*only save src-list from rx for per grp. update or add, no merge!!!!!!*/
static mcast_avltree_t *mcast_host_tree = NULL;

static bc_int32 __mcast_host_node_cmp(const void *f, const void *s, void *param)
{
	mcast_host_grp_t *a;
	mcast_host_grp_t *b;

	a = (mcast_host_grp_t*)f;
	b = (mcast_host_grp_t*)s;

	if (a->grp > b->grp)
		return 1;
	else if (a->grp < b->grp)
		return -1;
	else
		return 0;
}


static mcast_host_grp_t* __mcast_host_node_delete(IN bc_ip grp)
{
	mcast_host_grp_t delete_node;
	mcast_host_grp_t *node_p;
	
	memset(&delete_node, 0x00, sizeof(mcast_host_grp_t));
	delete_node.grp = grp;
	node_p = (mcast_host_grp_t *)mcast_avltree_delete(mcast_host_tree, &delete_node);
	return node_p;
}

static bc_boolean __mcast_host_node_insert(IN mcast_host_grp_t *grp_node)
{
	return mcast_avltree_insert(mcast_host_tree, grp_node) ? FALSE : TRUE;
}


static mcast_host_grp_t* __mcast_host_node_get_next(IN mcast_host_grp_t *grp_node)
{
	mcast_host_grp_t **grp_node_p = NULL;

	if (grp_node)
	{
		grp_node_p = (mcast_host_grp_t **)mcast_avltree_find(mcast_host_tree, grp_node);
		if (grp_node_p == NULL || *grp_node_p == NULL)
			return NULL;
	}

	grp_node_p = (mcast_host_grp_t **)mcast_avltree_get_next(mcast_host_tree, (void**)grp_node_p);
	if (grp_node_p == NULL || *grp_node_p == NULL)
		return NULL;

	return *grp_node_p;
}

mcast_host_grp_t* mcast_host_node_get(IN bc_ip grp)
{
	mcast_host_grp_t find_node;
	mcast_host_grp_t **tree_node = NULL;

	memset(&find_node, 0x00, sizeof(mcast_host_grp_t));
	find_node.grp = grp;
	tree_node = (mcast_host_grp_t **)mcast_avltree_find(mcast_host_tree, &find_node);
	if (tree_node == NULL || *tree_node == NULL)
		return NULL;

	return *tree_node;
}


#endif
#if 1
//static utili_block_ext_t		mcast_host_src_block;

/*
			grp_node_p.port_grp[port_idx++].src_list	grp_host_state_p->src_list
			----------------------------------------	------------------------------
			EX		[0] = {a, b, c}						src = {a, b, c}
			IN		[1] = {a, c, d}						src = {}
			EX		[2]	= {d, e, f}						src = {d,e, f}
			EX		[3]	= {b, f, g}						src = {g}

														src = {a, b, c, d, e, f, g}
*/
static mcast_ret_code __mcsat_host_cvt_collect_srclist(	
	IN mcast_grp_t *grp_node_p, 
	OUT mcast_list_t *src_list) /*only EX*/
{
	mcast_cfg_t mcast_cfg;

	bc_int32 i;
	mcast_grp_src_t *src_node_p = NULL;
	mcast_host_src_t *add_node_p = NULL;

	mcast_cfg_get(&mcast_cfg);
	for (i = 0; i < BC_PORT_PON_MAX_COUNT + BC_PORT_SNI_MAX_COUNT; i++)
	{
		if (grp_node_p->port_grp[i].mode != MCAST_PBC_RECORD_IS_EXCLUDE)
			continue;

		src_node_p = (mcast_grp_src_t*)mcast_list_first(&grp_node_p->port_grp[i].src_list);
		while (src_node_p) /*all src of per EX port.*/
		{
			if (mcast_list_find(src_list, src_node_p->src) == NULL) /* avoid repeat */
			{
				add_node_p = (mcast_host_src_t*)mcast_alloc(sizeof(mcast_host_src_t));
				if (add_node_p == NULL)
				{
					mcast_src_list_free(src_list);
					MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_NORES, TRUE);
				}
				
				add_node_p->src = src_node_p->src;
				add_node_p->robustness = mcast_cfg.robustness;
				mcast_list_add(src_list, add_node_p);
			}

			src_node_p = (mcast_grp_src_t*)mcast_list_next(src_node_p);
		}
	}

	return MCAST_RET_OK;
}

/*
	result:
	cur_type = IN, cur_src_list contained of all forwards.
	cur_type = EX, cur_src_list contained of all no forwards.
*/
static mcast_ret_code __mcast_host_cvt_per_port(
	IN mcast_pkt_record_type_e new_type,
	IN mcast_list_t *new_src_list,	/* from */
	IN mcast_pkt_record_type_e cur_type,
	INOUT mcast_list_t *cur_src_list)/* to */
{
	mcast_list_t new_state_src_list;
	mcast_grp_src_t *grp_src_node_p = NULL;
	mcast_grp_src_t *grp_src_next_node_p = NULL;
	
	mcast_list_t minus_list;
	mcast_list_t union_list;

	mcast_list_init(&new_state_src_list, mcast_utl_src_cmp);
	if (mcast_src_list_copy(&new_state_src_list, new_src_list) == FALSE)
		MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_NORES, TRUE);

	/*
		each time proc one port, only leave no forwards src. 
		ex: EX(A, B), leave B.
		
			new_src_list(EX)						new_src_list (EX)
			-------------------------------			--------------------------
			{a[tic>0], b[tic==0], c[tic>0]}			{b}
	*/
	if (new_type == MCAST_PBC_RECORD_IS_EXCLUDE)
	{
		grp_src_node_p = (mcast_grp_src_t*)mcast_list_first(&new_state_src_list);
		if (grp_src_node_p)
		{
			do
			{
				grp_src_next_node_p = (mcast_grp_src_t*)mcast_list_next(grp_src_node_p);

				/* src tic !=0 mean: the the src will receive pkt */
				if (grp_src_node_p->tic != 0)
				{
					mcast_list_delete(&new_state_src_list, grp_src_node_p);
					mcast_free(grp_src_node_p);
				}
				
				grp_src_node_p = grp_src_next_node_p;
			} while(grp_src_node_p);
		}
	}

	/*
		copy all src-list of this port to cur_src_list

		cur_src_list(IN) is forwards, but empty, because no proc (on proc EX).
		new_src_list(IN) is forwards, from one port(IN).
		new_src_list = cur_src_list + new_src_list

		new_src_list(IN)		cur_src_list(IN)		cur_src_list(IN)
		----------------		--------------------	-------------------
		{i, j, k}				{}						{i, j, k}
	*/
	if (cur_type == MCAST_PBC_RECORD_IS_INCLUDE) /*conflict with above*/
	{
		if (new_type != MCAST_PBC_RECORD_IS_INCLUDE)
			MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_UNKNOW, TRUE);  /* code error */
		
		mcast_list_init(&minus_list, mcast_utl_src_cmp);
		mcast_src_list_minus(&new_state_src_list, cur_src_list, &minus_list);
		mcast_src_list_free(&minus_list);

		mcast_list_init(&union_list, mcast_utl_src_cmp);
		mcast_src_list_union(&new_state_src_list, cur_src_list, &union_list);

		mcast_src_list_move(cur_src_list, &union_list);
	}
	else if (cur_type == (MCAST_PBC_RECORD_IS_EXCLUDE))
	{
		/*
		cur_src_list(EX) is no forwards, from all port(EX).
		new_src_list(IN) is forwards, from one port(IN).
		new_src_list = cur_src_list - new_src_list

		new_src_list(IN)		cur_src_list(EX)		cur_src_list(EX)
		----------------		---------------------	----------------
		{a, d, f}				{a, b, c, d, e, f, g}	{b, c, e, g}
		*/
		if (new_type == MCAST_PBC_RECORD_IS_INCLUDE)
		{
			mcast_list_init(&minus_list, mcast_utl_src_cmp);
			mcast_src_list_minus(cur_src_list, &new_state_src_list, &minus_list);
			mcast_src_list_free(&minus_list);
		}
		/*
		cur_src_list(EX) is no forwards, from per port(EX(A, B)).
		new_src_list(EX) is no forwards, from one port(EX(A, B), only leave B).

		new_src_list(EX)		cur_src_list(EX)		cur_src_list(EX)
		----------------		---------------------	----------------
		{b}						{a, b, c, d, e, f, g}	{b}
		*/
		else if (new_type == MCAST_PBC_RECORD_IS_EXCLUDE)
		{
			mcast_list_init(&minus_list, mcast_utl_src_cmp);
			mcast_src_list_minus(cur_src_list, &new_state_src_list, &minus_list);
			mcast_src_list_free(cur_src_list);
			
			mcast_src_list_move(cur_src_list, &minus_list);
		}
		else
		{
			MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_UNKNOW, TRUE); /* code error */
		}
	}
	else
	{
		MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_UNKNOW, TRUE);
	}

	return MCAST_RET_OK;
}

/*
	fill in grp_host_state_p base on rx report msg. (after new and old merge)
*/
static mcast_ret_code __mcast_host_cvt_grp_rt2host(
	IN mcast_grp_t *grp_node_p, 
	OUT mcast_host_grp_t *grp_host_state_p)
{
	bc_int32 i;
	mcast_ret_code ret = MCAST_RET_OK;

	grp_host_state_p->grp = grp_node_p->grp;
	grp_host_state_p->vid =  grp_node_p->vid;

	/* decide mode */
	grp_host_state_p->type = MCAST_PBC_RECORD_IS_INCLUDE;
	for (i = 0; i < BC_PORT_PON_MAX_COUNT + BC_PORT_SNI_MAX_COUNT; i++)
	{
		if (grp_node_p->port_grp[i].mode == MCAST_PBC_RECORD_IS_EXCLUDE)
		{
			grp_host_state_p->type = MCAST_PBC_RECORD_IS_EXCLUDE;
			break;
		}
	}

	mcast_src_list_free(&grp_host_state_p->src_list);
	mcast_list_init(&grp_host_state_p->src_list, mcast_utl_src_cmp);

	/* src-list contain of no forward sources. */
	if (grp_host_state_p->type == MCAST_PBC_RECORD_IS_EXCLUDE)
	{
		ret = __mcsat_host_cvt_collect_srclist(grp_node_p, &grp_host_state_p->src_list);
		if (ret != MCAST_RET_OK)
			return ret;
	}

	/*
	result:
		cur_type = IN, cur_src_list contained of all forwards.
		cur_type = EX, cur_src_list contained of all no forwards.
	*/
	for (i = 0; i < BC_PORT_PON_MAX_COUNT + BC_PORT_SNI_MAX_COUNT; i++)
	{
		if ((ret = __mcast_host_cvt_per_port(grp_node_p->port_grp[i].mode, &(grp_node_p->port_grp[i].src_list), 
										grp_host_state_p->type, &grp_host_state_p->src_list)) != MCAST_RET_OK)
		{
			mcast_src_list_free(&grp_host_state_p->src_list);
			return ret;
		}
	}

	return MCAST_RET_OK;
}

#endif
#if 1
#if 1

typedef struct {
	mcast_list_node_t	list_node;

	bc_ip src;
	bc_uint8 reserve[4]; /* compatibility mcast_grp_src_t */
} mc_delay_src_node_t;

typedef struct {
	mcast_list_node_t	list_node;
	
	mcast_pkt_record_type_e type;
	mcast_list_t src_list;

	bc_uint16	tic;
	bc_uint16 max_resp_time;
	bc_uint16	robustness;
} mc_delay_record_node_t;

typedef struct {
	bc_ip	grp;		/* key */
	bc_uint16	vid;		/* furture use for key: no use */

	mcast_list_t 	record_list;

	bc_uint16		query_tic;		/* for query */
	mcast_list_t 	gssq_src_list;		/* for group source specific query */
} mc_delay_report_node_t;

static bc_uint32  gen_query_tic = 0;

#endif
#if 1

static bc_int32 __mcast_host_record_cmp(IN void *node, IN bc_uint32 key)
{
	mc_delay_record_node_t	*report_p = NULL;

	report_p = (mc_delay_record_node_t*)node;

	if (report_p->type > key)
		return 1;
	else if (report_p->type < key)
		return -1;
	else
		return 0;
}

static bc_boolean __mcast_host_record_free(IN mc_delay_record_node_t *record_node_p)
{
	if (record_node_p == NULL)
		return TRUE;

	mcast_src_list_free(&record_node_p->src_list);
	mcast_free(record_node_p);
	record_node_p = NULL;
	return TRUE;
}


static bc_boolean __mcast_host_record_clear(IN mcast_list_t *report_list_p)
{
	mc_delay_record_node_t *record_node_p = NULL;

	while ((record_node_p = (mc_delay_record_node_t*)mcast_list_first(report_list_p)))
	{
		mcast_list_delete(report_list_p, record_node_p);
		__mcast_host_record_free(record_node_p);
		record_node_p = NULL;
	}

	return TRUE;
}

/*
	A = (B-A) + A, 
	B = B-A
	-------------------
	befor:
		A = {1,2,3}
		B = {2,3,4}
	after:
		A = {1,2,3,4}
		B = {4}
*/
static mcast_ret_code __record_merge_mode_change_allowtoin(
	INOUT mc_delay_record_node_t *toin_p,
	INOUT mc_delay_record_node_t *allow_p)
{
	mcast_list_t minus_list;
	mcast_list_t union_list;

	mcast_list_init(&minus_list, mcast_utl_src_cmp);
	mcast_src_list_minus(&allow_p->src_list, &toin_p->src_list, &minus_list);
	mcast_src_list_free(&minus_list);

	mcast_list_init(&union_list, mcast_utl_src_cmp);
	mcast_src_list_union(&toin_p->src_list, &allow_p->src_list, &union_list);
	mcast_src_list_move(&toin_p->src_list, &union_list);

	return MCAST_RET_OK;
}

/*
	A = (A*B) + A, 
	B = B
	-------------------
	befor:
		A = {1,2,3}
		B = {2,3,4}
	after:
		A = {1,2,3,2,3}
		B = {2,3,4}
*/
static mcast_ret_code __record_merge_srclist_change_toinallow(
	INOUT mc_delay_record_node_t *toin_node, 
	INOUT mc_delay_record_node_t *new_allow_node)
{
	mcast_list_t minus_list;
	mcast_list_t union_list;

	mcast_list_init(&minus_list, mcast_utl_src_cmp);
	mcast_src_list_minus(&new_allow_node->src_list, &toin_node->src_list, &minus_list);
	mcast_src_list_free(&new_allow_node->src_list);

	mcast_list_init(&union_list, mcast_utl_src_cmp);
	mcast_src_list_union(&toin_node->src_list, &minus_list, &union_list);
	mcast_src_list_move(&toin_node->src_list, &union_list);

	return MCAST_RET_OK;
}

/*
	A = A-B, 
	B = B
	-------------------
	befor:
		A = {1,2,3}
		B = {2,3,4}
	after:
		A = {1}
		B = {2,3,4}
*/
static mcast_ret_code __record_merge_srclist_change_toexallow(
	INOUT mc_delay_record_node_t *toex_node, 
	INOUT mc_delay_record_node_t *new_allow_node)
{
	mcast_list_t minus_list;

	mcast_list_init(&minus_list, mcast_utl_src_cmp);
	mcast_src_list_minus(&toex_node->src_list, &new_allow_node->src_list, &minus_list);
	mcast_src_list_free(&minus_list);

	return MCAST_RET_OK;
}

/*
	A = (B-A)+B, 
	B = A*B
	-------------------
	befor:
		A = {1,2,3}
		B = {2,3,4}
	after:
		A = {2,3,4,4}
		B = {2,3}

*/
static mcast_ret_code __record_merge_srclist_change_allowallow(
	INOUT mc_delay_record_node_t *allow_node, 
	INOUT mc_delay_record_node_t *new_allow_node)
{
	mcast_list_t minus_list;
	mcast_list_t union_list;

	mcast_list_init(&minus_list, mcast_utl_src_cmp);
	mcast_src_list_minus(&new_allow_node->src_list, &allow_node->src_list, &minus_list);// B-A

	mcast_list_init(&union_list, mcast_utl_src_cmp);
	mcast_src_list_union(&new_allow_node->src_list, &allow_node->src_list, &union_list); // 
	mcast_src_list_move(&allow_node->src_list, &union_list);

	mcast_src_list_move(&new_allow_node->src_list, &minus_list);

	return MCAST_RET_OK;
}

/*
	A = A-B, 
	B = B
	-------------------
	befor:
		A = {1,2,3}
		B = {2,3,4}
	after:
		A = {1}
		B = {2,3,4}
*/
static mcast_ret_code __record_merge_srclist_change_blockallow(
	INOUT mc_delay_record_node_t *block_node, 
	INOUT mc_delay_record_node_t *new_allow_node)
{
	mcast_list_t minus_list;

	mcast_list_init(&minus_list, mcast_utl_src_cmp);
	mcast_src_list_minus(&block_node->src_list, &new_allow_node->src_list, &minus_list);
	mcast_src_list_free(&minus_list);

	return MCAST_RET_OK;
}

/*
	A = A, 
	B = B
	-------------------
	befor:
		A = {1,2,3}
		B = {2,3,4}
	after:
		A = {1,2,3}
		B = {2,3,4}
*/
static mcast_ret_code __record_merge_srclist_change_toinblock(
	INOUT mc_delay_record_node_t *toin_node, 
	INOUT mc_delay_record_node_t *new_block_node)
{
#if 0
	mcast_list_t minus_list;

	mcast_list_init(&minus_list, mcast_utl_src_cmp);
	mcast_src_list_minus(&toin_node->src_list, &new_block_node->src_list, &minus_list);
	mcast_src_list_free(&minus_list);
#endif
	return MCAST_RET_OK;
}

/*
	A = (A*B)+A, 
	B = B-A
	-------------------
	befor:
		A = {1,2,3}
		B = {2,3,4}
	after:
		A = {1,2,3,2,3}
		B = {4}
*/
static mcast_ret_code __record_merge_srclist_change_toexblock(
	INOUT mc_delay_record_node_t *toex_node, 
	INOUT mc_delay_record_node_t *new_block_node)
{
	mcast_list_t minus_list;
	mcast_list_t union_list;

	mcast_list_init(&minus_list, mcast_utl_src_cmp);
	mcast_src_list_minus(&new_block_node->src_list, &toex_node->src_list, &minus_list);
	mcast_src_list_free(&minus_list);

	mcast_list_init(&union_list, mcast_utl_src_cmp);
	mcast_src_list_union(&toex_node->src_list, &minus_list, &union_list);
	mcast_src_list_move(&toex_node->src_list, &union_list);

	return MCAST_RET_OK;
}

/*
	A = A-B, 
	B = B
	-------------------
	befor:
		A = {1,2,3}
		B = {2,3,4}
	after:
		A = {1}
		B = {2,3,4}

*/
static mcast_ret_code __record_merge_srclist_change_allowblock(
	INOUT mc_delay_record_node_t *allow_node, 
	INOUT mc_delay_record_node_t *new_block_node)
{
	mcast_list_t minus_list;

	mcast_list_init(&minus_list, mcast_utl_src_cmp);
	mcast_src_list_minus(&allow_node->src_list, &new_block_node->src_list, &minus_list);
	mcast_src_list_free(&minus_list);

	return MCAST_RET_OK;
}

/*
	A = A+(B-A), 
	B = A*B
	-------------------
	befor:
		A = {1,2,3}
		B = {2,3,4}
	after:
		A = {1,2,3,4}
		B = {2,3}
*/
static mcast_ret_code __record_merge_srclist_change_blockblock(
	INOUT mc_delay_record_node_t *block_node, 
	INOUT mc_delay_record_node_t *new_block_node)
{
	mcast_list_t minus_list;
	mcast_list_t union_list;

	mcast_list_init(&minus_list, mcast_utl_src_cmp);
	mcast_src_list_minus(&new_block_node->src_list, &block_node->src_list, &minus_list);

	mcast_list_init(&union_list, mcast_utl_src_cmp);
	mcast_src_list_union(&new_block_node->src_list, &block_node->src_list, &union_list);
	mcast_src_list_move(&block_node->src_list, &union_list);

	mcast_src_list_move(&new_block_node->src_list, &minus_list);
	
	return MCAST_RET_OK;
}

#if 0
static mc_delay_record_node_t* __mcast_host_record_copy_node(IN mc_delay_record_node_t* node)
{
	mc_delay_record_node_t *node_p = NULL;
	node_p = (mc_delay_record_node_t*)mcast_alloc(sizeof(mc_delay_record_node_t));
	if (node_p == NULL)
		return NULL;

	memset(node_p, 0x00, sizeof(mc_delay_record_node_t));
	node_p->type = node->type;
	node_p->tic = node->tic;
	node_p->max_resp_time = node->max_resp_time;
	node_p->robustness = node->robustness;

	mcast_list_init(&node_p->src_list, mcast_utl_src_cmp);
	if (mcast_src_list_copy(&node_p->src_list, &node->src_list) == FALSE)
	{
		mcast_free(node_p);
		return NULL;
	}

	return node_p;
}
#endif

static bc_boolean __mcast_host_record_add(IN mcast_list_t *record_list_p, IN mc_delay_record_node_t *record)
{
	mc_delay_record_node_t *record_node_p = NULL;

	record_node_p = (mc_delay_record_node_t*)mcast_list_find(record_list_p, record->type);
	if (record_node_p == NULL)
	{
		mcast_list_add(record_list_p, record);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

#endif
#if 1

/*存放了各report报文中的信息*/
static mcast_avltree_t *mcast_delay_report_tree = NULL;

static int __mcast_host_delay_report_cmp(const void *f, const void *s, void *param)
{
	mc_delay_report_node_t *a;
	mc_delay_report_node_t *b;

	a = (mc_delay_report_node_t*)f;
	b = (mc_delay_report_node_t*)s;

	if (a->grp > b->grp)
		return 1;
	else if (a->grp < b->grp)
		return -1;
	else
		return 0;
}

static mc_delay_report_node_t* __mcast_host_delay_report_get(IN bc_ip grp, IN bc_uint16 vid)
{
	mc_delay_report_node_t find_node;
	mc_delay_report_node_t **tree_node_p;

	memset(&find_node, 0x00, sizeof(mc_delay_report_node_t));
	find_node.grp = grp;
	find_node.vid = vid;
	
	tree_node_p = (mc_delay_report_node_t**)mcast_avltree_find(mcast_delay_report_tree, &find_node);
	if (tree_node_p == NULL || *tree_node_p == NULL)
		return NULL;
	else
		return *tree_node_p;
}

static mc_delay_report_node_t* __mcast_host_delay_report_get_next(IN mc_delay_report_node_t *cur_node_p)
{
	mc_delay_report_node_t **tree_node_p = NULL;

	if (cur_node_p != NULL)
	{
		/*NOTE: 收到report报文后，在对HOST端进行处理时，会将信息存放在这个树中*/
		tree_node_p = (mc_delay_report_node_t**)mcast_avltree_find(mcast_delay_report_tree, cur_node_p);
		if (tree_node_p == NULL || *tree_node_p == NULL)
			return NULL;
	}

	tree_node_p = (mc_delay_report_node_t**)mcast_avltree_get_next(mcast_delay_report_tree, (void**)tree_node_p);
	if (tree_node_p == NULL || *tree_node_p == NULL)
		return NULL;

	return *tree_node_p;
}

static bc_boolean __mcast_host_delay_report_insert(IN mc_delay_report_node_t *node_p)
{
	node_p = (mc_delay_report_node_t*)mcast_avltree_insert(mcast_delay_report_tree, node_p);
	return (node_p) ? FALSE : TRUE;
}

static bc_boolean __mcast_host_delay_report_delete(IN mc_delay_report_node_t *node_p)
{
	node_p = (mc_delay_report_node_t*)mcast_avltree_delete(mcast_delay_report_tree, node_p);
	return (node_p) ? TRUE : FALSE; 
}

static bc_boolean __mcast_host_delay_report_free(IN mc_delay_report_node_t *node_p)
{
	if (node_p == NULL)
		return TRUE;

	__mcast_host_record_clear(&node_p->record_list);
	mcast_src_list_free(&node_p->gssq_src_list);
	mcast_free(node_p);
	return TRUE;
}

static mcast_ret_code __merged_filter_mode_change(
	IN mc_delay_report_node_t *report_node_p,
	IN mc_delay_record_node_t *new_record_node_p)
{
	mc_delay_record_node_t *old_record_node_p = NULL;
	mc_delay_record_node_t *old_next_record_node_p = NULL;

	mcast_ret_code ret = MCAST_RET_OK;

	if (new_record_node_p->type != MCAST_PBC_RECORD_CHANGE_TO_INCLUDE &&
		new_record_node_p->type != MCAST_PBC_RECORD_CHANGE_TO_EXCLUDE)
		MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_PAR, TRUE);

	old_next_record_node_p = NULL;
	old_record_node_p = (mc_delay_record_node_t*)mcast_list_first(&report_node_p->record_list);
	while (old_record_node_p)
	{
		old_next_record_node_p = (mc_delay_record_node_t*)mcast_list_next(old_record_node_p);

		/*
			new mode         old mode      				desc
			TOIN                 ISIN                	code error
			TOIN                 ISEX                	code error
			TOIN                 TOIN                 	It's impossible on protocol, toin appears only when ex mode timeout
			TOIN                 TOEX                	It's impossible on protocol, ex change to in, need time: member interval
			TOIN                 ALLOW             		OK, deal it
			TOIN                 BLOCK              	OK, deal it

			TOEX		    	 ISIN					code error
			TOEX                 ISEX              		code error
			TOEX                 TOIN                 	OK, deal it, ex mode timeout and received a isex or toex packet
			TOEX                 TOEX					It's impossible on protocol, can't appear toex continue
			TOEX                 ALLOW              	OK, deal it
			TOEX                 BLOCK              	OK, deal it
		*/
		if (new_record_node_p->type == MCAST_PBC_RECORD_CHANGE_TO_INCLUDE &&
			old_record_node_p->type == MCAST_PBC_RECORD_ALLOW_NEW_SOURCES)
		{
			/* allow recieve src, and then(the delay report is a short time), the mode chagne to include, 
			so, the allow packet is triggered by include mode packet.
			so, i think the allow src must include in the toin record already, the follow code is avoid exception */
			ret = __record_merge_mode_change_allowtoin(new_record_node_p, old_record_node_p);
			if (ret != MCAST_RET_OK)
				break;
		}
		else if (new_record_node_p->type == MCAST_PBC_RECORD_CHANGE_TO_INCLUDE &&
			old_record_node_p->type == MCAST_PBC_RECORD_BLOCK_OLD_SOURCES)
		{
			/* here block node is trigger by include packet or src tic timeout, but we don't know the follow request 
			is whether or not need the src, so don't merge the block node */
		}
		else if (new_record_node_p->type == MCAST_PBC_RECORD_CHANGE_TO_EXCLUDE &&
			old_record_node_p->type == MCAST_PBC_RECORD_CHANGE_TO_INCLUDE)
		{
			/* the condition is deal when host state before and after compare to calculate record */
		}
		else if (new_record_node_p->type == MCAST_PBC_RECORD_CHANGE_TO_EXCLUDE &&
			old_record_node_p->type == MCAST_PBC_RECORD_ALLOW_NEW_SOURCES)
		{
			/* the condition is deal when host state before and after compare to calculate record */
		}
		else if (new_record_node_p->type == MCAST_PBC_RECORD_CHANGE_TO_EXCLUDE &&
			old_record_node_p->type == MCAST_PBC_RECORD_BLOCK_OLD_SOURCES)
		{
			/* the condition is deal when host state before and after compare to calculate record */
		}
		else
		{
			/* error condition */
			MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_PAR, TRUE);
		}

		mcast_list_delete(&report_node_p->record_list, old_record_node_p);
		__mcast_host_record_free(old_record_node_p);
		old_record_node_p = old_next_record_node_p;
	}

	if (ret == MCAST_RET_OK)
		__mcast_host_record_add(&report_node_p->record_list, new_record_node_p);
	
	return ret;
}


static mcast_ret_code __merged_src_list_change_allow(
	IN mc_delay_report_node_t *report_node_p,
	IN mc_delay_record_node_t *new_record_node_p)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	mc_delay_record_node_t *old_record_node_p = NULL;
	mc_delay_record_node_t *old_next_record_node_p = NULL;

	bc_boolean dont_insert_node = FALSE;

	mcast_ret_code ret = MCAST_RET_OK;

	if (new_record_node_p->type != MCAST_PBC_RECORD_ALLOW_NEW_SOURCES)
		MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_PAR, TRUE);

	dont_insert_node = FALSE;
	old_record_node_p = (mc_delay_record_node_t*)mcast_list_first(&report_node_p->record_list);
	while (old_record_node_p)
	{
		old_next_record_node_p = (mc_delay_record_node_t*)mcast_list_next(old_record_node_p);

		/*
			new mode         old mode      	desc
			ALLOW              ISIN                	code error
			ALLOW              ISEX                	code error
			ALLOW              TOIN                 	OK, deal it
			ALLOW              TOEX                	OK, deal it
			ALLOW              ALLOW             	OK, deal it
			ALLOW              BLOCK              	OK, deal it
		*/
		if (old_record_node_p->type == MCAST_PBC_RECORD_CHANGE_TO_INCLUDE)
		{
			dont_insert_node = TRUE;
			ret = __record_merge_srclist_change_toinallow(old_record_node_p, new_record_node_p);
			if (ret != MCAST_RET_OK)
				return ret;
		}
		else if (old_record_node_p->type == MCAST_PBC_RECORD_CHANGE_TO_EXCLUDE)
		{
			dont_insert_node = TRUE;
			ret = __record_merge_srclist_change_toexallow(old_record_node_p, new_record_node_p);
			if (ret != MCAST_RET_OK)
				return ret;
		}		
		else if (old_record_node_p->type == MCAST_PBC_RECORD_ALLOW_NEW_SOURCES)
		{
			dont_insert_node = TRUE;
			ret = __record_merge_srclist_change_allowallow(old_record_node_p, new_record_node_p);
			if (ret != MCAST_RET_OK)
				return ret;
		}
		else if (old_record_node_p->type == MCAST_PBC_RECORD_BLOCK_OLD_SOURCES)
		{
		
	ret = __record_merge_srclist_change_blockallow(old_record_node_p, new_record_node_p);
			if (ret != MCAST_RET_OK)
				return ret;

			if (mcast_list_count(&old_record_node_p->src_list) == 0)
			{
				mcast_list_delete(&report_node_p->record_list, old_record_node_p);
				__mcast_host_record_free(old_record_node_p);
			}
		}
		else
		{
			/* do nothing */
			MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_PAR, TRUE);
		}
			
		old_record_node_p = old_next_record_node_p;
	}

	if (dont_insert_node)
		__mcast_host_record_free(new_record_node_p);
	else
		__mcast_host_record_add(&report_node_p->record_list, new_record_node_p);

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return MCAST_RET_OK;
}


static mcast_ret_code __merged_src_list_change_block(
	IN mc_delay_report_node_t *report_node_p,
	IN mc_delay_record_node_t *new_record_node_p)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	mc_delay_record_node_t *old_record_node_p = NULL;
	mc_delay_record_node_t *old_next_record_node_p = NULL;

	bc_boolean dont_insert_node = FALSE;

	mcast_ret_code ret = MCAST_RET_OK;

	if (new_record_node_p->type != MCAST_PBC_RECORD_BLOCK_OLD_SOURCES)
		MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_PAR, TRUE);

	dont_insert_node = FALSE;
	old_record_node_p = (mc_delay_record_node_t*)mcast_list_first(&report_node_p->record_list);
	while (old_record_node_p)
	{
		old_next_record_node_p = (mc_delay_record_node_t*)mcast_list_next(old_record_node_p);

		/*
			new mode         old mode      	desc
			BLOCK		   ISIN			code error
			BLOCK              ISEX              	code error
			BLOCK              TOIN                 	OK, deal it
			BLOCK              TOEX			OK, deal it
			BLOCK              ALLOW              	OK, deal it
			BLOCK              BLOCK              	OK, deal it
		*/
		if (old_record_node_p->type == MCAST_PBC_RECORD_CHANGE_TO_INCLUDE)
		{
			dont_insert_node = TRUE;
			
			/* ??? be careful, src list equal zero */
			/* the current design can't deal src list equal zero condition, so i just igron the case */
			ret = __record_merge_srclist_change_toinblock(old_record_node_p, new_record_node_p);
			if (ret != MCAST_RET_OK)
				return ret;
		}
		else if (old_record_node_p->type == MCAST_PBC_RECORD_CHANGE_TO_EXCLUDE)
		{
			dont_insert_node = TRUE;
			ret = __record_merge_srclist_change_toexblock(old_record_node_p, new_record_node_p);
			if (ret != MCAST_RET_OK)
				return ret;
		}
		else if (old_record_node_p->type == MCAST_PBC_RECORD_ALLOW_NEW_SOURCES)
		{
		
	ret = __record_merge_srclist_change_allowblock(old_record_node_p, new_record_node_p);
			if (ret != MCAST_RET_OK)
				return ret;

			if (mcast_list_count(&old_record_node_p->src_list) == 0)
			{
				mcast_list_delete(&report_node_p->record_list, old_record_node_p);
				__mcast_host_record_free(old_record_node_p);
			}
		}
		else if (old_record_node_p->type == MCAST_PBC_RECORD_BLOCK_OLD_SOURCES)
		{
			dont_insert_node = TRUE;
		
	ret = __record_merge_srclist_change_blockblock(old_record_node_p, new_record_node_p);
			if (ret != MCAST_RET_OK)
				return ret;
		}
		else
		{
			/* do nothing */
			MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_PAR, TRUE);
		}
			
		old_record_node_p = old_next_record_node_p;
	}

	if (dont_insert_node)
		__mcast_host_record_free(new_record_node_p);
	else
		__mcast_host_record_add(&report_node_p->record_list, new_record_node_p);

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return MCAST_RET_OK;
}


static mcast_ret_code __merged_src_list_change(
	IN mc_delay_report_node_t *report_node_p,
	IN mc_delay_record_node_t *new_record_node_p)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	mcast_ret_code ret = MCAST_RET_OK;

	if (new_record_node_p->type == MCAST_PBC_RECORD_ALLOW_NEW_SOURCES)
	{
		ret = __merged_src_list_change_allow(report_node_p, new_record_node_p);
	}
	else if (new_record_node_p->type == MCAST_PBC_RECORD_BLOCK_OLD_SOURCES)
	{
		ret = __merged_src_list_change_block(report_node_p, new_record_node_p);
	}
	else
	{	
		MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_UNTYPE, TRUE);
	}

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return ret;
}

/*
	merge to report_node_p.
*/
static mcast_ret_code __mcast_host_delay_report_merge_records(
	IN mc_delay_report_node_t *report_node_p, 
	IN mcast_list_t *new_reocrd_list)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	mc_delay_record_node_t *new_record_node_p = NULL;
	mc_delay_record_node_t *new_next_record_node_p = NULL;
	mcast_ret_code ret = MCAST_RET_OK;

	new_record_node_p = (mc_delay_record_node_t*)mcast_list_first(new_reocrd_list);
	while (new_record_node_p)
	{
		new_next_record_node_p = (mc_delay_record_node_t*)mcast_list_next(new_record_node_p);
		mcast_list_delete(new_reocrd_list, new_record_node_p);
	
		if (new_record_node_p->type == MCAST_PBC_RECORD_CHANGE_TO_INCLUDE ||
			new_record_node_p->type == MCAST_PBC_RECORD_CHANGE_TO_EXCLUDE)
		{
			ret = __merged_filter_mode_change(report_node_p, new_record_node_p);
			if (ret != MCAST_RET_OK)
			{
				__mcast_host_record_free(new_record_node_p);  /* if success, the node will be insert list */
				break;
			}
		}
		else if (new_record_node_p->type == MCAST_PBC_RECORD_ALLOW_NEW_SOURCES ||
				new_record_node_p->type == MCAST_PBC_RECORD_BLOCK_OLD_SOURCES)
		{
			ret = __merged_src_list_change(report_node_p, new_record_node_p);
			if (ret != MCAST_RET_OK)
			{
				__mcast_host_record_free(new_record_node_p); /* if success, the node will be insert list */
				break;
			}
		}
		else
		{
			/* 
				MCAST_PBC_RECORD_IS_INCLUDE || MCAST_PBC_RECORD_IS_EXCLUDE
				error condition, need log it
			*/
			__mcast_host_record_free(new_record_node_p);
			MCAST_LOG(MCAST_MODULE_HOST, MCAST_RET_ERR_PAR, TRUE);
			break;
		}

		new_record_node_p = new_next_record_node_p;
	}

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return ret;
}


bc_boolean mcast_host_delay_report_clear(void)
{
	mc_delay_report_node_t *node_p = NULL;
	
	while ((node_p = __mcast_host_delay_report_get_next(NULL)) != NULL)
	{
		__mcast_host_delay_report_delete(node_p);
		__mcast_host_delay_report_free(node_p);
	}

	return TRUE;
}


#endif
#if 1

static mcast_ret_code __mcast_host_send_isinex_report(IN mc_delay_report_node_t *report_node_p)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	mcast_host_grp_t *grp_host_state;
	
	mcast_list_t report_list;
	mcast_tx_report_node_t *report_node;

	mcast_list_t bak_gssq_list;
	mcast_list_t send_src_list;

	mcast_ret_code ret;

	grp_host_state = mcast_host_node_get(report_node_p->grp);
	if (grp_host_state == NULL)
		MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_NOTFOUND, TRUE);

	mcast_list_init(&report_list, NULL);
	report_node = (mcast_tx_report_node_t*)mcast_alloc(sizeof(mcast_tx_report_node_t));
	if (report_node == NULL)
		MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_NORES, TRUE);

	memset(report_node, 0x00, sizeof(mcast_tx_report_node_t));
	report_node->grp = grp_host_state->grp;
	report_node->vid = grp_host_state->vid;
	report_node->type = grp_host_state->type;
	mcast_list_init(&report_node->src_list, mcast_utl_src_cmp);

	if (mcast_list_count(&report_node_p->gssq_src_list) != 0)
	{
		mcast_list_init(&bak_gssq_list, mcast_utl_src_cmp);
		if (mcast_src_list_copy(&bak_gssq_list, &report_node_p->gssq_src_list) == FALSE)
		{
			mcast_free(report_node);
			MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_NORES, TRUE);
		}

		if (report_node->type == MCAST_PBC_RECORD_IS_INCLUDE)
		{
			mcast_list_init(&send_src_list, mcast_utl_src_cmp);
			mcast_src_list_minus(&bak_gssq_list, &grp_host_state->src_list, &send_src_list);
			mcast_src_list_free(&bak_gssq_list);

			mcast_src_list_move(&report_node->src_list, &send_src_list);
		}
		else if (report_node->type == MCAST_PBC_RECORD_IS_EXCLUDE)
		{
			report_node->type = MCAST_PBC_RECORD_IS_INCLUDE; /* base protocol "IS_IN(B-A)" */

			mcast_list_init(&send_src_list, mcast_utl_src_cmp);
			mcast_src_list_minus(&bak_gssq_list, &grp_host_state->src_list, &send_src_list);
			mcast_src_list_free(&send_src_list);

			mcast_src_list_move(&report_node->src_list, &bak_gssq_list);
		}
		else
		{
			mcast_src_list_free(&bak_gssq_list);
			mcast_free(report_node);
			MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_UNKNOW, TRUE);
		}
	}
	else
	{
		if (mcast_src_list_copy(&report_node->src_list, &grp_host_state->src_list) == FALSE)
		{
			mcast_free(report_node);
			MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_NORES, TRUE);
		}
	}

	mcast_list_add(&report_list, report_node);

	ret = mcast_tx_report(&report_list);

	mcast_src_list_free(&report_node->src_list);
	mcast_list_delete(&report_list, report_node);
	mcast_free(report_node);

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return ret;
}

static mcast_ret_code __mcast_host_send_recordchange_report(IN bc_ip grp, IN mc_delay_record_node_t *record)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	mcast_list_t report_list;
	mcast_tx_report_node_t *tx_report_node_p = NULL;
	mcast_ret_code ret;

	mcast_list_init(&report_list, NULL);

	tx_report_node_p = (mcast_tx_report_node_t*)mcast_alloc(sizeof(mcast_tx_report_node_t));
	if (tx_report_node_p == NULL)
		MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_NOTFOUND, TRUE);

	memset(tx_report_node_p, 0x00, sizeof(mcast_tx_report_node_t));
	tx_report_node_p->grp = grp;
	tx_report_node_p->vid = 0;
	tx_report_node_p->type = record->type;
	mcast_list_init(&tx_report_node_p->src_list, mcast_utl_src_cmp);
	if (mcast_src_list_copy(&tx_report_node_p->src_list, &record->src_list) == FALSE)
	{
		mcast_free(tx_report_node_p);
		MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_NORES, TRUE);
	}

	mcast_list_add(&report_list, tx_report_node_p);
	ret = mcast_tx_report(&report_list);
	
	mcast_src_list_free(&tx_report_node_p->src_list);
	mcast_list_delete(&report_list, tx_report_node_p);
	mcast_free(tx_report_node_p);

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return ret;
}

void mcast_host_send_report_tic(void)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	mc_delay_report_node_t *report_node_p = NULL;
	mc_delay_report_node_t *free_report_node_p = NULL;
	mc_delay_record_node_t *record_node_p = NULL;
	mc_delay_record_node_t *free_record_node_p = NULL;

#if 0 //add by bain.wang@outlook.com for test
	static int ii++;
	int *tx_report_node_p = NULL;
	BC_PT_DBG_SMP(BC_MODULE_IGMP, "*************************************************counter:%d*************************************************\n", ii);
	tx_report_node_p = (int*)bc_platform_mem_malloc(BC_MODULE_IGMP, sizeof(int));
//	tx_report_node_p = (mcast_tx_report_node_t*)malloc(sizeof(mcast_tx_report_node_t));
	return ;
#endif	

	free_report_node_p = NULL;

	while ((report_node_p = __mcast_host_delay_report_get_next(report_node_p)) != NULL)
	{
		if (free_report_node_p)
		{
			__mcast_host_delay_report_delete(free_report_node_p);
			__mcast_host_delay_report_free(free_report_node_p);
			free_report_node_p = NULL;
		}

		if (report_node_p->query_tic != 0)
		{
			report_node_p->query_tic--;
			if (report_node_p->query_tic == 0)
				__mcast_host_send_isinex_report(report_node_p);/* TX  this  report_node_p node to all up port*/
		}

		free_record_node_p = NULL;

		record_node_p = (mc_delay_record_node_t*)mcast_list_first(&report_node_p->record_list);
		if (record_node_p)
		{
			do
			{
				if (free_record_node_p)
				{
					mcast_list_delete(&report_node_p->record_list, free_record_node_p);
					__mcast_host_record_free(free_record_node_p);
					free_record_node_p = NULL;
				}
				if (record_node_p->tic != 0)
					record_node_p->tic--;
				
				if (record_node_p->tic == 0)
				{
					__mcast_host_send_recordchange_report(report_node_p->grp, record_node_p);

					if (record_node_p->robustness > 0)
						record_node_p->robustness--;

					if (record_node_p->robustness != 0)
						record_node_p->tic = mcast_random(MCAST_TIC_CAL(record_node_p->max_resp_time));
					
					else
						free_record_node_p = record_node_p;
				}
			} while ((record_node_p = (mc_delay_record_node_t*)mcast_list_next(record_node_p)) != NULL);
		}

		if (free_record_node_p)
		{
			mcast_list_delete(&report_node_p->record_list, free_record_node_p);
			__mcast_host_record_free(free_record_node_p);
			free_record_node_p = NULL;
		}

		if (report_node_p->query_tic == 0 && mcast_list_count(&report_node_p->record_list) == 0)
			free_report_node_p = report_node_p;
	}

	if (free_report_node_p)
	{
		__mcast_host_delay_report_delete(free_report_node_p);
		__mcast_host_delay_report_free(free_report_node_p);
		free_report_node_p = NULL;
	}

	/* deal with gen query */
		gen_query_tic--;

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
}

#endif
#if 1
//static utili_block_ext_t		mcast_host_grp_block;

/*
	Old State 		New State 		State-Change Record Sent
	----------- 	----------- 	------------------------
	INCLUDE (A) 	INCLUDE (B) 	ALLOW (B-A), BLOCK (A-B)
*/
static mcast_ret_code __mcast_host_proc_rpt_inin(
	IN mcast_host_grp_t *old_state_p, 
	IN mcast_host_grp_t *new_state_p,
	OUT mcast_list_t *record_list)
{
	mcast_cfg_t protocol_cfg;

	mcast_list_t new_list;
	mcast_list_t old_list;
	mc_delay_record_node_t *allow_node_p = NULL;
	mc_delay_record_node_t *block_node_p = NULL;

	mcast_list_t common_list;

	mcast_cfg_get(&protocol_cfg);

	/* allow */
	mcast_list_init(&new_list, mcast_utl_src_cmp);	/* B */
	if (mcast_src_list_copy(&new_list, &new_state_p->src_list) == FALSE)
		MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_NORES, TRUE);

	mcast_list_init(&old_list, mcast_utl_src_cmp);	/* A */
	if (mcast_src_list_copy(&old_list, &old_state_p->src_list) == FALSE)
	{
		mcast_src_list_free(&new_list);
		MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_NORES, TRUE);
	}

	allow_node_p = (mc_delay_record_node_t*)mcast_alloc(sizeof(mc_delay_record_node_t));
	if (allow_node_p == NULL)
	{
		mcast_src_list_free(&new_list);
		mcast_src_list_free(&old_list);
		MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_NORES, TRUE);
	}

	memset(allow_node_p, 0x00, sizeof(mc_delay_record_node_t));
	allow_node_p->type = MCAST_PBC_RECORD_ALLOW_NEW_SOURCES;	/* ALLOW */
	mcast_list_init(&allow_node_p->src_list, mcast_utl_src_cmp);

	/*
		To cover the possibility of the State-Change Report being missed by one or more multicast routers, 
		it is retransmitted [Robustness Variable] - 1 more times, 
		at intervals chosen at random from the range (0, [Unsolicited Report Interval]).

		8.11. Unsolicited Report Interval
			The Unsolicited Report Interval is the time between repetitions of a
			host’s initial report of membership in a group. Default: 1 second.
	*/
	allow_node_p->max_resp_time = protocol_cfg.unsolicited_report_interval;
	allow_node_p->robustness = protocol_cfg.robustness;
	allow_node_p->tic = mcast_random(MCAST_TIC_CAL(allow_node_p->max_resp_time));

	mcast_list_init(&common_list, mcast_utl_src_cmp);
	mcast_src_list_minus(&new_list, &old_list, &common_list);
	mcast_src_list_move(&allow_node_p->src_list, &new_list);	/* B-A */
	if (mcast_list_count(&allow_node_p->src_list) == 0)
	{
		/*
			If the computed source list for either an ALLOW or a BLOCK State Change Record is empty, 
			that record is omitted from the Report message.
		*/
		mcast_free(allow_node_p);
		allow_node_p = NULL;
	}
	else
	{
		mcast_list_add(record_list, allow_node_p);/* add ALLOW (B-A) to record_list*/ 
	}

	/* block */
	mcast_src_list_move(&new_list, &common_list); /* A*B */
	
	block_node_p = (mc_delay_record_node_t*)mcast_alloc(sizeof(mc_delay_record_node_t));
	if (block_node_p == NULL)
	{
		mcast_src_list_free(&new_list);
		mcast_src_list_free(&old_list);
		MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_NORES, TRUE);
	}

	memset(block_node_p, 0x00, sizeof(mc_delay_record_node_t));
	block_node_p->type = MCAST_PBC_RECORD_BLOCK_OLD_SOURCES;	/* BLOCK */
	mcast_list_init(&block_node_p->src_list, mcast_utl_src_cmp);
	block_node_p->max_resp_time = protocol_cfg.unsolicited_report_interval;
	block_node_p->robustness = protocol_cfg.robustness;
	block_node_p->tic = mcast_random(MCAST_TIC_CAL(block_node_p->max_resp_time));

	mcast_src_list_minus(&old_list, &new_list, &common_list);
	mcast_src_list_move(&block_node_p->src_list, &old_list); /* A-(A*B) == A-B */
	if (mcast_list_count(&block_node_p->src_list) == 0)
	{
		/*
			If the computed source list for either an ALLOW or a BLOCK StateChange Record is empty, 
			that record is omitted from the Report message.
		*/
		mcast_free(block_node_p);
		block_node_p = NULL;
	}
	else
	{
		mcast_list_add(record_list, block_node_p);/*add BLOCK (A-B) to record_list*/ 
	}

	mcast_src_list_free(&new_list);	
	mcast_src_list_free(&common_list);

	return MCAST_RET_OK;
}

/*
	Old State 		New State 		State-Change Record Sent
	----------- 	----------- 	------------------------
	INCLUDE (A) 	EXCLUDE (B) 	TO_EX (B)
*/
static mcast_ret_code __mcast_host_proc_rpt_inex(
	IN mcast_host_grp_t *old_state_p, 
	IN mcast_host_grp_t *new_state_p,
	OUT mcast_list_t *record_list)
{
	mcast_cfg_t protocol_cfg;
	mc_delay_record_node_t *toex_node_p = NULL;

	mcast_cfg_get(&protocol_cfg);

	toex_node_p = (mc_delay_record_node_t*)mcast_alloc(sizeof(mc_delay_record_node_t));
	if (toex_node_p == NULL)
		MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_NORES, TRUE);

	memset(toex_node_p, 0x00, sizeof(mc_delay_record_node_t));
	toex_node_p->type = MCAST_PBC_RECORD_CHANGE_TO_EXCLUDE;
	mcast_list_init(&toex_node_p->src_list, mcast_utl_src_cmp);
	toex_node_p->max_resp_time = protocol_cfg.unsolicited_report_interval;
	toex_node_p->robustness = protocol_cfg.robustness;
	toex_node_p->tic = mcast_random(MCAST_TIC_CAL(toex_node_p->max_resp_time));
	if (mcast_src_list_copy(&toex_node_p->src_list, &new_state_p->src_list) == FALSE)
	{
		mcast_free(toex_node_p);
		MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_NORES, TRUE);
	}

	mcast_list_add(record_list, toex_node_p);
	return MCAST_RET_OK;
}

/*
	Old State 		New State 		State-Change Record Sent
	----------- 	----------- 	------------------------
	EXCLUDE (A) 	EXCLUDE (B) 	ALLOW (A-B), BLOCK (B-A)
*/
static mcast_ret_code __mcast_host_proc_rpt_exex(
	IN mcast_host_grp_t *old_state_p, 
	IN mcast_host_grp_t *new_state_p,
	OUT mcast_list_t *record_list)
{
	mcast_cfg_t protocol_cfg;

	mcast_list_t new_list;
	mcast_list_t old_list;
	mc_delay_record_node_t *allow_node_p = NULL;
	mc_delay_record_node_t *block_node_p = NULL;

	mcast_list_t common_list;

	mcast_cfg_get(&protocol_cfg);

	/* allow */
	mcast_list_init(&new_list, mcast_utl_src_cmp);
	if (mcast_src_list_copy(&new_list, &new_state_p->src_list) == FALSE)
		MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_NORES, TRUE);

	mcast_list_init(&old_list, mcast_utl_src_cmp);
	if (mcast_src_list_copy(&old_list, &old_state_p->src_list) == FALSE)
	{
		mcast_src_list_free(&new_list);
		MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_NORES, TRUE);
	}

	allow_node_p = (mc_delay_record_node_t*)mcast_alloc(sizeof(mc_delay_record_node_t));
	if (allow_node_p == NULL)	
	{
		mcast_src_list_free(&new_list);
		mcast_src_list_free(&old_list);
		MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_NORES, TRUE);
	}

	memset(allow_node_p, 0x00, sizeof(mc_delay_record_node_t));
	allow_node_p->type = MCAST_PBC_RECORD_ALLOW_NEW_SOURCES;
	mcast_list_init(&allow_node_p->src_list, mcast_utl_src_cmp);
	allow_node_p->max_resp_time = protocol_cfg.unsolicited_report_interval;
	allow_node_p->robustness = protocol_cfg.robustness;
	allow_node_p->tic = mcast_random(MCAST_TIC_CAL(allow_node_p->max_resp_time));

	mcast_list_init(&common_list, mcast_utl_src_cmp);
	mcast_src_list_minus(&old_list, &new_list, &common_list);
	mcast_src_list_move(&allow_node_p->src_list, &old_list);
	if (mcast_list_count(&allow_node_p->src_list) == 0)
	{
		mcast_free(allow_node_p);
		allow_node_p = NULL;
	}
	else
	{
		mcast_list_add(record_list, allow_node_p);
	}


	/* block */
	mcast_src_list_move(&old_list, &common_list);

	block_node_p = (mc_delay_record_node_t*)mcast_alloc(sizeof(mc_delay_record_node_t));
	if (block_node_p == NULL)
	{
		mcast_src_list_free(&new_list);
		mcast_src_list_free(&old_list);
		MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_NORES, TRUE);
	}

	memset(block_node_p, 0x00, sizeof(mc_delay_record_node_t));
	block_node_p->type = MCAST_PBC_RECORD_BLOCK_OLD_SOURCES;
	mcast_list_init(&block_node_p->src_list, mcast_utl_src_cmp);
	block_node_p->max_resp_time = protocol_cfg.unsolicited_report_interval;
	block_node_p->robustness = protocol_cfg.robustness;
	block_node_p->tic = mcast_random(MCAST_TIC_CAL(block_node_p->max_resp_time));
	
	mcast_src_list_minus(&new_list, &old_list, &common_list);
	mcast_src_list_move(&block_node_p->src_list, &new_list);
	if (mcast_list_count(&block_node_p->src_list) == 0)
	{
		mcast_free(block_node_p);
		block_node_p = NULL;
	}
	else
	{
		mcast_list_add(record_list, block_node_p);
	}
	
	mcast_src_list_free(&old_list);		/* the old_list var same with new_list */
	mcast_src_list_free(&common_list);  /* the new_list var same with old_list */

	return MCAST_RET_OK;
}

/*
	Old State 		New State 		State-Change Record Sent
	----------- 	----------- 	------------------------
	EXCLUDE (A) 	INCLUDE (B) 	TO_IN (B)
*/
static mcast_ret_code __mcast_host_proc_rpt_exin(
	IN mcast_host_grp_t *old_state_p, 
	IN mcast_host_grp_t *new_state_p,
	OUT mcast_list_t *record_list)
{
	mcast_cfg_t protocol_cfg;
	mc_delay_record_node_t *toin_node_p = NULL;
	
	mcast_cfg_get(&protocol_cfg);

	toin_node_p = (mc_delay_record_node_t*)mcast_alloc(sizeof(mc_delay_record_node_t));
	if (toin_node_p == NULL)
		MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_NORES, TRUE);

	memset(toin_node_p, 0x00, sizeof(mc_delay_record_node_t));
	toin_node_p->type = MCAST_PBC_RECORD_CHANGE_TO_INCLUDE;
	mcast_list_init(&toin_node_p->src_list, mcast_utl_src_cmp);
	toin_node_p->max_resp_time = protocol_cfg.unsolicited_report_interval;
	toin_node_p->robustness = protocol_cfg.robustness;
	toin_node_p->tic = mcast_random(MCAST_TIC_CAL(toin_node_p->max_resp_time));
	if (mcast_src_list_copy(&toin_node_p->src_list, &new_state_p->src_list) == FALSE)
	{
		mcast_free(toin_node_p);
		MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_NORES, TRUE);
	}

	mcast_list_add(record_list, toin_node_p);
	return MCAST_RET_OK;
}


static mcast_host_grp_t* __mcast_host_proc_prev_node_init(IN bc_ip grp, OUT bc_boolean *alloc)
{
	mcast_host_grp_t *host_node_p = NULL;

	*alloc = FALSE;
	host_node_p = mcast_host_node_get(grp);
	if (host_node_p == NULL)
	{
		host_node_p = (mcast_host_grp_t*)mcast_alloc(sizeof(mcast_host_grp_t));
		if (host_node_p == NULL)
		{
			BC_PT_DBG_FUN(BC_MODULE_IGMP, "bc_platform_mem_malloc failure!\n");
			return NULL;
		}
		memset(host_node_p, 0x00, sizeof(mcast_host_grp_t));
		host_node_p->grp = grp;
		host_node_p->vid = 0;
		host_node_p->type = MCAST_PBC_RECORD_IS_INCLUDE;
		mcast_list_init(&host_node_p->src_list, mcast_utl_src_cmp);
		*alloc = TRUE;
	}

	return host_node_p;
}

/*
	create and fill in a host node of this grp. contained of file-mode, src-list.
*/
static mcast_host_grp_t* __mcast_host_proc_new_node_init(IN mcast_grp_t *new_grp_node_p)
{
	mcast_host_grp_t *host_node_p = NULL;
	mcast_ret_code ret;

	host_node_p = (mcast_host_grp_t*)mcast_alloc(sizeof(mcast_host_grp_t)); /*create*/
	if (host_node_p == NULL)
		return NULL;

	memset(host_node_p, 0x00, sizeof(mcast_host_grp_t));
	mcast_list_init(&host_node_p->src_list, mcast_utl_src_cmp);
	/*
		fill in host_node_p base on rx report msg. (after new and old merge)
	*/
	ret = __mcast_host_cvt_grp_rt2host(new_grp_node_p, host_node_p);
	if (ret != MCAST_RET_OK)
	{
		mcast_free(host_node_p);
		return NULL;
	}

	return host_node_p;
}

/*merge for host*/
static mcast_ret_code __mcast_host_proc_record(
	IN mcast_host_grp_t *old_host_node_p,	/* pending record */ 
	IN mcast_host_grp_t *new_host_node_p, 	/* cur rx record */
	OUT mcast_list_t *record_list)			/* new record after merge */
{
	mcast_ret_code ret = MCAST_RET_OK;

	/*
		Old State 		New State 		State-Change Record Sent
		----------- 	----------- 	------------------------
		INCLUDE (A) 	INCLUDE (B) 	ALLOW (B-A), BLOCK (A-B)
	*/
	if (old_host_node_p->type == MCAST_PBC_RECORD_IS_INCLUDE &&
		new_host_node_p->type == MCAST_PBC_RECORD_IS_INCLUDE)
	{
		ret = __mcast_host_proc_rpt_inin(old_host_node_p, new_host_node_p, record_list);
	}
	/*
		Old State 		New State 		State-Change Record Sent
		----------- 	----------- 	------------------------
		INCLUDE (A) 	EXCLUDE (B) 	TO_EX (B)
	*/
	else if (old_host_node_p->type == MCAST_PBC_RECORD_IS_INCLUDE &&
		new_host_node_p->type == MCAST_PBC_RECORD_IS_EXCLUDE)
	{
		ret = __mcast_host_proc_rpt_inex(old_host_node_p, new_host_node_p, record_list);
	}
	/*
		Old State 		New State 		State-Change Record Sent
		----------- 	----------- 	------------------------
		EXCLUDE (A) 	EXCLUDE (B) 	ALLOW (A-B), BLOCK (B-A)
	*/
	else if (old_host_node_p->type == MCAST_PBC_RECORD_IS_EXCLUDE &&
		new_host_node_p->type == MCAST_PBC_RECORD_IS_EXCLUDE)
	{
		ret = __mcast_host_proc_rpt_exex(old_host_node_p, new_host_node_p, record_list);
	}
	/*
		Old State 		New State 		State-Change Record Sent
		----------- 	----------- 	------------------------
		EXCLUDE (A) 	INCLUDE (B) 	TO_IN (B)
	*/
	else if (old_host_node_p->type == MCAST_PBC_RECORD_IS_EXCLUDE &&
		new_host_node_p->type == MCAST_PBC_RECORD_IS_INCLUDE)
	{
		ret = __mcast_host_proc_rpt_exin(old_host_node_p, new_host_node_p, record_list);
	}
	else
	{
		MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_PAR, TRUE);
	}

	return ret;
}

/*get this grp in mcast_delay_report_tree, if no exist, crate it*/
static mc_delay_report_node_t* __mcast_host_proc_delay_report_get(
	IN bc_ip grp, 
	IN bc_uint16 vid, 
	IN bc_boolean createIfNotExist,
	OUT bc_boolean *alloc)
{
	mc_delay_report_node_t *report_node_p = NULL;

	*alloc = FALSE;

	//find this grp in mcast_delay_report_tree, if no exist, create it.
	report_node_p = __mcast_host_delay_report_get(grp, vid);
	if (report_node_p == NULL)
	{
		if (!createIfNotExist)
			return NULL;

		report_node_p = (mc_delay_report_node_t*)mcast_alloc(sizeof(mc_delay_report_node_t));
		if (report_node_p == NULL)
			return NULL;

		memset(report_node_p, 0x00, sizeof(mc_delay_report_node_t));
		report_node_p->grp = grp;
		report_node_p->vid = 0;
		mcast_list_init(&(report_node_p->record_list), __mcast_host_record_cmp);
		report_node_p->query_tic = 0;
		mcast_list_init(&(report_node_p->gssq_src_list), mcast_utl_src_cmp);
		if (__mcast_host_delay_report_insert(report_node_p) == FALSE)/*insert*/
		{
			mcast_free(report_node_p);
			return NULL;
		}

		*alloc = TRUE;
	}

	return report_node_p;
}

/*
	5. Description of the Protocol for Group Members
		5.1. Action on Change of Interface State
		
	trigger report and update host grp state
		get src-list from rx, and update or add to mcast_host_tree, and merge with old src-list of mcast_host_tree.
		merge resutl and src-list from mcast_delay_report_tree, and update this tree.
*/
mcast_ret_code mcast_host_trigger_report(IN mcast_grp_t *new_grp_node_p)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	bc_boolean old_host_node_alloc = FALSE;
	mcast_host_grp_t *old_host_node_p = NULL;
	mcast_host_grp_t *new_host_node_p = NULL;
	mcast_list_t record_list;

	mc_delay_report_node_t *report_node_p = NULL;
	bc_boolean new_delay_report_node = FALSE;

	mcast_ret_code ret = MCAST_RET_OK;

#if 1
	/*
		get new_host_node_p base-on rx.
		note:this new_host_node_p will update to mcast_host_tree.
	*/
	new_host_node_p = __mcast_host_proc_new_node_init(new_grp_node_p);
	if (new_host_node_p == NULL)
	{
		BC_PT_DBG_FUN(BC_MODULE_IGMP, "__mcast_host_proc_new_node_init failure!\n");
		MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_NORES, TRUE);
	}
	BC_PT_DBG_FUN(BC_MODULE_IGMP, "new_grp_node_p => new_host_node_p successful\n");
#endif

#if 1
	/*
		get old_host_node_p from mcast_host_tree.
	*/
	/*this alloc only for nonoccurrence sigment err when merge if mcast_host_tree has not this grp node.*/
	old_host_node_p = __mcast_host_proc_prev_node_init(new_grp_node_p->grp, &old_host_node_alloc);
	if (old_host_node_p == NULL)
	{
		BC_PT_DBG_FUN(BC_MODULE_IGMP, "get or malloc old_host_node_p on mcast_host_tree failure\n");
		mcast_src_list_free(&new_host_node_p->src_list);
		mcast_free(new_host_node_p);
		MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_NORES, TRUE);
	}
	BC_PT_DBG_FUN(BC_MODULE_IGMP, "get or malloc old_host_node_p on mcast_host_tree successful\n");
#endif

#if 1
	/*
		merge old_host_node_p and new_host_node_p to record_list. 
		note: record_list will merge with src-list from mcast_delay_report_tree, and update this tree.
		--------------
		5.1. Action on Change of Interface State
			However these records are not transmitted in a message 
			but instead merged with the contents of the pending report, 
			to create the new State-Change report. 
	*/
	mcast_list_init(&record_list, NULL);
	ret = __mcast_host_proc_record(old_host_node_p, new_host_node_p, &record_list);/*old and new no change.*/
#endif

#if 1
	/*
		update new_host_node_p to mcast_host_tree.
	*/
	
	if (old_host_node_alloc == FALSE) /* if old host node exist, del it from mcast_host_tree */
		old_host_node_p = __mcast_host_node_delete(new_grp_node_p->grp);

	if (old_host_node_p)
	{
		mcast_free(old_host_node_p);
	}

	/* only when new state don't equal ISIN(NULL), insert it to mcast_host_tree */
	if (!(new_host_node_p->type == MCAST_PBC_RECORD_IS_INCLUDE &&
			mcast_list_count(&new_host_node_p->src_list) == 0))
	{
		__mcast_host_node_insert(new_host_node_p);
		/*note: only when igmp disable, mcast_host_tree will be clean, other time, was updated*/
	}
	else
	{
		mcast_src_list_free(&new_host_node_p->src_list);
		mcast_free(new_host_node_p);
	}
#endif
	
	if (ret != MCAST_RET_OK)/*for merge*/
	{
		BC_PT_DBG_FUN(BC_MODULE_IGMP, "__mcast_host_proc_record failure!\n");
		__mcast_host_record_clear(&record_list);
		return ret;
	}

	/*
		If the computed source list for either an ALLOW or a BLOCK record is
		empty, that record is omitted from the State-Change report.
	*/
	if (mcast_list_count(&record_list) == 0)/* The state no change */
		return MCAST_RET_OK;

#if 1
	/*
		merge record_list and src-list from mcast_delay_report_tree, and update to it.
	*/
	/*get this grp from mcast_delay_report_tree, if no exist, crate it*/
	report_node_p = __mcast_host_proc_delay_report_get(new_grp_node_p->grp, 
							new_grp_node_p->vid, TRUE, &new_delay_report_node);
	if (report_node_p == NULL)
	{
		BC_PT_DBG_FUN(BC_MODULE_IGMP, "__mcast_host_proc_delay_report_get failure!\n");
		MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_NORES, TRUE);
	}
	BC_PT_DBG_FUN(BC_MODULE_IGMP, "get or malloc and insert on mcast_delay_report_tree successful!\n");

	/* merge src-list for delay_report_node, and update it to mcast_delay_report_tree */
	ret = __mcast_host_delay_report_merge_records(report_node_p, &record_list);
	if (ret != MCAST_RET_OK)
	{
		BC_PT_DBG_FUN(BC_MODULE_IGMP, "__mcast_host_delay_report_merge_records failure!\n");
		if (new_delay_report_node)
			mcast_free(report_node_p);
		return ret;
	}
	BC_PT_DBG_FUN(BC_MODULE_IGMP, "process record_list for host, and insert to mcast_delay_report_tree successful!\n");
#endif

	//free resource.
	__mcast_host_record_clear(&record_list);

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return MCAST_RET_OK;
}

mcast_ret_code mcast_host_proc_gen_query(IN mcast_pkt_igmp_query_t *query)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	mcast_grp_t *grp_node_p = NULL;
	mc_delay_report_node_t *report_node_p = NULL;
	bc_char buf[20];

	/* current exist gen query and the resp timer less */
	if ((gen_query_tic != 0) && (query->max_resp_time > gen_query_tic))
		return MCAST_RET_OK;

	gen_query_tic = MCAST_TIC_CAL(query->max_resp_time);

	while ((grp_node_p = mcast_rt_node_get_next(grp_node_p)) != NULL)
	{
		report_node_p = __mcast_host_delay_report_get(grp_node_p->grp, 0);
		if (report_node_p)
		{
			mcast_src_list_free(&report_node_p->gssq_src_list);

			if ((report_node_p->query_tic == 0) || (report_node_p->query_tic > MCAST_TIC_CAL(query->max_resp_time)))
			{
				report_node_p->query_tic = mcast_random(MCAST_TIC_CAL(query->max_resp_time));
				igmp_dbg("%s -> report_node_p->query_tic: %d\n", ip_format_get(report_node_p->grp, buf), report_node_p->query_tic);
			}
		}
		else
		{
			report_node_p = (mc_delay_report_node_t*)mcast_alloc(sizeof(mc_delay_report_node_t));
			if (report_node_p == NULL)
			{
				MCAST_LOG(MCAST_MODULE_HOST, MCAST_RET_ERR_NORES, TRUE);
				continue;
			}

			memset(report_node_p, 0x00, sizeof(mc_delay_report_node_t));
			report_node_p->grp = grp_node_p->grp;
			report_node_p->vid = 0;
			mcast_list_init(&(report_node_p->record_list), __mcast_host_record_cmp);
			report_node_p->query_tic = mcast_random(MCAST_TIC_CAL(query->max_resp_time));
			mcast_list_init(&(report_node_p->gssq_src_list), mcast_utl_src_cmp);
			if (__mcast_host_delay_report_insert(report_node_p) == FALSE)
			{
				mcast_free(report_node_p);
				MCAST_LOG(MCAST_MODULE_HOST, MCAST_RET_ERR_UNKNOW, TRUE);
			}
		}
	}

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return MCAST_RET_OK;
}

mcast_ret_code mcast_host_proc_grp_spec_query(IN mcast_pkt_igmp_query_t *query)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	mcast_grp_t *grp_node_p;
	mc_delay_report_node_t *report_node_p = NULL;
	bc_char buf[20] = {'0'};
	
	if ((gen_query_tic != 0) && (query->max_resp_time > gen_query_tic))
		return MCAST_RET_OK;	/* current exist gen query and the resp timer less */

	grp_node_p = mcast_rt_node_get(query->grp);
	if (grp_node_p)
	{
		report_node_p = __mcast_host_delay_report_get(query->grp, 0);
		if (report_node_p)
		{
			mcast_src_list_free(&report_node_p->gssq_src_list);
			if ((report_node_p->query_tic == 0) || (report_node_p->query_tic > MCAST_TIC_CAL(query->max_resp_time)))
			{
				report_node_p->query_tic = mcast_random(MCAST_TIC_CAL(query->max_resp_time));
				igmp_dbg("grp: %s, query_tic: %d\n", ip_format_get(report_node_p->grp, buf), report_node_p->query_tic);
			}
		}
		else
		{
			report_node_p = (mc_delay_report_node_t*)mcast_alloc(sizeof(mc_delay_report_node_t));
			if (report_node_p == NULL)
				MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_NORES, TRUE);

			memset(report_node_p, 0x00, sizeof(mc_delay_report_node_t));
			report_node_p->grp = query->grp;
			report_node_p->vid = 0;
			mcast_list_init(&(report_node_p->record_list), __mcast_host_record_cmp);
			report_node_p->query_tic = mcast_random(MCAST_TIC_CAL(query->max_resp_time));
			mcast_list_init(&(report_node_p->gssq_src_list), mcast_utl_src_cmp);
			if (__mcast_host_delay_report_insert(report_node_p) == FALSE)
			{
				mcast_free(report_node_p);
				MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_UNKNOW, TRUE);
			}
		}
	}

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return MCAST_RET_OK;
}

mcast_ret_code mcast_host_proc_grp_src_spec_query(IN mcast_pkt_igmp_query_t *query)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	mcast_grp_t *grp_node_p;
	mc_delay_report_node_t *report_node_p = NULL;
	bc_char buf[20] = {'0'};
	
	mcast_list_t new_list;
	mcast_list_t minus_list;
	mcast_list_t union_list;

	if ((gen_query_tic != 0) && (query->max_resp_time > gen_query_tic))
		return MCAST_RET_OK;	/* current exist gen query and the resp timer less */

	/* follow protocol rfc3376 5.2 page22 "4.If there already is a ..." */
	if (query->num_of_src == 0)
		return mcast_host_proc_grp_spec_query(query);

	grp_node_p = mcast_rt_node_get(query->grp);
	if (grp_node_p)
	{
		report_node_p = __mcast_host_delay_report_get(query->grp, 0);
		if (report_node_p)
		{
			/* if src list equal 0, we consider it's a group specific query or gen query */
			if ((report_node_p->query_tic != 0) && mcast_list_count(&report_node_p->gssq_src_list) == 0)
			{
				if ((report_node_p->query_tic == 0) || (report_node_p->query_tic > MCAST_TIC_CAL(query->max_resp_time)))
				{
					report_node_p->query_tic = mcast_random(MCAST_TIC_CAL(query->max_resp_time));
					igmp_dbg("grp: %s, query_tic: %d\n", ip_format_get(report_node_p->grp, buf), report_node_p->query_tic);
				}
				return MCAST_RET_OK;	
			}

			mcast_list_init(&new_list, mcast_utl_src_cmp);
			if (mcast_src_list_alloc(query->num_of_src, query->src, &new_list) == FALSE)
				MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_NORES, TRUE);

			mcast_list_init(&minus_list, mcast_utl_src_cmp);
			mcast_src_list_minus(&new_list, &report_node_p->gssq_src_list, &minus_list);
			//mcast_free(&minus_list);
			
			mcast_list_init(&union_list, mcast_utl_src_cmp);
			mcast_src_list_union(&new_list, &report_node_p->gssq_src_list, &union_list);
			mcast_src_list_move(&report_node_p->gssq_src_list, &union_list);

			if ((report_node_p->query_tic == 0) || (report_node_p->query_tic > MCAST_TIC_CAL(query->max_resp_time)))
			{
				report_node_p->query_tic = mcast_random(MCAST_TIC_CAL(query->max_resp_time));
				igmp_dbg("grp: %s, query_tic: %d\n", ip_format_get(report_node_p->grp, buf), report_node_p->query_tic);
			}
		}
		else
		{
			report_node_p = (mc_delay_report_node_t*)mcast_alloc(sizeof(mc_delay_report_node_t));
			if (report_node_p == NULL)
				MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_NORES, TRUE);

			memset(report_node_p, 0x00, sizeof(mc_delay_report_node_t));
			report_node_p->grp = query->grp;
			report_node_p->vid = 0;
			mcast_list_init(&(report_node_p->record_list), __mcast_host_record_cmp);
			report_node_p->query_tic = mcast_random(MCAST_TIC_CAL(query->max_resp_time));
			mcast_list_init(&(report_node_p->gssq_src_list), mcast_utl_src_cmp);
			if (mcast_src_list_alloc(query->num_of_src, query->src, &report_node_p->gssq_src_list) == FALSE)
			{
				mcast_free(report_node_p);
				MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_NORES, TRUE);
			}

			if (__mcast_host_delay_report_insert(report_node_p) == FALSE)
			{
				mcast_free(report_node_p);
				MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_UNKNOW, TRUE);
			}
		}
	}

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
	
	return MCAST_RET_OK;
}

#endif
#endif
#if 1

mcast_ret_code mcast_host_mgt_del_grp(IN bc_ip grp, IN bc_uint16 vid)
{
	mcast_host_grp_t new_host_node;
	mcast_host_grp_t *old_host_node_p = NULL;
	bc_boolean old_host_node_alloc = FALSE;
	
	mcast_list_t record_list;

	mc_delay_report_node_t *report_node_p = NULL;
	bc_boolean new_delay_report_node = FALSE;

	mcast_ret_code ret = MCAST_RET_OK;

	memset(&new_host_node, 0x00, sizeof(mcast_host_grp_t));
	new_host_node.grp = grp;
	new_host_node.vid = vid;
	new_host_node.type = MCAST_PBC_RECORD_IS_INCLUDE;
	mcast_list_init(&(new_host_node.src_list), mcast_utl_src_cmp);

	old_host_node_p = __mcast_host_proc_prev_node_init(grp, &old_host_node_alloc);
	if (old_host_node_p == NULL)
		MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_NORES, TRUE);
	
	mcast_list_init(&record_list, NULL);
	ret = __mcast_host_proc_record(old_host_node_p, &new_host_node, &record_list);
	
	if (old_host_node_alloc == FALSE)
		old_host_node_p = __mcast_host_node_delete(grp);
	
	if (old_host_node_p)
		mcast_free(old_host_node_p);

	if (ret != MCAST_RET_OK)
	{
		__mcast_host_record_clear(&record_list);
		return ret;
	}

	if (mcast_list_count(&record_list) == 0)	/* The state no change */
		return MCAST_RET_OK;
	
	report_node_p = __mcast_host_proc_delay_report_get(grp, vid, TRUE, &new_delay_report_node);
	if (report_node_p == NULL)
		MCAST_RET_ERR(MCAST_MODULE_HOST, MCAST_RET_ERR_NORES, TRUE);
	
	ret = __mcast_host_delay_report_merge_records(report_node_p, &record_list);
	if (ret != MCAST_RET_OK)
	{
		if (new_delay_report_node)
			mcast_free(report_node_p);
		return ret;
	}
	
	__mcast_host_record_clear(&record_list);
	return MCAST_RET_OK;
}


mcast_ret_code mcast_host_node_clear(void)
{
	mcast_host_grp_t *grp_node_p = NULL;

	while ((grp_node_p = __mcast_host_node_get_next(NULL)) != NULL)
	{
		mcast_host_mgt_del_grp(grp_node_p->grp, grp_node_p->vid);
	}

	return MCAST_RET_OK;
}


#endif
#if 1

typedef struct {
	bc_uint32				v1_tic;
	bc_uint32				v2_tic;
	mcast_igmp_version_e	host_ver;
} mcast_host_ver_t;

static mcast_host_ver_t mcast_host_ver;
extern bc_sem_t * mcast_sem;
bc_boolean mcast_host_ver_set(IN mcast_igmp_version_e ver)
{
	if (ver < mcast_host_ver.host_ver)
	{
		mcast_host_ver.host_ver = ver;
	}
	
	return TRUE;
}

mcast_igmp_version_e mcast_host_ver_get(void)
{
	return mcast_host_ver.host_ver;
}

/*
7.2.1. In the Presence of Older Version Queriers

In order to be compatible with older version routers, IGMPv3 hosts
MUST operate in version 1 and version 2 compatibility modes.
.........

This variable is kept per interface and is dependent on the version 
of General Queries heard on that interface as well as the Older 
Version Querier Present timers for the interface.
.........

In order to switch gracefully between versions of IGMP, hosts keep
both an IGMPv1 Querier Present timer and an IGMPv2 Querier Present
timer per interface. IGMPv1 Querier Present is set to Older Version
Querier Present Timeout seconds whenever an IGMPv1 Membership Query
is received. IGMPv2 Querier Present is set to Older Version Querier
Present Timeout seconds whenever an IGMPv2 General Query is received.

Host Compatibility Mode Timer State
----------------------- -----------
IGMPv3 (default) 		IGMPv2 Querier Present not running  and IGMPv1 
							Querier Present not running
IGMPv2 					IGMPv2 Querier Present running and IGMPv1 Querier 
							Present not running
IGMPv1 					IGMPv1 Querier Present running

*/
void mcast_host_ver_update_tic(IN mcast_igmp_version_e ver)
{
	mcast_cfg_t mcast_cfg;

	mcast_cfg_get(&mcast_cfg);

	if (ver == MCAST_IGMP_V1)
	{
		mcast_host_ver.v1_tic = MCAST_TIC_CAL(mcast_cfg.older_ver_querier_present_timeout);
		mcast_host_ver.host_ver = MCAST_IGMP_V1;
	}
	else if (ver == MCAST_IGMP_V2)
	{
		mcast_host_ver.v2_tic = MCAST_TIC_CAL(mcast_cfg.older_ver_querier_present_timeout);
		if (mcast_host_ver.v1_tic == 0)
			mcast_host_ver.host_ver = MCAST_IGMP_V2;
	}
	else
	{
		/* do nothing */
	}
}


bc_boolean mcast_host_ver_reset(void)
{
	mcast_cfg_t mcast_cfg;

	mcast_cfg_get(&mcast_cfg);

	mcast_host_ver.host_ver = mcast_cfg.igmp_version;
	mcast_host_ver.v1_tic = 0;
	mcast_host_ver.v2_tic = 0;

	return TRUE;
}

//递减mcast_host_ver中的TIC, 并给HOST端版本赋值，mcast_host_ver.host_ver
void mcast_host_ver_tic(void)
{
	mcast_igmp_version_e ver = MCAST_IGMP_V3;
	mcast_cfg_t mcast_cfg;

	memset(&mcast_cfg, 0x00, sizeof(mcast_cfg_t));
	mcast_cfg_get(&mcast_cfg);

	if (mcast_host_ver.v2_tic != 0)
	{
		mcast_host_ver.v2_tic--;
		if (mcast_host_ver.v2_tic != 0)
			ver = MCAST_IGMP_V2;
	}

	if (mcast_host_ver.v1_tic != 0)
	{	
		mcast_host_ver.v1_tic--;
		if (mcast_host_ver.v1_tic != 0)
			ver = MCAST_IGMP_V1;
	}

	if (mcast_host_ver.host_ver != ver)
		mcast_host_ver.host_ver = ver;

	if (mcast_cfg.igmp_version < mcast_host_ver.host_ver)
		mcast_host_ver.host_ver = mcast_cfg.igmp_version;
}

#endif
#if 1


void mcast_host_dyn_router_port_proc(IN bc_port_index_t rx_query_port)
{
	mcast_up_port_node_t up_port;
	mcast_cfg_t mcast_cfg;

	mcast_cfg_get(&mcast_cfg);
	mcast_port_get_up_port(rx_query_port, &up_port);

	if (up_port.router_port == MCAST_NONE_ROUTER_PORT ||
		up_port.router_port == MCAST_DYNAMIC_ROUTER_PORT)
	{
		mcast_port_update_up_rt_port(rx_query_port, MCAST_DYNAMIC_ROUTER_PORT, mcast_cfg.member_interval);
	}
}


void mcast_host_dyn_router_port_clear(void)
{
	bc_int32 i;
	mcast_up_port_node_t up_ports[BC_PORT_SNI_MAX_COUNT];

	mcast_port_get_up_ports(up_ports);
	for (i = 0; i < BC_PORT_SNI_MAX_COUNT; i++)
	{
		if (up_ports[i].en == FALSE)
			continue;

		if (up_ports[i].router_port != MCAST_DYNAMIC_ROUTER_PORT)
			continue;
		
		up_ports[i].dyn_tic = 0;
		up_ports[i].router_port = MCAST_NONE_ROUTER_PORT;
	}
	mcast_port_update_up_ports(up_ports);
}

void mcast_host_dyn_router_port_tic(void)
{
	bc_int32 i = 0;
	mcast_up_port_node_t up_ports[BC_PORT_SNI_MAX_COUNT];

	memset(up_ports, 0x00, sizeof(mcast_up_port_node_t)*BC_PORT_SNI_MAX_COUNT);
	mcast_port_get_up_ports(up_ports);
	for (i = 0; i < BC_PORT_SNI_MAX_COUNT; i++)
	{
		if (up_ports[i].en == FALSE)
			continue;

		if (up_ports[i].router_port != MCAST_DYNAMIC_ROUTER_PORT)
			continue;

		if (up_ports[i].dyn_tic > 0)
			up_ports[i].dyn_tic--;

		if (up_ports[i].dyn_tic <= 0)
		{
			up_ports[i].dyn_tic = 0;
			up_ports[i].router_port = MCAST_NONE_ROUTER_PORT;
		}
	}
	mcast_port_update_up_ports(up_ports);
}


#endif
#if 1


/* The API can't be used except debug */
void mcast_host_tree_dump(void)
{
	mcast_host_grp_t **host_p;
	mcast_host_src_t *src_node_p;
	bc_uint16 src_new_line = 0;
	
	bc_uint16 cnt = 0;

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

	MCAST_DBG_PRT("\t--------------- HOST TREE ---------------");

	MCAST_DBG_PRT("\n\t%-16s%-5s%-11s%-20s", "GRP", "VID", "RecordType", "Src List");
	MCAST_DBG_PRT("\n\t%-16s%-5s%-11s%-20s", "---------------", "----", "----------", "-------------------");

	cnt = 0;
	host_p = (mcast_host_grp_t**)mcast_avltree_get_next(mcast_host_tree, NULL);
	while (host_p && *host_p)
	{
		MCAST_DBG_PRT("\n\t");
	
		memset(buf, 0x00, 20);
		ip = (bc_uint8*)&(*host_p)->grp;
		MCAST_DBG_SPRT_IP(buf, 20, ip);
		MCAST_DBG_PRT("%-16s", buf);

		MCAST_DBG_PRT("%-5d", (*host_p)->vid);
		MCAST_DBG_PRT("%-11s", record_type_str[(*host_p)->type-1]);

		src_new_line = 0;
		src_node_p = (mcast_host_src_t*)mcast_list_first(&(*host_p)->src_list);
		while (src_node_p)
		{
			if (src_new_line % 2 == 0)
				MCAST_DBG_PRT("\n\t%-32s", " ");

			memset(buf, 0x00, 20);
			ip = (bc_uint8*)&src_node_p->src;
			MCAST_DBG_SPRT_IP(buf, 20, ip);
			MCAST_DBG_PRT("%-16s", buf);

			src_new_line++;
		
			src_node_p = (mcast_host_src_t*)mcast_list_next(src_node_p);
		}

		cnt++;
		
		host_p = (mcast_host_grp_t**)mcast_avltree_get_next(mcast_host_tree, (void**)host_p);
	}

	MCAST_DBG_PRT("\n\tTotal Cnt: %d\n", cnt);
}


/* The API can't be used except debug */
void mcast_host_query_dump(void)
{
	MCAST_DBG_PRT("\t--------------- Query Tic ---------------");
	MCAST_DBG_PRT("\n\tMcast Query Tic %d", gen_query_tic);
	MCAST_DBG_PRT("\n");
}


/* The API can't be used except debug */
void mcast_host_delay_report_dump(void)
{
	mc_delay_report_node_t **delay_node_p;

	mc_delay_src_node_t *gssq_node_p;
	
	mc_delay_record_node_t *record_node_p;
	mc_delay_src_node_t *record_src_node_p;
	
	bc_uint16 gssq_src_cnt;
	bc_uint16 record_src_cnt;
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

	MCAST_DBG_PRT("\t--------------- Delay Report ---------------");

	cnt = 0;
	delay_node_p = (mc_delay_report_node_t**)mcast_avltree_get_next(mcast_delay_report_tree, NULL);
	while (delay_node_p && *delay_node_p)
	{
		memset(buf, 0x00, 20);
		ip = (bc_uint8*)&(*delay_node_p)->grp;
		MCAST_DBG_SPRT_IP(buf, 20, ip);
	
		MCAST_DBG_PRT("\n\tGrp:%-16s Vid:%-5d Query Tic:%-5d Record Cnt:%d", buf, (*delay_node_p)->vid, 
								(*delay_node_p)->query_tic, mcast_list_count(&(*delay_node_p)->record_list));

		if (mcast_list_count(&(*delay_node_p)->gssq_src_list) != 0)
		{
			MCAST_DBG_PRT("\n\t  GSSQ SRC LIST:");
			gssq_src_cnt = 0;
			gssq_node_p = (mc_delay_src_node_t*)mcast_list_first(&(*delay_node_p)->gssq_src_list);
			while (gssq_node_p)
			{
				if (gssq_src_cnt % 4 == 0)
					MCAST_DBG_PRT("\n\t  ");

				memset(buf, 0x00, 20);
				ip = (bc_uint8*)&(gssq_node_p->src);
				MCAST_DBG_SPRT_IP(buf, 20, ip);
				MCAST_DBG_PRT("%-16s", buf);
			
				gssq_src_cnt++;
				gssq_node_p = (mc_delay_src_node_t*)mcast_list_next(gssq_node_p);
			}
		}

		if (mcast_list_count(&(*delay_node_p)->record_list) != 0)
		{
			MCAST_DBG_PRT("\n\t  RECORD LIST:");
			record_node_p = (mc_delay_record_node_t*)mcast_list_first(&(*delay_node_p)->record_list);
			while (record_node_p)
			{
				MCAST_DBG_PRT("\n\t  Mode:%-6s Tic:%-5d Robustness:%-3d MAX Resp Time:%-4d", 
										record_type_str[record_node_p->type-1], record_node_p->tic, 
										record_node_p->robustness, record_node_p->max_resp_time);

				record_src_cnt = 0;
				record_src_node_p = (mc_delay_src_node_t*)mcast_list_first(&record_node_p->src_list);
				while (record_src_node_p)
				{
					if (record_src_cnt % 4 == 0)
						MCAST_DBG_PRT("\n\t  ");

					memset(buf, 0x00, 20);
					ip = (bc_uint8*)&(record_src_node_p->src);
					MCAST_DBG_SPRT_IP(buf, 20, ip);
					MCAST_DBG_PRT("%-16s", buf);
				
					gssq_src_cnt++;
					record_src_node_p = (mc_delay_src_node_t*)mcast_list_next(record_src_node_p);
				}

				record_node_p = (mc_delay_record_node_t*)mcast_list_next(record_node_p);
			}
		}

		cnt++;
		delay_node_p = (mc_delay_report_node_t**)mcast_avltree_get_next(mcast_delay_report_tree, (void**)delay_node_p);
	}

	MCAST_DBG_PRT("\n\tTotal Cnt: %d\n", cnt);
}


/* The API can't be used except debug */
void mcast_host_ver_dump(void)
{
	char *ver_str[] = {
		"V1",
		"V2",
		"V3"
	};

	MCAST_DBG_PRT("\t--------------- Host Version ---------------");
	MCAST_DBG_PRT("\n\tMcast Ver V1 Tic %d", mcast_host_ver.v1_tic);
	MCAST_DBG_PRT("\n\tMcast Ver V2 Tic %d", mcast_host_ver.v2_tic);
	MCAST_DBG_PRT("\n\tMcast Host Current Ver %s", ver_str[mcast_host_ver.host_ver-1]);
	MCAST_DBG_PRT("\n");
}


void mcast_host_init(void)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	mcast_host_tree = mcast_avltree_create(__mcast_host_node_cmp, NULL);
	if (mcast_host_tree == NULL)
	{
		/* log it */
	}

	mcast_delay_report_tree = mcast_avltree_create(__mcast_host_delay_report_cmp, NULL);
	if (mcast_delay_report_tree == NULL)
	{
		/* log it */
	}
	//utili_block_ext_init(&mcast_host_src_block, BC_MODULE_IGMP, "MCAST_HOST_SRC", sizeof(mcast_host_src_t), 1024);
	//utili_block_ext_init(&mcast_host_grp_block, BC_MODULE_IGMP, "MCAST_HOST_GRP", sizeof(mcast_host_grp_t), 1024);
	mcast_host_ver.v1_tic = 0;
	mcast_host_ver.v2_tic = 0;
	mcast_host_ver.host_ver = MCAST_IGMP_V3;

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
}


#endif
#endif

