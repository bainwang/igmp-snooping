/****************************************************************************
 * Copyright (c) 2005-2010  Kingtype Corporation   All rights reserved.
 *
 * This is unpublished proprietary source code of Kingtype networks Corporation
 *
 * The copyright notice above does not evidence any actual or intended
 *  publication of such source code.
 ****************************************************************************
 */

/*----------------------------------------------------------------------------
 * MODULE NAME: Kingtype CLI, bc_cli
 * FILE NAME  : bc_cli_bnr_stk.c
 * Purposes:
 *----------------------------------------------------------------------------
 */

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              头   文   件                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

//#include <runtime/runtime.h>
#include "bc_cli_bnr_stk.h"
//#include <Stacking/st_stack.h>



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                      外 部 变 量、 函 数 引 用                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                      结   构   体   宏   定   义                           //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

//#define CLI_BNR_STK_SEND_MSG(unit, stype, ptr, size)   ST_STACK_Send_MessageAlways(unit, CFG_BNR, stype, (UI8_T *)ptr, size)



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                          全 局 变 量 定 义                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              函  数  声  明                                //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              函  数  定  义                                //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#if USER_PROMPT_INCLUDED

/*------------------------------------------------------------------------
 * Function   : void __cli2_bnr_stk_parse_cfg()
 * Purpose    :
 * Parameters :
 *    Input   :
 *    Output  :
 * Returns    :
 *------------------------------------------------------------------------
 */
static void __cli2_bnr_stk_parse_cfg
    (
    UI32_T senderBoxId,
    UI32_T sio_port,
    UI32_T subType,
    UI8_T *payloadPtr,
    UI16_T payloadLen
    )
{
    UI32_T                  myBoxId;
    BANNER_PRMPT_BANNER_T   info;

    if (sio_port)
    {
    }

    myBoxId = ST_STACK_Get_MyBoxID();
    if ((senderBoxId == myBoxId) || (ST_MASTER == ST_STACK_Get_Role()))
    {
        return;
    }

    switch (subType)
    {
    case CLI_BNR_STK_MSG_UPDATE_PROMPT_BANNER:
        if (payloadLen < sizeof(BANNER_PRMPT_BANNER_T))
        {
            memcpy(&info, payloadPtr, payloadLen);
        }
        else
        {
            memcpy(&info, payloadPtr, sizeof(BANNER_PRMPT_BANNER_T));
        }
        DBG_BNR_Printf("\n\rparse--banner update:bUseCmdPrompt=%x,bUseGreetMsg=%x,bUserName=%x",
						info.bUseCmdPrompt, info.bUseGreetMsg, info.cmd_prompt.bUserName);
        CLI_BNR_Update_PromptBannerInfo(&info);
        break;
    default:
        break;
    }

    return;
}



/*------------------------------------------------------------------------
 * Function   : static void __cli2_bnr_stk_config_unit(UI8_T unit_id)
 * Purpose    :
 * Parameters :
 *    Input   :
 *    Output  :
 * Returns    :
 *------------------------------------------------------------------------
 */
static void __cli2_bnr_stk_config_unit
    (
    UI8_T unit_id
    )
{
    BANNER_PRMPT_BANNER_T   tmp_bnr;

	/* configure new unit */
    if (ST_MASTER != ST_STACK_Get_Role())
    {
        return;
    }

    if (unit_id == ST_STACK_Get_MyBoxID())
    {
        return;
    }

    if (CLI_BNR_Get_PromptBannerInfo(&tmp_bnr))
    {
        CLI_BNR_STK_SEND_MSG(unit_id, CLI_BNR_STK_MSG_UPDATE_PROMPT_BANNER, &tmp_bnr, sizeof(BANNER_PRMPT_BANNER_T));
    }

    return;
}



/*-----------------------------------------------------------------------------
 * Function   : void CLI_BNR_STK_Send_UpdatePromptBannerMSG(BANNER_PRMPT_BANNER_T *info)
 * Purpose    : Send update prompt or banner system message
 * Parameters :
 *    Input   : msg info
 *    Output  : None
 * Returns    : None
 * Note       :
 * Programmer :
 *-----------------------------------------------------------------------------
 */
void CLI_BNR_STK_Send_UpdatePromptBannerMSG
    (
    BANNER_PRMPT_BANNER_T *info
    )
{
    if (ST_MASTER == ST_STACK_Get_Role() || ST_ISOLATION == ST_STACK_Get_Role())
    {
        DBG_BNR_Printf("\n CLI_BNR_STK_NotifyOtherDevice--1");
        CLI_BNR_STK_SEND_MSG(0, CLI_BNR_STK_MSG_UPDATE_PROMPT_BANNER, info, sizeof(BANNER_PRMPT_BANNER_T));
    }

    return;
}



/*-----------------------------------------------------------------------------
 * Function   : void CLI_BNR_STK_ResetDefault(void)
 * Purpose    : Command reset config or reset system using
 * Parameters :
 *    Input   : None
 *    Output  : None
 * Returns    : None
 * Note       :
 * Programmer :
 *-----------------------------------------------------------------------------
 */
void CLI_BNR_STK_ResetDefault
    (
    void
    )
{
    BANNER_PRMPT_BANNER_T   cur_bnr_msg;

    DBG_BNR_Printf("\n\rCLI_BNR_STK_reset callback");
    memset(&cur_bnr_msg, 0x0, sizeof(BANNER_PRMPT_BANNER_T));
    cur_bnr_msg.bUseCmdPrompt = USR_BANN_STATE_DISABLED;
    cur_bnr_msg.bUseGreetMsg = USR_BANN_STATE_DISABLED;
    CLI_BNR_Update_To_Default_Bnr(&cur_bnr_msg);
    CLI_BNR_Update_PromptBannerInfo(&cur_bnr_msg);

    //send msg to other device
    CLI_BNR_STK_Send_UpdatePromptBannerMSG(&cur_bnr_msg);
    return;
}



/*------------------------------------------------------------------------
 * Function   : void CLI_BNR_STK_Init_Stack()
 * Purpose    :
 * Parameters :
 *    Input   :
 *    Output  :
 * Returns    :
 *------------------------------------------------------------------------
 */
void CLI_BNR_STK_Init_Stack
    (
    void
    )
{
    ST_CALLBACK_FUN_T   callback_t;

    /*init callback function*/
    MEMSET(&callback_t, 0x00, sizeof(ST_CALLBACK_FUN_T));
    strcpy((char *) &callback_t.name[0], "CFG_BNR");

    callback_t.parse_fun = __cli2_bnr_stk_parse_cfg;
    callback_t.config_unit_fun = __cli2_bnr_stk_config_unit;

    /*register callback function*/
    ST_STACK_Register_CallBackFunc(CFG_BNR, &callback_t);
}



#endif

