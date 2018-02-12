/*******************************************************************************
  [Author]     : bain.wang@outlook.com
  [Version]    : 1.0
  [Date]       : 2017-04-04
  [Description]: 
  
  [Others]     :

  [Function List]:
	1. ....
	2. ....
  [History]:
	 D a t e    Modification 										  Initials
	---------- --------------                                        ----------
	2017-04-04  Created	 								bain.wang@outlook.com
*******************************************************************************/

#ifndef __INC_UTILI_STRING_H__
#define __INC_UTILI_STRING_H__

#include "bc_common_defs.h"
#include "bc_proj_defs.h"

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
extern bc_int32 utili_netaddr_u32_ipv4_to_str(bc_ip addr,char str[100]);

extern bc_int32 utili_str_to_mask_4byte(bc_char *str, bc_uint8 mask_4byte[4]);
extern bc_int32 utili_str_to_gate_4byte(bc_char *str, bc_uint8 gate_4byte[4]);

#ifdef BC_SYS_BIGENDIAN

#define UTILI_STRING_TO_UINT32(data_str)	\
				(((data_str)[0] << 24) & 0xFF000000u) | \
				(((data_str)[1] << 16) & 0x00FF0000u) | \
				(((data_str)[2] << 8) & 0x0000FF00u) | \
				((data_str)[3] & 0x000000FFu)

#define UTILI_STRING_TO_UINT16(data_str)	\
				(((data_str)[0] << 8) & 0xFF00u) | \
				((data_str)[1] & 0x00FFu)

#define UTILI_UINT32_TO_STRING(data, str) \
				do \
				{ \
					(str)[0] = ((data) & 0xFF000000u) >> 24; \
					(str)[1] = ((data) & 0x00FF0000u) >> 16; \
					(str)[2] = ((data) & 0x0000FF00u) >> 8; \
					(str)[3] = (data) & 0x000000FFu; \
				} while(0)

#define UTILI_UINT16_TO_STRING(data, str) \
				do \
				{ \
					(str)[0] = ((data) & 0xFF00u) >> 8; \
					(str)[1] = (data) & 0x00FFu; \
				} while(0)

#else /* LITTLEENDIAN */

#define UTILI_STRING_TO_UINT32(data_str)	\
				(((data_str)[3] << 24) & 0xFF000000u) | \
				(((data_str)[2] << 16) & 0x00FF0000u) | \
				(((data_str)[1] << 8) & 0x0000FF00u) | \
				((data_str)[0] & 0x000000FFu)

#define UTILI_STRING_TO_UINT16(data_str)	\
				(((data_str)[1] << 8) & 0xFF00u) | \
				((data_str)[0] & 0x00FFu)

#define UTILI_UINT32_TO_STRING(data, str) \
				do \
				{ \
					(str)[3] = ((data) & 0xFF000000u) >> 24; \
					(str)[2] = ((data) & 0x00FF0000u) >> 16; \
					(str)[1] = ((data) & 0x0000FF00u) >> 8; \
					(str)[0] = (data) & 0x000000FFu; \
				} while(0)

#define UTILI_UINT16_TO_STRING(data, str) \
				do \
				{ \
					(str)[1] = ((data) & 0xFF00u) >> 8; \
					(str)[0] = (data) & 0x00FFu; \
				} while(0)

#endif
#endif /* __INC_UTILI_STRING_H__ */

