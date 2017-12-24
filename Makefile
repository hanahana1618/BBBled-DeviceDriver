obj-m+=bbb_dev.o
all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
	$(CC) bbb_user.c bbb_user.h -o user_bbb
rm:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
	rm user_bbb
