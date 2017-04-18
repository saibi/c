OS=$(shell uname -o)
CC=gcc
LD=ld
AR=ar

CFLAGS=-Wall -Wstrict-prototypes -Wmissing-declarations  \
	-Winline -Wshadow -Wreturn-type -Wsign-compare -Wundef \
	-Wpointer-arith -Wcast-align -Wbad-function-cast \
	-I. -D_GCC_  -I./inc_ssl \
	-DZERO_ARRAY_IDX=1
	#-D_VCA_DCS_PACKED_BINARY_CODE_
	#-D__BIG_ENDIAN__ 
	#-Wimplicit-prototypes # -ansi-pedantic


#ALL_SRC=$(wildcard *.c)
#ALL_OBJ=$(ALL_SRC:%.c=%.o)
#ifeq ($(OS),Cygwin)
#ALL_EXE=$(ALL_SRC:%.c=%.exe)
#else
#ALL_EXE=$(ALL_SRC:%.c=%)
#endif

TARGET=ascii_diff

OBJS=$(TARGET).o

all: $(TARGET)

$(TARGET): $(OBJS)	
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) extlib/libsslxld_gcc.a -lm 

.SUFFIXES: .o .exe

.o.exe:
	$(CC) -Wall -o $@ $<



clean:
	rm -f $(OBJS) $(TARGET)

