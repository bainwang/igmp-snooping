/*==============================================================================
 * FILE NAME  : bc_cli_paratype.h
 * VERSION    : 1.0.0
 * DESCRIPTION:
 * NOTES:
 *
 * HISTORY:
 * -----------------------------------------------------------------------------
 * Version 1.0 -- 2009-Mar-18 by bain.wang@outlook.com
 * [NEW FEATURE]
 * <DESCRIPTION> Create
 *============================================================================*/

#ifndef __INC_BC_CLI_PARATYPE_H__
#define __INC_BC_CLI_PARATYPE_H__

#include "bc_cli_type.h"
#include "bc_cli_kernel_cfg.h"



typedef enum
{ /* CLI_TYPES_* */
	CLI_TYPES_REQUIRED = 1,
	CLI_TYPES_OPTIONAL = 2,
	CLI_TYPES_ELEMENT  = 3, /* |(only use in lexical of parameter) */
	CLI_TYPES_ENUM = 16,
	CLI_TYPES_KEYWORD, /* previous are reserved types */
	CLI_TYPES_STRING, /* Ex: "string with spaces" or string-without-space */
	CLI_TYPES_STRING_WITHOUT_WHITESPACE, /* string-without-space */
	CLI_TYPES_NAME, /* start with [a-zA-Z][a-zA-Z0-9!#$%&'()+,.=@[]^_`{}~/\:<>\*\-]* */
	CLI_TYPES_SENTENCE, /* add for compatibility with CLI G1, just begin with current pointer and end with command end */
	CLI_TYPES_ENUMLIST_UI32, /* Ex: bps <BPS> */
	CLI_TYPES_MONTH, /* add for compatibility with CLI G1 */
	CLI_TYPES_WEEKDAY, /* add for compatibility with CLI G1 */
	CLI_TYPES_WEEK, /* add for compatibility with CLI G1 */
	CLI_TYPES_IPADDR, /* Ex: 192.168.1.200 */
	CLI_TYPES_IPNETADDR, /* Ex: 192.168.1.200/16 */
	CLI_TYPES_IPMULTICASTADDR, /* multicast ip address add for compatibility with CLI G1 */
	CLI_TYPES_IPMULTICASTADDRCHAIN, /*multicast ip address chain add for compatibility with CLI G1 Ex: 192.168.1.200-192.168.1.220,192.168.236 */
	CLI_TYPES_STANDALONEPORTLIST, /* Ex: 1-6,10,12 */
	CLI_TYPES_FRAMEPORTNUM, /* Ex: S1/10 or s1/10 or P2/5 or p2/5 ... */
	CLI_TYPES_PONPORTNUM, /* Ex: P2/6 */
	CLI_TYPES_SNIPORTNUM, /* Ex: S1/8 */
	CLI_TYPES_UI32, /* Ex: 200 */
	CLI_TYPES_I32, /* Signed int */
	CLI_TYPES_UI32CHAIN, /* store the UI32 range in chain mode just like ints in CLI G1 */
	CLI_TYPES_INTLIST, /* 0-5,9-20 */
	CLI_TYPES_VLANLIST, /* Ex: 1-10,15,18-20 */
	CLI_TYPES_VLANLIST_NAME, /* Ex: 1-10,vlan1,vlan2,20-30 */
	CLI_TYPES_MACADDR, /* Ex:ff-ff-ff-ff-ff-ff */
	CLI_TYPES_MMACADDR, /* Ex: 01-xx-xx-xx-xx-xx */
	CLI_TYPES_UMACADDR, /* Ex: first value can not be 01 */
	CLI_TYPES_SHORTTIME, /* hh:mm */
	CLI_TYPES_LONGTIME,  /* hh:mm:ss */
	CLI_TYPES_DATE, /* dd-mm-yyyy */
	CLI_TYPES_DATECN, /* yyyy-mm-dd */
	CLI_TYPES_HEX,  /* 0xaabbcc */
	CLI_TYPES_BINARY, /* 0b01000 */
	CLI_TYPES_OID, /* string */
	CLI_TYPES_FLOAT,
	CLI_TYPES_ONUID, /* Ex: 1/10:3 */
	CLI_TYPES_STORM_CONTROL, /* 可以多选的枚举字符，如风暴抑制 Ex: "u" or "b" or "m" or "u,m" or "u,m,b" */

	CLI_TYPES_MAX
} CLI_PRIMITIVE_SYNTAX_T;



