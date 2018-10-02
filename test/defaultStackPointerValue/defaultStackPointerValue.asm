; Turns out that:
; 1. Stack pointer for x86-64 architecture do have a default value, which should be considered reasonable because the first program gotten running is BIOS,
; and it has already put the stack into use.
; 2. [org 0x7c00] does not produce any effect on the registers, looks like it only modifies instructions like this `mov [0x9000], cx`

[bits 16]
mov bx, bp
call print_16_hex
call print_16_nl

mov bx, sp
call print_16_hex
call print_16_nl

[org 0x7c00]
mov bx, bp
call print_16_hex
call print_16_nl

mov bx, sp
call print_16_hex
call print_16_nl

jmp $

%include "../../master/16BitPrint/16BitPrint.asm"


; Suffix always needed for a standalone bootloader
times 510 - ($ - $$) db 0
dw 0xaa55
