; One mandotary requirement of running code in this file is that a `begin_pm` label should be well implemented.
; This file is more closely tied to 32BitGPT.asm than any other source file.
[bits 16]
switch_to_pm:   ; Protected mode
    cli         ; 1. Disable incoming interrupt
    lgdt [gdt_descriptor]   ; 2. Load the GDT descriptor

    mov eax, cr0            ; 3. Set the least bit(32-bit mode flag bit) to 1
    or eax, 0x1
    mov cr0, eax

    ; Current stage: the segmentation approach is changed. CODE_SEG is just a offset to the GDT_START
    jmp CODE_S:init_pm    ; 4. Far jump by using a different segment to flush the pipeline (The jump is workable since the code segment actually does not change, which is 0x0000 before and after.)

[bits 32]
init_pm:       
    mov ax, DATA_S       ; 5. Update the segment registers since the inner mechanism of segment has already changed
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax             ; Following two are OS-specific registers
    mov gs, ax

    mov ebp, 0x90000       ; Update the stack registers
    mov esp, ebp

    call begin_pm