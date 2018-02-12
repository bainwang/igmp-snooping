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
export CLI_INC_DIR 	= $(shell pwd)/include
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
export TOPDIR

## pass to C files
PROJ_DEFS_X86 := MK_CLI_PRJ_NAME_X86

TARGET := cliApp
#TARGET1 := snmpApp
IMAGEDIR := $(TOPDIR)/$(image)
	  
CFLAGS += -I $(CLI_INC_DIR)/common	\
		  -I $(CLI_INC_DIR)/common/platform \
		  -I $(CLI_INC_DIR)/common/print \
		  -I $(CLI_INC_DIR)/common/util \
		  -I $(CLI_INC_DIR)/common/vfs \
		  -I $(CLI_INC_DIR)/module	\
		  -I $(CLI_INC_DIR)/module/filetrans \
		  -I $(CLI_INC_DIR)/core
		  
ifeq ($(CC), gcc)
	CFLAGS += -D $(PROJ_DEFS_X86)
endif
LDFLAGS := -lpthread -lrt
##################################################################		  

obj-y += common/
obj-y += module/
obj-y += core/
obj-y += bc_cli.o

##################################################################
ifeq ($(CC), gcc)
	export CFLAGS LDFLAGS
else
	export CFLAGS LDFLAGS	
endif
##################################################################

#note: $(IMAGEDIR)$(TARGET1)已构成目录结构，无需写'/'。 echo前面加@表示只回显
all : 
ifeq ($(CC), gcc)
	@echo "********[CLI PRJ NAME IS X86]********"
else
	@echo "********[CLI PRJ NAME IS 610A]********"
endif

	make -C ./ -f $(TOPDIR)/Makefile.build
	
	$(CC) -o $(TARGET) $(CFLAGS) $(LDFLAGS) $(BUILDAGENTLIBS) $(BUILDLIBS) built-in.o


##################################################################
#	mv $(TARGET) $(IMAGEDIR)$(TARGET1)
#	chmod 777 $(IMAGEDIR)$(TARGET1)

ifeq ($(CC), gcc)
	@export LD_LIBRARY_PATH=/usr/local/lib
	@echo "============ BUILD FINISHED, PRJ NAME IS [X86] ============"
else
	@echo "============ BUILD FINISHED, PRJ NAME IS [610A] ============"
endif
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
