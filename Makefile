##################################################################
##          For Framwork by wangbin.uestc@gmail.com             ##
##################################################################
CROSS_COMPILE = #arm-linux-
AS		= $(CROSS_COMPILE)as
LD		= $(CROSS_COMPILE)ld
CC		= $(CROSS_COMPILE)gcc
CPP		= $(CC) -E
AR		= $(CROSS_COMPILE)ar
NM		= $(CROSS_COMPILE)nm

STRIP		= $(CROSS_COMPILE)strip
OBJCOPY		= $(CROSS_COMPILE)objcopy
OBJDUMP		= $(CROSS_COMPILE)objdump

ARFLAGS 	= rcs

export AS LD CC CPP AR NM
export STRIP OBJCOPY OBJDUMP

##################################################################
#CFLAGS := -Wall -O2 -g
export BC_INC_DIR 	= $(shell pwd)/include
#CFLAGS += -I $(shell pwd)/include	\
#		+= -I $(shell pwd)/include/common

#CFLAGS=-I`net-snmp-config --cflags`
#BUILDLIBS=`net-snmp-config --libs`
#BUILDAGENTLIBS=`net-snmp-config --agent-libs`

# shared library flags (assumes gcc)
#DLFLAGS=-fPIC -shared

#LDFLAGS := -lm -lfreetype -lts -lpthread
#export CFLAGS LDFLAGS		
##################################################################
TOPDIR := $(shell pwd)
COMMONDIR := $(TOPDIR)/common
MODULEDIR := $(TOPDIR)/module
PROJDIR := $(TOPDIR)/proj
BC_INC_DIR_COMMON := $(BC_INC_DIR)/common
BC_INC_DIR_MODULE := $(BC_INC_DIR)/module
BC_INC_DIR_PROJ := $(BC_INC_DIR)/proj

BC_LIB_A_DIR := $(TOPDIR)/lib_a
BC_IMAGEDIR := $(TOPDIR)/image

OTHER_PROCESS_DIR := $(TOPDIR)/processes

export TOPDIR COMMONDIR MODULEDIR \
       BC_INC_DIR_COMMON BC_INC_DIR_MODULE BC_INC_DIR_PROJ

## pass to C files
PROJ_DEFS_X86 := MK_BC_PRJ_NAME_X86

TARGET := bcImage

	  
CFLAGS += -I $(TOPDIR)	\
		  -I $(BC_INC_DIR_COMMON)	\
		  -I $(BC_INC_DIR_COMMON)/error	\
		  -I $(BC_INC_DIR_COMMON)/modules	\
		  -I $(BC_INC_DIR_COMMON)/nouse	\
		  -I $(BC_INC_DIR_COMMON)/ipc	\
		  -I $(BC_INC_DIR_COMMON)/platform	\
		  -I $(BC_INC_DIR_COMMON)/print	\
		  -I $(BC_INC_DIR_COMMON)/vfs	\
		  -I $(BC_INC_DIR_COMMON)/log	\
		  -I $(BC_INC_DIR_COMMON)/util	\
		  -I $(BC_INC_DIR_COMMON)/message	\
		  -I $(BC_INC_DIR_MODULE)/L1/port	\
		  -I $(BC_INC_DIR_MODULE)/system/onu	\
		  -I $(BC_INC_DIR_MODULE)/system/ipc	\
		  -I $(BC_INC_DIR_MODULE)/system/session	\
		  -I $(BC_INC_DIR_MODULE)/system/binchie	\
		  -I $(BC_INC_DIR_MODULE)/system/baseinfo	\
		  -I $(BC_INC_DIR_MODULE)/system/cli	\
		  -I $(BC_INC_DIR_MODULE)/system/platform	\
		  -I $(BC_INC_DIR_MODULE)/system/log	\
		  -I $(BC_INC_DIR_MODULE)/system/print	\
		  -I $(BC_INC_DIR_MODULE)/system/test	\
		  -I $(BC_INC_DIR_MODULE)/system/usermgmt	\
		  -I $(BC_INC_DIR_MODULE)/system/filetrans	\
		  -I $(BC_INC_DIR_MODULE)/system/clock	\
		  -I $(BC_INC_DIR_MODULE)/system/cfgmgmt	\
		  -I $(BC_INC_DIR_MODULE)/system/stats	\
		  -I $(BC_INC_DIR_PROJ)

###############################库###################################
BC_SDK_LIB_A += -Wl,--start-group \
		$(BC_LIB_A_DIR)/libcommon.a \
		$(BC_LIB_A_DIR)/libsdk.a \
		\
		-Wl,--end-group \
		$(LDFLAGS)		  
		  
ifeq ($(CC), gcc)
	CFLAGS += -D $(PROJ_DEFS_X86)
endif
LDFLAGS := -lpthread -lrt
##################################################################		  
OBJECT = module/
obj-y += $(OBJECT)
##################################################################
ifeq ($(CC), gcc)
	export CFLAGS LDFLAGS
else
	export CFLAGS LDFLAGS	
endif
##################################################################

#note: $(IMAGEDIR)$(TARGET1)已构成目录结构，无需写'/'。 echo前面加@表示只回显

##################################################################	
				   ####### 开始执行编译 #######	
##################################################################
all : 
ifeq ($(CC), gcc)
	@echo "------------- Buildding $(TARGET) process begin -------------"
else
	@echo "------------- Buildding $(TARGET) process finish -------------"
endif

	make -C ./ -f $(TOPDIR)/Makefile.build
	
	$(CC) -o $(TARGET) $(CFLAGS) $(LDFLAGS) $(BUILDAGENTLIBS) $(BUILDLIBS) built-in.o $(BC_SDK_LIB_A)
	
##################################################################	

##################################################################	

	@ ## 编译其它进程 ##
#	@ cd $(OTHER_PROCESS_DIR); make all;

##################################################################	
	@ cp $(TARGET) $(BC_IMAGEDIR)/$(TARGET)
	@ chmod 777 $(BC_IMAGEDIR)/$(TARGET)

ifeq ($(CC), gcc)
	@echo "----------------------------------------------------------"
	@echo "|           BUILD FINISHED, PRJ NAME IS [x86]            |"
	@echo "----------------------------------------------------------"
else
	@echo "----------------------------------------------------------"
	@echo "|          BUILD FINISHED, PRJ NAME IS [board]           |"
	@echo "----------------------------------------------------------"
endif
##################################################################


##################################################################	
clean:
	rm -f $(shell find -name "*.o")
#	rm -f $(shell find -name "*.a")
#	rm -f $(BC_IMAGEDIR)/*
	rm -f $(TARGET)

distclean:
	rm -f $(shell find -name "*.o")
	rm -f $(shell find -name "*.d")
#	rm -f $(shell find -name "*.a")
#	rm -f $(BC_IMAGEDIR)/*
	rm -f $(TARGET)
	
############################### END ###################################
