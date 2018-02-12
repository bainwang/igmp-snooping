/*******************************************************************************
  Copyright (C), 1988-2012, xxxxx Tech. Co., Ltd.
  [File name]  : \\BC\include\cli\bc_cli_type.h
  [Author]     : wangbin
  [Version]    : 1.0
  [Date]       : 2014-04-22
  [Description]:

  [Others]     :

  [Function List]:
	1. ....
	2. ....
  [History]:
	 D a t e	Modification										  Initials
	---------- --------------										 ----------
	2014-04-22	Created 											  wangbin
*******************************************************************************/

#ifndef __INC_BC_CLI_TYPE_H__
#define __INC_BC_CLI_TYPE_H__

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								头   文   件								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <termio.h>
#include <unistd.h>
//#include <conio.h>


#include "bc_print.h"



////////////////////////////////////////////////////////////////////////////////
//																			  //
//								宏   定   义								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#define MIB_CST_MAX_PORT_OF_STACK_BOX 	64
#define CLI_LIST_MAX_NUM				1024 /* 8000 */

#ifndef I8_T
typedef char                I8_T;
typedef unsigned char       UI8_T;
#endif

#ifndef I16_T
typedef short               I16_T;
typedef unsigned short      UI16_T;
#endif

#ifndef I32_T
typedef int                 I32_T;
typedef unsigned int        UI32_T;
#endif

#ifndef BOOL_T
typedef int                 BOOL_T;
#endif

typedef unsigned long long  CLOCK_T;
typedef void *				HANDLE_T;

#ifndef LPARAM
typedef UI32_T 				LPARAM;
typedef UI32_T 				RPARAM;
#endif



#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif


#ifndef NULL
#define NULL	0
#endif

#ifndef UNUSED
#define UNUSED(x)                   ((x) = (x))
#endif

#ifndef INVALID
#define INVALID                     (~0)
#endif



/* NAMING CONSTANT DECLARATIONS */
#ifndef STR4_T
typedef char				STR4_T[4+4];
typedef char				STR8_T[8+4];
typedef char				STR16_T[16+4];
typedef char				STR32_T[32+4];
typedef char				STR64_T[64+4];
typedef char				STR80_T[80+4];
typedef char				STR128_T[128+4];
typedef char				STR256_T[256+4];
typedef char				STR512_T[512+4];
typedef char				STR1024_T[1024+4];
#endif

#ifndef UI64_T
typedef struct UI64_T
{
    UI32_T  high;        /* the high (msb) 4 bytes of the uint */
    UI32_T  low;         /* the low (lsb) 4 bytes of the uint  */
} UI64_T, COUNTER64_T;
#endif

#define UI64_T_TO_BIT64(a, x) 		do {x = (a).high; x = (x << 32) | (a).low;} while (0)
#define BIT64_TO_UI64_T(x, a) 		do {(a).low = (UI32_T)x; (a).high = (UI32_T)(x >> 32);} while (0)

#define KB(x)           ((x)*1024)
#define MB(x)           ((x)*1024*1024)

typedef UI32_T        	ST_PORT_T;
typedef UI16_T        	VID_T;
typedef unsigned char  	MAC_T[6];
typedef unsigned char  	MAC_ADDRESS_T[6];
typedef unsigned char  	PORTLIST_T[(MIB_CST_MAX_PORT_OF_STACK_BOX + 7) / 8];
//typedef unsigned char  	ST_PORTLIST_T[((MIB_CST_MAX_PORT_OF_STACK_BOX +7)/8)*MIB_CST_MAX_BOX_OF_STACK];
typedef I8_T		  	VLANNAME_T[32+4];		/* max vlan name = 32 */

typedef UI8_T  			VID_LIST_T[(4096+7)/8]; /* size: 512 bytes */

typedef UI32_T			IPV4_ADDRESS_T;

typedef UI8_T   		CLI_API_INTLIST_T[(CLI_LIST_MAX_NUM + 7) / 8];

typedef enum etag_port_storm_control_type_enum
{
    CLI_STORM_CTRL_NONE  = 0,
    CLI_STORM_CTRL_UNI   = 1,
	CLI_STORM_CTRL_MULTI = 2,
	CLI_STORM_CTRL_BROAD = 4,
	CLI_STORM_CTRL_ALL   = 7
} cli_sc_e;

