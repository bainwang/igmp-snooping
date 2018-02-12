/************************************************************
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

#ifndef __bc_sys_ip_h__
#define __bc_sys_ip_h__

#include "bc_common_defs.h"
#include "bc_modules.h"
#include "bc_err.h"

typedef enum {
		BC_SYS_IP_TYPE_INBAND_E 			= 0x00,
		BC_SYS_IP_TYPE_OUTBAND_E 		= 0x01,
		BC_SYS_IP_TYPE_INTERNAL_E		= 0x02,
		BC_SYS_IP_TYPE_SWITCH_CPU_E	= 0x03
} bc_sys_ip_type_e;


/*************************************************
  Function: bc_sys_ip_def_get
  Description: get sys ip
  Input: 
  		type: interface 
  Output:
       intf_num: eth*, * is the intf_num
  		ip: default ip
  		mask: default mask
  		gateway: default gateway
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_sys_ip_def_get(bc_sys_ip_type_e type, bc_int32 *intf_num, bc_ip *ip, bc_ip *mask, bc_ip *gateway);

extern bc_err_e bc_sys_ip_def_other_board_get(bc_ip *ip);


/*************************************************
  Function: bc_sys_ip_valid_unicast
  Description: check sys ip for unicast 
  Input: 
  		type: bc_ip 
  Output:
         	 NONE
  Return:
  		FALSE :0
  		TRUE :1
  Note: 
  History: 
*************************************************/
bc_boolean bc_sys_ip_valid_unicast(bc_ip ip);

/*************************************************
  Function: bc_sys_ip_valid_multicast
  Description: check sys ip for multicast
  Input: 
  Input: 
  		type: bc_ip 
  Output:
          NONE
  Return:
  		FALSE
  		true
  Note: 
  History: 
*************************************************/

bc_boolean bc_sys_ip_valid_multicast(bc_ip ip);

/*************************************************
  Function: bc_sys_ip_valid_submask
  Description: check sys submask valid
  Input: 
  		type: bc_ip 
  Output:
         	 NONE
  Return:
  		FALSE :0
  		TRUE :1
  Note: 
  History: 
*************************************************/
extern bc_boolean bc_sys_ip_valid_submask(bc_ip ip);


/*************************************************
  Function: bc_sys_ip_valid_ip
  Description: check sys ip valid
  Input: 
  		type: bc_ip 
  Output:
         	 NONE
  Return:
  		FALSE :0
  		TRUE :1
  Note: 
  History: 
*************************************************/
extern bc_boolean bc_sys_ip_valid_ip(bc_ip ip);

/*
 * Function:
 *      bc_sys_ip_mask_create
 * Description:
 *      Create IPv4 network address from prefix length
 * Input:
 *      len - the prefix/mask length
 * Returns:
 *      The IPv4 mask
 */
extern bc_uint32 bc_sys_ip_mask_create(bc_int32 len);

/*
 * Function:
 *      bc_sys_ip_mask_length
 * Description:
 *      Return the mask length from IPv4 network address
 * Input:
 *      mask - The IPv4 mask as IP address
 * Returns:
 *      The IPv4 mask length
 */
bc_int32 bc_sys_ip_mask_length(bc_uint32 mask);

/*************************************************
  Function: bc_sys_ip_valid_gw
  Description: check sys ip valid
  Input: 
  		type: bc_ip 
  Output:
         	 NONE
  Return:
  		FALSE :0
  		TRUE :1
  Note: 
  History: 
*************************************************/
bc_boolean bc_sys_ip_valid_gw(bc_ip ip);
/*************************************************
  Function: bc_sys_ip_init
  Description: sys ip init
  Input: 
  Output:
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/

bc_err_e bc_sys_ip_init(void);

bc_boolean bc_sys_ip_get(bc_ip* ip);
#endif

