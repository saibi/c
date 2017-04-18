
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

path=
COPTS=
ifdef T 
	ifeq ("$(T)","ns")
		path=/opt/arm-2009q3/bin/arm-linux-
		COPTS=-mfloat-abi=soft
	endif
	ifeq ("$(T)","nsf")
		path=/opt/arm-2009q3/bin/arm-linux-
		COPTS=-mfloat-abi=softfp
	endif
	ifeq ("$(T)","nsfn")
		path=/opt/arm-2009q3/bin/arm-linux-
		COPTS=-march=armv7-a -mfpu=neon -mfloat-abi=softfp
	endif
	ifeq ("$(T)","nhf")
		path=/opt/gcc-linaro-arm-linux-gnueabihf-4.8-2014.04_linux/bin/arm-linux-gnueabihf-
		COPTS=-mfloat-abi=hard -march=armv7-a -mfpu=neon
	endif
	ifeq ("$(T)","ahf")
		path=/opt/gcc-linaro-arm-linux-gnueabihf-4.8-2014.04_linux/bin/arm-linux-gnueabihf-
		COPTS=-marm -mthumb-interwork -mfloat-abi=hard -mcpu=cortex-a7 -mtune=cortex-a7 -mfpu=neon-vfpv4
	endif
else
T=gcc
endif

ifdef O  
COPTS+=-O$(O)
POSTFIX=_o$(O)
endif

TEST_PRJ="libssl$(core_type_str)$(endian_str)d_$(compiler_str).a"
RELEASE_PRJ="libssl$(core_type_str)$(endian_str)_$(compiler_str).a"
PRJ=$(TEST_PRJ)


CC=$(path)gcc
LD=$(path)ld 
AS=$(path)as
AR=$(path)ar
OC=$(path)objcopy

RM=rm -f


COPTS+=-Wall -Wstrict-prototypes -Wno-trigraphs
COPTS+=-fno-strict-aliasing -fno-common -pipe
COPTS+=-Wmissing-declarations -Winline -Wshadow -Wreturn-type -Wundef -Wpointer-arith -Wbad-function-cast #-Wcast-align -Wsign-compare 

GLOBAL_DEF=-D_saibi_shady_library_ -DINLINE=__inline__ -DZERO_ARRAY_IDX=1 -DDATE_STR=\"$(date_str)\" -D_GCC_
AROPT=rcs
INC=-I. 

ASFLAGS=$(COPTS) $(INC) $(GLOBAL_DEF)
CFLAGS=$(COPTS) $(INC) $(GLOBAL_DEF) 

LIB_DIR=./lib
DIRS=
SRCS=$(foreach var,$(DIRS),$(wildcard $(var)/*.c))
OBJS=$(SRCS:%.c=%.o)

ALL_SRCS=$(SRCS) 
ALL_OBJS=$(OBJS) 


all: pretask build_all posttask 

help:
	@echo "make F=[ns|nsf|nsfn|nhf|ahf] V=[0|1] R=[0|1]"
	@echo "T(arget)"
	@echo "  ns - float-abi=soft (code sourcery arm-2009 eabi)"
	@echo "  nsf - float-abi=softfp (code sourcery arm-2009 eabi)"
	@echo "  nsfn - float-abi=softfp + neon (code sourcery arm-2009 eabi)"
	@echo "  nhf - float-abi=hard + neon (linaro eabihf)"
	@echo "  ahf - float-abi=hard + cortex-a7 (linaro eabihf)"
	@echo "V(erbose)"
	@echo "  0 - off"
	@echo "  1 - on (display compile msg)"

pretask:
	@echo Build $(T)

posttask:
	@echo end...

build_all: 
	$(CC) $(CFLAGS) adaptor.c -lm -static
	$(Q)mv a.out float_$(T)_test$(POSTFIX)
	$(CC) $(CFLAGS) int.c -static
	$(Q)mv a.out int_$(T)_test$(POSTFIX)


.s.o:
.S.o:
	@echo "assemble $<"
	$(Q)$(CC) $(ASFLAGS) $< -o $@

.c.o:
	@echo "compile $<"
	$(Q)$(CC) $(CFLAGS) $< -o $@

clean:
	$(Q)$(RM) *.o *test*

