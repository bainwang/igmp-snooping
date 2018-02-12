/************************************************************
  Copyright (C), 1988-2014, xxxxx Tech. Co., Ltd.
  FileName:
  Author:  wangbin      Version :  1.0        Date:2014-2-8
  Description:   ��ʱ����ʱ����غ���                
  Version:      1.0                  
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/
#include "bc_platform_mem.h"
#include "bc_platform_time.h"
#include "bc_platform_mutex.h"
#include "bc_print.h"
#include "utili_list.h"

typedef struct  bc_timer_arg_s
{
	bc_timer_handle handle;
	void *arg;
}bc_timer_arg_t;


typedef struct bc_timer_info_s
{
	bc_timer_t timerid;
	bc_char name[BC_TIMER_MAX_API_NAME];
	bc_timer_arg_t timerarg;
}bc_timer_info_t;

typedef struct 
{
	utili_node 	     utili_node;
	bc_timer_info_t	 data;        
} bc_timer_node_t;


static utili_list bc_platform_timer_head;
static bc_pthread_mutex_t *bc_platform_timer_mut;

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
void bc_platform_time_date_get(bc_loc_date_t *date)
{
	time_t timep;
	
	struct tm *p;
	
	time(&timep);
	
	p = localtime(&timep); 

	date->loc_year = p->tm_year + 1900;
	date->loc_mon  = p->tm_mon + 1;
	date->loc_mday = p->tm_mday;
	date->loc_hour = p->tm_hour;
	date->loc_min  = p->tm_min;
	date->loc_sec  = p->tm_sec;
	date->loc_wday = p->tm_wday;
}

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
bc_err_e bc_platform_time_us_get(bc_uint64 *us)
{
    struct timeval	tv;
	
    if(gettimeofday(&tv, 0))
    {
    	return BC_ERR_RESOURCE;
    }
	
    *us = ((bc_uint64)tv.tv_sec)*1000000 + (bc_uint64)tv.tv_usec;
	
	return BC_ERR_OK;
}

/*************************************************
  Function: bc_platform_time_sec_get
  Description:��ȡ��ǰʱ�䷵����
  Input: 
  		sec:����ʱ��ָ��
  Output:
  Return:
  		�ɹ�:����BC_ERR_OK   ʧ��:other
  Note: 
  History: 
*************************************************/
bc_err_e bc_platform_time_sec_get(bc_uint32 *sec)
{
	bc_uint32 seconds;
	seconds = time((time_t *)NULL);

	if(seconds != ((time_t)-1))
	{
		*sec = seconds; 
		return BC_ERR_OK;
	}

	return BC_ERR_RESOURCE;
}

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
bc_char *bc_platform_time_date_str_get(bc_char *str_date,int str_size)
{
	bc_char *date = NULL;

	bc_int32 size;
	
	time_t timep;
	
	time(&timep);
	
	date = asctime(localtime(&timep));

	//ȥ�����һ�����з�'\n'
	if(date[strlen(date)-1] == '\n')
	{
		date[strlen(date)-1] = '\0';
	}
	
	size = strlen(date) > str_size ? str_size:strlen(date);
		
	strncpy(str_date,date,size);

	return str_date;
}



static void bc_platform_time_TimerBoot(union sigval v)
{
	bc_timer_arg_t *tv = (bc_timer_arg_t *)(v.sival_ptr);
	//printf("<2.ti:%p,handle:%p,arg:%p,handle:%p,arg:%p>\n",tv,tv->handle,tv->arg,ti->handle,ti->arg);
	if(tv->handle != NULL)
	{
		tv->handle(tv->arg);
	}
}


