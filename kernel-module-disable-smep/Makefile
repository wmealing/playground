obj-m := skeleton.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD)

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD)
	rm -rf *.o *.ko
	rm -rf .skeleton*
	rm -rf .tmp_versions* 
	rm -rf .built-in.o.cmd
