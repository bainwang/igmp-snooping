/*******************************************************************************
  Copyright (C), 1988-2013, xxxxx Tech. Co., Ltd.
  [File name]	: utili_avlt.c
  [Author]     	: wangbin
  [Version]    	: 1.0
  [Date]       	: 2013-03-12
  [Description]	:
	define avlt api
  [Others]     	:
	NULL
  [Function List]:  
    1. ....
    2. ....
  [History]:
	 Date       	Modification 							 Initials
	---------- 	--------------                                        ----------
	2013-03-12  	Created								 wangbin
*******************************************************************************/

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include "utili_avlt.h"

static int Avlt_Mem_Count=0;

#undef PLUS
/* Tag types. */
#define PLUS +1
#define MINUS -1

#define avl_offsetof(TYPE, MEMBER) 	((unsigned int) &((TYPE *)0)->MEMBER)

#define OS_MemAVL_Allocate	malloc
#define OS_MemAVL_Free		free

#define DEV_OS_MemAvlNode_Allocate() 	malloc(sizeof(utili_avlt_node_t))
#define DEV_OS_MemAvlNode_Free(p) 		free(p)

static void *utili_xmalloc(unsigned int size)
{
	void *vp;

	if (size == 0)
		return NULL;

	vp = OS_MemAVL_Allocate((unsigned long)size);
	assert (vp != NULL);
	if (vp == NULL)
		return NULL;

	Avlt_Mem_Count++;
	return vp;
}

void utili_xfree(void *ptr, void *param)
{
	if (ptr) {}
	if (param) {}

	Avlt_Mem_Count--;
	OS_MemAVL_Free(ptr);
}

/* Creates an AVL tree in arena OWNER (which can be NULL).  The arena
   is owned by the caller, not by the AVL tree.  CMP is a order
   function for the data to be stored in the tree.  PARAM is arbitrary
   data that becomes an argument to the comparison function. */
utili_avlt_tree_t * utili_avlt_create (utili_avlt_comp_func cmp, void *param)
{
	utili_avlt_tree_t *tree;

	assert (cmp != NULL);
	tree = utili_xmalloc (sizeof (utili_avlt_tree_t));
	tree->root.link[0] = tree->root.link[1] = &tree->root;
	tree->root.tag[0] = MINUS;
	tree->root.tag[1] = PLUS;
	tree->cmp = cmp;
	tree->count = 0;
	tree->param = param;
	return tree;
}

/* Destroy tree TREE.  Function FREE_FUNC is called for every node in
   the tree as it is destroyed.

   No effect if the tree has an arena owner and free_func is NULL.
   The caller owns the arena and must destroy it itself.

   Do not attempt to reuse the tree after it has been freed.  Create a
   new one.  */
void utili_avlt_destroy (utili_avlt_tree_t *tree, utili_avlt_node_func free_func)
{
	assert (tree != NULL);
	if (tree->root.link[0] != &tree->root)
	{
		/* Uses Knuth's Algorithm 2.3.1T as modified in exercise 13
		(postorder traversal). */

		/* T1. */
		utili_avlt_node_t *an[UTILI_AVLT_MAX_HEIGHT];	/* Stack A: nodes. */
		char ab[UTILI_AVLT_MAX_HEIGHT];				/* Stack A: bits. */
		int ap = 0;									/* Stack A: height. */
		utili_avlt_node_t *p = tree->root.link[0];

		for (;;)
		{
			/* T2. */
			for (;;)
			{
				/* T3. */
				ab[ap] = 0;
				an[ap++] = p;
				if (p->tag[0] == MINUS)
					break;
				
				p = p->link[0];
			}

			/* T4. */
			for (;;)
			{
				if (ap == 0)
					goto done;

				p = an[--ap];
				if (ab[ap] == 0)
				{
					ab[ap++] = 1;
					if (p->tag[1] == MINUS)
						continue;
					
					p = p->link[1];
						break;
				}

				if (free_func)
					free_func (p->data, tree->param);
				
				utili_xfree (p, NULL);
			}
		}
	}

done:
	utili_xfree (tree, NULL);
}

