obj-m := kmod.o

rustmod-y :=  rustm.o kmod.o

CFLAGS:=-fno-pic

all: main_build

main_build: kmod.c rustm.o rust
	 make -C /lib/modules/$(shell uname -r)/build M=$(PWD) CFLAGS=$(CFLAGS) modules
rust:


%.o: %.rs
	rustc -C relocation-model=static --emit=obj $< --crate-type=lib  

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean


install:
	sudo insmod rustmod.ko

remove:
	sudo rmmod rustmod.ko
