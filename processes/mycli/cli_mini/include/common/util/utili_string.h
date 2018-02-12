/*******************************************************************************
  Copyright (C), 1988-2012, xxxxx Tech. Co., Ltd.
  [File name]  : \\BC\cli\include\deal_string.h
  [Author]     : wangbin
  [Version]    : 1.0
  [Date]       : 2012-08-02
  [Description]:

  [Others]     :

  [Function List]:
    1. ....
    2. ....
  [History]:
     D a t e    Modification                                          Initials
    ---------- --------------                                        ----------
    2012-08-02  Created                                               wangbin
*******************************************************************************/

#ifndef __INC_UTILI_STRING_H__
#define __INC_UTILI_STRING_H__

#include "bc_common_defs.h"

/*
	检测输入字符串是否规范
*/
extern bc_int32 utili_check_input_str(bc_char *ptr_string);
/*检查IP*/
extern bc_int32 utili_check_net_ip_int(bc_int32 ip);
/*检查子网掩码*/
extern bc_int32 utili_check_net_mask_int(bc_int32 mask);

/*
	转换输入字符串为数值，失败返回-1，成功返回0
*/

extern bc_char *utili_str_to_uint32(bc_char *str,bc_uint32 radix, bc_uint32 *value);
extern bc_char *utili_str_to_float(bc_char *str,float *value);
extern bc_char *utili_str_to_ipv4_int(bc_char *str, bc_uint32 *ipaddr);

extern bc_int32 utili_u16_to_u8(bc_uint16 buf16[], bc_uint8 buf8[], bc_uint8 buf_len);
extern bc_int32 utili_str_to_range(bc_char *str, bc_int32 value[2]);
extern bc_int32 utili_str_to_list(bc_char *str, bc_uint16 value[], bc_uint32 buf_len);
extern bc_int32 utili_str_to_mac(bc_char *str, bc_uint8 mac[6]);
extern bc_int32 utili_str_to_mac_mask(bc_char *str, bc_uint8 mac_mask[6]);
extern bc_int32 utili_str_to_ipv4_4byte(bc_char *str, bc_uint8 ip_4byte[4]);
extern bc_int32 utili_ipv4_to_str(bc_int32 str, bc_char* ip_str);
extern bc_int32 utili_str_to_mask_4byte(bc_char *str, bc_uint8 mask_4byte[4]);
extern bc_int32 utili_str_to_gate_4byte(bc_char *str, bc_uint8 gate_4byte[4]);

#endif /* __INC_UTILI_STRING_H__ */

