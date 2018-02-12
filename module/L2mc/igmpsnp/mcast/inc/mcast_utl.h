/*******************************************************************************
  [File name]	: mcast_utl.h
  [Author]     	: bain.wang@outlook.com
  [Version]    	: 1.0
  [Date]       	: 2017-06-13
  [Description]	:
	Multicast module common operation
  [Others]     	:
	NULL
  [Function List]:  
    1. ....
    2. ....
  [History]:
	 D a t e      	Modification 							 Initials
	---------- 	--------------                                        ----------
	2017-06-13  	Created								 bain.wang@outlook.com
*******************************************************************************/

#ifndef __mcast_utl_h__
#define __mcast_utl_h__

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include "mcast_def.h"
#include "mcast_call.h"
#include "utili_ip_mac.h"

#include "bc_print.h"

#if BC_MULTICAST_INCLUDE
#if 1

/* -------------------- Common -------------------- */

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef INOUT
#define INOUT
#endif

#define MCAST_DBG_PRT_OPEN	1
#if MCAST_DBG_PRT_OPEN
//#define MCAST_DBG_PRT			printf

#define MCAST_DBG_PRT(fmt, args...)	BC_PT_DBG_SMP(BC_MODULE_IGMP, fmt, ##args)
#else
#define MCAST_DBG_PRT(fmt, args...)
#endif


#define MCAST_DBG_SPRT_IP(buf, len, ip) \
	do { \
		memset(buf, 0x00, len); \
		sprintf(buf, "%d.%d.%d.%d", (ip)[3], (ip)[2], (ip)[1], (ip)[0]); \
	} while(0)

