/*******************************************************************************
  -------------------------------------------------------------------------
  [File name]  : \\BC\cli\include\deal_string.h
  [Author]     : bain.wang@outlook.com
  [Version]    : 1.0
  [Date]       : 2017-08-02
  [Description]:

  [Others]     :

  [Function List]:
    1. ....
    2. ....
  [History]:
     D a t e    Modification                                          Initials
    ---------- --------------                                        ----------
    2017-08-02  Created                                               bain.wang@outlook.com
*******************************************************************************/

#ifndef __bc_cli_utili_print_h__
#define __bc_cli_utili_print_h__

#include "bc_common_defs.h"
#include "bc_proj_defs.h"

#include "bc_err.h"
#include "bc_modules.h"
#include "bc_modules_com_para.h"


#define UTILI_PRINT_MAX_COLUMN 80
#define UTILI_PRINT_WITH_MAX 80

typedef struct {
	bc_uint32 column_num;

	bc_uint32 each_column_with[UTILI_PRINT_MAX_COLUMN];
} utili_print_format_t;


extern bc_err_e bc_cli_utili_print_format(bc_modules_e module_id, utili_print_format_t *format, bc_char *each_column_str[UTILI_PRINT_MAX_COLUMN]);




#endif 

