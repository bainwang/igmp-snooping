/*************************************************
  Copyright (C), 2012-2020, xxxxx Tech. Co., Ltd.
  File name:      message_queue.c
  Author:  leijp     Version:  v1.0      Date: 2013/04/23
  Description:    Define some function about tx/rx packet for drv layer and bc_api layer.
  Others:         none
  Function List:  none
  History:          
    1. Date: 2013/04/23
       Author: leijp       
       Modification: create
  
*************************************************/

#include "bc_platform_queue.h"
#include "bc_platform_sem.h"
#include "bc_platform_mem.h"
#include "bc_platform_mutex.h"
#include "utili_list.h"
#include "bc_print.h"

#define MAX_QUEUE_NAME_LEN             32             //max queue name length
#define MAX_MSG_QUEUE_COUNTS           8              //max queue count  
#define MAX_MSG_PIR_QUEUE_COUNTS       8              //max queue pir count

/*queue_node*/
typedef struct bc_queue_node_s
{
	utili_node 	     utili_node;
	void             *data;     /*message member */
}bc_queue_node_t;


/* message queue*/
typedef struct {
    bc_int32 	     	id;                                     /*queue id*/ 
    bc_char 	     	name[MAX_QUEUE_NAME_LEN];               /*queue name*/
    bc_int32	     	queue_size;                             /*queue size*/
    bc_int32        	pri_num;                                /*pri num*/  
    bc_sem_t   	     	*queue_sem;                              /*queue sem */   
	bc_pthread_mutex_t  *queue_mutex;                            /*queue mutext*/ 
    utili_list 	        queue_list[MAX_MSG_PIR_QUEUE_COUNTS];   /*queue pri list */
    bc_pthread_mutex_t  *queue_list_mutex[MAX_MSG_PIR_QUEUE_COUNTS];  /*each mutex for each pri list */
    bc_int32 	    	current_num;                            /*current  node count */  
	bc_boolean       	is_used;                                /* if used*/      
}bc_msg_queue_t;


/*max message queue*/
bc_msg_queue_t  msg_queue[MAX_MSG_QUEUE_COUNTS];
/*queue operation mutext*/
static bc_pthread_mutex_t *msg_queue_mutext; 

/*************************************************
  Function: bc_platform_queue_init
  Description:初始化队列结构
  Input: 
  
  Output:
  Return:
 		成功:返回BC_ERR_OK   失败:other
  Note:用bc_platform_init替换bc_platform_queue_init进行初始化
  History: 
*************************************************/
bc_err_e bc_platform_queue_init(void)
{			
	bc_int32 i = 0;
	memset(msg_queue, 0, sizeof(msg_queue));
	for(i = 0; i < MAX_MSG_QUEUE_COUNTS; i++)
	{
		msg_queue[i].is_used = FALSE;
	}

    /* init queue operation mutex*/
	if((msg_queue_mutext = bc_platform_mutex_create("QueMutexStatic")) == NULL)
	{
		BC_PT_ERROR(BC_MODULE_PLATFORM,"<%s>:create mutex fail!\n",__FUNCTION__);
		return BC_ERR_PLATFROM_QUE_FAILED;
	}
	
	return BC_ERR_OK;
}

