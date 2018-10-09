C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h)

OBJ = ${C_SOURCES:.c=.o}

CC = /usr/local/i386elfgcc/bin/i386-elf-gcc
LD = /usr/local/i386elfgcc/bin/i386-elf-ld
GDB = /usr/local/i386elfgcc/bin/i386-elf-gdb
ASM = nasm

CFLAGS = -g

os_image.bin: startUp/startUp.bin kernel/kernel.bin
	cat $^ > os_image.bin

kernel/kernel.bin: kernel/kernel_entry.o ${OBJ}
	${LD} -o $@ -Ttext 0x1000 $^ --oformat binary

kernel/kernel.elf: kernel/kernel_entry.o ${OBJ}
	${LD} -o $@ -Ttext 0x1000 $^

startUp/startUp.bin: startUp/startUp.asm
	cd startUp && nasm -f bin -o startUp.bin startUp.asm

run: os_image.bin
	qemu-system-i386 -fda os_image.bin

debug: os_image.bin kernel/kernel.elf
	qemu-system-i386 -s -fda os_image.bin &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel/kernel.elf"

%.o: %.c ${HEADERS}
	${CC}  ${CFLAGS} -ffreestanding -c $< -o $@

%.o: %.asm 
	${ASM} $< -f elf -o $@

%.bin: %.asm
	${ASM} $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o os_image.bin *.elf
	rm -rf kernel/*.o startUp/*.bin drivers/*.o kernel/*.bin kernel/*.elf