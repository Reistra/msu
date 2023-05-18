%include 'io.inc'
section .bss
    N equ 6
    a resd N
section .text
maximum:
    push ebp
    mov ebp, esp
    mov ebx, dword[esp + 8]         ; ebx = a
    mov edx, dword[esp + 12]        ; edx = N
    xor ecx, ecx
    mov eax, dword[ebx + ecx*4]       ; eax = max; eax = a[0]
    inc ecx
    MAX:
        cmp ecx, edx
        je FIN
        cmp eax, dword[ebx + ecx*4]
        jge MOVE
        mov eax, dword[ebx + ecx*4]
        MOVE:
        inc ecx
        jmp MAX
    FIN:
    leave 
    ret
global main
main:
    xor edx, edx
    INPUT:
        cmp edx, N
        je NEXT
        GET_DEC 4, eax
        mov dword[a + edx*4], eax
        inc edx
        jmp INPUT
    NEXT:
        mov ebx, a
        push edx
        push a
        call maximum
        add esp, 8
        PRINT_DEC 4, eax
    xor eax, eax
    ret