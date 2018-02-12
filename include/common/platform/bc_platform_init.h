#ifndef __BC_PLATFORM_INIT_H__
#define __BC_PLATFORM_INIT_H__
/************************************************************
  FileName:
  Author:  bain.wang@outlook.com      Version :  1.0        Date:2017-04-04
  Description:                平台结构初始化函数
  Version:                 1.0    
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/
#include "bc_platform_mem.h"
#include "bc_platform_mutex.h"
#include "bc_platform_thread.h"
#include "bc_platform_sem.h"
#include "bc_platform_time.h"
#include "bc_platform_queue.h"
#include "bc_platform_interrupt.h"
#include "bc_platform_dbg_trace.h"

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
extern void bc_platform_init(void);

#endif
