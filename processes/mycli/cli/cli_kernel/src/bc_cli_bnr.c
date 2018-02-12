
/*----------------------------------------------------------------------------
 * Module Name: bc_cli_bnr.c
 * Purposes:
 *----------------------------------------------------------------------------
 */

////////////////////////////////////////////////////////////////////////////////
// 																			  //
// 							 	头   文   件								  //
// 																			  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_cli_type.h"
#include "bc_cli_kernel_cfg.h"

#include "bc_cli_bnr.h"

#include "bc_sys_ipc_client.h"



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



////////////////////////////////////////////////////////////////////////////////
//																			  //
//							全 局 变 量 定 义								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

static BANNER_PRMPT_BANNER_T    s_banner_prompt_info;
/*+++ if switch is without EEPROM support, you should open it, by bain.wang@outlook.com */
static BANNER_COMMAND_T         s_banner_oper =
{
    INIT_CONFIG, 0
};
/*--- if switch is without EEPROM support, you should open it, by bain.wang@outlook.com */

static unsigned int l_mdl_id = BC_MODULE_CLI_KERNEL_BNR;

extern I8_T l_hostname[32];

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
 * Writer      : bain.wang@outlook.com
 *------------------------------------------------------------------------
*/
BOOL_T CLI_BNR_Get_Prompt(IN const int sessionID, OUT I8_T *prompt, IN I32_T prompt_len)
{
    NO_WARNING(sessionID);

    if (prompt_len < BNR_MAX_LEN)
    {
        return FALSE;
    }

    strcpy(prompt, s_banner_prompt_info.cmd_prompt.string);

    return TRUE;
}

#endif



