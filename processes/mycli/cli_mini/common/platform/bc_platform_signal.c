/************************************************************
  Copyright (C), 1988-2014, xxxxx Tech. Co., Ltd.
  FileName:
  Author:  wangbin      Version :  1.0        Date:2014-2-8
  Description:                   
  Version:                        
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/
#include "bc_platform_signal.h"
#include "bc_platform_time.h"

bc_err_e bc_platform_signal_init(signal_fun dump)
{
	struct sigaction act;
	memset(&act,0,sizeof(act));
	act.sa_sigaction = dump;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	if(sigaction(SIGSEGV, &act, NULL)) //SIGSEGV表示该信号的值 
	{
		printf("Sigaction returned error..＼n");
   		return BC_ERR_PARA;
	}
	
	return BC_ERR_OK;
}


void bc_platform_signal_dump(int sn,siginfo_t *si,void *sc)
{ 
#ifdef _DUMP_REG_
	unsigned int mnip;
	unsigned int i;
	struct ucontext *uc = (struct ucontext *)sc;
  	struct pt_regs *regs = (struct pt_regs *)((&(uc->uc_mcontext))->regs);
#endif
	
  	printf(" Signal number = %d, Signal errno = %d \n",si->si_signo,si->si_errno);
	
#ifdef _DUMP_REG_
	switch(si->si_code)
	{
	   case 1: printf(" SI code = %d (Address not mapped to object)\n",si->si_code);
	             break;
	   case 2: printf(" SI code = %d (Invalid permissions for mapped object)\n",si->si_code);
	           break;
	   default: printf("SI code = %d (Unknown SI Code)\n",si->si_code);
	            break;
	}
	
	printf(" Intruction pointer = %x \n",*((unsigned int *)regs->nip));
  	printf(" Fault addr = 0x%x \n",si->si_addr);
  	printf(" dar = 0x%x \n",regs->dar);
  	printf(" trap = 0x%x \n",regs->trap);
  	printf(" Op-Code [nip - 4] = 0x%x at address = 0x%x \n",*((unsigned int *)(regs->nip-4)),(regs->nip-4));
	printf(" Failed Op-code    = 0x%x at address = 0x%x \n",*((unsigned int *)(regs->nip)),regs->nip);
  	printf(" Op-Code [nip + 1] = 0x%x at address = 0x%x \n",*((unsigned int *)(regs->nip+4)),(regs->nip + 4));
#endif

	while(1)
	{
		bc_platform_time_sleep(10);
		printf("Into the death cycle.....\n");
	}
}

