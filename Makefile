KERNEL_DIR:=/lib/modules/$(shell uname -r)/build
obj-m := tiny.o

all: driver client

driver: tiny.c
	make -C $(KERNEL_DIR) SUBDIRS=`pwd` modules

client: client.c
	gcc client.c -o t

load:
	sudo insmod tiny.ko

unload:
	sudo rmmod tiny

log:
	dmesg | tail -n 10
