/*******************************************************************************
  
  [File name]  : drv_53724_mcast.c
  [Author]     : yangl
  [Version]    : 1.0
  [Date]       : 2013-04-04
  [Description]:

  [Others]     :

  [Function List]:  
    1. ....
    2. ....
  [History]:
	 D a t e    Modification 										  Initials
	---------- --------------                                        ----------
	2013-04-04  Created												  yangl
*******************************************************************************/

#include "mcast_def.h"



#include "drv_chipname_mcast.h"
#include "drv_mcast.h"
#include "utili_avlt.h"
#include "bc_platform_mem.h"
#include "bc_print.h"

#include "utili_block_ext.h"


#if 1

typedef struct
{

	bc_ip 		grp;
	bc_uint16	vid;
	bc_int32	index;
	bc_uint8	grp_fwd_msk[(BC_PORT_PON_MAX_COUNT + BC_PORT_PON_MAX_COUNT + 7) / 8];

	bc_int32	src_num;
	drv_mcast_src_node_t  src_list[DRV_MCAST_SRC_MAX];
} bc_mcast_node_t;

static utili_avlt_tree_t * drv_mcast_tree = NULL;
static utili_block_ext_t		drv_mcast_block;

/******************************************************************************\
  Function   : bitOpSetBits
  Description: 设置一段内存的值
  parameter  : 
               pa - 原始bit流
               pb - 开始位
               pc - 结束位
               pd - 设置值，不为0时，填写为1，为0时填写为0
  Return     : TRUE  成功  FALSE 失败
  Others     : 
\******************************************************************************/
static char bitOpSetBits(bc_uint8 *abyData, bc_uint32 dwStartBit, bc_uint32 dwEndBit, bc_uint8 byVal)
{	
	if (dwEndBit < dwStartBit)
	{
		return FALSE;
	}

	
	while (dwStartBit <= dwEndBit)
	{
		if (byVal)
		{
			abyData[dwStartBit / 8] |= 1 << (dwStartBit % 8);
		}
		else
		{
			abyData[dwStartBit/8] &= ~(1 << (dwStartBit % 8));
		}
		
		dwStartBit++;
	}
	
	return TRUE;
}

/******************************************************************************\
  Function   : bitOpCheck
  Description: 检测一段内存内某特定位置的值
  parameter  : 
               pa - 原始bit流
               pb - 测试位
  Return     : TRUE  该位被置位  FALSE 未置位
  Others     : 
\******************************************************************************/
static char bitOpCheck(bc_uint8 *pbySrc, bc_int32 dwBit)
{
	if (pbySrc[dwBit / 8] & (1 << (dwBit % 8)))
	{
		return TRUE;
	}
	
	return FALSE;
}
static bc_int32 drv_mcast_tree_cmp(const void * f, const void * s, void * param)
{
	bc_mcast_node_t * a;
	bc_mcast_node_t * b;

	a = (bc_mcast_node_t *)f;
	b = (bc_mcast_node_t *)s;

	if (a->grp > b->grp)
	{
		return 1;
	}
	else if (a->grp < b->grp)
	{
		return -1;
	}
	else
	{
		if (a->vid > b->vid)
		{
			return 1;
		}
		else if (a->vid < b->vid)
		{
			return -1;
		}
		else
		{
			return 0;
		}
	}
}

static bc_mcast_node_t * drv_mcast_tree_find(IN bc_mcast_node_t * find_node_p)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP_DRV);
	
	bc_mcast_node_t ** tree_node = NULL;

	if(!drv_mcast_tree)
	{
		BC_PT_DBG_FUN(BC_MODULE_IGMP_DRV, "drv_mcast_tree is NULL!!!\n");
	}
	
	tree_node = (bc_mcast_node_t **)utili_avlt_find(drv_mcast_tree, find_node_p);
	if (tree_node == NULL || *tree_node == NULL)
	{
		BC_PT_DBG_FUN(BC_MODULE_IGMP_DRV, "find tree_node from drv_mcast_tree failure.\n");
		return NULL;
	}
	else
	{
		return *tree_node;
	}

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP_DRV);
}

static bc_boolean drv_mcast_tree_add(IN bc_mcast_node_t * add_node_p)
{
	return utili_avlt_insert(drv_mcast_tree, add_node_p) ? FALSE : TRUE;
}

static bc_mcast_node_t * drv_mcast_tree_del(IN bc_mcast_node_t * del_node_p)
{
	return utili_avlt_delete(drv_mcast_tree, del_node_p);
}

