_some_function:
    push rbp

    mov rbp, rsp
    mov eax, 0xbaba     ;EAX as return value's container

    pop rbp
    ret