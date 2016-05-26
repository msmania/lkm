KERNEL_DIR:=/lib/modules/$(shell uname -r)/build
obj-m := tiny.o
driver: tiny.c
	make -C $(KERNEL_DIR) SUBDIRS=`pwd` modules
