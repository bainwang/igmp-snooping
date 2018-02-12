
/*******************************************************************************
  -------------------------------------------------------------------------
  [File name]  : \\BC\cli\bc_cli.c
  [Author]     : bain.wang@outlook.com
  [Version]    : 1.0
  [Date]       : 2016-04-21
  [Description]: 
  
  [Others]     :

  [Function List]:
    1. ....
    2. ....
  [History]:
     D a t e    Modification                                          Initials
    ---------- --------------                                        ----------
    2016-04-21  Created                                               
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              ͷ   ��   ��                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/un.h>
#include <getopt.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

#include "bc_common_defs.h"
#include "bc_modules.h"
#include "bc_platform_init.h"
#include "bc_print.h"
#include "bc_ipc_dev_client.h"
#include "bc_sys_defs.h"

#include "bc_cli_type.h"
#include "bc_cli_pseudo.h"
#include "bc_cli_mainprocess.h"
#include "bc_cli_cmds.h"

#include "bc_cli.h"

#include "bc_log.h"
#include "bc_vfs.h"
//#include "bc_cli_cmd_cfg.h"
//#include "bc_cli_ipc_server.h"
#include "bc_cli_misc.h"

#include "bc_cli_para_lex_dnf.h"

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                      �� �� �� ���� �� �� �� ��                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//extern void cmd_file_config_file_load(char *filename, char flg);



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                      ��   ��   ��   ��   ��   ��                           //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
/*
 *      ��Դ�ļ���Ҫ����꣬��ͷ�ļ���������ģ��ͷ�ļ��еĺ궨�����ظ���������
 *  ʱ���ڴ˴����塣
 */


typedef enum enum_start_up_mode
{
	UP_WAIT_CMD = 0,	/* ����������ģʽ����ʼ�����л�����������shell */
	UP_LOAD_USR_CFG,	/* �����û�����ģʽ�����س���Ĭ�����ü��û����� */
	UP_ARG_CMD,
	UP_READ_FILE,
	UP_MAX_MODE
} start_mode_e;

typedef struct tag_start_up_arg
{
	cli_link_t		link_type;
	start_mode_e	mode;
	char            *pgm_name;
	char        	*arg;
} start_arg_t;

#define BUG_ADDRESS 	"cligroup@binchie.com"

//#define DEBUG_MODULE



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                          ȫ �� �� �� �� ��                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
/* 
 *  �ⲿȫ�ֱ������ṩ�������̵��ã���ͷ�ļ����ṩ���ýӿ�(�ⲿ��������)��
 */
FILE 					*g_fp_cfg_tmp = NULL;

/* 
 *  �ڲ�ȫ�ֱ�����ֻ�ṩ�����ļ��ڲ��������ã�����ͷ�ļ����ṩ���ýӿڡ�
 */

static unsigned int 	l_mdl_id = BC_MODULE_CLI;
static start_arg_t 		l_run_arg = {0};

#ifdef GET_MAIN_PROCESS_CONNTLIM
static bc_uint8 		l_connlim;
#endif



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              ��  ��  ��  ��                                //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//static void __get_option(int argc, char **argv);
//static void __prt_option(void);
//static void __prt_usage(int status);



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              ��  ��  ��  ��                                //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
/******************************************************************************\
  Function   : __prt_usage
  Description: Help information display
  Return     : 
  Others     : 
\******************************************************************************/
static void __prt_usage
	(
    int status
	)
{
	CLI_DBG_ENTER(l_mdl_id);

    if (status != 0)
    {
        fprintf(stderr, "Try `%s --help' for more information.\r\n\r\n", l_run_arg.pgm_name);
    }
	else
	{
	    printf( "Usage : %s [OPTION...]\r\n\r\n"
       			"-b, --boot               Execute boot startup configuration\r\n"
       			"-e, --eval               Execute argument as command\r\n"
       			"-f, --file               Execute user configuration file as command\r\n"
       			"-h, --help               Display this help and exit\r\n"
				"-s, --serial 			  To perform configuration by the user input serial command\r\n"
				"NA                       To perform configuration by the user input telnet command\r\n"
       			"\r\n"
       			"Report bugs to %s\r\n\r\n", 
       			l_run_arg.pgm_name, 
       			BUG_ADDRESS);
	}

	CLI_DBG_LEAVE(l_mdl_id);
	exit(status);
}



