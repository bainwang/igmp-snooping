/************************************************************
  -------------------------------------------------------------------------
  FileName:
  Author:  bain.wang@outlook.com      Version :  1.0        Date:2016-4-22
  Description:                   
  Version:                        
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/

#ifndef __bc_func_h__
#define __bc_func_h__


#include "bc_common_defs.h"
#include "bc_modules.h"
#include "bc_proj_defs.h"


/*  
	BC_F_DONT_SYNC: 不会同步，仅作进程间通信

	BC_F_SYNC: 数据会被同步发送到(主备切换)的备份板中，备份板的*_srv
接口同样能够收到这个数据，一般来讲只有set动作需要同步，而get
动作不需要同步。

   BC_F_SYNC_ONLY: 该接口只用来做主备数据同步，如果被用作进程间通信会
 返回系统不支持的错误号
*/
#define BC_F_DONT_SYNC 	0
#define BC_F_SYNC 					1
#define BC_F_SYNC_ONLY		2


/*
    BC_F_SLAVE_USE: 当本板卡作为(主备切换)备份板时，仍然可以使用该接口，
一般来说，在备份板中只允许get动作。

    BC_F_SLAVE_CANNOT_USE: 不允许在备份板中使用
*/
#define BC_F_SLAVE_USE 1
#define BC_F_SLAVE_CANNOT_USE 0

#if 1

/*

	在这里添加进程 间通信API，

	1. 需同步在bc_modules_e中增加相关的模块ID。
	2. 需同步在bc_func_e中增加这里所定义的BC_FUNC_XXXX_TEMPLATE 宏
	3. 需同步在ipc_dev_srv_hdr_arr中增加BC_FUNC_XXXX_TEMPLATE 宏

	头文件请添加到bc_ipc_dev_server.c中
*/

#define BINCHIE_ADD_API_STEP_C

#define    BC_FUNC_SYSTEM_TEMPLATE \
    __bc_func_start_tmplate(BC_MODULE_SYSTEM) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_clock_date_set_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_clock_date_get_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_clock_tz_set_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_clock_tz_get_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_sys_ipc_baseinfo_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_sys_ipc_event_dbg_dump_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_sys_ipc_polling_dbg_dump_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_sys_ipc_block_ext_dump_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_sys_ipc_block_ext_dump_single_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_sys_ipc_name_set_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_sys_ipc_language_set_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_sys_ipc_reboot_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_sys_ipc_reset_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_sys_mac_set_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_sys_mac_get_srv) \

#define    BC_FUNC_IGMP_TEMPLATE \
    __bc_func_start_tmplate(BC_MODULE_IGMP)

#define    BC_FUNC_PLATFORM_TEMPLATE \
    __bc_func_start_tmplate(BC_MODULE_PLATFORM) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_dev_thread_show_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_dev_timer_show_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_dev_sem_show_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_dev_mutex_show_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_dev_mem_show_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_dev_queue_show_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_dev_queue_dump_single_srv) \

#define    BC_FUNC_UTILI_TEMPLATE \
    __bc_func_start_tmplate(BC_MODULE_UTILI)

#define    BC_FUNC_PRINT_TEMPLATE \
    __bc_func_start_tmplate(BC_MODULE_PRINT) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_pt_prt_open_all_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_pt_prt_close_all_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_pt_prt_lvl_open_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_pt_prt_lvl_close_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_pt_open_prj_all_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_pt_open_prj_mdl_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_pt_open_prj_mdl_file_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_pt_close_prj_all_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_pt_close_prj_mdl_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_pt_close_prj_mdl_file_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_pt_get_prt_lvl_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_pt_get_prj_all_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_pt_dbg_save_cfg_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_pt_dbg_save_clear_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_pt_dump_srv) \

#define    BC_FUNC_VFS_TEMPLATE \
    __bc_func_start_tmplate(BC_MODULE_VFS)

#define    BC_FUNC_LOG_TEMPLATE \
    __bc_func_start_tmplate(BC_MODULE_LOG) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_log_lvl_en_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_log_lvl_open_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_log_lvl_close_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_log_lvl_get_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_log_sys_wrt_upper_layer_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_log_get_sys_log_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_log_sys_dbg_dump_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_log_sys_dbg_wrt_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_log_sys_buffer_clear_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_log_sys_flash_clear_srv) \

#define    BC_FUNC_IPC_TEMPLATE \
    __bc_func_start_tmplate(BC_MODULE_IPC) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_ipc_dev_client_release_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_ipc_dev_client_request_test_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_ipc_dev_client_struct_test_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_ipc_dev_broad_client_struct_test_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_ipc_dev_bcdevapp_server_dump_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_ipc_dev_server_package_dump_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_ipc_dev_bcdevapp_trans_dump_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_ipc_dev_bcdevapp_proc_dump_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_ipc_dev_bcdevapp_proc_ofs_dump_srv) \

#define    BC_FUNC_SESSION_TEMPLATE \
    __bc_func_start_tmplate(BC_MODULE_SESSION) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_session_create_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_session_release_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_session_time_tick_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_session_ipc_dump_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_session_ipc_msg_back_srv) \

#define    BC_FUNC_TEST_PROC_TEMPLATE \
    __bc_func_start_tmplate(BC_MODULE_TEST_PROC)

