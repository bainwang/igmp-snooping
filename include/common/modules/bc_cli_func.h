/************************************************************
  -------------------------------------------------------------------------
  FileName:
  Author:  bain.wang@outlook.com      Version :  1.0        Date:2016-4-22
  Description:                   
  Version:                        
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/

#ifndef __bc_cli_func_h__
#define __bc_cli_func_h__

#include "bc_common_defs.h"
#include "bc_modules.h"
#include "bc_proj_defs.h"
#include "bc_ipc_def.h"

#if 1

#define BC_CLI_FUNC_CLI_TEMPLATE \
    __bc_func_cli_start_tmplate(BC_MODULE_CLI) \
	__bc_func_cli_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_cli_ipc_msg_recv) \


#endif
#if 1

#undef __bc_func_cli_start_tmplate
#define __bc_func_cli_start_tmplate(module_id) module_id##_e = module_id,

#undef __bc_func_cli_srv_temp
#define __bc_func_cli_srv_temp(sync, slave, func) func##_e,

#define BC_FUNC_CLI_ENUM(func) func##_e

typedef enum {
	BC_CLI_FUNC_CLI_TEMPLATE
} bc_func_cli_e;

#undef __bc_func_cli_start_tmplate
#undef __bc_func_cli_srv_temp

#endif
#endif