#if 1 /* cli1 */

typedef struct _cli2_valuearray
{
	UI32_T	type; /* type of the word in parameter part */
	UI32_T	count; /* the range number in valueBegin buffer  */
	/* buffer for store multiple ranges such as:
	 * (int list) 1,4,7-10 store as 1 1 4 4 7 10 ; valueBegin -> (I32_T *)&valueBegin
	 */
	I8_T		valueBegin;
} CLI_VALUEARRAY_T;

#endif

#define CLI_TYPE_VLAN_NAME_MAX_LEN 	32
#define CLI_TYPES_IPV6_MAX_PART 		8
#define CLI_TYPES_IPV4_MAX_PART 		4


typedef UI8_T CLI_TYPE_VLANLIST_T[(MIB_CST_MAX_VLAN_ID + 7) / 8];

typedef struct 
{
	I32_T 					type; /* 0 -- vlanlist, 1 -- vlan name */
	CLI_TYPE_VLANLIST_T 	vlanlist;
	I8_T 					vlanname[CLI_TYPE_VLAN_NAME_MAX_LEN];
} CLI_TYPE_VLANLIST_NAME_T;

typedef struct 
{ /* range as [(UI16_T)min, (UI16_T)max] */
	UI16_T min;
	UI16_T max;
} CLI_TYPE_SRANGE_T;

typedef struct 
{ /* range as [(UI32_T)min, (UI32_T)max] */
	UI32_T min;
	UI32_T max;
} CLI_TYPE_LRANGE_T;

typedef struct 
{
	UI8_T reserved;
	UI8_T boxid;
	UI8_T moduleid;
	UI8_T portid;
} CLI_TYPE_INTERFACE_T; /* boxid:moduleid:portid */

typedef struct 
{
	UI8_T hour;  /* hh:mm:ss (00:00:00 - 23:59:59) */
	UI8_T minute;
	UI8_T second;
	UI8_T use12; /* reserved */
} CLI_TYPE_TIME_T;

typedef struct 
{
	I16_T year; /* 1000-9999 */
	UI8_T month; /* 1-12 */
	UI8_T day; /* 1-31 */
} CLI_TYPE_DATE_T;

typedef struct 
{
	UI32_T ipaddr;
	UI32_T ipmask;
} CLI_TYPE_IPNETADDR_T;

#define CLI_TYPES_OID_MIN 0
#define CLI_TYPES_OID_MAX 0xffffffff
#define CLI_TYPES_OID_COUNT_MAX 32

typedef struct 
{
	UI32_T len; /* how many value used */
	UI32_T value[CLI_TYPES_OID_COUNT_MAX]; /* value of the oid */
} CLI_OID_T;



