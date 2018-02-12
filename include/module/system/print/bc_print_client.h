/************************************************************
  -------------------------------------------------------------------------
  FileName: bc_print_client.h
  Author:  bain.wang@outlook.com      Version :  1.0        Date:2016-6-23
  Description: proj depend parameter define       
  Version:                        
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/
#ifndef __BC_PRINT_CLIENT_H__
#define __BC_PRINT_CLIENT_H__

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              ͷ   ��   ��                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
#include "bc_print.h"
#include "bc_err.h"
#include "bc_common_defs.h"
#include "bc_modules.h"

#include "bc_ipc_def.h"
#include "bc_ipc_client.h"
#include "bc_ipc_dev_client.h"




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



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                  �� �� �� ���� �� �塢ö �� �� ��                          //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////



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
  Function: bc_pt_prt_open_all_client
  Description: �����д�ӡ����(���������д�ӡ
  				 ����ʹ�����ģ��),�ͻ���
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
bc_err_e bc_pt_prt_open_all_client(void);



/*************************************************
  Function: bc_pt_prt_close_all_client
  Description: �����ӡ���ã�ȫ�ر�(�ر����еĴ�
  				 ӡ�����ģ��)
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
bc_err_e bc_pt_prt_close_all_client(void);



/*************************************************
  Function: bc_pt_prt_lvl_open_client
  Description: �򿪴�ӡ�ĸü���(λ)
  Input: 
  		prt_level		��ӡ����
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_pt_prt_lvl_open_client(bc_int32 prt_level);



/*************************************************
  Function: bc_pt_prt_lvl_close_client
  Description: �򿪴�ӡ�ĸü���(λ)
  Input: 
  		prt_level		��ӡ����
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_pt_prt_lvl_close_client(bc_int32 prt_level);



/*************************************************
  Function: bc_pt_open_prj_all_client
  Description: �򿪴�ӡ��������(������ӡ���е�ģ��)
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
bc_err_e bc_pt_open_prj_all_client(void);



/*************************************************
  Function: bc_pt_open_prj_mdl_client
  Description: ��ĳ��ģ�������ļ�
  Input: 
  		module_id		ģ��id
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_pt_open_prj_mdl_client(bc_uint32 module_id);



/*************************************************
  Function: bc_pt_open_prj_mdl_file_client
  Description: ��ĳ��ģ���ĳ���ļ�
  Input: 
  		module_id		ģ��id
  		file			ĳ���ļ����ļ��ṹָ��
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_pt_open_prj_mdl_file_client(bc_uint32 module_id, bc_pt_file_flg_t *file);



/*************************************************
  Function: bc_pt_close_prj_all_client
  Description: �ر���������(����ģ��������ļ�)��
  				 ��ӡ
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
bc_err_e bc_pt_close_prj_all_client(void);



/*************************************************
  Function: bc_pt_close_prj_mdl_client
  Description: �ر�ĳ��ģ��������ļ��Ĵ�ӡ
  Input: 
  		module_id		ģ��id
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_pt_close_prj_mdl_client(bc_uint32 module_id);




/*************************************************
  Function: bc_pt_close_prj_mdl_file_client
  Description: �ر�ĳ��ģ���ĳ���ļ��Ĵ�ӡ
  Input: 
  		module_id								ģ��id
  		file_name[BC_PT_FILE_NAME_LEN_MAX]	�ļ���
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_pt_close_prj_mdl_file_client(bc_uint32 module_id, bc_char file_name[BC_PT_FILE_NAME_LEN_MAX]);



/*************************************************
  Function: bc_pt_get_prt_lvl_client
  Description: ��ȡ��ӡ�Ĵ�ӡ����
  Input: 
  		prt_level		��ӡ����
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_pt_get_prt_lvl_client(bc_uint32 *prt_level);



/*************************************************
  Function: bc_pt_get_prj_all_client
  Description: ��ȡ��������(����ģ��)������Ϣ
  Input: 
  		all_prj			ָ���������̵�ָ��
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  History: 
*************************************************/
bc_err_e bc_pt_get_prj_all_client(bc_pt_prj_flg_t *all_prj);




/*************************************************
  Function: bc_pt_dbg_save_cfg_client
  Description: ��������������ݵ��ļ�
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
bc_err_e bc_pt_dbg_save_cfg_client(void);



/*************************************************
  Function: bc_pt_dbg_save_clear_client
  Description: ������������ļ����ڴ��������
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
bc_err_e bc_pt_dbg_save_clear_client(void);


/*************************************************
  Function: bc_pt_dump_client
  Description: dump�����ڴ�����
  Input: 
   		pt_lvl     ָ���ӡ�����ָ��
   		pt_prj     ָ��PTģ�鹤�̵�ָ��
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_pt_dump_client(bc_uint32 *pt_lvl, bc_pt_prj_flg_t *pt_prj);



#endif /* __BC_PRINT_CLIENT_H__ */


