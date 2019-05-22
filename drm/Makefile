OS=$(shell uname -o)
CC=$(CROSS_COMPILE)gcc
LD=$(CROSS_COMPILE)ld
AR=$(CROSS_COMPILE)ar

CFLAGS=	-Wall -Wstrict-prototypes -Wmissing-declarations  \
	-Winline -Wshadow -Wreturn-type -Wsign-compare -Wundef \
	-Wpointer-arith -Wcast-align -Wbad-function-cast \
	-I. -D_GCC_ 
	#-D_VCA_DCS_PACKED_BINARY_CODE_
	#-D__BIG_ENDIAN__ 
	#-Wimplicit-prototypes # -ansi-pedantic



ALL_SRC=$(wildcard *.c)
ALL_OBJ=$(ALL_SRC:%.c=%.o)
#ifeq ($(OS),Cygwin)
#ALL_EXE=$(ALL_SRC:%.c=%.exe)
#else
#ALL_EXE=$(ALL_SRC:%.c=%)
#endif


all: $(ALL_OBJ)
	$(CC) $(LDFLAGS) $(CFLAGS) -o drm $(ALL_OBJ)

#.SUFFIXES: .o .exe
#.o.exe:
#	$(CC) -Wall -o $@ $<


.SUFFIXES: .o .c
.c.o:
	$(CC) $(CFLAGS) -c $<


clean:
	rm -f *.o drm
