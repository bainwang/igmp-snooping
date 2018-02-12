
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
//								ͷ   ��   ��								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_cli_text.h"



////////////////////////////////////////////////////////////////////////////////
//																			  //
//						�� �� �� ���� �� �� �� ��							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//																			  //
//						��   ��   ��   ��   ��   ��							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
/*
 *		��Դ�ļ���Ҫ����꣬��ͷ�ļ���������ģ��ͷ�ļ��еĺ궨�����ظ���������
 *	ʱ���ڴ˴����塣
 */



////////////////////////////////////////////////////////////////////////////////
//																			  //
//							ȫ �� �� �� �� ��								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
/* 
 *	�ⲿȫ�ֱ������ṩ�������̵��ã���ͷ�ļ����ṩ���ýӿ�(�ⲿ��������)��
 */

#if 0
// bc_cli_menu
const char *bc_cli_menu[CMD_MID_MAXNUM][CMD_ML_MAXNUM] = 
{
	{"��ȡ���ó���", "Error while api getting!"}, //CMD_MID_ERR_GET
	{"���ó���", "Error while api setting!"}, //CMD_MID_ERR_SET
	
	{"ʱ��", "zone"}, //CMD_MID_ZONE
	{"��", "year"},//CMD_MID_YEAR
	{"��", "month"}, //CMD_MID_MONTH
	{"��", "day"}, //CMD_MID_DAY
	{"ʱ", "hour"}, //CMD_MID_HOUR
	{"��", "minute"}, //CMD_MID_MINUTE
	{"��", "second"}, //CMD_MID_SECOND
	
	{"�汾��Ϣ", "version information"}, //CMD_MID_VERINFO
	{"����汾", "software version"}, //CMD_MID_SOFTVER
	{"Ӳ���汾", "hardware version"}, //CMD_MID_HARDVER
	{"���ڹ���", "management inband"}, //CMD_MID_MGNTIN
	{"�������", "management outband"}, //CMD_MID_MGNTOUT
	{"�����ַ", "mac address"}, //CMD_MID_MACADDR
	{"�����ַ", "ip address"}, //CMD_MID_IPADDR
	{"��������", "subnet mask"}, //CMD_MID_NETMASK
	{"����", "gateway"}, //CMD_MID_GATEWAY
	{"vlan id", "vlan id"}, //CMD_MID_VLANID
	{"���ȼ�", "prority"}, //CMD_MID_PRORITY
	
	{"olt����", "olt property"}, //CMD_MID_OLTPPT
	{"����", "name"}, //CMD_MID_NAME
	{"����", "type"}, //CMD_MID_TYPE
	{"���ذ�", "control board"}, //CMD_MID_TYPE_BDCTRL
	{"GE EPON ��", "GE EPON board"}, //CMD_MID_TYPE_BDGEPON
	{"������", "uplink board"}, //CMD_MID_TYPE_BDUPLINK
	{"������", "switch board"}, //CMD_MID_TYPE_BDSWITCH
	{"δ֪���Ͱ忨", "others"}, //CMD_MID_TYPE_BDOTHER
	{"�忨δ����", "vacant"}, //CMD_MID_TYPE_BDVACANT
	{"����״̬", "admin status"}, //CMD_MID_ADMINSTA
	{"�豸����", "up"}, //CMD_MID_STA_UP
	{"�豸����", "down"}, //CMD_MID_STA_DOWN
	{"�豸����", "testing"}, //CMD_MID_STA_TESTING
	{"����ʱ��", "up time"}, //CMD_MID_UPTIME
	{"ҵ�񿨲�λ��", "number of service slot"}, //CMD_MID_SRVSLOTS
	{"��Դ����λ��", "number of power slot"}, //CMD_MID_POWERSLOTS
	{"���ȿ���λ��", "number of fan slot"}, //CMD_MID_FANSLOTS
	{"�豸����", "device style"}, //CMD_MID_DEVSTYLE
	{"�̶���ʽ", "fixed"}, //CMD_MID_STYLE_FIXED
	{"����ʽ", "chassis based"}, //CMD_MID_STYLE_CHASSIS
	{"��������", "others"}, //CMD_MID_STYLE_OTHER
		
	{"�忨��Ϣ", "board information"}, //CMD_MID_BDINFO
	{"��", "slot"}, //CMD_MID_SLOT
	{"��������״̬", "main/back redundance"}, //CMD_MID_MAINBACK
	{"���ð忨", "active"}, //CMD_MID_MB_ACT
	{"���ð忨", "stand by"}, //CMD_MID_MB_STBY
	{"�����忨", "stand alone"}, //CMD_MID_MB_STAL
	{"��֧����������", "not applicable"}, //CMD_MID_MB_NOTAP
	{"�̼��汾", "fireware version"}, //CMD_MID_FIRMVER
	{"�澯״̬", "alarm status"}, //CMD_MID_WARNSTA
	{"�޸澯", "none"}, //CMD_MID_WARN_NONE
	{"����", "critical"}, //CMD_MID_WARN_CRITICAL
	{"����", "major"}, //CMD_MID_WARN_MAJOR
	{"��΢", "minor"}, //CMD_MID_WARN_MINOR
	{"����", "warning"}, //CMD_MID_WARN_WARNING
	{"���к�", "serial no"}, //CMD_MID_SERIALNO
	{"��λ״̬", "slot status"}, //CMD_MID_SLOTSTA
	{"�Ѱ�װ", "installed"}, //CMD_MID_SLOTSTA_INSTALL
	{"δ��װ", "uninstalled"}, //CMD_MID_SLOTSTA_UNINSTALL
	{"����״̬", "others"}, //CMD_MID_SLOTSTA_OTHERS

	{"MAC ��ַѧϰ��", "mac address table"}, //CMD_MID_MAT
	{"�˿�", "port"}, //CMD_MID_PORT
	{"s", "s"}, //CMD_MID_PORT_OLTSNI
	{"p", "p"}, //CMD_MID_PORT_OLTPON
	{"p", "p"}, //CMD_MID_PORT_ONUPON
	{"u", "u"}, //CMD_MID_PORT_ONUUNI
	{"t", "t"}, //CMD_MID_PORT_OLTTRUNK
	{"c", "c"}, //CMD_MID_PORT_OLTCPU
	{"m", "m"}, //CMD_MID_PORT_OLTMII
	{"��̬", "dynamic"}, //CMD_MID_DYNAMIC
	{"��̬", "static"}, //CMD_MID_STATIC
	
	{"�籩������Ϣ", "storm control informatioin"}, //CMD_MID_STORMCTRL
	{"δ֪����", "unknown unicast"}, //CMD_MID_UNICAST
	{"�鲥", "multicast"}, //CMD_MID_MULTI
	{"�㲥", "broadcast"}, //CMD_MID_BROAD
	{"��", "enable"}, //CMD_MID_ENABLE
	{"�ر�", "disable"}, //CMD_MID_DISABLE
	{"״̬", "state"},//CMD_MID_STATE
	{"���", "ingress"}, //CMD_MID_INGRESS
	{"����", "egress"}, //CMD_MID_EGRESS	
	{"�����ֽ�����", "Receive Byte Rate"}, //CMD_MID_INGRESS_RATE
	{"�����ֽ�����", "Transmit Byte Rate"}, //CMD_MID_EGRESS_RATE
	{"λ/��", "bps"}, //CMD_MID_BPS
	{"ǧλ/��", "kbps"}, //CMD_MID_KBPS	
	{"�ֽ�/��", "Bytes/s"}, //CMD_MID_BYTES_PS
	
	{"�˿ھ�����Ϣ", "port mirror information"}, //CMD_MID_MIRROR
	{"��", "session"}, //CMD_MID_SESSION
	{"Դ", "source"}, //CMD_MID_SOURCE
	{"Ŀ��", "destination"}, //CMD_MID_DESTINATION
//sni	
	{"sni����Ϣ", "sni information"}, //CMD_MID_SNI_INFO
	
	{"comboģʽ", "combo mode"}, //CMD_MID_SNI_COMBO_MODE
	{"��������", "media type"}, //CMD_MID_SNI_MEDIA_TYPE
	{"ͭ����", "copper"}, //CMD_MID_MEDIA_COPPER
	{"����", "fiber"}, //CMD_MID_MEDIA_FIBER
	{"�Զ�", "auto"}, //CMD_MID_MEDIA_AUTO
	{"��������", "others"}, //CMD_MID_MEDIA_OTHER
	{"����Ӧʹ��", "auto negotiation enable"}, //CMD_MID_AUTO_NEGO_ENABLE
	{"����Ӧ״̬", "auto negotiation status"}, //CMD_MID_AUTO_NEGO_STA
	{"����Ӧģʽ", "auto negotiation mode"}, //CMD_MID_AUTO_NEGO_MODE
	{"�Զ�", "auto"}, //CMD_MID_AN_AUTO
	{"10M��˫��", "half-10"}, //CMD_MID_AN_H10
	{"10Mȫ˫��", "full-10"}, //CMD_MID_AN_F10
	{"100M��˫��", "half-100"}, //CMD_MID_AN_H100
	{"100Mȫ˫��", "full-100"}, //CMD_MID_AN_F100
	{"1Gȫ˫��", "full-1000"}, //CMD_MID_AN_F1000
	{"10Gȫ˫��", "full-10000"}, //CMD_MID_AN_F10000
	{"����޸�ʱ��", "last change time"}, //CMD_MID_LAST_CHG_TIME
	{"link up", "link up"}, //CMD_MID_LINK_UP
	{"link down", "link down"}, //CMD_MID_LINK_DOWN	
	{"�˿�ʹ��", "port enable"}, //CMD_MID_PORT_ENABLE
	{"�˿�MAC", "port MAC"}, //CMD_MID_PORT_MAC	
	{"STPʹ��", "STP enable"}, //CMD_MID_STP_ENABLE
//pon	
	{"pon����Ϣ", "pon information"}, //CMD_MID_PON_INFO	
	{"pon�ڼ�����Ϣ", "pon crypto information"}, //CMD_MID_PON_CRYPTO_INFO
	{"���֧��ONU��", "max onu num support"}, //CMD_MID_MAX_ONU
	{"����ONU��", "up onu num "}, //CMD_MID_UP_ONU
	{"����ʹ��", "encrypt enable"}, //CMD_MID_ENCRYPT_ENABLE
	{"����ģʽ", "encrypt mode"}, //CMD_MID_ENCRYPT_MODE
	{"δ����", "none"}, //CMD_MID_ENCRYPT_MODE_NONE
	{"AES32", "AES32"}, //CMD_MID_ENCRYPT_MODE_AES32
	{"AES48", "AES48"}, //CMD_MID_ENCRYPT_MODE_AES48
	{"AES128", "AES128"}, //CMD_MID_ENCRYPT_MODE_AES128
	{"�������", "ctc triple churning"}, //CMD_MID_ENCRYPT_MODE_CTCTRIPLECHURNING
	{"������������", "others"}, //CMD_MID_ENCRYPT_MODE_OTHER
	{"��Կ����ʱ��", "encrypt key exchange time"}, //CMD_MID_ENCRYPT_KEY_EXCHANGE_TIME
	{"���빦��ʹ��", "isolation enable"}, //CMD_MID_ISOLATION_EN
	{"��������", "flow control"}, //CMD_MID_FLOW_CONTROL_EN
	{"��·���", "loopback detect "}, //CMD_MID_LOOPBACK_DETECT_EN
	{"����������", "downstream bandwidth max"}, //CMD_MID_DS_BANDWIDTH_MAX
	{"����ʵ��ʹ�ô���", "downstream bandwidth in use"}, //CMD_MID_DS_BANDWIDTH_INUSE
	{"����ʣ�����", "downstream bandwidth remain"}, //CMD_MID_DS_BANDWIDTH_REMAIN
	{"15��������ͳ��ʹ��", "perf stats in 15 minutes"}, //CMD_MID_15M_EN
	{"24Сʱ����ͳ��ʹ��", "perf stats in 24 hours"}, //CMD_MID_24H_EN
	{"mac��ַѧϰ�����ѧϰ��", "max. of mac learning"}, //CMD_MID_MACADDR_LEARN_MAXNUM
	{"����������", "up stream bandwidth max"}, //CMD_MID_UP_BANDWIDTH_MAX
	{"����ʵ��ʹ�ô���", "downstream bandwidth in use"}, //CMD_MID_UP_BANDWIDTH_INUSE
	{"����ʣ�����", "up stream bandwidth remain"}, //CMD_MID_UP_BANDWIDTH_REMAIN
//acl	
	{"acl ����", "acl rule"}, //CMD_MID_ACL_RULE_INFO
	{"����", "permit"}, //CMD_MID_ACL_RULE_PERMIT
	{"�ܾ�", "deny"}, //CMD_MID_ACL_RULE_DENY
	{"���", "mark"}, //CMD_MID_ACL_RULE_MARK	

	{"acl������Ϣ", "acl list information"}, //CMD_MID_ACL_LIST_INFO
	{"ip", "ip"}, //CMD_MID_ACL_IP
	{"access-list", "access-list"}, //CMD_MID_ACL_ACL
	{"ACL����", "acl type"}, //CMD_MID_ACL_TYPE
	{"standard", "standard"}, //CMD_MID_ACL_TYPE_STD
	{"extended", "extended"}, //CMD_MID_ACL_TYPE_EXTEND
	{"expert", "expert"}, //CMD_MID_ACL_TYPE_EXPERT_EXTEND
	
	{"acl����Ϣ", "acl group information"}, //CMD_MID_ACL_GROUP_INFO
	{"��ڷ����acl", "acl for ingress"}, //CMD_MID_ACL_INGRESS
	{"���ڷ����acl", "acl for egress"}, //CMD_MID_ACL_EGRESS
	{"��", "no acl"}, //CMD_MID_ACL_NO_ACL

	{"��̬���������Ϣ", "dynamic bandwidth access info"}, //CMD_MID_SLA_INFO
	{"llid", "llid"}, //CMD_MID_ONU_LLID
	{"���й̶�����", "down stream fixed bandwidth"}, //CMD_MID_DS_FIXED
	{"���з�ֵ����", "down stream peek bandwidth"}, //CMD_MID_DS_PEEK
	{"���б�֤����", "down stream committed bandwidth"}, //CMD_MID_DS_COMMITTED
	{"���й̶�����", "up stream fixed bandwidth"}, //CMD_MID_US_FIXED
	{"���з�ֵ����", "up stream peek bandwidth"}, //CMD_MID_US_PEEK
	{"���б�֤����", "up stream committed bandwidth"}, //CMD_MID_US_COMMITTED
//vlan
	{"vlanȫ����Ϣ", "vlan global information"}, //CMD_MID_VLAN_GBL_INFO
	{"���vlan id", "max vlan id"}, //CMD_MID_VLAN_ID_MAX
	{"���֧�ֵ�vlan����", "max supported vlan numbers"}, //CMD_MID_VLAN_NUM_MAX
	{"�Ѵ�����vlan����", "created vlan numbers"}, //CMD_MID_VLAN_NUM_CREATED
	{"svlan tpid", "svlan tpid"}, //CMD_MID_VLAN_SVLAN_TPID
	
	{"vlan������Ϣ", "vlan config information"}, //CMD_MID_VLAN_CFG_INFO
	{"vlan����", "vlan name"}, //CMD_MID_VLAN_NAME
	{"vlan tagged �˿�", "vlan tagged port"}, //CMD_MID_VLAN_TAG
	{"vlan untagged �˿�", "vlan untagged port"}, //CMD_MID_VLAN_UNTAG	

	{"�˿�vlan��Ϣ", "port vlan information"}, //CMD_MID_VLAN_PORT_INFO
	{"vlanЭ���ʶ", "vlan tag tpid"}, //CMD_MID_VLAN_TAGTPID
	{"vlan����ʽָʾ��", "vlan tag cfi"}, //CMD_MID_VLAN_TAGCFI
	{"vlan���ȼ�", "vlan priority"}, //CMD_MID_VLAN_PRIORITY
	{"�˿�vlan id", "port vlan id"}, //CMD_MID_VLAN_PVID
	{"vlanģʽ", "vlan mode"}, //CMD_MID_VLAN_MODE
	{"͸��ģʽ", "transparent mode"}, //CMD_MID_VLAN_MODE_TRANSPARENT
	{"tagģʽ", "tag mode"}, //CMD_MID_VLAN_MODE_TAG
	{"����ģʽ", "translation mode"}, //CMD_MID_VLAN_MODE_TRANSLATION
	{"�ۺ�ģʽ", "aggregation mode"}, //CMD_MID_VLAN_MODE_AGGREGATION
	{"trunk ģʽ", "trunk mode"}, //CMD_MID_VLAN_MODE_TRUNK
	{"access ģʽ", "access mode"}, //CMD_MID_VLAN_MODE_ACCESS
	{"qinqģʽ", "qinq mode"}, //CMD_MID_VLAN_MODE_STACKING
	{"svlan trunk ģʽ", "svlan trunk mode"}, //CMD_MID_VLAN_MODE_STRUNK
	{"vlan����", "vlan type"}, //CMD_MID_VLAN_TYPE
	{"cvlan", "cvlan"}, //CMD_MID_VLAN_TYPE_CVLAN
	{"svlan", "svlan"}, //CMD_MID_VLAN_TYPE_SVLAN
	{"configure failed, because entry is full !", "����ʧ�ܣ���Ϊ�����Ѿ�����!"}, //CMD_MID_VLAN_FULL_NOTE
//igmp
	{"igmp ��Ϣ", "igmp information"}, //CMD_MID_IGMP_INFO	
	{"igmp ʹ��", "igmp enable"}, //CMD_MID_IGMP_ENABLE
	{"igmp ģʽ", "igmp mode"}, //CMD_MID_IGMP_MODE
	{"centralized ģʽ", "centralized mode"}, //CMD_MID_IGMP_MODE_CENTRALIZED
	{"distributewithcm ģʽ", "distributewithcm mode"}, //CMD_MID_IGMP_MODE_DISTRIBUTEWITHCM
	{"�ر�", "disable mode"}, //CMD_MID_IGMP_MODE_DISABLED
	{"distributedwocm ģʽ", "distributedwocm mode"}, //CMD_MID_IGMP_MODE_DISTRIBUTEDWOCM
	{"igmp���Ӧ��ʱ��", "igmp max query response time"}, //CMD_MID_IGMP_MAXQUERESTIME
	{"igmpǿ׳��", "igmp robust"}, //CMD_MID_IGMP_ROBUST
	{"igmp������ʱ��", "igmp query interval"}, //CMD_MID_IGMP_QUEINTERVAL
	{"igmp�����Ա������ʱ��", "igmp last member query interval"}, //CMD_MID_IGMP_LASTMEMQUEINTERVAL
	{"igmp�����Ա���������", "igmp last member query count"}, //CMD_MID_IGMP_LASTMEMQUECOUNT
	{"igmp�汾", "igmp version"}, //CMD_MID_IGMP_VERSION	
	
	{"igmp��������Ϣ", "igmp proxy information"}, //CMD_MID_IGMP_PROXY_GROUP_INFO
	{"igmp��������", "igmp proxy name"}, //CMD_MID_IGMP_PROXY_GROUP_NAME
	{"igmp����Դip", "igmp proxy source ip"}, //CMD_MID_IGMP_PROXY_GROUP_SRCIP
	{"igmp�����鲥vlan��", "igmp proxy multicast vlan id"}, //CMD_MID_IGMP_PROXY_GROUP_MCASTVID
	{"igmp�����鲥ip��ַ", "igmp proxy multicast ip"}, //CMD_MID_IGMP_PROXY_GROUP_MCASTIP
	{"igmp�����鲥��֤����", "igmp proxy multicast assured bandwidth"}, //CMD_MID_IGMP_PROXY_GROUP_MCASTABW
	{"igmp�����鲥������", "igmp proxy multicast max bandwidth"}, //CMD_MID_IGMP_PROXY_GROUP_MCASTMBW
	{"igmp ת����", "igmp forwarding table"}, //CMD_MID_IGMP_FWD_INFO
//file
	{"�����ļ�������� - �ϴ�", "configure file transfer information - upload"}, //CMD_MID_FILE_CFG_UP_INFO
	{"�����ļ�������� - ����", "configure file transfer information - download"}, //CMD_MID_FILE_CFG_DOWN_INFO
	{"ϵͳ�ں˸��²���", "system kernel upgrade information"}, //CMD_MID_FILE_KERNEL_INFO
	{"�ļ�ϵͳ���²���", "filesystem upgrade information"}, //CMD_MID_FILE_FILESYS_INFO
	{"olt���²���", "olt upgrade information"}, //CMD_MID_FILE_OLT_INFO
	
	{"Э������", "protocol type"}, //CMD_MID_FILE_TRAN_PROTOCOL
	{"������ip", "server ip address"}, //CMD_MID_FILE_TRAN_IP
	{"�û���", "user name"}, //CMD_MID_FILE_TRAN_USRNAME
	{"����", "password"}, //CMD_MID_FILE_TRAN_USRPWD
	{"Դ�ļ�", "source file(include path)"}, //CMD_MID_FILE_TRAN_SRC
	{"Ŀ���ļ�", "destination file(include path)"}, //CMD_MID_FILE_TRAN_DST
	{"״̬", "status"}, //CMD_MID_FILE_TRAN_STA
	{"����", "idle"}, //CMD_MID_FILE_TRAN_STA_IDLE
	{"���ڴ���", "in progress"}, //CMD_MID_FILE_TRAN_STA_PROCESS
	{"����ɹ�", "success"}, //CMD_MID_FILE_TRAN_STA_SUCCESS
	{"����ʧ��", "failure"}, //CMD_MID_FILE_TRAN_STA_FAILED	
	{"������Դ������", "No Resource"}, //CMD_MID_FILE_TRAN_STA_NO_RESOURCE	
	{"ǿ��ֹͣONU�����ɹ�.", "stop onu tftp success!"}, //CMD_MID_FILE_TRAN_STA_STOP_SUCCESS
//sntp
	{"����ʱ��ͬ��", "SNTP information"}, //CMD_MID_SNTP_INFO
	{"����״̬", "state"}, //CMD_MID_SNTP_STA
	{"ͬ��������", "sync server"}, //CMD_MID_SNTP_SERVER
	{"ͬ�����", "sync interval"}, //CMD_MID_SNTP_INTERVAL
	{"ʱ��", "zone"}, //CMD_MID_SNTP_ZONE
//onu
    {"����", "on line"}, //CMD_MID_ON_LINE
	{"����", "off line"}, //CMD_MID_OFF_LINE
	{"onu��Ϣ�б�", "onu list information"}, //CMD_MID_ONU_LIST_INFO
	{"onu id", "onu id"}, //CMD_MID_ONU_ID
	{"Mac �ϻ�ʱ��", "Mac aging time"}, //CMD_MID_ONU_MAC_AGING
	{"оƬ����", "chip vendor"}, //CMD_MID_ONU_CHIP_VENDOR
	{"оƬ�ͺ�", "chip type"}, //CMD_MID_ONU_CHIP_TYPE
	{"оƬ�汾", "chip version"}, //CMD_MID_ONU_CHIP_VER
	{"����汾", "software version"}, //CMD_MID_ONU_SFTWR_VER
	{"�̼��汾", "firmware version"}, //CMD_MID_ONU_FRMWR_VER
	{"����", "distance"}, //CMD_MID_ONU_DISTANCE
	{"ע��ʱ��", "register time"}, //CMD_MID_ONU_REG_TIME
	{"onu ģ��", "profile"},//CMD_MID_ONU_PROFILE
	{"���ȼ�", "priority"}, //CMD_MID_PRIORITY
	{"Trap IP", "Trap IP"}, //CMD_MID_ONU_TRAP_IP
	{"����", "down"}, //CMD_MID_POWER_DOWN
	{"��֤�ܾ�", "auth reject"}, //CMD_MID_ONU_STATUS_AUTH_REJECT

	{"�Զ���ȡip��ַ", "DHCP"}, //CMD_MID_DHCP
	{"��", "yes"}, //CMD_MID_YES
	{"��", "no"}, //CMD_MID_NO
	{"��mac", "Bind mac"}, //CMD_MID_BIND_MAC
	{"���� %u �\r\n", "there are %u entries.\r\n"}, //CMD_MID_THERE_ARE
	{"onu", "onu"}, //CMD_MID_ONU
	
	{"ONU��PON�˿ڹ⴫������", "onu optical trans information"}, //CMD_MID_ONU_OPT_TRANS_INFO
	{"����չ���", "received optical power"}, //CMD_MID_ONU_OPT_REC_POWER
	{"�ⷢ�书��", "transmitted optical power"}, //CMD_MID_ONU_OPT_TRANS_POWER
	{"ƫ�õ���", "bias current"}, //CMD_MID_ONU_BIAS_CURRENT
	{"������ѹ", "working voltage"}, //CMD_MID_ONU_WORK_V
	{"�����¶�", "working temparature"}, //CMD_MID_ONU_WORK_T
	{"fecʹ��", "fec enable"}, //CMD_MID_FEC_ENABLE
	
	{"ONU����������", "onu capability information"}, //CMD_MID_ONU_CAP_INFO
	{"GE��", "GE port num"}, //CMD_MID_ONU_GE_NUM
	{"GE bitͼ", "GE port bitmap"}, //CMD_MID_ONU_GE_BMP
	{"FE��", "FE port num"}, //CMD_MID_ONU_FE_NUM
	{"FE bitͼ", "FE port bitmap"}, //CMD_MID_ONU_FE_BMP
	{"���ж�����", "queue num uplink"}, //CMD_MID_ONU_QUE_NUM_UP
	{"���ж˿���������", "max queue num uplink"}, //CMD_MID_ONU_QUE_NUM_UP_MAX
	{"���ж�����", "queue num downlink"}, //CMD_MID_ONU_QUE_NUM_DOWN
	{"���ж˿���������", "max queue num downlink"}, //CMD_MID_ONU_QUE_NUM_DOWN_MAX
	
	{"ONU�İ�ȫ����", "onu auth policy"}, //CMD_MID_ONU_AUTH_POLICY
	{"������ģʽ", "Blacklist"}, //CMD_MID_ONU_BLACK_LIST
	{"������ģʽ", "Whitelist"}, //CMD_MID_ONU_WHITE_LIST
	{"����ע����������", "Accept all"}, //CMD_MID_ONU_ACCEPT_ALL
	{"ONU����֤��Ϣ: �ڡ�������ģʽ�������б�", "ONU registration information"}, //CMD_MID_ONU_AUTH_INFO
	{"������", "Index"}, //CMD_MID_INDEX
	{"��Ȩ��Ϊ", "auth action"}, //CMD_MID_ONU_AUTH_ACTION
	{"�ܾ�", "reject"}, //CMD_MID_ONU_AUTH_REJECT
	{"����", "accept"}, //CMD_MID_ONU_AUTH_ACCEPT
	{"ONU�ĺڡ���״̬", "ONU registration mode"}, //CMD_MID_ONU_AUTH_MODE
	{"ģʽ", "mode"}, //CMD_MID_MODE
	{"��֤�����ѱ��ܾ���ONU�б�", "ONU rejected list"}, //CMD_MID_ONU_AUTH_REJECT_LIST

	{"onu����״̬", "onu upgrade status"}, //CMD_MID_ONU_UPGRADE_STATUS
	{"onu״̬", "onu status"}, //CMD_MID_ONU_STATUS
	{"�ȴ�����", "Wait for the upgrade"}, //CMD_MID_ONU_WAIT_UPGRADE
	{"����ʧ��", "Upgrade failed"}, //CMD_MID_ONU_UPGRADE_FAILED
	{"�����ɹ�", "Upgrade successed"}, //CMD_MID_ONU_UPGRADE_SUCCESSED
	{"�����л����", "Partition switch finished"}, //CMD_MID_ONU_UPGRADE_SWITCH_FINISHED
	{"ģ�����", "profile id"},//CMD_MID_ONU_PROFILE_ID
	{"ģ������", "profile name"},//	CMD_MID_ONU_PROFILE_NAME
	{"onu������", "onu_num"},//CMD_MID_ONU_PROFILE_ONU_NUM
	
//uni
	{"UNI", "UNI"}, //CMD_MID_UNI
	{"��������Ӧ����", "local auto negotiationa bility"}, //CMD_MID_AUTO_NEGO_ABL_LOCAL
	{"Զ������Ӧ����", "remote auto negotiationa bility"}, //CMD_MID_AUTO_NEGO_ABL_REMOTE
	{"����Ӧ����", "auto negotiationa restart"}, //CMD_MID_AUTO_NEGO_RESTART

	{"1- ʮ��ȫ˫��", "1- tenBaseTFullDuplex"}, //CMD_MID_AUTO_NEGO_ABL_F10
	{"2- ʮ�װ�˫��", "2- tenBaseTHalfDuplex"}, //CMD_MID_AUTO_NEGO_ABL_H10
	{"3- ����ȫ˫��", "3- hundredBaseTFullDuplex"}, //CMD_MID_AUTO_NEGO_ABL_F100
	{"4- ���װ�˫��", "4- hundredBaseTHalfDuplex"}, //CMD_MID_AUTO_NEGO_ABL_H100
	{"5- ǧ��ȫ˫��", "5- thousandBaseTFullDuplex"}, //CMD_MID_AUTO_NEGO_ABL_F1000
	{"6- ǧ�װ�˫��", "6- thousandBaseTHalfDuplex"}, //CMD_MID_AUTO_NEGO_ABL_H1000
	{"7- thousandBaseXFullDuplex", "7- thousandBaseXFullDuplex"}, //CMD_MID_AUTO_NEGO_ABL_F1000X
	{"8- thousandBaseXHalfDuplex", "8- thousandBaseXHalfDuplex"}, //CMD_MID_AUTO_NEGO_ABL_H1000X
	{"9- fdxPause", "9- fdxPause"}, //CMD_MID_AUTO_NEGO_ABL_FDX
	{"10-fdxApause", "10-fdxApause"}, //CMD_MID_AUTO_NEGO_ABL_FDXA
	{"11-fdxSpause", "11-fdxSpause"}, //CMD_MID_AUTO_NEGO_ABL_FDXS
	{"12-fdxBpause", "12-fdxBpause"}, //CMD_MID_AUTO_NEGO_ABL_FDXB	
	
	{"UNI�˿�����", "UNI attribute"}, //CMD_MID_UNI_ATTR
	{"ONU��Ϊ %d��", "the onu id is %d.\r\n"}, //CMD_MID_ONU_ID_IS	
	{"MAC �����ϻ���", "MAC non-aging.\r\n"}, //CMD_MID_NON_AGING
	{"MAC �ϻ�ʱ��Ϊ %d �롣", "aging time is %d second.\r\n"}, //CMD_MID_AGING_TIME_IS
	{"��̬MAC��ַ��", "static mac address table"}, //CMD_MID_STATIC_MAT
	{"��̬MAC��ַ��", "dynamic mac address table"}, //CMD_MID_DYNAMIC_MAT
	{"�˿����̬mac��ַѧϰ����", "port maximum dynamic mac learn count"},//CMD_MID_MAX_LRN
	{"ֻ��sni���ܹ����þ�̬mac��ַ", "just sni port can configure static mac address"},//CMD_MID_SNI_STATIC_MAC
	{"ֻ�е���mac�ܹ�����Ϊ��̬����", "just unicast mac can configure to static mac address"},//CMD_MID_MUTI_MAC_NOT_STATIC
	{"����ʧ�ܣ���Ϊ��������!","configure failed, because table is full!"},//CMD_MID_MAC_FULL_NOTE
	
	{"UNI �˿�����������Ϣ", "uni port rate-limite information"}, //CMD_MID_UNI_RATE_LIMIT
	{"CIR(kbps)", "CIR(kbps)"}, //CMD_MID_CIR
	{"CBS(kbps)", "CBS(kbps)"}, //CMD_MID_CBS
	{"EBS(kbps)", "EBS(kbps)"}, //CMD_MID_EBS
	{"PIR(kbps)", "PIR(kbps)"}, //CMD_MID_PIR
	{"����״̬", "link status"}, //CMD_MID_LINK_STATUS
//statistics
	{"ͳ��������Ϣ", "statistics configure information"}, //CMD_MID_STATS_CONF_INFO
	{"15��������ͳ������¼��", "15 minutes max record"}, //CMD_MID_STATS_M15_MAX
	{"24Сʱ����ͳ������¼��", "1-day max record"}, //CMD_MID_STATS_H24_MAX
	{"ͳ����Ŀ", "name"}, //CMD_MID_STATS_NAME
	{"����", "in"}, //CMD_MID_STATS_IN
	{"����", "out"}, //CMD_MID_STATS_OUT
	{"�ֽ���", "octets"}, //CMD_MID_STATS_OCTS
	{"֡��", "packets"}, //CMD_MID_STATS_PKTS
	{"�㲥֡��", "brodcast packets"}, //CMD_MID_STATS_PKTS_BROD
	{"�鲥֡��", "multcast packets"}, //CMD_MID_STATS_PKTS_MULT
	{"����Ϊ(64)�ֽڰ���", "packets(64)B"}, //CMD_MID_STATS_PKTS_64
	{"����Ϊ(65~127)�ֽڰ���", "packets(65~127)B"}, //CMD_MID_STATS_PKTS_65_127
	{"����Ϊ(128~255)�ֽڰ���", "packets(128~255)B"}, //CMD_MID_STATS_PKTS_128_255
	{"����Ϊ(256~511)�ֽڰ���", "packets(256~511)B"}, //CMD_MID_STATS_PKTS_256_511
	{"����Ϊ(512~1023)�ֽڰ���", "packets(512~1023)B"}, //CMD_MID_STATS_PKTS_512_1023
	{"����Ϊ(1024~1518)�ֽڰ���", "packets(1024~1518)B"}, //CMD_MID_STATS_PKTS_1024_1518
	{"����Ϊ(1519~1522)�ֽڰ���", "packets(1519~1522)B"}, //CMD_MID_STATS_PKTS_1519_1522
	{"����֡��", "undersize packets"}, //CMD_MID_STATS_PKTS_UNDERSIZE
	{"����֡��", "oversize packets"}, //CMD_MID_STATS_PKTS_OVERSIZE
	{"��Ƭ��", "fragments"}, //CMD_MID_STATS_FRAGMENTS
	{"MPCP ֡��", "MPCP frames"}, //CMD_MID_STATS_MPCP_FRMS
	{"MPCP �ֽ���", "MPCP octets"}, //CMD_MID_STATS_MPCP_OCTS
	{"OAM ֡��", "OAM frames"}, //CMD_MID_STATS_OAM_FRMS
	{"OAM �ֽ���", "OAM octets"}, //CMD_MID_STATS_OAM_OCTS
	{"CRC ����֡��", "CRC error packets"}, //CMD_MID_STATS_PKTS_CRC_ERR
	{"�����¼�����", "drop events"}, //CMD_MID_STATS_DROP_EVTS
	{"��������֡��", "jabbers"}, //CMD_MID_STATS_JABBERS
	{"��ײ֡��", "collisions"}, //CMD_MID_STATS_COLLISIONS
	
	{"����������", "discard frames"},//CMD_MID_STATS_PKTS_DISCARD
	{"��������", "error frames"},//CMD_MID_STATS_PKTS_ERR
	{"�˿�״̬�仯����", "port status change times"},//CMD_MID_STATS_STATUS_CHG_TIMES
	
	{"ͳ��ʹ��", "statistic enable"}, //CMD_MID_STATS_ENABLE	
	{"ͳ������", "statistic period"}, //CMD_MID_STATS_PERIOD
	
	{"ʵʱͳ����������", "current statistics data"}, //CMD_MID_STATS_INFO_CUR
	{"��ʷͳ����������", "history statistics data"}, //CMD_MID_STATS_INFO_HISTORY
	{"�Ƿ���Ч", "is valid"}, //CMD_MID_STATS_IS_VALID
	{"��ʼʱ��", "start time"}, //CMD_MID_STATS_START_TIME
	{"����ʱ��", "end time"}, //CMD_MID_STATS_END_TIME
	{"15����ͳ����������", "15 minutes statistics data"}, //CMD_MID_STATS_INFO_M15
	{"24Сʱͳ����������", "1-day statistics data"}, //CMD_MID_STATS_INFO_H24
	{"���� %d ���ǰΪ %d ��\r\n", "there are %d entries, current is %d.\r\n"}, //CMD_MID_STATS_CUR_IS
	
	{"ͳ��������Ϣ", "statistics threshold information"}, //CMD_MID_STATS_INFO_THRESHOLD
//ppg
	{"pon�˿ڱ�������Ϣ", "protect group information"}, //CMD_MID_PPG_INFO
	{"��ID", "GID"}, //CMD_MID_PPG_ID
	{"��/��", "on/off"}, //CMD_MID_PPG_ENABLE
	{"��", "on"}, //CMD_MID_ON
	{"��", "off"}, //CMD_MID_OFF
	{"���ö˿�", "main-Port"}, //CMD_MID_PPG_PORT_MAIN
	{"���ö˿�", "backup-Port"}, //CMD_MID_PPG_PORT_BACKUP
	{"�л���ʽ", "switch-mode"}, //CMD_MID_PPG_SWITCH_MODE
	{"�Զ�", "auto"}, //CMD_MID_AUTO
	{"�ֶ�", "manual"}, //CMD_MID_MANUAL
	{"�鹤��״̬", "group-status"}, //CMD_MID_PPG_STATUS
	{"��", "primary"}, //CMD_MID_PPG_PRIMARY
	{"��", "secondary"}, //CMD_MID_PPG_SECONDARY
	{"δ����", "unlock"}, //CMD_MID_PPG_UNLOCK
	{"�Զ��ָ�ʱ��", "recover-time"}, //CMD_MID_PPG_RECOVER_TIME
//qos
	{"�豸��", "Device ID"}, //CMD_MID_DEVICE_ID
	{"��������", "Max queue count"}, //CMD_MID_QOS_QUE_MAX
	{"QOS����ģʽ", "Qos mode"}, //CMD_MID_QOS_MODE
	{"���ڶ˿�", "port based"}, //CMD_MID_QOS_BASED_PORT
	{"�����豸", "device based"}, //CMD_MID_QOS_BASED_DEVICE
	{"QOSȫ��������Ϣ", "qos global information"}, //CMD_MID_QOS_GBL_INFO

	{"����!!!�������ȼ�[%d]����Ч��!\r\n", "error!!! the priority number[%d] is invalid!\r\n"}, //CMD_MID_QOS_PRI_ERR
	{"�����豸ģʽ���������ȫ��ģʽ!\r\n", "device based, you must go to CONFIG mode!\r\n"}, //CMD_MID_QOS_GO_CFG_MODE
	{"����!!!��������ģʽ��\r\n", "error!!!other command mode. \r\n"}, //CMD_MID_QOS_CMD_MODE_ERR
	{"����!!!δ֪QOSģʽ��\r\n", "error!!!unknown qos mode.\r\n"}, //CMD_MID_QOS_MODE_ERR
	
	{"QOSӳ�����", "Qos map rule"}, //CMD_MID_QOS_MAP_RULE
	{"COS", "COS"}, //CMD_MID_QOS_COS
	{"TOS", "TOS"}, //CMD_MID_QOS_TOS
	{"DSCP", "DSCP"}, //CMD_MID_QOS_DSCP
	{"���ȼ����ֵ", "max priority number"}, //CMD_MID_QOS_PRI_MAX
	{"QOS����ӳ��", "Qos map queue"}, //CMD_MID_QOS_MAP_QUE
	{"QOS����ӳ����Ϣ", "qos map information"}, //CMD_MID_QOS_MAP_INFO
	
	{"QOS������Ϣ", "qos scheduler policy information"}, //CMD_MID_QOS_SCHE_INFO
	{"QOS���Ȳ���", "Qos policy type"}, //CMD_MID_QOS_SCHE_POLICY
	{"SP", "SP"}, //CMD_MID_QOS_SP
	{"WRR", "WRR"}, //CMD_MID_QOS_WRR
	{"SPWRR", "SPWRR"}, //CMD_MID_QOS_SPWRR
	{"WFP", "WFP"}, //CMD_MID_QOS_WFP
	{"Ȩ��", "weight value"}, //CMD_MID_QOS_WEIGHT_VALUE
	{"����!!!����Ȩ���б�[%s]����Ч�ġ�\r\n", "error! Input weight list is invalid, List=%s.�\r\n"},//CMD_MID_QOS_WEIGHT_VALUE_INVALID
	{"ת��Ȩ���б�Ϊ: ", "change weight list: "},//CMD_MID_QOS_CHANGE_WEIGHT_LIST

//alarm
	{"�澯����", "trap information"}, //CMD_MID_TRAP_INFO
	{"�澯�ܿ���", "trap enable"}, //CMD_MID_TRAP_ENABLE

	{"ȷ��", "cf"}, //CMD_MID_CONFIRM
	{"�澯����", "alarm description"}, //CMD_MID_ALARM_DESP
	{"���ؼ���", "Severity"}, //CMD_MID_SEVERITY
	{"����", "Critical"}, //CMD_MID_CRITICAL
	{"����", "Major"}, //CMD_MID_MAJOR
	{"��΢", "Minor"}, //CMD_MID_MINOR
	{"����", "Warning"}, //CMD_MID_WARNING
	{"��Ϣ", "Info"}, //CMD_MID_INFO
	{"���", "Clear"}, //CMD_MID_CLEAR

	{"��ʼ����ʱ��", "First time"}, //CMD_MID_FIRST_TIME
	{"�����ʱ��", "Last time"}, //CMD_MID_LAST_TIME
	{"��������", "additional info"}, //CMD_MID_ADD_TEXT
	{"ʵʱ�澯��Ϣ", "current alarm information"}, //CMD_MID_ALARM_INFO_CURRENT
	{"��ʷ�澯��Ϣ", "history alarm information"}, //CMD_MID_ALARM_INFO_HISTORY	
	{"�¼���־", "event log"}, //CMD_MID_ALARM_INFO_EVENT
	
	{"δ֪�澯����", "unknown alarm code"}, //CMD_MID_ALARM_UNKNOWN
	{"�忨�����Զ�����ʧ��", "boardProvisionFail"}, //CMD_MID_ALARM_BOARD_PROVISION_FAIL
	{"�忨����", "boardReset"}, //CMD_MID_ALARM_BOARD_RESET
	{"�忨���γ�", "boardRemoval"}, //CMD_MID_ALARM_BOARD_REMOVEL
	{"�忨�¶��쳣", "boardTempAbnormal"}, //CMD_MID_ALARM_BOARD_TEMP_ABNORMAL
	{"�豸���ȹ���", "fanFailed"}, //CMD_MID_ALARM_FAN_FAILED
	{"�豸���ȿ򱻰γ�", "fanRemoval"}, //CMD_MID_ALARM_FAN_REMOCAL
	{"�豸��Դģ���쳣", "powerFailed"}, //CMD_MID_ALARM_POWER_FAILED
	{"��Դģ�鱻�γ�", "powerRemoval"}, //CMD_MID_ALARM_POWER_REMOVAL
	{"оƬ�̼���������", "fatalOLTHwError"}, //CMD_MID_ALARM_FATAL_OLT_HW_ERROR

	{"OLT PON��ģ��ʧЧ", "oltPonOpticalModuleFaulty"}, //CMD_MID_ALARM_PON_OPT_FAULTY
	{"OLT SNI��ģ��ʧЧ", "oltSniOpticalModuleFaulty"}, //CMD_MID_ALARM_SNI_OPT_FAULTY
	{"OLT PON��link״̬", "oltPonLink"}, //CMD_MID_ALARM_PON_LINK_FAULTY
	{"OLT SNI��link״̬", "oltSniLINK"}, //CMD_MID_ALARM_SNI_LINK_FAULTY
	{"OLT PON�ڹ��źŶ�ʧ", "OltPonRLos"}, //CMD_MID_ALARM_PON_RLOS
	{"OLT SNI�ڹ��źŶ�ʧ", "OltSniRLos"}, //CMD_MID_ALARM_SNI_RLOS	

	{"OLT���յ��Ķ����¼����������õĸ澯����ʱ�ϱ�", "Olt DownstreamDropEventsAlarm"}, //CMD_MID_OLT_DOWNSTREAMDROPEVENTSALARM
	{"OLTδ���͵Ķ����¼����������õĸ澯����ʱ�ϱ�", "Olt UpstreamDropEventsAlarm"}, //CMD_MID_OLT_UPSTREAMDROPEVENTSALARM
	{"OLT���յ���CRC���������������õĸ澯����ʱ�ϱ�", "Olt DownstreamCrcerrorFramesAlarm"}, //CMD_MID_OLT_DOWNSTREAMCRCERRORFRAMESALARM
	{"OLT���յ��ĳ��̱������������õĸ澯����ʱ�ϱ�", "Olt DownstreamUndersizeFramesAlarm"}, //CMD_MID_OLT_DOWNSTREAMUNDERSIZEFRAMESALARM
	{"OLT���͵ĳ��̱������������õĸ澯����ʱ�ϱ�", "Olt UpstreamUndersizeFramesAlarm"}, //CMD_MID_OLT_UPSTREAMUNDERSIZEFRAMESALARM
	{"OLT���յ��ĳ����������������õĸ澯����ʱ�ϱ�", "Olt DownstreamOversizeFramesAlarm"}, //CMD_MID_OLT_DOWNSTREAMOVERSIZEFRAMESALARM
	{"OLT���͵ĳ����������������õĸ澯����ʱ�ϱ�", "Olt UpstreamOversizeFramesAlarm"}, //CMD_MID_OLT_UPSTREAMOVERSIZEFRAMESALARM
	{"OLT���յ���Fragments���������õĸ澯����ʱ�ϱ�", "Olt DownstreamFragmentsAlarm"}, //CMD_MID_OLT_DOWNSTREAMFRAGMENTSALARM
	{"OLT���յ���Jabbers���������õĸ澯����ʱ�ϱ�", "Olt DownstreamJabbersAlarm"}, //CMD_MID_OLT_DOWNSTREAMJABBERSALARM
	{"OLT���յ��ĳ�ͻ�����������õĸ澯����ʱ�ϱ�", "Olt DownstreamCollistonsAlarm"}, //CMD_MID_OLT_DOWNSTREAMCOLLISIONSALARM
	{"OLT���յ��Ķ����������������õĸ澯����ʱ�ϱ�", "Olt DownstreamDiscardFramesAlarm"}, //CMD_MID_OLT_DOWNSTREAMDISCARDFRAMESALARM
	{"OLTδ���͵Ķ����������������õĸ澯����ʱ�ϱ�", "Olt UpstreamDiscardFramesAlarm"}, //CMD_MID_OLT_UPSTREAMDISCARDFRAMESALARM
	{"OLT���յ��Ĵ��������������õĸ澯����ʱ�ϱ�", "Olt DownstreamErrorFramesAlarm"}, //CMD_MID_OLT_DOWNSTREAMERRORFRAMESALARM
	

//stp
	{"stp������������Ϣ", "stp bridge information"}, //CMD_MID_STP_BR_INFO
	{"������", "bridge"}, //CMD_MID_STP_BRIDGE
	{"Э��汾", "version"}, //CMD_MID_STP_VER
	{"SSTP", "SSTP"}, //CMD_MID_SSTP
	{"RSTP", "RSTP"}, //CMD_MID_RSTP
	{"MSTP", "MSTP"}, //CMD_MID_MSTP
	{"���ȼ�", "priority"}, //CMD_MID_STP_PRI
	{"���ʱ��", "last topology change"}, //CMD_MID_STP_CHG_TIME
	{"�������", "topology changes"}, //CMD_MID_STP_CHG_COUNT
	{"��·������", "root path cost"}, //CMD_MID_STP_ROOT_PATH_COST
	{"�ϻ�ʱ��", "max age"}, //CMD_MID_STP_MAX_AGE
	{"���ķ��ͼ��ʱ��", "hello time"}, //CMD_MID_STP_HELLO_TIME
	{"ռ��ʱ��", "hold time"}, //CMD_MID_STP_HOLD_TIME
	{"ת��ʱ��", "forward delay"}, //CMD_MID_STP_FWD_DELAY
	{"ÿ����෢�� BPDU ����", "Transmit Hold Count"}, //CMD_MID_STP_TXHOLD_CNT
	{"�����ŵ��ϻ�ʱ��", "root max age"}, //CMD_MID_STP_ROOT_MAX_AGE
	{"�����ŵı��ķ��ͼ��ʱ��", "root hello time"}, //CMD_MID_STP_ROOT_HELLO_TIME
	{"�����ŵ�ת��ʱ��", "root forward delay"}, //CMD_MID_STP_ROOT_FWD_DELAY	
	{"·�������㷨", "pathcost method"}, //CMD_MID_STP_COST_METHOD

//igmp configure
	{"�鲥vlan��Ϣ", "multicast vlan information"}, //CMD_MID_VLAN_MULTICAST_INFO
	{"vlan�ŵķ�Χ", "vlan id range"}, //CMD_MID_VLAN_ID_RANGE
	{"�鲥vlan�˿���Ϣ", "multicast vlan port information"}, //CMD_MID_VLAN_MULTICAST_PORT_INFO
	{"�鲥vlan��", "multicast vlan id"}, //CMD_MID_VLAN_MULTICAST_ID
	{"Igmp mcst vlan �˿���Ϣ", "Igmp mcst vlan port information"}, //CMD_MID_VLAN_MCST_IGMP_PORT_INFO
	
	{"�ɿ��鲥����Ϣ", "Controlled multicast packages information"}, //CMD_MID_MULTICAST_CONTROL_PKG_INFO
	{"ҵ�������", "package index"}, //CMD_MID_PKG_INDEX
	{"ҵ�����", "package name"}, //CMD_MID_PKG_NAME
	{"�����б�", "proxy list"}, //CMD_MID_IGMP_PROXY_LIST
	{"�鲥�����û�����Ȩ��", "multicast user authority"}, //CMD_MID_IGMP_MULTICAST_USER_AUTHORITY
	{"�鲥������������Ŀ��", "max request channel num"}, //CMD_MID_IGMP_MAX_REQUEST_CHANNEL_NUM
	{"�鲥���ĵ���Ԥ��ʱ��", "single preview time"}, //CMD_MID_IGMP_SINGLE_PREVIEW_TIME
	{"�鲥����Ԥ����ʱ��", "total preview time"}, //CMD_MID_IGMP_TOTAL_PREVIEW_TIME
	{"�鲥����Ԥ����λʱ��", "preview reset time"}, //CMD_MID_IGMP_PREVIEW_RESET_TIME
	{"�鲥����Ԥ������", "preview count"}, //CMD_MID_IGMP_PREVIEW_COUNT

	{"�û��ɿ��鲥����Ϣ", "Controlled multicast user authority information"}, //CMD_MID_IGMP_MULTICAST_USER_AUTHORITY_INFO
	{"package list", "ҵ����б�"}, //CMD_MID_PKG_LIST
	{"igmp�鲥ҵ��������", "igmp global bw"}, //CMD_MID_IGMP_GLOBAL_BW
	{"igmp�鲥ҵ��ʹ�ô���", "igmp global bw used"}, //CMD_MID_IGMP_GLOBAL_BW_USED

//file-system
	{"ϵͳ��Ϣ", "system information"}, //CMD_MID_FILE_SYS_INFO
	{"ϵͳ��������", "system partition index"}, //CMD_MID_SYS_INDEX
	{"ϵͳ������־", "system start flag"}, //CMD_MID_SYS_START_FALG
	{"����ϵͳ��Ϣ", "detailed system information"}, //CMD_MID_SYS_INFO

	{"olt�˿�������Ϣ", "olt interface rate-limit information"}, //CMD_MID_OLT_INTERFACE_RATE_INFO
	{"�˿ڸ�����Ϣ", "interface isolation information"}, //CMD_MID_OLT_INTERFACE_ISOT_INFO

//onu max distance
	{"pon�˿�onu������", "olt pon onu max distance"}, //CMD_MID_OLT_PON_ONU_MAX_DISTANCE

//snmp community 
	{"SNMP�����������������Ϣ", "snmp server community list info"}, //CMD_MID_SNMP_COMMUNITY_LIST_INFO
	{"������", "community name"}, //CMD_MID_COMMUNITY_NAME
	{"����Ȩ��", "permission"}, //CMD_MID_COMMUNITY_PERMISSION

	{"��֧��", "Not Supported"}, //CMD_MID_NOTSUPPORT
//	{"", ""}//CMD_MID_NULL
};



