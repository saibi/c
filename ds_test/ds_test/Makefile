#
# How to compile
#
#

PROJECT=tester

OS=$(shell uname -s)
CC=gcc
LD=ld
AR=ar
CXX = g++

INC=-I. -I../inc_ssl -I../inc_sec
COPTS=-Wall -Wstrict-prototypes -Wmissing-declarations  \
	-Winline -Wshadow -Wreturn-type -Wundef \
	-Wpointer-arith -Wcast-align -Wbad-function-cast \
	# -Wsign-compare #-Wimplicit-prototypes # -ansi-pedantic

DEFS=-DNDEBUG -DINLINE=__inline -DZERO_ARRAY_IDX=0 -D_GCC_ -D_X86_TESTER_
CFLAGS=$(COPTS) $(INC) $(DEFS) -m32
CXXFLAGS=$(CFLAGS)

EXT_LIB=$(wildcard ../extlib/*.a)

LIBS=$(EXT_LIB) #-lpthread

OBJS=main.o wrapper.o

SRCS=$(OBJS:.o=.c)

all: $(PROJECT)

$(PROJECT): $(OBJS)
	$(CC) $(CFLAGS) -o $(PROJECT) $(OBJS) $(LIBS)
	
dep:
	gcc -MM $(INC) $(SRCS) > depend

clean:
	rm -f *.o $(PROJECT) $(OBJS)

# DO NOT DELETE
-include depend

