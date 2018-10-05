[org 0x7c00]

    mov bp, 0x9000
    mov sp, bp

    mov bx, MSG_REAL_MODE
    call print_16_string
    call switch_to_pm

    jmp $

%include "../../master/16BitPrint/16BitPrint.asm"
%include "../../master/32Bit/32BitGDT.asm"
%include "../../master/32Bit/32BitSwitch.asm"
%include "../../master/32BitPrint/32BitPrint.asm"

[bits 32]
begin_pm:
    mov ecx, MSG_PROT_MODE
    call print_32_string
    jmp $

MSG_REAL_MODE: db "Started in 16-bit Real mode...", 0x0a, 0x0d, 0
MSG_PROT_MODE: db "Successfully landed in 32-bit Protected Mode          "

times 510 - ($ - $$) db 0
dw 0xaa55