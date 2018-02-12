/*******************************************************************************
  [File name]	: utili_ip_mac.c
  [Author]     	: bain.wang@outlook.com
  [Version]    	: 1.0
  [Date]       	: 2017-04-04
  [Description]	:
	list api porting from cortina
  [Others]     	:
	NULL
  [Function List]:  
    1. ....
    2. ....
  [History]:
	 Date       	Modification 							 Initials
	---------- 	--------------                                        ----------
	2017-04-04  	Created								 bain.wang@outlook.com
*******************************************************************************/

#ifndef __UTILI_IP_MAC_H__
#define __UTILI_IP_MAC_H__

#define CPU_LITTLE_ENDIAN 0
#define CPU_BIG_ENDIAN 1

#define CPU_ENDIAN CPU_BIG_ENDIAN

#if CPU_ENDIAN == CPU_LITTLE_ENDIAN
#define bc_ntohl(x)	   ((((x) & 0xff) << 24) | (((x) & 0xff00) << 8) | (((x) & 0xff0000) >> 8) | ((x) >> 24))
#define bc_ntohs(x)	   ((((x) & 0xff) << 8) | ((x) >> 8))
#define bc_htonl(x)	   bc_ntohl(x)
#define bc_htons(x)    bc_ntohs(x)
#else
#define bc_ntohl(x)	   x	
#define bc_ntohs(x)    x
#define bc_htonl(x)    x
#define bc_htons(x)    x 
#endif


void mcast_ip_cvrt_mac(IN bc_ip grp, OUT bc_mac mac);
bc_boolean mcast_utl_is_mc_mac(bc_mac mac);
extern bc_boolean utili_ip_mac_zero_mac(bc_mac mac);
bc_boolean mcast_utl_valid_mc_ip(IN bc_ip grp);
bc_boolean mcast_utl_valid_uc_ip(IN bc_ip ip);
bc_boolean mcast_utl_valid_src_ip(IN bc_ip ip);
bc_boolean utili_mac_is_mcast_addr(bc_mac mac);

extern bc_boolean utili_ip_mac_strmac_2_mac(char str_mac[18], bc_mac mac);
extern bc_boolean utili_ip_mac_mac_2_strmac(bc_mac mac, char str_mac[18]);
extern bc_char * ip_format_get(bc_uint32 grp, bc_char ip[20]);

extern bc_char *utili_ip_mac_cnvt_ip_2_str(bc_uint32 ip, bc_char ip_str[20]);

#endif
