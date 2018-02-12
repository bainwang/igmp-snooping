/*******************************************************************************
  [File name]	: mcast_mgmt.c
  [Author]     	: bain.wang@outlook.com
  [Version]    	: 1.0
  [Date]       	: 2017-06-15
  [Description]	:
	Multicast module API for CLI SNMP
  [Others]     	:
	NULL
  [Function List]:  
    1. ....
    2. ....
  [History]:
	 D a t e      	Modification 							 Initials
	---------- 	--------------                                        ----------
	2017-06-15  	Created								 bain.wang@outlook.com
*******************************************************************************/

#include "mcast_mgmt.h"

#if BC_MULTICAST_INCLUDE

#include "mcast_core.h"

#if 1 /*bain.wang@outlook.com*/
#include "stdlib.h"
#include "string.h"
#endif

#if 1

#define mcast_mgmt_err_ret(errcode)	\
	{ \
		MCAST_DBG_PRT("\n\t%s,%d, errcode:%d\n", __FILE__, __LINE__, errcode); \
		return errcode; \
	}

#define mcast_err_m2k_cvt(mccode, bcapicode) \
	do \
	{ \
		if (mccode == MCAST_RET_OK) \
			bcapicode = BC_ERR_OK; \
		else if (mccode == MCAST_RET_ERR_PAR) \
			bcapicode = BC_ERR_IGMP_PAR_ERROR; \
		else if (mccode == MCAST_RET_ERR_NORES) \
			bcapicode = BC_ERR_IGMP_MLTCST_RES_OUT; \
		else if (mccode == MCAST_RET_ERR_PBCINFO) \
			bcapicode = BC_ERR_IGMP_PAR_ERROR; \
		else if (mccode == MCAST_RET_ERR_UNTYPE) \
			bcapicode = BC_ERR_IGMP_PAR_ERROR; \
		else if (mccode == MCAST_RET_ERR_NOTFOUND) \
			bcapicode = BC_ERR_IGMP_TARGE_NOT_EXIST; \
		else if (mccode == MCAST_RET_ERR_DRVERR) \
			bcapicode = BC_ERR_IGMP_DRIVER_ERROR; \
		else if (mccode == MCAST_RET_ERR_NOENABLE) \
			bcapicode = BC_ERR_IGMP_FUNC_INACTIVE; \
		else if (mccode == MCAST_RET_ERR_UNKNOW) \
			bcapicode = BC_ERR_IGMP_PAR_ERROR; \
		else \
			bcapicode = BC_ERR_IGMP_PAR_ERROR; \
	} while(0)

bc_err_e mcast_mgmt_xx_cfg_get(IN bc_uint32 set_opt_flag, OUT mcast_mgmt_cfg_t *xx_cfg)
{
	mcast_cfg_t mcast_cfg;

	M_MCAST_ASSERT(xx_cfg);

	if (xx_cfg == NULL)
		mcast_mgmt_err_ret(BC_ERR_IGMP_PAR_ERROR);

	mcast_cfg_get(&mcast_cfg);
	
	if (set_opt_flag & MCAST_MGMT_CFG_STATE)
		xx_cfg->en = mcast_cfg.enable;
	
	if (set_opt_flag & MCAST_MGMT_CFG_MQRT)
		xx_cfg->mqrt = mcast_cfg.query_rsp_interval;

	if (set_opt_flag & MCAST_MGMT_CFG_ROBUST_VAR)
		xx_cfg->robust_var = mcast_cfg.robustness;

	if (set_opt_flag & MCAST_MGMT_CFG_QUERY_INTERVAL)
		xx_cfg->query_interval = mcast_cfg.query_interval;
	
	if (set_opt_flag & MCAST_MGMT_CFG_LMQI)
		xx_cfg->lmqi = mcast_cfg.last_member_query_interval;
	
	if (set_opt_flag & MCAST_MGMT_CFG_LMQC)
		xx_cfg->lmqc = mcast_cfg.last_member_query_count;

	if (set_opt_flag & MCAST_MGMT_CFG_VER)
		xx_cfg->ver = mcast_cfg.igmp_version;

	if (set_opt_flag & MCAST_MGMT_CFG_MODE)
		xx_cfg->mode = mcast_cfg.mode;

	return BC_ERR_OK;
}


