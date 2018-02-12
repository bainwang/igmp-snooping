/*******************************************************************************
  -------------------------------------------------------------------------
  [File name]  : \\BC\cli\cli_cmds\bc_cli_text.h
  [Author]     : bain.wang@outlook.com
  [Version]    : 1.0
  [Date]       : 2017-07-02
  [Description]:

  [Others]     :

  [Function List]:
	1. ....
	2. ....
  [History]:
	 D a t e	Modification										  Initials
	---------- --------------										 ----------
	2016-06-25  modified											  bain.wang@outlook.com
	2017-11-30  modified												yest
	2017-07-02  Modified                                              bain.wang@outlook.com
	2017-06-28	Created 											  bain.wang@outlook.com
*******************************************************************************/

#ifndef __INC_BC_CLI_TEXT_H__
#define __INC_BC_CLI_TEXT_H__

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								ͷ   ��   ��								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//																			  //
//								��   ��   ��								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#define CMD_HELP_KEY_CN_					"��\r\n"


#define CMD_HELP_KEY_CN_ABILITY				"����Ӧ������\r\n"
#define CMD_HELP_KEY_CN_ACL					"ACL��������\r\n"
#define CMD_HELP_KEY_CN_ACL_GROUP			"�˿ڰ�ACL��\r\n"
#define CMD_HELP_KEY_CN_ACL_GROUP_BY_INDEX	"ͨ��ACL�����Ŷ˿ڰ�ACL.\r\n"
#define	CMD_HELP_KEY_CN_ACL_GROUP_BY_NAME	"ͨ��ACL���ƶ˿ڰ�ACL.\r\n"
#define CMD_HELP_KEY_CN_ACL_RULE			"Acl���ʹ���\r\n"
#define CMD_HELP_KEY_CN_ADD					"#��ӡ�\r\n#"
#define CMD_HELP_KEY_CN_ADDRESS				"��ַ(MAC, ip��ַ)��\r\n"
#define CMD_HELP_KEY_CN_ADMIN_STATUS		"����״̬��\r\n"
#define CMD_HELP_KEY_CN_AES32				"����PON�ڵļ���ģʽΪAES 32ģʽ��\r\n"		
#define CMD_HELP_KEY_CN_AES48				"����PON�ڵļ���ģʽΪAES 48ģʽ��\r\n"	
#define CMD_HELP_KEY_CN_AES128				"����PON�ڵļ���ģʽΪAES 128ģʽ��\r\n"	
#define CMD_HELP_KEY_CN_AGING_TIME			"MAC��ַѧϰ���ϻ�ʱ�䡣\r\n"
#define CMD_HELP_KEY_CN_AGGREGATION			"vlan�ۺ�ģʽ��\r\n"
#define CMD_HELP_KEY_CN_ALARM				"�澯��Ϣ����\r\n"
#define CMD_HELP_KEY_CN_ALL					"#ȫ����Ϣ��\r\n#"
#define CMD_HELP_KEY_CN_ANY					"����ֵ��\r\n"
#define CMD_HELP_KEY_CN_ARP					"ARPЭ�顣\r\n"
#define CMD_HELP_KEY_CN_ATTRIBUTE			"�˿����ԡ�\r\n"
#define CMD_HELP_KEY_CN_AUTO_NEGO			"����Ӧ��\r\n"
#define CMD_HELP_KEY_CN_AUTO_NEGO_AUTO		"�Զ���\r\n"
#define CMD_HELP_KEY_CN_AUTO_NEGO_H10		"Half-10:ʮ�װ�˫����\r\n"
#define CMD_HELP_KEY_CN_AUTO_NEGO_F10		"Full-10:ʮ��ȫ˫����\r\n"
#define CMD_HELP_KEY_CN_AUTO_NEGO_H100		"Half-100:���װ�˫����\r\n"
#define CMD_HELP_KEY_CN_AUTO_NEGO_F100		"Full-100:����ȫ˫����\r\n"
#define CMD_HELP_KEY_CN_AUTO_NEGO_F1000		"Full-1000:ǧ��ȫ˫����\r\n"
#define CMD_HELP_KEY_CN_AUTO_NEGO_F10000	"Full-10000:����ȫ˫����\r\n"

#define CMD_HELP_KEY_CN_BACKUP				"�������á���������ļ���.\r\n"
#define CMD_HELP_KEY_CN_BANDWIDTH			"#����\r\n#"
#define CMD_HELP_KEY_CN_BASED				"�����豸/�˿ڡ�\r\n"
#define CMD_HELP_KEY_CN_BLACK				"������ģʽ��\r\n"
#define CMD_HELP_KEY_CN_BLOCK				"�ܾ���Ȩ������\r\n"
#define CMD_HELP_KEY_CN_BOARD				"olt���忨��\r\n"
#define CMD_HELP_KEY_CN_BOTH				"�����˫��\r\n"
#define CMD_HELP_KEY_CN_BRIEF				"������Ϣ�б�\r\n"

#define CMD_HELP_KEY_CN_CAPABILITY			"���ܡ�\r\n"//??
#define CMD_HELP_KEY_CN_CBS					"CBS:��֤ͻ��Ͱ�\r\n"
#define CMD_HELP_KEY_CN_CFI					"CFI:�˿ڵĹ����ʽָʾ����\r\n"
#define CMD_HELP_KEY_CN_CIR					"CIR:��֤���ʡ�\r\n"
#define CMD_HELP_KEY_CN_CLEAR				"#�����\r\n#"
#define CMD_HELP_KEY_CN_COS					"COS��\r\n"
#define CMD_HELP_KEY_CN_CONFIG_FILE			"�����û������ļ���ز�����\r\n"
#define CMD_HELP_KEY_CN_CONFIRM				"�û�ȷ�ϡ�\r\n"
#define CMD_HELP_KEY_CN_CORRECTION			"ǰ�����\r\n"
#define CMD_HELP_KEY_CN_CREATE				"#������\r\n#"
#define CMD_HELP_KEY_CN_CRYPTO 				"���ܹ��ܡ�\r\n"
#define CMD_HELP_KEY_CN_CURRENT				"��ǰ�ġ�\r\n"
#define CMD_HELP_KEY_CN_CVLAN				"cvlan��\r\n"
#define CMD_HELP_KEY_CN_CTC					"#CTC��\r\n#"

#define CMD_HELP_KEY_CN_TIMEZONE			"����ϵͳʱ����\r\n"
#define CMD_HELP_KEY_CN_DATE				"����ϵͳ��ǰʱ�䡣\r\n"
#define CMD_HELP_KEY_CN_DATE_2				"ϵͳ��ǰʱ�䡣\r\n"
#define CMD_HELP_KEY_CN_DELETE				"#ɾ�����á�\r\n#"
#define CMD_HELP_KEY_CN_DENY				"#���÷���Ȩ��Ϊ�ܾ�(ACL, igmp����)��\r\n#"
#define CMD_HELP_KEY_CN_DESCRIPRIOIN		"�豸������\r\n"
#define CMD_HELP_KEY_CN_DESTINATION			"UNIĿ�Ķ˿ڡ�\r\n"
#define CMD_HELP_KEY_CN_DESTIP				"����Ŀ��ip��ַ��\r\n"
#define CMD_HELP_KEY_CN_DESTMAC				"����Ŀ��mac��ַ��\r\n"
#define CMD_HELP_KEY_CN_DEREGISTER  		"����ONU���ߡ�\r\n"
#define CMD_HELP_KEY_CN_DEVICE				"�����豸��\r\n"
#define CMD_HELP_KEY_CN_DHCP				"DHCP:�Զ���ȡip��ַ��\r\n"
#define CMD_HELP_KEY_CN_DIFFSERV			"Diffserv��\r\n"
#define CMD_HELP_KEY_CN_DISABLE				"#�رա�\r\n#"
#define CMD_HELP_KEY_CN_DOWN				"����״̬:���ߡ�\r\n"
#define CMD_HELP_KEY_CN_DOWNLOAD			"�����ļ���\r\n"
#define CMD_HELP_KEY_CN_DYNAMIC				"��̬��\r\n"

#define CMD_HELP_KEY_CN_EBS					"EBS:������֤ͻ��Ͱ�\r\n"
#define CMD_HELP_KEY_CN_ENABLE				"#�򿪡�\r\n#"
#define CMD_HELP_KEY_CN_EOC           		"Eoc �豸��\r\n"
#define CMD_HELP_KEY_CN_EXTATTR          	"�������ԡ�\r\n"

#define CMD_HELP_KEY_CN_FEC					"����FEC��\r\n"

#define CMD_HELP_KEY_CN_FILE_SYSTEM			"�ļ�ϵͳ��\r\n"
#define CMD_HELP_KEY_CN_ROOT_FS				"���ļ�ϵͳ��\r\n"
#define CMD_HELP_KEY_CN_USER_FS				"�û��ļ�ϵͳ��\r\n"

#define CMD_HELP_KEY_CN_FORCED_SWITCH		"ǿ���л�������Ĺ�����·��\r\n"
#define CMD_HELP_KEY_CN_FORWARDING			"#IGMP��OLT PON��ת����\r\n#"
#define CMD_HELP_KEY_CN_FTP					"����ftp��ز�����\r\n"

#define CMD_HELP_KEY_CN_GATEWAY				"���ء�\r\n"
#define CMD_HELP_KEY_CN_GLOBAL				"ȫ�ֲ�����\r\n"
#define CMD_HELP_KEY_CN_GROUPS				"#��(�˿ھ���, ACL����)��\r\n#"

#define CMD_HELP_KEY_CN_H24					"24Сʱ����ͳ�ơ�\r\n"
#define CMD_HELP_KEY_CN_HOSTNAME			"OLT�豸������\r\n"

#define CMD_HELP_KEY_CN_ID					"��Ŀ�����š�\r\n"
#define CMD_HELP_KEY_CN_IGMP				"#����IGMP��\r\n#"
#define CMD_HELP_KEY_CN_IGMP_MODE_CTZD		"�����鲥ģʽΪcentralized��\r\n"
#define CMD_HELP_KEY_CN_IGMP_MODE_DTBWTCM	"#�����鲥ģʽΪdistributed-with-cm��\r\n#"
#define CMD_HELP_KEY_CN_IGMP_MODE_DIS		"�ر��鲥��\r\n"
#define CMD_HELP_KEY_CN_IGMP_MODE_DTBWOCM	"#�����鲥ģʽΪdistributed-wo-cm��\r\n#"
#define CMD_HELP_KEY_CN_IGMP_PROXY			"#IGMP�鲥����\r\n#"
#define CMD_HELP_KEY_CN_IGMP_PACKAGE		"#�鲥ҵ�����\r\n#"
#define CMD_HELP_KEY_CN_IGMP_PACKAGE_NAME	"#�����鲥ҵ��������ơ�\r\n#"
#define CMD_HELP_KEY_CN_IGMP_PACKAGE_AUTH	"#�����鲥ҵ������û�����Ȩ�ޡ�\r\n#"
#define CMD_HELP_KEY_CN_IGMP_PACKAGE_MRC	"#�����鲥ҵ�������������Ŀ����\r\n#"
#define CMD_HELP_KEY_CN_IGMP_PACKAGE_PC		"#�����鲥ҵ�����Ԥ��������\r\n#"
#define CMD_HELP_KEY_CN_IGMP_PACKAGE_PRT	"#�����鲥ҵ�����Ԥ����λʱ�䡣\r\n#"
#define CMD_HELP_KEY_CN_IGMP_PACKAGE_PIT  	"#�����鲥ҵ�����Ԥ�����ʱ�䡣\r\n#"
#define CMD_HELP_KEY_CN_IGMP_PACKAGE_SPT	"#�����鲥ҵ����ĵ���Ԥ��ʱ����\r\n#"
#define CMD_HELP_KEY_CN_IGMP_PACKAGE_TPT	"#�����鲥ҵ�����Ԥ����ʱ����\r\n#"
#define CMD_HELP_KEY_CN_IGMP_CONTROLLED 	"#���ÿɿ��鲥��\r\n#"
#define CMD_HELP_KEY_CN_IN					"��ڷ���\r\n" 
#define CMD_HELP_KEY_CN_INBAND				"���ڹ���\r\n" 
#define CMD_HELP_KEY_CN_INFORMATION			"ONU��Ϣ��\r\n"
#define CMD_HELP_KEY_CN_INFORMATION_LIST	"ONU�б���Ϣ��\r\n"
#define CMD_HELP_KEY_CN_INTERFACE			"���ö˿ڡ�\r\n"
#define CMD_HELP_KEY_CN_INTERFACE_ONU		"����onu�˿�.\r\n"
#define CMD_HELP_KEY_CN_IP					"#TCP/IP ���硣\r\n#"
#define CMD_HELP_KEY_CN_ISOLATION			"�˿ڸ��빦�ܡ�\r\n" 
#define CMD_HELP_KEY_CN_FLOW_CONTROL		" "
#define CMD_HELP_KEY_CN_LOOPBACK_DETECT		" "

