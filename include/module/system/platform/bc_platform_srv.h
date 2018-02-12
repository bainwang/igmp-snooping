/************************************************************
  -------------------------------------------------------------------------
  FileName:bc_platform_srv.h
  Author:  bain.wang@outlook.com      Version :  1.0        Date:2016-6-9
  Description:    Platform debugging srv                
  Version:                        
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/
#ifndef _BC_PLATFORM_SRV_H_
#define _BC_PLATFORM_SRV_H_
#include "bc_common_defs.h"
#include "bc_ipc_def.h"
#include "bc_err.h"

#if 1

/*************************************************
  Function: bc_dev_thread_show_srv
  Description:dump���� �߳���Ϣ
  Input: 

  Output:
  Return:
		void
  Notes:
  History: 
*************************************************/
extern bc_err_e bc_dev_thread_show_srv(bc_ipc_package_t *data);

/*************************************************
  Function: bc_dev_timer_show_srv
  Description:dump ���ж�ʱ�������Ϣ
  Input: 
  
  Output:
  Return:
 		void
  Note: 
  History: 
*************************************************/
extern bc_err_e bc_dev_timer_show_srv(bc_ipc_package_t *data);

/*************************************************
  Function: bc_dev_sem_show_srv
  Description:dump�����ź�����״̬������������Ϣ
  Input:  
 		 
  Output:
  Return:
  		void
  Note: 
  History: 
*************************************************/
extern bc_err_e bc_dev_sem_show_srv(bc_ipc_package_t *data);

/*************************************************
  Function: bc_dev_mutex_show_srv
  Description:dump ���л�������״̬���Ƶ���Ϣ
  Input: 
  
  Output:
  Return:
		void
  Note: 
  History: 
*************************************************/
extern bc_err_e bc_dev_mutex_show_srv(bc_ipc_package_t *data);


/*************************************************
  Function: bc_dev_mem_show_srv
  Description:dump �����ڴ��������
  Input: 
	
  Output:
  Return:
  		void
  Note: 
  History: 
*************************************************/
extern bc_err_e bc_dev_mem_show_srv(bc_ipc_package_t *data);


/*************************************************
  Function: bc_dev_queue_show_srv
  Description:dump���ж��е���Ϣ
  Input: 

  Output:
  		
  Return:
 		
  Note: ����debug���鿴�����Ƿ�ռ��
  History: 
*************************************************/ 
extern bc_err_e bc_dev_queue_show_srv(bc_ipc_package_t *data);

extern bc_err_e bc_dev_queue_dump_single_srv(bc_ipc_package_t *data);

#endif


#endif //_BC_PLATFORM_SRV_H_