#define    BC_FUNC_TEST_TEMPLATE \
    __bc_func_start_tmplate(BC_MODULE_TEST)

#define    BC_FUNC_SNMP_TEMPLATE \
    __bc_func_start_tmplate(BC_MODULE_SNMP)

#define    BC_FUNC_CLI_TEMPLATE \
    __bc_func_start_tmplate(BC_MODULE_CLI)

#define    BC_FUNC_USERMGMT_TEMPLATE \
    __bc_func_start_tmplate(BC_MODULE_USERMGMT) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_CANNOT_USE, bc_usermgmt_register_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_CANNOT_USE, bc_usermgmt_unregister_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_CANNOT_USE, bc_usermgmt_login_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_CANNOT_USE, bc_usermgmt_logout_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_CANNOT_USE, bc_usermgmt_get_info_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_CANNOT_USE, bc_usermgmt_get_list_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_CANNOT_USE, bc_usermgmt_get_user_count_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_CANNOT_USE, bc_usermgmt_set_password_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_CANNOT_USE, bc_usermgmt_set_level_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_CANNOT_USE, bc_usermgmt_get_line_info_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_CANNOT_USE, bc_usermgmt_get_list_dump_srv) \

#define    BC_FUNC_BINCHIE_TEMPLATE \
    __bc_func_start_tmplate(BC_MODULE_BINCHIE) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_CANNOT_USE, bc_binchie_get_info_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_CANNOT_USE, bc_binchie_set_info_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_CANNOT_USE, bc_binchie_get_list_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_CANNOT_USE, bc_binchie_set_def_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_CANNOT_USE, bc_binchie_add_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_CANNOT_USE, bc_binchie_del_srv) \

#define    BC_FUNC_FILETRANS_TEMPLATE \
    __bc_func_start_tmplate(BC_MODULE_FILETRANS) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_filetrans_get_list_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_filetrans_get_info_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_filetrans_set_info_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_filetrans_upload_file_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_filetrans_download_file_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_filetrans_set_upload_file_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_filetrans_set_download_file_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_filetrans_switch_over_kernel_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_filetrans_switch_over_file_system_srv)

#define    BC_FUNC_CFGMGMT_TEMPLATE \
    __bc_func_start_tmplate(BC_MODULE_CFGMGMT) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_cfg_save_name_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_cfg_save_no_name_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_cfg_get_run_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_cfg_clr_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_cfg_get_cfglist_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_cfg_set_boot_load_file_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_cfg_no_boot_load_file_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_cfg_dbg_dump_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_cfg_dbg_mdl_ins_srv)

#define    BC_FUNC_STATS_TEMPLATE \
    __bc_func_start_tmplate(BC_MODULE_STATS) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_stats_get_board_temp_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_stats_get_oamport_info_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_stats_get_oamport_list_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_stats_get_port_info_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_stats_get_port_list_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_stats_get_ptpport_info_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_stats_get_ptpport_list_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_stats_get_ptp_info_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_stats_get_vp_info_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_stats_get_vp_list_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_stats_get_vc_info_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_stats_get_vc_list_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_stats_get_e1_info_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_stats_get_e1_list_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_stats_get_cur_info_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_stats_get_15min_info_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_stats_get_24hour_info_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_stats_get_15min_incream_info_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_stats_get_24hour_incream_info_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_stats_get_15min_num_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_stats_get_24hour_num_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_stats_get_15min_valid_num_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_stats_get_24hour_valid_num_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_stats_del_info_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_stats_del_15min_info_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_stats_del_24hour_info_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_stats_threshold_get_srv) \
    __bc_func_dev_srv_temp(BC_F_DONT_SYNC, BC_F_SLAVE_USE, bc_stats_threshold_set_srv)


/*依次添加各模块的SRV*/

#endif



#if 1

#undef __bc_func_start_tmplate
#define __bc_func_start_tmplate(module_id) module_id##_e = module_id,

#undef __bc_func_dev_srv_temp
#define __bc_func_dev_srv_temp(sync, slave, func) func##_e,


#define BC_FUNC_ENUM(func) func##_e


#define BINCHIE_ADD_API_STEP_B

typedef enum {
	/*存放的位置必须与bc_modules_e中的位置一致*/
	BC_FUNC_SYSTEM_TEMPLATE
	BC_FUNC_IGMP_TEMPLATE
	BC_FUNC_PLATFORM_TEMPLATE
	BC_FUNC_UTILI_TEMPLATE
	BC_FUNC_PRINT_TEMPLATE
	BC_FUNC_VFS_TEMPLATE
	BC_FUNC_LOG_TEMPLATE
	BC_FUNC_IPC_TEMPLATE
	BC_FUNC_SESSION_TEMPLATE
	BC_FUNC_TEST_PROC_TEMPLATE
	BC_FUNC_TEST_TEMPLATE
	BC_FUNC_SNMP_TEMPLATE
	BC_FUNC_CLI_TEMPLATE
	BC_FUNC_USERMGMT_TEMPLATE
	BC_FUNC_BINCHIE_TEMPLATE
	BC_FUNC_FILETRANS_TEMPLATE
	BC_FUNC_CFGMGMT_TEMPLATE
	BC_FUNC_STATS_TEMPLATE
	

} bc_func_e;

#undef __bc_func_start_tmplate
#undef __bc_func_dev_srv_temp

#endif
#endif

