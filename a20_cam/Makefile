CC := /opt/gcc-linaro-arm-linux-gnueabihf-4.8-2014.04_linux/bin/arm-linux-gnueabihf-gcc 
LINUX_DIR := /home/saibi/work_space/a20_platform/kernel/huvitz_latest/linux-sunxi/include
CFLAGS := -Wall #-I$(LINUX_DIR)
TARGET := app_test

.PHONY: all clean


all: $(TARGET)

app_test:app_test_ok.c
	$(CC) $(CFLAGS) -static  $^  -o  $@

clean:
	rm -rf $(TARGET)
