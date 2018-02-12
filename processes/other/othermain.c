#include "bc_ipc_dev_api.h"
#include "bc_vfs.h"
#include "bc_print.h"
#include "bc_log.h"
#include "bc_platform_init.h"
#include "bc_common_defs.h"
#include "bc_ipc_client.h"
#include "bc_log_client.h"

#include <stdio.h>
#include <string.h>


#define BC_OTHER_PROC_NAME	"other"


#if 1
void __pt_init()
{
	bc_pt_init();
//	bc_pt_open_prj_mdl(BC_MODULE_IPC);
	bc_pt_open_prj_mdl(BC_MODULE_TEST_PROC);
//	bc_pt_open_prj_mdl(BC_MODULE_IPC_TRANS);
	bc_pt_prt_lvl_open(BC_LVL_BIT_ALL);
}

void __log_init()
{
	;
}
#endif


int main()
{
	bc_err_e ret = BC_ERR_OK;
	
	__pt_init();
	bc_platform_init();
	__log_init();
	
	ret = bc_ipc_create(IPC_CLIENT_TYPE_TEST);
	bc_log_sys_dbg_wrt_client(BC_LOG_BIT_INIT, BC_MODULE_TEST_PROC, "process "BC_OTHER_PROC_NAME" running ....\n");
	
	if(ret != BC_ERR_OK)
	{
		BC_PT_ERROR(BC_MODULE_TEST_PROC, "Ipc client init failure, ret = 0x%x\n", ret);
		bc_log_sys_dbg_wrt_client(BC_LOG_BIT_ERROR, BC_MODULE_TEST_PROC, "Ipc client init failure\n");
	}
	BC_PT_INIT(BC_MODULE_TEST_PROC, "Ipc client init successful\n");
	bc_log_sys_dbg_wrt_client(BC_LOG_BIT_INIT, BC_MODULE_TEST_PROC, "Ipc client init successful\n");
	
	bc_dev_thread_show();
	
	return 1;
}

