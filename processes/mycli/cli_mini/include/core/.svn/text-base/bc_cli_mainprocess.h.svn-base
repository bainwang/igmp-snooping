
#ifndef __BC_CLI_MAINPROCESS_H__
#define __BC_CLI_MAINPROCESS_H__

#include "bc_cli_type.h"



/**************************************************************************
FUNCTION NAME:
    cli_main_process

DESCRIPTION:
    Run the main process of CLI kernel for the input session.

INPUT:
    map_sessionID   : mapped session ID for other modules used
    pseudo_enable	: pseudo task enable

OUTPUT:
    NA

RETURN:
    quit reason
    the value is in bc_cli_vkey.h
    CLI_VKEY_IO_CLOSED
    CLI_VKEY_IO_TIMEOUT
    ...

NOTES:

HISTORY:

**************************************************************************/
I32_T cli_main_process(IN I32_T map_sessionID, IN BOOL_T pseudo_enable);

/*------------------------------------------------------------------------
 * Function   : cli_io_task
 * Purpose    : the main task
 * Parameters :
 *    Input   : argc = no use
 *              (argv) = no use
 *    Output  : NA
 * Returns    : NA
 *------------------------------------------------------------------------
 */
void cli_io_task(void *argv);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   cli_ker_cmd_reg
 *
 * DESCRIPTION:
 *   Init cli2 environment when switch startup, this function must called
 *   before other cli2 functions been called.
 *
 * INPUT:
 *   NA
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   0  -- init success
 *   -1 -- init failure
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2009-Mar-25 by wangbin -- Create
 *
*******************************************************************************/
I32_T               cli_ker_cmd_reg(void);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   cli_ker_init
 *
 * DESCRIPTION:
 *   Initialize CLI's OS resource and fixed database
 *
 * INPUT:
 *   None
 *
 * OUTPUT:
 *   None
 *
 * RETURN:
 *   None
 *
 * NOTES:
 *   None
 *
 * HISTORY:
 *   2010-Mar-05 by wangbin -- Create
 *
*******************************************************************************/
void                cli_ker_init(void);



#endif

