_callee:
    push ebp
    mov ebp, esp
    sub esp, 0x10   ; 16 bytes (each int takes 4)

    ; Division with result in eax
    mov eax, dword ptr [ebp+0xc] ; One int far from stack top (@param b)
    cdq
    idiv dword ptr [ebp+0x10]    ; Top int (@param c)

    ; Add division result and @param a
    mov edx, eax
    mov eax, dword ptr [ebp+0x8] ; (@param a)
    add eax, edx

    ; Store the d into ebp-0x4
    mov dword ptr [ebp-0x4], eax

    ; Return the result
    mov eax, dword ptr [ebp-0x4]
    leave
    ret
