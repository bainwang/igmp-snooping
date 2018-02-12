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
	__bc_err_start_template(0, BC_ERR_OK,           						"success", 				                                	"�ɹ�") \
	__bc_err_template(BC_ERR_PARA,               							"parameter error", 				                    		"��������") \
	__bc_err_template(BC_ERR_RESOURCE,            						"resource not enough", 							"��Դ����") \
	__bc_err_template(BC_ERR_NOT_SUPPORT,	       					"not support",                                                   	"��֧��") \
	__bc_err_template(BC_ERR_NOT_FIND, 		  						"not found",                                                      	"û���ҵ�") \
	__bc_err_template(BC_ERR_SEND_FAIL, 							"send fail",                                                       	"����ʧ��") \
	__bc_err_template(BC_ERR_RECV_FAIL, 							"receive fail",                                                   	"����ʧ��") \
	__bc_err_template(BC_ERR_SLOT_ID, 								"slot id error",                                                   	"��λID����") \
	__bc_err_template(BC_ERR_DRV_ACCESS,	      						"driver access error",                                        	"�������ʴ���") \
	__bc_err_template(BC_ERR_FILE_ACCESS,	  						"file access error",                                             	"�ļ����ʴ���") \
	__bc_err_template(BC_ERR_INVALID_INDEX,   						"invalid index",                                                 	"�Ƿ�������") \
	__bc_err_template(BC_ERR_OUT_OF_RANGE,     						"out of range",                                                 	"������Χ") \
	__bc_err_template(BC_ERR_ALREADY_EXSIT,    						"already exsit",                                                 	"�Ѿ�����") \
	__bc_err_template(BC_ERR_NOT_EXSIT, 							"not exsit",                                                        	"������") \
	__bc_err_template(BC_ERR_GET,  									"Error while getting config!",                               	"��ȡ���ó���")\

#define BC_ERR_SYS_TEMPLATE \
	__bc_err_start_template(BC_MODULE_SYSTEM, BC_ERR_SYS_START,    	"sys error id", 				     				"ϵͳ������Ϣ��ʼ")\
	__bc_err_start_template(BC_MODULE_SYSTEM, BC_ERR_SYS_GET_INFO,    	"sys get info error", 				     		"ϵͳ��Ϣ��ȡ����")\


