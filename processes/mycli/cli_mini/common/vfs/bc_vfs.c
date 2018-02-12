/************************************************************
  Copyright (C), 1988-2014, xxxxx Tech. Co., Ltd.
  FileName: \\OLT\common\vfs\bc_vfs.c
  Author:  zhanglei      Version :  1.0        Date:2014-5-26
  Description:                   
  Version:                        
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								头   文   件								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include "bc_platform_mutex.h"
#include "bc_modules.h"
#include "bc_print.h"
#include	"bc_vfs.h"

////////////////////////////////////////////////////////////////////////////////
//																			  //
//						外 部 变 量、 函 数 引 用					  //
//																			  //
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//																			  //
//						结   构   体   宏   定   义							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////


/*		当源文件需要定义宏，而头文件又与其它模块头文件中的宏定义有重复定义嫌疑
 *	时，在此处定义。
 */

#define VFS_FILE_NAME	"vfs_data_file"
#define VFS_FILE_PATH_LEN_MAX		BC_VFS_MAX_FILE_NAME_LEN+BC_VFS_MAX_FILE_PATH_LEN
#define VFS_ERR_FLAG	-1
#define BC_VFS_BUFFER_SIZE	1024
#define BC_VFS_UNUSEED		-1

#define BC_VFS_MUTEX_NAME                 "vfs mutex"            /*VFS资源互斥量*/ 
static bc_pthread_mutex_t *bc_vfs_mutex;
#define BC_VFS_MUTEX_LOCK()		bc_platform_mutex_lock(bc_vfs_mutex)
#define BC_VFS_MUTEX_UNLOCK()		bc_platform_mutex_unlock(bc_vfs_mutex)
#define BC_VFS_PATH_MAX 255
typedef enum
{
	BC_VFS_OPRATE_CREATE = 1,
	BC_VFS_OPRATE_OPEN,
	BC_VFS_OPRATE_CLOSE,
	BC_VFS_OPRATE_DELETE,
	BC_VFS_OPRATE_IS_CLOSED
} bc_vfs_opreate_t;

typedef struct{
	bc_modules_e		module_id;/*模块id*/
	bc_char			file_name[BC_VFS_MAX_FILE_NAME_LEN];/*文件名字*/
	bc_char			mod_name[BC_VFS_MAX_FILE_NAME_LEN];
	bc_char			file_path[BC_VFS_MAX_FILE_PATH_LEN];
	bc_boolean		closed;
	bc_uint32			open_counter;/*记录文件被打开的次数*/
	bc_uint32			close_counter;/*记录文件关闭的次数*/
} bc_file_type_t;

typedef struct{
	bc_int32			num;
	bc_uint32			file_open_counter;/*记录文件被打开的次数*/
	bc_uint32			file_close_counter;/*记录文件关闭的次数*/
	bc_file_type_t		file_type[BC_VFS_MAX_FILE_TYPE_NUM];
}bc_file_type;

////////////////////////////////////////////////////////////////////////////////
//																			  //
//							全 局 变 量 定 义							      //
//																			  //
////////////////////////////////////////////////////////////////////////////////
/* 
 *	外部全局变量，提供整个工程调用，在头文件中提供调用接口(外部引用声明)。
 */

/* 
 *	内部全局变量，只提供给该文件内部函数调用，不在头文件中提供调用接口。
 */

static bc_file_type file_type_globle;
////////////////////////////////////////////////////////////////////////////////
//																			  //
//								函  数  声  明							      //
//																			  //
////////////////////////////////////////////////////////////////////////////////



/*获取文件类型属性*/
static bc_file_type* __get_file_type(void);
/*设置文件类型*/
//static bc_int32 __bc_file_set_type(bc_modules_e module_id, bc_char *filename, bc_char *file_path );

//static void __bc_file_save_clear(void);

//static bc_int32 __bc_file_is_exist(bc_modules_e module_id, bc_char *filename);

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								函  数  定  义							      //
//																			  //
////////////////////////////////////////////////////////////////////////////////
#if 1

