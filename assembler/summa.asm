%include 'io.inc'
section .bss
    N equ 5
    a resd N
    b resd N
    c resd N
section .text
sum:
    push ebp
    mov ebp, esp
    mov edx, dword[esp + 20]        ; edx = N
    xor ecx, ecx
    SUMMA:
        cmp ecx, edx
        je MOVE
        mov eax, dword[b + ecx*4]
        add dword[a + ecx*4], eax   ; a[i] := a[i] + b[i]
        mov eax, dword[a + ecx*4]
        mov dword[c + ecx*4], eax   ; c[i] := a[i] + b[i]
        inc ecx
        jmp SUMMA
    MOVE:
    xor ecx, ecx
    OUTPUT:
        cmp ecx, edx
        je FIN
        mov eax, dword[c + ecx*4]
        PRINT_DEC 4, eax
        PRINT_CHAR ' '
        inc ecx
        jmp OUTPUT
    FIN:
    leave 
    ret
global main
main:
    xor edx, edx
    INPUT_A:
        cmp edx, N
        je NE
        GET_DEC 4, eax
        mov dword[a + edx*4], eax
        inc edx
        jmp INPUT_A
    NE:
    xor edx, edx
    INPUT_B:
        cmp edx, N
        je NEXT
        GET_DEC 4, eax
        mov dword[b + edx*4], eax
        inc edx
        jmp INPUT_B
    NEXT:
        push edx
        mov ebx, c
        push ebx
        mov ebx, b
        push ebx
        mov ebx, a
        push ebx
        call sum
        add esp, 16
    xor eax, eax
    ret