#define BC_ERR_IGMP_TEMPLATE \
    __bc_err_start_template(BC_MODULE_IGMP, BC_ERR_IGMP_START,    	"igmp error id", 				     				"IGMP ������Ϣ��ʼ") \
    __bc_err_template(BC_ERR_IGMP_INIT_FAILED,       					"igmp init fail",                               				"IGMP��ʼ��ʧ��") \
    __bc_err_template(BC_ERR_IGMP_CFG_VALUE_ERROR,   				"igmp cfg err",                           					"IGMP���ò���ֵ����") \
    __bc_err_template(BC_ERR_IGMP_INDEX_ERROR,       					"igmp proxy id err",                               			"IGMP ������������") \
    __bc_err_template(BC_ERR_IGMP_INDEX_USED,       					"igmp proxy id exist",                               			"IGMP���������Ѿ�ʹ��") \
    __bc_err_template(BC_ERR_IGMP_PROXY_RES_OUT,       				"igmp has no valid proxy num",                               	"IGMP������������") \
    __bc_err_template(BC_ERR_IGMP_ONU_ID_ERROR,       					"igmp not find onu id",                               		"IGMPָ��onu_id������") \
    __bc_err_template(BC_ERR_IGMP_PROXY_MC_IP_EXIST,       			"igmp addr is exist",                               			"IGMP�鲥IP�Ѿ�����") \
    __bc_err_template(BC_ERR_IGMP_NO_PROXY_ITEM,       				"igmp no proxy item",                               			"IGMP�޴�������") \
    __bc_err_template(BC_ERR_IGMP_MC_VID_EQUAL_TO_VLAN_ID,       		"igmp proxy vlan equal ucast vlan",                    	"IGMP����vlan���ܵ��ڵ���vlan") \
    __bc_err_template(BC_ERR_IGMP_VID_EQUAL_TO_MAN_VLAN,       		"igmp proxy vlan equal mnmt vlan",             		"IGMP����vlan���ܵ��ڹ���vlan") \
    __bc_err_template(BC_ERR_IGMP_PROXY_INDEX_ERROR,       			"igmp proxy id err",                               			"IGMP������������") \
    __bc_err_template(BC_ERR_IGMP_PROXY_NOT_EXIST,       				"igmp proxy id not exist",                               		"IGMP������������Ŀ������") \
    __bc_err_template(BC_ERR_IGMP_PROXY_EXIST,       					"igmp proxy id exist",                               			"IGMPָ��������������Ŀ�Ѿ�����") \
    __bc_err_template(BC_ERR_IGMP_PROXY_VID_USED,       				"igmp vlan already used",                               		"IGMPָ������vid�Ѿ�ʹ��") \
    __bc_err_template(BC_ERR_IGMP_PROXY_VID_ERROR,       				"igmp vlan id err",                               			"IGMPָ������vid����") \
    __bc_err_template(BC_ERR_IGMP_PROXY_USED,       					"igmp proxy is using",                               			"IGMPָ��������������ʹ��") \
    __bc_err_template(BC_ERR_IGMP_PROXY_NAME_ERR,       				"igmp proxy name err",                               		"IGMP������������") \
    __bc_err_template(BC_ERR_IGMP_MLTCST_RES_OUT,       				"igmp num beyond control",                               	"IGMP����onu�鲥��������") \
    __bc_err_template(BC_ERR_IGMP_MLTCST_VLAN_ID_NOT_EXIST,       		"mcast vlan id not exist",                               		"�鲥vlan������") \
    __bc_err_template(BC_ERR_IGMP_PORT_ID_ERROR,       				"port id err",                               				"�˿ڴ���") \
    __bc_err_template(BC_ERR_IGMP_PORT_ID_EXIST,       					"port id exist",                               				"�˿��Ѿ�����") \
    __bc_err_template(BC_ERR_IGMP_PORT_ID_NOT_EXIST,       			"port id not exist",                               			"�˿ڲ�����") \
    __bc_err_template(BC_ERR_IGMP_PAR_ERROR,       					"paramter err",                              	 			"����ֵ����") \
    __bc_err_template(BC_ERR_IGMP_TARGE_NOT_EXIST,      	 			"igmp init fail",                               				"igmpĿ�겻����") \
    __bc_err_template(BC_ERR_IGMP_DRIVER_ERROR,       					"igmp driver err",                               			"igmp��������") \
    __bc_err_template(BC_ERR_IGMP_RSP_BIGGER_THAN_QUERY,       		"response interval bigger than query interval",     	"��ѯ��Ӧ����Ȳ�ѯʱ������") \
    __bc_err_template(BC_ERR_IGMP_PARAM_ERROR,       					"param err",                               				"��������") \
    __bc_err_template(BC_ERR_IGMP_FUNC_INACTIVE,       				"igmp function un support",                               	"���ܲ�֧��") \
    __bc_err_template(BC_ERR_IGMP_MLTCST_VLAN_ID_EXIST,      			"mcast vlan exist",                               			"�鲥vlan�Ѿ�����") \
    __bc_err_template(BC_ERR_IGMP_RESOURE,       						"have no resouce",                               			"IGMP ��Դ����")


#define BC_ERR_PLATFROM_TEMPLATE \
	__bc_err_start_template(BC_MODULE_PLATFORM, BC_ERR_PLATFROM_START,    "platform error id",						"PLATFORM ������Ϣ��ʼ") \
	__bc_err_template(BC_ERR_PLATFROM_THREAD_NOT_EXIST,       		"Thread does not exist",							"���̲߳�����") \
	__bc_err_template(BC_ERR_PLATFROM_MUTEX_NOT_EXIST,      			"mutex  does not exist",							"������������") \
	__bc_err_template(BC_ERR_PLATFROM_SEM_CREATE_FAIL,       		"Semaphore creation failed",						"�ź�������ʧ��") \
	__bc_err_template(BC_ERR_PLATFROM_SEM_NOT_EXIST,       			"Semaphore  does not exist",					"�ź���������") \
	__bc_err_template(BC_ERR_PLATFROM_SEM_OP_FAIL,       				"Semaphore operation failed",					"�ź�������ʧ��") \
	__bc_err_template(BC_ERR_PLATFROM_QUE_FAILED,       				"Queue operation failed",					    	"���в���ʧ��") \
	__bc_err_template(BC_ERR_PLATFROM_SPI_CFG_FAIL,       			"SPI configure failed",					    		"spi����ʧ��")


