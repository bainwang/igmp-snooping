
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              头   文   件                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "bc_cli_kernel_cfg.h"
#include "bc_cli_type.h"
#include "bc_cli_misc.h"
#include "bc_cli_fltr.h"



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
typedef enum
{
    CFG_FLT_TYPE_BGN = 0, /* CFG_FILTER_TYPE_BEGIN */
    CFG_FLT_TYPE_INC,     /* CFG_FILTER_TYPE_INCLUDE */
    CFG_FLT_TYPE_EXC      /* CFG_FILTER_TYPE_EXCLUDE */
} CFG_FILTER_TYPE_T;

typedef struct _cfg_filter_string
{
    I8_T                        *ptr_filter_string; /* start address of filter string */
    struct _cfg_filter_string   *next;
} CFG_FILTER_STRING_T;

typedef struct _cfg_filter_para
{
    CFG_FILTER_TYPE_T       filter_type;    /* indicate which filter */
    CFG_FILTER_STRING_T     *ptr_filter_string; /* start address of filter string */
    UI32_T                  filter_string_count; /* record total number of filter string for each filter type */
    struct _cfg_filter_para *next;
    BOOL_T                  used;
} CFG_FILTER_PARA_T;



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                          全 局 变 量 定 义                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
static I8_T *s_cfg_flt_tkn[]  =
{
    "begin", "include", "exclude"
};



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
HANDLE_T CLI_FILTER_Create_Filterpara
    (
    IN const I8_T *ptr_parser
    )
{
    I8_T                *ptr_double_quote;
    CFG_FILTER_TYPE_T   filter_type_value;
    CFG_FILTER_PARA_T   *cfg_filter_para, *ptrFilterPara;
    CFG_FILTER_STRING_T *ptrFilterString;

    ptrFilterPara = (CFG_FILTER_PARA_T *)CLI_MISC_Malloc(sizeof(CFG_FILTER_PARA_T));
    cfg_filter_para = ptrFilterPara;

    while (*ptr_parser != '\0')
    {
        /* extract filter type or string */
        if (!memcmp(ptr_parser, s_cfg_flt_tkn[CFG_FLT_TYPE_BGN], strlen(s_cfg_flt_tkn[CFG_FLT_TYPE_BGN]))
         || !memcmp(ptr_parser, s_cfg_flt_tkn[CFG_FLT_TYPE_INC], strlen(s_cfg_flt_tkn[CFG_FLT_TYPE_INC]))
         || !memcmp(ptr_parser, s_cfg_flt_tkn[CFG_FLT_TYPE_EXC], strlen(s_cfg_flt_tkn[CFG_FLT_TYPE_EXC])))
        {
            if (!memcmp(ptr_parser, s_cfg_flt_tkn[CFG_FLT_TYPE_BGN], strlen(s_cfg_flt_tkn[CFG_FLT_TYPE_BGN])))
            {/* begin keyword */
                filter_type_value = CFG_FLT_TYPE_BGN;
            }
            else if (!memcmp(ptr_parser, s_cfg_flt_tkn[CFG_FLT_TYPE_INC], strlen(s_cfg_flt_tkn[CFG_FLT_TYPE_INC])))
            {/* include keyword */
                filter_type_value = CFG_FLT_TYPE_INC;
            }
            else if (!memcmp(ptr_parser, s_cfg_flt_tkn[CFG_FLT_TYPE_EXC], strlen(s_cfg_flt_tkn[CFG_FLT_TYPE_EXC])))
            {/* exclude keyword */
                filter_type_value = CFG_FLT_TYPE_EXC;
            }
            else /* error, free source */
            {
                CLI_FILTER_Destroy_Filterpara((HANDLE_T) cfg_filter_para);
                return NULL;
            }

            ptrFilterPara->next = (CFG_FILTER_PARA_T *) CLI_MISC_Malloc(sizeof(CFG_FILTER_PARA_T));
            ptrFilterPara = ptrFilterPara->next;

            ptrFilterPara->filter_type = filter_type_value;
            ptrFilterPara->used = TRUE;
            ptr_parser += strlen(s_cfg_flt_tkn[filter_type_value]);
        }
        else if (*ptr_parser == '"')
        {
            /* no any filter type in user filter string */
            if (ptrFilterPara == cfg_filter_para)
            {
                // free source
                CLI_MISC_Free(ptrFilterPara);
                return NULL;
            }

            /* extract filter string */
            ptr_parser++;
            ptr_double_quote = strchr(ptr_parser, '"');
            if (ptr_double_quote == NULL || (ptr_double_quote - ptr_parser) <= 0)
            {
                /* error */
                CLI_FILTER_Destroy_Filterpara((HANDLE_T) cfg_filter_para);
                return NULL;
            }
            else
            {
                if (ptrFilterPara->ptr_filter_string == NULL)
                {
                    ptrFilterPara->ptr_filter_string = (CFG_FILTER_STRING_T *)CLI_MISC_Malloc(sizeof(CFG_FILTER_STRING_T));
                    ptrFilterString = ptrFilterPara->ptr_filter_string;
                }
                else
                {
                    ptrFilterString = ptrFilterPara->ptr_filter_string;
                    while (ptrFilterString->next != NULL)
                    {
                        ptrFilterString = ptrFilterString->next;
                    }
                    ptrFilterString->next = (CFG_FILTER_STRING_T *)CLI_MISC_Malloc(sizeof(CFG_FILTER_STRING_T));
                    ptrFilterString = ptrFilterString->next;
                }
                ptrFilterString->ptr_filter_string = (I8_T *)CLI_MISC_Malloc((UI32_T)(ptr_double_quote - ptr_parser) + 1);
                memcpy(ptrFilterString->ptr_filter_string, ptr_parser, ptr_double_quote - ptr_parser);
                *(ptrFilterString->ptr_filter_string + (ptr_double_quote - ptr_parser)) = '\0';
                ptrFilterPara->filter_string_count++;
                ptr_parser = ptr_double_quote + 1;  /* across '"' */
            }
        }
        else if (*ptr_parser == ' ')
        {
            ptr_parser++;
        }
        else /* error in user filter string */
        {
            CLI_FILTER_Destroy_Filterpara((HANDLE_T) cfg_filter_para);
            return NULL;
        }
    }

    ptrFilterPara = cfg_filter_para->next;
    CLI_MISC_Free(cfg_filter_para);

    /* check cfg_filter_para */
    for (cfg_filter_para = ptrFilterPara; cfg_filter_para != NULL; cfg_filter_para = cfg_filter_para->next)
    {
        /* no filter string */
        if (cfg_filter_para->filter_string_count == 0)
        {
            /* error */
            CLI_FILTER_Destroy_Filterpara((HANDLE_T) ptrFilterPara);
            return NULL;
        }
    }

    return (HANDLE_T) ptrFilterPara;
}