/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 CLI_CMD_FUNC_T
 *
 * DESCRIPTION:
 *	 Type of the callback function for CLI syntax command register.
 *	 These callback functions will be called when CLI core execute a correct
 *	 user command.
 * INPUT:
 *	 session_id -- Session ID created by bc_cli_session_create
 *	 user_data -- Other data was sended to this callback function from CLI
 *		kernel, it was same as the user_data in bc_cli_reg_cmd
 *	 cli_value -- CLI value list generated by CLI kernel after execute a user
 *		command. It was a list of all parameters from left to right in CLI
 *		user command. The value in cli_value_t node is decided by the type
 *		in it.
 ****************** type list in cli_value_t **********************************
 *-------- TYPE NAME -----------------------+------ value type ------------------------------------------------
 *											|
 *	 CLI_TYPES_ENUM							| enum_name = cli_value->name;
 *											| enum_value = *(UI32_T *)value;
 *	 CLI_TYPES_KEYWORD 						| keyword = cli_value->name;
 *											| cli_value->value = NULL;
 *	 CLI_TYPES_STRING						| str = (I8_T *)cli_value->value <NULL terminated>
 *   CLI_TYPES_STRING_WITHOUT_WHITESPACE 	| str = (I8_T *)cli_value->value <NULL terminated>
 *   CLI_TYPES_NAME            				| str = (I8_T *)cli_value->value <NULL terminated>
 *	 CLI_TYPES_ENUMLIST_UI32				| i = *(UI32_T *)cli_value->value;
 *	 CLI_TYPES_ENUMLIST_STRING 				| str = (I8_T *)cli_value->value;
 *	 CLI_TYPES_IPADDR						| ipaddr = *(UI32_T *)cli_value->value;
 *   CLI_SYNTAX_IPV6ADDR       				| LA3_IP6ADDR *ipv6addr = cli_value->value;
 *	 CLI_TYPES_FRAMEPORTNUM					| port_kt = *(cli_pid_t *)cli_value->value;
 *   CLI_TYPES_PONPORTNUM                   | pon_port = *(cli_pid_t *)cli_value->value;
 *   CLI_TYPES_SNIPORTNUM                   | sni_port = *(cli_pid_t *)cli_value->value;
 *	 CLI_TYPES_STACKINGPORTLIST				| portlist = *(ST_PORTLIST_T *)cli_value->value;
 *   CLI_TYPES_ZTE_PORT_ID     				| portlist = *(CLI_API_ZTE_PORTLIST_T *)cli_value->value;
 *   CLI_TYPES_ZTE_PORT_LIST   				| portlist = *(CLI_API_ZTE_PORTLIST_T *)cli_value->value;
 *                              			|     use CLI_API_Check_ZTE_Port to check all port in <portlist>
 *                              			|     if it has set.
 *	 CLI_TYPES_UI32 		    			| i = *(UI32_T *)cli_value->value;
 *	 CLI_TYPES_I32             				| i = *(I32_T *)cli_value->value;
 *	 CLI_TYPES_INTLIST		    			| intlist = *(CLI_API_INTLIST_T *)cli_value->value;
 *	 CLI_TYPES_VLANLIST						| vlanlist = *(VID_LIST_T *)cli_value->value;
 *	 CLI_TYPES_VLANLIST_NAME   				| vlanlist = *(CLI_TYPE_VLANLIST_NAME_T *)cli_value->value;
 *	 CLI_TYPES_MACADDR 						| mac[6] = (I8_T *)cli_value->value;
 *	 CLI_TYPES_SHORTTIME					| shorttime = (CLI_TYPE_TIME_T *)cli_value->value;
 *	 CLI_TYPES_LONGTIME						| longtime = (CLI_TYPE_TIME_T *)cli_value->value;
 *	 CLI_TYPES_DATE							| date = (CLI_TYPE_DATE_T *)cli_value->value;
 *	 CLI_TYPES_DATECN						| datecn = (CLI_TYPE_DATE_T *)cli_value->value;
 *	 CLI_TYPES_HEX 							| hex = (UI32_T *)cli_value->value;
 *	 CLI_TYPES_BINARY						| binary = (UI32_T *)cli_value->value;
 *	 CLI_TYPES_OID 							| oid = (CLI_OID_T *)cli_value->value;
 *	 CLI_TYPES_ONUID						| onuid = *(cli_onuid_t *)cli_value->value;
 *	 CLI_TYPES_STORM_CONTROL				| storm_mode = *(cli_sc_e *)cli_value->value;
 *											|
 ****************************************************************************************************************
 *
 * OUTPUT:
 *	 NA
 *
 * RETURN:
 *	 Ref. cli_cmd_ret_e
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-06 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
typedef struct stag_cli_para_value_type
{
	struct stag_cli_para_value_type 	*next; /* next parameter word */
	UI32_T 	type; /* type of the word in parameter part */
	I8_T 	*name; /* name of the word */
	void 	*value; /* decided by type */
	UI32_T 	priority; /* not used in CLI */
} cli_value_t;

typedef I32_T (*CLI_CMD_FUNC_T) (IN UI32_T sid,	IN cli_value_t *cli_para, IN void *user_data);



#endif /* __INC_BC_CLI_PARATYPE_H__ */

/* End of file */
