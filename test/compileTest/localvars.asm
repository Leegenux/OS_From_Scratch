_localVars:
	push rbp

	mov rbp, rsp
	mov dword ptr [rbp - 4], 0xaabb   ; Store the local variable at the stack, but not under management, which is easier to control.
	mov eax, dword ptr [rbp - 4]	  ; EAX is used as the container of return value

	pop rbp
	ret
	
