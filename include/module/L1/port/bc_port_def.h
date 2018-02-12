/************************************************************
  -------------------------------------------------------------------------
  FileName:
  Author:  bain.wang@outlook.com      Version :  1.0        Date:2016-6-10
  Description:                   
  Version:                        
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/
#ifndef __BC_PORT_DEF_H__
#define __BC_PORT_DEF_H__

#include "bc_modules_com_para.h"
#include "bc_common_defs.h"
#include "bc_ipc_def.h"
#include "bc_ipc_package.h"


#include "bc_err.h"
#include "bc_proj_defs.h"
#include "bc_proj_port_defs.h"


#define	BC_PORT_NAME_LENGTH             32



/*   SNI端口介质类型
*    get不能返回auto
*/
typedef enum
{
	BC_PORT_VALID_TYPE_UNEXIT = 0,
	BC_PORT_VALID_TYPE_CFGE = 1,    /*通过命令行添加板卡，端口可配、实际不存在，*/
	BC_PORT_VALID_TYPE_VALID =2,
	BC_PORT_VALID_TYPE_UNMANAGEABLE =3
} bc_port_valid_type_e;

/*   SNI端口介质类型
*    get不能返回auto
*/
typedef enum
{
	SNI_MEDIA_TYPE_COPPER = 0,
	SNI_MEDIA_TYPE_FIBER = 1,
	SNI_MEDIA_TYPE_MAX
} bc_sni_media_type_e;
/*   SNI端口介质类型
*    get不能返回auto
*/
typedef enum
{
	SNI_COMBO_MODE_COPPER = 0,
	SNI_COMBO_MODE_FIBER,
	SNI_COMBO_MODE_AUTO,
	SNI_COMBO_MODE_MAX
} bc_sni_combo_mode_e;


/*端口类型*/
typedef enum
{
    PORT_TYPE_OLT_GESNI = 0,
    PORT_TYPE_OLT_XGSNI ,
	PORT_TYPE_OLT_GEEPON ,
	PORT_TYPE_OLT_XGEPON ,
	PORT_TYPE_OLT_TRUNK,
	PORT_TYPE_OLT_CPU,
	PORT_TYPE_OLT_MANAGE,
	PORT_TYPE_OLT_8022MII,      /*for 8022 */
	PORT_TYPE_ONU_UNI,
    PORT_TYPE_ONU_PON,
    PORT_TYPE_ONU_LLID,
	PORT_TYPE_MAX,
	PORT_TYPE_UNKNOW = PORT_TYPE_MAX,
}bc_pt_type_e;

typedef unsigned char bc_port_type_e;
/*
*       这里为了节省空间bc_port_type_e 修改为unsigned char 类型，
*       实际使用的时候还是使用上面的bc_pt_type_e 枚举
*/

typedef struct
{
    bc_port_type_e         port_type;
    bc_uint8               slot_id;
	bc_uint8               port_id;
}bc_port_index_t;

typedef struct
{
    bc_uint8               slot_id;
	bc_uint8               port_id;
}bc_port_lpid_t;


//自协商状态
typedef enum
{
	AUTO_NEGO_STATUS_HALF10 = 1,
	AUTO_NEGO_STATUS_FULL10 = 2,
	AUTO_NEGO_STATUS_HALF100 = 3,
	AUTO_NEGO_STATUS_FULL100 = 4,
	AUTO_NEGO_STATUS_FULL1000 = 5,
	AUTO_NEGO_STATUS_FULL10000 = 6,
	AUTO_NEGO_STATUS_UNKNOW = 7	
} bc_auto_nego_status_e;

//自协商mode
typedef enum
{
	AUTO_NEGO_MODE_AUTO = 1,
	AUTO_NEGO_MODE_HALF10 = 2,
	AUTO_NEGO_MODE_FULL10 = 3,
	AUTO_NEGO_MODE_HALF100 = 4,
	AUTO_NEGO_MODE_FULL100 = 5,
	AUTO_NEGO_MODE_FULL1000 = 6,
	AUTO_NEGO_MODE_FULL10000 = 7,
	AUTO_NEGO_MODE_MAX
} bc_auto_nego_mode_e;

