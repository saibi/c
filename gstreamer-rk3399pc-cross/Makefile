OS=$(shell uname -o)
CROSS_COMPILE=/opt/gcc-linaro-7.3.1-2018.05-i686_aarch64-linux-gnu/bin/aarch64-linux-gnu-

CC=$(CROSS_COMPILE)gcc
LD=$(CROSS_COMPILE)ld
AR=$(CROSS_COMPILE)ar

SYSROOT=/opt/rootfs-rk3399pc-ubuntu18.04

CFLAGS=	--sysroot=$(SYSROOT) \
	-Wall -Wstrict-prototypes -Wmissing-declarations  \
	-Winline -Wshadow -Wreturn-type -Wsign-compare -Wundef \
	-Wpointer-arith -Wcast-align -Wbad-function-cast \
	-I. \
	`pkg-config --cflags gstreamer-1.0` 
	#`pkg-config --cflags gstreamer-audio-1.0 gstreamer-video-1.0 gtk+-3.0 gstreamer-1.0 gstreamer-pbutils-1.0` 
	# normal `pkg-config --cflags gstreamer-1.0`
	# for gtk-player `pkg-config --cflags gstreamer-video-1.0 gtk+-3.0  gstreamer-1.0` 

LFLAGS = -Wl,-rpath-link,$(SYSROOT)/usr/lib/aarch64-linux-gnu -Wl,-rpath-link,$(SYSROOT)/lib/aarch64-linux-gnu --sysroot=$(SYSROOT)

LIBS= \
	`pkg-config --libs gstreamer-1.0` 

	#`pkg-config --libs gstreamer-audio-1.0 gstreamer-video-1.0 gtk+-3.0  gstreamer-1.0 gstreamer-pbutils-1.0` 
	#-D_GCC_  
	#-Wimplicit-prototypes # -ansi-pedantic



#ALL_SRC=$(wildcard *.c)
ALL_SRC=3-dynamic3.c
ALL_OBJ=$(ALL_SRC:%.c=%.o)
ALL_BIN=$(ALL_SRC:%.c=%)

all: $(ALL_OBJ)

%.o : %.c
	$(CC) $(CFLAGS) -c $< 
	$(CC) $(LFLAGS) -o $(basename $@) $@ $(LIBS)


clean:
	rm -f *.o $(ALL_BIN)
