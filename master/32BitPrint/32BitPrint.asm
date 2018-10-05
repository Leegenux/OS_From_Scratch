; Given that the ecx was set to point to the source string
; ecx contains the parameter
[bits 32]

VIDEO_MEMORY equ 0xb8000      ; The Video memory in 32-bit mode is located at 0xb8000
WHITE_ON_BLACK equ 0x0f

print_32_string:		      ; First you should set the VIDEO_MEMORY iteral
    push ax
    push ebx                  ; Source string pointer                
    push ecx                  ; Destination pointer (Video memory)

    ; Init
    mov ah, WHITE_ON_BLACK    ; Set the style of the print
    mov ecx, VIDEO_MEMORY     ; Set the  pointing to the video_memory

    print_32_loop:

    ; Check and print
    mov al, [ebx]
    cmp al, 0
    je print_32_done

    ; Print and loop (or exit)
    mov [ecx], ax             ; Write the ax to the video memory
    add ecx, 2
    add ebx, 1

    jmp print_32_loop

    print_32_done:
    pop ecx
    pop ebx
    pop ax
    ret

PROTECT_MODE_MSG: db "Entered protect mode.     ", 0

