
#ifndef __BC_CLI_FLTR_H__
#define __BC_CLI_FLTR_H__

////////////////////////////////////////////////////////////////////////////////
// 								    										  //
// 							    头   文   件								  //
// 										    								  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_cli_type.h"



////////////////////////////////////////////////////////////////////////////////
//																			  //
//						结   构   体   宏   定   义							  //
//																			  //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//																			  //
//								函	数	声	明								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

/*********************************************************************
FUNCTION NAME:
    CLI_FILTER_Create_Filterpara

DESCRIPTION:
    Create the filter's parameters

INPUT:
    ptr_parser: user filter string's copy pointer

OUTPUT:
    NA

RETURN:
    the handle of the filter's parameters

NOTES:

HISTORY:

**********************************************************************/
HANDLE_T CLI_FILTER_Create_Filterpara(IN const I8_T * ptr_parser);

/*********************************************************************
FUNCTION NAME:
	CLI_FILTER_Destroy_Filterpara

DESCRIPTION:
	destroy the filter's parameters

INPUT:
	hfilter:	handle used for storing filter's parameters

OUTPUT:
	None

RETURN:

NOTES:

HISTORY:

**********************************************************************/
void CLI_FILTER_Destroy_Filterpara(IN HANDLE_T hfilter);

/****************************************************************************
FUNCTION NAME:
	CLI_FILTER_MatchLine

DESCRIPTION:
	This function is used to  check that if the input string match the filter.

INPUT:
	hfilter:		the handle used for filter(the pointer used for storing filter parameters)
	line:			input line
	line_len:		the number of chars for the input line

OUTPUT:
	None

RETURN:
	TURE:		the input line and the filter match
	FALSE:		the input line and the filter don't match

NOTES:

HISTORY:

*****************************************************************************/
BOOL_T CLI_FILTER_MatchLine(IN HANDLE_T hfilter,
							 IN const I8_T * line, IN UI32_T line_len);

/****************************************************************************
FUNCTION NAME:
	CLI_FILTER_Cfg

DESCRIPTION:
	This function is used to  filter config file.

INPUT:
	ptr_usr_filter_string: 	user filter string pointer
	ptr_cfg: 				config pointer
	ptr_cfg_size:			config size pointer

OUTPUT:
	ptr_cfg: 				config pointer after filter
	ptr_cfg_size:			config size pointer after filter

RETURN:
	TRUE:				Success
	FALSE:				the format of input filter expression is wrong
	
NOTES:

HISTORY:

*****************************************************************************/
BOOL_T CLI_FILTER_Cfg(IN I8_T *ptr_usr_filter_string,
                                        	  IN OUT I8_T *ptr_cfg,
                                        	  IN OUT UI32_T *ptr_cfg_size);



#endif /* __BC_CLI_FLTR_H__ */

