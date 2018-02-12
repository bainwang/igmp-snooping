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
//                              ͷ   ��   ��                                  //
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
//                      �� �� �� ���� �� �� �� ��                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              ��   ��   ��                                  //
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

#define BC_CFG_BOOT_DEF_CFG				"bc_boot_def_cfg"		/* �������� 			*/
#define BC_CFG_BOOT_USR_CFG				"bc_boot_usr_cfg"		/* �û��������� 		*/
#define BC_CFG_BOOT_USR_BAK_CFG			"bc_boot_usr_bak_cfg"	/* �û��������ñ��� 	*/
#define BC_CFG_BOOT_RD_CFG				"bc_boot_rd_cfg"		/* �������ض������ļ� */

#define BC_CFG_RUNNING_CFG				"bc_running_cfg"		/* ��ǰ���� 			*/
#define BC_CFG_TMP_CFG					"bc_tmp_cfg"			/* ϵͳ�е���ʱ���� 	*/

#define BC_CFG_BOOT_FILE_NAME 			"bc_boot_file_name"		/* ���ù��������ļ����ļ��� */



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                  �� �� �� ���� �� �塢ö �� �� ��                          //
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
	bc_int32      onu_num;    /* ��ģ��󶨵�onu���� */
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
//                          ȫ �� �� �� �� ��                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
/* 
 *  �ⲿȫ�ֱ������ṩ�������̵��ã���ͷ�ļ����ṩ���ýӿ�(�ⲿ��������)��
 */

/* 
 *  �ڲ�ȫ�ֱ�����ֻ�ṩ�����ļ��ڲ��������ã�����ͷ�ļ����ṩ���ýӿڡ�
 */




////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              ��  ��  ��  ��                                //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
/*************************************************
  Function: bc_cfg_init
  Description: ��ʼ�����ù���
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
  Description: �������ȼ�����ģ�飬ע�����ģ���Ӧ
  				 �Ļص�����
  Input: 
  cback_fun                         �������ûص�����
  mdl_id							��ע�Ṧ��ģ��ID
  mode                              ע��ص�������ģʽ
  mdl_pri							ģ��ע�����ȼ�
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: mdl_pri��ʾģ��ע������ȼ��𣬷�Χ��1��32��
  		���ȼ�˳��Ӹߵ���Ϊ:1,2,3,4,5,6,...,32
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
  Description: ���������ļ�(�����û������ļ���������
  				 �����ļ�)
  Input: file_name		�����ļ���
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
  Description: ��ȡϵͳ�����е���������
  Input: p_run_buf	ָ����������buffer��ָ��
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
  Description: ��������ļ�
  Input: cfg_name		�����ļ���
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
  Description: ��ȡ�豸�Դ洢�����ļ������б�
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
  Description: ����ϵͳ�������������ļ�
  Input: 
  		file_name		�ļ���
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
  Description: ����ϵͳ�������������ļ�
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



