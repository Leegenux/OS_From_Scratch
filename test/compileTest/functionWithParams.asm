_functionWithParams:
    push rbp
    mov rbp, rsp

    mov dword ptr [rbp - 4], edi   ; The params are stored in EDI, ESI.
    mov dword ptr [rbp - 8], esi
    mov esi, dword ptr [rbp - 4]   ; 
    add esi, dword ptr [rbp - 8]

    ; Return value
    mov eax, esi
    pop rbp
    ret