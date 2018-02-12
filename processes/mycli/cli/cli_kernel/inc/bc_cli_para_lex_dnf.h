/*==============================================================================
 * FILE NAME  : bc_cli_alias.c
 * VERSION    : 1.0.0
 * DESCRIPTION:
 * NOTES:
 *
 * HISTORY:
 * -----------------------------------------------------------------------------
 * Version 1.0 -- 2016-3-31 by Zeng Yi
 * [NEW FEATURE]
 * <DESCRIPTION> Create
 *============================================================================*/

#ifndef __bc_cli_para_lex_dnf_h__
#define __bc_cli_para_lex_dnf_h__

#if 1	/*bain.wang@outlook.com for cli code transplantation*/
#include "bc_common_defs.h"
#include "bc_print.h"

#include "bc_cli_type.h"
#include "bc_cli_paratype.h"
#include "bc_cli_sesn.h"
#include "bc_cli_misc.h"

extern bc_err_e bc_cli_para_lex_bnf_init(void);

typedef enum {
	BC_CLI_PARA_LEX_BNF_PORTS,
	BC_CLI_PARA_LEX_BNF_PORTS_SWITCH,
	BC_CLI_PARA_LEX_BNF_PORTS_EPON,
	BC_CLI_PARA_LEX_BNF_PORT,
	BC_CLI_PARA_LEX_BNF_PORT_SWITCH,
	BC_CLI_PARA_LEX_BNF_PORT_EPON,
	BC_CLI_PARA_LEX_BNF_VLAN,
	BC_CLI_PARA_LEX_BNF_EPON_ONUS,
	BC_CLI_PARA_LEX_BNF_EPON_ONU,
} bc_cli_para_lex_bnf_type_e;

#endif

#endif

 
