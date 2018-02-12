/************************************************************
  FileName: bc_log.h
  Author:  bain.wang@outlook.com      Version :  1.0        Date:2017-04-04
  Description:                   
  Version:                        
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/
#ifndef __BC_LOG_H__
#define __BC_LOG_H__



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              ͷ   ��   ��                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "bc_err.h"
#include "bc_vfs.h"
#include "bc_print.h"
#include "bc_modules.h"

#include "bc_platform_time.h"
#include "bc_platform_mutex.h"
#include "bc_platform_procps.h"



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

#define BC_LOG_MAX_NOTE_NUM         	2000

#define BC_LOG_SYS_TIME_BUF_LEN			20
#define BC_LOG_ROW_POS_INFO_LEN			32
#define BC_LOG_TMP_DATA_INFO_LEN		64
#define BC_LOG_MAX_LINE_LEN				1024


/* user log */
#define BC_LOG_MAX_USER_NAME_LEN		32
#define BC_LOG_USR_BUF_LEN				384
#define BC_LOG_USER_CMD_LEN				200



/* system log */
#define BC_LOG_SYS_LEVEL_NAME_LEN		16
#define BC_LOG_SYS_BUF_LEN				384
#define BC_LOG_SYS_MAX_CONTENT_LEN		150

#define BC_LOG_SYS_FILE					"system.log"
#define BC_LOG_SYS_FILE_BACKUP			"backup_syslog"
#define BC_LOG_SYS_RUNNING_FILE 		"sys_running.log"
#define BC_LOG_SYS_TMP_FILE 			"tmp_sys.log"

#define	BC_LOG_SYS_WRT_THREAD			"sys_log_wrt_thread"	




////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                  �� �� �� ���� �� �塢ö �� �� ��                          //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
typedef enum bc_log_etag_level_bit
{
	BC_LOG_LVL_INIT,
	BC_LOG_LVL_EVT,
	BC_LOG_LVL_WARN,
	BC_LOG_LVL_ERR,
	BC_LOG_LVL_COMMAND,
	BC_LOG_LVL_MAX
} bc_log_lvl_e;

/* ��־����λ */
#define BC_LOG_BIT_ALL					0xFFFFFFFF
#define BC_LOG_BIT_NONE					0x00000000

#define BC_LOG_BIT_INIT					(BC_LOG_BIT_ALL & (0x01 << BC_LOG_LVL_INIT))
#define BC_LOG_BIT_EVENT				(BC_LOG_BIT_ALL & (0x01 << BC_LOG_LVL_EVT))
#define BC_LOG_BIT_WARNING				(BC_LOG_BIT_ALL & (0x01 << BC_LOG_LVL_WARN))
#define BC_LOG_BIT_ERROR				(BC_LOG_BIT_ALL & (0x01 << BC_LOG_LVL_ERR))
#define BC_LOG_BIT_COMMAND				(BC_LOG_BIT_ALL & (0x01 << BC_LOG_LVL_COMMAND))

typedef struct bc_log_sys_note_flag
{
	bc_int16			item_no;
	bc_log_lvl_e  		log_lvl;
	bc_char				sys_level[BC_LOG_SYS_LEVEL_NAME_LEN];
	bc_char				sys_time[BC_LOG_SYS_TIME_BUF_LEN];
	bc_char				log_content[BC_LOG_SYS_MAX_CONTENT_LEN];
} bc_log_sys_note_t;



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
#if 1
/*************************************************
  Function: bc_log_lvl_en
  Description: �Ƿ�д�ü������־
  Input: 
  		log_level		��־����λ��
  Output:
  		NULL
  Return:
  		0: FALSE(0)��ʾ��д��־���ļ�
  		~0: TRUE(1)��ʾд����־�ļ�
  Note: 
  History: 
*************************************************/
bc_boolean bc_log_lvl_en(bc_uint32 log_level);



