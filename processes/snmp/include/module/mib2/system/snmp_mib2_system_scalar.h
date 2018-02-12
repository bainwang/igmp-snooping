/*******************************************************************************
  [Author]	   : bain.wang@outlook.com.uestc@gmail.com
  [Version]    : 1.0
  [Date]       : 2017-02-27
  [Description]:

  [Others]     :

  [Function List]:  
    1. ....
    2. ....
  [History]:
	 D a t e    Modification 										  Initials
	---------- --------------                                        ----------
	2017-02-27  Created												  bain.wang@outlook.com
*******************************************************************************/
#ifndef __SNMP_FHENTITYSTATE_H__
#define __SNMP_FHENTITYSTATE_H__

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								头   文   件								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include "bc_common_defs.h"
#include "snmp_global.h"
#include "snmp_core_ex.h"

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								宏   定   义								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
/*system*/
#define 	SNMP_SYS_DESCR_LEN			256
#define	SNMP_SYS_CANTACT_LEN			256
#define	SNMP_SYS_NAME_LEN			256
#define	SNMP_SYS_LOCATION_LEN		256
#define	SNMP_SYS_SERVICE				256


////////////////////////////////////////////////////////////////////////////////
//																			  //
//					结 构 体 、联 合 体、枚 举 定 义						  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	bc_char		sysDescr[SNMP_SYS_DESCR_LEN];
	oid				sysObjectID[MAX_OID_LEN];
	bc_int32		sysObjectID_len;
	bc_int32		sysUpTime;
	bc_char		sysContact[SNMP_SYS_CANTACT_LEN];
	bc_char		sysName[SNMP_SYS_NAME_LEN];
	bc_char		sysLocation[SNMP_SYS_LOCATION_LEN];
	bc_int32		sysServices;
} snmp_mib2_sys_mib_t;


////////////////////////////////////////////////////////////////////////////////
//																			  //
//						外 部 变 量、 函 数 声 明							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
void snmp_mib2_system_scalar_init(void);

#endif /* __SNMP_FHENTITYSTATE_H__ */