/******************************************************************************\
  Function   : get_file_type
  Description: 获取文件类型属性
  Return     : 无
  Others     : 
\******************************************************************************/
static bc_file_type* __get_file_type(void)
{	
	return (bc_file_type*)&file_type_globle;
}
#if 0
/******************************************************************************\
  Function   : bc_file_set_type
  Description: 设置文件类型
  Return     : 无
  Others     : 
\******************************************************************************/
static bc_int32 __bc_file_set_type(bc_modules_e module_id, bc_char *filename, bc_char *file_path )
{
	bc_file_type *file_type_s = NULL;
	bc_int32  index;
	bc_char *module_name;
	
	file_type_s = __get_file_type();	
	index =  file_type_s->num;
	if (index > BC_VFS_MAX_FILE_TYPE_NUM)
		return VFS_ERR_FLAG;
	module_name = bc_modules_get_module_name(module_id);
 	BC_VFS_MUTEX_LOCK();
	file_type_s->num = index + 1;
	index = file_type_s->num;
	file_type_s->file_type[index].module_id = module_id;
	file_type_s->file_open_counter ++;
	strncpy(file_type_s->file_type[index].file_name, filename, sizeof(file_type_s->file_type[index].file_name));
	strncpy(file_type_s->file_type[index].mod_name, module_name, sizeof(file_type_s->file_type[index].mod_name));
	strncpy(file_type_s->file_type[index].file_path, file_path, sizeof(file_type_s->file_type[index].file_path));
	file_type_s->file_type[index].closed = FALSE;
	 BC_VFS_MUTEX_UNLOCK();
	return 0;
}
#endif


static bc_int32 __bc_file_note_file_opreate(bc_int32 num, bc_vfs_opreate_t operate_id)
{
	bc_file_type *file_type_n = NULL;
	bc_int32 ret = VFS_ERR_FLAG;
	
	file_type_n = __get_file_type();
	
	//index = __bc_file_is_exist(module_id, filename);
	if (num != VFS_ERR_FLAG)
	{
		BC_VFS_MUTEX_LOCK();
		switch(operate_id)
		{
			case BC_VFS_OPRATE_CREATE:
				file_type_n->file_open_counter++;
				file_type_n->file_type[num].open_counter++;
				ret = 0;
				break;
			case BC_VFS_OPRATE_OPEN:
				file_type_n->file_type[num].closed = FALSE;
				file_type_n->file_open_counter++;
				file_type_n->file_type[num].open_counter++;
				ret = 0;
				break;
			case BC_VFS_OPRATE_CLOSE:
				file_type_n->file_close_counter++;
				file_type_n->file_type[num].close_counter++;
				file_type_n->file_type[num].closed = TRUE;
				ret = 0;
				break;
			case BC_VFS_OPRATE_DELETE:
				file_type_n->file_type[num].closed = TRUE;
				file_type_n->file_type[num].module_id = BC_VFS_UNUSEED;
				memset(file_type_n->file_type[num].file_name, 0 , sizeof(file_type_n->file_type[num].file_name));
				memset(file_type_n->file_type[num].mod_name, 0 , sizeof(file_type_n->file_type[num].mod_name));
				memset(file_type_n->file_type[num].file_path, 0 ,sizeof(file_type_n->file_type[num].file_path));
				file_type_n->file_type[num].open_counter = 0;
				file_type_n->file_type[num].close_counter = 0;
				file_type_n->num--;
				ret = 0;
				break;
			default:
				ret = VFS_ERR_FLAG;
		}
		 BC_VFS_MUTEX_UNLOCK();
		 return ret;
	}

	return ret;		
}

#if 0
/******************************************************************************\
  Function   : bc_mode_to_letter
  Description: 转化stat库函数中st_mode模式值为字符串
  Return     : 无
  Others     : 
\******************************************************************************/
static void __bc_mode_to_letter(int mode, char *str)
{
	str[0]='-';
	if (S_ISDIR(mode))
		str[0]='d';
	if (S_ISCHR(mode))
		str[0]='c';
	if (S_ISBLK(mode))
		str[0]='b';
	if (mode&S_IRUSR)
		str[1]='r';
	else
		str[1]='-';
	if (mode&S_IWUSR)
		str[2]='w';
	else
		str[2]='-';
	if (mode&S_IXUSR)
		str[3]='x';
	else
		str[3]='-';
	if (mode&S_IRGRP)
		str[4]='r';
	else
		str[4]='-';
	if (mode&S_IWGRP)
		str[5]='w';
	else
		str[5]='-';
	if (mode&S_IXGRP)
		str[6]='x';
	else
		str[6]='-';
	if (mode&S_IROTH)
		str[7]='r';
	else
		str[7]='-';
	if (mode&S_IWOTH)
		str[8]='w';
	else
		str[8]='-';
	if (mode&S_IXOTH)
		str[9]='x';
	else
		str[9]='-';
	str[10]='\0';
}

