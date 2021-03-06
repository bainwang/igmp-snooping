/*******************************************************************************
  -------------------------------------------------------------------------
  [Author]     : bain.wang@outlook.com
  [Version]    : 1.0
  [Date]       : 2017-06-11
  [Description]:

  [Others]     :

  [Function List]:  
    1. ....
    2. ....
  [History]:
	 D a t e    Modification 										  Initials
	---------- --------------                                        ----------
	2016-08-05  Created									bain.wang@outlook.com
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								头   文   件								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "bc_modules.h"

#include "bc_cli_type.h"
#include "bc_cli_paratype.h"

#include "bc_cli.h"

#include "utili_bit.h"
//#include "bc_cli_cmd_port.h"
////////////////////////////////////////////////////////////////////////////////
//																			  //
//						外 部 变 量、 函 数 引 用					          //
//																			  //
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//																			  //
//						结   构   体   宏   定   义							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
/*
 *		当源文件需要定义宏，而头文件又与其它模块头文件中的宏定义有重复定义嫌疑
 *	时，在此处定义。
 */


bc_char ptcode_ipc[][256] = 
{
"/******************************************************************************\\",
"  Function   : thread_ipc_porcess",
"  Description: IPC thread handler (sync)",
"  Return     :", 
"  Others     :", 
"\\******************************************************************************/",
"static void __ipc_process_thread(void *para)",
"{",
"	bc_ipc_proc_thread_t *ipc_pro = NULL;",
"	struct timeval send_timeout 	= {2,0};", 
"	struct timeval recv_timeout 	= {10,0};",
"",
"	bc_err_e ret = BC_ERR_OK;",
"	",
"	ipc_pro = (bc_ipc_proc_thread_t*)para;",
"	ipc_pro->package = bc_platform_mem_malloc(BC_MODULE_IPC, sizeof(bc_ipc_package_t));",
"	if (NULL == ipc_pro->package)",
"	{",
"		BC_PT_ERROR(BC_MODULE_IPC, \"Failed to malloc memory!\\r\\n\");",
"		return;",
"	}",
"	",
"	while (TRUE)",
"	{",
"		bc_platform_sem_wait(ipc_pro->proc_sem, BC_SEM_WAIT_FOREVER);",
"		BC_PT_DBG_CPL(BC_MODULE_IPC, \"SRV: will recv from client....\\n\");",
"		if (ipc_pro->is_process == FALSE)",
"		{",
"			ipc_pro->fd_para_err_cnt++;",
"			continue;",
"		}",
"",
"		if (ipc_pro->fd_socket == INVALID_SOCKET)",
"		{",
"			ipc_pro->fd_para_err_cnt++;",
"			continue;",
"		}",
"",
"		setsockopt(ipc_pro->fd_socket, SOL_SOCKET, SO_SNDTIMEO, (char*)&send_timeout, sizeof(struct timeval));  /* set tx tic*/",
"		setsockopt(ipc_pro->fd_socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&recv_timeout, sizeof(struct timeval));  /* set rx tic*/",
"",
"		/*recv data*/",
"		BC_IPC_INIT_PACK(ipc_pro->package);",
"		ret = bc_ipc_package_recv(ipc_pro->fd_socket, ipc_pro->package);",
"		if (ret != BC_ERR_OK)",
"		{",
"			BC_PT_DBG_CPL(BC_MODULE_IPC, \"SRV: recv failure ....\\n\");",
"			ipc_pro->fd_data_recv_err_cnt++;",
"			__ipc_process_close_deal(ipc_pro);",
"			continue;",
"		}",
"",
"		BC_PT_DBG_CPL(BC_MODULE_IPC, \"SRV: recv successd ....\\n\");",
"		/* recv data check */",
"		",
"		ipc_pro->functionid = ipc_pro->package->package_head.functionid;",
"		time(&ipc_pro->start_time);",
"",
"		ret = ipc_pro->srv_proc(ipc_pro->package);",
"		if (ret != BC_ERR_OK)",
"		{",
"			BC_PT_DBG_CPL(BC_MODULE_IPC, \"SRV: srv_proc func failure ....\\n\");",
"			ipc_pro->fd_data_op_err_cnt++;",
"			__ipc_process_close_deal(ipc_pro);",
"			continue;",
"		}",
"		BC_PT_DBG_CPL(BC_MODULE_IPC, \"SRV: srv_proc func successd ....\\n\");",
"		",
"		if (ipc_pro->package->user_data_size > MAC_IPC_USER_DATA_LEN)",
"		{",
"			ipc_pro->fd_data_op_para_err_cnt++;",
"			__ipc_process_close_deal(ipc_pro);",
"			continue;",
"		}",
"",
"		BC_PT_DBG_CPL(BC_MODULE_IPC, \"SRV: will send to client ....\\n\");",
"	",	
"		/*reset rw offset*/",
"		time(&ipc_pro->end_time);",
"		ipc_pro->package->package_head.rw_pos = 0;",
"		ipc_pro->package->package_head.pack_len = ",
"			sizeof(bc_ipc_package_head_t) + sizeof(ipc_pro->package->user_data_size) + ipc_pro->package->user_data_size;",
"		ret = bc_ipc_package_send(ipc_pro->fd_socket, ipc_pro->package);",
"		if(ret != BC_ERR_OK)",
"		{",
"			BC_PT_DBG_CPL(BC_MODULE_IPC, \"SRV: send to client failure....\\n\");",
"			ipc_pro->fd_data_send_err_cnt++;",
"		}",
"		else",
"		{",
"			BC_PT_DBG_CPL(BC_MODULE_IPC, \"SRV: send to client successed....\\n\");",
"			ipc_pro->fd_process_response_cnt++;",
"		}",
"		",
"		__ipc_process_close_deal(ipc_pro);",
"    }",
"}",
"the_end"
};
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
 static unsigned int 	l_mdl_id = BC_MODULE_CLI;

