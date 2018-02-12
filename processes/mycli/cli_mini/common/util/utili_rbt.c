/*******************************************************************************
  Copyright (C), 1988-2013, xxxxx Tech. Co., Ltd.
  [File name]	: utili_rbt.c
  [Author]     	: wangbin
  [Version]    	: 1.0
  [Date]       	: 2013-03-12
  [Description]	:
	red-black tree
  [Others]     	:
	NULL
  [Function List]:  
    1. ....
    2. ....
  [History]:
	 Date        Modification 							 			   Initials
	---------- 	--------------                                        ----------
	2013-03-27	 Modified											   wangbin
	2013-03-12  	Created								 				wangbin
*******************************************************************************/

#include "utili_rbt.h"

/* red-black tree node color */
#define RBT_RED				0
#define RBT_BLACK			1

/* right = right (bit31-bit1) + color(bit0) */
#define RBT_COLOR_BIT			(0x00000001u)
#define RBT_PTR_MASK			(~RBT_COLOR_BIT)

#define RBT_GET_RIGHT(x)		((utili_rbt_node_t *)((unsigned int)(x) & RBT_PTR_MASK))
#define RBT_GET_COLOR(x)		((unsigned int)(x) & RBT_COLOR_BIT)

#define RBT_IS_BLACK(x)			((unsigned int)(x) & RBT_COLOR_BIT)
#define RBT_IS_RED(x)			(!RBT_IS_BLACK(x))

#define RBT_SET_RIGHT(dst, src)	do { (dst) = (utili_rbt_node_t *)(((unsigned int)(dst) & RBT_COLOR_BIT) | (unsigned int)(src)); } while (0)
#define RBT_SET_COLOR(dst, c)	do { (dst) = (utili_rbt_node_t *)(((unsigned int)(dst) & RBT_PTR_MASK) | (unsigned int)(c)); } while (0)

#define RBT_SET_BLACK(dst) 		do { (dst) = (utili_rbt_node_t *)((unsigned int)(dst) | RBT_BLACK); } while (0)
#define RBT_SET_RED(dst) 		do { (dst) = (utili_rbt_node_t *)((unsigned int)(dst) & RBT_PTR_MASK); } while (0)

/* null node */
#define NULL_NODE				((utili_rbt_node_t *)0)

/* struct for pseudo red-black tree data node */
typedef struct
{
	utili_rbt_node_t 		node;
	int 					data;
} utili_rbt_pseudo_node_t;


#define utili_rbt_pseudo_data(node)	(const void *)&(((utili_rbt_pseudo_node_t *)node)->data)

static void utili_rbt_rotate_left(utili_rbt_node_t *upper);
static void utili_rbt_rotate_right(utili_rbt_node_t *upper);

/*
	Perform a ``left rotation'' adjustment on the tree.  The given node P and
	its right child C are rearranged so that the P instead becomes the left
	child of C.   The left subtree of C is inherited as the new right subtree
	for P.  The ordering of the keys within the tree is thus preserved.
*/
static void utili_rbt_rotate_left(utili_rbt_node_t *upper)
{
	utili_rbt_node_t *lower, *lowleft, *upparent;

	lower = RBT_GET_RIGHT(upper->right_color);
	lowleft = lower->left;
	RBT_SET_RIGHT(upper->right_color, lowleft);
	lowleft->parent = upper;

	lower->parent = upparent = upper->parent;

	/* don't need to check for root node here because root->parent is
		the sentinel nil node, and root->parent->left points back to root
	*/

	if (upper == upparent->left)
	{
		upparent->left = lower;
	}
	else
	{
		RBT_SET_RIGHT(upparent->right_color, lower);
	}

	lower->left = upper;
	upper->parent = lower;
}



/*
	This operation is the ``mirror'' image of utili_rbt_rotate_left. It is
	the same procedure, but with left and right interchanged.
*/
static void utili_rbt_rotate_right(utili_rbt_node_t *upper)
{
	utili_rbt_node_t *lower, *lowright, *upparent;

	lower = upper->left;
	upper->left = lowright = RBT_GET_RIGHT(lower->right_color);
	lowright->parent = upper;

	lower->parent = upparent = upper->parent;

	if (upper == RBT_GET_RIGHT(upparent->right_color))
	{
		RBT_SET_RIGHT(upparent->right_color, lower);
	}
	else
	{
		upparent->left = lower;
	}

	RBT_SET_RIGHT(lower->right_color, upper);
	upper->parent = lower;
}



/*************************************************
FUNCTION NAME:
	utili_rbt_init

DESCRIPTION:
	Initialize a red-black tree

INPUT:
	tree		: the tree struct pointer
	comp_func	: compare function for red-black tree node compare

OUTPUT:
	tree		: the tree struct pointer

RETURN:

NOTES:

*************************************************/
void utili_rbt_init(OUT utili_rbt_t *tree, IN utili_rbt_comp_func_t comp_func)
{
	/* save the compare function */
	tree->compare = comp_func;

	/* initialize the counter */
	tree->count = 0;

	/* initialize the root node */
	tree->nilnode.parent = &tree->nilnode;
	tree->nilnode.left = &tree->nilnode;
	RBT_SET_RIGHT(tree->nilnode.right_color, &tree->nilnode);
	RBT_SET_BLACK(tree->nilnode.right_color);

	/* initialize the lookup result, not used */
	tree->lookupParent = &tree->nilnode;
	tree->lookupResult = -1;
}



/******************************************************************************\
  Function   : utili_rbt_detach
  Description: 
  Return     : 
  Others     : 
\******************************************************************************/
void utili_rbt_detach(OUT utili_rbt_t *tree)
{
	return;
}



/*************************************************
FUNCTION NAME:
	utili_rbt_set_cookie

DESCRIPTION:
	set the cookie of pass to compare function

INPUT:
	tree		: the tree struct pointer
	cookie		: user's cookie pass to compare function

OUTPUT:
	tree		: the tree's cookie

RETURN:

NOTES:

*************************************************/
void utili_rbt_set_cookie(OUT utili_rbt_t *tree, IN void *cookie)
{
	/* save the cookie */
	tree->cookie = cookie;
}



/*************************************************
FUNCTION NAME:
	utili_rbt_get_count

DESCRIPTION:
	get node count of tree

INPUT:
	tree		: the tree struct pointer

OUTPUT:

RETURN:
	node number of tree

NOTES:

*************************************************/
unsigned int utili_rbt_get_count(IN utili_rbt_t *tree)
{
	return tree->count;
}



/*************************************************
FUNCTION NAME:
	utili_rbt_ins_node_afterfind

DESCRIPTION:
	fast insert a node into tree after find.

INPUT:
	tree		: the tree struct pointer
	node		: insert node (red-black node + the real-data)

OUTPUT:

RETURN:

NOTES:
	the node must initialize before call.

EXAMPLE:
	if (utili_rbt_find(&tree, key)) or (utili_rbt_find_byfun(&tree, key))
	{
        duplicated node
        replace it?
	}
	else
	{
		node = (FDB_RBT_NODE_T *)UTL_BLOCK_Alloc(&tree);
		node->entry.vid = vid var;
		memcpy(node->entry.mac, mac var, sizeof(mac));
		utili_rbt_ins_node_afterfind(&tree, (utili_rbt_node_t *)node);
	}

*************************************************/
void utili_rbt_ins_node_afterfind(IN OUT utili_rbt_t *tree, IN OUT utili_rbt_node_t *node)
{
	utili_rbt_node_t 	*nil = &tree->nilnode;
	utili_rbt_node_t 	*parent, *uncle, *grandpa;

	/* load last lookup result */
	parent = tree->lookupParent;

	if (tree->lookupResult < 0)
	{
		parent->left = node;
	}
	else
	{
		RBT_SET_RIGHT(parent->right_color, node);
	}

	node->parent = parent;
	node->left = nil;
	RBT_SET_RIGHT(node->right_color, nil);

	tree->count++;

	/* red black adjustments */

	RBT_SET_RED(node->right_color);

	while (RBT_IS_RED(parent->right_color))
	{
		grandpa = parent->parent;
		if (parent == grandpa->left)
		{
			uncle = RBT_GET_RIGHT(grandpa->right_color);
			if (RBT_IS_RED(uncle->right_color))
			{
				/* red parent, red uncle */
				RBT_SET_BLACK(parent->right_color);
				RBT_SET_BLACK(uncle->right_color);
				RBT_SET_RED(grandpa->right_color);
				node = grandpa;
				parent = grandpa->parent;
			}
			else
			{
				/* red parent, black uncle */
				if (node == RBT_GET_RIGHT(parent->right_color))
				{
					/* rotation between parent and child preserves grandpa */
					utili_rbt_rotate_left(parent);
					parent = node;
				}

				RBT_SET_BLACK(parent->right_color);
				RBT_SET_RED(grandpa->right_color);
				utili_rbt_rotate_right(grandpa);
				break;
			}
		}
		else
		{
			/* symmetric cases: parent == parent->parent->right */
			uncle = grandpa->left;
			if (RBT_IS_RED(uncle->right_color))
			{
				RBT_SET_BLACK(parent->right_color);
				RBT_SET_BLACK(uncle->right_color);
				RBT_SET_RED(grandpa->right_color);
				node = grandpa;
				parent = grandpa->parent;
			}
			else
			{
				if (node == parent->left)
				{
					utili_rbt_rotate_right(parent);
					parent = node;
				}
				RBT_SET_BLACK(parent->right_color);
				RBT_SET_RED(grandpa->right_color);
				utili_rbt_rotate_left(grandpa);
				break;
			}
		}
	}

	RBT_SET_BLACK(tree->nilnode.left->right_color);
}



