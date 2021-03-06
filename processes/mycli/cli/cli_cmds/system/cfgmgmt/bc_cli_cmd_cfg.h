/************************************************************
  -------------------------------------------------------------------------
  FileName: bc_cli_cmd_cfg.h
  Author:  bain.wang@outlook.com      Version :  1.0        Date:2016-8-15
  Description: proj depend parameter define       
  Version:                        
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/
#ifndef __BC_CLI_CMD_CFG_H__
#define __BC_CLI_CMD_CFG_H__



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              头   文   件                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
#include "bc_cli_type.h"


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                      外 部 变 量、 函 数 引 用                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              宏   定   义                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                  结 构 体 、联 合 体、枚 举 定 义                          //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                          全 局 变 量 定 义                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
/* 
 *  外部全局变量，提供整个工程调用，在头文件中提供调用接口(外部引用声明)。
 */

/* 
 *  内部全局变量，只提供给该文件内部函数调用，不在头文件中提供调用接口。
 */



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              函  数  声  明                                //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

/*************************************************
  Function: bc_cli_cmd_cfg_reg
  Description: 配置文件的命令注册接口
  Input:   
  		void
  Output:
  		NULL
  Return:
  		void
  Note: 
  History: 
*************************************************/
void bc_cli_cmd_cfg_reg(void);



/*************************************************
  Function: bc_cfg_load_config_file
  Description: 加载用户配置文件
  Input:   
  		filename		文件名
  		flag			加载标记
  Output:
  		NULL
  Return:
  		void
  Note: 
  History: 
*************************************************/
void bc_cfg_load_config_file(I8_T *filename, BOOL_T flag);








#endif		/* __BC_CLI_CMD_CFG_H__ */


