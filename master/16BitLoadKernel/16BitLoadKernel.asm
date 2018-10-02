
load_disk:      ; 5 parameters should already have been pre-configured
; 1. dl, ch, dh, cl are respectively "drive number", "cylindar number", "header number" and "starting sector #".
; 2. al will be automatically set to the amount of the sectors read.

    mov ah, 0x02  ; Read and load disk data function
    ; mov al, 0x0f  ; Load 15 sectors totally
    ; mov [BOOT_DRIVE_NUMBER], dl  ;  The BIOS set the dl defaultly as the boot-drive number

    push al
    int 0x13
    jc load_disk_unknown_error
    pop ah

    cmp al, ah      ; Two possible errors handling
    jne load_disk_count_error

    ret 

    load_disk_count_error:
    mov bx, LOAD_DISK_COUNT_ERROR_MSG
    call print_16_string
    jmp os_freeze

    load_disk_unknown_error:
    mov bx, LOAD_DISK_UNKNOWN_ERROR_MSG
    call print_16_string
    jmp os_freeze

load_kernel:
    mov bx, LOAD_KERNEL_MSG
    call print_16_string

    mov dl, [BOOT_DRIVE_NUMBER] ; Drive number
    mov al, 0x0f    ; Sectors expected = 15
    mov ch, 0x00    ; Cylinder #0
    mov dh, 0x00    ; Head #0
    mov cl, 0x02    ; Sector #2
    call load_disk

BOOT_DRIVE_NUMBER: db 0x00     ; Constant temporarily storing value of drive number, dl  ; 
LOAD_DISK_COUNT_ERROR_MSG: db "load disk count error.", 0x0a, 0x0d , 0x00
LOAD_DISK_UNKNOWN_ERROR_MSG: db "load disk unknown error.", 0x0a, 0x0d, 0x00
LOAD_KERNEL_MSG: db "Start to load kernel...", 0x0a, 0x0d, 0x00





