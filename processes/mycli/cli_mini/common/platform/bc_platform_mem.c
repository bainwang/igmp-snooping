/************************************************************
  Copyright (C), 1988-2014, xxxxx Tech. Co., Ltd.
  FileName:
  Author:  wangbin      Version :  1.0        Date:2014-2-8
  Description:    内存分配相关函数               
  Version:             1.0           
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "utili_rbt.h"
#include <string.h>
#include "bc_modules.h"
#include "bc_common_defs.h"
#include "bc_platform_types.h"
#include "bc_platform_mutex.h"
#include "bc_platform_mem.h"
#include "bc_print.h"


#ifdef _STATIC_NODE_
#define BC_MEM_ALLOC_NODE_COUNT   10240 //limit malloc max count 
#endif
#define BC_MEM_ALLOC_MAX_SIZE           //limit malloc max size 

typedef struct 
{	
	bc_modules_e module;
	bc_char *func;
	bc_uint32 line;
	void *data;
	bc_uint32 size;
	bc_int32 result;
}mem_allot_t;


typedef struct mem_rbt_node
{
	utili_rbt_node_t 	rbt_node;
	mem_allot_t			data;
	bc_uint8            avail;         
} mem_rbt_node_t;

static utili_rbt_t   bc_platform_mem_tree;
static bc_uint64     bc_mem_totalsize = 0;
static bc_pthread_mutex_t  *bc_mem_mutext_mut;
static bc_uint64 bc_mem_alloc_maxsize = (50*1024*1024); /*default max memory 50M for malloc */


#ifdef _STATIC_NODE_

static mem_rbt_node_t mem_alloc_node[BC_MEM_ALLOC_NODE_COUNT];
static mem_rbt_node_t * _mem_tree_node_alloc(void)
{
	bc_uint32 i = 0;
#ifdef BC_MEM_ALLOC_MAX_SIZE
	for(i = 0;(i < BC_MEM_ALLOC_NODE_COUNT)&&(bc_mem_totalsize < bc_mem_alloc_maxsize);i++)
#else
	for(i = 0;i < BC_MEM_ALLOC_NODE_COUNT;i++)
#endif
	{
		if(mem_alloc_node[i].avail == FALSE)
			break;
	}
#ifdef BC_MEM_ALLOC_MAX_SIZE
	if( (i >= BC_MEM_ALLOC_NODE_COUNT)||(bc_mem_totalsize >= bc_mem_alloc_maxsize))
#else
	if( i >= BC_MEM_ALLOC_NODE_COUNT)
#endif
	{
#ifdef BC_MEM_ALLOC_MAX_SIZE
		BC_PT_ERROR(BC_MODULE_PLATFORM,"\r\nerr,count:%d,bc_mem_totalsize:%lu,memory malloc max count:%d,max size:%d\n",i,bc_mem_totalsize,BC_MEM_ALLOC_NODE_COUNT,bc_mem_alloc_maxsize);
#else
		BC_PT_ERROR(BC_MODULE_PLATFORM,"\r\ncount:%d,memory malloc failed\n",i);
#endif
		return NULL;
	}

	mem_alloc_node[i].avail = TRUE;
	
	return &mem_alloc_node[i];	
}

static void _mem_tree_node_free(mem_rbt_node_t *node)
{
	if(node == NULL)
	{
		BC_PT_ERROR(BC_MODULE_PLATFORM,"\r\n[%s-%d]:err NULL parameter",__FUNCTION__,__LINE__);		
		return ;
	}
	node->avail = FALSE;
	return ;
}

#else
static mem_rbt_node_t * _mem_tree_node_alloc(void)
{

#ifdef BC_MEM_ALLOC_MAX_SIZE
	if(bc_mem_totalsize > bc_mem_alloc_maxsize)
	{
		BC_PT_ERROR(BC_MODULE_PLATFORM,"\r\nerr,bc_mem_totalsize:%llu,memory malloc max size:%llu\n",bc_mem_totalsize,bc_mem_alloc_maxsize);
		return NULL;
	}
#endif
	mem_rbt_node_t *node = (mem_rbt_node_t *)malloc(sizeof(mem_rbt_node_t));

	if(node == NULL)
	{
		BC_PT_ERROR(BC_MODULE_PLATFORM,"mem node malloc err!!\n");
		return NULL;
	}
	node->avail = TRUE;

	return node;
}

static void _mem_tree_node_free(mem_rbt_node_t *node)
{
	if(node == NULL)
	{
		BC_PT_ERROR(BC_MODULE_PLATFORM,"\r\n[%s-%d]:err NULL parameter",__FUNCTION__,__LINE__);		
		return ;
	}
	
	if(node->avail == TRUE)
	{
		free(node);
	}
	else
	{
		BC_PT_ERROR(BC_MODULE_PLATFORM,"\r\n[%s-%d]:err node is unused!!\n",__FUNCTION__,__LINE__);
		return ;
	}
	
}

