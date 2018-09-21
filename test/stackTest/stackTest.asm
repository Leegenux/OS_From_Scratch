; Leegenux 2018-09-18

; This piece of code is a standalone boot loader
; It's designed for figuring out the inner machanism of the way the "stack" works
; As I had expected, the pointer points to the little endian. 
; And every push operation starts with decrementation to the pointer by 2 bytes.
; Then write the data into the stack just as the usual way of writting word data into memory.

[org 0x7c00]

mov bp, 0x8000
mov sp, bp

push "A"		; A word was pushed into the mem
push "B"
push "C"

mov ah, 0x0e
mov al, [0x8000]
int 0x10

mov ah, 0x0e
mov al, [0x7ffe]
int 0x10

mov ah, 0x0e
mov al, [0x7ffc]
int 0x10

mov ah, 0x0e
mov al, [0x7ffa]
int 0x10

push bx
push bx
push bx

jmp $

times 510-($-$$) db 0
dw 0xaa55
