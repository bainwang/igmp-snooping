/*******************************************************************************
  [File name]	: mcast_cfg_grp.c
  [Author]     	: bain.wang@outlook.com
  [Version]    	: 1.0
  [Date]       	: 2017-06-13
  [Description]	:
	Multicast module configure group
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

#include "mcast_cfg_grp.h"

#if BC_MULTICAST_INCLUDE

typedef struct {
	bc_boolean valid;
	mcast_cfg_grp_t info;
} mcast_cfg_grp_local_t;

static mcast_cfg_grp_local_t cfg_grp_db[MCAST_CFG_GRP_MAX];

static mcast_avltree_t *mcast_cfg_grp_tree;

#if 1

static bc_int32 __mcast_cfg_grp_cmp(const void *f, const void *s, void *param)
{
	mcast_cfg_grp_t *a;
	mcast_cfg_grp_t *b;

	a = (mcast_cfg_grp_t*)f;
	b = (mcast_cfg_grp_t*)s;

	/* why i don't check src ip and vid ?
		1. src ip: the spec doc don't clearly describe;
		2. vid: grp is a uniquely key, don't use vid can 
		enhace tx performance, and tx will use grp find vid
	*/

	if (a->grp > b->grp)
		return 1;
	else if (a->grp < b->grp)
		return -1;
	else
		return 0;
}

static bc_boolean __mcast_cfg_grp_tree_insert(IN mcast_cfg_grp_t *cfg_grp_node)
{
	cfg_grp_node = mcast_avltree_insert(mcast_cfg_grp_tree, cfg_grp_node);
	return (cfg_grp_node) ? FALSE : TRUE;
}

static bc_boolean __mcast_cfg_grp_tree_delete(IN bc_ip grp)
{
	mcast_cfg_grp_t delete_node;

	memset(&delete_node, 0x00, sizeof(mcast_cfg_grp_t));
	delete_node.grp = grp;
	return mcast_avltree_delete(mcast_cfg_grp_tree, &delete_node) ? TRUE : FALSE;
}

static mcast_cfg_grp_t* __mcast_cfg_grp_tree_find(IN bc_ip grp)
{
	mcast_cfg_grp_t find_node;
	mcast_cfg_grp_t **tree_node;

	memset(&find_node, 0x00, sizeof(mcast_cfg_grp_t));
	find_node.grp = grp;
	tree_node = (mcast_cfg_grp_t **)mcast_avltree_find(mcast_cfg_grp_tree, &find_node);
	if (tree_node == NULL || *tree_node == NULL)
		return NULL;

	return *tree_node;
}

bc_boolean mcast_cfg_grp_search_by_ip(IN bc_ip grp, IN bc_uint16 vid, OUT mcast_cfg_grp_t *cfg_grp)
{
	mcast_cfg_grp_t find_node;
	mcast_cfg_grp_t **tree_node;

	memset(&find_node, 0x00, sizeof(mcast_cfg_grp_t));
	find_node.grp = grp;
	find_node.vid = vid;
	tree_node = (mcast_cfg_grp_t **)mcast_avltree_find(mcast_cfg_grp_tree, &find_node);
	if (tree_node == NULL || *tree_node == NULL)
		return FALSE;

	memcpy(cfg_grp, *tree_node, sizeof(mcast_cfg_grp_t));
	return TRUE;
}

#endif
#if 1


bc_boolean mcast_cfg_grp_get_vid_by_grp(IN bc_ip grp, OUT bc_uint16 *vid)
{
	mcast_cfg_grp_t *node_p = NULL;
	bc_char ip[20] = {'0'};
	
	node_p = __mcast_cfg_grp_tree_find(grp);
	if (node_p == NULL)
	{
		igmp_dbg("not found grp %s!\n", ip_format_get(grp, ip));
		return FALSE;
	}

	*vid = node_p->vid;
	return TRUE;
}

