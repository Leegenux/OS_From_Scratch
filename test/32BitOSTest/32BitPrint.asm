; Given that the ecx was set to point to the source string

[bits 32]

VIDEO_MEMORY equ 0xb8000      ; The Video memory in 32-bit mode is located at 0xb8000
WHITE_ON_BLACK equ 0x0f

print_32_string:		          ; First you should set the VIDEO_MEMORY iteral
    push ax
    push ebx                  ; Destination pointer (Video memory)
    push ecx                  ; Source string pointer

    print_32_loop:

    mov ebx, VIDEO_MEMORY     ; Set the edx pointing to the video_memory
    mov ah, WHITE_ON_BLACK    ; Set the style of the print
    mov al, [ecx]
    
    cmp al, 0
    je print_32_done

    ; Print and loop (or exit)
    mov [ebx], ax             ; Write the ax to the video memory
    add ebx, 2
    add ecx, 1

    jmp print_32_loop

    print_32_done:
    pop ecx
    pop ebx
    pop ax
    ret

