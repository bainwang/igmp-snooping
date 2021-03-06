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
#ifndef __SNMP_FHENTITYIFPFMTABLE_H__
#define __SNMP_FHENTITYIFPFMTABLE_H__

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
#define FHENTITYIFPFMTABLE_INDEX_NUM			1
#define FHENTITYIFPFMTABLE_OID_LEN				12		/*表的OID个数*/
#define FHENTITYIFPFMTABLE_OID_NODE_LEN		(FHENTITYIFPFMTABLE_OID_LEN+2)/*叶子结点OID个数*/
#define FHENTITYIFPFMTABLE_OID_FULL_LEN		(FHENTITYIFPFMTABLE_OID_NODE_LEN+FHENTITYIFPFMTABLE_INDEX_NUM)/*完整结点OID个数*/

/* column number definitions for table fhEntityIfPfmTable */
       #define COLUMN_FHIFPFMINDEX				1




////////////////////////////////////////////////////////////////////////////////
//																			  //
//					结 构 体 、联 合 体、枚 举 定 义						  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
/*
 * Typical data structure for a row entry 
 */
struct fhEntityIfPfmTable_entry
{
    /*
     * Index values 
     */
    long            fhIfPfmIndex;

    /*
     * Column values 
     */
	

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
void snmp_fhEntityIfPfmTable_init(void);

#endif /* __SNMP_FHENTITYIFPFMTABLE_H__ */


