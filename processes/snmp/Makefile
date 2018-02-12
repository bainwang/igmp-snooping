##################################################################
##          For snmp by wangb@longraise.com                     ##
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

export AS LD CC CPP AR NM
export STRIP OBJCOPY OBJDUMP

##################################################################
#CFLAGS := -Wall -O2 -g
export SNMP_INC_DIR 	= $(shell pwd)/include
#CFLAGS += -I $(shell pwd)/include	\
#		+= -I $(shell pwd)/include/common

CFLAGS=-I`net-snmp-config --cflags`
BUILDLIBS=`net-snmp-config --libs`
BUILDAGENTLIBS=`net-snmp-config --agent-libs`

# shared library flags (assumes gcc)
#DLFLAGS=-fPIC -shared

#LDFLAGS := -lm -lfreetype -lts -lpthread
#export CFLAGS LDFLAGS		
##################################################################

export BC_INC_DIR 	= $(shell pwd)/../../include

TOPDIR := $(shell pwd)
export TOPDIR

BC_IMAGEDIR := $(TOPDIR)/../../image

## pass to C files
PROJ_DEFS_X86 := MK_SNMP_PRJ_NAME_X86

TARGET := snmpApp

IMAGEDIR := $(TOPDIR)/$(image)

CFLAGS += -I $(BC_INC_DIR)	\
		  -I $(BC_INC_DIR)/common	\
		  -I $(BC_INC_DIR)/common/error	\
		  -I $(BC_INC_DIR)/common/modules	\
		  -I $(BC_INC_DIR)/common/nouse	\
		  -I $(BC_INC_DIR)/common/ipc	\
		  -I $(BC_INC_DIR)/common/platform	\
		  -I $(BC_INC_DIR)/common/print	\
		  -I $(BC_INC_DIR)/common/vfs	\
		  -I $(BC_INC_DIR)/common/log	\
		  -I $(BC_INC_DIR)/common/util	\
		  -I $(BC_INC_DIR)/module/system/baseinfo	\
		  -I $(BC_INC_DIR)/module/system/ipc	\
		  -I $(BC_INC_DIR)/module/system/platform	\
		  -I $(BC_INC_DIR)/module/system/session	\
		  -I $(BC_INC_DIR)/module/system/log	\
		  -I $(BC_INC_DIR)/proj
		  
CFLAGS += -I $(SNMP_INC_DIR)	\
		  -I $(SNMP_INC_DIR)/module	\
		  -I $(SNMP_INC_DIR)/module/fhEntityExtentMIB	\
		  -I $(SNMP_INC_DIR)/module/fhIfExtMIB	\
		  -I $(SNMP_INC_DIR)/module/fhSysExtMIB	\
		  -I $(SNMP_INC_DIR)/module/privateObject	\
		  -I $(SNMP_INC_DIR)/module/mib2	\
		  -I $(SNMP_INC_DIR)/module/mib2/ip \
		  -I $(SNMP_INC_DIR)/module/mib2/system \
		  -I $(SNMP_INC_DIR)/module/mib2/interface \
		  -I $(SNMP_INC_DIR)/module/trap \
		  -I $(SNMP_INC_DIR)/core		  

#############################  传递宏 ############################
ifeq ($(CC), gcc)
	CFLAGS += -D $(PROJ_DEFS_X86)
else
#	LDFLAGS := -lmpapi -lcomm -lmbase
endif

#############################动/静态库############################
LDFLAGS := -lpthread -lrt

BC_LIB_DIR := $(TOPDIR)/../../lib_a

BC_LIB_A += -Wl,--start-group \
		$(BC_LIB_DIR)/libcommon.a \
		$(BC_LIB_DIR)/libplatform.a \
		$(BC_LIB_DIR)/libsession.a  \
		$(BC_LIB_DIR)/libipc.a \
		$(BC_LIB_DIR)/liblog.a \
		\
		-Wl,--end-group \
		$(LDFLAGS)


########################要编译的文件或目录########################	  
OBJECT = core/ module/ snmp.o
obj-y += $(OBJECT)

##################################################################
ifeq ($(CC), gcc)
	export CFLAGS LDFLAGS
else
	export CFLAGS LDFLAGS	
endif
##################################################################

#note: $(IMAGEDIR)$(TARGET1)已构成目录结构，无需写'/'。 echo前面加@表示只回显

all : 
	@echo "------------- Buildding $(TARGET) process begin -------------"

	make -C ./ -f $(TOPDIR)/Makefile.build
	$(CC) -o $(TARGET) $(CFLAGS) $(BUILDAGENTLIBS) $(BUILDLIBS) built-in.o $(BC_LIB_A)

	
	cp $(TARGET) $(BC_IMAGEDIR)/$(TARGET)
	chmod 777 $(BC_IMAGEDIR)/$(TARGET)
	
ifeq ($(CC), gcc)
	@export LD_LIBRARY_PATH=/usr/local/lib
endif

	@echo "------------- Buildding $(TARGET) process finish -------------"

##################################################################
clean:
	rm -f $(shell find -name "*.o")
	rm -f $(TARGET)
	rm -f 

distclean:
	rm -f $(shell find -name "*.o")
	rm -f $(shell find -name "*.d")
	rm -f $(TARGET)
	
############################### END ###################################