#endif
static bc_int32 mem_comp_func(const void *data_new, const void *data_tre, void *opt)
{
	void 	*item_new, *item_tre;
	bc_uint32 __attribute__((unused)) tre_size = 0;
	item_new = (void *)((mem_allot_t *)data_new)->data;
	item_tre = (void *)((mem_allot_t *)data_tre)->data;
	tre_size = ((mem_allot_t *)data_tre)->size;
	//bc_platform_trace("comp:src-[%p],des-[%p],size-[%d]\n",item_new,item_tre,tre_size);
	if(item_new == item_tre)
	{
		//bc_platform_trace("\r\n[%s-%d]:find [%p] success!\n",((mem_allot_t *)data_tre)->func,((mem_allot_t *)data_tre)->line,item_new);
		return 0;
	}
	else if(item_new > item_tre)
	{
		return 1;
	}
	else //if(item_new < item_tre)
	{
		return -1;
	}
}

/*************************************************
  Function: bc_platform_mem_init_ex
  Description:初始化内存分配相关结构
  Input: 
  		
  Output:
  Return:
  		void
  Note: 用bc_platform_init替代bc_platform_mem_init
  进行平台结构的初始化
  History: 
*************************************************/
void bc_platform_mem_init_ex(void)
{

#ifdef _STATIC_NODE_
	memset(mem_alloc_node, 0, BC_MEM_ALLOC_NODE_COUNT*sizeof(mem_rbt_node_t));
#endif
	if((bc_mem_mutext_mut = bc_platform_mutex_create("MemMutex1")) == NULL)
	{
		BC_PT_ERROR(BC_MODULE_PLATFORM,"<%s>:create mutex 1 fail!\n",__FUNCTION__);
		return ;
	}
	
	utili_rbt_init(&bc_platform_mem_tree, mem_comp_func);
}

/*************************************************
  Function: bc_platform_mem_set_maxsize
  Description:设置每个进程内存分配的最大值
  Input: 
  		maxsize:每个进程内存分配的最大值，
  		单位字节
  		
  Output:
  Return:
  		void
  Note: 默认值:5*1024*1024
  History: 
*************************************************/
void bc_platform_mem_set_maxsize(bc_uint64 maxsize)
{
#ifdef BC_MEM_ALLOC_MAX_SIZE
	bc_mem_alloc_maxsize = maxsize;
#endif
}

/*************************************************
  Function: bc_platform_mem_malloc_ex
  Description:分配函数
  Input: 
  		module:模块id
  		func:记录调用分配函数的函数名
  		line:记录分配位置
  		size:分配的空间大小
  		
  Output:
  Return:
  		成功:返回 指
  		失败:返回NULL
  Note: 外部调用请使用宏bc_platform_mem_malloc
  History: 
*************************************************/
void *bc_platform_mem_malloc_ex(
	bc_modules_e module,
	bc_char *func,
	bc_uint32 line,
	bc_uint32 size
	)
{
	mem_rbt_node_t *node;
	mem_allot_t p ;

	if(module > BC_LAST_MODULE)
	{
		BC_PT_ERROR(BC_MODULE_PLATFORM,"module id is errr!\n");
		return NULL;
	}
	p.func = func;
	p.line = line;
	p.module = module;
	p.data = malloc(size);
	if(p.data == NULL)
	{
		p.module = BC_FIRST_MODULE;
		p.size = 0;
		p.result = -1;
		BC_PT_ERROR(BC_MODULE_PLATFORM,"\r\n [%s-%d]:fun:%s,line:%d,memory malloc failed\n",__FUNCTION__,__LINE__,func,line);
		return NULL;
	}
	p.size  = size;
	p.result = 0;
	node = _mem_tree_node_alloc();
	if(node == NULL)
	{
		BC_PT_ERROR(BC_MODULE_PLATFORM,"\r\n [%s-%d]:fun:%s,line:%d,memory malloc failed\n",__FUNCTION__,__LINE__,func,line);
		free(p.data);	
		return NULL;
	}
	memcpy(&node->data,&p,sizeof(mem_allot_t));
	bc_platform_mutex_lock(bc_mem_mutext_mut);
	bc_mem_totalsize +=size;
	utili_rbt_ins_node(&bc_platform_mem_tree, &node->rbt_node);
	bc_platform_trace("\r\n[%s-%d]:malloc[%p]success!\n",p.func,p.line,p.data);
	bc_platform_mutex_unlock(bc_mem_mutext_mut);
	
	return p.data;
}

