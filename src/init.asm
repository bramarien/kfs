org 0x7C00
bits 16

main:

        mov ax, 0
        
	hlt

.halt:
	jmp .halt


times 510-($-$$) db 0
dw 0AA55H
