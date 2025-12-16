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

KERNEL_CS equ 0x08		; kernel code segment
KERNEL_DS equ 0x10		; kernel data segment
USER_CS   equ 0x18		; user code segment
USER_DS   equ 0x20		; user data segment

; GDT variables 
GDT_PRESENT   equ 1 << 7
GDT_RING0     equ 0 << 5
GDT_RING3     equ 3 << 5
GDT_CODEDATA  equ 1 << 4

GDT_EXEC      equ 1 << 3
GDT_RW        equ 1 << 1

GDT_GRAN_4K   equ 1 << 7
GDT_32BIT     equ 1 << 6

%macro GDT_ENTRY 4
	; %1 = base
	; %2 = limit
	; %3 = access
	; %4 = flags

	dw %2 & 0xFFFF
	dw %1 & 0xFFFF
	db (%1 >> 16) & 0xFF
	db %3
	db ((%2 >> 16) & 0x0F) | (%4 & 0xF0)
	db (%1 >> 24) & 0xFF
%endmacro

section .gdt
align 8
gdt_start:
	GDT_ENTRY 0, 0, 0, 0																						; null
	GDT_ENTRY 0, 0xFFFFF, GDT_PRESENT | GDT_RING0 | GDT_CODEDATA | GDT_EXEC | GDT_RW, GDT_GRAN_4K | GDT_32BIT	; KERNEL CODE
	GDT_ENTRY 0, 0xFFFFF, GDT_PRESENT | GDT_RING0 | GDT_CODEDATA | GDT_RW, GDT_GRAN_4K | GDT_32BIT				; KERNEL DATA
	GDT_ENTRY 0, 0xFFFFF, GDT_PRESENT | GDT_RING3 | GDT_CODEDATA | GDT_EXEC | GDT_RW, GDT_GRAN_4K | GDT_32BIT	; USER CODE
	GDT_ENTRY 0, 0xFFFFF, GDT_PRESENT | GDT_RING3 | GDT_CODEDATA | GDT_RW, GDT_GRAN_4K | GDT_32BIT				; USER DATA
gdt_end:

gdtr:
	dw gdt_end - gdt_start - 1   ; limit
	dd gdt_start                 ; base

section .bss
align 16
saved_eax: resd 1
saved_ebx: resd 1

stack_bottom:
resb 16384 ; 16 KiB is reserved for stack
stack_top:

section .text
global _start
_start:
	cli
	lgdt [gdtr]
	mov [saved_eax], eax
    	mov [saved_ebx], ebx
	jmp KERNEL_CS:reload_cs

reload_cs:
	mov ax, KERNEL_DS
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	mov esp, stack_top
	
	mov eax, [saved_eax]
	mov ebx, [saved_ebx]
	push ebx
	push eax
	call kernel_main


.hang:
	cli
	hlt
	jmp .hang