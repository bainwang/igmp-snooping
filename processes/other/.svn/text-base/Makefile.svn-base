##################################################################
##          For igmp by wangb@longraise.com                     ##
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
export BC_INC_DIR 	= $(shell pwd)/../../include
	
##################################################################
TOPDIR := $(shell pwd)
export TOPDIR

BC_IMAGEDIR := $(TOPDIR)/../../image

## pass to C files
#PROJ_DEFS_X86 := MK_OTHER_PRJ_NAME_X86

TARGET := otherImage

########################### INCLUDE DIR ##############################
CFLAGS += -I $(TOPDIR)	\
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
	  

		  
#ifeq ($(CC), gcc)
#	CFLAGS += -D $(PROJ_DEFS_X86)
#endif
LDFLAGS := -lpthread -lrt

#############################静态库###############################
BC_LIB_DIRETOR := $(TOPDIR)/../../lib_a

LIB_A += -Wl,--start-group \
		$(BC_LIB_DIRETOR)/libcommon.a \
		$(BC_LIB_DIRETOR)/libplatform.a \
		$(BC_LIB_DIRETOR)/libsession.a  \
		$(BC_LIB_DIRETOR)/libipc.a \
		$(BC_LIB_DIRETOR)/liblog.a \
		\
		-Wl,--end-group \
		$(LDFLAGS)


##################################################################		  
OBJECT = othermain.o

obj-y += $(OBJECT)

##################################################################
ifeq ($(CC), gcc)
	export CFLAGS LDFLAGS
else
	export CFLAGS LDFLAGS	
endif
##################################################################
all : 
	@echo "------------- Buildding $(TARGET) process begin -------------"

	make -C ./ -f $(TOPDIR)/Makefile.build
	$(CC) -o $(TARGET) $(CFLAGS) built-in.o $(LIB_A)

	cp $(TARGET) $(BC_IMAGEDIR)/$(TARGET)
	chmod 777 $(BC_IMAGEDIR)/$(TARGET)

	@echo "------------- Buildding $(TARGET) process finish -------------"
##################################################################

clean:
	rm -f $(shell find -name "*.o")
	rm -f $(shell find -name "*.a")
	rm -f $(BC_IMAGEDIR)/*
	rm -f $(TARGET)

distclean:
	rm -f $(shell find -name "*.o")
	rm -f $(shell find -name "*.d")
	rm -f $(shell find -name "*.a")
	rm -f $(BC_IMAGEDIR)/*
	rm -f $(TARGET)
	
############################### END ###################################