typedef enum etag_cli_port_type
{
	CLI_PORT_TYPE_SNI,
	CLI_PORT_TYPE_PON,
	CLI_PORT_TYPE_MAX
} cli_ptype_e;

typedef struct stag_cli_port_id_type
{
	UI32_T 		slot_id;
	cli_ptype_e	port_type;
	UI32_T 		port_id;
} cli_pid_t;

typedef struct stag_cli_onu_id_type
{
	UI32_T 		slot_id;
	UI32_T 		port_id;
	UI32_T 		llid;
} cli_onuid_t;



#define INOUT

/* ERR_STR_T should be used for the type of error string, instead of using STR80_T or STR128_T. */
#define ERR_STR_T	STR128_T
/* This struct type specially for lacp error code */
typedef struct
{
	UI32_T			errorCode;  /* error code */
	ERR_STR_T		errorString; /* error string */
	UI32_T			cookie;     /* runtime variable. */
} ERROR_T;
#define   ERROR_COOKIE_NONE                 0x00


#define   ST_SET_NONE                       0x00



typedef enum enum_link_type
{
	CLI_LINK_TELNET,
	CLI_LINK_SERIAL,
	CLI_LINK_MAX
} cli_link_t;

typedef enum enum_language_type
{
	CLI_LAN_EN,
	CLI_LAN_CN,
	CLI_LAN_MAX
} cli_lan_t;

/*keystroke input mode*/
typedef enum
{
    CLI_INPUT_NORMAL   = 1,
    CLI_INPUT_INSERT
} CLI_INPUT_MODE_T;

typedef enum
{
    CLI_OUTPUT_NORMAL                = 1,    /* echo the same char user inputted */
    CLI_OUTPUT_WITHOUT_SPECIAL_CHAR,
    CLI_OUTPUT_PASSWORD                      /* echo asterisk for security data */
} cli_output_mode_e;

#define CLI_MAX_IPV6_INTERFACE_NAME_LEN 20 // include the terminate '\0'

typedef struct
{
    union
    {
        UI8_T  	u1ByteAddr[16];
        UI16_T  u2ShortAddr[8];
        UI32_T  u4WordAddr[4];
    } la3_ip6_addr_u;
} LA3_IP6ADDR;

typedef struct 
{
	LA3_IP6ADDR addr;
	UI16_T prefix[8];
} CLI_IPV6_NET_ADDR;

typedef struct 
{
	LA3_IP6ADDR addr;
	I8_T name[CLI_MAX_IPV6_INTERFACE_NAME_LEN];
} CLI_IPV6_ADDR;

typedef struct
{
    UI32_T              ipaddr;
    LA3_IP6ADDR         ipv6addr;
    BOOL_T              is_ipv6;
} CLI_IP_INFO_T;



#ifndef MEMCPY
#define MEMCPY(dst, src, n)  	memcpy(dst, src, n)
#endif
#ifndef MEMCMP
#define MEMCMP(s1, s2, n)   	memcmp(s1, s2, n)
#endif

#define ACTIVE_DEBUG_KERNEL() 	{*((int *)0) = 0;}

#define MEMSET(dst,val,size)	memset((dst),(val),(size))

#ifndef STRCMP
#define STRCMP(s1, s2)      	strcmp(s1, s2)
#endif
#ifndef STRCPY
#define STRCPY(dst, src)     	strcpy(dst, src)
#endif
#ifndef STRNCPY
#define  STRNCPY(d,s,n)    		strncpy((char *)(d), (const char *)(s), n)
#endif
#ifndef STRNCMP
#define  STRNCMP(s1,s2,n)  		strncmp((const char *)(s1), (const char *)(s2), n)
#endif
#ifndef STRLEN
#define STRLEN(s)            	strlen(s)
#endif
#ifndef STRCAT
#define STRCAT(d,s)				strcat(d,s)
#endif

typedef struct
{
	UI8_T			mainVersion;	/* mainversion */
	UI8_T	    	subVersion;
	UI16_T			minorSubVersion;
} VERSION_T;

