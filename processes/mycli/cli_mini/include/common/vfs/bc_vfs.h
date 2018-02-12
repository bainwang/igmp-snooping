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
//								头   文   件								  //
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
//								宏   定   义								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

/*文件打开方式参数*/
#define	BC_VFS_READ			"r"		/*打开只读文件，该文件必须存在*/
#define	BC_VFS_READ_RW		"r+"		/*打开可读写的文件，该文件必须存在*/
#define	BC_VFS_WRITE			"w"		/*打开只写文件，若文件存在则文件长度清为零，即该文件内容会消失。若文件不存在则建立该文件*/
#define	BC_VFS_WRITE_RW		"w+"	/*打开可读写的文件，若文件存在则文件长度清为零，即该文件内容会消失。若文件不存在则建立该文件*/
#define 	BC_VFS_ADD				"a"		/*以附加的方式打开只写文件，若文件不存在，则会建立该文件，如果文件存在，写入的数据会被加到文件尾，即文件原先的内容会被保留*/
#define	BC_VFS_ADD_RW			"a+"		/*以附加的方式打开可读写的文件。若文件不存在，则会建立该文件。如果文件存在，写入的数据会被加到文件尾后，即文件原先的内容会被保留*/
#define	BC_VFS_READ_B			"rb"		/*带有字符b，表示该文件为二进制文件*/
#define	BC_VFS_READ_BRW		"rb+"
#define	BC_VFS_WRITE_B		"wb"
#define	BC_VFS_WRITE_BRW		"wb+"
#define	BC_VFS_ADD_B			"ab"
#define	BC_VFS_ADD_BRW		"ab+"

/*文件存放路径*/
#define	BC_VFS_ROOT				"/usr/"
#define	BC_VFS_ROOT_C				BC_VFS_ROOT"cfg/"
#define	BC_VFS_ROOT_D				BC_VFS_ROOT"fw/"
#define	BC_VFS_ROOT_E				BC_VFS_ROOT"fwbak/"
#define	BC_VFS_ROOT_F				"/tmp/"
#define	BC_VFS_CFG_FILE_PATH		BC_VFS_ROOT_C"cfg/"
#define	BC_VFS_LOG_FILE_PATH		BC_VFS_ROOT_C"log/"
#define	BC_VFS_DATA_FILE_PATH		BC_VFS_ROOT_C"data/"



/*文件读写位置*/
#define	BC_VFS_SEEK_SET		0	/* Seek from beginning of file.  */
#define	BC_VFS_SEEK_CUR		1	/* Seek from current position.  */
#define	BC_VFS_SEEK_END		2	/* Seek from end of file.  */
/*文件访问方式*/
#define	BC_VFS_R_OK	4		/* Test for read permission.  */
#define	BC_VFS_W_OK	2		/* Test for write permission.  */
#define	BC_VFS_X_OK	1		/* Test for execute permission.  */
#define	BC_VFS_F_OK	0		/* Test for existence.  */
/*文件名长度*/
#define	BC_VFS_MAX_FILE_NAME_LEN		32
/*文件路径长度*/
#define	BC_VFS_MAX_FILE_PATH_LEN		64
/*文件个数*/
#define	BC_VFS_MAX_FILE_TYPE_NUM		64
/**/
#define	BC_VFS_MAX_FILE_ATTRIBUTE_SIZE		12
/**/
#define	BC_VFS_MAX_FILE_ATTRIBUTE_NUM		128
////////////////////////////////////////////////////////////////////////////////
//																			  //
//					结 构 体 、联 合 体、枚 举 定 义				          //
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
//						外 部 变 量、 函 数 声 明					          //
//																			  //
////////////////////////////////////////////////////////////////////////////////

/*************************************************
  Function: bc_file_init
  Description: 虚拟文件模块初始化
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
  Description: 查看文件是否关闭
  Input: 
  		file_name		文件名
  		file_path			文件路径
  Output:
  		NULL
  Return:
  		0: 成功
  		
  		~0:失败
  Note: 
  History: 
*************************************************/
bc_err_e bc_file_delete(bc_char *filename, bc_char *file_path);

#if 0
/*************************************************
  Function: bc_file_create
  Description: 创建文件
  Input: 
  		module_id		模块id
  		file_name		文件名
  		file_path			文件路径
  Output:
  		NULL
  Return:
  		返回指向创建好的文件指针或空
  Note: 
  History: 
*************************************************/
bc_file *bc_file_create(bc_modules_e module_id, bc_char *filename, bc_char *file_path);

/*************************************************
  Function: bc_file_close
  Description: 关闭文件
  Input: 
  		module_id		模块id
  		file_name		文件名
  		file				文件指针
  Output:
  		NULL
  Return:
  		0: 成功
  		~0: 失败
  Note: 
  History: 
*************************************************/
bc_err_e bc_file_close(bc_file *file, bc_modules_e module_id, bc_char *filename);