/*************************************************
  Function: bc_log_lvl_open
  Description: ��д��־�ļ���
  Input: 
  		log_level		��־����λ��
  Output:
  		NULL
  Return:
  		0: 
  		~0: 
  Note: 
  History: 
*************************************************/
bc_boolean bc_log_lvl_open(bc_uint32 log_level);



/*************************************************
  Function: bc_log_lvl_close
  Description: �ر�д��־����(λ)
  Input: 
  		log_level		��־����λ��
  Output:
  		NULL
  Return:
  		0: 
  		~0: 
  Note: 
  History: 
*************************************************/
bc_boolean bc_log_lvl_close(bc_uint32 log_level);



/*************************************************
  Function: bc_log_lvl_get
  Description: ��ȡ��־����(λ)
  Input: 
  		log_level		��־����λ��
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_log_lvl_get(bc_uint32 *log_level);


#endif


#if 1
/*************************************************
  Function: bc_log_sys_init
  Description: ��ʼ��ϵͳ��־(��־����ϵͳ��־)
  Input: 
  		void
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: core process init
  History: 
*************************************************/
bc_err_e bc_log_sys_init(void);



/*************************************************
  Function: bc_log_wrt_sys_log
  Description: дϵͳ��־(һ��ϵͳ��־������:��¼�š�
  			ʱ�䡢����������־����)��ϵͳ��־�ļ���
  Input: 
  		log_level		��־�ļ���
	  	module _id		ģ��id
	  	filename		�ļ���
	  	fun_name		������
	  	line_no			�к�
	  	fmt				��ʽ����Ϣ
	  	��				�����б���Ϣ
  Output:
  		NULL
  Return:
  		0: 
  		~0: 
  Note: 
  History: 
*************************************************/
bc_err_e bc_log_wrt_sys_log
	(
		bc_int32 			log_level, 
		bc_int32 			module_id, 
		const bc_char 		*filename, 
		const bc_char 		*fun_name, 
		bc_int32 			line_no, 
		const char 			*fmt, 
		...
	);



/*************************************************
  Function: bc_log_sys_buffer_clear
  Description: ����ڴ��е�ϵͳ��־������Ϣ��
  Input: 
  		void
  Output:
  		NULL
  Return:
  		0: 
  		~0: 
  Note:    ���Ľ�������ڴ�ӿ�
  History: 
*************************************************/
bc_err_e bc_log_sys_buffer_clear(void);


/*************************************************
  Function: bc_log_sys_flash_clear
  Description: �����ʱ��־�ļ���
  Input: 
  		void
  Output:
  		NULL
  Return:
  		0: 
  		~0: 
  Note:    ���Ľ�������ļ��ӿ�
  History: 
*************************************************/
bc_err_e bc_log_sys_tmp_flash_clear(void);


/*************************************************
  Function: bc_log_sys_flash_clear
  Description: ���ϵͳ��־�ļ���
  Input: 
  		void
  Output:
  		NULL
  Return:
  		0: 
  		~0: 
  Note:    ���Ľ�������ļ��ӿ�
  History: 
*************************************************/
bc_err_e bc_log_sys_flash_clear(void);



/*************************************************
  Function: bc_log_get_sys_log
  Description: ��ȡ����ϵͳ��־��������Ϣ��
  Input: 
 		void
  Output:
  		NULL
  Return:
  		0: 
  		~0: 
  Note: 
  History: 
*************************************************/
bc_err_e bc_log_get_sys_log(void);



/*************************************************
  Function: bc_log_sys_wrt_opper_layer
  Description: 
  Input: 
  		
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_log_sys_wrt_upper_layer(bc_log_sys_note_t *sys_note);



/*************************************************
  Function: bc_log_sys_dbg_dump
  Description: ��ӡϵͳ�����е�ϵͳ��־������Ϣ
  Input: 
  Output:
  		NULL
  Return:
  		0: BC_ERR_OK
  		~0: error id
  Note: 
  History: 
*************************************************/
bc_err_e bc_log_sys_dbg_dump(void);

#endif


#endif