/*************************************************
  Function: bc_platform_queue_create
  Description:创建一个队列
  Input: 
  		queueid:队列id
  		queue_name:队列名称
  		queue_size:队列大小
  		pri_num:队列优先级个数
  
  Output:
  Return:
 		成功:返回BC_ERR_OK   失败:other
  Note: 
  History: 
*************************************************/
bc_err_e bc_platform_queue_create(
	bc_int32 *queueid,
	bc_char *queue_name,
	bc_int32 queue_size,
	bc_int32 pri_num
)
{
	/*get queue id*/
    bc_int32 i = 0;
	bc_int32 j = 0;
	bc_platform_mutex_lock(msg_queue_mutext);
	
	for(i = 0; i < MAX_MSG_QUEUE_COUNTS; i++)
	{
		if(msg_queue[i].is_used == FALSE)
		{
			/* init queue */
			*queueid = i;
			msg_queue[i].id = i;
			if(strlen(queue_name) >= MAX_QUEUE_NAME_LEN)
			{
				bc_platform_mutex_unlock(msg_queue_mutext);
				BC_PT_ERROR(BC_MODULE_PLATFORM,"message queue name is too length up to [%d]\r\n", strlen(queue_name));
				return BC_ERR_PARA;
			}
			strcpy(msg_queue[i].name, queue_name);
			msg_queue[i].queue_size = queue_size;
			msg_queue[i].pri_num = pri_num;
			msg_queue[i].current_num = 0;
			msg_queue[i].is_used = TRUE;

			/*init sem*/
			if((msg_queue[i].queue_sem = bc_platform_sem_create("BC_Queue_Sem",0))==NULL)
			{
				bc_platform_mutex_unlock(msg_queue_mutext);
				return BC_ERR_PLATFROM_QUE_FAILED;
			}
	
			/*init queue mutext*/
			if((msg_queue[i].queue_mutex = bc_platform_mutex_create("QueMutexInit")) == NULL)
			{
				bc_platform_mutex_unlock(msg_queue_mutext);
				BC_PT_ERROR(BC_MODULE_PLATFORM,"failed to init queue mutex\r\n");
				return BC_ERR_PLATFROM_QUE_FAILED;
			}
			
			/*init pri queue list and mutex */
			for(j = 0; j < pri_num; j++)
			{
			
				utili_lst_init(&msg_queue[i].queue_list[j],NULL);
				
                if((msg_queue[i].queue_list_mutex[j] = bc_platform_mutex_create("QueMutexList"))==NULL)
                {
					bc_platform_mutex_unlock(msg_queue_mutext);
					return BC_ERR_PLATFROM_QUE_FAILED;
				}
			}

			bc_platform_mutex_unlock(msg_queue_mutext);
			return BC_ERR_OK;
		}
	}

	bc_platform_mutex_unlock(msg_queue_mutext);
	BC_PT_ERROR(BC_MODULE_PLATFORM,"message queue is full\r\n");
	return BC_ERR_RESOURCE;
}

/*************************************************
  Function: bc_platform_queue_destroy
  Description:删除一个队列
  Input: 
  		queueid:队列id

  Output:
  Return:
 		成功:返回BC_ERR_OK   失败:other
  Note: 
  History: 
*************************************************/
bc_err_e bc_platform_queue_destroy(bc_int32 queueid)
{
	bc_int32 i = 0;
	
	if((queueid < 0)||(queueid > MAX_MSG_QUEUE_COUNTS))
	{
		return BC_ERR_PARA;
	}
	
	bc_platform_mutex_lock(msg_queue_mutext);

	if (msg_queue[queueid].current_num)
	{
		bc_platform_mutex_unlock(msg_queue_mutext);
		return BC_ERR_RESOURCE;
	}

	if(msg_queue[queueid].is_used == TRUE)
	{
		msg_queue[queueid].is_used = FALSE;
		/*release sem*/
		bc_platform_sem_destroy(msg_queue[queueid].queue_sem);

		/*release queue mutex*/
		bc_platform_mutex_destroy(msg_queue[queueid].queue_mutex);

		/*release queue list mutext*/  
        for(i = 0; i < msg_queue[queueid].pri_num; i++)
        {
			bc_platform_mutex_destroy(msg_queue[queueid].queue_list_mutex[i]);
        }
		msg_queue[queueid].current_num = 0;
	}

	bc_platform_mutex_unlock(msg_queue_mutext);
	
	return BC_ERR_OK;
}

