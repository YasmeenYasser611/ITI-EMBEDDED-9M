obj-m := ledcontroldriver.o
SRC := $(shell pwd)

KDIR := $(KERNEL_SRC)

all:
	$(MAKE) -C $(KDIR) M=$(SRC) modules

modules_install:
	$(MAKE) -C $(KDIR) M=$(SRC) modules_install

clean:
	rm -f *.o *~ core .depend .*.cmd *.ko *.mod.c
	rm -f Module.markers Module.symvers modules.order
	rm -rf .tmp_versions
