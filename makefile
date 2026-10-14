CC = i686-elf-gcc
ASM = nasm
MKGRUB = grub-mkrescue
RPT_FLAGS = -ffreestanding -O2 -Wall
SOURCES = $(wildcard lib/*.c)
OBJECTS = $(patsubst lib/%.c, build/%.o, $(SOURCES))
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	GBFLAG += /usr/lib/grub/i386-pc
endif

kenos.iso: kenos.bin
	cp $? isodir/boot/$<
	${MKGRUB} $(GBFLAG) -o $@ isodir

kenos.bin: build/kernel.o build/boot.o $(OBJECTS)
	${CC} -T linker.ld -o $@ -ffreestanding -O2 -nostdlib $^

build:
	mkdir -p $@

build/kernel.o: kernel.c | build
	${CC} -c $< -o $@ -std=gnu99 ${RPT_FLAGS} -Iinclude -Wextra

build/%.o: lib/%.c | build
	${CC} -c $< -o $@ -std=gnu99 ${RPT_FLAGS} -Iinclude -Wextra

build/boot.o: boot.asm | build
	${ASM} -felf32 $< -o $@

.PHONY: clean
clean:
	rm -rf build
	rm -f kenos.bin isodir/boot/kenos.bin kenos.iso
