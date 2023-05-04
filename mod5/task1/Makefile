obj-m += helloworld.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

insert: helloworld.ko
	sudo insmod helloworld.ko

rm:
	sudo rmmod helloworld.ko

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean