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

#ifndef __BC_SYS_SRV_H__
#define __BC_SYS_SRV_H__





/*************************************************
  Function: bc_sys_ipc_baseinfo_srv
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
extern bc_err_e bc_sys_ipc_baseinfo_srv(bc_ipc_package_t *data);


/*************************************************
  Function: bc_sys_ipc_event_dbg_dump_srv
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
extern bc_err_e bc_sys_ipc_event_dbg_dump_srv(bc_ipc_package_t *data);


/*************************************************
  Function: bc_sys_ipc_polling_dbg_dump_srv
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
extern bc_err_e bc_sys_ipc_polling_dbg_dump_srv(bc_ipc_package_t *data);

extern bc_err_e bc_sys_ipc_block_ext_dump_srv(bc_ipc_package_t *data);
extern bc_err_e bc_sys_ipc_block_ext_dump_single_srv(bc_ipc_package_t *data);

/*************************************************
  Function: bc_sys_ipc_name_set_srv
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
extern bc_err_e bc_sys_ipc_name_set_srv(bc_ipc_package_t *data);



/*************************************************
  Function: bc_sys_ipc_language_set_srv
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
extern bc_err_e bc_sys_ipc_language_set_srv(bc_ipc_package_t *data);


extern bc_err_e bc_sys_ipc_reboot_srv(bc_ipc_package_t *data);

extern bc_err_e bc_sys_ipc_reset_srv(bc_ipc_package_t *data);
bc_err_e bc_sys_mac_set_srv(bc_ipc_package_t *data);
bc_err_e bc_sys_mac_get_srv(bc_ipc_package_t *data);
#endif

