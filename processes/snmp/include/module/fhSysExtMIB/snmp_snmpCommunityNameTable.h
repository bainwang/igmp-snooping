/*******************************************************************************
  [Author]	   : bain.wang@outlook.com.uestc@gmail.com
  [Version]    : 1.0
  [Date]       : 2017-02-25
  [Description]:

  [Others]     :

  [Function List]:  
    1. ....
    2. ....
  [History]:
	 D a t e    Modification 										  Initials
	---------- --------------                                        ----------
	2017-02-25  Created												  bain.wang@outlook.com
*******************************************************************************/
#ifndef __SNMP_SNMPCOMMUNITYNAMETABLE_H__
#define __SNMP_SNMPCOMMUNITYNAMETABLE_H__

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								ͷ   ��   ��								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include "bc_common_defs.h"
#include "snmp_global.h"
#include "snmp_core_ex.h"

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								��   ��   ��								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
#define SNMPCOMMUNITYNAMETABLE_INDEX_NUM			1
#define SNMPCOMMUNITYNAMETABLE_OID_LEN				11
#define SNMPCOMMUNITYNAMETABLE_OID_NODE_LEN		(SNMPCOMMUNITYNAMETABLE_OID_LEN+2)
#define SNMPCOMMUNITYNAMETABLE_OID_FULL_LEN		(SNMPCOMMUNITYNAMETABLE_OID_NODE_LEN+SNMPCOMMUNITYNAMETABLE_INDEX_NUM)

/* column number definitions for table snmpCommunityNameTable */
#define COLUMN_SNMPCOMMUNITYINDEX						1
#define COLUMN_SNMPCOMMUNITYNAME		2



////////////////////////////////////////////////////////////////////////////////
//																			  //
//					�� �� �� ���� �� �塢ö �� �� ��						  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
/*
 * Typical data structure for a row entry 
 */
struct snmpCommunityNameTable_entry
{
    /*
     * Index values 
     */
    long            snmpCommunityIndex;

    /*
     * Column values 
     */
    char snmpCommunityName[SNMP_DEV_NAME_LEN];

	time_t			update_time;/*2017.02.20*/
    /*
     * Illustrate using a simple linked list 
     */
    int             storageType;
};


////////////////////////////////////////////////////////////////////////////////
//																			  //
//						�� �� �� ���� �� �� �� ��							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
void snmp_snmpCommunityNameTable_init(void);

#endif /* __SNMP_SNMPCOMMUNITYNAMETABLE_H__ */

