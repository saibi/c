#
# cross compile makefile, created by saibi
#

ifeq ("$(LINARO_ARM_GCC_BIN)","")
GCCPATH=
else
GCCPATH=$(LINARO_ARM_GCC_BIN)/
endif

PLATFORM=arm-linux-gnueabihf-

CC=$(GCCPATH)$(PLATFORM)gcc
LD=$(GCCPATH)$(PLATFORM)ld
AS=$(GCCPATH)$(PLATFORM)as
AR=$(GCCPATH)$(PLATFORM)ar
OC=$(GCCPATH)$(PLATFORM)objcopy

ifdef V
ifeq ("$(origin V)", "command line")
	VERBOSE = $(V)
endif
endif
ifndef VERBOSE
	VERBOSE = 0
endif

ifeq ($(VERBOSE),1)
	Q =
	SOPTION =
else
	Q = @
	SOPTION=-s
endif

date_str=$(shell date +%Y%m%d)
build_count_str=$(shell touch build_count.txt;cat build_count.txt)
version_str=$(shell cat version.txt | awk '{print $1;}' )



# optimize flag : -Os optimize size, -O0 none, -O1 optimize, -O2 optimize more, -O3 optimize most
# debug format : -gdwarf-2, -gdb, ...
# debug level : -g3 maximum, -g default, -g1 minimal

ifdef D 
ifeq ($(D),1)
DEBUG_DEF=-D_DEBUG_
DEBUG_FLAGS=-g3 -O0 -gdwarf-2
PREBUILT_OBJS=
EXT_LIB=
MSG="Debug Mode"
endif
endif

#ifdef R
#ifeq ($(R),1)
DEBUG_DEF=-DNDEBUG
DEBUG_FLAGS=-O0
PREBUILT_OBJS=
EXT_LIB=
MSG="Release Mode"
#endif
#endif

DIRS=.
SRCS=$(foreach var,$(DIRS),$(wildcard $(var)/*.c))
OBJS=$(SRCS:%.c=%.o)

SHARED_DIR=
SHARED_DIRS=
SHARED_SRCS_FILTER_OUT = 
SHARED_SRCS=$(foreach var,$(SHARED_DIRS),$(filter-out $(SHARED_SRCS_FILTER_OUT), $(wildcard $(var)/*.c)))
SHARED_OBJS=$(SHARED_SRCS:%.c=%.o)

AROPTS=rcs
DEFS=-DVERSION_STR=\"$(version_str)\" -DDATE_STR=\"$(date_str)\" -DBUILD_COUNT_STR=\"$(build_count_str)\"

USER_INC=-I. $(DIRS:%=-I%) 
INC=

COPTS=-Wstrict-prototypes -Wno-trigraphs 
COPTS+=-fno-strict-aliasing -fno-common -pipe
COPTS+=-Wmissing-declarations -Winline -Wshadow -Wreturn-type -Wundef -Wpointer-arith -Wbad-function-cast #-Wcast-align -Wsign-compare -Wunused-function
COPTS+=-Wall -std=gnu99 #-ffunction-sections -mfloat-abi=softfp -fmessage-length=0 -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb

CFLAGS=$(DEFS) $(INC) $(COPTS) $(DEBUG_FLAGS)
LDFLAGS=#-mcpu=cortex-m4 -mthumb $(DEBUG_FLAGS)
BIN_DIR=./bin

PRJ=test

STARTUP_OBJ=

GEN_SRCS= 
GEN_OBJS=$(GEN_SRCS:%.c=%.o)

BUILD_LIB_OBJS=$(GEN_OBJS) $(OBJS) $(SHARED_OBJS)
ALL_OBJS=$(STARTUP_OBJ) $(BUILD_LIB_OBJS)

all: msg build dep 
	$(Q)./build_count.sh ./build_count.txt

msg:
	@echo $(MSG)

RELFILE=$(BIN_DIR)/"test_V$(version_str)_$(date_str).BIN"

build: $(PRJ) 

$(PRJ): $(ALL_OBJS)
	@echo build elf
	$(Q)$(CC) $(LDFLAGS) -o $(BIN_DIR)/$(PRJ) $(ALL_OBJS) 
ifeq ($(A),1)
	$(Q)rm -f a.out
endif 


.PHONY: refresh_build_str
refresh_build_str:
	$(Q)$(CC) $(CFLAGS) -c version.c -o version.o

.s.o:
	$(Q)echo "assemble $<"
	$(Q)$(CC) -x assembler-with-cpp $(CFLAGS) -c $< -o $@

.c.o:
	$(Q)echo "compile $<"
	$(Q)$(CC) $(CFLAGS) -c $< -o $@
ifeq ($(A),1)
	$(Q)$(CC) $(CFLAGS) -S -fverbose-asm $< -o $(<:%.c=%.asm)
	$(Q)$(AS) -alhnd $(<:%.c=%.asm) > $(<:%.c=%.casm)  
endif

dep:
	@echo generate dependency file
	$(Q)$(CC) -MM $(CFLAGS) $(SRCS) > depend

clean: 
	@echo clean 
	$(Q)rm -f $(ALL_OBJS) $(BIN_DIR)/$(PRJ)

cleanall: clean
	@echo clean all
	$(Q)rm -f *.o
#	$(Q)for dir in $(DIRS); do rm -f $$dir/*.swp $$dir/*.out $$dir/*~ $$dir/*.casm $$dir/*.asm; done

allclean: cleanall

cleanasm:
	@echo clean asm 
	@find . -name '*.asm' -exec rm {} \;
	@find . -name '*.casm' -exec rm {} \;

-include depend
