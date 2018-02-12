/*==============================================================================
 * FILE NAME  : bc_cli_pseudo.c
 * VERSION    : 1.0.0
 * DESCRIPTION:
 * NOTES:
 *
 * HISTORY:
 * -----------------------------------------------------------------------------
 * Version 1.0 -- 2009-May-31 by bain.wang@outlook.com
 * [NEW FEATURE]
 * <DESCRIPTION> Create
 *============================================================================*/

////////////////////////////////////////////////////////////////////////////////
// 																			  //
// 							 	头   文   件								  //
// 																			  //
////////////////////////////////////////////////////////////////////////////////

#include "bc_platform_sem.h"
#include "bc_cli_type.h"
#include "bc_cli_msg.h"
#include "bc_cli_pseudo.h"
#include "bc_cli_term.h"
#include "bc_cli_vio.h"
#include "bc_cli_sesn.h"
#include "bc_cli_mainprocess.h"

#include "bc_cli.h"
#include "bc_vfs.h"
#if 0	/*bain.wang@outlook.com for cli code transplantation*/
#include "bc_cfg_mgmt_client.h"
#endif
#include "bc_platform_thread.h"



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

#define CLI_PSEUDO_IBUF_SIZE 		100000
#define CLI_PSEUDO_OBUF_SIZE 		100000
#define CLI_PSEUDO_BUF_EMPTY 		1
#define CLI_PSEUDO_BUF_FULL 		2
#define CLI_PSEUDO_BUF_NORMAL 		3

#define CLI_PSEUDO_IBUF_NOT_FULL 	1
#define CLI_PSEUDO_IBUF_NOT_EMPTY 	2
#define CLI_PSEUDO_OBUF_NOT_FULL 	4
#define CLI_PSEUDO_OBUF_NOT_EMPTY 	8



////////////////////////////////////////////////////////////////////////////////
//																			  //
//							全 局 变 量 定 义								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

//#define IBUF_EVENT // else IBUF_SEM

static bc_modules_e 	l_mdl_id = BC_MODULE_CLI_KERNEL_PSEUDO;

#ifdef IBUF_EVENT
static HANDLE_T s_psd_evt; 		/* pseudo event */
#else
static HANDLE_T s_sem_full; 	/* pseudo event */
static HANDLE_T s_sem_empty; 	/* pseudo event */
#endif

#if 1 /* i buffer */
static HANDLE_T s_psd_ilock; /* pseudo ilock */

static I8_T 	s_psd_ibuf[CLI_PSEUDO_IBUF_SIZE]; /* pseudo ibuffer */
static I32_T 	s_psd_ibuf_start = 0; /* pseudo ibuffer start */
static I32_T 	s_psd_ibuf_end   = 0; /* pseudo ibuffer end */

