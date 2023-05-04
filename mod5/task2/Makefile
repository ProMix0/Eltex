obj-m += prochello.o

prochello.ko: prochello.c
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

insert: prochello.ko rm
	sudo insmod prochello.ko

rm:
	sudo rmmod prochello.ko || echo Not loaded

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean