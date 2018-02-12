/************************************************************
  FileName:
  Author:  bain.wang@outlook.com      Version :  1.0        Date:2017-04-04
  Description:   定时器和时间相关函数                
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


//获取时间间隔
#define  BC_TIME_INTERVAL_GET(newtime,lasttime) (newtime-lasttime)
			

/*************************************************
  Function: bc_platform_time_date_get
  Description:获取时间包括年月日时分秒
  Input: 
  		date:保存时间的指针
  Output:
  Return:
  		void
  Note: 
  History: 
*************************************************/
extern void bc_platform_time_date_get(bc_loc_date_t *date);

/*************************************************
  Function: bc_platform_time_sec_get
  Description:获取当前时间返回秒
  Input: 
  		sec:保存时间指针
  Output:
  Return:
  		bc_err_e
  Note: 
  History: 
*************************************************/
extern bc_err_e bc_platform_time_sec_get(bc_uint32 *sec);

/*************************************************
  Function: bc_platform_time_us_get
  Description:获取当前时间返回微妙
  Input: 
  		us:保存时间指针
  Output:
  Return:
  		成功:返回BC_ERR_OK   失败:other
  Note: 
  History: 
*************************************************/
extern bc_err_e bc_platform_time_us_get(bc_uint64 *us);

/*************************************************
  Function: bc_platform_time_date_str_get
  Description:获取当前时间返回字符串结构
  Input: 
  		str_date:保存时间的指针
  		str_size:保存时间size
  Output:
  Return:
  		str_date 指针
  Note: 
  History: 
*************************************************/
extern bc_char *bc_platform_time_date_str_get(bc_char *str_date,int str_size);

/*************************************************
  Function: bc_platform_time_init
  Description:初始化定时器，创建链表
  Input: 
  
  Output:
  Return:
  		void
  Note: 用bc_platform_init替代bc_platform_time_init进行初始化
  History: 
*************************************************/
extern void bc_platform_time_init(void);

/*************************************************
  Function: bc_platform_timer_create
  Description:创建一个定时器
  Input: 
  		name:定时器名称
  		func:callback function
  		arg:callback function 的参数
  
  Output:
  Return:
  		成功:定时器id指针
  		失败:NULL
  Note: 创建定时器后，需要调用bc_platform_timer_start 开始
  History: 
*************************************************/
extern bc_timer_t *bc_platform_timer_create(
	 bc_char *name,                 /*timer name*/
	 bc_timer_handle func,				/* callback function */
	 void				*arg				/* argument of callback */
);

/*************************************************
  Function: bc_platform_timer_start
  Description:开始一个已创建的定时器
  Input: 
  		timerid:定时器id
  		initial_time:定时器超时时间，单位微妙
  		Interval:BC_TIMER_NOCYCLE 单次定时器，BC_TIMER_CYCLE周期定时器
  
  Output:
  Return:
 		成功:返回BC_ERR_OK   失败:other
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
  Description:创建一个定时器，并开始计时
  Input: 
  		name:定时器名称
  		func:callback function
  		arg:callback function 的参数
  		initial_time:定时器超时时间，单位微妙
  		Interval:BC_TIMER_NOCYCLE 单次定时器，BC_TIMER_CYCLE周期定时器
  
  Output:
  Return:
  		成功:定时器id指针
  		失败:NULL
  Note: 创建定时器后开始倒计时，不需要调用bc_platform_timer_start
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
  Description:删除定时器
  Input: 
  		timerid:定时器id指针
  Output:
  Return:
 		成功:返回BC_ERR_OK   失败:other
  Note: 
  History: 
*************************************************/
extern bc_err_e bc_platform_timer_del(bc_timer_t *timerid);

/*************************************************
  Function: bc_platform_timer_rem_get
  Description:获取定时器的剩余时间
  Input: 
  		timerid:定时器id指针
  		remtime:存放剩余时间的指针
  Output:
  Return:
 		成功:返回BC_ERR_OK   失败:other
  Note: 
  History: 
*************************************************/
extern bc_err_e bc_platform_timer_rem_get(
	 bc_timer_t *timerid,
	 bc_uint32 *remtime);

/*************************************************
  Function: bc_platform_timer_show
  Description:dump 所有定时器相关信息
  Input: 
  
  Output:
  Return:
 		void
  Note: 
  History: 
*************************************************/
extern void bc_platform_timer_show(void);


#endif  //  _BC_PLATFORM_TIME_H_

