[org 0x7c00]

mov bp, 0x9000       ; Init stack pointers
mov sp, bp

mov bx, 0x78aa      ; Test print_hex
call print_16_hex

call print_16_nl    ; Test print_nl

mov bx, HELLO_WORLD ; Test print_string
call print_16_string


jmp $

HELLO_WORLD:
    db "Hello world!", 0
%include "../../master/16BitPrint/16BitPrint.asm"  ; print_16_string, print_16_hex, print_16_nl

times 510 - ($ - $$) db 0x0
dw 0xaa55