/******************************************************************************\
  Function   : __get_option
  Description: Help information display
  Return     : 
  Others     : 
\******************************************************************************/
static void __get_option(int argc, char **argv)
{
	CLI_DBG_ENTER(l_mdl_id);

	/* KTY shell options, we use GNU getopt library */
	struct option	s_long_opts[]  =
	{
		{ "boot",		no_argument,			NULL,	'b'}, 
		{ "eval",		required_argument,	NULL,	'e'}, 
		{ "file",		required_argument,	NULL,	'f'},
		{ "help",		no_argument,			NULL,	'h'},
		{ "serial",	no_argument,			NULL,	's'}, /* Ĭ��Ϊtelnet���������ý��� */
		{ 0 }
	};
	
	char	*pgm_name = NULL;
	int 	opt;
	
	// ��ȡ�ó��������
	l_run_arg.pgm_name = ((pgm_name = strrchr(argv[0], '/')) ? ++pgm_name : argv[0]);

	opt = getopt_long(argc, argv, "be:f:h", s_long_opts, 0);
	CLI_DBG_CPL(l_mdl_id, "option<%u>(b=%u, e=%u, f=%u, h=%u), optarg<%s>\r\n", opt, 'b', 'e', 'f', 'h', optarg);

	if (opt == EOF)
	{
		return;
	}

	switch (opt)
	{
	case 0:
		CLI_DBG_CPL(l_mdl_id, "-telnet\n");
		l_run_arg.mode = UP_WAIT_CMD;
		l_run_arg.link_type = CLI_LINK_TELNET;
		break;

	case 's':
		CLI_DBG_CPL(l_mdl_id, "-serial\n");
		l_run_arg.mode = UP_WAIT_CMD;
		l_run_arg.link_type = CLI_LINK_SERIAL;
		break;

	case 'b':
		CLI_DBG_CPL(l_mdl_id, "-boot\n");
		l_run_arg.mode = UP_LOAD_USR_CFG;
		break;

	case 'e':
		CLI_DBG_CPL(l_mdl_id, "-exe\n");
		{
			unsigned int i;

			l_run_arg.mode = UP_ARG_CMD;
			l_run_arg.arg = (char *) malloc (1024);
			if (NULL == l_run_arg.arg)
			{
				CLI_DBG_CPL(l_mdl_id, "Failed to allocate memory for command string.\r\n");
				exit(1);
			}

			for (i = 2; i < argc; i++)
			{
		        strcat(l_run_arg.arg, argv[i]);
				strcat(l_run_arg.arg, " ");
			}
			strcat(l_run_arg.arg, "\n");
			CLI_DBG_CPL(l_mdl_id, "l_run_arg.arg<%s>\r\n", l_run_arg.arg);
		}
		break;

	case 'f':
		CLI_DBG_CPL(l_mdl_id, "-file\n");
		l_run_arg.mode = UP_READ_FILE;
		l_run_arg.arg  = strdup(optarg);
		break;

	case 'h':
		CLI_DBG_CPL(l_mdl_id, "-help\n");
		__prt_usage(0);
		break;

	default:
		__prt_usage(1);
		break;
	}//end switch

	CLI_DBG_LEAVE(l_mdl_id);
	return;
}



/******************************************************************************\
  Function   : __prt_option
  Description: 
  Return     : 
  Others     : 
\******************************************************************************/
static void __prt_option(void)
{
	CLI_DBG_ENTER(l_mdl_id);

	CLI_DBG_CPL(l_mdl_id, "[%s]\n", "program option information");
	CLI_DBG_CPL(l_mdl_id, "%15s:%s\n", "program name", l_run_arg.pgm_name);
	CLI_DBG_CPL(l_mdl_id, "%15s:%u\n", "start up mode", l_run_arg.mode);
	CLI_DBG_CPL(l_mdl_id, "%15s:%s\n", "argument", l_run_arg.arg);

	CLI_DBG_LEAVE(l_mdl_id);
	return;
}



#if 0
/******************************************************************************\
  Function   : __open_file
  Description: 
  Return     : 
  Others     : 
\******************************************************************************/
static FILE * __open_file(char *pFileName)
{
	CLI_DBG_ENTER(l_mdl_id);

	FILE	*pFile = NULL;
	
	pFile = fopen(pFileName, "w+b");

	CLI_DBG_LEAVE(l_mdl_id);
	return pFile;
}
#endif



