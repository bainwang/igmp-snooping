/*******************************************************************************
  [Author]	   : bain.wang@outlook.com.uestc@gmail.com
  [Version]    : 
  [Date]       : 
  [Description]:

  [Others]     :

  [History]:
	 Date          Modification 							    Initials
	----------     ----------                                   -------
	2017-02-22      Created								   		bain.wang@outlook.com
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//																			  //
//								Õ∑   Œƒ   º˛								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
#ifndef __SNMP_GLOBAL_H__
#define __SNMP_GLOBAL_H__

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include <net-snmp/agent/snmp_vars.h>
#include <sys/time.h>

#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>   
#include <sys/ioctl.h>   
#include <netinet/in.h>   
#include <net/if.h>   
#include <net/if_arp.h>   
#include <arpa/inet.h>   
#include <errno.h>  
#include <pthread.h>
#include <semaphore.h>

#include "bc_common_defs.h"
#include "bc_modules.h"
#include "bc_print.h"
////////////////////////////////////////////////////////////////////////////////
//																			  //
//								ÂÆè   ÂÆö   ‰πâ								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#ifdef BC_PRJ_NAME_X86

#define SNMP_PRJ_NAME_610A	FALSE
#define SNMP_PRJ_NAME_X86		TRUE
#else
#define SNMP_PRJ_NAME_610A	TRUE
#define SNMP_PRJ_NAME_X86		FALSE
#endif



#define MAXINTERFACES 				16    /* ◊Ó¥ÛΩ”ø⁄ ˝ */
#define SNMP_IP_ADDR_COUNT		16
#define SNMP_IP_ADDR_LEN			32



#define SNMP_DEV_NAME_LEN			32


#define SNMP_UPDATE_INTERVAL			0	//debug

#define SNMP_CONFIG_FILE_DIR			"/usr/local/netsnmp/share/snmp/"
#define SNMP_CONFIG_FILE_NAME			"bc-snmp"
#define SNMP_ENTRY_COUNT				3

/*profile*/
#define SNMP_PROFILE_NAME_LEN		16
#define SNMP_PROFILE_COUNT_MAX	256


typedef pthread_mutex_t snmp_pthread_mutex_t;
typedef pthread_t snmp_thread_t;

/*create a pthread*/
#define SNMP_PTHREAD_CREATE(id, attr, func, arg)	\
	do{	\
		pthread_create(id ,attr, (void *)func, arg);	\
	}while(0)
	

#define SNMP_MEM_GET(_s_, _t_, _n_)	\
	do{	\
		_s_ = malloc(sizeof(_t_)*_n_);	\
		if(_s_) memset(_s_, 0, sizeof(_t_)*_n_);	\
	}while(0)

#define SNMP_MEM_FREE(_s_)	\
		do { if (_s_) { free((void *)_s_); _s_=NULL; } } while(0)

#define SNMP_MEM_ZERO(s,l)	\
		do { if (s) memset(s, 0, l); } while(0)

#define SNMP_MIB_FFLUSH_INIT()	\
	do{	\
		struct timeval tv;	\
		struct timezone tz;	\
		gettimeofday(&tv, &tz);	\
		update_time = tv.tv_sec - SNMP_UPDATE_INTERVAL;	\
	}while(0)

#define SNMP_P_FREE(s)    do { if (s) { free((void *)s); s=NULL; } } while(0)

bc_int32 snmp_get_addr_by_name(bc_char net_name[SNMP_DEV_NAME_LEN], bc_char ipstr[SNMP_IP_ADDR_LEN]);
bc_boolean snmp_save_config_file();

#if 1
void snmp_time_to_datatime(time_t time_tick, bc_uint8 date_and_time[8]);
#else
bc_boolean snmp_time_to_datatime(time_t timep, bc_char datetime[8]);
#endif



#if 1
#define SECOND_USEC            	(1000000)
void snmp_time_sleep(bc_uint32 sec);
void snmp_time_usleep(bc_uint32 usec);
#endif


#if SNMP_PRJ_NAME_610A
#include "mBase.h"
#include "event/event_eth_port.h"
#include "mpapi.h"
#include "comm/lr_errors.h"
#endif


#endif /*__SNMP_GLOBAL_H__*/