#define CMD_HELP_KEY_CN_KERNEL				"ϵͳ�ںˡ�\r\n"
#define CMD_HELP_KEY_CN_KEY_RES_TO			"PON�ڵ����ؽ�������ģʽ�µ���Կ������Ӧ��ʱʱ�䡣\r\n"
#define CMD_HELP_KEY_CN_KEY_UPD_PRD			"PON�ڵ����ؽ�������ģʽ�µ���Կ�������ڡ�\r\n"

#define CMD_HELP_KEY_CN_LAST_MEM_QUE_CNT	"#�鲥��������Ա��ѯ������\r\n#"
#define CMD_HELP_KEY_CN_LAST_MEM_QUE_INT	"#�鲥��������Ա��ѯ���ʱ�䡣\r\n#"
#define CMD_HELP_KEY_CN_LINK           		"EPON/EOC���ܻ�ͨ�豸��Ϣ��\r\n"
#define CMD_HELP_KEY_CN_LOAD				"�����û����á�\r\n"
#define CMD_HELP_KEY_CN_LOCK           		"����������Ĺ�����·��\r\n"
#define CMD_HELP_KEY_CN_LLID           		"Llid��\r\n"

#define CMD_HELP_KEY_CN_M15					"15��������ͳ�ơ�\r\n"
#define CMD_HELP_KEY_CN_MAC_ADDR_TBL		"MAC��ַѧϰ��\r\n"
#define CMD_HELP_KEY_CN_MAC_ADDR		    "����MAC��ַ��\r\n"
#define CMD_HELP_KEY_CN_MANAGE				"���ڴ���������á�\r\n"
#define CMD_HELP_KEY_CN_MAP					"����ӳ�䡣\r\n"
#define CMD_HELP_KEY_CN_MARK				"���÷���Ȩ��Ϊ���(ACL, igmp����)��\r\n"
#define CMD_HELP_KEY_CN_MAX_QUERY_RES_INT	"#������Ӧ�����ʱ�䣨�����Ӧʱ�䳬ʱ����δ�յ���ѯ��Ӧ�������ٴβ�ѯ����\r\n#"
#define CMD_HELP_KEY_CN_MAXIMUM				"����¼����\r\n"
#define CMD_HELP_KEY_CN_MEMBER				"Member name��\r\n"//???
#define CMD_HELP_KEY_CN_MIRROR				"���ö˿ھ����顣\r\n"
#define CMD_HELP_KEY_CN_MODE				"#ģʽ��\r\n#"
#define CMD_HELP_KEY_CN_MCST				"#�鲥��\r\n#"
#define CMD_HELP_KEY_CN_MCST_VID			"#�鲥vlan ID��\r\n#"

#define CMD_HELP_KEY_CN_NAME				"Vlan���˿ڻ��豸���ơ�\r\n"
#define CMD_HELP_KEY_CN_NO					"#�ָ�Ĭ�����û�ɾ�����á�\r\n#"
#define CMD_HELP_KEY_CN_NULL				"������������Ĺ�����·��\r\n"

#define CMD_HELP_KEY_CN_OLT_IMAGE			"olt�����ļ���\r\n"
#define CMD_HELP_KEY_CN_OLT_STARTUP			"olt start-up ���������ļ���\r\n"
#define CMD_HELP_KEY_CN_ONU					"onu�˿ڡ�\r\n"
#define CMD_HELP_KEY_CN_ONU_BIND			"onu�󶨡�\r\n"
#define CMD_HELP_KEY_CN_ONU_IP				"����ONU ip��ַ��\r\n"
#define CMD_HELP_KEY_CN_ONU_ADM_STA			"onu ����״̬��\r\n"
#define CMD_HELP_KEY_CN_OUT					"���ڷ���\r\n" 
#define CMD_HELP_KEY_CN_OUTBAND				"�������\r\n"

#define CMD_HELP_KEY_CN_PERMIT				"#���÷���Ȩ��Ϊ����(ACL, igmp����)��\r\n#"
#define CMD_HELP_KEY_CN_PIR					"��ֵ����\r\n"
#define CMD_HELP_KEY_CN_POLICY				"QOS���Ȳ��ԡ�\r\n"
#define CMD_HELP_KEY_CN_POLICY_SP			"SP:�ϸ����ȼ���\r\n"
#define CMD_HELP_KEY_CN_POLICY_SPWRR		"SP+WRR:�ϸ����ȼ�+��Ȩ��ѯ��\r\n"
#define CMD_HELP_KEY_CN_POLICY_WFP			"WFP:��Ȩ��ƽ�Ŷӡ�\r\n"
#define CMD_HELP_KEY_CN_POLICY_WRR			"WRR:��Ȩ��ѯ��\r\n"
#define CMD_HELP_KEY_CN_PON					"pon�˿ڡ�\r\n"
#define CMD_HELP_KEY_CN_PORT				"#���ö˿ڡ�\r\n#"
#define CMD_HELP_KEY_CN_PORTPROTECT		    "olt��pon�˿ڱ����顣\r\n"
#define CMD_HELP_KEY_CN_PREVIEW				"#���÷���Ȩ��ΪԤ��(igmp)��\r\n#"
#define CMD_HELP_KEY_CN_PRIMARY				"���˿ڡ�\r\n"
#define CMD_HELP_KEY_CN_PRIORITY			"���ȼ���\r\n"
#define CMD_HELP_KEY_CN_PSC					"�����ֲ����ԡ�\r\n"
#define CMD_HELP_KEY_CN_PVID				"pvid:�˿ڵ�Ĭ��vlan id��\r\n"

#define CMD_HELP_KEY_CN_QINQ				"vlan QinQ ģʽ��\r\n"
#define CMD_HELP_KEY_CN_QOS					"�����豸/�˿� QOS��\r\n"
#define CMD_HELP_KEY_CN_QUERY_INTERVAL		"#���Ͳ�ѯ���ĵ�ʱ������\r\n#"

#define CMD_HELP_KEY_CN_RATE				"���ʡ�\r\n"
#define CMD_HELP_KEY_CN_RATELIMIT			"�������ơ�\r\n"
#define CMD_HELP_KEY_CN_REBOOT				"�����豸��\r\n"
#define CMD_HELP_KEY_CN_REBOOT_ONU			"���� onu��\r\n"
#define CMD_HELP_KEY_CN_RECOVER_TIME		"������·���ϻָ���ӱ�����·�Զ��ָ���������·��ʱ�䡣\r\n"
#define CMD_HELP_KEY_CN_REGISTER			"���� ONU ��ȫ���ԡ�\r\n"
#define CMD_HELP_KEY_CN_REMOVE				"ɾ����\r\n"
#define CMD_HELP_KEY_CN_RESET				"��ԭ�������á�\r\n"
#define CMD_HELP_KEY_CN_ROBUST				"#�鲥��׳�Ա�����\r\n#"
#define CMD_HELP_KEY_CN_RUNNING_CONFIG		"ϵͳ�������е�����.\r\n"
#define CMD_HELP_KEY_CN_RX					"��ڷ���\r\n"

#define CMD_HELP_KEY_CN_SCHEDULER			"���ȼ����ȡ�\r\n"
#define CMD_HELP_KEY_CN_SECONDARY			"���ö˿ڡ�\r\n"
#define CMD_HELP_KEY_CN_SERVER				"NTP/SNTP Server��\r\n"
#define CMD_HELP_KEY_CN_SESSION				"���������š�\r\n"
#define CMD_HELP_KEY_CN_SHOW				"#��ӡ/��ʾ�豸���忨�����á�Э�顢�汾�������Ϣ��\r\n#"
#define CMD_HELP_KEY_CN_SLA					"�������á�\r\n"
#define CMD_HELP_KEY_CN_SLA_PIR				"��ֵ����\r\n"
#define CMD_HELP_KEY_CN_SLA_CIR				"��֤����\r\n"
#define CMD_HELP_KEY_CN_SLA_FIR				"�̶�����\r\n"
#define CMD_HELP_KEY_CN_SNI					"sni�˿ڡ�\r\n"
#define CMD_HELP_KEY_CN_SNI_DESTINATION		"SNIĿ�Ķ˿ڡ�\r\n"
#define CMD_HELP_KEY_CN_SNI_PON_SOURCE		"SNI��PONԴ�˿ڡ�\r\n"
#define CMD_HELP_KEY_CN_SNMP				"OLT�ĸ澯����\r\n"
#define CMD_HELP_KEY_CN_SNTP				"sntp:����ʱ��ͬ����\r\n"
#define CMD_HELP_KEY_CN_SRCIP				"����Դip��ַ��\r\n"
#define CMD_HELP_KEY_CN_SRCIPDEST			"����Դip��ַ��Ŀ��ip��ַ��\r\n"
#define CMD_HELP_KEY_CN_SRCMAC				"����ԴMAC��ַ ��\r\n"
#define CMD_HELP_KEY_CN_SRCMACDEST			"����ԴMAC��ַ��Ŀ��MAC��ַ ��\r\n"
#define CMD_HELP_KEY_CN_STATISTICS			"����ͳ�ơ�\r\n"
#define CMD_HELP_KEY_CN_STATUS			    "״̬��\r\n"
#define CMD_HELP_KEY_CN_STP					"����������Э�顣\r\n"
#define CMD_HELP_KEY_CN_SOURCE				"UNIԴ�˿ڡ�\r\n"
#define CMD_HELP_KEY_CN_SPECIFIC			"�ض����͸澯��\r\n"
#define CMD_HELP_KEY_CN_STATIC				"��̬��\r\n"
#define CMD_HELP_KEY_CN_STORM_CTRL			"�籩���ơ�\r\n"
#define CMD_HELP_KEY_CN_STRUNK				"vlan strunkģʽ��\r\n"
#define CMD_HELP_KEY_CN_SVLAN				"svlan��\r\n"
#define CMD_HELP_KEY_CN_SWITCHOVER			"�л���/��ϵͳ���������豸�ȡ�\r\n"
#define CMD_HELP_KEY_CN_SYSTEM				"ϵͳ��Ϣ: �豸�������ҡ���\r\n"
#define CMD_HELP_KEY_CN_SYSTEM_DEF_TPID		"ϵͳ����tpid��\r\n" //???

#define CMD_HELP_KEY_CN_TABLE				"ӳ���\r\n"
#define CMD_HELP_KEY_CN_TAG_STRIPE			"#����tag-stripe ����: �Ƿ����ONU�յ��������鲥���ĵ� VLAN tag��\r\n#"
#define CMD_HELP_KEY_CN_TAGGED				"Tagged��\r\n"
#define CMD_HELP_KEY_CN_TESTING				"����״̬:���ԡ�\r\n"
#define CMD_HELP_KEY_CN_TFTP				"����tftp��ز�����\r\n"
#define CMD_HELP_KEY_CN_THRESHOLD			"����ͳ�ơ��澯�ĸ������޷�ֵ��\r\n"
#define CMD_HELP_KEY_CN_TOS					"TOS��\r\n"
#define CMD_HELP_KEY_CN_TPID				"�˿�svlan/cvlan tpid��\r\n"
#define CMD_HELP_KEY_CN_TRANSLATION			"vlan����ģʽ��\r\n"
#define CMD_HELP_KEY_CN_TRANSMISSION		"�������紫�������\r\n"
#define CMD_HELP_KEY_CN_TRANSPARENT			"vlan͸��ģʽ��\r\n"
#define CMD_HELP_KEY_CN_TRAP				"OLT�ĸ澯����\r\n"
#define CMD_HELP_KEY_CN_TRIPLE_CHURNING 	"���ؽ�������ģʽ��\r\n"
#define CMD_HELP_KEY_CN_TRUNK				"Trunk(�˿�,vlan...)��\r\n"
#define CMD_HELP_KEY_CN_TX					"���ڷ���\r\n"