/*------------------------------------------------------------------------
 * Function    : CLI_BNR_Update_Default_Bnr
 * Description : Get the default banner string
 * Parameters  :
 *     Input   : BANNER_PRMPT_BANNER_T    *bnr_default
 *     Output  : BANNER_PRMPT_BANNER_T    *bnr_default
 * Returns     : TRUE
 * Writer      : bain.wang@outlook.com
 *------------------------------------------------------------------------
*/
BOOL_T CLI_BNR_Update_To_Default_Bnr(IN BANNER_PRMPT_BANNER_T *bnr_default)
{
    char                tmp_chr[81]     = "";
    I8_T                brand[DEV_FLSH_BRAND_NAME_LEN + 1];
    I8_T                descr[32 + 1];
    I8_T                version[DEV_FLSH_VERSION_LEN + 1];
    I8_T                name[DEV_FLSH_MODULE_NAME_LEN + 1];

    I8_T                cliName[]       = "Command Line Interface";
    I8_T                firmwareBuild[] = "Firmware: Build";
    I8_T                copyRight[]     = "Copyright(C)";
    I8_T                copyRight1[]    = "2008-2108";
    I8_T                copyRight2[]    = "Organization. All rights reserved.";

    BANNER_COMMAND_T    cli_banner_oper;
    I32_T               cnt, i;
    const   I32_T       BannerMaxWidth  = BANNER_MAX_COLUMN;

	I8_T				olt_name[32] = {0}; 
	bc_sys_baseinfo_t	sys_info;

    /*
     * get device module information
     */
    memset(descr, 0x0, sizeof(descr));
    memset(brand, 0x0, sizeof(DEV_FLSH_BRAND_NAME_LEN + 1));
    memset(bnr_default->greeting_msg, 0, (BANNER_MAX_LINE * BANNER_MAX_COLUMN + 1));

	/* get frame olt device name */
	memset(&sys_info, 0x00, sizeof(sys_info));
	if (BC_ERR_OK != bc_sys_ipc_baseinfo(&sys_info))
	{
		CLI_DBG_CPL(l_mdl_id, "get system base info ipc error!\r\n");
		return FALSE;
	}
	
	strncpy(olt_name, sys_info.sys_name, 31);
	olt_name[31] = '\0';

	CLI_DBG_CPL(l_mdl_id, "olt_name: %s, strlen(olt_name) = %d\r\n", olt_name, strlen(olt_name));
	if (0 == olt_name[0])
	{
		CLI_DBG_CPL(l_mdl_id, "get olt device name is null!\r\n");
		strcpy(descr, DEV_NAME);

		memset(olt_name, 0x00, sizeof(olt_name));
		strncpy(olt_name, DEV_NAME, 31);
		olt_name[31] = '\0';

		/* set olt device name */
		if (BC_ERR_OK != bc_sys_set_sys_name_client(olt_name))
		{
			CLI_DBG_CPL(l_mdl_id, "set system name client error!\r\n");
			return FALSE;
		}
	}
	else
	{
		CLI_DBG_CPL(l_mdl_id, "get olt device name: %s, strlen(olt_name) = %d\r\n", olt_name, strlen(olt_name));
		strncpy(descr, olt_name, 32);
	}
	

#if 0
    SYS_INFO_Get_Device_Info(SYS_INFO_MODULE, name, DEV_FLSH_MODULE_NAME_LEN + 1);
    SYS_INFO_Get_Device_Info(SYS_INFO_VERSION, version, DEV_FLSH_VERSION_LEN + 1);
    SYS_INFO_Get_Device_Info(SYS_INFO_BRAND, brand, DEV_FLSH_BRAND_NAME_LEN + 1);
    SYS_INFO_Get_Device_Info(SYS_INFO_SYS_DESC, descr, DEV_FLSH_SYS_DESC_LEN + 1);
#else
	strcpy(name, "Welcome to");
	//strcpy(descr, DEV_NAME);
	strcpy(version, CLI_VERSION);
	strcpy(brand, CLI_COMPANY);
#endif

    /* 
     * some action make the first character not print,
     * so we print nouse character first
     */

    /* default user mode  */
    bnr_default->bUseGreetMsg = USR_BANN_STATE_DISABLED;

    /* #1 line */
    bnr_default->greeting_msg[0] = '\n' ;

    /* #2 line : name + space + description */
    cnt = strlen(name)
          + 1  //space between name and description
          + strlen(descr);

    if (cnt % 2 != 0)
    {
        cnt--;
    }

    for (i = 0 ; i < (BannerMaxWidth - cnt) / 2; i++)
    {
        strcat(tmp_chr, " ");
    }

    sprintf(tmp_chr, "%s%s %s", tmp_chr, name, descr);
    strcat(bnr_default->greeting_msg, tmp_chr) ;
    strcat(bnr_default->greeting_msg, "\n") ;

    /* #3 line : cliname */
    cnt = strlen(cliName);

    if (cnt % 2 != 0)
    {
        cnt--;
    }

    tmp_chr[0] = '\0';
    for (i = 0 ; i < (BannerMaxWidth - cnt) / 2; i++)
    {
        strcat(tmp_chr, " ");
    }

    sprintf(tmp_chr, "%s%s", tmp_chr, cliName);
    strcat(bnr_default->greeting_msg, "\n") ;
    strcat(bnr_default->greeting_msg, tmp_chr) ;

    /* #4 line */
    strcat(bnr_default->greeting_msg, "\n") ;

    /* #5 line : fireware build + space + version */
    cnt = strlen(firmwareBuild)
          + 1 //space between frimwareBuild and version
          + strlen(version)
          + 1;

	if (cnt % 2 != 0)
    {
        cnt--;
    }

	tmp_chr[0] = '\0';
    for (i = 0 ; i < (BannerMaxWidth - cnt) / 2; i++)
    {
        strcat(tmp_chr, " ");
    }
    sprintf(tmp_chr, "%s%s %s", tmp_chr, firmwareBuild, version);
    strcat(bnr_default->greeting_msg, tmp_chr) ;
    strcat(bnr_default->greeting_msg, "\n") ;

    /* #6 line */
    cnt = strlen(copyRight)
          + 1 					/* space bewteen copyRight and copyRight1 */
          + strlen(copyRight1)
          + 1					/* space bewteen copyRight1 and brand */
          + strlen(brand)
          + 1    				/* space bewteen brand and copyRight2 */
          + strlen(copyRight2);

	if (cnt % 2 != 0)
    {
        cnt--;
    }

	tmp_chr[0] = '\0';
    for (i = 0 ; i < (BannerMaxWidth - cnt) / 2; i++)
    {
        strcat(tmp_chr, " ");
    }

    sprintf(tmp_chr, "%s%s %s %s %s", tmp_chr, copyRight, copyRight1, brand, copyRight2);

    strcat(bnr_default->greeting_msg, tmp_chr) ;

    /*+++ if switch is without EEPROM support, you should open it, by bain.wang@outlook.com */
    cli_banner_oper.currLINE = 0;
    cli_banner_oper.state = CONFIG_CLEAR_OLD;//USER_COMMAND;
    CLI_BNR_Set_Banner_Oper(cli_banner_oper);
    /*--- if switch is without EEPROM support, you should open it, by bain.wang@outlook.com */

    strcpy(bnr_default->cmd_prompt.string, olt_name);

    return TRUE;
}



/*------------------------------------------------------------------------
 * Function    : CLI_BNR_Update_Bnr_oper_to_Default
 * Description : set to the default banner string
 * Parameters  :
 *       Input :
 *      Output :
 * Returns     :
 * Writer      : bain.wang@outlook.com
 *------------------------------------------------------------------------
*/
void CLI_BNR_Update_Bnr_oper_to_Default(void)
{
    BANNER_COMMAND_T    cli_banner_oper;

    cli_banner_oper.currLINE = 0;
    cli_banner_oper.state = CONFIG_CLEAR_OLD;//USER_COMMAND;
    CLI_BNR_Set_Banner_Oper(cli_banner_oper);
}



/*------------------------------------------------------------------------
 * Function    : CLI_BNR_Get_PromptBannerInfo
 * Description : Get the editor banner and prompt information
 * Parameters  :
 *     Input   : BANNER_PRMPT_BANNER_T 		*usr_banner_prompt_info
 *     Output  : BANNER_PRMPT_BANNER_T 		*usr_banner_prompt_info
 * Returns     : TRUE
 *               FALSE
 * Writer      : bain.wang@outlook.com
 *------------------------------------------------------------------------
*/
BOOL_T CLI_BNR_Get_PromptBannerInfo(OUT BANNER_PRMPT_BANNER_T *usr_banner_prompt_info)
{
    if (usr_banner_prompt_info != NULL)
    {
        memcpy(usr_banner_prompt_info, &s_banner_prompt_info, sizeof(BANNER_PRMPT_BANNER_T));
        return TRUE;
    }

	return FALSE;
}



