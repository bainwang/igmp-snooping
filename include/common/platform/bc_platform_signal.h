/************************************************************
  FileName:
  Author:  bain.wang@outlook.com      Version :  1.0        Date:2016-2-8
  Description:                   
  Version:                        
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/
#ifndef _BC_PLATFORM_SIGNAL_H_
#define _BC_PLATFORM_SIGNAL_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h> 
#include <sys/signal.h>
#include <sys/ucontext.h>
#include <asm/ptrace.h>
#include <bits/siginfo.h>
#include <semaphore.h>
#include "bc_platform_thread.h"

typedef void (*signal_fun)(int sn,siginfo_t *si,void *sc);


extern void bc_platform_signal_dump(int sn,siginfo_t *si,void *sc);
extern bc_err_e bc_platform_signal_init(signal_fun dump);


#endif //_BC_PLATFORM_SIGNAL_H_