/*************************************************
  Function: bc_file_open
  Description:打开文件
  Input: 
  		module_id		模块id
  		file_name		文件名
  		file_path			文件路径
  		mode			打开方式
  Output:
  		NULL
  Return:
  		返回以打开好的文件指针或空  
  Note: 
  History: 
*************************************************/
bc_file *bc_file_open(bc_char *filename, bc_char *mode, bc_char *file_path, bc_modules_e module_id);


/*************************************************
  Function: bc_file_write
  Description:写文件
  Input: 
  		buff				欲写入的数据地址
  		nmemb			欲写入的总字符数
  		size      			要写入内容的单字节数
  		filename   		要写入的文件
  Output:
  		NULL
  Return:
  		返回实际写入的数目
  Note: 
  History: 
*************************************************/
bc_size_t	bc_file_write(void *buff, bc_size_t size, bc_size_t nmemb, bc_file *stream);

/*************************************************
  Function: bc_file_read
  Description: 读文件
  Input: 
  		buff				指向欲存放读取进来的数据空间
  		nmemb			实际读取到的数目
  		size      			要读取内容的单字节数
  		filename    		已打开的文件指针
  Output:
  		NULL
  Return:
  		返回实际读取到的nmemb数目
  Note: 
  History: 
*************************************************/
bc_size_t bc_file_read(void *buff, bc_size_t size, bc_size_t nmemb, bc_file *stream);

/*************************************************
  Function: bc_file_is_closed
  Description: 查看文件是否关闭
  Input: 
  		module_id		模块id
  		file_name		文件名
  		file				文件指针
  Output:
  		NULL
  Return:
  		0: 关闭
  		~0: 未关闭
  Note: 
  History: 
*************************************************/
//bc_err_e bc_file_is_closed(bc_modules_e module_id, bc_char *file_path, bc_char *filename);

/*************************************************
  Function: bc_file_copy
  Description: 查看文件是否关闭
  Input: 
  		src_filename		源文件名
  		des_filename		目的文件名
  		srcpath			源路径
  		despath			目的路径
  Output:
  		NULL
  Return:
  		0: 成功
  		
  		~0:失败
  Note: 
  History: 
*************************************************/
bc_err_e bc_file_copy(bc_char *src_filename, bc_char *des_filename, bc_char *srcpath, bc_char *despath);

/*************************************************
  Function: bc_file_seek
  Description: 移动文件流 的读写位置
  Input: 
  		fp				文件指针
  		offset			位移量
  		whence			移动方式
  Output:
  		NULL
  Return:
  		0: 成功
  		~0: 失败
  Note: 
  History: 
*************************************************/
bc_int32 bc_file_seek(bc_file *fp, bc_long offset, bc_int32 whence);

/*************************************************
  Function: bc_file_access
  Description: 检查是否可以读写某一已存在的文件
  Input: 
  		file_name		文件名
  		file				文件指针
  		mode			检查方式
  Output:
  		NULL
  Return:
  		0: 成功
  		~0: 失败
  Note: 
  History: 
*************************************************/
bc_err_e bc_file_access(bc_char *filename, bc_char *filepath, bc_int32 mode);

/*************************************************
  Function: bc_file_get_file_directory
  Description: 获取文件属性
  Input: 
  		path				文件路径
  		file_attribute		文件属性
  Output:
  		NULL
  Return:
  		0: 成功
  		~0: 失败
  Note: 
  History: 
*************************************************/
bc_err_e bc_file_get_file_directory(bc_char *path, bc_file_attribute *file_attribute);

/*************************************************
  Function: bc_vfs_is_dir
  Description:  判断是否为目录
  Input: 
  		path		路径
  Output:
  		NULL
  Return:
  		bool true: 成功  false:非零失败
  Note: 
  History: 
*************************************************/
 bc_boolean bc_vfs_is_dir(const char *path);

/*************************************************
  Function: bc_vfs_is_file
  Description: 判断是否为常规文件
  Input: 
  		path		路径
  Output:
  		NULL
  Return:
  		bool true: 成功  false:非零失败
  Note: 
  History: 
*************************************************/
bc_boolean bc_vfs_is_file(const char *path);

/*************************************************
  Function: bc_vfs_is_special_dir
  Description: 判断是否是特殊目录
  Input: 
  		path		路径
  Output:
  		NULL
  Return:
  		bool true: 成功  false:非零失败
  Note: 
  History: 
*************************************************/
bc_boolean bc_vfs_is_special_dir(const char *path);

/*************************************************
  Function: bc_vfs_file_path_get
  Description:生成完整的文件路径
  Input: 
  		path		路径
  		file_name		文件名
  		file_path				文件路径
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
  Description:删除文件路径
  Input: 
  		path		路径
  Output:
  		NULL
  Return:
  		0: 成功
  		~0: 失败
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
  		0: 成功
  		
  		~0:失败
  Note: 
  History: 
*************************************************/
bc_err_e bc_file_dump(void);
#endif
#endif	/*_BC_VFS_H_*/