#define DEBUG_CMD_EN	FALSE

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								函  数  声  明							      //
//																			  //
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								函  数  定  义							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////




#if 1
/******************************************************************************\
  Function   : __filetrans_transmission_show
  Description: 显示下载中的信息
  Return     : bool true: 成功  false:非零失败
  Others     : 
\******************************************************************************/
static bc_err_e __ptcode_show_ipc()
{
	int i = 0;

	while(ptcode_ipc+i)
	{
		if(!strcmp("the_end", ptcode_ipc+i))
			break;
		
		CLI_API_Printf(l_mdl_id, "\r\n%s", ptcode_ipc+i);
		i++;
	}
	CLI_API_Printf(l_mdl_id, "\r\n");

	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

/******************************************************************************\
  Function   : __filetrans_upgrade
  Description: 设置且升级
  Return     : bool true: 成功  false:非零失败
  Others     : 
\******************************************************************************/
static cli_cmd_ret_e __ptcode_show
    (
    IN const UI32_T	sid,
    IN cli_value_t		*ptrCliValue,
    IN void			*ptrUserData
    )
{
	cli_value_t *para_tmp = ptrCliValue;
	UI32_T op_id = *(UI32_T *)para_tmp->value;
	para_tmp = para_tmp->next;

	if(op_id == 1)
	{
		__ptcode_show_ipc();
	}
	else if(op_id == 2)
	{
		
	}
	else if(op_id == 3)
	{
		
	}
	else if(op_id == 4)
	{
		
	}
	else
	{
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

#endif

void bc_cli_cmd_ptcode_reg(void)
{
	CLI_DBG_ENTER(l_mdl_id);
	BOOL_T ret_reg;

/*
	download or upload
*/
#if 1	
	ret_reg = bc_cli_reg_cmd(
		CLI_MOD_PRIVI_PATH
		"/show "		 	"##""##"
		"ptcode"			"#show a few code#""#显示一些代码#"
		"mdl-id"			"#Module id #""#模块号#"
		"{ "
			"ipc(1) "	"#Download files #""#下载文件#"
			"| "
			"usermgmt(2) "		"#Upload files.#""#上传文件#"
			"|"
			"filetrans(3) "		"#Upload files.#""#上传文件#"
			"|"
			"binchie(4) "		"#Upload files.#""#上传文件#"
			"|"
			"cli(5) "		"#Upload files.#""#上传文件#"
		"} ",
		__ptcode_show,
		CLI_ACC_LVL_BASIC,
		"show ptcode.",
		"显示代码。",
		NULL);
	CLI_DBG_CPL(l_mdl_id, "ret=%d\r\n", ret_reg);

#endif

}



/* 
 *	预留一个注释在文件最后
 */
/******************************************************************************\
  Function   : 
  Description: 
  Return     : 
  Others     : 
\******************************************************************************/
