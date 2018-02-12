/*******************************************************************************
  Copyright (C), 2010-2030, xxxxx Tech. Co., Ltd.
  [File name]  : \\BC\Include\Common\Ipc\bc_ipc_package.h
  [Author]     : bain.wang@outlook.com
  [Version]    : 1.0
  [Date]       : 2016-04-10
  [Description]:

  [Others]     :

  [Function List]:
	1. ....
	2. ....
  [History]:
	 D a t e	Modification										  Initials
	---------- --------------										 ----------
	2016-04-10	Created 											  bain.wang@outlook.com
*******************************************************************************/

#ifndef __BC_IPC_PACKAGE_H__
#define __BC_IPC_PACKAGE_H__
   
////////////////////////////////////////////////////////////////////////////////
//																			  //
//								ͷ   ��   ��								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_err.h"
#include "bc_print.h"
#include "bc_ipc_def.h"

#define  IPC_PACKAGE_FLAG_LEN           16                                   /*IPC package flag ����*/ 
#define  IPC_PACKAGE_FLAG               "0123456789987610"                   /*IPC ����ͷ��ʶ*/ 
#define  MAC_IPC_USER_DATA_LEN          (512 *1024)                          /*����IPC�û�����*/


/*IPC ���ݰ�ͷ*/
typedef struct
{
	bc_char                        pack_flag[IPC_PACKAGE_FLAG_LEN];    /*���ݰ���ʶ*/
    bc_uint32                      pack_len;                           /*���ݰ�����*/
    bc_uint32                      sessionid;                          /*SessionID Ĭ��Ϊ0*/
    bc_uint32                      functionid;                         /*����ID*/
	bc_err_e                       function_ret;                       /*��������ֵ*/  
    bc_uint32                      rw_pos;                             /*�û����ݵ�ǰ��дλ��*/
} bc_ipc_package_head_t;


/*IPC �û����ݰ�*/
typedef struct
{ 
	bc_ipc_package_head_t	       package_head;                       /*IPC ���ݰ�ͷ*/
    bc_uint32                      user_data_size;                     /*IPC �û����ݴ�С*/  
	bc_char                        user_data[MAC_IPC_USER_DATA_LEN];   /*IPC �û�����*/
}bc_ipc_package_t;  



#define  BC_IPC_PPACK_MALLOC_RETPROC(data)  \
	do \
	{ \
		bc_err_e __ret__   = BC_ERR_OK; \
		__ret__ = bc_ipc_pacakge_alloc((bc_ipc_package_t**)&data); \
		if(__ret__ != BC_ERR_OK) \
		{ \
			BC_PT_ERROR(BC_MODULE_IPC, "Failed to malloc ipc package: ret = %d\n", __ret__); \
			return __ret__; \
		} \
	}while(0)	

#define BC_IPC_PPACK_FREE_RETPROC(data)  \
	do \
	{ \
		bc_err_e __ret__   = BC_ERR_OK; \
		__ret__ = bc_ipc_pacakge_free((bc_ipc_package_t*)data); \
		if(__ret__ != BC_ERR_OK) \
		{ \
			BC_PT_ERROR(BC_MODULE_IPC, "Failed to free ipc package: ret = %d\n", __ret__); \
			return __ret__; \
		} \
	}while(0)


/*��ʼ�����ݰ�*/
#define BC_IPC_INIT_PACK(data) \
        do\
		{\
			memset(((char*)(data)), 0x00, sizeof(bc_ipc_package_t));\
			memcpy(((char*)(data)), (char*)IPC_PACKAGE_FLAG, IPC_PACKAGE_FLAG_LEN); \
		} while (0) 

 
/*��λ�û����ݶ�дλ��*/
#define BC_IPC_PACK_WR_POS_RESET(data) \
        do\
		{\
			((data)->rw_pos) = 0;\
		} while (0) 

/*˳��д�û�����*/
#define BC_IPC_PACK_WRITE(data, p, size) \
        do\
		{\
			if(((((bc_ipc_package_t*)data)->user_data_size) + (size)) < MAC_IPC_USER_DATA_LEN) \
			{\
				memcpy((((bc_ipc_package_t*)data)->user_data) + (((bc_ipc_package_t*)data)->package_head.rw_pos), (p), (size));\
				(((bc_ipc_package_t*)data)->package_head.rw_pos) += (size);\
				(((bc_ipc_package_t*)data)->user_data_size) = (((bc_ipc_package_t*)data)->package_head.rw_pos); \
			}\
			else\
			{\
				BC_PT_DBG_PRINT(BC_MODULE_IPC, "IPC Package write data too long!\n");\
			}\
		} while (0) 

/*˳����û�����*/
#define BC_IPC_PACK_READ(data, p, size) \
        do\
		{\
			if(((((bc_ipc_package_t*)data)->package_head.rw_pos) + (size)) < MAC_IPC_USER_DATA_LEN) \
			{\
				memcpy((p), (((bc_ipc_package_t*)data)->user_data) + (((bc_ipc_package_t*)data)->package_head.rw_pos), (size));\
				(((bc_ipc_package_t*)data)->package_head.rw_pos) += (size);\
			}\
			else\
			{\
				BC_PT_DBG_PRINT(BC_MODULE_IPC, "IPC Package read data too long!\n");\
			}\
		} while (0) 

/*���û���������*/
#define BC_IPC_PACK_READ_FUN_RET(data, p) \
		do\
		{\
			(*p) = (((bc_ipc_package_t*)data)->package_head.function_ret); \
		} while (0) 
		

/*�û���������ƫ��λ��*/
#define BC_IPC_PACK_WR_POS_SET(data, pos) \
        do\
		{\
			if((pos) < MAC_IPC_USER_DATA_LEN) \
			{\
				(((bc_ipc_package_t*)data)->rw_pos) = (pos);\
			}\
			else\
			{\
				BC_PT_DBG_PRINT(BC_MODULE_IPC, "IPC Package setting position is too big!\n");\
			}\
		} while (0) 

			/*�û���������ƫ��λ��*/
#define BC_IPC_PACK_SESSION_GET(data, p) \
		do\
		{\
			(*p) = (((bc_ipc_package_t*)data)->package_head.sessionid); \
		} while (0)  




/*IPC Package ��Դ��ʼ��(�����̳�ʼ����ͬһ����ֻ��ʼ��һ��)*/
bc_err_e bc_ipc_pacakge_init(bc_uint32 max_count);
/*IPC Package ��Դ����*/
bc_err_e bc_ipc_pacakge_alloc(bc_ipc_package_t **data);
/*IPC Package ��Դ�ͷ�*/
bc_err_e bc_ipc_pacakge_free(bc_ipc_package_t  *data);
/*IPC Package ��Դdump*/
bc_err_e bc_ipc_pacakge_dump(void);



#endif /* __BC_IPC_PACKAGE_H__ */
