/*******************************************************************************
  -------------------------------------------------------------------------
  [File name]  : \\BC\cli\cli_cmds\bc_cli_base.h
  [Author]     : bain.wang@outlook.com
  [Version]    : 1.0
  [Date]       : 2017-06-10
  [Description]:

  [Others]     :

  [Function List]:
	1. ....
	2. ....
  [History]:
	 D a t e	Modification										  Initials
	---------- --------------										 ----------
	2016-06-25	Created 									bain.wang@outlook.com
	2017-06-04	Created 									bain.wang@outlook.com
*******************************************************************************/

#ifndef __IN_BC_CLI_BASE_H__
#define __IN_BC_CLI_BASE_H__

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								头   文   件								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_cli.h"
#include "bc_cli_text.h"
//#include "l1/port/bc_port_def.h"
//#include "l2/fdb/bc_fdb_def.h"




////////////////////////////////////////////////////////////////////////////////
//																			  //
//								宏   定   义								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#define CLI_LAN						(bc_cli_get_lan() == CLI_LAN_CN ? CMD_ML_CN : CMD_ML_EN)

#define CMD_GET_STRING(string_id)  	((const char *)bc_cli_menu[string_id][CLI_LAN]) // bc_cli_menu


#define CMD_HELP_KEY_EN_ETHTYPE_ipv4 			"#Internet Protocol version 4 (type 0x0800).#"
#define CMD_HELP_KEY_EN_ETHTYPE_ipv6 			"#Internet Protocol version 6 (type 0x86DD).#"
#define CMD_HELP_KEY_EN_ETHTYPE_arp 			"#Address Resolution Protocol (type 0x0806).#"
#define CMD_HELP_KEY_EN_ETHTYPE_rarp 			"#Reverse Address Resolution Protocol (type 0x8035).#"
#define CMD_HELP_KEY_EN_ETHTYPE_fr	 			"#Frame Relay (type 0x0808).#"
#define CMD_HELP_KEY_EN_ETHTYPE_ppp 			"#Point-to-Point Protocol (type 0x880B).#"
#define CMD_HELP_KEY_EN_ETHTYPE_gsmp 			"#General Switch Management Protocol (type 0x880C).#"
#define CMD_HELP_KEY_EN_ETHTYPE_mpls 			"#Multiprotocol Label Switching (type 0x8847).#"
#define CMD_HELP_KEY_EN_ETHTYPE_mps 			"#Multiprotocol Label Switching with Upstream-assigned Label (type 0x8848).#"
#define CMD_HELP_KEY_EN_ETHTYPE_mcap 			"#Multicast Channel Allocation Protocol (type 0x8861).#"
#define CMD_HELP_KEY_EN_ETHTYPE_pppoed 			"#PPP over Ethernet Discovery Stage (type 0x8863).#"
#define CMD_HELP_KEY_EN_ETHTYPE_pppoes 			"#PPP over Ethernet Session Stage (type 0x8864).#"
#define CMD_HELP_KEY_EN_ETHTYPE_ctag 			"#Customer VLAN Tag Type (type 0x8100).#"
#define CMD_HELP_KEY_EN_ETHTYPE_epon 			"#Ethernet Passive Optical Network (type 0x8808).#"
#define CMD_HELP_KEY_EN_ETHTYPE_pbnac 			"#Port-based network access control (type 0x888E).#"
#define CMD_HELP_KEY_EN_ETHTYPE_stag 			"#Service VLAN tag identifier (type 0x88A8).#"
#define CMD_HELP_KEY_EN_ETHTYPE_ethexp1 		"#Local Experimental Ethertype 1 (type 0x88B5).#"
#define CMD_HELP_KEY_EN_ETHTYPE_ethexp2 		"#Local Experimental Ethertype 2 (type 0x88B6).#"
#define CMD_HELP_KEY_EN_ETHTYPE_ethoui 			"#OUI Extended Ethertype (type 0x88B7).#"
#define CMD_HELP_KEY_EN_ETHTYPE_preauth 		"#Pre-Authentication (type 0x88C7).#"
#define CMD_HELP_KEY_EN_ETHTYPE_lldp 			"#Link Layer Discovery Protocol (type 0x88CC).#"
#define CMD_HELP_KEY_EN_ETHTYPE_macsec 			"#Media Access Control Security (type 0x88E5).#"
#define CMD_HELP_KEY_EN_ETHTYPE_mvrp 			"#Multiple VLAN Registration Protocol (type 0x88F5).#"
#define CMD_HELP_KEY_EN_ETHTYPE_mmrp 			"#Multiple Multicast Registration Protocol (type 0x88F6).#"
#define CMD_HELP_KEY_EN_ETHTYPE_frrr 			"#Fast Roaming Remote Request (type 0x890D).#"
#define CMD_HELP_ARG_EN_ETHTYPE 				"#Ethernet type. 2bytes length.#"

