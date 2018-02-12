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
#ifndef	__BC_CM_H__
#define __BC_CM_H__



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              头   文   件                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
#include <time.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>

#include "bc_common_defs.h"
#include "bc_platform_mem.h"
#include "bc_platform_time.h"
#include "bc_platform_mutex.h"

#include "bc_err.h"
#include "bc_vfs.h"
#include "bc_print.h"
#include "bc_modules.h"
//#include "../../L3/intf/bc_intf_network.h"
#include "bc_port_def.h"
#include "bc_onu_type.h"
#include "bc_proj_onumgmt_defs.h"



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                      外 部 变 量、 函 数 引 用                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              宏   定   义                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
#define BC_CFG_VERSION_INFO				"binchie cmd save. v1.0"
#define BC_CFG_SPACE					"!\r\n"

#define BC_CFG_LIST_MAX_NUM 			10
#define BC_CFG_USE_MAX_LEN				32
#define BC_CFG_BOOT_NAME_LEN			32
#define BC_CFG_MDL_NAME_SIZE			32
#define BC_CFG_USED_INDEX               (-1)

#define BC_CFG_MAXLINE					1024
#define BC_CFG_USR_CFG_SIZE				(5*1024*1024)

#define BC_CFG_BOOT_DEF_CFG				"bc_boot_def_cfg"		/* 出厂配置 			*/
#define BC_CFG_BOOT_USR_CFG				"bc_boot_usr_cfg"		/* 用户启机配置 		*/
#define BC_CFG_BOOT_USR_BAK_CFG			"bc_boot_usr_bak_cfg"	/* 用户启机配置备份 	*/
#define BC_CFG_BOOT_RD_CFG				"bc_boot_rd_cfg"		/* 开发者特定配置文件 */

#define BC_CFG_RUNNING_CFG				"bc_running_cfg"		/* 当前配置 			*/
#define BC_CFG_TMP_CFG					"bc_tmp_cfg"			/* 系统中的临时配置 	*/

#define BC_CFG_BOOT_FILE_NAME 			"bc_boot_file_name"		/* 配置管理启机文件的文件名 */



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                  结 构 体 、联 合 体、枚 举 定 义                          //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

typedef enum
{
	BC_CFG_TYPE_CONFIG_HIGH = 1,
	BC_CFG_TYPE_VLAN ,
	BC_CFG_TYPE_CONFIG,
	BC_CFG_TYPE_ACL,
	BC_CFG_TYPE_ONU_PROFILE,
	BC_CFG_TYPE_SNI,
	BC_CFG_TYPE_PON,
	BC_CFG_TYPE_VLAN_INTF,
	BC_CFG_TYPE_ONU,
	BC_CFG_TYPE_UNI,
	BC_CFG_TYPE_ONU_PROFILE_UNI,
	BC_CFG_TYPE_STP_REGION_CFG,
	BC_CFG_TYPE_CONFIG_LOW,
	BC_CFG_TYPE_MAX
} bc_cfg_type_e;

/* cfg mode parameter */
typedef struct 
{
	bc_port_type_e port_type;
	bc_uint8       slot_id;
	bc_uint8       port_id;
} bc_cfg_sni_t;

typedef struct
{
	bc_port_type_e port_type;
	bc_uint8       slot_id;
	bc_uint8       port_id;
} bc_cfg_pon_t;

typedef struct
{
	bc_uint32     slot_id;
	bc_uint32     port_id;
	bc_uint32     llid;
	bc_uint8      uni_port;
} bc_cfg_onu_t;

typedef struct 
{
	bc_int32      onu_num;    /* 该模板绑定的onu数量 */
	bc_uint32     profile_id;
	bc_uint8      uni_port;
} bc_cfg_onu_profile_t;

typedef struct
{
	bc_cfg_onu_t   onu_info;
} bc_cfg_uni_t;

typedef struct
{
	bc_uint16     inband_vlanid;
} bc_cfg_vlan_intf_t;

typedef struct
{
	bc_uint32     vlan_id;
} bc_cfg_vlan_t;

typedef struct
{
	bc_uint32    acl_id;
	bc_char      acl_name[BC_CFG_MDL_NAME_SIZE];
} bc_cfg_acl_t;


/* call back */
typedef bc_err_e (*bc_cfg_cback)(bc_char *, bc_uint32, bc_int32 *, void *);

typedef struct bc_cfg_mdl
{
	struct bc_cfg_mdl	*next; 
	bc_cfg_cback   	    fun;        
	bc_modules_e        id;
	bc_char             name[BC_CFG_MDL_NAME_SIZE];
	bc_boolean 			enable;
	bc_uint32           priority;
} bc_cfg_mdl_t;