bc_err_e mcast_mgmt_xx_cfg_set(IN bc_uint32 set_opt_flag, IN mcast_mgmt_cfg_t *xx_cfg)
{
	
	mcast_cfg_t mcast_cfg;
	mcast_ret_code ret = MCAST_RET_OK;
	bc_err_e bc_ret = BC_ERR_OK;

	M_MCAST_ASSERT(xx_cfg);
	memset(&mcast_cfg, 0x00, sizeof(mcast_cfg));
	
	if (xx_cfg == NULL)
		mcast_mgmt_err_ret(BC_ERR_IGMP_PAR_ERROR);

	mcast_cfg_get(&mcast_cfg);

	if (set_opt_flag & MCAST_MGMT_CFG_STATE)
	{
		if (xx_cfg->en != mcast_cfg.enable)
		{
			if (xx_cfg->en)
				ret = mcast_core_igmp_enable(); /* enable */
			else
				ret = mcast_core_igmp_disable(); /* disable */ 

			if (ret != MCAST_RET_OK)
			{
				mcast_err_m2k_cvt(ret, bc_ret);
				return bc_ret;
			}

			mcast_cfg_set_state(xx_cfg->en);
		}	
	}

	if (set_opt_flag & MCAST_MGMT_CFG_MQRT)
	{
		if (xx_cfg->mqrt < MCAST_MAX_RESP_TIME_MIN || MCAST_MAX_RESP_TIME_MAX < xx_cfg->mqrt)
			mcast_mgmt_err_ret(BC_ERR_IGMP_PAR_ERROR);

		if (mcast_cfg_set_query_rsp_interval(xx_cfg->mqrt) == FALSE)
			mcast_mgmt_err_ret(BC_ERR_IGMP_RSP_BIGGER_THAN_QUERY);
	}

	if (set_opt_flag & MCAST_MGMT_CFG_ROBUST_VAR)
	{
		if (xx_cfg->robust_var < MCAST_ROBUSTNESS_MIN || MCAST_ROBUSTNESS_MAX < xx_cfg->robust_var)
			mcast_mgmt_err_ret(BC_ERR_IGMP_PAR_ERROR);

		if (mcast_cfg_set_robustness(xx_cfg->robust_var) == FALSE)
			mcast_mgmt_err_ret(BC_ERR_IGMP_PAR_ERROR);
	}

	if (set_opt_flag & MCAST_MGMT_CFG_QUERY_INTERVAL)
	{
		if (xx_cfg->query_interval < MCAST_QUERY_INTERVAL_MIN || MCAST_QUERY_INTERVAL_MAX < xx_cfg->query_interval)
			mcast_mgmt_err_ret(BC_ERR_IGMP_PAR_ERROR);

		if (xx_cfg->query_interval < mcast_cfg.query_rsp_interval)
			mcast_mgmt_err_ret(BC_ERR_IGMP_RSP_BIGGER_THAN_QUERY);

	
		if (mcast_cfg_set_query_interval(xx_cfg->query_interval) == FALSE)
			mcast_mgmt_err_ret(BC_ERR_IGMP_PAR_ERROR);
	}
	
	if (set_opt_flag & MCAST_MGMT_CFG_LMQI)
	{
		if (xx_cfg->lmqi < MCAST_LAST_MEMBER_QUERY_INTERVAL_MIN || MCAST_LAST_MEMBER_QUERY_INTERVAL_MAX < xx_cfg->lmqi)
			mcast_mgmt_err_ret(BC_ERR_IGMP_PAR_ERROR);

		if (xx_cfg->lmqi > mcast_cfg.query_interval)
			mcast_mgmt_err_ret(BC_ERR_IGMP_RSP_BIGGER_THAN_QUERY);
	
		if (mcast_cfg_set_last_member_query_interval(xx_cfg->lmqi) == FALSE)
			mcast_mgmt_err_ret(BC_ERR_IGMP_PAR_ERROR);
	}
	
	if (set_opt_flag & MCAST_MGMT_CFG_LMQC)
	{
		if (xx_cfg->lmqc < MCAST_LAST_MEMBER_QUERY_COUNT_MIN || MCAST_LAST_MEMBER_QUERY_COUNT_MAX < xx_cfg->lmqc)
			mcast_mgmt_err_ret(BC_ERR_IGMP_PAR_ERROR);
	
		if (mcast_cfg_set_last_member_query_count(xx_cfg->lmqc) == FALSE)
			mcast_mgmt_err_ret(BC_ERR_IGMP_PAR_ERROR);
	}

	if (set_opt_flag & MCAST_MGMT_CFG_VER)
	{
		if (xx_cfg->ver < MCAST_IGMP_V1 || MCAST_IGMP_V3 < xx_cfg->ver)
			mcast_mgmt_err_ret(BC_ERR_IGMP_PAR_ERROR);
 
		ret = mcast_core_igmp_ver_proc(mcast_cfg.igmp_version, xx_cfg->ver);
		if (ret != MCAST_RET_OK)
		{
			mcast_err_m2k_cvt(ret, bc_ret);
			return bc_ret;
		}		
		
		mcast_cfg_set_igmp_version(xx_cfg->ver); 
	}

	if (set_opt_flag & MCAST_MGMT_CFG_MODE)
	{
		if (xx_cfg->mode <= MCAST_MODE_CENTRALIZED || MCAST_MODE_DISTRIBUTEDWOCM < xx_cfg->mode)
			mcast_mgmt_err_ret(BC_ERR_IGMP_PAR_ERROR);
		ret = mcast_core_igmp_mode_proc(mcast_cfg.mode, xx_cfg->mode);
		if (ret != MCAST_RET_OK)
		{
			mcast_err_m2k_cvt(ret, bc_ret);
			return bc_ret;
		}
		mcast_cfg_set_mode(xx_cfg->mode); 		
	}

	return BC_ERR_OK;
}

#endif
#if 1


bc_err_e mcast_mgmt_xx_fwd_get_all(INOUT mcast_mgmt_fwd_t *fwd_block, OUT bc_uint16 *acutal_num)
{ 
	M_MCAST_ASSERT(fwd_block);
	M_MCAST_ASSERT(acutal_num);

	mcast_core_xx_fwd_get_all((mcast_core_fwd_t*)fwd_block, acutal_num);
	return BC_ERR_OK;
}

#endif



#endif

