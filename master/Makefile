# Variable groups
C_SOURCES = $(wildcard kernel/*.c drivers/*.c constants/*.c cpu/*.c)   # Needs modification if any new C source folder is created 
HEADERS = $(wildcard kernel/*.h drivers/*.h constants/*.h cpu/*.h)

OBJ = ${C_SOURCES:.c=.o}
# Tools, the i386 directory should have been added into the $PATH

CC = i386-elf-gcc
LD = i386-elf-ld
GDB = i386-elf-gdb
ASM = nasm
EMU = qemu-system-i386

# Flags
CFLAGS = -g
CXXFLAGS = -g

# $^ --- deps(multiple)
# $@ --- target
# $< --- first dep

os_image.bin: startUp/startUp.bin kernel/kernel.bin
	cat $^ > $@

kernel/kernel.bin: kernel/kernel_entry.o ${OBJ}
	${LD} -o $@ -Ttext 0x1000 $^ --oformat binary

kernel/kernel.elf: kernel/kernel_entry.o ${OBJ}
	${LD} -o $@ -Ttext 0x1000 $^

startUp/startUp.bin: startUp/startUp.asm  # Nasm needs working directory as current directory while handling %include links.
	cd startUp && nasm -f bin -o startUp.bin startUp.asm

run: os_image.bin  # Set starting from floppy disk with -fda
	${EMU} -fda $<

debug: os_image.bin kernel/kernel.elf    ## Here -S suspends the program from running and waits for the gdb, and -s specifies the default port for remote debuggin.
	${EMU} -S -s -fda os_image.bin &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel/kernel.elf" -ex "b main" -ex "c"

%.o: %.c ${HEADERS}
	${CC}  ${CFLAGS} -ffreestanding -c $< -o $@

%.o: %.asm 
	${ASM} $< -f elf -o $@

%.bin: %.asm
	${ASM} $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o os_image.bin *.elf
	rm -rf kernel/*.o startUp/*.bin drivers/*.o kernel/*.bin kernel/*.elf constants/*.o