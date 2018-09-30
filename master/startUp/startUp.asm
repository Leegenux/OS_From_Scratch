[org 0x7c00]    ; BIOS code offset

load_kernel:

switch_protected_mode:

trigger_main:

jmp $

%include "../16BitPrint/16BitPrint.asm"
%include "../32Bit/32BitGPT.asm"
%include "../32Bit/32BitSwitch.asm"

times 510 - ($ - $$) db 0x0
dw 0xaa55