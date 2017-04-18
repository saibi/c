OS=$(shell uname -o)
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

LIBS= #../minini/minIni.o -lpthread

OBJS=test.o  #binsend.o
SRCS=$(OBJS:.o=.c)

TARGET=test #binsend



all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)
	
dep:
	gccmakedep $(SRCS)

clean:
	rm -f *.o $(TARGET)

# DO NOT DELETE
binsend.o: binsend.c /usr/include/sys/types.h \
  /usr/include/sys/appleapiopts.h /usr/include/sys/cdefs.h \
  /usr/include/machine/types.h /usr/include/i386/types.h \
  /usr/include/i386/_types.h /usr/include/sys/_types.h \
  /usr/include/machine/_types.h /usr/include/machine/endian.h \
  /usr/include/i386/endian.h /usr/include/sys/_endian.h \
  /usr/include/libkern/_OSByteOrder.h \
  /usr/include/libkern/i386/_OSByteOrder.h /usr/include/sys/_structs.h \
  /usr/include/sys/stat.h /usr/include/Availability.h \
  /usr/include/AvailabilityInternal.h /usr/include/fcntl.h \
  /usr/include/sys/fcntl.h /usr/include/termios.h \
  /usr/include/sys/termios.h /usr/include/sys/ttycom.h \
  /usr/include/sys/ioccom.h /usr/include/sys/ttydefaults.h \
  /usr/include/_types.h /usr/include/stdio.h /usr/include/secure/_stdio.h \
  /usr/include/secure/_common.h /usr/include/stdlib.h \
  /usr/include/sys/wait.h /usr/include/sys/signal.h \
  /usr/include/machine/signal.h /usr/include/i386/signal.h \
  /usr/include/i386/_structs.h /usr/include/machine/_structs.h \
  /usr/include/mach/i386/_structs.h /usr/include/sys/resource.h \
  /usr/include/alloca.h /usr/include/string.h \
  /usr/include/secure/_string.h /usr/include/unistd.h \
  /usr/include/sys/unistd.h /usr/include/sys/select.h \
  /usr/include/sys/_select.h /usr/include/sys/time.h /usr/include/time.h \
  /usr/include/_structs.h
