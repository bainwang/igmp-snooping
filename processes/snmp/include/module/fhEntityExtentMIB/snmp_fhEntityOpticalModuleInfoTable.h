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
#ifndef __SNMP_FHENTITYOPTICALMODULEINFOTABLE_H__
#define __SNMP_FHENTITYOPTICALMODULEINFOTABLE_H__

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
#define FHENTITYOPTICALMODULEINFOTABLE_INDEX_NUM			1
#define FHENTITYOPTICALMODULEINFOTABLE_OID_LEN				11		/*表的OID个数*/
#define FHENTITYOPTICALMODULEINFOTABLE_OID_NODE_LEN		(FHENTITYOPTICALMODULEINFOTABLE_OID_LEN+2)/*叶子结点OID个数*/
#define FHENTITYOPTICALMODULEINFOTABLE_OID_FULL_LEN		(FHENTITYOPTICALMODULEINFOTABLE_OID_NODE_LEN+FHENTITYOPTICALMODULEINFOTABLE_INDEX_NUM)/*完整结点OID个数*/

/* column number definitions for table fhEntityOpticalModuleInfoTable */
       #define COLUMN_FHENTITYOPTICALINDEX				1
       #define COLUMN_FHENTITYOPTICALWAVELENGTH		3
       #define COLUMN_FHENTITYOPTICALTRANSDISTANCE		4
       #define COLUMN_FHENTITYOPTICALMEDIATYPE			5
       #define COLUMN_FHENTITYRXOPTICALPOWER			6
       #define COLUMN_FHENTITYTXOPTICALPOWER			7
       #define COLUMN_FHENTITYOPTICALSPEED				12



////////////////////////////////////////////////////////////////////////////////
//																			  //
//					结 构 体 、联 合 体、枚 举 定 义						  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
/*
 * Typical data structure for a row entry 
 */
struct fhEntityOpticalModuleInfoTable_entry
{
    /*
     * Index values 
     */
    long            fhEntityOpticalIndex;

    /*
     * Column values 
     */
    long fhEntityOpticalWavelength;
    long fhEntityOpticalTransDistance;
    long fhEntityOpticalMediaType;
    long fhEntityRxOpticalPower;
    long fhEntityTxOpticalPower;
    char fhEntityOpticalSpeed[SNMP_DEV_NAME_LEN];

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
void snmp_fhEntityOpticalModuleInfoTable_init(void);

#endif /* __SNMP_FHENTITYOPTICALMODULEINFOTABLE_H__ */

