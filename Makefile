CROSS_COMPILE = arm-linux-
CC = $(CROSS_COMPILE)gcc

LINUX_DEBUG = false

export CC

EXTRA_CFLAGS += -D_TI_DM365 -D_GPIO_MODE
#EXTRA_CFLAGS += -D_TI_DM365 -D_I2C_MODE
#EXTRA_CFLAGS += -D_MOZART -D_GPIO_MODE
#EXTRA_CFLAGS += -D_MOZART -D_I2C_MODE

obj-m := focusmotor.o
KDIR := $(KERNELROOT)
PWD := $(shell pwd)

# Files needed for the build
MODULE = focusmotor.ko
INSTALL = install
INSTALL_DIR = ${ROOTFSDIR}/drivers

default:
	$(MAKE) ARCH=arm CROSS_COMPILE=arm-linux- -C $(KDIR) O=$(PRODUCTDIR)/tmp M=$(PWD) modules
clean:
	rm -rf *.ko *.o *.mod.* *.symvers test test1 *.c~ .mod* .focusmotor* .test* .tmp*

install:
	$(INSTALL) -C -o root -g root -m 644 $(MODULE) $(INSTALL_DIR)

app:
	$(CC) -D_TI_DM365 testmotor.c -o MOTORTEST