/*********************************************************************
FUNCTION NAME:
    CLI_FILTER_Destroy_Filterpara

DESCRIPTION:
    Destroy the filter's parameters

INPUT:
    hfilter : handle used for storing filter's parameters

OUTPUT:
    NA

RETURN:

NOTES:

HISTORY:

**********************************************************************/
void CLI_FILTER_Destroy_Filterpara
    (
    IN HANDLE_T hfilter
    )
{
    CFG_FILTER_PARA_T   *ptrFilterPara, *ptrFilterNextPara;
    CFG_FILTER_STRING_T *ptrFilterString, *ptrFilterNextString;

    if (hfilter == NULL)
    {
        return;
    }

	ptrFilterPara = (CFG_FILTER_PARA_T *) hfilter;

    for (; ;)
    {
        ptrFilterNextPara = ptrFilterPara->next;

        ptrFilterString = ptrFilterPara->ptr_filter_string;
        while (ptrFilterString != NULL)
        {
            ptrFilterNextString = ptrFilterString->next;
            if (ptrFilterString->ptr_filter_string)
            {
                CLI_MISC_Free(ptrFilterString->ptr_filter_string);
            }
            CLI_MISC_Free(ptrFilterString);
            ptrFilterString = ptrFilterNextString;
        }

        CLI_MISC_Free(ptrFilterPara);

        if (ptrFilterNextPara == NULL)
        {
            break;
        }
        else
        {
            ptrFilterPara = ptrFilterNextPara;
        }
    }

    return;
}