/* 自适应状态 */
typedef enum enum_auto_negotiation_sta
{
	E_NEGO_F10 = 0,
	E_NEGO_H10,
	E_NEGO_F100,
	E_NEGO_H100,
	E_NEGO_F1000,
	E_NEGO_F10000,
	E_NEGO_AUTO,
	E_NEGO_INVALID
} auto_nego_sta_t;

/* 自适应能力 */
typedef enum enum_auto_negotiation_ability_bit
{
	BIT_NEGO_F10 = 0,
	BIT_NEGO_H10,
	BIT_NEGO_F100,
	BIT_NEGO_H100,
	BIT_NEGO_F1000,
	BIT_NEGO_H1000,
	BIT_NEGO_F1000X,
	BIT_NEGO_H1000X,
	BIT_NEGO_FDX_PAUSE,
	BIT_NEGO_FDX_APAUSE,
	BIT_NEGO_FDX_SPAUSE,
	BIT_NEGO_FDX_BPAUSE,
	BIT_NEGO_INVALID
} auto_nego_abl_bit;

typedef union tag_int_auto_nego_ability 
{
	struct 
	{
		unsigned int reserved_3:8;		//高位
		unsigned int reserved_2:8;
		unsigned int reserved_1:3;
		unsigned int fdxbpause_bit:1;
		unsigned int fdxspause_bit:1;
		unsigned int fdxapause_bit:1;
		unsigned int fdxpause_bit:1;
		unsigned int h1000x_bit:1;
		unsigned int f1000x_bit:1;
		unsigned int h1000_bit:1;
		unsigned int f1000_bit:1;
		unsigned int h100_bit:1;
		unsigned int f100_bit:1;
		unsigned int h10_bit:1;
		unsigned int f10_bit:1;
    	unsigned int reserved_0:1;

	} bits;

	unsigned int val;
}auto_nego_abl;

/*端口LINK 状态*/
typedef enum
{
	PORT_LINK_DOWN = 0,
	PORT_LINK_UP,
	PORT_LINK_MAX
}bc_port_link_status_e;

//PON端口加密方式
typedef enum
{
    PON_ENCRYPT_MODE_NONE = 0, // 不加密
    PON_ENCRYPT_MODE_CTC = 1,
    PON_ENCRYPT_MODE_AES32 = 2, // not support
    PON_ENCRYPT_MODE_AES48 = 3, // not support
    PON_ENCRYPT_MODE_AES128 = 4,
    PON_ENCRYPT_MODE_OTHER = 5,
    PON_ENCRYPT_MODE_MAX 
} bc_pon_encrypt_mode_e;

/*ONU 最大最大距离*/
typedef enum
{
	ONU_MAX_DISTANCE_NORMAL = 0,  //20KM
	ONU_MAX_DISTANCE_30KM = 1,  //30KM
	ONU_MAX_DISTANCE_40KM = 2,  //40KM
	ONU_MAX_DISTANCE_50KM = 3   //50KM
}bc_onu_max_distance_e;

/*P2P模式*/
typedef enum
{
	ONU_P2P_MODE_DISABLE = 0,    /*不启动P2P*/
	ONU_P2P_MODE_FULL = 1,       /*启动P2P*/
	ONU_P2P_MODE_GROUP = 2,      /*启动组P2P模式*/
	ONU_P2P_MODE_MAX             /*未知*/   
}bc_onu_p2p_mode_e;



//SNI端口基本信息
typedef struct
{
	bc_int32 					sni_index;                      // xx: 设备中SNI的索引号 
	bc_uint8 				   	slot_id;
	bc_uint8				   	port_id;
	bc_port_type_e				port_type;

	bc_mac 						port_mac;					   /*端口MAC*/	

	bc_char				        port_name[BC_PORT_NAME_LENGTH];
	
	bc_sni_media_type_e			media_type;
	bc_sni_combo_mode_e			combo_mode;
	
	bc_auto_nego_status_e 		auto_nego_status;
   	bc_auto_nego_mode_e 		auto_nego_mode;
	bc_uint32				   	lst_status_chng_tm;
	
	bc_boolean					pause_enable;
	bc_boolean                 	enable;                         /*端口使能*/
	
	bc_port_link_status_e       link_status;                    /*端口Link status */
	bc_port_valid_type_e        valid;    				         /* 是否存在 */
} bc_sni_base_info_t;