#define MCAST_DBG_SPRT_MAC(buf, len, mac) \
	do { \
		memset(buf, 0x00, len); \
		sprintf(buf, "%02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]); \
	} while(0)

void mcast_dbg_prt_str(bc_uint8 *buf, bc_uint16 len, bc_uint16 width, bc_uint16 offset, bc_boolean newline);

#if 0

#define M_MCAST_ASSERT(p) \
	do \
	{ \
		if (!p) \
		{ \
			MCAST_DBG_PRT("%s,%d. Null Pointer Found.\n", __FILE__, __LINE__); \
		} \
	} while(0)
#else

#define M_MCAST_ASSERT(p) \
	do \
	{ \
		if (!p) \
		{ \
			printf("%s,%d. Null Pointer Found.\n", __FILE__, __LINE__); \
		} \
	} while(0)

#endif


#define M_MCAST_32_N2H(data)	\
	(((data)[0] << 24) & 0xFF000000) | \
	(((data)[1] << 16) & 0x00FF0000) | \
	(((data)[2] << 8) & 0x0000FF00) | \
	((data)[3] & 0x000000FF)

#define M_MCAST_16_N2H(data)	\
	(((data)[0] << 8) & 0xFF00) | \
	((data)[1] & 0x00FF)

#define M_MCAST_32_H2N(data, buf) \
	do \
	{ \
		(buf)[0] = ((data) & 0xFF000000) >> 24; \
		(buf)[1] = ((data) & 0x00FF0000) >> 16; \
		(buf)[2] = ((data) & 0x0000FF00) >> 8; \
		(buf)[3] = (data) & 0x000000FF; \
	} while(0)

#define M_MCAST_16_H2N(data, buf) \
	do \
	{ \
		(buf)[0] = ((data) & 0xFF00) >> 8; \
		(buf)[1] = (data) & 0x00FF; \
	} while(0)

#endif
#if 1

/* -------------------- Return & Debug -------------------- */

#define MCAST_MODULE_PBC	0x01
#define MCAST_MODULE_CORE	0x02
#define MCAST_MODULE_HOST	0x03
#define MCAST_MODULE_RT	0x04
#define MCAST_MODULE_TX	0x05
#define MCAST_MODULE_RX	0x06
#define MCAST_MODULE_MGT	0x07
#define MCAST_MODULE_CM	0x08
#define MCAST_MODULE_DRV	0x09
#define MCAST_MODEULE_CALL 0x0a

typedef bc_int32 	mcast_ret_code;

#define MCAST_RET_OK				0x00
#define MCAST_RET_ERR_PAR			0x01
#define MCAST_RET_ERR_NORES		0x02	/* not enough resource */
#define MCAST_RET_ERR_PBCINFO		0x04
#define MCAST_RET_ERR_UNTYPE		0x08
#define MCAST_RET_ERR_NOTFOUND	0x10
#define MCAST_RET_ERR_DRVERR		0x20
#define MCAST_RET_ERR_NOENABLE	0x40
#define MCAST_RET_ERR_UNSUPPORT	0x80
#define MCAST_RET_ERR_EXIST		0x100
#define MCAST_RET_ERR_EXISTRELATIONBIND 0x200
#define MCAST_RET_ERR_TXERRR		0x400
#define MCAST_RET_ERR_UNKNOW		0x80000000

#define MCAST_RET_ERR(module, err_num, logit) \
		{ \
			BC_PT_DBG_SMP(BC_MODULE_IGMP, "\n\t%s,%d. module:%d. err_num:%d.\n", __FILE__, __LINE__, module, err_num); \
			return err_num; \
		}


#define MCAST_LOG(module, err_num, logit) \
		{ \
			BC_PT_DBG_SMP(BC_MODULE_IGMP, "\n\t%s,%d. module:%d. err_num:%d.\n", __FILE__, __LINE__, module, err_num); \
			if (logit) {} \
		}


#define MCAST_PRT(str) printf str


#endif
#if 1

typedef enum {
	MCAST_MODE_CENTRALIZED 			= 1,
	MCAST_MODE_DISTRIBUTEDWITHCM 	= 2,		/* dynamic control multicast */
	MCAST_MODE_DISABLE 				= 3,
	MCAST_MODE_DISTRIBUTEDWOCM 	= 4		/* protocol multicast */
} mcast_mode_e;


typedef enum {
	MCAST_IGMP_V1 = 0x01,
	MCAST_IGMP_V2 = 0x02,
	MCAST_IGMP_V3 = 0x03
} mcast_igmp_version_e;


typedef enum {
	mcast_ctrlmc_authority_permit 	= 0x01,
	mcast_ctrlmc_authority_preview 	= 0x02,
	mcast_ctrlmc_authority_deny 	= 0x03
} mcast_cm_user_authority_e;

typedef bc_uint8 mcast_proxy_list[MCAST_CFG_GRP_MAX/8];
typedef bc_uint8 mcast_package_list[MCAST_CM_PACKAGE_MAX/8];

#endif
#if 1

typedef struct {
	mcast_list_node_t 	list_node;

	bc_ip src;
	bc_uint8 reserve[4];
} mcast_utl_src_node_t;

bc_int32 mcast_utl_src_cmp(IN void *node, IN bc_uint32 key);
bc_ip* mcast_src_list_2_block(IN mcast_list_t *src_list, OUT bc_uint16 *src_num);
bc_boolean mcast_src_list_alloc(IN bc_int32 src_num, IN bc_ip *src_list, OUT mcast_list_t *mcast_list);
void mcast_src_list_free(IN mcast_list_t *src_list);
bc_boolean mcast_src_list_copy(OUT mcast_list_t *dst, IN mcast_list_t *src);

void mcast_src_list_union(INOUT mcast_list_t *A, INOUT mcast_list_t *B, OUT mcast_list_t* reslt);
void mcast_src_list_intersection(INOUT mcast_list_t *A, IN mcast_list_t *B, OUT mcast_list_t* reslt);
void mcast_src_list_xor(INOUT mcast_list_t *A, INOUT mcast_list_t *B, OUT mcast_list_t* reslt);
void mcast_src_list_minus(INOUT mcast_list_t *A, IN mcast_list_t *B, OUT mcast_list_t* reslt);
void mcast_src_list_move(INOUT mcast_list_t *dst, INOUT mcast_list_t *src);

#endif
#if 1

void mcast_ip_cvrt_mac(IN bc_ip grp, OUT bc_mac mac);

bc_boolean mcast_utl_is_mc_mac(bc_mac mac);

bc_boolean mcast_utl_valid_mc_ip(IN bc_ip grp);
bc_boolean mcast_utl_valid_uc_ip(IN bc_ip ip);
bc_boolean mcast_utl_valid_src_ip(IN bc_ip ip);

#define mcast_utl_valid_vlan_id(vid)	(((1 <= (vid)) && ((vid) <= 4095)) ? TRUE : FALSE)

#endif
#if 1

bc_boolean mcast_utl_bitlist_and(IN bc_uint8 *f_list, IN bc_uint8 *s_list, OUT bc_uint8 *r_list, IN bc_uint16 size);
bc_boolean mcast_utl_bitlist_xor(IN bc_uint8 *f_list, IN bc_uint8 *s_list, OUT bc_uint8 *r_list, IN bc_uint16 size);
bc_boolean mcast_utl_bitlist_or(IN bc_uint8 *f_list, IN bc_uint8 *s_list, OUT bc_uint8 *r_list, IN bc_uint16 size);
bc_boolean mcast_utl_bitlist_is_empty(IN bc_uint8 *list, IN bc_uint16 size);

bc_boolean mcast_utl_bit_is_set(IN bc_uint8 *list, IN bc_uint16 size, IN bc_uint32 offset);
bc_boolean mcast_utl_bit_set(IN bc_uint8 *list, IN bc_uint16 size, IN bc_uint32 offset);
bc_boolean mcast_utl_bit_clr(IN bc_uint8 *list, IN bc_uint16 size, IN bc_uint32 offset);
bc_boolean mcast_utl_bit_get_next(IN bc_uint8 *list, IN bc_uint16 size, INOUT bc_uint32 *offset);

#endif
#endif
#endif

