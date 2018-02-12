/************************************************************
  Copyright (C), 1988-2014, xxxxx Tech. Co., Ltd.
  FileName:
  Author:  zhanglei      Version :  1.0        Date:2014-5-26
  Description:                   
  Version:                        
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/

#ifndef _BC_VFS_H_
#define _BC_VFS_H_

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								ͷ   ��   ��								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "bc_common_defs.h"
#include "bc_modules.h"
#include "bc_err.h"



////////////////////////////////////////////////////////////////////////////////
//																			  //
//								��   ��   ��								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

/*�ļ��򿪷�ʽ����*/
#define	BC_VFS_READ			"r"		/*��ֻ���ļ������ļ��������*/
#define	BC_VFS_READ_RW		"r+"		/*�򿪿ɶ�д���ļ������ļ��������*/
#define	BC_VFS_WRITE			"w"		/*��ֻд�ļ������ļ��������ļ�������Ϊ�㣬�����ļ����ݻ���ʧ�����ļ��������������ļ�*/
#define	BC_VFS_WRITE_RW		"w+"	/*�򿪿ɶ�д���ļ������ļ��������ļ�������Ϊ�㣬�����ļ����ݻ���ʧ�����ļ��������������ļ�*/
#define 	BC_VFS_ADD				"a"		/*�Ը��ӵķ�ʽ��ֻд�ļ������ļ������ڣ���Ὠ�����ļ�������ļ����ڣ�д������ݻᱻ�ӵ��ļ�β�����ļ�ԭ�ȵ����ݻᱻ����*/
#define	BC_VFS_ADD_RW			"a+"		/*�Ը��ӵķ�ʽ�򿪿ɶ�д���ļ������ļ������ڣ���Ὠ�����ļ�������ļ����ڣ�д������ݻᱻ�ӵ��ļ�β�󣬼��ļ�ԭ�ȵ����ݻᱻ����*/
#define	BC_VFS_READ_B			"rb"		/*�����ַ�b����ʾ���ļ�Ϊ�������ļ�*/
#define	BC_VFS_READ_BRW		"rb+"
#define	BC_VFS_WRITE_B		"wb"
#define	BC_VFS_WRITE_BRW		"wb+"
#define	BC_VFS_ADD_B			"ab"
#define	BC_VFS_ADD_BRW		"ab+"

/*�ļ����·��*/
#define	BC_VFS_ROOT				"/usr/"
#define	BC_VFS_ROOT_C				BC_VFS_ROOT"cfg/"
#define	BC_VFS_ROOT_D				BC_VFS_ROOT"fw/"
#define	BC_VFS_ROOT_E				BC_VFS_ROOT"fwbak/"
#define	BC_VFS_ROOT_F				"/tmp/"
#define	BC_VFS_CFG_FILE_PATH		BC_VFS_ROOT_C"cfg/"
#define	BC_VFS_LOG_FILE_PATH		BC_VFS_ROOT_C"log/"
#define	BC_VFS_DATA_FILE_PATH		BC_VFS_ROOT_C"data/"



/*�ļ���дλ��*/
#define	BC_VFS_SEEK_SET		0	/* Seek from beginning of file.  */
#define	BC_VFS_SEEK_CUR		1	/* Seek from current position.  */
#define	BC_VFS_SEEK_END		2	/* Seek from end of file.  */
/*�ļ����ʷ�ʽ*/
#define	BC_VFS_R_OK	4		/* Test for read permission.  */
#define	BC_VFS_W_OK	2		/* Test for write permission.  */
#define	BC_VFS_X_OK	1		/* Test for execute permission.  */
#define	BC_VFS_F_OK	0		/* Test for existence.  */
/*�ļ�������*/
#define	BC_VFS_MAX_FILE_NAME_LEN		32
/*�ļ�·������*/
#define	BC_VFS_MAX_FILE_PATH_LEN		64
/*�ļ�����*/
#define	BC_VFS_MAX_FILE_TYPE_NUM		64
/**/
#define	BC_VFS_MAX_FILE_ATTRIBUTE_SIZE		12
/**/
#define	BC_VFS_MAX_FILE_ATTRIBUTE_NUM		128
////////////////////////////////////////////////////////////////////////////////
//																			  //
//					�� �� �� ���� �� �塢ö �� �� ��				          //
//																			  //
////////////////////////////////////////////////////////////////////////////////

