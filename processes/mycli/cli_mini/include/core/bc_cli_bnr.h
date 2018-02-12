/*******************************************************************************
 * Copyright(C) 2011, Kingtype Networks Corporation. All rights reserved.
 *
 * This is unpublished proprietary source code of Kingtype Networks Corporation.
 *
 * The copyright notice above does not evidence any actual or intended
 *	publication of such source code.
*******************************************************************************/
/*==============================================================================
 * MODULE NAME: Banner
 * FILE NAME  : bc_cli_bnr.h
 * VERSION    : 1.0.0
 * DESCRIPTION: Manage the greeting message and command prompt
 * NOTES:
 *
 * HISTORY:
 * -----------------------------------------------------------------------------
 * Version 1.0
 * [NEW FEATURE]
 * <DESCRIPTION>
 *============================================================================*/

#ifndef  __BC_CLI_BNR_H__
#define  __BC_CLI_BNR_H__

#include "bc_cli_type.h"
#include "bc_cli_kernel_cfg.h"

/*-----------------------------------------------------------------------
 * Macro
 *-----------------------------------------------------------------------
 */
#define BANNER_MAX_COLUMN 		80  /* BANNER_MAX_COLUMN should be the same as MAX_SCREEN_WIDTH */
#define BANNER_MAX_SCREEN_LINE 	12

/* modified by wangbin to support enhance greeting message */
#if ENHANCE_GREETING_MESSAGE
#define BANNER_MAX_LINE 		24
#else
#define BANNER_MAX_LINE 		6
#endif



/*-----------------------------------------------------------------------
 * Definiton
 *-----------------------------------------------------------------------
 */

typedef enum
{
    USR_BANN_STATE_DISABLED,
    USR_BANN_STATE_ENABLED
} BANN_STATE_T;

typedef enum
{
    INIT_CONFIG,
    CONFIG_CLEAR_OLD,
    CONFIG_RUN,
    USER_COMMAND
} BANNER_CONFIG_STATE;

typedef struct _BANNER_PROMPT_T
{
    BOOL_T					bUserName;
    I8_T					string[32 + 1];//BNR_CPU_NAME_MAX_LEN
} BANNER_PROMPT_T;

typedef struct _BANNER_PRMPT_BANNER_T
{
    I8_T					greeting_msg[BANNER_MAX_LINE * BANNER_MAX_COLUMN + 1]; /* ¿ª»úÎÊºòÓï */
    BANN_STATE_T			bUseGreetMsg;
    BANN_STATE_T			bUseCmdPrompt;
    BANNER_PROMPT_T			cmd_prompt;
} BANNER_PRMPT_BANNER_T;

typedef struct _banner_command
{
    BANNER_CONFIG_STATE		state;
    UI32_T					currLINE;
} BANNER_COMMAND_T;



#if 1//USER_PROMPT_INCLUDED
/*------------------------------------------------------------------------
 * Function    : CLI_BNR_Get_Prompt
 * Description : Display the editor prompt
 * Parameters  :
 *     Input   : const int   sessionID,
 *               I8_T        *prompt
 *     Output  : new prompt setting in user mode
 * Returns     : TRUE
 *               FALSE   not in user mode
 * Writer      : wangbin
 *------------------------------------------------------------------------
*/
BOOL_T CLI_BNR_Get_Prompt(IN const int sessionID, OUT I8_T *prompt, IN I32_T prompt_len);

#endif

#if 1//USER_BANNER_INCLUDED

/*------------------------------------------------------------------------
 * Function    : CLI_BNR_Update_Default_Bnr
 * Description : Get the default banner string
 * Parameters  :
 *     Input   : BANNER_PRMPT_BANNER_T    *bnr_default
 *     Output  : BANNER_PRMPT_BANNER_T    *bnr_default
 * Returns     : TRUE
 * Writer      : wangbin
 *------------------------------------------------------------------------
*/
BOOL_T CLI_BNR_Update_To_Default_Bnr(OUT BANNER_PRMPT_BANNER_T    *bnr_default);

