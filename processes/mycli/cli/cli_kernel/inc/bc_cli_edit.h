
#ifndef  __BC_CLI_EDIT_H__
#define  __BC_CLI_EDIT_H__

////////////////////////////////////////////////////////////////////////////////
// 								    										  //
// 							    头   文   件								  //
// 										    								  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_cli_type.h"
#include "bc_cli_priv.h"
//#include "bc_cli.h"



////////////////////////////////////////////////////////////////////////////////
//																			  //
//						结   构   体   宏   定   义							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#define CLI_EDIT_LINE_LEN	 80



////////////////////////////////////////////////////////////////////////////////
//																			  //
//								函	数	声	明								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_EDIT_Create
 *
 * DESCRIPTION:
 *   create a handle for using edit module
 *
 * INPUT:
 *   hvio: the handle for using vio module
 *
 * OUTPUT:
 *   None
 *
 * RETURN:
 *   pointer: the handle for using edit module
 *
 * NOTES:
 *   None
 *
 * HISTORY:
 *
*******************************************************************************/
HANDLE_T CLI_EDIT_Create(IN HANDLE_T hvio);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_EDIT_Destroy
 *
 * DESCRIPTION:
 *   destroy the handle and free memory
 *
 * INPUT:
 *   hedit: the handle for using edit module
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
 *
*******************************************************************************/
void CLI_EDIT_Destroy(IN HANDLE_T hedit);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_EDIT_Get_InputMode
 *
 * DESCRIPTION:
 *   get the input_mode
 *
 * INPUT:
 *   hedit: the handle for using edit module
 *
 * OUTPUT:
 *   None
 *
 * RETURN:
 *   mode: input mode
 *
 * NOTES:
 *   None
 *
 * HISTORY:
 *
*******************************************************************************/
CLI_INPUT_MODE_T CLI_EDIT_Get_InputMode(IN HANDLE_T hedit);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_EDIT_Get_Line
 *
 * DESCRIPTION:
 *   get the input cmd and control keys
 *
 * INPUT:
 *   buf_len: the length of buffer
 *   hedit: the handle for using edit module
 *   h_hist: handle of the history for using history module
 *   pbuf: pointer of buffer for storing input cmd
 *   timeout_sec: time out second
 *   previous_ch: 0 -- nothing, other -- previous char user inputed
 *
 * OUTPUT:
 *   hedit: the handle for using edit module
 *   pbuf: pointer of input cmd string
 *
 * RETURN:
 *   -1: IO closed
 *   -2: timeout
 *   -3: noaction(the input function is null)
 *   -4: exit cmd
 *   +1: input CR and get input cmd success
 *   >1: The control key last pressed
 *
 * NOTES:
 *   None
 *
 * HISTORY:
 *
*******************************************************************************/
I32_T CLI_EDIT_Get_Line(
	IN OUT HANDLE_T hedit,
	IN HANDLE_T h_hist,
	IN OUT I8_T * pbuf,
	IN UI32_T buf_len,
	IN I32_T timeout_sec,
	IN I32_T previous_ch);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_EDIT_Get_OutputMode
 *
 * DESCRIPTION:
 *   get the output_mode
 *
 * INPUT:
 *   hedit: the handle for using edit module
 *
 * OUTPUT:
 *   None
 *
 * RETURN:
 *   mode: output mode
 *
 * NOTES:
 *   None
 *
 * HISTORY:
 *
*******************************************************************************/
CLI_INPUT_MODE_T CLI_EDIT_Get_OutputMode(IN HANDLE_T hedit);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_EDIT_Set_InputMode
 *
 * DESCRIPTION:
 *   set the input_mode
 *
 * INPUT:
 *   mode: input mode
 *   hedit: the handle for using edit module
 *
 * OUTPUT:
 *   hedit: the handle for using edit module
 *
 * RETURN:
 *   TRUE: set success
 *   FALSE: set failure
 *
 * NOTES:
 *   None
 *
 * HISTORY:
 *
*******************************************************************************/
BOOL_T CLI_EDIT_Set_InputMode(IN OUT HANDLE_T hedit, IN CLI_INPUT_MODE_T mode);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_EDIT_Set_OutputMode
 *
 * DESCRIPTION:
 *   set the output_mode
 *
 * INPUT:
 *   hedit: the handle for using edit module
 *   mode: output mode
 *
 * OUTPUT:
 *   hedit: the handle for using edit module
 *
 * RETURN:
 *   TRUE: set success
 *   FALSE: set failure
 *
 * NOTES:
 *   None
 *
 * HISTORY:
 *
