/************************************************************
  Copyright (C), 1988-2014, xxxxx Tech. Co., Ltd.
  FileName:
  Author:  wangbin      Version :  1.0        Date:2014-2-8
  Description:         ��������غ���
  Version:                1.0     
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/

#ifndef _BC_PLATFORM_MUTEX_H
#define _BC_PLATFORM_MUTEX_H

#include <pthread.h>
#include "bc_platform_types.h"

#define BC_PLATFORM_MUTEX_DEBUG 

#define BC_MUTEX_MAX_API_NAME  30

typedef pthread_mutex_t bc_pthread_mutex_t;

/*************************************************
  Function: bc_platform_mutex_init
  Description:��ʼ���������ṹ
  Input: 
  		
  Output:
  Return:
  		void
  Note: ��bc_platform_init���bc_platform_mutex_init
  ����ƽ̨�ṹ�ĳ�ʼ��
  History: 
*************************************************/
extern void bc_platform_mutex_init(void);
/*************************************************
  Function: bc_platform_mutex_create
  Description:����������
  Input: 
  		name:����������
  		
  Output:
  Return:
  		�ɹ�:���ػ�����id
  		ʧ��:����NULL
  Note: 
  History: 
*************************************************/
extern bc_pthread_mutex_t *bc_platform_mutex_create(bc_char *name);

/*************************************************
  Function: bc_platform_mutex_destroy
  Description:ɾ��������
  Input: 
  		m:������id
  		
  Output:
  Return:
		�ɹ�:����BC_ERR_OK   ʧ��:other
  Note: 
  History: 
*************************************************/
extern bc_err_e bc_platform_mutex_destroy(bc_pthread_mutex_t *m);

/*************************************************
  Function: bc_platform_mutex_lock_ex
  Description:����������
  Input: 
  		m:������id
  		fun:��¼�����ĺ�����
  		line:��¼������λ��
  		
  Output:
  Return:
		bc_err_e
  Note: �ⲿ������ֱ��ʹ��bc_platform_mutex_lock
  ����궨��
  History: 
*************************************************/
extern bc_err_e bc_platform_mutex_lock_ex(bc_pthread_mutex_t *m,bc_char *func,bc_uint32 line);


/*************************************************
  Function: bc_platform_mutex_lock
  Description:����������
  Input: 
  		m:������id	
  Output:
  Return:
		�ɹ�:����BC_ERR_OK   ʧ��:other
  Note: �ⲿ������ֱ��ʹ��bc_platform_mutex_lock
  ����궨��
  History: 
*************************************************/
#define bc_platform_mutex_lock(m) \
	bc_platform_mutex_lock_ex(m,(bc_char *)__FUNCTION__,__LINE__)
	
/*************************************************
  Function: bc_platform_mutex_unlock
  Description:����������
  Input: 
  		m:������id
  		
  Output:
  Return:
		�ɹ�:����BC_ERR_OK   ʧ��:other
  Note: 
  History: 
*************************************************/
extern bc_err_e bc_platform_mutex_unlock(bc_pthread_mutex_t *m);

/*************************************************
  Function: bc_platform_mutex_statue_get
  Description:��ȡ��������״̬
  Input: 
  		m:������id
  		statue:o-lock,1-unlock
  		
  Output:
  Return:
		�ɹ�:����BC_ERR_OK   ʧ��:other
  Note: 
  History: 
*************************************************/
extern bc_err_e bc_platform_mutex_statue_get(bc_pthread_mutex_t *m, bc_uint8 *statue);

/*************************************************
  Function: bc_platform_mutex_name_statue_get
  Description:��ȡ��������״̬������
  Input: 
  		m:������id
  		name:����������
  		mutex_name_size:����������name ��ռ��С
  		statue:o-lock,1-unlock
  		
  Output:
  Return:
		�ɹ�:����BC_ERR_OK   ʧ��:other
  Note: 
  History: 
*************************************************/
extern bc_err_e bc_platform_mutex_name_statue_get(
	 bc_pthread_mutex_t *m, 
	 bc_int8 *name, 
	 bc_int32 mutex_name_size, 
	 bc_int32 *statue);

/*************************************************
  Function: bc_platform_mutex_show
  Description:dump ���л�������״̬���Ƶ���Ϣ
  Input: 
  
  Output:
  Return:
		void
  Note: 
  History: 
*************************************************/
extern void bc_platform_mutex_show(void);

#ifdef BC_PLATFORM_MUTEX_DEBUG
extern void bc_platform_mutex_ResourceUsageGet(unsigned int *mutex_curr, unsigned int *mutex_max);
#endif


#endif	//_BC_PLATFORM_MUTEX_H 

