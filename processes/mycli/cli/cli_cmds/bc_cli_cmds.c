
//#include "bc_cli_cmds.h"
#include "bc_modules.h"
#include "bc_proj_defs.h"

#include "bc_cli_type.h"

#include "bc_cli_cmd_monitor.h"
#include "bc_cli_cmd_usermgmt.h"
#include "bc_cli_cmd_baseinfo.h"
#include "bc_cli_cmd_print_dbg.h"
#include "bc_cli_cmd_binchie.h"
#include "bc_cli_cmd_filetrans.h"
#include "bc_cli_cmd_ptcode.h"
#include "bc_cli_cmd_cfg.h"
#include "bc_cli_cmd_clock.h"
#include "bc_cli_cmd_stats.h"


static unsigned int 	l_mdl_id = BC_MODULE_CLI_CMDS;

//extern void bc_cli_cmd_ping_reg(void);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   bc_cli_app_cmd_reg
 *
 * DESCRIPTION:
 *   ��ʼ��CLIӦ�ò�ĸ�ģ�����ע�����﷨����������ִ�С�
 *
 * INPUT:
 *   NA
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   0  -- ��ʼ���ɹ�
 *   -1 -- ��ʼ��ʧ��
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2016-05-25 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
I32_T bc_cli_app_cmd_reg(void)
{
    CLI_DBG_ENTER(l_mdl_id);

    /* =============================== *\
        register demo module commands 
    \* =============================== */
	bc_cli_dm_cmd_reg();

    /* ======================================== *\
        ����Ϊ��Ҫ���õĸ�ģ�������﷨ע��ӿ�
    \* ======================================== */
	bc_cli_cmd_monitor_reg();
	bc_cli_cmd_usermgmt_reg();
	bc_cli_cmd_baseinfo_reg();
	bc_cli_cmd_baseinfo_dbg_reg();
	bc_cli_cmd_print_dbg_reg();
	bc_cli_cmd_cli_reg();
	bc_cli_cmd_ipc_reg();
	bc_cli_cmd_binchie_reg();
	bc_cli_cmd_filetrans_reg();
	bc_cli_cmd_ptcode_reg();
	bc_cli_cmd_cfg_reg();
	bc_cli_cmd_clock_reg();
	bc_cli_cmd_stats_reg();

    /* ======================================== *\
        ����Ϊ��Ҫ���õĸ�ģ�������﷨ע��ӿ�
    \* ======================================== */

    CLI_DBG_LEAVE(l_mdl_id);
    return 0;
}



