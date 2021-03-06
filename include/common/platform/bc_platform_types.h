/************************************************************
  FileName:
  Author:  bain.wang@outlook.com      Version :  1.0        Date:2017-04-04
  Description:                   
  Version:                        
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/
#ifndef _BC_PLATFORM_TYPES_H_
#define _BC_PLATFORM_TYPES_H_

#include "bc_common_defs.h"
#include "bc_err.h"

typedef bc_uint32    bc_vaddr_t;        /* Virtual address (Host address) */
#define BC_PTR_TO_INT(x)           ((bc_uint32)(x))
#define BC_PTR_HI_TO_INT(x)        (0)


#define BC_INT_TO_PTR(x)           ((void *)((bc_vaddr_t)(x)))

#define BC_PTR_TO_UINTPTR(x)       ((bc_vaddr_t)(x))
#define BC_UINTPTR_TO_PTR(x)       ((void *)(x))

#define BC_MAX_UINT_SPACE   0xfffffffa  

#if 0
	#define bc_platform_trace(msg...) printf(msg) 
#else
	#define bc_platform_trace(msg...) 
#endif



#endif    //_BC_PLATFORM_TYPES_H_
