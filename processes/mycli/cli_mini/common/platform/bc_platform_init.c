/************************************************************
  Copyright (C), 1988-2014, xxxxx Tech. Co., Ltd.
  FileName:
  Author:  wangbin      Version :  1.0        Date:2014-2-8
  Description:      平台结构初始化函数             
  Version:        1.0                
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/
#include "bc_platform_init.h"

/*************************************************
  Function: bc_platform_init
  Description:平台结构初始化
  Input: 
  
  Output:
  Return:
  		void
  Note: 所有平台函数调用前都应该调用此接口
  进行 初始化
  History: 
*************************************************/
void bc_platform_init(void)
{
	static bc_boolean initialized = FALSE;
	
	if(initialized == FALSE)
	{
		bc_platform_mutex_init();
		bc_platform_mem_init();
		bc_platform_sem_init();
		bc_platform_thread_init();
		bc_platform_time_init();
		//bc_platform_queue_init();
		initialized = TRUE;
	}

}