/*------------------------------------------------------------------------
 * Function    : CLI_BNR_Update_Bnr_oper_to_Default
 * Description : set to the default banner string
 * Parameters  :
 *       Input :
 *      Output :
 * Returns     :
 * Writer      : wangbin
 *------------------------------------------------------------------------
*/
void  CLI_BNR_Update_Bnr_oper_to_Default(void);
#endif

/*------------------------------------------------------------------------
 * Function    : CLI_BNR_Get_PromptBannerInfo
 * Description : Get the editor banner and prompt information
 * Parameters  :
 *     Input   : BANNER_PRMPT_BANNER_T 		*usr_banner_prompt_info
 *     Output  : BANNER_PRMPT_BANNER_T 		*usr_banner_prompt_info
 * Returns     : TRUE
 *               FALSE
 * Writer      : wangbin
 *------------------------------------------------------------------------
*/
BOOL_T CLI_BNR_Get_PromptBannerInfo(OUT BANNER_PRMPT_BANNER_T *usr_banner_prompt_info);

/*------------------------------------------------------------------------
 * Function    : CLI_BNR_Update_PromptBannerInfo
 * Description : Update the editor banner and prompt information
 * Parameters  :
 *     Input   : BANNER_PRMPT_BANNER_T usr_banner_prompt_info
 *     Output  : NA
 * Returns     : TRUE
 *               FALSE
 * Writer      : wangbin
 *------------------------------------------------------------------------
*/
BOOL_T CLI_BNR_Update_PromptBannerInfo(IN BANNER_PRMPT_BANNER_T *usr_banner_prompt_info);

/*------------------------------------------------------------------------
 * Function    : CLI_BNR_Get_GreetingMsg
 * Description : Get greeting message
 * Parameters  :
 *     Input   : UI8_T 	*msg_buf
 *               I32_T 	msg_buf_len
 *     Output  : I32_T 	*used_len
 * Returns     : TRUE
 *               FALSE
 * Writer      : wangbin
 *------------------------------------------------------------------------
*/
BOOL_T CLI_BNR_Get_GreetingMsg(IN UI8_T *msg_buf ,IN I32_T msg_buf_len ,OUT I32_T *used_len);

/*------------------------------------------------------------------------
 * Function    : CLI_BNR_Get_Banner_Oper
 * Description : Get the editor banner operation information
 * Parameters  :
 *     Input   : BANNER_COMMAND_T 		*pcli_banner_oper
 *     Output  : BANNER_COMMAND_T 		*pcli_banner_oper
 * Returns     : TRUE
 *               FALSE
 * Writer      : wangbin
 *------------------------------------------------------------------------
*/
BOOL_T CLI_BNR_Get_Banner_Oper(BANNER_COMMAND_T *pcli_banner_oper);

/*------------------------------------------------------------------------
 * Function    : CLI_BNR_Set_Banner_Oper
 * Description : Set the editor banner operation information
 * Parameters  :
 *     Input   : BANNER_COMMAND_T 	cli_banner_oper
 *     Output  : NA
 * Returns     : TRUE
 *               FALSE
 * Writer      : wangbin
 *------------------------------------------------------------------------
*/
BOOL_T CLI_BNR_Set_Banner_Oper(BANNER_COMMAND_T cli_banner_oper);

/*------------------------------------------------------------------------
 * Function    : CLI_BNR_Prepare_Banner_Oper_Before_Running_Config_Script
 * Description : Set the editor banner operation information
 * Parameters  :
 *     Input   : NA
 *     Output  : NA
 * Returns     : TRUE
 *               FALSE
 * Writer      : wangbin
 * ATTENTION   : If you want to download config to run or using flash config 
 *               to run, you should call this routine, else you can not exit 
 *               banner config mode
 *------------------------------------------------------------------------
*/
BOOL_T CLI_BNR_Prepare_Banner_Oper_Before_Running_Config_Script(void);

/*------------------------------------------------------------------------
 * Function    : bc_cli_bnr_init
 * Description : Init the greeting message and command prompt
 * Parameters  :
 *     Input   : NA
 *     Output  : NA
 * Returns     : 
 * Writer      : wangbin
 * ATTENTION   :   
 *------------------------------------------------------------------------
*/
void bc_cli_bnr_init(void);



#endif /* __BC_CLI_BNR_H__ */

