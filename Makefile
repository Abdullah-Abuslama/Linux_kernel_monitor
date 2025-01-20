# Makefile for kernel module and user application
KERNEL_VERSION := $(shell uname -r)
KERNEL_DIR := /lib/modules/$(KERNEL_VERSION)/build
PWD := $(shell pwd)

ARCH := x86_64

# Kernel module
obj-m += Kernel_Module.o

# Build targets
all: kernel_module user_app

kernel_module:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules

user_app: User_Space_Application.c
	gcc -o monitor User_Space_Application.c -lncurses

clean:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) clean
	rm -f monitor