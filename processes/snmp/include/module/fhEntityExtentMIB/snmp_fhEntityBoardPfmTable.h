/*******************************************************************************
  [Author]	   : bain.wang@outlook.com.uestc@gmail.com
  [Version]    : 1.0
  [Date]       : 2017-06-11
  [Description]:

  [Others]     :

  [Function List]:  
    1. ....
    2. ....
  [History]:
	 D a t e    Modification 										  Initials
	---------- --------------                                        ----------
	2016-06-03  Created												  bain.wang@outlook.com
*******************************************************************************/
#ifndef __SNMP_FHENTITYBOARDPFMTABLE_H__
#define __SNMP_FHENTITYBOARDPFMTABLE_H__

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
#define FHENTITYBOARDPFMTABLE_INDEX_NUM			1
#define FHENTITYBOARDPFMTABLE_OID_LEN				12		/*����OID����*/
#define FHENTITYBOARDPFMTABLE_OID_NODE_LEN		(FHENTITYBOARDPFMTABLE_OID_LEN+2)/*Ҷ�ӽ��OID����*/
#define FHENTITYBOARDPFMTABLE_OID_FULL_LEN		(FHENTITYBOARDPFMTABLE_OID_NODE_LEN+FHENTITYBOARDPFMTABLE_INDEX_NUM)/*�������OID����*/

/* column number definitions for table fhEntityBoardPfmTable */
       #define COLUMN_FHBOARDPFMINDEX				1
       #define COLUMN_FHBOARDTEMPERATURE		3
       #define COLUMN_FHBOARDVOLTAGE			4



////////////////////////////////////////////////////////////////////////////////
//																			  //
//					�� �� �� ���� �� �塢ö �� �� ��						  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
/*
 * Typical data structure for a row entry 
 */
struct fhEntityBoardPfmTable_entry
{
    /*
     * Index values 
     */
    long            fhBoardPfmIndex;

    /*
     * Column values 
     */
    char fhBoardTemperature[SNMP_DEV_NAME_LEN];
    char fhBoardVoltage[SNMP_DEV_NAME_LEN];

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
void snmp_fhEntityBoardPfmTable_init(void);

#endif /* __SNMP_FHENTITYBOARDPFMTABLE_H__ */