static bc_mcast_node_t* drv_mcast_tree_get_next(IN bc_mcast_node_t * node_p)
{
	bc_mcast_node_t **search_node;
	bc_mcast_node_t **tree_node;

	if (node_p != NULL)
	{
		search_node = (bc_mcast_node_t **)utili_avlt_find(drv_mcast_tree, (void *)node_p);
		if (search_node == NULL || *search_node == NULL)
			return NULL;
	}
	else
	{
		search_node = NULL;
	}

	tree_node = (bc_mcast_node_t **)utili_avlt_next(drv_mcast_tree, (void **)search_node);
	if (tree_node == NULL || *tree_node == NULL)
		return NULL;

	return *tree_node;
}
#endif


#if 1

static bc_err_e drv_bcmchipname_chip_pid_get(bc_uint8 port, bc_int32 * chip_pid)
{
	if (NULL == chip_pid)
	{
		return BC_ERR_PARA;
	}

	/*
		todo
	*/

	return BC_ERR_OK;
}

static bc_err_e drv_mcast_add_entry(drv_mcast_node_t * mcast_node)
{
	bc_mac mac = {0};
	bc_int32 ret;

	if (NULL == mcast_node)
	{
		return BC_ERR_PARA;
	}
	
	mcast_ip_cvrt_mac(mcast_node->grp, mac);
	
	/*
		todo
			ex: bcm_mcast_addr_add
	*/

	return BC_ERR_OK;
}

static bc_err_e drv_mcast_del_entry(bc_ip grp, bc_uint16 vid)
{
	bc_mac mac = {0};
	bc_int32 ret;
	
	mcast_ip_cvrt_mac(grp, mac);
	
	/*
		todo
			ret = bcm_mcast_addr_remove(BCMchipname_UNIT_ID, mac, (bcm_vlan_t)vid));
	*/

	return BC_ERR_OK;
}


static bc_mcast_node_t * drv_mcast_create(IN drv_mcast_node_t * fwd_node)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP_DRV);
	
	bc_mcast_node_t * new_node_p = NULL;
	bc_int32 idx;
	bc_int32 ret;
	bc_char tmp[20];
	
	BC_PT_DBG_FUN(BC_MODULE_IGMP_DRV,"grp: %s, vid: %d\n", ip_format_get(fwd_node->grp, tmp), fwd_node->vid);
	if (TRUE != mcast_utl_valid_mc_ip(fwd_node->grp))
	{
		BC_PT_DBG_FUN(BC_MODULE_IGMP_DRV,"grp:%s invalid!!!\n", ip_format_get(fwd_node->grp, tmp));
		return NULL;
	}

	if (fwd_node->vid <= 0 || fwd_node->vid > 4095)
	{
		BC_PT_DBG_FUN(BC_MODULE_IGMP_DRV,"vid:%d invalid!!!\n", fwd_node->vid);
		return NULL;
	}
	new_node_p = (bc_mcast_node_t *)utili_block_ext_alloc(&drv_mcast_block);
	if (NULL == new_node_p)
	{
		BC_PT_DBG_FUN(BC_MODULE_IGMP_DRV,"malloc new_node_p failure!!!\n", fwd_node->vid);
		return new_node_p;
	}

	memset(new_node_p, 0, sizeof(* new_node_p));
	new_node_p->grp = fwd_node->grp;
	new_node_p->vid = fwd_node->vid;
	for (idx = 0; idx < BC_PORT_PON_MAX_COUNT + BC_PORT_SNI_MAX_COUNT; idx++)
	{
		if (fwd_node->grp_fwd_list[idx] == TRUE)	/*port-idx is EX*/
		{
			bitOpSetBits(new_node_p->grp_fwd_msk, idx, idx, 1);
		}
		else /*port-idx is IN*/
		{
			bitOpSetBits(new_node_p->grp_fwd_msk, idx, idx, 0);
		}
	}

	new_node_p->src_num = fwd_node->src_num;
	memcpy(new_node_p->src_list, fwd_node->src_list, sizeof(fwd_node->src_list));
	if (BC_ERR_OK != (ret = drv_mcast_add_entry(fwd_node)))
	{
		BC_PT_DBG_FUN(BC_MODULE_IGMP_DRV,"drv_mcast_add_entry(fwd_node) failure!!!\n", fwd_node->vid);
		utili_block_ext_free(&drv_mcast_block, new_node_p);
		new_node_p = NULL;
		return NULL;
	}

	if (NULL == drv_mcast_tree)
	{
		BC_PT_DBG_FUN(BC_MODULE_IGMP_DRV,"drv_mcast_tree is NULL, creatting....\n");
		drv_mcast_tree = utili_avlt_create(drv_mcast_tree_cmp, NULL);
		if (drv_mcast_tree == NULL)
		{
			BC_PT_DBG_FUN(BC_MODULE_IGMP_DRV,"Mcast Driver Init Fail!!!\n");
		}
	}
	
	if (FALSE == drv_mcast_tree_add(new_node_p))
	{
		BC_PT_DBG_FUN(BC_MODULE_IGMP_DRV,"drv_mcast_tree_add failure\n");
		utili_block_ext_free(&drv_mcast_block, new_node_p);
		new_node_p = NULL;
		return NULL;
	}

	BC_PT_DBG_FUN(BC_MODULE_IGMP_DRV,"fwd_node => new_node, and insert to drv_mcast_tree, successful\n");
	BC_PT_FUN_LEAVE(BC_MODULE_IGMP_DRV);
	
	return new_node_p;
}

static bc_err_e drv_mcast_destroy(bc_ip grp, bc_uint16 vid)
{
	bc_int32 ret;
	bc_mac mac = {0};

	if (TRUE != mcast_utl_valid_mc_ip(grp))
	{
		return BC_ERR_PARA;
	}

	if (vid <= 0 || vid > 4095)
	{
		return BC_ERR_PARA;
	}

	drv_mcast_del_entry(grp, vid);
	
	return BC_ERR_OK;
}

static bc_err_e drv_mcast_member_add(bc_ip grp, bc_uint8 pid, bc_uint16 vid)
{
	bc_int32 ret;
	bc_mac mac = {0};
	
	bc_char tmp[20];
	bc_int32 chip_pid = 0;

	BC_PT_DBG_CPL(BC_MODULE_IGMP_DRV,"add pid: %d\n", pid);
	
	if (TRUE != mcast_utl_valid_mc_ip(grp))
	{
		return BC_ERR_PARA;
	}

	if (BC_PORT_PON_MAX_COUNT + BC_PORT_SNI_MAX_COUNT <= pid)
	{
		return BC_ERR_PARA;
	}
	
	if (vid <= 0 || vid > 4095)
	{
		return BC_ERR_PARA;
	}
	
	mcast_ip_cvrt_mac(grp, mac);

	if (BC_ERR_OK != drv_bcmchipname_chip_pid_get(pid, &chip_pid))
	{
		return BC_ERR_PARA;
	}
	
	/*
		todo
			add chipid to mac.
	*/

	return BC_ERR_OK;
}

static bc_err_e drv_mcast_member_delete(bc_ip grp, bc_uint8 pid, bc_uint16 vid)
{
	bc_int32 ret;
	bc_mac mac = {0};
	bc_char tmp[20];
	bc_int32 chip_pid = 0;
		
	if (TRUE != mcast_utl_valid_mc_ip(grp))
	{
		return BC_ERR_PARA;
	}

	if (BC_PORT_PON_MAX_COUNT + BC_PORT_SNI_MAX_COUNT <= pid)
	{
		return BC_ERR_PARA;
	}

	if (vid <= 0 || vid > 4095)
	{
		return BC_ERR_PARA;
	}

	if (BC_ERR_OK != drv_bcmchipname_chip_pid_get(pid, &chip_pid))
	{
		return BC_ERR_PARA;
	}
	
	BC_PT_DBG_CPL(BC_MODULE_IGMP_DRV,"hw pid: %d\n", chip_pid);

	mcast_ip_cvrt_mac(grp, mac);

	/*
		todo
			bcm_mcast_leave or bcm_mcast_port_remove
	*/

	return BC_ERR_OK;
}
#endif

#if 1
/******************************************************************************\
  Function   : drv_mcast_update
  Description: 更新多播条目,保持软件和硬件的同步
  parameter  : 
               pa - drv_mcast_node_t *
  Return     : 成功0，失败1
  Others     : 
\******************************************************************************/
bc_err_e drv_chipname_mcast_update(IN drv_mcast_node_t * fwd_node)
{
	BC_PT_FUN_ENTER(BC_MODULE_IGMP_DRV);
	
	bc_mcast_node_t tmp_node;
	bc_mcast_node_t * find_node_p = NULL;
	bc_uint8 pid = 0;
	bc_uint8 flag = 0;

	bc_char buf[20];

	if (NULL == fwd_node)
	{
		BC_PT_DBG_FUN(BC_MODULE_IGMP_DRV, "fwd_node is NULL!!!\n");
		return BC_ERR_DRV_ACCESS;
	}
	//printf("mcast_drv_update\n");
	memset(&tmp_node, 0, sizeof(tmp_node));
	tmp_node.grp = fwd_node->grp;
	tmp_node.vid = fwd_node->vid;

	find_node_p = drv_mcast_tree_find(&tmp_node);
	if (NULL == find_node_p)
	{
		BC_PT_DBG_FUN(BC_MODULE_IGMP_DRV, "None find[grp:%s, vid:%d] node on drv_mcast_tree\n", ip_format_get(tmp_node.grp, buf), tmp_node.vid);
		
		find_node_p = drv_mcast_create(fwd_node);
		if (NULL == find_node_p)
		{
			BC_PT_DBG_FUN(BC_MODULE_IGMP_DRV, "Create [grp:%s, vid:%d] node on drv_mcast_tree failure\n", ip_format_get(fwd_node->grp, buf), fwd_node->vid);
			return BC_ERR_DRV_ACCESS;
		}
		BC_PT_DBG_FUN(BC_MODULE_IGMP_DRV, "Create [grp:%s, vid:%d] node on drv_mcast_tree successful\n", ip_format_get(fwd_node->grp, buf), fwd_node->vid);
		
		for (pid = 0; pid < BC_PORT_PON_MAX_COUNT + BC_PORT_SNI_MAX_COUNT; pid++)
		{
			if (bitOpCheck(find_node_p->grp_fwd_msk, pid))
			{
				if (BC_ERR_OK != drv_mcast_member_add(find_node_p->grp, pid, find_node_p->vid))
				{
					BC_PT_DBG_FUN(BC_MODULE_IGMP_DRV, "drv_mcast_member_add failure\n");
					return BC_ERR_DRV_ACCESS;
				}
			}
		}
	}
	else
	{
		for (pid = 0; pid < BC_PORT_PON_MAX_COUNT + BC_PORT_SNI_MAX_COUNT; pid++)
		{
			if (bitOpCheck(find_node_p->grp_fwd_msk, pid))	/*EX*/
			{
				if (TRUE != fwd_node->grp_fwd_list[pid])/*IN*/
				{
					if (BC_ERR_OK != drv_mcast_member_delete(fwd_node->grp, pid, fwd_node->vid))
					{
						//printf("\n");
						BC_PT_DBG_FUN(BC_MODULE_IGMP_DRV, "drv_mcast_member_delete failure\n");
						return BC_ERR_DRV_ACCESS;
					}

					bitOpSetBits(find_node_p->grp_fwd_msk, pid, pid, 0);
				}
			}
			else	//
			{
				if (TRUE == fwd_node->grp_fwd_list[pid])
				{
					if (BC_ERR_OK != drv_mcast_member_add(fwd_node->grp, pid, fwd_node->vid))
					{
						//printf("\n");
						BC_PT_DBG_FUN(BC_MODULE_IGMP_DRV, "drv_mcast_member_add failure\n");
						return BC_ERR_DRV_ACCESS;
					}

					bitOpSetBits(find_node_p->grp_fwd_msk, pid, pid, 1);
				}
			}
		}
	}

	for (pid = 0; pid < BC_PORT_PON_MAX_COUNT + BC_PORT_SNI_MAX_COUNT; pid++)
	{
		if (bitOpCheck(find_node_p->grp_fwd_msk, pid))
		{
			flag = 1;
			break;
		}
	}
	if (!flag)
	{
		drv_mcast_destroy(fwd_node->grp, fwd_node->vid);
		drv_mcast_tree_del(find_node_p);
		utili_block_ext_free(&drv_mcast_block, find_node_p);
		find_node_p = NULL;
	}

	BC_PT_FUN_LEAVE(BC_MODULE_IGMP_DRV);
	
	return BC_ERR_OK;
}

/******************************************************************************\
  Function   : drv_mcast_delete
  Description: 删除一个多播组
  parameter  : 
               pa - group ip
               pb - vid
  Return     : 成功0，失败1
  Others     : 
\******************************************************************************/
bc_err_e drv_chipname_mcast_delete(IN bc_ip grp, IN bc_uint16 vid)
{
	bc_uint8 pid;
	bc_mcast_node_t tmp_node;
	bc_mcast_node_t * node_ptr = NULL;

	memset(&tmp_node, 0, sizeof(tmp_node));
	tmp_node.grp = grp;
	tmp_node.vid = vid;
	
	node_ptr = drv_mcast_tree_find(&tmp_node);
	if (NULL == node_ptr)
	{
		return BC_ERR_OK;
	}

	for (pid = 0; pid < BC_PORT_PON_MAX_COUNT + BC_PORT_SNI_MAX_COUNT; pid++)
	{
		if (bitOpCheck(node_ptr->grp_fwd_msk, pid))
		{
			if (BC_ERR_OK == drv_mcast_member_delete(node_ptr->grp, pid, node_ptr->vid))
			{
				bitOpSetBits(node_ptr->grp_fwd_msk, pid, pid, 0);
			}
		}
	}

	drv_mcast_destroy(grp, vid);
	{
		drv_mcast_tree_del(node_ptr);
		utili_block_ext_free(&drv_mcast_block, node_ptr);
		node_ptr = NULL;
		return BC_ERR_OK;
	}

	return BC_ERR_DRV_ACCESS;
}

/******************************************************************************\
  Function   : drv_mcast_clear
  Description: 清空所有多播条目
  parameter  : 
               无
  Return     : 成功0，失败1
  Others     : 
\******************************************************************************/
bc_err_e drv_chipname_mcast_clear(void)
{
	bc_mcast_node_t * node_ptr = NULL;

	/*这个if有点变态.因为driver在bcapi之后才运行,所以当driver还未初始化时bcapi调用到这里来会出错.*/
	if (NULL == drv_mcast_tree)
	{
		return BC_ERR_OK;
	}
	
	while (NULL != (node_ptr = drv_mcast_tree_get_next(NULL)))
	{
		if (BC_ERR_OK != drv_chipname_mcast_delete(node_ptr->grp, node_ptr->vid))
		{
			return BC_ERR_DRV_ACCESS;
		}
	}

	return BC_ERR_OK;
}

/******************************************************************************\
  Function   : drv_mcsat_get_next
  Description: 获得当前节点node的相邻节点
  parameter  : 
               pa - drv_mcast_node_t *,当前节点
  Return     : 成功0，失败1
  Others     : 
\******************************************************************************/
bc_err_e drv_chipname_mcsat_get_next( drv_mcast_node_t * node)
{
	bc_mcast_node_t * node_p;
	bc_mcast_node_t tmp_node;
	bc_uint8 pid;
	bc_char ip[20];
	
	if (NULL == node)
	{
		return BC_ERR_PARA;
	}
	
	memset(&tmp_node, 0, sizeof(tmp_node));
	tmp_node.grp = node->grp;
	tmp_node.vid = node->vid;

	if (NULL == drv_mcast_tree)
	{
		return BC_ERR_OK;
	}

	node_p = (node->grp == 0) ? NULL : &tmp_node;
	node_p = drv_mcast_tree_get_next(node_p);
	if (node_p == NULL)
	{
		BC_PT_DBG_CPL(BC_MODULE_IGMP_DRV,"DRV_E_NOT_FOUND\n");
		return BC_ERR_NOT_FIND;
	}

	node->grp = node_p->grp;
	node->vid = node_p->vid;
	for (pid = 0; pid < BC_PORT_PON_MAX_COUNT + BC_PORT_SNI_MAX_COUNT; pid++)
	{
		if (bitOpCheck(node_p->grp_fwd_msk, pid))
		{
			node->grp_fwd_list[pid] = TRUE;
		}
	}

	node->src_num = node_p->src_num;
	memcpy(node->src_list, node_p->src_list, sizeof(node_p->src_list));

	BC_PT_DBG_CPL(BC_MODULE_IGMP_DRV,"grp: %s, vid: %d\n", ip_format_get(node->grp, ip), node->vid);

	return BC_ERR_OK;
}

bc_err_e drv_chipname_mcast_enable(bc_uint8 flag)
{
	return BC_ERR_OK;
}

bc_err_e drv_chipname_mcast_init(void)
{
	bc_uint32 ret;
	bc_int16 i = 0;
	int val = 0;

	/*
		todo
			bcm mcast init.
	*/

	if (NULL == drv_mcast_tree)
	{
		drv_mcast_tree = utili_avlt_create(drv_mcast_tree_cmp, NULL);
		if (drv_mcast_tree == NULL)
		{
			BC_PT_DBG_CPL(BC_MODULE_IGMP_DRV,"Mcast Driver Init Fail!!!\n");
			return BC_ERR_DRV_ACCESS;
		}
	}
	utili_block_ext_init(&drv_mcast_block, BC_MODULE_IGMP_DRV, "DRV_MCAST", sizeof(bc_mcast_node_t), DRV_MCAST_NODE_MAX);
}

#endif
