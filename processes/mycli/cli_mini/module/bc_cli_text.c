
/*******************************************************************************
  Copyright (C), 1988-2012, xxxxx Tech. Co., Ltd.
  [File name]  : \\BC\cli\cmds\text.c
  [Author]     : wangbin
  [Version]    : 1.0
  [Date]       : 2012-06-28
  [Description]:

  [Others]     :

  [Function List]:  
    1. ....
    2. ....
  [History]:
	 D a t e    Modification 										  Initials
	---------- --------------                                        ----------
	2012-11-27  Modified                                              yest
	2012-07-02  Modified                                              wangbin
	2012-06-28  Created												  wangbin
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								头   文   件								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_cli_text.h"



////////////////////////////////////////////////////////////////////////////////
//																			  //
//						外 部 变 量、 函 数 引 用							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//																			  //
//						结   构   体   宏   定   义							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
/*
 *		当源文件需要定义宏，而头文件又与其它模块头文件中的宏定义有重复定义嫌疑
 *	时，在此处定义。
 */



////////////////////////////////////////////////////////////////////////////////
//																			  //
//							全 局 变 量 定 义								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
/* 
 *	外部全局变量，提供整个工程调用，在头文件中提供调用接口(外部引用声明)。
 */

#if 0
// bc_cli_menu
const char *bc_cli_menu[CMD_MID_MAXNUM][CMD_ML_MAXNUM] = 
{
	{"获取配置出错！", "Error while api getting!"}, //CMD_MID_ERR_GET
	{"设置出错！", "Error while api setting!"}, //CMD_MID_ERR_SET
	
	{"时区", "zone"}, //CMD_MID_ZONE
	{"年", "year"},//CMD_MID_YEAR
	{"月", "month"}, //CMD_MID_MONTH
	{"日", "day"}, //CMD_MID_DAY
	{"时", "hour"}, //CMD_MID_HOUR
	{"分", "minute"}, //CMD_MID_MINUTE
	{"秒", "second"}, //CMD_MID_SECOND
	
	{"版本信息", "version information"}, //CMD_MID_VERINFO
	{"软件版本", "software version"}, //CMD_MID_SOFTVER
	{"硬件版本", "hardware version"}, //CMD_MID_HARDVER
	{"带内管理", "management inband"}, //CMD_MID_MGNTIN
	{"带外管理", "management outband"}, //CMD_MID_MGNTOUT
	{"物理地址", "mac address"}, //CMD_MID_MACADDR
	{"网络地址", "ip address"}, //CMD_MID_IPADDR
	{"子网掩码", "subnet mask"}, //CMD_MID_NETMASK
	{"网关", "gateway"}, //CMD_MID_GATEWAY
	{"vlan id", "vlan id"}, //CMD_MID_VLANID
	{"优先级", "prority"}, //CMD_MID_PRORITY
	
	{"olt属性", "olt property"}, //CMD_MID_OLTPPT
	{"名称", "name"}, //CMD_MID_NAME
	{"类型", "type"}, //CMD_MID_TYPE
	{"主控板", "control board"}, //CMD_MID_TYPE_BDCTRL
	{"GE EPON 板", "GE EPON board"}, //CMD_MID_TYPE_BDGEPON
	{"上联板", "uplink board"}, //CMD_MID_TYPE_BDUPLINK
	{"交换板", "switch board"}, //CMD_MID_TYPE_BDSWITCH
	{"未知类型板卡", "others"}, //CMD_MID_TYPE_BDOTHER
	{"板卡未插入", "vacant"}, //CMD_MID_TYPE_BDVACANT
	{"管理状态", "admin status"}, //CMD_MID_ADMINSTA
	{"设备在线", "up"}, //CMD_MID_STA_UP
	{"设备下线", "down"}, //CMD_MID_STA_DOWN
	{"设备测试", "testing"}, //CMD_MID_STA_TESTING
	{"运行时长", "up time"}, //CMD_MID_UPTIME
	{"业务卡槽位数", "number of service slot"}, //CMD_MID_SRVSLOTS
	{"电源卡槽位数", "number of power slot"}, //CMD_MID_POWERSLOTS
	{"风扇卡槽位数", "number of fan slot"}, //CMD_MID_FANSLOTS
	{"设备类型", "device style"}, //CMD_MID_DEVSTYLE
	{"固定盒式", "fixed"}, //CMD_MID_STYLE_FIXED
	{"机架式", "chassis based"}, //CMD_MID_STYLE_CHASSIS
	{"其它类型", "others"}, //CMD_MID_STYLE_OTHER
		
	{"板卡信息", "board information"}, //CMD_MID_BDINFO
	{"槽", "slot"}, //CMD_MID_SLOT
	{"主备冗余状态", "main/back redundance"}, //CMD_MID_MAINBACK
	{"主用板卡", "active"}, //CMD_MID_MB_ACT
	{"备用板卡", "stand by"}, //CMD_MID_MB_STBY
	{"独立板卡", "stand alone"}, //CMD_MID_MB_STAL
	{"不支持主备冗余", "not applicable"}, //CMD_MID_MB_NOTAP
	{"固件版本", "fireware version"}, //CMD_MID_FIRMVER
	{"告警状态", "alarm status"}, //CMD_MID_WARNSTA
	{"无告警", "none"}, //CMD_MID_WARN_NONE
	{"紧急", "critical"}, //CMD_MID_WARN_CRITICAL
	{"严重", "major"}, //CMD_MID_WARN_MAJOR
	{"轻微", "minor"}, //CMD_MID_WARN_MINOR
	{"警告", "warning"}, //CMD_MID_WARN_WARNING
	{"序列号", "serial no"}, //CMD_MID_SERIALNO
	{"槽位状态", "slot status"}, //CMD_MID_SLOTSTA
	{"已安装", "installed"}, //CMD_MID_SLOTSTA_INSTALL
	{"未安装", "uninstalled"}, //CMD_MID_SLOTSTA_UNINSTALL
	{"其它状态", "others"}, //CMD_MID_SLOTSTA_OTHERS

	{"MAC 地址学习表", "mac address table"}, //CMD_MID_MAT
	{"端口", "port"}, //CMD_MID_PORT
	{"s", "s"}, //CMD_MID_PORT_OLTSNI
	{"p", "p"}, //CMD_MID_PORT_OLTPON
	{"p", "p"}, //CMD_MID_PORT_ONUPON
	{"u", "u"}, //CMD_MID_PORT_ONUUNI
	{"t", "t"}, //CMD_MID_PORT_OLTTRUNK
	{"c", "c"}, //CMD_MID_PORT_OLTCPU
	{"m", "m"}, //CMD_MID_PORT_OLTMII
	{"动态", "dynamic"}, //CMD_MID_DYNAMIC
	{"静态", "static"}, //CMD_MID_STATIC
	
	{"风暴抑制信息", "storm control informatioin"}, //CMD_MID_STORMCTRL
	{"未知单播", "unknown unicast"}, //CMD_MID_UNICAST
	{"组播", "multicast"}, //CMD_MID_MULTI
	{"广播", "broadcast"}, //CMD_MID_BROAD
	{"打开", "enable"}, //CMD_MID_ENABLE
	{"关闭", "disable"}, //CMD_MID_DISABLE
	{"状态", "state"},//CMD_MID_STATE
	{"入口", "ingress"}, //CMD_MID_INGRESS
	{"出口", "egress"}, //CMD_MID_EGRESS	
	{"接收字节速率", "Receive Byte Rate"}, //CMD_MID_INGRESS_RATE
	{"发送字节速率", "Transmit Byte Rate"}, //CMD_MID_EGRESS_RATE
	{"位/秒", "bps"}, //CMD_MID_BPS
	{"千位/秒", "kbps"}, //CMD_MID_KBPS	
	{"字节/秒", "Bytes/s"}, //CMD_MID_BYTES_PS
	
	{"端口镜像信息", "port mirror information"}, //CMD_MID_MIRROR
	{"组", "session"}, //CMD_MID_SESSION
	{"源", "source"}, //CMD_MID_SOURCE
	{"目的", "destination"}, //CMD_MID_DESTINATION
//sni	
	{"sni口信息", "sni information"}, //CMD_MID_SNI_INFO
	
	{"combo模式", "combo mode"}, //CMD_MID_SNI_COMBO_MODE
	{"介质类型", "media type"}, //CMD_MID_SNI_MEDIA_TYPE
	{"铜轴线", "copper"}, //CMD_MID_MEDIA_COPPER
	{"光纤", "fiber"}, //CMD_MID_MEDIA_FIBER
	{"自动", "auto"}, //CMD_MID_MEDIA_AUTO
	{"其它介质", "others"}, //CMD_MID_MEDIA_OTHER
	{"自适应使能", "auto negotiation enable"}, //CMD_MID_AUTO_NEGO_ENABLE
	{"自适应状态", "auto negotiation status"}, //CMD_MID_AUTO_NEGO_STA
	{"自适应模式", "auto negotiation mode"}, //CMD_MID_AUTO_NEGO_MODE
	{"自动", "auto"}, //CMD_MID_AN_AUTO
	{"10M半双工", "half-10"}, //CMD_MID_AN_H10
	{"10M全双工", "full-10"}, //CMD_MID_AN_F10
	{"100M半双工", "half-100"}, //CMD_MID_AN_H100
	{"100M全双工", "full-100"}, //CMD_MID_AN_F100
	{"1G全双工", "full-1000"}, //CMD_MID_AN_F1000
	{"10G全双工", "full-10000"}, //CMD_MID_AN_F10000
	{"最后修改时间", "last change time"}, //CMD_MID_LAST_CHG_TIME
	{"link up", "link up"}, //CMD_MID_LINK_UP
	{"link down", "link down"}, //CMD_MID_LINK_DOWN	
	{"端口使能", "port enable"}, //CMD_MID_PORT_ENABLE
	{"端口MAC", "port MAC"}, //CMD_MID_PORT_MAC	
	{"STP使能", "STP enable"}, //CMD_MID_STP_ENABLE
//pon	
	{"pon口信息", "pon information"}, //CMD_MID_PON_INFO	
	{"pon口加密信息", "pon crypto information"}, //CMD_MID_PON_CRYPTO_INFO
	{"最大支持ONU数", "max onu num support"}, //CMD_MID_MAX_ONU
	{"在线ONU数", "up onu num "}, //CMD_MID_UP_ONU
	{"加密使能", "encrypt enable"}, //CMD_MID_ENCRYPT_ENABLE
	{"加密模式", "encrypt mode"}, //CMD_MID_ENCRYPT_MODE
	{"未加密", "none"}, //CMD_MID_ENCRYPT_MODE_NONE
	{"AES32", "AES32"}, //CMD_MID_ENCRYPT_MODE_AES32
	{"AES48", "AES48"}, //CMD_MID_ENCRYPT_MODE_AES48
	{"AES128", "AES128"}, //CMD_MID_ENCRYPT_MODE_AES128
	{"三层搅动", "ctc triple churning"}, //CMD_MID_ENCRYPT_MODE_CTCTRIPLECHURNING
	{"其它加密类型", "others"}, //CMD_MID_ENCRYPT_MODE_OTHER
	{"密钥交换时间", "encrypt key exchange time"}, //CMD_MID_ENCRYPT_KEY_EXCHANGE_TIME
	{"隔离功能使能", "isolation enable"}, //CMD_MID_ISOLATION_EN
	{"流量控制", "flow control"}, //CMD_MID_FLOW_CONTROL_EN
	{"环路检测", "loopback detect "}, //CMD_MID_LOOPBACK_DETECT_EN
	{"下行最大带宽", "downstream bandwidth max"}, //CMD_MID_DS_BANDWIDTH_MAX
	{"下行实际使用带宽", "downstream bandwidth in use"}, //CMD_MID_DS_BANDWIDTH_INUSE
	{"下行剩余带宽", "downstream bandwidth remain"}, //CMD_MID_DS_BANDWIDTH_REMAIN
	{"15分钟性能统计使能", "perf stats in 15 minutes"}, //CMD_MID_15M_EN
	{"24小时性能统计使能", "perf stats in 24 hours"}, //CMD_MID_24H_EN
	{"mac地址学习表最大学习数", "max. of mac learning"}, //CMD_MID_MACADDR_LEARN_MAXNUM
	{"上行最大带宽", "up stream bandwidth max"}, //CMD_MID_UP_BANDWIDTH_MAX
	{"上行实际使用带宽", "downstream bandwidth in use"}, //CMD_MID_UP_BANDWIDTH_INUSE
	{"上行剩余带宽", "up stream bandwidth remain"}, //CMD_MID_UP_BANDWIDTH_REMAIN
//acl	
	{"acl 规则", "acl rule"}, //CMD_MID_ACL_RULE_INFO
	{"允许", "permit"}, //CMD_MID_ACL_RULE_PERMIT
	{"拒绝", "deny"}, //CMD_MID_ACL_RULE_DENY
	{"标记", "mark"}, //CMD_MID_ACL_RULE_MARK	

	{"acl链表信息", "acl list information"}, //CMD_MID_ACL_LIST_INFO
	{"ip", "ip"}, //CMD_MID_ACL_IP
	{"access-list", "access-list"}, //CMD_MID_ACL_ACL
	{"ACL类型", "acl type"}, //CMD_MID_ACL_TYPE
	{"standard", "standard"}, //CMD_MID_ACL_TYPE_STD
	{"extended", "extended"}, //CMD_MID_ACL_TYPE_EXTEND
	{"expert", "expert"}, //CMD_MID_ACL_TYPE_EXPERT_EXTEND
	
	{"acl组信息", "acl group information"}, //CMD_MID_ACL_GROUP_INFO
	{"入口方向的acl", "acl for ingress"}, //CMD_MID_ACL_INGRESS
	{"出口方向的acl", "acl for egress"}, //CMD_MID_ACL_EGRESS
	{"无", "no acl"}, //CMD_MID_ACL_NO_ACL

	{"动态带宽控制信息", "dynamic bandwidth access info"}, //CMD_MID_SLA_INFO
	{"llid", "llid"}, //CMD_MID_ONU_LLID
	{"下行固定带宽", "down stream fixed bandwidth"}, //CMD_MID_DS_FIXED
	{"下行峰值带宽", "down stream peek bandwidth"}, //CMD_MID_DS_PEEK
	{"下行保证带宽", "down stream committed bandwidth"}, //CMD_MID_DS_COMMITTED
	{"上行固定带宽", "up stream fixed bandwidth"}, //CMD_MID_US_FIXED
	{"上行峰值带宽", "up stream peek bandwidth"}, //CMD_MID_US_PEEK
	{"上行保证带宽", "up stream committed bandwidth"}, //CMD_MID_US_COMMITTED
//vlan
	{"vlan全局信息", "vlan global information"}, //CMD_MID_VLAN_GBL_INFO
	{"最大vlan id", "max vlan id"}, //CMD_MID_VLAN_ID_MAX
	{"最多支持的vlan个数", "max supported vlan numbers"}, //CMD_MID_VLAN_NUM_MAX
	{"已创建的vlan个数", "created vlan numbers"}, //CMD_MID_VLAN_NUM_CREATED
	{"svlan tpid", "svlan tpid"}, //CMD_MID_VLAN_SVLAN_TPID
	
	{"vlan配置信息", "vlan config information"}, //CMD_MID_VLAN_CFG_INFO
	{"vlan名称", "vlan name"}, //CMD_MID_VLAN_NAME
	{"vlan tagged 端口", "vlan tagged port"}, //CMD_MID_VLAN_TAG
	{"vlan untagged 端口", "vlan untagged port"}, //CMD_MID_VLAN_UNTAG	

	{"端口vlan信息", "port vlan information"}, //CMD_MID_VLAN_PORT_INFO
	{"vlan协议标识", "vlan tag tpid"}, //CMD_MID_VLAN_TAGTPID
	{"vlan规格格式指示符", "vlan tag cfi"}, //CMD_MID_VLAN_TAGCFI
	{"vlan优先级", "vlan priority"}, //CMD_MID_VLAN_PRIORITY
	{"端口vlan id", "port vlan id"}, //CMD_MID_VLAN_PVID
	{"vlan模式", "vlan mode"}, //CMD_MID_VLAN_MODE
	{"透传模式", "transparent mode"}, //CMD_MID_VLAN_MODE_TRANSPARENT
	{"tag模式", "tag mode"}, //CMD_MID_VLAN_MODE_TAG
	{"翻译模式", "translation mode"}, //CMD_MID_VLAN_MODE_TRANSLATION
	{"聚合模式", "aggregation mode"}, //CMD_MID_VLAN_MODE_AGGREGATION
	{"trunk 模式", "trunk mode"}, //CMD_MID_VLAN_MODE_TRUNK
	{"access 模式", "access mode"}, //CMD_MID_VLAN_MODE_ACCESS
	{"qinq模式", "qinq mode"}, //CMD_MID_VLAN_MODE_STACKING
	{"svlan trunk 模式", "svlan trunk mode"}, //CMD_MID_VLAN_MODE_STRUNK
	{"vlan类型", "vlan type"}, //CMD_MID_VLAN_TYPE
	{"cvlan", "cvlan"}, //CMD_MID_VLAN_TYPE_CVLAN
	{"svlan", "svlan"}, //CMD_MID_VLAN_TYPE_SVLAN
	{"configure failed, because entry is full !", "配置失败，因为表项已经配满!"}, //CMD_MID_VLAN_FULL_NOTE
//igmp
	{"igmp 信息", "igmp information"}, //CMD_MID_IGMP_INFO	
	{"igmp 使能", "igmp enable"}, //CMD_MID_IGMP_ENABLE
	{"igmp 模式", "igmp mode"}, //CMD_MID_IGMP_MODE
	{"centralized 模式", "centralized mode"}, //CMD_MID_IGMP_MODE_CENTRALIZED
	{"distributewithcm 模式", "distributewithcm mode"}, //CMD_MID_IGMP_MODE_DISTRIBUTEWITHCM
	{"关闭", "disable mode"}, //CMD_MID_IGMP_MODE_DISABLED
	{"distributedwocm 模式", "distributedwocm mode"}, //CMD_MID_IGMP_MODE_DISTRIBUTEDWOCM
	{"igmp最大应答时间", "igmp max query response time"}, //CMD_MID_IGMP_MAXQUERESTIME
	{"igmp强壮度", "igmp robust"}, //CMD_MID_IGMP_ROBUST
	{"igmp请求间隔时间", "igmp query interval"}, //CMD_MID_IGMP_QUEINTERVAL
	{"igmp最后组员请求间隔时间", "igmp last member query interval"}, //CMD_MID_IGMP_LASTMEMQUEINTERVAL
	{"igmp最后组员请求计数器", "igmp last member query count"}, //CMD_MID_IGMP_LASTMEMQUECOUNT
	{"igmp版本", "igmp version"}, //CMD_MID_IGMP_VERSION	
	
	{"igmp代理组信息", "igmp proxy information"}, //CMD_MID_IGMP_PROXY_GROUP_INFO
	{"igmp代理名称", "igmp proxy name"}, //CMD_MID_IGMP_PROXY_GROUP_NAME
	{"igmp代理源ip", "igmp proxy source ip"}, //CMD_MID_IGMP_PROXY_GROUP_SRCIP
	{"igmp代理组播vlan号", "igmp proxy multicast vlan id"}, //CMD_MID_IGMP_PROXY_GROUP_MCASTVID
	{"igmp代理组播ip地址", "igmp proxy multicast ip"}, //CMD_MID_IGMP_PROXY_GROUP_MCASTIP
	{"igmp代理组播保证带宽", "igmp proxy multicast assured bandwidth"}, //CMD_MID_IGMP_PROXY_GROUP_MCASTABW
	{"igmp代理组播最大带宽", "igmp proxy multicast max bandwidth"}, //CMD_MID_IGMP_PROXY_GROUP_MCASTMBW
	{"igmp 转发表", "igmp forwarding table"}, //CMD_MID_IGMP_FWD_INFO
//file
	{"配置文件传输参数 - 上传", "configure file transfer information - upload"}, //CMD_MID_FILE_CFG_UP_INFO
	{"配置文件传输参数 - 下载", "configure file transfer information - download"}, //CMD_MID_FILE_CFG_DOWN_INFO
	{"系统内核更新参数", "system kernel upgrade information"}, //CMD_MID_FILE_KERNEL_INFO
	{"文件系统更新参数", "filesystem upgrade information"}, //CMD_MID_FILE_FILESYS_INFO
	{"olt更新参数", "olt upgrade information"}, //CMD_MID_FILE_OLT_INFO
	
	{"协议类型", "protocol type"}, //CMD_MID_FILE_TRAN_PROTOCOL
	{"服务器ip", "server ip address"}, //CMD_MID_FILE_TRAN_IP
	{"用户名", "user name"}, //CMD_MID_FILE_TRAN_USRNAME
	{"密码", "password"}, //CMD_MID_FILE_TRAN_USRPWD
	{"源文件", "source file(include path)"}, //CMD_MID_FILE_TRAN_SRC
	{"目的文件", "destination file(include path)"}, //CMD_MID_FILE_TRAN_DST
	{"状态", "status"}, //CMD_MID_FILE_TRAN_STA
	{"空闲", "idle"}, //CMD_MID_FILE_TRAN_STA_IDLE
	{"正在传输", "in progress"}, //CMD_MID_FILE_TRAN_STA_PROCESS
	{"传输成功", "success"}, //CMD_MID_FILE_TRAN_STA_SUCCESS
	{"传输失败", "failure"}, //CMD_MID_FILE_TRAN_STA_FAILED	
	{"升级资源不存在", "No Resource"}, //CMD_MID_FILE_TRAN_STA_NO_RESOURCE	
	{"强制停止ONU升级成功.", "stop onu tftp success!"}, //CMD_MID_FILE_TRAN_STA_STOP_SUCCESS
//sntp
	{"网络时间同步", "SNTP information"}, //CMD_MID_SNTP_INFO
	{"开关状态", "state"}, //CMD_MID_SNTP_STA
	{"同步服务器", "sync server"}, //CMD_MID_SNTP_SERVER
	{"同步间隔", "sync interval"}, //CMD_MID_SNTP_INTERVAL
	{"时区", "zone"}, //CMD_MID_SNTP_ZONE
//onu
    {"在线", "on line"}, //CMD_MID_ON_LINE
	{"离线", "off line"}, //CMD_MID_OFF_LINE
	{"onu信息列表", "onu list information"}, //CMD_MID_ONU_LIST_INFO
	{"onu id", "onu id"}, //CMD_MID_ONU_ID
	{"Mac 老化时间", "Mac aging time"}, //CMD_MID_ONU_MAC_AGING
	{"芯片厂家", "chip vendor"}, //CMD_MID_ONU_CHIP_VENDOR
	{"芯片型号", "chip type"}, //CMD_MID_ONU_CHIP_TYPE
	{"芯片版本", "chip version"}, //CMD_MID_ONU_CHIP_VER
	{"软件版本", "software version"}, //CMD_MID_ONU_SFTWR_VER
	{"固件版本", "firmware version"}, //CMD_MID_ONU_FRMWR_VER
	{"距离", "distance"}, //CMD_MID_ONU_DISTANCE
	{"注册时间", "register time"}, //CMD_MID_ONU_REG_TIME
	{"onu 模板", "profile"},//CMD_MID_ONU_PROFILE
	{"优先级", "priority"}, //CMD_MID_PRIORITY
	{"Trap IP", "Trap IP"}, //CMD_MID_ONU_TRAP_IP
	{"掉电", "down"}, //CMD_MID_POWER_DOWN
	{"认证拒绝", "auth reject"}, //CMD_MID_ONU_STATUS_AUTH_REJECT

	{"自动获取ip地址", "DHCP"}, //CMD_MID_DHCP
	{"是", "yes"}, //CMD_MID_YES
	{"否", "no"}, //CMD_MID_NO
	{"绑定mac", "Bind mac"}, //CMD_MID_BIND_MAC
	{"共有 %u 项。\r\n", "there are %u entries.\r\n"}, //CMD_MID_THERE_ARE
	{"onu", "onu"}, //CMD_MID_ONU
	
	{"ONU的PON端口光传输属性", "onu optical trans information"}, //CMD_MID_ONU_OPT_TRANS_INFO
	{"光接收功率", "received optical power"}, //CMD_MID_ONU_OPT_REC_POWER
	{"光发射功率", "transmitted optical power"}, //CMD_MID_ONU_OPT_TRANS_POWER
	{"偏置电流", "bias current"}, //CMD_MID_ONU_BIAS_CURRENT
	{"工作电压", "working voltage"}, //CMD_MID_ONU_WORK_V
	{"工作温度", "working temparature"}, //CMD_MID_ONU_WORK_T
	{"fec使能", "fec enable"}, //CMD_MID_FEC_ENABLE
	
	{"ONU的容量能力", "onu capability information"}, //CMD_MID_ONU_CAP_INFO
	{"GE数", "GE port num"}, //CMD_MID_ONU_GE_NUM
	{"GE bit图", "GE port bitmap"}, //CMD_MID_ONU_GE_BMP
	{"FE数", "FE port num"}, //CMD_MID_ONU_FE_NUM
	{"FE bit图", "FE port bitmap"}, //CMD_MID_ONU_FE_BMP
	{"上行对列数", "queue num uplink"}, //CMD_MID_ONU_QUE_NUM_UP
	{"上行端口最大队列数", "max queue num uplink"}, //CMD_MID_ONU_QUE_NUM_UP_MAX
	{"下行对列数", "queue num downlink"}, //CMD_MID_ONU_QUE_NUM_DOWN
	{"下行端口最大队列数", "max queue num downlink"}, //CMD_MID_ONU_QUE_NUM_DOWN_MAX
	
	{"ONU的安全策略", "onu auth policy"}, //CMD_MID_ONU_AUTH_POLICY
	{"黑名单模式", "Blacklist"}, //CMD_MID_ONU_BLACK_LIST
	{"白名单模式", "Whitelist"}, //CMD_MID_ONU_WHITE_LIST
	{"所有注册请求都允许", "Accept all"}, //CMD_MID_ONU_ACCEPT_ALL
	{"ONU的认证信息: 黑、白名单模式及名单列表", "ONU registration information"}, //CMD_MID_ONU_AUTH_INFO
	{"索引号", "Index"}, //CMD_MID_INDEX
	{"授权行为", "auth action"}, //CMD_MID_ONU_AUTH_ACTION
	{"拒绝", "reject"}, //CMD_MID_ONU_AUTH_REJECT
	{"接收", "accept"}, //CMD_MID_ONU_AUTH_ACCEPT
	{"ONU的黑、白状态", "ONU registration mode"}, //CMD_MID_ONU_AUTH_MODE
	{"模式", "mode"}, //CMD_MID_MODE
	{"认证请求已被拒绝的ONU列表", "ONU rejected list"}, //CMD_MID_ONU_AUTH_REJECT_LIST

	{"onu升级状态", "onu upgrade status"}, //CMD_MID_ONU_UPGRADE_STATUS
	{"onu状态", "onu status"}, //CMD_MID_ONU_STATUS
	{"等待升级", "Wait for the upgrade"}, //CMD_MID_ONU_WAIT_UPGRADE
	{"升级失败", "Upgrade failed"}, //CMD_MID_ONU_UPGRADE_FAILED
	{"升级成功", "Upgrade successed"}, //CMD_MID_ONU_UPGRADE_SUCCESSED
	{"分区切换完成", "Partition switch finished"}, //CMD_MID_ONU_UPGRADE_SWITCH_FINISHED
	{"模板序号", "profile id"},//CMD_MID_ONU_PROFILE_ID
	{"模板名称", "profile name"},//	CMD_MID_ONU_PROFILE_NAME
	{"onu绑定数量", "onu_num"},//CMD_MID_ONU_PROFILE_ONU_NUM
	
//uni
	{"UNI", "UNI"}, //CMD_MID_UNI
	{"本地自适应能力", "local auto negotiationa bility"}, //CMD_MID_AUTO_NEGO_ABL_LOCAL
	{"远程自适应能力", "remote auto negotiationa bility"}, //CMD_MID_AUTO_NEGO_ABL_REMOTE
	{"自适应重启", "auto negotiationa restart"}, //CMD_MID_AUTO_NEGO_RESTART

	{"1- 十兆全双工", "1- tenBaseTFullDuplex"}, //CMD_MID_AUTO_NEGO_ABL_F10
	{"2- 十兆半双工", "2- tenBaseTHalfDuplex"}, //CMD_MID_AUTO_NEGO_ABL_H10
	{"3- 百兆全双工", "3- hundredBaseTFullDuplex"}, //CMD_MID_AUTO_NEGO_ABL_F100
	{"4- 百兆半双工", "4- hundredBaseTHalfDuplex"}, //CMD_MID_AUTO_NEGO_ABL_H100
	{"5- 千兆全双工", "5- thousandBaseTFullDuplex"}, //CMD_MID_AUTO_NEGO_ABL_F1000
	{"6- 千兆半双工", "6- thousandBaseTHalfDuplex"}, //CMD_MID_AUTO_NEGO_ABL_H1000
	{"7- thousandBaseXFullDuplex", "7- thousandBaseXFullDuplex"}, //CMD_MID_AUTO_NEGO_ABL_F1000X
	{"8- thousandBaseXHalfDuplex", "8- thousandBaseXHalfDuplex"}, //CMD_MID_AUTO_NEGO_ABL_H1000X
	{"9- fdxPause", "9- fdxPause"}, //CMD_MID_AUTO_NEGO_ABL_FDX
	{"10-fdxApause", "10-fdxApause"}, //CMD_MID_AUTO_NEGO_ABL_FDXA
	{"11-fdxSpause", "11-fdxSpause"}, //CMD_MID_AUTO_NEGO_ABL_FDXS
	{"12-fdxBpause", "12-fdxBpause"}, //CMD_MID_AUTO_NEGO_ABL_FDXB	
	
	{"UNI端口属性", "UNI attribute"}, //CMD_MID_UNI_ATTR
	{"ONU号为 %d。", "the onu id is %d.\r\n"}, //CMD_MID_ONU_ID_IS	
	{"MAC 永不老化。", "MAC non-aging.\r\n"}, //CMD_MID_NON_AGING
	{"MAC 老化时间为 %d 秒。", "aging time is %d second.\r\n"}, //CMD_MID_AGING_TIME_IS
	{"静态MAC地址表", "static mac address table"}, //CMD_MID_STATIC_MAT
	{"动态MAC地址表", "dynamic mac address table"}, //CMD_MID_DYNAMIC_MAT
	{"端口最大动态mac地址学习个数", "port maximum dynamic mac learn count"},//CMD_MID_MAX_LRN
	{"只有sni口能够配置静态mac地址", "just sni port can configure static mac address"},//CMD_MID_SNI_STATIC_MAC
	{"只有单播mac能够配置为静态表项", "just unicast mac can configure to static mac address"},//CMD_MID_MUTI_MAC_NOT_STATIC
	{"配置失败，因为表项已满!","configure failed, because table is full!"},//CMD_MID_MAC_FULL_NOTE
	
	{"UNI 端口速率限制信息", "uni port rate-limite information"}, //CMD_MID_UNI_RATE_LIMIT
	{"CIR(kbps)", "CIR(kbps)"}, //CMD_MID_CIR
	{"CBS(kbps)", "CBS(kbps)"}, //CMD_MID_CBS
	{"EBS(kbps)", "EBS(kbps)"}, //CMD_MID_EBS
	{"PIR(kbps)", "PIR(kbps)"}, //CMD_MID_PIR
	{"连接状态", "link status"}, //CMD_MID_LINK_STATUS
//statistics
	{"统计配置信息", "statistics configure information"}, //CMD_MID_STATS_CONF_INFO
	{"15分钟性能统计最大记录数", "15 minutes max record"}, //CMD_MID_STATS_M15_MAX
	{"24小时性能统计最大记录数", "1-day max record"}, //CMD_MID_STATS_H24_MAX
	{"统计项目", "name"}, //CMD_MID_STATS_NAME
	{"接收", "in"}, //CMD_MID_STATS_IN
	{"发送", "out"}, //CMD_MID_STATS_OUT
	{"字节数", "octets"}, //CMD_MID_STATS_OCTS
	{"帧数", "packets"}, //CMD_MID_STATS_PKTS
	{"广播帧数", "brodcast packets"}, //CMD_MID_STATS_PKTS_BROD
	{"组播帧数", "multcast packets"}, //CMD_MID_STATS_PKTS_MULT
	{"长度为(64)字节包数", "packets(64)B"}, //CMD_MID_STATS_PKTS_64
	{"长度为(65~127)字节包数", "packets(65~127)B"}, //CMD_MID_STATS_PKTS_65_127
	{"长度为(128~255)字节包数", "packets(128~255)B"}, //CMD_MID_STATS_PKTS_128_255
	{"长度为(256~511)字节包数", "packets(256~511)B"}, //CMD_MID_STATS_PKTS_256_511
	{"长度为(512~1023)字节包数", "packets(512~1023)B"}, //CMD_MID_STATS_PKTS_512_1023
	{"长度为(1024~1518)字节包数", "packets(1024~1518)B"}, //CMD_MID_STATS_PKTS_1024_1518
	{"长度为(1519~1522)字节包数", "packets(1519~1522)B"}, //CMD_MID_STATS_PKTS_1519_1522
	{"超短帧数", "undersize packets"}, //CMD_MID_STATS_PKTS_UNDERSIZE
	{"超长帧数", "oversize packets"}, //CMD_MID_STATS_PKTS_OVERSIZE
	{"碎片数", "fragments"}, //CMD_MID_STATS_FRAGMENTS
	{"MPCP 帧数", "MPCP frames"}, //CMD_MID_STATS_MPCP_FRMS
	{"MPCP 字节数", "MPCP octets"}, //CMD_MID_STATS_MPCP_OCTS
	{"OAM 帧数", "OAM frames"}, //CMD_MID_STATS_OAM_FRMS
	{"OAM 字节数", "OAM octets"}, //CMD_MID_STATS_OAM_OCTS
	{"CRC 错误帧数", "CRC error packets"}, //CMD_MID_STATS_PKTS_CRC_ERR
	{"丢包事件次数", "drop events"}, //CMD_MID_STATS_DROP_EVTS
	{"超长错误帧数", "jabbers"}, //CMD_MID_STATS_JABBERS
	{"碰撞帧数", "collisions"}, //CMD_MID_STATS_COLLISIONS
	
	{"丢弃报文数", "discard frames"},//CMD_MID_STATS_PKTS_DISCARD
	{"错误报文数", "error frames"},//CMD_MID_STATS_PKTS_ERR
	{"端口状态变化次数", "port status change times"},//CMD_MID_STATS_STATUS_CHG_TIMES
	
	{"统计使能", "statistic enable"}, //CMD_MID_STATS_ENABLE	
	{"统计周期", "statistic period"}, //CMD_MID_STATS_PERIOD
	
	{"实时统计性能数据", "current statistics data"}, //CMD_MID_STATS_INFO_CUR
	{"历史统计性能数据", "history statistics data"}, //CMD_MID_STATS_INFO_HISTORY
	{"是否有效", "is valid"}, //CMD_MID_STATS_IS_VALID
	{"开始时间", "start time"}, //CMD_MID_STATS_START_TIME
	{"结束时间", "end time"}, //CMD_MID_STATS_END_TIME
	{"15分钟统计性能数据", "15 minutes statistics data"}, //CMD_MID_STATS_INFO_M15
	{"24小时统计性能数据", "1-day statistics data"}, //CMD_MID_STATS_INFO_H24
	{"共有 %d 项，当前为 %d 。\r\n", "there are %d entries, current is %d.\r\n"}, //CMD_MID_STATS_CUR_IS
	
	{"统计门限信息", "statistics threshold information"}, //CMD_MID_STATS_INFO_THRESHOLD
//ppg
	{"pon端口保护组信息", "protect group information"}, //CMD_MID_PPG_INFO
	{"组ID", "GID"}, //CMD_MID_PPG_ID
	{"开/关", "on/off"}, //CMD_MID_PPG_ENABLE
	{"开", "on"}, //CMD_MID_ON
	{"关", "off"}, //CMD_MID_OFF
	{"主用端口", "main-Port"}, //CMD_MID_PPG_PORT_MAIN
	{"备用端口", "backup-Port"}, //CMD_MID_PPG_PORT_BACKUP
	{"切换方式", "switch-mode"}, //CMD_MID_PPG_SWITCH_MODE
	{"自动", "auto"}, //CMD_MID_AUTO
	{"手动", "manual"}, //CMD_MID_MANUAL
	{"组工作状态", "group-status"}, //CMD_MID_PPG_STATUS
	{"主", "primary"}, //CMD_MID_PPG_PRIMARY
	{"备", "secondary"}, //CMD_MID_PPG_SECONDARY
	{"未锁定", "unlock"}, //CMD_MID_PPG_UNLOCK
	{"自动恢复时间", "recover-time"}, //CMD_MID_PPG_RECOVER_TIME
//qos
	{"设备号", "Device ID"}, //CMD_MID_DEVICE_ID
	{"最大队列数", "Max queue count"}, //CMD_MID_QOS_QUE_MAX
	{"QOS工作模式", "Qos mode"}, //CMD_MID_QOS_MODE
	{"基于端口", "port based"}, //CMD_MID_QOS_BASED_PORT
	{"基于设备", "device based"}, //CMD_MID_QOS_BASED_DEVICE
	{"QOS全局配置信息", "qos global information"}, //CMD_MID_QOS_GBL_INFO

	{"错误!!!输入优先级[%d]是无效的!\r\n", "error!!! the priority number[%d] is invalid!\r\n"}, //CMD_MID_QOS_PRI_ERR
	{"基于设备模式，必须进入全局模式!\r\n", "device based, you must go to CONFIG mode!\r\n"}, //CMD_MID_QOS_GO_CFG_MODE
	{"错误!!!其它命令模式。\r\n", "error!!!other command mode. \r\n"}, //CMD_MID_QOS_CMD_MODE_ERR
	{"错误!!!未知QOS模式。\r\n", "error!!!unknown qos mode.\r\n"}, //CMD_MID_QOS_MODE_ERR
	
	{"QOS映射规则", "Qos map rule"}, //CMD_MID_QOS_MAP_RULE
	{"COS", "COS"}, //CMD_MID_QOS_COS
	{"TOS", "TOS"}, //CMD_MID_QOS_TOS
	{"DSCP", "DSCP"}, //CMD_MID_QOS_DSCP
	{"优先级最大值", "max priority number"}, //CMD_MID_QOS_PRI_MAX
	{"QOS队列映射", "Qos map queue"}, //CMD_MID_QOS_MAP_QUE
	{"QOS队列映射信息", "qos map information"}, //CMD_MID_QOS_MAP_INFO
	
	{"QOS调度信息", "qos scheduler policy information"}, //CMD_MID_QOS_SCHE_INFO
	{"QOS调度策略", "Qos policy type"}, //CMD_MID_QOS_SCHE_POLICY
	{"SP", "SP"}, //CMD_MID_QOS_SP
	{"WRR", "WRR"}, //CMD_MID_QOS_WRR
	{"SPWRR", "SPWRR"}, //CMD_MID_QOS_SPWRR
	{"WFP", "WFP"}, //CMD_MID_QOS_WFP
	{"权重", "weight value"}, //CMD_MID_QOS_WEIGHT_VALUE
	{"错误!!!输入权重列表[%s]是无效的。\r\n", "error! Input weight list is invalid, List=%s.r\n"},//CMD_MID_QOS_WEIGHT_VALUE_INVALID
	{"转换权重列表为: ", "change weight list: "},//CMD_MID_QOS_CHANGE_WEIGHT_LIST

//alarm
	{"告警管理", "trap information"}, //CMD_MID_TRAP_INFO
	{"告警总开关", "trap enable"}, //CMD_MID_TRAP_ENABLE

	{"确认", "cf"}, //CMD_MID_CONFIRM
	{"告警描述", "alarm description"}, //CMD_MID_ALARM_DESP
	{"严重级别", "Severity"}, //CMD_MID_SEVERITY
	{"紧急", "Critical"}, //CMD_MID_CRITICAL
	{"严重", "Major"}, //CMD_MID_MAJOR
	{"轻微", "Minor"}, //CMD_MID_MINOR
	{"警告", "Warning"}, //CMD_MID_WARNING
	{"信息", "Info"}, //CMD_MID_INFO
	{"清除", "Clear"}, //CMD_MID_CLEAR

	{"初始发生时间", "First time"}, //CMD_MID_FIRST_TIME
	{"最后发生时间", "Last time"}, //CMD_MID_LAST_TIME
	{"其它描述", "additional info"}, //CMD_MID_ADD_TEXT
	{"实时告警信息", "current alarm information"}, //CMD_MID_ALARM_INFO_CURRENT
	{"历史告警信息", "history alarm information"}, //CMD_MID_ALARM_INFO_HISTORY	
	{"事件日志", "event log"}, //CMD_MID_ALARM_INFO_EVENT
	
	{"未知告警类型", "unknown alarm code"}, //CMD_MID_ALARM_UNKNOWN
	{"板卡启动自动配置失败", "boardProvisionFail"}, //CMD_MID_ALARM_BOARD_PROVISION_FAIL
	{"板卡重启", "boardReset"}, //CMD_MID_ALARM_BOARD_RESET
	{"板卡被拔出", "boardRemoval"}, //CMD_MID_ALARM_BOARD_REMOVEL
	{"板卡温度异常", "boardTempAbnormal"}, //CMD_MID_ALARM_BOARD_TEMP_ABNORMAL
	{"设备风扇故障", "fanFailed"}, //CMD_MID_ALARM_FAN_FAILED
	{"设备风扇框被拔出", "fanRemoval"}, //CMD_MID_ALARM_FAN_REMOCAL
	{"设备电源模块异常", "powerFailed"}, //CMD_MID_ALARM_POWER_FAILED
	{"电源模块被拔出", "powerRemoval"}, //CMD_MID_ALARM_POWER_REMOVAL
	{"芯片固件致命错误", "fatalOLTHwError"}, //CMD_MID_ALARM_FATAL_OLT_HW_ERROR

	{"OLT PON光模块失效", "oltPonOpticalModuleFaulty"}, //CMD_MID_ALARM_PON_OPT_FAULTY
	{"OLT SNI光模块失效", "oltSniOpticalModuleFaulty"}, //CMD_MID_ALARM_SNI_OPT_FAULTY
	{"OLT PON口link状态", "oltPonLink"}, //CMD_MID_ALARM_PON_LINK_FAULTY
	{"OLT SNI口link状态", "oltSniLINK"}, //CMD_MID_ALARM_SNI_LINK_FAULTY
	{"OLT PON口光信号丢失", "OltPonRLos"}, //CMD_MID_ALARM_PON_RLOS
	{"OLT SNI口光信号丢失", "OltSniRLos"}, //CMD_MID_ALARM_SNI_RLOS	

	{"OLT接收到的丢包事件数超过设置的告警门限时上报", "Olt DownstreamDropEventsAlarm"}, //CMD_MID_OLT_DOWNSTREAMDROPEVENTSALARM
	{"OLT未发送的丢包事件数超过设置的告警门限时上报", "Olt UpstreamDropEventsAlarm"}, //CMD_MID_OLT_UPSTREAMDROPEVENTSALARM
	{"OLT接收到的CRC错误报文数超过设置的告警门限时上报", "Olt DownstreamCrcerrorFramesAlarm"}, //CMD_MID_OLT_DOWNSTREAMCRCERRORFRAMESALARM
	{"OLT接收到的超短报文数超过设置的告警门限时上报", "Olt DownstreamUndersizeFramesAlarm"}, //CMD_MID_OLT_DOWNSTREAMUNDERSIZEFRAMESALARM
	{"OLT发送的超短报文数超过设置的告警门限时上报", "Olt UpstreamUndersizeFramesAlarm"}, //CMD_MID_OLT_UPSTREAMUNDERSIZEFRAMESALARM
	{"OLT接收到的超长报文数超过设置的告警门限时上报", "Olt DownstreamOversizeFramesAlarm"}, //CMD_MID_OLT_DOWNSTREAMOVERSIZEFRAMESALARM
	{"OLT发送的超长报文数超过设置的告警门限时上报", "Olt UpstreamOversizeFramesAlarm"}, //CMD_MID_OLT_UPSTREAMOVERSIZEFRAMESALARM
	{"OLT接收到的Fragments数超过设置的告警门限时上报", "Olt DownstreamFragmentsAlarm"}, //CMD_MID_OLT_DOWNSTREAMFRAGMENTSALARM
	{"OLT接收到的Jabbers数超过设置的告警门限时上报", "Olt DownstreamJabbersAlarm"}, //CMD_MID_OLT_DOWNSTREAMJABBERSALARM
	{"OLT接收到的冲突次数超过设置的告警门限时上报", "Olt DownstreamCollistonsAlarm"}, //CMD_MID_OLT_DOWNSTREAMCOLLISIONSALARM
	{"OLT接收到的丢弃报文数超过设置的告警门限时上报", "Olt DownstreamDiscardFramesAlarm"}, //CMD_MID_OLT_DOWNSTREAMDISCARDFRAMESALARM
	{"OLT未发送的丢弃报文数超过设置的告警门限时上报", "Olt UpstreamDiscardFramesAlarm"}, //CMD_MID_OLT_UPSTREAMDISCARDFRAMESALARM
	{"OLT接收到的错误报文数超过设置的告警门限时上报", "Olt DownstreamErrorFramesAlarm"}, //CMD_MID_OLT_DOWNSTREAMERRORFRAMESALARM
	

//stp
	{"stp参数及拓扑信息", "stp bridge information"}, //CMD_MID_STP_BR_INFO
	{"虚拟桥", "bridge"}, //CMD_MID_STP_BRIDGE
	{"协议版本", "version"}, //CMD_MID_STP_VER
	{"SSTP", "SSTP"}, //CMD_MID_SSTP
	{"RSTP", "RSTP"}, //CMD_MID_RSTP
	{"MSTP", "MSTP"}, //CMD_MID_MSTP
	{"优先级", "priority"}, //CMD_MID_STP_PRI
	{"变更时间", "last topology change"}, //CMD_MID_STP_CHG_TIME
	{"变更次数", "topology changes"}, //CMD_MID_STP_CHG_COUNT
	{"根路径开销", "root path cost"}, //CMD_MID_STP_ROOT_PATH_COST
	{"老化时间", "max age"}, //CMD_MID_STP_MAX_AGE
	{"报文发送间隔时间", "hello time"}, //CMD_MID_STP_HELLO_TIME
	{"占用时间", "hold time"}, //CMD_MID_STP_HOLD_TIME
	{"转换时延", "forward delay"}, //CMD_MID_STP_FWD_DELAY
	{"每秒最多发送 BPDU 个数", "Transmit Hold Count"}, //CMD_MID_STP_TXHOLD_CNT
	{"根网桥的老化时间", "root max age"}, //CMD_MID_STP_ROOT_MAX_AGE
	{"根网桥的报文发送间隔时间", "root hello time"}, //CMD_MID_STP_ROOT_HELLO_TIME
	{"根网桥的转换时延", "root forward delay"}, //CMD_MID_STP_ROOT_FWD_DELAY	
	{"路径开销算法", "pathcost method"}, //CMD_MID_STP_COST_METHOD

//igmp configure
	{"组播vlan信息", "multicast vlan information"}, //CMD_MID_VLAN_MULTICAST_INFO
	{"vlan号的范围", "vlan id range"}, //CMD_MID_VLAN_ID_RANGE
	{"组播vlan端口信息", "multicast vlan port information"}, //CMD_MID_VLAN_MULTICAST_PORT_INFO
	{"组播vlan号", "multicast vlan id"}, //CMD_MID_VLAN_MULTICAST_ID
	{"Igmp mcst vlan 端口信息", "Igmp mcst vlan port information"}, //CMD_MID_VLAN_MCST_IGMP_PORT_INFO
	
	{"可控组播包信息", "Controlled multicast packages information"}, //CMD_MID_MULTICAST_CONTROL_PKG_INFO
	{"业务包索引", "package index"}, //CMD_MID_PKG_INDEX
	{"业务包名", "package name"}, //CMD_MID_PKG_NAME
	{"代理列表", "proxy list"}, //CMD_MID_IGMP_PROXY_LIST
	{"组播包的用户访问权限", "multicast user authority"}, //CMD_MID_IGMP_MULTICAST_USER_AUTHORITY
	{"组播包的最大请求节目数", "max request channel num"}, //CMD_MID_IGMP_MAX_REQUEST_CHANNEL_NUM
	{"组播包的单次预览时长", "single preview time"}, //CMD_MID_IGMP_SINGLE_PREVIEW_TIME
	{"组播包的预览总时长", "total preview time"}, //CMD_MID_IGMP_TOTAL_PREVIEW_TIME
	{"组播包的预览复位时间", "preview reset time"}, //CMD_MID_IGMP_PREVIEW_RESET_TIME
	{"组播包的预览次数", "preview count"}, //CMD_MID_IGMP_PREVIEW_COUNT

	{"用户可控组播包信息", "Controlled multicast user authority information"}, //CMD_MID_IGMP_MULTICAST_USER_AUTHORITY_INFO
	{"package list", "业务包列表"}, //CMD_MID_PKG_LIST
	{"igmp组播业务最大带宽", "igmp global bw"}, //CMD_MID_IGMP_GLOBAL_BW
	{"igmp组播业务使用带宽", "igmp global bw used"}, //CMD_MID_IGMP_GLOBAL_BW_USED

//file-system
	{"系统信息", "system information"}, //CMD_MID_FILE_SYS_INFO
	{"系统分区索引", "system partition index"}, //CMD_MID_SYS_INDEX
	{"系统启动标志", "system start flag"}, //CMD_MID_SYS_START_FALG
	{"具体系统信息", "detailed system information"}, //CMD_MID_SYS_INFO

	{"olt端口速率信息", "olt interface rate-limit information"}, //CMD_MID_OLT_INTERFACE_RATE_INFO
	{"端口隔离信息", "interface isolation information"}, //CMD_MID_OLT_INTERFACE_ISOT_INFO

//onu max distance
	{"pon端口onu最大距离", "olt pon onu max distance"}, //CMD_MID_OLT_PON_ONU_MAX_DISTANCE

//snmp community 
	{"SNMP服务器社区名表的信息", "snmp server community list info"}, //CMD_MID_SNMP_COMMUNITY_LIST_INFO
	{"社区名", "community name"}, //CMD_MID_COMMUNITY_NAME
	{"操作权限", "permission"}, //CMD_MID_COMMUNITY_PERMISSION

	{"不支持", "Not Supported"}, //CMD_MID_NOTSUPPORT
//	{"", ""}//CMD_MID_NULL
};



