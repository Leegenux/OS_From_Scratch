; This file is the main driver of the startup process

[org 0x7c00]    ; BIOS code offset
BIOS_CODE_OFFSET equ 0x7c00

mov [BOOT_DRIVE_NUMBER], dl

mov bp, 0x9000  ; Set up stack
mov sp, bp

; Load the kernel at offset 0x1000
; mov [KERNEL_OFFSET], 0x1000
; mov [KERNEL_SEGMENT], 0x0000
; Above are defaults
call load_kernel
call switch_to_pm

[bits 32]
begin_pm:       ; This label is required by 32BitSwitch
call 0x1000 ; Remember that if your KERNEL_SEGMENT is not 0x0000
                   ; Then here is supposed to be some tuning.
jmp $

%include "../16BitPrint/16BitPrint.asm"
%include "../16BitLoadKernel/16BitLoadKernel.asm"
%include "../32Bit/32BitGDT.asm"
%include "../32Bit/32BitSwitch.asm"
%include "../32BitPrint/32BitPrint.asm"

times 510 - ($ - $$) db 0x0
dw 0xaa55

; times 0x1e00 db 0x00  ; 15 sectors
; To avoid read disk error, use -boot or -fda flags while exec qemu

; Remember this number qemu: Trying to execute code outside RAM or ROM at 0x00000000ff007d50