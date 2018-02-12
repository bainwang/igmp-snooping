/************************************************************
  FileName: proj_defs.h
  Author:  bain.wang@outlook.com      Version :  1.0        Date:2017-04-04
  Description: proj depend parameter define       
  Version:                        
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/

#ifndef __bc_proj_platform_defs_h__
#define __bc_proj_platform_defs_h__

#include "bc_common_defs.h"
#include "bc_modules.h"
#include "bc_print.h"
#include "bc_err.h"

/*---------- BC_MODULE_PLATFORM START ----------*/

#define BC_PLATFORM_MEM_MAX 10240
#define BC_PLATFORM_MUTEX_MAX 1024
#define BC_PLATFORM_SEM_MAX 1024
#define BC_PLATFORM_THREAD_MAX 128
#define BC_PLATFORM_TIMER_MAX 128

#define BC_PLATFORM_INTERRUPT_NUM_MAX     		128
#define BC_PLATFORM_INTERRUPT_FUNC_NODE_NUM	6
#define BC_PLATFORM_INTERRUPT_FUNC_NODE_MAX	(BC_PLATFORM_INTERRUPT_NUM_MAX * BC_PLATFORM_INTERRUPT_FUNC_NODE_NUM)

/*---------- BC_MODULE_PLATFORM END ----------*/

#endif