#define CMD_HELP_KEY_CN_UNI 				"uni�˿ڡ�\r\n"
#define CMD_HELP_KEY_CN_UNTAGGED			"Untagged��\r\n" 
#define CMD_HELP_KEY_CN_UP					"����״̬:���ߡ�\r\n"
#define CMD_HELP_KEY_CN_UPGRADE				"����ϵͳ����������ںˡ��������õȡ�\r\n"
#define CMD_HELP_KEY_CN_UPLOAD				"�����ϴ���\r\n"

#define CMD_HELP_KEY_CN_USER_DEF_TPID		"�û��Զ���tpid��\r\n" 

#define CMD_HELP_KEY_CN_VERSION				"#�汾�š�\r\n#"
#define CMD_HELP_KEY_CN_VLAN				"#Vlan��\r\n#"

#define CMD_HELP_KEY_CN_WEIGHT				"���ȼ�����Ȩ�ء�\r\n"
#define CMD_HELP_KEY_CN_WHITE				"������ģʽ��\r\n"
#define CMD_HELP_KEY_CN_WRITE				"�����û����á�\r\n"

#define CMD_HELP_KEY_CN_TIMEOUT				"���õ�¼�û��ĳ�ʱʱ�䡣\r\n"
#define CMD_HELP_KEY_CN_ZERO				"���ó�ʱʱ��Ϊ������ʱ��\r\n"
#define CMD_HELP_KEY_CN_PROMPT				"����ϵͳ�����нӿ���ʾ����\r\n"

//STP key cn
#define CMD_HELP_KEY_CN_BRIDGE				"����STP�����š�\r\n"
#define CMD_HELP_KEY_CN_SSTP				"����STPģʽ:SSTP��\r\n"
#define CMD_HELP_KEY_CN_RSTP				"����STPģʽ:RSTP��\r\n"
#define CMD_HELP_KEY_CN_MSTP				"����STPģʽ:MSTP��\r\n"
#define CMD_HELP_KEY_CN_FORWARD				"���ö˿ڴ���forward״̬��\r\n"

#define CMD_HELP_KEY_CN_MAX_AGE				"�����������ĸ����ŵ��ϻ�ʱ�䡣\r\n"
#define CMD_HELP_KEY_CN_HELLO_TIME			"�����������ĸ����ŵı��ķ��ͼ��ʱ�䡣\r\n"
#define CMD_HELP_KEY_CN_FORWARD_TIME		"�����������ĸ����ŵ�ת��ʱ�ӡ�\r\n"
#define CMD_HELP_KEY_CN_TX_HOLD_COUNT		"����������ÿ����෢�� BPDU ������\r\n"
#define CMD_HELP_KEY_CN_PATHCOST_METHOD		"�����������˿�·�����ѵ�ȱʡ���㷽����\r\n"
#define CMD_HELP_KEY_CN_LONG				"�����������˿�·�����ѵ�ȱʡ���㷽��Ϊ�����͡�\r\n"
#define CMD_HELP_KEY_CN_SHORT				"�����������˿�·�����ѵ�ȱʡ���㷽��Ϊ�����Ρ�\r\n"

#define CMD_HELP_KEY_CN_PATH_COST			"�����������Ķ˿�·��������\r\n"
#define CMD_HELP_KEY_CN_PORT_EDGE			"�����������Ķ˿�Ϊ��Ե�˿ڡ�\r\n"
#define CMD_HELP_KEY_CN_MIGRATION_CHECK		"�����˿ڵ�Э��ת�������̡�\r\n"

#define CMD_HELP_KEY_CN_PROTOCOL			"����������Э�顣\r\n"
#define CMD_HELP_KEY_CN_BRIDGE_GROUP		"���������������Ŷ˿ڡ�\r\n"
#define CMD_HELP_KEY_CN_SWITCHPORT			"�����������˿ڡ�\r\n"

#define CMD_HELP_KEY_CN_PERIOD				"��������.\r\n"

#define CMD_HELP_KEY_CN_HISTORY				"��ʷ��Ϣ.\r\n"
#define CMD_HELP_KEY_CN_EVENT				"�¼���־.\r\n"

#define CMD_HELP_KEY_CN_ONU_ALARM			"����onu�澯.\r\n"
#define CMD_HELP_KEY_CN_ONU_ALARM_CONFIG	"onu�澯������Ϣ.\r\n"

#define CMD_HELP_KEY_CN_ONU_IMAGE_SWITCH	"�л�����onu����\r\n"
#define CMD_HELP_KEY_CN_ONU_IMAGE			"onu����\r\n"

#define CMD_HELP_KEY_CN_MAX_DISTANCE		"Olt pon onu��������.\r\n"
#define CMD_HELP_KEY_CN_FULL				"PON��������ONU���ܻ�ͨ.\r\n"

//snmp community
#define CMD_HELP_KEY_CN_SNMP_SERVER				"����SNMP������\r\n"
#define CMD_HELP_KEY_CN_COMMUNITY				"����\r\n"
#define CMD_HELP_KEY_CN_COMMUNITY_NAME			"������\r\n"
#define	CMD_HELP_KEY_CN_RO						"ֻ��\r\n"
#define CMD_HELP_KEY_CN_RW						"�ɶ���д\r\n"


#define CMD_HELP_KEY_EN_					".\r\n"


#define CMD_HELP_KEY_EN_ABILITY				"Configure ability.\r\n"
#define CMD_HELP_KEY_EN_ACL					"Access list.\r\n"
#define CMD_HELP_KEY_EN_ACL_GROUP			"Configure port ACL.\r\n"
#define CMD_HELP_KEY_EN_ACL_GROUP_BY_INDEX	"Configure port ACL by index.\r\n"
#define CMD_HELP_KEY_EN_ACL_GROUP_BY_NAME	"Configure port ACL by name.\r\n"
#define CMD_HELP_KEY_EN_ACL_RULE			"Acl rule.\r\n"
#define CMD_HELP_KEY_EN_ADD					"#Add configuration.\r\n#"
#define CMD_HELP_KEY_EN_ADDRESS				"Address.\r\n"
#define CMD_HELP_KEY_EN_ADMIN_STATUS		"Controllable status.\r\n"
#define CMD_HELP_KEY_EN_AES32				"Aes32.\r\n"		
#define CMD_HELP_KEY_EN_AES48				"Aes48.\r\n"	
#define CMD_HELP_KEY_EN_AES128				"Aes128.\r\n"	
#define CMD_HELP_KEY_EN_AGING_TIME			"Configure aging time.\r\n"
#define CMD_HELP_KEY_EN_AGGREGATION			"Aggregation mode.\r\n"
#define CMD_HELP_KEY_EN_ALARM				"Configure alarm management.\r\n"
#define CMD_HELP_KEY_EN_ALL					"#All configuration.\r\n#"
#define CMD_HELP_KEY_EN_ANY					"Any value.\r\n"
#define CMD_HELP_KEY_EN_ARP					"Manipulate the system ARP cache.\r\n"
#define CMD_HELP_KEY_EN_ATTRIBUTE			"Configure attribute.\r\n"
#define CMD_HELP_KEY_EN_AUTO_NEGO			"Configure auto-negotiation.\r\n"
#define CMD_HELP_KEY_EN_AUTO_NEGO_AUTO		"Auto mode.\r\n"
#define CMD_HELP_KEY_EN_AUTO_NEGO_H10		"Half-10 mode.\r\n"
#define CMD_HELP_KEY_EN_AUTO_NEGO_F10		"Full-10 mode.\r\n"
#define CMD_HELP_KEY_EN_AUTO_NEGO_H100		"Half-100 mode.\r\n"
#define CMD_HELP_KEY_EN_AUTO_NEGO_F100		"Full-100 mode.\r\n"
#define CMD_HELP_KEY_EN_AUTO_NEGO_F1000		"Full-1000 mode.\r\n"
#define CMD_HELP_KEY_EN_AUTO_NEGO_F10000	"Full-10000 mode.\r\n"

#define CMD_HELP_KEY_EN_BACKUP				"Backup configuration or image or start-up file.\r\n"
#define CMD_HELP_KEY_EN_BANDWIDTH			"#Configure bandwidth.\r\n#"
#define CMD_HELP_KEY_EN_BASED				"Based on.\r\n"
#define CMD_HELP_KEY_EN_BLACK				"Blacklist table mode.\r\n"
#define CMD_HELP_KEY_EN_BLOCK				"List name that was blocked.\r\n"
#define CMD_HELP_KEY_EN_BOARD				"Configure board.\r\n"
#define CMD_HELP_KEY_EN_BOTH				"Both rx and tx.\r\n"
#define CMD_HELP_KEY_EN_BRIEF				"brief information list.\r\n"

#define CMD_HELP_KEY_EN_CAPABILITY			"Ability of capability.\r\n"
#define CMD_HELP_KEY_EN_CBS					"Excess Burst size.\r\n"
#define CMD_HELP_KEY_EN_CFI					"CFI.\r\n"
#define CMD_HELP_KEY_EN_CIR					"Base rate.\r\n"
#define CMD_HELP_KEY_EN_CLEAR				"#Clear configuration.\r\n#"
#define CMD_HELP_KEY_EN_COS					"Class of service.\r\n"
#define CMD_HELP_KEY_EN_CONFIG_FILE			"User configuration file.\r\n"
#define CMD_HELP_KEY_EN_CONFIRM				"User confirm information.\r\n"
#define CMD_HELP_KEY_EN_CORRECTION			"Forward error correction.\r\n"
#define CMD_HELP_KEY_EN_CREATE				"#Create object or entity.\r\n#"
#define CMD_HELP_KEY_EN_CRYPTO 				"Configure crypto.\r\n"
#define CMD_HELP_KEY_EN_CURRENT				"Real time status.\r\n"
#define CMD_HELP_KEY_EN_CVLAN				"Custom vlan.\r\n"
#define CMD_HELP_KEY_EN_CTC					"#CTC.\r\n#"

#define CMD_HELP_KEY_EN_TIMEZONE			"Set the current timezone.\r\n"
#define CMD_HELP_KEY_EN_DATE				"Set the current time.\r\n"
#define CMD_HELP_KEY_EN_DATE_2				"Current time.\r\n"
#define CMD_HELP_KEY_EN_DELETE				"#Delete configuration.\r\n#"
#define CMD_HELP_KEY_EN_DENY				"#Acl or igmp-package deny.\r\n#"
#define CMD_HELP_KEY_EN_DESCRIPRIOIN		"Device description.\r\n"
#define CMD_HELP_KEY_EN_DESTINATION			"Configure destination.\r\n"
#define CMD_HELP_KEY_EN_DESTIP				"Destination ipaddress mode.\r\n"
#define CMD_HELP_KEY_EN_DESTMAC				"Destination macaddress mode.\r\n"
#define CMD_HELP_KEY_EN_DEREGISTER  		"Set onu to deregister.\r\n"
#define CMD_HELP_KEY_EN_DEVICE				"Configuration of device.\r\n"
#define CMD_HELP_KEY_EN_DHCP				"DHCP setted.\r\n"
#define CMD_HELP_KEY_EN_DIFFSERV			"Differential services code point.\r\n"
#define CMD_HELP_KEY_EN_DISABLE				"#Turn off.\r\n#"
#define CMD_HELP_KEY_EN_DOWN				"status:DOWN.\r\n"
#define CMD_HELP_KEY_EN_DOWNLOAD			"Download files.\r\n"
#define CMD_HELP_KEY_EN_DYNAMIC				"Dynamic mode.\r\n"