#define BC_ERR_UTILI_TEMPLATE \
	__bc_err_start_template(BC_MODULE_UTILI, BC_ERR_UTILI_START,    	"utili error id",									"UTILI ������Ϣ��ʼ")


#define BC_ERR_PRINT_TEMPLATE \
	__bc_err_start_template(BC_MODULE_PRINT, BC_ERR_PRINT_START,    	"print error id",								"PRINT ������Ϣ��ʼ"	) \
	__bc_err_template(BC_ERR_PRINT_NOT_INIT,       					"print module not init", 							"PRINT ģ��δ��ʼ��"	) \
	__bc_err_template(BC_ERR_PRINT_MDL_ID_EXCEED,       				"print module id exceed", 						"PRINT ģ��ID�ų���") \
	__bc_err_template(BC_ERR_PRINT_FILE_NAME_NO_MATCH,       		"print cfg file name no match", 					"PRINT �����ļ�����ƥ��") \
	__bc_err_template(BC_ERR_PRINT_FILE_NUM_EXCEED,       			"print cfg file number exceed", 					"PRINT �����ļ���������") \
	__bc_err_template(BC_ERR_PRINT_FILE_LINE_NUM_EXCEED,       		"print cfg file line number exceed", 				"PRINT �����ļ��кų���") \
	__bc_err_template(BC_ERR_PRINT_FILE_READ_ERROR,       			"print cfg file read data error", 					"PRINT �����ļ������ݴ���") \
	__bc_err_template(BC_ERR_PRINT_FILE_WRITE_ERROR,       			"print cfg file write data error", 					"PRINT �����ļ�д���ݴ���")


#define BC_ERR_VFS_TEMPLATE \
	__bc_err_start_template(BC_MODULE_VFS, BC_ERR_VFS_START,    		"virtual fs error id",								"VFS ������Ϣ��ʼ") \
	__bc_err_template(BC_ERR_VFS_MDL_ID_EXCEED,       				"????",                                                 			"ģ��id������Χ") \
	__bc_err_template(BC_ERR_VFS_FILENAME_EXCEED,       				"????",                                                 			"�ļ���������Χ") \
	__bc_err_template(BC_ERR_VFS_PATH_EXCEED,       					"????",                                                 			"�ļ�·��������Χ") \
	__bc_err_template(BC_ERR_VFS_CREATE_FAIL,       					"????",                                                 			"�ļ�����ʧ��") \
	__bc_err_template(BC_ERR_VFS_OPEN_FAIL,       					"????",                                                 			"�ļ���ʧ��") \
	__bc_err_template(BC_ERR_VFS_CLOSE_FAIL,       					"????",                                                 			"�ļ��ر�ʧ��") \
	__bc_err_template(BC_ERR_VFS_DELETE_FAIL,       					"????",                                                 			"�ļ�ɾ��ʧ��") \
	__bc_err_template(BC_ERR_VFS_COPY_FAIL,       					"????",                                                 			"�ļ�����ʧ��")

#define BC_ERR_LOG_TEMPLATE \
	__bc_err_start_template(BC_MODULE_LOG, BC_ERR_LOG_START,    	"log error id",									"LOG ������Ϣ��ʼ") \
	__bc_err_template(BC_ERR_LOG_FILE_OPEN,       					"open log file error!",							"����־�ļ�����") \
	__bc_err_template(BC_ERR_LOG_FILE_CREATE,       					"create log file error!",							"������־�ļ�����") \
	__bc_err_template(BC_ERR_LOG_GET_DATA,      	 					"get log data error!",							"��ȡ��־���ݳ���") \
	__bc_err_template(BC_ERR_LOG_WRITE_FAIL,       					"write log file error!", 							"д��־�ļ�����") \
	__bc_err_template(BC_ERR_LOG_OFFSET,       						"log file offset error!",							"��־�ļ�ƫ�Ƴ���") \
	__bc_err_template(BC_ERR_LOG_INIT_FAIL,       						"log file init fail!",								"��־�ļ���ʼ��ʧ��"	) \
	__bc_err_template(BC_ERR_LOG_SYS_IPC,      				 		"system log ipc fail!", 							"ϵͳ��־����ͨ��ʧ��") \
	__bc_err_template(BC_ERR_LOG_LVL,       							"log level error!",								"��־�������")