/* avlt_destroy() with FREE_FUNC hardcoded as free(). */
void utili_avlt_free (utili_avlt_tree_t *tree)
{
	utili_avlt_destroy (tree, (utili_avlt_node_func)utili_xfree);
}

/* Return the number of nodes in TREE. */
int utili_avlt_count (const utili_avlt_tree_t *tree)
{
    assert (tree != NULL);
    return tree->count;
}

/* Walk tree TREE in inorder, calling WALK_FUNC at each node.  Passes
   PARAM to WALK_FUNC.  */
void utili_avlt_walk (const utili_avlt_tree_t *tree, utili_avlt_node_func walk_func, void *param)
{
	const utili_avlt_node_t *p;

	/* Uses Knuth's algorithm 2.3.1D (threaded inorder successor). */
	assert (tree && walk_func);
	p = &tree->root;
	for (;;)
	{
		if (p->tag[1] == MINUS)
			p = p->link[1];
		else
		{
			p = p->link[1];
			while (p->tag[0] == PLUS)
				p = p->link[0];
		}

		if (p == &tree->root)
		{
			return;
		}
		walk_func (p->data, param);
	}
}


/* Given ITEM, a pointer to a data item in TREE (or NULL), returns a
   pointer to the next item in the tree in comparison order, or NULL
   if ITEM is the last item. */
void **utili_avlt_next (const utili_avlt_tree_t *tree, void **item)
{
	const utili_avlt_node_t *p;

	assert (tree != NULL);

	if (item == NULL)
		p = &tree->root;
	else
		p = (utili_avlt_node_t *) (((char *) item) - avl_offsetof (utili_avlt_node_t, data));

	/* Knuth's Algorithm 2.3.1S (threaded inorder successor). */
	if (p->tag[1] == MINUS)
		p = p->link[1];
	else
	{
		p = p->link[1];
		while (p->tag[0] == PLUS)
			p = p->link[0];
	}

	if (p == &tree->root)
		return NULL;

	return (void **) &p->data;
}

/* Given ITEM, a pointer to a data item in TREE (or NULL), returns a
   pointer to the previous item in the tree in comparison order, or
   NULL if ITEM is the first item. */
void **utili_avlt_prev (const utili_avlt_tree_t *tree, void **item)
{
	const utili_avlt_node_t *p;

	assert (tree != NULL);

	if (item == NULL)
	{
		/* Find node with greatest value. */
		p = tree->root.link[0];
		if (p == &tree->root)
		{
			return NULL;
		}
		
		while (p->tag[1] == PLUS)
			p = p->link[1];
	}
	else
	{
		p = (utili_avlt_node_t *) (((char *) item) - avl_offsetof (utili_avlt_node_t, data));

		/* Knuth's Algorithm 2.3.1S (threaded inorder successor)
		modified to find the predecessor node. */
		if (p->tag[0] == MINUS)
			p = p->link[0];
		else
		{
			assert (p->tag[0] == PLUS);
			p = p->link[0];
			while (p->tag[1] == PLUS)
				p = p->link[1];
		}
	}

	if (p == &tree->root)
		return NULL;

	return (void **) &p->data;
}

/* Search TREE for an item matching ITEM.  If found, returns a pointer
   to the address of the item.  If none is found, ITEM is inserted
   into the tree, and a pointer to the address of ITEM is returned.
   In either case, the pointer returned can be changed by the caller,
   or the returned data item can be directly edited, but the key data
   in the item must not be changed. */
