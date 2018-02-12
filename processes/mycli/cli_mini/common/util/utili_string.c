
/*******************************************************************************
  Copyright (C), 1988-2012, xxxxx Tech. Co., Ltd.
  [File name]  : \\BC\util\utili_string.c
  [Author]     : 
  [Version]    : 1.0
  [Date]       : 2013-06-19
  [Description]: 
  
  [Others]     :

  [Function List]:
	1. ....
	2. ....
  [History]:
	 D a t e    Modification 										  Initials
	---------- --------------                                        ----------
	2013-06-19  Created	 											  yest
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								头   文   件								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
/* inet_... */
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <sys/time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <regex.h>
#include <termios.h>
#include "bc_common_defs.h"
#include "utili_string.h"


#define SUBSLEN 	10            
#define EBUFLEN 	128          
#define BUFLEN 		1024 

#define GET_LEN_OF_VAL(x)       (((x) < 10) ? 1 : (((x) < 100) ? 2 : (((x) < 1000) ? 3 : (((x) < 10000) ? 4 : 5))))

#define MAC_IS_EQUAL( aPtr, bPtr)\
    (\
    (   1                                        \
        && ((aPtr)[0] == (bPtr)[0])        		 \
        && ((aPtr)[1] == (bPtr)[1])              \
        && ((aPtr)[2] == (bPtr)[2])              \
        && ((aPtr)[3] == (bPtr)[3])              \
        && ((aPtr)[4] == (bPtr)[4])              \
        && ((aPtr)[5] == (bPtr)[5])              \
        )                                        \
    ? 1 : 0)

typedef enum etag_value_refex_t
{
	VALUE_REFEX_INT = 1,
	VALUE_REFEX_SLASH,
	VALUE_REFEX_IP,
	VALUE_REFEX_INTRANGE,
	VALUE_WOS_WEIGHT,
	VALUE_MAC_COLON,
	VALUE_MAC_LINE,
	VALUE_MAC_POINT,
	VALUE_REFEX_PONONU,
	VALUE_REFEX_COMMA,
	VALUE_REFEX_INT_16,
	VALUE_REFEX_INT_2,
	VALUE_REFEX_MAX	
}value_refex_e;