/*************************************************
FUNCTION NAME:
	utili_rbt_ins_node

DESCRIPTION:
	insert a node into tree

INPUT:
	tree		: the tree struct pointer
	node		: insert node (red-black node + the real-data)

OUTPUT:

RETURN:
	success		: the param: node
	failure		: the duplication node

NOTES:
	the node must initialize before call.


*************************************************/
utili_rbt_node_t *utili_rbt_ins_node(IN OUT utili_rbt_t *tree, IN OUT utili_rbt_node_t *node)
{
	utili_rbt_node_t	*old_node;

	old_node = utili_rbt_find(tree, utili_rbt_pseudo_data(node));
	if (old_node == NULL_NODE)
	{
		utili_rbt_ins_node_afterfind(tree, node);
		return node;
	}

	return old_node;
}



/*************************************************
FUNCTION NAME:
	utili_rbt_del_node

DESCRIPTION:
	delete a node from tree

INPUT:
	tree		: the tree struct pointer
	node		: deleted node (red-black node + the real-data)

OUTPUT:

RETURN:

NOTES:
	the node must in the tree, ensure this, please use utili_rbt_find.

*************************************************/
void utili_rbt_del_node(IN OUT utili_rbt_t *tree, IN OUT utili_rbt_node_t *node)
{
	utili_rbt_node_t 	*nil = &tree->nilnode, *child, *delparent = node->parent;
	utili_rbt_node_t 	*next,*nextparent, *parent, *sister, *tmp_right, *tmp_left;
	unsigned int		nextcolor, color;

	/* basic deletion */

	/*
		If the node being deleted has two children, then we replace it with its
		successor (i.e. the leftmost node in the right subtree.) By doing this,
		we avoid the traditional algorithm under which the successor's key and
		value *only* move to the deleted node and the successor is spliced out
		from the tree. We cannot use this approach because the user may hold
		pointers to the successor, or nodes may be inextricably tied to some
		other structures by way of embedding, etc. So we must splice out the
		node we are given, not some other node, and must not move contents from
		one node to another behind the user's back.
	*/

	if (node->left != nil && RBT_GET_RIGHT(node->right_color) != nil)
	{
		next = utili_rbt_get_next(tree, node);
		nextparent = next->parent;
		nextcolor = RBT_GET_COLOR(next->right_color);

		/*
			First, splice out the successor from the tree completely, by
			moving up its right child into its place.
		*/

		child = RBT_GET_RIGHT(next->right_color);
		child->parent = nextparent;

		if (nextparent->left == next)
		{
			nextparent->left = child;
		}
		else
		{
			RBT_SET_RIGHT(nextparent->right_color, child);
		}

		/*
			Now that the successor has been extricated from the tree, install it
			in place of the node that we want deleted.
		*/

		next->parent = delparent;
		next->left = node->left;
		tmp_right = RBT_GET_RIGHT(node->right_color);
		RBT_SET_RIGHT(next->right_color, tmp_right);
		next->left->parent = next;
		tmp_right = RBT_GET_RIGHT(next->right_color);
		tmp_right->parent = next;
		color = RBT_GET_COLOR(node->right_color);
		RBT_SET_COLOR(next->right_color, color);
		RBT_SET_COLOR(node->right_color, nextcolor);

		if (delparent->left == node)
		{
			delparent->left = next;
		}
		else
		{
			RBT_SET_RIGHT(delparent->right_color, next);
		}
	}
	else
	{
		child = (node->left != nil) ? node->left : RBT_GET_RIGHT(node->right_color);
		child->parent = delparent = node->parent;
		if (node == delparent->left)
		{
			delparent->left = child;
		}
		else
		{
			RBT_SET_RIGHT(delparent->right_color, child);
		}
	}

	node->parent = NULL_NODE;
	RBT_SET_RIGHT(node->right_color, NULL_NODE);
	node->left = NULL_NODE;

	tree->count--;

	/* red-black adjustments */

	if (RBT_IS_BLACK(node->right_color))
	{
		RBT_SET_RED(tree->nilnode.left->right_color);

		while (RBT_IS_BLACK(child->right_color))
		{
			parent = child->parent;
			if (child == parent->left)
			{
				sister = RBT_GET_RIGHT(parent->right_color);
				if (RBT_IS_RED(sister->right_color))
				{
					RBT_SET_BLACK(sister->right_color);
					RBT_SET_RED(parent->right_color);
					utili_rbt_rotate_left(parent);
					sister = RBT_GET_RIGHT(parent->right_color);
				}

				tmp_left = sister->left;
				tmp_right = RBT_GET_RIGHT(sister->right_color);
				if (RBT_IS_BLACK(tmp_left->right_color) && RBT_IS_BLACK(tmp_right->right_color))
				{
					RBT_SET_RED(sister->right_color);
					child = parent;
				}
				else
				{
					if (RBT_IS_BLACK(tmp_right->right_color))
					{
						RBT_SET_BLACK(tmp_left->right_color);
						RBT_SET_RED(sister->right_color);
						utili_rbt_rotate_right(sister);
						sister = RBT_GET_RIGHT(parent->right_color);
					}
					color = RBT_GET_COLOR(parent->right_color);
					RBT_SET_COLOR(	sister->right_color, color);
					tmp_right = RBT_GET_RIGHT(sister->right_color);
					RBT_SET_BLACK(tmp_right->right_color);
					RBT_SET_BLACK(parent->right_color);
					utili_rbt_rotate_left(parent);
					break;
				}
			}
			else
			{
				/* symmetric case: child == child->parent->right */
				sister = parent->left;
				if (RBT_IS_RED(sister->right_color))
				{
					RBT_SET_BLACK(sister->right_color);
					RBT_SET_RED(parent->right_color);
					utili_rbt_rotate_right(parent);
					sister = parent->left;
				}
				tmp_left = sister->left;
				tmp_right = RBT_GET_RIGHT(sister->right_color);
				if (RBT_IS_BLACK(tmp_right->right_color) && RBT_IS_BLACK(tmp_left->right_color))
				{
					RBT_SET_RED(sister->right_color);
					child = parent;
				}
				else
				{
					if (RBT_IS_BLACK(tmp_left->right_color))
					{
						RBT_SET_BLACK(tmp_right->right_color);
						RBT_SET_RED(sister->right_color);
						utili_rbt_rotate_left(sister);
						sister = parent->left;
					}
					color = RBT_GET_COLOR(parent->right_color);
					RBT_SET_COLOR(	sister->right_color, color);
					tmp_left = sister->left;
					RBT_SET_BLACK(tmp_left->right_color);
					RBT_SET_BLACK(parent->right_color);
					utili_rbt_rotate_right(parent);
					break;
				}
			}
		}

		RBT_SET_BLACK(child->right_color);
		RBT_SET_BLACK(tree->nilnode.left->right_color);
	}
}



