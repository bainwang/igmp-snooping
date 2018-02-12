CFLAGS += -I $(BC_INC_DIR)/common	\
		  -I $(BC_INC_DIR)/common/error	\
		  -I $(BC_INC_DIR)/common/modules	\
		  -I $(BC_INC_DIR)/common/nouse	\
		  -I $(BC_INC_DIR)/common/ipc	\
		  -I $(BC_INC_DIR)/common/platform	\
		  -I $(BC_INC_DIR)/common/print	\
		  -I $(BC_INC_DIR)/common/vfs	\
		  -I $(BC_INC_DIR)/common/log	\
		  -I $(BC_INC_DIR)/common/util	\
		  -I $(BC_INC_DIR)/common/message	\
		  -I $(BC_INC_DIR)/module/system/baseinfo	\
		  -I $(BC_INC_DIR)/module/system/ipc	\
		  -I $(BC_INC_DIR)/module/system/platform	\
		  -I $(BC_INC_DIR)/module/system/session	\
		  -I $(BC_INC_DIR)/module/system/log	\
		  -I $(BC_INC_DIR)/module/system/usermgmt	\
		  -I $(BC_INC_DIR)/module/system/print	\
		  -I $(BC_INC_DIR)/module/system/cli	\
		  -I $(BC_INC_DIR)/module/system/binchie	\
		  -I $(BC_INC_DIR)/module/system/filetrans	\
		  -I $(BC_INC_DIR)/module/system/clock	\
		  -I $(BC_INC_DIR)/module/system/cfgmgmt	\
		  -I $(BC_INC_DIR)/proj

##在这里添加各注册的模块
CFLAGS += -I $(CLI_INC_DIR)	\
          -I $(CLI_INC_CMDS_DIR)	\
		  -I $(CLI_INC_CMDS_DIR)/demo	\
          -I $(CLI_INC_CMDS_DIR)/system/monitor	\
		  -I $(CLI_INC_CMDS_DIR)/system/usermgmt \
		  -I $(CLI_INC_CMDS_DIR)/system/binchie \
		  -I $(CLI_INC_CMDS_DIR)/system/filetrans \
		  -I $(CLI_INC_CMDS_DIR)/system/print \
		  -I $(CLI_INC_CMDS_DIR)/system/dbg/cli \
		  -I $(CLI_INC_CMDS_DIR)/system/dbg/ipc \
		  -I $(CLI_INC_CMDS_DIR)/system/baseinfo \
		  -I $(CLI_INC_CMDS_DIR)/system/clock \
		  -I $(CLI_INC_CMDS_DIR)/system/cfgmgmt \
		  -I $(CLI_INC_CMDS_DIR)/system/stats \
		  -I $(CLI_INC_CMDS_DIR)/system/ptcode

OBJECT = bc_cli_base.o bc_cli_cmds.o bc_cli_text.o demo/ system/
		
obj-y += $(OBJECT)