#define BC_PORT_SNI_SET_BIT_NAME 					0x1
#define BC_PORT_SNI_SET_BIT_MEDIA 				0x2
#define BC_PORT_SNI_SET_BIT_COMBO 				0x4
#define BC_PORT_SNI_SET_BIT_NEGO_STATUS 	0x8
#define BC_PORT_SNI_SET_BIT_NEGO_MODE 		0x10
#define BC_PORT_SNI_SET_BIT_CHG_TM 				0x20
#define BC_PORT_SNI_SET_BIT_PAUSE 				0x40
#define BC_PORT_SNI_SET_BIT_ENABLE 				0x80
#define BC_PORT_SNI_SET_BIT_LINK 					0x100
#define BC_PORT_SNI_SET_BIT_VALID 					0x200
#define BC_PORT_SNI_SET_BIT_DEFVALUE			0x80000000

//PON端口基本信息
typedef struct
{
   	bc_int32      				pon_index;
	bc_uint8 					slot_id;
	bc_uint8					port_id;
	bc_uint8        			chip_id;       /* 硬件 chip id */
	bc_port_type_e				port_type;

	bc_mac                  	port_mac;					   /*端口MAC*/	
	
	bc_char				 		port_name[BC_PORT_NAME_LENGTH];
	
	bc_boolean                  enable;   						 /*端口使能*/
	
	bc_boolean                  is_online;    					 /* 是否在线    0: 不在线    1:在线 */
	bc_port_link_status_e  		link_status;                    /*端口Link status */
	bc_port_valid_type_e   		valid;    				         /* 是否存在 */

	bc_uint32					max_onu_num;
	bc_uint32					up_onu_num;
	
	bc_pon_encrypt_mode_e		encrypt_mode;
	bc_uint32					encrypt_key_exchng_tm;  /*774~786426 ms*/
    bc_boolean                  encrypt_enable;
	
	bc_onu_max_distance_e  		onu_max_distince;               /*最大ONU距离*/
	bc_onu_p2p_mode_e      		onu_p2p_mode;                   /*ONU P2P模式*/
}bc_pon_base_info_t;

typedef struct {
	bc_port_index_t port;

	bc_int32 bias_current;
	bc_int32 working_voltage;
	bc_int32 working_temperature;

	bc_int32 received_optical_power;
	bc_int32 transmitted_optical_power;
} bc_port_pon_optical_info_t;

#define BC_PORT_PON_SET_BIT_NAME 					0x1
#define BC_PORT_PON_SET_BIT_ENABLE 				0x2
#define BC_PORT_PON_SET_BIT_ONLINE 				0x4
#define BC_PORT_PON_SET_BIT_LINK 					0x8
#define BC_PORT_PON_SET_BIT_VALID 				0x10
#define BC_PORT_PON_SET_BIT_ONU_NUM			0x20
#define BC_PORT_PON_SET_BIT_ENC_ENABLE		0x40
#define BC_PORT_PON_SET_BIT_ENC_MODE			0x80
#define BC_PORT_PON_SET_BIT_ENC_TM				0x100
#define BC_PORT_PON_SET_BIT_DIST					0x200
#define BC_PORT_PON_SET_BIT_P2P						0x400
#define BC_PORT_PON_SET_BIT_DEFVALUE			0x80000000

//PON端口基本信息
typedef struct
{
   bc_port_index_t     port_index;

	bc_uint8                valid;    				         /* 是否存在 */
	
	bc_char				   port_name[BC_PORT_NAME_LENGTH];

	bc_boolean                  enable;   						 /*端口使能*/
	bc_port_link_status_e   link_status;                    /*端口Link status */
}bc_manage_base_info_t;

#define BC_PORT_MGMT_SET_BIT_NAME			0x1
#define BC_PORT_MGMT_SET_BIT_ENABLE		0x2
#define BC_PORT_MGMT_SET_BIT_LINK				0x4
#define BC_PORT_MGMT_SET_BIT_VALUE			0x8

typedef struct
{
	bc_sni_base_info_t    sni_base_info[BC_PORT_SNI_MAX_COUNT];
} bc_sni_port_t;

typedef struct
{
    bc_pon_base_info_t    pon_base_info[BC_PORT_PON_MAX_COUNT];
} bc_pon_port_t;

typedef struct
{
    bc_manage_base_info_t    manage_base_info[BC_PORT_MANAGE_MAX_COUNT];
} bc_manage_port_t;


#endif