/******************************************************************************\
  Function   : bc_file_save_clear
  Description: 删除文件
  Return     : 无
  Others     : 
\******************************************************************************/

/*static void __bc_file_save_clear(void)
{
	bc_file_delete(VFS_FILE_NAME, BC_VFS_DATA_FILE_PATH);
	return;
}*/



static bc_int32 __bc_file_is_exist(bc_modules_e module_id, bc_char *filename)
{
	bc_file_type *file_type_e = NULL;
	bc_int32 index,i;
	
	file_type_e = __get_file_type();
	index = file_type_e ->num + 1;	
	for (i = 0; i < index; i++)
	{
		if (module_id == file_type_e->file_type[i].module_id)
		{
			if (0 == strncmp(file_type_e->file_type[i].file_name, filename, sizeof(file_type_e->file_type[i].file_name)) )
			{
				return i;
			}
		}
	}
	return VFS_ERR_FLAG;
}
#endif

static bc_int32 __bc_file_is_exist_by_name(bc_char *filename, bc_char *file_path)
{
	bc_file_type *file_type_m = NULL;
	bc_int32 index,i;
	
	file_type_m = __get_file_type();
	index = file_type_m ->num + 1;
	
	for (i = 0; i < index; i++)
	{
		if (0 == strncmp(file_type_m->file_type[i].file_name, filename, sizeof(file_type_m->file_type[i].file_name)))
		{
			if (0 == strncmp(file_type_m->file_type[i].file_path, file_path, sizeof(file_type_m->file_type[i].file_path)))
			{
				return i;
			}
		}

	}
	return VFS_ERR_FLAG;
}

#if 0
static bc_uint32 __bc_file_get_open_couter(bc_char *filename, bc_char *file_path)
{
	bc_file_type *file_type_m = NULL;
	bc_int32  index,i;
	
	file_type_m = __get_file_type();
	index = file_type_m ->num + 1;
	for (i = 0; i < index; i++)
	{
		if (0 == strncmp(file_type_m->file_type[i].file_name, filename, sizeof(file_type_m->file_type[i].file_name)))
		{
			if (0 == strncmp(file_type_m->file_type[i].file_path, file_path, sizeof(file_type_m->file_type[i].file_path)))
			{
				return file_type_m->file_type[i].open_counter;
			}
		}

	}
	return 0;
}


static bc_int32 __bc_file_copy(const char *filename_src, const char *filename_dst)
{
	bc_file *fp_src = NULL;
	bc_file *fp_dst = NULL;
	bc_char buffer[BC_VFS_BUFFER_SIZE];
	bc_size_t numread = 0;
	bc_size_t numwritten = 0;

	if ((fp_src = fopen(filename_src, BC_VFS_READ)) == NULL)
	{
		return VFS_ERR_FLAG;
	}
	if ((fp_dst = fopen(filename_dst, BC_VFS_WRITE_RW)) == NULL)
	{	
		fclose(fp_src);
		return VFS_ERR_FLAG;
	}
	while ((numread = fread(buffer, sizeof(char), BC_VFS_BUFFER_SIZE, fp_src)))
	{
		if (numread == 0)
			break;
		if ((numwritten = fwrite(buffer, sizeof(char), numread, fp_dst)) != numread)
		{
			fclose(fp_src);
			fclose(fp_dst);
			return VFS_ERR_FLAG;
		}
	}
	
	fclose(fp_src);
	fclose(fp_dst);
	
	return 0;
}
#endif

