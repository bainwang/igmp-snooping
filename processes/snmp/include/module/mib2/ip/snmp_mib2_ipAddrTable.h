/*******************************************************************************
  [Author]	   : bain.wang@outlook.com.uestc@gmail.com
  [Version]    : 1.0
  [Date]       : 2017-03-01 
  [Description]:

  [Others]     :

  [Function List]:  
    1. ....
    2. ....
  [History]:
	 D a t e    Modification 										  Initials
	---------- --------------                                        ----------
	2017-03-01   Created												  bain.wang@outlook.com
*******************************************************************************/

#ifndef __SNMP_MIB2_IPADDRTABLE_H__
#define __SNMP_MIB2_IPADDRTABLE_H__

#define RFC_1213_MIB

#ifndef RFC_1213_MIB

//#ifndef __SNMP_MIB2_IPADDRTABLE_H__
//#define __SNMP_MIB2_IPADDRTABLE_H__

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
#define IPADDRTABLE_INDEX_NUM			4	//ip
#define IPADDRTABLE_OID_LEN				8		/*表的OID个数*/
#define IPADDRTABLE_OID_NODE_LEN		(IPADDRTABLE_OID_LEN+2)/*叶子结点OID个数*/
#define IPADDRTABLE_OID_FULL_LEN		(IPADDRTABLE_OID_NODE_LEN+IPADDRTABLE_INDEX_NUM)/*完整结点OID个数*/

/* column number definitions for table ipAddrTable */
       #define COLUMN_IPADENTADDR				1
       #define COLUMN_IPADENTIFINDEX				2
       #define COLUMN_IPADENTNETMASK			3
       #define COLUMN_IPADENTBCASTADDR			4
       #define COLUMN_IPADENTREASMMAXSIZE		5



////////////////////////////////////////////////////////////////////////////////
//																			  //
//					结 构 体 、联 合 体、枚 举 定 义						  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
/*
 * Typical data structure for a row entry 
 */
struct ipAddrTable_entry
{
    /*
     * Index values 
     */
    in_addr_t             ipAdEntAddr; 

    /*
     * Column values 
     */
    long ipAdEntIfIndex;
    in_addr_t ipAdEntNetMask;
    in_addr_t ipAdEntBcastAddr;
    long ipAdEntReasmMaxSize;

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
void snmp_ipAddrTable_init(void);

#else

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include "bc_common_defs.h"
#include "snmp_global.h"
#include "snmp_core_ex.h"

#if 1
/*
 *  Template MIB group interface - ipAddr.h
 *
 */
#ifndef _MIBGROUP_IPADDR_H
#define _MIBGROUP_IPADDR_H

//#if !defined(NETSNMP_ENABLE_MFD_REWRITES)
//config_require(mibII/ip)
//#endif

     extern snmp_find_var_callback var_ipAddrEntry;

#endif                          /* _MIBGROUP_IPADDR_H */


#endif

#ifndef _MIBGROUP_VAR_ROUTE_H
#define _MIBGROUP_VAR_ROUTE_H

config_require(mibII/ip)
config_arch_require(solaris2, kernel_sunos5)

     void            init_var_route(void);
#if defined(RTENTRY_4_4) && !defined(hpux11)
     struct radix_node;
     void            load_rtentries(struct radix_node *);
#endif
#if defined(freebsd2) || defined(netbsd1) || defined(bsdi2) || defined(openbsd2)
     struct sockaddr_in *klgetsa(struct sockaddr_in *);
#endif