/*------------------------------------------------------------------------
 * Function    : CLI_BNR_Update_PromptBannerInfo
 * Description : Update the editor banner and prompt information
 * Parameters  :
 *     Input   : BANNER_PRMPT_BANNER_T usr_banner_prompt_info
 *     Output  : NA
 * Returns     : TRUE
 *               FALSE
 * Writer      : bain.wang@outlook.com
 *------------------------------------------------------------------------
*/
BOOL_T CLI_BNR_Update_PromptBannerInfo(IN BANNER_PRMPT_BANNER_T *usr_banner_prompt_info)
{
    memcpy(&s_banner_prompt_info, usr_banner_prompt_info, sizeof(BANNER_PRMPT_BANNER_T));
    return TRUE;
}



/*------------------------------------------------------------------------
 * Function    : CLI_BNR_Get_GreetingMsg
 * Description : Get greeting message
 * Parameters  :
 *     Input   : UI8_T 	*msg_buf
 *               I32_T 	msg_buf_len
 *     Output  : I32_T 	*used_len
 * Returns     : TRUE
 *               FALSE
 * Writer      : bain.wang@outlook.com
 *------------------------------------------------------------------------
*/
BOOL_T CLI_BNR_Get_GreetingMsg(IN UI8_T *msg_buf, IN I32_T msg_buf_len, OUT I32_T *used_len)
{
    if (!msg_buf || msg_buf_len < (BANNER_MAX_LINE * BANNER_MAX_COLUMN + 1))
    {
        return FALSE ;
    }

    strcpy((I8_T *)msg_buf, s_banner_prompt_info.greeting_msg) ;
    return TRUE ;
}



/*+++ if switch is without EEPROM support, you should open it, by bain.wang@outlook.com */
/*------------------------------------------------------------------------
 * Function    : CLI_BNR_Get_Banner_Oper
 * Description : Get the editor banner operation information
 * Parameters  :
 *     Input   : BANNER_COMMAND_T 		*pcli_banner_oper
 *     Output  : BANNER_COMMAND_T 		*pcli_banner_oper
 * Returns     : TRUE
 *               FALSE
 * Writer      : bain.wang@outlook.com
 *------------------------------------------------------------------------
*/
BOOL_T CLI_BNR_Get_Banner_Oper(OUT BANNER_COMMAND_T *pcli_banner_oper)
{
    if (pcli_banner_oper)
    {
        memcpy(pcli_banner_oper, &s_banner_oper, sizeof(BANNER_COMMAND_T));
        return TRUE;
    }

    return FALSE;
}



/*------------------------------------------------------------------------
 * Function    : CLI_BNR_Set_Banner_Oper
 * Description : Set the editor banner operation information
 * Parameters  :
 *     Input   : BANNER_COMMAND_T 	cli_banner_oper
 *     Output  : NA
 * Returns     : TRUE
 *               FALSE
 * Writer      : bain.wang@outlook.com
 *------------------------------------------------------------------------
*/
BOOL_T CLI_BNR_Set_Banner_Oper(IN BANNER_COMMAND_T cli_banner_oper)
{
    memcpy(&s_banner_oper, &cli_banner_oper, sizeof(BANNER_COMMAND_T));
    return TRUE;
}



/*------------------------------------------------------------------------
 * Function    : CLI_BNR_Prepare_Banner_Oper_Before_Running_Config_Script
 * Description : Set the editor banner operation information
 * Parameters  :
 *     Input   : NA
 *     Output  : NA
 * Returns     : TRUE
 *               FALSE
 * Writer      : bain.wang@outlook.com
 * ATTENTION   : If you want to download config to run or using flash config 
 *               to run, you should call this routine, else you can not exit 
 *               banner config mode
 *------------------------------------------------------------------------
*/
BOOL_T CLI_BNR_Prepare_Banner_Oper_Before_Running_Config_Script(void)
{
    BANNER_COMMAND_T    cli_banner_oper;

    cli_banner_oper.currLINE = 0;
    cli_banner_oper.state = CONFIG_CLEAR_OLD;
    CLI_BNR_Set_Banner_Oper(cli_banner_oper);

    return TRUE;
}
/*--- if switch is without EEPROM support, you should open it, by bain.wang@outlook.com */



/*------------------------------------------------------------------------
 * Function    : bc_cli_bnr_init
 * Description : Init the greeting message and command prompt
 * Parameters  :
 *     Input   : NA
 *     Output  : NA
 * Returns     : 
 * Writer      : bain.wang@outlook.com
 * ATTENTION   :   
 *------------------------------------------------------------------------
*/
void bc_cli_bnr_init(void)
{
    CLI_BNR_Update_To_Default_Bnr(&s_banner_prompt_info);
}