const char* bc_cli_menu_thresholdtype[CMD_TRSD_TYPE_MAX][CMD_ML_MAXNUM] = 
{
	{"0   错误类型               ", "0   Error                           "},  
	{"1   下行丢弃事件告警       ", "1   DownstreamDropEventsAlarm       "},  
	{"2   上行丢弃事件告警       ", "2   UpstreamDropEventsAlarm         "},  
	{"3   下行CRC错误帧告警      ", "3   DownstreamCRCErrorFramesAlarm   "},  
	{"4   下行过小帧告警         ", "4   DownstreamUndersizeFramesAlarm  "},  
	{"5   上行过小帧告警         ", "5   UpstreamUndersizeFramesAlarm    "},  
	{"6   下行过大帧告警         ", "6   DownstreamOversizeFramesAlarm   "},  
	{"7   上行过大帧告警         ", "7   UpstreamOversizeFramesAlarm     "},  
	{"8   下行碎片告警           ", "8   DownstreamFragmentsAlarm        "},  
	{"9   下行逾限告警           ", "9   DownstreamJabbersAlarm          "},  
	{"10  下行冲突告警           ", "10  DownstreamCollisionsAlarm       "},  
	{"11  下行丢弃帧告警         ", "11  DownstreamDiscardFramesAlarm    "},  
	{"12  上行丢弃帧告警         ", "12  UpstreamDiscardFramesAlarm      "},  
	{"13  下行错误帧告警         ", "13  DownstreamErrorFramesAlarm      "},  
	{"14  上行错误帧告警         ", "14  UpstreamErrorFramesAlarm        "},  
	{"15  状态改变次数告警       ", "15  StatusChangeTimesAlarm          "},  
	{"16  下行丢弃事件提醒       ", "16  DownstreamDropEventsWarning     "},  
	{"17  上行丢弃事件提醒       ", "17  UpstreamDropEventsWarning       "},  
	{"18  下行CRC错误帧提醒      ", "18  DownstreamCRCErrorFramesWarning "},  
	{"19  下行过小帧提醒         ", "19  DownstreamUndersizeFramesWarning"},  
	{"20  上行过小帧提醒         ", "20  UpstreamUndersizeFramesWarning  "},  
	{"21  下行过大帧提醒         ", "21  DownstreamOversizeFramesWarning "},  
	{"22  上行过大帧提醒         ", "22  UpstreamOversizeFramesWarning   "},  
	{"23  下行碎片提醒           ", "23  DownstreamFragmentsWarning      "},  
	{"24  下行逾限提醒           ", "24  DownstreamJabbersWarning        "},  
	{"25  下行冲突提醒           ", "25  DownstreamCollisionsWarning     "},  
	{"26  下行丢弃帧提醒         ", "26  DownstreamDiscardFramesWarning  "},  
	{"27  上行丢弃帧提醒         ", "27  UpstreamDiscardFramesWarning    "},  
	{"28  下行错误帧提醒         ", "28  DownstreamErrorFramesWarning    "},  
	{"29  上行错误帧提醒         ", "29  UpstreamErrorFramesWarning      "},  
	{"30  状态改变次数提醒       ", "30  StatusChangeTimesWarning        "},
};
#endif


/* 
 *	内部全局变量，只提供给该文件内部函数调用，不在头文件中提供调用接口。
 */

//static unsigned int l_mdl_id = CLI_SHELL_MODULE;



////////////////////////////////////////////////////////////////////////////////
//																			  //
//								函  数  声  明								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//																			  //
//								函  数  定  义								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
/******************************************************************************\
  Function   : 
  Description: 
  Return     : 
  Others     : 
\******************************************************************************/



/* 
 *	预留一个注释在文件最后
 */
/******************************************************************************\
  Function   : 
  Description: 
  Return     : 
  Others     : 
\******************************************************************************/



