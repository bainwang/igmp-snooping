/************************************************************
  Copyright (C), 1988-2014, xxxx Tech. Co., Ltd.
  FileName: proj_defs.h
  Author:  bain.wang@outlook.com      Version :  1.0        Date:2015-8-7
  Description: proj depend parameter define       
  Version:                        
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/

#ifndef __bc_proj_onumgmt_defs_h__
#define __bc_proj_onumgmt_defs_h__

#include "bc_common_defs.h"
#include "bc_modules.h"
#include "bc_print.h"
#include "bc_err.h"


/*---------- BC_MODULE_ONUMGMT START ----------*/
#define BC_ONU_MAX_OLT_PON_MAX_ONU_COUNTS      64        /*OLT PON端口最大ONU数    */ 
#define BC_ONU_MAX_ONU_UNI_PORT_COUNTS         4         /*每个ONU最大的uni口数 */

#define BC_ONU_MAX_ONU_COUNTS                  (BC_PORT_PON_MAX_COUNT * BC_ONU_MAX_OLT_PON_MAX_ONU_COUNTS)      /*最大ONU数  */ 
#define	BC_ONU_UNI_MAX_COUNT		           (BC_ONU_MAX_ONU_COUNTS*BC_ONU_MAX_ONU_UNI_PORT_COUNTS)

#define BC_ONU_ONU_ID_EXCURSION                1         /*ONU ID 与 数组索引号偏移 */

#define BC_ONU_PROFILE_NUM	256/*---------- BC_MODULE_ONUMGMT END ----------*/

#endif