static bc_int32 __bc_platform_timer_compare(void * node, bc_uint32 key)
{

	bc_timer_info_t *ti = &((bc_timer_node_t *)node)->data;
	bc_int32 ret = 0;
	
	if((bc_uint32)&ti->timerid == key)
	{
		ret = 0;
	}
	else //if(&ti->id != key)
	{
		ret = -1;
	}
	
	//bc_platform_trace("<%s-%d>:ti->id:%p,key:%p,name:%s,ret=%d\n",__FUNCTION__,__LINE__,&ti->id,(bc_sem_t *)key,ti->name,ret);
	
	return ret;
}

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
void bc_platform_time_init(void)
{
	if((bc_platform_timer_mut = bc_platform_mutex_create("TimerMutex1")) == NULL)
	{
		BC_PT_ERROR(BC_MODULE_PLATFORM, "<%s>:create mutex 1 fail!\n",__FUNCTION__);
		return ;
	}
	
	utili_lst_init(&bc_platform_timer_head,__bc_platform_timer_compare);
}

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
bc_timer_t *bc_platform_timer_create(
	 bc_char *name,                 /*timer name*/
	 bc_timer_handle func,				/* callback function */
	 void				*arg				/* argument of callback */
	)
{
	bc_timer_info_t *ti;
	bc_timer_node_t *timer_node;
	clockid_t clock_id = CLOCK_REALTIME;
	struct sigevent evp;

	if(NULL == name||NULL == func)
	{
		return NULL;
	}

	if(strlen(name) >= BC_TIMER_MAX_API_NAME)
	{
		BC_PT_ERROR(BC_MODULE_PLATFORM, "timer name is too long ....\n");
		return NULL;
	}
	
	memset(&evp, 0, sizeof(struct sigevent)); 

    if ((timer_node = bc_platform_mem_malloc(BC_MODULE_PLATFORM,sizeof(bc_timer_node_t))) == NULL)
	{
		return NULL;
    }	
	ti = &timer_node->data;
	strcpy(ti->name,name);
	ti->timerarg.handle = func;
	ti->timerarg.arg = arg;
	
	evp.sigev_value.sival_ptr = &ti->timerarg; 
    evp.sigev_notify = SIGEV_THREAD;            
    evp.sigev_notify_function = bc_platform_time_TimerBoot; 
	
   	//printf("<1.ti:%p,handle:%p,arg:%p,handle:%p,arg:%p>\n",ti,func,arg,ti->handle,ti->arg);
   	
	if(timer_create(clock_id, &evp,&(ti->timerid)) == -1)
	{
		perror("\r\n fail to timer create");  
		return NULL;
	}
	
	bc_platform_mutex_lock(bc_platform_timer_mut);
	utili_lst_add(&bc_platform_timer_head,(utili_node *)timer_node);
	bc_platform_mutex_unlock(bc_platform_timer_mut);
	
	return (bc_timer_t *)&ti->timerid;
}


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
bc_err_e bc_platform_timer_start(
	 bc_timer_t *timerid,/*timer id*/
	 bc_uint32 initial_time,  /*Microsecond*/
	 bc_timer_type_t  Interval		/* Interval */
)
{
	struct itimerspec it; 

	if(Interval == BC_TIMER_NOCYCLE)
	{
		it.it_interval.tv_sec = 0;   
		it.it_interval.tv_nsec = 0; 
	}
	else
	{
		it.it_interval.tv_sec = (time_t)(initial_time / SECOND_USEC);   
		it.it_interval.tv_nsec = (long) (initial_time % SECOND_USEC); 
	}
	
	it.it_value.tv_sec = (time_t)(initial_time / SECOND_USEC);   
	it.it_value.tv_nsec = (long) (initial_time % SECOND_USEC);
	
	if (timer_settime(*timerid, 0, &it, NULL) == -1)
	{   
		perror("\r\n fail to timer_settime");   
		return  BC_ERR_PARA; 
	}
	
	return BC_ERR_OK;
}

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
bc_timer_t *bc_platform_timer_create_start(
	 bc_char *name,                 /*timer name*/
	 bc_timer_handle func,		/* callback function */
	 void	*arg,/* argument of callback */
	 bc_uint32 initial_time,  /*Microsecond*/
	 bc_timer_type_t  Interval		/* Interval */
)
{
	bc_timer_info_t *ti;
	bc_timer_node_t *timer_node;
	struct itimerspec it;
	clockid_t clock_id = CLOCK_REALTIME;
	struct sigevent evp;

	if(NULL == name||NULL == func)
	{
		return NULL;
	}

	if(strlen(name) >= BC_TIMER_MAX_API_NAME)
	{
		BC_PT_ERROR(BC_MODULE_PLATFORM,"timer name is too long ....\n");
		return NULL;
	}
	
	memset(&evp, 0, sizeof(struct sigevent)); 

    if ((timer_node = bc_platform_mem_malloc(BC_MODULE_PLATFORM,sizeof(bc_timer_node_t))) == NULL)
	{
		return NULL;
    }

	ti = &timer_node->data;
	strcpy(ti->name,name);
	ti->timerarg.handle = func;
	ti->timerarg.arg = arg;
	
	evp.sigev_value.sival_ptr = &ti->timerarg; 
    evp.sigev_notify = SIGEV_THREAD;            
    evp.sigev_notify_function = bc_platform_time_TimerBoot; 
	
   	//printf("<1.ti:%p,handle:%p,arg:%p,handle:%p,arg:%p>\n",ti,func,arg,ti->handle,ti->arg);
   	
	if(timer_create(clock_id, &evp,&(ti->timerid)) == -1)
	{
		bc_platform_mem_free(BC_MODULE_PLATFORM,timer_node);
		perror("\r\n fail to timer create");
		return NULL;
	}
	
	bc_platform_mutex_lock(bc_platform_timer_mut);
	utili_lst_add(&bc_platform_timer_head,(utili_node *)timer_node);
	bc_platform_mutex_unlock(bc_platform_timer_mut);
	
	if(Interval == BC_TIMER_NOCYCLE)
	{
		it.it_interval.tv_sec = 0;   
		it.it_interval.tv_nsec = 0; 
	}
	else
	{
		it.it_interval.tv_sec = (time_t)(initial_time / SECOND_USEC);   
		it.it_interval.tv_nsec = (long) (initial_time % SECOND_USEC); 
	}
	
	it.it_value.tv_sec = (time_t)(initial_time / SECOND_USEC);   
	it.it_value.tv_nsec = (long) (initial_time % SECOND_USEC);
	
	if (timer_settime(ti->timerid, 0, &it, NULL) == -1)
	{   
	 	utili_lst_delete(&bc_platform_timer_head, (utili_node *)timer_node);
		bc_platform_mem_free(BC_MODULE_PLATFORM,timer_node);
		perror("\r\n fail to timer_settime"); 
		return  NULL; 
	}
	
	return (bc_timer_t *)&ti->timerid;

}


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
bc_err_e bc_platform_timer_del(bc_timer_t *timerid)
{

    utili_node *node;
	
	bc_platform_mutex_lock(bc_platform_timer_mut);
	if(timer_delete(*timerid) == -1)
	{
		perror("\r\n fail to timer del"); 
		bc_platform_mutex_unlock(bc_platform_timer_mut);
		return  BC_ERR_PARA; 
	}
	node = utili_lst_find(&bc_platform_timer_head,(unsigned int)timerid);
	if(node == NULL)
	{
		BC_PT_ERROR(BC_MODULE_PLATFORM,"%s-%d\n",__FUNCTION__,__LINE__);
		bc_platform_mutex_unlock(bc_platform_timer_mut);
		return BC_ERR_PLATFROM_SEM_NOT_EXIST;
	}
	utili_lst_delete(&bc_platform_timer_head,node);
	bc_platform_mem_free(BC_MODULE_PLATFORM,node);
	
	bc_platform_mutex_unlock(bc_platform_timer_mut);
	
	return BC_ERR_OK;
}

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
bc_err_e bc_platform_timer_rem_get(bc_timer_t *timerid, bc_uint32 *remtime)
{
	struct itimerspec value; 
	memset(&value,0,sizeof(value));
	
	if(timer_gettime(*timerid,&value) == -1)
	{
		perror("\r\n fail to timer del");   
		return  BC_ERR_PARA; 
	}

	*remtime = SECOND_USEC*value.it_value.tv_sec + value.it_value.tv_nsec/1000000000;
	
	return BC_ERR_OK;
}

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
void bc_platform_timer_show(void)
{
 	bc_uint32 count = 1;
	utili_node *predecessor,*next;
	bc_timer_info_t *ti;
    BC_PT_COMMAND(BC_MODULE_PLATFORM, "\r\n=============================================================");
    BC_PT_COMMAND(BC_MODULE_PLATFORM, "\r\n%-4s %-20s %-11s","Id", "TIMER", "FUNC");
    BC_PT_COMMAND(BC_MODULE_PLATFORM, "\r\n-------------------------------------------------------------");

	predecessor = utili_lst_first(&bc_platform_timer_head);
	while(predecessor != NULL)
	{
		ti = &((bc_timer_node_t *)predecessor)->data;
		BC_PT_COMMAND(BC_MODULE_PLATFORM, "\r\n%-4d %-20s %p",count++,ti->name,ti->timerarg.handle);
		next = utili_lst_next((utili_node *)predecessor);
		predecessor = next;
	}
	BC_PT_COMMAND(BC_MODULE_PLATFORM, "\r\nTIMER COUNT:%d\n",bc_platform_timer_head.count);
}

