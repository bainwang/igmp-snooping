/*************************************************
  File name:      message_queue.h
  Author:  bain.wang@outlook.com     Version:  v1.0      Date: 2017-04-04
  Description:    Define internal interface and data structure of sys module
  Others:         none
  Function List:  none
  History:          
    1. Date: 2017-04-04
       Author: bain.wang@outlook.com       
       Modification: create
  
*************************************************/

#ifndef _BC_PLATFORM_MSGQUEUE_H_
#define _BC_PLATFORM_MSGQUEUE_H_

#include"bc_common_defs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include "bc_err.h"

/* message struct */
typedef struct {
	//bc_int32        messageid;       /*message id */
	bc_int32        data_size;       /*data size */
	void            *msg_data;       /*message data */
}bc_msg_member_t;


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
extern bc_err_e bc_platform_queue_init(void);

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
extern bc_err_e bc_platform_queue_create(bc_int32 *queueid, bc_char *queue_name, bc_int32 queue_size, bc_int32 pri_num);

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
extern bc_err_e bc_platform_queue_destroy(bc_int32 queueid);

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
extern bc_err_e bc_platform_queue_send(bc_int32 queueid, bc_int32 pri, void *data);

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
extern bc_err_e bc_platform_queue_recv(bc_int32 queueid, bc_int32 *data);

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
extern bc_err_e bc_platform_queue_count_get(bc_int32 *queue_count);

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
extern bc_err_e bc_platform_queue_node_count_get(bc_int32 queueid, bc_int32 *node_count);

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
extern void bc_platform_queue_lookup(bc_int32 queueid,bc_int32 prio,bc_int32 *prio_count);

/*************************************************
  Function: bc_platform_queue_show
  Description:dump所有队列的信息
  Input: 

  Output:
  		
  Return:

  Note: 用于debug，查看队列是否占满
  History: 
*************************************************/ 
extern void bc_platform_queue_show(void);

extern void bc_platform_queue_id_dump(bc_uint32 que_id);


#endif //_BC_PLATFORM_MSGQUEUE_H_
