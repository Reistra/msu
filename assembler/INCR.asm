%include 'io.inc'

%macro INCR  1
 add dword[%1], 1
 adc dword[%1 + 4], 0
%endmacro

section .data
x dq 0xFC20
y dq 0x1FFFFFFF

section .text
global CMAIN
CMAIN:
    INCR x
    INCR y
    PRINT_HEX 4, [x+4]
    PRINT_CHAR ' '
    PRINT_HEX 4, [x]
    NEWLINE
    
    PRINT_HEX 4, [y+4]
    PRINT_CHAR ' '
    PRINT_HEX 4, [y]
    NEWLINE
    
    xor eax, eax
    ret