/*************************************************
  Function: bc_platform_queue_send
  Description:发送一个队列消息
  Input: 
  		queueid:发送消息的队列id
  		pri:发送消息的队列优先级(数值越大优先级越高)
  		data:发送的消息指针

  Output:
  Return:
 		成功:返回BC_ERR_OK   失败:other
  Note: 1、data不能为局部变量，如果是动态分配，请在rev
  这个消息之后在处理函数中释放
  	    2、数值越大优先级越高
  History: 
*************************************************/
bc_err_e bc_platform_queue_send(
	bc_int32 queueid,
	bc_int32 pri,
	void *data
)
{
	bc_queue_node_t *node;
	/* queueid */
	if((queueid < 0)||(queueid > MAX_MSG_QUEUE_COUNTS))
	{
		BC_PT_ERROR(BC_MODULE_PLATFORM,"message queue id [%d] is error!\r\n", queueid);
		return BC_ERR_PARA;
	}
	
    if(msg_queue[queueid].is_used == FALSE)
    {
    	BC_PT_ERROR(BC_MODULE_PLATFORM,"message queue don't be create, queue id [%d]!\r\n", queueid);
    	return BC_ERR_RESOURCE;
    }

    /*pri*/
	if(pri > msg_queue[queueid].pri_num)
	{
		pri = msg_queue[queueid].pri_num;
	}
	else if(pri < 1)
	{
		pri = 1;
	}

	if(NULL == data)
	{
		BC_PT_ERROR(BC_MODULE_PLATFORM,"message param is error, point is NULL!\r\n");
		return BC_ERR_PARA;
	}

	/*queue is or not full*/	
	if(msg_queue[queueid].current_num >= msg_queue[queueid].queue_size)
	{
		BC_PT_ERROR(BC_MODULE_PLATFORM,"message queue member is full, queue id[%d]!\r\n", queueid);
		return BC_ERR_RESOURCE;
	}

	/*copy message member*/
    node = bc_platform_mem_malloc(BC_MODULE_PLATFORM, sizeof(bc_queue_node_t));
	if(node == NULL)
	{
		BC_PT_ERROR(BC_MODULE_PLATFORM,"message queue member alloc memory error, queue id[%d]!\r\n", queueid);
		return BC_ERR_RESOURCE;
	}
	
	memset(node, 0, sizeof(bc_queue_node_t));

	node->data = data;
	
	/*add message to queue*/
	bc_platform_mutex_lock(msg_queue[queueid].queue_list_mutex[pri-1]);
	
	utili_lst_add(&msg_queue[queueid].queue_list[pri-1],(utili_node *)node);
	
	bc_platform_mutex_unlock(msg_queue[queueid].queue_list_mutex[pri-1]);

    /*current node count ++*/
	bc_platform_mutex_lock(msg_queue[queueid].queue_mutex);
	msg_queue[queueid].current_num++;
	bc_platform_mutex_unlock(msg_queue[queueid].queue_mutex);

    /*post sem*/
	bc_platform_sem_post(msg_queue[queueid].queue_sem);

	return BC_ERR_OK;
}

/*************************************************
  Function: bc_platform_queue_recv
  Description:接收一个队列消息
  Input: 
  		queueid:队列id
  		
  Output:
  		data:返回data地址
  Return:
 		成功:返回BC_ERR_OK   失败:other
  Note: 如果data是send时动态分配的请在接收后释放data
  History: 
*************************************************/
bc_err_e bc_platform_queue_recv(bc_int32 queueid, bc_int32 *data)
{
	utili_node *first_node;
	bc_int32 i = 0; 
	/* queueid */
	if((queueid < 0)||(queueid > MAX_MSG_QUEUE_COUNTS))
	{
		BC_PT_ERROR(BC_MODULE_PLATFORM,"message queue id [%d] is error!\r\n", queueid);
		return BC_ERR_PARA;
	}
	
    if(msg_queue[queueid].is_used == FALSE)
    {
    	BC_PT_ERROR(BC_MODULE_PLATFORM,"message queue don't be create, queue id [%d]!\r\n", queueid);
    	return BC_ERR_RESOURCE;
    }

	/*wait sem*/
	bc_platform_sem_wait(msg_queue[queueid].queue_sem,BC_SEM_WAIT_FOREVER);
	
	for(i = (msg_queue[queueid].pri_num-1); i >= 0; i--)
	{
		first_node = utili_lst_first(&msg_queue[queueid].queue_list[i]);
		if(first_node != NULL)
		{
			
			bc_platform_mutex_lock(msg_queue[queueid].queue_list_mutex[i]);

			*data = (bc_int32)(((bc_queue_node_t *)first_node)->data);
			
			utili_lst_delete(&msg_queue[queueid].queue_list[i],(utili_node *)first_node);
	
			bc_platform_mem_free(BC_MODULE_PLATFORM,first_node);
			
			bc_platform_mutex_unlock(msg_queue[queueid].queue_list_mutex[i]);

			/*current node count --*/
			bc_platform_mutex_lock(msg_queue[queueid].queue_mutex);
			msg_queue[queueid].current_num--;
			bc_platform_mutex_unlock(msg_queue[queueid].queue_mutex);

			break;
		}
	}
	
	return BC_ERR_OK;
}