const char* bc_cli_menu_thresholdtype[CMD_TRSD_TYPE_MAX][CMD_ML_MAXNUM] = 
{
	{"0   ��������               ", "0   Error                           "},  
	{"1   ���ж����¼��澯       ", "1   DownstreamDropEventsAlarm       "},  
	{"2   ���ж����¼��澯       ", "2   UpstreamDropEventsAlarm         "},  
	{"3   ����CRC����֡�澯      ", "3   DownstreamCRCErrorFramesAlarm   "},  
	{"4   ���й�С֡�澯         ", "4   DownstreamUndersizeFramesAlarm  "},  
	{"5   ���й�С֡�澯         ", "5   UpstreamUndersizeFramesAlarm    "},  
	{"6   ���й���֡�澯         ", "6   DownstreamOversizeFramesAlarm   "},  
	{"7   ���й���֡�澯         ", "7   UpstreamOversizeFramesAlarm     "},  
	{"8   ������Ƭ�澯           ", "8   DownstreamFragmentsAlarm        "},  
	{"9   �������޸澯           ", "9   DownstreamJabbersAlarm          "},  
	{"10  ���г�ͻ�澯           ", "10  DownstreamCollisionsAlarm       "},  
	{"11  ���ж���֡�澯         ", "11  DownstreamDiscardFramesAlarm    "},  
	{"12  ���ж���֡�澯         ", "12  UpstreamDiscardFramesAlarm      "},  
	{"13  ���д���֡�澯         ", "13  DownstreamErrorFramesAlarm      "},  
	{"14  ���д���֡�澯         ", "14  UpstreamErrorFramesAlarm        "},  
	{"15  ״̬�ı�����澯       ", "15  StatusChangeTimesAlarm          "},  
	{"16  ���ж����¼�����       ", "16  DownstreamDropEventsWarning     "},  
	{"17  ���ж����¼�����       ", "17  UpstreamDropEventsWarning       "},  
	{"18  ����CRC����֡����      ", "18  DownstreamCRCErrorFramesWarning "},  
	{"19  ���й�С֡����         ", "19  DownstreamUndersizeFramesWarning"},  
	{"20  ���й�С֡����         ", "20  UpstreamUndersizeFramesWarning  "},  
	{"21  ���й���֡����         ", "21  DownstreamOversizeFramesWarning "},  
	{"22  ���й���֡����         ", "22  UpstreamOversizeFramesWarning   "},  
	{"23  ������Ƭ����           ", "23  DownstreamFragmentsWarning      "},  
	{"24  ������������           ", "24  DownstreamJabbersWarning        "},  
	{"25  ���г�ͻ����           ", "25  DownstreamCollisionsWarning     "},  
	{"26  ���ж���֡����         ", "26  DownstreamDiscardFramesWarning  "},  
	{"27  ���ж���֡����         ", "27  UpstreamDiscardFramesWarning    "},  
	{"28  ���д���֡����         ", "28  DownstreamErrorFramesWarning    "},  
	{"29  ���д���֡����         ", "29  UpstreamErrorFramesWarning      "},  
	{"30  ״̬�ı��������       ", "30  StatusChangeTimesWarning        "},
};
#endif


/* 
 *	�ڲ�ȫ�ֱ�����ֻ�ṩ�����ļ��ڲ��������ã�����ͷ�ļ����ṩ���ýӿڡ�
 */

//static unsigned int l_mdl_id = CLI_SHELL_MODULE;



////////////////////////////////////////////////////////////////////////////////
//																			  //
//								��  ��  ��  ��								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//																			  //
//								��  ��  ��  ��								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
/******************************************************************************\
  Function   : 
  Description: 
  Return     : 
  Others     : 
\******************************************************************************/



/* 
 *	Ԥ��һ��ע�����ļ����
 */
/******************************************************************************\
  Function   : 
  Description: 
  Return     : 
  Others     : 
\******************************************************************************/



