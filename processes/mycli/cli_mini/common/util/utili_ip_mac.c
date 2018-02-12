/*******************************************************************************
  Copyright (C), 1988-2013, xxxxx Tech. Co., Ltd.
  [File name]	: utili_ip_mac.c
  [Author]     	: yangl
  [Version]    	: 1.0
  [Date]       	: 2013-05-08
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
	2013-05-08  	Created								 yangl
*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include "bc_common_defs.h"

bc_char * ip_format_get(bc_uint32 grp, bc_char ip[20])
{
	if (NULL == ip)
	{
		return NULL;
	}
	
	memset(ip, '0', sizeof(ip));

	sprintf(ip, "%d.%d.%d.%d", (int)((grp & 0xff000000) >> 24),
		(int)((grp & 0xff0000) >> 16),
		(int)((grp & 0xff00) >> 8),
		(int)((grp & 0xff)));

	return ip;
}

void mcast_ip_cvrt_mac(IN bc_ip grp, OUT bc_mac mac)
{
	mac[0] = 0x01;
	mac[1] = 0x00;
	mac[2] = 0x5e;

	mac[3] = (grp & 0x00EF0000) >> 16;
	mac[4] = (grp & 0x0000FF00) >> 8;
	mac[5] = grp & 0x000000FF;
}

bc_boolean mcast_utl_is_mc_mac(bc_mac mac)
{
	if (!mac)
		return FALSE;

	return (mac[0] & 0x01) ? TRUE : FALSE;
}

bc_boolean utili_ip_mac_zero_mac(bc_mac mac)
{
	if (!mac)
		return FALSE;

	if (mac[0] == 0 &&
		mac[1] == 0 &&
		mac[2] == 0 &&
		mac[3] == 0 &&
		mac[4] == 0 &&
		mac[5] == 0)
		return TRUE;

	return FALSE;
}

bc_boolean mcast_utl_valid_mc_ip(IN bc_ip grp)
{
	if (grp == 0)
		return FALSE;

	if ((grp & 0xE0000000) != 0xE0000000)
		return FALSE;

	return TRUE;
}

bc_boolean mcast_utl_valid_uc_ip(IN bc_ip ip)
{
	if (ip == 0)
		return FALSE;

	if (ip > 0xE0000000)
		return FALSE;

	return TRUE;
}

bc_boolean mcast_utl_valid_src_ip(IN bc_ip ip)
{
	if (ip > 0xE0000000)
		return FALSE;

	return TRUE;
}

static int __mac_str_cvt2_num(char fir, char sec)
{
	int ret;

	ret = 0;
	if (fir >= '0' && fir <= '9')
		ret = (fir-'0')*16;
	else if (fir >= 'a' && fir <= 'f')
		ret = ((fir-'a')+10)*16;
	else if (fir >= 'A' && fir <= 'F')
		ret = ((fir-'A')+10)*16;
	else
		ret = 0;

	if (sec >= '0' && sec <= '9')
		ret += sec-'0';
	else if (sec >= 'a' && sec <= 'f')
		ret += (sec-'a')+10;
	else if (sec >= 'A' && sec <= 'F')
		ret += (sec-'A')+10;
	else
		ret += 0;

	return ret;	
}

/* str_mac: str mac is a string "04:00:00:00:00:20" */
bc_boolean utili_ip_mac_strmac_2_mac(char str_mac[18], bc_mac mac)
{
	int idx;
	int mac_idx;

	if (!str_mac || !mac)
		return FALSE;

	mac_idx = 0;
	for (idx = 0; idx < 18; idx += 3)
	{
		if (str_mac[idx] == '\0' || str_mac[idx] == '\n')
			break;

		if (mac_idx > 5)
			break;
		
		mac[mac_idx] = __mac_str_cvt2_num(str_mac[idx], str_mac[idx+1]);
		mac_idx++;
	}

	return TRUE;
}

bc_boolean utili_ip_mac_mac_2_strmac(bc_mac mac, char str_mac[18])
{
	if (!str_mac || !mac)
		return FALSE;

	snprintf(str_mac, 18, "%02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
	return TRUE;
}

/*return TRUE if the mac is mcast addr, otherwise FALSE*/
bc_boolean utili_mac_is_mcast_addr(bc_mac mac)
{
	if (NULL != mac && mac[0] & 0x1)
	{
		return TRUE;
	}

	return FALSE;
}
