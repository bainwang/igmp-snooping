/*******************************************************************************
  Copyright (C), 2010-2030, xxxxx Tech. Co., Ltd.
  [File name]  : \\BC\Include\Common\Ipc\bc_ipc_def.h
  [Author]     : bain.wang@outlook.com
  [Version]    : 1.0
  [Date]       : 2016-04-15
  [Description]:
 
  [Others]     :

  [Function List]:
	1. ....
	2. ....
  [History]:
	 D a t e	Modification										  Initials
	---------- --------------										 ----------
	2016-04-15	Created 											  bain.wang@outlook.com
*******************************************************************************/

#ifndef __BC_IPC_DEF_H__
#define __BC_IPC_DEF_H__
       
////////////////////////////////////////////////////////////////////////////////
//																			  //
//								ͷ   ��   ��								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#include <memory.h>
#include <stdio.h>
#include "bc_err.h"
#include "bc_print.h"
#include "bc_common_defs.h"
#include "bc_platform_thread.h"
#include "bc_ipc_package.h"

////////////////////////////////////////////////////////////////////////////////
//																			  //
//								��   ��   ��								  //
//																			  //
////////////////////////////////////////////////////////////////////////////////


#define  MAX_IPC_NAME_LEN               64                                   /*����IPC NAME����*/ 
#define  MAX_HANDER_NAME                64                                   /*�û�Hander�������Ϊ64�ֽ�*/  

#define  IP_ADDRESS_LEN                 20                                   /*IP��ַ����*/  


/*  
	BC_F_DONT_SYNC: ����ͬ�����������̼�ͨ��

	BC_F_SYNC: ���ݻᱻͬ�����͵�(�����л�)�ı��ݰ��У����ݰ��*_srv
�ӿ�ͬ���ܹ��յ�������ݣ�һ������ֻ��set������Ҫͬ������get
��������Ҫͬ����

   BC_F_SYNC_ONLY: �ýӿ�ֻ��������������ͬ����������������̼�ͨ�Ż�
 ����ϵͳ��֧�ֵĴ����
*/
#define BC_F_DONT_SYNC 	0
#define BC_F_SYNC 					1
#define BC_F_SYNC_ONLY		2


/*
    BC_F_SLAVE_USE: �����忨��Ϊ(�����л�)���ݰ�ʱ����Ȼ����ʹ�øýӿڣ�
һ����˵���ڱ��ݰ���ֻ����get������

    BC_F_SLAVE_CANNOT_USE: �������ڱ��ݰ���ʹ��
*/
#define BC_F_SLAVE_USE 1
#define BC_F_SLAVE_CANNOT_USE 0


#endif /* __BC_IPC_DEF_H__ */