#ifndef	 __packed__
#define __packed__
#endif

#ifndef NOT_USED
#define NOT_USED(x)		(void)(x)			/* no warning */
#endif

#ifndef NO_WARNING
#define NO_WARNING(x)	if (x) {}			/* no warning */
#endif
#ifndef MIPSEB
#define MIPSEB
#endif
/* big endian define */
#define CPU_IS_BIG_ENDIAN				1

#if CPU_IS_BIG_ENDIAN
#define ntohl(x) (UI32_T)(x)
#define ntohs(x) (UI16_T)(x)
#define htonl(x) (UI32_T)(x)
#define htons(x) (UI16_T)(x)
#else //LITTLE_ENDIAN TBD.
#endif


#define INTERRUPT_BEGIN(x)				/* interrupt function start point, for debug */

#ifndef MIN
#define	MIN(a, b)		(((a)<(b))?(a):(b))
#endif

#ifndef MAX
#define	MAX(a, b)		(((a)>(b))?(a):(b))
#endif

typedef unsigned long		UNSIGNED;


/******unstandard types***********************************************/

/* calucate element number of an array */
#define COUNT_OF(x)		(int)(sizeof(x) / sizeof((x)[0]))



#define CLI_COMPANY_AB "KT"

#define CLI_PRINT_FUNCTION(msg...) 	printf(msg)
#define CLI_FLUSH_FUNCTION() 		fflush(stdout)

/*
 * 打印调试、日志宏定义
 * LOG_FLAG_MODULE : 模块打印条件，由各模块自行定义，推荐定义在个模块.c源码文件中，并事先用undef取消原始模块条件
 *
 * LVL_DBGFUNC   : 调试函数级，例如进入函数、退出函数、函数中的tag标记等的打印信息；
 * LVL_DBGSMPL : 调试简易级，例如打印十六进制数据进行验证，而不需要多余的影响数据对齐时的打印信息；
 * LVL_DBGCPLX : 调试详细级，常用的普通调试信息；
 *
 * LVL_INFO : 初始级，设备初始化时，提供用户跟踪、观察进度的打印信息；
 * LVL_EVT  : 事件级，例如端口LinkUp，ONU注册等的打印信息；
 * LVL_WARN : 警告级，
 * LVL_ERR  : 错误级，
 * LVL_CMD  : 命令级，命令行专用；
 */

/* print level bit */
typedef enum etag_cli_print_level_bit
{
	/* 开发者级别 */
	CLI_LVL_DBGFUNC,	// 调试函数级
	CLI_LVL_DBGSMPL,	// 调试简易级
	CLI_LVL_DBGCPLX,	// 调试详细级

	/* 操作用户级别 */
	CLI_LVL_MSGINI,		// 初始化级
	CLI_LVL_MSGEVT,		// 事件级
	CLI_LVL_MSGWNG,		// 警告级
	CLI_LVL_MSGERR,		// 错误级

	CLI_LVL_CMD,		// 命令行级
	CLI_LVL_MORE, 		// 

	CLI_LVL_MAX
} cli_pt_lvl_t;

#ifdef BC_PT_DBG_FUN

#define CLI_DBG_FUN(l_mdl_id, msg...) 			BC_PT_DBG_FUN(l_mdl_id, msg)
#define CLI_DBG_SMP(l_mdl_id, msg...) 			BC_PT_DBG_SMP(l_mdl_id, msg)
#define CLI_DBG_CPL(l_mdl_id, msg...) 			BC_PT_DBG_CPL(l_mdl_id, msg)
#define CLI_MSG_INI(l_mdl_id, msg...) 			BC_PT_INIT(l_mdl_id, msg)
#define CLI_MSG_EVT(l_mdl_id, msg...) 			BC_PT_EVENT(l_mdl_id, msg)
#define CLI_MSG_WNG(l_mdl_id, msg...) 			BC_PT_WARNING(l_mdl_id, msg)
#define CLI_MSG_ERR(l_mdl_id, msg...) 			BC_PT_ERROR(l_mdl_id, msg)
#define CLI_CMD_PRT(l_mdl_id, msg...) 			BC_PT_COMMAND(l_mdl_id, msg)

