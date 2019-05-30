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



ALL_SRC=$(wildcard *.c)
ALL_OBJ=$(ALL_SRC:%.c=%.o)

all: $(ALL_OBJ)
	$(CC) -o t1 basic_tutorial-1.o $(LIBS) 
	$(CC) -o t2 basic_tutorial-2.o $(LIBS) 

.SUFFIXES: .o .c
.c.o:
	$(CC) $(CFLAGS) -c $< 


clean:
	rm -f *.o $(TARGET)
