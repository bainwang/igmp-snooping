/************************************************************
  -------------------------------------------------------------------------
  FileName:bc_system_clock_srv.h
  Author:  bain.wang@outlook.com      Version :  1.0        Date:2016-6-9
  Description:  The system clock srv                  
  Version:                        
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/
#ifndef _BC_CLOCK_SRV_H_
#define _BC_CLOCK_SRV_H_
#include "bc_err.h"
#include "bc_ipc_def.h"
#include "bc_common_defs.h"

/*************************************************
  Function: bc_clock_init 
  Description: 初始化系统时钟
  Input: 
  		NULL
  Output:
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
extern bc_err_e bc_clock_init();

/*************************************************
  Function: bc_clock_save_configure 
  Description: 全局模式下保存olt 的时区信息
  Input: 
  		NULL
  Output:
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
extern bc_err_e bc_clock_save_configure(bc_char *cmd_buf, bc_uint32 cmd_len, bc_int32 *buf_len, void *cfg_data);


/*************************************************
  Function: bc_clock_date_set_srv
  Description:set system clock srv
  Input: 
		tmtime:To set the time
  Output:
  Return:
		Success:BC_ERR_OK,Failure:other
  Notes:
  History: 
*************************************************/
extern bc_err_e bc_clock_date_set_srv(bc_ipc_package_t *data);

/*************************************************
  Function: bc_clock_date_get_srv
  Description:get set system clock srv
  Input: 
  		tmtime:Save the time pointer
  Output:
  Return:
 		Success:BC_ERR_OK,Failure:other
  Note: 
  History: 
*************************************************/
extern bc_err_e bc_clock_date_get_srv(bc_ipc_package_t *data);

/*************************************************
  Function: bc_clock_tz_set_srv
  Description: set system clock Time zone srv
  Input: 
  		data:ipc data
  Output:
  Return:
 		Success:BC_ERR_OK,Failure:other
  Note: 
  History: 
*************************************************/
extern bc_err_e bc_clock_tz_set_srv(bc_ipc_package_t *data);

/*************************************************
  Function: bc_clock_tz_get_srv
  Description:get  system clock Time zone srv 
  Input: 
  		data:ipc data
  Output:
  Return:
 		Success:BC_ERR_OK,Failure:other
  Note: 
  History: 
*************************************************/
extern bc_err_e bc_clock_tz_get_srv(bc_ipc_package_t *data);

#endif //_BC_CLOCK_SRV_H_

