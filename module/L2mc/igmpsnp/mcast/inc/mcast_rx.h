/*******************************************************************************
  [File name]	: mcast_rx.h
  [Author]     	: bain.wang@outlook.com
  [Version]    	: 1.0
  [Date]       	: 2017-06-15
  [Description]	:
	Multicast module receive protocol packet
  [Others]     	:
	NULL
  [Function List]:  
    1. ....
    2. ....
  [History]:
	 D a t e      	Modification 							 Initials
	---------- 	--------------                                        ----------
	2017-06-15  	Created								 bain.wang@outlook.com
*******************************************************************************/

#ifndef __mcast_rx_h__
#define __mcast_rx_h__

#include "mcast_def.h"
#include "mcast_utl.h"

#if BC_MULTICAST_INCLUDE

typedef struct {
	bc_port_index_t rx_port;
	bc_uint8		llid;		/* dynamic control multicast will use it */
	bc_uint16		vid;
	
	bc_uint16      	buf_len;    /* Indicate the whole packet length ( without FCS) */
	bc_uint8		*buf;
	
	void (*free)(void*);
} mcast_rx_node_t;

void mcast_rx_receive_pkt(mcast_rx_node_t *pkt);

#endif
#endif