typedef FILE			bc_file;
typedef size_t		bc_size_t;

typedef struct{
	bc_char		filename[BC_VFS_MAX_FILE_NAME_LEN];
	bc_uint32		size;
	bc_uint32		f_year;
	bc_uint32		f_mon;
	bc_uint32		f_mday;
	bc_uint32		f_hour;
	bc_uint32		f_min;
	bc_uint32		f_sec;
	bc_char		file_type[BC_VFS_MAX_FILE_ATTRIBUTE_SIZE];
}bc_file_attribute_t;

typedef struct{
	bc_int32			num;
	bc_file_attribute_t	file_attribute[BC_VFS_MAX_FILE_ATTRIBUTE_NUM];	

}bc_file_attribute;

////////////////////////////////////////////////////////////////////////////////
//																			  //
//						�� �� �� ���� �� �� �� ��					          //
//																			  //
////////////////////////////////////////////////////////////////////////////////

/*************************************************
  Function: bc_file_init
  Description: �����ļ�ģ���ʼ��
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
bc_err_e bc_file_init(void);

/*************************************************
  Function: bc_file_delete
  Description: �鿴�ļ��Ƿ�ر�
  Input: 
  		file_name		�ļ���
  		file_path			�ļ�·��
  Output:
  		NULL
  Return:
  		0: �ɹ�
  		
  		~0:ʧ��
  Note: 
  History: 
*************************************************/
bc_err_e bc_file_delete(bc_char *filename, bc_char *file_path);

#if 0
/*************************************************
  Function: bc_file_create
  Description: �����ļ�
  Input: 
  		module_id		ģ��id
  		file_name		�ļ���
  		file_path			�ļ�·��
  Output:
  		NULL
  Return:
  		����ָ�򴴽��õ��ļ�ָ����
  Note: 
  History: 
*************************************************/
bc_file *bc_file_create(bc_modules_e module_id, bc_char *filename, bc_char *file_path);

/*************************************************
  Function: bc_file_close
  Description: �ر��ļ�
  Input: 
  		module_id		ģ��id
  		file_name		�ļ���
  		file				�ļ�ָ��
  Output:
  		NULL
  Return:
  		0: �ɹ�
  		~0: ʧ��
  Note: 
  History: 
*************************************************/
bc_err_e bc_file_close(bc_file *file, bc_modules_e module_id, bc_char *filename);

/*************************************************
  Function: bc_file_open
  Description:���ļ�
  Input: 
  		module_id		ģ��id
  		file_name		�ļ���
  		file_path			�ļ�·��
  		mode			�򿪷�ʽ
  Output:
  		NULL
  Return:
  		�����Դ򿪺õ��ļ�ָ����  
  Note: 
  History: 
*************************************************/
bc_file *bc_file_open(bc_char *filename, bc_char *mode, bc_char *file_path, bc_modules_e module_id);


/*************************************************
  Function: bc_file_write
  Description:д�ļ�
  Input: 
  		buff				��д������ݵ�ַ
  		nmemb			��д������ַ���
  		size      			Ҫд�����ݵĵ��ֽ���
  		filename   		Ҫд����ļ�
  Output:
  		NULL
  Return:
  		����ʵ��д�����Ŀ
  Note: 
  History: 
*************************************************/
bc_size_t	bc_file_write(void *buff, bc_size_t size, bc_size_t nmemb, bc_file *stream);

/*************************************************
  Function: bc_file_read
  Description: ���ļ�
  Input: 
  		buff				ָ������Ŷ�ȡ���������ݿռ�
  		nmemb			ʵ�ʶ�ȡ������Ŀ
  		size      			Ҫ��ȡ���ݵĵ��ֽ���
  		filename    		�Ѵ򿪵��ļ�ָ��
  Output:
  		NULL
  Return:
  		����ʵ�ʶ�ȡ����nmemb��Ŀ
  Note: 
  History: 
*************************************************/
bc_size_t bc_file_read(void *buff, bc_size_t size, bc_size_t nmemb, bc_file *stream);

/*************************************************
  Function: bc_file_is_closed
  Description: �鿴�ļ��Ƿ�ر�
  Input: 
  		module_id		ģ��id
  		file_name		�ļ���
  		file				�ļ�ָ��
  Output:
  		NULL
  Return:
  		0: �ر�
  		~0: δ�ر�
  Note: 
  History: 
*************************************************/
//bc_err_e bc_file_is_closed(bc_modules_e module_id, bc_char *file_path, bc_char *filename);

