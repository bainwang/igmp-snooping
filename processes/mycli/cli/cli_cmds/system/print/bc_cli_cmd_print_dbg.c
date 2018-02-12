/************************************************************
  -------------------------------------------------------------------------
  FileName: bc_cli_cmd_print_dbg.c
  Author:  bain.wang@outlook.com      Version :  1.0        Date:2016-4-25
  Description:                   
  Version:                        
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              ͷ   ��   ��                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
#include "bc_cli.h"
#include "bc_modules.h"
#include "bc_cli_type.h"
#include "bc_cli_paratype.h"
#include "bc_cli_cmd_print_dbg.h"

#include "bc_print.h"
#include "bc_print_client.h"




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
#define BC_CLI_CMD_PT_BUF_SIZE   1024



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
static bc_modules_e l_mdl_id = BC_MODULE_PRINT;



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              ��  ��  ��  ��                                //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
static I32_T __print_conver_arg_range(I8_T *cmd_arg, I32_T value [2]);
static I32_T __print_lvl_show(UI32_T *prt_level);
static I32_T __print_prj_show(bc_pt_prj_flg_t *prj);

static I32_T __print_enable_all(I32_T e_flg);
static I32_T __print_level(I32_T e_flg, I32_T prt_lvl);

static I32_T __print_module_all(I32_T e_flg);
static I32_T __print_module(I32_T e_flg, I32_T module_id);
static I32_T __print_module_file(I32_T e_flg, cli_value_t *cmd_para, I32_T module_id);

static I32_T __print_help(IN const UI32_T sid, IN cli_value_t *ptrCliValue, IN void *ptrUserData);
static I32_T __show_print(IN const UI32_T sid, IN cli_value_t *ptrCliValue, IN void *ptrUserData);
static I32_T __print_switch_all(IN const UI32_T sid, IN cli_value_t *ptrCliValue, IN void *ptrUserData);

static I32_T __print_cfg_save(IN const UI32_T sid, IN cli_value_t *ptrCliValue, IN void *ptrUserData);
static I32_T __print_cfg_clear(IN const UI32_T sid, IN cli_value_t *ptrCliValue, IN void *ptrUserData);

//static I32_T __print_mem_dump(IN const UI32_T sid, IN cli_value_t *ptrCliValue, IN void *ptrUserData);



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              ��  ��  ��  ��                                //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#if 1
/*************************************************
  Function: __print_enable_all
  Description: ���м�����������̵�ʹ��
  Input: 
  		e_flg		ʹ�ܱ��
  Output:
  		NULL
  Return:
  		0: success
  		~0: fail
  Note: 
  History: 
*************************************************/
static I32_T __print_enable_all(I32_T e_flg)
{
	bc_err_e    ret = BC_ERR_OK;

	switch (e_flg)
	{
	case 01:
		bc_pt_prt_lvl_open(BC_LVL_BIT_ALL);
		ret = bc_pt_prt_lvl_open_client(BC_LVL_BIT_ALL);
		if (BC_ERR_OK != ret)
		{
			BC_PT_ERROR(l_mdl_id, "Failed to ipc open print level all!\n");
			return CLI_CMD_FAIL_PRT_NEWLINE;
		}

		ret = BC_ERR_OK;
		bc_pt_prt_open_all();
		ret = bc_pt_prt_open_all_client();
		if (BC_ERR_OK != ret)
		{
			BC_PT_ERROR(l_mdl_id, "Failed to ipc open print project!\n");
			return CLI_CMD_FAIL_PRT_NEWLINE;
		}
		break;
		
	case 02:
		bc_pt_prt_close_all();
		ret = bc_pt_prt_close_all_client();
		if (BC_ERR_OK != ret)
		{
			BC_PT_ERROR(l_mdl_id, "Failed to ipc close print!\n");
			return CLI_CMD_FAIL_PRT_NEWLINE;
		}
		break;
	default:
		return CLI_CMD_FAIL_PRT_NEWLINE;
		break;
	}

	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}



/*************************************************
  Function: __print_level
  Description: ��ӡ���𿪹ؿ��ƽӿ�
  Input: 
  		e_flg			ʹ�ܱ��
  		prt_lvl			��ӡ����
  Output:
  		NULL
  Return:
  		0: success
  		~0: fail
  Note: 
  History: 
*************************************************/
static I32_T __print_level(I32_T e_flg, I32_T prt_lvl)
{
	bc_err_e    ret = BC_ERR_OK;

	switch(e_flg)
	{
	case 1:
		bc_pt_prt_lvl_open(prt_lvl);
		if (BC_ERR_OK != (ret = bc_pt_prt_lvl_open_client(prt_lvl)))
		{
			BC_PT_ERROR(l_mdl_id, "Failed to olt open print level!\n");
			return CLI_CMD_FAIL_PRT_NEWLINE;
		}
		break;
	case 2:
		bc_pt_prt_lvl_close(prt_lvl);
        if (BC_ERR_OK != (ret = bc_pt_prt_lvl_close_client(prt_lvl)))
        {
        	BC_PT_ERROR(l_mdl_id, "Failed to olt close print level!\n");
			return CLI_CMD_FAIL_PRT_NEWLINE;
        }
		break;
	default:
		return CLI_CMD_FAIL_PRT_NEWLINE;
		break;
	}

	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}



