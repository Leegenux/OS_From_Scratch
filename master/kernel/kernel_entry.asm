[bits 32]       ; It's really important to put it at the first place at the link time.
[extern main]
call main;
jmp $