     extern snmp_find_var_callback var_ipRouteEntry;

#if !defined(hpux11) && !defined(solaris2)
     RTENTRY **netsnmp_get_routes(size_t *out_numroutes);
#endif

#endif                          /* _MIBGROUP_VAR_ROUTE_H */

/*
 *  Template MIB group interface - ip.h
 *
 */

#ifndef _MIBGROUP_IP_H
#define _MIBGROUP_IP_H


config_require(mibII/ifTable)
config_require(mibII/ipAddr)
config_require(mibII/at)
config_require(mibII/var_route mibII/route_write)

config_arch_require(solaris2,        kernel_sunos5)
config_arch_require(linux,     mibII/kernel_linux)
config_arch_require(netbsd,    mibII/kernel_netbsd)
config_arch_require(netbsd5,   mibII/kernel_netbsd)
config_arch_require(netbsd6,   mibII/kernel_netbsd)
config_arch_require(netbsdelf, mibII/kernel_netbsd)
config_arch_require(netbsdelf5, mibII/kernel_netbsd)

//#include "var_route.h"
//#include "route_write.h"

extern void     init_ip(void);
extern snmp_ns_node_handler ip_handler;
extern NetsnmpCacheLoad ip_load;
extern NetsnmpCacheFree ip_free;

#ifdef USING_MIBII_AT_MODULE
//#include "at.h"                 /* for var_atEntry() */
#endif


#define IPFORWARDING	  1
#define IPDEFAULTTTL	  2
#define IPINRECEIVES	  3
#define IPINHDRERRORS	  4
#define IPINADDRERRORS	  5
#define IPFORWDATAGRAMS   6
#define IPINUNKNOWNPROTOS 7
#define IPINDISCARDS	  8
#define IPINDELIVERS	  9
#define IPOUTREQUESTS	 10
#define IPOUTDISCARDS	 11
#define IPOUTNOROUTES	 12
#define IPREASMTIMEOUT	 13
#define IPREASMREQDS	 14
#define IPREASMOKS	 15
#define IPREASMFAILS	 16
#define IPFRAGOKS	 17
#define IPFRAGFAILS	 18
#define IPFRAGCREATES	 19
#define IPADDRTABLE	 20	/* Placeholder */
#define IPROUTETABLE	 21	/* Placeholder */
#define IPMEDIATABLE	 22	/* Placeholder */
#define IPROUTEDISCARDS	 23

#define IPADADDR	  1
#define IPADIFINDEX	  2
#define IPADNETMASK	  3
#define IPADBCASTADDR	  4
#define IPADREASMMAX	  5

#define IPROUTEDEST	  1
#define IPROUTEIFINDEX	  2
#define IPROUTEMETRIC1	  3
#define IPROUTEMETRIC2	  4
#define IPROUTEMETRIC3	  5
#define IPROUTEMETRIC4	  6
#define IPROUTENEXTHOP	  7
#define IPROUTETYPE	  8
#define IPROUTEPROTO	  9
#define IPROUTEAGE	 10
#define IPROUTEMASK	 11
#define IPROUTEMETRIC5	 12
#define IPROUTEINFO	 13

/* #define IPMEDIAIFINDEX		1 */
/* #define IPMEDIAPHYSADDRESS	2 */
/* #define IPMEDIANETADDRESS	3 */
/* #define IPMEDIATYPE		4 */

#endif                          /* _MIBGROUP_IP_H */


/*
 *  Template MIB group interface - route_write.h
 *
 */
#ifndef _MIBGROUP_ROUTE_WRITE_H
#define _MIBGROUP_ROUTE_WRITE_H

#if !defined(NETSNMP_ENABLE_MFD_REWRITES)
config_require(mibII/ip)
#endif

     int             addRoute(u_long, u_long, u_long, u_short);
     int             delRoute(u_long, u_long, u_long, u_short);
     struct rtent   *findCacheRTE(u_long);
     struct rtent   *newCacheRTE(void);
     int             delCacheRTE(u_long);
     struct rtent   *cacheKernelRTE(u_long);
     WriteMethod     write_rte;

#endif                          /* _MIBGROUP_ROUTE_WRITE_H */




#if 1
//#ifndef _MIBGROUP_IP_H
//#define _MIBGROUP_IP_H


config_require(mibII/ifTable)
config_require(mibII/ipAddr)
config_require(mibII/at)
config_require(mibII/var_route mibII/route_write)

config_arch_require(solaris2,        kernel_sunos5)
config_arch_require(linux,     mibII/kernel_linux)
config_arch_require(netbsd,    mibII/kernel_netbsd)
config_arch_require(netbsd5,   mibII/kernel_netbsd)
config_arch_require(netbsd6,   mibII/kernel_netbsd)
config_arch_require(netbsdelf, mibII/kernel_netbsd)
config_arch_require(netbsdelf5, mibII/kernel_netbsd)

//#include "var_route.h"
//#include "route_write.h"

extern void     __init_ip(void);
extern snmp_ns_node_handler ip_handler;
extern NetsnmpCacheLoad ip_load;
extern NetsnmpCacheFree ip_free;
/*
 *  Template MIB group interface - at.h
 * IPMEDIAIFINDEX
 */

//#ifndef _MIBGROUP_AT_H
//#define _MIBGROUP_AT_H

config_arch_require(solaris2, kernel_sunos5)

