/************************************************************
  -------------------------------------------------------------------------
  FileName:
  Author:  bain.wang@outlook.com      Version :  1.0        Date:2016-4-24
  Description:                   
  Version:                        
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/

#ifndef __bc_sys_event_h__
#define __bc_sys_event_h__

#include "bc_common_defs.h"
#include "bc_modules.h"
#include "bc_err.h"
//#include "bc_port_def.h"

/*
	添加事件步骤:
		1. 在bc_sys_event_e中添加事件类型
		2. 在bc_sys_event_msg_t中添加事件数据结构体
		3. 在bc_sys_event_hi或bc_sys_event_lo中初始化事件的bc_sys_event_t数据
*/

typedef enum {
	/* 这里添加高优先级事件 */
	BC_SYS_EVENT_HI_NOUSE_E = 1,									/*保留*/
	BC_SYS_EVENT_HI_LO_DIVIDE_E					= 100,

	BC_SYS_EVENT_LO_NOUSE_E	= BC_SYS_EVENT_HI_LO_DIVIDE_E+1,	/*保留*/

	/* 这里添加低优先级事件 */
	BC_SYS_EVENT_LO_SESSION_RELEASE_E = 102,
	BC_SYS_EVENT_LO_TEST_E	    	= 103,	
} bc_sys_event_e;


typedef union {

	struct {
			bc_uint32 session_id;
	} session_release;	/*BC_SYS_EVENT_LO_SESSION_RELEASE_E*/
	
	struct {
		char name[32];
		int age;
		int count;	//次数，以验证
	}test;	/*BC_SYS_EVENT_LO_TEST_E*/

	bc_char max_struct_size[512];
} bc_sys_event_msg_t;


typedef void (*bc_sys_event_notify_cb)(bc_sys_event_msg_t*);


/*************************************************
  Function: bc_sys_event
  Description: event trigger
  Input: 
  		evt: event
  Output:
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
extern bc_err_e bc_sys_event(bc_sys_event_e evt, bc_sys_event_msg_t *msg);


/*************************************************
  Function: bc_sys_event_notify_reg
  Description: register event callback function
  Input: 
  		module_id: module id
  		evt: event
  		cb: event callbck function
  Output:
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
extern bc_err_e bc_sys_event_notify_reg
(
	bc_modules_e module_id,
	bc_sys_event_e evt,
	bc_sys_event_notify_cb cb
);

/*************************************************
  Function: bc_sys_event_notify_unreg
  Description: deregister event callback function
  Input: 
  		module_id: module id
  		evt: event
  		cb: event callbck function
  Output:
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
extern bc_err_e bc_sys_event_notify_unreg 
(
	bc_modules_e module_id,
	bc_sys_event_e evt,
	bc_sys_event_notify_cb cb
);

/*************************************************
  Function: bc_sys_event_init
  Description: sys event init
  Input: 
  Output:
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
extern bc_err_e bc_sys_event_init(void);


#endif