/*************************************************
  Function: bc_platform_mem_free_ex
  Description:释放内存函数
  Input: 
  		module:模块id
  		func:记录调用分配函数的函数名
  		line:记录分配位置
  		p:释放的地址指针
  		
  Output:
  Return:
  		void
  Note: 外部调用请使用宏bc_platform_mem_free
  History: 
*************************************************/
void bc_platform_mem_free_ex(bc_modules_e module,bc_char *func,bc_uint32 line,void *p)
{
	void *addr = p;
	utili_rbt_node_t *mem_node;
	mem_allot_t freedata;

	if(addr == NULL)
	{
		BC_PT_ERROR(BC_MODULE_PLATFORM,"\r\n[%s-%d]memory free failed cause some NULL parameter",__FUNCTION__,__LINE__);
		return ;
	}
	memset(&freedata,0,sizeof(mem_allot_t));
	freedata.data = p;
	
	bc_platform_mutex_lock(bc_mem_mutext_mut);
	mem_node = utili_rbt_del_node_byentry(&bc_platform_mem_tree,(const void *)&freedata);
	if(mem_node == NULL)
	{
		bc_platform_mutex_unlock(bc_mem_mutext_mut);
		BC_PT_ERROR(BC_MODULE_PLATFORM,"\r\n[%s-%d]memory free ,not found the item[%p]\n",func,line,p);
		return ;
	}
	
	bc_mem_totalsize -=((mem_rbt_node_t *)mem_node)->data.size;
	bc_platform_trace("\r\n[%s-%d]:free[%p]success!\n",((mem_rbt_node_t *)mem_node)->data.func,((mem_rbt_node_t *)mem_node)->data.line,((mem_rbt_node_t *)mem_node)->data.data);
	_mem_tree_node_free((mem_rbt_node_t *)mem_node);

	free(addr);
	bc_platform_mutex_unlock(bc_mem_mutext_mut);
}


/*************************************************
  Function: bc_platform_mem_show
  Description:dump 所有内存分配的情况
  Input: 
	
  Output:
  Return:
  		void
  Note: 
  History: 
*************************************************/
void bc_platform_mem_show(void)
{
	utili_rbt_node_t *predecessor = NULL,*next = NULL;
	mem_allot_t *data = NULL;
	bc_uint32  i    = 1;
	bc_uint32 memsize[BC_LAST_MODULE/BC_MODULE_INTERVAL];
	memset(memsize,0 ,sizeof(memsize));
	
	BC_PT_COMMAND(BC_MODULE_PLATFORM,"\r\n================================================================================================");
    BC_PT_COMMAND(BC_MODULE_PLATFORM,"\r\n%-8s %-8s %-16s %-8s %-8s %-8s %-30s ","Id","MODULEID","Index","Size","Result","Line","Func");
    BC_PT_COMMAND(BC_MODULE_PLATFORM,"\r\n------------------------------------------------------------------------------------------------");
	predecessor = utili_rbt_get_first(&bc_platform_mem_tree);
	while(predecessor != NULL)
	{
		data = &((mem_rbt_node_t *)predecessor)->data;
		memsize[data->module/BC_MODULE_INTERVAL] += data->size;
	
		BC_PT_COMMAND(BC_MODULE_PLATFORM,"\r\n%-8d %-8d %-16p %-8d %-8d %-8d %-30s",i,data->module,data->data,data->size,data->result,data->line,data->func);
		next = utili_rbt_get_next(&bc_platform_mem_tree,(utili_rbt_node_t *)predecessor);
		predecessor = next;
		i++;
	}
	
    BC_PT_COMMAND(BC_MODULE_PLATFORM,"\r\n%-8s %-10s","MODULEID","TOTAL-SIZE");
	for(i=0; i < BC_LAST_MODULE/BC_MODULE_INTERVAL; i++)
	{
		if(memsize[i] > 0)
		{
			BC_PT_COMMAND(BC_MODULE_PLATFORM,"\r\n%-8d %10dbytes",BC_MODULE_INTERVAL*i,memsize[i]);
		}
	}
	
#ifdef BC_MEM_ALLOC_MAX_SIZE
	BC_PT_COMMAND(BC_MODULE_PLATFORM,"\r\nmemory alloc total[COUNT:%u,USED:%0.1lfMB,MAX:%0.1lfMB]\n",bc_platform_mem_tree.count,(float)bc_mem_totalsize/1024/1024,(float)bc_mem_alloc_maxsize/1024/1024);
#else
	BC_PT_COMMAND(BC_MODULE_PLATFORM,"\r\nmemory alloc total[COUNT:%u,USED:%0.1lfMB]\n",bc_platform_mem_tree.count,(float)bc_mem_totalsize/1024/1024);
#endif

	return ;
}