     extern void     init_at(void);
     extern snmp_find_var_callback var_atEntry;


#define ATIFINDEX	0
#define ATPHYSADDRESS	1
#define ATNETADDRESS	2

#define IPMEDIAIFINDEX          0
#define IPMEDIAPHYSADDRESS      1
#define IPMEDIANETADDRESS       2
#define IPMEDIATYPE             3

/*
 * in case its missing: 
 */
#ifndef ATF_PERM
# define ATF_PERM	0x04
#endif                          /*  ATF_PERM */
#ifndef ATF_COM
# define ATF_COM	0x02
#endif                          /*  ATF_COM */

/* InfiniBand uses HW addr > 6 */
#define MAX_MAC_ADDR_LEN 32 

#if defined(linux) || defined(irix6)
/*
 * arp struct to pass flags, hw-addr and ip-addr in bsd manner:
 */
     struct arptab {
         int             at_flags;
         char            at_enaddr[MAX_MAC_ADDR_LEN];
         int             at_enaddr_len;
         struct in_addr  at_iaddr;
         int             if_index;
     };
//#endif
//#endif                          /* _MIBGROUP_AT_H */

#ifdef USING_MIBII_AT_MODULE
//#include "at.h"                 /* for var_atEntry() */

#endif


#define IPFORWARDING	  1
#define IPDEFAULTTTL	  2
#define IPINRECEIVES	  3
#define IPINHDRERRORS	  4
#define IPINADDRERRORS	  5
#define IPFORWDATAGRAMS   6
#define IPINUNKNOWNPROTOS 7
#define IPINDISCARDS	  8
#define IPINDELIVERS	  9
#define IPOUTREQUESTS	 10
#define IPOUTDISCARDS	 11
#define IPOUTNOROUTES	 12
#define IPREASMTIMEOUT	 13
#define IPREASMREQDS	 14
#define IPREASMOKS	 15
#define IPREASMFAILS	 16
#define IPFRAGOKS	 17
#define IPFRAGFAILS	 18
#define IPFRAGCREATES	 19
#define IPADDRTABLE	 20	/* Placeholder */
#define IPROUTETABLE	 21	/* Placeholder */
#define IPMEDIATABLE	 22	/* Placeholder */
#define IPROUTEDISCARDS	 23

#define IPADADDR	  1
#define IPADIFINDEX	  2
#define IPADNETMASK	  3
#define IPADBCASTADDR	  4
#define IPADREASMMAX	  5

#define IPROUTEDEST	  1
#define IPROUTEIFINDEX	  2
#define IPROUTEMETRIC1	  3
#define IPROUTEMETRIC2	  4
#define IPROUTEMETRIC3	  5
#define IPROUTEMETRIC4	  6
#define IPROUTENEXTHOP	  7
#define IPROUTETYPE	  8
#define IPROUTEPROTO	  9
#define IPROUTEAGE	 10
#define IPROUTEMASK	 11
#define IPROUTEMETRIC5	 12
#define IPROUTEINFO	 13

/* #define IPMEDIAIFINDEX		1 */
/* #define IPMEDIAPHYSADDRESS	2 */
/* #define IPMEDIANETADDRESS	3 */
/* #define IPMEDIATYPE		4 */

#endif                          /* _MIBGROUP_IP_H */

//#endif

#ifndef _MIBGROUP_INTERFACES_H
#define _MIBGROUP_INTERFACES_H

/***********************************************************************
 * configure macros
 */
config_require(util_funcs/header_generic)

/*
 * conflicts with the new MFD rewrite
 */
config_exclude(if-mib/ifTable/ifTable)

#if !defined(WIN32) && !defined(cygwin)
config_require(if-mib/data_access/interface)
#endif

config_arch_require(solaris2, kernel_sunos5)
/*
 * need get_address in var_route for some platforms (USE_SYSCTL_IFLIST).
 * Not sure if that can be translated into a config_arch_require, so be
 * indiscriminate for now.
 */
config_require(mibII/var_route)

/***********************************************************************
 */
#ifndef USING_IF_MIB_IFTABLE_MODULE
#ifdef hpux11
#include <sys/mib.h>
#else
     struct in_ifaddr;
     struct ifnet;
#endif