typedef struct bc_cfg_mode
{
	bc_cfg_mdl_t        mdl;
	bc_cfg_type_e       type;
} bc_cfg_mode_t;

typedef struct bc_cfg_proj
{
	bc_cfg_mode_t      mode[BC_CFG_TYPE_MAX - 1];
	bc_uint32          num;
} bc_cfg_t;

typedef struct bc_cfg_file
{
	bc_char 		name[BC_CFG_BOOT_NAME_LEN];
	bc_char 		version[BC_CFG_USE_MAX_LEN];
	bc_char 		date[BC_CFG_USE_MAX_LEN];
	bc_uint32       size;
} bc_cfg_file_info_t;


typedef struct bc_cfg_run
{
	bc_boolean      para_enable;
	bc_boolean      all_port_enable;
	bc_port_index_t portlist[BC_PORT_MAX_COUNT];
	bc_int32        port_num;
	bc_onu_index_t  onulist[BC_ONU_MAX_ONU_COUNTS];
	bc_int32        onu_num;
} bc_cfg_run_t;


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                          全 局 变 量 定 义                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
/* 
 *  外部全局变量，提供整个工程调用，在头文件中提供调用接口(外部引用声明)。
 */

/* 
 *  内部全局变量，只提供给该文件内部函数调用，不在头文件中提供调用接口。
 */




////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              函  数  声  明                                //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
/*************************************************
  Function: bc_cfg_init
  Description: 初始化配置工程
  Input: 
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_cfg_init(void);



/*************************************************
  Function: bc_cfg_mdl_ins
  Description: 按照优先级插入模块，注册各个模块对应
  				 的回调函数
  Input: 
  cback_fun                         保存配置回调函数
  mdl_id							所注册功能模块ID
  mode                              注册回调所处的模式
  mdl_pri							模块注册优先级
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: mdl_pri表示模块注册的优先级别，范围从1到32，
  		优先级顺序从高到低为:1,2,3,4,5,6,...,32
  History: 
*************************************************/
bc_err_e bc_cfg_mdl_ins
	(
		bc_cfg_cback		cb_fun,
		bc_modules_e		mdl_id,
		bc_cfg_type_e       mode,
		bc_uint32           mdl_pri
	);



/*************************************************
  Function: bc_cfg_save
  Description: 保存配置文件(包括用户配置文件、开发者
  				 配置文件)
  Input: file_name		配置文件名
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_cfg_save(bc_char * file_name);



/*************************************************
  Function: bc_cfg_get_run
  Description: 获取系统运行中的配置命令
  Input: p_run_buf	指向运行配置buffer的指针
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_cfg_get_run(bc_cfg_run_t run_para);



/*************************************************
  Function: bc_cfg_clr
  Description: 清除配置文件
  Input: cfg_name		配置文件名
  Output: 
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_cfg_clr(bc_char *cfg_name);



/*************************************************
  Function: bc_cfg_get_cfglist
  Description: 获取设备以存储配置文件名的列表
  Input: 
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_cfg_get_cfglist(bc_cfg_file_info_t file_info[BC_CFG_LIST_MAX_NUM], bc_uint32 *actual_num);



/*************************************************
  Function: bc_cfg_set_boot_load_file
  Description: 设置系统开机加载配置文件
  Input: 
  		file_name		文件名
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_cfg_set_boot_load_file(bc_char *file_name);



/*************************************************
  Function: bc_cfg_no_boot_load_file
  Description: 设置系统开机加载配置文件
  Input: 
		void
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_cfg_no_boot_load_file(void);


/*************************************************
  Function: bc_cfg_file_copy_to_dev
  Description: configure file copy to device
  Input: 
		file_name:	configure file name
		file_path:	configure file path
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_cfg_file_copy_to_dev(bc_char *file_name, bc_char *file_path);



/*************************************************
  Function: bc_cfg_check_file_form_dev
  Description: check configure file for uploading
  			   form device
  Input: 
		file_name:	configure file name
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_cfg_check_file_form_dev(bc_char *file_name);



/*************************************************
  Function: bc_cfg_dbg_dump
  Description: configure debug dump info
  Input: 
		void
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_cfg_dbg_dump(void);


/*************************************************
  Function: bc_cfg_dbg_mdl_reg
  Description: module register function debug
  Input: 
		void
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_cfg_dbg_mdl_reg(bc_uint32 fun_id, bc_modules_e mdl_id, bc_cfg_type_e mode, bc_uint32 mdl_pri);

#endif



