gdt_start:      ; The nullptr with which the GPT starts
    dd 0x00000000
    dd 0x00000000

gdt_code:
    dw 0xffff   ; Segment limit [0 - 15]
    dw 0x0000   ; Segment base address [16 - 39] together with the next line
    db 0x00
    db 10011010b ; Segment present set 1, since segment is present in memory - used for virtual memory
    db 11001111b ;
    db 0x00

gdt_data:
    dd 0x0000ffff
    db 0x00
    db 10010010b
    db 11001111b
    db 0x00

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start ; Address should be 32 bits


global CODE_SEG
global DATA_SEG
CODE_SEG: db gdt_code - gdt_start
DATA_SEG: db gdt_data - gdt_start

CODE_S equ gdt_code - gdt_start
DATA_S equ gdt_data - gdt_start

; CODE_SEG equ gdt_code - gdt_start   ; An offset
; DATA_SEG equ gdt_data - gdt_start