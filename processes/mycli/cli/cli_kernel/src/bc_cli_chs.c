
/*==============================================================================
 * FILE NAME  : bc_cli_chs.c
 * VERSION    : 1.0.0
 * DESCRIPTION: 
 * NOTES: 
 * 
 * HISTORY:
 * -----------------------------------------------------------------------------
 * Version 1.0 -- 2015-May-08 by bain.wang@outlook.com
 * [NEW FEATURE]
 * <DESCRIPTION> Create
 *============================================================================*/

////////////////////////////////////////////////////////////////////////////////
// 																			  //
// 							 	头   文   件								  //
// 																			  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_cli_type.h"
#include "bc_cli_chs.h"



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

BOOL_T CLI_CHARSET_Is_AsciiChar (UI8_T ch)
{
	if ((ch > 0x0) && (ch <= 0x7F))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}



BOOL_T CLI_CHARSET_Is_Gb2312FirstChar (UI8_T ch)
{
	if ((ch >= 0xA1) && (ch <= 0xFE))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}



BOOL_T CLI_CHARSET_Is_Gb2312SecondChar (UI8_T ch)
{
	if ((ch >= 0xA1) && (ch <= 0xFE))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}



BOOL_T CLI_CHARSET_Is_Gb2312Char (UI8_T ch1, UI8_T ch2)
{
	if (CLI_CHARSET_Is_Gb2312FirstChar (ch1) && CLI_CHARSET_Is_Gb2312SecondChar(ch2))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}



BOOL_T CLI_CHARSET_Is_GbkFirstChar (UI8_T ch)
{
	if ((ch >= 0x81) && (ch <= 0xFE))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}



BOOL_T CLI_CHARSET_Is_GbkSecondChar (UI8_T ch)
{
	if (((ch >= 0x40) && (ch <= 0x7E)) || ((ch >= 0x80) && (ch <= 0xFE)))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}



BOOL_T CLI_CHARSET_Is_GbkChar (UI8_T ch1, UI8_T ch2)
{
	if (CLI_CHARSET_Is_GbkFirstChar (ch1) && CLI_CHARSET_Is_GbkSecondChar(ch2))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}



I32_T CLI_CHARSET_Get_PrevCharSize(I32_T charset, UI8_T *buf, I32_T idx)
{
	I32_T size = 0;
	I32_T i = 0;

	while ( i < idx)
	{
		if (CLI_CHARSET_Is_AsciiChar(buf[i]))
		{
			size = 1;
		}
		else if (charset == CLI_CHARSET_GB2312)
		{
			if (CLI_CHARSET_Is_Gb2312Char(buf[i], buf[i + 1]))
			{
				size = 2;
			}
			else
			{
				size = 1;
			}
		}
		else if (charset == CLI_CHARSET_GBK)
		{
			if (CLI_CHARSET_Is_GbkChar(buf[i], buf[i + 1]))
			{
				size = 2;
			}
			else
			{
				size = 1;
			}
		}
		else
		{
			size = 1;
		}

		i+= size;
	}

	return size;
}



BOOL_T CLI_CHARSET_Is_CursorInsideChar(I32_T charset, UI8_T *buf, I32_T idx)
{
	I32_T size = 0;
	I32_T i = 0;

	while (i < idx)
	{
		if (CLI_CHARSET_Is_AsciiChar(buf[i]))
		{
			size = 1;
		}
		else if (charset == CLI_CHARSET_GB2312)
		{
			if (CLI_CHARSET_Is_Gb2312Char(buf[i], buf[i + 1]))
			{
				size = 2;
			}
			else
			{
				size = 1;
			}
		}
		else if (charset == CLI_CHARSET_GBK)
		{
			if (CLI_CHARSET_Is_GbkChar(buf[i], buf[i + 1]))
			{
				size = 2;
			}
			else
			{
				size = 1;
			}
		}
		else
		{
			size = 1;
		}

		i+= size;
	}

	if (i > idx)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}



I32_T CLI_CHARSET_Get_NextCharSize(I32_T charset, UI8_T *buf, I32_T idx)
{
	I32_T size = 0;

	if (*buf == '\0')
	{
		return 0;
	}

	if (CLI_CHARSET_Is_AsciiChar(buf[idx]))
	{
		size = 1;
	}
	else if (charset == CLI_CHARSET_GB2312)
	{
		if (CLI_CHARSET_Is_Gb2312Char(buf[idx], buf[idx + 1]))
		{
			size = 2;
		}
		else
		{
			size = 1;
		}
	}
	else if (charset == CLI_CHARSET_GBK)
	{
		if (CLI_CHARSET_Is_GbkChar(buf[idx], buf[idx + 1]))
		{
			size = 2;
		}
		else
		{
			size = 1;
		}
	}
	else
	{
		size = 1;
	}

	return size;
}



/* End of file */