#define STR_CMD_RULE_ETH_TYPE \
			"{ " \
				"ipv4 " 				CMD_HELP_KEY_EN_ETHTYPE_ipv4 CMD_HELP_KEY_EN_ETHTYPE_ipv4 \
				"| " \
				"ipv6 " 				CMD_HELP_KEY_EN_ETHTYPE_ipv6 CMD_HELP_KEY_EN_ETHTYPE_ipv6 \
				"| " \
				"arp "					CMD_HELP_KEY_EN_ETHTYPE_arp CMD_HELP_KEY_EN_ETHTYPE_arp \
				"| " \
				"rarp " 				CMD_HELP_KEY_EN_ETHTYPE_rarp CMD_HELP_KEY_EN_ETHTYPE_rarp \
				"| " \
				"fr "					CMD_HELP_KEY_EN_ETHTYPE_fr CMD_HELP_KEY_EN_ETHTYPE_fr \
				"| " \
				"ppp "					CMD_HELP_KEY_EN_ETHTYPE_ppp CMD_HELP_KEY_EN_ETHTYPE_ppp \
				"| " \
				"gsmp " 				CMD_HELP_KEY_EN_ETHTYPE_gsmp CMD_HELP_KEY_EN_ETHTYPE_gsmp \
				"| " \
				"mpls " 				CMD_HELP_KEY_EN_ETHTYPE_mpls CMD_HELP_KEY_EN_ETHTYPE_mpls \
				"| " \
				"mps "					CMD_HELP_KEY_EN_ETHTYPE_mps CMD_HELP_KEY_EN_ETHTYPE_mps \
				"| " \
				"mcap " 				CMD_HELP_KEY_EN_ETHTYPE_mcap CMD_HELP_KEY_EN_ETHTYPE_mcap \
				"| " \
				"pppoe-d "				CMD_HELP_KEY_EN_ETHTYPE_pppoed CMD_HELP_KEY_EN_ETHTYPE_pppoed \
				"| " \
				"pppoe-s "				CMD_HELP_KEY_EN_ETHTYPE_pppoes CMD_HELP_KEY_EN_ETHTYPE_pppoes \
				"| " \
				"ctag " 				CMD_HELP_KEY_EN_ETHTYPE_ctag CMD_HELP_KEY_EN_ETHTYPE_ctag \
				"| " \
				"stag " 				CMD_HELP_KEY_EN_ETHTYPE_stag CMD_HELP_KEY_EN_ETHTYPE_stag \
				"| " \
				"ethexp1 "				CMD_HELP_KEY_EN_ETHTYPE_ethexp1 CMD_HELP_KEY_EN_ETHTYPE_ethexp1 \
				"| " \
				"ethexp2 "				CMD_HELP_KEY_EN_ETHTYPE_ethexp2 CMD_HELP_KEY_EN_ETHTYPE_ethexp2 \
				"| " \
				"ethoui "				CMD_HELP_KEY_EN_ETHTYPE_ethoui CMD_HELP_KEY_EN_ETHTYPE_ethoui \
				"| " \
				"preauth "				CMD_HELP_KEY_EN_ETHTYPE_preauth CMD_HELP_KEY_EN_ETHTYPE_preauth \
				"| " \
				"lldp " 				CMD_HELP_KEY_EN_ETHTYPE_lldp CMD_HELP_KEY_EN_ETHTYPE_lldp \
				"| " \
				"mac-sec "				CMD_HELP_KEY_EN_ETHTYPE_macsec CMD_HELP_KEY_EN_ETHTYPE_macsec \
				"| " \
				"mvrp " 				CMD_HELP_KEY_EN_ETHTYPE_mvrp CMD_HELP_KEY_EN_ETHTYPE_mvrp \
				"| " \
				"mmrp " 				CMD_HELP_KEY_EN_ETHTYPE_mmrp CMD_HELP_KEY_EN_ETHTYPE_mmrp \
				"| " \
				"frrr " 				CMD_HELP_KEY_EN_ETHTYPE_frrr CMD_HELP_KEY_EN_ETHTYPE_frrr \
				"| " \
				"<ethernet-protocol-type-hex> "  \
			"} " 