void **utili_avlt_probe (utili_avlt_tree_t *tree, void *item)
{
	/* Uses Knuth's Algorithm 6.2.3A (balanced tree search and
	insertion), modified for a threaded binary tree.  Caches results
	of comparisons.  In empirical tests this eliminates about 25% of
	the comparisons seen under random insertions.  */

	/* A1. */
	utili_avlt_node_t *t;
	utili_avlt_node_t *s, *p, *q, *r;

	assert (tree != NULL);
	t = &tree->root;
	s = p = t->link[0];

	if (t->tag[0] == MINUS)
	{
		tree->count++;
		assert (tree->count == 1);
		t->tag[0] = PLUS;
		q = t->link[0] = (utili_avlt_node_t *)DEV_OS_MemAvlNode_Allocate();
		q->data = item;
		q->link[0] = q->link[1] = t;
		q->tag[0] = q->tag[1] = MINUS;
		q->bal = 0;
		return &q->data;
	}

	for (;;)
	{
		/* A2. */
		int diff = tree->cmp (item, p->data, tree->param);

		/* A3. */
		if (diff < 0)
		{
			p->cache = 0;
			q = p->link[0];
			if (p->tag[0] == MINUS)
			{
				q = (utili_avlt_node_t *)DEV_OS_MemAvlNode_Allocate();
				q->link[0] = p->link[0];
				q->tag[0] = p->tag[0];
				p->link[0] = q;
				p->tag[0] = PLUS;
				q->link[1] = p;
				q->tag[1] = MINUS;
				break;
			}
		}
		/* A4. */
		else if (diff > 0)
		{
			p->cache = 1;
			q = p->link[1];
			if (p->tag[1] == MINUS)
			{
				q = (utili_avlt_node_t *)DEV_OS_MemAvlNode_Allocate();
				q->link[1] = p->link[1];
				q->tag[1] = p->tag[1];
				p->link[1] = q;
				p->tag[1] = PLUS;
				q->link[0] = p;
				q->tag[0] = MINUS;
				break;
			}
		}
		else /* A2. */
			return &p->data;

		/* A3, A4. */
		if (q->bal != 0)
			t = p, s = q;
		p = q;
	}

	/* A5. */
	tree->count++;
	q->data = item;
	q->bal = 0;

	/* A6. */
	r = p = s->link[(int) s->cache];
	while (p != q)
	{
		p->bal = (signed char)(p->cache * 2 - 1);
		p = p->link[(int) p->cache];
	}

	/* A7. */
	if (s->cache == 0)
	{
		/* a = -1. */
		if (s->bal == 0)
		{
			s->bal = -1;
			return &q->data;
		}
		else if (s->bal == +1)
		{
			s->bal = 0;
			return &q->data;
		}

		assert (s->bal == -1);
		if (r->bal == -1)
		{
			/* A8. */
			p = r;
			s->link[0] = r->link[1];
			s->tag[0] = r->tag[1];
			r->link[1] = s;
			r->tag[1] = PLUS;
			if (s->link[0] == s)
			{
				s->link[0] = r;
				s->tag[0] = MINUS;
			}
			r->tag[0] = r->tag[1] = PLUS;
			s->bal = r->bal = 0;
		}
		else
		{
			/* A9. */
			assert (r->bal == +1);
			p = r->link[1];
			r->link[1] = p->link[0];
			p->link[0] = r;
			s->link[0] = p->link[1];
			p->link[1] = s;
			if (p->bal == -1)
				s->bal = 1, r->bal = 0;
			else if (p->bal == 0)
				s->bal = r->bal = 0;
			else
			{
				assert (p->bal == +1);
				s->bal = 0, r->bal = -1;
			}
			p->bal = 0;
			p->tag[0] = p->tag[1] = PLUS;
			if (s->link[0] == s)
			{
				s->link[0] = p;
				s->tag[0] = MINUS;
			}
			
			if (r->link[1] == r)
			{
				r->link[1] = p;
				r->tag[1] = MINUS;
			}
		}
	}
	else
	{
		/* a == +1. */
		if (s->bal == 0)
		{
			s->bal = 1;
			return &q->data;
		}
		else if (s->bal == -1)
		{
			s->bal = 0;
			return &q->data;
		}

		assert (s->bal == +1);
		if (r->bal == +1)
		{
			/* A8. */
			p = r;
			s->link[1] = r->link[0];
			s->tag[1] = r->tag[0];
			r->link[0] = s;
			r->tag[0] = PLUS;
			if (s->link[1] == s)
			{
				s->link[1] = r;
				s->tag[1] = MINUS;
			}
			s->bal = r->bal = 0;
		}
		else
		{
			/* A9. */
			assert (r->bal == -1);
			p = r->link[0];
			r->link[0] = p->link[1];
			p->link[1] = r;
			s->link[1] = p->link[0];
			p->link[0] = s;
			if (p->bal == +1)
				s->bal = -1, r->bal = 0;
			else if (p->bal == 0)
				s->bal = r->bal = 0;
			else
			{
				assert (p->bal == -1);
				s->bal = 0, r->bal = 1;
			}
			
			p->tag[0] = p->tag[1] = PLUS;
			if (s->link[1] == s)
			{
				s->link[1] = p;
				s->tag[1] = MINUS;
			}
			if (r->link[0] == r)
			{
				r->link[0] = p;
				r->tag[0] = MINUS;
			}
			p->bal = 0;
		}
	}

	/* A10. */
	if (t != &tree->root && s == t->link[1])
		t->link[1] = p;
	else
		t->link[0] = p;

	return &q->data;
}

