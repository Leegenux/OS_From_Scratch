[org 0x7c00]

mov bp 0x9000
mov sp, bp

mov 

jmp $

%include "../../master/16BitPrint/16BitPrint.asm"  ; print_16_string, print_16_hex, print_16_nl

times 510 - ($ - $$) db 0x0
dw 0xaa55
