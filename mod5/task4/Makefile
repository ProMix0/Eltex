obj-m += netlink.o

netlink.ko: netlink.c
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

insert: netlink.ko rm userspace
	sudo insmod netlink.ko

userspace: userspace.c
	gcc userspace.c -o userspace
	chmod u+x userspace

rm:
	sudo rmmod netlink.ko || echo Not loaded

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm userspace