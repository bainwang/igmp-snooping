
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              头   文   件                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "utili_rbt.h"
#include "bc_cli_type.h"
#include "bc_cli_misc.h"
#include "bc_cli_db.h"



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                      外 部 变 量、 函 数 引 用                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                      结   构   体   宏   定   义                           //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************
 * This DB use the red-black tree as the container of address data,
 * each node have a red-black tree node and the real data
*******************************************************************************/
typedef struct
{
	utili_rbt_node_t 		node;		/* the red-black tree node */
	CLI_CMD_NODE_T 		cli2_entry; /* the path or command */
} CLI_DB_NODE_T;

typedef struct
{
	I8_T					*name;
	UI32_T					len;
	UI32_T					type;
} db_cmp_t;



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                          全 局 变 量 定 义                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
/* the red-black tree of CLI root path */
static utili_rbt_t 			s_cli2_root_tree;



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              函  数  声  明                                //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              函  数  定  义                                //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   __cli2_db_compare
 *
 * DESCRIPTION:
 *   Red-black tree keyword compare callback function:
 *
 * INPUT:
 *   a      : the internal path/command entry pointer
 *   b      : the internal path/command entry pointer
 *   cookie : the cookie of tree
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   -1 : a->name < b_name with b_len
 *    0 : a->name == b_name with b_len
 *    1 : a->name > b_name with b_len
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *
*******************************************************************************/
static I32_T __cli2_db_compare
	(
	IN const CLI_CMD_NODE_T 	*a,
	IN const CLI_CMD_NODE_T 	*b,
	IN void 					*cookie
	)
{
	I32_T 	ret;

	if (cookie)
	{
	}

	ret = strcmp(a->name, b->name);
	return (ret == 0) ? ((I32_T)a->type - (I32_T)b->type) /* second keyword */ : ret;
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *   __cli2_db_compare_ex
 *
 * DESCRIPTION:
 *   Red-black tree keyword compare callback function:
 *     when search the node name with given length, use this function can speed up the search by reduce:
 *       1. build a entry struct
 *       2. strncpy the name with length
 *     called by these function:
 *       UTL_RBT_Find_ByKey/UTL_RBT_Find_PrevByKey/UTL_RBT_Find_NextByKey
 *       /UTL_RBT_Find_LEByKey/UTL_RBT_Find_GEByKey
 *
 * INPUT:
 *   a      : the internal path/command entry pointer
 *   b_name : the compare name that pass in by caller function
 *   b_len  : the compare name's length pass in by caller function
 *   b_type : the compare type pass in by caller function
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   -1 : a->name < b_name with b_len
 *    0 : a->name == b_name with b_len
 *    1 : a->name > b_name with b_len
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *
*******************************************************************************/
static I32_T __cli2_db_compare_ex
	(
	IN const CLI_CMD_NODE_T 	*a,
	IN const void 				*b_void
	)
{
	const I8_T 					*a_name;
	I32_T 						result;
	db_cmp_t					*b;
	I8_T 						*b_name;
	UI32_T 						b_len;
	UI32_T 						b_type;

	if (NULL == b_void)
	{
		return -1;
	}

	b = (db_cmp_t *)b_void;
	b_name = b->name;
	b_len = b->len;
	b_type = b->type;
	
	a_name = a->name;

	/* compare a_name and b_name with b_len */
	result = strncmp(a_name, b_name, b_len);
	if (result == 0)
	{
		if (a_name[b_len] != '\0')
		{
			/* result=0, then strlen(a_name)>=b_len, if a_name[b_len]!=0, then a>b */
			result = 1;
		}
		else
		{
			/* compare second keyword */
			result = (I32_T)a->type - (I32_T)b_type;
		}
	}

	return result;
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_DB_Init
 *
 * DESCRIPTION:
 *   Initialize the database
 *
 * INPUT:
 *   NA
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   NA
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *
*******************************************************************************/
void CLI_DB_Init(void)
{
	/* CLI root tree init */
	utili_rbt_init(&s_cli2_root_tree, (utili_rbt_comp_func_t) __cli2_db_compare);
	return;
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_DB_Find_Entry
 *
 * DESCRIPTION:
 *   Find/create the entry:
 *     Find the entry with given name,
 *     if !found && auto-create: allocate node memory and insert to tree, set new=TRUE
 *
 * INPUT:
 *   path        : find/insert on which tree (NULL for root tree)
 *   type        : the node type (only used for create)
 *   name        : entry name
 *   len         : length of name
 *   auto_create : TRUE  : if entry not exist, allocate memory and create it, 
 *                 FALSE : if entry not exist, don't create
 *   (use this speed up the insert: merge the find and create on tree)
 *
 * OUTPUT:
 *   is_new	 : TRUE  : not-exist and auto-create and create success
 *             FALSE : old entry
 *
 * RETURN:
 *   pointer : the entry pointer
 *   NULL	 : not found or create fail when auto=TRUE
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *
*******************************************************************************/
CLI_CMD_NODE_T *CLI_DB_Find_Entry
	(
	IN OUT CLI_CMD_NODE_T 	*path,
	IN CLI_NODE_TYPE_T 	type,
	IN const I8_T 			*name,
	IN UI32_T 				len,
	IN BOOL_T 				auto_create,
	OUT BOOL_T 				*is_new
	)
{
	utili_rbt_t 			*tree;
	CLI_DB_NODE_T 			*node;
	UI32_T 					size;
	db_cmp_t				cmp_para;

	/* init the output value */
	if (is_new)
	{
		*is_new = FALSE;
	}

	/* select the tree: path==NULL then use root tree */
	tree = (path == CLI_ROOT_PATH) ? &s_cli2_root_tree : &path->sub_tree;

	/* lookup the node by keyword : name (with length) */
	cmp_para.len  = len;
	cmp_para.name = (I8_T *)name;
	cmp_para.type = type;
	node = (CLI_DB_NODE_T *)utili_rbt_find_byfun(tree, (utili_rbt_user_comp_func_t)__cli2_db_compare_ex, &cmp_para);

	if (node) /* found */
	{
		return &node->cli2_entry;
	}

	if (!auto_create) /* not found */
	{
		return NULL;
	}

	/* allocated a node(include entry buffer + dynamic name buffer) from pool */
	size = (sizeof(utili_rbt_node_t) + sizeof(CLI_CMD_NODE_T) + 1 + len);
	node = (CLI_DB_NODE_T *)CLI_MISC_Malloc(size);
	if (!node) /* no memory? */
	{
		return NULL;
	}

	/* save the keyword and initialize the entry */
	memset(&node->cli2_entry, 0, size - sizeof(utili_rbt_node_t));
	node->cli2_entry.name = ((I8_T *)(&(node->cli2_entry))) + sizeof(CLI_CMD_NODE_T);
	node->cli2_entry.type = type;
	memcpy(node->cli2_entry.name, name, len);
	node->cli2_entry.name[len] = '\0';

	/* initialize the sub tree of path */
	utili_rbt_init(&node->cli2_entry.sub_tree, (utili_rbt_comp_func_t)__cli2_db_compare);

	/* insert to RB tree by fast because already do the lookup */
	utili_rbt_ins_node_afterfind(tree, (utili_rbt_node_t *)node);

	if (is_new)
	{
		*is_new = TRUE;
	}

	/* return the group data */
	return &node->cli2_entry;
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_DB_Destory_Entry
 *
 * DESCRIPTION:
 *   Destory the node: delete from tree and free the entry memory
 *
 * INPUT:
 *   path  : which tree (NULL for root tree)
 *   entry : destory which
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   NA
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *
*******************************************************************************/
void CLI_DB_Destory_Entry(IN CLI_CMD_NODE_T *path, IN CLI_CMD_NODE_T *entry)
{
	utili_rbt_t 		*tree;
	CLI_DB_NODE_T 	*node;

	/* select the tree: path==NULL then use root tree */
	tree = (path == CLI_ROOT_PATH) ? &s_cli2_root_tree : &path->sub_tree;

	/* get the node address */
	node = (CLI_DB_NODE_T *) ((UI32_T) entry - sizeof(utili_rbt_node_t));

	/* remove it from tree */
	utili_rbt_del_node(tree, (utili_rbt_node_t *)node);

	/* free the memory */
	CLI_MISC_Free(node);

	return;
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_DB_Get_FirstEntry
 *
 * DESCRIPTION:
 *   Get the first entry node from tree
 *
 * INPUT:
 *   path: get from which tree (NULL for root tree)
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   pointer : the node entry pointer
 *   NULL    : no entry found
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *
*******************************************************************************/
CLI_CMD_NODE_T *CLI_DB_Get_FirstEntry(IN CLI_CMD_NODE_T *path)
{
	utili_rbt_t 		*tree;
	CLI_DB_NODE_T 	*node;

	/* select the tree: path==NULL then use root tree */
	tree = (path == CLI_ROOT_PATH) ? &s_cli2_root_tree : &path->sub_tree;

	/* get first node from ipv4 tree */
	node = (CLI_DB_NODE_T *)utili_rbt_get_first(tree);

	return ((node) ? &node->cli2_entry : NULL);
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_DB_Get_NextEntry
 *
 * DESCRIPTION:
 *   Get the next entry node with given entry node (direct get from tree, no compare)
 *
 * INPUT:
 *   current : current entry
 *   path    : get from which tree (NULL for root tree)
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   pointer : the node entry pointer
 *   NULL    : no next entry found
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *
*******************************************************************************/
CLI_CMD_NODE_T *CLI_DB_Get_NextEntry
	(
	IN CLI_CMD_NODE_T 	*path,
	IN CLI_CMD_NODE_T 	*current
	)
{
	utili_rbt_t 		*tree;
	CLI_DB_NODE_T 		*node;

	/* select the tree: path==NULL then use root tree */
	tree = (path == CLI_ROOT_PATH) ? &s_cli2_root_tree : &path->sub_tree;

	/* get the next node */
	node = (CLI_DB_NODE_T *)((UI32_T)current - sizeof(utili_rbt_node_t));

	/* get next node */
	node = (CLI_DB_NODE_T *)utili_rbt_get_next(tree, (utili_rbt_node_t *)node);

	return ((node) ? &node->cli2_entry : NULL);
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_DB_Get_NearEntryByName
 *
 * DESCRIPTION:
 *   Search the near node entry with given name (>=given name)
 *
 * INPUT:
 *   path : search which tree (NULL for root tree)
 *   name : search name
 *   len  : the length of name
 *   type : the type
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   pointer : the node entry pointer
 *   NULL    : no near node entry found (or the prefix not same with given name+len)
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *
*******************************************************************************/
CLI_CMD_NODE_T *CLI_DB_Get_NearEntryByName
	(
	IN CLI_CMD_NODE_T 		*path,
	IN const I8_T 			*name,
	IN UI32_T 				len,
	IN CLI_NODE_TYPE_T 	type
	)
{
	utili_rbt_t 			*tree;
	CLI_DB_NODE_T 			*node;
	db_cmp_t				cmp_para;

	/* select the tree: path==NULL then use root tree */
	tree = (path == CLI_ROOT_PATH) ? &s_cli2_root_tree : &path->sub_tree;

	/* get first node from ipv4 tree */
	cmp_para.len  = len;
	cmp_para.name = (I8_T *)name;
	cmp_para.type = type;
	node = (CLI_DB_NODE_T *)utili_rbt_find_ge_byfun(tree, (utili_rbt_user_comp_func_t)__cli2_db_compare_ex, &cmp_para);

	return ((node) ? &node->cli2_entry : NULL);
}

#if 1

static bc_boolean __bc_cli_db_permit_print(bc_char *buf, bc_uint32 mode, bc_char str[256])
{
	if (mode == 0)
	{
		if (strstr(buf, str))
			return TRUE;
		else
			return FALSE;
	}
	else if (mode == 1)
	{
		if (strstr(buf, str))
			return FALSE;
		else
			return TRUE;
	}
	else
	{
		return TRUE;
	}
}

static void __bc_cli_db_str_get(bc_char *buf, bc_char *buf_end, bc_char *keyword, bc_char *keyword_end, CLI_PRIV_PARA_SYN_NODE_T *para)
{
	if (para->type == CLI_TYPES_KEYWORD)
	{
		snprintf(buf, 256, "%s %s", keyword, para->name);
		strncpy(buf_end, keyword_end, 64);
	}
	else if (para->type == CLI_TYPES_REQUIRED)
	{
		snprintf(buf, 256, "%s", keyword);
		snprintf(buf_end, 64, "%s", keyword_end);
	}
	else if (para->type == CLI_TYPES_OPTIONAL)
	{
		snprintf(buf, 256, "%s", keyword);
		snprintf(buf_end, 64, "%s", keyword_end);
	}
	else
	{
		if (para->name)
		{
			if (para->type == 16)
			{
				snprintf(buf, 256, "%s %s", keyword, para->name);
				strncpy(buf_end, keyword_end, 64);
			}
			else
			{
				snprintf(buf, 256, "%s <%s>", keyword, para->name);
				strncpy(buf_end, keyword_end, 64);
			}
		}
		else
		{
			snprintf(buf, 256, "%s <%d>", keyword, para->type);
			strncpy(buf_end, keyword_end, 64);
		}
	}
}


static void __bc_cli_db_dump_para(bc_char *keyword, bc_char *keyword_end, CLI_PRIV_PARA_SYN_NODE_T *para, bc_uint32 mode, bc_char str[256])
{
	bc_char buf[256] = {0};
	bc_char buf_end[64] = {0};

	bc_char buf_tmp[256] = {0};
	bc_char buf_end_tmp[64] = {0};

	bc_boolean child_exist = FALSE;

	bc_uint32 idx;

	__bc_cli_db_str_get(buf, buf_end, keyword, keyword_end, para);

	if (para->child)
	{
		child_exist = TRUE;
		for (idx = 0; idx < para->rparam; idx++)	
			__bc_cli_db_dump_para(buf, buf_end, para->child+idx, mode, str);
	}
	
	if (para->sibling)
	{
		if ((para->sibling->type != CLI_TYPES_REQUIRED)
				&& (para->sibling->type != CLI_TYPES_OPTIONAL))
		{
		#if 0
			printf("(sibling)%s %s\n\r", buf, buf_end);

			strncpy(buf_tmp, keyword, 256);
			strncpy(buf_end_tmp, keyword_end, 64);
		#endif

			strncpy(buf_tmp, buf, 256);
			strncpy(buf_end_tmp, buf_end, 64);
		}
		else
		{
			strncpy(buf_tmp, buf, 256);
			strncpy(buf_end_tmp, buf_end, 64);
		}

		para = para->sibling;
		while (para)
		{
			__bc_cli_db_str_get(buf, buf_end, buf_tmp, buf_end_tmp, para);

			child_exist = FALSE;
			if (para->child)
			{
				child_exist = TRUE;
				for (idx = 0; idx < para->rparam; idx++)	
					__bc_cli_db_dump_para(buf, buf_end, para->child+idx, mode, str);
			}
	
			if (para->sibling)
			{
				if ((para->sibling->type != CLI_TYPES_REQUIRED)
						&& (para->sibling->type != CLI_TYPES_OPTIONAL))
				{
				#if 0
					printf("(sibling2)%s %s\n\r", buf, buf_end);

					strncpy(buf_tmp, keyword, 256);
					strncpy(buf_end_tmp, keyword_end, 64);
				#endif

					strncpy(buf_tmp, buf, 256);
					strncpy(buf_end_tmp, buf_end, 64);
				}
				else
				{
					strncpy(buf_tmp, buf, 256);
					strncpy(buf_end_tmp, buf_end, 64);
				}
			}
			else
			{
				if ((!child_exist) && __bc_cli_db_permit_print(buf, mode, str))
					printf("%s %s\n\r", buf, buf_end);
			}

			para = para->sibling;
		}
	}
	else
	{
		if ((!child_exist) && __bc_cli_db_permit_print(buf, mode, str))
			printf("%s %s\n\r", buf, buf_end);
	}
}

static void __bc_cli_db_dump(bc_char *name, bc_uint32 ofs, utili_rbt_t *root, bc_uint32 mode, bc_char str[256])
{
	//bc_uint32 idx;
	CLI_DB_NODE_T *node;

	bc_char buf[256] = {0};
	bc_char buf_end[64] = {0};

	node = (CLI_DB_NODE_T *)utili_rbt_get_first(root);
	if (node)
	{
		do
		{
			//printf("\n\r");
			//for (idx = 0; idx < ofs; idx++)
				//printf(" ");
			//printf("%s ", node->cli2_entry.name);

			snprintf(buf, 128, "%s %s", name, node->cli2_entry.name);

			if (node->cli2_entry.sub_tree.count != 0)
			{
				__bc_cli_db_dump(buf, ofs+ strlen(node->cli2_entry.name), &(node->cli2_entry.sub_tree), mode, str);
			}
			else
			{
				if (node->cli2_entry.para)
				{
					__bc_cli_db_dump_para(buf, buf_end, node->cli2_entry.para, mode, str);
				}
				else
				{
					if (__bc_cli_db_permit_print(buf, mode, str))
						printf("%s \n\r", buf);
				}
			}
		} while ((node = (CLI_DB_NODE_T *)utili_rbt_get_next(root, (utili_rbt_node_t*)node)) != NULL);
	}
}

void bc_cli_db_dump(bc_uint32 mode, bc_char str[256])
{
	__bc_cli_db_dump("", 0, &s_cli2_root_tree, mode, str);
}

#endif

