obj-m = device.o driver.o

KDIR = /lib/modules/$(shell uname -r)/build

all:
	make -C ${KDIR} M=$(shell pwd) modules