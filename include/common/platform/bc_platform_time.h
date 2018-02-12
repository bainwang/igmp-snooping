/************************************************************
  FileName:
  Author:  bain.wang@outlook.com      Version :  1.0        Date:2017-04-04
  Description:   ��ʱ����ʱ����غ���                
  Version:      1.0                  
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/

#ifndef _BC_PLATFORM_TIME_H_
#define _BC_PLATFORM_TIME_H_

#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include "bc_platform_types.h"

/*
 * Constants
 */

#define MILLISECOND_USEC        (1000)
#define SECOND_USEC            	(1000000)
#define MINUTE_USEC           	(60 * SECOND_USEC)
#define HOUR_USEC            	(60 * MINUTE_USEC)

#define SECOND_MSEC            	(1000)
#define MINUTE_MSEC            	(60 * SECOND_MSEC)


#define BC_TIMER_MAX_API_NAME 30

typedef struct bc_loc_date_s
{
	int loc_sec;
	int loc_min;
	int loc_hour;
	int loc_mday;
	int loc_mon;
	int loc_year;
	int loc_wday;
}bc_loc_date_t;

typedef enum 
{
	BC_TIMER_NOCYCLE = 0,
	BC_TIMER_CYCLE   = 1
}bc_timer_type_t;

typedef timer_t bc_timer_t;
typedef void (*bc_timer_handle)(void *arg);


//��ȡʱ����
#define  BC_TIME_INTERVAL_GET(newtime,lasttime) (newtime-lasttime)
			

/*************************************************
  Function: bc_platform_time_date_get
  Description:��ȡʱ�����������ʱ����
  Input: 
  		date:����ʱ���ָ��
  Output:
  Return:
  		void
  Note: 
  History: 
*************************************************/
extern void bc_platform_time_date_get(bc_loc_date_t *date);

/*************************************************
  Function: bc_platform_time_sec_get
  Description:��ȡ��ǰʱ�䷵����
  Input: 
  		sec:����ʱ��ָ��
  Output:
  Return:
  		bc_err_e
  Note: 
  History: 
*************************************************/
extern bc_err_e bc_platform_time_sec_get(bc_uint32 *sec);

/*************************************************
  Function: bc_platform_time_us_get
  Description:��ȡ��ǰʱ�䷵��΢��
  Input: 
  		us:����ʱ��ָ��
  Output:
  Return:
  		�ɹ�:����BC_ERR_OK   ʧ��:other
  Note: 
  History: 
*************************************************/
extern bc_err_e bc_platform_time_us_get(bc_uint64 *us);

/*************************************************
  Function: bc_platform_time_date_str_get
  Description:��ȡ��ǰʱ�䷵���ַ����ṹ
  Input: 
  		str_date:����ʱ���ָ��
  		str_size:����ʱ��size
  Output:
  Return:
  		str_date ָ��
  Note: 
  History: 
*************************************************/
extern bc_char *bc_platform_time_date_str_get(bc_char *str_date,int str_size);

/*************************************************
  Function: bc_platform_time_init
  Description:��ʼ����ʱ������������
  Input: 
  
  Output:
  Return:
  		void
  Note: ��bc_platform_init���bc_platform_time_init���г�ʼ��
  History: 
*************************************************/
extern void bc_platform_time_init(void);

/*************************************************
  Function: bc_platform_timer_create
  Description:����һ����ʱ��
  Input: 
  		name:��ʱ������
  		func:callback function
  		arg:callback function �Ĳ���
  
  Output:
  Return:
  		�ɹ�:��ʱ��idָ��
  		ʧ��:NULL
  Note: ������ʱ������Ҫ����bc_platform_timer_start ��ʼ
  History: 
*************************************************/
extern bc_timer_t *bc_platform_timer_create(
	 bc_char *name,                 /*timer name*/
	 bc_timer_handle func,				/* callback function */
	 void				*arg				/* argument of callback */
);

/*************************************************
  Function: bc_platform_timer_start
  Description:��ʼһ���Ѵ����Ķ�ʱ��
  Input: 
  		timerid:��ʱ��id
  		initial_time:��ʱ����ʱʱ�䣬��λ΢��
  		Interval:BC_TIMER_NOCYCLE ���ζ�ʱ����BC_TIMER_CYCLE���ڶ�ʱ��
  
  Output:
  Return:
 		�ɹ�:����BC_ERR_OK   ʧ��:other
  Note: 
  History: 
*************************************************/
extern bc_err_e bc_platform_timer_start(
	 bc_timer_t *timerid,/*timer id*/
	 bc_uint32 initial_time,  /*Microsecond*/
	 bc_timer_type_t  Interval		/* Interval */
);

/*************************************************
  Function: bc_platform_timer_create_start
  Description:����һ����ʱ��������ʼ��ʱ
  Input: 
  		name:��ʱ������
  		func:callback function
  		arg:callback function �Ĳ���
  		initial_time:��ʱ����ʱʱ�䣬��λ΢��
  		Interval:BC_TIMER_NOCYCLE ���ζ�ʱ����BC_TIMER_CYCLE���ڶ�ʱ��
  
  Output:
  Return:
  		�ɹ�:��ʱ��idָ��
  		ʧ��:NULL
  Note: ������ʱ����ʼ����ʱ������Ҫ����bc_platform_timer_start
  History: 
*************************************************/
extern bc_timer_t *bc_platform_timer_create_start(
	 bc_char *name,                 /*timer name*/
	 bc_timer_handle func,		/* callback function */
	 void	*arg,/* argument of callback */
	 bc_uint32 initial_time,  /*Microsecond*/
	 bc_timer_type_t  Interval		/* Interval */
);

/*************************************************
  Function: bc_platform_timer_del
  Description:ɾ����ʱ��
  Input: 
  		timerid:��ʱ��idָ��
  Output:
  Return:
 		�ɹ�:����BC_ERR_OK   ʧ��:other
  Note: 
  History: 
*************************************************/
extern bc_err_e bc_platform_timer_del(bc_timer_t *timerid);

/*************************************************
  Function: bc_platform_timer_rem_get
  Description:��ȡ��ʱ����ʣ��ʱ��
  Input: 
  		timerid:��ʱ��idָ��
  		remtime:���ʣ��ʱ���ָ��
  Output:
  Return:
 		�ɹ�:����BC_ERR_OK   ʧ��:other
  Note: 
  History: 
*************************************************/
extern bc_err_e bc_platform_timer_rem_get(
	 bc_timer_t *timerid,
	 bc_uint32 *remtime);

/*************************************************
  Function: bc_platform_timer_show
  Description:dump ���ж�ʱ�������Ϣ
  Input: 
  
  Output:
  Return:
 		void
  Note: 
  History: 
*************************************************/
extern void bc_platform_timer_show(void);


#endif  //  _BC_PLATFORM_TIME_H_