#if 0
2 IGMP Internet 组管理 
3 GGP 网关对网关 
4 IP IP 中的 IP（封装） 
5 ST 流 
6 TCP 传输控制 
7 CBT CBT 
8 EGP 外部网关协议 
9 IGP 任何专用内部网关 
（Cisco 将其用于 IGRP）
10 BBN-RCC-MON BBN RCC 监视 
11 NVP-II 网络语音协议 
12 PUP PUP 
13 ARGUS ARGUS 
14 EMCON EMCON 
15 XNET 跨网调试器 
16 CHAOS Chaos 
17 UDP 用户数据报 
18 MUX 多路复用 
19 DCN-MEAS DCN 测量子系统 
20 HMP 主机监视 
21 PRM 数据包无线测量 
22 XNS-IDP XEROX NS IDP 
23 TRUNK-1 第 1 主干 
24 TRUNK-2 第 2 主干 
25 LEAF-1 第 1 叶 
26 LEAF-2 第 2 叶 
27 RDP 可靠数据协议 
28 IRTP Internet 可靠事务 
29 ISO-TP4 ISO 传输协议第 4 类 
30 NETBLT 批量数据传输协议 
31 MFE-NSP MFE 网络服务协议 
32 MERIT-INP MERIT 节点间协议 
33 SEP 顺序交换协议 
34 3PC 第三方连接协议 
35 IDPR 域间策略路由协议
36 XTP XTP 
37 DDP 数据报传送协议 
38 IDPR-CMTP IDPR 控制消息传输协议
39 TP++ TP++ 传输协议 
40 IL IL 传输协议 
41 IPv6 Ipv6 
42 SDRP 源要求路由协议 
43 IPv6-Route IPv6 的路由标头 
44 IPv6-Frag IPv6 的片断标头 
45 IDRP 域间路由协议 
46 RSVP 保留协议 
47 GRE 通用路由封装 
48 MHRP 移动主机路由协议
49 BNA BNA 
50 ESP IPv6 的封装安全负载 
51 AH IPv6 的身份验证标头 
52 I-NLSP 集成网络层安全性 TUBA 
53 SWIPE 采用加密的 IP 
54 NARP NBMA 地址解析协议 
55 MOBILE IP 移动性 
56 TLSP 传输层安全协议 
使用 Kryptonet 密钥管理
57 SKIP SKIP 
58 IPv6-ICMP 用于 IPv6 的 ICMP 
59 IPv6-NoNxt 用于 IPv6 的无下一个标头 
60 IPv6-Opts IPv6 的目标选项 
61 任意主机内部协议 
62 CFTP CFTP 
63 任意本地网络 
64 SAT-EXPAK SATNET 与后台 EXPAK 
65 KRYPTOLAN Kryptolan 
66 RVD MIT 远程虚拟磁盘协议 
67 IPPC Internet Pluribus 数据包核心 
68 任意分布式文件系统 
69 SAT-MON SATNET 监视 
70 VISA VISA 协议 
71 IPCV Internet 数据包核心工具 
72 CPNX 计算机协议网络管理 
73 CPHB 计算机协议检测信号 
74 WSN 王安电脑网络 
75 PVP 数据包视频协议 
76 BR-SAT-MON 后台 SATNET 监视 
77 SUN-ND SUN ND PROTOCOL-Temporary 
78 WB-MON WIDEBAND 监视 
79 WB-EXPAK WIDEBAND EXPAK 
80 ISO-IP ISO Internet 协议 
81 VMTP VMTP 
82 SECURE-VMTP SECURE-VMTP 
83 VINES VINES 
84 TTP TTP 
85 NSFNET-IGP NSFNET-IGP 
86 DGP 异类网关协议 
87 TCF TCF 
88 EIGRP EIGRP 
89 OSPFIGP OSPFIGP 
90 Sprite-RPC Sprite RPC 协议 
91 LARP 轨迹地址解析协议 
92 MTP 多播传输协议 
93 AX.25 AX.25 帧 
94 IPIP IP 中的 IP 封装协议 
95 MICP 移动互联控制协议 
96 SCC-SP 信号通讯安全协议 
97 ETHERIP IP 中的以太网封装 
98 ENCAP 封装标头 
99 任意专用加密方案 
100 GMTP GMTP 
101 IFMP Ipsilon 流量管理协议 
102 PNNI IP 上的 PNNI 
103 PIM 独立于协议的多播 
104 ARIS ARIS 
105 SCPS SCPS 
106 QNX QNX 
107 A/N 活动网络 
108 IPComp IP 负载压缩协议 
109 SNP Sitara 网络协议 
110 Compaq-Peer Compaq 对等协议 
111 IPX-in-IP IP 中的 IPX 
112 VRRP 虚拟路由器冗余协议 
113 PGM PGM 可靠传输协议 
114 任意 0 跳协议 
115 L2TP 第二层隧道协议 
116 DDX D-II 数据交换 (DDX) 
117 IATP 交互式代理传输协议 
118 STP 计划传输协议 
119 SRP SpectraLink 无线协议 
120 UTI UTI 
121 SMP 简单邮件协议 
122 SM SM 
123 PTP 性能透明协议 
124 ISIS over IPv4 
125 FIRE 
126 CRTP Combat 无线传输协议 
127 CRUDP Combat 无线用户数据报 
128 SSCOPMCE 
129 IPLT 
130 SPS 安全数据包防护 
131 PIPE IP 中的专用 IP 封装 
132 SCTP 流控制传输协议 
133 FC 光纤通道 
134-254 未分配 
255 保留
#endif

