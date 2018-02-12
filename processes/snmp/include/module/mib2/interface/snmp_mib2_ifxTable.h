#ifndef __SNMP_MIB2_IFXTABLE_H__
#define __SNMP_MIB2_IFXTABLE_H__


#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include "bc_common_defs.h"
#include "snmp_global.h"
#include "snmp_core_ex.h"

#define IFXTABLE_INDEX_NUM			1
#define IFXTABLE_OID_LEN				11		/*表的OID个数*/
#define IFXTABLE_OID_NODE_LEN		(IFXTABLE_OID_LEN+2)/*叶子结点OID个数*/
#define IFXTABLE_OID_FULL_LEN		(IFXTABLE_OID_NODE_LEN+IFXTABLE_INDEX_NUM)/*完整结点OID个数*/


#define NETSNMP_IFNAME         				0
#define NETSNMP_IFINMULTICASTPKTS         	1
#define NETSNMP_IFINBROADCASTPKTS          	2
#define NETSNMP_IFOUTMULTICASTPKTS           	3
#define NETSNMP_IFOUTBROADCASTPKTS         	4
#define NETSNMP_IFHCINOCTETS   				5
#define NETSNMP_IFHCINUCASTPKTS   			6
#define NETSNMP_IFHCINMULTICASTPKTS    	7
#define NETSNMP_IFHCINBROADCASTPKTS    	8
#define NETSNMP_IFHCOUTOCTETS      			9
#define NETSNMP_IFHCOUTUCASTPKTS   		10
#define NETSNMP_IFHCOUTMULTICASTPKTS  	11
#define NETSNMP_IFHCOUTBROADCASTPKTS    	12
#define NETSNMP_IFLINKUPDOWNTRAPENABLE	13
#define NETSNMP_IFHIGHSPEED 				14
#define NETSNMP_IFPROMISCUOUSMODE     		15
#define NETSNMP_IFCONNECTORPRESENT  		16
#define NETSNMP_IFALIAS					17
#define NETSNMP_IFCOUNTERDISCONTINUITYTIME   	18



struct snmp_ifx_entry
{
	bc_int32	ifIndex;
	bc_char		ifName[256];
	bc_int32	ifInMulticastPkts;
	bc_int32	ifInBroadcastPkts;
	bc_int32	ifOutMulticastPkts;
	bc_int32	ifOutBroadcastPkts;
	bc_int64	ifHCInOctets;
	bc_int64	ifHCInUcastPkts;
	bc_int64	ifHCInMulticastPkts;
	bc_int64	ifHCInBroadcastPkts;
	bc_int64	ifHCOutOctets;
	bc_int64	ifHCOutUcastPkts;
	bc_int64	ifHCOutMulticastPkts;
	bc_int64	ifHCOutBroadcastPkts;
	bc_int32	ifLinkUpDownTrapEnable;
	bc_int32	ifHighSpeed;
	bc_int32	ifPromiscuousMode;
	bc_int32	ifConnectorPresent;
	bc_char		ifAlias[64];
	bc_int32	ifCounterDiscontinuityTime;
	
    bc_int32	storageType;
};




/** other required module components */
config_require(header_complex);


void snmp_mib2_ifx_init(void);


#endif 
