UNAME=$(shell uname -s)
ifeq ($(UNAME),Linux)
CPPCHECK=/usr/bin/cppcheck
NSIQ=/opt/nsiqcollector/nsiqcollector
else
CPPCHECK=
NSIQ=
endif


CC=$(GCCPATH)gcc
LD=$(GCCPATH)ld
AS=$(GCCPATH)as
AR=$(GCCPATH)ar
OC=$(GCCPATH)objcopy

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
model_str=X86

# optimize flag : -Os optimize size, -O0 none, -O1 optimize, -O2 optimize more, -O3 optimize most
# debug format : -gdwarf-2, -gdb, ...
# debug level : -g3 maximum, -g default, -g1 minimal

D=1
ifdef D 
ifeq ($(D),1)
DEBUG_DEF=-D_DEBUG_
DEBUG_FLAGS=-g3 -O0 
PREBUILT_OBJS=
EXT_LIB=-lsecxld_gcc -lsslxld_gcc
MSG="Debug Mode"
endif
endif

ifdef R
ifeq ($(R),1)
DEBUG_DEF=-DNDEBUG
DEBUG_FLAGS=-O2
PREBUILT_OBJS=
EXT_LIB=-lsecxl_gcc -lsslxl_gcc
MSG="Release Mode"
endif
endif

DIRS=src 
SRCS=$(foreach var,$(DIRS),$(wildcard $(var)/*.c))
OBJS=$(SRCS:%.c=%.o)

DEFS += 
MOTOR_MAGIC=pseudo
BINFILE=$(BIN_DIR)/pseudo_motor

EXCLUDE_OBJS=
EXCLUDE_SHARED_OBJS=

FILTERED_OBJS=$(filter-out $(EXCLUDE_OBJS), $(OBJS))
OBJS:=$(FILTERED_OBJS)

AROPTS=rcs
DEFS+=-D_GCC_ -D_SALLOC_MALLOC -DINLINE=__inline -DZERO_ARRAY_IDX=0 -DVERSION_STR=\"$(version_str)\" -DDATE_STR=\"$(date_str)\" -DBUILD_COUNT_STR=\"$(build_count_str)\"

LIB_INC=-I./inc_ssl -I./inc_sec
USER_INC=-I. $(DIRS:%=-I./%) 
INC=$(LIB_INC) $(USER_INC)

COPTS=-Wstrict-prototypes -Wno-trigraphs 
COPTS+=-fno-strict-aliasing -fno-common -pipe
COPTS+=-Wmissing-declarations -Winline -Wshadow -Wreturn-type -Wundef -Wpointer-arith -Wbad-function-cast #-Wcast-align -Wsign-compare -Wunused-function
COPTS+=-Wall -std=gnu99 -ffunction-sections # -mfloat-abi=softfp -fmessage-length=0 -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb

CFLAGS=$(DEFS) $(INC) $(COPTS) $(DEBUG_FLAGS)
LDFLAGS=$(DEBUG_FLAGS)
BIN_DIR=./bin

PRJ=PSEUDO

STARTUP_OBJ=

BUILD_LIB_OBJS=$(OBJS) 
ALL_OBJS=$(STARTUP_OBJ) $(BUILD_LIB_OBJS)

all: msg build dep 
	$(Q)./build_count.sh ./build_count.txt

msg:
	@echo Build $(model_str)_MOTOR $(MSG)
	@if [ ! -d $(BIN_DIR) ]; then \
		mkdir $(BIN_DIR); \
	fi

RELFILE=$(BIN_DIR)/"$(model_str)_MOTOR_$(version_str)_$(date_str).BIN"

build: $(PRJ) 
	$(Q)cp $(BINFILE) $(RELFILE)
	@if [ -f /usr/local/bin/md5_generator ]; then \
		md5_generator $(BINFILE) ; \
		md5_generator $(RELFILE) ; \
	fi

$(PRJ): refresh_build_str $(ALL_OBJS)
	@echo build 
	$(Q)$(CC) $(LDFLAGS) -o $(BINFILE) $(ALL_OBJS) -L./extlib $(EXT_LIB) -lm
ifeq ($(A),1)
	$(Q)rm -f a.out
endif 


.PHONY: refresh_build_str
refresh_build_str:
	$(Q)$(CC) $(CFLAGS) -c src/version.c -o src/version.o

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
	$(Q)rm -f $(BINFILE)* $(RELFILE)* 
	$(Q)rm -f libobjs.a *.o src/*.o
	$(Q)rm -f $(BIN_DIR)/$(PRJ).* 
	$(Q)rm -f $(OBJS) $(SHARED_OBJS)
	$(Q)for dir in $(DIRS); do rm -f $$dir/*.o; done
	$(Q)for dir in $(SHARED_DIRS); do rm -f $$dir/*.o; done

cleanall: clean
	@echo clean all
	$(Q)rm -f $(ALL_OBJS) 
	$(Q)for dir in $(DIRS); do rm -f $$dir/*.swp $$dir/*.out $$dir/*~ $$dir/*.casm $$dir/*.asm; done
	$(Q)rm -f $(BIN_DIR)/$(model_str)_MOTOR*

allclean: cleanall

cleanasm:
	@echo clean asm 
	@find . -name '*.asm' -exec rm {} \;
	@find . -name '*.casm' -exec rm {} \;

cppcheck:
	$(Q)if [ -f $(CPPCHECK) ]; then \
		$(CPPCHECK) -q --enable=all --inline-suppr -iDave -ICMSIS -ibin . ; \
	fi

nsiq:
	$(Q)if [ -f $(NSIQ) ]; then \
		$(NSIQ) -f nsiq_filter.txt . ; \
	fi

help:
	@echo "build : $ make"
	@echo "clean : $ make clean"


# dependency
-include depend

