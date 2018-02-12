/************************************************************
  Copyright (C), 1988-2014, xxxxx Tech. Co., Ltd.
  FileName:
  Author:  wangbin      Version :  1.0        Date:2014-4-22
  Description:                   
  Version:                        
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/

#ifndef __bc_err_h__
#define __bc_err_h__

#include "bc_common_defs.h"
#include "bc_modules.h"

#define BC_ERR_COMMON_TEMPLATE \
	__bc_err_start_template(0, BC_ERR_OK,                        "success", 				                                "成功") \
	__bc_err_template(BC_ERR_PARA,                        "parameter error", 				                                "参数错误") \
	__bc_err_template(BC_ERR_RESOURCE,                "resource not enough", 							              "资源不足") \
	__bc_err_template(BC_ERR_NOT_SUPPORT,	       "not support",                                                   "不支持") \
	__bc_err_template(BC_ERR_NOT_FIND, 		          "not found",                                                      "没有找到") \
	__bc_err_template(BC_ERR_SEND_FAIL, 		          "send fail",                                                       "发送失败") \
	__bc_err_template(BC_ERR_RECV_FAIL, 		          "receive fail",                                                   "接收失败") \
	__bc_err_template(BC_ERR_SLOT_ID, 			          "slot id error",                                                   "槽位ID错误") \
	__bc_err_template(BC_ERR_DRV_ACCESS,	          "driver access error",                                        "驱动访问错误") \
	__bc_err_template(BC_ERR_FILE_ACCESS,	          "file access error",                                             "文件访问错误") \
	__bc_err_template(BC_ERR_INVALID_INDEX,        "invalid index",                                                 "非法的索引") \
	__bc_err_template(BC_ERR_OUT_OF_RANGE,        "out of range",                                                 "超出范围") \
	__bc_err_template(BC_ERR_ALREADY_EXSIT,       "already exsit",                                                 "已经存在") \
	__bc_err_template(BC_ERR_NOT_EXSIT, 			      "not exsit",                                                        "不存在") \
	__bc_err_template(BC_ERR_ONU_NOT_SUPPORT,  "onu not support",                                             " ???") \
	__bc_err_template(BC_ERR_ONU_OFFLINE,  "onu is offline",                                             " ONU已下线")\
	__bc_err_template(BC_ERR_GET,  "Error while getting config!",                                             "获取配置出错！")\
	


#define BC_ERR_SYS_TEMPLATE \
	__bc_err_start_template(BC_MODULE_SYSTEM, BC_ERR_SYS_START,    "sys error id", 				     "系统错误消息开始")\
	__bc_err_start_template(BC_MODULE_SYSTEM, BC_ERR_SYS_GET_INFO, "get system info error", 	     "获取系统信息出错")\
	

#define BC_ERR_VLAN_TEMPLATE \
	__bc_err_start_template(BC_MODULE_VLAN, BC_ERR_VLAN_START,    	"vlan error id", 				     "VLAN 错误消息开始") \
	__bc_err_template(BC_ERR_VLAN_ID_ERR,       					"vlan id ERROR",                     "VLAN ID 错误") \
	__bc_err_template(BC_ERR_VLAN_NOT_EXIT,       					"vlan not exit",                     "VLAN 不存在") \
	__bc_err_template(BC_ERR_VLAN_MODE_NOT_TRUNK,       				"access port can not add other vlan",      "access 模式端口不能添加其他vlan") \
	__bc_err_template(BC_ERR_VLAN_TRANS_NOT_EXIT,       			"vlan translation list not exit",   "VLAN映射列表 不存在") \
	__bc_err_template(BC_ERR_VLAN_ENTRY_FULL,       	"configure failed, because entry is full !\r\n", "配置失败，因为表项已经配满!") \
	__bc_err_template(BC_ERR_VLAN_AGG_NOT_EXIT,       			"vlan aggration list not exit",   "VLAN聚合列表 不存在") \
	__bc_err_template(BC_ERR_VLAN_QINQ_NOT_EXIT,       			"vlan qinq list not exit",   "VLAN QINQ列表 不存在") \
	__bc_err_template(BC_ERR_VLAN_DEL_DEF_VLAN,       			"do not delete default vlan 1",   "不能删除默认vlan 1") \
	__bc_err_template(BC_ERR_VLAN_DEL_MANAGE_VLAN,       "do not delete manage vlan 4094",   "不能删除管理vlan 4094") \
	__bc_err_template(BC_ERR_VLAN_ID_USED,  						"vlan id used",                      "VLAN ID 被占用") \
	__bc_err_template(BC_ERR_VLAN_IN_USED, 							"vlan in use",                       "VLAN 正在使用") \
	__bc_err_template(BC_ERR_VLAN_ID_USED_BY_OTHER_MODULE, 	"vlan in used by other modules",                       "VLAN 正在被其他模块使用") \
	__bc_err_template(BC_ERR_VLAN_AGG_DEST_OU,       				"vlan agg just support one dest vlan",             "VLAN agg 只支持一个目的vlan") \
	__bc_err_template(BC_ERR_VLAN_AGG_RES_OU,       				"vlan agg resource out",             "VLAN agg 资源耗尽") \
	__bc_err_template(BC_ERR_VLAN_TRANS_RES_OU,       				"vlan trans resource out",           "VLAN trans 资源耗尽") \
	__bc_err_template(BC_ERR_VLAN_TRUNK_RES_OU,       				"vlan trunk resource out",           "VLAN trunk 资源耗尽") \
	__bc_err_template(BC_ERR_VLAN_TRANS_CFL_OTHER,       		"vlan trans config conflict with others",      "VLAN trans和其他vlan配置冲突") \
	__bc_err_template(BC_ERR_VLAN_AGG_CFL_OTHER,       		"vlan agg config conflict with others",      "VLAN agg和其他vlan配置冲突") \
	__bc_err_template(BC_ERR_VLAN_QINQ_CFL_OTHER,       		"vlan qinq config conflict with others",      "VLAN qinq和其他vlan配置冲突") \
	__bc_err_template(BC_ERR_VLAN_QINQ_RES_OU,  					"vlan qinq resource out",            "VLAN qinq 资源耗尽") \
	__bc_err_template(BC_ERR_VLAN_ONU_ID_ERR,						"vlan onu id error",			 	 "VLAN onu ID错误") \
	__bc_err_template(BC_ERR_VLAN_ONU_DRIVER, 						"vlan onu driver not support",			 	 "VLAN onu 驱动不支持") \
	__bc_err_template(BC_ERR_VLAN_ONU_MODE_ERROR,					"vlan onu mode error",			 	 "VLAN onu 模式错误") \
	__bc_err_template(BC_ERR_VLAN_ONU_DOWNLOAD_ALLREADY,			"vlan onu download allready",		 "VLAN onu 配置已下发") \
	__bc_err_template(BC_ERR_VLAN_POOL_FULL,			"vlan pool resource out",		 "VLAN 池资源耗尽") \
	__bc_err_template(BC_ERR_VLAN_POOL_ID_HAS_BEEN_USED,	"vlan pool id has been used",		 "VLAN 池id已经被使用") \
	__bc_err_template(BC_ERR_VLAN_POOL_BIND_IN_PROFILE,	"vlan pool is bind in profile, we can not delete this pool", "VLAN 池绑定在模板上,不能删除vlan池") \
	__bc_err_template(BC_ERR_VLAN_POOL_BIND_IN_PON,		"vlan pool is bind in pon port, we can not delete this pool", "VLAN 池绑定在pon口上,不能删除vlan池") \
	__bc_err_template(BC_ERR_VLAN_POOL_BIND_IN_GLOBAL,	"vlan pool is bind in global, we can not delete this pool", "VLAN 池绑定在全局上,不能删除vlan池") \
	__bc_err_template(BC_ERR_VLAN_POOL_ID_INVALID,	"vlan pool id is invalid", "VLAN 池ID无效") \
	__bc_err_template(BC_ERR_VLAN_POOL_ID_NOT_EXIST,	"vlan pool id not exist", "VLAN 池ID不存在") \
	__bc_err_template(BC_ERR_VLAN_POOL_PROFILE_HAS_BINDED_OTHER_POOL,	"profile has binded other vlan pool", "模板已经绑定了其他的vlan池") \
	__bc_err_template(BC_ERR_VLAN_POOL_PON_HAS_BINDED_OTHER_POOL,	"pon port has binded other vlan pool", "pon 端口已经绑定了其他的vlan池") \
	__bc_err_template(BC_ERR_VLAN_POOL_GLOBAL_HAS_BINDED_OTHER_POOL,	"global has binded other vlan pool", "全局已经绑定了其他的vlan池") \
	__bc_err_template(BC_ERR_VLAN_POOL_CANT_CFG_IN_POOL_MODE,	"just write software config in tag pool mode,onu pvid is not modified", "在tag池模式下只修改软件配置，onu的pvid并没有被修改") 

#define BC_ERR_PORT_TEMPLATE \
	__bc_err_start_template(BC_MODULE_PORT, BC_ERR_PORT_START,    "port error id", 				     "PORT 错误消息开始") \
	__bc_err_template(BC_ERR_PORT_INVALID,			"Input port ID is invalid. etc: intface s1/1-1/3,1/5",		"端口非法，输入格式: etc: intface s1/1-1/3,1/5") \
	__bc_err_template(BC_ERR_PORT_UNI_SET_SUCCESS,	"ONU %d/%d:%d port %d/%d set success",		"ONU %d/%d:%d port %d/%d 设置成功") \
	__bc_err_template(BC_ERR_PORT_UNI_SET_ERROR,	"ONU %d/%d:%d port %d/%d set fail",		"ONU %d/%d:%d port %d/%d 设置失败 ") \
	__bc_err_template(BC_ERR_PORT_PROFILE_UNI_SET_SUCCESS,	"Profile id: %d port %d/%d set success",		"Profile id:%d port %d/%d 设置成功") \
	__bc_err_template(BC_ERR_PORT_PROFILE_UNI_SET_ERROR,	"Profile id:%d port %d/%d set fail",		"Profile id:%d port %d/%d 设置失败 ") \

#define BC_ERR_QOS_TEMPLATE \
	__bc_err_start_template(BC_MODULE_QOS, BC_ERR_QOS_START,    "qos error id", 						"QOS 错误消息开始") \
	__bc_err_template(BC_ERR_QOS_MODE_ERR,       		"qos mode is error",							"QOS 模式错误") \
	__bc_err_template(BC_ERR_QOS_PSG_BACK_PORT,       	"can't set psg backup port",					"不能直接设置PSG备用端口") \
	__bc_err_template(BC_ERR_QOS_WGHT_VALUE_ERR,       	"invalid weight value " ,						"无效权重值") \
	__bc_err_template(BC_ERR_QOS_POLICY_TYPE_ERR,       "qos policy type is unknown", 					"未知qos调度策略") \
	__bc_err_template(BC_ERR_QOS_NOT_SUPPORT_SET_WGHT,	"qos policy type is SP, can't set weight",		"调度策略为SP模式，不需要配置权重") \
	__bc_err_template(BC_ERR_QOS_SDK_CALL,				"call qos sdk failed", 							"调用QOS SDK 返回错误值")\
	__bc_err_template(BC_ERR_QOS_GO_CFG_MODE,			"device based, you must go to CONFIG mode!\r\n", 		"基于设备模式，必须进入全局模式!\r\n")\
	__bc_err_template(BC_ERR_QOS_WEIGHT_VALUE_INVALID,	"error! Input weight list is invalid, List=%s.r\n", 	"错误!!!输入权重列表[%s]是无效的。\r\n")\
	__bc_err_template(BC_ERR_QOS_WRR_INVALID,			"Input WRR[%d]=%d is invalid! must be (%d - %d).\r\n", 	"输入WRR[%d]=%d 无效，必须为(%d - %d!)")\
	__bc_err_template(BC_ERR_QOS_SPWRR_INVALID,			"Input SPWRR[%d]=%d is invalid! must be (%d - %d), ex.(25,25,25,25,0,0,0,0).\r\n", "输入SPWRR[%d]=%d无效, 必须为(%d - %d), 格式(25,25,25,25,0,0,0,0).")\
	__bc_err_template(BC_ERR_QOS_SPWRR_INVALID_0,		"Input SPWRR[%d]=%d is invalid! must be 0, ex.(25,25,25,25,0,0,0,0).\r\n", "输入SPWRR[%d]=%d无效, 后4位必须为0。格式(25,25,25,25,0,0,0,0).")\
	__bc_err_template(BC_ERR_QOS_POLICY_UNKNOWN,		"unknown schedule polcy.", 							"未知调度策略")\


#define BC_ERR_ONU_CLS_TEMPLATE \
	__bc_err_start_template(BC_MODULE_ONU_CLS, BC_ERR_ONU_CLS_START,	  "onu cls error id",			"ONU CLS 错误消息开始")\
	__bc_err_template(BC_ERR_ONU_CLS_SELECT_FIELD,		"you have selected %d field,  but only support %d field !\r\n", 			"选择了 %d 个字段, 最多只支持选择4个匹配字段。\r\n")\


#define BC_ERR_DBA_TEMPLATE \
	__bc_err_start_template(BC_MODULE_DBA, BC_ERR_DBA_START,    "dba error id", 						"DBA 错误消息开始") \
	__bc_err_template(BC_ERR_DBA_PIR_LESS_CIR,  	"PIR must be greater than CIR or equal to CIR",     "PIR必须大于等于CIR") \
	__bc_err_template(BC_ERR_DBA_CIR_LESS_FIR, 		"CIR must be greater than FIR or equal to FIR",     "CIR必须大于等于FIR") \
	__bc_err_template(BC_ERR_DBA_ONU_GET_FAIL,      "get onu information failed",                       "获取onu信息失败") \
	__bc_err_template(BC_ERR_DBA_OUT_OF_PON_RATE,   "the sum of all onu cir > pon rate",                "所有onu CIR和不能超过pon端口速率") \
	__bc_err_template(BC_ERR_DBA_ONU_DOWN,          "the onu is down",                                  "onu不在线") \
	__bc_err_template(BC_ERR_DBA_SDK_CALL,          "call dba sdk failed",                              "调用DBA SDK返回错误值") \


#define BC_ERR_STP_TEMPLATE \
	__bc_err_start_template(BC_MODULE_STP, BC_ERR_STP_START,    	"stp error id", "STP 错误消息开始") \
	__bc_err_template(BC_ERR_STP_NOT_INT,       					"STP is not initialized!", "生成树未开启！") \
	__bc_err_template(BC_ERR_STP_FAIL_INIT,       					"Failed to init IPI mstp!", "初始化 ipi mstp 失败！") \
	__bc_err_template(BC_ERR_STP_BRIDGE_DISABLE, 					"STP module is disabled!", "生成树未使能！") \
	__bc_err_template(BC_ERR_STP_PORT_DISABLE,						"STP port is disable!", "端口未开启生成树！") \
	__bc_err_template(BC_ERR_STP_BPDU_HANDLE,       				"Failed to register bpdu handle!", "注册 bpdu 回调函数失败！") \
	__bc_err_template(BC_ERR_STP_BEINGNESS_CHANGE_HANDLE,			"Failed to register BEINGNESS_CHANGE handle!", "注册 BEINGNESS_CHANGE 回调函数失败！") \
	__bc_err_template(BC_ERR_STP_LINK_CHANGE_HANDLE,				"Failed to register LINK-CHANGE handle!", "注册 LINK-CHANGE 回调函数失败！") \
	__bc_err_template(BC_ERR_STP_TRUNKGROUP_MODIFIED_HANDLE,		"Failed to register TRUNKGROUP handle!", "注册 TRUNKGROUP 回调函数失败！") \
	__bc_err_template(BC_ERR_STP_VLAN_CHANGE_HANDLE,				"Failed to register VLAN-CHANGE handle!", "注册 VLAN-CHANGE 回调函数失败！") \
	\
	__bc_err_template(BC_ERR_STP_IPI_GENERAL,                       "STP GENERAL ERROR!", "生成树调用错误！") \
	\
	__bc_err_template(BC_ERR_STP_IPI_BRIDGE_NOT_FOUND, 				"STP BRIDGE NOT FOUND!", "生成树桥未找到！") \
	__bc_err_template(BC_ERR_STP_IPI_PRIORITY_VALUE_WRONG, 			"STP PRIORITY VALUE WRONG!", "生成树优先级错误！") \
	__bc_err_template(BC_ERR_STP_IPI_PRIORITY_OUTOFBOUNDS, 			"STP PRIORITY OUTOFBOUNDS!", "生成树优先级越界！") \
	__bc_err_template(BC_ERR_STP_IPI_INSTANCE_OUTOFBOUNDS, 			"STP INSTANCE OUTOFBOUNDS!", "生成树 INSTANCE 越界！") \
	__bc_err_template(BC_ERR_STP_IPI_INSTANCE_NOT_FOUND, 			"STP INSTANCE NOT FOUND!", "生成树 INSTANCE 未找到！") \
	__bc_err_template(BC_ERR_STP_IPI_PORT_NOT_FOUND, 				"STP PORT NOT FOUND!", "生成树端口未找到！") \
	__bc_err_template(BC_ERR_STP_IPI_NOT_MSTP_BRIDGE, 				"STP NOT MSTP BRIDGE!", "生成树非 MSTP 模式！") \
	__bc_err_template(BC_ERR_STP_IPI_NOT_RPVST_BRIDGE, 				"STP NOT RPVST BRIDGE!", "生成树非 RPVST 模式！") \
	__bc_err_template(BC_ERR_STP_IPI_RPVST_BRIDGE_NO_VLAN, 			"STP RPVST BRIDGE NO VLAN!", "生成树 RPVST 桥无 VLAN！") \
	__bc_err_template(BC_ERR_STP_IPI_RPVST_BRIDGE_VLAN_EXISTS, 		"STP RPVST BRIDGE VLAN EXISTS!", "生成树 RPVST 桥 VLAN 已存在！") \
	__bc_err_template(BC_ERR_STP_IPI_RPVST_BRIDGE_MAX_VLAN, 		"STP RPVST BRIDGE MAX VLAN!", "生成树 RPVST 桥 VLAN 越界！") \
	__bc_err_template(BC_ERR_STP_IPI_RPVST_NONE, 					"STP RPVST NONE!", "生成树 RPVST NONE！") \
	__bc_err_template(BC_ERR_STP_IPI_RPVST_VLAN_CONFIG_ERR, 		"STP RPVST VLAN CONFIG ERROR!", "生成树 RPVST VLAN 配置错误！") \
	__bc_err_template(BC_ERR_STP_IPI_RPVST_VLAN_MEM_ERR, 			"STP RPVST VLAN MEM ERR!", "生成树 RPVST VLAN MEM 错误！") \
	__bc_err_template(BC_ERR_STP_IPI_RPVST_VLAN_BR_GR_ASSOCIATE, 	"STP RPVST VLAN BRIDGE GR ASSOCIATE!", "生成树 RPVST_VLAN_BR_GR_ASSOCIATE！") \
	__bc_err_template(BC_ERR_STP_IPI_RPVST_VLAN_BR_GR_ADD, 			"STP RPVST VLAN BR GR ADD!", "生成树 RPVST_VLAN_BR_GR_ADD！") \
	__bc_err_template(BC_ERR_STP_IPI_INSTANCE_ALREADY_BOUND, 		"STP INSTANCE ALREADY BOUND!", "生成树 INSTANCE 已绑定！") \
	__bc_err_template(BC_ERR_STP_IPI_INSTANCE_IN_USE_ERR, 			"STP INSTANCE IN USE ERR!", "生成树 INSTANCE 正在使用！") \
	__bc_err_template(BC_ERR_STP_IPI_HELLO_NOT_CONFIGURABLE, 		"STP HELLO-TIME is not configurable in current mode!", "生成树当前模式不支持配置HELLO-TIME！") \
	__bc_err_template(BC_ERR_STP_IPI_BRIDGE_DOESNT_SUPPORT_INST, 	"STP BRIDGE DOES NOT SUPPORT INST!", "生成树桥不支持 INSTANCE！") \
	__bc_err_template(BC_ERR_STP_IPI_PORT_PRIORITY_VALUE_WRONG, 	"STP PORT PRIORITY VALUE WRONG!", "生成树端口优先级错误！") \
	\
	__bc_err_template(BC_ERR_STP_IPI_NOT_SPB_BRIDGE, 				"STP NOT SPB BRIDGE!", "生成树非 SPB 桥！") \
	__bc_err_template(BC_ERR_STP_IPI_NOT_SPBM_BRIDGE, 				"STP NOT SPBM BRIDGE!", "生成树非 SPBM 桥！") \
	__bc_err_template(BC_ERR_STP_IPI_BR_INST_ISID_MAPPED_TO_BVLAN, 	"STP BRIDGE INSTANCE ID MAPPED TO BVLAN!", "生成树桥 INSTANCE 映射到 BVLAN！") \
	__bc_err_template(BC_ERR_STP_IPI_SPB_BRIDGE_PATH_COST, 			"STP SPB BRIDGE PATH COST ERROR!", "生成树 SPB 桥路径开销错误！") \
	\
	__bc_err_template(BC_ERR_STP_IPI_BRIDGE_DOESNT_SUPPORT_SPBM, 	"STP BRIDGE DOESNOT SUPPORT SPBM!", "生成树不支持 SPBM！") \
	__bc_err_template(BC_ERR_STP_IPI_CANT_CREATE_INSTANCE, 			"STP CANNOT CREATE INSTANCE!", "生成树无法创建 INSTANCE！") \
	__bc_err_template(BC_ERR_STP_IPI_BRIDGE_DOESNT_SUPPORT_SPBV, 	"STP BRIDGE DOESNOT SUPPORT SPBV!", "生成树不支持 SPBV！") \
	\
	__bc_err_template(BC_ERR_STP_IPI_VLAN_NOT_IN_COMMON_INSTANCE,	"Cannot add vlan to instance : absent in common instance!", "无法将vlan添加至实例，公共实例不存在该vlan！") \
	\
	__bc_err_template(BC_ERR_STP_DRV_START,       					"STP DRIVER ERROR!", "STP驱动错误！") \
	__bc_err_template(BC_ERR_STP_DRV_BCM_START,       				"STP DRIVER BCM ERROR!", "STP驱动BCM交换芯片模块错误！") \
	__bc_err_template(BC_ERR_STP_DRV_BCM_SDK_CALL,       			"STP DRIVER BCM SDK CALL ERROR!", "STP驱动BCM交换芯片SDK调用错误！") \
	__bc_err_template(BC_ERR_STP_DRV_BCM_STG_INIT,       			"STP DRIVER BCM STG INIT ERROR!", "STP驱动BCM交换芯片STP VLAN组初始化错误！") \
	__bc_err_template(BC_ERR_STP_DRV_BCM_STG_CLEAR,       			"STP DRIVER BCM STG CLEAR ERROR!", "STP驱动BCM交换芯片STP VLAN组清除错误！") \
	__bc_err_template(BC_ERR_STP_DRV_BCM_STG_RESOURCE,       		"STP DRIVER BCM STG RESOURCE ERROR!", "STP驱动BCM交换芯片STP VLAN组资源错误！") \
	__bc_err_template(BC_ERR_STP_DRV_CS_START,       				"STP DRIVER CS ERROR!", "STP驱动CORTINA芯片错误！") \
	__bc_err_template(BC_ERR_STP_END,       						"STP ERROR END!", "STP错误结束！")

#define BC_ERR_STATS_TEMPLATE \
	__bc_err_start_template(BC_MODULE_STATS, BC_ERR_STATS_START,    "stats error id", 				     "STATS 错误消息开始") \
	__bc_err_template(BC_ERR_STATS_PORT_ERROR,       "Invalid port", "端口无效") \
	__bc_err_template(BC_ERR_STATS_15MIN_ENABLE_ERROR,       "Failed! Stats enable of 15 minutes is disable!",                                                 "15分钟统计使能关闭") \
	__bc_err_template(BC_ERR_STATS_24HOUR_ENABLE_ERROR,       "Failed! Stats enable of 24 hours is disable!",                                                 "24小时统计使能关闭") \
	__bc_err_template(BC_ERR_STATS_INDEX_ERROR,       "Failed! The index error!",                                                 "门限配置索引错误") \
	__bc_err_template(BC_ERR_STATS_THRESHOLD_EXIST,       "Failed! The threshold is exist!",                                                 "门限配置已经存在") \
	__bc_err_template(BC_ERR_STATS_THRESHOLD_TYPE_ERROR,       "Failed! The threshold type error!",                                                 "门限类型错误") \
	__bc_err_template(BC_ERR_STATS_DEV_ID_ERROR,       "Failed! Device ID error!",                                                 "设备id错误") \
	__bc_err_template(BC_ERR_STATS_ONU_DEV_ID_ERROR,       "Failed! Onu ID error!",                                                 "ONU id 错误") \
	__bc_err_template(BC_ERR_STATS_PORT_ENABLE_ERROR,       "Failed! Port statistic enable of current is disable!",                                                 "端口使能错误") \
	__bc_err_template(BC_ERR_STATS_DRIVER_ERROR,       "Failed! Driver error!",                                                 "驱动错误") \
	__bc_err_template(BC_ERR_STATS_ONU_OFF_LINE_ERROR,       "Failed! onu off line!",                                                 "ONU不在线")


#define BC_ERR_IGMP_TEMPLATE \
    __bc_err_start_template(BC_MODULE_IGMP, BC_ERR_IGMP_START,    "igmp error id", 				     "IGMP 错误消息开始") \
    __bc_err_template(BC_ERR_IGMP_INIT_FAILED,       "igmp init fail",                               "IGMP初始化失败") \
    __bc_err_template(BC_ERR_IGMP_CFG_VALUE_ERROR,   "igmp cfg err",                           "IGMP配置参数值错误") \
    __bc_err_template(BC_ERR_IGMP_INDEX_ERROR,       "igmp proxy id err",                               "IGMP 代理索引错误") \
    __bc_err_template(BC_ERR_IGMP_INDEX_USED,       "igmp proxy id exist",                               "IGMP代理索引已经使用") \
    __bc_err_template(BC_ERR_IGMP_PROXY_RES_OUT,       "igmp has no valid proxy num",                               "IGMP代理数量超限") \
    __bc_err_template(BC_ERR_IGMP_ONU_ID_ERROR,       "igmp not find onu id",                               "IGMP指定onu_id不存在") \
    __bc_err_template(BC_ERR_IGMP_PROXY_MC_IP_EXIST,       "igmp addr is exist",                               "IGMP组播IP已经存在") \
    __bc_err_template(BC_ERR_IGMP_NO_PROXY_ITEM,       "igmp no proxy item",                               "IGMP无代理条码") \
    __bc_err_template(BC_ERR_IGMP_MC_VID_EQUAL_TO_VLAN_ID,       "igmp proxy vlan equal ucast vlan",                               "IGMP代理vlan不能等于单播vlan") \
    __bc_err_template(BC_ERR_IGMP_VID_EQUAL_TO_MAN_VLAN,       "igmp proxy vlan equal mnmt vlan",                               "IGMP代理vlan不能等于管理vlan") \
    __bc_err_template(BC_ERR_IGMP_PROXY_INDEX_ERROR,       "igmp proxy id err",                               "IGMP代理索引错误") \
    __bc_err_template(BC_ERR_IGMP_PROXY_NOT_EXIST,       "igmp proxy id not exist",                               "IGMP代理索引的条目不存在") \
    __bc_err_template(BC_ERR_IGMP_PROXY_EXIST,       "igmp proxy id exist",                               "IGMP指定代理索引的条目已经存在") \
    __bc_err_template(BC_ERR_IGMP_PROXY_VID_USED,       "igmp vlan already used",                               "IGMP指定代理vid已经使用") \
    __bc_err_template(BC_ERR_IGMP_PROXY_VID_ERROR,       "igmp vlan id err",                               "IGMP指定代理vid错误") \
    __bc_err_template(BC_ERR_IGMP_PROXY_USED,       "igmp proxy is using",                               "IGMP指定代理配置正在使用") \
    __bc_err_template(BC_ERR_IGMP_PROXY_NAME_ERR,       "igmp proxy name err",                               "IGMP代理名称有误") \
    __bc_err_template(BC_ERR_IGMP_MLTCST_RES_OUT,       "igmp num beyond control",                               "IGMP创建onu组播数量超限") \
    __bc_err_template(BC_ERR_IGMP_MLTCST_VLAN_ID_ERROR,       "onu mcast vlan id err",                               "onu组播vlan错误") \
    __bc_err_template(BC_ERR_IGMP_MLTCST_NOT_EXIST,       "onu mcast vlan id not exist",                               "onu组播配置不存在") \
    __bc_err_template(BC_ERR_IGMP_MLTCST_ONU_VLAN_ID_EXIST,       "onu mcast vlan id exist",                               "onu组播vlan已经存在") \
    __bc_err_template(BC_ERR_IGMP_MLTCST_VLAN_ID_NOT_EXIST,       "mcast vlan id not exist",                               "组播vlan不存在") \
    __bc_err_template(BC_ERR_IGMP_MLTCST_PACKAGE_INDEX_ERROR,       "controled mcast package id err",                               "可控组播业务包索引错误") \
    __bc_err_template(BC_ERR_IGMP_MLTCST_PACKAGE_INDEX_EXIST,       "controled mcast package id exist",                               "可控组播业务包索引已经存在") \
    __bc_err_template(BC_ERR_IGMP_MLTCST_PACKAGE_INDEX_NOT_EXIST,       "controled mcast package id not exist",                               "可控组播业务包索引不存在") \
    __bc_err_template(BC_ERR_IGMP_MLTCST_PACKAGE_RES_OUT,       "controled mcast package id beyond control",                               "可控组播业务包数量超限") \
    __bc_err_template(BC_ERR_IGMP_MLTCST_AUTH_INDEX_ERROR,       "mcast user privilege table id err",                               "可控组播用户权限表索引错误") \
    __bc_err_template(BC_ERR_IGMP_MLTCST_AUTH_EXIST,       "mcast user privilege table id exist",                               "可控组播用户权限表条目已经存在") \
    __bc_err_template(BC_ERR_IGMP_MLTCST_AUTH_NOT_EXIST,       "mcast user privilege table id not exist",                               "可控组播用户权限表条目不存在") \
    __bc_err_template(BC_ERR_IGMP_MLTCST_AUTH_RESOURCE_OUT,       "mcast user privilege table num beyond control",                               "可控组播用户权限表数量超限") \
    __bc_err_template(BC_ERR_IGMP_ONU_DEV_ID_ERROR,       "onu id err",                               "onu设备id错误") \
    __bc_err_template(BC_ERR_IGMP_PORT_ID_ERROR,       "port id err",                               "端口错误") \
    __bc_err_template(BC_ERR_IGMP_PORT_ID_EXIST,       "port id exist",                               "端口已经存在") \
    __bc_err_template(BC_ERR_IGMP_PORT_ID_NOT_EXIST,       "port id not exist",                               "端口不存在") \
    __bc_err_template(BC_ERR_IGMP_PAR_ERROR,       "paramter err",                               "参数值有误") \
    __bc_err_template(BC_ERR_IGMP_TARGE_NOT_EXIST,       "igmp init fail",                               "igmp目标不存在") \
    __bc_err_template(BC_ERR_IGMP_DRIVER_ERROR,       "igmp driver err",                               "igmp驱动错误") \
    __bc_err_template(BC_ERR_IGMP_RSP_BIGGER_THAN_QUERY,       "response interval bigger than query interval",                               "查询响应间隔比查询时间间隔大") \
    __bc_err_template(BC_ERR_IGMP_PARAM_ERROR,       "param err",                               "参数错误") \
    __bc_err_template(BC_ERR_IGMP_FUNC_INACTIVE,       "igmp function un support",                               "功能不支持") \
    __bc_err_template(BC_ERR_IGMP_MLTCST_VLAN_ID_EXIST,      "mcast vlan exist",                               "组播vlan已经存在") \
    __bc_err_template(BC_ERR_IGMP_RESOURE,       "have no resouce",                               "IGMP 资源不足")








#define BC_ERR_ALARM_TEMPLATE \
	__bc_err_start_template(BC_MODULE_ALARM, BC_ERR_ALARM_START,    "alarm error id", 				     "ALARM 错误消息开始") \
	__bc_err_template(BC_ERR_ALARM_CODE_ERROR,       "alarm code error.",                                  "告警id错误") \
	__bc_err_template(BC_ERR_ALARM_DEV_ID_ERROR,     "device id error.",                                   "设备id错误") \
	__bc_err_template(BC_ERR_ALARM_POWER_INDEX_ERROR,"power index error.",                                 "电压索引号错误") \
	__bc_err_template(BC_ERR_ALARM_BOARD_INDEX_ERROR,  "board index error.",                                   "板卡索引号错误") \
	__bc_err_template(BC_ERR_ALARM_FAN_INDEX_ERROR,  "fan index error.",                                   "风扇索引号错误") \
	__bc_err_template(BC_ERR_ALARM_OAM_ERROR,        "OAM error.",                                         "OAM 错误") \
	__bc_err_template(BC_ERR_ALARM_PORT_ID_ERROR,    "port error",                                         "端口错误") \
	__bc_err_template(BC_ERR_ALARM_NO_THRESHOLD,     "alarm parameter not support threshold.",              "告警参数不支持门限设置") \
	__bc_err_template(BC_ERR_ALARM_THRESHOLD_ERROR,     "alarm threshold error",              "告警门限错误") \
	__bc_err_template(BC_ERR_ALARM_COMMUNITY_PERMISSION_ERROR,     "snmp community permission error.",              "snmp社区权限错误") \
	__bc_err_template(BC_ERR_ALARM_COMMUNITY_RESOURCE_ERROR,     "snmp community resource error.",              "创建snmp社区数量超限") \
	__bc_err_template(BC_ERR_ALARM_COMMUNITY_NOT_EXIST,     "snmp community not exist.",              "snmp社区不存在") \
	__bc_err_template(BC_ERR_ALARM_COMMUNITY_INDEX_ERROR,     "snmp community index error.",              "snmp社区索引错误") \
	__bc_err_template(BC_ERR_ALARM_EMS_RESOURCE_ERROR,     "snmp ems resource error.",              "创建snmp网管工作站数量超限") \
	__bc_err_template(BC_ERR_ALARM_EMS_INDEX_ERROR,     "snmp ems index error.",              "snmp网管工作站索引错误") \
	__bc_err_template(BC_ERR_ALARM_EMS_NOT_EXIST,     "snmp ems not exist.",              "创建snmp网管工作站不存在")


#define BC_ERR_ACL_TEMPLATE \
	__bc_err_start_template(BC_MODULE_ACL, BC_ERR_ACL_START,    "acl error id", 				     "ACL 错误消息开始") \
	__bc_err_template(BC_ERR_ACL_NAME_USED,       "acl name have been used",                           "ACL名称已经使用") \
	__bc_err_template(BC_ERR_ACL_INSTALLED,       "acl is being used",                           "ACL正在使用") \
	__bc_err_template(BC_ERR_ACL_INSTALLED_SAME_TYPE,       " the same acl type have been installed",                           "重复的ACL类型") \
	__bc_err_template(BC_ERR_ACL_NOT_INSTALLED,       "acl have not been installed",             "ACL没有被绑定到端口") \
	__bc_err_template(BC_ERR_ACL_FIELD_SELEC,       "acl field selection error",       	     "ACL匹配字段错误") \
	__bc_err_template(BC_ERR_ACL_ACTION,       "acl action error",                           "ACL行为错误") \
	__bc_err_template(BC_ERR_ACL_RULE_INVALID,       "acl rule invalid",                     "ACL规则无效") \
	__bc_err_template(BC_ERR_ACL_RULE_REPEATED,       "acl rule is repeated",                     "ACL规则重复") \


#define BC_ERR_MPCP_TEMPLATE \
	__bc_err_start_template(BC_MODULE_MPCP, BC_ERR_MPCP_START,    "mpcp error id", 				     "MPCP 错误消息开始") \
    __bc_err_template(BC_ERR_MPCP_FAILED,              "mpcp cfg fail",                               "MPCP配置失败")

#define BC_ERR_OAM_TEMPLATE \
	__bc_err_start_template(BC_MODULE_OAM, BC_ERR_OAM_START,    "oam error id", 				     "OAM 错误消息开始") \
	__bc_err_template(BC_ERR_OAM_AUTH_OK,       "????",                                                 "????") \
	__bc_err_template(BC_ERR_OAM_AUTH_REJECT,		"Oam onu authorization reject!",			"OAM的ONU认证被拒绝!")\
	__bc_err_template(BC_ERR_OAM_AUTH_DEL_FAIL,		"Oam onu authorization info del fail!",			"OAM的ONU认证信息删除失败!")\
	__bc_err_template(BC_ERR_OAM_AUTH_ENTRY_OUT, "Oam onu authorization entry exceed!",          "OAM的ONU认证条目超限!")\
	__bc_err_template(BC_ERR_OAM_AUTH_MODE, "Oam authorization port mode error!",                "OAM认证端口模式错误!")\
	__bc_err_template(BC_ERR_OAM_PARAM_INVALID,   "Oam parameter invalid",                       "OAM参数非法") \
	__bc_err_template(BC_ERR_OAM_GET_ERROR,       "Failed to get oam parameter!",                    "错误的获取OMA参数!") \
	__bc_err_template(BC_ERR_OAM_SET_ERROR,       "Failed to set oam parameter!",                    "错误的设置OMA参数") \
	__bc_err_template(BC_ERR_OAM_RSP_INCOMPLETE,       "Return is not all of oam response!",            "OMA请求返回不是所有应答!") \
	__bc_err_template(BC_ERR_OAM_RSP_PARA_ERR,       "Parameter of oam is error!",                 "OMA参数错!") \
	__bc_err_template(BC_ERR_OAM_RSP_NOT_FINISHED,       "Oam setting isn't finished!",              "OAM设置无法完成!") \
	__bc_err_template(BC_ERR_OAM_RSP_SUC,       "Successed to response all of oam request!",                 "OAM成功返回所有请求!") \
	__bc_err_template(BC_ERR_OAM_RSP_ERR,       "Failed to response all of oam request!",                 "OAM所有请求都返回失败!") \
	__bc_err_template(BC_ERR_OAM_RSP_PART_ERR,       "Failed to response part of oam request!",                 "OAM请求返回部分失败!")\
	__bc_err_template(BC_ERR_OAM_RSP_TIMEOUT,       "Oam request is timeout!",                 "OAM请求超时失败!")\
	__bc_err_template(BC_ERR_OAM_UPGRADE_UNKNOWN_ERR,       "Oam upgrade is unknown error!!",                 "OAM升级有一个未知错误!")\
	__bc_err_template(BC_ERR_OAM_UPGRADE_NOT_ENOUGH_SPACE,       "Oam upgrade is not enought space!",                 "OAM升级没有足够的空间!")\
	__bc_err_template(BC_ERR_OAM_UPGRADE_INVALID_EXE_OAM,       "Oam upgrade is invalid oam info!",                 "OAM升级收到无效的扩展OAM协议!")\
	__bc_err_template(BC_ERR_OAM_UPGRADE_IGM_EXIST,       "Oam upgrade image is exist!",                 "OAM升级image已经存在!")\
	__bc_err_template(BC_ERR_OAM_UPGRADE_END_RESPONSE,       "Failed to response OAM upgrade end response!",                 "OAM升级End response应答错!")\
	__bc_err_template(BC_ERR_OAM_UPGRADE_IMG_ACTIVATE,       "Failed to response OAM upgrade image activate!",                 "OAM升级Image activate应答错!")\
	__bc_err_template(BC_ERR_OAM_UPGRADE_IMG_COMMIT,       "Failed to response OAM upgrade image commit!",                 "OAM升级Image commit应答错!")\
	__bc_err_template(BC_ERR_OAM_UPGRADE_RX_PROCESSED,       "The OAM of upgrade is already processed!",                 "OAM升级收报已处理!")\
	__bc_err_template(BC_ERR_OAM_SEND_INCOMPLETE,       "Sending OAM is incomplete!",                 "OAM报文发送不完整!")\
	__bc_err_template(BC_ERR_OAM_SEND_COMPLETE,       "Sending OAM is incomplete!",                 "OAM报文完整发送!")


#define BC_ERR_PSG_TEMPLATE \
	__bc_err_start_template(BC_MODULE_PSG, BC_ERR_PSG_START,    "psg error id", 				     "PSG 错误消息开始") \
	__bc_err_template(BC_ERR_PSG_GROUP_FULL,       "Err:The number of psg groups has been the biggest",  "PSG创建组数量已经最大") \
	__bc_err_template(BC_ERR_PSG_PORT_IS_SAME,       "Err:main psg port and backup psg port is same",   "PSG主备端口相同") \
	__bc_err_template(BC_ERR_PSG_PORT_IS_USED,       "Err:psg port is used by other psg group",              "PSG端口已经是PSG端口成员") \
	__bc_err_template(BC_ERR_PSG_GROUP_CREATE_FAIL,       "Err:psg Creation failed",                             "PSG创建失败") \
	__bc_err_template(BC_ERR_PSG_OUT,       "Err:PSG out!",                                                 "PSG 配置超出范围") \
	__bc_err_template(BC_ERR_PSG_INDEX_NOT_EXIST,       "Err:PSG cfg is not exist",            "PSG 配置不存在, 可能已经删除")


#define BC_ERR_MIRROR_TEMPLATE \
	__bc_err_start_template(BC_MODULE_MIRROR, BC_ERR_MIRROR_START,    "mirror error id", 				     "MIRROR 错误消息开始") \
	__bc_err_template(BC_ERR_MIRROR_OUT,       "Failed! Sni mirror session is full!",                                                 "SNI镜像配置超出个数范围") \
	__bc_err_template(BC_ERR_MIRROR_INDEX_NOT_EXIST,       "Failed! Sni mirror session is not exist!",                                                 "SNI 镜像索引不存在 ") \
	__bc_err_template(BC_ERR_MIRROR_INDEX,       "Failed! Sni mirror session error!",                                                 "镜像索引错误") \
	__bc_err_template(BC_ERR_MIRROR_DST_PORT_INVALID,       "Failed! Destination port error!",                                                 "目的端口无效") \
	__bc_err_template(BC_ERR_MIRROR_SRC_PORT_INVALID,       "Failed! Source port error!",                                                 "源端口无效") \
	__bc_err_template(BC_ERR_MIRROR_PORT_OUT,       "Failed! Port num is out of range value!",                                                 "镜像端口数超出范围") \
	__bc_err_template(BC_ERR_MIRROR_DST_SCR_SAME,       "Failed! The mirror destination port is same as source port!",                                                 "目的源相同") \
	__bc_err_template(BC_ERR_MIRROR_DST_PORT_ALREAD_USED,       "Failed! The port is being used",                                                 "源端口已被配置")


#define BC_ERR_TRUNK_TEMPLATE \
	__bc_err_start_template(BC_MODULE_TRUNK, BC_ERR_TRUNK_START,    "trunk error id", 				     "TRUNK 错误消息开始")


#define BC_ERR_P2P_TEMPLATE \
	__bc_err_start_template(BC_MODULE_P2P, BC_ERR_P2P_START,    "p2p error id", 				     "P2P 错误消息开始")


#define BC_ERR_BCMP_TEMPLATE \
	__bc_err_start_template(BC_MODULE_BCMP, BC_ERR_BCMP_START,    "bcmp error id", 				     "BCMP 错误消息开始")	\
	__bc_err_template(BC_ERR_BCMP_RCV_L2_BUF_ERR,       "bcmp recv l2 buf error",                                                 "proxy 从client接收的报文不正确")

#define BC_ERR_CLI_TEMPLATE \
	__bc_err_start_template(BC_MODULE_CLI, BC_ERR_CLI_START,    "cli error id", 				     "CLI 错误消息开始")


#define BC_ERR_SNMP_TEMPLATE \
	__bc_err_start_template(BC_MODULE_SNMP, BC_ERR_SNMP_START,    "snmp error id",								"SNMP 错误消息开始")


#define BC_ERR_TRAP_TEMPLATE \
	__bc_err_start_template(BC_MODULE_TRAP, BC_ERR_TRAP_START,    "trap error id",									"TRAP 错误消息开始")


#define BC_ERR_WEB_TEMPLATE \
	__bc_err_start_template(BC_MODULE_WEB, BC_ERR_WEB_START,    "web error id",									"WEB 错误消息开始")


#define BC_ERR_PLATFROM_TEMPLATE \
	__bc_err_start_template(BC_MODULE_PLATFORM, BC_ERR_PLATFROM_START,    "platform error id",									"PLATFORM 错误消息开始") \
	__bc_err_template(BC_ERR_PLATFROM_THREAD_NOT_EXIST,       "Thread does not exist",						"此线程不存在") \
	__bc_err_template(BC_ERR_PLATFROM_MUTEX_NOT_EXIST,       "mutex  does not exist",						"互斥锁不存在") \
	__bc_err_template(BC_ERR_PLATFROM_SEM_CREATE_FAIL,       "Semaphore creation failed",					"信号量创建失败") \
	__bc_err_template(BC_ERR_PLATFROM_SEM_NOT_EXIST,       "Semaphore  does not exist",					"信号量不存在") \
	__bc_err_template(BC_ERR_PLATFROM_SEM_OP_FAIL,       "Semaphore operation failed",					"信号量操作失败") \
	__bc_err_template(BC_ERR_PLATFROM_QUE_FAILED,       "Queue operation failed",					    "队列操作失败") \
	__bc_err_template(BC_ERR_PLATFROM_SPI_CFG_FAIL,       "SPI configure failed",					    "spi配置失败")


#define BC_ERR_UTILI_TEMPLATE \
	__bc_err_start_template(BC_MODULE_UTILI, BC_ERR_UTILI_START,    "utili error id",									"UTILI 错误消息开始")


#define BC_ERR_PRINT_TEMPLATE \
	__bc_err_start_template(BC_MODULE_PRINT, BC_ERR_PRINT_START,    "print error id",									"PRINT 错误消息开始"	) \
	__bc_err_template(BC_ERR_PRINT_NOT_INIT,       "print module not init", 							"PRINT 模块未初始化"	) \
	__bc_err_template(BC_ERR_PRINT_MDL_ID_EXCEED,       "print module id exceed", 							"PRINT 模块ID号超限") \
	__bc_err_template(BC_ERR_PRINT_FILE_NAME_NO_MATCH,       "print cfg file name no match", 					"PRINT 配置文件名不匹配") \
	__bc_err_template(BC_ERR_PRINT_FILE_NUM_EXCEED,       "print cfg file number exceed", 					"PRINT 配置文件个数超限") \
	__bc_err_template(BC_ERR_PRINT_FILE_LINE_NUM_EXCEED,       "print cfg file line number exceed", 				"PRINT 配置文件行号超限") \
	__bc_err_template(BC_ERR_PRINT_FILE_READ_ERROR,       "print cfg file read data error", 					"PRINT 配置文件读数据错误") \
	__bc_err_template(BC_ERR_PRINT_FILE_WRITE_ERROR,       "print cfg file write data error", 				"PRINT 配置文件写数据错误")


#define BC_ERR_IPC_TEMPLATE \
	__bc_err_start_template(BC_MODULE_IPC, BC_ERR_IPC_START,    "ipc error id",									"IPC 错误消息开始"	) \
	__bc_err_template(BC_ERR_IPC_RECV,       "failed to receive ipc data",						"IPC 接收数据错误") \
	__bc_err_template(BC_ERR_IPC_DATA_INVALID,       "ipc data is invalid",								"IPC 数据无效") \
	__bc_err_template(BC_ERR_IPC_SEND,       "failed to send ipc data",							"IPC 发送数据错误") \
	__bc_err_template(BC_ERR_IPC_SOCKET_CREATE,       "failed to create ipc socket",						"创建IPC通信Socket失败") \
	__bc_err_template(BC_ERR_IPC_PACK_INIT,       "failed to initialization ipc data package",		"初始化IPC数据包失败") \
	__bc_err_template(BC_ERR_IPC_GET_SERVER_PARA,       "failed to get ipc server parameter",				"获取IPC Server参数失败") \
	__bc_err_template(BC_ERR_IPC_CLIENT_CREATE,       "failed to create ipc client",						"创建IPC Client失败") \
	__bc_err_template(BC_ERR_IPC_SERVER_CREATE,       "failed to create ipc server",						"创建IPC Server失败") \
	__bc_err_template(BC_ERR_IPC_PROCESS_HANDER,       "ipc process handler is invalid",					"IPC 处理句柄无效") \
	__bc_err_template(BC_ERR_IPC_SESSION_NO_CREATE,       "ipc session is not created",					    "IPC Session未创建")


#define BC_ERR_SESSION_TEMPLATE \
	__bc_err_start_template(BC_MODULE_SESSION, BC_ERR_SESSION_START,    "session error id",									"SESSION 错误消息开始")


#define BC_ERR_FILESYS_TEMPLATE \
	__bc_err_start_template(BC_MODULE_FS, BC_ERR_FS_START,    "file sys error id",									"FILESYS 错误消息开始")


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


#define BC_ERR_BOARD_TEMPLATE \
	__bc_err_start_template(BC_MODULE_BOARD, BC_ERR_BOARD_START,    "board error id",									"BOARD 错误消息开始")


#define BC_ERR_VFS_TEMPLATE \
	__bc_err_start_template(BC_MODULE_VFS, BC_ERR_VFS_START,    "virtual fs error id",									"VFS 错误消息开始") \
	__bc_err_template(BC_ERR_VFS_MDL_ID_EXCEED,       "????",                                                 "模块id超出范围") \
	__bc_err_template(BC_ERR_VFS_FILENAME_EXCEED,       "????",                                                 "文件名超出范围") \
	__bc_err_template(BC_ERR_VFS_PATH_EXCEED,       "????",                                                 "文件路径超出范围") \
	__bc_err_template(BC_ERR_VFS_CREATE_FAIL,       "????",                                                 "文件创建失败") \
	__bc_err_template(BC_ERR_VFS_OPEN_FAIL,       "????",                                                 "文件打开失败") \
	__bc_err_template(BC_ERR_VFS_CLOSE_FAIL,       "????",                                                 "文件关闭失败") \
	__bc_err_template(BC_ERR_VFS_DELETE_FAIL,       "????",                                                 "文件删除失败") \
	__bc_err_template(BC_ERR_VFS_COPY_FAIL,       "????",                                                 "文件复制失败")


#define BC_ERR_SWAP_TEMPLATE \
	__bc_err_start_template(BC_MODULE_SWAP, BC_ERR_SWAP_START,    "swap error id",									"SWAP 错误消息开始"	) \
	__bc_err_template(BC_ERR_SWAP_TIMER_FAIL,       "swap send tick timer create fail",	"SWAP 发送定时器创建失败")


#define BC_ERR_FDB_TEMPLATE \
	__bc_err_start_template(BC_MODULE_FDB, BC_ERR_FDB_START,     "fdb error id",									"FDB 错误消息开始") \
	__bc_err_template(BC_ERR_FDB_ADD_ST_NOT_SNI,       "just sni port can configure static mac address",                                                 "只有sni口能够配置静态mac地址") \
	__bc_err_template(BC_ERR_FDB_ADD_ST_MUTI_MAC,      "just unicast mac can configure to static mac address",                       "只有单播mac能够配置为静态表项")\
	__bc_err_template(BC_ERR_FDB_MAC_FULL_NOTE,      "configure failed, because table is full!",                       "配置失败，因为表项已满!")\


#define BC_ERR_LOG_TEMPLATE \
	__bc_err_start_template(BC_MODULE_LOG, BC_ERR_LOG_START,    "log error id",									"LOG 错误消息开始") \
	__bc_err_template(BC_ERR_LOG_FILE_OPEN,       "open log file error!",							"打开日志文件错误") \
	__bc_err_template(BC_ERR_LOG_FILE_CREATE,       "create log file error!",							"创建日志文件错误") \
	__bc_err_template(BC_ERR_LOG_GET_DATA,       "get log data error!",								"获取日志数据出错") \
	__bc_err_template(BC_ERR_LOG_WRITE_FAIL,       "write log file error!", 							"写日志文件出错") \
	__bc_err_template(BC_ERR_LOG_OFFSET,       "log file offset error!",							"日志文件偏移出错") \
	__bc_err_template(BC_ERR_LOG_INIT_FAIL,       "log file init fail!",								"日志文件初始化失败"	) \
	__bc_err_template(BC_ERR_LOG_SYS_IPC,       "system log ipc fail!", 							"系统日志进程通信失败") \
	__bc_err_template(BC_ERR_LOG_LVL,       "log level error!",								"日志级别出错")


#define BC_ERR_PBC_TEMPLATE \
	__bc_err_start_template(BC_MODULE_PKT, BC_ERR_PBC_START,    "pkt error id",									"PKT 错误消息开始") \
	__bc_err_template(BC_ERR_PBC_OK,       "????",                                                 "????") \
	__bc_err_template(BC_ERR_PBC_INIT_FAIL,       "????",                                                 "????") \
	__bc_err_template(BC_ERR_PBC_NO_RESOURCE,       "????",                                                 "????") \
	__bc_err_template(BC_ERR_PBC_NOT_SUPPORT,       "????",                                                 "????") \
	__bc_err_template(BC_ERR_PBC_ILLEGAL,           "????",                                                 "????") \
	__bc_err_template(BC_ERR_PBC_8022_LOGIC_PORT,       "????",                                                 "????")


#define BC_ERR_ACCOUNT_TEMPLATE \
	__bc_err_start_template(BC_MODULE_ACCOUNT, BC_ERR_ACCOUNT_START,    "account error id",							"ACCOUNT 错误消息开始")


#define BC_ERR_INTF_TEMPLATE \
	__bc_err_start_template(BC_MODULE_INTF, BC_ERR_INTF_START,    "ip interface error id",						"INTF 错误消息开始") \
	__bc_err_template(BC_ERR_INTF_INBAND_IPADDR_SET,       "inband ipaddr set error id",					"带内ip地址设置出错") \
	__bc_err_template(BC_ERR_INTF_INBAND_NETMASK_SET,       "inband netmask set error id",					"带内子网掩码设置出错") \
	__bc_err_template(BC_ERR_INTF_INBAND_GWAY_SET,       "inband getway set error id",					"带内网关设置出错") \
	__bc_err_template(BC_ERR_INTF_INBAND_VLAN_SET,       "inband vlan set error id",					"带内vlan设置出错"	) \
	__bc_err_template(BC_ERR_INTF_OUTBAND_IPADDR_SET,       "outband ipaddr set error id",					"带外ip地址设置出错") \
	__bc_err_template(BC_ERR_INTF_OUTBAND_NETMASK_SET,       "outband netmask set error id",				"带外子网掩码设置出错") \
	__bc_err_template(BC_ERR_INTF_OUTBAND_GWAY_SET,       "outband getway set error id",					"带外网关设置出错") \
	__bc_err_template(BC_ERR_INTF_INBAND_NET_GET,       "inband network get error id",					"带内参数获取出错") \
	__bc_err_template(BC_ERR_INTF_OUTBAND_NET_GET,       "outband network get error id",				"带外参数获取出错") \
	__bc_err_template(BC_ERR_INTF_INBAND_NET_SAVE,       "????",                                                 "????") \
	__bc_err_template(BC_ERR_INTF_OUTBAND_NET_SAVE,       "????",                                                 "????") \
	__bc_err_template(BC_ERR_INTF_INBAND_GWAY_DEL,       "????",                                                 "????") \
	__bc_err_template(BC_ERR_INTF_OUTBAND_GWAY_DEL,       "????",                                                 "????") \
	__bc_err_template(BC_ERR_INTF_ILLEGALITY_IP_ADDR,   "illegality ip address",                        "非法的ip地址") \
	__bc_err_template(BC_ERR_INTF_CREATE_FAIL,   		"interface create fail",                        "interface创建失败") \
	__bc_err_template(BC_ERR_INTF_NO_EXIST,   			"interface no exist",                           "interface不存在") \
	__bc_err_template(BC_ERR_INTF_NAME_EXIST,   		"interface's name existed",                     "interface名字存在") \
	__bc_err_template(BC_ERR_INTF_NAME_LEN_TOO_LONG,    "interface's name too long",                    "interface名字太长") \
	__bc_err_template(BC_ERR_INTF_INBAND_DEFAULT_VLAN_INTF,    "default vlan interface don't remove",   "默认的interface不能删除") \
	__bc_err_template(BC_ERR_INTF_IP_OR_MASK_CHECK,     "please input interface's ip and mask",   		"请输入IP和掩码") \
	__bc_err_template(BC_ERR_INTF_INBAND_DEFAULT_VLAN_MODIFY, 		"please use command 'management in-band modify vlan <vlan>'", \
																									    "请用命令management in-band modify vlan <vlan>") \
	__bc_err_template(BC_ERR_INTF_INBAND_DEFAULT_VLAN_NOT_EXIST,    "vlan interface 1 don't exist",   	"默认vlan interface 1不存在") \
	__bc_err_template(BC_ERR_INTF_MASK_CHECK,    		"please input the mask",   						"请输入掩码") \
	__bc_err_template(BC_ERR_INTF_SUPPORT_NET_GATEWAY,  "please input the net gateway",   				"请输入网段网关")
																									    

#define BC_ERR_STORMCTRL_TEMPLATE \
	__bc_err_start_template(BC_MODULE_STORMCTRL, BC_ERR_STORMCTRL_START,    "storm control error id",					"STORMCTRL 错误消息开始") \
	__bc_err_template(BC_ERR_STORMCTRL_SNI_SPRSSN_RX_U,       "????",                                                 "????") \
	__bc_err_template(BC_ERR_STORMCTRL_SNI_SPRSSN_U_ENABLE,       "????",                                                 "????") \
	__bc_err_template(BC_ERR_STORMCTRL_SNI_SPRSSN_RX_B,       "????",                                                 "????") \
	__bc_err_template(BC_ERR_STORMCTRL_SNI_SPRSSN_B_ENABLE,       "????",                                                 "????") \
	__bc_err_template(BC_ERR_STORMCTRL_SNI_SPRSSN_RX_M,       "????",                                                 "????") \
	__bc_err_template(BC_ERR_STORMCTRL_SNI_SPRSSN_M_ENABLE,       "????",                                                 "????") \
	__bc_err_template(BC_ERR_STORMCTRL_SNI_SPRSSN_TX_U,       "????",                                                 "????") \
	__bc_err_template(BC_ERR_STORMCTRL_SNI_SPRSSN_TX_B,       "????",                                                 "????") \
	__bc_err_template(BC_ERR_STORMCTRL_SNI_SPRSSN_TX_M,       "????",                                                 "????") \
	__bc_err_template(BC_ERR_STORMCTRL_UNI_SPRSSN_RX_U,       "????",                                                 "????") \
	__bc_err_template(BC_ERR_STORMCTRL_UNI_SPRSSN_RX_B,       "????",                                                 "????")


#define BC_ERR_RATECTRL_TEMPLATE \
	__bc_err_start_template(BC_MODULE_RATECTRL, BC_ERR_RATECTRL_START,    "rate control error id",						"RATECTRL 错误消息开始") \
	__bc_err_template(BC_ERR_RATECTRL_PORT_SET,       "sni rate set failed\r\n",                                                 "sni 速率设置失败\r\n") \
	__bc_err_template(BC_ERR_RATECTRL_OUT_OF_RANGE,       "rate set out of range(1024000KB)\r\n",               "速率设置超出了范围(1024000KB)\r\n") \
	__bc_err_template(BC_ERR_RATECTRL_UNI_RX_SET,       "????",                                                 "????") \
	__bc_err_template(BC_ERR_RATECTRL_UNI_TX_SET,       "????",                                                 "????")\
	__bc_err_template(BC_ERR_RATECTRL_ONU_NOT_SUPPORT,       "only support onu tx rate set",  "只持支onu tx限速")


#define BC_ERR_PORTISO_TEMPLATE \
	__bc_err_start_template(BC_MODULE_PORTISO, BC_ERR_PORTISO_START,    "port isolation error id",					"PORTISO 错误消息开始") \
	__bc_err_template(BC_ERR_PORTISO_SNI_ISOT_SET,       "sni isolation set err\r\n",                                                 "sni口隔离设置错误\r\n") \
	__bc_err_template(BC_ERR_PORTISO_PON_ISOT_SET,       "????",                                                 "????") \
	__bc_err_template(BC_ERR_PORTISO_UNI_ISOT_SET,       "????",                                                 "????")\
	__bc_err_template(BC_ERR_PORTISO_UNI_ISOT_GET,       "failed to get onu isolation",         "获取onu隔离信息失败")


#define BC_ERR_SNTP_TEMPLATE \
	__bc_err_start_template(BC_MODULE_SNTP, BC_ERR_SNTP_START,    "sntp error id",									"SNTP 错误消息开始") \
	__bc_err_template(BC_ERR_SNTP_POLL_REG,      				  "????",                                           "????") \
	__bc_err_template(BC_ERR_SNTP_UNKNOW_STATUS,       			  "sntp unknow status",                             "SNTP 未知状态") \
	__bc_err_template(BC_ERR_SNTP_ENABLE_FAIL,       			  "sntp enable fail",                               "SNTP 使能失败") \
	__bc_err_template(BC_ERR_SNTP_SET_SERVERIP_FAIL,       		  "sntp set server ip fail",                        "SNTP 设置server ip 失败") \
	__bc_err_template(BC_ERR_SNTP_SET_INTERVAL_FAIL,       		  "sntp set interval fail",                         "SNTP 设置时间间隔失败") \
	__bc_err_template(BC_ERR_SNTP_NO_STATUS_FAIL,       		  "sntp recover defualt status fail",               "SNTP 恢复默认状态失败") \
	__bc_err_template(BC_ERR_SNTP_NO_SERVERIP_FAIL,       	      "sntp recover defualt server ip fail",            "SNTP 恢复默认server ip 失败") \
	__bc_err_template(BC_ERR_SNTP_NO_INTERVAL_FAIL,       	      "sntp recover defualt interval fail",             "SNTP 恢复默认时间间隔失败") \
	__bc_err_template(BC_ERR_SNTP_GET_INFORMATION_FAIL, 		  "sntp get config information fail", 			    "SNTP 获取配置信息失败")


#define BC_ERR_ONUMGMT_TEMPLATE \
	__bc_err_start_template(BC_MODULE_ONUMGMT, BC_ERR_ONUMGMT_START,    "onu management error id",														"ONUMGMT 错误消息开始") \
	__bc_err_template(BC_ERR_ONUMGMT_OUT_RANGE,       					"????",                                                	 						"????") \
	__bc_err_template(BC_ERR_ONUMGMT_PROFILE_CREATE,       				"creat profile event send failed",                                              "????") \
	__bc_err_template(BC_ERR_ONUMGMT_PROFILE_DEL,       				"????",                                                 						"????") \
	__bc_err_template(BC_ERR_ONUMGMT_INFO_SHOW,       					"????",                                                 						"????") \
	__bc_err_template(BC_ERR_ONUMGMT_IPADD_SET,       					"????",                                                 						"????") \
	__bc_err_template(BC_ERR_ONUMGMT_IPMASK_SET,      	 				"????",                                                 						"????") \
	__bc_err_template(BC_ERR_ONUMGMT_GWAY_SET,       					"????",                                                 						"????") \
	__bc_err_template(BC_ERR_ONUMGMT_CVLAN_SET,       					"????",                                                 						"????") \
	__bc_err_template(BC_ERR_ONUMGMT_SVLAN_SET,       					"????",                                                 						"????") \
	__bc_err_template(BC_ERR_ONUMGMT_DHCP_SET,       					"????",                                                 						"????") \
	__bc_err_template(BC_ERR_ONUMGMT_BIND_SET,       					"????",                                                 						"????") \
	__bc_err_template(BC_ERR_ONUMGMT_CAN_NOT_UNBIND_ONLINE,       		"you can't unbind online onu",                                     				"不能解绑在线onu") \
	__bc_err_template(BC_ERR_ONUMGMT_UNBIND_SET,       					"drv bind failed",                                                 				"驱动层绑定失败") \
	__bc_err_template(BC_ERR_ONUMGMT_RENAME_SET,       					"????",                                                 						"????") \
	__bc_err_template(BC_ERR_ONUMGMT_REBOOT_SET,       					"onu reboot failed",                                                 			"onu重启失败") \
	__bc_err_template(BC_ERR_ONUMGMT_PRORITY_SET,       				"????",                                                 						"????") \
	__bc_err_template(BC_ERR_ONUMGMT_PROFILE_IPADD_SET,       			"????",                                                 						"????") \
	__bc_err_template(BC_ERR_ONUMGMT_PROFILE_IPMASK_SET,       			"????",                                                 						"????") \
	__bc_err_template(BC_ERR_ONUMGMT_PROFILE_GWAY_SET,       			"????",                                                 						"????") \
	__bc_err_template(BC_ERR_ONUMGMT_PROFILE_CVLAN_SET,       			"????",                                                 						"????") \
	__bc_err_template(BC_ERR_ONUMGMT_PROFILE_SVLAN_SET,       			"????",                                                 						"????") \
	__bc_err_template(BC_ERR_ONUMGMT_PROFILE_BIND_SET,       			"????",                                                 						"????") \
	__bc_err_template(BC_ERR_ONUMGMT_PROFILE_ALREADY_BIND,       		"????",                                                 						"????") \
	__bc_err_template(BC_ERR_ONUMGMT_PROFILE_UNBIND_SET,       			"????",                                                 						"????") \
	__bc_err_template(BC_ERR_ONUMGMT_PROFILE_RENAME_SET,       			"????",                                                 						"????") \
	__bc_err_template(BC_ERR_ONUMGMT_PROFILE_NOT_EMPTY,       			"profile already bind onu，you need unbind onu",                                "模板已经绑定onu，需先解绑模板中所有onu") \
	__bc_err_template(BC_ERR_ONUMGMT_PROFILE_INFO_SET,       			"????",                                                 						"????") \
	__bc_err_template(BC_ERR_ONUMGMT_DRV_INFO_GET,       				"????",                                                 						"????") \
	__bc_err_template(BC_ERR_ONUMGMT_SN_INFO_GET,       				"????",                                                 						"????") \
	__bc_err_template(BC_ERR_ONUMGMT_FW_INFO_GET,       				"????",                                                 						"????") \
	__bc_err_template(BC_ERR_ONUMGMT_ABILITY_INFO_GET,       			"????",                                                 						"????")\
	__bc_err_template(BC_ERR_ONUMGMT_BASE_INFO_INIT,       				"????",                                                 						"????") \
	__bc_err_template(BC_ERR_ONUMGMT_MGMTV4_INFO_SET,       			"????",                                                							"????") \
	__bc_err_template(BC_ERR_ONUMGMT_FEC_ENABLE_SET,       				"????",                                                 						"????") \
	__bc_err_template(BC_ERR_ONUMGMT_ABILITY_FEC_SET,       			"FEC already set",                                                 				"FEC已经设置") \
	__bc_err_template(BC_ERR_ONUMGMT_DOWN_SET,       					"????",                                                 						"????")\
	__bc_err_template(BC_ERR_ONUMGMT_LLID_ALREADY_BIND,      			"llid already bind,need unbind first",                              			"该llid已经绑定，需要先解绑")\
	__bc_err_template(BC_ERR_ONUMGMT_MAC_ALREADY_BIND,       			"mac already bind llid,need unbind first",                          			"该MAC地址已经绑定llid，需要先解绑")\
	__bc_err_template(BC_ERR_ONUMGMT_UPDATE_ONU_BIND_INFO,      		"update onu bind info error",                              						"更新onu绑定信息失败")\
	__bc_err_template(BC_ERR_ONUMGMT_DRV_MPCP_ERROR,      				"drv mpcp bind error",                              							"drv mpcp 绑定错误")\
	__bc_err_template(BC_ERR_ONUMGMT_BIND_ONU_NOT_EXIST,      			"onu not exist,You need bind LLID and MAC first",                              	"ONU不存在,需要进行LLID和MAC的绑定")\
	__bc_err_template(BC_ERR_ONUMGMT_EVENT_SEND_FAIL,      				"event send failed",                              								"事件发送失败")\
	__bc_err_template(BC_ERR_ONUMGMT_MCS_GET_FAIL,      				"get management configuration store info failed",                              	"获取管理存储配置信息失败")\
	__bc_err_template(BC_ERR_ONUMGMT_MCS_SET_FAIL,      				"set management configuration store info failed",                              	"设置管理存储配置信息失败")\
	__bc_err_template(BC_ERR_ONUMGMT_GET_ONU_OPTICAL_FAIL,      		"get onu optical parameter failed",                              				"获取onu光功率参数失败")\
	__bc_err_template(BC_ERR_ONUMGMT_SET_ONU_MNG_FAIL,      			"set drv onu management info failed",                              				"驱动层设置onu管理信息失败")\
	__bc_err_template(BC_ERR_ONUMGMT_IP_ERROR,      					"ip address error",                              								"ip地址错误")\
	__bc_err_template(BC_ERR_ONUMGMT_MASK_ERROR,      					"mask error",                              										"掩码错误")\
	__bc_err_template(BC_ERR_ONUMGMT_GATEWAY_ERROR,      				"gateway error",                              									"网关错误")\
	__bc_err_template(BC_ERR_ONUMGMT_PROFILE_NO_ONU,      				"onu not in the profile",                              							"模板中没有该onu")\
	__bc_err_template(BC_ERR_ONUMGMT_MIN_BIG_MAX,      					"min value biger than max value",                              					"最小值大于最大值")\
	__bc_err_template(BC_ERR_ONUMGMT_DRV_FEC_FAIL,      				"drv set onu fec failed",                              							"驱动层设置onu管理信息失败")\
	__bc_err_template(BC_ERR_ONUMGMT_ONU_NOT_EXIST,      				"onu not exist",                              									"该onu不存在")\
	__bc_err_template(BC_ERR_ONUMGMT_ONU_IDX_INVALID,      				"onu index invalid",                              								"onu索引无效")\
	__bc_err_template(BC_ERR_ONUMGMT_PRO_ID_INVALID,      				"profile id invalid",                              								"模板id无效")\
	__bc_err_template(BC_ERR_ONUMGMT_ERROR_INPUT,      					"error input",                              									"输入错误")\
	__bc_err_template(BC_ERR_ONUMGMT_PRO_NOT_CREATE,      				"profile not create",                              								"模板未创建")\
	__bc_err_template(BC_ERR_ONUMGMT_OAM_GET_CHIP_INFO_FAIL,      		"oam get chipset info false",                              						"OAM获取onu芯片信息失败")\
	__bc_err_template(BC_ERR_ONUMGMT_PROFILE_EXIST,						"profile already exist",														"模板已经存在")\
	__bc_err_template(BC_ERR_ONUMGMT_PROFILE_ERR_RESOURCE,				"err profile resource",															"模板资源不足")\
	__bc_err_template(BC_ERR_ONUMGMT_GET_ONU_INFO_FAILED,				"get onu info failed",															"获取onu信息失败")\
	__bc_err_template(BC_ERR_ONUMGMT_MAC_ADDR_ERROR,					"MAC address error",															"MAC地址错误")\
	__bc_err_template(BC_ERR_ONUMGMT_UPDATE_ONU_MNG_FAILED,				"update onu net info failed",													"获取onu信息失败")\
	__bc_err_template(BC_ERR_ONUMGMT_SET_ONU_MNG_MCS_FAILED,			"set onu net info to management configuration store failed",					"设置onu网络参数到管理配置存储模块失败")\
	__bc_err_template(BC_ERR_ONUMGMT_SET_ONU_FEC_MCS_FAILED,			"set onu fec info to management configuration store failed",					"设置onu fec到管理配置存储模块失败")\
	__bc_err_template(BC_ERR_ONUMGMT_UNBIND_ONU_NOT_EXIST,				"unbind onu not exist",															"解绑的onu不存在")\
	__bc_err_template(BC_ERR_ONUMGMT_ONU_REBOOT_FAIL,					"reboot fail",																	"重启onu失败")\
	__bc_err_template(BC_ERR_ONUMGMT_ONU_LLID_ERROR,					"llid error",																	"错误llid")\
	__bc_err_template(BC_ERR_ONUMGMT_ONU_POWER_OFF,						"onu power off",																"onu断电状态")\
	__bc_err_template(BC_ERR_ONUMGMT_ONU_ALREADY_BIND_THIS_PRO,			"onu already bind this profile",												"onu已经绑定该模板")




#define BC_ERR_PING_TEMPLATE \
	__bc_err_start_template(BC_MODULE_PING, BC_ERR_PING_START,    "ping error id",						"PING 错误消息开始") \
	__bc_err_template(BC_ERR_PING_RECV_FAIL,      				  "ping receive fail", 					"PING 接受数据失败") \
	__bc_err_template(BC_ERR_PING_SIGALRM_HANDLER_SET_FAIL,		  "ping SIGALRM handler set fail",		"PING 告警信号设置失败") \
	__bc_err_template(BC_ERR_PING_SIGINT_HANDLER_SET_FAIL, 	 	  "ping SIGINT handler set fail",		"PING 中断信号设置失败") \
	__bc_err_template(BC_ERR_PING_SETITIMER_SET_FAIL, 	 	  	  "ping setitimer fail",				"PING 定时器设置失败") \
	__bc_err_template(BC_ERR_PING_PRAR_NOT_SUPPORT, 	 	  	  "ping para not support",				"PING 参数不支持")


#define BC_ERR_8022_TEMPLATE \
	__bc_err_start_template(BC_MODULE_8022, BC_ERR_8022_START,    "8022 error id",			"8022 错误消息开始")


#define BC_ERR_SWCHIP_TEMPLATE \
	__bc_err_start_template(BC_MODULE_SWCHIP, BC_ERR_SWCHIP_START,    "switch chip error id",			"SWCHIP 错误消息开始") \
   __bc_err_template(BC_ERR_SWCHIP_SAL_FAIL,       "SDK sal layer fail", 	"SDK SAL层失败") \
   __bc_err_template(BC_ERR_SWCHIP_INIT_ALL_FAIL,  "SDK init all fail", 	"SDK 初始化失败")

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


#define BC_ERR_USERMGMT_TEMPLATE \
	__bc_err_start_template(BC_MODULE_USERMGMT, BC_ERR_USERMGMT_START,    "user mgmt error id",					"USERMGMT 错误消息开始") \
	__bc_err_template(BC_ERR_USERMGMT_UNREG_ERR,       "user unregister error id",                                                 "用户注销错误") \
	__bc_err_template(BC_ERR_USERMGMT_LINKS_NUM_MAX,       "user link num max error id",                                                 "用户连接数上限") \
	__bc_err_template(BC_ERR_USERMGMT_MUTEX_ERR,       "usermgmt mutex error id",                                                 "用户模块互斥销初始失败") \
	__bc_err_template(BC_ERR_USERMGMT_REG_ERR,       "user register error id",                                                 "用户注册错误") \
	__bc_err_template(BC_ERR_USERMGMT_WRITE_ERR,       "user file write error id",                                                 "用户文件写入错误") \
	__bc_err_template(BC_ERR_USERMGMT_READ_ERR,       "user file read error id",                                                 "用户文件读取错误") \
	__bc_err_template(BC_ERR_USERMGMT_CREATE_ERR,       "user file create error id",                                                 "用户文件创建错误") \
	__bc_err_template(BC_ERR_USERMGMT_LVL_ERR,       "user level error id",                                                 "用户权限错误") \
	__bc_err_template(BC_ERR_USERMGMT_NO_EXIST,       "user no exist error id",                                                 "用户不存在") \
	__bc_err_template(BC_ERR_USERMGMT_NO_LOGIN,       "user no lline error id",                                                 "用户不在线") \
	__bc_err_template(BC_ERR_USERMGMT_USER_NUM_MAX,       "user num max error id",                                                 "用户数上限") \
	__bc_err_template(BC_ERR_USERMGMT_REPEAT_REG,       "user repeat register error id",                                                 "用户重复注册") \
	__bc_err_template(BC_ERR_USERMGMT_REPEAT_LOGIN,       "user repeat login error id",                                                 "用户重复登陆") \
	__bc_err_template(BC_ERR_USERMGMT_USER_INFO_ERR,       "user info error id",                                                 "用户信息错误") \
	__bc_err_template(BC_ERR_USERMGMT_SID_UNUSED,       "client sid error id",                                                 "客户端SID错误") \
	__bc_err_template(BC_ERR_USERMGMT_DEFAULT_USER,  "default user error id",                                                "系统用户不可操作")	\
	__bc_err_template(BC_ERR_USERMGMT_MEM_ALLOC,  "usermgmt memory alloction failed",                                                "用户内存分配失败")

#define BC_ERR_TEMP_TEMPLATE \
	__bc_err_start_template(BC_MODULE_TEMP, BC_ERR_TEMP_START,    "user mgmt error id",					"TEMP错误消息开始") \
	__bc_err_template(BC_ERR_TEMP_SLOTID_UNFIT,       "temperature slot id no fit",                                                 "温度板卡未安装") \
	__bc_err_template(BC_ERR_TEMP_SLOTID_NONEXIST,       "temperature slot id nonexist",                                                 "温度板卡无效") 

#define BC_ERR_MEM_TEMPLATE \
	__bc_err_start_template(BC_MODULE_MEM, BC_ERR_MEM_START,    "mem error id",					"MEM 错误消息开始") \
	__bc_err_template(BC_ERR_MEM_SLOTID_UNFIT,       "memory slot id no fit",                                                 "E2PROM板卡未安装") \
	__bc_err_template(BC_ERR_MEM_SLOTID_NONEXIST,       "memory slot id nonexist",                                                 "E2PROM板卡无效") 
	
#define BC_ERR_FAN_TEMPLATE \
	__bc_err_start_template(BC_MODULE_FAN, BC_ERR_FAN_START,    "fan error id",					"FAN 错误消息开始") \
	__bc_err_template(BC_ERR_FAN_LVL_ERR,       "fan lvl error",                                                 "风扇档位错误")	\
	__bc_err_template(BC_ERR_FAN_MOD_ERR,       "fan mode error",                                                 "风扇配置模式错误")	\
	__bc_err_template(BC_ERR_FAN_WRITE_ERR,       "fan write error",                                                 "风扇文件写入错误")	\
	__bc_err_template(BC_ERR_FAN_READ_ERR,       "fan read error",                                                 "风扇文件读取错误")	\
	__bc_err_template(BC_ERR_FAN_CREATE_ERR,       "fan create error",                                                 "风扇文件创建错误")	\
	__bc_err_template(BC_ERR_FAN_MUTEX_ERR,       "fan mutex error",                                                 "风扇互斥锁错误")

#define BC_ERR_PWR_TEMPLATE \
	__bc_err_start_template(BC_MODULE_PWR, BC_ERR_PWR_START,    "pwr error id",					"PWR 错误消息开始") \
	__bc_err_template(BC_ERR_PWR_GET_ERR,       "pwr get info error",                                                 "电源信息获取错误")	\
	__bc_err_template(BC_ERR_PWR_SET_ERR,       "pwr set info error",                                                 "电源配置错误")

#define BC_ERR_LWIP_TEMPLATE \
	__bc_err_start_template(BC_MODULE_LWIP, BC_ERR_LWIP_START,    "lwip error id",					"LWIP 错误消息开始")

#define BC_ERR_L3_TEMPLATE \
	__bc_err_start_template(BC_MODULE_L3, BC_ERR_L3_START,    "l3 error id",					"L3 错误消息开始")

#define BC_ERR_EDFA_TEMPLATE \
	__bc_err_start_template(BC_MODULE_EDFA, BC_ERR_EDFA_START,    "edfa error id",					"EDFA 错误消息开始")


#undef __bc_err_start_template
#define __bc_err_start_template(mod_id, err_id, english_m, chinese_m) err_id = mod_id,

#undef __bc_err_template
#define __bc_err_template(err_id, english_m, chinese_m) err_id,

typedef enum
{
	BC_ERR_COMMON_TEMPLATE
		
	BC_ERR_SYS_TEMPLATE
	BC_ERR_VLAN_TEMPLATE
	BC_ERR_PORT_TEMPLATE 
	BC_ERR_QOS_TEMPLATE
	BC_ERR_ONU_CLS_TEMPLATE
	
	BC_ERR_DBA_TEMPLATE
	BC_ERR_STP_TEMPLATE
	BC_ERR_STATS_TEMPLATE
	BC_ERR_IGMP_TEMPLATE
	BC_ERR_ALARM_TEMPLATE
	
	BC_ERR_ACL_TEMPLATE
	BC_ERR_MPCP_TEMPLATE
	BC_ERR_OAM_TEMPLATE
	BC_ERR_PSG_TEMPLATE
	BC_ERR_MIRROR_TEMPLATE
	
	BC_ERR_TRUNK_TEMPLATE
	BC_ERR_P2P_TEMPLATE
	BC_ERR_BCMP_TEMPLATE
	BC_ERR_CLI_TEMPLATE
	BC_ERR_SNMP_TEMPLATE
	
	BC_ERR_TRAP_TEMPLATE
	BC_ERR_WEB_TEMPLATE
	BC_ERR_PLATFROM_TEMPLATE
	BC_ERR_UTILI_TEMPLATE
	BC_ERR_PRINT_TEMPLATE
	
	BC_ERR_IPC_TEMPLATE
	BC_ERR_SESSION_TEMPLATE
	BC_ERR_FILESYS_TEMPLATE
	BC_ERR_FILETRANS_TEMPLATE
	BC_ERR_BOARD_TEMPLATE
	
	BC_ERR_VFS_TEMPLATE
	BC_ERR_SWAP_TEMPLATE
	BC_ERR_FDB_TEMPLATE
	BC_ERR_LOG_TEMPLATE
	BC_ERR_PBC_TEMPLATE
	
	BC_ERR_ACCOUNT_TEMPLATE
	BC_ERR_INTF_TEMPLATE
	BC_ERR_STORMCTRL_TEMPLATE
	BC_ERR_RATECTRL_TEMPLATE
	BC_ERR_PORTISO_TEMPLATE
	
	BC_ERR_SNTP_TEMPLATE
	BC_ERR_ONUMGMT_TEMPLATE
	BC_ERR_PING_TEMPLATE
	BC_ERR_8022_TEMPLATE
	BC_ERR_SWCHIP_TEMPLATE
	
	BC_ERR_CFGMGMT_TEMPLATE
	BC_ERR_USERMGMT_TEMPLATE
	BC_ERR_TEMP_TEMPLATE
	BC_ERR_MEM_TEMPLATE
	BC_ERR_FAN_TEMPLATE
	
	BC_ERR_PWR_TEMPLATE
	BC_ERR_LWIP_TEMPLATE
	BC_ERR_L3_TEMPLATE
	BC_ERR_EDFA_TEMPLATE
} bc_err_e;

#undef __bc_err_start_template
#undef __bc_err_template


#endif

