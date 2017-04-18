#
# How to compile
#
# 1. build minini first : cd ../minini ; make clean; make
# 2. copy minIni.o 
# 3. make dep; make
#

PROJECT=bintr

OS=$(shell uname -s)
CC=gcc
LD=ld
AR=ar
CXX = g++

INC=-I. -I./inc
COPTS=-Wall -Wstrict-prototypes -Wmissing-declarations  \
	-Winline -Wshadow -Wreturn-type -Wsign-compare -Wundef \
	-Wpointer-arith -Wcast-align -Wbad-function-cast #-Wimplicit-prototypes
	# -ansi-pedantic

DEFS=-DNDEBUG
CFLAGS=$(COPTS) $(INC) $(DEFS)
CXXFLAGS=$(CFLAGS)

LIBS=../minini_09/minIni.o -lpthread

OBJS=main.o checksum.o file.o cmdarg.o serial.o
SRCS=$(OBJS:.o=.c)

all: $(PROJECT)

$(PROJECT): $(OBJS)
	$(CC) $(CFLAGS) -o $(PROJECT) $(OBJS) $(LIBS)
	
dep:
	gcc -MM $(INC) $(SRCS) > depend

clean:
	rm -f *.o $(PROJECT)

# DO NOT DELETE
-include depend