#define CMD_HELP_KEY_EN_EBS					"Excess Burst size.\r\n"
#define CMD_HELP_KEY_EN_ENABLE				"#Turn on.\r\n#"
#define CMD_HELP_KEY_EN_EOC           		"Eoc device.\r\n"
#define CMD_HELP_KEY_EN_EXTATTR          	"Other attribute.\r\n"

#define CMD_HELP_KEY_EN_FEC					"Configure fec.\r\n"
#define CMD_HELP_KEY_EN_FILE_SYSTEM			"File system.\r\n"
#define CMD_HELP_KEY_EN_ROOT_FS				"Root file system.\r\n"
#define CMD_HELP_KEY_EN_USER_FS				"User file system.\r\n"

#define CMD_HELP_KEY_EN_FORCED_SWITCH		"Force change work mode.\r\n"
#define CMD_HELP_KEY_EN_FORWARDING			"#Forwarding table.\r\n#"
#define CMD_HELP_KEY_EN_FTP					"Ftp transfer information.\r\n"

#define CMD_HELP_KEY_EN_GATEWAY				"Subnet gateway.\r\n"
#define CMD_HELP_KEY_EN_GLOBAL				"Global configuration.\r\n"
#define CMD_HELP_KEY_EN_GROUPS				"#Groups (for forwarding, mirror, acl).\r\n#"

#define CMD_HELP_KEY_EN_H24					"Configuration of performance statistics in 24 hours.\r\n"
#define CMD_HELP_KEY_EN_HOSTNAME			"Configure olt hostname.\r\n"

#define CMD_HELP_KEY_EN_ID					"Configure by id number.\r\n"
#define CMD_HELP_KEY_EN_IGMP				"#Configure IGMP.\r\n#"
#define CMD_HELP_KEY_EN_IGMP_MODE_CTZD		"All the multicast control is done by OLT.\r\n"
#define CMD_HELP_KEY_EN_IGMP_MODE_DTBWTCM	"#Both OLT and ONU perform IGMP proxy and controlled multicast will be enabled.\r\n#"
#define CMD_HELP_KEY_EN_IGMP_MODE_DIS		"Disable IGMP proxy on OLT and ONU.\r\n"
#define CMD_HELP_KEY_EN_IGMP_MODE_DTBWOCM	"#Both OLT and ONU perform IGMP proxy and controlled multicast will be disabled.\r\n#"
#define CMD_HELP_KEY_EN_IGMP_PROXY			"#Configure IGMP Proxy.\r\n#"
#define CMD_HELP_KEY_EN_IGMP_PACKAGE		"#Configure IGMP Package.\r\n#"
#define CMD_HELP_KEY_EN_IGMP_PACKAGE_NAME	"#Configure igmp-package name.\r\n#"
#define CMD_HELP_KEY_EN_IGMP_PACKAGE_AUTH	"#Configure igmp-package user-authority.\r\n#"
#define CMD_HELP_KEY_EN_IGMP_PACKAGE_MRC	"#Configure igmp-package max-request-channel.\r\n#"
#define CMD_HELP_KEY_EN_IGMP_PACKAGE_PC		"#Configure igmp-package preview-count.\r\n#"
#define CMD_HELP_KEY_EN_IGMP_PACKAGE_PRT	"#Configure igmp-package preview-reset-time.\r\n#"
#define CMD_HELP_KEY_EN_IGMP_PACKAGE_PIT	       "#Configure igmp-package preview-interval-time.\r\n#"
#define CMD_HELP_KEY_EN_IGMP_PACKAGE_SPT	"#Configure igmp-package single-preview-time.\r\n#"
#define CMD_HELP_KEY_EN_IGMP_PACKAGE_TPT	"#Configure igmp-package total-preview-time.\r\n#"
#define CMD_HELP_KEY_EN_IGMP_CONTROLLED 	"#Configure controlled-multicast.\r\n#"
#define CMD_HELP_KEY_EN_IN					"Rx direction.\r\n" 
#define CMD_HELP_KEY_EN_INBAND				"Network management inband.\r\n" 
#define CMD_HELP_KEY_EN_INFORMATION			"Information about onu.\r\n"
#define CMD_HELP_KEY_EN_INFORMATION_LIST	"Information about onu list.\r\n"
#define CMD_HELP_KEY_EN_INTERFACE			"Configure interfaces.\r\n"
#define CMD_HELP_KEY_EN_INTERFACE_ONU		"Configure onu interface.\r\n"
#define CMD_HELP_KEY_EN_IP					"#TCP/IP network.\r\n#"
#define CMD_HELP_KEY_EN_ISOLATION			"Configure isolation status of port.\r\n" 
#define CMD_HELP_KEY_EN_FLOW_CONTROL		"Configure flow-control status of port.\r\n" 

#define CMD_HELP_KEY_EN_LOOPBACK_DETECT		"Configure loopback-detect status of port.\r\n" 


#define CMD_HELP_KEY_EN_KERNEL				"System kernel.\r\n"
#define CMD_HELP_KEY_EN_DBTB				"dbtb.\r\n"
#define CMD_HELP_KEY_EN_UBOOT				"uboot.\r\n"

#define CMD_HELP_KEY_EN_KEY_RES_TO			"Key response timeout.\r\n"
#define CMD_HELP_KEY_EN_KEY_UPD_PRD			"Key update period.\r\n"

#define CMD_HELP_KEY_EN_LAST_MEM_QUE_CNT	"#Query times of last member.\r\n#"
#define CMD_HELP_KEY_EN_LAST_MEM_QUE_INT	"#Query interval time of last member.\r\n#"
#define CMD_HELP_KEY_EN_LINK           		"Link information.\r\n"
#define CMD_HELP_KEY_EN_LOAD				"Load user configuration.\r\n"
#define CMD_HELP_KEY_EN_LOCK           		"Lock setting.\r\n"
#define CMD_HELP_KEY_EN_LLID           		"Llid.\r\n"

#define CMD_HELP_KEY_EN_M15					"Configuration of performance statistics in 15 minutes.\r\n"
#define CMD_HELP_KEY_EN_MAC_ADDR_TBL		"Configuration of mac address table.\r\n"
#define CMD_HELP_KEY_EN_MAC_ADDR		    "Configuration by mac address.\r\n"
#define CMD_HELP_KEY_EN_MANAGE				"Inband or Outband Management.\r\n"
#define CMD_HELP_KEY_EN_MAP					"Blank map.\r\n"
#define CMD_HELP_KEY_EN_MARK				"Acl or igmp-package marked.\r\n"
#define CMD_HELP_KEY_EN_MAX_QUERY_RES_INT	"#Max interval time of query response.\r\n#"
#define CMD_HELP_KEY_EN_MAXIMUM				"Configuration of maximum.\r\n"
#define CMD_HELP_KEY_EN_MEMBER				"Member name.\r\n"
#define CMD_HELP_KEY_EN_MIRROR				"Configuration of mirror group.\r\n"
#define CMD_HELP_KEY_EN_MODE				"#Running mode.\r\n#"
#define CMD_HELP_KEY_EN_MCST				"#Multicast.\r\n#"
#define CMD_HELP_KEY_EN_MCST_VID			"#Multicast vlan ID.\r\n#"
#define CMD_HELP_KEY_EN_MAX_DISTANCE		"Olt pon onu's max distance.\r\n"

#define CMD_HELP_KEY_EN_NAME				"Vlan, port or device name.\r\n"
#define CMD_HELP_KEY_EN_NO					"#Set default value.\r\n#"
#define CMD_HELP_KEY_EN_NULL				"Setting nothing.\r\n"

#define CMD_HELP_KEY_EN_OLT_IMAGE			"Image file of OLT.\r\n"
#define CMD_HELP_KEY_EN_OLT_STARTUP			"Start-up file of OLT.\r\n"
#define CMD_HELP_KEY_EN_ONU					"Configure onu.\r\n"
#define CMD_HELP_KEY_EN_ONU_BIND			"Configure onu bind.\r\n"
#define CMD_HELP_KEY_EN_ONU_IP				"Configure onu ip.\r\n"
#define CMD_HELP_KEY_EN_ONU_NETMASK			"Configure onu netmask.\r\n"

#define CMD_HELP_KEY_EN_ONU_ADM_STA			"Onu status configuration.\r\n"
#define CMD_HELP_KEY_EN_OUT					"Tx direction.\r\n" 
#define CMD_HELP_KEY_EN_OUTBAND				"Network management outband.\r\n"

#define CMD_HELP_KEY_EN_PERMIT				"#Acl or igmp-package permit.\r\n#"
#define CMD_HELP_KEY_EN_PIR					"Max rate.\r\n"
#define CMD_HELP_KEY_EN_POLICY				"Policy-based QOS.\r\n"
#define CMD_HELP_KEY_EN_POLICY_SP			"Queue as strict priority.\r\n"
#define CMD_HELP_KEY_EN_POLICY_SPWRR		"Queue as strict priority and weighted round robin.\r\n"
#define CMD_HELP_KEY_EN_POLICY_WFP			"Queue as weighted fair.\r\n"
#define CMD_HELP_KEY_EN_POLICY_WRR			"Queue as weighted round robin.\r\n"
#define CMD_HELP_KEY_EN_PON					"Configure pon port.\r\n"
#define CMD_HELP_KEY_EN_PORT				"#Configure port.\r\n#"
#define CMD_HELP_KEY_EN_PORTPROTECT		    "Set port group protected.\r\n"
#define CMD_HELP_KEY_EN_PREVIEW				"#Igmp-package preview.\r\n#"
#define CMD_HELP_KEY_EN_PRIMARY				"Primary pon port.\r\n"
#define CMD_HELP_KEY_EN_PRIORITY			"Configure priority.\r\n"
#define CMD_HELP_KEY_EN_PSC					"Policy of stream chorology.\r\n"
#define CMD_HELP_KEY_EN_PVID				"Configure pvid.\r\n"

#define CMD_HELP_KEY_EN_QINQ				"QinQ mode.\r\n"
#define CMD_HELP_KEY_EN_QOS					"Configure device or port QOS.\r\n"
#define CMD_HELP_KEY_EN_QUERY_INTERVAL		"#Interval time of query.\r\n#"

#define CMD_HELP_KEY_EN_RATE				"Rate value.\r\n"
#define CMD_HELP_KEY_EN_RATELIMIT			"Rate limit.\r\n"
#define CMD_HELP_KEY_EN_REBOOT				"Reboot device or special card.\r\n"
#define CMD_HELP_KEY_EN_REBOOT_ONU			"Reboot onu.\r\n"
#define CMD_HELP_KEY_EN_RECOVER_TIME		"Set time that slave recovered link form master.\r\n"
#define CMD_HELP_KEY_EN_REGISTER			"Configure ONU security policy.\r\n"
#define CMD_HELP_KEY_EN_REMOVE				"Remove configuration.\r\n"
#define CMD_HELP_KEY_EN_RESET				"Reset configuration.\r\n"
#define CMD_HELP_KEY_EN_ROBUST				"#Robust.\r\n#"
#define CMD_HELP_KEY_EN_RUNNING_CONFIG		"Running configuration on system.\r\n"
#define CMD_HELP_KEY_EN_RX					"Rx direction.\r\n"