#define BC_ERR_IPC_TEMPLATE \
	__bc_err_start_template(BC_MODULE_IPC, BC_ERR_IPC_START,    		"ipc error id",									"IPC ������Ϣ��ʼ"	) \
	__bc_err_template(BC_ERR_IPC_RECV,       							"failed to receive ipc data",						"IPC �������ݴ���") \
	__bc_err_template(BC_ERR_IPC_DATA_INVALID,       					"ipc data is invalid",							"IPC ������Ч") \
	__bc_err_template(BC_ERR_IPC_SEND,       							"failed to send ipc data",						"IPC �������ݴ���") \
	__bc_err_template(BC_ERR_IPC_SOCKET_CREATE,       				"failed to create ipc socket",						"����IPCͨ��Socketʧ��") \
	__bc_err_template(BC_ERR_IPC_PACK_INIT,       					"failed to initialization ipc data package",			"��ʼ��IPC���ݰ�ʧ��") \
	__bc_err_template(BC_ERR_IPC_GET_SERVER_PARA,       				"failed to get ipc server parameter",				"��ȡIPC Server����ʧ��") \
	__bc_err_template(BC_ERR_IPC_CLIENT_CREATE,       				"failed to create ipc client",						"����IPC Clientʧ��") \
	__bc_err_template(BC_ERR_IPC_SERVER_CREATE,       				"failed to create ipc server",						"����IPC Serverʧ��") \
	__bc_err_template(BC_ERR_IPC_PROCESS_HANDER,       				"ipc process handler is invalid",					"IPC ��������Ч") \
	__bc_err_template(BC_ERR_IPC_SESSION_NO_CREATE,       			"ipc session is not created",					    	"IPC Sessionδ����")

#define BC_ERR_SESSION_TEMPLATE \
	__bc_err_start_template(BC_MODULE_SESSION, BC_ERR_SESSION_START,    "session error id",							"SESSION ������Ϣ��ʼ")

#define BC_ERR_TEST_PROC_TEMPLATE \
	__bc_err_start_template(BC_MODULE_TEST_PROC, BC_ERR_TEST_PROC_START,    "test proc error id",					"TEST PROC ������Ϣ��ʼ")

#define BC_ERR_TEST_TEMPLATE \
	__bc_err_start_template(BC_MODULE_TEST, BC_ERR_TEST_START,    	"test error id",									"TEST ������Ϣ��ʼ")

#define BC_ERR_SNMP_TEMPLATE \
	__bc_err_start_template(BC_MODULE_SNMP, BC_ERR_SNMP_START,    	"snmp error id",								"SNMP ������Ϣ��ʼ")
	
#define BC_ERR_CLI_TEMPLATE \
	__bc_err_start_template(BC_MODULE_CLI, BC_ERR_CLI_START,    		"cli error id", 				     					"CLI ������Ϣ��ʼ")

#define BC_ERR_USERMGMT_TEMPLATE \
	__bc_err_start_template(BC_MODULE_USERMGMT, BC_ERR_USERMGMT_START,    "user mgmt error id",					"USERMGMT ������Ϣ��ʼ") \
	__bc_err_template(BC_ERR_USERMGMT_UNREG_ERR,       				"user unregister error id",                                    	"�û�ע������") \
	__bc_err_template(BC_ERR_USERMGMT_LINKS_NUM_MAX,       			"user link num max error id",                               	"�û�����������") \
	__bc_err_template(BC_ERR_USERMGMT_MUTEX_ERR,       				"usermgmt mutex error id",                               	"�û�ģ�黥������ʼʧ��") \
	__bc_err_template(BC_ERR_USERMGMT_REG_ERR,       				"user register error id",                                        	"�û�ע�����") \
	__bc_err_template(BC_ERR_USERMGMT_WRITE_ERR,       				"user file write error id",                                       	"�û��ļ�д�����") \
	__bc_err_template(BC_ERR_USERMGMT_READ_ERR,       				"user file read error id",                                        	"�û��ļ���ȡ����") \
	__bc_err_template(BC_ERR_USERMGMT_CREATE_ERR,       			"user file create error id",                                    	"�û��ļ���������") \
	__bc_err_template(BC_ERR_USERMGMT_LVL_ERR,       				"user level error id",                                           	"�û�Ȩ�޴���") \
	__bc_err_template(BC_ERR_USERMGMT_NO_EXIST,       				"user no exist error id",                                  		"�û�������") \
	__bc_err_template(BC_ERR_USERMGMT_NO_LOGIN,       				"user no lline error id",                                         	"�û�������") \
	__bc_err_template(BC_ERR_USERMGMT_USER_NUM_MAX,       			"user num max error id",                                      	"�û�������") \
	__bc_err_template(BC_ERR_USERMGMT_REPEAT_REG,       				"user repeat register error id",                          		"�û��ظ�ע��") \
	__bc_err_template(BC_ERR_USERMGMT_REPEAT_LOGIN,       			"user repeat login error id",                                   	"�û��ظ���½") \
	__bc_err_template(BC_ERR_USERMGMT_USER_INFO_ERR,       			"user info error id",                                                 	"�û���Ϣ����") \
	__bc_err_template(BC_ERR_USERMGMT_SID_UNUSED,       			"client sid error id",                                                 	"�ͻ���SID����") \
	__bc_err_template(BC_ERR_USERMGMT_DEFAULT_USER,  				"default user error id",                                       	"ϵͳ�û����ɲ���")	\
	__bc_err_template(BC_ERR_USERMGMT_MEM_ALLOC,  				"usermgmt memory alloction failed",                    	"�û��ڴ����ʧ��")

