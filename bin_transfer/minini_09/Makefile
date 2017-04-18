OS=$(shell uname -o)
CC=gcc
LD=ld
AR=ar

CFLAGS=-Wall -Wstrict-prototypes -Wmissing-declarations  \
	-Winline -Wshadow -Wreturn-type -Wsign-compare -Wundef \
	-Wpointer-arith -Wcast-align -Wbad-function-cast #-Wimplicit-prototypes
	# -ansi-pedantic


ALL_SRC=$(wildcard *.c)
ALL_OBJ=$(ALL_SRC:%.c=%.o)
ifeq ($(OS),Cygwin)
ALL_EXE=$(ALL_SRC:%.c=%.exe)
else
ALL_EXE=$(ALL_SRC:%.c=%)
endif

all: minini

minini:	minIni.o minIni.h minGlue.h

	

.SUFFIXES: .o .exe

.o.exe:
	$(CC) -Wall -o $@ $<



clean:
	rm -f $(ALL_OBJ) $(ALL_EXE)

