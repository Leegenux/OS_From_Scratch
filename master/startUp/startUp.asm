; This file is the main driver of the startup process

[org 0x7c00]    ; BIOS code offset

mov [BOOT_DRIVE_NUMBER], dl

; Load the kernel at offset 0x1000
; mov [KERNEL_OFFSET], 0x1000
; mov [KERNEL_SEGMENT], 0x0000
; Above are defaults
call load_kernel
call switch_to_pm

[bits 32]
begin_pm:       ; This label is required by 32BitSwitch
call KERNEL_OFFSET ; Remember that if your KERNEL_SEGMENT is not 0x0000
                   ; Then here is supposed to be some tuning.

jmp $

%include "../16BitPrint/16BitPrint.asm"
%include "../16BitLoadKernel/16BitLoadKernel.asm"
%include "../32Bit/32BitGPT.asm"
%include "../32Bit/32BitSwitch.asm"

times 510 - ($ - $$) db 0x0
dw 0xaa55