#define BC_ERR_BINCHIE_TEMPLATE \
	__bc_err_start_template(BC_MODULE_BINCHIE, BC_ERR_BINCHIE_START,    "binchie info error id",						"BINCHIE ������Ϣ��ʼ") \
	__bc_err_template(BC_ERR_BINCHIE_USER_FULL,       				"binchie user full",                                    			"BINCHIE��Ա����") \
	__bc_err_template(BC_ERR_BINCHIE_USER_EMPTY,       				"binchie user empty",                               			"BINCHIE��Ա�ѿ�") \
	__bc_err_template(BC_ERR_BINCHIE_USER_UNLAWFUL,       			"binchie user operation unlawful",                             "BINCHIE��Ա�Ƿ������з���Ա��Ϣ") \
	__bc_err_template(BC_ERR_BINCHIE_USER_DUTY_INVALID,       				"binchie user add duty invalid",                 	"BINCHIE��ԱȨ�޲��Ϸ�") \
	__bc_err_template(BC_ERR_BINCHIE_USER_ALREADY_EXIST,       			"binchie user already exist",                             	"BINCHIE��Ա�Ѵ���") \
	__bc_err_template(BC_ERR_BINCHIE_USER_INEXIST,       				"user user no exist",                                        		"BINCHIE��Ա��������")

#define BC_ERR_FILETRANS_TEMPLATE \
	__bc_err_start_template(BC_MODULE_FILETRANS, BC_ERR_FILETRANS_START,    "filetrans error id",									"FILETRANS ������Ϣ��ʼ"	) \
	__bc_err_template(BC_ERR_FILETRANS_FUN_ERROR,       "failed to source file",									"FILETRANS Դ�ļ�����") \
	__bc_err_template(BC_ERR_FILETRANS_SET_ERROR,       "failed to transfer of information configuration",			"FILETRANS ���ô�����Ϣ����") \
	__bc_err_template(BC_ERR_FILETRANS_PUT_ERROR,       "failed to upload file",									"FILETRANS �ϴ�����") \
	__bc_err_template(BC_ERR_FILETRANS_GET_ERROR,       "failed to download file",									"FILETRANS ���س���") \
	__bc_err_template(BC_ERR_FILETRANS_TRANS_FUN_ERROR,       "failed to trans fun id",									"FILETRANS �ļ����ͳ���"	) \
	__bc_err_template(BC_ERR_FILETRANS_RUNNING,       "failed to file trans running",									"FILETRANS ���ļ����ڴ�����") \
	__bc_err_template(BC_ERR_FILETRANS_WRITE_PARA_ERROR,       "failed to para set error",									"FILETRANS �������ô���") \
	__bc_err_template(BC_ERR_FILETRANS_USB_AREA_NONEXIST,       "failed to usr area get error",									"USB�д�ŵľ����ļ�������") \
	__bc_err_template(BC_ERR_FILETRANS_NAME_INVALID,       "failed to file name invalidr",									"�ļ���������Ч�ַ�") \
	__bc_err_template(BC_ERR_FILETRANS_ACCESS_ERROR,       "????",                                                 "????")