/*************************************************
FUNCTION NAME:
	utili_rbt_del_node_byentry

DESCRIPTION:
	delete a item from tree

INPUT:
	tree			: the tree struct pointer
	item			: deleted node by key-word

OUTPUT:

RETURN:
	NULL			: not found the item
	valid pointer	: deleted node

NOTES:

*************************************************/
utili_rbt_node_t *utili_rbt_del_node_byentry(IN OUT utili_rbt_t *tree, IN const void *item)
{
	utili_rbt_node_t *node;

	node = utili_rbt_find(tree, item);

	if (node)
	{
		utili_rbt_del_node(tree, node);
	}

	return node;
}



#define WHAT_IS_GET

/* ======================================================================================= *\
    get 簇: 指定树中的某一个结点（指向某个节点的指针），找出相关（上一个、下一个、第一个、
            最后一个）的其它节点
\* ======================================================================================= */

/*************************************************
FUNCTION NAME:
	utili_rbt_get_first

DESCRIPTION:
	search lowest(leftmost) node of tree

INPUT:
	tree		: the tree struct pointer

OUTPUT:

RETURN:
	NULL		: tree is empty
	pointer		: the first node

NOTES:

*************************************************/
utili_rbt_node_t *utili_rbt_get_first(IN utili_rbt_t *tree)
{
	utili_rbt_node_t *nil = &tree->nilnode, *root = tree->nilnode.left, *left;

	if (root != nil)
	{
		while ((left = root->left) != nil)
		{
			root = left;
		}
	}

	return (root == nil) ? NULL_NODE : root;
}