/****************************************************************************
FUNCTION NAME:
    CLI_FILTER_MatchLine

DESCRIPTION:
    This function is used to  check that if the input string match the filter.

INPUT:
    hfilter  : the handle used for filter(the pointer used for storing filter parameters)
    line     : input line
    line_len : the number of chars for the input line

OUTPUT:
    NA

RETURN:
    TURE     : the input line and the filter match
    FALSE    : the input line and the filter don't match

NOTES:

HISTORY:

*****************************************************************************/
BOOL_T CLI_FILTER_MatchLine
    (
    IN HANDLE_T 	hfilter,
    IN const I8_T 	*line,
    IN UI32_T 		line_len
    )
{
    CFG_FILTER_PARA_T   *cfg_filter_para, *ptrFilterPara;
    I8_T                *line_string;
    UI32_T              filter_type_count;  /* record total number of filter type */
    BOOL_T              line_match, filter_string_match;
    CFG_FILTER_STRING_T *ptrFilterString;

    if (!hfilter || !line || !line_len)
    {
        return FALSE;
    }

    cfg_filter_para = (CFG_FILTER_PARA_T *) hfilter;
    filter_type_count = 0;

    /* check cfg_filter_para */
    for (ptrFilterPara = cfg_filter_para; ptrFilterPara != NULL; ptrFilterPara = ptrFilterPara->next)
    {
        if (ptrFilterPara->used == FALSE)
        {
            continue;
        }

        /* no filter string */
        if (ptrFilterPara->filter_string_count == 0)
        {
            /* error */
            return FALSE;
        }
        filter_type_count++;
    }

    /* user filter string are all blank */
    if (filter_type_count == 0)
    {
        return TRUE;
    }

    line_string = (I8_T *)CLI_MISC_Malloc(line_len + 1);
    MEMCPY(line_string, line, line_len);
    *(line_string + line_len) = '\0';

    line_match = TRUE;

    for (ptrFilterPara = cfg_filter_para; ptrFilterPara != NULL; ptrFilterPara = ptrFilterPara->next)
    {
        if (ptrFilterPara->used == FALSE)
        {
            continue;
        }

        line_match = FALSE;
        filter_string_match = FALSE;
        for (ptrFilterString = ptrFilterPara->ptr_filter_string; ptrFilterString != NULL; ptrFilterString = ptrFilterString->next)
        {
            if (strstr(line_string, ptrFilterString->ptr_filter_string) != NULL)
            {
                filter_string_match = TRUE;
                break;
            }
        }

        /* find the expected type string and do something */
        switch (ptrFilterPara->filter_type)
        {
        case CFG_FLT_TYPE_BGN:
            if (filter_string_match)
            {
                /* According to spec,
                 * find one of the filter type string and disable it
                 */
                ptrFilterPara->used = FALSE;
                line_match = TRUE;
            }
            else
            {
                line_match = FALSE;
            }
            break;

        case CFG_FLT_TYPE_INC:
            if (filter_string_match)
            {
                line_match = TRUE;
            }
            else
            {
                line_match = FALSE;
            }
            break;

        case CFG_FLT_TYPE_EXC:
            if (filter_string_match)
            {
                line_match = FALSE;
            }
            else
            {
                line_match = TRUE;
            }
            break;
        default:
            break;
        }

        /* line doesn't match */
        if (line_match == FALSE)
        {
            break;
        }
    }

    /* free source */
    CLI_MISC_Free(line_string);

    return line_match;
}