static bc_uint8	EMPTY_MAC_ADDR[6]	=
{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static bc_uint8	EMPTY_MACFF_ADDR[6] =
{
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

static bc_int32 check_net_ip(bc_uint8 ip_byte4[4]);
static bc_int32 check_net_mask(bc_uint8 mask_4byte[4]);

static bc_int32 match_string(bc_char match_strings[], bc_char reg_string[]);
static bc_int32 st_mac_2a2t(const bc_char *str, bc_uint8 *bin);
static bc_int32 st_mac_4ap2t(const bc_char *str, bc_uint8 *bin);
static bc_int32 st_ip_a2t(const bc_char *str, bc_uint8 *bin);



static bc_char * utili_find_wordbegin(bc_char *string)
{
	while (string[0] == ' ' || string[0] == '\t')
	{
		string++;      /* skip for ' ' */
	}

	return string;
}


/******************************************************************************\
  Function   : match_string
  Description: 
  Return     : 
  Others     : 
\******************************************************************************/
static bc_int32 match_string(bc_char match_strings[], bc_char reg_string[])
{
#if 1
    regex_t     reg;                    
    regmatch_t  subs[SUBSLEN]; 
    bc_char        errbuf[EBUFLEN];
    bc_int32         err;

    if (match_strings == NULL || reg_string == NULL)
    {
        return -1;
    }

    //translate regular 
    err = regcomp(&reg, reg_string, REG_EXTENDED);
    if (err)
    {
        regerror(err, &reg, errbuf, sizeof(errbuf));
        return -1;
    }

    // match string
    err = regexec(&reg, match_strings, (size_t) SUBSLEN, subs, 0);
    if (err == REG_NOMATCH) //no macth
    {
        regfree(&reg);
        return -1;
        //continue;
    }
    else if (err) //other error
    {
        regerror(err, &reg, errbuf, sizeof(errbuf));
        regfree(&reg); 
        return -1;
    }

    regfree(&reg);  
    return 0;

#else

    regex_t   reg;                    
    regmatch_t  subs[SUBSLEN]; 
    bc_char errbuf[EBUFLEN];
    bc_int32 err;
    if(match_strings==NULL||reg_string==NULL)
    return -1;
     //translate regular 
    err=regcomp(&reg,reg_string,REG_EXTENDED);
    if (err) 
    {
    regerror(err,&reg,errbuf,sizeof(errbuf));
    return -1;
    }
    // match string
    err=regexec(&reg,match_strings,(size_t)SUBSLEN,subs,0);
    if (err==REG_NOMATCH) //no macth
    {
    regfree(&reg);
    return -1;
    //continue;
    } 
    else if(err) //other error
    { 
    regerror(err,&reg,errbuf,sizeof(errbuf));
    regfree(&reg); 
    return -1;
    }
    regfree(&reg);  
return 0;
#endif
}



/******************************************************************************\
  Function   : check_input_string
  Description: 检测输入字符串是否规范
  Return     : 
  Others     : 
\******************************************************************************/
bc_int32 check_input_string(bc_char *ptr_string)
{
#if 1
    bc_int32 	i, len;
    bc_char	*arry_regul[]   =
    {
        /*"^[0-9]*[0-9][0-9]*$",\*/
        "^[0-9]*$",
        "^([0-9]*)(([/]([0-9]*)){1})$",
        "^([0-9]{1,3}[.]){3}[0-9]{1,3}$",
        "^([0-9]*)(([-]([0-9]*)){1})$",
        "^([0-9]*)(([-]([0-9]*)){3})$",
        "^([0-9a-fA-F]{2})(([:][0-9a-fA-F]{2}){5})$",
        "^([0-9a-fA-F]{2})(([-][0-9a-fA-F]{2}){5})$",
        "^([0-9a-fA-F]{4})(([.][0-9a-fA-F]{4}){2})$",
        "^([0-9]*)(([/]([0-9]*)){1})(([:]([0-9]*))){1}$",
        "^([0-9]*)(([-,]([0-9]*)){1,31})$",
		"^(([0][Xx]){1})([0-9a-fA-F]*)$",
		"^(([0][hH]){1})([0-1]*)$"
    };

    len = sizeof(arry_regul) / sizeof(bc_char *); 
    for (i = 0; i < len; i++)
    {
        if (0 == match_string(ptr_string, arry_regul[i]))
        {
            return (i + 1);
        }
    }

    return -1;

#else

    bc_int32 ret=0,i,flag=0,len=0;
    bc_char* arry_regul[]={"^[0-9]*[0-9][0-9]*$",\
                                "^([0-9]*)(([/]([0-9]*)){1})$",\
                                "^([0-9]{1,3}[.]){3}[0-9]{1,3}$",\
                                "^([0-9]*)(([-]([0-9]*)){1})$",\
                                "^([0-9]*)(([-]([0-9]*)){3})$",\
                                "^([0-9a-fA-F]{2})(([:][0-9a-fA-F]{2}){5})$",\
                                "^([0-9a-fA-F]{2})(([-][0-9a-fA-F]{2}){5})$",\
                                "^([0-9a-fA-F]{4})(([.][0-9a-fA-F]{4}){2})$",\
                                "^([0-9]*)(([/]([0-9]*)){1})(([:]([0-9]*))){1}$",\
                                "^([0-9]*)(([-,]([0-9]*)){1,31})$"};
  len=sizeof(arry_regul)/sizeof(bc_char*); 
  for(i=0;i<len;i++)
  {
   ret=match_string(ptr_string,arry_regul[i]);
    if(0==ret)
     {
       flag=1;  
       break;
     }  
    else
        continue;
  }
  if(1==flag)
    return (i+1);
  else
    return -1;

#endif
}



/******************************************************************************\
  Function   : check_net_ip
  Description: 
  Return     : 
  Others     : 
\******************************************************************************/
static bc_int32 check_net_ip(bc_uint8 ip_byte4[4])
{
    if (0 == ip_byte4[0])
    {
        return -1;
    }

    return 0;
}



/******************************************************************************\
  Function   : check_net_mask
  Description: 
  Return     : 
  Others     : 
\******************************************************************************/
static bc_int32 check_net_mask(bc_uint8 mask_4byte[4])
{
	bc_uint8 		*pmask = mask_4byte;
	bc_int32 	byte, bit;
	bc_uint8 		flg_bit_0 = 0;

	/* 首位0或末尾1，非法 */
	if ((!(mask_4byte[0] & 0x80)) || (mask_4byte[3] & 0x01))
	{
		return -1;
	}

	/* 循环检查位 */
	for (byte = 0; byte < 4; byte++)
	{
		pmask = mask_4byte + byte;
		for (bit = 7; bit >= 0; bit--)
		{
			if(flg_bit_0 == 0)
			{	
				if(((*pmask) & (0x01 << bit)) == 0)
				{
					flg_bit_0 = 1;
				}
			}
			else
			{
				if(((*pmask) & (0x01 << bit)) > 0)
				{
					return -1;
				}
			}
		}
	}

	return 0;
}

/******************************************************************************\
  Function   : utili_check_net_ip_int
  Description: 
  Return     : 
  Others     : 
\******************************************************************************/
bc_int32 utili_check_net_ip_int(bc_int32 ip)
{
	bc_char    ipaddr[18] = {0};
	bc_uint8      ip_4byte[4] = {0};
	
	if(utili_ipv4_to_str(ip, ipaddr) != 0)
	{
		return -1;
	}

	if(st_ip_a2t(ipaddr, ip_4byte) != 0)
	{
		return -1;
	}

	return check_net_ip(ip_4byte);

}

/******************************************************************************\
  Function   : utili_check_net_mask_int
  Description: 
  Return     : 
  Others     : 
\******************************************************************************/
bc_int32 utili_check_net_mask_int(bc_int32 mask)
{
	bc_char    ipaddr[18] = {0};
	bc_uint8      ip_4byte[4] = {0};
	
	if(utili_ipv4_to_str(mask, ipaddr) != 0)
	{
		return -1;
	}

	if(st_ip_a2t(ipaddr, ip_4byte) != 0)
	{
		return -1;
	}

	return check_net_mask(ip_4byte);

}

/******************************************************************************\
  Function   : st_mac_2a2t
  Description: 
  Return     : 
  Others     : 00:12:34:AB:CD:EF -> Array[6] = {00, 12, 34, AB, CD, EF}
               00-12-34-AB-CD-EF -> Array[6] = {00, 12, 34, AB, CD, EF}
               00.12.34.AB.CD.EF -> Array[6] = {00, 12, 34, AB, CD, EF}
               00?12?34?AB?CD?EF -> Array[6] = {00, 12, 34, AB, CD, EF}
\******************************************************************************/
static bc_int32 st_mac_2a2t(const bc_char *str, bc_uint8 *bin)
{
    bc_int32 	i;
    bc_char	*ptr, *strtok_ctx;

    if ((bin == NULL) || (str == NULL))
    {
        return -1;
    }

    ptr = (bc_char *) str; 
    for (i = 0; i < 6; ++i)
    {
        bin[i] = ptr ? strtoul(ptr, &strtok_ctx, 16) : 0;
        //  printf("%s,%s\n",ptr,strtok_ctx);
        if (ptr)
        {
            ptr = (*strtok_ctx) ? strtok_ctx + 1 : strtok_ctx;
        }
    }

    return 0;
}



/******************************************************************************\
  Function   : st_mac_4ap2t
  Description: 
  Return     : 
  Others     : 0012.34AB.CDEF -> Array[6] = {00, 12, 34, AB, CD, EF}
\******************************************************************************/
static bc_int32 st_mac_4ap2t(const bc_char *str, bc_uint8 *bin)
{
    bc_char	*ptr;
    bc_int32 	tmp[6] = {0};

    if ((bin == NULL) || (str == NULL))
    {
        return -1;
    }

    ptr = (bc_char *) str; 

    sscanf(ptr, "%02x%02x.%02x%02x.%02x%02x", &tmp[0], &tmp[1], &tmp[2], &tmp[3], &tmp[4], &tmp[5]);
    bin[0] = (bc_uint8) tmp[0];
    bin[1] = (bc_uint8) tmp[1];
    bin[2] = (bc_uint8) tmp[2];
    bin[3] = (bc_uint8) tmp[3];
    bin[4] = (bc_uint8) tmp[4];
    bin[5] = (bc_uint8) tmp[5];   

    return 0;
}



/******************************************************************************\
  Function   : st_ip_a2t
  Description: 
  Return     : 
  Others     : 
\******************************************************************************/
static bc_int32 st_ip_a2t(const bc_char *str, bc_uint8 *bin)
{
    bc_int32     i;
    bc_char    ipaddr[18] = {0};

    if ((bin == NULL) || (str == NULL))
    {
        return -1;
    }

    memcpy(ipaddr, str, sizeof(ipaddr));
    bc_char	*dig    = strtok(ipaddr, ".");

	for (i = 0; i < 4; i++)
    {
        if (dig)
        {
            if (atoi(dig) > 255)
            {
                return -1;
            }

            bin[i] = (bc_uint8) strtoul(dig, NULL, 10);
            dig = strtok(NULL, ".");
        }
    }

    return 0;
}



/*
	转换输入字符串为数值
*/
/******************************************************************************\
  Function   : utili_str_to_uint32
  Description: 
  Return     : 
  Others     : 
\******************************************************************************/
bc_char *utili_str_to_uint32(bc_char *str,bc_uint32 radix, bc_uint32 *value)
{
	bc_uint32 val;
	bc_char rxCh;
	bc_char *current_str;
	val = 0;
	current_str = str;

	switch(radix)
	{
		case 16:
			/* check the heard of "0x","0X" and skip it */
			if (current_str[0] == '0' && ((current_str[1] == 'x') || (current_str[1] == 'X')))
			{
				current_str += 2;
			}

			for (;;)
			{
				rxCh = *current_str;
				if (isxdigit(rxCh))
				{
					/* the max num is 2^32 - 1 = 0xffffffff */
					if (val > 0xfffffff)
					{
						/* out of range */
						return NULL;
					}

					rxCh = (bc_char)toupper(rxCh);
					if (isdigit(rxCh))
					{
						rxCh -= '0';
					}
					else
					{
						rxCh = (rxCh - 'A') + 10;
					}

					val = val * 16;
					val += rxCh;
					current_str++;
				}
				else
				{
					break;
				}

			}
			break;

		case 10:
		default:
			for (;;)
			{
				rxCh = *current_str;
				if (isdigit(rxCh))
				{
					/* the max num is 2^32 - 1 = 4294967295 */
					/* 429496729 = 0x19999999 */
					if (val > 0x19999999)
					{
						/* out of range */
						return NULL;
					}
					else if (val == 0x19999999 && ((rxCh - '0') > 5))
					{
						/* out of range */
						return NULL;
					}
					val = val * 10;
					val += (rxCh - '0');
					current_str++;
				}
				else
				{
					break;
				}
			}
			break;
	}

	*value = val;
	return current_str;
}


/******************************************************************************\
  Function   : check_convertion_inputidormac
  Description: 
  Return     : 
  Others     : 
\******************************************************************************/
bc_char *utili_str_to_float(bc_char *str,float *value)
{
	bc_boolean fraction = FALSE, exaction = FALSE;
	bc_char *ptr,*ptrfloat;

	ptr = utili_find_wordbegin(str);
	if ('\0' == *ptr)
	{
		return NULL;
	}

	if ('-' == *ptr)
	{
		ptr++;
	}
	else if ('+' == *ptr)
	{
	       ptr ++;
	}
	/* for the range case: for example "1e-4-100" */
	while (' ' != *ptr && '-' != *ptr && '\0' != *ptr)
	{
		if ('.' == *ptr && (!fraction))
		{
			fraction = TRUE;
			/* example: 1e-2.3 */
			if (exaction)
			{
				return NULL;
			}
		}
		/* example: 1e-04, 3e+8, 4e6, 1E-4 and so on */
		else if (('e' == *ptr || 'E' == *ptr) && (!exaction))
		{
			exaction = TRUE;
			if ('-' == *(ptr+1) || '+' == *(ptr+1))
			{
				ptr++;
			}
		}
		else
		{
           	 	if ('0' > *ptr || '9' < *ptr)
           	 	{
            			return  NULL;
           	 	}
		}
		ptr++;
	}
	ptrfloat = utili_find_wordbegin(str);

	*value = (float)atof(ptrfloat);
	
	return ptr;
}


/******************************************************************************\
  Function   : check_convertion_inputidormac
  Description: 
  Return     : 
  Others     : 
\******************************************************************************/
bc_int32 utili_str_to_range(bc_char *str, bc_int32 value[2])
{
    bc_int32 			index1 = 0, index0 = 0;

    if (VALUE_REFEX_INTRANGE != check_input_string(str))
	{
		return -1;
	}

    sscanf(str, "%d-%d", &index0, &index1);
    if (index0 > index1)
    {
        //fprintf(stdout, "Invalid device id range id1 must be less than id2\n");
        return -1;
    }

    value[0] = index0;
	value[1] = index1;

    return 2;
}



/******************************************************************************\
  Function   : utili_str_to_list
  Description: 
  Return     : 
  Others     : 
\******************************************************************************/
bc_int32 utili_str_to_list(bc_char *str, bc_uint16 buf[], bc_uint32 buf_len)
{
    bc_int32     Write   	= 0;
    bc_char    *pStr       = str;
    bc_char    TempLen 	= 0;
    bc_uint16     *pValue     = buf;
    bc_uint16     ValTemp1;
    bc_uint16     ValTemp2;
    bc_int32     str_type;

    str_type = check_input_string(pStr);
    if ((str_type != VALUE_REFEX_INT) && (str_type != VALUE_REFEX_INTRANGE) && (str_type != VALUE_REFEX_COMMA))
    {
        return -1;
    }

vlan_list_flag:
    if (*pStr == '\0')
    {
        return Write;
    }
    else if (*pStr == ',')
    {
        pStr++;
    }

    ValTemp1 = atoi(pStr);
#if 0
	if (IS_VALID_VLANID(ValTemp1) == FALSE)
    {
        return 0;
    }
#endif
    *pValue = ValTemp1;
    pValue++;
    Write++;

    if (Write == buf_len)
    {
        return buf_len;
    }

    TempLen = GET_LEN_OF_VAL(ValTemp1);
    pStr += TempLen;

    if (*pStr =='\0')
    {
        return Write;
    }
    else if (*pStr == ',')
    {
        pStr++;
        goto vlan_list_flag;
    }
    else if (*pStr == '-')
    {
        pStr++;

        ValTemp2 = atoi(pStr);
#if 0
		if (IS_VALID_VLANID(ValTemp2) == FALSE)
        {
            return 0;
        }
#endif
        if (ValTemp2 <= ValTemp1)
        {
            return 0;
        }

        bc_int32 i, range;

        range = ValTemp2 - ValTemp1;

        if ((range + Write) > buf_len)
        {
            return 0;
        }

        for (i = 0; i < range; i++)
        {
            *pValue = ValTemp1 + i + 1;
            pValue++;
        }

        Write += range;

        TempLen = GET_LEN_OF_VAL(ValTemp2);
        pStr += TempLen;

        goto vlan_list_flag;
    }
    else
    {
        return 0;
    }

    return Write;
}



/******************************************************************************\
  Function   : utili_str_to_mac
  Description: 
  Return     : 
  Others     : 
\******************************************************************************/
bc_int32 utili_str_to_mac(bc_char *str, bc_uint8 mac[6])
{
    bc_int32 	ret;

    ret = check_input_string(str);
    if ((ret == VALUE_MAC_COLON) || (ret == VALUE_MAC_LINE))
    {
        st_mac_2a2t(str, mac);
    }
	else if (ret == VALUE_MAC_POINT)
	{
		st_mac_4ap2t(str, mac);
	}
    else
    {
        //fprintf(stdout, "%s", "Invalid MAC-ADDR, FORMAT:XXXX.XXXX.XXXX (X<F).\n");
        return -1;
    }

	if (MAC_IS_EQUAL(mac, EMPTY_MAC_ADDR) || MAC_IS_EQUAL(mac, EMPTY_MACFF_ADDR))
	{
		//fprintf(stdout, "%s", "Invalid MAC-ADDR, FORMAT:XXXX.XXXX.XXXX (X<F).\n");
		return -1;
	}

    return 0;
}



/******************************************************************************\
  Function   : utili_str_to_mac_mask
  Description: 
  Return     : 
  Others     : 
\******************************************************************************/
bc_int32 utili_str_to_mac_mask(bc_char *str, bc_uint8 mac_mask[6])
{
    bc_int32 	ret;

    ret = check_input_string(str);
    if ((ret == VALUE_MAC_COLON) || (ret == VALUE_MAC_LINE))
    {
        st_mac_2a2t(str, mac_mask);
    }
	else if (ret == VALUE_MAC_POINT)
	{
		st_mac_4ap2t(str, mac_mask);
	}
    else
    {
        //fprintf(stdout, "%s", "Invalid MAC-ADDR, FORMAT:XXXX.XXXX.XXXX (X<F).\n");
        return -1;
    }

	if (MAC_IS_EQUAL(mac_mask, EMPTY_MAC_ADDR))
	{
		//fprintf(stdout, "%s", "Invalid MAC-ADDR, FORMAT:XXXX.XXXX.XXXX (X<F).\n");
		return -1;
	}

    return 0;
}



/******************************************************************************\
  Function   : utili_str_to_ipv4_4byte
  Description: 
  Return     : 
  Others     : 
\******************************************************************************/
bc_int32 utili_str_to_ipv4_4byte(bc_char *str, bc_uint8 ip_4byte[4])
{
    bc_int32 check = 0;

    if (VALUE_REFEX_IP != check_input_string(str))
	{
		return -1;
    }

	if (st_ip_a2t(str, ip_4byte) < 0)
	{
		return -1;
	}

	/* check network ip address */
    check = check_net_ip(ip_4byte);
    if (check < 0)
    {
        //fprintf(stdout, "%s", "Invalid IP-ADDR, FORMAT:XXX.XXX.XXX (0<XXX<255).\r\n");
        return -1;
    }

    return 0;
}



/******************************************************************************\
  Function   : utili_str_to_ipv4_int
  Description: 
  Return     : 
  Others     : 
\******************************************************************************/
bc_char *utili_str_to_ipv4_int(bc_char *str, bc_uint32 *ipaddr)
{
	bc_char *current_ptr, *end_ptr;
	bc_uint8 *ipstr;
	bc_uint32 temp_ipaddr;
	bc_int32 num, i;

	current_ptr = str;
	ipstr = (bc_uint8 *)&temp_ipaddr;
	
	/* get ipaddress now just for ipv4 address */
	for (i = 0; i < 4; i++)
	{
		num = strtoul(current_ptr, &end_ptr, 10);
		if (((end_ptr - current_ptr) > 3) || (num < 0) || (num > 255))
		{
			return NULL;
		}
		*ipstr++ = (bc_uint8)num;

		current_ptr = end_ptr;
		if (i < 3)
		{
			if (*current_ptr != '.')
			{
				return NULL;
			}
			current_ptr++;
		}
	}

	*ipaddr = temp_ipaddr;

	return current_ptr;
}

/******************************************************************************\
  Function   : utili_ipv4_to_str
  Description: 
  Return     : 
  Others     : 
\******************************************************************************/
bc_int32 utili_ipv4_to_str(bc_int32 str, bc_char* ip_str)
{
	struct in_addr inp;
	
	inp.s_addr = str;
	strcpy(ip_str, inet_ntoa(inp)); 
	
    return 0;
}


/******************************************************************************\
  Function   : utili_str_to_mask_4byte
  Description: 
  Return     : 
  Others     : 
\******************************************************************************/
bc_int32 utili_str_to_mask_4byte(bc_char *str, bc_uint8 mask_4byte[4])
{
    bc_int32 check = 0;

    if (VALUE_REFEX_IP != check_input_string(str))
	{
		return -1;
    }

	if (st_ip_a2t(str, mask_4byte) < 0)
	{
		return -1;
    }

	/* check mask address */
    check = check_net_mask(mask_4byte);
    if (check < 0)
    {
        //fprintf(stdout, "Invalid NETMASK vlaue,"IP_FORMAT);
        return -1;
    }

    return 0;
}



/******************************************************************************\
  Function   : utili_str_to_gate_4byte
  Description: 
  Return     : 
  Others     : 
\******************************************************************************/
bc_int32 utili_str_to_gate_4byte(bc_char *str, bc_uint8 gate_4byte[4])
{
    return utili_str_to_ipv4_4byte(str, gate_4byte);
}



/******************************************************************************\
  Function   : convert_u16_to_bc_uint8
  Description: 
  Return     : 
  Others     : 
\******************************************************************************/
bc_int32 utili_u16_to_u8(bc_uint16 buf16[], bc_uint8 buf8[], bc_uint8 buf_len)
{
	bc_uint8 i = 0;

	for (i=0; i < buf_len; i++)
	{
		buf8[i] = (bc_uint8)(buf16[i] & 0xFF);
	}

	return 1;
}





/* 
 *	预留一个注释在文件最后
 */
/******************************************************************************\
  Function   : 
  Description: 
  Return     : 
  Others     : 
\******************************************************************************/