/*************************************************
FUNCTION NAME:
	utili_rbt_get_last

DESCRIPTION:
	search highest (rightmost) node of tree

INPUT:
	tree		: the tree struct pointer

OUTPUT:

RETURN:
	NULL		: tree is empty
	pointer		: the last node

NOTES:

*************************************************/
utili_rbt_node_t *utili_rbt_get_last(IN utili_rbt_t *tree)
{
	utili_rbt_node_t *nil = &tree->nilnode, *root = tree->nilnode.left, *right;

	if (root != nil)
	{
		while ((right = RBT_GET_RIGHT(root->right_color)) != nil)
		{
			root = right;
		}
	}

	return (root == nil) ? NULL_NODE : root;
}



/*************************************************
FUNCTION NAME:
	utili_rbt_get_next

DESCRIPTION:
	search the given node's successor

INPUT:
	tree		: the tree struct pointer
	curr		: predecessor node

OUTPUT:

RETURN:
	NULL		: arrive the tail of tree
	pointer		: the next node

NOTES:

*************************************************/
utili_rbt_node_t *utili_rbt_get_next(IN utili_rbt_t *tree, IN utili_rbt_node_t *curr)
{
	utili_rbt_node_t *nil = &tree->nilnode, *parent, *left;

	if (RBT_GET_RIGHT(curr->right_color) != nil)
	{
		curr = RBT_GET_RIGHT(curr->right_color);
		while ((left = curr->left) != nil)
		{
			curr = left;
		}
		return curr;
	}

	parent = curr->parent;
	while (parent != nil && curr == RBT_GET_RIGHT(parent->right_color))
	{
		curr = parent;
		parent = curr->parent;
	}

	return (parent == nil) ? NULL_NODE : parent;
}



/*************************************************
FUNCTION NAME:
	utili_rbt_get_prev

DESCRIPTION:
	search the given node's predecessor

INPUT:
	tree		: the tree struct pointer
	curr		: successor node

OUTPUT:

RETURN:
	NULL		: arrive the tail of tree
	pointer		: the prev node

NOTES:

*************************************************/
utili_rbt_node_t *utili_rbt_get_prev(IN utili_rbt_t *tree, IN utili_rbt_node_t *curr)
{
	utili_rbt_node_t *nil = &tree->nilnode, *parent, *right;

	if (curr->left != nil)
	{
		curr = curr->left;
		while ((right = RBT_GET_RIGHT(curr->right_color)) != nil)
		{
			curr = right;
		}

		return curr;
	}

	parent = curr->parent;
	while (parent != nil && curr == parent->left)
	{
		curr = parent;
		parent = curr->parent;
	}

	return (parent == nil) ? NULL_NODE : parent;
}



#define WHAT_IS_FIND 

/* ======================================================================================= *\
    find 簇: 指定data，从root开始查找 
\* ======================================================================================= */

