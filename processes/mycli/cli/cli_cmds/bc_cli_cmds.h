
#ifndef __BC_CLI_CMDS_H__
#define __BC_CLI_CMDS_H__

#include "bc_cli_type.h"



/*******************************************************************************
 *
 * FUNCTION NAME:
 *   bc_cli_app_cmd_reg
 *
 * DESCRIPTION:
 *   初始化CLI应用层的各模块命令，注册至语法树，供搜索执行。
 *
 * INPUT:
 *   NA
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   0  -- 初始化成功
 *   -1 -- 初始化失败
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2016-05-25 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
I32_T bc_cli_app_cmd_reg(void);



#endif /* __BC_CLI_CMDS_H__ */