/*************************************************
  Function: __print_module_all
  Description: ������������ģ�鿪�ؿ���
  Input: 
  		e_flg			ʹ�ܱ��
  Output:
  		NULL
  Return:
  		0: success
  		~0: fail
  Note: 
  History: 
*************************************************/
static I32_T __print_module_all(I32_T e_flg)
{
	bc_err_e    ret = BC_ERR_OK;

	switch (e_flg)
	{
	case 1:
		BC_PT_COMMAND(l_mdl_id, "case 1: 1 enter\n");
		bc_pt_open_prj_all();
		BC_PT_COMMAND(l_mdl_id, "case 1: 2 enter\n");
		if (BC_ERR_OK != (ret = bc_pt_open_prj_all_client()))
		{
			BC_PT_ERROR(l_mdl_id, "Failed to olt open print project!\n");
			return CLI_CMD_FAIL_PRT_NEWLINE;
		}
		break;
		
	case 2:
		BC_PT_COMMAND(l_mdl_id, "case 2: 1 enter\n");
		bc_pt_close_prj_all();
		BC_PT_COMMAND(l_mdl_id, "case 2: 2 enter\n");
		if (BC_ERR_OK != (ret = bc_pt_close_prj_all_client()))
		{
			BC_PT_ERROR(l_mdl_id, "Failed to olt close print project!\n");
			return CLI_CMD_FAIL_PRT_NEWLINE;
		}
		break;
	default:
		return CLI_CMD_FAIL_PRT_NEWLINE;
		break;
	}

	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}



/*************************************************
  Function: __print_module
  Description: ĳ��ģ�鿪�ؿ���
  Input: 
  		e_flg				ʹ�ܱ��
  		module_id			ģ��id
  Output:
  		NULL
  Return:
  		0: success
  		~0: fail
  Note: 
  History: 
*************************************************/
static I32_T __print_module(I32_T e_flg, I32_T module_id)
{
	bc_err_e    ret = BC_ERR_OK;
	
	switch(e_flg)
	{
	case 1:
		if ((ret = bc_pt_open_prj_mdl(module_id)) != BC_ERR_OK)
		{
			BC_PT_ERROR(l_mdl_id, "Failed to cli open project module! ret = %d\n", ret);
			return CLI_CMD_FAIL_PRT_NEWLINE;
		}
		if ((ret = bc_pt_open_prj_mdl_client(module_id)) != BC_ERR_OK)
		{
			BC_PT_ERROR(l_mdl_id, "Failed to olt open project module! ret = %d\n", ret);
			return CLI_CMD_FAIL_PRT_NEWLINE;
		}
		break;
	case 2:
		if ((ret = bc_pt_close_prj_mdl(module_id)) != BC_ERR_OK)
		{
			BC_PT_ERROR(l_mdl_id, "Failed to cli close project module! ret = %d\n", ret);
			return CLI_CMD_FAIL_PRT_NEWLINE;
		}
		if ((ret = bc_pt_close_prj_mdl_client(module_id)) != BC_ERR_OK)
		{
			BC_PT_ERROR(l_mdl_id, "Failed to olt close project module! ret = %d\n", ret);
			return CLI_CMD_FAIL_PRT_NEWLINE;
		}
		break;
	default:
		return CLI_CMD_FAIL_PRT_NEWLINE;
		break;
	}

	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}



