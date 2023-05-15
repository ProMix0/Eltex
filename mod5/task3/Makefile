obj-m += ledctl.o

ledctl.ko: ledctl.c
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

insert: ledctl.ko rm
	sudo insmod ledctl.ko

rm:
	sudo rmmod ledctl.ko || echo Not loaded

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean