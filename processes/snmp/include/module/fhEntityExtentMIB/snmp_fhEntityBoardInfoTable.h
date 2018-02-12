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
#ifndef __SNMP_FHENTITYBOARDINFOTABLE_H__
#define __SNMP_FHENTITYBOARDINFOTABLE_H__

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								头   文   件								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>

#include "snmp_global.h"
#include "snmp_core_ex.h"

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								宏   定   义								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
#define FHENTITYBOARDINFOTABLE_INDEX_NUM			1
#define FHENTITYBOARDINFOTABLE_OID_LEN				11		/*表的OID个数*/
#define FHENTITYBOARDINFOTABLE_OID_NODE_LEN		(FHENTITYBOARDINFOTABLE_OID_LEN+2)/*叶子结点OID个数*/
#define FHENTITYBOARDINFOTABLE_OID_FULL_LEN		(FHENTITYBOARDINFOTABLE_OID_NODE_LEN+FHENTITYBOARDINFOTABLE_INDEX_NUM)/*完整结点OID个数*/

/* column number definitions for table fhEntityBoardInfoTable */
       #define COLUMN_FHBOARDENTITYINDEX		1
       #define COLUMN_FHBOARDENTITYNO			2
       #define COLUMN_FHBOARDHARDWAREREV		8
       #define COLUMN_FHBOARDSLOTSEQ			9
       #define COLUMN_FHBOARDSLOTNUM			10
       #define COLUMN_FHBOARDOPERSTATUS			11
       #define COLUMN_FHHARDWARETYPE			19
       #define COLUMN_FHBOARDIDLESTATUS			22



////////////////////////////////////////////////////////////////////////////////
//																			  //
//					结 构 体 、联 合 体、枚 举 定 义						  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
/*
 * Typical data structure for a row entry 
 */
struct fhEntityBoardInfoTable_entry
{
    /*
     * Index values 
     */
    long            fhBoardEntityIndex;

    /*
     * Column values 
     */
    long fhBoardEntityNo;
    char fhBoardHardwareRev[SNMP_DEV_NAME_LEN];
    long fhBoardSlotSeq;
    long fhBoardSlotNum;
    char fhBoardOperStatus[SNMP_DEV_NAME_LEN];
    char fhHardwareType[SNMP_DEV_NAME_LEN];
    long fhBoardIdleStatus;

	time_t			update_time;/*2017.02.20*/
    /*
     * Illustrate using a simple linked list 
     */
    int             storageType;
};


////////////////////////////////////////////////////////////////////////////////
//																			  //
//						外 部 变 量、 函 数 声 明							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
void snmp_fhEntityBoardInfoTable_init(void);

#endif /* __SNMP_FHENTITYBOARDINFOTABLE_H__ */