/****************************************************************
FUNCTION NAME:
    __cli2_filter_cfg_getline

DESCRIPTION:
    This function is used to get a line from a string buffer.
    The line is terminated by '\n'.

INPUT:
    buffer    : string buffer
    lineLimit : max length of a line

OUTPUT:
    line      : a line string

RETURN:
    character number of the line

NOTES:

HISTORY:

******************************************************************/
static I32_T __cli2_filter_cfg_getline
    (
    IN const I8_T 	*buffer,
    IN I32_T 		lineLimit,
    OUT I8_T 		*line
    )
{
    I32_T   i = 0;

    if ((buffer == NULL) || (line == NULL))
    {
        return 0;
    }

    while (i < lineLimit - 1)
    {
        if ((*buffer == '\0') || (*buffer == '\n'))
        {
            break;
        }

        *line++ = *buffer++;
        ++i;
    }

    if (*buffer == '\n')
    {
        *line++ = '\n';
        i++;
    }

    *line = '\0';

    return i;
}



/****************************************************************************
FUNCTION NAME:
    CLI_FILTER_Cfg

DESCRIPTION:
    This function is used to  filter config file.

INPUT:
    ptr_usr_filter_string : user filter string pointer
    ptr_cfg               : config pointer
    ptr_cfg_size          : config size pointer

OUTPUT:
    ptr_cfg               : config pointer after filter
    ptr_cfg_size          : config size pointer after filter

RETURN:
    TRUE                  : Success
    FALSE                 : the format of input filter expression is wrong
    
NOTES:

HISTORY:

*****************************************************************************/
BOOL_T CLI_FILTER_Cfg
    (
    IN I8_T 		*ptr_usr_filter_string,
    IN OUT I8_T 	*ptr_cfg,
    IN OUT UI32_T 	*ptr_cfg_size
    )
{
    I8_T        *ptr_end_of_valid_cfg   = NULL;
    I32_T       new_cfg_size;
    I32_T       length;
    I32_T       count                   = 0;
    I8_T        line[CLI_API_MAX_CMD_LEN];
    I32_T       maxLength;
    HANDLE_T    hfilter;

    if (!ptr_usr_filter_string || !ptr_cfg || !ptr_cfg_size)
    {
        return FALSE;
    }

    /* parse user filter string and extract filter type and string
     * ex: begin "login default" "para" include "application" "telnet"
     */
    hfilter = CLI_FILTER_Create_Filterpara(ptr_usr_filter_string);
    if (hfilter == NULL)
    {
        return FALSE;
    }

    /* filter config */
    ptr_end_of_valid_cfg = ptr_cfg;
    new_cfg_size = 0;
    maxLength = ((*ptr_cfg_size - count) > CLI_API_MAX_CMD_LEN) ? CLI_API_MAX_CMD_LEN : (*ptr_cfg_size - count);

    length = __cli2_filter_cfg_getline(ptr_cfg, maxLength, line);

    /* Notice
     * the algothrim is keep the end pointer of "valid" cfg file buffer,
     * if have an new "valid" line, will append to the pointer.
     * "valid" means the line experience filter process.
     */
    while (length > 0)
    {
        if (CLI_FILTER_MatchLine(hfilter, line, length))
        {
            /* copy valid line */
            strncpy(ptr_end_of_valid_cfg, ptr_cfg + count, length);
            ptr_end_of_valid_cfg += length;
            new_cfg_size += length;
        }
        count += length;
        maxLength = ((*ptr_cfg_size - count) > CLI_API_MAX_CMD_LEN) ? CLI_API_MAX_CMD_LEN : (*ptr_cfg_size - count);
        length = __cli2_filter_cfg_getline(ptr_cfg + count, maxLength, line);
    } /* end while (length > 0) */

    *ptr_cfg_size = (UI32_T) new_cfg_size;

    ptr_cfg[new_cfg_size] = '\0';

    CLI_FILTER_Destroy_Filterpara(hfilter);

    return TRUE;
}/* End of cmd_firm_FilterCfg */



/*-------------------------------------- end of program ------------------------------------------*/