/* Search TREE for an item matching ITEM, and return a pointer to it
   if found. */
void **utili_avlt_find (const utili_avlt_tree_t *tree, const void *item)
{
	const utili_avlt_node_t *p;

	assert (tree != NULL);
	if (tree->root.tag[0] == MINUS) 
		return NULL; /* Tree is empty. */

	p = tree->root.link[0];
	for (;;)
	{
		int diff = tree->cmp (item, p->data, tree->param);
		int t;

		/* A3. */
		if (diff < 0)
			t = 0;
		else if (diff > 0)
			t = 1;
		else
			return (void **) &p->data;

		if (p->tag[t] == PLUS)
			p = p->link[t];
		else
			return NULL;
	}
}

/* Search TREE for an item close to the value of ITEM, and return it.
   This function will return a null pointer only if TREE is empty. */
void **utili_avlt_find_close (const utili_avlt_tree_t *tree, const void *item)
{
	const               utili_avlt_node_t *p;

	assert (tree != NULL);
	if (tree->root.tag[0] == MINUS)
		return NULL; /* Tree is empty. */

	p = tree->root.link[0];
	for (;;)
	{
		int diff = tree->cmp (item, p->data, tree->param);
		int t;
		/* A3. */
		if (diff < 0)
			t = 0;
		else if (diff > 0)
			t = 1;
		else
			return (void **) &p->data;


		if (p->tag[t] == PLUS)
			p = p->link[t];
		else
			return (void **) &p->data;
	}
}

/* Searches AVL tree TREE for an item matching ITEM.  If found, the
   item is removed from the tree and the actual item found is returned
   to the caller.  If no item matching ITEM exists in the tree,
   returns NULL. */