#define CMD_HELP_KEY_EN_SCHEDULER			"Priority scheduler.\r\n"
#define CMD_HELP_KEY_EN_SECONDARY			"Secndary pon port.\r\n"
#define CMD_HELP_KEY_EN_SERVER				"Configure server.\r\n"
#define CMD_HELP_KEY_EN_SESSION				"Session number.\r\n"
#define CMD_HELP_KEY_EN_SHOW				"#Display information.\r\n#"
#define CMD_HELP_KEY_EN_SLA					"Service level access.\r\n"
#define CMD_HELP_KEY_EN_SLA_PIR				"Peak Information Rate.\r\n"
#define CMD_HELP_KEY_EN_SLA_CIR				"Committed Information Rate.\r\n"
#define CMD_HELP_KEY_EN_SLA_FIR				"Fixed Information Rate.\r\n"
#define CMD_HELP_KEY_EN_SNI					"Configure sni port.\r\n"
#define CMD_HELP_KEY_EN_SNMP				"Configure snmp.\r\n"
#define CMD_HELP_KEY_EN_SNTP				"Configure sntp.\r\n"
#define CMD_HELP_KEY_EN_SRCIP				"Source ipaddress mode.\r\n"
#define CMD_HELP_KEY_EN_SRCIPDEST			"Source ipaddress mode and destination ipaddress mode.\r\n"
#define CMD_HELP_KEY_EN_SRCMAC				"Source macaddress mode .\r\n"
#define CMD_HELP_KEY_EN_SRCMACDEST			"Source macaddress mode and destination macaddress mode .\r\n"
#define CMD_HELP_KEY_EN_STATISTICS			"Configure statistics.\r\n"
#define CMD_HELP_KEY_EN_STATUS			    "Status configuration.\r\n"
#define CMD_HELP_KEY_EN_STP					"Configure spanning-tree protocol.\r\n"
#define CMD_HELP_KEY_EN_SOURCE				"Configure source.\r\n"
#define CMD_HELP_KEY_EN_SPECIFIC			"Specific warning.\r\n"
#define CMD_HELP_KEY_EN_STATIC				"Static mode.\r\n"
#define CMD_HELP_KEY_EN_STORM_CTRL			"Storm control.\r\n"
#define CMD_HELP_KEY_EN_STRUNK				"Strunk mode.\r\n"
#define CMD_HELP_KEY_EN_SVLAN				"Service vlan.\r\n"
#define CMD_HELP_KEY_EN_SWITCHOVER			"Switch over system or partition.\r\n"
#define CMD_HELP_KEY_EN_SYSTEM				"System information.\r\n"
#define CMD_HELP_KEY_EN_SYSTEM_DEF_TPID		"System defined tpid.\r\n"

#define CMD_HELP_KEY_EN_TABLE				"Running table.\r\n"
#define CMD_HELP_KEY_EN_TAG_STRIPE			"#Tag stripe.\r\n#"
#define CMD_HELP_KEY_EN_TAGGED				"Tagged.\r\n"
#define CMD_HELP_KEY_EN_TESTING				"status:TESTING.\r\n"
#define CMD_HELP_KEY_EN_TFTP				"Tftp transfer information.\r\n"
#define CMD_HELP_KEY_EN_THRESHOLD			"Critical point threshold.\r\n"
#define CMD_HELP_KEY_EN_TOS					"Type of service.\r\n"
#define CMD_HELP_KEY_EN_TPID				"Tpid.\r\n"
#define CMD_HELP_KEY_EN_TRANSLATION			"Translation mode.\r\n"
#define CMD_HELP_KEY_EN_TRANSPARENT			"Transparent mode.\r\n"
#define CMD_HELP_KEY_EN_TRANSMISSION		"Configure network transmission.\r\n"
#define CMD_HELP_KEY_EN_TRAP				"Configure trap management.\r\n"
#define CMD_HELP_KEY_EN_TRIPLE_CHURNING 	"Triple churning.\r\n"
#define CMD_HELP_KEY_EN_TRUNK				"Trunk mode.\r\n"
#define CMD_HELP_KEY_EN_TX					"Tx direction.\r\n"

#define CMD_HELP_KEY_EN_UNI 				"Configure uni.\r\n"
#define CMD_HELP_KEY_EN_UNTAGGED			"Untagged.\r\n"
#define CMD_HELP_KEY_EN_UP					"status:UP.\r\n"
#define CMD_HELP_KEY_EN_UPGRADE				"Upgrade software or configuration.\r\n"
#define CMD_HELP_KEY_EN_UPLOAD				"Upload files.\r\n"
#define CMD_HELP_KEY_EN_USER_DEF_TPID		"User defined tpid.\r\n"

#define CMD_HELP_KEY_EN_VERSION				"#Version number.\r\n#"
#define CMD_HELP_KEY_EN_VLAN				"#Vlan configuration.\r\n#"

#define CMD_HELP_KEY_EN_WEIGHT				"Weight list.\r\n"
#define CMD_HELP_KEY_EN_WHITE				"Whitelist table mode.\r\n"
#define CMD_HELP_KEY_EN_WRITE				"Save user configuration to flash.\r\n"

#define CMD_HELP_KEY_EN_TIMEOUT				"set telnet timeout.\r\n"
#define CMD_HELP_KEY_EN_ZERO				"set never timeout.\r\n"
#define CMD_HELP_KEY_EN_PROMPT				"set commond prompt.\r\n"

#define CMD_HELP_KEY_EN_MAC_FILTER			"uni mac filter\r\n"
#define CMD_HELP_KEY_EN_DEST_MAC			"destination mac address\r\n"
#define CMD_HELP_KEY_EN_SRC_MAC				"source mac address\r\n"
#define CMD_HELP_KEY_EN_MAC_BIND			"source mac binding\r\n"

//STP
#define CMD_HELP_KEY_EN_BRIDGE				"Configure STP bridge.\r\n"
#define CMD_HELP_KEY_EN_SSTP				"Configure STP mode:SSTP.\r\n"
#define CMD_HELP_KEY_EN_RSTP				"Configure STP mode:RSTP.\r\n"
#define CMD_HELP_KEY_EN_MSTP				"Configure STP mode:MSTP.\r\n"
#define CMD_HELP_KEY_EN_FORWARD				"Configure STP port in forwarding.\r\n"

#define CMD_HELP_KEY_EN_MAX_AGE				"Configure STP MAX-AGING-TIME.\r\n"
#define CMD_HELP_KEY_EN_HELLO_TIME			"Configure STP HELLO-TIME.\r\n"
#define CMD_HELP_KEY_EN_FORWARD_TIME		"Configure STP FORWARD-DELAY.\r\n"
#define CMD_HELP_KEY_EN_TX_HOLD_COUNT		"Configure STP TX-HOLD-COUNT.\r\n"
#define CMD_HELP_KEY_EN_PATHCOST_METHOD		"Configure STP PATHCOST-METHOD, {short | long}.\r\n"
#define CMD_HELP_KEY_EN_LONG				"Configure STP PATHCOST-METHOD, long int .\r\n"
#define CMD_HELP_KEY_EN_SHORT				"Configure STP PATHCOST-METHOD, short int.\r\n"

#define CMD_HELP_KEY_EN_PATH_COST			"Configure STP PATH-COST.\r\n"
#define CMD_HELP_KEY_EN_PORT_EDGE			"Configure STP edge port.\r\n"
#define CMD_HELP_KEY_EN_MIGRATION_CHECK		"Configure STP port migration-check.\r\n"

#define CMD_HELP_KEY_EN_PROTOCOL			"Configure STP protocol.\r\n"
#define CMD_HELP_KEY_EN_BRIDGE_GROUP		"Configure STP bridge-group.\r\n"
#define CMD_HELP_KEY_EN_SWITCHPORT			"Configure STP port.\r\n"
	
#define CMD_HELP_KEY_EN_PERIOD				"Configure period.\r\n"

#define CMD_HELP_KEY_EN_ONU_CLS				"Configure onu classification.\r\n"
#define CMD_HELP_KEY_EN_ONU_CLS_PRECEDENCE	"Configure onu classification precedence.\r\n"
#define CMD_HELP_KEY_EN_ONU_CLS_QUEMAPED	"Map the stream to specify queue.\r\n"
#define CMD_HELP_KEY_EN_ONU_CLS_ETH_PRI		"Configure onu classification Ethernet Priority.\r\n"

#define CMD_HELP_KEY_EN_HISTORY				"history information.\r\n"
#define CMD_HELP_KEY_EN_EVENT				"event log information.\r\n"

#define CMD_HELP_KEY_EN_ONU_ALARM			"Configure onu alarm.\r\n"
#define CMD_HELP_KEY_EN_ONU_ALARM_CONFIG	"Onu alarm configure information.\r\n"


#define CMD_HELP_ARG_EN_						"FORMAT:  \r\n"

#define CMD_HELP_ARG_EN_DISTANCE				"20 or 30 or 40 or 50.\r\n"
#define CMD_HELP_ARG_EN_MACADDRESS				"FORMAT:XXXX.XXXX.XXXX (X<F) \r\n"
//#define CMD_HELP_ARG_EN_MACWITHMASK			"FORMAT:XXXX.XXXX.XXXX:XXXX.XXXX.XXXX \r\n"
#define CMD_HELP_ARG_EN_MACADDRESSLIST			"FORMAT:XXXX.XXXX.XXXX,XXXX.XXXX.XXXX-XXXX.XXXX.XXXX (X<F) \r\n"

#define CMD_HELP_ARG_EN_IPADDRESS				"FORMAT:DDD.DDD.DDD.DDD (DDD<255) \r\n"
#define CMD_HELP_ARG_EN_IPMASK					"FORMAT:DDD.DDD.DDD.DDD (DDD<255) \r\n"
//#define CMD_HELP_ARG_EN_IPWITHMASK			"FORMAT:DDD.DDD.DDD.DDD:DDD.DDD.DDD.DDD \r\n"
#define CMD_HELP_ARG_EN_IPGATEWAY				"FORMAT:DDD.DDD.DDD.DDD (DDD<255) \r\n"
#define CMD_HELP_ARG_EN_IPADDRESSANDMASK   		"Set ipaddress and mask. FORMAT:DDD.DDD.DDD.DDD (DDD<255) \r\n"
#define CMD_HELP_ARG_EN_SLOTID					"FORMAT:Decimal Number \r\n"
#define CMD_HELP_ARG_EN_PORTID					"FORMAT:1/2 \r\n"
//#define CMD_HELP_ARG_EN_PORTIF				"FORMAT:S1/3 or P2/2 \r\n"
//#define CMD_HELP_KEY_EN_PORT_ONU				"FORMAT:P1/2:3.\r\n"
#define CMD_HELP_ARG_EN_PORTIF_PROTECT			"FORMAT:P2/2 \r\n"
#define CMD_HELP_ARG_EN_PROTOPORT				"FORMAT:80. Range:[0,65535] \r\n"
#define CMD_HELP_ARG_EN_ONU_LLID				"Onu interface and llid. FORMAT:1/3:16 \r\n"
#define CMD_HELP_ARG_EN_ONU_LLIDSEQUENCE		"Only onu llid. FORMAT:16 \r\n"
#define CMD_HELP_ARG_EN_ONU_UNIID				"#Onu uni port. FORMAT:Decimal Number [1-4] \r\n#"
#define CMD_HELP_ARG_EN_ONU_UNILIST				"Onu uni port list. FORMAT:Decimal Number, support character ',' and '-'. Range:[1-4] \r\n"
#define CMD_HELP_ARG_EN_VLANID					"FORMAT:DDDD [1, 4094] \r\n"
#define CMD_HELP_ARG_EN_VLANLIST				"FORMAT:Decimal Number, support character ',' and '-'. Range:[1, 4094] \r\n"
#define CMD_HELP_ARG_EN_VLANRANGE				"FORMAT:Decimal Number, support character '-'. Range:[1, 4094], ex.100-200 \r\n"

#define CMD_HELP_ARG_EN_TPID					"FORMAT:0xXXXX [0x0001, 0xFFFE] \r\n"
#define CMD_HELP_ARG_EN_CFI						"FORMAT:0 or 1 \r\n"
#define CMD_HELP_ARG_EN_PORT					"Port value, FORMAT:Decimal Number \r\n"

#define CMD_HELP_ARG_EN_PRIORITY				"FORMAT:Decimal Number \r\n"
#define CMD_HELP_ARG_EN_PVID					"FORMAT:Decimal Number \r\n"
#define CMD_HELP_ARG_EN_COS						"FORMAT:Decimal Number \r\n"

#define CMD_HELP_ARG_EN_MINUTE					"Time value (minute) \r\n"
#define CMD_HELP_ARG_EN_STIME					"Time value (second) \r\n"
#define CMD_HELP_ARG_EN_100MSTIME				"Time value (100 millisecond) \r\n"
#define CMD_HELP_ARG_EN_MSTIME					"Time value (millisecond) \r\n"
#define CMD_HELP_ARG_EN_USTIME					"Time value (microsecond) \r\n"

