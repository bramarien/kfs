; Multiboot2 header + framebuffer request
BITS 32

extern kernel_main

section .multiboot
align 8

MB2_MAGIC            equ 0xe85250d6        ; MULTIBOOT2_HEADER_MAGIC
MB2_ARCH_I386        equ 0
MB2_HEADER_LEN       equ header_end - header_start

header_start:
    dd MB2_MAGIC
    dd MB2_ARCH_I386
    dd MB2_HEADER_LEN
    dd -(MB2_MAGIC + MB2_ARCH_I386 + MB2_HEADER_LEN)

align 8			  ; tag alignment
    dw 5                  ; type = MULTIBOOT_HEADER_TAG_FRAMEBUFFER
    dw 0                  ; flags
    dd 20                 ; size (20 bytes total)
    dd 800                ; width request
    dd 600                ; height request
    dd 32                 ; depth = 32 bpp

align 8
    dw 0                  ; type = END
    dw 0
    dd 8                  ; size = 8 bytes

header_end:

section .text
global _start
_start:

    push ebx
    push eax
    call kernel_main

.hang:
    cli
    hlt
    jmp .hang
