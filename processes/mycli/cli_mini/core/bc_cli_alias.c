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
 * FILE NAME  : bc_cli_alias.c
 * VERSION    : 1.0.0
 * DESCRIPTION:
 * NOTES:
 *
 * HISTORY:
 * -----------------------------------------------------------------------------
 * Version 1.0 -- 2009-Mar-12 by wangbin
 * [NEW FEATURE]
 * <DESCRIPTION> Create
 *============================================================================*/

////////////////////////////////////////////////////////////////////////////////
// 																			  //
// 							 	头   文   件								  //
// 																			  //
////////////////////////////////////////////////////////////////////////////////
#include "bc_common_defs.h"
#include "bc_modules.h"

#include "utili_bit.h"
#include "utili_string.h"

#include "bc_cli_kernel_cfg.h"
#include "bc_cli_type.h"
#include "bc_cli_misc.h"
#include "bc_cli_msg.h"
#include "bc_cli_vt100.h"
#include "bc_cli_alias.h"



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
/* port define */
#define CLI_ALIAS_PORT_TYPE_SNI_UP 			'S'
#define CLI_ALIAS_PORT_TYPE_SNI_LOW			's'
#define CLI_ALIAS_PORT_TYPE_PON_UP 			'P'
#define CLI_ALIAS_PORT_TYPE_PON_LOW 		'p'

#define CLI_ALIAS_PORT_SEPERATOR 			'/'
#define CLI_ALIAS_LLID_SEPERATOR 			':'
#define CLI_ALIAS_PORT_RANGE_SEPERATOR		'-'

#define CLI_ALIAS_DATE_SEPERATOR1			'-'
#define CLI_ALIAS_DATE_SEPERATOR2			'/'
#define IS_DATE_SEPERATOR(ch)				((((ch) == CLI_ALIAS_DATE_SEPERATOR1) || ((ch) == CLI_ALIAS_DATE_SEPERATOR2)) ? TRUE : FALSE)

#define CLI_TYPES_MAX_ENUMLIST 				32

#define IS_SNI_PORT_TYPE_CH(ch)				((((ch) == CLI_ALIAS_PORT_TYPE_SNI_UP) || ((ch) == CLI_ALIAS_PORT_TYPE_SNI_LOW)) ? TRUE : FALSE)
#define IS_PON_PORT_TYPE_CH(ch)				((((ch) == CLI_ALIAS_PORT_TYPE_PON_UP) || ((ch) == CLI_ALIAS_PORT_TYPE_PON_LOW)) ? TRUE : FALSE)

typedef struct
{
	I8_T 		*name; 		// name of the enum list
	const I8_T 	**entry; 	// address of the enumlist
	UI32_T 		count; 		// count of string in the enumlist entry
} CLI_TYPES_ENUMLIST_T;



////////////////////////////////////////////////////////////////////////////////
//																			  //
//							全 局 变 量 定 义								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

static unsigned int 	l_mdl_id = BC_MODULE_CLI_KERNEL_ALIAS;

static const I8_T *_cli2_types_enumlist_operator[] =
{
	"lt",
	"gt",
	"eq"
};

static const I8_T *_cli2_types_enumlist_bps[] =
{
	"2400",
	"9600",
	"19200",
	"38400",
	"57600",
	"115200"
};

static const I8_T *_cli2_types_enumlist_level[] =
{
	"1",
	"12",
	"15"
};

static const I8_T *_cli2_types_enumlist_log_level[] =
{
	"5",
	"7",
	"9"
};

static const I8_T *_cli2_types_enumlist_month[] =
{
	"jan",
	"feb",
	"mar",
	"apr",
	"may",
	"jun",
	"jul",
	"aug",
	"sep",
	"oct",
	"nov",
	"dec"
};

static const I8_T *_cli2_types_enumlist_weekday[] =
{
	"sun",
	"mon",
	"tue",
	"wed",
	"thu",
	"fri",
	"sat"
};

static const I8_T *_cli2_types_enumlist_week[] =
{
	"last",
	"1",
	"2",
	"3",
	"4"
};

static const I8_T *_cli2_types_enumlist_offset[] =
{
	"30",
	"60",
	"90",
	"120"
};

static const I8_T *_cli2_types_enumlist_workday[] =
{
	"1",
	"2",
	"3",
	"4",
	"last"
};



static CLI_TYPES_ENUMLIST_T 	s_cli2_types_enumlist[CLI_TYPES_MAX_ENUMLIST]; // used to save registered enum list
static UI32_T 					s_cli2_types_enumlist_count; // enum list already registered

#define CLI_TYPES_REG_ENUMARRAY(name, array) 	cli2_types_reg_enum(name, array, sizeof(array)/sizeof(int))



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

/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 cli2_types_reg_enum
 *
 * DESCRIPTION:
 *	 Register a enum list
 *
 * INPUT:
 *	 name  -- name of the enum list
 *	 entry -- address of the enum list
 *	 count -- count of the string in the enum list
 *
 * OUTPUT:
 *	 NA
 *
 * RETURN:
 *	 TRUE  -- success
 *	 FALSE -- failure
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-18 by wangbin -- Create
 *