#define CMD_HELP_ARG_EN_IGMP_PROXY_LIST			"FORMAT:Decimal Number, support character ',' and '-' \r\n"
#define CMD_HELP_ARG_EN_IGMP_PKG_LIST			"FORMAT:Decimal Number, support character ',' and '-' \r\n"


#define CMD_HELP_ARG_EN_TIMES					"Count times \r\n"

#define CMD_HELP_ARG_EN_VALUE					"Value, FORMAT:Decimal Number \r\n"
#define CMD_HELP_ARG_EN_NAME					"Object name (at the end of the string with a space character) \r\n"

#define CMD_HELP_ARG_EN_MAX_AGING_TIME			"FORMAT:Decimal Number, 0=not be aged \r\n"

#define CMD_HELP_ARG_EN_SESSIONID				"FORMAT:Decimal Number \r\n"
#define CMD_HELP_ARG_EN_GID          			"#Value of group id. FORMAT:Decimal Number \r\n#"
#define CMD_HELP_ARG_EN_STORMMODE 				"FORMAT:U=UNICAST M=MULTICAST B=BROADCAST ,=&  \r\n"
#define CMD_HELP_ARG_EN_STREAMRATE 				"FORMAT:Decimal Number (Kbps) \r\n"

#define CMD_HELP_ARG_EN_RATE_bps				"FORMAT:Decimal Number (bps) \r\n"
#define CMD_HELP_ARG_EN_RATE_Bps				"FORMAT:Decimal Number (Bps) \r\n"
#define CMD_HELP_ARG_EN_RATE_Kbps				"FORMAT:Decimal Number (Kbps) \r\n"
#define CMD_HELP_ARG_EN_RATE_KBps				"FORMAT:Decimal Number (KBps) \r\n"
#define CMD_HELP_ARG_EN_RATE_Mbps				"FORMAT:Decimal Number (Mbps) \r\n"
#define CMD_HELP_ARG_EN_RATE_MBps				"FORMAT:Decimal Number (MBps) \r\n"

#define CMD_HELP_ARG_EN_ACL_INDEX				"FORMAT:Decimal Number \r\n"
#define CMD_HELP_ARG_EN_ACL_NAME				CMD_HELP_ARG_EN_NAME
#define CMD_HELP_ARG_EN_ACL_OPTION				"FORMAT:src-mac=..., dst-mac=..., vid=..., eth-type=..., src-ip=..., dst-ip=..., ip-msg-type=..., dscp=..., src-port=..., dst-port=...\r\n"
#define CMD_HELP_ARG_EN_ACL_RULE_INDEX			"FORMAT:Decimal Number >0 \r\n"

#define CMD_HELP_ARG_EN_QUEUEID					"Value of QOS queue ID \r\n"
#define CMD_HELP_ARG_EN_COSLIST					"Priority list based on cos \r\n"
#define CMD_HELP_ARG_EN_TOSLIST					"Priority list based on tos \r\n"
#define CMD_HELP_ARG_EN_DIFFSERVLIST			"Priority list based on diffserv \r\n"
//#define CMD_HELP_ARG_EN_WEIGHTLIST				"Value of weight list \r\n"
#define CMD_HELP_ARG_EN_BANDWIDTHLIST			"Value of Bandwidth \r\n"

#define CMD_HELP_ARG_EN_THTYPE					"Threshold type. FORMAT:Decimal Number \r\n"
#define CMD_HELP_ARG_EN_THMIN					"Threshold min. FORMAT:Decimal Number \r\n"
#define CMD_HELP_ARG_EN_THMAX					"Threshold max. FORMAT:Decimal Number \r\n"

//Snmp trap specific-warning WARNING-NO
#define CMD_HELP_ARG_EN_SNMP_SWN				"Snmp specific-warning number \r\n"
#define CMD_HELP_ARG_EN_LLID_MAX				"LLID max \r\n"

#define CMD_HELP_ARG_EN_ONU_ADM_PRIORITY		"FORMAT:Decimal Number [0-7] \r\n"

#define CMD_HELP_ARG_EN_AUTO_NEGO_ABILITY		"Auto-negotiation ability. FORMAT:Decimal Number, support character ',' and '-'. Range:[1-12] \r\n"


//STP ARG

#define CMD_HELP_ARG_EN_BRIDGE_ID				"stp bridge id, FORMAT:Decimal Number \r\n"

#define CMD_HELP_ARG_EN_ALARM_ID				"alarm number \r\n"
#define CMD_HELP_ARG_EN_ALARM_THRESHOLD			"alarm threshold \r\n"
#define CMD_HELP_ARG_EN_ALARM_CLEAR_THRESHOLD	"clear alarm threshold \r\n"

#define CMD_HELP_ARG_EN_TIMEZONE				"timezone, FORMAT:Decimal Number [-12,13]\r\n"


#define CMD_HELP_KEY_EN_ONU_IMAGE_SWITCH		"All onu image switch \r\n"
#define CMD_HELP_KEY_EN_ONU_IMAGE				"onu image \r\n"

#define CMD_HELP_KEY_EN_P2P						"p2p\r\n"
#define CMD_HELP_KEY_EN_FULL					"All onu can communicate.\r\n"

//snmp community
#define CMD_HELP_KEY_EN_SNMP_SERVER				"Configure snmp-server\r\n"
#define CMD_HELP_KEY_EN_COMMUNITY				"community\r\n"
#define CMD_HELP_KEY_EN_COMMUNITY_NAME			"COMMUNITY-NAME\r\n"
#define	CMD_HELP_KEY_EN_RO						"ro\r\n"
#define CMD_HELP_KEY_EN_RW						"rw\r\n"
#define CMD_HELP_KEY_EN_HOST 					"trap information\r\n"
#define CMD_HELP_KEY_EN_HOST_NAME				"\r\n"

#define CMD_TRSD_TYPE_MAX 		31


#if 0
#endif


