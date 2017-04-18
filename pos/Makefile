OS=$(shell uname -o)
CC=gcc
LD=ld
AR=ar

CFLAGS=-Wall -Wstrict-prototypes -Wmissing-declarations  \
	-Winline -Wshadow -Wreturn-type -Wsign-compare -Wundef \
	-Wpointer-arith -Wcast-align -Wbad-function-cast \
	-I. -I../inc_ssl -D_GCC_ -DZERO_ARRAY_IDX=1
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

TARGET=pos

OBJS=$(TARGET).o

all: $(TARGET)

EXT_LIB=$(wildcard ../extlib/*gcc.a)

$(TARGET): $(OBJS)	
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lm $(EXT_LIB)

.SUFFIXES: .o .exe

.o.exe:
	$(CC) -Wall -o $@ $<



clean:
	rm -f $(OBJS) $(TARGET)