#ifdef GET_MAIN_PROCESS_CONNTLIM
/******************************************************************************\
  Function   : __get_conntlim
  Description: 
  Return     : 
  Others     : 
\******************************************************************************/
static bc_uint8 __get_conntlim(void)
{
	CLI_DBG_ENTER(l_mdl_id);

	bc_uint8 	conntlim;

	bc_get_xxxxx(&conntlim);

	CLI_DBG_LEAVE(l_mdl_id);
	return conntlim;
}
#endif

void __bc_cli_stop_release(int signo)
{
	bc_ipc_dev_client_release();
	_exit(0);
}

extern BOOL_T bc_cli_global_paging;
/******************************************************************************\
  Function   : main
  Description: 
  Return     : 
  Others     : 
\******************************************************************************/
int
main(int argc, char **argv, char **env)
{
	bc_pt_init();
	
	/*process CTRL+C*/
	signal(SIGINT, __bc_cli_stop_release);

	bc_platform_init();

	bc_file_init();

//	bc_log_sys_cli_init();
//	bc_log_user_cli_init();
	
	bc_pt_dbg_init();
	
	bc_ipc_create(IPC_CLIENT_TYPE_CLI);
	if (l_run_arg.mode == UP_WAIT_CMD)
		bc_ipc_cli_server_init(bc_ipc_dev_client_session_get());
	

	/* ------------ */
	/* ��������ѡ�� */
	/* ------------ */
	__get_option(argc, argv);
	__prt_option();

	/* --------------------- */
	/* �޸�shell���Ĭ������ */
	/* --------------------- */
#ifdef GET_MAIN_PROCESS_LANGUAGE
	kinsh_set_conn_limit(__get_conntlim());/* ���ÿͻ�������ֵ��Ĭ��ֵΪ7 */
#endif
 
	/* ------------------------------- */
	/* ��ʼ��shell����������û����� */
	/* ------------------------------- */
	bc_cli_misc_init();
	bc_cli_para_lex_bnf_init();
	cli_ker_init();

	cli_ker_cmd_reg();
	bc_cli_app_cmd_reg();

	/* ------------------------------------------------------------------- */
	
	/* ------------------------------------------------------------------- */
	switch (l_run_arg.mode)
	{
	case UP_ARG_CMD:
		CLI_DBG_CPL(l_mdl_id, "UP_ARG_CMD\n");
		break;

	case UP_READ_FILE:
		CLI_DBG_CPL(l_mdl_id, "UP_READ_FILE\n");
		break;

	case UP_LOAD_USR_CFG:/* �����û�����ģʽ�����س���Ĭ�����ü��û����� */
		CLI_DBG_CPL(l_mdl_id, "UP_LOAD_USR_CFG\n");
		CLI_MSG_INI(l_mdl_id, "\n\rBC Configuration..............................0%%\r");

		bc_cli_global_paging = FALSE;
		if (cli_pseudo_task(l_run_arg.arg) != TRUE)
		{
			sleep(2);
			CLI_MSG_INI(l_mdl_id, "\rBC Configuration............................100%%\r\n");
			system("echo \"cli cfg completed\" > /tmp/"BC_SYS_CLI_CFG_COMPLETE" ");
			break;
		}
		sleep(2);
		CLI_MSG_INI(l_mdl_id, "\rBC Configuration............................100%%\r\n");
		system("echo \"cli cfg completed\" > /tmp/"BC_SYS_CLI_CFG_COMPLETE" ");
		break;
		
	case UP_WAIT_CMD:/* ����������ģʽ����ʼ�����л�����������shell */
		CLI_DBG_CPL(l_mdl_id, "UP_WAIT_CMD\n");
		CLI_DBG_CPL(l_mdl_id, "Create CLI STDOUT buffer successed!\r\n");
		bc_cli_global_paging = TRUE;
		
		cli_io_task(NULL);
		break;

	default:
		CLI_DBG_CPL(l_mdl_id, "Unknown program mode!\r\n");
		break;
	}

    return 0;
}



/******************************************************************************\
  Function   : bc_cli_get_linktype
  Description: 
  Return     : 
  Others     : 
\******************************************************************************/
cli_link_t bc_cli_get_linktype()
{
	return l_run_arg.link_type;
}



/* 
 *	Ԥ��һ��ע�����ļ����
 */
/******************************************************************************\
  Function   : 
  Description: 
  Return     : 
  Others     : 
\******************************************************************************/