/*************************************************
FUNCTION NAME:
	utili_rbt_find

DESCRIPTION:
	find a item from tree

INPUT:
	tree		: the tree struct pointer
	key			: find key pointer (the real-data but not the red-black node)

OUTPUT:

RETURN:
	NULL		: can't found the item
	pointer		: the red-black node match the item

NOTES:

*************************************************/
utili_rbt_node_t *utili_rbt_find(IN utili_rbt_t *tree, IN const void *key)
{
	utili_rbt_node_t 	*root = tree->nilnode.left;
	utili_rbt_node_t 	*nil = &tree->nilnode;
	utili_rbt_node_t 	*parent = nil;
	int 				result = -1;

	while (root != nil)
	{
		result = tree->compare(key, utili_rbt_pseudo_data(root), tree->cookie);
		if (!result)
		{
			return root;
		}

		parent = root;
		root = (result < 0) ? root->left : RBT_GET_RIGHT(root->right_color);
	}

	/* save the result for fast insert */
	tree->lookupParent = parent;
	tree->lookupResult = result;

	return NULL_NODE;
}



/*************************************************
FUNCTION NAME:
	utili_rbt_find_byfun

DESCRIPTION:
	find a item from tree

INPUT:
	tree		: the tree struct pointer
	fcmp		: the user special compare function
	para		: special compare field value

OUTPUT:

RETURN:
	NULL		: can't found the item
	pointer		: the red-black node match the item

NOTES:

*************************************************/
utili_rbt_node_t *utili_rbt_find_byfun
	(
		IN utili_rbt_t *tree, 
		IN utili_rbt_user_comp_func_t fcmp,
		IN void *para
	)
{
	utili_rbt_node_t 	*root = tree->nilnode.left;
	utili_rbt_node_t 	*nil = &tree->nilnode;
	utili_rbt_node_t 	*parent = nil;
	int 				result = -1;

	while (root != nil)
	{
		result = fcmp(utili_rbt_pseudo_data(root), para);
		if (!result)
		{
			return root;
		}

		parent = root;

		/* because swap the parameter of compare, so inverse the result
			note: the result maybe save to lookupResult
		*/
		result = -result;
		root = (result < 0) ? root->left : RBT_GET_RIGHT(root->right_color);
	}

	/* save the result for fast insert */
	tree->lookupParent = parent;
	tree->lookupResult = result;

	return NULL_NODE;
}



/*************************************************
FUNCTION NAME:
	utili_rbt_find_prev

DESCRIPTION:
	search node that < item

INPUT:
	tree		: the tree struct pointer
	item		: the compare keyword  (the real-data)

OUTPUT:

RETURN:
	NULL		: arrive the head of tree
	pointer		: the founded node

NOTES:

*************************************************/
utili_rbt_node_t *utili_rbt_find_prev(IN utili_rbt_t *tree, IN const void *item)
{
	utili_rbt_node_t 	*root = tree->nilnode.left;
	utili_rbt_node_t 	*nil = &tree->nilnode;
	utili_rbt_node_t 	*tentative = NULL_NODE;
	int 				result;

	while (root != nil)
	{
		result = tree->compare(item, utili_rbt_pseudo_data(root), tree->cookie);
		if (!result)
		{
			/* find the entry, it is equal, should get the prev */
			return utili_rbt_get_prev(tree, root);
		}

		if (result < 0)
		{
			root = root->left;
		}
		else
		{
			tentative = root;
			root = RBT_GET_RIGHT(root->right_color);
		}
	}

	return tentative;
}



