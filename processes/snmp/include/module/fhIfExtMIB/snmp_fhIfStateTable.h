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
#ifndef __SNMP_FHIFSTATETABLE_H__
#define __SNMP_FHIFSTATETABLE_H__

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
#define FHIFSTATETABLE_INDEX_NUM			1
#define FHIFSTATETABLE_OID_LEN				11		/*表的OID个数*/
#define FHIFSTATETABLE_OID_NODE_LEN		(FHIFSTATETABLE_OID_LEN+2)/*叶子结点OID个数*/
#define FHIFSTATETABLE_OID_FULL_LEN		(FHIFSTATETABLE_OID_NODE_LEN+FHIFSTATETABLE_INDEX_NUM)/*完整结点OID个数*/

/* column number definitions for table fhIfStateTable */
       #define COLUMN_FHIFSTATEINDEX			1
       #define COLUMN_FHIFDESCR		2
       #define COLUMN_FHIFMODE		3



////////////////////////////////////////////////////////////////////////////////
//																			  //
//					结 构 体 、联 合 体、枚 举 定 义						  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
/*
 * Typical data structure for a row entry 
 */
struct fhIfStateTable_entry
{
    /*
     * Index values 
     */
    long            fhIfStateIndex;

    /*
     * Column values 
     */
    char fhIfDescr[SNMP_DEV_NAME_LEN];
    long fhIfMode;

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
void snmp_fhIfStateTable_init(void);

#endif /* __SNMP_FHIFSTATETABLE_H__ */

