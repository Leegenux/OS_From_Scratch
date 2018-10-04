[bits 16]

; Set up disk
mov bp, 0x9000
mov sp, bp

mov [BOOT_DRIVE_NUMBER], dl

mov bx, 0x0901      ; Load the disk
mov es, bx
mov bx, 0x0000
mov al, 0x05
mov dl, [BOOT_DRIVE_NUMBER]
mov ch, 0x00
mov dh, 0x00
mov cl, 0x02

call load_disk

mov bx, 0x0901      ; Print the read data result
mov ds, bx
mov bx, [512]
call print_16_hex
call print_16_nl
mov bx, [1024]
call print_16_hex
call print_16_nl
mov bx, [1536]
call print_16_hex
call print_16_nl
mov bx, [2048]
call print_16_hex
call print_16_nl
mov bx, [2560]
call print_16_hex
call print_16_nl

jmp $

%include "../../master/16BitPrint/16BitPrint.asm"
%include "../../master/16BitLoadKernel/16BitLoadKernel.asm"
; %include "../../master/startUp/startUp.asm"   You should take care of the including behaviour

times 510 - ($ - $$) db 0
dw 0xaa55

times 256 dw 0x1234
times 256 dw 0x2345
times 256 dw 0x3456
times 256 dw 0x4567
times 256 dw 0xabcd