static bc_boolean __bc_file_is_dir(const char *path)
{
	struct stat statbuf;
	
	if (lstat(path, &statbuf) ==0)/*lstat返回文件的信息，文件信息存放在stat结构中*/
	{
		if (S_ISDIR(statbuf.st_mode) != 0)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	return FALSE;
}

static bc_boolean __bc_file_is_file(const char *path)
{
	struct stat statbuf;
	
	if (lstat(path, &statbuf) ==0)
	{
		if (S_ISREG(statbuf.st_mode) != 0)
		{
        		return TRUE;
        	}
		else
		{
			return FALSE;
		}
	} 
	return FALSE;
}

static bc_boolean __bc_file_is_special_dir(const char *path)
{
	if (strcmp(path, ".") == 0 || strcmp(path, "..") == 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

static void __bc_file_get_file_path(const char *path, const char *file_name, char *file_path)
{
	strcpy(file_path, path);
	if (file_path[strlen(path) - 1] != '/')
		strcat(file_path, "/");
	strcat(file_path, file_name);
}

/*static bc_boolean __bc_file_get_file_is_closed(bc_int32 index)
{
	bc_file_type *file_type_e = NULL;
	
	file_type_e = __get_file_type();
	return file_type_e->file_type[index].closed;
}
*/

static void __bc_file_dir_create(void)
{
	if (access(BC_VFS_CFG_FILE_PATH, BC_VFS_F_OK) == -1)
		mkdir(BC_VFS_CFG_FILE_PATH, 0777);
	
	if (access(BC_VFS_LOG_FILE_PATH, BC_VFS_F_OK) == -1)
		mkdir(BC_VFS_LOG_FILE_PATH, 0777);
	
	if (access(BC_VFS_DATA_FILE_PATH, BC_VFS_F_OK) == -1)
		mkdir(BC_VFS_DATA_FILE_PATH, 0777);
}
#endif

#if 1

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

bc_err_e bc_file_init(void)
{
	bc_file_type *file_type_i = NULL;
	bc_uint32 i;

	bc_vfs_mutex = bc_platform_mutex_create((bc_char*)BC_VFS_MUTEX_NAME);
	if (NULL == bc_vfs_mutex)
	{
		BC_PT_ERROR(BC_MODULE_VFS, "Failed to create mutex!");
		return BC_ERR_RESOURCE;
	}
	
	file_type_i = __get_file_type();
	file_type_i->num = BC_VFS_UNUSEED;
	file_type_i->file_close_counter = 0;
	file_type_i->file_open_counter = 0;
	for (i = 0; i < BC_VFS_MAX_FILE_TYPE_NUM; i++)
	{
		file_type_i->file_type[i].closed = FALSE;
		file_type_i->file_type[i].module_id = BC_VFS_UNUSEED;
		file_type_i->file_type[i].close_counter = 0;
		file_type_i->file_type[i].open_counter = 0;
		memset(file_type_i->file_type[i].file_name, 0, sizeof(file_type_i->file_type[i].file_name));
		memset(file_type_i->file_type[i].file_path, 0, sizeof(file_type_i->file_type[i].file_path));
	}
	__bc_file_dir_create();
	return BC_ERR_OK;
}

#if 0
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
bc_err_e bc_file_get_file_directory(bc_char *path, bc_file_attribute *file_attribute)
{
	DIR *dp;
	struct dirent *dirp;
	struct stat buf;
	struct tm *p;
	bc_uint32 index = 0;
	char str[12];

	if ((!path) || (!file_attribute))
		return BC_ERR_PARA;
	
	if (!(dp = opendir(path)))
	{
		return BC_ERR_PARA;
	}
	
	while ((dirp=readdir(dp)) != NULL)
	{
		stat(dirp->d_name, &buf);
		__bc_mode_to_letter(buf.st_mode, str);
		p=localtime(&buf.st_ctime);
		memcpy(file_attribute->file_attribute[index].filename, dirp->d_name, sizeof(file_attribute->file_attribute[index].filename));
		memcpy(file_attribute->file_attribute[index].file_type, str, sizeof(file_attribute->file_attribute[index].file_type));
		file_attribute->file_attribute[index].size = buf.st_size;
		file_attribute->file_attribute[index].f_year = 1900+p->tm_year;
		file_attribute->file_attribute[index].f_mon = 1+p->tm_mon;
		file_attribute->file_attribute[index].f_mday = p->tm_mday;
		file_attribute->file_attribute[index].f_hour = p->tm_hour;
		file_attribute->file_attribute[index].f_min = p->tm_min;
		file_attribute->file_attribute[index].f_sec = p->tm_sec;
		index++;
		
	}
	file_attribute->num= index;
	closedir(dp);
	return BC_ERR_OK;
	
}

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

bc_file *bc_file_create(bc_modules_e module_id, bc_char *filename, bc_char *file_path)
{
	bc_file *fp =NULL;
	bc_char path[VFS_FILE_PATH_LEN_MAX];
	bc_uint32 index;
	
	if (BC_ERR_OK !=bc_modules_valid_id(module_id))
		return NULL;
	
	if ((!filename) || (!file_path))
		return NULL;
		
	snprintf(path, VFS_FILE_PATH_LEN_MAX, "%s%s", file_path,filename);
	index = __bc_file_is_exist(module_id, filename);
	if( index != VFS_ERR_FLAG)
	{
		fp = fopen(path,"a+");
		if (fp != NULL)
			__bc_file_note_file_opreate(index, BC_VFS_OPRATE_CREATE);
		return fp;
	}
	else
	{
		fp = fopen(path,"w");
		if (fp !=  NULL)
			__bc_file_set_type(module_id, filename, file_path);
		return fp;
	}
}

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
bc_err_e bc_file_close(bc_file *file, bc_modules_e module_id, bc_char *filename)
{
	bc_int32 ret;
	bc_int32 index;
	
	if ((!file) || (!filename))
		return BC_ERR_PARA;

	if (BC_ERR_OK !=bc_modules_valid_id(module_id))
		return BC_ERR_PARA;
	
	ret = fclose(file);
	if (ret == 0)
	{
		index = __bc_file_is_exist(module_id, filename);
		if (index != VFS_ERR_FLAG)
			__bc_file_note_file_opreate( index, BC_VFS_OPRATE_CLOSE);
		return BC_ERR_OK;
	}
	return BC_ERR_VFS_CLOSE_FAIL;
}

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
bc_file *bc_file_open(bc_char *filename, bc_char *mode, bc_char *file_path, bc_modules_e module_id)
{
	bc_file *fp;
	bc_int32 index;
	bc_char path[VFS_FILE_PATH_LEN_MAX];
	bc_uint32 open_couter;
	
	if ((!filename) || (!mode) || (!file_path))
		return NULL;
	
	if (BC_ERR_OK !=bc_modules_valid_id(module_id))
		return NULL;

	snprintf(path, VFS_FILE_PATH_LEN_MAX, "%s%s", file_path, filename);
	if (0 == access(path, BC_VFS_F_OK))
	{
		fp = fopen(path, mode);
		if (fp !=  NULL)
		{
			index = __bc_file_is_exist(module_id, filename);
			if (index != VFS_ERR_FLAG)/*该文件在该模块已被记录*/
			{
				__bc_file_note_file_opreate(index, BC_VFS_OPRATE_OPEN);
			}
			
			open_couter = __bc_file_get_open_couter(filename, file_path);
			if ((index == VFS_ERR_FLAG)&&(open_couter > 0))/*该模块未在该模块记录，但在其他模块有记录*/
			{
				fclose(fp);
				return NULL;
			}
			if ((index == VFS_ERR_FLAG)&&(open_couter == 0))/*该文件未被任何模块记录，记录到该模块*/
			{
				__bc_file_set_type(module_id, filename, file_path);
			}
		}
		return fp;
	}
	else
	{
		fp = fopen(path, mode);
		if (fp !=  NULL)
		{
			__bc_file_set_type(module_id, filename, file_path);
		}
		return fp;
	}
}

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
bc_size_t	bc_file_write(void *buff, bc_size_t size, bc_size_t nmemb, bc_file *stream)
{
	bc_size_t result = -1;
	
	if (NULL == stream)
		return result;
	
	result = fwrite(buff, size, nmemb, stream);
	return result;
}


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
bc_size_t bc_file_read(void *buff, bc_size_t size, bc_size_t nmemb, bc_file *stream)
{
	bc_size_t result = -1;
	
	if (NULL == stream)
		return result;
	
	result = fread(buff, size, nmemb, stream);
	return result;
}

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
bc_err_e bc_file_access(bc_char *filename, bc_char *file_path, bc_int32 mode)
{	
	bc_char path[VFS_FILE_PATH_LEN_MAX];
	
	if ((!filename) ||(!file_path))
		return BC_ERR_PARA;
	
	snprintf(path, VFS_FILE_PATH_LEN_MAX, "%s%s", file_path, filename);
	if (access(path, mode) == 0)
	{
		return BC_ERR_OK;
	}
	
	return BC_ERR_NOT_EXSIT;
}

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
bc_int32 bc_file_seek(bc_file *fp, bc_long offset, bc_int32 whence)
{	
	bc_int32 ret = -1;
	
	if (NULL == fp)
		return ret;
	
	ret = fseek(fp, offset, whence);	
	return ret;
}
#endif

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
bc_err_e bc_file_delete(bc_char *filename, bc_char *file_path)
{
	bc_char path_d[VFS_FILE_PATH_LEN_MAX];
	bc_int32 index;
	bc_int32 ret;
	
	if ((!filename)||(!file_path))
		return BC_ERR_PARA;

	snprintf(path_d, VFS_FILE_PATH_LEN_MAX, "%s%s", file_path, filename);
	
	ret = remove(path_d);
	if (ret == 0)
	{
		index = __bc_file_is_exist_by_name(filename, file_path);
		if (index != VFS_ERR_FLAG)
		{
			__bc_file_note_file_opreate(index, BC_VFS_OPRATE_DELETE);
		}
		return BC_ERR_OK;
	}
	
	return BC_ERR_VFS_DELETE_FAIL;
}

#if 0
/*************************************************
  Function: bc_file_copy
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
bc_err_e bc_file_copy(bc_char *src_filename, bc_char *des_filename, bc_char *srcpath, bc_char *despath)
{
	bc_char src_path[VFS_FILE_PATH_LEN_MAX];
	bc_char des_path[VFS_FILE_PATH_LEN_MAX];
	bc_int32 ret;
	
	if ((!src_filename)||(!des_filename)||(!srcpath)||(!despath))
		return BC_ERR_PARA;

	snprintf(src_path, VFS_FILE_PATH_LEN_MAX, "%s%s", srcpath,src_filename);
	snprintf(des_path, VFS_FILE_PATH_LEN_MAX, "%s%s", despath,des_filename);
	ret = __bc_file_copy(src_path, des_path);
	if (ret != VFS_ERR_FLAG)
		return BC_ERR_OK;

	return BC_ERR_VFS_COPY_FAIL;
}


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
/*bc_err_e bc_file_is_closed(bc_modules_e module_id, bc_char *file_path, bc_char *filename)
{
	bc_uint32  index;
	bc_boolean flag;
	
	if (NULL == file_path)
		return BC_ERR_PARA;
	
	if (NULL == filename)
		return BC_ERR_PARA;

	if (BC_ERR_OK !=bc_modules_valid_id(module_id))
		return BC_ERR_PARA;
	
	index = __bc_file_is_exist(module_id, filename);
	if (index != VFS_ERR_FLAG)
	{
		flag = __bc_file_get_file_is_closed(index);
		if (flag == TRUE)
		{
			return BC_ERR_OK;
		}
	}
	return BC_ERR_NOT_EXSIT;
}*/
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
 bc_boolean bc_vfs_is_dir(const char *path)
{
	struct stat statbuf;
	
	if (lstat(path, &statbuf) ==0)/*lstat返回文件的信息，文件信息存放在stat结构中*/
	{
		return (S_ISDIR(statbuf.st_mode) != 0);
	}
	return FALSE;
}

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
bc_boolean bc_vfs_is_file(const char *path)
{
	struct stat statbuf;
	
	if (lstat(path, &statbuf) ==0)
	{
		return (S_ISREG(statbuf.st_mode) != 0);
	} 
	return FALSE;
}

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
bc_boolean bc_vfs_is_special_dir(const char *path)
{
	return (strcmp(path, ".") == 0 || strcmp(path, "..") == 0);	
}

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
void bc_vfs_file_path_get(const char *path, const char *file_name,  char *file_path)
{
	strcpy(file_path, path);
	if (file_path[strlen(path) - 1] != '/')
	{
		strcat(file_path, "/");
	}
	strcat(file_path, file_name);
}
#endif

/*************************************************
  Function: bc_vfs_file_by_dir_delete
  Description:删除文件路径
  Input: 
  		path		路径
  Output:
  		NULL
  Return:
  		NULL
  Note: 
  History: 
*************************************************/
bc_int32 bc_vfs_file_by_dir_delete(const char *path)
{
	DIR *dir;
	struct dirent *dir_info;
	char file_path[BC_VFS_PATH_MAX];
	
	if (__bc_file_is_file(path))
	{
		return -1;
	}
	
	if (__bc_file_is_dir(path))
	{
		if ((dir = opendir(path)) == NULL)
			return -1;
		
		while ((dir_info = readdir(dir)) != NULL)
		{
			__bc_file_get_file_path(path, dir_info->d_name, file_path);
			if (__bc_file_is_special_dir(dir_info->d_name))
				continue;

			if (__bc_file_is_file(file_path))
			{
				if (remove(file_path) != 0)
				{
					printf("delete file %s failed\n", file_path);
					return -1;
				}
				
				if (access(file_path, 0) == 0)
				{
					return -1;
				}
			}
		}
	}
	return 0;
}

/*bc_int32 bc_file_save_cfg(void)
{
	bc_file *fp_cfg = NULL;
	bc_uint32  wrt_count = 0;
	bc_file_type *file_type_s = NULL;

	file_type_s = __get_file_type();
	fp_cfg = bc_file_open(VFS_FILE_NAME, BC_VFS_ADD_RW, BC_VFS_DATA_FILE_PATH, BC_MODULE_VFS);
	if (NULL == fp_cfg)
	{
		return -1;
	}

	wrt_count = bc_file_write(file_type_s, sizeof(bc_file_type), 1, fp_cfg);
	if (0 == wrt_count)
	{
		bc_file_close(fp_cfg, BC_MODULE_VFS, VFS_FILE_NAME);
		return -1;
	}

	bc_file_close(fp_cfg, BC_MODULE_VFS, VFS_FILE_NAME);

	return BC_ERR_OK;
}*/
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
bc_err_e bc_file_dump(void)
{
	bc_file_type *file_type_d = NULL;
	bc_int32 i;
	bc_char* closed_str[] = {"FALSE", "TRUE"};
	file_type_d = __get_file_type();
	
	BC_PT_COMMAND(BC_MODULE_VFS, "bc_vfs dump:\n");	
	BC_PT_COMMAND(BC_MODULE_VFS, "bc_vfs_mutex: 0x%08x\n", (bc_uint32)bc_vfs_mutex);
	BC_PT_COMMAND(BC_MODULE_VFS, "index: %d\n", file_type_d->num);
	BC_PT_COMMAND(BC_MODULE_VFS, "file_open_counter: %d\n", file_type_d->file_open_counter);
	BC_PT_COMMAND(BC_MODULE_VFS, "file_close_counter: %d\n", file_type_d->file_close_counter);
	BC_PT_COMMAND(BC_MODULE_VFS, "%-10s%-32s%-32s%-6s\n", "module_id", "file_name", "file_path", "closed");
	BC_PT_COMMAND(BC_MODULE_VFS, "%-10s%-32s%-32s%-6s\n", "--------", "--------------------------------", "--------------------------------", "-----");
	for ( i = 0; i < BC_VFS_MAX_FILE_TYPE_NUM; i++)
	{
		BC_PT_COMMAND(BC_MODULE_VFS, "%-10d%-32s%-32s%-6s\n", file_type_d->file_type[i].module_id,
																   file_type_d->file_type[i].file_name, file_type_d->file_type[i].file_path,
																   closed_str[file_type_d->file_type[i].closed]);
	}
	BC_PT_COMMAND(BC_MODULE_VFS, "\n");
	
	return BC_ERR_OK;
}
#endif
#endif