/*************************************************
  Function: __print_module_file
  Description: ģ���ĳ���ļ����ؿ���
  Input: 
  		e_flg				ʹ�ܱ��
  		cmd_para			�������
  		module_id			ģ��id
  Output:
  		NULL
  Return:
  		0: success
  		~0: fail
  Note: 
  History: 
*************************************************/
static I32_T __print_module_file(I32_T e_flg, cli_value_t *cmd_para, I32_T module_id)
{
	cli_value_t        *tmp_para    						= NULL;
	I32_T               line_rang[2]                        = {0};
	bc_pt_file_flg_t    file;

	tmp_para = cmd_para->next;    /* <file name> */
	if (NULL == tmp_para->next)   /* line */
	{
		switch(e_flg)
		{
		case 1:
			strncpy(file.file_name, (I8_T *)tmp_para->value, BC_PT_FILE_NAME_LEN_MAX-1);
			file.file_name[BC_PT_FILE_NAME_LEN_MAX] = '\0';
			file.line_start = 0;
			file.line_end = ~0;

			bc_pt_open_prj_mdl_file(module_id, &file);
			if (BC_ERR_OK != bc_pt_open_prj_mdl_file_client(module_id, &file))
			{
				BC_PT_ERROR(l_mdl_id, "Failed to olt open project module file!\n");
				return CLI_CMD_FAIL_PRT_NEWLINE;
			}
			break;
		case 2:
			bc_pt_close_prj_mdl_file(module_id, (I8_T *)tmp_para->value);
			if (BC_ERR_OK != bc_pt_close_prj_mdl_file_client(module_id, (I8_T *)tmp_para->value))
			{
				BC_PT_ERROR(l_mdl_id, "Failed to olt close project module file!\n");
				return CLI_CMD_FAIL_PRT_NEWLINE;
			}
			break;
		default:
			return CLI_CMD_FAIL_PRT_NEWLINE;
			break;
		}
	}
	else
	{
		switch (e_flg)
		{
		case 1:
			tmp_para = tmp_para->next;    /* line */
			strncpy(file.file_name, (I8_T *)tmp_para->value, BC_PT_FILE_NAME_LEN_MAX-1);

			__print_conver_arg_range((I8_T *)tmp_para->next->value, line_rang);
			file.line_start = line_rang[0];
			file.line_end = line_rang[1];

			bc_pt_open_prj_mdl_file(module_id, &file);
			if (BC_ERR_OK != bc_pt_open_prj_mdl_file_client(module_id, &file))
			{
				BC_PT_ERROR(l_mdl_id, "Failed to olt open project module file line!\n");
				return CLI_CMD_FAIL_PRT_NEWLINE;
			}
			break;
			
		default:
			return CLI_CMD_FAIL_PRT_NEWLINE;
			break;
		}
	}
	
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}



