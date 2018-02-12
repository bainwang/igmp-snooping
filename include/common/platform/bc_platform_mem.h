/************************************************************
  FileName:
  Author:  bain.wang@outlook.com      Version :  1.0        Date:2017-04-04
  Description:         �ڴ���亯��
  Version:     1.0                
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/

#ifndef _BC_PLATFORM_MEM_H_
#define _BC_PLATFORM_MEM_H_

#include "bc_common_defs.h"
#include "bc_modules.h"


#ifdef _MEM_POOL_







#else
extern void bc_platform_mem_init_ex(void);

extern void *bc_platform_mem_malloc_ex(
	bc_modules_e module,
	bc_char *func,
	bc_uint32 line,
	bc_uint32  size
);

extern void bc_platform_mem_free_ex(
	bc_modules_e module,
	bc_char  *func,
	bc_uint32 line,
	void *p
);


/*************************************************
  Function: bc_platform_mem_init_ex
  Description:��ʼ���ڴ������ؽṹ
  Input: 
  		
  Output:
  Return:
  		void
  Note: ��bc_platform_init���bc_platform_mem_init
  ����ƽ̨�ṹ�ĳ�ʼ��
  History: 
*************************************************/
#define bc_platform_mem_init()  bc_platform_mem_init_ex()

/*************************************************
  Function: bc_platform_mem_set_maxsize
  Description:����ÿ�������ڴ��������ֵ
  Input: 
  		maxsize:ÿ�������ڴ��������ֵ��
  		��λ�ֽ�
  		
  Output:
  Return:
  		void
  Note: Ĭ��ֵ:5*1024*1024
  History: 
*************************************************/
extern void bc_platform_mem_set_maxsize(bc_uint64 maxsize);

/*************************************************
  Function: bc_platform_mem_malloc
  Description:���亯��
  Input: 
  		module:ģ��id
  		func:��¼���÷��亯���ĺ�����
  		line:��¼����λ��
  		size:����Ŀռ��С
  		
  Output:
  Return:
  		�ɹ�:���� ָ����������ڴ浥Ԫ��ָ��
  		ʧ��:����NULL
  Note: �ⲿ������ʹ�ú�bc_platform_mem_malloc
  History: 
*************************************************/
#define  bc_platform_mem_malloc(module_id,size) \
	bc_platform_mem_malloc_ex(module_id,(bc_char *)__FUNCTION__,(bc_uint32)__LINE__,size)

/*************************************************
  Function: bc_platform_mem_free
  Description:�ͷ��ڴ溯��
  Input: 
  		module:ģ��id
  		func:��¼���÷��亯���ĺ�����
  		line:��¼����λ��
  		p:�ͷŵĵ�ַָ��
  		
  Output:
  Return:
  		void
  Note: �ⲿ������ʹ�ú�bc_platform_mem_free
  History: 
*************************************************/	
#define  bc_platform_mem_free(module_id,ptr) \
	bc_platform_mem_free_ex(module_id,(bc_char *)__FUNCTION__,(bc_uint32)__LINE__,ptr)
	
/*************************************************
  Function: bc_platform_mem_show
  Description:dump �����ڴ��������
  Input: 
	
  Output:
  Return:
  		void
  Note: 
  History: 
*************************************************/
extern void bc_platform_mem_show(void);

#endif




#endif //_BC_PLATFORM_MEM_H_

