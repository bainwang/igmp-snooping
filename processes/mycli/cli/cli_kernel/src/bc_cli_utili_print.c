/*******************************************************************************
  Copyright (C), 1988-2013, xxxxx Tech. Co., Ltd.
  [File name]	: utili_block_ext.h
  [Author]     	: bain.wang@outlook.com
  [Version]    	: 1.0
  [Date]       	: 2015-11-02
  [Description]	:
	define avlt api
  [Others]     	:
	NULL
  [Function List]:  
    1. ....
    2. ....
  [History]:
	 Date       	Modification 							 Initials
	---------- 	--------------                                        ----------
	2015-11-02  	Created								 bain.wang@outlook.com
*******************************************************************************/

#include "bc_print.h"
#include "bc_platform_mem.h"
#include "utili_list.h"
#include "bc_cli_utili_print.h"
#include "bc_cli.h"

typedef struct {
	bc_char *each_column_ptr[UTILI_PRINT_MAX_COLUMN];
} utili_print_control_t;

#define UTILI_PRINT_INNER_MAX_COLUMN 256

static bc_err_e __utili_print_para_check(utili_print_format_t *format, bc_char *each_column_str[UTILI_PRINT_MAX_COLUMN])
{
	bc_uint32 idx;
	bc_uint32 total_column = 0;

	if (format->column_num > UTILI_PRINT_MAX_COLUMN)
		return BC_ERR_OUT_OF_RANGE;

	for (idx = 0; idx < format->column_num; idx++)
	{
		if (format->each_column_with[idx] > UTILI_PRINT_WITH_MAX)
			return BC_ERR_OUT_OF_RANGE;

		total_column += format->each_column_with[idx];

		if (each_column_str[idx])
		{
			if (strlen(each_column_str[idx]) > UTILI_PRINT_WITH_MAX)
				return BC_ERR_OUT_OF_RANGE;
		}
	}

	if (total_column > UTILI_PRINT_INNER_MAX_COLUMN)
		return BC_ERR_OUT_OF_RANGE;

	return BC_ERR_OK;
}

static void __utili_print_ctrl_init(utili_print_format_t *format, bc_char *each_column_str[UTILI_PRINT_MAX_COLUMN], utili_print_control_t *ctrl)
{
	bc_uint32 idx;

	for (idx = 0; idx < format->column_num; idx++)
	{
		if (each_column_str[idx])
		{
			ctrl->each_column_ptr[idx] = each_column_str[idx];
		}
		else
		{
			ctrl->each_column_ptr[idx] = NULL;
		}
	}
}

static bc_boolean __utili_print_all_data_printed(utili_print_format_t *format, utili_print_control_t *ctrl)
{
	bc_uint32 idx;

	for (idx = 0; idx < format->column_num; idx++)
	{
		if (ctrl->each_column_ptr[idx] && (*(ctrl->each_column_ptr[idx]) != '\0'))
			return FALSE;
	}

	return TRUE;
}

static void __utili_print_a_column(bc_uint32 with, bc_uint32 column_ofs, utili_print_control_t *ctrl, bc_char *buf)
{
	bc_uint32 str_len;

	if (!ctrl->each_column_ptr[column_ofs])
	{
		str_len = 0;
		while (str_len < with)
		{
			buf[str_len] = ' ';
			str_len++;
		}
	}
	else
	{
		str_len = strlen(ctrl->each_column_ptr[column_ofs]);
		if (str_len < with)
		{
			memcpy(buf, ctrl->each_column_ptr[column_ofs], str_len);
			ctrl->each_column_ptr[column_ofs] += str_len;

			/* padding */
			while (str_len < with)
			{
				buf[str_len] = ' ';
				str_len++;
			}
		}
		else
		{
			memcpy(buf, ctrl->each_column_ptr[column_ofs], with-1);
			ctrl->each_column_ptr[column_ofs] += (with-1);
			buf[with-1] = ' ';
		}
	}
}

bc_err_e bc_cli_utili_print_format(bc_modules_e module_id, utili_print_format_t *format, bc_char *each_column_str[UTILI_PRINT_MAX_COLUMN])
{
	utili_print_control_t ctrl;
	
	bc_uint32 idx;

	bc_uint32 ofs;
	bc_char tmp_buf[UTILI_PRINT_INNER_MAX_COLUMN] = {0};

	if (!format || !each_column_str)
		return BC_ERR_PARA;

	if (__utili_print_para_check(format, each_column_str) != BC_ERR_OK)
		return BC_ERR_PARA;

	__utili_print_ctrl_init(format, each_column_str, &ctrl);
	
	while (__utili_print_all_data_printed(format, &ctrl) == FALSE)
	{
		memset(tmp_buf, 0x00, UTILI_PRINT_INNER_MAX_COLUMN);
		ofs = 0;
		for (idx = 0; idx < format->column_num; idx++)
		{
			ofs += ((idx) ? format->each_column_with[idx-1] : 0);
			__utili_print_a_column(format->each_column_with[idx], idx, &ctrl, tmp_buf+ofs);
		}

		BC_PT_COMMAND(module_id, "%s\n\r", tmp_buf);
	}

	return BC_ERR_OK;
}