/*************************************************
FUNCTION NAME:
	utili_rbt_find_prev_byfun

DESCRIPTION:
	search node that < item
	a special version for performance, most we use struct as entry,
	if use UTL_RBT_UpperBound, need merge each field into a struct,
	this function can direct use some value or pointer, but not memcpy into a struct

INPUT:
	tree		: the tree struct pointer
	fcmp		: the user special compare function
	para		: special compare field value

OUTPUT:

RETURN:
	NULL		: arrive the tail of tree
	pointer		: the founded node

NOTES:

*************************************************/
utili_rbt_node_t *utili_rbt_find_prev_byfun
	(
		IN utili_rbt_t *tree, 
		IN utili_rbt_user_comp_func_t fcmp,
		IN void *para
	)
{
	utili_rbt_node_t 	*root = tree->nilnode.left;
	utili_rbt_node_t 	*nil = &tree->nilnode;
	utili_rbt_node_t 	*tentative = NULL_NODE;
	int 				result;

	while (root != nil)
	{
		result = fcmp(utili_rbt_pseudo_data(root), para);
		if (!result)
		{
			/* find the entry, it is equal, should get the prev */
			return utili_rbt_get_prev(tree, root);
		}

		/* because swap the parameter of compare, so inverse the result */
		result = -result;
		if (result < 0)
		{
			root = root->left;
		}
		else
		{
			tentative = root;
			root = RBT_GET_RIGHT(root->right_color);
		}
	}

	return tentative;
}



/*************************************************
FUNCTION NAME:
	utili_rbt_find_next

DESCRIPTION:
	search node that > item

INPUT:
	tree		: the tree struct pointer
	item		: the compare keyword  (the real-data)

OUTPUT:

RETURN:
	NULL		: arrive the tail of tree
	pointer		: the founded node

NOTES:

HISTORY:
		porting from kazlib-1.20 dict.c : dict_lower_bound

*************************************************/
utili_rbt_node_t *utili_rbt_find_next(IN utili_rbt_t *tree, IN const void *item)
{
	utili_rbt_node_t 	*root = tree->nilnode.left;
	utili_rbt_node_t 	*nil = &tree->nilnode;
	utili_rbt_node_t 	*tentative = NULL_NODE;
	int 				result;

	while (root != nil)
	{
		result = tree->compare(item, utili_rbt_pseudo_data(root), tree->cookie);
		if (!result)
		{
			/* find the entry, it is equal, should get the next */
			return utili_rbt_get_next(tree, root);
		}

		if (result > 0)
		{
			root = RBT_GET_RIGHT(root->right_color);
		}
		else
		{
			tentative = root;
			root = root->left;
		}
	}

	return tentative;
}



/*************************************************
FUNCTION NAME:
	utili_rbt_find_next_byfun

DESCRIPTION:
	search node that > item
	a special version for performance, most we use struct as entry,
	if use UTL_RBT_LowerBound, need merge each field into a struct,
	this function can direct use some value or pointer, but not memcpy into a struct

INPUT:
	tree		: the tree struct pointer
	fcmp		: the user special compare function
	para		: special compare field value

OUTPUT:

RETURN:
	NULL		: arrive the tail of tree
	pointer		: the founded node

NOTES:

*************************************************/
utili_rbt_node_t *utili_rbt_find_next_byfun
	(
		IN utili_rbt_t *tree, 
		IN utili_rbt_user_comp_func_t fcmp,
		IN void *para
	)
{
	utili_rbt_node_t 	*root = tree->nilnode.left;
	utili_rbt_node_t 	*nil = &tree->nilnode;
	utili_rbt_node_t 	*tentative = NULL_NODE;
	int 				result;

	while (root != nil)
	{
		result = fcmp(utili_rbt_pseudo_data(root), para);
		if (!result)
		{
			/* find the entry, it is equal, should get the next */
			return utili_rbt_get_next(tree, root);
		}

		/* because swap the parameter of compare, so inverse the result */
		result = -result;
		if (result > 0)
		{
			root = RBT_GET_RIGHT(root->right_color);
		}
		else
		{
			tentative = root;
			root = root->left;
		}
	}

	return tentative;
}



/*************************************************
FUNCTION NAME:
	utili_rbt_find_le(Littler Element)

DESCRIPTION:
	search node that <= item

INPUT:
	tree		: the tree struct pointer
	item		: the compare keyword  (the real-data)

OUTPUT:

RETURN:
	NULL		: arrive the head of tree
	pointer		: the founded node

NOTES:

*************************************************/
utili_rbt_node_t *utili_rbt_find_le(IN utili_rbt_t *tree, IN const void *item)
{
	utili_rbt_node_t 	*root = tree->nilnode.left;
	utili_rbt_node_t 	*nil = &tree->nilnode;
	utili_rbt_node_t 	*tentative = NULL_NODE;
	int 				result;

	while (root != nil)
	{
		result = tree->compare(item, utili_rbt_pseudo_data(root), tree->cookie);
		if (!result)
		{
			/* found */
			return root;
		}

		if (result < 0)
		{
			root = root->left;
		}
		else
		{
			tentative = root;
			root = RBT_GET_RIGHT(root->right_color);
		}
	}

	return tentative;
}



