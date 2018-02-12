/************************************************************
  FileName:
  Author:  bain.wang@outlook.com      Version :  1.0        Date:2016-10-10
  Description:                   
  Version:                        
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/

#ifndef __BC_SYS_H__
#define __BC_SYS_H__


#include "bc_sys_defs.h"

#if 1



/*************************************************
  Function: bc_sys_ipc_event_dbg_dump
  Description: get system event info
  Input: 
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
extern bc_err_e bc_sys_ipc_event_dbg_dump(void);


/*************************************************
  Function: bc_sys_ipc_polling_dbg_dump
  Description: get system polling info
  Input: 
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
extern bc_err_e bc_sys_ipc_polling_dbg_dump(void);

extern bc_err_e bc_sys_ipc_block_ext_dbg_dump(void);
extern bc_err_e bc_sys_ipc_block_ext_dbg_dump_single(bc_uint32 ofs);

#endif
#if 1


/*************************************************
  Function: bc_sys_ipc_baseinfo
  Description: get system base info
  Input: 
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_sys_ipc_baseinfo(bc_sys_baseinfo_t *info);


/*************************************************
  Function: bc_sys_set_sys_name_client
  Description: set system name
  Input: 
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
extern bc_err_e bc_sys_set_sys_name_client(bc_char sys_name[BC_MODULE_NAME_LENGTH]);

/*************************************************
  Function: bc_sys_ipc_language_get
  Description: get sys language
  Input: 
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
extern bc_lan_e bc_sys_ipc_language_get(void);

/*************************************************
  Function: bc_sys_set_sys_language_client
  Description: set system language
  Input: 
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
extern bc_err_e bc_sys_set_sys_language_client(bc_lan_e language);

bc_err_e bc_sys_reboot_client(void);

bc_err_e bc_sys_reset_client(void);

bc_err_e bc_sys_mac_set_client(bc_mac mac);

bc_err_e bc_sys_mac_get_client(bc_mac mac);

#endif
#endif
