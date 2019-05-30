OS=$(shell uname -o)
CC=$(CROSS_COMPILE)gcc
LD=$(CROSS_COMPILE)ld
AR=$(CROSS_COMPILE)ar

CFLAGS=	-Wall -Wstrict-prototypes -Wmissing-declarations  \
	-Winline -Wshadow -Wreturn-type -Wsign-compare -Wundef \
	-Wpointer-arith -Wcast-align -Wbad-function-cast \
	-I. \
	`pkg-config --cflags gstreamer-1.0`

LIBS= `pkg-config --libs gstreamer-1.0`

	#-D_GCC_  
	#-Wimplicit-prototypes # -ansi-pedantic


TARGET = test

ALL_SRC=$(wildcard *.c)
ALL_OBJ=$(ALL_SRC:%.c=%.o)

all: basic_tutorial-1.o 
	$(CC) -o $(TARGET) basic_tutorial-1.o $(LIBS) 

.SUFFIXES: .o .c
.c.o:
	$(CC) $(CFLAGS) -c $< 


clean:
	rm -f *.o $(TARGET)
