/************************************************************
  FileName: proj_defs.h
  Author:  bain.wang@outlook.com      Version :  1.0        Date:2017-6-1
  Description: proj depend parameter define       
  Version:                        
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/


#ifndef __bc_proj_port_defs_h__
#define __bc_proj_port_defs_h__

#include "bc_common_defs.h"
#include "bc_modules.h"
#include "bc_print.h"
#include "bc_err.h"


/*---------- BC_MODULE_PORT START ----------*/
#ifdef BC_PRJ_NAME_DEV

#define	BC_PORT_INCLUDE_PON		    

#define	BC_PORT_PON_MAX_COUNT		    48
#define	BC_PORT_SNI_MAX_COUNT		    8
#define	BC_PORT_MANAGE_MAX_COUNT		2


#define	BC_PORT_MAX_COUNT			    (BC_PORT_PON_MAX_COUNT + BC_PORT_SNI_MAX_COUNT + BC_PORT_MANAGE_MAX_COUNT)
#define	BC_PORT_SNI_MIN_SLOTNUM		    3
#define	BC_PORT_SNI_MAX_SLOTNUM		    3
#define	BC_PORT_SNI_MIN_PORTNUM		    1
#define	BC_PORT_SNI_MAX_PORTNUM		    8

#define 	BC_PORT_SNI_MIN_SLOT_STR 	"3"
#define 	BC_PORT_SNI_MAX_SLOT_STR 	"3"
#define   BC_PORT_SNI_MIN_PORT_STR		"1"
#define 	BC_PORT_SNI_MAX_PORT_STR	"8"

#define	BC_PORT_PON_MIN_SLOTNUM		    4
#define	BC_PORT_PON_MAX_SLOTNUM		    6
#define	BC_PORT_PON_MIN_PORTNUM		    1
#define	BC_PORT_PON_MAX_PORTNUM		    16

#define 	BC_PORT_PON_MIN_SLOT_STR 	"4"
#define 	BC_PORT_PON_MAX_SLOT_STR 	"6"
#define   BC_PORT_PON_MIN_PORT_STR	"1"
#define 	BC_PORT_PON_MAX_PORT_STR	"16"

#define	BC_PORT_PON_CURRENT_SLOT_NUM		(BC_PORT_PON_MAX_SLOTNUM - BC_PORT_PON_MIN_SLOTNUM+1)

#define	BC_PORT_MAN_MIN_SLOTNUM		    0
#define	BC_PORT_MAN_MAX_SLOTNUM		    0
#define	BC_PORT_MAN_MIN_PORTNUM		    1
#define	BC_PORT_MAN_MAX_PORTNUM		    2

#else

#define	BC_PORT_INCLUDE_PON		    

#define	BC_PORT_PON_MAX_COUNT		    48
#define	BC_PORT_SNI_MAX_COUNT		    8
#define	BC_PORT_MANAGE_MAX_COUNT		2


#define	BC_PORT_MAX_COUNT			    (BC_PORT_PON_MAX_COUNT + BC_PORT_SNI_MAX_COUNT + BC_PORT_MANAGE_MAX_COUNT)
#define	BC_PORT_SNI_MIN_SLOTNUM		    3
#define	BC_PORT_SNI_MAX_SLOTNUM		    3
#define	BC_PORT_SNI_MIN_PORTNUM		    1
#define	BC_PORT_SNI_MAX_PORTNUM		    8

#define 	BC_PORT_SNI_MIN_SLOT_STR 	"3"
#define 	BC_PORT_SNI_MAX_SLOT_STR 	"3"
#define   BC_PORT_SNI_MIN_PORT_STR		"1"
#define 	BC_PORT_SNI_MAX_PORT_STR	"8"

#define	BC_PORT_PON_MIN_SLOTNUM		    4
#define	BC_PORT_PON_MAX_SLOTNUM		    6
#define	BC_PORT_PON_MIN_PORTNUM		    1
#define	BC_PORT_PON_MAX_PORTNUM		    16

#define 	BC_PORT_PON_MIN_SLOT_STR 	"4"
#define 	BC_PORT_PON_MAX_SLOT_STR 	"6"
#define   BC_PORT_PON_MIN_PORT_STR	"1"
#define 	BC_PORT_PON_MAX_PORT_STR	"16"

#define	BC_PORT_PON_CURRENT_SLOT_NUM		(BC_PORT_PON_MAX_SLOTNUM - BC_PORT_PON_MIN_SLOTNUM+1)

#define	BC_PORT_MAN_MIN_SLOTNUM		    0
#define	BC_PORT_MAN_MAX_SLOTNUM		    0
#define	BC_PORT_MAN_MIN_PORTNUM		    1
#define	BC_PORT_MAN_MAX_PORTNUM		    1

#endif

#if 0
#if 1
/*
	for igmp
	共三个槽，每槽16个端口，ID为1-16
*/
#define BC_PORT_MAX_CNT		48
#define BC_PORT_MIN_SLOTID		1
#define BC_PORT_MAX_SLOTID		3
#define BC_PORT_MIN_PORTID		1
#define BC_PORT_MIN_PORTID		16
#else
#define BC_PORT_UP_CNT		8
#define BC_PORT_DOWN_CNT	48
#define BC_PORT_MAX_CNT	(BC_PORT_UP_CNT+BC_PORT_DOWN_CNT)
#define BC_PORT_MIN_PORTID	1
#define BC_PORT_MAX_PORTID 16
#define BC_PORT_UP_MIN
#endif

/*---------- BC_MODULE_PORT END ----------*/

#endif
#endif