static bc_thread_t 	wrt_thread_id = 0;
UI32_T   			total_byte 	  = 0;




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
 *   __cli2_pseudo_check_empty
 *
 * DESCRIPTION:
 *   Check if the input buffer is empty
 *
 * INPUT:
 *   session_id -- not used
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   TRUE  -- input buffer is empty
 *   FALSE -- input buffer is not empty
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2009-Jun-01 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
static BOOL_T __cli2_pseudo_check_empty(I32_T session_id)
{
	BOOL_T ret;

	bc_platform_sem_wait(s_psd_ilock, BC_SEM_WAIT_FOREVER);
	ret = s_psd_ibuf_start == s_psd_ibuf_end ? TRUE : FALSE;
	bc_platform_sem_post(s_psd_ilock);

	return ret;
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *   __cli2_pseudo_buffer_is_full
 *
 * DESCRIPTION:
 *   Check the buffer used in cli2 pseudo is full or not
 *
 * INPUT:
 *   buf_start: position of the first char in the buffer
 *   buf_end: position next of the last char in the buffer
 *   buf_size: space of the buffer
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   TRUE: buffer is full
 *   FALSE: buffer is not full
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2009-Jun-09 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
static BOOL_T __cli2_pseudo_buffer_is_full (
	IN I32_T buf_start,
	IN I32_T buf_end,
	IN I32_T buf_size)
{
	if (((buf_end + 1) % buf_size) == buf_start)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *   __cli2_pseudo_buffer_is_empty
 *
 * DESCRIPTION:
 *   Check the buffer used in cli2 pseudo is empty or not
 *
 * INPUT:
 *   buf_start: position of the first char in the buffer
 *   buf_end: position next of the last char in the buffer
 *   buf_size: space of the buffer
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   TRUE: buffer is empty
 *   FALSE: buffer is not empty
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2009-Jun-09 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
static BOOL_T __cli2_pseudo_buffer_is_empty (
	IN I32_T buf_start,
	IN I32_T buf_end,
	IN I32_T buf_size)
{
	if (buf_size)
	{
		;
	}

	if (buf_end == buf_start)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *   __cli2_pseudo_get_buf_space
 *
 * DESCRIPTION:
 *   Get count of the bytes not used in buffer
 *
 * INPUT:
 *   buf_start: position of the first char in the buffer
 *   buf_end: position next of the last char in the buffer
 *   buf_size: space of the buffer
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   count of the bytes not used.
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2009-Jun-09 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
static BOOL_T __cli2_pseudo_get_buf_space (
	IN I32_T buf_start,
	IN I32_T buf_end,
	IN I32_T buf_size)
{
	return ((buf_size - 1) - ((buf_end + buf_size - buf_start) % buf_size));
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *   __cli2_pseudo_put_nchar2buf
 *
 * DESCRIPTION:
 *   Put n char to the specified buf
 *
 * INPUT:
 *   *p_buf_end : position next of the last char in the buffer
 *   buf        : start address of the buffer
 *   buf_size   : space of the buffer
 *   p_ch       : chars to be copied
 *   size       : size of the chars to be copied
 *
 * OUTPUT:
 *   *p_buf_end : new position next of the last char in the buffer
 *
 * RETURN:
 *   count of the bytes not used.
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2009-Jun-09 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
static BOOL_T __cli2_pseudo_put_nchar2buf (
	IN I32_T *p_buf_end,
	IN I32_T buf_size,
	IN I8_T *buf,
	IN const I8_T *p_ch,
	IN I32_T n)
{
	I32_T i;

	for (i = 0; i < n; i++)
	{
		buf[(*p_buf_end)++] = p_ch[i];
		*p_buf_end %= buf_size;
	}

	return TRUE;
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *   __cli2_pseudo_get_char
 *
 * DESCRIPTION:
 *   Get a char from the specified buf
 *
 * INPUT:
 *   *p_buf_start : position of the first char in the buffer
 *   buf          : start address of the buffer
 *   buf_size     : space of the buffer
 *
 * OUTPUT:
 *   *p_buf_start : new position of the first char in the buffer
 *
 * RETURN:
 *   count of the bytes not used.
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2009-Jun-09 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
static I32_T __cli2_pseudo_get_char(
	IN I32_T *p_buf_start,
	IN I32_T buf_size,
	IN I8_T *buf)
{
	I32_T ch;

	ch = buf[(*p_buf_start)++];
	*p_buf_start %=  buf_size;

	return ch;
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *   __cli2_pseudo_ibuf_getc
 *
 * DESCRIPTION:
 *   Get a char from pseudo buffer. It will not return until get a char in pseudo input buffer
 *
 * INPUT:
 *   session_id -- not used
 *   timeout    -- not used
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   the result char
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2009-Jun-01 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
static I32_T __cli2_pseudo_ibuf_getc(
	IN I32_T session_id,
	IN I32_T timeout)
{
	I32_T 	ch = 0;
	BOOL_T 	full;
	BOOL_T 	empty;
	
	while (ch == 0)
	{
		bc_platform_sem_wait(s_psd_ilock, BC_SEM_WAIT_FOREVER);
		empty = __cli2_pseudo_buffer_is_empty(s_psd_ibuf_start, s_psd_ibuf_end, CLI_PSEUDO_IBUF_SIZE);
		bc_platform_sem_post(s_psd_ilock);

		if (empty)
		{
#ifdef IBUF_EVENT
			OS_EVENT_Wait(s_psd_evt, CLI_PSEUDO_IBUF_NOT_EMPTY, OS_EVENT_OP_AND_CLEAR, BC_SEM_WAIT_FOREVER);
#else
			bc_platform_sem_wait(s_sem_full, BC_SEM_WAIT_FOREVER);
#endif
		}

		bc_platform_sem_wait(s_psd_ilock, BC_SEM_WAIT_FOREVER);
		empty = __cli2_pseudo_buffer_is_empty(s_psd_ibuf_start, s_psd_ibuf_end, CLI_PSEUDO_IBUF_SIZE);
		full = __cli2_pseudo_buffer_is_full (s_psd_ibuf_start, s_psd_ibuf_end, CLI_PSEUDO_IBUF_SIZE);
		if (empty == FALSE)
		{
			ch = __cli2_pseudo_get_char(&s_psd_ibuf_start, CLI_PSEUDO_IBUF_SIZE, s_psd_ibuf);
			if (full)
			{
#ifdef IBUF_EVENT
				OS_EVENT_Set(s_psd_evt, CLI_PSEUDO_IBUF_NOT_FULL);
#else
				bc_platform_sem_post(s_sem_empty);
#endif
			}
		}
		bc_platform_sem_post(s_psd_ilock);
	}

	return ch;
}



/*******************************************************************************
 *
 * FUNCTION NAME:
 *   CLI_PSEUDO_Execute_MiltiUserCmdWithoutOutput
 *
 * DESCRIPTION:
 *   Execute multiple user command. each command must end with a "\r\n".
 *   Commands in buffer are seperated by "\r\n"
 *
 * INPUT:
 *   str -- commands string
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   NA
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2009-Jun-01 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
void CLI_PSEUDO_Execute_MiltiUserCmdWithoutOutput(IN void *str)
{
	I32_T 	strsize = 0; /* length of the input str */
	I32_T 	buf_space = 0; /* length of the input buffer */
	BOOL_T 	full; /* 1: input buffer is full 0: input buffer is not full */
	BOOL_T 	empty;
	I8_T    *p_str = NULL;

	p_str = (I8_T *)str;
	if (NULL == p_str)
	{
		return;
	}

	wrt_thread_id = bc_platform_thread_id_get();

	strcat(p_str, "&\n");
	strsize = strlen(p_str);
	total_byte = strsize;
	while (strsize)
	{
		/* check the input buffer is full or not */
		bc_platform_sem_wait(s_psd_ilock, BC_SEM_WAIT_FOREVER);
		full = __cli2_pseudo_buffer_is_full (s_psd_ibuf_start, s_psd_ibuf_end, CLI_PSEUDO_IBUF_SIZE);
		bc_platform_sem_post(s_psd_ilock);

		/* wait until input buffer is not full */
		if (full)
		{
#ifdef IBUF_EVENT
			OS_EVENT_Wait(s_psd_evt, CLI_PSEUDO_IBUF_NOT_FULL, OS_EVENT_OP_AND_CLEAR, BC_SEM_WAIT_FOREVER);
#else
			bc_platform_sem_wait(s_sem_empty, BC_SEM_WAIT_FOREVER);
#endif
		}

		bc_platform_sem_wait(s_psd_ilock, BC_SEM_WAIT_FOREVER);
		full = __cli2_pseudo_buffer_is_full (s_psd_ibuf_start, s_psd_ibuf_end, CLI_PSEUDO_IBUF_SIZE);
		empty = __cli2_pseudo_buffer_is_empty(s_psd_ibuf_start, s_psd_ibuf_end, CLI_PSEUDO_IBUF_SIZE);
		if (full == FALSE)
		{
			/* buffer is not full, copy chars in str to the input buffer */
			buf_space = __cli2_pseudo_get_buf_space (s_psd_ibuf_start, s_psd_ibuf_end, CLI_PSEUDO_IBUF_SIZE);
			if (buf_space > strsize)
			{
				buf_space = strsize;
			}
			__cli2_pseudo_put_nchar2buf (&s_psd_ibuf_end, CLI_PSEUDO_IBUF_SIZE, s_psd_ibuf, p_str, buf_space);
			p_str += buf_space;
			strsize -= buf_space;

			if (empty)
			{
#ifdef IBUF_EVENT
				OS_EVENT_Set(s_psd_evt, CLI_PSEUDO_IBUF_NOT_EMPTY);
#else
				bc_platform_sem_post(s_sem_full);
#endif
			}
		}
		
		bc_platform_sem_post(s_psd_ilock);
	}

	return;
}

#endif



#if 1 /* o buffer */

/*******************************************************************************
 *
 * FUNCTION NAME:
 *   __cli2_pseudo_puts
 *
 * DESCRIPTION:
 *   Puts str[len] to the pseudo output. Now it was discards only.
 *
 * INPUT:
 *   len       -- length of the output string
 *   sessionID -- not used
 *   str       -- buffer of the output string
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   NA
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2009-Jun-01 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
static void __cli2_pseudo_puts(
	IN I32_T sessionID,
	IN UI8_T *str,
	IN I32_T len)
{
#if 0
	I32_T i;

	for (i = 0; i < len; i++)
	{
		xprintf("%c", str[i]);
	}
#endif
	return;
}

#endif


#if 0	/*bain.wang@outlook.com for cli code transplantation*/
static bc_boolean __cli2_pseudo_check_boot_file_len(bc_char *boot_file)
{
	bc_uint32 actual_num = 0;
	bc_cfg_file_info_t file_list[BC_CFG_LIST_MAX_NUM];
	bc_uint8 loop_cnt = 0;

	memset(file_list, 0x00, sizeof(bc_cfg_file_info_t) * BC_CFG_LIST_MAX_NUM);
	if (bc_cfg_get_cfglist_client(file_list, &actual_num) != BC_ERR_OK)
	{
		return FALSE;
	}

	for (loop_cnt = 0; loop_cnt < actual_num; loop_cnt++)
	{
		if (!strcmp(file_list[loop_cnt].name, boot_file))
		{
			if (file_list[loop_cnt].size < BC_CFG_USR_CFG_SIZE)
			{	
				return TRUE;
			}
			
			return FALSE;
		}
	}

	return FALSE;
}
#endif


static bc_boolean __cli2_pseudo_check_cfg_file_key_words(bc_char *ptr_cfg)
{
	bc_char key_words[] = "#\n# bain.wang xxx \"user configuration\".\n";
	bc_char get_cfg_buf[128] = {0};

	memcpy(get_cfg_buf, ptr_cfg, strlen(key_words));
	if (!strcmp(key_words, get_cfg_buf))
	{
		return TRUE;
	}

	return FALSE;
}


/*******************************************************************************
 *
 * FUNCTION NAME:
 *   cli_pseudo_task
 *
 * DESCRIPTION:
 *   Main function for the cli2 pseudo terminal task
 *
 * INPUT:
 *   arg -- not used
 *
 * OUTPUT:
 *   NA
 *
 * RETURN:
 *   NA
 *
 * NOTES:
 *   NA
 *
 * HISTORY:
 *   2009-Jun-01 by bain.wang@outlook.com -- Create
 *
*******************************************************************************/
bc_boolean cli_pseudo_task (void *arg)
{
	CLI_TERMINAL_IO_T	tio;
	CLI_IP_INFO_T 		ip_info;
	I32_T 				sessionID;
	CLI_VIOTYPE_T 		vio_type = CLI_VT100;
	bc_file             *fp_cfg = NULL;
	bc_file             *fp_boot = NULL;
	I8_T				*p_cfg = NULL;
	bc_thread_t    		*cli2_thread_write = NULL;
	void 				*thread_result;
#if 0	/*bain.wang@outlook.com for cli code transplantation*/
	bc_char             boot_name[BC_CFG_USE_MAX_LEN] = {0};
#endif
	/* create sem */
#ifdef IBUF_EVENT
	s_psd_evt = OS_EVENT_Create("cli2-pseudo-event");
#else
	s_sem_empty = bc_platform_sem_create("cli2-pseudo-ibuf_empty", 1);
	s_sem_full  = bc_platform_sem_create("cli2-pseudo-ibuf_full", 0);
#endif

	s_psd_ilock = bc_platform_sem_create("cli2-pseudo-ilock", 1);

#if 0	/*bain.wang@outlook.com for cli code transplantation*/
	if (bc_file_access(BC_CFG_BOOT_FILE_NAME, BC_VFS_DATA_FILE_PATH, BC_VFS_F_OK) != BC_ERR_OK)
	{
		CLI_DBG_CPL(l_mdl_id, "boot load config file is not exist!\r\n");
		if (bc_file_access(BC_CFG_BOOT_USR_CFG, BC_VFS_CFG_FILE_PATH, BC_VFS_F_OK) != BC_ERR_OK)
		{
			CLI_DBG_CPL(l_mdl_id, "config file not exist!\r\n");
			return FALSE;
		}
		fp_cfg = bc_file_open(BC_CFG_BOOT_USR_CFG, BC_VFS_READ, BC_VFS_CFG_FILE_PATH, l_mdl_id);
		if (NULL == fp_cfg)
		{	
			BC_PT_ERROR(l_mdl_id, "cli open config file failed!\r\n");
			return FALSE;
		}
	}
	else
	{
		CLI_DBG_CPL(l_mdl_id, "boot load config file is exist!\r\n");
		fp_boot = bc_file_open(BC_CFG_BOOT_FILE_NAME, BC_VFS_READ, BC_VFS_DATA_FILE_PATH, l_mdl_id);
		if (NULL == fp_boot)
		{	
			BC_PT_ERROR(l_mdl_id, "cli open boot config file failed!\r\n");
			return FALSE;
		}
		
		bc_file_read(boot_name, BC_CFG_USE_MAX_LEN, 1, fp_boot);
		boot_name[BC_CFG_USE_MAX_LEN - 1] = '\0';
		CLI_DBG_CPL(l_mdl_id, "boot_name:%s, strlen(boot_name):%d\n", boot_name, strlen(boot_name));
		if (bc_file_access(boot_name, BC_VFS_CFG_FILE_PATH, BC_VFS_F_OK) != BC_ERR_OK)
		{
			CLI_DBG_CPL(l_mdl_id, "config file not exist!\r\n");
			return FALSE;
		}

		/* check boot file size */
		if (FALSE == __cli2_pseudo_check_boot_file_len(boot_name))
		{
			BC_PT_ERROR(l_mdl_id, "config file data too long!\r\n");
			return FALSE;
		}
		
		fp_cfg = bc_file_open(boot_name, BC_VFS_READ, BC_VFS_CFG_FILE_PATH, l_mdl_id);
		if (NULL == fp_cfg)
		{	
			BC_PT_ERROR(l_mdl_id, "cli open config file failed!\r\n");
			return FALSE;
		}
	}
	
	p_cfg = bc_platform_mem_malloc(l_mdl_id, BC_CFG_USR_CFG_SIZE);
	if (NULL == p_cfg)
	{
		CLI_DBG_CPL(l_mdl_id, "memory allocation failed!\r\n");
		return FALSE;
	}

	bc_file_read(p_cfg, BC_CFG_USR_CFG_SIZE, 1, fp_cfg);
	bc_file_close(fp_cfg, l_mdl_id, "bc_boot_usr_cfg");

	/* check cfg-file key words */
	if (FALSE == __cli2_pseudo_check_cfg_file_key_words(p_cfg))
	{
		BC_PT_ERROR(l_mdl_id, "config file key words error!\r\n");
		bc_platform_mem_free(l_mdl_id, p_cfg);
		p_cfg = NULL;
		return FALSE;
	}

	/* create write buffer thread */
	if (NULL == (cli2_thread_write = bc_platform_thread_create("cli2-pseudo-write_buf", BC_THREAD_DEF_STACK_SIZE, 20, 
									  (void *)CLI_PSEUDO_Execute_MiltiUserCmdWithoutOutput, (void *)p_cfg)))
	{
		bc_platform_mem_free(l_mdl_id, p_cfg);
		p_cfg = NULL;
		return FALSE;
	}
#endif

	tio.getchar = __cli2_pseudo_ibuf_getc;
	tio.putstr = __cli2_pseudo_puts;
	tio.checkEmpty = __cli2_pseudo_check_empty;
	tio.sessionID = VT_PSEUDO_CHANNEL;

	memset(&ip_info, 0, sizeof(CLI_IP_INFO_T));
	sessionID = bc_cli_session_create(VT_PSEUDO_CHANNEL, CLI_SESN_TYPE_PSEUDO, &tio, vio_type, &ip_info, NULL);
	if (sessionID < 0)
	{
		bc_platform_mem_free(l_mdl_id, p_cfg);
		p_cfg = NULL;
		return FALSE;
	}

	bc_cli_session_set_lvl(CLI_ACC_LVL_DEBUG);
	cli_main_process(sessionID, TRUE);

	/* wait for finishing to write buffer thread  */
	pthread_join(wrt_thread_id, &thread_result);

	bc_platform_mem_free(l_mdl_id, p_cfg);
	p_cfg = NULL;
	
	bc_cli_session_destroy(sessionID);
	return TRUE;
}



/* End of file */

