INCLUDE := /usr/src/linux-headers-$(shell uname -r)/include/
INCLUDE += /usr/src/linux-headers-$(shell uname -r)/arch/x86/include/

CC      := gcc

ifneq ($(KERNELRELEASE),)

TARGET	+= beaglebone_driver

obj-m	+= beaglebone_driver.o

else

KDIR := /lib/modules/$(shell uname -r)/build
PWD  := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules -Wdeclaration-after-statement
endif

clean:
	rm -f -r *.o *.ko .*cmd .tmp* core *.i

depend .depend dep:
	$(CC) $(CFLAGS) $(INCLUDE) -M *.c > .depend

ifeq (.depend,$(wildcard .depend))
include .depend
endif
