section .text
global get_scan_code
get_scan_code:
.wait
        in al, 0x64 ; read command port to check whether there was a key press
        test al, 1
        jz .wait
        in al, 0x60 ; read data port to get the scan code
        ; mov al, 'Z'
        ret
