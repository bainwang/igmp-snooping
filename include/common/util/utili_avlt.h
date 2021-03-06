/*******************************************************************************
  [File name]	: utili_avlt.h
  [Author]     	: bain.wang@outlook.com
  [Version]    	: 1.0
  [Date]       	: 2017-04-04
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
	2017-04-04  	Created								 bain.wang@outlook.com
*******************************************************************************/

#ifndef __UTILI_AVLT_H__
#define __UTILI_AVLT_H__

/* The default maximum height of 32 allows for AVL trees having
   between 5,704,880 and 4,294,967,295 nodes, depending on order of
   insertion.  You may change this compile-time constant as you
   wish. */
#ifndef UTILI_AVLT_MAX_HEIGHT
#define UTILI_AVLT_MAX_HEIGHT	 32
#endif


/* Structure for a node in a threaded AVL tree. */
typedef struct utili_avlt_node {
    void                    		*data;	/* Pointer to data. */
    struct utili_avlt_node    	*link[2];	/* Subtrees or threads. */
    signed char             		bal;		/* Balance factor. */
    char                    		cache;	/* Used during insertion. */
    signed char             		tag[2];	/* Left and right thread tags. */
} utili_avlt_node_t; 


typedef int (*utili_avlt_comp_func) (const void *a, const void *b, void *param);
typedef void (*utili_avlt_node_func) (void *data, void *param);

/* Structure which holds information about a threaded AVL tree. */
typedef struct {
    utili_avlt_node_t       		root;	/* Tree root node. */
    utili_avlt_comp_func    	cmp;	/* Used to compare keys. */
    int                   			count;  	/* Number of nodes in the tree. */
    void                  		*param;	/* Arbitary user data. */
} utili_avlt_tree_t; 

/* General functions. */
utili_avlt_tree_t *utili_avlt_create(utili_avlt_comp_func cmp, void *param);
void utili_avlt_destroy(utili_avlt_tree_t *, utili_avlt_node_func); 
void utili_avlt_free (utili_avlt_tree_t *tree);  
int utili_avlt_count (const utili_avlt_tree_t *);

/* Walk the tree. */
void utili_avlt_walk(const utili_avlt_tree_t *, utili_avlt_node_func, void *param);
void **utili_avlt_next (const utili_avlt_tree_t *tree, void **item);
void **utili_avlt_prev (const utili_avlt_tree_t *tree, void **item);

/* Search for a given item. */
void **utili_avlt_probe (utili_avlt_tree_t *, void *);
void **utili_avlt_find (const utili_avlt_tree_t *, const void *);
void **utili_avlt_find_close (const utili_avlt_tree_t *, const void *);
void *utili_avlt_delete (utili_avlt_tree_t *, const void *);
void *utili_avlt_insert (utili_avlt_tree_t *tree, void *item);
void *utili_avlt_replace (utili_avlt_tree_t *tree, void *item);

#endif