bc_boolean mcast_cfg_grp_cfg_exist(IN bc_ip grp, IN bc_uint16 vid)
{
	mcast_cfg_grp_t *node_p = NULL;

	node_p = __mcast_cfg_grp_tree_find(grp);
	if (node_p == NULL)
		return FALSE;

	return (vid == node_p->vid) ? TRUE : FALSE;
}

bc_boolean mcast_cfg_grp_vid_used(IN bc_uint16 mc_vid, IN bc_uint16 except_check_idx)
{
	bc_uint16 idx;

	for (idx = 0 ; idx < MCAST_CFG_GRP_MAX; idx++)
	{
		if (except_check_idx != 0 && idx == except_check_idx-1)
			continue;

		if (cfg_grp_db[idx].info.vid == mc_vid)
			return TRUE;
	}

	return FALSE;
}

bc_boolean mcast_cfg_grp_conflict(
	IN bc_uint16 mc_vid, 
	IN bc_ip mc_ip, 
	IN bc_uint16 except_check_idx)
{
	bc_uint16 idx;

	for (idx = 0 ; idx < MCAST_CFG_GRP_MAX; idx++)
	{
		if (except_check_idx != 0 && idx == except_check_idx-1)
			continue;

		if (cfg_grp_db[idx].info.grp == mc_ip)
			return TRUE;
	}

	return FALSE;
}

bc_boolean mcast_cfg_grp_add(IN mcast_cfg_grp_t *cfg_grp_node)
{
    bc_char ip[20] = {0};
	if (__mcast_cfg_grp_tree_find(cfg_grp_node->grp) != NULL)
		return FALSE; /* exist */

	if (cfg_grp_db[cfg_grp_node->idx-1].valid == TRUE)
		return FALSE;

	cfg_grp_db[cfg_grp_node->idx-1].valid = TRUE;
	memcpy(&cfg_grp_db[cfg_grp_node->idx-1].info, cfg_grp_node, sizeof(mcast_cfg_grp_t));
	__mcast_cfg_grp_tree_insert(&cfg_grp_db[cfg_grp_node->idx-1].info);

    igmp_dbg("add cfg idx %d, grp: %s\n", cfg_grp_node->idx, ip_format_get(cfg_grp_node->grp, ip));

	return TRUE;
}

bc_boolean mcast_cfg_grp_update(IN mcast_cfg_grp_t *cfg_grp_node)
{
	if (__mcast_cfg_grp_tree_find(cfg_grp_node->grp) == NULL)
		return FALSE; /* not exist */

	if (cfg_grp_db[cfg_grp_node->idx-1].valid == FALSE)
		return FALSE;

	cfg_grp_db[cfg_grp_node->idx-1].valid = TRUE;
	memcpy(&cfg_grp_db[cfg_grp_node->idx-1].info, cfg_grp_node, sizeof(mcast_cfg_grp_t));
	return TRUE;
}

bc_boolean mcast_cfg_grp_del(IN bc_uint32 index)
{
	if (cfg_grp_db[index-1].valid == FALSE)
		return FALSE;

	__mcast_cfg_grp_tree_delete(cfg_grp_db[index-1].info.grp);
	cfg_grp_db[index-1].valid = FALSE;
	memset(&cfg_grp_db[index-1].info, 0x00, sizeof(mcast_cfg_grp_t));
	return TRUE;
}


bc_boolean mcast_cfg_grp_get_by_index(IN bc_uint32 index, OUT mcast_cfg_grp_t*cfg_grp_node)
{
	if (cfg_grp_db[index-1].valid == FALSE)
		return FALSE;

	memcpy(cfg_grp_node, &(cfg_grp_db[index-1].info), sizeof(mcast_cfg_grp_t));
	return TRUE;
}

#endif
#if 1


