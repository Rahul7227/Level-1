

#obj-m := static.o
#obj-m := dynamic1.o
#obj-m := dynamic.o
#obj-m := dyn-chardriver.o
#obj-m := 12.o
obj-m := hellow2.o

KERNELDIR = /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)


default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean

install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install




