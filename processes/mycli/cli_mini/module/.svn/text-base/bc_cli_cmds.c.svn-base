
//#include "bc_cli_cmds.h"
#include "bc_modules.h"

#include "bc_cli_type.h"

//#include "ipc/bc_cli_cmd_ipc_debug.h"
//#include "bc_cli_cmd_print_dbg.h"
#include "bc_cli_cmd_filetrans.h"


static unsigned int 	l_mdl_id = BC_MODULE_CLI_CMDS;

//extern void bc_cli_cmd_ping_reg(void);

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
 *   2014-05-25 by wangbin -- Create
 *
*******************************************************************************/
I32_T bc_cli_app_cmd_reg(void)
{
    CLI_DBG_ENTER(l_mdl_id);

    /* =============================== *\
        register demo module commands 
    \* =============================== */
    //bc_cli_dm_cmd_reg();

    /* ======================================== *\
        以下为需要调用的各模块命令语法注册接口
    \* ======================================== */
	
	bc_cli_cmd_filetrans_reg();
	
	
    /* ======================================== *\
        以上为需要调用的各模块命令语法注册接口
    \* ======================================== */

    CLI_DBG_LEAVE(l_mdl_id);
    return 0;
}



