/*******************************************************************************
  [Author]     : bain.wang@outlook.com.uestc@gmail.com
  [Version]    : 
  [Date]       : 
  [Description]: 主进程MAIN文件

  [Others]     :

  [History]:
	 Date          	Modification 							    			Initials
	----------   ----------                                   					-------
	2017-03-16     Created								   			bain.wang@outlook.com
	2017-06-20     Add								   			bain.wang@outlook.com
				add cfgmgmt
				add clock
				add L1/port
				add system/onu
	2017-07-06	add stats											bain.wang@outlook.com
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//																			  //
//								头   文   件								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_ipc_dev_api.h"
#include "bc_vfs.h"
#include "bc_print.h"
#include "bc_log.h"
#include "bc_platform_init.h"
#include "bc_common_defs.h"
#include <stdio.h>
#include <string.h>


#include "bc_sys_event.h"
#include "bc_test.h"
#include "bc_binchie_db.h"
#include "bc_filetrans_core.h"
#include "bc_cfg_mgmt.h"
#include "bc_system_clock.h"
#include "bc_stats_core.h"
#include "bc_usermgmt_core.h"


#include "bc_igmp.h"


#define BC_MAJOR_PROC_NAME	"bcImage"

#if 1
static bc_uint32 bc_startup_progress_i = 0;
extern bc_uint32 bc_startup_progress_max;

#if	BC_PRJ_NAME_X86
#define PT_DOTDOTDOT "...................................."
#else
#define PT_DOTDOTDOT ".........................................."
#endif


#define BC_STARTUP_CAL(module_id, func) \
	do \
	{ \
	   	bc_uint64 pre, post; \
	   	bc_platform_time_us_get(&pre); \
	   	BC_PT_DBG_SMP(BC_MODULE_SYSTEM, "\n%s start...\n", #func); \
		BC_PT_INIT(module_id, "\rBC Start"PT_DOTDOTDOT"%d%%\r", (bc_startup_progress_i*100)/bc_startup_progress_max); \
		if (bc_startup_progress_i < bc_startup_progress_max) \
			bc_startup_progress_i++; \
		func(); \
		bc_platform_time_us_get(&post); \
		BC_PT_DBG_SMP(BC_MODULE_SYSTEM, "\n%s init cost %d us.\n", #func, (bc_uint32)(post-pre)); \
	} while(0)
#endif


static void __pt_init()
{
	bc_pt_init();
	bc_pt_dbg_init();
	bc_pt_open_prj_mdl(BC_MODULE_SYSTEM);
	
	/* for igmp */
	bc_pt_open_prj_mdl(BC_MODULE_IGMP);
	bc_pt_open_prj_mdl(BC_MODULE_IGMP_DRV);
	bc_pt_open_prj_mdl(BC_MODULE_PLATFORM);	/* igmp alloc source */
	
	bc_pt_prt_lvl_open(BC_LVL_BIT_ALL);
}

static bc_err_e __bc_startup_platform_init()
{
	__pt_init();

	#include "bc_startup.h"
	BC_STARTUP_CAL(BC_MODULE_PLATFORM, bc_platform_init);
	
	#include "bc_startup.h"
	BC_STARTUP_CAL(BC_MODULE_PLATFORM, bc_platform_interrupt_init);
	
	#include "bc_startup.h"
	BC_STARTUP_CAL(BC_MODULE_VFS, bc_file_init);
	
	return BC_ERR_OK;
}

static bc_err_e __bc_startup_system_init()
{
	#include "bc_startup.h"
	BC_STARTUP_CAL(BC_MODULE_CFGMGMT, bc_cfg_init);
	
	#include "bc_startup.h"
	BC_STARTUP_CAL(BC_MODULE_SYSTEM, bc_sys_init);
	
	#include "bc_startup.h"
	BC_STARTUP_CAL(BC_MODULE_SYSTEM, bc_sys_baseinfo_init);
	
	#include "bc_startup.h"
	BC_STARTUP_CAL(BC_MODULE_SYSTEM, bc_sys_ip_init);
	
	#include "bc_startup.h"
	BC_STARTUP_CAL(BC_MODULE_SYSTEM, bc_sys_mac_init);
	
	#include "bc_startup.h"
	BC_STARTUP_CAL(BC_MODULE_SYSTEM, bc_sys_event_init);
	
	#include "bc_startup.h"
	BC_STARTUP_CAL(BC_MODULE_SYSTEM, bc_sys_polling_init);
	
#if 0	/*依赖event 和polling*/
	#include "bc_startup.h"
	BC_STARTUP_CAL(BC_MODULE_TEST, bc_test_init);
#endif

	#include "bc_startup.h"
	BC_STARTUP_CAL(BC_MODULE_LOG, bc_log_sys_init);
	
	#include "bc_startup.h"
	BC_STARTUP_CAL(BC_MODULE_IPC, bc_ipc_dev_init);
	
	#include "bc_startup.h"
	BC_STARTUP_CAL(BC_MODULE_USERMGMT, bc_usermgmt_init);

	#include "bc_startup.h"
	BC_STARTUP_CAL(BC_MODULE_BINCHIE, bc_binchie_db_init);

	#include "bc_startup.h"
	BC_STARTUP_CAL(BC_MODULE_FILETRANS, bc_filetrans_init);

	#include "bc_startup.h"
	BC_STARTUP_CAL(BC_MODULE_STATS, bc_stats_init);
	
	return BC_ERR_OK;
}

static bc_err_e __bc_startup_protocol_init()
{
	#include "bc_startup.h"
	BC_STARTUP_CAL(BC_MODULE_IGMP, bc_igmp_init);
	
	return BC_ERR_OK;
}


int main()
{	
	bc_uint64 sys_pre, sys_post;

	bc_platform_time_us_get(&sys_pre);

	bc_platform_dbg_trace();
	__bc_startup_platform_init();
	__bc_startup_system_init();
	__bc_startup_protocol_init();

	/*主进程启动完成，可向某文件写一个标志，其它进程启动时读取，以保证主进程启动成功*/
	/*........................*/

#ifdef BC_PRJ_NAME_X86
	BC_PT_INIT(BC_MODULE_SYSTEM, "\nBC Start....................................100%%");
#else
	BC_PT_INIT(BC_MODULE_SYSTEM, "\nBC Start..........................................100%%");
#endif

	bc_platform_time_us_get(&sys_post);
	BC_PT_INIT(BC_MODULE_SYSTEM, "\nStartup cost time is %d.%d ms.\n\n", ((bc_uint32)(sys_post-sys_pre))/1000, ((bc_uint32)(sys_post-sys_pre))%1000);	

	bc_pt_open_prj_mdl(BC_MODULE_TEST);
	/* startup end */
	
	while (TRUE)/* keep client running ... */
	{
		/*一旦开启后，如果强行结束此进程可能会不成功，需手动杀死进程号*/
	//	bc_platform_time_sleep(24*60*60);
	}
	
	return 0;
}



#include "bc_startup_post.h"
bc_uint32 bc_startup_progress_max = (BC_STARTUP_NUM_E > 0) ? BC_STARTUP_NUM_E : 1;
