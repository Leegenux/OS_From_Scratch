[bits 32]

VIDEO_MEMORY equ 0xb8000      ; The Video memory in 32-bit mode is located at 0xb8000

print_32_bit:		          ; First you should set the VIDEO_MEMORY iteral
    pusha                     ; Temporarily store register values

    mov edx, VIDEO_MEMORY     ; Set the edx pointing to the video_memory


