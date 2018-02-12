/************************************************************
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

#ifndef __bc_sys_baseinfo_h__
#define __bc_sys_baseinfo_h__

#include "bc_sys_defs.h"


/*************************************************
  Function: bc_sys_baseinfo_get
  Description: get system basic information
  Input: 
  Output:
  		bi: system information
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
extern bc_err_e bc_sys_baseinfo_get(bc_sys_baseinfo_t *bi);


/*************************************************
  Function: bc_sys_baseinfo_init
  Description: system basic information init
  Input: 
  Output:
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
extern bc_err_e bc_sys_baseinfo_init(void);



/*************************************************
  Function: bc_sys_name_set
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
extern bc_err_e bc_sys_name_set(bc_char *sys_name);



/*************************************************
  Function: bc_sys_language_set
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
extern bc_err_e bc_sys_language_set(bc_lan_e lan);
/*************************************************
  Function: bc_sys_language_get
  Description: get system language
  Input: 
  Output:
  		bi: system information
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/

extern bc_lan_e bc_sys_language_get(void);




#endif