/*************************************************
  Function: __print_switch_all
  Description: ���д�ӡ���ƵĻص�����
  Input: 
  		sid					session id
  		ptrCliValue		�����в���
  		ptrUserData		�Զ����û�����
  Output:
  		NULL
  Return:
  		0: success
  		~0: fail
  Note: 
  History: 
*************************************************/
static I32_T __print_switch_all
    (
    IN const UI32_T 	sid,
    IN cli_value_t 		*ptrCliValue,
    IN void 			*ptrUserData
    )
{
	I32_T             op_code                              = 0;
	I32_T             en_flag                              = 0;
	I32_T             module_id                            = 0;
	cli_value_t       *tmp_cli_arg                         = ptrCliValue;

	CLI_DBG_ENTER(l_mdl_id);

	if (NULL == ptrCliValue)
	{
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	/* enable flag */
	op_code = *(I32_T *)ptrCliValue->value;
	BC_PT_DBG_CPL(l_mdl_id, "op_code = %d, (I8_T *)ptrCliValue->value: %s\n", op_code, (I8_T *)ptrCliValue->value);
	switch(op_code)
	{
	case 1:
		en_flag = 1;
		break;
	case 2:
		en_flag = 2;
		break;
	default:
		return CLI_CMD_FAIL_PRT_NEWLINE;
		break;
	}
	
	tmp_cli_arg = tmp_cli_arg->next;
	if (NULL == tmp_cli_arg)
	{
		__print_enable_all(en_flag);
	    
	}
	else
	{
		op_code = *(I32_T *)tmp_cli_arg->value;
		BC_PT_DBG_CPL(l_mdl_id, "1 switch op_code = %d\n", op_code);
		tmp_cli_arg = tmp_cli_arg->next;							/* id */
		switch (op_code)
		{
		/* level */
		case 31:
			op_code = *(I32_T *)tmp_cli_arg->value;
			switch(op_code)
			{
			case 311:
				__print_level(en_flag, BC_LVL_BIT_ALL);
				break;
			case 312:
				__print_level(en_flag, BC_LVL_BIT_DBG_FUNC);
				break;
			case 313:
				__print_level(en_flag, BC_LVL_BIT_DBG_CPLX);
				break;
			case 314:
				__print_level(en_flag, BC_LVL_BIT_DBG_SMPL);
				break;
			case 315:
				__print_level(en_flag, BC_LVL_BIT_EVENT);				
				break;
			case 316:
				__print_level(en_flag, BC_LVL_BIT_ERROR);
				break;
			case 317:
				__print_level(en_flag, BC_LVL_BIT_WARNING);
				break;
			default:
				return CLI_CMD_FAIL_PRT_NEWLINE;
				break;
			}
		break;
	
		/* module */
		case 32:	
			op_code = *(I32_T *)tmp_cli_arg->value;
			BC_PT_DBG_CPL(l_mdl_id, "2 switch op_code = %d\n", op_code);
			switch(op_code)
			{
			case 321:
				__print_module_all(en_flag);
				break;
				
			case 322:
				tmp_cli_arg = tmp_cli_arg->next;			/* <module-id> */
				module_id = *(I32_T *)tmp_cli_arg->value;
				BC_PT_DBG_CPL(l_mdl_id, "module_id: 0x%x\n", module_id);
				tmp_cli_arg = tmp_cli_arg->next;			/* file */
				if (NULL == tmp_cli_arg)
				{
					__print_module(en_flag, module_id);	
				}
				else
				{
					__print_module_file(en_flag, tmp_cli_arg, module_id);
				}
				break;
				
			default:
				return CLI_CMD_FAIL_PRT_NEWLINE;
				break;
			}
		break;
			
		default:
			return CLI_CMD_FAIL_PRT_NEWLINE;
			break;
		}
	}

	CLI_DBG_LEAVE(l_mdl_id);
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

#endif



#if 1
/*************************************************
  Function: __print_help
  Description: ���Դ�ӡ����ģ��ID������Ϣ
  Input: 
  		sid					session id
  		ptrCliValue		�����в���
  		ptrUserData		�Զ����û�����
  Output:
  		NULL
  Return:
  		0: success
  		~0: fail
  Note: 
  History: 
*************************************************/
static I32_T __print_help
	(
	IN const UI32_T 	sid,
    IN cli_value_t 		*ptrCliValue,
    IN void 			*ptrUserData	
	)
{
	I8_T               *p_mdl_name = NULL;
	I32_T			   count_flag  = 0;
	bc_modules_e       index_mdl   = BC_FIRST_MODULE;

	CLI_DBG_ENTER(l_mdl_id);
	
	CLI_API_Printf(sid, "-----------------------------------\r\n");
	CLI_API_Printf(sid, "%10s \t %s\r\n", "module id", "module name");
	CLI_API_Printf(sid, "---------- \t --------------\r\n");

	for (index_mdl = BC_MODULE_SYSTEM; index_mdl < BC_LAST_MODULE; index_mdl = index_mdl)
	{
		p_mdl_name = bc_modules_get_module_name(index_mdl);
		if (NULL == p_mdl_name)
		{
			index_mdl = (index_mdl - count_flag) + BC_MODULE_INTERVAL;
			count_flag = 0;
		}
		else
		{
			CLI_API_Printf(sid, " 0x%-10x \t %s\r\n", index_mdl, bc_modules_get_module_name(index_mdl));
			index_mdl += 1;
			count_flag++;
		}
	}
	
	CLI_API_Printf(sid, "-----------------------------------\n");
	CLI_DBG_LEAVE(l_mdl_id);

	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}



/*************************************************
  Function: __show_print
  Description: ��ʾ��ӡ���Կ��ؿ��Ƶ�������Ϣ
  Input: 
  		sid					session id
  		ptrCliValue		�����в���
  		ptrUserData		�Զ����û�����
  Output:
  		NULL
  Return:
  		0: success
  		~0: fail
  Note: 
  History: 
*************************************************/
static I32_T __show_print
	(
	IN const UI32_T 	sid,
    IN cli_value_t 		*ptrCliValue,
    IN void 			*ptrUserData	
	)
{
	UI32_T            prt_lvl = BC_LVL_BIT_NONE;
	bc_err_e          ret     = BC_ERR_OK;
	bc_pt_prj_flg_t   prj;

	CLI_DBG_ENTER(l_mdl_id);

	/* CLI process */
	CLI_API_Printf(sid, "[%s]\r\n", "CLI print info");
	bc_pt_get_prt_lvl(&prt_lvl);
	BC_PT_DBG_CPL(l_mdl_id, "CLI prt_lvl: 0x%x, %d\n", prt_lvl, prt_lvl);
	__print_lvl_show(&prt_lvl);

	/* show lvl and project */
	memset(&prj, 0x00, sizeof(bc_pt_prj_flg_t));
	bc_pt_get_prj_all(&prj);
	__print_prj_show(&prj);
	CLI_API_Printf(sid, "\r\n");
	
	/* Olt process */
	prt_lvl = BC_LVL_BIT_NONE;
	BC_PT_DBG_CPL(l_mdl_id, "BC prt_lvl: 0x%x, %d\n", prt_lvl, prt_lvl);

	CLI_API_Printf(sid, "[%s]\r\n", "Bc print info");
	ret = bc_pt_get_prt_lvl_client(&prt_lvl);
	if (BC_ERR_OK != ret)
	{
		BC_PT_ERROR(l_mdl_id, "Failed to ipc get print lvl!\n");
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}

	/* show lvl and project */
	BC_PT_DBG_CPL(l_mdl_id, "BC prt_lvl: 0x%x, %d\n", prt_lvl, prt_lvl);
	__print_lvl_show(&prt_lvl);

	ret = BC_ERR_OK;
	memset(&prj, 0x00, sizeof(bc_pt_prj_flg_t));
	ret = bc_pt_get_prj_all_client(&prj);
	if (BC_ERR_OK != ret)
	{
		BC_PT_ERROR(l_mdl_id, "Failed to ipc get print project!\n");
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	__print_prj_show(&prj);

	CLI_DBG_LEAVE(l_mdl_id);
	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

#endif


#if 1
/*************************************************
  Function: __print_conver_arg_range
  Description: ת��������Χ������ֵ�洢������������
  Input: 
  		cmd_arg				���������Χ
  		value[2]     		��������
  Output:
  		NULL
  Return:
  		0: success
  		~0: fail
  Note: 
  History: 
*************************************************/
static I32_T __print_conver_arg_range
	(
	I8_T *cmd_arg, 
	I32_T value[2]
	)
{
	I32_T			arr_fir = 0;
	I32_T			arr_sec = 0;

	if ((NULL == cmd_arg) || (NULL == value))
	{
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}

	sscanf(cmd_arg, "%d-%d", &arr_fir, &arr_sec);
	if (arr_fir > arr_sec)
	{
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}
	value[0] = arr_fir;
	value[1] = arr_sec;

	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}



/*************************************************
  Function: __print_lvl_show
  Description: ��ʾ��ӡ����
  Input: 
  		prt_level		��ӡ����
  Output:
  		NULL
  Return:
  		0: success
  		~0: fail
  Note: 
  History: 
*************************************************/
static I32_T __print_lvl_show
	(
	UI32_T   *prt_level
	)
{
	UI32_T       loop_lvl = 0;

	BC_PT_COMMAND(l_mdl_id, "\n%s\n", "Print level:");
	if (BC_LVL_BIT_ALL == *prt_level)
	{
		BC_PT_COMMAND(l_mdl_id, "%s\n", "all");
	}
	else if (BC_LVL_BIT_NONE == *prt_level)
	{
		BC_PT_COMMAND(l_mdl_id, "%s\n", "off");
	}
	else
	{
		for (loop_lvl = 0; loop_lvl < BC_LVL_MAX; loop_lvl++)
		{
			if ((*prt_level >> loop_lvl) & 0x01)
			{
				switch (loop_lvl)
				{
				case BC_LVL_DBGFUN:
					BC_PT_COMMAND(l_mdl_id, "%s ", "dbgfunc");
					break;
				case BC_LVL_DBGSMP:
					BC_PT_COMMAND(l_mdl_id, "%s ", "dbgsmpl");
					break;
				case BC_LVL_DBGCPL:
					BC_PT_COMMAND(l_mdl_id, "%s ", "dbgcplx");
					break;
				case BC_LVL_INIT:
					BC_PT_COMMAND(l_mdl_id, "%s ", "init");
					break;
				case BC_LVL_EVT:
					BC_PT_COMMAND(l_mdl_id, "%s ", "event");
					break;
				case BC_LVL_WARN:
					BC_PT_COMMAND(l_mdl_id, "%s ", "warning");
					break;
				case BC_LVL_ERR:
					BC_PT_COMMAND(l_mdl_id, "%s ", "error");
					break;
				case BC_LVL_CMD:
					BC_PT_COMMAND(l_mdl_id, "%s ", "command");
					break;
				default:
					return CLI_CMD_FAIL_PRT_NEWLINE;
				}
			}
		}
	}

	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}



/*************************************************
  Function: __print_prj_show
  Description: ��ʾ���̸���ģ����ؿ�����Ϣ
  Input: 
  		prj				������ӡ����
  Output:
  		NULL
  Return:
  		0: success
  		~0: fail
  Note: 
  History: 
*************************************************/
static I32_T __print_prj_show
	(
	bc_pt_prj_flg_t *prj
	)
{
	UI32_T                  loop_mdl  = 0;
	UI32_T                  loop_file = 0;
	UI8_T                   loop_cnt = 0;
	I8_T                    style1[]  = " |   |- ";
	I8_T                    style2[]  = "     |- ";
	I8_T                    *p_style  = NULL;
	bc_pt_prj_flg_t         *tmp_prj  = NULL; 

	BC_PT_COMMAND(l_mdl_id, "\n%s\n", "Print module:");
	tmp_prj = prj;
	p_style = style1;
	if (0 == tmp_prj->flag)
	{
		BC_PT_COMMAND(l_mdl_id, "%s\n", "modules off");
		return CLI_CMD_SUCCESS_PRT_NEWLINE;
	}
	else if (0xff == tmp_prj->flag)
	{
		BC_PT_COMMAND(l_mdl_id, "%s\n", "modules on");
		return CLI_CMD_SUCCESS_PRT_NEWLINE;
	}
	else
	{
		BC_PT_COMMAND(l_mdl_id, "\nModule tree\n");
		for (loop_mdl = 0; loop_mdl < BC_PT_PRJ_MDL_NUM_MAX; loop_mdl++)
		{
			if (0 == tmp_prj->mdls[loop_mdl].id || NULL == bc_modules_get_module_name(tmp_prj->mdls[loop_mdl].id))
			{
				continue;
			}

			loop_cnt++;
			BC_PT_COMMAND(l_mdl_id, " |\r\n");
			BC_PT_COMMAND(l_mdl_id, " |- (%02u) module 0x%x [ %s ]\r\n", 
								loop_cnt, 
								tmp_prj->mdls[loop_mdl].id,
								bc_modules_get_module_name(tmp_prj->mdls[loop_mdl].id));
			if ((BC_PT_PRJ_MDL_NUM_MAX-1 == loop_mdl) || (BC_FIRST_MODULE == tmp_prj->mdls[loop_mdl].id))
			{
				p_style = style2;
			}
			/* check file */
			if (tmp_prj->mdls[loop_mdl].flag == 0)
			{
				BC_PT_COMMAND(l_mdl_id, "%s %s\r\n", p_style, "print off!");				
				continue; 
			}
			else if (tmp_prj->mdls[loop_mdl].flag == 0xFF)
			{
				BC_PT_COMMAND(l_mdl_id, "%s %s\r\n", p_style, "print all files!");				
				continue; 
			}
			else
			{
				for (loop_file = 0; loop_file < BC_PT_MDL_FILE_NUM_MAX; loop_file++)
				{
					if (tmp_prj->mdls[loop_mdl].files[loop_file].file_name[0] == 0)
					{
						continue;
					}

					if (tmp_prj->mdls[loop_mdl].files[loop_file].line_end == 0xFFFFFFFF)
					{
						BC_PT_COMMAND(l_mdl_id, "%s (%02u) %s\r\n", 
										p_style,
										loop_file, 
										tmp_prj->mdls[loop_mdl].files[loop_file].file_name);
					}
					else
					{
						BC_PT_COMMAND(l_mdl_id, "%s (%02u) %s [ %u ~ %u ]\r\n", 
										p_style,
										loop_file, 
										tmp_prj->mdls[loop_mdl].files[loop_file].file_name, 
										tmp_prj->mdls[loop_mdl].files[loop_file].line_start, 
										tmp_prj->mdls[loop_mdl].files[loop_file].line_end);
					}					
				}
			}
		}
	}

	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

#if 0
/*************************************************
  Function: __print_dump_info_show
  Description: 
  Input: 
  		
  Output:
  		NULL
  Return:
  		0: success
  		~0: fail
  Note: 
  History: 
*************************************************/
static bc_err_e __print_dump_info_show(bc_uint32 pt_lvl, bc_pt_prj_flg_t pt_prj)
{
	bc_uint8        loop_cnt = 0;
	bc_uint8        actual_num = 0;
	bc_uint8        loop_file = 0;
	
	__print_lvl_show(&pt_lvl);
	BC_PT_COMMAND(l_mdl_id, "\nModule info:\r\n");
	switch (pt_prj.flag)
	{
	case 0x00:
		BC_PT_COMMAND(l_mdl_id, "%s\n", "all modules off");
		return CLI_CMD_SUCCESS_PRT_NEWLINE;
	case 0xFF:
		BC_PT_COMMAND(l_mdl_id, "%s\n", "all modules on");
		return CLI_CMD_SUCCESS_PRT_NEWLINE;
	default:
		break;
	}

	BC_PT_COMMAND(l_mdl_id, "%3s %-10s %-15s %-30s %-10s %-8s\n", "num", "module id", "module name", "file name", "line start", "line end");
	BC_PT_COMMAND(l_mdl_id, "%3s %-10s %-15s %-30s %-10s %-8s\n", "---", "----------", "---------------", "------------------------------", 
																  "----------", "--------");
	for (loop_cnt = 0; loop_cnt < BC_PT_PRJ_MDL_NUM_MAX; loop_cnt++)
	{
		if (0x00 == pt_prj.mdls[loop_cnt].id || NULL == bc_modules_get_module_name(pt_prj.mdls[loop_cnt].id))
		{
			continue;
		}

		actual_num++;
		BC_PT_COMMAND(l_mdl_id, "%03u 0x%x %30s ", actual_num, pt_prj.mdls[loop_cnt].id, 
			                        bc_modules_get_module_name(pt_prj.mdls[loop_cnt].id));
		switch (pt_prj.mdls[loop_cnt].flag)
		{
		case 0x00:
			BC_PT_COMMAND(l_mdl_id, "%30s\r\n", "all files off!");				
			continue; 
		case 0xFF:
			BC_PT_COMMAND(l_mdl_id, "%30s\r\n", "all files on!");				
			continue; 
		default:
			break;
		}

		for (loop_file = 0; loop_file < BC_PT_MDL_FILE_NUM_MAX; loop_file++)
		{
			if (NULL == pt_prj.mdls[loop_cnt].files[loop_file].file_name)
			{
				continue;
			}
			
			BC_PT_COMMAND(l_mdl_id, "%30s %10u %8u\r\n", 
        							pt_prj.mdls[loop_cnt].files[loop_file].file_name, 
        							pt_prj.mdls[loop_cnt].files[loop_file].line_start, 
        							pt_prj.mdls[loop_cnt].files[loop_file].line_end);
			BC_PT_COMMAND(l_mdl_id, "%31s", "                               ");
		}
	}

	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}
#endif
#endif

#if 1
/*************************************************
  Function: __print_cfg_save
  Description: �����ӡ������������
  Input: 
  		sid					session id
  		ptrCliValue		�����в���
  		ptrUserData		�Զ����û�����
  Output:
  		NULL
  Return:
  		0: success
  		~0: fail
  Note: 
  History: 
*************************************************/
static I32_T __print_cfg_save
	(
	IN const UI32_T   sid, 
	IN cli_value_t    *ptrCliValue, 
	IN void           *ptrUserData
	)
{
	bc_err_e          ret = BC_ERR_OK;
	
	ret = bc_pt_dbg_save_cfg_client();
	if (BC_ERR_OK != ret)
	{
		BC_PT_DBG_CPL(l_mdl_id, "Failed to print debug save cfg! IPC error!\n");
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}

	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}



/*************************************************
  Function: __print_cfg_clear
  Description: 
  Input: 
  		sid					session id
  		ptrCliValue		�����в���
  		ptrUserData		�Զ����û�����
  Output:
  		NULL
  Return:
  		0: success
  		~0: fail
  Note: 
  History: 
*************************************************/
static I32_T __print_cfg_clear
	(
	IN const UI32_T   sid, 
	IN cli_value_t    *ptrCliValue, 
	IN void           *ptrUserData
	)
{
	bc_err_e          ret = BC_ERR_OK;

	/* CLI process */
	bc_pt_cfg_clr();

	/* OLT process */
	ret = bc_pt_dbg_save_clear_client();
	if (BC_ERR_OK != ret)
	{
		BC_PT_DBG_CPL(l_mdl_id, "Failed to print debug clear cfg! IPC error!\n");
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}

	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}

#endif


#if 0
/*************************************************
  Function: __print_mem_dump
  Description: 
  Input: 
  		sid					session id
  		ptrCliValue		�����в���
  		ptrUserData		�Զ����û�����
  Output:
  		NULL
  Return:
  		0: success
  		~0: fail
  Note: 
  History: 
*************************************************/
static I32_T __print_mem_dump
	(
	IN const UI32_T   sid, 
	IN cli_value_t    *ptrCliValue, 
	IN void           *ptrUserData
	)
{
	bc_err_e          ret = BC_ERR_OK;
	bc_uint32         pt_lvl = 0;
	bc_pt_prj_flg_t   pt_prj;

	memset(&pt_prj, 0x00, sizeof(bc_pt_prj_flg_t));

	//CLI process
	CLI_API_Printf(sid, "%s\r\n", "[CLI process]");
	ret = bc_pt_db_dump(&pt_lvl, &pt_prj);
	__print_dump_info_show(pt_lvl, pt_prj);
	
	//OLT process
	pt_lvl = 0;
	memset(&pt_prj, 0x00, sizeof(bc_pt_prj_flg_t));
	ret = bc_pt_dump_client(&pt_lvl, &pt_prj);
	if (ret != BC_ERR_OK)
	{
		BC_PT_ERROR(l_mdl_id, "Failed to print dump client error! ret = %d\r\n", ret);
		return CLI_CMD_FAIL_PRT_NEWLINE;
	}

	CLI_API_Printf(sid, "%s\r\n", "[OLT process]");
	__print_dump_info_show(pt_lvl, pt_prj);

	return CLI_CMD_SUCCESS_PRT_NEWLINE;
}
#endif

/*************************************************
  Function: bc_cli_cmd_print_dbg_reg
  Description: ��ӡ���Ե�����ע��ӿ�
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
void bc_cli_cmd_print_dbg_reg(void)
{
	BOOL_T ret_reg;

	CLI_DBG_ENTER(l_mdl_id);

	ret_reg = bc_cli_reg_cmd(
		CLI_MOD_DEBUG_PATH
		"/print "	            				"#Print debug#" "#��ӡ������Ϣ#"
		"{ "		 	
		"enable(1) "  							"#Debug enable#" "#�򿪵���#"
		" | "
		"disable(2) "                  			"#Debug disable#" "#�رյ���#" 
		"} "
		"[ "
			"{ "
			"level(31) "						"#Print debug level#" "#��ӡ���Լ���#"
				"{ "
				"all(311) "						"#Print all debug level#" "#��ӡ�������м�����Ϣ#"
				" | "
				"dbgf(312) "					"#Print debug function level#" "#��ӡ����������Ϣ#"
				" | "
				"dbgc(313) "					"#Print debug complex level#" "#��ӡ��ϸ������Ϣ#"
				" | "
				"dbgs(314) "					"#Print debug simple level#" "#��ӡ�򵥵�����Ϣ#"
				" | "
				"event(315) "					"#Print debug system event#" "#��ӡϵͳ�¼�#"
				" | "
				"error(316) "					"#Print debug system error#" "#��ӡϵͳ����#"
				" | "
				"warning(317) "					"#Print debug system warning#" "#��ӡϵͳ����#"
				"} "
			" | "
			"module(32) "						"#Print debug module#" "#��ӡ����ģ��#"
				"{ "
				"all(321) "						"#Print all debug module#" "#��ӡ��������ģ����Ϣ#"				
				" | "
				"id(322) "						"#Module id#" "#ģ��id��#"		
				"<module-id> "
					"[ "
					"file "						"#Print debug file#" "#��ӡ�����ļ�#"
					"<file-name> "				"#FILE NAME#""#�ļ���#"
						"["
							"line "				"#Line#" "#����#"
							"<value-list> "     "#eg:1-100#""#eg:1-100#"
						"] "
					"] "
				"} "
			"} "
		"] "
		,
		__print_switch_all,
		CLI_ACC_LVL_DEBUG,
		"Function print debug switch.",
		"������ӡ���Կ��ء�",
		NULL
		);

	ret_reg = bc_cli_reg_cmd(
		CLI_MOD_DEBUG_PATH
		"/print "				"#Print debug#" "#��ӡ������Ϣ#"
		"help "					"#Print debug help info#" "#��ӡ���԰�����Ϣ#"
		,
		__print_help,
		CLI_ACC_LVL_DEBUG,
		"Print debug help info.",
		"��ӡ���԰�����Ϣ��",
		NULL
		);

	ret_reg = bc_cli_reg_cmd(
		CLI_MOD_DEBUG_PATH
		"/print "				"#Print debug#" "#��ӡ������Ϣ#"
		"show "					
		,
		__show_print,
		CLI_ACC_LVL_DEBUG,
		"Show. ",
		"��ʾ��",
		NULL
		);
	
	ret_reg = bc_cli_reg_cmd(
		CLI_MOD_DEBUG_PATH
		"/save "
		,
		__print_cfg_save,
		CLI_ACC_LVL_DEBUG,
		"Save print debug configure.",
		"�����ӡ����������Ϣ��",
		NULL
		);

	ret_reg = bc_cli_reg_cmd(
		CLI_MOD_DEBUG_PATH
		"/clear "
		"configure "
		,
		__print_cfg_clear,
		CLI_ACC_LVL_DEBUG,
		"Clear print debug configure.",
		"�����ӡ�������á�",
		NULL
		);
#if 0
	ret_reg = bc_cli_reg_cmd(
		CLI_MOD_DEBUG_PATH
		"/print "
		"dump "
		,
		__print_mem_dump,
		CLI_ACC_LVL_DEBUG,
		"print dump.",
		"��ӡ�ڴ�dump���ݡ�"
		,
		NULL
		);
#endif
	CLI_DBG_CPL(l_mdl_id, "ret=%d\r\n", ret_reg);

	CLI_DBG_LEAVE(l_mdl_id);
}