*******************************************************************************/
BOOL_T CLI_EDIT_Set_OutputMode(IN OUT HANDLE_T hedit, IN cli_output_mode_e mode);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_EDIT_Get_PromptLen
 *
 * DESCRIPTION:
 *   Get the length of the prompt
 *
 * INPUT:
 *   hedit: the handle for using edit module
 *
 * OUTPUT:
 *   None
 *
 * RETURN:
 *   length of the prompt
 *
 * NOTES:
 *   None
 *
 * HISTORY:
 *
*******************************************************************************/
UI32_T CLI_EDIT_Get_PromptLen (IN OUT HANDLE_T hedit);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_EDIT_Set_PromptLen
 *
 * DESCRIPTION:
 *   set the length of the prompt
 *
 * INPUT:
 *   hedit: the handle for using edit module
 *   prompt_len: length of the prompt
 *
 * OUTPUT:
 *   hedit: the handle for using edit module
 *
 * RETURN:
 *   TRUE: set success
 *   FALSE: set failure
 *
 * NOTES:
 *   None
 *
 * HISTORY:
 *
*******************************************************************************/
BOOL_T CLI_EDIT_Set_PromptLen (IN OUT HANDLE_T hedit, IN I32_T prompt_len);
/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_EDIT_Get_Char
 *
 * DESCRIPTION:
 *   Get char from terminal
 *
 * INPUT:
 *   hedit: handle for edit module
 *   timeout_sec: timeout second
 *
 * OUTPUT:
 *   None
 *
 * RETURN:
 *   > 0: char
 *   -1: IO closed
 *   -2: timeout
 *   -3: noaction(the input function is null)
 *
 * NOTES:
 *   None
 *
 * HISTORY:
 *   2009-Aug-28 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
I32_T CLI_EDIT_Get_Char(IN HANDLE_T hedit, IN I32_T timeout_sec);

/**************************************************************************
FUNCTION NAME:
	CLI_EDIT_Match_Tab

DESCRIPTION:
	Checks all consecutive <Tab>s, and complete the command.

INPUT:
	hedit		: the handle for using edit module
	view		: current path
	level		: current user level
	helplist	: struct pointer of help list

OUTPUT:
	helplist	: the result of complement current word
	p_edit_state: new edit state
 	p_edit_state: new command state

RETURN:
	TRUE		: the command is complemented, continue to parse in this line.
	FALSE		: the command don't need to complement,
				  the command prompt and input command should be print in new line.

NOTES:
	NA

HISTORY:

**************************************************************************/
BOOL_T CLI_EDIT_Match_Tab (
	IN HANDLE_T hedit,
	IN I8_T *view,
	IN UI32_T level,
	IN OUT CLI_PRIV_HELPLIST_T *helplist);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_EDIT_Set_HistoryStatus
 *
 * DESCRIPTION:
 *   set the history status
 *
 * INPUT:
 *   hedit: the handle for using edit module
 *   use_history: TRUE: enable history; FALSE: disable history
 *
 * OUTPUT:
 *   hedit: the handle for using edit module
 *
 * RETURN:
 *   None
 *
 * NOTES:
 *   None
 *
 * HISTORY:
 *
*******************************************************************************/
void CLI_EDIT_Set_HistoryStatus (IN OUT HANDLE_T hedit, IN BOOL_T use_history);

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_EDIT_Get_Line_WithBreak
 *
 * DESCRIPTION:
 *   Get the input chars until trigger chars.
 *
 * INPUT:
 *   hedit: the handle for using edit module
 *   pbuf: pointer of buffer for storing input cmd
 *   buf_len: the length of buffer
 *   timeout_sec: time out second
 *
 * OUTPUT:
 *   hedit: the handle for using edit module
 *   pbuf: pointer of input cmd string
 *
 * RETURN:
 *   CLI_VKEY_IO_CLOSED: IO closed
 *   CLI_VKEY_IO_TIMEOUT: timeout
 *   CLI_VKEY_IO_NOACTION: noaction(the input function is null)
 *   CLI_VKEY_IO_EXITCMD: exit cmd
 *   trigger char
 *
 * NOTES:
 *   None
 *
 * HISTORY:
 *
*******************************************************************************/
I32_T CLI_EDIT_Get_Line_WithBreak(
	IN OUT HANDLE_T hedit,
	IN OUT I8_T *pbuf,
	IN UI32_T buf_len,
	IN I32_T timeout_sec,
	IN I32_T *trigger);



#endif /* __BC_CLI_EDIT_H__ */