void *utili_avlt_delete (utili_avlt_tree_t *tree, const void *item)
{
	/* Uses my Algorithm DT, which can be found at
	http://www.msu.edu/user/pfaffben/avl.  Algorithm DT is based on
	Knuth's Algorithms 6.2.2D (Tree deletion), 6.2.3A (Balanced tree
	search and insertion), 2.3.1I (Insertion into a threaded binary
	trees), and the notes on pages 465-466 of Vol. 3. */

	/* D1. */
	utili_avlt_node_t *pa[UTILI_AVLT_MAX_HEIGHT];	/* Stack P: Nodes. */
	unsigned char a[UTILI_AVLT_MAX_HEIGHT];	/* Stack P: Bits. */
	int k = 1;				/* Stack P: Pointer. */

	utili_avlt_node_t *p;

	assert (tree != NULL);

	if (tree->root.tag[0] == MINUS)
		return NULL; /* Empty tree. */

	a[0] = 0;
	pa[0] = &tree->root;
	p = tree->root.link[0];
	for (;;)
	{
		/* D2. */
		int diff = tree->cmp (item, p->data, tree->param);

		if (diff == 0)
			break;

		/* D3, D4. */
		pa[k] = p;
		if (diff < 0)
		{
			if (p->tag[0] == PLUS)
			{
				p = p->link[0];
				a[k] = 0;
			}
			else
			{
				return NULL;
			}
		}
		else if (diff > 0)
		{
			if (p->tag[1] == PLUS)
			{
				p = p->link[1];
				a[k] = 1;
			}
			else
			{
				return NULL;
			}
		}

		k++;
	}
	
	tree->count--;
	item = p->data;

	{
		utili_avlt_node_t *t = p;
		utili_avlt_node_t **q = &pa[k - 1]->link[(int) a[k - 1]];

		/* D5. */
		if (t->tag[1] == MINUS)
		{
			if (t->tag[0] == PLUS)
			{
				utili_avlt_node_t *const x = t->link[0];

				*q = x;
				(*q)->bal = 0;
				if (x->tag[1] == MINUS)
				{
					if (a[k - 1] == 1)
						x->link[1] = t->link[1];
					else
						x->link[1] = pa[k - 1];
				}
			}
			else
			{
				*q = t->link[a[k - 1]];
				pa[k - 1]->tag[a[k - 1]] = MINUS;
			}
		}
		else
		{
			/* D6. */
			utili_avlt_node_t *r = t->link[1];
			if (r->tag[0] == MINUS)
			{
				r->link[0] = t->link[0];
				r->tag[0] = t->tag[0];
				r->bal = t->bal;
				if (r->tag[0] == PLUS)
				{
					utili_avlt_node_t *s = r->link[0];
					while (s->tag[1] == PLUS)
						s = s->link[1];
					
					assert (s->tag[1] == MINUS);
					s->link[1] = r;
				}
				
				*q = r;
				a[k] = 1;
				pa[k++] = r;
			}
			else
			{
				/* D7. */
				utili_avlt_node_t *s = r->link[0];

				a[k] = 1;
				pa[k++] = t;

				a[k] = 0;
				pa[k++] = r;

				/* D8. */
				while (s->tag[0] != MINUS)
				{
					r = s;
					s = r->link[0];
					a[k] = 0;
					pa[k++] = r;
				}

				/* D9. */
				t->data = s->data;
				if (s->tag[1] == MINUS)
				{
					r->tag[0] = MINUS;
					r->link[0] = t;
				}
				else
				{
					r->link[0] = s->link[1];
					if (s->link[1]->tag[0] == MINUS)
					s->link[1]->link[0] = t;
				}
				p = s;
			}
		}
	}

	DEV_OS_MemAvlNode_Free(p);

	assert (k > 0);
	/* D10. */
	while (--k)
	{
		utili_avlt_node_t *const s = pa[k];

		if (a[k] == 0)
		{
			utili_avlt_node_t *const r = s->link[1];

			/* D10. */
			if (s->bal == -1)
			{
				s->bal = 0;
				continue;
			}
			else if (s->bal == 0)
			{
				s->bal = +1;
				break;
			}

			assert (s->bal == +1);
			if (s->tag[1] == MINUS || r->bal == 0)
			{
				/* D11. */
				s->link[1] = r->link[0];
				r->link[0] = s;
				r->bal = -1;
				pa[k - 1]->link[(int) a[k - 1]] = r;
				break;
			}
			else if (r->bal == +1)
			{
				/* D12. */
				if (PLUS == (s->tag[1] = r->tag[0]))
				s->link[1] = r->link[0];
				r->link[0] = s;
				r->tag[0] = PLUS;
				s->bal = r->bal = 0;
				pa[k - 1]->link[a[k - 1]] = r;
			}
			else
			{
				/* D13. */
				assert (r->bal == -1);
				p = r->link[0];
				if (PLUS == (r->tag[0] = p->tag[1]))
					r->link[0] = p->link[1];
				
				p->link[1] = r;
				p->tag[1] = PLUS;
				if (MINUS == (s->tag[1] = p->tag[0]))
					s->link[1] = p;
				else
					s->link[1] = p->link[0];
				
				p->link[0] = s;
				p->tag[0] = PLUS;
				if (p->bal == +1)
					s->bal = -1, r->bal = 0;
				else if (p->bal == 0)
					s->bal = r->bal = 0;
				else
				{
					assert (p->bal == -1);
					s->bal = 0, r->bal = +1;
				}
				
				p->bal = 0;
				pa[k - 1]->link[(int) a[k - 1]] = p;
				pa[k - 1]->tag[(int) a[k - 1]] = PLUS;
			}
		}
		else
		{
			utili_avlt_node_t *const r = s->link[0];

			/* D10. */
			if (s->bal == +1)
			{
				s->bal = 0;
				continue;
			}
			else if (s->bal == 0)
			{
				s->bal = -1;
				break;
			}

			assert (s->bal == -1);
			if (s->tag[0] == MINUS || r->bal == 0)
			{
				/* D11. */
				s->link[0] = r->link[1];
				r->link[1] = s;
				r->bal = +1;
				pa[k - 1]->link[(int) a[k - 1]] = r;
				break;
			}
			else if (r->bal == -1)
			{
				/* D12. */
				if (PLUS == (s->tag[0] = r->tag[1]))
				s->link[0] = r->link[1];
				r->link[1] = s;
				r->tag[1] = PLUS;
				s->bal = r->bal = 0;
				pa[k - 1]->link[a[k - 1]] = r;
			}
			else
			{
				/* D13. */
				assert (r->bal == +1);
				p = r->link[1];
				if (PLUS == (r->tag[1] = p->tag[0]))
					r->link[1] = p->link[0];
				
				p->link[0] = r;
				p->tag[0] = PLUS;
				if (MINUS == (s->tag[0] = p->tag[1]))
					s->link[0] = p;
				else
					s->link[0] = p->link[1];
				
				p->link[1] = s;
				p->tag[1] = PLUS;
				if (p->bal == -1)
					s->bal = +1, r->bal = 0;
				else if (p->bal == 0)
					s->bal = r->bal = 0;
				else
				{
					assert (p->bal == +1);
					s->bal = 0, r->bal = -1;
				}
				p->bal = 0;
				pa[k - 1]->link[(int) a[k - 1]] = p;
				pa[k - 1]->tag[(int) a[k - 1]] = PLUS;
			}
		}
	}
	
	return (void *) item;
}

/* Inserts ITEM into TREE.  Returns NULL if the item was inserted,
   otherwise a pointer to the duplicate item. */
void *utili_avlt_insert (utili_avlt_tree_t *tree, void *item)
{
	void **p;

	assert (tree != NULL);
	p = utili_avlt_probe (tree, item);
	return (*p == item) ? NULL : *p;
}

/* If ITEM does not exist in TREE, inserts it and returns NULL.  If a
   matching item does exist, it is replaced by ITEM and the item
   replaced is returned.  The caller is responsible for freeing the
   item returned. */
void *utili_avlt_replace (utili_avlt_tree_t *tree, void *item)
{
	void **p;

	assert (tree != NULL);

	p = utili_avlt_probe (tree, item);

	if (*p == item)
		return NULL;
	else
	{
		void *r = *p;
		*p = item;
		return r;
	}
}

