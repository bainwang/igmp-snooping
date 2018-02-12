/*******************************************************************************
  [File name]	: mcast_def.h
  [Author]     	: bain.wang@outlook.com
  [Version]    	: 1.0
  [Date]       	: 2017-06-13
  [Description]	:
	Multicast module type
  [Others]     	:
	NULL
  [Function List]:  
    1. ....
    2. ....
  [History]:
	 D a t e      	Modification 							 Initials
	---------- 	--------------                                        ----------
	2017-06-13  	Created								 bain.wang@outlook.com
*******************************************************************************/

#ifndef __mcast_def_h__
#define __mcast_def_h__


#define BC_MULTICAST_INCLUDE	 1

#if BC_MULTICAST_INCLUDE

#define MCAST_WINDOWS_TEST	0
#include <stdio.h>

#include "bc_common_defs.h"
#include "bc_port_def.h"
/* -------------------- Protocol -------------------- */

#define MCAST_ROBUSTNESS_VARIABLE	2
#define MCAST_ROBUSTNESS_VARIABLE_MAX	7
#define MCAST_QUERY_INTERVAL    		125      	/* seconds */
#define MCAST_QUERY_RESPONSE_INTERVAL 10		/* seconds */
#define MCAST_LAST_MEMBER_QUERY_INTERVAL 1	/* seconds */
#define MCAST_UNSOLICITED_REPORT_INTERVAL 1	/* seconds */   

/* (1 sec / MCAST_TASK_TIC_INTERVAL) == 100 millisecond, 
so every 100 millisecond interval, task proc once */
#define MCAST_TASK_TIC_INTERVAL	10		
#define MCAST_TIC_CAL(sec)	(bc_uint16)((sec)*MCAST_TASK_TIC_INTERVAL)

#define MCAST_TIC_INTERVAL		100*1000  /* millisecond */

#define MCAST_QUERY_IP			0xE0000001  	/* 224.0.0.1 */
#define MCAST_V3_REPORT_IP		0xE0000016	/* 224.0.0.22 */

#define MCAST_PBC_DEFAULT_PRIO	5

/* -------------------- Configure -------------------- */

/*
   If Max Resp Code < 128, Max Resp Time = Max Resp Code

   If Max Resp Code >= 128, Max Resp Code represents a floating-point
   value as follows:

       0 1 2 3 4 5 6 7
      +-+-+-+-+-+-+-+-+
      |1| exp | mant  |
      +-+-+-+-+-+-+-+-+

   Max Resp Time = (mant | 0x10) << (exp + 3)
*/
#define MCAST_MAX_RESP_TIME_MAX	0x3c00
#define MCAST_MAX_RESP_TIME_MIN	10	/* protocol no define it */

#define MCAST_ROBUSTNESS_MAX 	7
#define MCAST_ROBUSTNESS_MIN 	2

/*
   If QQIC < 128, QQI = QQIC

   If QQIC >= 128, QQIC represents a floating-point value as follows:

       0 1 2 3 4 5 6 7
      +-+-+-+-+-+-+-+-+
      |1| exp | mant  |
      +-+-+-+-+-+-+-+-+

   QQI = (mant | 0x10) << (exp + 3)
*/
#define MCAST_QUERY_INTERVAL_MAX	0x3c00
#define MCAST_QUERY_INTERVAL_MIN	10	/* protocol no define it */

#define MCAST_LAST_MEMBER_QUERY_INTERVAL_MAX 0x3c00
#define MCAST_LAST_MEMBER_QUERY_INTERVAL_MIN 10

#define MCAST_LAST_MEMBER_QUERY_COUNT_MAX 7
#define MCAST_LAST_MEMBER_QUERY_COUNT_MIN 2

/* -------------------- Configure Group -------------------- */

#define MCAST_CFG_GRP_MAX	 512

#define MCAST_CFG_GRP_NAME 256

#define MCAST_CFG_GRP_ABW_MAX	(1000*1024*1024)
#define MCAST_CFG_GRP_ABW_MIN	(64*1024)


/* -------------------- Controlled Multicast -------------------- */

#define MCAST_CM_PACKAGE_MAX	128

#define MCAST_CM_PACKAGE_NAME MCAST_CFG_GRP_NAME
#define MCAST_CM_MAX_REQUEST_CHANNEL  MCAST_CFG_GRP_MAX
#define MCAST_CM_MAX_SINGLE_PREVIEW_TIME	(24*60*60)  /* 1 day */
#define MCAST_CM_MAX_PREVIEW_COUNT	100
#define MCAST_CM_MAX_TOTAL_PREVIEW_TIME		(MCAST_CM_MAX_PREVIEW_COUNT)*(MCAST_CM_MAX_SINGLE_PREVIEW_TIME)
#define MCAST_CM_MAX_RESET_PREVIEW_TIME		(24*60*60)  /* 1 day */
#define MCAST_CM_MAX_INTERVAL_PREVIEW_TIME		(24*60*60)  /* 1 day */
#define MCAST_CM_SINGLE_DONT_TIMEOUT 0xFFFFFFFF

#define MCAST_CM_AUTH_GLOBAL_BW		(1024*1024)	/* units: kbps */

/* -------------------- ONU Configure -------------------- */

#define MCAST_ONU_CFG_STATE	FALSE
#define MCAST_ONU_CFG_MODE	MCAST_MODE_DISABLE
#define MCAST_ONU_CFG_MQRT	MCAST_QUERY_RESPONSE_INTERVAL
#define MCAST_ONU_CFG_ROBST	MCAST_ROBUSTNESS_VARIABLE
#define MCAST_ONU_CFG_QI		MCAST_QUERY_INTERVAL
#define MCAST_ONU_CFG_LMQI	MCAST_LAST_MEMBER_QUERY_INTERVAL
#define MCAST_ONU_CFG_LMQC	MCAST_ROBUSTNESS_VARIABLE
#define MCAST_ONU_CFG_VER		MCAST_IGMP_V2

#define MCAST_ONU_CFG_VLAN_STATE	FALSE

#define MCAST_ONU_CFG_VLANTAG_STATE FALSE

/* -------------------- VLAN -------------------- */

#define MCAST_VLAN_MAX		256

/* -------------------- Group -------------------- */

#define MCAST_GRP_MAX			1024
#define MCAST_GRP_SRC_MAX		64

#endif
#endif

