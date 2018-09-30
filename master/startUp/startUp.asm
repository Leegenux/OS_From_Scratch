; This file is the main driver of the startup process

[org 0x7c00]    ; BIOS code offset

load_kernel:    ; Load kernel at 0x1000

switch_protected_mode:

trigger_main:

jmp $

%include "../16BitPrint/16BitPrint.asm"
%include "../32Bit/32BitGPT.asm"
%include "../32Bit/32BitSwitch.asm"

times 510 - ($ - $$) db 0x0
dw 0xaa55