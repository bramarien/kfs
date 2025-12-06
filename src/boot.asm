global start
extern kmain


section .text
bits 32
start:
	call kmain
	hlt
	; printing hello world in green.
	; mov word [0xb8000], 0x0248 ; H
	; mov word [0xb8002], 0x0245 ; E
	; mov word [0xb8004], 0x024C ; L
	; mov word [0xb8006], 0x024C ; L
	; mov word [0xb8008], 0x024F ; O
	; mov word [0xb800A], 0x0220 ; 
	; mov word [0xb800C], 0x0257 ; W
	; mov word [0xb800E], 0x024F ; O
	; mov word [0xb8010], 0x0252 ; R
	; mov word [0xb8012], 0x024C ; L
	; mov word [0xb8014], 0x0244 ; D
	; hlt