#define CLI_DBG_ENTER(l_mdl_id) 				BC_PT_FUN_ENTER(l_mdl_id)
#define CLI_DBG_LEAVE(l_mdl_id) 				BC_PT_FUN_LEAVE(l_mdl_id)
#define CLI_DBG_TAG(l_mdl_id) 					BC_PT_FUN_TAG(l_mdl_id)

#define CLI_DBG_NOTSUPPORTED(l_mdl_id) 			BC_PT_FUN_NOTSUPPORTED(l_mdl_id)

#else

#define CLI_DBG_FUN(l_mdl_id, fmt, ...)     \
	do\
	{\
		UNUSED(l_mdl_id);\
		CLI_PRINT_FUNCTION("[%s-F]%s(%06d)(%s): ", CLI_COMPANY_AB, __FILE__, __LINE__, __FUNCTION__);\
		CLI_PRINT_FUNCTION(fmt, ##__VA_ARGS__);\
		CLI_FLUSH_FUNCTION();\
	} while (0)

#define CLI_DBG_SMP(l_mdl_id, fmt, ...)   \
    do\
	{\
		UNUSED(l_mdl_id);\
	    CLI_PRINT_FUNCTION(fmt, ##__VA_ARGS__);\
		CLI_FLUSH_FUNCTION();\
	} while (0)
			
#define CLI_DBG_CPL(l_mdl_id, fmt, ...)     \
	do\
	{\
		UNUSED(l_mdl_id);\
		CLI_PRINT_FUNCTION("[%s-D]%s(%06d): ", CLI_COMPANY_AB, __FILE__, __LINE__);\
		CLI_PRINT_FUNCTION(fmt, ##__VA_ARGS__);\
		CLI_FLUSH_FUNCTION();\
	} while (0)
		
#define CLI_MSG_INI(l_mdl_id, fmt, ...)   \
	do\
	{\
		UNUSED(l_mdl_id);\
		CLI_PRINT_FUNCTION(fmt, ##__VA_ARGS__);\
		CLI_FLUSH_FUNCTION();\
	} while (0)

#define CLI_MSG_EVT(l_mdl_id, fmt, ...)     \
	do\
	{\
		UNUSED(l_mdl_id);\
		CLI_PRINT_FUNCTION("[%s-V]: ", CLI_COMPANY_AB);\
		CLI_PRINT_FUNCTION(fmt, ##__VA_ARGS__);\
		CLI_FLUSH_FUNCTION();\
	} while (0)

#define CLI_MSG_WNG(l_mdl_id, fmt, ...)    \
	do\
	{\
		UNUSED(l_mdl_id);\
		CLI_PRINT_FUNCTION("[%s-W]: ", CLI_COMPANY_AB);\
		CLI_PRINT_FUNCTION(fmt, ##__VA_ARGS__);\
		CLI_FLUSH_FUNCTION();\
	} while (0)

#define CLI_MSG_ERR(l_mdl_id, fmt, ...)     \
	do\
	{\
		UNUSED(l_mdl_id);\
		CLI_PRINT_FUNCTION("\r\n[%s-R]: ", CLI_COMPANY_AB);\
		CLI_PRINT_FUNCTION(fmt, ##__VA_ARGS__);\
		CLI_FLUSH_FUNCTION();\
	} while (0)

#define CLI_CMD_PRT(l_mdl_id, fmt, ...)   \
    do\
	{\
	    CLI_PRINT_FUNCTION(fmt, ##__VA_ARGS__);\
	} while (0)


/* 0 < l_mdl_id < 0xFFFFFFFF */
#define CLI_PRT(level, l_mdl_id, msg...)       \
    do\
    {\
        switch (level)\
		{\
		case CLI_LVL_DBGFUNC:\
			CLI_DBG_FUN(l_mdl_id, msg);\
			break;\
		case CLI_LVL_DBGSMPL:\
			CLI_DBG_SMP(l_mdl_id, msg);\
			break;\
		case CLI_LVL_DBGCPLX:\
			CLI_DBG_CPL(l_mdl_id, msg);\
			break;\
		case CLI_LVL_MSGINI:\
			CLI_MSG_INI(l_mdl_id, msg);\
			break;\
		case CLI_LVL_MSGEVT:\
			CLI_MSG_EVT(l_mdl_id, msg);\
			break;\
		case CLI_LVL_MSGWNG:\
			CLI_MSG_WNG(l_mdl_id, msg);\
			break;\
		case CLI_LVL_MSGERR:\
			CLI_MSG_ERR(l_mdl_id, msg);\
			break;\
		case CLI_LVL_CMD:\
			CLI_CMD_PRT(msg);\
			break;\
		default:\
			break;\
		}\
    } while (0)



#define CLI_DBG_ENTER(l_mdl_id) 	        CLI_DBG_FUN(l_mdl_id, "enter...\r\n")
#define CLI_DBG_LEAVE(l_mdl_id) 	        CLI_DBG_FUN(l_mdl_id, "leave...\r\n")
#define CLI_DBG_TAG(l_mdl_id) 	        	CLI_DBG_FUN(l_mdl_id, "TAG\r\n")

#define CLI_DBG_NOTSUPPORTED(l_mdl_id)    	CLI_MSG_WNG(l_mdl_id, "*** not supported ***\r\n")

#endif

#define xprintf(msg...)						CLI_CMD_PRT(l_mdl_id, msg)
#define CLI_API_Printf(sid, msg...)			CLI_CMD_PRT(l_mdl_id, msg)



/* Restore the type of monthday to be UI16_T, for backward compatibility */
typedef struct
{
    UI16_T	year;			/* year (A.D.)             */
	UI8_T	month;			/* month, January=1, ...   */
	UI16_T	monthday;		/* day of month            */
	UI8_T	weekday;		/* Sun=0, Mon=1, ...       */
	UI8_T	hour;			/* hour of day, midnight=0 */
	UI8_T	minute;			/* minute of hour          */
	UI8_T	second;			/* second of minute        */
} DEV_RTC_TIME_T;

typedef enum
{
    SNTP_IF_JAN = 1,
    SNTP_IF_FEB,
    SNTP_IF_MAR,
    SNTP_IF_APR,
    SNTP_IF_MAY,
    SNTP_IF_JUN,
    SNTP_IF_JUL,
    SNTP_IF_AUG,
    SNTP_IF_SET,
    SNTP_IF_OCT,
    SNTP_IF_NOV,
    SNTP_IF_DEC
} SNTP_IF_MONTHES;

typedef enum
{
    SNTP_IF_SUN = 0,
    SNTP_IF_MON,
    SNTP_IF_TUE,
    SNTP_IF_WED,
    SNTP_IF_THU,
    SNTP_IF_FRI,
    SNTP_IF_SAT
} SNTP_IF_WEEK_T;

typedef enum
{
    SNTP_IF_LAST_WEEK = 0,
    SNTP_IF_FIRST_WEEK,
    SNTP_IF_SECOND_WEEK,
    SNTP_IF_THIRD_WEEK,
    SNTP_IF_FOURTH_WEEK
} SNTP_IF_WEEK_NUM_T;

typedef struct
{
    SNTP_IF_WEEK_NUM_T  week_num;/* 1 ~ 5, LAST, FIRST, ... */
    SNTP_IF_WEEK_T      week_day;/* 0 ~ 6, SUN, MON, ... */
    SNTP_IF_MONTHES     month;   /* 1 ~ 12,JAN, FEB, ... */
    UI8_T               hour;
    UI8_T               minute;
} SNTP_IF_DST_T;



////////////////////////////////////////////////////////////////////////////////
//																			  //
//					结 构 体 、联 合 体、枚 举 定 义						  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#define NULL_POINTER_CHECK(x) \
	do \
	{ \
		if (NULL == (x)) \
		{ \
			CLI_MSG_ERR(l_mdl_id, "FAIL : NULL pointer check at %s(%d)\n\r", __FILE__,__LINE__); \
		} \
	} while (0)

#define STDIO_putchar(ch)			CLI_CMD_PRT(-1, "%c", (ch))
//#define STDIO_getcharT(to)		getchar()



////////////////////////////////////////////////////////////////////////////////
//																			  //
//						外 部 变 量、 函 数 声 明							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////




#endif /* __INC_BC_CLI_TYPE_H__ */


