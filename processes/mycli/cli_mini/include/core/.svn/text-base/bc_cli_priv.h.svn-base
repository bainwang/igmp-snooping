/*******************************************************************************
 * Copyright(C) 2008, Kingtype Networks Corporation. All rights reserved.
 *
 * This is unpublished proprietary source code of Kingtype Networks Corporation.
 *
 * The copyright notice above does not evidence any actual or intended
 *	publication of such source code.
*******************************************************************************/
/*==============================================================================
 * MODULE NAME: Kingtype CLI, bc_cli
 * FILE NAME  : bc_cli_priv.h
 * VERSION    : 1.0.0
 * DESCRIPTION:
 * NOTES:
 *
 * HISTORY:
 * -----------------------------------------------------------------------------
 * Version 1.0 -  2008-Nov-28 by wangbin
 * [NEW FEATURE]
 * <DESCRIPTION> Create
 *============================================================================*/

#ifndef __BC_CLI_PRIV_H__
#define __BC_CLI_PRIV_H__

#include "utili_rbt.h"
#include "bc_cli_paratype.h"



#ifdef CLI_BRACE_AS_OPTIONAL
#define CLI_DELIM_OPTIONAL_START 	'{'
#define CLI_DELIM_OPTIONAL_END 	'}'
#define CLI_DELIM_REQUIRED_START 	'['
#define CLI_DELIM_REQUIRED_END 	']'
#else
#define CLI_DELIM_OPTIONAL_START 	'['
#define CLI_DELIM_OPTIONAL_END 	']'
#define CLI_DELIM_REQUIRED_START 	'{'
#define CLI_DELIM_REQUIRED_END 	'}'
#endif

/* max path word number */
#define CLI_MAX_CMD_WORD 			32
#define CLI_MAX_CMD_PARA_LEN 		500

/* the ambiguous node */
#define CLI_AMBIGUOUS_NODE 		((CLI_CMD_NODE_T *)0xFFFFFFFFu)

/* the root path define */
#define CLI_ROOT_PATH				NULL
/* the not exist path define */
#define CLI_NULL_PATH				0xFFFFFFFF

/* CLI node type, it is the DB search aux keyword for different with the command, bit define for match */
typedef enum
{
	CLI_TYPE_CMD = 0x1, /* bit0: the node is a command node, like 'port' in 'config port' */
	CLI_TYPE_VIEW = 0x2 /* bit2: the node is a view node,	like 'vlan' in '/vlan/name' */
} CLI_NODE_TYPE_T;

#define CLI_CORE_HELPLIST_MAX 1000
typedef struct
{
	I8_T 		name_buf[CLI_CORE_HELPLIST_MAX * 30];
	I8_T 		*name[CLI_CORE_HELPLIST_MAX]; /* note: name point to name_buf, so memcpy the struct will be error */
	const I8_T 	*help[CLI_CORE_HELPLIST_MAX];
	BOOL_T 		nexthelp; /* TRUE: get word list after user command; FALSE: get wordlist for last word */
	BOOL_T 		local_help; /* TRUE: get local help; FALSE: get English help */
	I32_T 		name_buf_used;
	I32_T 		max_name_len; /* the max name length in *name[] array */
	I32_T 		para_count; /* the <parameter> number which need to parse */
	I32_T 		count; /* count of the help list */
	I32_T 		error_pos; /* error pos of the cmd para */
} CLI_PRIV_HELPLIST_T;

typedef struct tagCLI_PRIV_PARA_SYN_NODE
{
	UI32_T 		type;  // MULTIPLE, PORT, PORT-LIST ...
	I32_T 		lparam; /* for {}(x), lparam = x; for keyword(x), lparam = x; */
				  /* for PARA(x-y), lparam = x, rparam = y */
				  /* for wellknown PARA, (lparam, rparam) get from that type */
	I32_T 		rparam;
	I32_T 		match_count;
	struct tagCLI_PRIV_PARA_SYN_NODE 	*parent;	/* parent for the node */
	struct tagCLI_PRIV_PARA_SYN_NODE 	*sibling;	/* sibling for the same child */
	struct tagCLI_PRIV_PARA_SYN_NODE 	*child;	/* generate a array => child[num_of_child] */
#ifdef CLI_WORD_WITH_HELP
 // Word help in CLI is registered as /*English-help*//*Local-help*/
 // Ex: /PATH/OF/THE/COMMAND/COMMAND NAME PARA1 /*English-help-for-PARA1*//*Local-help-for-PARA1*/
	I8_T 		*help_en; // help in English
	I8_T 		*help_local; // help in local language
#endif
	I8_T 		*name; // name of the node
	UI32_T 		flag; //for other used(such as for required, set the repeat flag that means the repeated time can be increased)
} CLI_PRIV_PARA_SYN_NODE_T;

#define CLI_PARA_REQUIRE_REPEAT_FLAG	0x00000001 //set the repeat flag that means the repeated time can be increased

/* CLI path node struct */
typedef struct
{
	/* second search keyword */
	UI8_T 			type;                 	/* should be  CLI_TYPE_VIEW, CLI_TYPE_PART, CLI_TYPE_CMD */
	UI8_T 			level;                	/* 0-15,128. it is the path access level, user-level >= this level, can tab or execute this command */
	UI8_T 			cmd_level;				/* it is the command access level, only the command node used this level for checking */
	UI8_T 			register_cmd_level;		/* used to store original registered level, only the command node recored it */
	//CLI_VERSION_T 	version;     			/* version */
	utili_rbt_t 	sub_tree;         		/* child's tree */
	CLI_CMD_FUNC_T callback;   			/* the command callback */
	void 			*cookie;               	/* user data when register command pass in */
	I8_T 			*help_en;              	/* English help */
	I8_T 			*help_local;           	/* local help */
	BOOL_T 			help_alloc_flag;		/* help message is allocated from CLI buffer or point to constant string */
	CLI_PRIV_PARA_SYN_NODE_T *para; 		/* the command parameter */
	/* first search keyword */
	I8_T 			*name;                 	/* the view/cmd/part name, dynamic length */
} CLI_CMD_NODE_T;

#define CLI_PRIV_MAX_USRCMD_WORD 300 /* max words in a user command line */
typedef struct
{
	const I8_T 	*usrcmd;
	const I8_T 	*word[CLI_PRIV_MAX_USRCMD_WORD]; /* start position of the word */
	I32_T 		len[CLI_PRIV_MAX_USRCMD_WORD]; /* length of the word */
	I32_T 		count; /* count of the effective word */
	I32_T 		index; /* index of the word current parsed */
} CLI_PRIV_USRCMD_WORDLIST_T;

#define CLI_PRIV_AMBIGUOUS 1



#endif /* __BC_CLI_PRIV_H__ */