#define CMD_HELP_KEY_EN_PROTOTYPE_EIGRP 	"#EIGRP (Enhanced Interior Gateway Routing Protocol) (type 88).#"
#define CMD_HELP_KEY_EN_PROTOTYPE_GRE 		"#GRE (Generic Routing Encapsulation) protocol (type 47).#"
#define CMD_HELP_KEY_EN_PROTOTYPE_IPINIP 	"#IPINIP protocol (type 4).#"
#define CMD_HELP_KEY_EN_PROTOTYPE_IGMP 		"#IGMP (Internet Group Management Protocol) (type 2).#"
#define CMD_HELP_KEY_EN_PROTOTYPE_OSPF 		"#OSPF (Open Shortest Path First) protocol (type 89).#"
#define CMD_HELP_KEY_EN_PROTOTYPE_ICMP 		"#ICMP (Internet Control Message Protocol) (type 1).#"
#define CMD_HELP_KEY_EN_PROTOTYPE_UDP 		"#UDP (User Datagram Protocol) (type 17).#"
#define CMD_HELP_KEY_EN_PROTOTYPE_TCP 		"#TCP (Transmission Control Protocol) (type 6).#"

#define STR_CMD_RULE_IP_PRO \
			"{ " \
				"eigrp "				CMD_HELP_KEY_EN_PROTOTYPE_EIGRP CMD_HELP_KEY_EN_PROTOTYPE_EIGRP \
				"| " \
				"gre "					CMD_HELP_KEY_EN_PROTOTYPE_GRE CMD_HELP_KEY_EN_PROTOTYPE_GRE \
				"| " \
				"ipinip "				CMD_HELP_KEY_EN_PROTOTYPE_IPINIP CMD_HELP_KEY_EN_PROTOTYPE_IPINIP \
				"| " \
				"igmp " 				CMD_HELP_KEY_EN_PROTOTYPE_IGMP CMD_HELP_KEY_EN_PROTOTYPE_IGMP \
				"| " \
				"ospf " 				CMD_HELP_KEY_EN_PROTOTYPE_OSPF CMD_HELP_KEY_EN_PROTOTYPE_OSPF \
				"| " \
				"icmp " 				CMD_HELP_KEY_EN_PROTOTYPE_ICMP CMD_HELP_KEY_EN_PROTOTYPE_ICMP \
				"| " \
				"udp "					CMD_HELP_KEY_EN_PROTOTYPE_UDP CMD_HELP_KEY_EN_PROTOTYPE_UDP \
				"| " \
				"tcp "					CMD_HELP_KEY_EN_PROTOTYPE_TCP CMD_HELP_KEY_EN_PROTOTYPE_TCP \
				"| " \
				"<ip-protocol-type> " \
			"} "