#define BC_ERR_CFGMGMT_TEMPLATE \
	__bc_err_start_template(BC_MODULE_CFGMGMT, BC_ERR_CFGMGMT_START,    "configure mana error id",           "CFGMGMT ������Ϣ��ʼ") \
	__bc_err_template(BC_ERR_CFGMGMT_MEM_ALLOC,       "configuration memory alloction failed!",              "�����ڴ����ʧ��!") \
	__bc_err_template(BC_ERR_CFGMGMT_FILE_CREAT,       "configuration file create failed!",                  "�����ļ�����ʧ��!") \
	__bc_err_template(BC_ERR_CFGMGMT_SAVE,       "configuration file save error!", 	                         "�����ļ��������!") \
	__bc_err_template(BC_ERR_CFGMGMT_MDL_CLR,       "configuration file delete error!",                      "�����ļ��������!") \
	__bc_err_template(BC_ERR_CFGMGMT_FILE_OPEN,       "configuration file open failed!",                     "�����ļ���ʧ��!") \
	__bc_err_template(BC_ERR_CFGMGMT_GET_INFO,       "configuration file get info error!",                   "�����ļ���ȡ��Ϣ����!") \
	__bc_err_template(BC_ERR_CFGMGMT_FILE_NUM_OUT, "configuration file number exceed", 	                     "�����ļ���������!")\
	__bc_err_template(BC_ERR_CFGMGMT_MDL_REG, "failed to configuration module register",                "����ģ��ע��ʧ��!")

#define BC_ERR_STATS_TEMPLATE \
	__bc_err_start_template(BC_MODULE_STATS, BC_ERR_STATS_START,    "configure mana error id",           "STATS ������Ϣ��ʼ") \
	__bc_err_template(BC_ERR_STATS_GET_MUTEX,       "stats get mutex failed!",              "����ͳ�Ʒ��以����ʧ��!") \
	__bc_err_template(BC_ERR_STATS_GET_TEMP,       "stats get temperature failed!",                  "����ͳ��ȡ�¶�ʧ��!") \
	__bc_err_template(BC_ERR_STATS_GET_OAM_PORT,       "stats get oam-port info failed!", 	                         "����ͳ��ȡOAM�˿�ʧ��!") \
	__bc_err_template(BC_ERR_STATS_GET_PORT,       "stats get port info failed!",                      "����ͳ��ȡ�˿�ʧ��!") \
	__bc_err_template(BC_ERR_STATS_GET_PTP_PORT,       "stats get ptp-port info failed!",                     "����ͳ��ȡPTP�˿�ʧ��!") \
	__bc_err_template(BC_ERR_STATS_GET_PTP,       "stats get ptp info failed!",                   "����ͳ��ȡPTP ʧ��!") \
	__bc_err_template(BC_ERR_STATS_GET_VP, "stats get vp info failed!", 	                     "����ͳ��ȡVP ʧ��!")\
	__bc_err_template(BC_ERR_STATS_GET_VC, "stats get vc info failed!", 	                     "����ͳ��ȡVC ʧ��!")\
	__bc_err_template(BC_ERR_STATS_GET_E1, "stats get e1 info failed!", 	                     "����ͳ��ȡE1 ʧ��!")\
	__bc_err_template(BC_ERR_STATS_GET_INFO, "stats get info failed!", 	                     "����ͳ��ȡ��Ϣʧ��!")\
	__bc_err_template(BC_ERR_STATS_GET_CUR_INFO, "stats get cur perf info failed!", 	                     "����ͳ��ȡ��ǰ��Ϣʧ��!")\
	__bc_err_template(BC_ERR_STATS_GET_15MIN_INFO, "stats get 15min info failed!", 	                     "����ͳ��ȡ15������Ϣʧ��!")\
	__bc_err_template(BC_ERR_STATS_GET_24HOUR_INFO, "stats get 24hour info failed!", 	                     "����ͳ��ȡ24Сʱ��Ϣʧ��!")\
	__bc_err_template(BC_ERR_STATS_GET_15MIN_INCREAM_INFO, "stats get 15min incream info failed!", 	                     "����ͳ��ȡ15����������Ϣʧ��!")\
	__bc_err_template(BC_ERR_STATS_GET_24HOUR_INCREAM_INFO, "stats get 24hour incream info failed!", 	                     "����ͳ��ȡ24Сʱ������Ϣʧ��!")\
	__bc_err_template(BC_ERR_STATS_SET_THRESHOLD, "stats set threshold info failed!", 	                     "����ͳ������������Ϣʧ��!")\
	__bc_err_template(BC_ERR_STATS_GET_THRESHOLD, "stats get threshold info failed!",                "����ͳ��ȡ������Ϣʧ��!")


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

