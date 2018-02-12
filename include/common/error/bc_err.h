/************************************************************
  FileName:
  Author:  bain.wang@outlook.com      Version :  1.0        Date:2017-04-12
  Description:                   
  Version:                        
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/

#ifndef __BC_ERR_H__
#define __BC_ERR_H__

#include "bc_common_defs.h"
#include "bc_modules.h"


#define BINCHIE_ADD_API_STEP_I

#define BC_ERR_COMMON_TEMPLATE \
	__bc_err_start_template(0, BC_ERR_OK,           						"success", 				                                	"成功") \
	__bc_err_template(BC_ERR_PARA,               							"parameter error", 				                    		"参数错误") \
	__bc_err_template(BC_ERR_RESOURCE,            						"resource not enough", 							"资源不足") \
	__bc_err_template(BC_ERR_NOT_SUPPORT,	       					"not support",                                                   	"不支持") \
	__bc_err_template(BC_ERR_NOT_FIND, 		  						"not found",                                                      	"没有找到") \
	__bc_err_template(BC_ERR_SEND_FAIL, 							"send fail",                                                       	"发送失败") \
	__bc_err_template(BC_ERR_RECV_FAIL, 							"receive fail",                                                   	"接收失败") \
	__bc_err_template(BC_ERR_SLOT_ID, 								"slot id error",                                                   	"槽位ID错误") \
	__bc_err_template(BC_ERR_DRV_ACCESS,	      						"driver access error",                                        	"驱动访问错误") \
	__bc_err_template(BC_ERR_FILE_ACCESS,	  						"file access error",                                             	"文件访问错误") \
	__bc_err_template(BC_ERR_INVALID_INDEX,   						"invalid index",                                                 	"非法的索引") \
	__bc_err_template(BC_ERR_OUT_OF_RANGE,     						"out of range",                                                 	"超出范围") \
	__bc_err_template(BC_ERR_ALREADY_EXSIT,    						"already exsit",                                                 	"已经存在") \
	__bc_err_template(BC_ERR_NOT_EXSIT, 							"not exsit",                                                        	"不存在") \
	__bc_err_template(BC_ERR_GET,  									"Error while getting config!",                               	"获取配置出错！")\

#define BC_ERR_SYS_TEMPLATE \
	__bc_err_start_template(BC_MODULE_SYSTEM, BC_ERR_SYS_START,    	"sys error id", 				     				"系统错误消息开始")\
	__bc_err_start_template(BC_MODULE_SYSTEM, BC_ERR_SYS_GET_INFO,    	"sys get info error", 				     		"系统信息获取错误")\


#define BC_ERR_IGMP_TEMPLATE \
    __bc_err_start_template(BC_MODULE_IGMP, BC_ERR_IGMP_START,    	"igmp error id", 				     				"IGMP 错误消息开始") \
    __bc_err_template(BC_ERR_IGMP_INIT_FAILED,       					"igmp init fail",                               				"IGMP初始化失败") \
    __bc_err_template(BC_ERR_IGMP_CFG_VALUE_ERROR,   				"igmp cfg err",                           					"IGMP配置参数值错误") \
    __bc_err_template(BC_ERR_IGMP_INDEX_ERROR,       					"igmp proxy id err",                               			"IGMP 代理索引错误") \
    __bc_err_template(BC_ERR_IGMP_INDEX_USED,       					"igmp proxy id exist",                               			"IGMP代理索引已经使用") \
    __bc_err_template(BC_ERR_IGMP_PROXY_RES_OUT,       				"igmp has no valid proxy num",                               	"IGMP代理数量超限") \
    __bc_err_template(BC_ERR_IGMP_ONU_ID_ERROR,       					"igmp not find onu id",                               		"IGMP指定onu_id不存在") \
    __bc_err_template(BC_ERR_IGMP_PROXY_MC_IP_EXIST,       			"igmp addr is exist",                               			"IGMP组播IP已经存在") \
    __bc_err_template(BC_ERR_IGMP_NO_PROXY_ITEM,       				"igmp no proxy item",                               			"IGMP无代理条码") \
    __bc_err_template(BC_ERR_IGMP_MC_VID_EQUAL_TO_VLAN_ID,       		"igmp proxy vlan equal ucast vlan",                    	"IGMP代理vlan不能等于单播vlan") \
    __bc_err_template(BC_ERR_IGMP_VID_EQUAL_TO_MAN_VLAN,       		"igmp proxy vlan equal mnmt vlan",             		"IGMP代理vlan不能等于管理vlan") \
    __bc_err_template(BC_ERR_IGMP_PROXY_INDEX_ERROR,       			"igmp proxy id err",                               			"IGMP代理索引错误") \
    __bc_err_template(BC_ERR_IGMP_PROXY_NOT_EXIST,       				"igmp proxy id not exist",                               		"IGMP代理索引的条目不存在") \
    __bc_err_template(BC_ERR_IGMP_PROXY_EXIST,       					"igmp proxy id exist",                               			"IGMP指定代理索引的条目已经存在") \
    __bc_err_template(BC_ERR_IGMP_PROXY_VID_USED,       				"igmp vlan already used",                               		"IGMP指定代理vid已经使用") \
    __bc_err_template(BC_ERR_IGMP_PROXY_VID_ERROR,       				"igmp vlan id err",                               			"IGMP指定代理vid错误") \
    __bc_err_template(BC_ERR_IGMP_PROXY_USED,       					"igmp proxy is using",                               			"IGMP指定代理配置正在使用") \
    __bc_err_template(BC_ERR_IGMP_PROXY_NAME_ERR,       				"igmp proxy name err",                               		"IGMP代理名称有误") \
    __bc_err_template(BC_ERR_IGMP_MLTCST_RES_OUT,       				"igmp num beyond control",                               	"IGMP创建onu组播数量超限") \
    __bc_err_template(BC_ERR_IGMP_MLTCST_VLAN_ID_NOT_EXIST,       		"mcast vlan id not exist",                               		"组播vlan不存在") \
    __bc_err_template(BC_ERR_IGMP_PORT_ID_ERROR,       				"port id err",                               				"端口错误") \
    __bc_err_template(BC_ERR_IGMP_PORT_ID_EXIST,       					"port id exist",                               				"端口已经存在") \
    __bc_err_template(BC_ERR_IGMP_PORT_ID_NOT_EXIST,       			"port id not exist",                               			"端口不存在") \
    __bc_err_template(BC_ERR_IGMP_PAR_ERROR,       					"paramter err",                              	 			"参数值有误") \
    __bc_err_template(BC_ERR_IGMP_TARGE_NOT_EXIST,      	 			"igmp init fail",                               				"igmp目标不存在") \
    __bc_err_template(BC_ERR_IGMP_DRIVER_ERROR,       					"igmp driver err",                               			"igmp驱动错误") \
    __bc_err_template(BC_ERR_IGMP_RSP_BIGGER_THAN_QUERY,       		"response interval bigger than query interval",     	"查询响应间隔比查询时间间隔大") \
    __bc_err_template(BC_ERR_IGMP_PARAM_ERROR,       					"param err",                               				"参数错误") \
    __bc_err_template(BC_ERR_IGMP_FUNC_INACTIVE,       				"igmp function un support",                               	"功能不支持") \
    __bc_err_template(BC_ERR_IGMP_MLTCST_VLAN_ID_EXIST,      			"mcast vlan exist",                               			"组播vlan已经存在") \
    __bc_err_template(BC_ERR_IGMP_RESOURE,       						"have no resouce",                               			"IGMP 资源不足")


#define BC_ERR_PLATFROM_TEMPLATE \
	__bc_err_start_template(BC_MODULE_PLATFORM, BC_ERR_PLATFROM_START,    "platform error id",						"PLATFORM 错误消息开始") \
	__bc_err_template(BC_ERR_PLATFROM_THREAD_NOT_EXIST,       		"Thread does not exist",							"此线程不存在") \
	__bc_err_template(BC_ERR_PLATFROM_MUTEX_NOT_EXIST,      			"mutex  does not exist",							"互斥锁不存在") \
	__bc_err_template(BC_ERR_PLATFROM_SEM_CREATE_FAIL,       		"Semaphore creation failed",						"信号量创建失败") \
	__bc_err_template(BC_ERR_PLATFROM_SEM_NOT_EXIST,       			"Semaphore  does not exist",					"信号量不存在") \
	__bc_err_template(BC_ERR_PLATFROM_SEM_OP_FAIL,       				"Semaphore operation failed",					"信号量操作失败") \
	__bc_err_template(BC_ERR_PLATFROM_QUE_FAILED,       				"Queue operation failed",					    	"队列操作失败") \
	__bc_err_template(BC_ERR_PLATFROM_SPI_CFG_FAIL,       			"SPI configure failed",					    		"spi配置失败")


#define BC_ERR_UTILI_TEMPLATE \
	__bc_err_start_template(BC_MODULE_UTILI, BC_ERR_UTILI_START,    	"utili error id",									"UTILI 错误消息开始")


#define BC_ERR_PRINT_TEMPLATE \
	__bc_err_start_template(BC_MODULE_PRINT, BC_ERR_PRINT_START,    	"print error id",								"PRINT 错误消息开始"	) \
	__bc_err_template(BC_ERR_PRINT_NOT_INIT,       					"print module not init", 							"PRINT 模块未初始化"	) \
	__bc_err_template(BC_ERR_PRINT_MDL_ID_EXCEED,       				"print module id exceed", 						"PRINT 模块ID号超限") \
	__bc_err_template(BC_ERR_PRINT_FILE_NAME_NO_MATCH,       		"print cfg file name no match", 					"PRINT 配置文件名不匹配") \
	__bc_err_template(BC_ERR_PRINT_FILE_NUM_EXCEED,       			"print cfg file number exceed", 					"PRINT 配置文件个数超限") \
	__bc_err_template(BC_ERR_PRINT_FILE_LINE_NUM_EXCEED,       		"print cfg file line number exceed", 				"PRINT 配置文件行号超限") \
	__bc_err_template(BC_ERR_PRINT_FILE_READ_ERROR,       			"print cfg file read data error", 					"PRINT 配置文件读数据错误") \
	__bc_err_template(BC_ERR_PRINT_FILE_WRITE_ERROR,       			"print cfg file write data error", 					"PRINT 配置文件写数据错误")


#define BC_ERR_VFS_TEMPLATE \
	__bc_err_start_template(BC_MODULE_VFS, BC_ERR_VFS_START,    		"virtual fs error id",								"VFS 错误消息开始") \
	__bc_err_template(BC_ERR_VFS_MDL_ID_EXCEED,       				"????",                                                 			"模块id超出范围") \
	__bc_err_template(BC_ERR_VFS_FILENAME_EXCEED,       				"????",                                                 			"文件名超出范围") \
	__bc_err_template(BC_ERR_VFS_PATH_EXCEED,       					"????",                                                 			"文件路径超出范围") \
	__bc_err_template(BC_ERR_VFS_CREATE_FAIL,       					"????",                                                 			"文件创建失败") \
	__bc_err_template(BC_ERR_VFS_OPEN_FAIL,       					"????",                                                 			"文件打开失败") \
	__bc_err_template(BC_ERR_VFS_CLOSE_FAIL,       					"????",                                                 			"文件关闭失败") \
	__bc_err_template(BC_ERR_VFS_DELETE_FAIL,       					"????",                                                 			"文件删除失败") \
	__bc_err_template(BC_ERR_VFS_COPY_FAIL,       					"????",                                                 			"文件复制失败")

#define BC_ERR_LOG_TEMPLATE \
	__bc_err_start_template(BC_MODULE_LOG, BC_ERR_LOG_START,    	"log error id",									"LOG 错误消息开始") \
	__bc_err_template(BC_ERR_LOG_FILE_OPEN,       					"open log file error!",							"打开日志文件错误") \
	__bc_err_template(BC_ERR_LOG_FILE_CREATE,       					"create log file error!",							"创建日志文件错误") \
	__bc_err_template(BC_ERR_LOG_GET_DATA,      	 					"get log data error!",							"获取日志数据出错") \
	__bc_err_template(BC_ERR_LOG_WRITE_FAIL,       					"write log file error!", 							"写日志文件出错") \
	__bc_err_template(BC_ERR_LOG_OFFSET,       						"log file offset error!",							"日志文件偏移出错") \
	__bc_err_template(BC_ERR_LOG_INIT_FAIL,       						"log file init fail!",								"日志文件初始化失败"	) \
	__bc_err_template(BC_ERR_LOG_SYS_IPC,      				 		"system log ipc fail!", 							"系统日志进程通信失败") \
	__bc_err_template(BC_ERR_LOG_LVL,       							"log level error!",								"日志级别出错")

#define BC_ERR_IPC_TEMPLATE \
	__bc_err_start_template(BC_MODULE_IPC, BC_ERR_IPC_START,    		"ipc error id",									"IPC 错误消息开始"	) \
	__bc_err_template(BC_ERR_IPC_RECV,       							"failed to receive ipc data",						"IPC 接收数据错误") \
	__bc_err_template(BC_ERR_IPC_DATA_INVALID,       					"ipc data is invalid",							"IPC 数据无效") \
	__bc_err_template(BC_ERR_IPC_SEND,       							"failed to send ipc data",						"IPC 发送数据错误") \
	__bc_err_template(BC_ERR_IPC_SOCKET_CREATE,       				"failed to create ipc socket",						"创建IPC通信Socket失败") \
	__bc_err_template(BC_ERR_IPC_PACK_INIT,       					"failed to initialization ipc data package",			"初始化IPC数据包失败") \
	__bc_err_template(BC_ERR_IPC_GET_SERVER_PARA,       				"failed to get ipc server parameter",				"获取IPC Server参数失败") \
	__bc_err_template(BC_ERR_IPC_CLIENT_CREATE,       				"failed to create ipc client",						"创建IPC Client失败") \
	__bc_err_template(BC_ERR_IPC_SERVER_CREATE,       				"failed to create ipc server",						"创建IPC Server失败") \
	__bc_err_template(BC_ERR_IPC_PROCESS_HANDER,       				"ipc process handler is invalid",					"IPC 处理句柄无效") \
	__bc_err_template(BC_ERR_IPC_SESSION_NO_CREATE,       			"ipc session is not created",					    	"IPC Session未创建")

#define BC_ERR_SESSION_TEMPLATE \
	__bc_err_start_template(BC_MODULE_SESSION, BC_ERR_SESSION_START,    "session error id",							"SESSION 错误消息开始")

#define BC_ERR_TEST_PROC_TEMPLATE \
	__bc_err_start_template(BC_MODULE_TEST_PROC, BC_ERR_TEST_PROC_START,    "test proc error id",					"TEST PROC 错误消息开始")

#define BC_ERR_TEST_TEMPLATE \
	__bc_err_start_template(BC_MODULE_TEST, BC_ERR_TEST_START,    	"test error id",									"TEST 错误消息开始")

#define BC_ERR_SNMP_TEMPLATE \
	__bc_err_start_template(BC_MODULE_SNMP, BC_ERR_SNMP_START,    	"snmp error id",								"SNMP 错误消息开始")
	
#define BC_ERR_CLI_TEMPLATE \
	__bc_err_start_template(BC_MODULE_CLI, BC_ERR_CLI_START,    		"cli error id", 				     					"CLI 错误消息开始")

#define BC_ERR_USERMGMT_TEMPLATE \
	__bc_err_start_template(BC_MODULE_USERMGMT, BC_ERR_USERMGMT_START,    "user mgmt error id",					"USERMGMT 错误消息开始") \
	__bc_err_template(BC_ERR_USERMGMT_UNREG_ERR,       				"user unregister error id",                                    	"用户注销错误") \
	__bc_err_template(BC_ERR_USERMGMT_LINKS_NUM_MAX,       			"user link num max error id",                               	"用户连接数上限") \
	__bc_err_template(BC_ERR_USERMGMT_MUTEX_ERR,       				"usermgmt mutex error id",                               	"用户模块互斥销初始失败") \
	__bc_err_template(BC_ERR_USERMGMT_REG_ERR,       				"user register error id",                                        	"用户注册错误") \
	__bc_err_template(BC_ERR_USERMGMT_WRITE_ERR,       				"user file write error id",                                       	"用户文件写入错误") \
	__bc_err_template(BC_ERR_USERMGMT_READ_ERR,       				"user file read error id",                                        	"用户文件读取错误") \
	__bc_err_template(BC_ERR_USERMGMT_CREATE_ERR,       			"user file create error id",                                    	"用户文件创建错误") \
	__bc_err_template(BC_ERR_USERMGMT_LVL_ERR,       				"user level error id",                                           	"用户权限错误") \
	__bc_err_template(BC_ERR_USERMGMT_NO_EXIST,       				"user no exist error id",                                  		"用户不存在") \
	__bc_err_template(BC_ERR_USERMGMT_NO_LOGIN,       				"user no lline error id",                                         	"用户不在线") \
	__bc_err_template(BC_ERR_USERMGMT_USER_NUM_MAX,       			"user num max error id",                                      	"用户数上限") \
	__bc_err_template(BC_ERR_USERMGMT_REPEAT_REG,       				"user repeat register error id",                          		"用户重复注册") \
	__bc_err_template(BC_ERR_USERMGMT_REPEAT_LOGIN,       			"user repeat login error id",                                   	"用户重复登陆") \
	__bc_err_template(BC_ERR_USERMGMT_USER_INFO_ERR,       			"user info error id",                                                 	"用户信息错误") \
	__bc_err_template(BC_ERR_USERMGMT_SID_UNUSED,       			"client sid error id",                                                 	"客户端SID错误") \
	__bc_err_template(BC_ERR_USERMGMT_DEFAULT_USER,  				"default user error id",                                       	"系统用户不可操作")	\
	__bc_err_template(BC_ERR_USERMGMT_MEM_ALLOC,  				"usermgmt memory alloction failed",                    	"用户内存分配失败")

#define BC_ERR_BINCHIE_TEMPLATE \
	__bc_err_start_template(BC_MODULE_BINCHIE, BC_ERR_BINCHIE_START,    "binchie info error id",						"BINCHIE 错误消息开始") \
	__bc_err_template(BC_ERR_BINCHIE_USER_FULL,       				"binchie user full",                                    			"BINCHIE人员已满") \
	__bc_err_template(BC_ERR_BINCHIE_USER_EMPTY,       				"binchie user empty",                               			"BINCHIE人员已空") \
	__bc_err_template(BC_ERR_BINCHIE_USER_UNLAWFUL,       			"binchie user operation unlawful",                             "BINCHIE人员非法操作研发人员信息") \
	__bc_err_template(BC_ERR_BINCHIE_USER_DUTY_INVALID,       				"binchie user add duty invalid",                 	"BINCHIE人员权限不合法") \
	__bc_err_template(BC_ERR_BINCHIE_USER_ALREADY_EXIST,       			"binchie user already exist",                             	"BINCHIE人员已存在") \
	__bc_err_template(BC_ERR_BINCHIE_USER_INEXIST,       				"user user no exist",                                        		"BINCHIE人员名不存在")

#define BC_ERR_FILETRANS_TEMPLATE \
	__bc_err_start_template(BC_MODULE_FILETRANS, BC_ERR_FILETRANS_START,    "filetrans error id",									"FILETRANS 错误消息开始"	) \
	__bc_err_template(BC_ERR_FILETRANS_FUN_ERROR,       "failed to source file",									"FILETRANS 源文件错误") \
	__bc_err_template(BC_ERR_FILETRANS_SET_ERROR,       "failed to transfer of information configuration",			"FILETRANS 配置传输信息错误") \
	__bc_err_template(BC_ERR_FILETRANS_PUT_ERROR,       "failed to upload file",									"FILETRANS 上传出错") \
	__bc_err_template(BC_ERR_FILETRANS_GET_ERROR,       "failed to download file",									"FILETRANS 下载出错") \
	__bc_err_template(BC_ERR_FILETRANS_TRANS_FUN_ERROR,       "failed to trans fun id",									"FILETRANS 文件类型出错"	) \
	__bc_err_template(BC_ERR_FILETRANS_RUNNING,       "failed to file trans running",									"FILETRANS 有文件正在传输中") \
	__bc_err_template(BC_ERR_FILETRANS_WRITE_PARA_ERROR,       "failed to para set error",									"FILETRANS 参数设置错误") \
	__bc_err_template(BC_ERR_FILETRANS_USB_AREA_NONEXIST,       "failed to usr area get error",									"USB中存放的镜像文件不存在") \
	__bc_err_template(BC_ERR_FILETRANS_NAME_INVALID,       "failed to file name invalidr",									"文件名含有无效字符") \
	__bc_err_template(BC_ERR_FILETRANS_ACCESS_ERROR,       "????",                                                 "????")

#define BC_ERR_CFGMGMT_TEMPLATE \
	__bc_err_start_template(BC_MODULE_CFGMGMT, BC_ERR_CFGMGMT_START,    "configure mana error id",           "CFGMGMT 错误消息开始") \
	__bc_err_template(BC_ERR_CFGMGMT_MEM_ALLOC,       "configuration memory alloction failed!",              "配置内存分配失败!") \
	__bc_err_template(BC_ERR_CFGMGMT_FILE_CREAT,       "configuration file create failed!",                  "配置文件创建失败!") \
	__bc_err_template(BC_ERR_CFGMGMT_SAVE,       "configuration file save error!", 	                         "配置文件保存出错!") \
	__bc_err_template(BC_ERR_CFGMGMT_MDL_CLR,       "configuration file delete error!",                      "配置文件清除出错!") \
	__bc_err_template(BC_ERR_CFGMGMT_FILE_OPEN,       "configuration file open failed!",                     "配置文件打开失败!") \
	__bc_err_template(BC_ERR_CFGMGMT_GET_INFO,       "configuration file get info error!",                   "配置文件获取信息出错!") \
	__bc_err_template(BC_ERR_CFGMGMT_FILE_NUM_OUT, "configuration file number exceed", 	                     "配置文件数量超限!")\
	__bc_err_template(BC_ERR_CFGMGMT_MDL_REG, "failed to configuration module register",                "配置模块注册失败!")

#define BC_ERR_STATS_TEMPLATE \
	__bc_err_start_template(BC_MODULE_STATS, BC_ERR_STATS_START,    "configure mana error id",           "STATS 错误消息开始") \
	__bc_err_template(BC_ERR_STATS_GET_MUTEX,       "stats get mutex failed!",              "性能统计分配互斥锁失败!") \
	__bc_err_template(BC_ERR_STATS_GET_TEMP,       "stats get temperature failed!",                  "性能统计取温度失败!") \
	__bc_err_template(BC_ERR_STATS_GET_OAM_PORT,       "stats get oam-port info failed!", 	                         "性能统计取OAM端口失败!") \
	__bc_err_template(BC_ERR_STATS_GET_PORT,       "stats get port info failed!",                      "性能统计取端口失败!") \
	__bc_err_template(BC_ERR_STATS_GET_PTP_PORT,       "stats get ptp-port info failed!",                     "性能统计取PTP端口失败!") \
	__bc_err_template(BC_ERR_STATS_GET_PTP,       "stats get ptp info failed!",                   "性能统计取PTP 失败!") \
	__bc_err_template(BC_ERR_STATS_GET_VP, "stats get vp info failed!", 	                     "性能统计取VP 失败!")\
	__bc_err_template(BC_ERR_STATS_GET_VC, "stats get vc info failed!", 	                     "性能统计取VC 失败!")\
	__bc_err_template(BC_ERR_STATS_GET_E1, "stats get e1 info failed!", 	                     "性能统计取E1 失败!")\
	__bc_err_template(BC_ERR_STATS_GET_INFO, "stats get info failed!", 	                     "性能统计取信息失败!")\
	__bc_err_template(BC_ERR_STATS_GET_CUR_INFO, "stats get cur perf info failed!", 	                     "性能统计取当前信息失败!")\
	__bc_err_template(BC_ERR_STATS_GET_15MIN_INFO, "stats get 15min info failed!", 	                     "性能统计取15分钟信息失败!")\
	__bc_err_template(BC_ERR_STATS_GET_24HOUR_INFO, "stats get 24hour info failed!", 	                     "性能统计取24小时信息失败!")\
	__bc_err_template(BC_ERR_STATS_GET_15MIN_INCREAM_INFO, "stats get 15min incream info failed!", 	                     "性能统计取15分钟增量信息失败!")\
	__bc_err_template(BC_ERR_STATS_GET_24HOUR_INCREAM_INFO, "stats get 24hour incream info failed!", 	                     "性能统计取24小时增量信息失败!")\
	__bc_err_template(BC_ERR_STATS_SET_THRESHOLD, "stats set threshold info failed!", 	                     "性能统计设置门限信息失败!")\
	__bc_err_template(BC_ERR_STATS_GET_THRESHOLD, "stats get threshold info failed!",                "性能统计取门限信息失败!")


#undef __bc_err_start_template
#define __bc_err_start_template(mod_id, err_id, english_m, chinese_m) err_id = mod_id,

#undef __bc_err_template
#define __bc_err_template(err_id, english_m, chinese_m) err_id,


#define BINCHIE_ADD_API_STEP_J

typedef enum
{
	BC_ERR_COMMON_TEMPLATE

	BC_ERR_SYS_TEMPLATE
	BC_ERR_IGMP_TEMPLATE
	BC_ERR_PLATFROM_TEMPLATE
	BC_ERR_UTILI_TEMPLATE
	BC_ERR_PRINT_TEMPLATE
	BC_ERR_VFS_TEMPLATE
	BC_ERR_LOG_TEMPLATE
	BC_ERR_IPC_TEMPLATE
	BC_ERR_SESSION_TEMPLATE
	BC_ERR_TEST_PROC_TEMPLATE
	BC_ERR_TEST_TEMPLATE
	BC_ERR_SNMP_TEMPLATE
	BC_ERR_CLI_TEMPLATE
	BC_ERR_USERMGMT_TEMPLATE
	BC_ERR_BINCHIE_TEMPLATE
	BC_ERR_FILETRANS_TEMPLATE
	BC_ERR_CFGMGMT_TEMPLATE
	BC_ERR_STATS_TEMPLATE
}bc_err_e;

#undef __bc_err_start_template
#undef __bc_err_template


#endif

