#
# c code tester makefile , created by saibi
#


# to use gcc specified in $(GCC_BIN_PATH)
ifeq ("$(GCC_BIN_PATH)","")
GCCPATH=
else
GCCPATH=$(GCC_BIN_PATH)/
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


# optimize flag : -Os optimize size, -O0 none, -O1 optimize, -O2 optimize more, -O3 optimize most
# debug format : -gdwarf-2, -gdb, ...
# debug level : -g3 maximum, -g default, -g1 minimal
DEBUG_DEF=-D_DEBUG_
DEBUG_FLAGS=-g3 -O0 
ifdef R
ifeq ($(R),1)
DEBUG_DEF=-DNDEBUG
DEBUG_FLAGS=-Os
endif
endif

DEFS=-D_GCC_ -D_SALLOC_MALLOC -DINLINE=__inline -DZERO_ARRAY_IDX=0
INC=-I. 

COPTS=-Wall -Wstrict-prototypes -Wno-trigraphs 
COPTS+=-fno-strict-aliasing -fno-common -pipe
COPTS+=-Wmissing-declarations -Winline -Wshadow -Wreturn-type -Wundef -Wpointer-arith -Wbad-function-cast #-Wcast-align -Wsign-compare 

CFLAGS=$(DEFS) $(INC) $(COPTS) $(DEBUG_FLAGS)
LDFLAGS=$(DEBUG_FLAGS) -lm
BIN_DIR=./bin
LIBS=

PRJ=tester

SRCS=$(wildcard *.c)
OBJS=$(SRCS:%.c=%.o)

all: $(PRJ) dep

$(PRJ): $(OBJS)
	@echo build code tester 
	$(Q)$(CC) $(LDFLAGS) -Wl,-Map,$(PRJ).map -o $(PRJ) $(OBJS) $(LIBS)

.c.o:
	$(Q)echo "compile $<"
	$(Q)$(CC) $(CFLAGS) -c $< -o $@

dep:
	@echo generate dependency file
	$(Q)$(CC) -MM $(CFLAGS) $(SRCS) > depend

clean:
	@echo clean all
	$(Q)rm -f $(PRJ) $(OBJS) $(PRJ).* depend *.swp 

-include depend