////////////////////////////////////////////////////////////////////////////////
//																			  //
//					�� �� �� ���� �� �塢ö �� �� ��						  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
typedef enum tag_command_menu_index
{
	CMD_MID_ERR_GET,
	CMD_MID_ERR_SET,
	
    CMD_MID_ZONE,
    CMD_MID_YEAR,
	CMD_MID_MONTH,
	CMD_MID_DAY,
	CMD_MID_HOUR,
	CMD_MID_MINUTE,
	CMD_MID_SECOND,

	CMD_MID_NUM,
	CMD_MID_FILE_NAME, 
	CMD_MID_FILE_SIZE,
	CMD_MID_FILE_CREATE_DATA,

	CMD_MID_VERINFO,
	CMD_MID_SOFTVER,
	CMD_MID_HARDVER,
	CMD_MID_MGNTIN,
	CMD_MID_MGNTOUT,
	CMD_MID_MACADDR,
	CMD_MID_IPADDR,
	CMD_MID_NETMASK,
	CMD_MID_GATEWAY,
	CMD_MID_VLANID,
	CMD_MID_PRORITY,

	CMD_MID_OLTPPT,
	CMD_MID_NAME,
	CMD_MID_TYPE,
		CMD_MID_TYPE_BDCTRL,
		CMD_MID_TYPE_BDGEPON,
		CMD_MID_TYPE_BDUPLINK,
		CMD_MID_TYPE_BDSWITCH,
		CMD_MID_TYPE_BDOTHER,
		CMD_MID_TYPE_BDVACANT,
	CMD_MID_ADMINSTA,
		CMD_MID_STA_UP,
		CMD_MID_STA_DOWN,
		CMD_MID_STA_TESTING,
	CMD_MID_UPTIME,
	CMD_MID_SRVSLOTS,
	CMD_MID_POWERSLOTS,
	CMD_MID_FANSLOTS,
	CMD_MID_DEVSTYLE,
		CMD_MID_STYLE_FIXED,
		CMD_MID_STYLE_CHASSIS,
		CMD_MID_STYLE_OTHER,

	CMD_MID_BDINFO,
	CMD_MID_SLOT,
	CMD_MID_MAINBACK,//�������࣬��Ӧktep_board_attr_e
	    CMD_MID_MB_ACT,
	    CMD_MID_MB_STBY,
	    CMD_MID_MB_STAL,
	    CMD_MID_MB_NOTAP,
	CMD_MID_FIRMVER,
	CMD_MID_WARNSTA,
		CMD_MID_WARN_NONE,		 //�޸澯
		CMD_MID_WARN_CRITICAL,		 //������
		CMD_MID_WARN_MAJOR,			 //���ص�
		CMD_MID_WARN_MINOR,			 //�����ص�
		CMD_MID_WARN_WARNING,			 //����
	CMD_MID_SERIALNO,
	CMD_MID_SLOTSTA,
	    CMD_MID_SLOTSTA_INSTALL,
	    CMD_MID_SLOTSTA_UNINSTALL,
        CMD_MID_SLOTSTA_OTHERS,

    CMD_MID_MAT,
	CMD_MID_PORT,
		CMD_MID_PORT_OLTSNI,
		CMD_MID_PORT_OLTPON,
		CMD_MID_PORT_ONUPON,
		CMD_MID_PORT_ONUUNI,
		CMD_MID_PORT_OLTTRUNK,
		CMD_MID_PORT_OLTCPU,
		CMD_MID_PORT_OLTMII,
	CMD_MID_DYNAMIC,
	CMD_MID_STATIC,

    CMD_MID_STORMCTRL,
    CMD_MID_UNICAST,
    CMD_MID_MULTI,
    CMD_MID_BROAD,
    CMD_MID_ENABLE,
    CMD_MID_DISABLE,
    CMD_MID_STATE,
    CMD_MID_INGRESS,
    CMD_MID_EGRESS,
    CMD_MID_INGRESS_RATE,
    CMD_MID_EGRESS_RATE,
    CMD_MID_BPS,
    CMD_MID_KBPS,
    CMD_MID_FRAMES_PS,
    CMD_MID_BYTES_PS,

    CMD_MID_MIRROR,
    CMD_MID_SESSION,
    CMD_MID_SOURCE,
    CMD_MID_DESTINATION,

	CMD_MID_SNI_INFO,
	CMD_MID_SNI_COMBO_MODE,
	CMD_MID_SNI_MEDIA_TYPE,
		CMD_MID_MEDIA_COPPER,
		CMD_MID_MEDIA_FIBER,
        CMD_MID_MEDIA_AUTO,
		CMD_MID_MEDIA_OTHER,
	CMD_MID_AUTO_NEGO_ENABLE,
	CMD_MID_AUTO_NEGO_STA,
	CMD_MID_AUTO_NEGO_MODE,
		CMD_MID_AN_AUTO,
		CMD_MID_AN_H10,
		CMD_MID_AN_F10,
		CMD_MID_AN_H100,
		CMD_MID_AN_F100,
		CMD_MID_AN_F1000,
		CMD_MID_AN_F10000,
	CMD_MID_LAST_CHG_TIME,
	CMD_MID_LINK_UP,
	CMD_MID_LINK_DOWN,	
	CMD_MID_PORT_ENABLE,
	CMD_MID_PORT_MAC,

    CMD_MID_PON_INFO,
    CMD_MID_PON_CRYPTO_INFO,
    CMD_MID_MAX_ONU,
    CMD_MID_UP_ONU,    
    CMD_MID_ENCRYPT_ENABLE,
    CMD_MID_ENCRYPT_MODE,
    CMD_MID_ENCRYPT_MODE_NONE,
        CMD_MID_ENCRYPT_MODE_AES32,
        CMD_MID_ENCRYPT_MODE_AES48,
        CMD_MID_ENCRYPT_MODE_AES128,
        CMD_MID_ENCRYPT_MODE_CTCTRIPLECHURNING,
        CMD_MID_ENCRYPT_MODE_OTHER,
    CMD_MID_ENCRYPT_KEY_EXCHANGE_TIME,
    CMD_MID_ISOLATION_EN,
    CMD_MID_FLOW_CONTROL_EN,
    CMD_MID_LOOPBACK_DETECT_EN,
    CMD_MID_DS_BANDWIDTH_MAX,
    CMD_MID_DS_BANDWIDTH_INUSE,
    CMD_MID_DS_BANDWIDTH_REMAIN,
    CMD_MID_15M_EN,
    CMD_MID_24H_EN,
    CMD_MID_MACADDR_LEARN_MAXNUM,
    CMD_MID_UP_BANDWIDTH_MAX,
	CMD_MID_UP_BANDWIDTH_INUSE,
	CMD_MID_UP_BANDWIDTH_REMAIN,

	CMD_MID_ACL_RULE_INFO,
	CMD_MID_ACL_RULE_PERMIT,
	CMD_MID_ACL_RULE_DENY,
	CMD_MID_ACL_RULE_MARK,

	CMD_MID_ACL_LIST_INFO,
	CMD_MID_ACL_IP,
	CMD_MID_ACL_ACL,
	CMD_MID_ACL_TYPE,
		CMD_MID_ACL_TYPE_STD,
		CMD_MID_ACL_TYPE_EXTEND,
		CMD_MID_ACL_TYPE_EXPERT_EXTEND,

	CMD_MID_ACL_GROUP_INFO,
	CMD_MID_ACL_INGRESS,
	CMD_MID_ACL_EGRESS,
	CMD_MID_ACL_NO_ACL,

	CMD_MID_SLA_INFO,
	CMD_MID_ONU_LLID,
	CMD_MID_DS_FIXED,
	CMD_MID_DS_PEEK,
	CMD_MID_DS_COMMITTED,
	CMD_MID_US_FIXED,
	CMD_MID_US_PEEK,
	CMD_MID_US_COMMITTED,

    CMD_MID_VLAN_GBL_INFO,
	CMD_MID_VLAN_ID_MAX,
	CMD_MID_VLAN_NUM_MAX,
	CMD_MID_VLAN_NUM_CREATED,
	CMD_MID_VLAN_SVLAN_TPID,

	CMD_MID_VLAN_CFG_INFO,
	CMD_MID_VLAN_NAME,
	CMD_MID_VLAN_TAG,
	CMD_MID_VLAN_UNTAG,

	CMD_MID_VLAN_PORT_INFO,
	CMD_MID_VLAN_TAGTPID,
	CMD_MID_VLAN_TAGCFI,
	CMD_MID_VLAN_PRIORITY,
	CMD_MID_VLAN_PVID,
	CMD_MID_VLAN_MODE,
	    CMD_MID_VLAN_MODE_TRANSPARENT,
	    CMD_MID_VLAN_MODE_TAG,
	    CMD_MID_VLAN_MODE_TRANSLATION,
	    CMD_MID_VLAN_MODE_AGGREGATION,
	    CMD_MID_VLAN_MODE_TRUNK,
	    CMD_MID_VLAN_MODE_ACCESS,
	    CMD_MID_VLAN_MODE_STACKING,
	    CMD_MID_VLAN_MODE_STRUNK,
	CMD_MID_VLAN_TYPE,
	    CMD_MID_VLAN_TYPE_CVLAN,
	    CMD_MID_VLAN_TYPE_SVLAN,

	CMD_MID_VLAN_FULL_NOTE,

	CMD_MID_IGMP_INFO,
	CMD_MID_IGMP_ENABLE,
	CMD_MID_IGMP_MODE,
	    CMD_MID_IGMP_MODE_CENTRALIZED,
	    CMD_MID_IGMP_MODE_DISTRIBUTEWITHCM,
	    CMD_MID_IGMP_MODE_DISABLED,
	    CMD_MID_IGMP_MODE_DISTRIBUTEDWOCM,
	CMD_MID_IGMP_MAXQUERESTIME,
	CMD_MID_IGMP_ROBUST,
	CMD_MID_IGMP_QUEINTERVAL,
	CMD_MID_IGMP_LASTMEMQUEINTERVAL,
	CMD_MID_IGMP_LASTMEMQUECOUNT,
	CMD_MID_IGMP_VERSION,

	CMD_MID_IGMP_PROXY_GROUP_INFO,
	CMD_MID_IGMP_PROXY_GROUP_NAME,
	CMD_MID_IGMP_PROXY_GROUP_SRCIP,
	CMD_MID_IGMP_PROXY_GROUP_MCASTVID,
	CMD_MID_IGMP_PROXY_GROUP_MCASTIP,
	CMD_MID_IGMP_PROXY_GROUP_MCASTABW,
	CMD_MID_IGMP_PROXY_GROUP_MCASTMBW,

	CMD_MID_IGMP_FWD_INFO,

	CMD_MID_FILE_CFG_UP_INFO,
	CMD_MID_FILE_CFG_DOWN_INFO,
	CMD_MID_FILE_KERNEL_INFO,
	CMD_MID_FILE_FILESYS_INFO,
	CMD_MID_FILE_OLT_INFO,

	CMD_MID_FILE_TRAN_PROTOCOL,
	CMD_MID_FILE_TRAN_IP,
	CMD_MID_FILE_TRAN_USRNAME,
	CMD_MID_FILE_TRAN_USRPWD,
	CMD_MID_FILE_TRAN_SRC,
	CMD_MID_FILE_TRAN_DST,
	CMD_MID_FILE_TRAN_STA,
		CMD_MID_FILE_TRAN_STA_IDLE,
		CMD_MID_FILE_TRAN_STA_PROCESS,
		CMD_MID_FILE_TRAN_STA_SUCCESS,
		CMD_MID_FILE_TRAN_STA_FAILED,
		CMD_MID_FILE_TRAN_STA_NO_RESOURCE,
		CMD_MID_FILE_TRAN_STA_STOP_SUCCESS,

	CMD_MID_SNTP_INFO,
		CMD_MID_SNTP_STA,
		CMD_MID_SNTP_SERVER,
		CMD_MID_SNTP_INTERVAL,
		CMD_MID_SNTP_ZONE,

//onu
    CMD_MID_ON_LINE,
    CMD_MID_OFF_LINE,
	CMD_MID_ONU_LIST_INFO,
	CMD_MID_ONU_ID,
	CMD_MID_ONU_MAC_AGING,
	CMD_MID_ONU_CHIP_VENDOR,
	CMD_MID_ONU_CHIP_TYPE,
	CMD_MID_ONU_CHIP_VER,
	CMD_MID_ONU_SFTWR_VER,
	CMD_MID_ONU_FRMWR_VER,
	CMD_MID_ONU_DISTANCE,
	CMD_MID_ONU_REG_TIME,
	CMD_MID_ONU_PROFILE,
	CMD_MID_PRIORITY,
	CMD_MID_ONU_TRAP_IP,
	CMD_MID_POWER_DOWN,
	CMD_MID_ONU_STATUS_AUTH_REJECT,

	CMD_MID_DHCP,
	CMD_MID_YES,
	CMD_MID_NO,
	CMD_MID_BIND_MAC,
	CMD_MID_THERE_ARE,
	CMD_MID_ONU,

	CMD_MID_ONU_OPT_TRANS_INFO,
	CMD_MID_ONU_OPT_REC_POWER,
	CMD_MID_ONU_OPT_TRANS_POWER,
	CMD_MID_ONU_BIAS_CURRENT,
	CMD_MID_ONU_WORK_V,
	CMD_MID_ONU_WORK_T,
	CMD_MID_FEC_ENABLE,

	CMD_MID_ONU_CAP_INFO,
	CMD_MID_ONU_GE_NUM,
	CMD_MID_ONU_GE_BMP,
	CMD_MID_ONU_FE_NUM,
	CMD_MID_ONU_FE_BMP,
	CMD_MID_ONU_QUE_NUM_UP,
	CMD_MID_ONU_QUE_NUM_UP_MAX,
	CMD_MID_ONU_QUE_NUM_DOWN,
	CMD_MID_ONU_QUE_NUM_DOWN_MAX,

	CMD_MID_ONU_AUTH_POLICY,
	CMD_MID_ONU_BLACK_LIST,
	CMD_MID_ONU_WHITE_LIST,
	CMD_MID_ONU_ACCEPT_ALL,
	CMD_MID_ONU_AUTH_INFO,
	CMD_MID_INDEX,
	CMD_MID_ONU_AUTH_ACTION,
	CMD_MID_ONU_AUTH_REJECT,
	CMD_MID_ONU_AUTH_ACCEPT,
	CMD_MID_ONU_AUTH_MODE,
	CMD_MID_MODE,
	CMD_MID_ONU_AUTH_REJECT_LIST,

	CMD_MID_ONU_AUTH,
	CMD_MID_ONU_LOID_LIST,
	CMD_MID_ONU_LOID_PWD_LIST,
	CMD_MID_ONU_MIX_WHITE_LOID_LIST,
	CMD_MID_ONU_MIX_WHITE_LOID_PWD_LIST,
	CMD_MID_ONU_AUTH_LOID,
	CMD_MID_ONU_AUTH_PASSWORD,

	CMD_MID_ONU_UPGRADE_STATUS,
	CMD_MID_ONU_STATUS,
	CMD_MID_ONU_WAIT_UPGRADE,
	CMD_MID_ONU_UPGRADE_FAILED,	
	CMD_MID_ONU_UPGRADE_SUCCESSED,
	CMD_MID_ONU_UPGRADE_SWITCH_FINISHED,
	CMD_MID_ONU_PROFILE_ID,
	CMD_MID_ONU_PROFILE_NAME,
	CMD_MID_ONU_PROFILE_ONU_NUM,

	
//UNI
	CMD_MID_UNI,
	CMD_MID_AUTO_NEGO_ABL_LOCAL,
	CMD_MID_AUTO_NEGO_ABL_REMOTE,
	CMD_MID_AUTO_NEGO_RESTART,
#if 1
	CMD_MID_AUTO_NEGO_ABL_F10,
	CMD_MID_AUTO_NEGO_ABL_H10,
	CMD_MID_AUTO_NEGO_ABL_F100,
	CMD_MID_AUTO_NEGO_ABL_H100,
	CMD_MID_AUTO_NEGO_ABL_F1000,
	CMD_MID_AUTO_NEGO_ABL_H1000,
	CMD_MID_AUTO_NEGO_ABL_F1000X,
	CMD_MID_AUTO_NEGO_ABL_H1000X,
	CMD_MID_AUTO_NEGO_ABL_FDX,
	CMD_MID_AUTO_NEGO_ABL_FDXA,
	CMD_MID_AUTO_NEGO_ABL_FDXS,
	CMD_MID_AUTO_NEGO_ABL_FDXB,
#endif	
	CMD_MID_UNI_ATTR,
	CMD_MID_ONU_ID_IS,
	CMD_MID_NON_AGING,
	CMD_MID_AGING_TIME_IS,
	CMD_MID_STATIC_MAT,
	CMD_MID_DYNAMIC_MAT,
	CMD_MID_MAX_LRN,
	CMD_MID_SNI_STATIC_MAC,
	CMD_MID_MUTI_MAC_NOT_STATIC,
	CMD_MID_MAC_FULL_NOTE,
	
	CMD_MID_UNI_RATE_LIMIT,
	CMD_MID_CIR,
	CMD_MID_CBS,
	CMD_MID_EBS,
	CMD_MID_PIR,
	CMD_MID_LINK_STATUS,
//statistics
	CMD_MID_STATS_CONF_INFO,
	CMD_MID_STATS_M15_MAX,
	CMD_MID_STATS_H24_MAX,
	CMD_MID_STATS_NAME,
	CMD_MID_STATS_IN,
	CMD_MID_STATS_OUT,
	
	CMD_MID_STATS_OCTS,
	CMD_MID_STATS_PKTS,
	CMD_MID_STATS_PKTS_BROD,
	CMD_MID_STATS_PKTS_MULT,
	CMD_MID_STATS_PKTS_64,
	CMD_MID_STATS_PKTS_65_127,
	CMD_MID_STATS_PKTS_128_255,
	CMD_MID_STATS_PKTS_256_511,
	CMD_MID_STATS_PKTS_512_1023,
	CMD_MID_STATS_PKTS_1024_1518,
	CMD_MID_STATS_PKTS_1519_2047,
	CMD_MID_STATS_PKTS_UNDERSIZE,
	CMD_MID_STATS_PKTS_OVERSIZE,
	CMD_MID_STATS_FRAGMENTS,
	CMD_MID_STATS_MPCP_FRMS,
	CMD_MID_STATS_MPCP_OCTS,
	CMD_MID_STATS_OAM_FRMS,
	CMD_MID_STATS_OAM_OCTS,
	CMD_MID_STATS_PKTS_CRC_ERR,
	CMD_MID_STATS_DROP_EVTS,
	CMD_MID_STATS_JABBERS,
	CMD_MID_STATS_COLLISIONS,

	CMD_MID_STATS_PKTS_DISCARD,
	CMD_MID_STATS_PKTS_ERR,
	CMD_MID_STATS_STATUS_CHG_TIMES,
	CMD_MID_STATS_ENABLE,
	CMD_MID_STATS_PERIOD,

	CMD_MID_STATS_INFO_CUR,
	CMD_MID_STATS_INFO_HISTORY,
	CMD_MID_STATS_IS_VALID,
	CMD_MID_STATS_START_TIME,
	CMD_MID_STATS_END_TIME,
	CMD_MID_STATS_INFO_M15,
	CMD_MID_STATS_INFO_H24,
	CMD_MID_STATS_CUR_IS,
	CMD_MID_STATS_INFO_THRESHOLD,
//PPG
	CMD_MID_PPG_INFO,
	CMD_MID_PPG_ID,
	CMD_MID_PPG_ENABLE,
	CMD_MID_ON,
	CMD_MID_OFF,
	CMD_MID_PPG_PORT_MAIN,
	CMD_MID_PPG_PORT_BACKUP,
	CMD_MID_PPG_SWITCH_MODE,
	CMD_MID_AUTO,
	CMD_MID_MANUAL,
	CMD_MID_PPG_STATUS,
	CMD_MID_PPG_PRIMARY,
	CMD_MID_PPG_SECONDARY,
	CMD_MID_PPG_UNLOCK,
	CMD_MID_PPG_RECOVER_TIME,
//QOS
	CMD_MID_DEVICE_ID,
	CMD_MID_QOS_QUE_MAX,
	CMD_MID_QOS_MODE,
	CMD_MID_QOS_BASED_PORT,
	CMD_MID_QOS_BASED_DEVICE,
	CMD_MID_QOS_GBL_INFO,

	CMD_MID_QOS_PRI_ERR,
	CMD_MID_QOS_GO_CFG_MODE,
	CMD_MID_QOS_CMD_MODE_ERR,
	CMD_MID_QOS_MODE_ERR,

	CMD_MID_QOS_MAP_RULE,
	CMD_MID_QOS_COS,
	CMD_MID_QOS_TOS,
	CMD_MID_QOS_DSCP,
	CMD_MID_QOS_PRI_MAX,
	CMD_MID_QOS_MAP_QUE,
	CMD_MID_QOS_MAP_INFO,

	CMD_MID_QOS_SCHE_INFO,
	CMD_MID_QOS_SCHE_POLICY,
	CMD_MID_QOS_SP,
	CMD_MID_QOS_WRR,
	CMD_MID_QOS_SPWRR,
	CMD_MID_QOS_WFP,
	CMD_MID_QOS_WEIGHT_VALUE,
	CMD_MID_QOS_WEIGHT_VALUE_INVALID,
	CMD_MID_QOS_CHANGE_WEIGHT_LIST,
	
//alarm
	CMD_MID_TRAP_INFO,
	CMD_MID_TRAP_ENABLE,
	
	CMD_MID_CONFIRM,
	CMD_MID_ALARM_DESP,
	CMD_MID_SEVERITY,
	CMD_MID_CRITICAL,
	CMD_MID_MAJOR,
	CMD_MID_MINOR,
	CMD_MID_WARNING,
	CMD_MID_INFO,
	CMD_MID_CLEAR,
	
	CMD_MID_FIRST_TIME,
	CMD_MID_LAST_TIME,
	CMD_MID_ADD_TEXT,
	CMD_MID_ALARM_INFO_CURRENT,
	CMD_MID_ALARM_INFO_HISTORY,
	CMD_MID_ALARM_INFO_EVENT,

	CMD_MID_ALARM_UNKNOWN,
	CMD_MID_ALARM_BOARD_PROVISION_FAIL,
	CMD_MID_ALARM_BOARD_RESET,
	CMD_MID_ALARM_BOARD_REMOVEL,
	CMD_MID_ALARM_BOARD_TEMP_ABNORMAL,
	CMD_MID_ALARM_FAN_FAILED,
	CMD_MID_ALARM_FAN_REMOCAL,
	CMD_MID_ALARM_POWER_FAILED,
	CMD_MID_ALARM_POWER_REMOVAL,
	CMD_MID_ALARM_FATAL_OLT_HW_ERROR,

	CMD_MID_ALARM_PON_OPT_FAULTY,
	CMD_MID_ALARM_SNI_OPT_FAULTY,
	CMD_MID_ALARM_PON_LINK_FAULTY,
	CMD_MID_ALARM_SNI_LINK_FAULTY,
	CMD_MID_ALARM_PON_RLOS,
	CMD_MID_ALARM_SNI_RLOS,

	
	CMD_MID_OLT_DOWNSTREAMDROPEVENTSALARM,
	CMD_MID_OLT_UPSTREAMDROPEVENTSALARM,
	CMD_MID_OLT_DOWNSTREAMCRCERRORFRAMESALARM,
	CMD_MID_OLT_DOWNSTREAMUNDERSIZEFRAMESALARM,
	CMD_MID_OLT_UPSTREAMUNDERSIZEFRAMESALARM,
	CMD_MID_OLT_DOWNSTREAMOVERSIZEFRAMESALARM,
	CMD_MID_OLT_UPSTREAMOVERSIZEFRAMESALARM,
	CMD_MID_OLT_DOWNSTREAMFRAGMENTSALARM,
	CMD_MID_OLT_DOWNSTREAMJABBERSALARM,
	CMD_MID_OLT_DOWNSTREAMCOLLISIONSALARM,
	CMD_MID_OLT_DOWNSTREAMDISCARDFRAMESALARM,
	CMD_MID_OLT_UPSTREAMDISCARDFRAMESALARM,
	CMD_MID_OLT_DOWNSTREAMERRORFRAMESALARM,
	

//stp
#if 0
	CMD_MID_STP_BR_INFO,
	CMD_MID_STP_BRIDGE,
	CMD_MID_STP_ENABLE,
	CMD_MID_STP_VER,
	CMD_MID_SSTP,
	CMD_MID_RSTP,
	CMD_MID_MSTP,
	
	CMD_MID_STP_TOPO_CHG_DET,
	CMD_MID_STP_TOPO_CHG,
	
	CMD_MID_STP_PRI,
	CMD_MID_STP_CHG_TIME,
	CMD_MID_STP_CHG_COUNT,
	CMD_MID_STP_ROOT_PATH_COST,
	CMD_MID_STP_MAX_AGE,
	CMD_MID_STP_HELLO_TIME,
	CMD_MID_STP_HOLD_TIME,
	CMD_MID_STP_FWD_DELAY,
	CMD_MID_STP_TXHOLD_CNT,
	CMD_MID_STP_MAX_HOPS,

	CMD_MID_STP_ROOT_MAX_AGE,
	CMD_MID_STP_ROOT_HELLO_TIME,
	CMD_MID_STP_ROOT_FWD_DELAY,
	CMD_MID_STP_COST_METHOD,
	CMD_MID_STP_COST_METHOD_SHORT,
	CMD_MID_STP_COST_METHOD_LONG,
	CMD_MID_STP_COST_METHOD_DEF,

	CMD_MID_STP_ROOT_PORT_INDEX,

	CMD_MID_STP_ROOT_BR_ID,
	CMD_MID_STP_REG_ROOT_BR_ID,
	CMD_MID_STP_BR_ID,

	CMD_MID_STP_PORTFAST_BPDU_FILTER,
	CMD_MID_STP_PORTFAST_BPDU_GUARD,
	CMD_MID_STP_PORTFAST_ERRD_TO,
	CMD_MID_STP_PORTFAST_ERRD_TO_ITV,

	CMD_MID_STP_PORT_INFO,
	CMD_MID_STP_PORT_NAME,
	CMD_MID_STP_PORT_INDEX,
	CMD_MID_STP_PORT_ID,
	CMD_MID_STP_PORT_ROLE,
	CMD_MID_STP_PORT_STATE,

	CMD_MID_STP_PATH_COST,
	CMD_MID_MSTP_EXTERNAL_ROOT_PATH_COST,
	CMD_MID_MSTP_INTERNAL_ROOT_PATH_COST,
	
	CMD_MID_MSTP_REF_COUNT,
	CMD_MID_STP_DESIGNATED_PORT_ID,

	CMD_MID_MSTP_CIST_ROOT,
	CMD_MID_MSTP_DESIGNATED_BRIDGE,
	CMD_MID_MSTP_MESSAGE_AGE,

	CMD_MID_MSTP_FORWARD_TIMER_REMAIN,
	CMD_MID_MSTP_MESSAGE_AGE_TIMER_REMAIN,
	CMD_MID_MSTP_HELLO_TIMER_REMAIN,
	CMD_MID_MSTP_TOPOLOGY_CHANGE_TIMER_REMAIN,

	CMD_MID_MSTP_FORWARD_TRANS,
	CMD_MID_MSTP_PORTFAST_CONFIG,
	CMD_MID_MSTP_BPDU_GUARD,
	CMD_MID_MSTP_CURRENT_BPDU_GUARD,
	CMD_MID_MSTP_BPDU_FILTER,
	CMD_MID_MSTP_CURRENT_BPDU_FILTER,
	CMD_MID_MSTP_ROOT_GUARD_CONFIG,
	CMD_MID_MSTP_CURRENT_ROOT_GUARD,
#endif

//igmp configure
	CMD_MID_VLAN_MULTICAST_INFO,
	CMD_MID_VLAN_ID_RANGE,
	CMD_MID_VLAN_MULTICAST_PORT_INFO,
	CMD_MID_VLAN_MULTICAST_ID,
	CMD_MID_VLAN_MCST_IGMP_PORT_INFO,
	
	CMD_MID_MULTICAST_CONTROL_PKG_INFO,
	CMD_MID_PKG_INDEX,
	CMD_MID_PKG_NAME,
	CMD_MID_IGMP_PROXY_LIST,
	CMD_MID_IGMP_MULTICAST_USER_AUTHORITY,
	CMD_MID_IGMP_MAX_REQUEST_CHANNEL_NUM,
	CMD_MID_IGMP_SINGLE_PREVIEW_TIME,
	CMD_MID_IGMP_TOTAL_PREVIEW_TIME,
	CMD_MID_IGMP_PREVIEW_RESET_TIME,
	CMD_MID_IGMP_PREVIEW_INTERVAL_TIME,
	CMD_MID_IGMP_PREVIEW_COUNT,

	CMD_MID_IGMP_MULTICAST_USER_AUTHORITY_INFO,
	CMD_MID_PKG_LIST,
	CMD_MID_IGMP_GLOBAL_BW,
	CMD_MID_IGMP_GLOBAL_BW_USED,
	
//file-system
	CMD_MID_FILE_SYS_INFO,
	CMD_MID_SYS_INDEX,
	CMD_MID_SYS_START_FALG,
	CMD_MID_SYS_INFO,

//rate
	CMD_MID_OLT_INTERFACE_RATE_INFO,
//isolation
       CMD_MID_OLT_INTERFACE_ISOT_INFO, 

//onu max distance
	CMD_MID_OLT_PON_ONU_MAX_DISTANCE,

//snmp community 
	CMD_MID_SNMP_COMMUNITY_LIST_INFO,
	CMD_MID_COMMUNITY_NAME,
	CMD_MID_COMMUNITY_PERMISSION,

//other	
	CMD_MID_NOTSUPPORT,
	CMD_MID_NULL,
	CMD_MID_MAXNUM
} cli_cmd_mid_e;

typedef enum etag_command_menu_language_type
{
	CMD_ML_CN,
    CMD_ML_EN,
	CMD_ML_MAXNUM
} cli_cmd_mlan_e;



////////////////////////////////////////////////////////////////////////////////
//																			  //
//						�� �� �� ���� �� �� �� ��							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////



#endif /* __INC_BC_CLI_TEXT_H__ */

