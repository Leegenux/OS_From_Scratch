; One requirement of the file is: [BOOT_DISK_NUMBER] should have already set.
[bits 16]
load_disk:      ; 5 parameters should already have been pre-configured
; 1. dl, ch, dh, cl are respectively "drive number", "cylindar number", "header number" and "starting sector #".
; 2. al will be automatically set to the amount of the sectors read.
    pusha

    ; Set the interrupt code
    mov ah, 0x02  ; Read and load disk data function
    ; mov al, 0x0f  ; Load 15 sectors totally
    ; mov dl, [BOOT_DRIVE_NUMBER]  ;  The BIOS set the dl defaultly as the boot-drive number

    ; Trigger the interrupt and handle errors aferwards
    push ax ; Need value of al
    int 0x13
    pop bx
    jc load_disk_unknown_error

    cmp al, bl      ; Two possible errors handling
    jne load_disk_count_error

    popa
    ret 

    ; Two possible errors and handling
    load_disk_count_error:
    mov bx, LOAD_DISK_COUNT_ERROR_MSG
    call print_16_string
    jmp os_freeze

    load_disk_unknown_error:
    mov bx, LOAD_DISK_UNKNOWN_ERROR_MSG
    call print_16_string
    jmp os_freeze

load_kernel:
    pusha

    ; Prompt
    mov bx, LOAD_KERNEL_MSG
    call print_16_string

    ; Set up parameters for loading kernel data
    mov al, 0x0f   ; Sectors expected = 15
    mov dl, [BOOT_DRIVE_NUMBER] ; Drive number
    mov ch, 0x00    ; Cylinder #0
    mov dh, 0x00    ; Head #0
    mov cl, 0x02    ; Sector #2
    mov bx, [KERNEL_SEGMENT]
    mov es, bx
    mov bx, [KERNEL_OFFSET]

    ; Call the load_disk function
    call load_disk
    mov bx, LOAD_KERNEL_DONE_MSG
    call print_16_string

    popa
    ret

os_freeze:
    jmp os_freeze

; Some friend variables
BOOT_DRIVE_NUMBER: db 0x00     ; Constant temporarily storing value of drive number, dl  ; 
KERNEL_OFFSET: dw 0x1000       ; Offset where the kernel will be stored
KERNEL_SEGMENT: dw 0x0000      ; Segment registers value 

LOAD_DISK_COUNT_ERROR_MSG: db "load disk count error.", 0x0a, 0x0d , 0x00
LOAD_DISK_UNKNOWN_ERROR_MSG: db "load disk unknown error.", 0x0a, 0x0d, 0x00
LOAD_KERNEL_MSG: db "Start to load kernel...", 0x0a, 0x0d, 0x00
LOAD_KERNEL_DONE_MSG: db "Done loading kernel code...", 0x0a, 0x0d, 0x00

; DEBUG_BOOT_DISK_NUMBER_MSG: db "[DEBUG] BOOT_DISK_NUMBER: ", 0x0a, 0x0d, 0x00






