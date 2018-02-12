/************************************************************
  Copyright (C), 1988-2014, xxxxx Tech. Co., Ltd.
  FileName:bc_platform_procps.h
  Author:  wangbin      Version :  1.0        Date:2014-2-8
  Description:   procps  for linux          
  Version:                        
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/
#ifndef   _BC_PLATFORM_PROCPS_H_ 
#define   _BC_PLATFORM_PROCPS_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <errno.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/dir.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "bc_platform_types.h"
#include "bc_err.h"

#define PTH_NU          80  


#define PROCPATHLEN 64  // must hold /proc/2000222000/task/2000222000/cmdline

typedef struct proc_t {
    bc_int32   ppid;		    // stat,status     pid of parent process
    bc_ulong pcpu;         // stat (special)  %CPU usage (is not filled in by readproc!!!)
    bc_char  state;		// stat,status     single-bc_char code for process state (S=sleeping)
    bc_ulong utime;		// stat            user-mode CPU time accumulated by process
	bc_ulong stime;		// stat            kernel-mode CPU time accumulated by process
	bc_ulong cutime;		// stat            cumulative utime of process and reaped children
	bc_ulong cstime;		// stat            cumulative stime of process and reaped children
	bc_ulong start_time;	// stat            start time of process -- seconds since 1-1-70
    bc_ulong start_code;	// stat            address of beginning of code segment
	bc_ulong end_code;	// stat            address of end of code segment
	bc_ulong start_stack;	// stat            address of the bottom of stack for the process
	bc_ulong kstk_esp;	// stat            kernel stack pointer
	bc_ulong kstk_eip;	// stat            kernel instruction pointer
	bc_ulong wchan;		// stat (special)  address of kernel wait channel proc is sleeping in
	bc_long priority;	// stat            kernel scheduling priority
	bc_long nice;	    // stat            standard unix nice level of process
	bc_long rss;		// stat            resident set size from /proc/#/stat (pages)
	bc_long alarm;		// stat            ?
	bc_ulong rtprio;		// stat            real-time priority
	bc_ulong sched;		// stat            scheduling class
	bc_ulong vsize;		// stat            number of pages of virtual memory ...
	bc_ulong rss_rlim;	// stat            resident set size limit?
	bc_ulong flags;		// stat            kernel flags for the process
	bc_ulong min_flt;	// stat            number of minor page faults since process start
	bc_ulong maj_flt;	// stat            number of major page faults since process start
	bc_ulong cmin_flt;	// stat            cumulative min_flt of process and child processes
	bc_ulong cmaj_flt;	// stat            cumulative maj_flt of process and child processes
    bc_char cmd[16];	// stat,status     basename of executable file in call to exec(2)
    bc_int32 pgrp;		// stat            process group id
	bc_int32 session;	// stat            session id
	bc_int32 nlwp;		// stat,status     number of threads, or 0 if no clue
	bc_int32 pid;		// (special)       task group ID, the POSIX PID (see also: tid)
	bc_int32 tty;		// stat            full device number of controlling terminal
	bc_int32 tpgid;		// stat            terminal process group id
	bc_int32 exit_signal;	// stat            might not be SIGCHLD
	bc_int32 processor;      // stat            current (or most recent?) CPU
} proc_t;


struct pth_status_s
{
	bc_int32 thread_id;
	bc_char  status;
};

/*************************************************
  Function: bc_platform_proc_count
  Description:获取系统进程的数量
  Input: 
  	proc_count:进程数量
  		
  Output:
  Return:
  		  	0:成功
  			~0:失败
  Note: 
  History: 
*************************************************/
extern bc_err_e bc_platform_proc_count(bc_int32 *proc_count);

/*************************************************
  Function: bc_platform_cpu_info
  Description:读取cpu 利用率
  Input: 
  	usage:cpu 利用率，最大100
  		
  Output:
  Return:
  		  	0:成功
  			~0:失败
  Note: 
  History: 
*************************************************/
extern bc_err_e bc_platform_cpu_info(bc_ulong *usage);

/*************************************************
  Function: bc_platform_mem_info
  Description:获取内存使用情况
  Input: 
  		memtotal:内存大小(单位KB)
  		memfree:空闲内存大小(单位KB)
  Output:
  Return:
  		  	0:成功
  			~0:失败
  Note: 
  History: 
*************************************************/
extern bc_err_e bc_platform_mem_info(bc_ulong *memtotal, bc_ulong *memfree);

/*************************************************
  Function: bc_platform_prco_info_get
  Description: 获取进程相关信息
  Input: 
  		pid: 进程pid
  		info: 进程信息

  Output:
  Return:
  		  	0:成功
  			~0:失败
  Note: 
  History: 
*************************************************/
extern bc_err_e bc_platform_prco_info_get(const bc_int32 pid,proc_t *info);


/*************************************************
  Function: bc_platform_prco_info_get_byname
  Description: 获取进程相关信息
  Input: 
  		name: 进程名字
  		info: 进程信息

  Output:
  Return:
  		  	0:成功
  			~0:失败
  Note: 
  History: 
*************************************************/
extern bc_err_e bc_platform_prco_info_get_byname(bc_char const *name,proc_t *info);

/*************************************************
  Function: bc_platform_cur_proc_name_get
  Description:获取当前进程名称
  Input: 
  			 name:   保存进程名称
  			 size:     name size
  Output:
  			NULL
  Return:
  			0:成功
  			~0:失败
  Notes:
  History: 
*************************************************/
extern bc_err_e bc_platform_cur_proc_name_get(bc_char *name,bc_uint32 size);

/*************************************************
  Function: bc_platform_thread_info
  Description: 获取线程状态
  Input: 
  		pid: 进程pid
  		pthstate: 存储线程状态数组

  Output:
  Return:
  		  	0:成功
  			~0:失败
  Note: 
  History: 
*************************************************/
extern bc_int32 bc_platform_thread_info(const bc_int32 pid, struct pth_status_s pthstate[PTH_NU]);

#endif //#define  _BC_PLATFORM_PROCPS_H_

