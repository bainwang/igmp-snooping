
//#include "bc_proj_defs.h"
#include "bc_cli_type.h"
#include "bc_cli_text.h"
#include "bc_cli_base.h"
#include "bc_cli.h"
//#include "bc_msg.h"



#if 0
#include "bc_port_def.h"
#include "bc_fdb_def.h"

static unsigned int 	l_mdl_id = BC_MODULE_CLI_CMD_BASE;
//static cli_lan_t 		s_lan = CLI_LAN_CN;



/******************************************************************************\
  Function   : cmd_print_ktapi_port
  Description: 打印单个端口
  Return     : 
  Others     : 
\******************************************************************************/
inline void
cmd_print_ktapi_port
	(
	const UI32_T	sid/*session_id*/,
    bc_port_index_t *port_api
	)
{
	BC_PT_FUN_ENTER(l_mdl_id);
	
	switch (port_api->port_type)
	{
	case PORT_TYPE_OLT_GESNI:
	case PORT_TYPE_OLT_XGSNI:
		CLI_API_Printf(sid, "%s%02u/%02u ", CMD_GET_STRING(CMD_MID_PORT_OLTSNI), port_api->slot_id, port_api->port_id);
		break;

	case PORT_TYPE_OLT_GEEPON:
	case PORT_TYPE_OLT_XGEPON:
		CLI_API_Printf(sid, "%s%02u/%02u ", CMD_GET_STRING(CMD_MID_PORT_OLTPON), port_api->slot_id, port_api->port_id);
		break;

	case PORT_TYPE_OLT_TRUNK:
		CLI_API_Printf(sid, "%s%02d/%02u ", CMD_GET_STRING(CMD_MID_PORT_OLTTRUNK), port_api->slot_id, port_api->port_id);
		break;

	case PORT_TYPE_OLT_CPU:
		CLI_API_Printf(sid, "%s%02d/%02u ", CMD_GET_STRING(CMD_MID_PORT_OLTCPU), port_api->slot_id, port_api->port_id);
		break;

	case PORT_TYPE_OLT_8022MII:
		CLI_API_Printf(sid, "%s%02d/%02u ", CMD_GET_STRING(CMD_MID_PORT_OLTMII), port_api->slot_id, port_api->port_id);
		break;

	case PORT_TYPE_ONU_PON:
		CLI_API_Printf(sid, "%s%02d/%02u ", CMD_GET_STRING(CMD_MID_PORT_ONUPON), port_api->slot_id, port_api->port_id);
		break;

	case PORT_TYPE_ONU_UNI:
		CLI_API_Printf(sid, "%s%02d/%02u ", CMD_GET_STRING(CMD_MID_PORT_ONUUNI), port_api->slot_id, port_api->port_id);
		break;

	case PORT_TYPE_MAX:
	default:
		CLI_API_Printf(sid, "%s%02u/%02u ", "?", port_api->slot_id, port_api->port_id);
		BC_PT_DBG_CPL(l_mdl_id, "port_api->port_type=%u\r\n", port_api->port_type);
		break;
	}

	BC_PT_FUN_LEAVE(l_mdl_id);
	return;
}



/******************************************************************************\
  Function   : cmd_print_ktapi_mac
  Description: 
  Return     : 
  Others     : 
\******************************************************************************/
inline void
cmd_print_ktapi_mac
	(
	const UI32_T	sid/*session_id*/,
	bc_fdb_query_t 	*fdb_query
	)
{
	bc_fdb_item_t 	*fdb_item;
    unsigned int 	i, Max;

	BC_PT_FUN_ENTER(l_mdl_id);

	if (NULL == fdb_query)
	{
	    BC_PT_DBG_SMP(l_mdl_id, " error para \r\n");
		return;
	}    

    CLI_API_Printf(sid, "[%s]\r\n\r\n", bc_cli_msg_get(BC_MSG_FDB_MAT));	
	CLI_API_Printf(sid, CMD_GET_STRING(CMD_MID_THERE_ARE), fdb_query->recounts);
	if(fdb_query->recounts == 0)
	{
		return;
	}
	
	CLI_API_Printf(sid, "\r\n");
    CLI_API_Printf(sid, "%6s   %-4s   %-14s  %-7s  %-6s \r\n",
					"index",
                    bc_cli_msg_get(BC_MSG_VLAN_ID),
                    bc_cli_msg_get(BC_MSG_FDB_MACADDR),
                    bc_cli_msg_get(BC_MSG_CMM_TYPE),
                    bc_cli_msg_get(BC_MSG_CMM_PORT));
    CLI_API_Printf(sid, "-------  -------  --------------  -------  ------ \r\n");
	
	Max = fdb_query->recounts;
	fdb_item = fdb_query->maclist;

	for (i = 0; i < Max; i++, fdb_item++)
	{
		CLI_API_Printf(sid, " %06u    %04u   %02X%02X.%02X%02X.%02X%02X  ", 
						i+1,
			            fdb_item->vid, 
			            fdb_item->mac[0],fdb_item->mac[1],fdb_item->mac[2],fdb_item->mac[3],fdb_item->mac[4],fdb_item->mac[5]);
		switch (fdb_item->mac_type)
		{
		case BC_FDB_DSF_DY:
		    CLI_API_Printf(sid, "%7s  ", bc_cli_msg_get(BC_MSG_FDB_DYNAMIC));
			break;
		case BC_FDB_DSF_ST:
		    CLI_API_Printf(sid, "%7s  ", bc_cli_msg_get(BC_MSG_FDB_STATIC));
			break;
		case BC_FDB_DSF_UNKNOWN:
		default:
		    CLI_API_Printf(sid, "%7s  ", "??");
			break;
		}

		cmd_print_ktapi_port(sid, &fdb_item->pid_lgc);
		CLI_API_Printf(sid, "\r\n");
	}

	BC_PT_FUN_LEAVE(l_mdl_id);
	return;
}
#endif

