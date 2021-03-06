########################################################
#### This is basically a copy of OpenNI Makefiles   ####
########################################################


# Compile with gcc: make
# Compile with clang: CXX=clang++ make 

BIN_DIR = ./bin

SRC_FILES = ./src/*.cpp

CFLAGS += -I/usr/include/ni `pkg-config --cflags allegro-5.0 allegro_font-5.0 allegro_ttf-5.0 allegro_image-5.0 allegro_primitives-5.0`
LDFLAGS += -lOpenNI `pkg-config --libs allegro-5.0 allegro_font-5.0 allegro_ttf-5.0 allegro_image-5.0 allegro_primitives-5.0`


EXE_NAME = sprites

CFLAGS += -D__x86_64__ -Dlinux

CFG = Debug
#CFG = Release







#############################################################################
# Primesense template makefile.
# This file should not be made, but only included from other makefiles.
# By default, this makefile compiles in release. To compile a debug version:
#    make CFG=Debug
#
# Project makefile should define the following BEFORE including this file:
# SRC_FILES - a list of all source files
# Output name under one of the following:
#     EXE_NAME (executable), 
#     LIB_NAME (dynamic library) or 
#     SLIB_NAME (static library) or
# BIN_DIR - Bin directory (output dir)
# INC_DIRS - a list of additional include directories
# LIB_DIRS - a list of additional library directories
# USED_LIBS - a list of libraries to link with
# DEFINES - [Optional] additional preprocessor defines
# CFLAGS - [Optional] additional flags for the compiler
# LDFLAGS - [Optional] additional flags for the linker
# SSE_GENERATION - [Optional] The SSE generation to use (default is 3)
# TARGET_SYS_ROOT - [Optional] The path to the root of the target
#############################################################################

# take this file's dir
COMMON_CPP_MAKE_FILE_DIR = $(dir $(lastword $(MAKEFILE_LIST)))

#include $(COMMON_CPP_MAKE_FILE_DIR)CommonDefs.mak







# some defaults
ifndef CFG
    CFG = Release
endif

# find out the platform on which we're running
MACHINE = $(shell uname -m)
ifneq (,$(findstring x86_64,$(MACHINE)))
	HOST_PLATFORM = x64
else ifneq (,$(findstring x86,$(MACHINE)))
	HOST_PLATFORM = x86
else ifneq (,$(findstring i686,$(MACHINE)))
	HOST_PLATFORM = x86
else ifneq (,$(findstring i386,$(MACHINE)))
	HOST_PLATFORM = x86
else ifneq (,$(findstring arm,$(MACHINE)))
	HOST_PLATFORM = Arm
else
	DUMMY:=$(error Can't determine host platform)
endif

# now check if this is a cross-compilation or not
ifeq "$(PLATFORM)" ""
	PLATFORM = $(HOST_PLATFORM)
else
	ifneq "$(PLATFORM)" "$(HOST_PLATFORM)"
		# cross compiling. Take CXX and STAGING_DIR from environment
		PLATFORM_UPPER = $(shell echo $(PLATFORM) | tr 'a-z' 'A-Z')
		DUMMY:=$(eval CXX = $($(PLATFORM_UPPER)_CXX))
		DUMMY:=$(eval TARGET_SYS_ROOT = $($(PLATFORM_UPPER)_STAGING))
		
		ifeq "$(and $(CXX), $(TARGET_SYS_ROOT))" ""
			DUMMY:=$(error Cross-Compilation error. Can't find $(PLATFORM_UPPER)_CXX and $(PLATFORM_UPPER)_STAGING)
		endif
	endif
endif

# expand file list
SRC_FILES_LIST = $(wildcard $(SRC_FILES))

# define the intermediate directory
INT_DIR = $(PLATFORM)-$(CFG)

# define output directory
OUT_DIR = $(BIN_DIR)/$(PLATFORM)-$(CFG)

# full path to output file
OUTPUT_FILE = $(OUT_DIR)/$(OUTPUT_NAME)

# take this file's dir
COMMON_MAK_DIR = $(dir $(lastword $(MAKEFILE_LIST)))

# platform specific args
#include $(COMMON_MAK_DIR)Platform.$(PLATFORM)




# take this file's dir
COMMON_MAK_DIR = $(dir $(lastword $(MAKEFILE_LIST)))

# everything is the same as in x86
#include $(COMMON_MAK_DIR)Platform.x86





# some defaults
export GLUT_SUPPORTED=1

ifndef SSE_GENERATION
	SSE_GENERATION = 3
endif

ifeq ($(SSE_GENERATION), 2)
	CFLAGS += -msse2
else
	ifeq ($(SSE_GENERATION), 3)
		CFLAGS += -msse3
		ifeq ($(SSSE3_ENABLED), 1)
			CFLAGS += -mssse3
		endif
	else
		DUMMY:=($error "Only SSE2 and SSE3 are supported")
	endif
endif









# define a function to figure .o file for each source file (placed under intermediate directory)
SRC_TO_OBJ = $(addprefix ./$(INT_DIR)/,$(addsuffix .o,$(notdir $(basename $1))))

# create a list of all object files
OBJ_FILES = $(call SRC_TO_OBJ,$(SRC_FILES_LIST))

# define a function to translate any source file to its dependency file (note that the way we create
# dep files, as a side affect of compilation, always puts the files in the INT_DIR with suffix .d)
SRC_TO_DEP = $(addprefix ./$(INT_DIR)/,$(addsuffix .d,$(notdir $(basename $1))))

# create a list of all dependency files
DEP_FILES = $(call SRC_TO_DEP,$(SRC_FILES_LIST))

# append the -L switch to each library directory
LIB_DIRS_OPTION = $(foreach dir,$(LIB_DIRS),-L$(dir)) -L$(OUT_DIR)

# append the -D switch to each define
DEFINES_OPTION = $(foreach def,$(DEFINES),-D$(def))

# tell compiler to use the target system root
ifdef TARGET_SYS_ROOT
	CFLAGS += --sysroot=$(TARGET_SYS_ROOT)
	LDFLAGS += --sysroot=$(TARGET_SYS_ROOT)
endif

# set Debug / Release flags
ifeq "$(CFG)" "Debug"
	CFLAGS += -O0 -g
endif
ifeq "$(CFG)" "Release"
	CFLAGS += -O2 -DNDEBUG
endif

CFLAGS += $(DEFINES_OPTION)
LDFLAGS += $(LIB_DIRS_OPTION)

# some lib / exe specifics
ifneq "$(LIB_NAME)" ""
	OUTPUT_NAME = lib$(LIB_NAME).so
	CFLAGS += -fPIC -fvisibility=hidden
	LDFLAGS += -Wl,--no-undefined
	OUTPUT_NAME = lib$(LIB_NAME).so
	OUTPUT_COMMAND = $(CXX) -o $(OUTPUT_FILE) $(OBJ_FILES) $(LDFLAGS) -shared
endif
ifneq "$(EXE_NAME)" ""
	OUTPUT_NAME = $(EXE_NAME)
	OUTPUT_COMMAND = $(CXX) -o $(OUTPUT_FILE) $(OBJ_FILES) $(LDFLAGS)
endif
ifneq "$(SLIB_NAME)" ""
	CFLAGS += -fPIC
	OUTPUT_NAME = lib$(SLIB_NAME).a
	OUTPUT_COMMAND = $(AR) -cq $(OUTPUT_FILE) $(OBJ_FILES)
endif

define CREATE_SRC_TARGETS
# create a target for the object file (the CXX command creates both an .o file
# and a .d file)
$(call SRC_TO_OBJ,$1) : $1 | $(INT_DIR)
	$(CXX) -MD -MP -MT "$(call SRC_TO_DEP,$1) $$@" -c $(CFLAGS) -o $$@ $$<
endef

#############################################################################
# Targets
#############################################################################
.PHONY: clean-objs clean-defs

#include $(COMMON_CPP_MAKE_FILE_DIR)CommonTargets.mak






#############################################################################
# Targets
#############################################################################
.PHONY: all clean clean-$(OUTPUT_FILE)

# define the target 'all' (it is first, and so, default)
all: $(OUTPUT_FILE)
	cp ../../external/ttf-bitstream-vera-1.10/VeraMono.ttf $(OUT_DIR)

# Intermediate directory
$(INT_DIR):
	mkdir -p $(INT_DIR)

# Output directory
$(OUT_DIR):
	mkdir -p $(OUT_DIR)

# Final output file
$(OUTPUT_FILE): $(SRC_FILES_LIST) | $(OUT_DIR)

clean-$(OUTPUT_FILE):
	rm -rf $(OUTPUT_FILE)
	
clean: clean-$(OUTPUT_FILE)








# create targets for each source file
$(foreach src,$(SRC_FILES_LIST),$(eval $(call CREATE_SRC_TARGETS,$(src))))

# include all dependency files (we don't need them the first time, so we can use -include)
-include $(DEP_FILES)

$(OUTPUT_FILE): $(OBJ_FILES)
	$(OUTPUT_COMMAND)

clean-objs:
	rm -rf $(OBJ_FILES)
	
clean-defs:
	rm -rf $(DEP_FILES)

clean: clean-objs clean-defs