*******************************************************************************/
static BOOL_T cli2_types_reg_enum(
	IN const I8_T 	*name,
	IN const I8_T 	**entry,
	IN UI32_T 		count)
{
	UI32_T 			i;

	if (s_cli2_types_enumlist_count >= CLI_TYPES_MAX_ENUMLIST)
	{
		CLI_MSG_PrtErrMsg(UTL_MISC_ERR_TOO_MANY_ENUMLIST);
		return FALSE;
	}

	for (i = 0; i < s_cli2_types_enumlist_count; i++)
	{
		if (strcmp(name, s_cli2_types_enumlist[i].name) == 0)
		{ // already registered
			CLI_MSG_PrtErrMsg(UTL_MISC_ERR_REDEFINE_ENUMLIST);
			return FALSE;
		}
	}

	s_cli2_types_enumlist[s_cli2_types_enumlist_count].name = (I8_T *) name;
	s_cli2_types_enumlist[s_cli2_types_enumlist_count].entry = entry;
	s_cli2_types_enumlist[s_cli2_types_enumlist_count].count = count;

	s_cli2_types_enumlist_count++;

	return TRUE;
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_get_range_of_null

DESCRIPTION:
	cli2_types_get_range_of_null

INPUT:
	str				: begining of input range string
	end				: end of input range string

OUTPUT:
	lparam			: small value
	rparam			: large value

RETURN:
	TURE			: get range success
	FALSE			: input range string is error

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_range_of_null(
	IN const I8_T *str,
	IN const I8_T *end,
	OUT LPARAM *lparam,
	OUT RPARAM *rparam)
{
	if (str || end || lparam || rparam) {}

	return TRUE;
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_prt_range_of_null

DESCRIPTION:
	cli2_types_prt_range_of_null

INPUT:
	lparam			: small value
	rparam			: large value

OUTPUT:
	buf				: storing range string

RETURN:
	the length of the range string

NOTES:

HISTORY:

**************************************************************************/
static I32_T cli2_types_prt_range_of_null(
	OUT I8_T *buf,
	IN LPARAM lparam,
	IN RPARAM rparam)
{
	if (buf || lparam || rparam) {}

	return 0;
}

/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 cli2_types_get_enumlist_entry
 *
 * DESCRIPTION:
 *	 Get entry point of a enum list.
 *
 * INPUT:
 *	 name -- name of the enum list
 *	 len -- length of the name
 *
 * OUTPUT:
 *	 NA
 *
 * RETURN:
 *	 NULL -- failure
 *	 not NULL -- Entry point of the enum list
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-18 by wangbin -- Create
 *
*******************************************************************************/
static CLI_TYPES_ENUMLIST_T *cli2_types_get_enumlist_entry(
	IN const I8_T *name,
	IN I32_T len)
{
	UI32_T i;

	for (i = 0; i < s_cli2_types_enumlist_count; i++)
	{
		if ((len == strlen (s_cli2_types_enumlist[i].name)) && (strncmp(name, s_cli2_types_enumlist[i].name, len) == 0))
		{ // find enum list
			return s_cli2_types_enumlist + i;
		}
	}

	return NULL;
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 cli2_types_get_range_of_enumlist
 *
 * DESCRIPTION:
 *	 Get the range of enumlist
 *
 * INPUT:
 *	 str -- name of the enum list
 *	 end -- next char after enum list name

 * OUTPUT:
 *	 lparam -- address of the enumlist
 *	 rparam -- 0
 *
 * RETURN:
 *	 TRUE -- success
 *	 FALSE -- failure
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-19 by wangbin -- Create
 *
*******************************************************************************/
static BOOL_T cli2_types_get_range_of_enumlist(
	IN const I8_T *str,
	IN const I8_T *end,
	OUT LPARAM *lparam,
	OUT RPARAM *rparam)
{
	CLI_TYPES_ENUMLIST_T *enumentry;

	// get entry point of the enum list
	enumentry = cli2_types_get_enumlist_entry(str, end - str);
	if (enumentry == NULL)
	{
		return FALSE;
	}

	// save entry point to lparam
	*lparam = (LPARAM)enumentry;
	*rparam = 0;

	return TRUE;
}

/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 cli2_types_prt_range_of_enumlist
 *
 * DESCRIPTION:
 *	 print all members in enumlist to buffer
 *
 * INPUT:
 *	 lparam -- address of the enumlist
 *	 rparam -- 0
 *
 * OUTPUT:
 *	 buf -- members in enumlist, seperated by comma(,)
 *
 * RETURN:
 *	 result chars in buf.
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-19 by wangbin -- Create
 *
*******************************************************************************/
static I32_T cli2_types_prt_range_of_enumlist( // enum-ui32, enum-string
	OUT I8_T *buf,
	IN LPARAM lparam,
	IN RPARAM rparam)
{
	CLI_TYPES_ENUMLIST_T *enumentry;
	I32_T i;
	I32_T ret;

	ret = 0;
	enumentry = (CLI_TYPES_ENUMLIST_T *)lparam;
	for (i = 0; i < enumentry->count; i++)
	{
		//ret += sprintf(buf + ret, "%s,", enumentry->entry[i]);
		ret += sprintf(buf + ret, "%s,", enumentry->entry[i]);
	}

	if (ret > 0)
	{
		ret--;
		buf[ret] = '\0';
	}
	else
	{
		buf[0] = '\0';
	}

	return ret;
}

/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 cli2_types_get_value_of_enum_ui32
 *
 * DESCRIPTION:
 *	 Check a word in user command match a uinsigned int or not, if match, then
 *		get the value.
 *
 * INPUT:
 *	 str -- word in user command (zero terminated)
 *	 lparam
 *	 rparam -- [lparam, rparam] = range of the word.
 *
 * OUTPUT:
 *	 *value -- if str is a unsigned int, it Returns the value.
 *
 * RETURN:
 *	 TRUE -- success
 *	 FALSE -- failure
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-19 by wangbin -- Create
 *
*******************************************************************************/
static BOOL_T cli2_types_get_value_of_enum_ui32(
	IN const I8_T *str,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{
	CLI_TYPES_ENUMLIST_T *enumentry;
	I32_T i;

	enumentry = (CLI_TYPES_ENUMLIST_T *)lparam;
	for (i = 0; i < enumentry->count; i++)
	{
		if (strcmp(enumentry->entry[i], str) == 0)
		{
			*(UI32_T *)value = strtoul(enumentry->entry[i], NULL, 10);
			return TRUE;
		}
	}

	return FALSE;
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_get_value_of_enum_string

DESCRIPTION:
	cli2_types_get_value_of_enum_string

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_value_of_enum_string(
	IN const I8_T *str,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{
	CLI_TYPES_ENUMLIST_T *enumentry;
	I32_T i;

	enumentry = (CLI_TYPES_ENUMLIST_T *)lparam;
	for (i = 0; i < enumentry->count; i++)
	{
		if ((strcmp(enumentry->entry[i], str) == 0) && (strlen(enumentry->entry[i]) == strlen(str)))
		{
			strcpy(value, enumentry->entry[i]);
			return TRUE;
		}
	}

	return FALSE;
}


/**************************************************************************
FUNCTION NAME:
	cli2_types_prt_range_of_month

DESCRIPTION:
	cli2_types_prt_range_of_month

INPUT:
	lparam			: small value
	rparam			: large value

OUTPUT:
	buf				: storing range string

RETURN:
	the length of the range string

NOTES:

HISTORY:

**************************************************************************/
static I32_T cli2_types_prt_range_of_month(
	OUT I8_T *buf,
	IN LPARAM lparam,
	IN RPARAM rparam)
{
	I32_T i, count;
	I32_T ret;

	count = sizeof(_cli2_types_enumlist_month) / sizeof(I8_T *);
	ret = 0;
	for (i = 0; i < count; i++)
	{
		//ret += CLI_API_Sprintf(buf + ret, "%s,", _cli2_types_enumlist_month[i]);
		ret += sprintf(buf + ret, "%s,", _cli2_types_enumlist_month[i]);
	}

	if (ret > 0)
	{
		ret--;
		buf[ret] = '\0';
	}
	else
	{
		buf[0] = '\0';
	}

	return ret;
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_get_value_of_month

DESCRIPTION:
	cli2_types_get_value_of_months

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_value_of_month(
	IN const I8_T *str,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{
	UI32_T i, count;

	count = sizeof(_cli2_types_enumlist_month) / sizeof(I8_T *);

	for (i = 0; i < count; i++)
	{
		if (strcmp(_cli2_types_enumlist_month[i], str) == 0
			&& (strlen(_cli2_types_enumlist_month[i]) == strlen(str)))
		{
			*(UI32_T *)value = i;
			return TRUE;
		}
	}

	return FALSE;
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_prt_value_of_month

DESCRIPTION:
	cli2_types_prt_value_of_month

INPUT:
	value			: input parameter value

OUTPUT:
	buf				: storing parameter string

RETURN:
	the length of the parameter string

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_prt_value_of_month(
	OUT I8_T *buf,
	IN void *value)
{
	UI32_T count, i;

	count = sizeof(_cli2_types_enumlist_month) / sizeof(I8_T *);
	i = *(UI32_T *)value;

	if (i > count)
	{
		return FALSE;
	}
	else
	{
		return sprintf(buf, "%s", _cli2_types_enumlist_month[i]);
	}
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_prt_range_of_weekday

DESCRIPTION:
	cli2_types_prt_range_of_weekday

INPUT:
	lparam			: small value
	rparam			: large value

OUTPUT:
	buf				: storing range string

RETURN:
	the length of the range string

NOTES:

HISTORY:

**************************************************************************/
static I32_T cli2_types_prt_range_of_weekday(
	OUT I8_T *buf,
	IN LPARAM lparam,
	IN RPARAM rparam)
{
	I32_T i, count;
	I32_T ret;

	count = sizeof(_cli2_types_enumlist_weekday) / sizeof(I8_T *);
	ret = 0;
	for (i = 0; i < count; i++)
	{
		ret += sprintf(buf + ret, "%s,", _cli2_types_enumlist_weekday[i]);
	}

	if (ret > 0)
	{
		ret--;
		buf[ret] = '\0';
	}
	else
	{
		buf[0] = '\0';
	}

	return ret;
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_get_value_of_weekday

DESCRIPTION:
	cli2_types_get_value_of_weekday

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_value_of_weekday(
	IN const I8_T *str,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{
	UI32_T i, count;

	count = sizeof(_cli2_types_enumlist_weekday) / sizeof(I8_T *);

	for (i = 0; i < count; i++)
	{
		if (strcmp(_cli2_types_enumlist_weekday[i], str) == 0
			&& (strlen(_cli2_types_enumlist_weekday[i]) == strlen(str)))
		{
			*(UI32_T *)value = i;
			return TRUE;
		}
	}

	return FALSE;
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_prt_value_of_weekday

DESCRIPTION:
	cli2_types_prt_value_of_weekday

INPUT:
	value			: input parameter value

OUTPUT:
	buf				: storing parameter string

RETURN:
	the length of the parameter string

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_prt_value_of_weekday(
	OUT I8_T *buf,
	IN void *value)
{
	UI32_T count, i;

	count = sizeof(_cli2_types_enumlist_weekday) / sizeof(I8_T *);
	i = *(UI32_T *)value;

	if (i > count)
	{
		return FALSE;
	}
	else
	{
		return sprintf(buf, "%s", _cli2_types_enumlist_weekday[i]);
	}
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_prt_range_of_week

DESCRIPTION:
	cli2_types_prt_range_of_week

INPUT:
	lparam			: small value
	rparam			: large value

OUTPUT:
	buf				: storing range string

RETURN:
	the length of the range string

NOTES:

HISTORY:

**************************************************************************/
static I32_T cli2_types_prt_range_of_week(
	OUT I8_T *buf,
	IN LPARAM lparam,
	IN RPARAM rparam)
{
	I32_T i, count;
	I32_T ret;

	count = sizeof(_cli2_types_enumlist_week) / sizeof(I8_T *);
	ret = 0;
	for (i = 0; i < count; i++)
	{
		ret += sprintf(buf + ret, "%s,", _cli2_types_enumlist_week[i]);
	}

	if (ret > 0)
	{
		ret--;
		buf[ret] = '\0';
	}
	else
	{
		buf[0] = '\0';
	}

	return ret;
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_get_value_of_week

DESCRIPTION:
	cli2_types_get_value_of_week

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_value_of_week(
	IN const I8_T *str,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{
	UI32_T i, count;

	count = sizeof(_cli2_types_enumlist_week) / sizeof(I8_T *);

	for (i = 0; i < count; i++)
	{
		if (strcmp(_cli2_types_enumlist_week[i], str) == 0
			&& (strlen(_cli2_types_enumlist_week[i]) == strlen(str)))
		{
			*(UI32_T *)value = i;
			return TRUE;
		}
	}

	return FALSE;
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_prt_value_of_week

DESCRIPTION:
	cli2_types_prt_value_of_week

INPUT:
	value			: input parameter value

OUTPUT:
	buf				: storing parameter string

RETURN:
	the length of the parameter string

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_prt_value_of_week(
	OUT I8_T *buf,
	IN void *value)
{
	UI32_T count, i;

	count = sizeof(_cli2_types_enumlist_week) / sizeof(I8_T *);
	i = *(UI32_T *)value;

	if (i > count)
	{
		return FALSE;
	}
	else
	{
		return sprintf(buf, "%s", _cli2_types_enumlist_week[i]);
	}
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_prt_value_of_ui32

DESCRIPTION:
	cli2_types_prt_value_of_ui32

INPUT:
	value			: input parameter value

OUTPUT:
	buf				: storing parameter string

RETURN:
	the length of the parameter string

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_prt_value_of_ui32(
	OUT I8_T *buf,
	IN void *value)
{
	return sprintf(buf, "%u", *(UI32_T *)value);
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_cmp_value_of_ui32

DESCRIPTION:
	cli2_types_cmp_value_of_ui32

INPUT:
	ptr1				: parameter value
	ptr2				: parameter value

OUTPUT:

RETURN:
	1				: ptr1 > ptr2
	0				: ptr1 == ptr2
	-1				: ptr1 < ptr2

NOTES:

HISTORY:

**************************************************************************/
static I32_T cli2_types_cmp_value_of_ui32(IN void *ptr1, IN void *ptr2)
{
	UI32_T left;
	UI32_T right;

	left = *(UI32_T *) ptr1;
	right = *(UI32_T *) ptr2;

	if (left < right)
	{
		return -1;
	}
	else if (left == right)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_get_range_of_string

DESCRIPTION:
	cli2_types_get_range_of_string

INPUT:
	str				: begining of input range string
	end				: end of input range string

OUTPUT:
	lparam			: small value
	rparam			: large value

RETURN:
	TURE			: get range success
	FALSE			: input range string is error

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_range_of_string(
	IN const I8_T *str,
	IN const I8_T *end,
	IN OUT LPARAM *lparam,
	IN OUT RPARAM *rparam)
{
	I8_T *p;

	if ((str == NULL) || (str >= end)) // nothing in range string
	{
		return FALSE;
	}

	*lparam = strtoul(str, &p, 10);
	if (*p == '-') // range string is like "lparam-rparam"
	{
		p++;
		*rparam = strtoul (p, &p, 10); // we don't check if p is out of range
		if (p != end)
		{
			return FALSE;
		}
	}
	else // only rparam in range string
	{
		if (p != end)
		{
			return FALSE;
		}
		*rparam = *lparam;
		*lparam = 1;
	}

	if ((*lparam > *rparam) || (*rparam > CLI_API_MAX_CMD_LEN))
	{
		return FALSE;
	}

	return TRUE;
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_prt_range_of_string

DESCRIPTION:
	cli2_types_prt_range_of_string

INPUT:
	lparam			: small value
	rparam			: large value

OUTPUT:
	buf				: storing range string

RETURN:
	the length of the range string

NOTES:

HISTORY:

**************************************************************************/
static I32_T cli2_types_prt_range_of_string(
	OUT I8_T *buf,
	IN LPARAM lparam,
	IN RPARAM rparam)
{
	I32_T ret;
	if (lparam == rparam)
	{
		ret = sprintf(buf, "%u", lparam);
	}
	else
	{
		ret = sprintf(buf, "%u-%u", lparam, rparam);
	}

	return ret;
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_get_value_of_string

DESCRIPTION:
	cli2_types_get_value_of_string

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_value_of_string(
	IN const I8_T *str,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{
	I32_T len;

	len = strlen (str);
	// printf ("%d, %d\r\n", lparam, rparam);
	if ((len < lparam) || (len > rparam))
	{
		return FALSE;
	}

	strcpy(value, str);
	return TRUE;
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_get_value_of_string_without_whitespace

DESCRIPTION:
	cli2_types_get_value_of_string_without_whitespace

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_value_of_string_without_whitespace (
	IN const I8_T *str,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{
	I32_T len;
	I32_T i;

	len = strlen (str);
	// printf ("%d, %d\r\n", lparam, rparam);
	if ((len < lparam) || (len > rparam))
	{
		return FALSE;
	}

	for (i = 0; i < len; i++)
	{
		if ((str[i] == ' ') || (str[i] == '\t'))
		{
			return FALSE;
		}
	}

	strcpy(value, str);
	return TRUE;
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_get_value_of_name

DESCRIPTION:
	cli2_types_get_value_of_names

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_value_of_name (
	IN const I8_T *str,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{
	I32_T len;
	const I8_T *p;

	len = strlen (str);
	// printf ("%d, %d\r\n", lparam, rparam);
	if ((len < lparam) || (len > rparam))
	{
		return FALSE;
	}

	if (!isalpha(*str))
	{
		return FALSE;
	}

	for (p = str + 1; *p; p++)
	{
		if (isalpha(*p) || isdigit(*p))
		{
			continue;
		}

		switch (*p) // a-zA-Z0-9
		{
			case '!': /* fall through */
			case '#':
			case '$':
			case '%':
			case '&':
			case '(':
			case ')':
			case '+':
			case ',':
			case '.':
			case '=':
			case '@':
			case '[':
			case ']':
			case '^':
			case '_':
			case '`':
			case '{':
			case '}':
			case '~':
			case '/':
			case ':':
			case '<':
			case '>':
			case '*':
			case '-':
			case '\'':
			case '\\':
			    continue;

			default:
			    return FALSE;
		}
	}

	strcpy(value, str);
	return TRUE;
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_prt_value_of_string

DESCRIPTION:
	cli2_types_prt_value_of_string

INPUT:
	value			: input parameter value

OUTPUT:
	buf				: storing parameter string

RETURN:
	the length of the parameter string

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_prt_value_of_string(
	OUT I8_T *buf,
	IN void *value)
{
	return sprintf(buf, "%s", (char *)value);
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_cmp_value_of_string

DESCRIPTION:
	cli2_types_cmp_value_of_string

INPUT:
	ptr1				: parameter value
	ptr2				: parameter value

OUTPUT:

RETURN:
	1				: ptr1 > ptr2
	0				: ptr1 == ptr2
	-1				: ptr1 < ptr2

NOTES:

HISTORY:

**************************************************************************/
static I32_T cli2_types_cmp_value_of_string(IN void *ptr1, IN void *ptr2)
{
	I8_T *left;
	I8_T *right;

	left = ptr1;
	right = ptr2;
	return strcmp(left, right);
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_prt_value_multiword

DESCRIPTION:
	cli2_types_prt_value_multiword

INPUT:
	value			: input parameter value

OUTPUT:
	buf				: storing parameter string

RETURN:
	the length of the parameter string

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_prt_value_multiword(
	OUT I8_T *buf,
	IN void *value)
{
	if (*((I8_T *)value) == 0/*NULL*/)
	{
		return FALSE;
	}
	else
	{
		return sprintf(buf, "\"%s\"", (char *)value);
	}
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_get_value_of_ipaddr

DESCRIPTION:
	cli2_types_get_value_of_ipaddrs

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_value_of_ipaddr (
	IN const I8_T *start,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{
	// Format of IPADDR maybe xxx.xxx.xxx.xxx
	I8_T *end;
	UI8_T *ipstr;
	I32_T ret;
	I32_T i;

	if (lparam || rparam) {}

	ipstr = value;

	for (i = 0; i < 4; i++)
	{
		ret = strtoul(start, &end, 10);

		if (((end - start) > 3) || (ret < 0) || (ret > 255))
		{
			return FALSE;
		}

		if (ipstr)
		{
			*ipstr++ = (UI8_T) ret;
		}

		start = end;
		if (i < 3)
		{
			if (*start != '.')
			{
				return FALSE;
			}
			start++;
		}
	}

	if (*start != '\0')
	{
		return FALSE;
	}

	return TRUE;
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_prt_value_of_ipaddr

DESCRIPTION:
	cli2_types_prt_value_of_ipaddr

INPUT:
	value			: input parameter value

OUTPUT:
	buf				: storing parameter string

RETURN:
	the length of the parameter string

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_prt_value_of_ipaddr (
	OUT I8_T *buf,
	IN void *value)
{
	return sprintf(buf, "%a", (double)*(UI32_T *)value);
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_get_value_of_ipnetaddr

DESCRIPTION:
	cli2_types_get_value_of_ipnetaddr

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_value_of_ipnetaddr(
	IN const I8_T *start,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{
	// Format of IPADDR maybe xxx.xxx.xxx.xxx/32 or xxx.xxx.xxx.xxx/255.0.0.0
	I8_T ipv4addr[16];
	I8_T *str_end;
	I32_T i;
	UI32_T ip_num, mask_num, mask_len;

	if (lparam || rparam) {}

	memset(ipv4addr, 0, sizeof(ipv4addr));
	for (i = 0; i < 15; i++)
	{
		if (*start == '\0')
		{
			return FALSE;
		}

		if (*start == '/')
		{
			break;
		}

		ipv4addr[i] = *start++;
	}

	if (*start != '/')
	{
		return FALSE;
	}
	else
	{
		start++;
	}

	if (cli2_types_get_value_of_ipaddr(ipv4addr, (LPARAM)NULL, (RPARAM)NULL, &ip_num) == FALSE)
	{
		return FALSE;
	}

	memset(ipv4addr, 0, sizeof(ipv4addr));
	for (i = 0; i < 15; i++)
	{
		if (*start == '\0')
		{
			break;
		}

		ipv4addr[i] = *start++;
	}

	if (*start != '\0')
	{
		return FALSE;
	}

	if (cli2_types_get_value_of_ipaddr(ipv4addr, (RPARAM)NULL, (RPARAM)NULL, &mask_num) == FALSE)
	{
		mask_len = (UI32_T)strtoul(ipv4addr, &str_end, 10);
		if (*str_end != 0 || mask_len > 32 || mask_len < 0)
		{
			return FALSE;
		}

		mask_num = 0;
		for (i = 31; i >= (I32_T)(32 - mask_len); i--)
		{
			mask_num |= (1<<i);
		}
	}

	memcpy(value, &ip_num, sizeof(UI32_T));
	memcpy(((I8_T *)value)+sizeof(UI32_T), &mask_num, sizeof(UI32_T));

	return TRUE;
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_prt_value_of_ipnetaddr

DESCRIPTION:
	cli2_types_prt_value_of_ipnetaddr

INPUT:
	value			: input parameter value

OUTPUT:
	buf				: storing parameter string

RETURN:
	the length of the parameter string

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_prt_value_of_ipnetaddr(
	OUT I8_T *buf,
	IN void *value)
{
	return sprintf(buf, "%A", (double)*(UI32_T *)value);
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_get_value_of_ipmulticastaddr

DESCRIPTION:
	cli2_types_get_value_of_ipmulticastaddr

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_value_of_ipmulticastaddr (
	IN const I8_T *start,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{
	BOOL_T ret;
	UI8_T *ipstr;

	if (lparam || rparam) {}

	ret = cli2_types_get_value_of_ipaddr(start, lparam, rparam, value);

	if (ret)
	{
		/* check the first byte value */
		ipstr = value;
		if ((*ipstr < 224) || (*ipstr > 239))
		{
			return FALSE;
		}
	}

	return ret;
}

/**************************************************************************
FUNCTION NAME:
	cli2_alias_merge_ipmulticastaddrchain

DESCRIPTION:
	cli2_alias_merge_ipmulticastaddrchain

INPUT:
	pArray			: value chain need to merge

OUTPUT:
	pArray			: value chain need to merge

RETURN:

NOTES:

HISTORY:

**************************************************************************/
static void cli2_alias_merge_ipmulticastaddrchain(IN OUT CLI_VALUEARRAY_T *pArray)
{
	UI32_T *pBegin;
	UI32_T idx, cnt;
	UI32_T i;
	UI32_T *range1, *range2;

	if (pArray == NULL || pArray->count < 2)
	{
		return;
	}

	cnt = pArray->count;
	pBegin = (UI32_T *)&pArray->valueBegin;
	idx = 0;

	while (idx < (cnt - 1));
	{
		range1 = pBegin + idx * 2;

		i = idx + 1;
		while (i < cnt)
		{
			range2 = pBegin + i * 2;
			if (((range1[0] <= range2[0]) && (range1[1] >= range2[0]))
				|| ((range1[0] >= range2[0]) && (range1[0] <= range2[1])))
			{
				range1[0] = (range1[0] >= range2[0]) ? range2[0] : range1[0];
				range1[1] = (range1[1] >= range2[1]) ? range1[1] : range2[1];

				memmove(range2, range2 + 2, (cnt - i - 1) * sizeof(UI32_T) * 2);
				pArray->count--;
				cnt--;
				i = idx + 1;
			}
			else
			{
				i++;
			}
		}
		idx++;
	}
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_get_value_of_ipmulticastaddrchain

DESCRIPTION:
	cli2_types_get_value_of_ipmulticastaddrchain

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_value_of_ipmulticastaddrchain(
	IN const I8_T *start,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{
	I8_T ipv4addr[16];
	UI32_T used_size, i;
	UI32_T small, large;
	CLI_VALUEARRAY_T *ip_chain;
	UI32_T *value_begin;

	/* the alloc size is CLI_API_MAX_CMD_LEN
	 * in function CLI_TYPES_GetValue() and CLI_TYPES_Get_CurrentHelp()
	 */
	memset(value, 0, CLI_API_MAX_CMD_LEN);
	ip_chain = value;
	ip_chain->type = CLI_TYPES_IPMULTICASTADDRCHAIN;
	ip_chain->count = 0;
	used_size = sizeof(CLI_VALUEARRAY_T);
	value_begin = (UI32_T *)&ip_chain->valueBegin;

	while (*start)
	{
		/* check the used buffer size */
		if ((used_size += (sizeof(UI32_T) * 2)) > CLI_API_MAX_CMD_LEN)
		{
			return FALSE;
		}

		/* get left range */
		memset(ipv4addr, 0, sizeof(ipv4addr));
		for (i = 0; i < 15; i++)
		{
			if ((*start == '\0') || *start == '-' || *start == ',')
			{
				break;
			}
			ipv4addr[i] = *start++;
		}
		if (cli2_types_get_value_of_ipmulticastaddr(ipv4addr, lparam, rparam, &small) == FALSE)
		{
			return FALSE;
		}

		if (*start == '-')
		{
			/* get right range */
			start++;
			memset(ipv4addr, 0, sizeof(ipv4addr));
			for (i = 0; i < 15; i++)
			{
				if ((*start == '\0') || *start == ',')
				{
					break;
				}
				ipv4addr[i] = *start++;
			}
			if (cli2_types_get_value_of_ipmulticastaddr(ipv4addr, lparam, rparam, &large) == FALSE)
			{
				return FALSE;
			}
		}
		else
		{
			large = small;
		}

		if (small > large)
		{
			return FALSE;
		}

		*value_begin++ = small;
		*value_begin++ = large;
		ip_chain->count++;

		if (*start)
		{
			if (*start != ',')
			{
				return FALSE;
			}
			start++;
		}
	}

	if (ip_chain->count == 0)
	{
		return FALSE;
	}

	cli2_alias_merge_ipmulticastaddrchain(ip_chain);

	return TRUE;
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_prt_value_of_ipmulticastaddrchain

DESCRIPTION:
	cli2_types_prt_value_of_ipmulticastaddrchain

INPUT:
	value			: input parameter value

OUTPUT:
	buf				: storing parameter string

RETURN:
	the length of the parameter string

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_prt_value_of_ipmulticastaddrchain(
	OUT I8_T *buf,
	IN void *value)
{
	CLI_VALUEARRAY_T *pArray;
	UI32_T *pBegin;
	UI32_T cnt;
	I8_T *current;
	UI32_T *range;
	UI32_T i;

	pArray = (CLI_VALUEARRAY_T *)value;
	pBegin = (UI32_T *)&pArray->valueBegin;
	cnt = pArray->count;
	current = buf;

	for (i = 0; i < cnt; i++)
	{
		range = pBegin + i * 2;
		current += sprintf(current, "%a", (double)range[0]);
		if (range[1] > range[0])
		{
			*(current++) = '-';
			current += sprintf(current, "%a", (double)range[1]);
		}

		if (i != cnt - 1)
		{
			/* more value exists */
			*(current++) = ',';
		}
	}

	*(current) = VT_NULL;

    return (UI32_T)current - (UI32_T)buf;
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_get_value_of_ipv6addr

DESCRIPTION:
	cli2_types_get_value_of_ipv6addr

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_value_of_ipv6addr (
	IN const I8_T *ipv6_str,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{
#if 0
	LA3_IP6ADDR ipv6addr;
	I8_T *if_strptr;
	UI32_T if_len;
	BOOL_T ret;

	if (lparam || rparam) {}

	ret = UTL_EXTPRT_TransStrToIPv6((I8_T *)ipv6_str, &ipv6addr);

	if (ret)
	{
		memcpy(value, &ipv6addr, sizeof(LA3_IP6ADDR));

		while (*ipv6_str)
		{
			if (*ipv6_str == '/')
			{
				return FALSE;
			}

			if (*ipv6_str == '%')
			{
				break;
			}
			ipv6_str++;
		}

		/*process link local ipv6addr interfacename */
		if (*ipv6_str == '%')
		{
			if_len = 0;
			if_strptr = (I8_T *)ipv6_str;
			while (*ipv6_str)
			{
				ipv6_str++;
				if_len++;
				/*max len of interface =12*/
				/* beacuse '%' character is calculated, so the max len should be
				* 12(max len of interface) + 1(sign '%') = 13. so the judgement
				* should be (if_len > 13)
				*/
				if (if_len > 13)
				{
					break;
				}
			}

			/* no interface name or over the max len */
			if (if_len <= 1 || if_len > 13)
			{
				return FALSE;
			}

			memcpy(((UI8_T *)value + sizeof(LA3_IP6ADDR)), if_strptr, if_len);
			/*Add zero terminate*/
			*((UI8_T *)value + sizeof(LA3_IP6ADDR) + if_len) = 0;
		}
	}

	return ret;
#else
	CLI_DBG_NOTSUPPORTED(l_mdl_id);
	return FALSE;
#endif
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_prt_value_of_ipv6addr

DESCRIPTION:
	cli2_types_prt_value_of_ipv6addr

INPUT:
	value			: input parameter value

OUTPUT:
	buf				: storing parameter string

RETURN:
	the length of the parameter string

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_prt_value_of_ipv6addr (
	OUT I8_T *buf,
	IN void *value)
{
#if 0
	UI8_T *temp_ptr;
	I32_T len;

	len = sprintf(buf, "%v", value);

	temp_ptr = (UI8_T *)value + sizeof(LA3_IP6ADDR);
	/* check local ipif name */
	if (*temp_ptr == '%')
	{
		if (strlen(temp_ptr) > 13)
		{
			return FALSE;
		}

		strcat(buf, temp_ptr);
		len += strlen(temp_ptr);
	}

	return len;
#else
	CLI_DBG_NOTSUPPORTED(l_mdl_id);
	return FALSE;
#endif
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_get_value_of_ipv6netaddr

DESCRIPTION:
	cli2_types_get_value_of_ipv6netaddr

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_value_of_ipv6netaddr (
	IN const I8_T *ipv6_str,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{
#if 0
	// Format of IPv6NetAddr maybe xxxx::xxxx/64
	I8_T *p_end;
	UI32_T prefix_len;
	UI32_T byte_count, bit_count;
	I32_T i;
	CLI_IPV6_NET_ADDR *ipv6_netaddr = value;

	if (lparam || rparam) {}

	memset(ipv6_netaddr, 0, sizeof(CLI_IPV6_NET_ADDR));

	if (UTL_EXTPRT_TransStrToIPv6((I8_T *)ipv6_str, &ipv6_netaddr->addr) == FALSE)
	{
		return FALSE;
	}

	while (*ipv6_str)
	{
		/* for ipv6 netaddr don't have interfacename */
		if (*ipv6_str == '%')
		{
			return FALSE;
		}

		if (*ipv6_str == '/')
		{
			break;
		}

		ipv6_str++;
	}

	if (*ipv6_str != '/')
	{
		return FALSE;
	}
	else
	{
		ipv6_str++;
	}

	prefix_len = strtoul(ipv6_str, &p_end, 10);
	if (*p_end || (prefix_len > 128) || (prefix_len <= 0))
	{
		return FALSE;
	}

	byte_count = prefix_len / 16;
	bit_count = prefix_len % 16;

	for (i = 0; i < byte_count; i++)
	{
		ipv6_netaddr->prefix[i] = 0xFFFF;
	}

	for (i = 15; i >= (I32_T)(16 - bit_count); i--)
	{
		ipv6_netaddr->prefix[byte_count] |= (1<<i);
	}

	for (i = 0; i < 8; i++)
	{
		ipv6_netaddr->prefix[i] = UTL_MISC_SWAP16(ipv6_netaddr->prefix[i]);
	}

	return TRUE;
#else
	CLI_DBG_NOTSUPPORTED(l_mdl_id);
	return FALSE;
#endif
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_prt_value_of_ipv6netaddr

DESCRIPTION:
	cli2_types_prt_value_of_ipv6netaddr

INPUT:
	value			: input parameter value

OUTPUT:
	buf				: storing parameter string

RETURN:
	the length of the parameter string

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_prt_value_of_ipv6netaddr (
	OUT I8_T *buf,
	IN void *value)
{
#if 0
	return sprintf(buf,"%V",value);
#else
	CLI_DBG_NOTSUPPORTED(l_mdl_id);
	return FALSE;
#endif
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_get_value_of_ipv6multicastaddr

DESCRIPTION:
	cli2_types_get_value_of_ipv6multicastaddr

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_value_of_ipv6multicastaddr (
	IN const I8_T *ipv6_str,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{
#if 0
	UI32_T *ip6_addr;
	BOOL_T ret;

	ret = cli2_types_get_value_of_ipv6addr(ipv6_str, lparam, rparam, value);

	if (ret)
	{
		ip6_addr = value;
		/* check to see if it is a multicast address */
		if ((ip6_addr[0] & 0xFF000000u) != 0xFF000000u)
		{
			return FALSE;
		}
	}

	return ret;
#else
	CLI_DBG_NOTSUPPORTED(l_mdl_id);
	return FALSE;
#endif
}



/**************************************************************************
FUNCTION NAME:
	cli2_alias_merge_ipv6multicastaddrchain

DESCRIPTION:
	cli2_alias_merge_ipv6multicastaddrchain

INPUT:
	pArray			: value chain need to merge

OUTPUT:
	pArray			: value chain need to merge

RETURN:

NOTES:

HISTORY:

**************************************************************************/
static void cli2_alias_merge_ipv6multicastaddrchain(IN OUT CLI_VALUEARRAY_T *pArray)
{
#if 0
	LA3_IP6ADDR *pBegin;
	UI32_T idx, cnt;
	UI32_T i;
	LA3_IP6ADDR *range1, *range2;

	if (pArray == NULL || pArray->count < 2)
	{
		return;
	}

	cnt = pArray->count;
	pBegin = (LA3_IP6ADDR *)&pArray->valueBegin;
	idx = 0;

	while (idx < (cnt - 1));
	{
		range1 = pBegin + idx * 2;

		i = idx + 1;
		while (i < cnt)
		{
			range2 = pBegin + i * 2;
			if (((memcmp(range1, range2, sizeof(LA3_IP6ADDR)) <= 0 )
				&& (memcmp(range1 + 1, range2, sizeof(LA3_IP6ADDR)) >= 0))
				||
				((memcmp(range1, range2, sizeof(LA3_IP6ADDR)) >= 0)
					&& (memcmp(range1, range2 + 1, sizeof(LA3_IP6ADDR)) <= 0)))
			{
				if (memcmp(range1, range2,  sizeof(LA3_IP6ADDR)) >= 0)
				{
					memcpy(range1, range2,  sizeof(LA3_IP6ADDR));
				}

				if (memcmp(range1 + 1, range2 + 1,  sizeof(LA3_IP6ADDR)) < 0)
				{
					memcpy(range1 + 1, range2 + 1,  sizeof(LA3_IP6ADDR));
				}

				memmove(range2, range2 + 2, (cnt - i - 1) * sizeof(LA3_IP6ADDR) * 2);
				pArray->count--;
				cnt--;
				i = idx + 1;
			}
			else
			{
				i++;
			}
		}
		idx++;
	}
#else
	CLI_DBG_NOTSUPPORTED(l_mdl_id);
	return;
#endif
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_get_value_of_ipv6multicastaddrchain

DESCRIPTION:
	cli2_types_get_value_of_ipv6multicastaddrchain

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_value_of_ipv6multicastaddrchain(
	IN const I8_T *start,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{
#if 0
	/*ipv6 address -> xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx */
	I8_T ipv6addr[40];
	UI32_T used_size, i;
	LA3_IP6ADDR small, large;
	CLI_VALUEARRAY_T *ipv6_chain;
	LA3_IP6ADDR *value_begin;

	/* the alloc size is CLI_API_MAX_CMD_LEN
	 * in function CLI_TYPES_GetValue() and CLI_TYPES_Get_CurrentHelp()
	 */
	memset(value, 0, CLI_API_MAX_CMD_LEN);
	ipv6_chain = value;
	ipv6_chain->type = CLI_TYPES_IPMULTICASTADDRCHAIN;
	ipv6_chain->count = 0;
	used_size = sizeof(CLI_VALUEARRAY_T);
	value_begin = (LA3_IP6ADDR *)&ipv6_chain->valueBegin;

	while (*start)
	{
		/* check the used buffer size */
		if ((used_size += (sizeof(LA3_IP6ADDR) * 2)) > CLI_API_MAX_CMD_LEN)
		{
			return FALSE;
		}

		/* get left range */
		memset(ipv6addr, 0, sizeof(ipv6addr));
		for (i = 0; i < 39; i++)
		{
			if ((*start == '\0') || *start == '-' || *start == ',')
			{
				break;
			}
			ipv6addr[i] = *start++;
		}
		if (cli2_types_get_value_of_ipv6multicastaddr(ipv6addr, lparam, rparam, &small) == FALSE)
		{
			return FALSE;
		}

		if (*start == '-')
		{
			/* get right range */
			start++;
			memset(ipv6addr, 0, sizeof(ipv6addr));
			for (i = 0; i < 39; i++)
			{
				if ((*start == '\0') || *start == ',')
				{
					break;
				}
				ipv6addr[i] = *start++;
			}
			if (cli2_types_get_value_of_ipv6multicastaddr(ipv6addr, lparam, rparam, &large) == FALSE)
			{
				return FALSE;
			}
		}
		else
		{
			large = small;
		}

		for (i = 0; i < 4; i++)
		{
			if (small.la3_ip6_addr_u.u4WordAddr[i] > large.la3_ip6_addr_u.u4WordAddr[i])
			{
				return FALSE;
			}
		}

		*value_begin++ = small;
		*value_begin++ = large;
		ipv6_chain->count++;

		if (*start)
		{
			if (*start != ',')
			{
				return FALSE;
			}
			start++;
		}
	}

	if (ipv6_chain->count == 0)
	{
		return FALSE;
	}

	cli2_alias_merge_ipv6multicastaddrchain(ipv6_chain);

	return TRUE;
#else
	CLI_VALUEARRAY_T *ipv6_chain = NULL;
	cli2_alias_merge_ipv6multicastaddrchain(ipv6_chain);
	CLI_DBG_NOTSUPPORTED(l_mdl_id);
	return FALSE;
#endif
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_prt_value_of_ipv6multicastaddrchain

DESCRIPTION:
	cli2_types_prt_value_of_ipv6multicastaddrchain

INPUT:
	value			: input parameter value

OUTPUT:
	buf				: storing parameter string

RETURN:
	the length of the parameter string

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_prt_value_of_ipv6multicastaddrchain(
	OUT I8_T *buf,
	IN void *value)
{
#if 0
	CLI_VALUEARRAY_T *pArray;
	LA3_IP6ADDR *pBegin;
	UI32_T cnt;
	I8_T *current;
	LA3_IP6ADDR *range;
	UI32_T i;

	pArray = (CLI_VALUEARRAY_T *)value;
	pBegin = (LA3_IP6ADDR *)&pArray->valueBegin;
	cnt = pArray->count;
	current = buf;

	for (i = 0; i < cnt; i++)
	{
		range = pBegin + i * 2;
		current += sprintf(current, "%v", range);
		if (memcmp(range + 1, range, sizeof(LA3_IP6ADDR)) > 0)
		{
			*(current++) = '-';
			current += sprintf(current, "%v", (range + 1));
		}

		if (i != cnt - 1)
		{
			/* more value exists */
			*(current++) = ',';
		}
	}
	*(current) = VT_NULL;

	return (UI32_T)current - (UI32_T)buf;
#else
	//CLI_DBG_NOTSUPPORTED(l_mdl_id);
	return FALSE;
#endif
}



/**************************************************************************
FUNCTION NAME:
	get_range_frameportnum

DESCRIPTION:
	get_range_frameportnum

INPUT:
	str				: begining of input range string
	end				: end of input range string

OUTPUT:
	lparam			: small value
	rparam			: large value

RETURN:
	TURE			: get range success
	FALSE			: input range string is error

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T get_range_frameportnum(
	IN const I8_T *str,
	IN const I8_T *end,
	IN OUT LPARAM *lparam,
	IN OUT RPARAM *rparam)
{
#if 0
	CLI_TYPE_INTERFACE_T *port_min;
	CLI_TYPE_INTERFACE_T *port_max;

	port_min = (CLI_TYPE_INTERFACE_T *)lparam;
	port_max = (CLI_TYPE_INTERFACE_T *)rparam;

	/* check if the range is null */
	if (str == NULL || end == NULL || *str == 0/*NULL*/ || *end == 0/*NULL*/ || str == end)
	{
		port_min->boxid = 1;
		port_min->portid = 1;
		port_max->boxid = MIB_CST_MAX_BOX_OF_STACK;
		port_max->portid = MIB_CST_MAX_PORT_OF_STACK_BOX;

		return TRUE;
	}

	port_min->boxid = (UI8_T)strtoul(str, (I8_T **)&str, 10);

	if (*str != CLI_ALIAS_PORT_SEPERATOR)
	{
		port_min->portid = port_min->boxid;
		if (ST_MASTER == ST_STACK_Get_Role())
		{
			port_min->boxid = ST_STACK_Get_MyBoxID();
		}
		else
		{
			port_min->boxid = ST_STACK_Get_MasterBoxID();
		}
	}
	else
	{
		str++; /* skip ':' and parse */
		port_min->portid = (UI8_T)strtoul(str, (I8_T **)&str, 10);
	}

	if (*str == CLI_ALIAS_PORT_RANGE_SEPERATOR)
	{
		port_max->boxid = (UI8_T)strtoul(str, (I8_T **)&str, 10);

		if (*str != CLI_ALIAS_PORT_SEPERATOR)
		{
			port_max->portid = port_max->boxid;
			if (ST_MASTER == ST_STACK_Get_Role())
			{
				port_max->boxid = ST_STACK_Get_MyBoxID();
			}
			else
			{
				port_max->boxid = ST_STACK_Get_MasterBoxID();
			}
		}
		else
		{
			str++; /* skip ':' and parse */
			port_max->portid = (UI8_T)strtoul(str, (I8_T **)&str, 10);
		}
	}
	else
	{
		port_max->boxid = port_min->boxid;
		port_max->portid = port_min->portid;
		port_min->boxid = 1;
		port_min->portid = 1;
	}

	if ((str != end)
		|| (port_min->boxid > port_max->boxid)
		|| ((port_min->boxid == port_max->boxid) && (port_min->portid > port_max->portid))
		|| (port_min->boxid < 1) || (port_max->boxid > MIB_CST_MAX_BOX_OF_STACK)
		|| (port_min->portid < 1) || (port_min->portid > MIB_CST_MAX_PORT_OF_STACK_BOX)
		|| (port_max->portid < 1) || (port_max->portid > MIB_CST_MAX_PORT_OF_STACK_BOX))
	{
		return FALSE;
	}

	return TRUE;
#else
	//CLI_DBG_NOTSUPPORTED(l_mdl_id);
	return FALSE;
#endif
}



/**************************************************************************
FUNCTION NAME:
	prt_range_frameportnum

DESCRIPTION:
	prt_range_frameportnum

INPUT:
	lparam			: small value
	rparam			: large value

OUTPUT:
	buf				: storing range string

RETURN:
	the length of the range string

NOTES:

HISTORY:

**************************************************************************/
static I32_T prt_range_frameportnum(
	OUT I8_T *buf,
	IN LPARAM lparam,
	IN RPARAM rparam)
{
#if 0
	CLI_TYPE_INTERFACE_T *port_min;
	CLI_TYPE_INTERFACE_T *port_max;
	I32_T len;
	ST_SWITCH_MODE_T mode;

	port_min = (void *)&lparam;
	port_max = (void *)&rparam;

	len = 0;
	ST_STACK_Get_SwitchMode(&mode);

	/* left range */
	if (mode != ST_SWITCH_STANDALONE && port_min->boxid > 0 && port_min->boxid <= MIB_CST_MAX_BOX_OF_STACK)
	{
		len += sprintf(buf + len, "%u%c", port_min->boxid, CLI_ALIAS_PORT_SEPERATOR);
	}
	len += sprintf(buf + len, "%u%c", port_min->portid, CLI_ALIAS_PORT_RANGE_SEPERATOR);

	/* right range */
	if (mode != ST_SWITCH_STANDALONE && port_max->boxid > 0 && port_max->boxid <= MIB_CST_MAX_BOX_OF_STACK)
	{
		len += sprintf(buf + len, "%u%c", port_max->boxid, CLI_ALIAS_PORT_SEPERATOR);
	}
	len += sprintf(buf + len, "%u", port_max->portid);
	buf[len] = 0;

	return len;
#else
	UNUSED(buf);
	UNUSED(lparam);
	UNUSED(rparam);

	return 0;
#endif
}



/**************************************************************************
FUNCTION NAME:
	get_value_frameportnum

DESCRIPTION:
	get_value_frameportnum

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T get_value_frameportnum(
	IN const I8_T *str,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{
	CLI_DBG_ENTER(l_mdl_id);
	CLI_DBG_CPL(l_mdl_id, "frame port: %s\r\n", str);

#if 1
	I8_T 					*cur_pos = (I8_T *)str;
	cli_pid_t				port_cli;
	//CLI_TYPE_INTERFACE_T 	*min;
	//CLI_TYPE_INTERFACE_T 	*max;

	//min = (void *)&lparam;
	//max = (void *)&rparam;

	CLI_DBG_CPL(l_mdl_id, "cur port str: %s\r\n", cur_pos);
	/* check port type char */
	if (IS_SNI_PORT_TYPE_CH(*cur_pos))
	{
		port_cli.port_type = CLI_PORT_TYPE_SNI;
	}
	else if (IS_PON_PORT_TYPE_CH(*cur_pos))
	{
		port_cli.port_type = CLI_PORT_TYPE_PON;
	}
	else
	{
		CLI_DBG_LEAVE(l_mdl_id);
		return FALSE;
	}
	CLI_DBG_CPL(l_mdl_id, "port type=%u\r\n", port_cli.port_type);

	/* skip '/' and parse */
	cur_pos++; 

	CLI_DBG_CPL(l_mdl_id, "cur port str: %s\r\n", cur_pos);
	/* get slot id */
#if 0
	if (UTL_EXTPRT_TransStrToUI32(&str, 10, &slot_id) == FALSE)
#else
	cur_pos = utili_str_to_uint32((I8_T *)cur_pos, 10, &port_cli.slot_id);
	if (NULL == cur_pos)
#endif
	{
		CLI_DBG_LEAVE(l_mdl_id);
		return FALSE;
	}
	CLI_DBG_CPL(l_mdl_id, "slot id=%u\r\n", port_cli.slot_id);

	CLI_DBG_CPL(l_mdl_id, "cur port str: %s\r\n", cur_pos);
	if (*cur_pos != CLI_ALIAS_PORT_SEPERATOR)
	{
		CLI_DBG_LEAVE(l_mdl_id);
		return FALSE;
	}

	/* skip '/' and parse */
	cur_pos++; 

	CLI_DBG_CPL(l_mdl_id, "cur port str: %s\r\n", cur_pos);
	/* get port id */
#if 0
	if (UTL_EXTPRT_TransStrToUI32(&cur_pos, 10, &port_id) == FALSE)
#else
	cur_pos = utili_str_to_uint32((I8_T *)cur_pos, 10, &port_cli.port_id);
	if (NULL == cur_pos)
#endif
	{
		CLI_DBG_LEAVE(l_mdl_id);
		return FALSE;
	}
	CLI_DBG_CPL(l_mdl_id, "port id=%u\r\n", port_cli.port_id);

	CLI_DBG_CPL(l_mdl_id, "cur port str: %s\r\n", cur_pos);
	/* check slot & port id */
	//if ((*cur_pos != '\0') || (slot_id < min->boxid) || (slot_id > max->boxid) || (port_id < min->portid) || (port_id > max->portid))
	//{
	//	return FALSE;
	//}

	MEMCPY(value, &port_cli, sizeof(port_cli));

	return TRUE;
#else
	CLI_DBG_NOTSUPPORTED(l_mdl_id);
	return FALSE;
#endif
}



/**************************************************************************
FUNCTION NAME:
	prt_value_frameportnum

DESCRIPTION:
	prt_value_frameportnum

INPUT:
	value			: input parameter value

OUTPUT:
	buf				: storing parameter string

RETURN:
	the length of the parameter string

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T prt_value_frameportnum(
	OUT I8_T *buf,
	IN void *value)
{
#if 0
	return sprintf(buf, "%p", *(UI32_T *)value);
#else
	//CLI_DBG_NOTSUPPORTED(l_mdl_id);
	return FALSE;
#endif
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_get_value_of_stackingPortList

DESCRIPTION:
	cli2_types_get_value_of_stackingPortList

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:
	A list of port values is a group of digit number seperated by ','
	and '-'. Ex: "m:x-m:y,m:z,m:a,m:b-m:c" means integer x to y, z, a, b to c,
 	include x,y,b,and c. You should not include white spaces inside the
 	impresentation.

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_value_of_stackingPortList(
	IN const I8_T *str,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{
#if 0
	CLI_TYPE_INTERFACE_T *lvalue;
	CLI_TYPE_INTERFACE_T *rvalue;
	UI32_T i;
	UI32_T min_port, max_port;
	UI32_T small_logicalPort, large_logicalPort;
	UI8_T small_boxid, large_boxid;
	UI32_T small_localPort, large_localPort;
	ST_PORTLIST_T portlist, all_network;
	ST_UTL_BOX_PORT_INFO_T info;

	lvalue = (void *)&lparam;
	rvalue = (void *)&rparam;

	memset(portlist, 0, sizeof(ST_PORTLIST_T));
	memset(all_network, 0, sizeof(ST_PORTLIST_T));

	ST_UTL_Portlist_Get(ST_UTL_TYPE_EXIST_NETWORK, all_network);

	if ((ST_UTL_Translate_LocalToLogicalByUnit(lvalue->boxid, lvalue->portid, &min_port) == FALSE)
		|| (ST_UTL_Translate_LocalToLogicalByUnit(rvalue->boxid, rvalue->portid, &max_port) == FALSE))
	{
		return FALSE;
	}

	while (*str)
	{
		small_boxid = (UI8_T)strtoul(str, (I8_T **)&str, 10);

		if (*str != CLI_ALIAS_PORT_SEPERATOR)
		{
			small_localPort = small_boxid;
			if (ST_MASTER == ST_STACK_Get_Role())
			{
				small_boxid = ST_STACK_Get_MyBoxID();
			}
			else
			{
				small_boxid = ST_STACK_Get_MasterBoxID();
			}
		}
		else
		{
			str++; /* skip ':' and parse */
			small_localPort = strtoul(str, (I8_T **)&str, 10);
		}
		if (ST_UTL_Translate_LocalToLogicalByUnit(small_boxid, small_localPort, &small_logicalPort) == FALSE)
		{
			return FALSE;
		}
		else
		{
			if (ST_UTL_Get_Unit_StackInfo((UI8_T)small_boxid, &info) == FALSE)
			{
				return FALSE;
			}
			else
			{
				if (!ST_PORTMAP_Is_PortSet(all_network, small_logicalPort))
				{
					return FALSE;
				}
			}
		}

		if (*str == '-')
		{
			str++;
			if (*str == '*')
			{
				/* for Ex 3:1-* */
				str++;
				large_logicalPort = max_port;
			}
			else
			{
				large_boxid = (UI8_T)strtoul(str, (I8_T **)&str, 10);

				if (*str != CLI_ALIAS_PORT_SEPERATOR)
				{
					/* for Ex 3:1-17 */
					large_localPort = large_boxid;
					large_boxid = small_boxid;
				}
				else
				{
					str++; /* skip ':' and parse */
					if (*str == '*')
					{
						/* for Ex 3:1-4:* */
						str++;
						if (large_boxid == rvalue->boxid)
						{
							large_localPort = rvalue->portid;
						}
						else
						{
							large_localPort = MIB_CST_MAX_PORT_OF_STACK_BOX;
						}
					}
					else
					{
						large_localPort = strtoul(str, (I8_T **)&str, 10);
					}
				}
				if (ST_UTL_Translate_LocalToLogicalByUnit(large_boxid, large_localPort, &large_logicalPort) == FALSE)
				{
					return FALSE;
				}
				else
				{
					if (ST_UTL_Get_Unit_StackInfo((UI8_T)large_boxid, &info) == FALSE)
					{
						return FALSE;
					}
					else
					{
						/* for the case 3:1-4:* the large logical port need not to check */
						if (*(str - 1) != '*')
						{
							if (!ST_PORTMAP_Is_PortSet(all_network, large_logicalPort))
							{
								return FALSE;
							}
						}
					}
				}
			}
		}
		else
		{
			large_logicalPort = small_logicalPort;
		}

		if (small_logicalPort > large_logicalPort
			|| small_logicalPort < min_port
			|| large_logicalPort > max_port)
		{
			return FALSE;
		}
		else
		{
			for (i = small_logicalPort; i <= large_logicalPort; i++)
			{
				ST_PORTMAP_Set_Port(portlist, i);
			}
		}

		if (*str)
		{
			if (*str != ',')
			{
				return FALSE;
			}
			/* skip the ',' */
			str++;
		}
	}

	/* mask out sio and non-exist ports */
	ST_PORTMAP_And_2List(portlist, portlist, all_network);
	memcpy(value, portlist, sizeof(ST_PORTLIST_T));

	return TRUE;
#else
	//CLI_DBG_NOTSUPPORTED(l_mdl_id);
	return FALSE;
#endif
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_prt_value_of_stackingPortList

DESCRIPTION:
	cli2_types_prt_value_of_stackingPortList

INPUT:
	value			: input parameter value

OUTPUT:
	buf				: storing parameter string

RETURN:
	the length of the parameter string

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_prt_value_of_stackingPortList (
	OUT I8_T *buf,
	IN void *value)
{
#if 0
	return sprintf(buf, "%k", value);
#else
	//CLI_DBG_NOTSUPPORTED(l_mdl_id);
	return FALSE;
#endif
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_get_range_of_standalonePortList

DESCRIPTION:
	cli2_types_get_range_of_standalonePortList

INPUT:
	str				: begining of input range string
	end				: end of input range string

OUTPUT:
	lparam			: small value
	rparam			: large value

RETURN:
	TURE			: get range success
	FALSE			: input range string is error

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_range_of_standalonePortList(
	IN const I8_T *str,
	IN const I8_T *end,
	IN OUT LPARAM *lparam,
	IN OUT RPARAM *rparam)
{
	I8_T *cur_pos;

	/* check if the range is null */
	if (str == NULL || end == NULL || *str == '\0'/*NULL*/ || *end == '\0'/*NULL*/ || str == end)
	{
		*lparam = 1;
		*rparam = MIB_CST_MAX_PORT_OF_STACK_BOX;
		return TRUE;
	}

	cur_pos = (I8_T *)str;
#if 0
	if (UTL_EXTPRT_TransStrToUI32(&str, 10, lparam) == FALSE)
#else
	cur_pos = utili_str_to_uint32((I8_T *)cur_pos, 10, lparam);
	if (NULL == cur_pos)
#endif
	{
		return FALSE;
	}

	if (*cur_pos == '-') // range string is like "lparam-rparam"
	{
		cur_pos++;
#if 0
		if (UTL_EXTPRT_TransStrToUI32(&str, 10, rparam) == FALSE)
#else
		cur_pos = utili_str_to_uint32((I8_T *)cur_pos, 10, rparam);
		if (NULL == cur_pos)
#endif
		{
			return FALSE;
		}
	}
	else // only rparam in range string
	{
		*rparam = *lparam;
		*lparam = 1;
	}

	if ((cur_pos != end) || (*lparam > *rparam))
	{
		return FALSE;
	}

	return TRUE;
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_get_value_of_standalonePortList

DESCRIPTION:
	cli2_types_get_value_of_standalonePortList

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_value_of_standalonePortList(
	IN const I8_T *str,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{
	UI32_T 		i, port_id = 0;
	UI16_T 		port_list[MIB_CST_MAX_PORT_OF_STACK_BOX];
	PORTLIST_T 	port_map;

	memset(port_list, 0, sizeof(port_list));
	memset(port_map, 0, sizeof(port_map));

	if (utili_str_to_list((I8_T *)str, port_list, MIB_CST_MAX_PORT_OF_STACK_BOX) <= 0)
	{
		return FALSE;
	}

	//while (UTL_PORTMAP_Get_NextPort(port_list, &port_id))
	for (i = 0; (i < MIB_CST_MAX_PORT_OF_STACK_BOX) && (0 != port_list[i]); i++)
	{
		if ((port_list[i] < lparam) || (port_list[i] > rparam))
		{
			return FALSE;
		}

		port_id = port_list[i];
		utili_bit_set_bit((bc_uint8*)&port_map, port_id, sizeof(port_map));
	}

	memcpy(value, &port_map, sizeof(port_map));
	return TRUE;
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_prt_value_of_standalonePortList

DESCRIPTION:
	cli2_types_prt_value_of_standalonePortList

INPUT:
	value			: input parameter value

OUTPUT:
	buf				: storing parameter string

RETURN:
	the length of the parameter string

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_prt_value_of_standalonePortList(
	OUT I8_T *buf,
	IN void *value)
{
#if 0
	return sprintf(buf, "%T", value);
#else
	//CLI_DBG_NOTSUPPORTED(l_mdl_id);
	return FALSE;
#endif
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_get_range_of_ui32

DESCRIPTION:
	cli2_types_get_range_of_ui32s

INPUT:
	str				: begining of input range string
	end				: end of input range string

OUTPUT:
	lparam			: small value
	rparam			: large value

RETURN:
	TURE			: get range success
	FALSE			: input range string is error

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_range_of_ui32(
	IN const I8_T *str,
	IN const I8_T *end,
	IN OUT LPARAM *lparam,
	IN OUT RPARAM *rparam)
{
	I8_T *cur_pos;

	if ((str == NULL) || (str >= end)) // nothing in range string
	{
		return FALSE;
	}

	cur_pos = (I8_T *)str;
	
	/* skip the first '+' */
	if (*cur_pos == '+')
	{
		cur_pos++;
	}

#if 0
	if (UTL_EXTPRT_TransStrToUI32(&str, 10, lparam) == FALSE)
#else
	cur_pos = utili_str_to_uint32((I8_T *)cur_pos, 10, lparam);
	if (NULL == cur_pos)
#endif
	{
		return FALSE;
	}

	if (*cur_pos == '-') // range string is like "lparam-rparam"
	{
		cur_pos++;
		/* skip the first '+' */
		if (*cur_pos == '+')
		{
			cur_pos++;
		}

#if 0
		if (UTL_EXTPRT_TransStrToUI32(&str, 10, rparam) == FALSE)
#else
		cur_pos = utili_str_to_uint32((I8_T *)cur_pos, 10, rparam);
		if (NULL == cur_pos)
#endif
		{
			return FALSE;
		}
	}
	else // only rparam in range string
	{
		*rparam = *lparam;
		*lparam = 0;
	}

	if ((cur_pos != end) || (*lparam > *rparam))
	{
		return FALSE;
	}

	return TRUE;
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_prt_range_of_ui32

DESCRIPTION:
	cli2_types_prt_range_of_ui32

INPUT:
	lparam			: small value
	rparam			: large value

OUTPUT:
	buf				: storing range string

RETURN:
	the length of the range string

NOTES:

HISTORY:

**************************************************************************/
static I32_T cli2_types_prt_range_of_ui32(
	OUT I8_T *buf,
	IN LPARAM lparam,
	IN RPARAM rparam)
{
	return sprintf(buf, "%u-%u", lparam, rparam);
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_get_value_of_ui32

DESCRIPTION:
	cli2_types_get_value_of_ui32

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_value_of_ui32(
	IN const I8_T *str,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{
	UI32_T 		ret_value;
	I8_T 		*cur_pos;

	cur_pos = (I8_T *)str;

	/* skip the first '+' */
	if (*cur_pos == '+')
	{
		cur_pos++;
	}

#if 0
	if (UTL_EXTPRT_TransStrToUI32(&trans_str, 10, &ret_value))
#else
	cur_pos = utili_str_to_uint32((I8_T *)cur_pos, 10, &ret_value);
	if (NULL == cur_pos)
#endif
	{
		return FALSE;
	}

	if ((cur_pos == str) || (*cur_pos != '\0') || (ret_value < lparam) || (ret_value > rparam))
	{
		return FALSE;
	}

	*(UI32_T *)value = ret_value;
	return TRUE;
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_get_range_of_i32

DESCRIPTION:
	cli2_types_get_range_of_i32

INPUT:
	str				: begining of input range string
	end				: end of input range string

OUTPUT:
	lparam			: small value
	rparam			: large value

RETURN:
	TURE			: get range success
	FALSE			: input range string is error

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_range_of_i32(
	IN const I8_T *str,
	IN const I8_T *end,
	IN OUT LPARAM *lparam,
	IN OUT RPARAM *rparam)
{
	CLI_DBG_ENTER(l_mdl_id);
	CLI_DBG_CPL(l_mdl_id, "str: %s\r\n", str);
	
	I32_T 	lvalue;
	I32_T 	rvalue;
	BOOL_T 	neg_flag = FALSE;
	I8_T 	*cur_pos;

	if ((str == NULL) || (str >= end)) // nothing in range string
	{
		CLI_DBG_LEAVE(l_mdl_id);
		return FALSE;
	}

	cur_pos = (I8_T *)str;
	CLI_DBG_CPL(l_mdl_id, "cur port str: %s\r\n", cur_pos);
	
	/* skip the firt '+' */
	if (*cur_pos == '+')
	{
		cur_pos++;
	}
	/* get the sign */
	else if (*cur_pos == '-')
	{
		neg_flag = TRUE;
		cur_pos++;
	}
	CLI_DBG_CPL(l_mdl_id, "cur port str: %s\r\n", cur_pos);

#if 0
	if ((UTL_EXTPRT_TransStrToUI32(&str, 10, &lvalue) == FALSE) || (lvalue < 0))
#else
	cur_pos = utili_str_to_uint32((I8_T *)cur_pos, 10, (UI32_T *)&lvalue);
	CLI_DBG_CPL(l_mdl_id, "cur port str: %s\r\n", cur_pos);
	if ((NULL == cur_pos) || (lvalue < 0))
#endif
	{
		CLI_DBG_LEAVE(l_mdl_id);
		return FALSE;
	}

	if (neg_flag)
	{
		lvalue = (-1) * lvalue;
		neg_flag = FALSE;
	}

	CLI_DBG_CPL(l_mdl_id, "cur port str: %s\r\n", cur_pos);
	if (*cur_pos == '-')
	{
		cur_pos++;
		CLI_DBG_CPL(l_mdl_id, "cur port str: %s\r\n", cur_pos);
		/* skip the firt '+' */
		if (*cur_pos == '+')
		{
			cur_pos++;
		}
		/* get the sign */
		else if (*cur_pos == '-')
		{
			neg_flag = TRUE;
			cur_pos++;
		}
		CLI_DBG_CPL(l_mdl_id, "cur port str: %s\r\n", cur_pos);

#if 0
		if ((UTL_EXTPRT_TransStrToUI32(&str, 10, &rvalue) == FALSE) || (rvalue < 0))
#else
		cur_pos = utili_str_to_uint32((I8_T *)cur_pos, 10, (UI32_T *)&rvalue);
		CLI_DBG_CPL(l_mdl_id, "cur port str: %s\r\n", cur_pos);
		if ((NULL == cur_pos) || (rvalue < 0))
#endif
		{
			CLI_DBG_LEAVE(l_mdl_id);
			return FALSE;
		}

		if (neg_flag)
		{
			rvalue = (-1) * rvalue;
			neg_flag = FALSE;
		}
	}
	else
	{
		rvalue = lvalue;
		lvalue = 0;
	}

	CLI_DBG_CPL(l_mdl_id, "cur port str: %s\r\n", cur_pos);
	if ((cur_pos != end) || (lvalue > rvalue))
	{
		CLI_DBG_LEAVE(l_mdl_id);
		return FALSE;
	}

	*lparam = (LPARAM)lvalue;
	*rparam = (RPARAM)rvalue;

	CLI_DBG_LEAVE(l_mdl_id);
	return TRUE;
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_prt_range_of_i32

DESCRIPTION:
	cli2_types_prt_range_of_i32

INPUT:
	lparam			: small value
	rparam			: large value

OUTPUT:
	buf				: storing range string

RETURN:
	the length of the range string

NOTES:

HISTORY:

**************************************************************************/
static I32_T cli2_types_prt_range_of_i32(
	OUT I8_T *buf,
	IN LPARAM lparam,
	IN RPARAM rparam)
{
	return sprintf(buf, "%i-%i", (I32_T)lparam, (I32_T)rparam);
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_get_value_of_i32

DESCRIPTION:
	cli2_types_get_value_of_i32

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_value_of_i32(
	IN const I8_T *str,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{
	CLI_DBG_ENTER(l_mdl_id);

	I32_T 	ret_value;
	I32_T 	lvalue;
	I32_T 	rvalue;
	BOOL_T 	neg_flag = FALSE;
	I8_T 	*cur_pos;

	lvalue = (I32_T)lparam;
	rvalue = (I32_T)rparam;

	cur_pos = (I8_T *)str;
	
	/* skip the first '+' */
	if (*cur_pos == '+')
	{
		cur_pos++;
	}
	else if (*cur_pos == '-')
	{
		neg_flag = TRUE;
		cur_pos++;
	}

#if 0
	if (UTL_EXTPRT_TransStrToUI32(&trans_str, 10, &ret_value))
#else
	cur_pos = utili_str_to_uint32((I8_T *)cur_pos, 10, (UI32_T *)&ret_value);
	CLI_DBG_CPL(l_mdl_id, "after get:str=\"%s\",cur_pos=\"%s\",ret_value=%d\r\n", str, cur_pos, ret_value);
	if (NULL == cur_pos)
#endif
	{
		CLI_DBG_LEAVE(l_mdl_id);
		return FALSE;
	}

	if ((cur_pos == str) || (*cur_pos != '\0') || (ret_value < 0))
	{
		CLI_DBG_LEAVE(l_mdl_id);
		return FALSE;
	}

	if (neg_flag)
	{
		ret_value = (-1) * ret_value;
	}

	if ((ret_value < lvalue) || (ret_value > rvalue))
	{
		CLI_DBG_LEAVE(l_mdl_id);
		return FALSE;
	}

	*(I32_T *)value = ret_value;
	CLI_DBG_LEAVE(l_mdl_id);
	return TRUE;
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_prt_value_of_i32

DESCRIPTION:
	cli2_types_prt_value_of_i32

INPUT:
	value			: input parameter value

OUTPUT:
	buf				: storing parameter string

RETURN:
	the length of the parameter string

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_prt_value_of_i32(
	OUT I8_T *buf,
	IN void *value)
{
	return sprintf(buf, "%d", *(I32_T *)value);
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_cmp_value_of_i32

DESCRIPTION:
	cli2_types_cmp_value_of_i32

INPUT:
	ptr1				: parameter value
	ptr2				: parameter value

OUTPUT:

RETURN:
	1				: ptr1 value > ptr2 value
	0				: ptr1 value == ptr2 value
	-1				: ptr1 value < ptr2 value

NOTES:

HISTORY:

**************************************************************************/
static I32_T cli2_types_cmp_value_of_i32(IN void *ptr1, IN void *ptr2)
{
	I32_T *left;
	I32_T *right;

	left = ptr1;
	right = ptr2;

	if (left < right)
	{
		return -1;
	}
	else if (left == right)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_get_value_of_ui32chain

DESCRIPTION:
	cli2_types_get_value_of_ui32chain

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_value_of_ui32chain(
	IN const I8_T *str,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{
	UI32_T used_size;
	UI32_T small, large;
	I8_T *start;
	CLI_VALUEARRAY_T *ui32_chain;
	UI32_T *value_begin;

	/* the alloc size is CLI_API_MAX_CMD_LEN
	 * in function CLI_TYPES_GetValue() and CLI_TYPES_Get_CurrentHelp()
	 */
	memset(value, 0, CLI_API_MAX_CMD_LEN);
	ui32_chain = value;
	ui32_chain->type = CLI_TYPES_UI32CHAIN;
	ui32_chain->count = 0;
	used_size = sizeof(CLI_VALUEARRAY_T);
	value_begin = (UI32_T *)&ui32_chain->valueBegin;
	start = (I8_T *)str;

	while (*start)
	{
		/* check the used buffer size */
		if ((used_size += (sizeof(UI32_T) * 2)) > CLI_API_MAX_CMD_LEN)
		{
			return FALSE;
		}

		/* get left range */
		small = strtoul(start, &start, 10);

		if (*start == '-')
		{
			/* get right range */
			start++;
			large = strtoul(start, &start, 10);
		}
		else
		{
			large = small;
		}

		if ((small > large) || (small < lparam) || (large > rparam))
		{
			return FALSE;
		}

		*value_begin++ = small;
		*value_begin++ = large;
		ui32_chain->count++;

		if (*start)
		{
			if (*start != ',' || isdigit(*(start + 1)) == 0)
			{
				return FALSE;
			}

			start++;
		}
	}

	if (ui32_chain->count == 0)
	{
		return FALSE;
	}

	return TRUE;
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_prt_value_of_ui32chain

DESCRIPTION:
	cli2_types_prt_value_of_ui32chain

INPUT:
	value			: input parameter value

OUTPUT:
	buf				: storing parameter string

RETURN:
	the length of the parameter string

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_prt_value_of_ui32chain(
	OUT I8_T *buf,
	IN void *value)
{
	CLI_VALUEARRAY_T *ui32_chain;
	I32_T i;
	I32_T small;
	I32_T large;
	I32_T *value_begin;
	I8_T *temp_obuf;

	ui32_chain = value;
	value_begin = (I32_T *)&ui32_chain->valueBegin;
	temp_obuf = buf;

	for (i = 0; i < ui32_chain->count; i ++)
	{
		small = *value_begin++;
		large = *value_begin++;
		if (small == large)
		{
			temp_obuf += sprintf(temp_obuf, "%d", small);
		}
		else
		{
			temp_obuf += sprintf(temp_obuf, "%d-%d", small, large);
		}

		if ((i + 1) < ui32_chain->count)
		{
			temp_obuf += sprintf(temp_obuf, ",");
		}
	}

	return (temp_obuf - buf);
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_get_value_of_intlist

DESCRIPTION:
	cli2_types_get_value_of_intlist

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_value_of_intlist(
	IN const I8_T *str,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{
	UI32_T l_value;
	UI32_T r_value;
	UI32_T max_value;
	I8_T *start;
	I32_T j;

	memset(value, 0, sizeof(CLI_API_INTLIST_T));	 /* Init all vlans */
	max_value = sizeof(CLI_API_INTLIST_T) * 8;
	start = (I8_T *)str;
	while (*start)
	{
		/* get left range */
		l_value = strtoul(start, &start, 10);

		if (*start == '-')
		{
			/* get right range */
			start++;
			r_value = strtoul(start, &start, 10);
		}
		else
		{
			r_value = l_value;
		}

		if ((l_value > r_value) || (l_value < lparam) || (r_value > rparam)	|| (r_value >= max_value))
		{
			return FALSE;
		}

		for (j = l_value; j <= r_value; j++)
		{
			//UTL_BITMAP_Set_Bit(value, j, sizeof(CLI_API_INTLIST_T));
			utili_bit_set_bit(value, j, sizeof(CLI_API_INTLIST_T));
		}

		if (*start)
		{
			if (*start != ',')
			{
				return FALSE;
			}
			start++;
		}
	}

	return TRUE;
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_prt_value_of_intlist

DESCRIPTION:
	cli2_types_prt_value_of_intlist

INPUT:
	value			: input parameter value

OUTPUT:
	buf				: storing parameter string

RETURN:
	the length of the parameter string

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_prt_value_of_intlist(
	OUT I8_T *buf,
	IN void *value)
{
	I32_T i;
	I32_T lvalue; // start vlan id
	I32_T rvalue; // end vlan id
	I8_T *temp_obuf;
	UI8_T *intlist;

	temp_obuf = buf;
	intlist = value;
	lvalue = -1;

	for (i = 1; i <= sizeof(CLI_API_INTLIST_T)*sizeof(UI8_T); i++)
	{
		//if (UTL_BITMAP_Is_BitSet (intlist, i, sizeof(CLI_API_INTLIST_T)))
		if (utili_bit_is_bitset(intlist, i, sizeof(CLI_API_INTLIST_T)))
		{
			if (lvalue == -1)
			{
				lvalue = i;
			}
		}
		else
		{
			if (lvalue > 0)
			{
				rvalue = i - 1;
				if (lvalue == rvalue)
				{
					temp_obuf +=  sprintf(temp_obuf, "%d,", lvalue);
				}
				else
				{
					temp_obuf += sprintf(temp_obuf, "%d-%d,", lvalue, rvalue);
				}
				lvalue = -1;
			}
		}
	}

	if (lvalue < 0)
	{
		if (temp_obuf > buf)
		{
			// discard the end ", "
			temp_obuf -= 1;
		}
	}
	else
	{
		rvalue = i - 1;
		if (lvalue == rvalue)
		{
			// a single value
			temp_obuf += sprintf(temp_obuf, "%d", lvalue);
		}
		else
		{
			// multiple value
			temp_obuf += sprintf(temp_obuf, "%d-%d", lvalue, rvalue);
		}
	}
	*(temp_obuf) = '\0';

	return (temp_obuf - buf);
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_get_value_of_vlanlist

DESCRIPTION:
	cli2_types_get_value_of_vlanlist

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_value_of_vlanlist(
	IN const I8_T *str,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{
	CLI_DBG_ENTER(l_mdl_id);

	UI32_T l_value;
	UI32_T r_value;
	I8_T *cur_pos;
	I32_T j;

	memset(value, 0, sizeof(VID_LIST_T));	 /* Init all vlans */
	cur_pos = (I8_T *)str;
	CLI_DBG_CPL(l_mdl_id, "cur port str: %s\r\n", cur_pos);
	while (*cur_pos)
	{
		/* get left range */
		l_value = strtoul(cur_pos, &cur_pos, 10);
		CLI_DBG_CPL(l_mdl_id, "cur port str: %s\r\n", cur_pos);

		if (*cur_pos == '-')
		{
			/* get right range */
			cur_pos++;
			r_value = strtol(cur_pos, &cur_pos, 10);
		}
		else
		{
			r_value = l_value;
		}

		CLI_DBG_CPL(l_mdl_id, "cur port str: %s\r\n", cur_pos);
		if ((l_value > r_value) || (l_value < lparam) || (r_value > rparam))
		{
			CLI_DBG_LEAVE(l_mdl_id);
			return FALSE;
		}

		for (j = l_value; j <= r_value; j++)
		{
			CLI_DBG_CPL(l_mdl_id, "cur port str: %s\r\n", cur_pos);
			//if (UTL_BITMAP_Set_Bit(value, j, sizeof(VID_LIST_T)) == FALSE)
			if (utili_bit_set_bit(value, j, sizeof(VID_LIST_T)) == FALSE)
			{
				CLI_DBG_LEAVE(l_mdl_id);
				return FALSE;
			}
		}

		CLI_DBG_CPL(l_mdl_id, "cur port str: %s\r\n", cur_pos);
		if (*cur_pos)
		{
			if (*cur_pos != ',')
			{
				CLI_DBG_LEAVE(l_mdl_id);
				return FALSE;
			}

			cur_pos++;
		}
	}

	CLI_DBG_LEAVE(l_mdl_id);
	return TRUE;
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_prt_value_of_vlanlist

DESCRIPTION:
	cli2_types_prt_value_of_vlanlist

INPUT:
	value			: input parameter value

OUTPUT:
	buf				: storing parameter string

RETURN:
	the length of the parameter string

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_prt_value_of_vlanlist(
	OUT I8_T *buf,
	IN void *value)
{
#if 0
	return sprintf(buf, "%W", value);
#else
	//CLI_DBG_NOTSUPPORTED(l_mdl_id);
	return FALSE;
#endif
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_get_value_of_vlanlist_name

DESCRIPTION:
	cli2_types_get_value_of_vlanlist_name

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_value_of_vlanlist_name (
	IN const I8_T *str,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{
	UI32_T l_value;
	UI32_T r_value;
	CLI_TYPE_VLANLIST_NAME_T *p_vlanlist_name;
	I8_T *cur_pos;
	I32_T j;

	memset(value, 0, sizeof(CLI_TYPE_VLANLIST_NAME_T));	 /* Init all vlans */
	p_vlanlist_name = value;
	cur_pos = (I8_T *)str;
	if (!isdigit(*cur_pos))
	{
		/* get vlan name */
		p_vlanlist_name->type = 1;
		while (*cur_pos && (*cur_pos != ' ') && (*cur_pos != '\t'))
		{
			p_vlanlist_name->vlanname[cur_pos - str] = *cur_pos;
			cur_pos++;
		}

		if ((cur_pos - str) >= CLI_TYPE_VLAN_NAME_MAX_LEN)
		{
			return FALSE;
		}
		p_vlanlist_name->vlanname[cur_pos - str] = '\0';
		// printf ("#############vlanname = <%s>", p_vlanlist_name->vlanname);
		return TRUE;
	}

	p_vlanlist_name->type = 0;
	while (*cur_pos)
	{
		/* get left range */
		l_value = strtoul(cur_pos, &cur_pos, 10);

		if (*cur_pos == '-')
		{
			/* get right range */
			cur_pos++;
			r_value = strtol(cur_pos, &cur_pos, 10);
		}
		else
		{
			r_value = l_value;
		}

		if ((l_value > r_value) || (l_value < lparam) || (r_value > rparam))
		{
			return FALSE;
		}

		for (j = l_value; j <= r_value; j++)
		{
			//UTL_BITMAP_Set_Bit((UI8_T *)&p_vlanlist_name->vlanlist, j, sizeof(VID_LIST_T));
			utili_bit_set_bit((UI8_T *)&p_vlanlist_name->vlanlist, j, sizeof(VID_LIST_T));
		}

		if (*cur_pos)
		{
			if (*cur_pos != ',')
			{
				return FALSE;
			}
			cur_pos++;
		}
	}

	return TRUE;
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_prt_value_of_vlanlist_name

DESCRIPTION:
	cli2_types_prt_value_of_vlanlist_name

INPUT:
	value			: input parameter value

OUTPUT:
	buf				: storing parameter string

RETURN:
	the length of the parameter string

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_prt_value_of_vlanlist_name(
	OUT I8_T *buf,
	IN void *value)
{
	CLI_TYPE_VLANLIST_NAME_T *p;
	I32_T ret = 0;

	p = value;
	if (p->type == 0)
	{
		//ret = sprintf(buf, "%V", p->vlanlist);
		//CLI_DBG_NOTSUPPORTED(l_mdl_id);
	}
	else
	{
		ret = sprintf(buf, "%s", p->vlanname);
	}

	return ret;
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_get_value_of_macaddr

DESCRIPTION:
	cli2_types_get_value_of_macaddr

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_value_of_macaddr (
	IN const I8_T *start,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value) // UI8_T mac[6]
{
// Format: xx-xx-xx-xx-xx-xx; xx:xx:xx:xx:xx:xx,xxxx.xxxx.xxxx, or x(repeat 12 times)
	UI8_T *mac;
	I8_T *tmp;
	I8_T delim; 				// delimiter for MAC address
	I32_T i;
	I8_T buf[3];

	if (lparam || rparam) {}

	mac = value;
	buf[2] = '\0';

	// xx-xx-xx-xx-xx-xx or xx:xx:xx:xx:xx:xx
	if ((*(start + 2) == ':') || (*(start + 2) == '-'))
	{
		delim = *(start + 2);
	}
	else if (*(start + 4) == '.')	// xxxx.xxxx.xxxx
	{
		delim = *(start + 4);
	}
	else						// x(repeat 12 times)
	{
		delim = '\0';
	}

	for (i = 0; i < 6; i++)
	{
		if ((isxdigit(start[0]) == 0) || (isxdigit(start[1]) == 0))
		{
			return FALSE;
		}

		memcpy(buf, start, 2);
		*mac++ = (I8_T) strtoul(buf, &tmp, 16);

		start += 2;
		switch (delim)
		{
			case '.':	   // xxxx.xxxx.xxxx
				if ((i != 1) && (i != 3))
				{
					break;
				}

			case '-':	   // xx-xx-xx-xx-xx-xx or xx:xx:xx:xx:xx:xx
			case ':':
				if (i < 5)
				{
					if (*start != delim)
					{
						return FALSE;
					}
					start++;
				}
				break;

			default:	   // x(repeat 12 times)
				break;
		}
	}

	if (*start != '\0')
	{
		return FALSE;
	}

	return TRUE;
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_get_value_of_mmacaddr

DESCRIPTION:
	cli2_types_get_value_of_mmacaddr

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_value_of_mmacaddr (
	IN const I8_T *start,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{
	BOOL_T ret;
	UI8_T fristByte;  /* for test unicast or multicast */

	ret = cli2_types_get_value_of_macaddr(start, lparam, rparam, value);

	if (ret)
	{
		fristByte = *(UI8_T *)value;

		if (fristByte != 1)
		{
			return FALSE;
		}
	}

	return ret;
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_get_value_of_umacaddr

DESCRIPTION:
	cli2_types_get_value_of_umacaddr

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_value_of_umacaddr (
	IN const I8_T *start,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{
	BOOL_T ret;
	UI8_T fristByte;  /* for test unicast or multicast */

	ret = cli2_types_get_value_of_macaddr(start, lparam, rparam, value);

	if (ret)
	{
		fristByte = *(UI8_T *)value;

		if (fristByte == 1)
		{
			return FALSE;
		}
	}

	return ret;
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_prt_value_of_macaddr

DESCRIPTION:
	cli2_types_prt_value_of_macaddr

INPUT:
	value			: input parameter value

OUTPUT:
	buf				: storing parameter string

RETURN:
	the length of the parameter string

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_prt_value_of_macaddr(
	OUT I8_T *buf,
	IN void *value)
{
#if 0
	return sprintf(buf, "%s", value);
#else
	//CLI_DBG_NOTSUPPORTED(l_mdl_id);
	return FALSE;
#endif
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_get_range_of_shorttime

DESCRIPTION:
	cli2_types_get_range_of_shorttime

INPUT:
	str				: begining of input range string
	end				: end of input range string

OUTPUT:
	lparam			: small value
	rparam			: large value

RETURN:
	TURE			: get range success
	FALSE			: input range string is error

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_range_of_shorttime (
	IN const I8_T *str,
	IN const I8_T *end,
	IN OUT LPARAM *lparam,
	IN OUT RPARAM *rparam)
{// format of range string hh:mm-hh:mm
	I8_T *p;
	CLI_TYPE_TIME_T *ltime;
	CLI_TYPE_TIME_T *rtime;

	if ((str == NULL) || (str >= end)) // nothing in range string
	{
		return FALSE;
	}

	// get time value
	ltime = (CLI_TYPE_TIME_T *)lparam;
	rtime = (CLI_TYPE_TIME_T *)rparam;
	ltime->hour = (UI8_T)strtol (str, &p, 10);
	p++; // skip ':'
	ltime->minute = (UI8_T)strtol (p, &p, 10);
	p++; // skip '-'
	rtime->hour = (UI8_T)strtol (p, &p, 10);
	p++; // skip ':'
	rtime->minute = (UI8_T)strtol (p, &p, 10);
	ltime->second = 0;
	rtime->second = 0;
	if (p > end)
	{
		return FALSE;
	}

	// check the validation of left time and right time
	if ((ltime->hour > 23) || (ltime->minute > 59)
		|| (rtime->hour > 23) || (rtime->minute > 59))
	{
		return FALSE;
	}

	if ((ltime->hour * 60 + ltime->minute) > (rtime->hour * 60 + rtime->minute))
	{ // left time > right time
		return FALSE;
	}

	return TRUE;
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_prt_range_of_shorttime

DESCRIPTION:
	cli2_types_prt_range_of_shorttime

INPUT:
	lparam			: small value
	rparam			: large value

OUTPUT:
	buf				: storing range string

RETURN:
	the length of the range string

NOTES:

HISTORY:

**************************************************************************/
static I32_T cli2_types_prt_range_of_shorttime (
	OUT I8_T *buf,
	IN LPARAM lparam,
	IN RPARAM rparam)
{
	CLI_TYPE_TIME_T *left_time;
	CLI_TYPE_TIME_T *right_time;

	left_time = (CLI_TYPE_TIME_T *)&lparam;
	right_time = (CLI_TYPE_TIME_T *)&rparam;
	return sprintf(buf, "%02u:%02u-%02u:%02u",
		left_time->hour, left_time->minute,
		right_time->hour, right_time->minute);
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_get_value_of_shorttime

DESCRIPTION:
	cli2_types_get_value_of_shorttime

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_value_of_shorttime (
	IN const I8_T *str,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{// hh:mm
	I8_T *start;
	CLI_TYPE_TIME_T *p_time;
	CLI_TYPE_TIME_T *lrange;
	CLI_TYPE_TIME_T *rrange;

	lrange = (CLI_TYPE_TIME_T *)&lparam;
	rrange = (CLI_TYPE_TIME_T *)&rparam;

	start = (I8_T *) str;
	p_time = value;
	p_time->second = 0;

	p_time->hour = strtol(start, &start, 10);
	if ((p_time->hour < lrange->hour) || (p_time->hour > rrange->hour))
	{
		return FALSE;
	}

	if (*start != ':')
	{
		return FALSE;
	}

	start++;
	p_time->minute = strtol(start, &start, 10);
	if ((p_time->minute < lrange->minute) || (p_time->minute > rrange->minute))
	{
		return FALSE;
	}

	if (*start != '\0')
	{
		return FALSE;
	}

	return TRUE;
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_prt_value_of_shorttime

DESCRIPTION:
	cli2_types_prt_value_of_shorttime

INPUT:
	value			: input parameter value

OUTPUT:
	buf				: storing parameter string

RETURN:
	the length of the parameter string

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_prt_value_of_shorttime (
	OUT I8_T *buf,
	IN void *value)
{
	CLI_TYPE_TIME_T *p_time;

	p_time = value;
	return sprintf(buf, "%02i:%02i", p_time->hour, p_time->minute);
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_cmp_value_of_shorttime

DESCRIPTION:
	cli2_types_cmp_value_of_shorttime

INPUT:
	ptr1				: parameter value
	ptr2				: parameter value

OUTPUT:

RETURN:
	1				: ptr1 value > ptr2 value
	0				: ptr1 value == ptr2 value
	-1				: ptr1 value < ptr2 value

NOTES:

HISTORY:

**************************************************************************/
static I32_T cli2_types_cmp_value_of_shorttime (IN void *ptr1, IN void *ptr2)
{
	CLI_TYPE_TIME_T *left;
	CLI_TYPE_TIME_T *right;
	UI32_T minute_left;
	UI32_T minute_right;

	left = ptr1;
	right = ptr2;

	minute_left = left->hour * 60 + left->minute;
	minute_right = right->hour * 60 + right->minute;

	if (minute_left < minute_right)
	{
		return -1;
	}
	else if (minute_left == minute_right)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_get_range_of_longtime

DESCRIPTION:
	cli2_types_get_range_of_longtime

INPUT:
	str				: begining of input range string
	end				: end of input range string

OUTPUT:
	lparam			: small value
	rparam			: large value

RETURN:
	TURE			: get range success
	FALSE			: input range string is error

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_range_of_longtime (
	IN const I8_T *str,
	IN const I8_T *end,
	IN OUT LPARAM *lparam,
	IN OUT RPARAM *rparam)
{
	// format of range string hh:mm:ss-hh:mm:ss
	I8_T *p;
	CLI_TYPE_TIME_T *ltime;
	CLI_TYPE_TIME_T *rtime;

	if ((str == NULL) || (str >= end)) // nothing in range string
	{
		return FALSE;
	}

	// get time value
	ltime = (CLI_TYPE_TIME_T *)lparam;
	rtime = (CLI_TYPE_TIME_T *)rparam;
	ltime->hour = (UI8_T)strtol (str, &p, 10);
	p++; // skip ':'
	ltime->minute = (UI8_T)strtol (p, &p, 10);
	p++; // skip ':'
	ltime->second = (UI8_T)strtol (p, &p, 10);
	p++; // skip '-'
	rtime->hour = (UI8_T)strtol (p, &p, 10);
	p++; // skip ':'
	rtime->minute = (UI8_T)strtol (p, &p, 10);
	p++; // skip ':'
	rtime->second = (UI8_T)strtol (p, &p, 10);
	if (p > end)
	{
		return FALSE;
	}

	// check the validation of left time and right time
	if ((ltime->hour > 23) || (ltime->minute > 59) || (ltime->second > 59)
		|| (rtime->hour > 23) || (rtime->minute > 59) || (rtime->second > 59))
	{
		return FALSE;
	}

	if ((ltime->hour * 60 * 60 + ltime->minute * 60 + ltime->second)
		> (rtime->hour * 60 * 60+ rtime->minute * 60 + rtime->second))
	{ // left time > right time
		return FALSE;
	}

	return TRUE;
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_prt_range_of_longtime

DESCRIPTION:
	cli2_types_prt_range_of_longtime

INPUT:
	lparam			: small value
	rparam			: large value

OUTPUT:
	buf				: storing range string

RETURN:
	the length of the range string

NOTES:

HISTORY:

**************************************************************************/
static I32_T cli2_types_prt_range_of_longtime (
	OUT I8_T *buf,
	IN LPARAM lparam,
	IN RPARAM rparam)
{
	CLI_TYPE_TIME_T *left_time;
	CLI_TYPE_TIME_T *right_time;

	left_time = (CLI_TYPE_TIME_T *)&lparam;
	right_time = (CLI_TYPE_TIME_T *)&rparam;
	return sprintf(buf, "%02u:%02u:%02u-%02u:%02u:%02u",
		left_time->hour, left_time->minute, left_time->second,
		right_time->hour, right_time->minute, right_time->second);
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_get_value_of_longtime

DESCRIPTION:
	cli2_types_get_value_of_longtime

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_value_of_longtime (
	IN const I8_T *str,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{// hh:mm:ss
	I8_T *start;
	CLI_TYPE_TIME_T *p_time;
	CLI_TYPE_TIME_T *lrange;
	CLI_TYPE_TIME_T *rrange;

	lrange = (CLI_TYPE_TIME_T *)&lparam;
	rrange = (CLI_TYPE_TIME_T *)&rparam;

	start = (I8_T *) str;
	p_time = value;
	p_time->second = 0;

	p_time->hour = strtol(start, &start, 10);
	if ((p_time->hour < lrange->hour) || (p_time->hour > rrange->hour))
	{
		return FALSE;
	}

	if (*start != ':')
	{
		return FALSE;
	}

	start++;
	p_time->minute = strtol(start, &start, 10);
	if ((p_time->minute < lrange->minute) || (p_time->minute > rrange->minute))
	{
		return FALSE;
	}

	if (*start != ':')
	{
		return FALSE;
	}

	start++;
	p_time->second = strtol(start, &start, 10);
	if ((p_time->second < lrange->second) || (p_time->second > rrange->second))
	{
		return FALSE;
	}

	if (*start != '\0')
	{
		return FALSE;
	}

	return TRUE;
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_prt_value_of_longtime

DESCRIPTION:
	cli2_types_prt_value_of_longtime

INPUT:
	value			: input parameter value

OUTPUT:
	buf				: storing parameter string

RETURN:
	the length of the parameter string

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_prt_value_of_longtime (
	OUT I8_T *buf,
	IN void *value)
{
	CLI_TYPE_TIME_T *p_time;

	p_time = value;
	return sprintf(buf, "%02i:%02i:%02i", p_time->hour, p_time->minute, p_time->second);
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_cmp_value_of_longtime

DESCRIPTION:
	cli2_types_cmp_value_of_longtime

INPUT:
	ptr1				: parameter value
	ptr2				: parameter value

OUTPUT:

RETURN:
	1				: ptr1 value > ptr2 value
	0				: ptr1 value == ptr2 value
	-1				: ptr1 value < ptr2 value

NOTES:

HISTORY:

**************************************************************************/
static I32_T cli2_types_cmp_value_of_longtime (IN void *ptr1, IN void *ptr2)
{
	CLI_TYPE_TIME_T *left;
	CLI_TYPE_TIME_T *right;
	UI32_T second_left;
	UI32_T second_right;

	left = ptr1;
	right = ptr2;

	second_left = left->hour * 60 * 60 + left->minute * 60 + left->second;
	second_right = right->hour * 60 * 60 + right->minute * 60 + right->second;

	if (second_left < second_right)
	{
		return -1;
	}
	else if (second_left == second_right)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_get_range_of_date

DESCRIPTION:
	cli2_types_get_range_of_date

INPUT:
	str				: begining of input range string
	end				: end of input range string

OUTPUT:
	lparam			: small value
	rparam			: large value

RETURN:
	TURE			: get range success
	FALSE			: input range string is error

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_range_of_date(
	IN const I8_T *str,
	IN const I8_T *end,
	IN OUT LPARAM *lparam,
	IN OUT RPARAM *rparam)
{
	/* format of range string dd/mm/yyyy-dd/mm/yyyy */
	I8_T *p;
	CLI_TYPE_DATE_T *lrange;
	CLI_TYPE_DATE_T *rrange;

	if ((str == NULL) || (*str == 0/*NULL*/) || (str >= end)) // nothing in range string
	{
		*lparam = *rparam = 0/*NULL*/;
		return TRUE;
	}

	// get date range value
	lrange = (CLI_TYPE_DATE_T *)lparam;
	rrange = (CLI_TYPE_DATE_T *)rparam;
	lrange->day = (UI8_T)strtoul(str, &p, 10);
	if ((*p != '-') && (*p != '/'))
	{
		return FALSE;
	}
	p++; // skip '/'
	lrange->month = (UI8_T)strtoul(p, &p, 10);
	if ((*p != '-') && (*p != '/'))
	{
		return FALSE;
	}
	p++; // skip '/'
	lrange->year = (UI16_T)strtoul(p, &p, 10);

	if (*p != '-')
	{
		return FALSE;
	}
	p++; // skip '-'

	rrange->day = (UI8_T)strtoul(p, &p, 10);
	if ((*p != '-') && (*p != '/'))
	{
		return FALSE;
	}
	p++; // skip '/'
	rrange->month = (UI8_T)strtoul(p, &p, 10);
	if ((*p != '-') && (*p != '/'))
	{
		return FALSE;
	}
	p++; // skip '/'
	rrange->year = (UI16_T)strtoul(p, &p, 10);
	if (p != end)
	{
		return FALSE;
	}

	if ((lrange->day < 1) || (lrange->day > 31)
		|| (lrange->month < 1) || (lrange->month > 12)
		|| (rrange->day < 1) || (rrange->day > 31)
		|| (rrange->month < 1) || (rrange->month > 12))
	{
		return FALSE;
	}

	if (lrange->year > rrange->year)
	{
		return FALSE;
	}

	if (lrange->year == rrange->year)
	{
		if (lrange->month > rrange->month)
		{
			return FALSE;
		}

		if (lrange->month == rrange->month)
		{
			if (lrange->day > rrange->day)
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_prt_range_of_date

DESCRIPTION:
	cli2_types_prt_range_of_date

INPUT:
	lparam			: small value
	rparam			: large value

OUTPUT:
	buf				: storing range string

RETURN:
	the length of the range string

NOTES:

HISTORY:

**************************************************************************/
static I32_T cli2_types_prt_range_of_date(
	OUT I8_T *buf,
	IN LPARAM lparam,
	IN RPARAM rparam)
{
	/* dd/mm/yyyy */
	CLI_TYPE_DATE_T *lrange;
	CLI_TYPE_DATE_T *rrange;

	if (lparam == 0/*NULL*/ || rparam == 0/*NULL*/)
	{
		return 0;
	}

	lrange = (CLI_TYPE_DATE_T *)&lparam;
	rrange = (CLI_TYPE_DATE_T *)&rparam;
	return sprintf(buf, "%02i/%02i/%04i-%02i/%02i/%04i",
		lrange->day, lrange->month, lrange->year,
		rrange->day, rrange->month, rrange->year);
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_get_value_of_date

DESCRIPTION:
	cli2_types_get_value_of_date

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_value_of_date(
	IN const I8_T *str,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{
	/* dd-mm-yyyy, dd/mm/yyyy */
	I8_T *start;
	CLI_TYPE_DATE_T *p_date;
	CLI_TYPE_DATE_T *lrange = NULL;
	CLI_TYPE_DATE_T *rrange= NULL;
	BOOL_T check_range = FALSE;
	UI32_T lvalue, rvalue, current_value;

	if (lparam == 0/*NULL*/ || rparam == 0/*NULL*/)
	{
		check_range = FALSE;
	}
	else
	{
		check_range = TRUE;
		lrange = (CLI_TYPE_DATE_T *)&lparam;
		rrange = (CLI_TYPE_DATE_T *)&rparam;
	}

	start = (I8_T *) str;
	p_date = value;

	p_date->day = strtoul(start, &start, 10);
	if ((p_date->day < 1) || (p_date->day > 31))
	{
		return FALSE;
	}

	if ((*start != '-') && (*start != '/'))
	{
		return FALSE;
	}
	start++;

	p_date->month = strtoul(start, &start, 10);
	if ((p_date->month < 1) || (p_date->month > 12))
	{
		return FALSE;
	}

	if ((*start != '-') && (*start != '/'))
	{
		return FALSE;
	}
	start++;

	p_date->year = strtoul(start, &start, 10);

	if (*start != '\0')
	{
		return FALSE;
	}

	if (check_range)
	{
		current_value = p_date->year * 10000 + p_date->month * 100 + p_date->day;
		lvalue = lrange->year * 10000 + lrange->month * 100 + lrange->day;
		rvalue = rrange->year * 10000 + rrange->month * 100 + rrange->day;
		if (current_value < lvalue || current_value > rvalue)
		{
			return FALSE;
		}
	}

	return TRUE;
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_prt_value_of_date

DESCRIPTION:
	cli2_types_prt_value_of_date

INPUT:
	value			: input parameter value

OUTPUT:
	buf				: storing parameter string

RETURN:
	the length of the parameter string

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_prt_value_of_date(
	OUT I8_T *buf,
	IN void *value)
{
	/* dd-mm-yyyy */
	CLI_TYPE_DATE_T *p_date;

	p_date = value;
	return sprintf(buf, "%02i/%02i/%04i",
		p_date->day, p_date->month, p_date->year);
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_cmp_value_of_date

DESCRIPTION:
	cli2_types_cmp_value_of_date

INPUT:
	ptr1				: parameter value
	ptr2				: parameter value

OUTPUT:

RETURN:
	1				: ptr1 value > ptr2 value
	0				: ptr1 value == ptr2 value
	-1				: ptr1 value < ptr2 value

NOTES:

HISTORY:

**************************************************************************/
static I32_T cli2_types_cmp_value_of_date(IN void *ptr1, IN void *ptr2)
{
	CLI_TYPE_DATE_T *left;
	CLI_TYPE_DATE_T *right;

	left = ptr1;
	right = ptr2;

	if (left->year < right->year)
	{
		return -1;
	}
	else if (left->year > right->year)
	{
		return 1;
	}
	else
	{
		if (left->month < right->month)
		{
			return -1;
		}
		else if (left->month > right->month)
		{
			return 1;
		}
		else
		{
			if (left->day < right->day)
			{
				return -1;
			}
			else if (left->day > right->day)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
}



/**************************************************************************
FUNCTION NAME:
	get_range_datecn

DESCRIPTION:
	get_range_datecn

INPUT:
	str				: begining of input range string
	end				: end of input range string

OUTPUT:
	lparam			: small value
	rparam			: large value

RETURN:
	TURE			: get range success
	FALSE			: input range string is error

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T get_range_datecn(
	IN const I8_T 	*str,
	IN const I8_T 	*end,
	IN OUT LPARAM 	*lparam,
	IN OUT RPARAM 	*rparam)
{
	/* format of range string yyyy/mm/dd-yyyy/mm/dd */
	I8_T 			*p;
	CLI_TYPE_DATE_T *lrange;
	CLI_TYPE_DATE_T *rrange;

	if ((str == NULL) || (*str == 0/*NULL*/) || (str >= end)) // nothing in range string
	{
		*lparam = *rparam = 0/*NULL*/;
		return TRUE;
	}

	// get date range value
	lrange = (CLI_TYPE_DATE_T *)lparam;
	rrange = (CLI_TYPE_DATE_T *)rparam;
	lrange->year = (UI8_T)strtoul(str, &p, 10);
	if (FALSE == IS_DATE_SEPERATOR(*p))
	{
		return FALSE;
	}

	p++; // skip '/'
	lrange->month = (UI8_T)strtoul(p, &p, 10);
	if (FALSE == IS_DATE_SEPERATOR(*p))
	{
		return FALSE;
	}

	p++; // skip '/'
	lrange->day = (UI16_T)strtoul(p, &p, 10);
	if (*p != '-')
	{
		return FALSE;
	}

	p++; // skip '-'
	rrange->year = (UI8_T)strtoul(p, &p, 10);
	if (FALSE == IS_DATE_SEPERATOR(*p))
	{
		return FALSE;
	}

	p++; // skip '/'
	rrange->month = (UI8_T)strtoul(p, &p, 10);
	if (FALSE == IS_DATE_SEPERATOR(*p))
	{
		return FALSE;
	}

	p++; // skip '/'
	rrange->day = (UI16_T)strtoul(p, &p, 10);
	if (p != end)
	{
		return FALSE;
	}

	if ((lrange->day < 1) || (lrange->day > 31)
		|| (lrange->month < 1) || (lrange->month > 12)
		|| (rrange->day < 1) || (rrange->day > 31)
		|| (rrange->month < 1) || (rrange->month > 12))
	{
		return FALSE;
	}

	if (lrange->year > rrange->year)
	{
		return FALSE;
	}

	if (lrange->year == rrange->year)
	{
		if (lrange->month > rrange->month)
		{
			return FALSE;
		}

		if (lrange->month == rrange->month)
		{
			if (lrange->day > rrange->day)
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}



/**************************************************************************
FUNCTION NAME:
	prt_range_datecn

DESCRIPTION:
	prt_range_datecn

INPUT:
	lparam			: small value
	rparam			: large value

OUTPUT:
	buf				: storing range string

RETURN:
	the length of the range string

NOTES:

HISTORY:

**************************************************************************/
static I32_T prt_range_datecn(
	OUT I8_T *buf,
	IN LPARAM lparam,
	IN RPARAM rparam)
{
	/* yyyy-mm-dd */
	CLI_TYPE_DATE_T *lrange;
	CLI_TYPE_DATE_T *rrange;

	if (lparam == 0/*NULL*/ || rparam == 0/*NULL*/)
	{
		return 0;
	}

	lrange = (CLI_TYPE_DATE_T *)&lparam;
	rrange = (CLI_TYPE_DATE_T *)&rparam;
	return sprintf(buf, "%04i-%02i-%02i ~ %04i-%02i-%02i", lrange->year, lrange->month, lrange->day, rrange->year, rrange->month, rrange->day);
}



/**************************************************************************
FUNCTION NAME:
	get_value_datecn

DESCRIPTION:
	get_value_datecn

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T get_value_datecn(
	IN const I8_T *str,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{
	/* yyyy-mm-dd, yyyy/mm/dd */
	I8_T 			*start;
	CLI_TYPE_DATE_T *p_date;
	CLI_TYPE_DATE_T *lrange     = NULL;
	CLI_TYPE_DATE_T *rrange     = NULL;
	BOOL_T 			check_range = FALSE;
	UI32_T 			lvalue, rvalue, current_value;

	if (lparam == 0/*NULL*/ || rparam == 0/*NULL*/)
	{
		check_range = FALSE;
	}
	else
	{
		check_range = TRUE;
		lrange = (CLI_TYPE_DATE_T *)&lparam;
		rrange = (CLI_TYPE_DATE_T *)&rparam;
	}

	start = (I8_T *) str;
	p_date = value;

	/* year */
	p_date->year = strtoul(start, &start, 10);
	if (FALSE == IS_DATE_SEPERATOR(*start))
	{
		return FALSE;
	}

	start++; /* skip '-' */
	/* month */
	p_date->month = strtoul(start, &start, 10);
	if ((p_date->month < 1) || (p_date->month > 12))
	{
		return FALSE;
	}
	if (FALSE == IS_DATE_SEPERATOR(*start))
	{
		return FALSE;
	}

	start++; /* skip '-' */
	/* day */
	p_date->day = strtoul(start, &start, 10);
	if ((p_date->day < 1) || (p_date->day > 31))
	{
		return FALSE;
	}

	if (*start != '\0')
	{
		return FALSE;
	}

	if (check_range)
	{
		current_value = p_date->year * 10000 + p_date->month * 100 + p_date->day;
		lvalue        = lrange->year * 10000 + lrange->month * 100 + lrange->day;
		rvalue        = rrange->year * 10000 + rrange->month * 100 + rrange->day;

		if (current_value < lvalue || current_value > rvalue)
		{
			return FALSE;
		}
	}

	return TRUE;
}



/**************************************************************************
FUNCTION NAME:
	prt_value_datecn

DESCRIPTION:
	prt_value_datecn

INPUT:
	value			: input parameter value

OUTPUT:
	buf				: storing parameter string

RETURN:
	the length of the parameter string

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T prt_value_datecn(
	OUT I8_T *buf,
	IN void *value)
{
	/* yyyy-mm-dd */
	CLI_TYPE_DATE_T *p_date;

	p_date = value;
	return sprintf(buf, "%04i-%02i-%02i", p_date->year, p_date->month, p_date->day);
}



/**************************************************************************
FUNCTION NAME:
	cmp_value_datecn

DESCRIPTION:
	cmp_value_datecn

INPUT:
	ptr1			: parameter value
	ptr2			: parameter value

OUTPUT:

RETURN:
	1				: ptr1 value > ptr2 value
	0				: ptr1 value == ptr2 value
	-1				: ptr1 value < ptr2 value

NOTES:

HISTORY:

**************************************************************************/
static I32_T cmp_value_datecn(IN void *ptr1, IN void *ptr2)
{
	CLI_TYPE_DATE_T *left;
	CLI_TYPE_DATE_T *right;

	left = ptr1;
	right = ptr2;

	if (left->year < right->year)
	{
		return -1;
	}
	else if (left->year > right->year)
	{
		return 1;
	}
	//else
	//{
		if (left->month < right->month)
		{
			return -1;
		}
		else if (left->month > right->month)
		{
			return 1;
		}
		//else
		//{
			if (left->day < right->day)
			{
				return -1;
			}
			else if (left->day > right->day)
			{
				return 1;
			}
			//else
			//{
				return 0;
			//}
		//}
	//}
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_get_value_of_clig1_date

DESCRIPTION:
	cli2_types_get_value_of_clig1_date

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_value_of_clig1_date(
	IN const I8_T *str,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{
	UI32_T i;
	UI32_T val ; /* variable for one byte value */
	DEV_RTC_TIME_T ptrDate;
	BOOL_T valid_month_string;
	I8_T month[4];
	I8_T *month_str[] = {"jan","feb","mar","apr","may",
						"jun","jul","aug","sep",
						"oct","nov","dec"};

	if (lparam || rparam) {}

	memset(month, 0, sizeof(month));
	memset(&ptrDate, 0, sizeof(ptrDate));

	/* monthday */
	val = strtoul(str, (I8_T **)&str, 10);
	if ((val > 31) || (val < 1))
	{
		return  FALSE;
	}
	ptrDate.monthday = (UI8_T)val;

	/* month */
	valid_month_string = FALSE;/* To check if the string is valid, Claire, 2003/11/18 12:09PM */
	month[0] = *str++;
	month[1] = *str++;
	month[2] = *str++;
	for (i = 0; i < 12; i++)
	{
		if (strcmp(month, month_str[i]) == 0)
		{
			ptrDate.month = (UI8_T)(i+1);
			valid_month_string = TRUE;
			break;
		}
	}
	if (valid_month_string == FALSE)
	{
		return FALSE;
	}

	/* year */
	val = strtoul(str, (I8_T **)&str, 10);
	if (*str != '\0')
	{
		return FALSE;
	}
	ptrDate.year = (UI16_T)val;

	memcpy(value, &ptrDate, sizeof(DEV_RTC_TIME_T));

	return TRUE;
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_prt_value_of_clig1_date

DESCRIPTION:
	cli2_types_prt_value_of_clig1_date

INPUT:
	value			: input parameter value

OUTPUT:
	buf				: storing parameter string

RETURN:
	the length of the parameter string

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_prt_value_of_clig1_date(
	OUT I8_T *buf,
	IN void *value)
{
	DEV_RTC_TIME_T *ptrDate;
	I8_T *month_str[] = {"jan","feb","mar","apr","may",
						"jun","jul","aug","sep",
						"oct","nov","dec"};

	ptrDate = (DEV_RTC_TIME_T *)value;

	return sprintf(buf,"%2.2i%s%2.2i",
		ptrDate->monthday, month_str[ptrDate->month-1],ptrDate->year);
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_get_value_of_clig1_time

DESCRIPTION:
	cli2_types_get_value_of_clig1_time

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_value_of_clig1_time(
	IN const I8_T *str,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{
	UI32_T val ; /* variable for one byte value */
	DEV_RTC_TIME_T ptrDate;

	if (lparam || rparam) {}

	memset(&ptrDate, 0, sizeof(DEV_RTC_TIME_T));

	/* hour */
	val = strtoul(str, (I8_T **)&str, 10);
	if ((val > 23) || (val < 0))
	{
		return FALSE;
	}
	ptrDate.hour = (UI8_T)val;

	if (*str == ':' || *str == '/' || *str == '-')
	{
		str++;
	}
	else
	{
		return FALSE;
	}

	/* minute */
	val = strtoul(str, (I8_T **)&str, 10);
	if ((val > 59) || (val < 0))
	{
		return FALSE;
	}
	ptrDate.minute = (UI8_T)val;

	if (*str == ':' || *str == '/' || *str == '-')
	{
		str++;
	}
	else
	{
		return FALSE;
	}

	/* second */
	val = strtoul(str, (I8_T **)&str, 10);
	if ((val > 59) || (val < 0))
	{
		return FALSE;
	}
	ptrDate.second = (UI8_T)val;

	if (*str != '\0')
	{
		return FALSE;
	}
	memcpy(value, &ptrDate, sizeof(DEV_RTC_TIME_T));

	return TRUE;
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_prt_value_of_clig1_time

DESCRIPTION:
	cli2_types_prt_value_of_clig1_time

INPUT:
	value			: input parameter value

OUTPUT:
	buf				: storing parameter string

RETURN:
	the length of the parameter string

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_prt_value_of_clig1_time(
	OUT I8_T *buf,
	IN void *value)
{
	DEV_RTC_TIME_T *ptrDate;

	ptrDate = (DEV_RTC_TIME_T*)value;

	return sprintf(buf,"%i:%i:%i",
		ptrDate->hour, ptrDate->minute, ptrDate->second);
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_get_value_of_clig1_time2

DESCRIPTION:
	cli2_types_get_value_of_clig1_time2

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_value_of_clig1_time2(
	IN const I8_T *str,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{
	UI32_T val ; /* variable for one byte value */
	SNTP_IF_DST_T ptrDate;

	if (lparam || rparam)
	{
		;
	}

	memset(&ptrDate, 0, sizeof(SNTP_IF_DST_T));

	/* hour */
	val = strtoul(str, (I8_T **)&str, 10);
	if ((val > 23) || (val < 0))
	{
		return FALSE;
	}

	ptrDate.hour = (UI8_T)val;

	if (*str == ':' || *str == '/' || *str == '-')
	{
		str++;
	}
	else
	{
		return FALSE;
	}

	/* minute */
	val = strtoul(str, (I8_T **)&str, 10);
	if ((val > 59) || (val < 0))
	{
		return FALSE;
	}

	ptrDate.minute = (UI8_T)val;

	if (*str != '\0')
	{
		return FALSE;
	}

	memcpy(value, &ptrDate, sizeof(SNTP_IF_DST_T));

	return TRUE;
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_prt_value_of_clig1_time2

DESCRIPTION:
	cli2_types_prt_value_of_clig1_time2

INPUT:
	value			: input parameter value

OUTPUT:
	buf				: storing parameter string

RETURN:
	the length of the parameter string

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_prt_value_of_clig1_time2(
	OUT I8_T *buf,
	IN void *value)
{
	SNTP_IF_DST_T *ptrDst;

	ptrDst = (SNTP_IF_DST_T*)value;

	if (ptrDst->hour < 10)
	{
		if (ptrDst->minute < 10)
		{
			return sprintf(buf, "0%i:0%i", ptrDst->hour, ptrDst->minute);
		}
		else
		{
			return sprintf(buf, "0%i:%i", ptrDst->hour, ptrDst->minute);
		}
	}
	else
	{
		if (ptrDst->minute < 10)
		{
			return sprintf(buf, "%i:0%i", ptrDst->hour, ptrDst->minute);
		}
		else
		{
			return sprintf(buf, "%i:%i", ptrDst->hour, ptrDst->minute);
		}
	}
}

/**************************************************************************
FUNCTION NAME:
	cli2_types_get_value_of_clig1_daylist

DESCRIPTION:
	cli2_types_get_value_of_clig1_daylist

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_value_of_clig1_daylist(
	IN const I8_T *str,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{
	const I8_T *ptr;
	I8_T *datlist_str[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", ""};
	I8_T *datlist_str2[] = {"sun", "mon", "tue", "wed", "thu", "fri", "sat", ""};
	UI32_T day_offset, i;
	UI32_T start_day = 0, end_day = 0;
	PORTLIST_T day_list;


	if (lparam || rparam) {}

	ptr = str;
	memset(day_list, 0, sizeof(PORTLIST_T));

	while (*ptr)
	{
		for (day_offset = 0; day_offset < 7; day_offset++)
		{
			if ((0 == memcmp(ptr, datlist_str[day_offset], 3)) || (0 == memcmp(ptr, datlist_str2[day_offset], 3)))
			{
			start_day = day_offset + 1;
			ptr = ptr + 3;
			break;
			}
		}

		if (day_offset >= 7)
		{
			return FALSE;
		}

		if (*ptr == '-')
		{
			ptr++; /* skip '-' */
			for (day_offset = 0; day_offset < 7; day_offset++)
	    		{
	    			if ((0 == memcmp(ptr, datlist_str[day_offset], 3)) || (0 == memcmp(ptr, datlist_str2[day_offset], 3)))
	    			{
					end_day = day_offset + 1;
					ptr = ptr + 3;
					break;
	    			}
	    		}

			if (day_offset >= 7 || start_day > end_day)
			{
				return FALSE;
			}
		}
		else
		{
			end_day = start_day;
		}

		for (i = start_day; i <= end_day; i++)
		{
			//UTL_PORTMAP_Set_Port(day_list, i);
			utili_bit_set_bit((UI8_T *)&day_list, i, sizeof(day_list));
		}

		if (*ptr != '\0'/*NULL*/)
		{
			if (*ptr != ',')
			{
				return FALSE;
			}

			ptr++; /* skip '-' */
			if (*ptr == '\0')
			{
				return FALSE;
			}
		}
	}

	memcpy(value, day_list, sizeof(PORTLIST_T));

	return  TRUE;
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_prt_value_of_clig1_daylist

DESCRIPTION:
	cli2_types_prt_value_of_clig1_daylist

INPUT:
	value			: input parameter value

OUTPUT:
	buf				: storing parameter string

RETURN:
	the length of the parameter string

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_prt_value_of_clig1_daylist(
	OUT I8_T *buf,
	IN void *value)
{
	UI32_T i, start_day = 0, end_day;
	BOOL_T successive;
	I8_T *temp_obuf;
	I8_T *weekday_str[] = {"sun", "mon", "tue", "wed", "thu", "fri", "sat", ""};

	successive = FALSE;
	temp_obuf = buf;

	for (i = 1; i <= 8; i++)
	{
		if (i < 8)
		{
			//if (UTL_PORTMAP_Is_PortSet(value, i))
			if (utili_bit_is_bitset(value, i, sizeof(PORTLIST_T)))
			{
				if (!successive)
				{
					start_day = i;
					successive = TRUE;
				}
				continue;
			}
		}

		if (successive)
		{
			end_day = i - 1;
			if (start_day == end_day)
			{

				memcpy(temp_obuf, weekday_str[start_day - 1], 3);
				temp_obuf += 3;

				*(temp_obuf++) = ',';
				*(temp_obuf) = VT_NULL;
			}
			else
			{
				memcpy(temp_obuf, weekday_str[start_day - 1], 3);
				temp_obuf += 3;
				*(temp_obuf++) = '-';

				memcpy(temp_obuf, weekday_str[end_day - 1], 3);
				temp_obuf += 3;

				*(temp_obuf++) = ',';
				*(temp_obuf) = VT_NULL;
			}
			successive = FALSE;
		}
	}

	/* add NULL end */
	if (temp_obuf > buf)
	{
		*(--temp_obuf) = VT_NULL;
	}
	else
	{
		*(temp_obuf) = VT_NULL;
	}

	return (temp_obuf - buf);
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_get_value_of_clig1_media

DESCRIPTION:
	cli2_types_get_value_of_clig1_media

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_value_of_clig1_media(
	IN const I8_T *str,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{
	if (lparam || rparam) {}

	if (isalpha(str[0]) && (':' == str[1]) && '\0' == str[2])
	{
		strcpy(value, str);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_get_value_of_oid

DESCRIPTION:
	cli2_types_get_value_of_oid

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_value_of_oid(
	IN const I8_T *str,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{
	CLI_OID_T 	*p_oid;
	const I8_T 	*start, *end;
	I8_T 		*cur_pos;

	if (lparam || rparam)
	{
	}

	start = str;
	p_oid = value;
	p_oid->len = 0;
	while (*start)
	{
		if (p_oid->len >= CLI_TYPES_OID_COUNT_MAX)
		{
			return FALSE;
		}

		end = start;
#if 0
		if (UTL_EXTPRT_TransStrToUI32(&end, 10, &p_oid->value[p_oid->len]) == FALSE)
#else
		cur_pos = utili_str_to_uint32((I8_T *)end, 10, &p_oid->value[p_oid->len]);
		if (NULL == cur_pos)
#endif
		{
			return FALSE;
		}

		end = cur_pos;
		if ((end == start) || (*end && (*end != '.')))
		{
			return FALSE;
		}

		p_oid->len++;

		if (*end == '.')
		{
			end++; // skip '.'
		}
		start = end;
	}

	return TRUE;
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_prt_value_of_oid

DESCRIPTION:
	cli2_types_prt_value_of_oid

INPUT:
	value			: input parameter value

OUTPUT:
	buf				: storing parameter string

RETURN:
	the length of the parameter string

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_prt_value_of_oid (
	OUT I8_T *buf,
	IN void *value)
{
#if 0
	return sprintf(buf, "%s", value);
#else
	//CLI_DBG_NOTSUPPORTED(l_mdl_id);
	return FALSE;
#endif
}



/**************************************************************************
FUNCTION NAME:
	__get_range_hex

DESCRIPTION:
	__get_range_hex

INPUT:
	str				: begining of input range string
	end				: end of input range string

OUTPUT:
	lparam			: small value
	rparam			: large value

RETURN:
	TURE			: get range success
	FALSE			: input range string is error

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T __get_range_hex(
	IN const I8_T *str,
	IN const I8_T *end,
	IN OUT LPARAM *lparam,
	IN OUT RPARAM *rparam)
{
	CLI_DBG_ENTER(l_mdl_id);

	I8_T *cur_pos;

	if ((str == NULL) || (str >= end)) // nothing in range string
	{
		CLI_DBG_LEAVE(l_mdl_id);
		return FALSE;
	}

	cur_pos = (I8_T *)str;
	CLI_DBG_CPL(l_mdl_id, "cur port str: %s\r\n", cur_pos);
#if 0
	if (UTL_EXTPRT_TransStrToUI32(&str, 16, lparam) == FALSE)
#else
	cur_pos = utili_str_to_uint32(cur_pos, 16, lparam);
	CLI_DBG_CPL(l_mdl_id, "cur port str: %s\r\n", cur_pos);
	if (NULL == cur_pos)
#endif
	{
		CLI_DBG_LEAVE(l_mdl_id);
		return FALSE;
	}

	if (*cur_pos == '-') // range string is like "lparam-rparam"
	{
		cur_pos++;
		CLI_DBG_CPL(l_mdl_id, "cur port str: %s\r\n", cur_pos);
#if 0
		if (UTL_EXTPRT_TransStrToUI32(&str, 16, rparam) == FALSE)
#else
		cur_pos = utili_str_to_uint32((I8_T *)cur_pos, 16, rparam);
		CLI_DBG_CPL(l_mdl_id, "cur port str: %s\r\n", cur_pos);
		if (NULL == cur_pos)
#endif
		{
			CLI_DBG_LEAVE(l_mdl_id);
			return FALSE;
		}
	}
	else // only rparam in range string
	{
		*rparam = *lparam;
		*lparam = 0;
	}

	if ((cur_pos != end) || (*lparam > *rparam))
	{
		CLI_DBG_CPL(l_mdl_id, "str: begin=0x%08X, cur_pos=0x%08X, end=0x%08X\r\n", (int)str, (int)cur_pos, (int)end);
		CLI_DBG_LEAVE(l_mdl_id);
		return FALSE;
	}

	CLI_DBG_LEAVE(l_mdl_id);
	return TRUE;
}



/**************************************************************************
FUNCTION NAME:
	__prt_range_hex

DESCRIPTION:
	__prt_range_hex

INPUT:
	lparam			: small value
	rparam			: large value

OUTPUT:
	buf				: storing range string

RETURN:
	the length of the range string

NOTES:

HISTORY:

**************************************************************************/
static I32_T __prt_range_hex (
	OUT I8_T *buf,
	IN LPARAM lparam,
	IN RPARAM rparam)
{
	return sprintf(buf, "0x%X-0x%X", lparam, rparam);
}



/**************************************************************************
FUNCTION NAME:
	__get_value_hex

DESCRIPTION:
	__get_value_hex

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T __get_value_hex (
	IN const I8_T *str,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{
	UI32_T 	*p;
	I8_T 	*cur_pos;

	p = value;
	if ((str[0] != '0') || ((str[1] != 'x') && (str[1] != 'X')))
	{
		return FALSE;
	}

	cur_pos = (I8_T *)str;
#if 0
	if (UTL_EXTPRT_TransStrToUI32(&str, 16, p) == FALSE)
#else
	cur_pos = utili_str_to_uint32((I8_T *)cur_pos, 16, p);
	if (NULL == cur_pos)
#endif
	{
		return FALSE;
	}

	if ((*cur_pos != '\0') || (*p < lparam) || (*p > rparam))
	{
		return FALSE;
	}

	return TRUE;
}



/**************************************************************************
FUNCTION NAME:
	__prt_value_hex

DESCRIPTION:
	__prt_value_hex

INPUT:
	value			: input parameter value

OUTPUT:
	buf				: storing parameter string

RETURN:
	the length of the parameter string

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T __prt_value_hex (
	OUT I8_T *buf,
	IN void *value)
{
	return sprintf(buf, "0x%x", *(UI32_T *)value);
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_get_value_of_binary

DESCRIPTION:
	cli2_types_get_value_of_binary

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_value_of_binary (
	IN const I8_T *str,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{
	UI32_T *p;
	I8_T *q;

	p = value;
	// check binary string header
	if ((str[0] != '\0') || ((str[1] != 'b') && (str[1] != 'B')))
	{
		return FALSE;
	}
	str += 2;

	if (strlen(str) > 32)
	{
		return FALSE;
	}

	*p = strtoul(str, &q, 2);
	if ((*q != '\0') || (*p < lparam) || (*p > rparam))
	{
		return FALSE;
	}

	return TRUE;
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_get_range_of_float

DESCRIPTION:
	cli2_types_get_range_of_float

INPUT:
	str				: begining of input range string
	end				: end of input range string

OUTPUT:
	lparam			: small value
	rparam			: large value

RETURN:
	TURE			: get range success
	FALSE			: input range string is error

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_range_of_float(
	IN const I8_T *str,
	IN const I8_T *end,
	IN OUT LPARAM *lparam,
	IN OUT RPARAM *rparam)
{
	float *lvalue, *rvalue;

	*lparam = *rparam = 0/*NULL*/;

	/* check if the range is null */
	if (str == NULL || end == NULL || *str == 0/*NULL*/ || *end == 0/*NULL*/ || str == end)
	{
		return TRUE;
	}

	lvalue = CLI_MISC_Malloc(sizeof(float));
	if (lvalue == NULL)
	{
		return FALSE;
	}

	rvalue = CLI_MISC_Malloc(sizeof(float));
	if (rvalue == NULL)
	{
		cli_misc_free(lvalue);
		return FALSE;
	}

#if 0
	if (UTL_EXTPRT_TransStrToFloat(&str, lvalue) == FALSE)
#else
	str = utili_str_to_float((I8_T *)str, lvalue);
	if (NULL == str)
#endif
	{
		cli_misc_free(lvalue);
		cli_misc_free(rvalue);
		return FALSE;
	}

	if (*str == '-')
	{
		str++;
#if 0
		if (UTL_EXTPRT_TransStrToFloat(&str, rvalue) == FALSE)
#else
		str = utili_str_to_float((I8_T *)str, rvalue);
		if (NULL == str)
#endif
		{
			cli_misc_free(lvalue);
			cli_misc_free(rvalue);
			return FALSE;
		}
	}
	else
	{
		*rvalue = *lvalue;
		*lvalue = 0;
	}

	if ((str != end) || (*lvalue > *rvalue))
	{
		cli_misc_free(lvalue);
		cli_misc_free(rvalue);
		return FALSE;
	}

	*lparam = (UI32_T)lvalue;
	*rparam = (UI32_T)rvalue;

	return TRUE;
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_prt_range_of_float

DESCRIPTION:
	cli2_types_prt_range_of_float

INPUT:
	lparam			: small value
	rparam			: large value

OUTPUT:
	buf				: storing range string

RETURN:
	the length of the range string

NOTES:

HISTORY:

**************************************************************************/
static I32_T cli2_types_prt_range_of_float(
	OUT I8_T *buf,
	IN LPARAM lparam,
	IN RPARAM rparam)
{
	if (lparam == 0/*NULL*/ || rparam == 0/*NULL*/)
	{
		return 0;
	}
	else
	{
		return sprintf(buf, "%g-%g", *(float *)lparam, *(float *)rparam);
	}
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_get_value_of_float

DESCRIPTION:
	cli2_types_get_value_of_float

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_get_value_of_float(
	IN const I8_T *str,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{
	float ret_value, lvalue, rvalue;

#if 0
	if (UTL_EXTPRT_TransStrToFloat(&str, &ret_value))
#else
	str = utili_str_to_float((I8_T *)str, &ret_value);
	if (NULL == str)
#endif
	{
		if (*str != '\0')
		{
			return FALSE;
		}

		/* check the range */
		if (lparam && rparam)
		{
			lvalue = *(float *)lparam;
			rvalue = *(float *)rparam;

			if ((ret_value < lvalue) || (ret_value > rvalue))
			{
				return FALSE;
			}
		}

		*(float *)value = ret_value;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_prt_value_of_float

DESCRIPTION:
	cli2_types_prt_value_of_float

INPUT:
	value			: input parameter value

OUTPUT:
	buf				: storing parameter string

RETURN:
	the length of the parameter string

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T cli2_types_prt_value_of_float(
	OUT I8_T *buf,
	IN void *value)
{
	return sprintf(buf, "%g", *(float *)value);
}



/**************************************************************************
FUNCTION NAME:
	cli2_types_cmp_value_of_float

DESCRIPTION:
	cli2_types_cmp_value_of_float

INPUT:
	ptr1				: parameter value
	ptr2				: parameter value

OUTPUT:

RETURN:
	1				: ptr1 value > ptr2 value
	0				: ptr1 value == ptr2 value
	-1				: ptr1 value < ptr2 value

NOTES:

HISTORY:

**************************************************************************/
static I32_T cli2_types_cmp_value_of_float(IN void *ptr1, IN void *ptr2)
{
	float left;
	float right;

	left = *(float *) ptr1;
	right = *(float *) ptr2;

	if (left < right)
	{
		return -1;
	}
	else if (left == right)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}



/**************************************************************************
FUNCTION NAME:
	__get_range_multi_enumlist_ch

DESCRIPTION:
	__get_range_multi_enumlist_ch

INPUT:
	str				: begining of input range string
	end				: end of input range string

OUTPUT:
	lparam			: small value
	rparam			: large value

RETURN:
	TURE			: get range success
	FALSE			: input range string is error

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T __get_range_multi_enumlist_ch(
	IN const I8_T *str,
	IN const I8_T *end,
	IN OUT LPARAM *lparam,
	IN OUT RPARAM *rparam)
{
#if 0
	CLI_TYPE_INTERFACE_T *port_min;
	CLI_TYPE_INTERFACE_T *port_max;

	port_min = (CLI_TYPE_INTERFACE_T *)lparam;
	port_max = (CLI_TYPE_INTERFACE_T *)rparam;

	/* check if the range is null */
	if (str == NULL || end == NULL || *str == 0/*NULL*/ || *end == 0/*NULL*/ || str == end)
	{
		port_min->boxid = 1;
		port_min->portid = 1;
		port_max->boxid = MIB_CST_MAX_BOX_OF_STACK;
		port_max->portid = MIB_CST_MAX_PORT_OF_STACK_BOX;

		return TRUE;
	}

	port_min->boxid = (UI8_T)strtoul(str, (I8_T **)&str, 10);

	if (*str != CLI_ALIAS_PORT_SEPERATOR)
	{
		port_min->portid = port_min->boxid;
		if (ST_MASTER == ST_STACK_Get_Role())
		{
			port_min->boxid = ST_STACK_Get_MyBoxID();
		}
		else
		{
			port_min->boxid = ST_STACK_Get_MasterBoxID();
		}
	}
	else
	{
		str++; /* skip ':' and parse */
		port_min->portid = (UI8_T)strtoul(str, (I8_T **)&str, 10);
	}

	if (*str == CLI_ALIAS_PORT_RANGE_SEPERATOR)
	{
		port_max->boxid = (UI8_T)strtoul(str, (I8_T **)&str, 10);

		if (*str != CLI_ALIAS_PORT_SEPERATOR)
		{
			port_max->portid = port_max->boxid;
			if (ST_MASTER == ST_STACK_Get_Role())
			{
				port_max->boxid = ST_STACK_Get_MyBoxID();
			}
			else
			{
				port_max->boxid = ST_STACK_Get_MasterBoxID();
			}
		}
		else
		{
			str++; /* skip ':' and parse */
			port_max->portid = (UI8_T)strtoul(str, (I8_T **)&str, 10);
		}
	}
	else
	{
		port_max->boxid = port_min->boxid;
		port_max->portid = port_min->portid;
		port_min->boxid = 1;
		port_min->portid = 1;
	}

	if ((str != end)
		|| (port_min->boxid > port_max->boxid)
		|| ((port_min->boxid == port_max->boxid) && (port_min->portid > port_max->portid))
		|| (port_min->boxid < 1) || (port_max->boxid > MIB_CST_MAX_BOX_OF_STACK)
		|| (port_min->portid < 1) || (port_min->portid > MIB_CST_MAX_PORT_OF_STACK_BOX)
		|| (port_max->portid < 1) || (port_max->portid > MIB_CST_MAX_PORT_OF_STACK_BOX))
	{
		return FALSE;
	}

	return TRUE;
#else
	//CLI_DBG_NOTSUPPORTED(l_mdl_id);
	return FALSE;
#endif
}



/**************************************************************************
FUNCTION NAME:
	__prt_range_multi_enumlist_cn

DESCRIPTION:
	__prt_range_multi_enumlist_cn

INPUT:
	lparam			: small value
	rparam			: large value

OUTPUT:
	buf				: storing range string

RETURN:
	the length of the range string

NOTES:

HISTORY:

**************************************************************************/
static I32_T __prt_range_multi_enumlist_cn(
	OUT I8_T *buf,
	IN LPARAM lparam,
	IN RPARAM rparam)
{
#if 0
	CLI_TYPE_INTERFACE_T *port_min;
	CLI_TYPE_INTERFACE_T *port_max;
	I32_T len;
	ST_SWITCH_MODE_T mode;

	port_min = (void *)&lparam;
	port_max = (void *)&rparam;

	len = 0;
	ST_STACK_Get_SwitchMode(&mode);

	/* left range */
	if (mode != ST_SWITCH_STANDALONE && port_min->boxid > 0 && port_min->boxid <= MIB_CST_MAX_BOX_OF_STACK)
	{
		len += sprintf(buf + len, "%u%c", port_min->boxid, CLI_ALIAS_PORT_SEPERATOR);
	}
	len += sprintf(buf + len, "%u%c", port_min->portid, CLI_ALIAS_PORT_RANGE_SEPERATOR);

	/* right range */
	if (mode != ST_SWITCH_STANDALONE && port_max->boxid > 0 && port_max->boxid <= MIB_CST_MAX_BOX_OF_STACK)
	{
		len += sprintf(buf + len, "%u%c", port_max->boxid, CLI_ALIAS_PORT_SEPERATOR);
	}
	len += sprintf(buf + len, "%u", port_max->portid);
	buf[len] = 0;

	return len;
#else
	UNUSED(buf);
	UNUSED(lparam);
	UNUSED(rparam);

	return 0;
#endif
}


#define CHAR_NUM_STORM_MODE					6
#define UNIT_NUM_STORM_MODE					2
#define MULTI_NUM_STORM_MODE				2
#define BROAD_NUM_STORM_MODE				2

/**************************************************************************
FUNCTION NAME:
	__get_value_multi_enumlist_cn

DESCRIPTION:
	option: u U m M b B 
	format: u or m or b or u,m or u,b or m,b or u,m,b or ...

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T __get_value_multi_enumlist_cn(
	IN const I8_T *str,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{
	CLI_DBG_ENTER(l_mdl_id);
	CLI_DBG_CPL(l_mdl_id, "frame port: %s\r\n", str);

	char 			*pStr = (char*)str;
	unsigned char 	flag = 0;
	int i = 0;
	int un = 1;
	int bn = 1;
	int mn = 1;
	cli_sc_e 		*storm_mode = (cli_sc_e*)value;

	*storm_mode = CLI_STORM_CTRL_NONE;

	while (1)
	{
		if (i < CHAR_NUM_STORM_MODE)
		{
			switch (*pStr)
			{
			case 'U':
			case 'u':
				if (un < UNIT_NUM_STORM_MODE)
				{
					if (flag == 1)
					{
						*storm_mode = CLI_STORM_CTRL_NONE;
						goto Exit_storm;
					}

					*storm_mode |= CLI_STORM_CTRL_UNI;
					flag = 1;
					i++;
					un++;
				}
				else
				{
					CLI_DBG_CPL(l_mdl_id, "Input storm mode error: u parameter repeat!\r\n");
					*storm_mode = CLI_STORM_CTRL_NONE;
					goto Exit_storm;
				}
			break;

			case 'M':
			case 'm':
				if (mn < MULTI_NUM_STORM_MODE)
				{
					if (flag == 1)
					{
						*storm_mode = CLI_STORM_CTRL_NONE;
						goto Exit_storm;
					}

					*storm_mode |= CLI_STORM_CTRL_MULTI;
					flag = 1;
					i++;
					mn++;
				}
				else
				{
					CLI_DBG_CPL(l_mdl_id, "Input storm mode error: m parameter repeat!\r\n");
					*storm_mode = CLI_STORM_CTRL_NONE;
					goto Exit_storm;
				}
			break;

			case 'B':
			case 'b':
				if (bn < BROAD_NUM_STORM_MODE)
				{
					if (flag == 1)
					{
						*storm_mode = CLI_STORM_CTRL_NONE;
						goto Exit_storm;
					}

					*storm_mode |= CLI_STORM_CTRL_BROAD;
					flag = 1;
					i++;
					bn++;
				}
				else
				{
					CLI_DBG_CPL(l_mdl_id, "Input storm mode error: b parameter repeat!\r\n");
					*storm_mode = CLI_STORM_CTRL_NONE;
					goto Exit_storm;
				}
			break;

			case ',':
				if (flag == 0)
				{
					*storm_mode = CLI_STORM_CTRL_NONE;
					goto Exit_storm;
				}

				flag = 0;
				i++;
			break;

			case '\0':
				if (flag == 1)
				{
					goto Exit_storm;
				}
				else
				{
					*storm_mode = CLI_STORM_CTRL_NONE;
					goto Exit_storm;
				}
			break;

			default:
				*storm_mode = CLI_STORM_CTRL_NONE;
				goto Exit_storm;
			break;
			}

			pStr++;
		}
		else
		{
			CLI_DBG_CPL(l_mdl_id, "Input storm mode error: too many parameters!\r\n");
			*storm_mode = CLI_STORM_CTRL_NONE;
			goto Exit_storm;
		}
	}

Exit_storm:

	if (*storm_mode == CLI_STORM_CTRL_NONE)
	{
		CLI_DBG_CPL(l_mdl_id, "Input storm mode [%s] is error! must be [u,b,m]\r\n", str);
		return FALSE;
	}
	else
	{
		CLI_DBG_CPL(l_mdl_id, "Input storm mode : unicast=%u, multicast=%u, broadcast=%u\r\n", 
								(*storm_mode & CLI_STORM_CTRL_UNI), (*storm_mode & CLI_STORM_CTRL_MULTI), (*storm_mode & CLI_STORM_CTRL_BROAD));
		return TRUE;
	}
}



/**************************************************************************
FUNCTION NAME:
	__prt_value_multi_enumlist_cn

DESCRIPTION:
	__prt_value_multi_enumlist_cn

INPUT:
	value			: input parameter value

OUTPUT:
	buf				: storing parameter string

RETURN:
	the length of the parameter string

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T __prt_value_multi_enumlist_cn(
	OUT I8_T *buf,
	IN void *value)
{
#if 0
	return sprintf(buf, "%p", *(UI32_T *)value);
#else
	//CLI_DBG_NOTSUPPORTED(l_mdl_id);
	return FALSE;
#endif
}



/**************************************************************************
FUNCTION NAME:
	__cmp_value_multi_enumlist_cn

DESCRIPTION:
	__cmp_value_multi_enumlist_cn

INPUT:
	ptr1				: parameter value
	ptr2				: parameter value

OUTPUT:

RETURN:
	1				: ptr1 value > ptr2 value
	0				: ptr1 value == ptr2 value
	-1				: ptr1 value < ptr2 value

NOTES:

HISTORY:

**************************************************************************/
static I32_T __cmp_value_multi_enumlist_cn(IN void *ptr1, IN void *ptr2)
{
	float left;
	float right;

	left = *(float *) ptr1;
	right = *(float *) ptr2;

	if (left < right)
	{
		return -1;
	}
	else if (left == right)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}



/**************************************************************************
FUNCTION NAME:
	__get_range_onuid

DESCRIPTION:
	__get_range_onuid

INPUT:
	str				: begining of input range string
	end				: end of input range string

OUTPUT:
	lparam			: small value
	rparam			: large value

RETURN:
	TURE			: get range success
	FALSE			: input range string is error

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T __get_range_onuid(
	IN const I8_T *str,
	IN const I8_T *end,
	IN OUT LPARAM *lparam,
	IN OUT RPARAM *rparam)
{
#if 0
	CLI_TYPE_INTERFACE_T *port_min;
	CLI_TYPE_INTERFACE_T *port_max;

	port_min = (CLI_TYPE_INTERFACE_T *)lparam;
	port_max = (CLI_TYPE_INTERFACE_T *)rparam;

	/* check if the range is null */
	if (str == NULL || end == NULL || *str == 0/*NULL*/ || *end == 0/*NULL*/ || str == end)
	{
		port_min->boxid = 1;
		port_min->portid = 1;
		port_max->boxid = MIB_CST_MAX_BOX_OF_STACK;
		port_max->portid = MIB_CST_MAX_PORT_OF_STACK_BOX;

		return TRUE;
	}

	port_min->boxid = (UI8_T)strtoul(str, (I8_T **)&str, 10);

	if (*str != CLI_ALIAS_PORT_SEPERATOR)
	{
		port_min->portid = port_min->boxid;
		if (ST_MASTER == ST_STACK_Get_Role())
		{
			port_min->boxid = ST_STACK_Get_MyBoxID();
		}
		else
		{
			port_min->boxid = ST_STACK_Get_MasterBoxID();
		}
	}
	else
	{
		str++; /* skip ':' and parse */
		port_min->portid = (UI8_T)strtoul(str, (I8_T **)&str, 10);
	}

	if (*str == CLI_ALIAS_PORT_RANGE_SEPERATOR)
	{
		port_max->boxid = (UI8_T)strtoul(str, (I8_T **)&str, 10);

		if (*str != CLI_ALIAS_PORT_SEPERATOR)
		{
			port_max->portid = port_max->boxid;
			if (ST_MASTER == ST_STACK_Get_Role())
			{
				port_max->boxid = ST_STACK_Get_MyBoxID();
			}
			else
			{
				port_max->boxid = ST_STACK_Get_MasterBoxID();
			}
		}
		else
		{
			str++; /* skip ':' and parse */
			port_max->portid = (UI8_T)strtoul(str, (I8_T **)&str, 10);
		}
	}
	else
	{
		port_max->boxid = port_min->boxid;
		port_max->portid = port_min->portid;
		port_min->boxid = 1;
		port_min->portid = 1;
	}

	if ((str != end)
		|| (port_min->boxid > port_max->boxid)
		|| ((port_min->boxid == port_max->boxid) && (port_min->portid > port_max->portid))
		|| (port_min->boxid < 1) || (port_max->boxid > MIB_CST_MAX_BOX_OF_STACK)
		|| (port_min->portid < 1) || (port_min->portid > MIB_CST_MAX_PORT_OF_STACK_BOX)
		|| (port_max->portid < 1) || (port_max->portid > MIB_CST_MAX_PORT_OF_STACK_BOX))
	{
		return FALSE;
	}

	return TRUE;
#else
	//CLI_DBG_NOTSUPPORTED(l_mdl_id);
	return FALSE;
#endif
}



/**************************************************************************
FUNCTION NAME:
	__prt_range_onuid

DESCRIPTION:
	__prt_range_onuid

INPUT:
	lparam			: small value
	rparam			: large value

OUTPUT:
	buf				: storing range string

RETURN:
	the length of the range string

NOTES:

HISTORY:

**************************************************************************/
static I32_T __prt_range_onuid(
	OUT I8_T *buf,
	IN LPARAM lparam,
	IN RPARAM rparam)
{
#if 0
	CLI_TYPE_INTERFACE_T *port_min;
	CLI_TYPE_INTERFACE_T *port_max;
	I32_T len;
	ST_SWITCH_MODE_T mode;

	port_min = (void *)&lparam;
	port_max = (void *)&rparam;

	len = 0;
	ST_STACK_Get_SwitchMode(&mode);

	/* left range */
	if (mode != ST_SWITCH_STANDALONE && port_min->boxid > 0 && port_min->boxid <= MIB_CST_MAX_BOX_OF_STACK)
	{
		len += sprintf(buf + len, "%u%c", port_min->boxid, CLI_ALIAS_PORT_SEPERATOR);
	}
	len += sprintf(buf + len, "%u%c", port_min->portid, CLI_ALIAS_PORT_RANGE_SEPERATOR);

	/* right range */
	if (mode != ST_SWITCH_STANDALONE && port_max->boxid > 0 && port_max->boxid <= MIB_CST_MAX_BOX_OF_STACK)
	{
		len += sprintf(buf + len, "%u%c", port_max->boxid, CLI_ALIAS_PORT_SEPERATOR);
	}
	len += sprintf(buf + len, "%u", port_max->portid);
	buf[len] = 0;

	return len;
#else
	UNUSED(buf);
	UNUSED(lparam);
	UNUSED(rparam);

	return 0;
#endif
}



/**************************************************************************
FUNCTION NAME:
	__get_value_onuid

DESCRIPTION:
	1/2:3

INPUT:
	str				: the input parameter string
	lparam			: small value
	rparam			: large value

OUTPUT:
	value			: used to store the value of translated parameter

RETURN:
	TURE			: get parameter value success
	FALSE			: input parameter string is error or out of range

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T __get_value_onuid(
	IN const I8_T *str,
	IN LPARAM lparam,
	IN RPARAM rparam,
	OUT void *value)
{
	CLI_DBG_ENTER(l_mdl_id);
	CLI_DBG_CPL(l_mdl_id, "frame port: %s\r\n", str);

#if 1
	I8_T 					*cur_pos = (I8_T *)str;
	cli_onuid_t				onu_id;
	//CLI_TYPE_INTERFACE_T 	*min;
	//CLI_TYPE_INTERFACE_T 	*max;

	//min = (void *)&lparam;
	//max = (void *)&rparam;

	CLI_DBG_CPL(l_mdl_id, "cur port str: %s\r\n", cur_pos);
	/* get slot id */
#if 0
	if (UTL_EXTPRT_TransStrToUI32(&str, 10, &slot_id) == FALSE)
#else
	cur_pos = utili_str_to_uint32((I8_T *)cur_pos, 10, &onu_id.slot_id);
	if (NULL == cur_pos)
#endif
	{
		CLI_DBG_LEAVE(l_mdl_id);
		return FALSE;
	}
	CLI_DBG_CPL(l_mdl_id, "slot id=%u\r\n", onu_id.slot_id);

	CLI_DBG_CPL(l_mdl_id, "cur port str: %s\r\n", cur_pos);
	if (*cur_pos != CLI_ALIAS_PORT_SEPERATOR)
	{
		CLI_DBG_LEAVE(l_mdl_id);
		return FALSE;
	}

	/* skip '/' and parse */
	cur_pos++; 

	CLI_DBG_CPL(l_mdl_id, "cur port str: %s\r\n", cur_pos);
	/* get port id */
#if 0
	if (UTL_EXTPRT_TransStrToUI32(&cur_pos, 10, &port_id) == FALSE)
#else
	cur_pos = utili_str_to_uint32((I8_T *)cur_pos, 10, &onu_id.port_id);
	if (NULL == cur_pos)
#endif
	{
		CLI_DBG_LEAVE(l_mdl_id);
		return FALSE;
	}
	CLI_DBG_CPL(l_mdl_id, "port id=%u\r\n", onu_id.port_id);

	CLI_DBG_CPL(l_mdl_id, "cur port str: %s\r\n", cur_pos);
	if (*cur_pos != CLI_ALIAS_LLID_SEPERATOR)
	{
		CLI_DBG_LEAVE(l_mdl_id);
		return FALSE;
	}

	/* skip ':' and parse */
	cur_pos++; 
	
	
	CLI_DBG_CPL(l_mdl_id, "cur port str: %s\r\n", cur_pos);
	/* get llid */
#if 0
	if (UTL_EXTPRT_TransStrToUI32(&cur_pos, 10, &port_id) == FALSE)
#else
	cur_pos = utili_str_to_uint32((I8_T *)cur_pos, 10, &onu_id.llid);
	if (NULL == cur_pos)
#endif
	{
		CLI_DBG_LEAVE(l_mdl_id);
		return FALSE;
	}
	CLI_DBG_CPL(l_mdl_id, "llid=%u\r\n", onu_id.llid);

	CLI_DBG_CPL(l_mdl_id, "cur port str: %s\r\n", cur_pos);
	/* check slot & port id */
	//if ((*cur_pos != '\0') || (slot_id < min->boxid) || (slot_id > max->boxid) || (port_id < min->portid) || (port_id > max->portid))
	//{
	//	return FALSE;
	//}

	MEMCPY(value, &onu_id, sizeof(onu_id));

	return TRUE;
#else
	CLI_DBG_NOTSUPPORTED(l_mdl_id);
	return FALSE;
#endif
}



/**************************************************************************
FUNCTION NAME:
	__prt_value_onuid

DESCRIPTION:
	__prt_value_onuid

INPUT:
	value			: input parameter value

OUTPUT:
	buf				: storing parameter string

RETURN:
	the length of the parameter string

NOTES:

HISTORY:

**************************************************************************/
static BOOL_T __prt_value_onuid(
	OUT I8_T *buf,
	IN void *value)
{
#if 0
	return sprintf(buf, "%p", *(UI32_T *)value);
#else
	CLI_DBG_NOTSUPPORTED(l_mdl_id);
	return FALSE;
#endif
}



// collect not ordered functions of the primitive type(get_range, prt_range,
//		 get_value, prt_value, cmp_value)
static CLI_TYPES_ARGUFUNC_T _cli2_types_argufunc_collect[] =
{
/*
 *	{
 *		CLI_PRIMITIVE_SYNTAX_T type; // primitive type of the argument in CLI
 *		UI32_T flags; // reserved
 *		CLI_TYPES_GET_RANGE_FUNC_T *get_range;
 *		CLI_TYPES_PRT_RANGE_FUNC_T *prt_range;
 *		CLI_TYPES_GET_VALUE_FUNC_T *get_value;
 *		CLI_TYPES_PRT_VALUE_FUNC_T *prt_value;
 *		CLI_TYPES_CMP_VALUE_FUNC_T *cmp_value;
 *	}
 */
	{
		CLI_TYPES_STRING,
		1,
		cli2_types_get_range_of_string,
		cli2_types_prt_range_of_string,
		cli2_types_get_value_of_string,
		NULL,
		cli2_types_prt_value_of_string,
		cli2_types_cmp_value_of_string
	},
	{
		CLI_TYPES_STRING_WITHOUT_WHITESPACE,
		1,
		cli2_types_get_range_of_string,
		cli2_types_prt_range_of_string,
		cli2_types_get_value_of_string_without_whitespace,
		NULL,
		cli2_types_prt_value_of_string,
		cli2_types_cmp_value_of_string
	},
	{
		CLI_TYPES_NAME,
		1,
		cli2_types_get_range_of_string,
		cli2_types_prt_range_of_string,
		cli2_types_get_value_of_name,
		NULL,
		cli2_types_prt_value_of_string,
		cli2_types_cmp_value_of_string
	},
	{
		CLI_TYPES_MULTIWORD,
		1,
		cli2_types_get_range_of_string,
		cli2_types_prt_range_of_string,
		cli2_types_get_value_of_string,
		NULL,
		cli2_types_prt_value_multiword,
		cli2_types_cmp_value_of_string
	},
	{
		CLI_TYPES_SENTENCE,
		1,
		cli2_types_get_range_of_string,
		cli2_types_prt_range_of_string,
		cli2_types_get_value_of_string,
		NULL,
		cli2_types_prt_value_of_string,
		cli2_types_cmp_value_of_string
	},
	{
		CLI_TYPES_ENUMLIST_UI32,
		1,
		cli2_types_get_range_of_enumlist,
		cli2_types_prt_range_of_enumlist,
		cli2_types_get_value_of_enum_ui32,
		NULL,
		cli2_types_prt_value_of_ui32,
		NULL
	},
	{
		CLI_TYPES_ENUMLIST_STRING,
		1,
		cli2_types_get_range_of_enumlist,
		cli2_types_prt_range_of_enumlist,
		cli2_types_get_value_of_enum_string,
		NULL,
		cli2_types_prt_value_of_string,
		NULL
	},
	{
		CLI_TYPES_MONTH,
		1,
		cli2_types_get_range_of_null,
		cli2_types_prt_range_of_month,
		cli2_types_get_value_of_month,
		NULL,
		cli2_types_prt_value_of_month,
		NULL
	},
	{
		CLI_TYPES_WEEKDAY,
		1,
		cli2_types_get_range_of_null,
		cli2_types_prt_range_of_weekday,
		cli2_types_get_value_of_weekday,
		NULL,
		cli2_types_prt_value_of_weekday,
		NULL
	},
	{
		CLI_TYPES_WEEK,
		1,
		cli2_types_get_range_of_null,
		cli2_types_prt_range_of_week,
		cli2_types_get_value_of_week,
		NULL,
		cli2_types_prt_value_of_week,
		NULL
	},
	{
		CLI_TYPES_IPADDR,
		1,
		cli2_types_get_range_of_null,
		cli2_types_prt_range_of_null,
		cli2_types_get_value_of_ipaddr,
		NULL,
		cli2_types_prt_value_of_ipaddr,
		NULL
	},
	{
		CLI_TYPES_IPNETADDR,
		1,
		cli2_types_get_range_of_null,
		cli2_types_prt_range_of_null,
		cli2_types_get_value_of_ipnetaddr,
		NULL,
		cli2_types_prt_value_of_ipnetaddr,
		NULL
	},
	{
		CLI_TYPES_IPMULTICASTADDR,
		1,
		cli2_types_get_range_of_null,
		cli2_types_prt_range_of_null,
		cli2_types_get_value_of_ipmulticastaddr,
		NULL,
		cli2_types_prt_value_of_ipaddr,
		NULL
	},
	{
		CLI_TYPES_IPMULTICASTADDRCHAIN,
		1,
		cli2_types_get_range_of_null,
		cli2_types_prt_range_of_null,
		cli2_types_get_value_of_ipmulticastaddrchain,
		NULL,
		cli2_types_prt_value_of_ipmulticastaddrchain,
		NULL
	},
	{
		CLI_TYPES_IPV6ADDR,
		1,
		cli2_types_get_range_of_null,
		cli2_types_prt_range_of_null,
		cli2_types_get_value_of_ipv6addr,
		NULL,
		cli2_types_prt_value_of_ipv6addr,
		NULL
	},
	{
		CLI_TYPES_IPV6NETADDR,
		1,
		cli2_types_get_range_of_null,
		cli2_types_prt_range_of_null,
		cli2_types_get_value_of_ipv6netaddr,
		NULL,
		cli2_types_prt_value_of_ipv6netaddr,
		NULL
	},
	{
		CLI_TYPES_IPV6MULTICASTADDR,
		1,
		cli2_types_get_range_of_null,
		cli2_types_prt_range_of_null,
		cli2_types_get_value_of_ipv6multicastaddr,
		NULL,
		cli2_types_prt_value_of_ipv6addr,
		NULL
	},
	{
		CLI_TYPES_IPV6MULTICASTADDRCHAIN,
		1,
		cli2_types_get_range_of_null,
		cli2_types_prt_range_of_null,
		cli2_types_get_value_of_ipv6multicastaddrchain,
		NULL,
		cli2_types_prt_value_of_ipv6multicastaddrchain,
		NULL
	},
	{
		CLI_TYPES_FRAMEPORTNUM,
		1,
		get_range_frameportnum,
		prt_range_frameportnum,
		get_value_frameportnum,
		NULL,
		prt_value_frameportnum,
		NULL
	},
	{
		CLI_TYPES_STACKINGPORTLIST,
		1,
		get_range_frameportnum,
		prt_range_frameportnum,
		cli2_types_get_value_of_stackingPortList,
		NULL,
		cli2_types_prt_value_of_stackingPortList,
		NULL
	},
	{
		CLI_TYPES_STANDALONEPORTLIST,
		1,
		cli2_types_get_range_of_standalonePortList,
		cli2_types_prt_range_of_null,
		cli2_types_get_value_of_standalonePortList,
		NULL,
		cli2_types_prt_value_of_standalonePortList,
		NULL
	},
	{
		CLI_TYPES_UI32,
		1,
		cli2_types_get_range_of_ui32,
		cli2_types_prt_range_of_ui32,
		cli2_types_get_value_of_ui32,
		NULL,
		cli2_types_prt_value_of_ui32,
		cli2_types_cmp_value_of_ui32
	},
	{
		CLI_TYPES_I32,
		1,
		cli2_types_get_range_of_i32,
		cli2_types_prt_range_of_i32,
		cli2_types_get_value_of_i32,
		NULL,
		cli2_types_prt_value_of_i32,
		cli2_types_cmp_value_of_i32
	},
	{
		CLI_TYPES_UI32CHAIN,
		1,
		cli2_types_get_range_of_ui32,
		cli2_types_prt_range_of_ui32,
		cli2_types_get_value_of_ui32chain,
		NULL,
		cli2_types_prt_value_of_ui32chain,
		NULL
	},
	{
		CLI_TYPES_INTLIST,
		1,
		cli2_types_get_range_of_ui32,
		cli2_types_prt_range_of_ui32,
		cli2_types_get_value_of_intlist,
		NULL,
		cli2_types_prt_value_of_intlist,
		NULL
	},
	{
		CLI_TYPES_VLANLIST,
		1,
		cli2_types_get_range_of_ui32,
		cli2_types_prt_range_of_ui32,
		cli2_types_get_value_of_vlanlist,
		NULL,
		cli2_types_prt_value_of_vlanlist,
		NULL
	},
	{
		CLI_TYPES_VLANLIST_NAME,
		1,
		cli2_types_get_range_of_ui32,
		cli2_types_prt_range_of_ui32,
		cli2_types_get_value_of_vlanlist_name,
		NULL,
		cli2_types_prt_value_of_vlanlist_name,
		NULL
	},
	{
		CLI_TYPES_MACADDR,
		1,
		cli2_types_get_range_of_null,
		cli2_types_prt_range_of_null,
		cli2_types_get_value_of_macaddr,
		NULL,
		cli2_types_prt_value_of_macaddr,
		NULL
	},
	{
		CLI_TYPES_MMACADDR,
		1,
		cli2_types_get_range_of_null,
		cli2_types_prt_range_of_null,
		cli2_types_get_value_of_mmacaddr,
		NULL,
		cli2_types_prt_value_of_macaddr,
		NULL
	},
	{
		CLI_TYPES_UMACADDR,
		1,
		cli2_types_get_range_of_null,
		cli2_types_prt_range_of_null,
		cli2_types_get_value_of_umacaddr,
		NULL,
		cli2_types_prt_value_of_macaddr,
		NULL
	},
	{
		CLI_TYPES_SHORTTIME,
		1,
		cli2_types_get_range_of_shorttime,
		cli2_types_prt_range_of_shorttime,
		cli2_types_get_value_of_shorttime,
		NULL,
		cli2_types_prt_value_of_shorttime,
		cli2_types_cmp_value_of_shorttime
	},
	{
		CLI_TYPES_LONGTIME,
		1,
		cli2_types_get_range_of_longtime,
		cli2_types_prt_range_of_longtime,
		cli2_types_get_value_of_longtime,
		NULL,
		cli2_types_prt_value_of_longtime,
		cli2_types_cmp_value_of_longtime
	},
	{
		CLI_TYPES_DATE, // dd-mm-yyyy
		1,
		cli2_types_get_range_of_date,
		cli2_types_prt_range_of_date,
		cli2_types_get_value_of_date,
		NULL,
		cli2_types_prt_value_of_date,
		cli2_types_cmp_value_of_date
	},
	{
		CLI_TYPES_DATECN, // yyyy-mm-dd
		1,
		get_range_datecn,
		prt_range_datecn,
		get_value_datecn,
		NULL,
		prt_value_datecn,
		cmp_value_datecn
	},
	{
		CLI_TYPES_CLIG1_DATE, // ddmmmyyyy
		1,
		cli2_types_get_range_of_null,
		cli2_types_prt_range_of_null,
		cli2_types_get_value_of_clig1_date,
		NULL,
		cli2_types_prt_value_of_clig1_date,
		NULL
	},
	{
		CLI_TYPES_CLIG1_TIME, // hh:mm:ss
		1,
		cli2_types_get_range_of_null,
		cli2_types_prt_range_of_null,
		cli2_types_get_value_of_clig1_time,
		NULL,
		cli2_types_prt_value_of_clig1_time,
		NULL
	},
	{
		CLI_TYPES_CLIG1_TIME2, // hh:mm
		1,
		cli2_types_get_range_of_null,
		cli2_types_prt_range_of_null,
		cli2_types_get_value_of_clig1_time2,
		NULL,
		cli2_types_prt_value_of_clig1_time2,
		NULL
	},
	{
		CLI_TYPES_CLIG1_DAYLIST, // string such as: sun,mon
		1,
		cli2_types_get_range_of_null,
		cli2_types_prt_range_of_null,
		cli2_types_get_value_of_clig1_daylist,
		NULL,
		cli2_types_prt_value_of_clig1_daylist,
		NULL
	},
	{
		CLI_TYPES_CLIG1_MEDIA, // string such as: c:
		1,
		cli2_types_get_range_of_null,
		cli2_types_prt_range_of_null,
		cli2_types_get_value_of_clig1_media,
		NULL,
		cli2_types_prt_value_of_string,
		NULL
	},
	{
		CLI_TYPES_OID,
		1,
		cli2_types_get_range_of_null,
		cli2_types_prt_range_of_null,
		cli2_types_get_value_of_oid,
		NULL,
		cli2_types_prt_value_of_oid,
		NULL
	},
	{
		CLI_TYPES_HEX,
		1,
		__get_range_hex,
		__prt_range_hex,
		__get_value_hex,
		NULL,
		__prt_value_hex,
		cli2_types_cmp_value_of_ui32
	},
	{
		CLI_TYPES_BINARY,
		1,
		__get_range_hex,
		__prt_range_hex,
		cli2_types_get_value_of_binary,
		NULL,
		__prt_value_hex,
		cli2_types_cmp_value_of_ui32
	},
	{
		CLI_TYPES_FLOAT,
		1,
		cli2_types_get_range_of_float,
		cli2_types_prt_range_of_float,
		cli2_types_get_value_of_float,
		NULL,
		cli2_types_prt_value_of_float,
		cli2_types_cmp_value_of_float
	},
	{
		CLI_TYPES_ONUID,
		1,
		__get_range_onuid,
		__prt_range_onuid,
		__get_value_onuid,
		NULL,
		__prt_value_onuid,
		NULL
	},
	{
		CLI_TYPES_STORM_CONTROL,
		1,
		__get_range_multi_enumlist_ch,
		__prt_range_multi_enumlist_cn,
		__get_value_multi_enumlist_cn,
		NULL,
		__prt_value_multi_enumlist_cn,
		__cmp_value_multi_enumlist_cn
	},
};

// used to collect ordered process functions of the primitive type
static CLI_TYPES_ARGUFUNC_T _cli2_types_argufunc_list[CLI_TYPES_MAX];

/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 CLI_TYPES_GetGetRangeFunc
 *
 * DESCRIPTION:
 *	 Get get_range function of the specified argument type
 *
 * INPUT:
 *	 type -- type of the argument
 *
 * OUTPUT:
 *	 NA
 *
 * RETURN:
 *	 pointer of the get_range function
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-15 by foo -- Create
 *
*******************************************************************************/
CLI_TYPES_GET_RANGE_FUNC_T *CLI_TYPES_GetGetRangeFunc (IN I32_T type)
{
	CLI_TYPES_ARGUFUNC_T *p;

	CLI_MISC_Assert(type < CLI_TYPES_MAX);
	p = &_cli2_types_argufunc_list[type];
	return p->get_range;
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 CLI_TYPES_GetPrtRangeFunc
 *
 * DESCRIPTION:
 *	 Get prt_range function of the specified argument type
 *
 * INPUT:
 *	 type -- type of the argument
 *
 * OUTPUT:
 *	 NA
 *
 * RETURN:
 *	 pointer of the prt_range function
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-15 by foo -- Create
 *
*******************************************************************************/
CLI_TYPES_PRT_RANGE_FUNC_T *CLI_TYPES_GetPrtRangeFunc (IN I32_T type)
{
	CLI_TYPES_ARGUFUNC_T *p;

	CLI_MISC_Assert(type < CLI_TYPES_MAX);
	p = &_cli2_types_argufunc_list[type];
	return p->prt_range;
}

/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 CLI_TYPES_GetGetValueFunc
 *
 * DESCRIPTION:
 *	 Get get_value functions of the specified argument type
 *
 * INPUT:
 *	 type -- type of the argument
 *
 * OUTPUT:
 *	 NA
 *
 * RETURN:
 *	 pointer of the get_value function
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-15 by foo -- Create
 *
*******************************************************************************/
CLI_TYPES_GET_VALUE_FUNC_T *CLI_TYPES_GetGetValueFunc(IN I32_T type)
{
	CLI_TYPES_ARGUFUNC_T *p;

	CLI_MISC_Assert(type < CLI_TYPES_MAX);
	p = &_cli2_types_argufunc_list[type];
	return p->get_value;
}

/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 CLI_TYPES_GetGetHelpFunc
 *
 * DESCRIPTION:
 *	 Get get_help functions of the specified argument type
 *
 * INPUT:
 *	 type -- type of the argument
 *
 * OUTPUT:
 *	 NA
 *
 * RETURN:
 *	 pointer of the get_value function
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *   2010-Nov-08 by wangbin -- Create
 *
*******************************************************************************/
CLI_TYPES_GET_HELP_FUNC_T *CLI_TYPES_GetGetHelpFunc (IN I32_T type)
{
	CLI_TYPES_ARGUFUNC_T *p;

	CLI_MISC_Assert(type < CLI_TYPES_MAX);
	p = &_cli2_types_argufunc_list[type];
	return p->get_help;
}

/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 CLI_TYPES_GetPrtValueFunc
 *
 * DESCRIPTION:
 *	 Get prt_value functions of the specified argument type
 *
 * INPUT:
 *	 type -- type of the argument
 *
 * OUTPUT:
 *	 NA
 *
 * RETURN:
 *	 pointer of the prt_value function
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-15 by foo -- Create
 *
*******************************************************************************/
CLI_TYPES_PRT_VALUE_FUNC_T *CLI_TYPES_GetPrtValueFunc (IN I32_T type)
{
	CLI_TYPES_ARGUFUNC_T *p;

	CLI_MISC_Assert(type < CLI_TYPES_MAX);
	p = &_cli2_types_argufunc_list[type];
	return p->prt_value;
}

/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 CLI_TYPES_GetCmpValueFunc
 *
 * DESCRIPTION:
 *	 Get cmp_value functions of the specified argument type
 *
 * INPUT:
 *	 type -- type of the argument
 *
 * OUTPUT:
 *	 NA
 *
 * RETURN:
 *	 pointer of the cmp_value function
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-15 by foo -- Create
 *
*******************************************************************************/
CLI_TYPES_CMP_VALUE_FUNC_T *CLI_TYPES_GetCmpValueFunc (IN I32_T type)
{
	CLI_TYPES_ARGUFUNC_T *p;

	CLI_MISC_Assert(type < CLI_TYPES_MAX);
	p = &_cli2_types_argufunc_list[type];
	return p->cmp_value;
}
/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 cli2_types_reg_argufunc
 *
 * DESCRIPTION:
 *	 Register functions for primitive argument type.
 *
 * INPUT:
 *	 argufunc -- collection of the functions
 *	 size -- how many primitive types will be registered
 *
 * OUTPUT:
 *	 NA
 *
 * RETURN:
 *	 TRUE -- success
 *	 FALSE -- failure
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-18 by wangbin -- Create
 *
*******************************************************************************/
static BOOL_T cli2_types_reg_argufunc(IN CLI_TYPES_ARGUFUNC_T *argufunc, IN UI32_T size)
{
	UI32_T i;
	UI32_T index;

	for (i = 0; i < size; i++)
	{
		index = argufunc[i].type;
		if (_cli2_types_argufunc_list[index].get_value != NULL)
		{
			CLI_MSG_PrtErrMsg(UTL_MISC_ERR_TYPES_PRIMITIVE_REPETITION);
			return FALSE;
		}

		memcpy (_cli2_types_argufunc_list + index, argufunc + i, sizeof(CLI_TYPES_ARGUFUNC_T));
	}

	return TRUE;
}

/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 CLI_TYPES_GetValue
 *
 * DESCRIPTION:
 *	 Check and convert word in parameter of the user command to cli_value_t
 *
 * INPUT:
 *	 current -- current node in parameter tree
 *	 cmd -- word in user command
 *	 result -- word result already checked
 *
 * OUTPUT:
 *	 result -- if word in user command match word in parameter tree, the new
 *		word information will be added. else nothing changed
 *
 * RETURN:
 *	 TRUE -- success
 *	 FALSE -- failure
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-18 by wangbin -- Create
 *
*******************************************************************************/
BOOL_T CLI_TYPES_GetValue(
	IN CLI_PRIV_PARA_SYN_NODE_T * current,
	IN const I8_T * cmd,
	IN OUT CLI_PARA_CMD_TAB_LIST_T * result)
{
	CLI_DBG_ENTER(l_mdl_id);
	CLI_DBG_CPL(l_mdl_id, "type=%d,name=%s\r\n", current->type, current->name);

	UI32_T size; // size of the (cli_value_t *)p->value.
	void *value;
	CLI_TYPES_GET_VALUE_FUNC_T *get_value;

	if (current->type == CLI_TYPES_KEYWORD)
	{
		size = CLI_ALIAS_Clac_ParaValueSize(current->type, current->name);
	}
	else
	{
		size = CLI_ALIAS_Clac_ParaValueSize(current->type, cmd);
	}

	if ((current->type != CLI_TYPES_KEYWORD) && (current->type != CLI_TYPES_ENUM))
	{
		get_value = CLI_TYPES_GetGetValueFunc(current->type);
		CLI_MISC_Assert(get_value);

		value = CLI_MISC_Malloc(size);
		if (!value)
		{
			CLI_MSG_PrtErrMsg(UTL_MISC_ERR_MEMORY_OVERFLOW);
			CLI_DBG_LEAVE(l_mdl_id);
			return FALSE;
		}

		CLI_DBG_CPL(l_mdl_id, "cmd=%s,lparam=%d,rparam=%d\r\n", cmd, current->lparam, current->rparam);
		if (get_value(cmd, current->lparam, current->rparam, value) == FALSE)
		{
			cli_misc_free(value);
			CLI_DBG_LEAVE(l_mdl_id);
			return FALSE;
		}
	}
	else
	{ // match keyword or enum
		if (strncmp (current->name, cmd, strlen(cmd)) != 0)
		{
			CLI_DBG_LEAVE(l_mdl_id);
			return FALSE;
		}

		if (strlen(cmd) == strlen (current->name))   //beat match in this command
		{
			result->most_match = TRUE;
			result->count = 0;
		}

		value = CLI_MISC_Malloc(size);
		if (!value)
		{
			CLI_MSG_PrtErrMsg(UTL_MISC_ERR_MEMORY_OVERFLOW);
			CLI_DBG_LEAVE(l_mdl_id);
			return FALSE;
		}

		if (current->type == CLI_TYPES_ENUM)
		{
			*(UI32_T *)value = current->lparam;
		}
		else
		{
			strcpy(value, current->name);
		}
	}

	result->list[result->count++] = current;
	if (result->tail)
	{
		// save the value of the word
		result->tail->next = CLI_MISC_Calloc(1, sizeof(cli_value_t));
		if (!result->tail->next)
		{
			cli_misc_free(value);
			CLI_MSG_PrtErrMsg(UTL_MISC_ERR_MEMORY_OVERFLOW);
			CLI_DBG_LEAVE(l_mdl_id);
			return FALSE;
		}

		result->tail = result->tail->next;
		result->tail->next = NULL;
		result->tail->value = value;

		// save the name of the word
		if (current->name && (strlen (current->name) > 0))
		{
			result->tail->name = CLI_MISC_Malloc(strlen (current->name) + 1);
			if (!result->tail->name)
			{
				cli_misc_free(value);
				CLI_DBG_LEAVE(l_mdl_id);
				return FALSE;
			}

			strcpy(result->tail->name, current->name);
		}
		else
		{
			result->tail->name = NULL;
		}

		result->tail->type = current->type;
	}
	else
	{
		cli_misc_free(value);
	}

	CLI_DBG_LEAVE(l_mdl_id);
	return TRUE;
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_TYPES_Get_CurrentHelp
 *
 * DESCRIPTION:
 *   Get current help string.
 *
 * INPUT:
 *   cmd: word in user command
 *   current: current node in parameter tree
 *   result: word result already checked
 *
 * OUTPUT:
 *	 result -- if word in user command match word in parameter tree, the new
 *		word information will be added. else nothing changed
 *
 * RETURN:
 *	 TRUE -- success
 *	 FALSE -- failure
 *
 * NOTES:
 *   None
 *
 * HISTORY:
 *   2010-Nov-08 by wangbin -- Create
 *
*******************************************************************************/
BOOL_T CLI_TYPES_Get_CurrentHelp (
	IN CLI_PRIV_PARA_SYN_NODE_T * current,
	IN const I8_T * cmd,
	IN OUT CLI_PARA_CMD_TAB_LIST_T * result)
{
	UI32_T size; // size of the (cli_value_t *)p->value.
	void *value;
	CLI_TYPES_GET_VALUE_FUNC_T *get_value = NULL;
	CLI_TYPES_GET_HELP_FUNC_T *get_help = NULL;

	if (current->type == CLI_TYPES_KEYWORD)
	{
		size = CLI_ALIAS_Clac_ParaValueSize(current->type, current->name);
	}
	else
	{
		size = CLI_ALIAS_Clac_ParaValueSize(current->type, cmd);
	}

	if ((current->type != CLI_TYPES_KEYWORD) && (current->type != CLI_TYPES_ENUM))
	{
		value = CLI_MISC_Malloc(size);
		if (!value)
		{
			CLI_MSG_PrtErrMsg(UTL_MISC_ERR_MEMORY_OVERFLOW);
			return FALSE;
		}

		get_help = CLI_TYPES_GetGetHelpFunc (current->type);
		if (get_help)
		{
			if (get_help (cmd, current->lparam, current->rparam) == FALSE)
			{
				cli_misc_free(value);
				return FALSE;
			}
		}
		else
		{
			get_value = CLI_TYPES_GetGetValueFunc(current->type);
			if (get_value(cmd, current->lparam, current->rparam, value) == FALSE)
			{
				cli_misc_free(value);
				return FALSE;
			}
		}

	}
	else
	{ // match keyword or enum
		value = NULL;
		size = strlen(cmd);
		if (strncmp (current->name, cmd, size) != 0)
		{
			return FALSE;
		}
		if (size == strlen (current->name))   //best match in this command
		{
			result->most_match = TRUE;
			result->count = 0;

		}
		if (current->type == CLI_TYPES_ENUM)
		{
			value = CLI_MISC_Malloc(sizeof(UI32_T));
			if (!value)
			{
				CLI_MSG_PrtErrMsg(UTL_MISC_ERR_MEMORY_OVERFLOW);
				return FALSE;
			}
			*(UI32_T *)value = current->lparam;
		}
	}

	result->list[result->count++] = current;
	cli_misc_free(value);

	return TRUE;
}



/*******************************************************************************
 *
 * Func		  : CLI_TYPES_Init
 * DESCRIPTION: Init resources for CLI Types
 * INPUT	  : NA
 * OUTPUT	  : NA
 * RETURN	  : NA
 * NOTES	  : NA
 * HISTORY	  :
 *	 2009-Feb-13 by wangbin -- Create
 *
*******************************************************************************/
void CLI_TYPES_Init(void)
{
	// register all enumlists.
	s_cli2_types_enumlist_count = 0;

	CLI_TYPES_REG_ENUMARRAY("bps", _cli2_types_enumlist_bps);
	CLI_TYPES_REG_ENUMARRAY("operator", _cli2_types_enumlist_operator);
	CLI_TYPES_REG_ENUMARRAY("month", _cli2_types_enumlist_month);
	CLI_TYPES_REG_ENUMARRAY("level", _cli2_types_enumlist_level);
	CLI_TYPES_REG_ENUMARRAY("log-level", _cli2_types_enumlist_log_level);

	CLI_TYPES_REG_ENUMARRAY("workday", _cli2_types_enumlist_workday);
	CLI_TYPES_REG_ENUMARRAY("offset", _cli2_types_enumlist_offset);
	CLI_TYPES_REG_ENUMARRAY("weekday", _cli2_types_enumlist_weekday);

	// register functions for primitive type
	memset(_cli2_types_argufunc_list, 0x0, sizeof(_cli2_types_argufunc_list));
	cli2_types_reg_argufunc(_cli2_types_argufunc_collect, sizeof(_cli2_types_argufunc_collect) / sizeof(CLI_TYPES_ARGUFUNC_T));

	// init alias.
	CLI_ALIAS_Init();

	return;
}



typedef struct  // This structure is used to register an alias to CLI kernel
{
	I8_T *name; // alias name
	I8_T *define; // range of the alias
	CLI_PRIMITIVE_SYNTAX_T type; // primitive argument type of the alias
#ifdef CLI_WORD_WITH_HELP
	I8_T *help_en; // English help
#ifdef CLI_WORD_WITH_LOCAL_HELP
	I8_T *help_local; // local help
#endif
#endif
} CLI_ALIAS_REGNODE_T;

typedef struct  // this structure is used after alias is registered.
{
	CLI_PRIMITIVE_SYNTAX_T	type; 			// primitive CLI argument type
	I8_T 					*name;  		// alias type name
	LPARAM 					lparam; 		// first param of the range
	RPARAM 					rparam; 		// second param of the range
#ifdef CLI_WORD_WITH_HELP
	I8_T 					*help_en; 		// English help of the alias
#ifdef CLI_WORD_WITH_LOCAL_HELP
	I8_T 					*help_local; 	// local help of the alias
#endif
#endif
} CLI_ALIAS_DBNODE_T;

typedef struct  // collect all alias dbnode
{
	UI32_T count; // alias names have been registered
	CLI_ALIAS_DBNODE_T entry[CLI_MAX_ALIAS_NAME];
} CLI_ALIAS_DBLIST_T;

#define CLI_ALIAS_FIRST CLI_TYPES_KEYWORD // first alias type
static CLI_ALIAS_DBLIST_T s_cli_alias_dblist; // used to save all registered alias

/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 cli2_alias_get_node_by_index
 *
 * DESCRIPTION:
 *	 Get an alias node by it's index.
 *
 * INPUT:
 *	 index -- index of the alias dbnode
 *
 * OUTPUT:
 *	 NA
 *
 * RETURN:
 *	 pointer of the db node
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-19 by wangbin -- Create
 *
*******************************************************************************/
static CLI_ALIAS_DBNODE_T *cli2_alias_get_node_by_index (IN UI32_T index)
{
	return &s_cli_alias_dblist.entry[index - CLI_ALIAS_FIRST];
}



#define cli2_tolower(ch) ((((ch)>='A') && ((ch)<='Z')) ? (((ch) - 'A') + 'a') : (ch))
/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 __cli2_alias_get_node_by_name
 *
 * DESCRIPTION:
 *	 Get an alias dbnode info by it's name
 *
 * INPUT:
 *	 name -- name of the alias
 *	 len  -- length of the name
 *
 * OUTPUT:
 *	 NA
 *
 * RETURN:
 *	 NULL -- the name of the alias isn't registered.
 *	 not NULL -- pointer of the db node
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-19 by wangbin -- Create
 *
*******************************************************************************/
static CLI_ALIAS_DBNODE_T *__cli2_alias_get_node_by_name (
	IN const I8_T *name,
	IN I32_T len)
{
	I32_T 				i;
	I32_T 				j;
	CLI_ALIAS_DBNODE_T *node;

	CLI_MISC_Assert(name);
	for (i = CLI_ALIAS_FIRST; i < s_cli_alias_dblist.count; i++)
	{
		node = cli2_alias_get_node_by_index(i);

		if (len != strlen (node->name))
		{
			continue;
		}

		for (j = 0; j < len; j++)
		{
			if (cli2_tolower(node->name[j]) != cli2_tolower(name[j]))
			{
				break;
			}
		}

		if (j == len)
		{
			// find node in the exact name
			return node;
		}
	}

	return NULL;
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 cli2_alias_reg_nodes
 *
 * DESCRIPTION:
 *	 Register an array of alias
 *
 * INPUT:
 *	 ptrList[] -- pointer of the array
 *	 size -- size of the array
 *
 * OUTPUT:
 *	 NA
 *
 * RETURN:
 *	 TRUE -- success
 *	 FALSE -- failure
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-19 by wangbin -- Create
 *
*******************************************************************************/
static BOOL_T cli2_alias_reg_nodes (
	IN CLI_ALIAS_REGNODE_T * ptrList,
	IN UI32_T size)
{
	UI32_T i;
	CLI_ALIAS_DBNODE_T *dbnode;
	CLI_TYPES_GET_RANGE_FUNC_T *get_range;

#ifdef __LINUX_DEBUG__
	UI32_T index;
	CLI_MISC_Assert(ptrList && size && ptrList->define);
	CLI_MISC_Assert(s_cli_alias_dblist.count + size - CLI_ALIAS_FIRST <= CLI_MAX_ALIAS_NAME);
	printf ("alias-size=%d, max-alias-size=%d\r\n", size, CLI_MAX_ALIAS_NAME);
#endif
	for (i = 0; i < size; i++)
	{
#ifdef __LINUX_DEBUG__
		CLI_MISC_Assert((ptrList->name) && (strlen (ptrList->name)));
		for (index = CLI_ALIAS_FIRST; index < s_cli_alias_dblist.count; index++)
		{
			dbnode = cli2_alias_get_node_by_index (index);
			if (strcmp(dbnode->name, ptrList->name) == 0)
			{
				printf ("(alias redefined)name=%s\r\n", ptrList->name);
			}
		}
#endif

		dbnode = cli2_alias_get_node_by_index (s_cli_alias_dblist.count);
		get_range = CLI_TYPES_GetGetRangeFunc (ptrList->type);
		CLI_MISC_Assert(get_range);
		get_range (ptrList->define, ptrList->define + strlen (ptrList->define),
			&dbnode->lparam, &dbnode->rparam);
		dbnode->type = ptrList->type;
		dbnode->name = ptrList->name;
		dbnode->help_en = ptrList->help_en;
		dbnode->help_local = ptrList->help_local;

		s_cli_alias_dblist.count++;
		ptrList++;
	}

	return TRUE;
}

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_ALIAS_Set_AliasRange
 *
 * DESCRIPTION:
 *   Change the range of the alias.
 *
 * INPUT:
 *   alias_name -- name of the alias
 *   alias_range -- range of the alias
 *
 * OUTPUT:
 *   None
 *
 * RETURN:
 *   TRUE -- set alias range to new value success
 *   FALSE -- set alias range to new value failure
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2009-May-26 by wangbin -- Create
 *
*******************************************************************************/
BOOL_T CLI_ALIAS_Set_AliasRange(
	IN const I8_T *alias_name,
	IN const I8_T *alias_range)
{
	CLI_ALIAS_DBNODE_T *p_node;
	CLI_TYPES_GET_RANGE_FUNC_T *get_range;
	LPARAM lparam;
	RPARAM rparam;

	p_node = __cli2_alias_get_node_by_name(alias_name, strlen (alias_name));
	if (!p_node)
	{
		return FALSE;
	}

	get_range = CLI_TYPES_GetGetRangeFunc(p_node->type);
	if (!get_range)
	{
		return FALSE;
	}

	if (!get_range(alias_range, alias_range + strlen (alias_range), &lparam, &rparam))
	{
		return FALSE;
	}

	p_node->lparam = lparam;
	p_node->rparam = rparam;

	return TRUE;
}



/* please register all alias here */
static CLI_ALIAS_REGNODE_T s_cli_alias_list[] =
{
/* =============================Single Value========================================*/

/*Begin for the alias which base type is UI32_T */
	{
		"uint",
		"0-4294967295",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"privilege",
		"1-15",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"interval",
		"1-2147483647",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"fast-port",
		"0-65535",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"vlan-id",
		"1-4094",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"svid",
		"0-4094",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"repeat-count",
		"1-65535",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"timeout",
		"1-65535",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"group-num",
		"1-64",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"acl-number",
		"1-65535",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"rule-number",
		"1-65535",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"icmp-type",
		"1-255",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"icmp-code",
		"1-255",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"precedence-value",
		"1-8",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"cos-value",
		"1-8",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"tos-value",
		"1-16",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"dscp-value",
		"1-64",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"ip-protocol-type",
		"1-255",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"ethernet-protocol-type",
		"1-65535",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"queue-number",
		"1-8",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"queue-id",
		"1-8",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"queue-weight",
		"0-100",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"rate-limit",
		"1-4294967294",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"bucket-size",
		"1-4294967294",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"version",
		"0-65535",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"hop",
		"1-255",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"aging-time",
		"10-1000000",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"upd-port",
		"1-65535",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"speed-kBps",
		"64-10240000",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"tcp-port",
		"1-65535",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"percent",
		"0-100",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"prefixlen",
		"0-128",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"the IPv6 prefix lengh of the entry",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"seconds",
		"0-4294967295",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"centi-second",
		"0-4294967295",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"milli-seconds",
		"0-4294967295",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"range",
		"0-4294967295",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"gmt-hour",
		"0-13",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"start-month",
		"1-12",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"end-month",
		"1-12",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},

	{
		"start-date",
		"1-31",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"end-date",
		"1-31",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"hour-id",
		"0-23",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"minute-id",
		"0-59",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"second-id",
		"0-59",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"week-id",
		"1-54",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"weekday-id",
		"1-7",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"day-id",
		"1-365",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"statistics-threshold-type",
		"1-12",
		CLI_TYPES_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
/* End for the alias which base type is UI32_T */

/* Begin for the alias which base type is I32_T */
	{
		"int",
		"-2147483647-2147483647",
		CLI_TYPES_I32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"temperature",
		"-2147483647-2147483647",
		CLI_TYPES_I32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"width",
		"-2147483647-2147483647",
		CLI_TYPES_I32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"value",
		"-2147483647-2147483647",
		CLI_TYPES_I32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"start-sn",
		"1-4294967294",
		CLI_TYPES_I32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"inc-sn",
		"1-4294967294",
		CLI_TYPES_I32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"sn",
		"1-4294967294",
		CLI_TYPES_I32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"profile-id",
		"-2147483647-2147483647",
		CLI_TYPES_I32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"max-lock-no",
		"-2147483647-2147483647",
		CLI_TYPES_I32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},

	{
		"min-lock-no",
		"-2147483647-2147483647",
		CLI_TYPES_I32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"times",
		"-2147483647-2147483647",
		CLI_TYPES_I32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"metric",
		"-2147483647-2147483647",
		CLI_TYPES_I32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"priority",
		"-2147483647-2147483647",
		CLI_TYPES_I32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"classification-id",
		"-2147483647-2147483647",
		CLI_TYPES_I32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"dscp",
		"-2147483647-2147483647",
		CLI_TYPES_I32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"instance",
		"1-65535",
		CLI_TYPES_I32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
/* End for the alias which base type is I32_T */

/* Begin for the alias which base type is float */
	{
		"float",
		"",
		CLI_TYPES_FLOAT,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"degrees",
		"",
		CLI_TYPES_FLOAT,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"voltage",
		"",
		CLI_TYPES_FLOAT,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"milliampere", /* 毫安 */
		"",
		CLI_TYPES_FLOAT,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"milliwatts", /* 毫瓦 */
		"",
		CLI_TYPES_FLOAT,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
/* End for the alias which base type is float */

/* Begin for the alias which base type is BINARY */
	{
		"bin",
		"0x0-0xFFFFFFFF",
		CLI_TYPES_BINARY,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
/* End for the alias which base type is BINARY */

/* Begin for the alias which base type is HEX */
	{
		"hex",
		"0x0-0xFFFFFFFF",
		CLI_TYPES_HEX,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"module-id",
		"0x0-0xFFFFFFFF",
		CLI_TYPES_HEX,
#ifdef CLI_WORD_WITH_HELP
		NULL,
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"register-address",
		"0x0-0xFFFFFFFF",
		CLI_TYPES_HEX,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"register-base",
		"0x0-0xFFFFFFFF",
		CLI_TYPES_HEX,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"register-offset",
		"0x0-0xFFFFFFFF",
		CLI_TYPES_HEX,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"register-value",
		"0x0-0xFFFFFFFF",
		CLI_TYPES_HEX,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"tpid",
		"0x0-0xFFFE",
		CLI_TYPES_HEX,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"ethernet-protocol-type-hex",
		"0x0-0xFFFF",
		CLI_TYPES_HEX,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
/* End for the alias which base type is HEX */

/* Begin for the alias which base type is STRING */
	{
		"string",
		"1-31",
		CLI_TYPES_STRING,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"word",
		"1-32",
		CLI_TYPES_STRING,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"line",
		"1-1",
		CLI_TYPES_STRING,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"text",
		"1-255",
		CLI_TYPES_STRING,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"tcpparttype",
		"1-255",
		CLI_TYPES_STRING,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},

	{
		"description",
		"1-32",
		CLI_TYPES_STRING,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
/* End for the alias which base type is STRING */

/* Begin for the alias which base type is STRING_WITHOUT_WHITESPACE */
	{
		"str-without-sp",
		"1-31",
		CLI_TYPES_STRING_WITHOUT_WHITESPACE,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"username",
		"1-31",
		CLI_TYPES_STRING_WITHOUT_WHITESPACE,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"password",
		"1-31",
		CLI_TYPES_STRING_WITHOUT_WHITESPACE,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"port-group",
		"1-63",
		CLI_TYPES_STRING_WITHOUT_WHITESPACE,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
/* End for the alias which base type is STRING_WITHOUT_WHITESPACE */

/* Begin for the alias which base type is NAME */
	{
		"name",
		"1-31",
		CLI_TYPES_NAME,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"community",
		"1-31",
		CLI_TYPES_NAME,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"network-name",
		"1-16",
		CLI_TYPES_NAME,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"directory",
		"1-128",
		CLI_TYPES_NAME,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"community-name",
		"1-32",
		CLI_TYPES_NAME,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"group-name",
		"1-32",
		CLI_TYPES_NAME,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"rule-name",
		"1-255",
		CLI_TYPES_NAME,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"source-path-file-name",
		"1-256",
		CLI_TYPES_NAME,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"target-path-file-name",
		"1-256",
		CLI_TYPES_NAME,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"path-name",
		"1-64",
		CLI_TYPES_NAME,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"image-name",
		"1-32",
		CLI_TYPES_NAME,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"file-name",
		"1-64",
		CLI_TYPES_NAME,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"pool-name",
		"1-12",
		CLI_TYPES_NAME,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"access-list-name",
		"1-16",
		CLI_TYPES_NAME,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"map-name",
		"1-16",
		CLI_TYPES_NAME,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"vlan-name",
		"1-32",
		CLI_TYPES_NAME,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
/* End for the alias which base type is NAME */

/* Begin for the alias which base type is MULTIWORD */
/* End for the alias which base type is MULTIWORD */

/* Begin for the alias which base type is SENTENCE */
/* End for the alias which base type is SENTENCE */

/* Begin for the alias which base type is MAC Address */
	{
		"mac-address",
		"",
		CLI_TYPES_MACADDR,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"mac-mask",
		"",
		CLI_TYPES_MACADDR,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"source-mac",
		"",
		CLI_TYPES_MACADDR,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"source-mac-wildcard",
		"",
		CLI_TYPES_MACADDR,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"dest-mac",
		"",
		CLI_TYPES_MACADDR,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"dest-mac-wildcard",
		"",
		CLI_TYPES_MACADDR,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
/* End for the alias which base type is MAC Address */

/* Begin for the alias which base type is Multicast MAC Address */
	{
		"multicast-mac-address",
		"",
		CLI_TYPES_MMACADDR,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
/* End for the alias which base type is Multicast MAC Address */

/* Begin for the alias which base type is Unitcast MAC Address */
	{
		"unitcast-mac-address",
		"",
		CLI_TYPES_UMACADDR,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
/* End for the alias which base type is Unitcast MAC Address */

/* Beding for the alias which base type is IPv4 Address */
	{
		"ip-address",
		"",
		CLI_TYPES_IPADDR,
#ifdef CLI_WORD_WITH_HELP
		"the IP address of the entry",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"ip-mask",
		"",
		CLI_TYPES_IPADDR,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"source-ip",
		"",
		CLI_TYPES_IPADDR,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"source-ip-wildcard",
		"",
		CLI_TYPES_IPADDR,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"dest-ip",
		"",
		CLI_TYPES_IPADDR,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"dest-ip-wildcard",
		"",
		CLI_TYPES_IPADDR,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"server-ip",
		"",
		CLI_TYPES_IPADDR,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"router-id",
		"",
		CLI_TYPES_IPADDR,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"cluster-id",
		"",
		CLI_TYPES_IPADDR,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
/* End for the alias which base type is IPv4 Address */

/* Beding for the alias which base type is IPv4 Address with mask */
	{
		"network-address",
		"",
		CLI_TYPES_IPNETADDR,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
/* End for the alias which base type is IPv4 Address with mask */

/* Beding for the alias which base type is IPv4 Multicast Address */
	{
		"multicast-ip-address",
		"",
		CLI_TYPES_IPMULTICASTADDR,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
/* End for the alias which base type is IPv4 Multicast Address */

/* Beding for the alias which base type is IPv4 Multicast Address Chain */
	{
		"multicast-ip-address-list",
		"",
		CLI_TYPES_IPMULTICASTADDRCHAIN,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
/* End for the alias which base type is IPv4 Multicast Address Chain */

/* Begin for the alias which base type is IPv6 Address */
	{
		"ipv6-address",
		"",
		CLI_TYPES_IPV6ADDR,
#ifdef CLI_WORD_WITH_HELP
		"the IPv6 address of the entry",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"ipv6-mask",
		"",
		CLI_TYPES_IPV6ADDR,
#ifdef CLI_WORD_WITH_HELP
		"the IPv6 address mask of the entry",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
/* End for the alias which base type is IPv6 Address */

/* Begin for the alias which base type is IPv6NET Address */
	{
		"ipv6-network-address",
		"",
		CLI_TYPES_IPV6NETADDR,
#ifdef CLI_WORD_WITH_HELP
		"the IPv6 network address of the entry",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
/* End for the alias which base type is IPv6NET Address */

/* Begin for the alias which base type is IPv6 Multicast Address */
	{
		"multicast-ipv6-address",
		"",
		CLI_TYPES_IPV6MULTICASTADDR,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
/* End for the alias which base type is IPv6 Multicast Address */


/* Begin for the alias which base type is IPv6 Multicast Address Chain */
	{
		"multicast-ipv6-address-list",
		"",
		CLI_TYPES_IPV6MULTICASTADDRCHAIN,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
/* End for the alias which base type is IPv6 Multicast Address Chain */

/* Begin for the alias which base type is Frame Port Number */
	{
		"port-frame",
		"",
		CLI_TYPES_FRAMEPORTNUM,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		"机框式端口号"
#endif
#endif
	},
/* End for the alias which base type is Stacking Port Number */

/* Begin for the alias which base type is Stacking Port List */
	{
		"port-frame-list",
		"",
		CLI_TYPES_STACKINGPORTLIST,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"storm-group-list",
		"",
		CLI_TYPES_STACKINGPORTLIST,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
/* End for the alias which base type is Stacking Port List */

/* Begin for the alias which base type is OID */
	{
		"oid",
		"",
		CLI_TYPES_OID,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
/* End for the alias which base type is OID */

/* Begin for the alias which base type is SHORTTIME */
	{
		"HH:MM",
		"00:00-23:59",
		CLI_TYPES_SHORTTIME,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
/* End for the alias which base type is SHORTTIME */

/* Begin for the alias which base type is LONGTIME */
	{
		"HH:MM:SS",
		"00:00:00-23:59:59",
		CLI_TYPES_LONGTIME,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
/* End for the alias which base type is LONGTIME */

/* Begin for the alias which base type is DATE */
	{
		"dd-mm-yyyy",
		"",
		CLI_TYPES_DATE,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"yyyy-mm-dd",
		"",
		CLI_TYPES_DATECN,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
/* End for the alias which base type is DATE */

/* Begin for the alias which base type is CLIG1 DATE */
	{
		"date",
		"",
		CLI_TYPES_CLIG1_DATE,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
/* End for the alias which base type is CLIG1 DATE */

/* Begin for the alias which base type is CLIG1 TIME */
	{
		"time",
		"",
		CLI_TYPES_CLIG1_TIME,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
/* End for the alias which base type is CLIG1 TIME */

/* Begin for the alias which base type is CLIG1 TIME2 */
	{
		"start-time",
		"",
		CLI_TYPES_CLIG1_TIME2,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"end-time",
		"",
		CLI_TYPES_CLIG1_TIME2,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"offset",
		"",
		CLI_TYPES_CLIG1_TIME2,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
/* End for the alias which base type is CLIG1 TIME2 */

/* Begin for the alias which base type is CLIG1 DAYLIST */
	{
		"day-list",
		"",
		CLI_TYPES_CLIG1_DAYLIST,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
/* End for the alias which base type is CLIG1 DAYLIST */

/* Begin for the alias which base type is CLIG1 MEDIA */
	{
		"drive-id",
		"",
		CLI_TYPES_CLIG1_MEDIA,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
/* End for the alias which base type is CLIG1 MEDIA */


/* =============================List Value========================================*/

/* Begin for the alias which base type is UI32_T chain */
	{
		"value-list",
		"1-90000",
		CLI_TYPES_UI32CHAIN,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"rule-id-list",
		"1-128",
		CLI_TYPES_UI32CHAIN,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"profile-id-list",
		"1-128",
		CLI_TYPES_UI32CHAIN,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"dscp-list",
		"1-64",
		CLI_TYPES_INTLIST,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"priority-list",
		"0-63",
		CLI_TYPES_UI32CHAIN,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"level-list",
		"0-7",
		CLI_TYPES_UI32CHAIN,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"cos-id-list",
		"1-8",
		CLI_TYPES_INTLIST,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"mepid-list",
		"1-8191",
		CLI_TYPES_UI32CHAIN,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"access-id-list",
		"1-128",
		CLI_TYPES_UI32CHAIN,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
/* End for the alias which base type is UI32_T chain */

/* Begin for the alias which base type is INT List */
	{
		"unit-list",
		"1-"STACKING_STRING_MAX_UNIT"",
		CLI_TYPES_INTLIST,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
/* End for the alias which base type is INT List */

/* Begin for the alias which base type is Standalone Port List */
	{
		"port-num-list",
		"",
		CLI_TYPES_STANDALONEPORTLIST,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
/* End for the alias which base type is Standalone Port List */

/* Begin for the alias which base type is VLAN List */
	{
		"vlan-id-list",
		"1-4094",
		CLI_TYPES_VLANLIST,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
/* End for the alias which base type is VLAN List */

/* Begin for the alias which base type is ENUMUI32 List */
	{
		"level",
		"level",
		CLI_TYPES_ENUMLIST_UI32,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
/* End for the alias which base type is ENUMUI32 List */

/* Begin for the alias which base type is VLANNAME List */
	{
		"vlan-list-name",
		"1-4094",
		CLI_TYPES_VLANLIST_NAME,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
/* End for the alias which base type is VLANNAME List */

/* Begin for the alias which base type is ENUMSTRING List */
	{
		"month-name", // Jan, Feb, ...
		"month",
		CLI_TYPES_ENUMLIST_STRING,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"week-name", // [1 | 2 | 3 | 4 | last]
		"workday",
		CLI_TYPES_ENUMLIST_STRING,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"weekday-name", // [Sun | Mon | Tue | Wed | Thu | Fri | Sat]
		"weekday",
		CLI_TYPES_ENUMLIST_STRING,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"operator",
		"operator",
		CLI_TYPES_ENUMLIST_STRING,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
/* End for the alias which base type is ENUMSTRING List */

/* Begin for the alias which base type is Month */
	{
		"month",
		"",
		CLI_TYPES_MONTH,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
/* End for the alias which base type is Month */

/* Begin for the alias which base type is Week Day */
	{
		"weekday",
		"",
		CLI_TYPES_WEEKDAY,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"start-day",
		"",
		CLI_TYPES_WEEKDAY,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"end-day",
		"",
		CLI_TYPES_WEEKDAY,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
/* End for the alias which base type is Week Day */

/* Begin for the alias which base type is Week */
	{
		"week",
		"",
		CLI_TYPES_WEEK,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"start-week",
		"",
		CLI_TYPES_WEEK,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},
	{
		"end-week",
		"",
		CLI_TYPES_WEEK,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		NULL
#endif
#endif
	},

/* End for the alias which base type is Week */

/* Begin for the alias which base type is onu id, ex 1/2:3 */
	{
		"onu-id",
		"",
		CLI_TYPES_ONUID,
#ifdef CLI_WORD_WITH_HELP
		"",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		""
#endif
#endif
	},
/* End for the alias which base type is onu id, ex 1/2:3 */

/* Begin for the alias which base type is 可以多选的枚举字符，中间以都好间隔，如风暴抑制："u" or "m" or "b" or "u,m" or "u,b" or "m,b" or "u,m,b" */
	{
		"storm-mode",
		"u,m,b,U,M,B",
		CLI_TYPES_STORM_CONTROL,
#ifdef CLI_WORD_WITH_HELP
		"u | m | b | u,m | u,m,b | ...",
#ifdef CLI_WORD_WITH_LOCAL_HELP
		""
#endif
#endif
	},
/* End for the alias which base type is 可以多选的枚举字符，中间以都好间隔，如风暴抑制："u" or "m" or "b" or "u,m" or "u,b" or "m,b" or "u,m,b" */
};



/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 CLI_ALIAS_Init
 *
 * DESCRIPTION:
 *	 Init global variables in alias module
 *
 * INPUT:
 *	 NA
 *
 * OUTPUT:
 *	 NA
 *
 * RETURN:
 *	 NA
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-19 by wangbin -- Create
 *
*******************************************************************************/
void CLI_ALIAS_Init (void)
{
	memset(&s_cli_alias_dblist, 0x0, sizeof(CLI_ALIAS_DBLIST_T));
	s_cli_alias_dblist.count = CLI_ALIAS_FIRST;

	/* List the CLI G2 parameter types(alias list) bellow */
	cli2_alias_reg_nodes(s_cli_alias_list,	sizeof(s_cli_alias_list)/sizeof(CLI_ALIAS_REGNODE_T));
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *	 CLI_ALIAS_Parse
 *
 * DESCRIPTION:
 *	 Parse an alias in syntax command to check the correction of it and get the
 *		range and other message of it.
 *
 * INPUT:
 *	 alias -- alias string in syntax command. it may be in <> or in uppercase.
 *	 end -- end pointer of the string.
 *
 * OUTPUT:
 *	 node -- alias messages(name, type, range and help information)
 *
 * RETURN:
 *	 TRUE -- success
 *	 FALSE -- failure
 *
 * NOTES:
 *	 NA
 *
 * HISTORY:
 *	 2009-Mar-19 by wangbin -- Create
 *
*******************************************************************************/
BOOL_T CLI_ALIAS_Parse(
	IN const I8_T *alias,
	IN const I8_T *end,
	OUT CLI_PARA_WORD_T * node)
{
	const I8_T *name;
	I32_T name_len;
	CLI_ALIAS_DBNODE_T *alias_dbnode;
	CLI_TYPES_GET_RANGE_FUNC_T *get_range;

	CLI_MISC_Assert(alias && end && node);
	// get alias name
	alias = CLI_MISC_Skip_WhiteSpace(alias);
	name = alias;
	while (CLI_MISC_Is_Alias_Char(*alias))
	{
		alias++;
	}
	name_len = alias - name;

	alias = CLI_MISC_Skip_WhiteSpace(alias);	// skip white spaces
	// get alias db node
	alias_dbnode = __cli2_alias_get_node_by_name(name, name_len);
	if (!alias_dbnode)
	{
		return FALSE;
	}

	node->name = alias_dbnode->name;
	node->name_len = name_len;
	node->type = alias_dbnode->type;
#ifdef CLI_WORD_WITH_HELP
	if (alias_dbnode->help_en == NULL)
	{
		node->help_en = NULL;
		node->help_en_len = 0;
	}
	else if (*alias_dbnode->help_en == '\0')
	{
		node->help_en = NULL;
		node->help_en_len = 0;
	}
	else
	{
		node->help_en = alias_dbnode->help_en;
		node->help_en_len = strlen (node->help_en);
	}
#ifdef CLI_WORD_WITH_LOCAL_HELP
	if (alias_dbnode->help_local && (*alias_dbnode->help_local != '\0'))
	{
		node->help_local = alias_dbnode->help_local;
		node->help_local_len = strlen (node->help_local);
	}
	else
	{
		node->help_local = node->help_en;
		node->help_local_len = 0;
	}
#endif
#endif
	get_range = CLI_TYPES_GetGetRangeFunc (node->type);

	// get range of the alias
	if ((alias >= end) || (get_range (alias, end, &node->lparam, &node->rparam) == FALSE))
	{
		// get default range
		node->lparam = alias_dbnode->lparam;
		node->rparam = alias_dbnode->rparam;
	}

	return TRUE;
}



/**************************************************************************
FUNCTION NAME:
	CLI_ALIAS_Clac_ParaValueSize

DESCRIPTION:
	Calculate the parameter value size.

INPUT:
	type			: parameter base type
	ptr			: input string or parameter value

OUTPUT:

RETURN:
	The size of parameter value

NOTES:

HISTORY:

**************************************************************************/
UI32_T CLI_ALIAS_Clac_ParaValueSize(
	IN CLI_PRIMITIVE_SYNTAX_T 	type,
	IN const I8_T 				*ptr)
{
	UI32_T size; // size of the (cli_value_t *)p->value.

	switch (type)
	{
	case CLI_TYPES_KEYWORD:
		size = strlen(ptr) + 1;
		break;

	case CLI_TYPES_ENUM:
		size = sizeof(UI32_T);
		break;

	case CLI_TYPES_STRING:
	case CLI_TYPES_STRING_WITHOUT_WHITESPACE:
	case CLI_TYPES_NAME:
	case CLI_TYPES_MULTIWORD:
	case CLI_TYPES_SENTENCE:
	case CLI_TYPES_ENUMLIST_STRING:
	case CLI_TYPES_CLIG1_MEDIA:
		size = strlen(ptr) + 1;
		break;

	case CLI_TYPES_MONTH:
	case CLI_TYPES_WEEKDAY:
	case CLI_TYPES_WEEK:
	case CLI_TYPES_ENUMLIST_UI32:
		size = sizeof(UI32_T);
		break;

	case CLI_TYPES_IPADDR:
	case CLI_TYPES_IPMULTICASTADDR:
		size = sizeof(UI32_T);
		break;

	case CLI_TYPES_IPNETADDR:
		size = sizeof(UI32_T) * 2;
		break;

	case CLI_TYPES_IPMULTICASTADDRCHAIN:
	case CLI_TYPES_IPV6MULTICASTADDRCHAIN:
		size = CLI_API_MAX_CMD_LEN;
		break;

	case CLI_TYPES_IPV6ADDR:
	case CLI_TYPES_IPV6MULTICASTADDR:
		size = sizeof(LA3_IP6ADDR) + CLI_MAX_IPV6_INTERFACE_NAME_LEN;
		break;

	case CLI_TYPES_IPV6NETADDR:
		size = sizeof(CLI_IPV6_NET_ADDR);
		break;

	case CLI_TYPES_FRAMEPORTNUM:
		size = sizeof(cli_pid_t);
		break;

	case CLI_TYPES_STACKINGPORTLIST:
#if 0
		size = sizeof(ST_PORTLIST_T);
#else
		size = 0;
		CLI_DBG_NOTSUPPORTED(l_mdl_id);
#endif
		break;

	case CLI_TYPES_STANDALONEPORTLIST:
		size = sizeof(PORTLIST_T);
		break;

	case CLI_TYPES_UI32:
		size = sizeof(UI32_T);
		break;

	case CLI_TYPES_I32:
		size = sizeof(I32_T);
		break;

	case CLI_TYPES_UI32CHAIN:
		size = CLI_API_MAX_CMD_LEN;
		break;

	case CLI_TYPES_INTLIST:
		size = sizeof(CLI_API_INTLIST_T);
		break;

	case CLI_TYPES_VLANLIST:
		size = sizeof(VID_LIST_T);
		break;

	case CLI_TYPES_VLANLIST_NAME:
		size = sizeof(CLI_TYPE_VLANLIST_NAME_T);
		break;

	case CLI_TYPES_MACADDR:
	case CLI_TYPES_MMACADDR:
	case CLI_TYPES_UMACADDR:
		size = 6;
		break;

	case CLI_TYPES_SHORTTIME:
		size = sizeof(CLI_TYPE_TIME_T);
		break;

	case CLI_TYPES_LONGTIME:
		size = sizeof(CLI_TYPE_TIME_T);
		break;

	case CLI_TYPES_DATE:
	case CLI_TYPES_DATECN:
		size = sizeof(CLI_TYPE_DATE_T);
		break;

	case CLI_TYPES_CLIG1_DATE:
	case CLI_TYPES_CLIG1_TIME:
		size = sizeof(DEV_RTC_TIME_T);
		break;

	case CLI_TYPES_CLIG1_TIME2:
		size = sizeof(SNTP_IF_DST_T);
		break;

	case CLI_TYPES_CLIG1_DAYLIST:
		size = sizeof(PORTLIST_T);
		break;

	case CLI_TYPES_HEX:
		size = sizeof(UI32_T);
		break;

	case CLI_TYPES_BINARY:
		size = sizeof(UI32_T);
		break;

	case CLI_TYPES_OID:
		size = sizeof(CLI_OID_T);
		break;

	case CLI_TYPES_FLOAT:
		size = sizeof(float);
		break;

	case CLI_TYPES_ONUID:
		size = sizeof(cli_onuid_t);
		break;

	case CLI_TYPES_STORM_CONTROL:
		size = sizeof(cli_sc_e);
		break;

	default:
		size = sizeof(UI32_T);
		break;
	}

	return size;
}



/**************************************************************************
FUNCTION NAME:
	CLI_ALIAS_GetParaType_ByName

DESCRIPTION:
	Get parameter type by input name string.

INPUT:
	name		: parameter name string
	len			: length of name string

OUTPUT:

RETURN:
	parameter type
	-1			: don't have this parameter with input name

NOTES:

HISTORY:

**************************************************************************/
CLI_PRIMITIVE_SYNTAX_T CLI_ALIAS_GetParaType_ByName(
	IN const I8_T 	*name,
	IN I32_T 		len)
{
	CLI_ALIAS_DBNODE_T *node;

	/* get the parameter node by input name */
	node = __cli2_alias_get_node_by_name(name, len);

	if (NULL == node)
	{
		/* don't have this parameter by input name */
		return -1;
	}

	return node->type;
}



/**************************************************************************
FUNCTION NAME:
	CLI_ALIAS_GetParaFormat_ByParaString

DESCRIPTION:
	Get the parameter format string by input parameter string.

INPUT:
	para_str	: parameter string(Ex: <int 1-100>)

OUTPUT:
	format_str	: used to store the translated parameter format string

RETURN:
	TRUE		: Get success
	FALSE		: the parameter string is error

NOTES:

HISTORY:

**************************************************************************/
BOOL_T CLI_ALIAS_GetParaFormat_ByParaString(
	IN I8_T 	*para_str,
	OUT I8_T 	*format_str)
{
	I8_T 					*src_ptr, *tmp_ptr;
	I8_T 					para_name[80];
	CLI_PRIMITIVE_SYNTAX_T para_type;

	src_ptr = CLI_MISC_Skip_WhiteSpace(para_str);
	if (*src_ptr != '<')
	{
		/* it's not parameter string */
		return FALSE;
	}
	else
	{
		/* skip the '<' and point to the parameter name */
		src_ptr++;
		src_ptr = CLI_MISC_Skip_WhiteSpace(src_ptr);
	}

	/* get the parameter name and get it's type by name */
	tmp_ptr = para_name;
	while (*src_ptr && (*src_ptr != ' ') && (*src_ptr != '\t') && (*src_ptr != '>'))
	{
		*tmp_ptr++ = *src_ptr++;
	}

	*tmp_ptr = '\0';
	para_type = CLI_ALIAS_GetParaType_ByName(para_name, strlen(para_name));

	/* skip the white space, point to the range or the end '>' */
	src_ptr = CLI_MISC_Skip_WhiteSpace(src_ptr);

	/* get the parameter format */
	tmp_ptr = format_str;
	switch (para_type)
	{
		case CLI_TYPES_UI32CHAIN:
		case CLI_TYPES_INTLIST:
		case CLI_TYPES_VLANLIST:
		case CLI_TYPES_VLANLIST_NAME:
			memcpy(tmp_ptr, "LIST ", strlen("LIST "));
			tmp_ptr += strlen("LIST ");

		case CLI_TYPES_UI32:
		case CLI_TYPES_I32:
		case CLI_TYPES_HEX:
		case CLI_TYPES_SHORTTIME:
		case CLI_TYPES_LONGTIME:
			*tmp_ptr++ = '<';
			while (*src_ptr && (*src_ptr != '>'))
			{
				*tmp_ptr++ = *src_ptr++;
			}
			*tmp_ptr++ = '>';
			*tmp_ptr = '\0';
			break;

		case CLI_TYPES_FRAMEPORTNUM:
			strcpy(tmp_ptr, "PORT(Ex p1/4 or s2/3)");
			break;

		case CLI_TYPES_STANDALONEPORTLIST:
		case CLI_TYPES_STACKINGPORTLIST:
			strcpy(tmp_ptr, "PORTLIST");
			break;

		case CLI_TYPES_FLOAT:
			strcpy(tmp_ptr, "FLOAT");
			break;

		case CLI_TYPES_BINARY:
			strcpy(tmp_ptr, "BINARY");
			break;

		case CLI_TYPES_STRING:
		case CLI_TYPES_NAME:
			strcpy(tmp_ptr, "WORD");
			break;

		case CLI_TYPES_STRING_WITHOUT_WHITESPACE:
			strcpy(tmp_ptr, "WORD-WORD");
			break;

		case CLI_TYPES_MULTIWORD:
			strcpy(tmp_ptr, "MULTI-WORD");
			break;

		case CLI_TYPES_SENTENCE:
			strcpy(tmp_ptr, "LINE");
			break;

		case CLI_TYPES_MACADDR:
		case CLI_TYPES_MMACADDR:
		case CLI_TYPES_UMACADDR:
			strcpy(tmp_ptr, "H.H.H");
			break;

		case CLI_TYPES_IPADDR:
		case CLI_TYPES_IPMULTICASTADDR:
			strcpy(tmp_ptr, "A.B.C.D");
			break;

		case CLI_TYPES_IPNETADDR:
			strcpy(tmp_ptr, "A.B.C.D/N");
			break;

		case CLI_TYPES_IPMULTICASTADDRCHAIN:
			strcpy(tmp_ptr, "LIST A.B.C.D");
			break;

		case CLI_TYPES_IPV6ADDR:
			strcpy(tmp_ptr, "X:X:X:X::X");
			break;

		case CLI_TYPES_IPV6NETADDR:
		case CLI_TYPES_IPV6MULTICASTADDR:
			strcpy(tmp_ptr, "X:X:X:X::X/N");
			break;

		case CLI_TYPES_IPV6MULTICASTADDRCHAIN:
			strcpy(tmp_ptr, "LIST X:X:X:X::X");
			break;

		case CLI_TYPES_OID:
			strcpy(tmp_ptr, "N.N.N...N");
			break;

		case CLI_TYPES_DATE:
			strcpy(tmp_ptr, "DD-MM-YYYY");
			break;

		case CLI_TYPES_DATECN:
			strcpy(tmp_ptr, "YYYY-MM-DD");
			break;

		case CLI_TYPES_CLIG1_DATE:
			strcpy(tmp_ptr, "DATE(Ex: 31jan2000)");
			break;

		case CLI_TYPES_CLIG1_TIME:
			strcpy(tmp_ptr, "HH:MM:SS");
			break;

		case CLI_TYPES_CLIG1_TIME2:
			strcpy(tmp_ptr, "HH:MM");
			break;

		case CLI_TYPES_CLIG1_DAYLIST:
			strcpy(tmp_ptr, "LIST DAY-STRING(Ex: sun,tue-fri)");
			break;

		case CLI_TYPES_CLIG1_MEDIA:
			strcpy(tmp_ptr, "DRIVE-ID(Ex: c:)");
			break;

		case CLI_TYPES_ENUMLIST_STRING:
		case CLI_TYPES_MONTH:
		case CLI_TYPES_WEEKDAY:
		case CLI_TYPES_WEEK:
			strcpy(tmp_ptr, "ENUM-WORD");
			break;

		case CLI_TYPES_ONUID:
			strcpy(tmp_ptr, "ONU-ID(Ex 1/4:3)");
			break;

		case CLI_TYPES_STORM_CONTROL:
			strcpy(tmp_ptr, "STORM-MODE(Inc u,m,b)");
			break;

		default:
			return FALSE;
	}

	return TRUE;
}



/* End of file */

