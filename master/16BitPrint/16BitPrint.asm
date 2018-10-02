[org 0x7c00]
; [bits 16] is not must, cuz this function can be used both in 16-bit and 32-bit

print_16_string:    ; Given that the address has been stored in bx
    push ax
    push bx
    mov ah, 0x0e    ; TTY
    
    print_16_string_loop:
    mov al, [bx]
    
    cmp al, 0x0  ; Jump handling
    je print_16_string_done

    int 0x10
    inc bx
    jmp print_16_string_loop

    print_16_string_done:
    pop bx
    pop ax
    ret

; print_16_string:
;     push ax

print_16_hex:   ; The hex code to be printed is stored in bx
    pusha

    mov ah, 0x0e
    mov cx, 0x4

    mov al, "0"     ; Prefix
    int 0x10
    mov al, "x"
    int 0x10

    print_16_hex_loop:
    dec cx          ; Decrement the loop count

    mov al, 0x0f    ; Rotate left and get the least four bits of bx
    rol bx, 4
    and al, bl

    cmp al, 0x0a ; Decode using ASCII code table
    jl less_than_ten

    greater_than_ten:
    add al, "a" - 0x0a
    jmp done_decode

    less_than_ten:
    add al, "0"

    done_decode:
    int 0x10

    cmp cx, 0x0
    jne print_16_hex_loop

    popa
    ret

print_16_nl:
    push ax
    
    mov ah, 0x0e
    mov al, 0x0a ; newline char
    int 0x10
    mov al, 0x0d ; carriage return
    int 0x10
    
    pop ax
    ret


