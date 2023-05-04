obj-m += helloworld.o

helloworld.ko: helloworld.c
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

insert: helloworld.ko rm
	sudo insmod helloworld.ko

rm:
	sudo rmmod helloworld.ko || echo Not loaded

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean