OS=$(shell uname -o)
CC=gcc
LD=ld
AR=ar

CFLAGS=-Wall -Wstrict-prototypes -Wmissing-declarations  \
	-Winline -Wshadow -Wreturn-type -Wsign-compare -Wundef \
	-Wpointer-arith -Wcast-align -Wbad-function-cast \
	-I. -D_GCC_ \
	-g -fprofile-arcs -ftest-coverage -O0

	#-D_VCA_DCS_PACKED_BINARY_CODE_
	#-D__BIG_ENDIAN__ 
	#-Wimplicit-prototypes # -ansi-pedantic

LDFLAGS=-g -fprofile-arcs -ftest-coverage -O0


#ALL_SRC=$(wildcard *.c)
#ALL_OBJ=$(ALL_SRC:%.c=%.o)
#ifeq ($(OS),Cygwin)
#ALL_EXE=$(ALL_SRC:%.c=%.exe)
#else
#ALL_EXE=$(ALL_SRC:%.c=%)
#endif

OBJS=main.o cov.o

all: test

test: $(OBJS)	
	$(CC) $(CFLAGS) -o test $(OBJS)

.SUFFIXES: .o .exe

.o.exe:
	$(CC) -Wall -o $@ $<



clean:
	rm -f *.o *.gcno *.gcda *.gcov test

