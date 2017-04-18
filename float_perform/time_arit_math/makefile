# Copyright 2014-2015 Nicolas Limare <nicolas@limare.net>
#
# Copying and distribution of this file, with or without modification,
# are permitted in any medium without royalty provided the copyright
# notice and this notice are preserved. This file is offered as-is,
# without any warranty.

C99 	= c99
CFLAGS	= -g -Ofast #-DNOFLT80 -DNOFLT128 #-DNOMEMALIGN
LDFLAGS	=
LDLIBS	= -lm -lrt


CSRC	= $(wildcard *.c)
CHDR	= $(wildcard *.h)

default	: time_arit time_math
	@echo "["
	@taskset -c 0 ./time_arit 2>/dev/null \
		| sed -e 's/\[i\]//g' -e 's/^/[/' -e 's/$$/],/'
	@echo "]"
	@echo "["
	@taskset -c 0 ./time_math 2>/dev/null \
		| sed -e 's/\[i\]//g' -e 's/^/[/' -e 's/$$/],/'
	@echo "]"

time_arit	: time_arit.o timing.o
	$(C99) $(LDFLAGS) $^ $(LDLIBS) -o $@
time_math	: time_math.o timing.o
	$(C99) $(LDFLAGS) $^ $(LDLIBS) -o $@

%.o	: %.c
	$(C99) -c $(CFLAGS) $< -o $@


.PHONY	: clean distclean beautify lint
clean	:
	$(RM) *.o
distclean	: clean
	$(RM) time_arit time_math
beautify: $(CSRC) $(CHDR) 
	astyle -O $^
	$(RM) *.orig
lint	: $(CSRC)
	clang --analyze $^ -DNOFLT80 -DNOFLT128
	$(RM) *.plist
