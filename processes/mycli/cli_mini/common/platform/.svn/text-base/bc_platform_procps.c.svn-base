/************************************************************
  Copyright (C), 1988-2014, xxxxx Tech. Co., Ltd.
  FileName:bc_platform_procps.c
  Author:  wangbin      Version :  1.0        Date:2014-2-8
  Description:             procps  for linux          
  Version:                        
  History:        
                  
    1. Date:
       Author:
       Modification:
    2. ...
***********************************************************/
#include "bc_platform_procps.h"
#include "bc_platform_thread.h"
#include "bc_print.h"
#include "bc_modules.h"


typedef struct  bc_platform_cpu_s    
{
	bc_ulong user; 
	bc_ulong nice; 
	bc_ulong system;
	bc_ulong idle; 
	bc_ulong iowait;
	bc_ulong HardIrq; 
	bc_ulong SoftIRQ;
	bc_ulong Steal;
	
}bc_platform_cpu_t;



/*************************************************
  Function: __bc_file2str
  Description:读取文件内容
  Input: 
  		
  Output:
  Return:
  		success:read num ,err:-1
  Note: 
  History: 
*************************************************/
static bc_int32 __bc_file2str(
	const bc_char *directory, 
	const bc_char *what, 
	bc_char *ret, 
	bc_int32 cap) 
{
    static bc_char filename[80];
    bc_int32 fd, num_read;

    sprintf(filename, "%s/%s", directory, what);
    fd = open(filename, O_RDONLY, 0);
    if(fd == -1)
    {
		return -1;
    }
	
    num_read = read(fd, ret, cap - 1);
	
    close(fd);
	
    if(num_read <= 0)
	{
		return -1;
	}
	
    ret[num_read] = '\0';

    return num_read;
}



/*************************************************
  Function: __bc_cpu_deal
  Description:读取cpu相关信息
  Input: 
  		
  Output:
  Return:
  		  	0:成功
  			~0:失败
  Note: 
  History: 
*************************************************/
static bc_err_e __bc_cpu_deal(bc_platform_cpu_t *cpu)
{
	bc_char *tmp;
	bc_char path[64],buf[1024];
	
	if(cpu == NULL)
	{
		return BC_ERR_PARA;
	}
	
	strcpy(path,"/proc/");
	if (__bc_file2str(path, "stat", buf, sizeof(buf)) == -1)
	{
		BC_PT_ERROR(BC_MODULE_PLATFORM,"__bc_file2str is not opened!\n");
		return BC_ERR_RESOURCE;	
	}
	
    tmp = strchr(buf, ' ') + 2;
	sscanf(tmp,"%ld %ld %ld %ld %ld %ld %ld %ld ",
				&cpu->user,
				&cpu->nice,
				&cpu->system,
				&cpu->idle,
				&cpu->iowait,
				&cpu->HardIrq,
				&cpu->SoftIRQ,
				&cpu->Steal);
	
	bc_platform_trace("%ld %ld %ld %ld %ld %ld %ld %ld\n",
				cpu->user,
				cpu->nice,
				cpu->system,
				cpu->idle,
				cpu->iowait,
				cpu->HardIrq,
				cpu->SoftIRQ,
				cpu->Steal);
	
	return BC_ERR_OK;
}


#if 0
/*************************************************
  Function: __bc_cpu_deal
  Description:读取进程cpu利用率
  Input: 
  		
  Output:
  Return:
  		  	0:成功
  			~0:失败
  Note: 
  History: 
*************************************************/	
static bc_int32 __bc_pcpudeal(proc_t *info,bc_ulong *ctotal, bc_ulong *ptotal)
{

	bc_platform_cpu_t cpu;
	if(info ==NULL || ctotal == NULL || ptotal == NULL)
		return 0;
	
	if(__bc_cpu_deal(&cpu) != 1)
		return 0;

	*ptotal = (info->utime + info->stime + info->cutime + info->cstime);

	*ctotal  = (cpu.user + cpu.system + cpu.nice  + cpu.idle + cpu.iowait + cpu.HardIrq + cpu.SoftIRQ + cpu.Steal);

	bc_platform_trace("ptotal=%lu,ctotal=%lu\n",ptotal,ctotal);
	
	 return 1;
}
#endif

