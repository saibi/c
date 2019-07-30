OS=$(shell uname -o)
CC=gcc

CFLAGS=-Wall -Wstrict-prototypes -Wmissing-declarations  \
	-Winline -Wshadow -Wreturn-type -Wsign-compare -Wundef \
	-Wpointer-arith -Wcast-align -Wbad-function-cast \
	-I. -D_GCC_ 
	#-Wimplicit-prototypes # -ansi-pedantic

CROSS_CC=/opt/gcc-linaro-arm-linux-gnueabihf-4.8-2014.04_linux/bin/arm-linux-gnueabihf-gcc


OBJS=key.o

all: key 



key: $(OBJS)
	$(CC) -o $@ $(OBJS)

a20_key: $(OBJS)
	$(CROSS_CC) -o $@


%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) key a20_key

a20:
	$(CROSS_CC) $(CFLAGS) -I/usr/include -o a20_key key.c