#define CMD_HELP_KEY_EN_ETHTYPE_TYPE "#Ethernet type.#"
#define CMD_HELP_KEY_CN_ETHTYPE_TYPE "#以太网类型.#"
#define CMD_HELP_KEY_EN_PROTOTYPE_TYPE "#IP protocol type.#"
#define CMD_HELP_KEY_CN_PROTOTYPE_TYPE "#IP 协议类型.#"
				
#define CMD_HELP_KEY_EN_DSCP "#DSCP.#"
#define CMD_HELP_KEY_CN_DSCP "#DSCP.#"
#define CMD_HELP_ARG_EN_DSCP "#FORMAT: Decimal. Range: [0-63].#"
				
#define CMD_HELP_ARG_EN_MACWITHMASK	"#MAC with mask, FORMAT:XXXX.XXXX.XXXX:XXXX.XXXX.XXXX.#"
#define CMD_HELP_ARG_EN_IPWITHMASK 	"#IP with mask, FORMAT:DDD.DDD.DDD.DDD:DDD.DDD.DDD.DDD.#"


////////////////////////////////////////////////////////////////////////////////
//																			  //
//					结 构 体 、联 合 体、枚 举 定 义				  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

typedef enum etag_vlan_map_type_type_t
{
	E_VLAN_MAP_TYPE_BIT,
	E_VLAN_MAP_TYPE_BYTE,
	E_VLAN_MAP_TYPE_MAX
} vlan_map_type_e;

#define PRINT_BC_RET(sid, ret)\
	do\
	{\
		if (ret != BC_ERR_OK)\
		{\
			CLI_API_Printf(sid, "Fail.%s!\r\n", bc_msg_err_get(ret, (bc_cli_get_lan() == CLI_LAN_CN ? BC_LAN_CHINESE_E : BC_LAN_ENGLISH_E)));\
		}\
	} while (0)


////////////////////////////////////////////////////////////////////////////////
//																			  //
//						外 部 变 量、 函 数 声 明					  //
//																			  //
////////////////////////////////////////////////////////////////////////////////
extern const char *bc_cli_menu[CMD_MID_MAXNUM][CMD_ML_MAXNUM];




#endif /* __IN_BC_CLI_BASE_H__ */

