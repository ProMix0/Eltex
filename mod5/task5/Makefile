obj-m += chardev.o

.PHONY: all

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

chardev.ko: chardev.c
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

insert: chardev.ko rm
	sudo insmod chardev.ko

rm:
	sudo rmmod chardev.ko || echo Not loaded

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