/*************************************************
FUNCTION NAME:
	utili_rbt_find_le_byfun(Littler Element)

DESCRIPTION:
	search node that <= item
	a special version for performance, most we use struct as entry,
	if use UTL_RBT_UpperBound, need merge each field into a struct,
	this function can direct use some value or pointer, but not memcpy into a struct

INPUT:
	tree		: the tree struct pointer
	fcmp		: the user special compare function
	para		: special compare field value

OUTPUT:

RETURN:
	NULL		: arrive the tail of tree
	pointer		: the founded node

NOTES:

*************************************************/
utili_rbt_node_t *utili_rbt_find_le_byfun
	(
	IN utili_rbt_t *tree, 
	IN utili_rbt_user_comp_func_t fcmp,
	IN void *para
	)
{
	utili_rbt_node_t 	*root = tree->nilnode.left;
	utili_rbt_node_t 	*nil = &tree->nilnode;
	utili_rbt_node_t 	*tentative = NULL_NODE;
	int 				result;

	while (root != nil)
	{
		result = fcmp(utili_rbt_pseudo_data(root), para);
		if (!result)
		{
			/* found */
			return root;
		}

		/* because swap the parameter of compare, so inverse the result */
		result = -result;
		if (result < 0)
		{
			root = root->left;
		}
		else
		{
			tentative = root;
			root = RBT_GET_RIGHT(root->right_color);
		}
	}

	return tentative;
}



/*************************************************
FUNCTION NAME:
	utili_rbt_find_ge(Greater Element)

DESCRIPTION:
	search node that >= item

INPUT:
	tree		: the tree struct pointer
	item		: the compare keyword  (the real-data)

OUTPUT:

RETURN:
	NULL		: arrive the tail of tree
	pointer		: the founded node

NOTES:

*************************************************/
utili_rbt_node_t *utili_rbt_find_ge(IN utili_rbt_t *tree, IN const void *item)
{
	utili_rbt_node_t 	*root = tree->nilnode.left;
	utili_rbt_node_t 	*nil = &tree->nilnode;
	utili_rbt_node_t 	*tentative = NULL_NODE;
	int 				result;

	while (root != nil)
	{
		result = tree->compare(item, utili_rbt_pseudo_data(root), tree->cookie);
		if (!result)
		{
			/* found */
			return root;
		}

		if (result > 0)
		{
			root = RBT_GET_RIGHT(root->right_color);
		}
		else
		{
			tentative = root;
			root = root->left;
		}
	}

	return tentative;
}



/*************************************************
FUNCTION NAME:
	utili_rbt_find_ge_byfun(Greater Element)

DESCRIPTION:
	search node that >= item
	a special version for performance, most we use struct as entry,
	if use UTL_RBT_LowerBound, need merge each field into a struct,
	this function can direct use some value or pointer, but not memcpy into a struct

INPUT:
	tree		: the tree struct pointer
	fcmp		: the user special compare function
	para		: special compare field value

OUTPUT:

RETURN:
	NULL		: arrive the tail of tree
	pointer		: the founded node

NOTES:

*************************************************/
utili_rbt_node_t *utili_rbt_find_ge_byfun
	(
	IN utili_rbt_t *tree, 
	IN utili_rbt_user_comp_func_t fcmp,
	IN void *para
	)
{
	utili_rbt_node_t 	*root = tree->nilnode.left;
	utili_rbt_node_t 	*nil = &tree->nilnode;
	utili_rbt_node_t 	*tentative = NULL_NODE;
	int 				result;

	while (root != nil)
	{
		result = fcmp(utili_rbt_pseudo_data(root), para);
		if (!result)
		{
			/* found */
			return root;
		}

		/* because swap the parameter of compare, so inverse the result */
		result = -result;
		if (result > 0)
		{
			root = RBT_GET_RIGHT(root->right_color);
		}
		else
		{
			tentative = root;
			root = root->left;
		}
	}

	return tentative;
}



