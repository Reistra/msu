%include 'io.inc'
section .text
del:
    push ebp
    mov ebp, esp
    mov eax, dword[ebp + 8]     ; eax = a
    mov ecx, 1                  ; ecx = del
    imul ecx, ecx               ; ecx := del*del, go til the square
    cmp ecx, 0xFFFF             ; ecx = 2^16
    cmp ecx, eax
    
    leave
    ret
    
global main
main:
    INPUT:
        GET_DEC 4, eax
        push eax
        call del
        add esp, 4
    xor eax, eax
    ret