/* The API can't be used except debug */
void mcast_cfg_grp_db_dbg_dump(void)
{
	bc_uint16 idx;

	bc_uint8 *ip;
	char buf[20] = {0};

	bc_uint8 cnt = 0;
	
	MCAST_DBG_PRT("\t--------------- CFG GRP DB ---------------");

	MCAST_DBG_PRT("\n\t%-5s%-5s%-16s%-16s%-12s%-12s", "Idx", "Vid", "Grp", "Src", "ABW", "MaxABW" );
	MCAST_DBG_PRT("\n\t%-5s%-5s%-16s%-16s%-12s%-12s", "----", "----", "---------------", "---------------", 
				"-----------", "-----------");

	cnt = 0;
	for (idx = 0; idx < MCAST_CFG_GRP_MAX; idx++)
	{
		if (cfg_grp_db[idx].valid == FALSE)
			continue;
	
		MCAST_DBG_PRT("\n\t");

		MCAST_DBG_PRT("%-5d", idx);
		MCAST_DBG_PRT("%-5d", cfg_grp_db[idx].info.vid);

		memset(buf, 0x00, 20);
		ip = (bc_uint8*)&(cfg_grp_db[idx].info.grp);
		MCAST_DBG_SPRT_IP(buf, 20, ip);
		MCAST_DBG_PRT("%-16s", buf);

		memset(buf, 0x00, 20);
		ip = (bc_uint8*)&(cfg_grp_db[idx].info.src);
		MCAST_DBG_SPRT_IP(buf, 20, ip);
		MCAST_DBG_PRT("%-16s", buf);
		 
		MCAST_DBG_PRT("%-12d", cfg_grp_db[idx].info.abw);
		MCAST_DBG_PRT("%-12d", cfg_grp_db[idx].info.max_bw); 

		cnt++;
	}

	MCAST_DBG_PRT("\n\tTotal Cnt: %d", cnt);
	MCAST_DBG_PRT("\n");
}


/* The API can't be used except debug */
void mcast_cfg_grp_tree_dbg_dump(void)
{
	mcast_cfg_grp_t **cfg_grp_p;

	bc_uint8 *ip;
	char buf[20] = {0};

	bc_uint16 cnt = 0;
	
	MCAST_DBG_PRT("\t--------------- CFG GRP TREE ---------------");

	MCAST_DBG_PRT("\n\t%-5s%-16s%-16s%-12s%-12s", "Vid", "Grp", "Src", "ABW", "MaxABW");
	MCAST_DBG_PRT("\n\t%-5s%-16s%-16s%-12s%-12s", "----", "---------------", "---------------", 
				"-----------", "-----------");

	cnt = 0;
	cfg_grp_p = (mcast_cfg_grp_t**)mcast_avltree_get_next(mcast_cfg_grp_tree, NULL);
	while (cfg_grp_p != NULL && *cfg_grp_p != NULL)
	{
		MCAST_DBG_PRT("\n\t");

		MCAST_DBG_PRT("%-5d", (*cfg_grp_p)->vid);

		memset(buf, 0x00, 20);
		ip = (bc_uint8*)&((*cfg_grp_p)->grp);
		MCAST_DBG_SPRT_IP(buf, 20, ip);
		MCAST_DBG_PRT("%-16s", buf);

		memset(buf, 0x00, 20);
		ip = (bc_uint8*)&((*cfg_grp_p)->src);
		MCAST_DBG_SPRT_IP(buf, 20, ip);
		MCAST_DBG_PRT("%-16s", buf);
		
		MCAST_DBG_PRT("%-12d", (*cfg_grp_p)->abw);
		MCAST_DBG_PRT("%-12d", (*cfg_grp_p)->max_bw);

		cnt++;

		cfg_grp_p = (mcast_cfg_grp_t**)mcast_avltree_get_next(mcast_cfg_grp_tree, (void**)cfg_grp_p);
	}
	
	MCAST_DBG_PRT("\n\tTotal Cnt: %d", cnt);
	MCAST_DBG_PRT("\n");
}


void mcast_cfg_grp_init(void)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP);
	
	memset(cfg_grp_db, 0x00, sizeof(mcast_cfg_grp_local_t)*MCAST_CFG_GRP_MAX);
	
	mcast_cfg_grp_tree = mcast_avltree_create(__mcast_cfg_grp_cmp, NULL);
	if (mcast_cfg_grp_tree == NULL)
	{
		/* log it */
	}

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP);
}

#endif
#endif

