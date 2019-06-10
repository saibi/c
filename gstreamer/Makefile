OS=$(shell uname -o)
CC=$(CROSS_COMPILE)gcc
LD=$(CROSS_COMPILE)ld
AR=$(CROSS_COMPILE)ar

CFLAGS=	-Wall -Wstrict-prototypes -Wmissing-declarations  \
	-Winline -Wshadow -Wreturn-type -Wsign-compare -Wundef \
	-Wpointer-arith -Wcast-align -Wbad-function-cast \
	-I. \
	`pkg-config --cflags gstreamer-audio-1.0 gstreamer-video-1.0 gtk+-3.0 gstreamer-1.0 gstreamer-pbutils-1.0` 

	# normal `pkg-config --cflags gstreamer-1.0`
	# for gtk-player `pkg-config --cflags gstreamer-video-1.0 gtk+-3.0  gstreamer-1.0` 


LIBS=`pkg-config --libs gstreamer-audio-1.0 gstreamer-video-1.0 gtk+-3.0  gstreamer-1.0 gstreamer-pbutils-1.0` 

	#-D_GCC_  
	#-Wimplicit-prototypes # -ansi-pedantic



ALL_SRC=$(wildcard *.c)
ALL_OBJ=$(ALL_SRC:%.c=%.o)
ALL_BIN=$(ALL_SRC:%.c=%)

all: $(ALL_OBJ)

%.o : %.c
	$(CC) $(CFLAGS) -c $< 
	$(CC) -o $(basename $@) $@ $(LIBS)


clean:
	rm -f *.o $(ALL_BIN)
