[bits 16]
switch_to_pm:   ; Protected mode
    cli         ; Disable interrupt
    lgdt [gdt_descriptor]   ; Load the GDT descriptor

    mov eax, cr0            ; Set the least bit(32-bit mode flag bit) to 1
    or eax, 0x1
    mov cr0, eax

    ; Current stage: the segmentation approach is changed. CODE_SEG is just a offset to the GDT_STARTR
    jmp CODE_SEG:init_pm    ; Far jump by using a different segment

[bits 32]
init_pm:       
    mov ax, DATA_SEG       ; Update the segment registers
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gx, ax

    mov ebp, 0x90000        ; Update the stack registers
    mov esp, ebp

    call BEGIN_PM