/*************************************************
  Function: bc_file_copy
  Description: �鿴�ļ��Ƿ�ر�
  Input: 
  		src_filename		Դ�ļ���
  		des_filename		Ŀ���ļ���
  		srcpath			Դ·��
  		despath			Ŀ��·��
  Output:
  		NULL
  Return:
  		0: �ɹ�
  		
  		~0:ʧ��
  Note: 
  History: 
*************************************************/
bc_err_e bc_file_copy(bc_char *src_filename, bc_char *des_filename, bc_char *srcpath, bc_char *despath);

/*************************************************
  Function: bc_file_seek
  Description: �ƶ��ļ��� �Ķ�дλ��
  Input: 
  		fp				�ļ�ָ��
  		offset			λ����
  		whence			�ƶ���ʽ
  Output:
  		NULL
  Return:
  		0: �ɹ�
  		~0: ʧ��
  Note: 
  History: 
*************************************************/
bc_int32 bc_file_seek(bc_file *fp, bc_long offset, bc_int32 whence);

/*************************************************
  Function: bc_file_access
  Description: ����Ƿ���Զ�дĳһ�Ѵ��ڵ��ļ�
  Input: 
  		file_name		�ļ���
  		file				�ļ�ָ��
  		mode			��鷽ʽ
  Output:
  		NULL
  Return:
  		0: �ɹ�
  		~0: ʧ��
  Note: 
  History: 
*************************************************/
bc_err_e bc_file_access(bc_char *filename, bc_char *filepath, bc_int32 mode);

/*************************************************
  Function: bc_file_get_file_directory
  Description: ��ȡ�ļ�����
  Input: 
  		path				�ļ�·��
  		file_attribute		�ļ�����
  Output:
  		NULL
  Return:
  		0: �ɹ�
  		~0: ʧ��
  Note: 
  History: 
*************************************************/
bc_err_e bc_file_get_file_directory(bc_char *path, bc_file_attribute *file_attribute);

/*************************************************
  Function: bc_vfs_is_dir
  Description:  �ж��Ƿ�ΪĿ¼
  Input: 
  		path		·��
  Output:
  		NULL
  Return:
  		bool true: �ɹ�  false:����ʧ��
  Note: 
  History: 
*************************************************/
 bc_boolean bc_vfs_is_dir(const char *path);

/*************************************************
  Function: bc_vfs_is_file
  Description: �ж��Ƿ�Ϊ�����ļ�
  Input: 
  		path		·��
  Output:
  		NULL
  Return:
  		bool true: �ɹ�  false:����ʧ��
  Note: 
  History: 
*************************************************/
bc_boolean bc_vfs_is_file(const char *path);

/*************************************************
  Function: bc_vfs_is_special_dir
  Description: �ж��Ƿ�������Ŀ¼
  Input: 
  		path		·��
  Output:
  		NULL
  Return:
  		bool true: �ɹ�  false:����ʧ��
  Note: 
  History: 
*************************************************/
bc_boolean bc_vfs_is_special_dir(const char *path);

/*************************************************
  Function: bc_vfs_file_path_get
  Description:�����������ļ�·��
  Input: 
  		path		·��
  		file_name		�ļ���
  		file_path				�ļ�·��
  Output:
  		NULL
  Return:
  		NULL
  Note: 
  History: 
*************************************************/
void bc_vfs_file_path_get(const char *path, const char *file_name,  char *file_path);
#endif

/*************************************************
  Function: bc_vfs_file_by_dir_delete
  Description:ɾ���ļ�·��
  Input: 
  		path		·��
  Output:
  		NULL
  Return:
  		0: �ɹ�
  		~0: ʧ��
  Note: 
  History: 
*************************************************/
bc_int32 bc_vfs_file_by_dir_delete(const char *path);

#if 0
/*************************************************
  Function: bc_file_dump
  Description: 
  Input: 
  		NULL
  Output:
  		NULL
  Return:
  		0: �ɹ�
  		
  		~0:ʧ��
  Note: 
  History: 
*************************************************/
bc_err_e bc_file_dump(void);
#endif
#endif	/*_BC_VFS_H_*/