/*************************************************
  Function: __bc_myitoa
  Description: 数字字符转换
  Input: 

  Output:
  Return:
  		  bc_char*
  Note: 
  History: 
*************************************************/
static bc_char *__bc_myitoa(bc_int32 num,bc_char *str,bc_int32 radix)
{  

	bc_char index[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	unsigned unum;
	bc_char temp;
	bc_int32 i=0,j,k;
	
	if(radix == 10&&num < 0) 
	{
		unum = (unsigned)-num;
		
		str[i++] = '-';
	}
	else
	{
		unum = (unsigned)num;
	}
	
	do  
	{
		str[i++] = index[unum%(unsigned)radix];
		unum /= radix;
	}while(unum);
	
	str[i] = '\0';
	if(str[0] == '-')
	{ 
		k = 1; 
	}
	else
	{ 
		k = 0;
	}

	for(j=k;j<=(i-k-1)/2;j++) 
	{ 
		temp = str[j]; 
		str[j] = str[i-j-1]; 
		str[i-j-1] = temp; 
	}
	
	return str;
}



/*************************************************
  Function: __bc_stat2proc
  Description: 获取进程相关信息
  Input: 

  Output:
  Return:
  		  	0:成功
  			~0:失败
  Note: 
  History: 
*************************************************/
static void __bc_stat2proc(const bc_char* S, proc_t * P) 
{
    unsigned num;
    bc_char* tmp;
	
    /* fill in default values for older kernels */
    P->processor = 0;
    P->rtprio = -1;
    P->sched = -1;
    P->nlwp = 0;

    S = strchr(S, '(') + 1;
    tmp = strrchr(S, ')');
    num = tmp - S;
    if((num >= sizeof P->cmd)) num = sizeof P->cmd - 1;
    memcpy(P->cmd, S, num);
    P->cmd[num] = '\0';
    S = tmp + 2;                 // skip ") "

    num = sscanf(S,
       "%c "
       "%d %d %d %d %d "
       "%lu %lu %lu %lu %lu "
       "%lu %lu %lu %lu "  /* utime stime cutime cstime */
       "%ld %ld "
       "%d "
       "%ld "
       "%lu "  /* start_time */
       "%lu "
       "%ld "
       "%lu %lu %lu %lu %lu %lu ",
       &P->state,
       &P->ppid, &P->pgrp, &P->session, &P->tty, &P->tpgid,
       &P->flags, &P->min_flt, &P->cmin_flt, &P->maj_flt, &P->cmaj_flt,
       &P->utime, &P->stime, &P->cutime, &P->cstime,
       &P->priority, &P->nice,
       &P->nlwp,
       &P->alarm,
       &P->start_time,
       &P->vsize,
       &P->rss,
       &P->rss_rlim, &P->start_code, &P->end_code, &P->start_stack, &P->kstk_esp, &P->kstk_eip
    );

    if(!P->nlwp)
	{
      P->nlwp = 1;
    }
}

/*************************************************
  Function: __bc_stat2thread
  Description: 获取线程状态
  Input: 

  Output:
  Return:
  		  	0:成功
  			~0:失败
  Note: 
  History: 
*************************************************/
static void __bc_stat2thread(const bc_char* S, bc_char *state)
{
    unsigned __attribute__((unused)) num;
    bc_char* tmp;
    S = strchr(S, '(') + 1;
    tmp = strrchr(S, ')');
    num = tmp - S;
    S = tmp + 2;                 // skip ") "
    num = sscanf(S,
       "%c ",
       state);
}

/*************************************************
  Function: __bc_meminfo2proc
  Description:获取内存使用状态
  Input: 
  		
  Output:
  Return:
  		  	0:成功
  			~0:失败
  Note: 
  History: 
*************************************************/
static bc_err_e __bc_meminfo2proc(const bc_char* S, bc_ulong *memtotal, bc_ulong *memfree)
{
	unsigned num;
	bc_char buf[64];
    bc_char* tmp;
	
    S = strchr(S, ':') + 1;
    tmp = strchr(S, 'k');
    num = tmp - S;
	memcpy(buf,S,num);
	*memtotal=strtoul(buf, NULL, 10);

	S = strchr(S, ':') + 1;
    tmp = strchr(S, 'k');
    num = tmp - S;
	memcpy(buf,S,num);
	*memfree=strtoul(buf, NULL, 10);
	
	return BC_ERR_OK;
}


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
bc_err_e bc_platform_proc_count(bc_int32 *proc_count)
{
    struct dirent* ent;
    DIR* procfs = NULL; 
	bc_int32 count = 0;
	
    procfs = opendir("/proc");
    if(!procfs) 
	{
		return BC_ERR_PARA;
	}
	
	for (;;) 
	{
        ent = readdir(procfs);
        if((!ent) || (!ent->d_name)) 
		{
			break;
		}
        if((*ent->d_name > '0') && (*ent->d_name <= '9') )
		{	
			count++;
        }
	}

	*proc_count = count;
	
	closedir(procfs);
	
	return BC_ERR_OK;
}


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
bc_err_e bc_platform_cpu_info(bc_ulong *usage)
{
	bc_platform_cpu_t cpu1,cpu2;
	bc_ulong user1,user2,total1,total2;
	
	if(usage == NULL)
	{
		return BC_ERR_PARA;
	}
	
	if (__bc_cpu_deal(&cpu1) != BC_ERR_OK)
	{
		return BC_ERR_NOT_SUPPORT;
	}

	bc_platform_time_usleep(1000000);
	
	if (__bc_cpu_deal(&cpu2) != BC_ERR_OK)
	{
		return BC_ERR_NOT_SUPPORT;
	}

	user1 = (cpu1.user + cpu1.system + cpu1.nice + cpu1.iowait + cpu1.HardIrq + cpu1.SoftIRQ + cpu1.Steal);

	total1= (cpu1.user + cpu1.system + cpu1.nice  + cpu1.idle + cpu1.iowait + cpu1.HardIrq + cpu1.SoftIRQ + cpu1.Steal);

    user2 = (cpu2.user + cpu2.system + cpu2.nice + cpu2.iowait + cpu2.HardIrq + cpu2.SoftIRQ + cpu2.Steal);

	total2= (cpu2.user + cpu2.system + cpu2.nice  + cpu2.idle + cpu2.iowait + cpu2.HardIrq + cpu2.SoftIRQ + cpu2.Steal);


	*usage =((user2 - user1)*100)/(total2 - total1);

	return BC_ERR_OK;
}



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
bc_err_e bc_platform_mem_info(bc_ulong *memtotal, bc_ulong *memfree)
{
	bc_char path[64],buf[1024];

	if(memtotal == NULL||memfree == NULL)
	{
		return BC_ERR_PARA;
	}
	
	strcpy(path,"/proc/");
	if (__bc_file2str(path, "meminfo", buf, sizeof(buf)) == -1)
	{
		BC_PT_ERROR(BC_MODULE_PLATFORM,"__bc_file2str is not opened.\n");
		return BC_ERR_PARA;	
	}
	
	if(__bc_meminfo2proc(buf, memtotal, memfree) != BC_ERR_OK)
	{
		return BC_ERR_PARA;
	}

	return BC_ERR_OK;

}

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
bc_int32 bc_platform_thread_info(const bc_int32 pid, struct pth_status_s pthstate[PTH_NU])
{
	bc_int32 num = 0;
	DIR* procfs = NULL;
	struct dirent* ent;
	bc_char str[25];
	bc_char	path[64];
	bc_char	path1[64];
	bc_char	buf[1024];

	if(pid <= 0)
	{
		return 0;
	}
	__bc_myitoa(pid,str,10);
	
	sprintf(path, "/%s/%s/%s","proc",str,"task");
	procfs = opendir(path);
	if(!procfs)
	{
		return 0;	
	}
	
	for (;;) 
	{  
		ent = readdir(procfs);       
		if((!ent) || (!ent->d_name))
		{
			break;
		}  
		if((*ent->d_name > '0') && (*ent->d_name <= '9') )
		{	
			memset(path1, 0, sizeof(path1));
			sprintf(path1, "%s/%s", path, ent->d_name);
			if(__bc_file2str(path1, "stat", buf, sizeof(buf)) == -1)
			{
				break;
			}
			pthstate[num].thread_id = strtoul(ent->d_name, NULL, 10);
			__bc_stat2thread(buf, &pthstate[num].status);
			num++;
			if (num >= PTH_NU)
			{
				break;
			}
		}	

	}
	
	closedir(procfs);
	
	return num;
}


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
bc_err_e bc_platform_prco_info_get(const bc_int32 pid,proc_t *info)
{
	bc_char str[25],path[64],buf[1024];

	if(pid <= 0||info == NULL)
	{
		return BC_ERR_PARA;
	}
	
	info->pid = pid;
	__bc_myitoa(pid,str,10);
	
	memcpy(path, "/proc/", 6);
	strcpy(path+6,str);
	if (__bc_file2str(path, "stat", buf, sizeof(buf)) == -1)
	{
		return BC_ERR_NOT_SUPPORT;	
	}
	
	__bc_stat2proc(buf,info);


	return BC_ERR_OK;
}

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
bc_err_e bc_platform_prco_info_get_byname(bc_char const *name,proc_t *info)
{
    struct dirent* ent;
	bc_int32 pid = -1;
	DIR* procfs = NULL;
	
	memset(info,0,sizeof(proc_t));
	procfs = opendir("/proc");
	if(!procfs)
	{
		return BC_ERR_PARA;	
	}
	
	for (;;) 
	{  
		ent = readdir(procfs);       
		if((!ent) || (!ent->d_name))
		{
			memset(info,0,sizeof(proc_t));
			closedir(procfs);
			return BC_ERR_NOT_FIND;
		}  
		if((*ent->d_name > '0') && (*ent->d_name <= '9') )
		{				
			pid = strtoul(ent->d_name, NULL, 10);
			bc_platform_prco_info_get(pid,info);
			if(strcmp(name,info->cmd) == 0)
			{
				info->pid = pid;
				closedir(procfs);
				return BC_ERR_OK;
			}
		}	

	}
	
	closedir(procfs);
	
	return BC_ERR_NOT_FIND;
}

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
bc_err_e bc_platform_cur_proc_name_get(bc_char *name,bc_uint32 size)
{	
	proc_t info;
	bc_err_e ret;
	pid_t pid = getpid();
	
	ret = bc_platform_prco_info_get(pid, &info);
	
	size = size > sizeof(info.cmd)?sizeof(info.cmd):size;
	
	memcpy(name,&info.cmd,size);

	return ret;
}