     int             Interface_Scan_Get_Count(void);
     int             Interface_Index_By_Name(char *, int);
     void            Interface_Scan_Init(void);
#if defined(linux) || defined(sunV3)
     struct in_ifaddr {
         int             dummy;
     };
#endif
#if defined(hpux11)
     int             Interface_Scan_Next(short *, char *, nmapi_phystat *);
     int             Interface_Scan_NextInt(int *, char *, nmapi_phystat *);
#else
     int             Interface_Scan_Next(short *, char *, struct ifnet *,
                                         struct in_ifaddr *);
     int             Interface_Scan_NextInt(int *, char *, struct ifnet *,
                                         struct in_ifaddr *);
#endif

     void            init_interfaces(void);
     extern snmp_find_var_callback var_interfaces;
     extern snmp_find_var_callback var_ifEntry;

#endif /* USING_IF_MIB_IFTABLE_MODULE */

#define NETSNMP_IFNUMBER        0
#define NETSNMP_IFINDEX         1
#define NETSNMP_IFDESCR         2
#define NETSNMP_IFTYPE          3
#define NETSNMP_IFMTU           4
#define NETSNMP_IFSPEED         5
#define NETSNMP_IFPHYSADDRESS   6
#define NETSNMP_IFADMINSTATUS   7
#define NETSNMP_IFOPERSTATUS    8
#define NETSNMP_IFLASTCHANGE    9
#define NETSNMP_IFINOCTETS      10
#define NETSNMP_IFINUCASTPKTS   11
#define NETSNMP_IFINNUCASTPKTS  12
#define NETSNMP_IFINDISCARDS    13
#define NETSNMP_IFINERRORS      14
#define NETSNMP_IFINUNKNOWNPROTOS 15
#define NETSNMP_IFOUTOCTETS     16
#define NETSNMP_IFOUTUCASTPKTS  17
#define NETSNMP_IFOUTNUCASTPKTS 18
#define NETSNMP_IFOUTDISCARDS   19
#define NETSNMP_IFOUTERRORS     20
#define NETSNMP_IFOUTQLEN       21
#define NETSNMP_IFSPECIFIC      22

#ifdef linux
/*
 * this struct ifnet is cloned from the generic type and somewhat modified.
 * it will not work for other un*x'es...
 */

     struct ifnet {
         char           *if_name;       /* name, e.g. ``en'' or ``lo'' */
         char           *if_unit;       /* sub-unit for lower level driver */
         short           if_mtu;        /* maximum transmission unit */
         short           if_flags;      /* up/down, broadcast, etc. */
         int             if_metric;     /* routing metric (external only) */
         char            if_hwaddr[6];  /* ethernet address */
         int             if_type;       /* interface type: 1=generic,
                                         * 28=slip, ether=6, loopback=24 */
         u_long          if_speed;      /* interface speed: in bits/sec */

         struct sockaddr if_addr;       /* interface's address */
         struct sockaddr ifu_broadaddr; /* broadcast address */
         struct sockaddr ia_subnetmask; /* interface's mask */

         struct ifqueue {
             int             ifq_len;
             int             ifq_drops;
         } if_snd;              /* output queue */
         u_long          if_ibytes;     /* octets received on interface */
         u_long          if_ipackets;   /* packets received on interface */
         u_long          if_ierrors;    /* input errors on interface */
         u_long          if_iqdrops;    /* input queue overruns */
         u_long          if_obytes;     /* octets sent on interface */
         u_long          if_opackets;   /* packets sent on interface */
         u_long          if_oerrors;    /* output errors on interface */
         u_long          if_collisions; /* collisions on csma interfaces */
         /*
          * end statistics 
          */
         struct ifnet   *if_next;
     };
#endif	/* linux */
#endif	/* _MIBGROUP_INTERFACES_H */


#endif	/*_MIBGROUP_IP_H*/

#endif	/*#ifndef RFC_1213_MIB*/

#endif 	/*__SNMP_MIB2_IPADDRTABLE_H__*/
