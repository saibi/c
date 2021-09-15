SRC_DIRS=. dirs
SRCS0=$(foreach var,$(SRC_DIRS),$(wildcard $(var)/*.c))
SRCS=$(foreach var,$(SRC_DIRS),$(wildcard $(var)/*.c))

OBJS=$(SRCS:%.c=%.o)

INC_FLAGS=$(SRC_DIRS:%=-I%)
CFLAGS=-Wall $(INC_FLAGS)

all: dep $(OBJS)
	gcc -Wall -o main $(OBJS)

.c.o:
	@echo "compile $<"
	gcc $(CFLAGS) -c $< -o $@

dep: 
	gcc -MM $(SRCS) > depend

clean:
	rm -f $(OBJS) main

-include depend
