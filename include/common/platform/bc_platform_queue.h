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
  Description:��ʼ�����нṹ
  Input: 
  
  Output:
  Return:
 		�ɹ�:����BC_ERR_OK   ʧ��:other
  Note:��bc_platform_init�滻bc_platform_queue_init���г�ʼ��
  History: 
*************************************************/
extern bc_err_e bc_platform_queue_init(void);

/*************************************************
  Function: bc_platform_queue_create
  Description:����һ������
  Input: 
  		queueid:����id
  		queue_name:��������
  		queue_size:���д�С
  		pri_num:�������ȼ�����
  
  Output:
  Return:
 		�ɹ�:����BC_ERR_OK   ʧ��:other
  Note: 
  History: 
*************************************************/
extern bc_err_e bc_platform_queue_create(bc_int32 *queueid, bc_char *queue_name, bc_int32 queue_size, bc_int32 pri_num);

/*************************************************
  Function: bc_platform_queue_destroy
  Description:ɾ��һ������
  Input: 
  		queueid:����id

  Output:
  Return:
 		�ɹ�:����BC_ERR_OK   ʧ��:other
  Note: 
  History: 
*************************************************/
extern bc_err_e bc_platform_queue_destroy(bc_int32 queueid);

/*************************************************
  Function: bc_platform_queue_send
  Description:����һ��������Ϣ
  Input: 
  		queueid:������Ϣ�Ķ���id
  		pri:������Ϣ�Ķ������ȼ�(��ֵԽ�����ȼ�Խ��)
  		data:���͵���Ϣָ��

  Output:
  Return:
 		�ɹ�:����BC_ERR_OK   ʧ��:other
  Note: 1��data����Ϊ�ֲ�����������Ƕ�̬���䣬����rev
  �����Ϣ֮���ڴ��������ͷ�
  	    2����ֵԽ�����ȼ�Խ��
  History: 
*************************************************/
extern bc_err_e bc_platform_queue_send(bc_int32 queueid, bc_int32 pri, void *data);

/*************************************************
  Function: bc_platform_queue_recv
  Description:����һ��������Ϣ
  Input: 
  		queueid:����id
  		
  Output:
  		data:����data��ַ
  Return:
 		�ɹ�:����BC_ERR_OK   ʧ��:other
  Note: ���data��sendʱ��̬��������ڽ��պ��ͷ�data
  History: 
*************************************************/
extern bc_err_e bc_platform_queue_recv(bc_int32 queueid, bc_int32 *data);

/*************************************************
  Function: bc_platform_queue_count_get
  Description:��ȡ��ǰʹ�õĶ�����
  Input: 
  		queue_count:ʹ�õĶ�����
  Output:
  		
  Return:
 		�ɹ�:����BC_ERR_OK   ʧ��:other
  Note: ���е������MAX_MSG_QUEUE_COUNTS
  History: 
*************************************************/
extern bc_err_e bc_platform_queue_count_get(bc_int32 *queue_count);

/*************************************************
  Function: bc_platform_queue_node_count_get
  Description:��ȡһ�����е�ǰʹ�õ�size
  Input: 
  		queue_count:ʹ�õĶ���id
  		node_count:��ǰʹ�õĶ��нڵ���
  Output:
  		
  Return:
 		�ɹ�:����BC_ERR_OK   ʧ��:other
  Note: 
  History: 
*************************************************/ 
extern bc_err_e bc_platform_queue_node_count_get(bc_int32 queueid, bc_int32 *node_count);

/*************************************************
  Function: bc_platform_queue_lookup
  Description:��ѯһ�����У���ĳ�����ȼ�
  �µĽڵ����
  Input: 
  		queueid:Ҫ��ѯ�Ķ���id
  		prio:��ѯ�����ȼ�
  		prio_count:���ظ����ȼ��µĽڵ�����

  Output:
  		
  Return:
 		�ɹ�:����BC_ERR_OK   ʧ��:other
  Note: 
  History: 
*************************************************/ 
extern void bc_platform_queue_lookup(bc_int32 queueid,bc_int32 prio,bc_int32 *prio_count);

/*************************************************
  Function: bc_platform_queue_show
  Description:dump���ж��е���Ϣ
  Input: 

  Output:
  		
  Return:

  Note: ����debug���鿴�����Ƿ�ռ��
  History: 
*************************************************/ 
extern void bc_platform_queue_show(void);

extern void bc_platform_queue_id_dump(bc_uint32 que_id);


#endif //_BC_PLATFORM_MSGQUEUE_H_