/*************************************************
  Function: bc_platform_queue_count_get
  Description:获取当前使用的队列数
  Input: 
  		queue_count:使用的队列数
  Output:
  		
  Return:
 		成功:返回BC_ERR_OK   失败:other
  Note: 队列的最大数MAX_MSG_QUEUE_COUNTS
  History: 
*************************************************/
bc_err_e bc_platform_queue_count_get(bc_int32 *queue_count)
{
    bc_int32 i = 0; 
	*queue_count = 0;
	for(i = 0; i < MAX_MSG_QUEUE_COUNTS; i++)
	{
		if(msg_queue[i].is_used == TRUE)
		{
			*queue_count = *queue_count + 1;
		}
	}
	
	return BC_ERR_OK;
}

/*************************************************
  Function: bc_platform_queue_node_count_get
  Description:获取一个队列当前使用的size
  Input: 
  		queue_count:使用的队列id
  		node_count:当前使用的队列节点数
  Output:
  		
  Return:
 		成功:返回BC_ERR_OK   失败:other
  Note: 
  History: 
*************************************************/
bc_err_e bc_platform_queue_node_count_get(bc_int32 queueid, bc_int32 *node_count)
{
	/* queueid */
	if((queueid < 0)||(queueid > MAX_MSG_QUEUE_COUNTS))
	{
		BC_PT_ERROR(BC_MODULE_PLATFORM,"message queue id [%d] is error!\r\n", queueid);
		return BC_ERR_PARA;
	}
	
    if(msg_queue[queueid].is_used == FALSE)
    {
    	*node_count = 0;
    }
	else
	{
		*node_count = msg_queue[queueid].current_num;
	}
	
	return BC_ERR_OK;
}

/*************************************************
  Function: bc_platform_queue_lookup
  Description:查询一个队列，在某个优先级
  下的节点个数
  Input: 
  		queueid:要查询的队列id
  		prio:查询的优先级
  		prio_count:返回该优先级下的节点数量

  Output:
  		
  Return:
 		成功:返回BC_ERR_OK   失败:other
  Note: 
  History: 
*************************************************/
void bc_platform_queue_lookup(bc_int32 queueid,bc_int32 prio,bc_int32 *prio_count)
{
	utili_node *predecessor,*next;
	bc_int32 node_count = 0;
	
	if(queueid >= MAX_MSG_QUEUE_COUNTS)
	{
		BC_PT_ERROR(BC_MODULE_PLATFORM,"err:queue id is out of range!!\n");
		return ;
	}

	if(msg_queue[queueid].is_used == FALSE)
	{
		BC_PT_ERROR(BC_MODULE_PLATFORM,"err:this queue  is disable!!\n");
		return ;	
	}
	
	node_count = 0;
	predecessor = utili_lst_first(&msg_queue[queueid].queue_list[prio-1]);
	while(predecessor != NULL)
	{
		node_count++;
		next = utili_lst_next((utili_node *)predecessor);
		predecessor = next;
	}
	*prio_count = node_count;
	
	return ;
}


/*************************************************
  Function: bc_platform_queue_show
  Description:dump所有队列的信息
  Input: 

  Output:
  		
  Return:
 		
  Note: 用于debug，查看队列是否占满
  History: 
*************************************************/ 
void bc_platform_queue_show(void)
{
	bc_uint32 i = 0;
	BC_PT_COMMAND(BC_MODULE_PLATFORM,"\r\n==============================================================================================");
    BC_PT_COMMAND(BC_MODULE_PLATFORM,"\r\n%-8s %-20s %-8s %-10s %-10s %-8s","QueueId","Name","ProNum","CurrSize", "MaxSize","Status");
    BC_PT_COMMAND(BC_MODULE_PLATFORM,"\r\n----------------------------------------------------------------------------------------------");
	for(i = 0; i < MAX_MSG_QUEUE_COUNTS; i++)
	{	
		if(msg_queue[i].is_used == TRUE)
		{
			BC_PT_COMMAND(BC_MODULE_PLATFORM,"\r\n%-8d %-20s %-8d %-10d %-10d %-8s",i,msg_queue[i].name,msg_queue[i].pri_num,msg_queue[i].current_num,msg_queue[i].queue_size,"Enable");
		}
		else
		{
			BC_PT_COMMAND(BC_MODULE_PLATFORM,"\r\n%-8d %-20s %-8s %-10s %-10s %-8s",i,"---","---","---","---","Disable");
		}
	}
	BC_PT_COMMAND(BC_MODULE_PLATFORM,"\n");
}


